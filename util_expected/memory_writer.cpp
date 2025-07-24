// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module util_expected.memory.writer;

import util_expected.error;

namespace util {

MemoryWriter::MemoryWriter(std::uint8_t* ptr_, std::int64_t count_) : ptr(ptr_), pos(ptr), count(count_)
{
}

std::expected<bool, int> MemoryWriter::Write(std::uint8_t x)
{
    if (pos - ptr >= count)
    {
        return std::unexpected<int>(AllocateError("memory writer: end of space"));
    }
    *pos++ = x;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> MemoryWriter::Write(std::int8_t x)
{
    return Write(static_cast<std::uint8_t>(x));
}

std::expected<bool, int> MemoryWriter::Write(std::uint16_t x)
{
    std::uint8_t b0 = static_cast<std::uint8_t>(x >> 8u);
    std::uint8_t b1 = static_cast<std::uint8_t>(x);
    std::expected<bool, int> rv = Write(b0);
    if (!rv) return rv;
    return Write(b1);
}

std::expected<bool, int> MemoryWriter::Write(std::int16_t x)
{
    return Write(static_cast<std::uint16_t>(x));
}

std::expected<bool, int> MemoryWriter::Write(std::uint32_t x)
{
    std::uint8_t b0 = static_cast<std::uint8_t>(x >> 24u);
    std::uint8_t b1 = static_cast<std::uint8_t>(x >> 16u);
    std::uint8_t b2 = static_cast<std::uint8_t>(x >> 8u);
    std::uint8_t b3 = static_cast<std::uint8_t>(x);
    std::expected<bool, int> rv = Write(b0);
    if (!rv) return rv;
    rv = Write(b1);
    if (!rv) return rv;
    rv = Write(b2);
    if (!rv) return rv;
    return Write(b3);
}

std::expected<bool, int> MemoryWriter::Write(std::int32_t x)
{
    return Write(static_cast<std::uint32_t>(x));
}

std::expected<bool, int> MemoryWriter::Write(std::uint64_t x)
{
    std::uint8_t b0 = static_cast<std::uint8_t>(x >> 56u);
    std::uint8_t b1 = static_cast<std::uint8_t>(x >> 48u);
    std::uint8_t b2 = static_cast<std::uint8_t>(x >> 40u);
    std::uint8_t b3 = static_cast<std::uint8_t>(x >> 32u);
    std::uint8_t b4 = static_cast<std::uint8_t>(x >> 24u);
    std::uint8_t b5 = static_cast<std::uint8_t>(x >> 16u);
    std::uint8_t b6 = static_cast<std::uint8_t>(x >> 8u);
    std::uint8_t b7 = static_cast<std::uint8_t>(x);
    std::expected<bool, int> rv = Write(b0);
    if (!rv) return rv;
    rv = Write(b1);
    if (!rv) return rv;
    rv = Write(b2);
    if (!rv) return rv;
    rv = Write(b3);
    if (!rv) return rv;
    rv = Write(b4);
    if (!rv) return rv;
    rv = Write(b5);
    if (!rv) return rv;
    rv = Write(b6);
    if (!rv) return rv;
    return Write(b7);
}

std::expected<bool, int> MemoryWriter::Write(std::int64_t x)
{
    return Write(static_cast<std::uint64_t>(x));
}

std::expected<bool, int> MemoryWriter::Write(const DateTime& dt)
{
    Date date = dt.GetDate();
    std::expected<bool, int> rv = Write(date.Year());
    if (!rv) return rv;
    rv = Write(static_cast<std::int8_t>(date.GetMonth()));
    if (!rv) return rv;
    rv = Write(date.Day());
    if (!rv) return rv;
    return Write(dt.Seconds());
}

std::expected<bool, int> MemoryWriter::Write(const std::string& str)
{
    for (char c : str)
    {
        std::expected<bool, int> rv = Write(static_cast<std::uint8_t>(c));
        if (!rv) return rv;
    }
    return Write(static_cast<std::uint8_t>(0u));
}

} // namespace util
