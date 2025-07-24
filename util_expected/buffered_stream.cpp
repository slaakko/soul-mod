// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module util_expected.buffered.stream;

import util_expected.stream;

namespace util {

BufferedStream::BufferedStream(Stream& baseStream_) : BufferedStream(baseStream_, 4096)
{
}

BufferedStream::BufferedStream(Stream& baseStream_, std::int64_t bufferSize_) :
    Stream(), baseStream(baseStream_), bufferSize(bufferSize_), buffer(static_cast<std::uint8_t*>(std::malloc(bufferSize))), pos(bufferSize), bytesAvailable(0), end(0)
{
}

BufferedStream::~BufferedStream()
{
    std::expected<bool, int> rv = Flush();
}

std::expected<int, int> BufferedStream::ReadByte()
{
    std::expected<bool, int> frv = Flush();
    if (!frv) return std::unexpected<int>(frv.error());
    if (bytesAvailable == 0)
    {
        frv = FillBuf();
        if (!frv) return std::unexpected<int>(frv.error());
        if (bytesAvailable == 0)
        {
            return std::expected<int, int>(-1);
        }
    }
    std::uint8_t* b = buffer.get();
    std::uint8_t value = b[pos++];
    --bytesAvailable;
    SetPosition(Position() + 1);
    return std::expected<int, int>(value);
}

std::expected<std::int64_t, int> BufferedStream::Read(std::uint8_t* buf, std::int64_t count)
{
    std::expected<bool, int> frv = Flush();
    if (!frv) return std::unexpected<int>(frv.error());
    if (bytesAvailable == 0)
    {
        frv = FillBuf();
        if (!frv) return std::unexpected<int>(frv.error());
    }
    std::int64_t bytesRead = 0;
    std::int64_t n = std::min(bytesAvailable, count);
    for (std::int64_t i = 0; i < n; ++i)
    {
        std::uint8_t* b = buffer.get();
        buf[i] = b[pos++];
        ++bytesRead;
        --bytesAvailable;
    }
    SetPosition(Position() + bytesRead);
    return std::expected<std::int64_t, int>(bytesRead);
}

std::expected<bool, int> BufferedStream::Write(std::uint8_t x)
{
    if (end >= bufferSize)
    {
        std::expected<bool, int> frv = Flush();
        if (!frv) return std::unexpected<int>(frv.error());
    }
    std::uint8_t* b = buffer.get();
    b[end++] = x;
    SetPosition(Position() + 1);
    return std::expected<bool, int>(true);
}

std::expected<bool, int> BufferedStream::Write(std::uint8_t* buf, std::int64_t count)
{
    for (std::int64_t i = 0; i < count; ++i)
    {
        std::expected<bool, int> rv = Write(buf[i]);
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> BufferedStream::Flush()
{
    if (end != 0)
    {
        std::expected<bool, int> rv = baseStream.Write(buffer.get(), end);
        if (!rv) return rv;
        rv = baseStream.Flush();
        if (!rv) return rv;
        end = 0;
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> BufferedStream::Seek(std::int64_t pos, Origin origin)
{
    std::expected<bool, int> rv = Flush();
    if (!rv) return rv;
    bytesAvailable = 0;
    rv = baseStream.Seek(pos, origin);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<std::int64_t, int> BufferedStream::Tell()
{
    std::expected<bool, int> rv = Flush();
    if (!rv) return rv;
    std::expected<std::int64_t, int> trv = baseStream.Tell();
    if (!trv) return std::unexpected<int>(trv.error());
    return std::expected<std::int64_t, int>(*trv - bytesAvailable);
}

std::expected<bool, int> BufferedStream::FillBuf()
{
    std::expected<std::int64_t, int> rv = baseStream.Read(buffer.get(), bufferSize);
    if (!rv) return rv;
    bytesAvailable = *rv;
    pos = 0;
    return std::expected<bool, int>(true);
}

} // namespace util
