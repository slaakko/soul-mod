// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module util.binary.stream.reader;

import util.error;
import util.unicode;

namespace util {

BinaryStreamReader::BinaryStreamReader(Stream& stream_) : stream(stream_)
{
}

std::expected<bool, int> BinaryStreamReader::ReadBool()
{
    std::expected<std::uint8_t, int> rv = ReadByte();
    if (!rv) return std::unexpected<int>(rv.error());
    std::uint8_t b = *rv;
    return std::expected<bool, int>(b != 0);
}

std::expected<std::uint8_t, int> BinaryStreamReader::ReadByte()
{
    std::expected<int, int> rv = stream.ReadByte();
    if (!rv) return std::unexpected<int>(rv.error());
    int x = *rv;
    if (x == -1)
    {
        return std::unexpected<int>(AllocateError("unexpected end of stream"));
    }
    return std::expected<std::uint8_t, int>(static_cast<std::uint8_t>(x));
}

std::expected<std::int8_t, int> BinaryStreamReader::ReadSByte()
{
    std::expected<std::uint8_t, int> rv = ReadByte();
    if (!rv) return std::unexpected<int>(rv.error());
    std::uint8_t b = *rv;
    return std::expected<std::int8_t, int>(static_cast<std::int8_t>(b));
}

std::expected<std::uint16_t, int> BinaryStreamReader::ReadUShort()
{
    std::expected<std::uint8_t, int> rv = ReadByte();
    if (!rv) return std::unexpected<int>(rv.error());
    std::uint8_t h = *rv;
    rv = ReadByte();
    if (!rv) return std::unexpected<int>(rv.error());
    std::uint8_t l = *rv;
    return std::expected<std::uint16_t, int>((static_cast<std::uint16_t>(h) << 8) | static_cast<std::uint16_t>(l));
}

std::expected<std::int16_t, int> BinaryStreamReader::ReadShort()
{
    std::expected<std::uint16_t, int> rv = ReadUShort();
    if (!rv) return std::unexpected<int>(rv.error());
    std::uint16_t x = *rv;
    return std::expected<std::int16_t, int>(static_cast<std::int16_t>(x));
}

std::expected<std::uint32_t, int> BinaryStreamReader::ReadUInt()
{
    std::expected<std::uint8_t, int> rv = ReadByte();
    if (!rv) return std::unexpected<int>(rv.error());
    std::uint8_t b0 = *rv;
    rv = ReadByte();
    if (!rv) return std::unexpected<int>(rv.error());
    std::uint8_t b1 = *rv;
    rv = ReadByte();
    if (!rv) return std::unexpected<int>(rv.error());
    std::uint8_t b2 = *rv;
    rv = ReadByte();
    if (!rv) return std::unexpected<int>(rv.error());
    std::uint8_t b3 = *rv;
    return std::expected<std::uint32_t, int>((static_cast<std::uint32_t>(b0) << 24U) | (static_cast<std::uint32_t>(b1) << 16U) | (static_cast<std::uint32_t>(b2) << 8U) |
        static_cast<std::uint32_t>(b3));
}

std::expected<std::int32_t, int> BinaryStreamReader::ReadInt()
{
    std::expected<std::uint32_t, int> rv = ReadUInt();
    if (!rv) return std::unexpected<int>(rv.error());
    std::uint32_t x = *rv;
    return std::expected<std::int32_t, int>(static_cast<std::int32_t>(x));
}

std::expected<std::uint64_t, int> BinaryStreamReader::ReadULong()
{
    std::expected<std::uint8_t, int> rv = ReadByte();
    if (!rv) return std::unexpected<int>(rv.error());
    std::uint8_t b0 = *rv;
    rv = ReadByte();
    if (!rv) return std::unexpected<int>(rv.error());
    std::uint8_t b1 = *rv;
    rv = ReadByte();
    if (!rv) return std::unexpected<int>(rv.error());
    std::uint8_t b2 = *rv;
    rv = ReadByte();
    if (!rv) return std::unexpected<int>(rv.error());
    std::uint8_t b3 = *rv;
    rv = ReadByte();
    if (!rv) return std::unexpected<int>(rv.error());
    std::uint8_t b4 = *rv;
    rv = ReadByte();
    if (!rv) return std::unexpected<int>(rv.error());
    std::uint8_t b5 = *rv;
    rv = ReadByte();
    if (!rv) return std::unexpected<int>(rv.error());
    std::uint8_t b6 = *rv;
    rv = ReadByte();
    if (!rv) return std::unexpected<int>(rv.error());
    std::uint8_t b7 = *rv;
    return std::expected<std::uint64_t, int>((static_cast<std::uint64_t>(b0) << 56) | (static_cast<std::uint64_t>(b1) << 48) | (static_cast<std::uint64_t>(b2) << 40) |
        (static_cast<std::uint64_t>(b3) << 32) | (static_cast<std::uint64_t>(b4) << 24) | (static_cast<std::uint64_t>(b5) << 16) | (static_cast<std::uint64_t>(b6) << 8) |
        static_cast<std::uint64_t>(b7));
}

std::expected<std::int64_t, int> BinaryStreamReader::ReadLong()
{
    std::expected<std::uint64_t, int> rv = ReadULong();
    if (!rv) return std::unexpected<int>(rv.error());
    std::uint64_t x = *rv;
    return std::expected<std::int64_t, int>(static_cast<std::int64_t>(x));
}

std::expected<float, int> BinaryStreamReader::ReadFloat()
{
    std::expected<std::uint32_t, int> rv = ReadUInt();
    if (!rv) return std::unexpected<int>(rv.error());
    std::uint32_t x = *rv;
    return std::expected<float, int>(*reinterpret_cast<float*>(&x));
}

std::expected<double, int> BinaryStreamReader::ReadDouble()
{
    std::expected<std::uint64_t, int> rv = ReadULong();
    if (!rv) return std::unexpected<int>(rv.error());
    std::uint64_t x = *rv;
    return std::expected<double, int>(*reinterpret_cast<double*>(&x));
}

std::expected<char, int> BinaryStreamReader::ReadChar()
{
    std::expected<std::uint8_t, int> rv = ReadByte();
    if (!rv) return std::unexpected<int>(rv.error());
    std::uint8_t x = *rv;
    return std::expected<char, int>(static_cast<char>(x));
}

std::expected<char8_t, int> BinaryStreamReader::ReadChar8()
{
    std::expected<std::uint8_t, int> rv = ReadByte();
    if (!rv) return std::unexpected<int>(rv.error());
    std::uint8_t x = *rv;
    return std::expected<char8_t, int>(static_cast<char8_t>(x));
}

std::expected<char16_t, int> BinaryStreamReader::ReadWChar()
{
    std::expected<std::uint16_t, int> rv = ReadUShort();
    if (!rv) return std::unexpected<int>(rv.error());
    std::uint16_t x = *rv;
    return std::expected<char16_t, int>(static_cast<char16_t>(x));
}

std::expected<char32_t, int> BinaryStreamReader::ReadUChar()
{
    std::expected<std::uint32_t, int> rv = ReadUInt();
    if (!rv) return std::unexpected<int>(rv.error());
    std::uint32_t x = *rv;
    return std::expected<char32_t, int>(static_cast<char32_t>(x));
}

std::expected<std::string, int> BinaryStreamReader::ReadUtf8String()
{
    std::string s;
    std::expected<std::uint8_t, int> rv = ReadByte();
    if (!rv) return std::unexpected<int>(rv.error());
    std::uint8_t x = *rv;
    while (x != 0)
    {
        s.append(1, static_cast<char>(x));
        rv = ReadByte();
        if (!rv) return std::unexpected<int>(rv.error());
        x = *rv;
    }
    return std::expected<std::string, int>(s);
}

std::expected<std::u16string, int> BinaryStreamReader::ReadUtf16String()
{
    std::expected<std::string, int> rv = ReadUtf8String();
    if (!rv) return std::unexpected<int>(rv.error());
    std::string s = *rv;
    return ToUtf16(s);
}

std::expected<std::u32string, int> BinaryStreamReader::ReadUtf32String()
{
    std::expected<std::string, int> rv = ReadUtf8String();
    if (!rv) return std::unexpected<int>(rv.error());
    std::string s = *rv;
    return ToUtf32(s);
}

std::expected<std::uint32_t, int> BinaryStreamReader::ReadULEB128UInt()
{
    std::uint32_t result = 0;
    std::uint32_t shift = 0;
    while (true)
    {
        std::expected<std::uint8_t, int> rv = ReadByte();
        if (!rv) return std::unexpected<int>(rv.error());
        std::uint8_t b = *rv;
        result |= static_cast<std::uint32_t>(((b & 0x7FU) << shift));
        if ((b & 0x80) == 0) break;
        shift += static_cast<std::uint32_t>(7);
    }
    return std::expected<std::uint32_t, int>(result);
}

std::expected<std::uint64_t, int> BinaryStreamReader::ReadULEB128ULong()
{
    std::uint64_t result = 0;
    std::uint64_t shift = 0;
    while (true)
    {
        std::expected<std::uint8_t, int> rv = ReadByte();
        if (!rv) return std::unexpected<int>(rv.error());
        std::uint8_t b = *rv;
        result |= ((b & 0x7F) << shift);
        if ((b & 0x80) == 0) break;
        shift += 7;
    }
    return std::expected<std::uint64_t, int>(result);
}

std::expected<std::int32_t, int> BinaryStreamReader::ReadSLEB128Int()
{
    std::int32_t result = 0;
    std::int32_t shift = 0;
    std::uint8_t b = 0;
    do
    {
        std::expected<std::uint8_t, int> rv = ReadByte();
        if (!rv) return std::unexpected<int>(rv.error());
        std::uint8_t b = *rv;
        result |= (b & 0x7F) << shift;
        shift += 7;
    } while ((b & 0x80) != 0);
    if ((shift < 32) && (b & 0x40) != 0)
    {
        result |= ~std::int32_t(0) << shift;
    }
    return std::expected<std::int32_t, int>(result);
}

std::expected<std::int64_t, int> BinaryStreamReader::ReadSLEB128Long()
{
    std::int64_t result = 0;
    std::int64_t shift = 0;
    std::uint8_t b = 0;
    do
    {
        std::expected<std::uint8_t, int> rv = ReadByte();
        if (!rv) return std::unexpected<int>(rv.error());
        std::uint8_t b = *rv;
        result |= (b & 0x7F) << shift;
        shift += 7;
    } while ((b & 0x80) != 0);
    if ((shift < 64) && (b & 0x40) != 0)
    {
        result |= ~std::int64_t(0) << shift;
    }
    return std::expected<std::int64_t, int>(result);
}

std::expected<bool, int> BinaryStreamReader::ReadUuid(uuid& id)
{
    for (uuid::value_type& x : id)
    {
        std::expected<std::uint8_t, int> rv = ReadByte();
        if (!rv) return std::unexpected<int>(rv.error());
        x = *rv;
    }
    return std::expected<bool, int>(true);
}

std::expected<std::time_t, int> BinaryStreamReader::ReadTime()
{
    std::expected<std::int64_t, int> rv = ReadLong();
    if (!rv) return std::unexpected<int>(rv.error());
    return std::expected<std::time_t, int>(static_cast<time_t>(*rv));
}

} // namespace util
