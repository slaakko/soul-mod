// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module util.memory.stream;

import std.core;
import util.stream;

export namespace util {

class MemoryStream : public Stream
{
public:
    MemoryStream();
    MemoryStream(std::uint8_t* data_, std::int64_t size_);
    int ReadByte() override;
    std::int64_t Read(std::uint8_t* buf, std::int64_t count) override;
    void Write(std::uint8_t x) override;
    void Write(std::uint8_t* buf, std::int64_t count) override;
    void Seek(std::int64_t pos, Origin origin) override;
    std::int64_t Tell() override;
    std::uint8_t* Data() { return data; }
    std::int64_t Size() const { return size; }
    std::int64_t ReadPos() const { return readPos; }
    const std::vector<std::uint8_t>& Content() const { return content; }
    void SetFromContent();
private:
    std::uint8_t* data;
    std::int64_t size;
    std::int64_t readPos;
    std::vector<std::uint8_t> content;
};

} // namespace util

