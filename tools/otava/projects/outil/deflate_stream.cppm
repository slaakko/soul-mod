// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module util.deflate.stream;

import std;
import util.compression;
import util.stream;

export namespace util {

const int defaultDeflateCompressionLevel = -1;
const int noDeflateCompression = 0;
const int fastestDeflateCompression = 1;
const int optimalDeflateCompression = 9;
const int Z_FINISH = 4;
const int Z_STREAM_END = 1;
const int Z_NO_FLUSH = 0;

class DeflateStream : public Stream
{
public:
    DeflateStream(CompressionMode mode_, Stream& underlyingStream_);
    DeflateStream(CompressionMode mode_, Stream& underlyingStream_, std::int64_t bufferSize_);
    DeflateStream(CompressionMode mode_, Stream& underlyingStream_, std::int64_t bufferSize_, int compressionLevel_);
    ~DeflateStream() override;
    std::expected<int, int> ReadByte() override;
    std::expected<std::int64_t, int> Read(std::uint8_t* buf, std::int64_t count) override;
    std::expected<bool, int> Write(std::uint8_t x) override;
    std::expected<bool, int> Write(std::uint8_t* buf, std::int64_t count) override;
    inline bool Valid() const { return error == 0; }
    inline explicit operator bool() const { return Valid(); }
    inline int Error() const { return error; }
private:
    std::expected<bool, int> Finish();
    CompressionMode mode;
    Stream& underlyingStream;
    std::int64_t bufferSize;
    int compressionLevel;
    std::int64_t inAvail;
    std::unique_ptr<std::uint8_t> in;
    std::uint32_t outAvail;
    std::int64_t outPos;
    std::int64_t outHave;
    bool endOfInput;
    bool endOfStream;
    std::unique_ptr<std::uint8_t> out;
    void* handle;
    int error;
};

} // namespace util
