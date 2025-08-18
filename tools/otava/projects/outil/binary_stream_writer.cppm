// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module util.binary.stream.writer;

import std;
import util.stream;
import util.uuid;

export namespace util {

class BinaryStreamWriter
{
public:
    BinaryStreamWriter(Stream& stream_);
    inline Stream& GetStream() { return stream; }
    std::expected<bool, int> Write(bool x);
    std::expected<bool, int> Write(std::uint8_t x);
    std::expected<bool, int> Write(std::int8_t x);
    std::expected<bool, int> Write(std::uint16_t x);
    std::expected<bool, int> Write(std::int16_t x);
    std::expected<bool, int> Write(std::uint32_t x);
    std::expected<bool, int> Write(std::int32_t x);
    std::expected<bool, int> Write(std::uint64_t x);
    std::expected<bool, int> Write(std::int64_t x);
    std::expected<bool, int> Write(float x);
    std::expected<bool, int> Write(double x);
    std::expected<bool, int> Write(char x);
    std::expected<bool, int> Write(char8_t x);
    std::expected<bool, int> Write(char16_t x);
    std::expected<bool, int> Write(char32_t x);
    std::expected<bool, int> Write(const std::string& s);
    std::expected<bool, int> Write(const std::string& s, bool writeNull);
    std::expected<bool, int> Write(const std::u16string& s);
    std::expected<bool, int> Write(const std::u32string& s);
    std::expected<bool, int> WriteULEB128UInt(std::uint32_t x);
    std::expected<bool, int> WriteULEB128ULong(std::uint64_t x);
    std::expected<bool, int> WriteSLEB128Int(std::int32_t x);
    std::expected<bool, int> WriteSLEB128Long(std::int64_t x);
    std::expected<bool, int> Write(const uuid& uuid);
    std::expected<bool, int> WriteTime(std::time_t time);
    inline std::int64_t Position() const { return stream.Position(); }
private:
    Stream& stream;
};

} // util
