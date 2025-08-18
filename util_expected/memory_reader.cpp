// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module util_expected.memory.reader;

import util_expected.error;

namespace util {

MemoryReader::MemoryReader(const std::uint8_t* ptr_, std::int64_t count_) : ptr(ptr_), pos(ptr), count(count_)
{
}

std::expected<std::uint8_t, int> MemoryReader::ReadByte()
{
    if (pos - ptr >= count)
    {
        return std::unexpected<int>(AllocateError("memory reader: unexpected end of data"));
    }
    return std::expected<std::uint8_t, int>(*pos++);
}

std::expected<std::int8_t, int> MemoryReader::ReadSByte()
{
    std::expected<std::uint8_t, int> rv = ReadByte();
    if (!rv) return std::unexpected<int>(rv.error());
    std::uint8_t u = *rv;
    return std::expected<std::int8_t, int>(static_cast<std::int8_t>(u));
}

std::expected<std::uint16_t, int> MemoryReader::ReadUShort()
{
    std::expected<std::uint8_t, int> rv = ReadByte();
    if (!rv) return std::unexpected<int>(rv.error());
    std::uint8_t b0 = *rv;
    rv = ReadByte();
    if (!rv) return std::unexpected<int>(rv.error());
    std::uint8_t b1 = *rv;
    return std::expected<std::uint16_t, int>((static_cast<std::uint16_t>(b0) << 8u) | static_cast<std::uint16_t>(b1));
}

std::expected<std::int16_t, int> MemoryReader::ReadShort()
{
    std::expected<std::uint16_t, int> rv = ReadUShort();
    if (!rv) return std::unexpected<int>(rv.error());
    return std::expected<std::int16_t, int>(static_cast<std::int16_t>(*rv));
}

std::expected<std::uint32_t, int> MemoryReader::ReadUInt()
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
    return std::expected<std::uint32_t, int>(
        (static_cast<std::uint32_t>(b0) << 24u) | (static_cast<std::uint32_t>(b1) << 16u) | (static_cast<std::uint32_t>(b2) << 8u) | static_cast<std::uint32_t>(b3));
}

std::expected<std::int32_t, int> MemoryReader::ReadInt()
{
    std::expected<std::uint32_t, int> rv = ReadUInt();
    if (!rv) return std::unexpected<int>(rv.error());
    return std::expected<std::int32_t, int>(static_cast<std::int32_t>(*rv));
}

std::expected<std::uint64_t, int> MemoryReader::ReadULong()
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
    return std::expected<std::uint64_t, int>((static_cast<std::uint64_t>(b0) << 56u) | (static_cast<std::uint64_t>(b1) << 48u) | (static_cast<std::uint64_t>(b2) << 40u) | 
        (static_cast<std::uint64_t>(b3) << 32u) | (static_cast<std::uint64_t>(b4) << 24u) | (static_cast<std::uint64_t>(b5) << 16u) | 
        (static_cast<std::uint64_t>(b6) << 8u) | static_cast<std::uint64_t>(b7));
}

std::expected<std::int64_t, int> MemoryReader::ReadLong()
{
    std::expected<std::uint64_t, int> rv = ReadULong();
    if (!rv) return std::unexpected<int>(rv.error());
    return std::expected<std::int64_t, int>(static_cast<std::int64_t>(*rv));
}

std::expected<DateTime, int> MemoryReader::ReadDateTime()
{
    std::expected<std::int16_t, int> rv = ReadShort();
    if (!rv) return std::unexpected<int>(rv.error());
    std::int16_t year = *rv;
    std::expected<std::int8_t, int> mrv = ReadSByte();
    if (!mrv) return std::unexpected<int>(mrv.error());
    Month month = static_cast<Month>(*mrv);
    std::expected<std::int8_t, int> drv = ReadSByte();
    if (!drv) return std::unexpected<int>(drv.error());
    std::int8_t day = *drv;
    Date date(year, month, day);
    std::expected<std::int32_t, int> srv = ReadInt();
    if (!srv) return std::unexpected<int>(srv.error());
    std::int32_t secs = *srv;
    DateTime dt(date, secs);
    return std::expected<DateTime, int>(dt);
}

std::expected<std::string, int> MemoryReader::ReadString()
{
    std::string result;
    std::expected<std::uint8_t, int> rv = ReadByte();
    if (!rv) return std::unexpected<int>(rv.error());
    std::uint8_t b = *rv;
    while (b != 0u)
    {
        result.append(1, static_cast<char>(b));
        rv = ReadByte();
        if (!rv) return std::unexpected<int>(rv.error());
        b = *rv;
    }
    return std::expected<std::string, int>(result);
}

} // namespace util
