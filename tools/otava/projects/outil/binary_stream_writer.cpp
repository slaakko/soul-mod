// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module util.binary.stream.writer;

import util.unicode;

namespace util {

BinaryStreamWriter::BinaryStreamWriter(Stream& stream_) : stream(stream_)
{
}

std::expected<bool, int> BinaryStreamWriter::Write(bool x)
{
    return Write(std::uint8_t(x));
}

std::expected<bool, int> BinaryStreamWriter::Write(std::uint8_t x)
{
    return stream.Write(x);
}

std::expected<bool, int> BinaryStreamWriter::Write(std::int8_t x)
{
    return Write(static_cast<std::uint8_t>(x));
}

std::expected<bool, int> BinaryStreamWriter::Write(std::uint16_t x)
{
    std::uint8_t b0 = static_cast<std::uint8_t>(x >> 8);
    std::uint8_t b1 = static_cast<std::uint8_t>(x);
    std::expected<bool, int> rv = Write(b0);
    if (!rv) return rv;
    rv = Write(b1);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> BinaryStreamWriter::Write(std::int16_t x)
{
    return Write(static_cast<std::uint16_t>(x));
}

std::expected<bool, int> BinaryStreamWriter::Write(std::uint32_t x)
{
    std::uint8_t b0 = static_cast<std::uint8_t>(x >> 24U);
    std::uint8_t b1 = static_cast<std::uint8_t>(x >> 16U);
    std::uint8_t b2 = static_cast<std::uint8_t>(x >> 8U);
    std::uint8_t b3 = static_cast<std::uint8_t>(x);
    std::expected<bool, int> rv = Write(b0);
    if (!rv) return rv;
    rv = Write(b1);
    if (!rv) return rv;
    rv = Write(b2);
    if (!rv) return rv;
    rv = Write(b3);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> BinaryStreamWriter::Write(std::int32_t x)
{
    return Write(static_cast<std::uint32_t>(x));
}

std::expected<bool, int> BinaryStreamWriter::Write(std::uint64_t x)
{
    std::uint8_t b0 = static_cast<std::uint8_t>(x >> 56);
    std::uint8_t b1 = static_cast<std::uint8_t>(x >> 48);
    std::uint8_t b2 = static_cast<std::uint8_t>(x >> 40);
    std::uint8_t b3 = static_cast<std::uint8_t>(x >> 32);
    std::uint8_t b4 = static_cast<std::uint8_t>(x >> 24);
    std::uint8_t b5 = static_cast<std::uint8_t>(x >> 16);
    std::uint8_t b6 = static_cast<std::uint8_t>(x >> 8);
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
    rv = Write(b7);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> BinaryStreamWriter::Write(std::int64_t x)
{
    return Write(static_cast<std::uint64_t>(x));
}

std::expected<bool, int> BinaryStreamWriter::Write(float x)
{
    std::uint32_t* u = reinterpret_cast<std::uint32_t*>(&x);
    return Write(*u);
}

std::expected<bool, int> BinaryStreamWriter::Write(double x)
{
    std::uint64_t* u = reinterpret_cast<std::uint64_t*>(&x);
    return Write(*u);
}

std::expected<bool, int> BinaryStreamWriter::Write(char x)
{
    return Write(static_cast<std::uint8_t>(x));
}

std::expected<bool, int> BinaryStreamWriter::Write(char8_t x)
{
    return Write(static_cast<std::uint8_t>(x));
}

std::expected<bool, int> BinaryStreamWriter::Write(char16_t x)
{
    return Write(static_cast<std::uint16_t>(x));
}

std::expected<bool, int> BinaryStreamWriter::Write(char32_t x)
{
    return Write(static_cast<std::uint32_t>(x));
}

std::expected<bool, int> BinaryStreamWriter::Write(const std::string& s)
{
    return Write(s, true);
}

std::expected<bool, int> BinaryStreamWriter::Write(const std::string& s, bool writeNull)
{
    for (char c : s)
    {
        std::uint8_t x = static_cast<std::uint8_t>(c);
        std::expected<bool, int> rv = Write(x);
        if (!rv) return rv;
    }
    if (writeNull)
    {
        std::expected<bool, int> rv = Write(static_cast<std::uint8_t>(0));
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> BinaryStreamWriter::Write(const std::u16string& s)
{
    std::expected<std::string, int> utf8rv = ToUtf8(s);
    if (!utf8rv) return std::unexpected<int>(utf8rv.error());
    const std::string& utf8_str = *utf8rv;
    return Write(utf8_str);
}

std::expected<bool, int> BinaryStreamWriter::Write(const std::u32string& s)
{
    std::expected<std::string, int> utf8rv = ToUtf8(s);
    if (!utf8rv) return std::unexpected<int>(utf8rv.error());
    const std::string& utf8_str = *utf8rv;
    return Write(utf8_str);
}

std::expected<bool, int> BinaryStreamWriter::WriteULEB128UInt(std::uint32_t x)
{
    do
    {
        std::uint8_t b = x & 0x7FU;
        x >>= 7u;
        if (x != 0)
        {
            b |= static_cast<std::uint8_t>(0x80);
        }
        std::expected<bool, int> rv = Write(b);
        if (!rv) return rv;
    } while (x != 0);
    return std::expected<bool, int>(true);
}

std::expected<bool, int> BinaryStreamWriter::WriteULEB128ULong(std::uint64_t x)
{
    do
    {
        std::uint8_t b = x & 0x7F;
        x >>= 7;
        if (x != 0)
        {
            b |= static_cast<std::uint8_t>(0x80);
        }
        std::expected<bool, int> rv = Write(b);
        if (!rv) return rv;
    } while (x != 0);
    return std::expected<bool, int>(true);
}

std::expected<bool, int> BinaryStreamWriter::WriteSLEB128Int(std::int32_t x)
{
    bool more = true;
    bool negative = x < 0;
    while (more)
    {
        std::uint8_t b = x & 0x7F;
        x >>= 7;
        if (negative)
        {
            x |= ~std::int32_t(0) << (32 - 7);
        }
        if (x == 0 && (b & 0x40) == 0 || x == -1 && (b & 0x40) != 0)
        {
            more = false;
        }
        else
        {
            b |= static_cast<std::uint8_t>(0x80);
        }
        std::expected<bool, int> rv = Write(b);
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> BinaryStreamWriter::WriteSLEB128Long(std::int64_t x)
{
    bool more = true;
    bool negative = x < 0;
    while (more)
    {
        std::uint8_t b = x & 0x7F;
        x >>= 7;
        if (negative)
        {
            x |= ~std::int64_t(0) << (64 - 7);
        }
        if (x == 0 && (b & 0x40) == 0 || x == -1 && (b & 0x40) != 0)
        {
            more = false;
        }
        else
        {
            b |= static_cast<std::uint8_t>(0x80);
        }
        std::expected<bool, int> rv = Write(b);
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> BinaryStreamWriter::Write(const uuid& id)
{
    for (uuid::value_type x : id)
    {
        std::expected<bool, int> rv = Write(x);
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> BinaryStreamWriter::WriteTime(time_t time)
{
    return Write(static_cast<std::int64_t>(time));
}

} // namespace util
