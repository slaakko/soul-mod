// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module util_expected.memory.stream;

import std;
import util_expected.stream;

export namespace util {

class MemoryStream : public Stream
{
public:
    MemoryStream();
    MemoryStream(std::uint8_t* data_, std::int64_t size_);
    std::expected<int, int> ReadByte() override;
    std::expected<std::int64_t, int> Read(std::uint8_t* buf, std::int64_t count) override;
    std::expected<bool, int> Write(std::uint8_t x) override;
    std::expected<bool, int> Write(std::uint8_t* buf, std::int64_t count) override;
    std::expected<bool, int> Seek(std::int64_t pos, Origin origin) override;
    std::expected<std::int64_t, int> Tell() override;
    inline std::uint8_t* Data() { return data; }
    inline std::int64_t Size() const { return size; }
    inline std::int64_t ReadPos() const { return readPos; }
    inline const std::vector<std::uint8_t>& Content() const { return content; }
    void SetFromContent();
private:
    std::uint8_t* data;
    std::int64_t size;
    std::int64_t readPos;
    std::vector<std::uint8_t> content;
};

} // namespace util

