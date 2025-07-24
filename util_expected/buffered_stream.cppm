// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module util_expected.buffered.stream;

import std;
import util_expected.stream;

export namespace util {

class BufferedStream : public Stream
{
public:
    BufferedStream(Stream& baseStream_);
    BufferedStream(Stream& baseStream_, std::int64_t bufferSize_);
    ~BufferedStream() override;
    std::expected<int, int> ReadByte() override;
    std::expected<std::int64_t, int> Read(std::uint8_t* buf, std::int64_t count) override;
    std::expected<bool, int> Write(std::uint8_t x) override;
    std::expected<bool, int> Write(std::uint8_t* buf, std::int64_t count) override;
    std::expected<bool, int> Flush() override;
    std::expected<bool, int> Seek(std::int64_t pos, Origin origin) override;
    std::expected<std::int64_t, int> Tell() override;
    Stream& BaseStream() { return baseStream; }
private:
    std::expected<bool, int> FillBuf();
    Stream& baseStream;
    std::int64_t bufferSize;
    std::unique_ptr<std::uint8_t> buffer;
    std::int64_t pos;
    std::int64_t bytesAvailable;
    std::int64_t end;
};

} // namespace util

