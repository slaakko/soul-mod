// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module util.memory.reader;

import std;
import util.time;

export namespace util {

class MemoryReader
{
public:
    MemoryReader(const std::uint8_t* ptr_, std::int64_t count_);
    std::expected<std::uint8_t, int> ReadByte();
    std::expected<std::int8_t, int> ReadSByte();
    std::expected<std::uint16_t, int> ReadUShort();
    std::expected<std::int16_t, int> ReadShort();
    std::expected<std::uint32_t, int> ReadUInt();
    std::expected<std::int32_t, int> ReadInt();
    std::expected<std::uint64_t, int> ReadULong();
    std::expected<std::int64_t, int> ReadLong();
    std::expected<DateTime, int> ReadDateTime();
    std::expected<std::string, int> ReadString();
private:
    const std::uint8_t* ptr;
    const std::uint8_t* pos;
    std::int64_t count;
};

} // namespace util
