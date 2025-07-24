// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module util_expected.binary.stream.reader;

import std;
import util_expected.stream;
import util_expected.uuid;

export namespace util {

class BinaryStreamReader
{
public:
    BinaryStreamReader(Stream& stream_);
    Stream& GetStream() { return stream; }
    std::expected<bool, int> ReadBool();
    std::expected<std::uint8_t, int> ReadByte();
    std::expected<std::int8_t, int> ReadSByte();
    std::expected<std::uint16_t, int> ReadUShort();
    std::expected<std::int16_t, int> ReadShort();
    std::expected<std::uint32_t, int> ReadUInt();
    std::expected<std::int32_t, int> ReadInt();
    std::expected<std::uint64_t, int> ReadULong();
    std::expected<std::int64_t, int> ReadLong();
    std::expected<float, int> ReadFloat();
    std::expected<double, int> ReadDouble();
    std::expected<char, int> ReadChar();
    std::expected<char8_t, int> ReadChar8();
    std::expected<char16_t, int> ReadWChar();
    std::expected<char32_t, int> ReadUChar();
    std::expected<std::string, int> ReadUtf8String();
    std::expected<std::u16string, int> ReadUtf16String();
    std::expected<std::u32string, int> ReadUtf32String();
    std::expected<std::uint32_t, int> ReadULEB128UInt();
    std::expected<std::uint64_t, int> ReadULEB128ULong();
    std::expected<std::int32_t, int> ReadSLEB128Int();
    std::expected<std::int64_t, int> ReadSLEB128Long();
    std::expected<bool, int> ReadUuid(uuid& uuid);
    std::expected<std::time_t, int> ReadTime();
    std::int64_t Position() const { return stream.Position(); }
private:
    Stream& stream;
};

} // util
