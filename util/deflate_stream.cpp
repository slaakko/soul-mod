// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module;
#include <util/ZlibInterface.h>
#ifdef NDEBUG
#pragma comment(lib, "zlibstat.lib")
#else 
#pragma comment(lib, "zlibstatd.lib")
#endif

module util.deflate.stream;

namespace util {

#ifndef SOUL_CPP20

DeflateStream::DeflateStream(CompressionMode mode_, Stream& underlyingStream_) : DeflateStream(mode_, underlyingStream_, 16384)
{
}

DeflateStream::DeflateStream(CompressionMode mode_, Stream& underlyingStream_, std::int64_t bufferSize_) : DeflateStream(mode_, underlyingStream_, bufferSize_, defaultDeflateCompressionLevel)
{
}

DeflateStream::DeflateStream(CompressionMode mode_, Stream& underlyingStream_, std::int64_t bufferSize_, int compressionLevel_) :
    Stream(), mode(mode_), underlyingStream(underlyingStream_), bufferSize(bufferSize_), compressionLevel(compressionLevel_),
    inAvail(0), in(new std::uint8_t[bufferSize]), outAvail(0), outPos(0), outHave(0), endOfInput(false), endOfStream(false), out(new std::uint8_t[bufferSize]),
    handle(nullptr)
{
    SetPosition(underlyingStream.Position());
    int ret = zlib_init(std::int32_t(mode), compressionLevel, &handle);
    if (ret < 0)
    {
        throw std::runtime_error("could not create deflate stream: zlib initialization returned error code " + std::to_string(ret));
    }
}

DeflateStream::~DeflateStream()
{
    if (handle)
    {
        try
        {
            if (mode == CompressionMode::compress)
            {
                Finish();
            }
        }
        catch (...)
        {
        }
        zlib_done(std::int32_t(mode), handle);
    }
}

int DeflateStream::ReadByte()
{
    std::uint8_t x = 0;
    std::int64_t bytesRead = Read(&x, 1);
    if (bytesRead == 0)
    {
        return -1;
    }
    return x;
}

std::int64_t DeflateStream::Read(std::uint8_t* buf, std::int64_t count)
{
    if (mode != CompressionMode::decompress)
    {
        throw std::runtime_error("deflate stream: cannot read in 'compress' compression mode");
    }
    std::int64_t bytesRead = 0;
    do
    {
        if (inAvail == 0 && !endOfInput)
        {
            inAvail = static_cast<std::uint32_t>(underlyingStream.Read(in.get(), static_cast<std::uint32_t>(bufferSize)));
            if (inAvail == 0)
            {
                endOfInput = true;
            }
            zlib_set_input(in.get(), inAvail, handle);
        }
        do
        {
            if (outHave == 0 && !endOfStream)
            {
                int ret = zlib_inflate(out.get(), static_cast<std::uint32_t>(bufferSize), &outHave, &outAvail, &inAvail, handle);
                if (ret < 0)
                {
                    throw std::runtime_error("deflate stream: could not decompress: inflate returned error code " + std::to_string(ret));
                }
                if (ret == Z_STREAM_END)
                {
                    endOfStream = true;
                }
                outPos = 0;
            }
            while (count > 0 && outHave > 0)
            {
                std::uint8_t* o = out.get();
                *buf++ = o[outPos++];
                --count;
                --outHave;
                ++bytesRead;
            }
        } while (count > 0 && outAvail == 0);
    } while (count > 0 && !endOfStream && !endOfInput);
    if (endOfInput && !endOfStream)
    {
        throw std::runtime_error("deflate stream: unexpected end of input");
    }
    SetPosition(Position() + bytesRead);
    return bytesRead;
}

void DeflateStream::Write(std::uint8_t x)
{
    Write(&x, 1);
}

void DeflateStream::Write(std::uint8_t* buf, std::int64_t count)
{
    if (mode != CompressionMode::compress)
    {
        throw std::runtime_error("deflate stream: cannot write in 'decompress' compression mode");
    }
    std::int64_t bytesWritten = 0;
    while (count > 0)
    {
        std::uint8_t* inP = in.get();
        inAvail = 0;
        while (count > 0 && inAvail < static_cast<std::uint32_t>(bufferSize))
        {
            *inP++ = *buf++;
            --count;
            ++inAvail;
            ++bytesWritten;
        }
        zlib_set_input(in.get(), inAvail, handle);
        do
        {
            std::uint32_t have = 0;
            int ret = zlib_deflate(out.get(), static_cast<std::uint32_t>(bufferSize), &have, &outAvail, handle, Z_NO_FLUSH);
            if (ret < 0)
            {
                throw std::runtime_error("deflate stream: could not compress: deflate returned error code " + std::to_string(ret));
            }
            underlyingStream.Write(out.get(), static_cast<std::int64_t>(have));
        } while (outAvail == 0);
    }
    SetPosition(Position() + bytesWritten);
}

void DeflateStream::Finish()
{
    do
    {
        std::uint32_t have = 0u;
        int ret = zlib_deflate(out.get(), static_cast<std::uint32_t>(bufferSize), &have, &outAvail, handle, Z_FINISH);
        if (ret < 0)
        {
            throw std::runtime_error("deflate stream: could not compress: deflate returned error code " + std::to_string(ret));
        }
        underlyingStream.Write(out.get(), static_cast<std::int64_t>(have));
    } while (outAvail == 0);
}

#endif

} // namespace util
