// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module util.deflate.stream;

import util.error;

namespace util {

DeflateStream::DeflateStream(CompressionMode mode_, Stream& underlyingStream_) : DeflateStream(mode_, underlyingStream_, 16384)
{
}

DeflateStream::DeflateStream(CompressionMode mode_, Stream& underlyingStream_, std::int64_t bufferSize_) :
    DeflateStream(mode_, underlyingStream_, bufferSize_, defaultDeflateCompressionLevel)
{
}

DeflateStream::DeflateStream(CompressionMode mode_, Stream& underlyingStream_, std::int64_t bufferSize_, int compressionLevel_) :
    Stream(), mode(mode_), underlyingStream(underlyingStream_), bufferSize(bufferSize_), compressionLevel(compressionLevel_),
    inAvail(0), in(static_cast<std::uint8_t*>(std::malloc(bufferSize))), outAvail(0), outPos(0), outHave(0), endOfInput(false), endOfStream(false), 
    out(static_cast<std::uint8_t*>(std::malloc(bufferSize))), handle(nullptr), error(0)
{
    SetPosition(underlyingStream.Position());
    int ret = ort_zlib_init(std::int32_t(mode), compressionLevel, &handle);
    if (ret < 0)
    {
        error = AllocateError("could not create deflate stream: zlib initialization returned error code " + std::to_string(ret));
        return;
    }
}

DeflateStream::~DeflateStream()
{
    if (handle)
    {
        if (mode == CompressionMode::compress)
        {
            std::expected<bool, int> rv = Finish();
        }
        ort_zlib_done(std::int32_t(mode), handle);
    }
}

std::expected<int, int> DeflateStream::ReadByte()
{
    if (error != 0) return std::unexpected<int>(error);
    std::uint8_t x = 0;
    std::expected<std::int64_t, int> rv = Read(&x, 1);
    if (!rv) return std::unexpected<int>(rv.error());
    std::int64_t bytesRead = *rv;
    if (bytesRead == 0)
    {
        return std::expected<int, int>(-1);
    }
    return std::expected<int, int>(x);
}

std::expected<std::int64_t, int> DeflateStream::Read(std::uint8_t* buf, std::int64_t count)
{
    if (error != 0) return std::unexpected<int>(error);
    if (mode != CompressionMode::decompress)
    {
        return std::unexpected<int>(AllocateError("deflate stream: cannot read in 'compress' compression mode"));
    }
    std::int64_t bytesRead = 0;
    do
    {
        if (inAvail == 0 && !endOfInput)
        {
            std::expected<std::int64_t, int> rv = underlyingStream.Read(in.get(), static_cast<std::uint32_t>(bufferSize));
            if (!rv) return rv;
            inAvail = static_cast<std::int64_t>(*rv);
            if (inAvail == 0)
            {
                endOfInput = true;
            }
            std::uint32_t uinAvail = static_cast<std::uint32_t>(inAvail);
            ort_zlib_set_input(in.get(), uinAvail, handle);
        }
        do
        {
            if (outHave == 0 && !endOfStream)
            {
                std::uint32_t uoutHave = static_cast<std::uint32_t>(outHave);
                std::uint32_t uinAvail = static_cast<std::uint32_t>(inAvail);
                int ret = ort_zlib_inflate(out.get(), static_cast<std::uint32_t>(bufferSize), &uoutHave, &outAvail, &uinAvail, handle);
                if (ret < 0)
                {
                    return std::unexpected<int>(AllocateError("deflate stream: could not decompress: inflate returned error code " + std::to_string(ret)));
                }
                outHave = static_cast<std::int64_t>(uoutHave);
                inAvail = static_cast<std::int64_t>(uinAvail);
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
        return std::unexpected<int>(AllocateError("deflate stream: unexpected end of input"));
    }
    SetPosition(Position() + bytesRead);
    return std::expected<std::int64_t, int>(bytesRead);
}

std::expected<bool, int> DeflateStream::Write(std::uint8_t x)
{
    if (error != 0) return std::unexpected<int>(error);
    std::expected<bool, int> rv = Write(&x, 1);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> DeflateStream::Write(std::uint8_t* buf, std::int64_t count)
{
    if (error != 0) return std::unexpected<int>(error);
    if (mode != CompressionMode::compress)
    {
        return std::unexpected<int>(AllocateError("deflate stream: cannot write in 'decompress' compression mode"));
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
        std::uint32_t uinAvail = static_cast<std::uint32_t>(inAvail);
        ort_zlib_set_input(in.get(), uinAvail, handle);
        do
        {
            std::uint32_t have = 0;
            int ret = ort_zlib_deflate(out.get(), static_cast<std::uint32_t>(bufferSize), &have, &outAvail, handle, Z_NO_FLUSH);
            if (ret < 0)
            {
                return std::unexpected<int>(AllocateError("deflate stream: could not compress: deflate returned error code " + std::to_string(ret)));
            }
            std::expected<bool, int> rv = underlyingStream.Write(out.get(), static_cast<std::int64_t>(have));
            if (!rv) return rv;
        } while (outAvail == 0);
    }
    SetPosition(Position() + bytesWritten);
    return std::expected<bool, int>(true);
}

std::expected<bool, int> DeflateStream::Finish()
{
    if (error != 0) return std::unexpected<int>(error);
    do
    {
        std::uint32_t have = 0u;
        int ret = ort_zlib_deflate(out.get(), static_cast<std::uint32_t>(bufferSize), &have, &outAvail, handle, Z_FINISH);
        if (ret < 0)
        {
            return std::unexpected<int>(AllocateError("deflate stream: could not compress: deflate returned error code " + std::to_string(ret)));
        }
        std::expected<bool, int> rv = underlyingStream.Write(out.get(), static_cast<std::int64_t>(have));
        if (!rv) return rv;
    } while (outAvail == 0);
    return std::expected<bool, int>(true);
}

} // namespace util
