// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module util.memory.stream;

namespace util {

MemoryStream::MemoryStream() : Stream(), data(), size(), readPos(0)
{
}

MemoryStream::MemoryStream(std::uint8_t* data_, std::int64_t size_) : Stream(), data(data_), size(size_), readPos(0)
{
}

std::expected<int, int> MemoryStream::ReadByte()
{
    if (readPos < size)
    {
        SetPosition(Position() + 1);
        return std::expected<int, int>(data[readPos++]);
    }
    return std::expected<int, int>(-1);
}

std::expected<std::int64_t, int> MemoryStream::Read(std::uint8_t* buf, std::int64_t count)
{
    std::int64_t bytesRead = 0;
    std::int64_t n = size;
    while (count > 0 && readPos < n)
    {
        *buf++ = data[readPos++];
        ++bytesRead;
        --count;
    }
    SetPosition(Position() + bytesRead);
    return std::expected<std::int64_t, int>(bytesRead);
}

std::expected<bool, int> MemoryStream::Write(std::uint8_t x)
{
    content.push_back(x);
    SetPosition(Position() + 1);
    return std::expected<bool, int>(true);
}

std::expected<bool, int> MemoryStream::Write(std::uint8_t* buf, std::int64_t count)
{
    std::int64_t bytesWritten = 0;
    while (count > 0)
    {
        content.push_back(*buf++);
        --count;
        ++bytesWritten;
    }
    SetPosition(Position() + bytesWritten);
    return std::expected<bool, int>(true);
}

std::expected<bool, int> MemoryStream::Seek(std::int64_t pos, Origin origin)
{
    switch (origin)
    {
    case Origin::seekSet:
    {
        readPos = pos;
        SetPosition(readPos);
        break;
    }
    case Origin::seekCur:
    {
        readPos = readPos + pos;
        SetPosition(readPos);
        break;
    }
    case Origin::seekEnd:
    {
        readPos = size + pos;
        SetPosition(readPos);
        break;
    }
    }
    return std::expected<bool, int>(true);
}

std::expected<std::int64_t, int> MemoryStream::Tell()
{
    return std::expected<std::int64_t, int>(readPos);
}

void MemoryStream::SetFromContent()
{
    data = content.data();
    size = content.size();
    readPos = 0;
    SetPosition(readPos);
}

} // namespace util
