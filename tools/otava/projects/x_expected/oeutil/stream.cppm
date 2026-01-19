// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module util.stream;

import std;

export namespace util {

enum class Origin
{
    seekSet, seekCur, seekEnd
};

class StreamObserver;

class Stream
{
public:
    Stream();
    virtual ~Stream();
    virtual std::expected<int, int> ReadByte() = 0;
    virtual std::expected<std::int64_t, int> Read(std::uint8_t* buf, std::int64_t count) = 0;
    virtual std::expected<bool, int> Write(std::uint8_t x) = 0;
    virtual std::expected<bool, int> Write(std::uint8_t* buf, std::int64_t count) = 0;
    virtual std::expected<bool, int> Flush();
    virtual std::expected<bool, int> Seek(std::int64_t pos, Origin origin);
    virtual std::expected<std::int64_t, int> Tell();
    std::expected<bool, int> CopyTo(Stream& destination);
    std::expected<bool, int> CopyTo(Stream& destination, std::int64_t bufferSize);
    std::int64_t Position() const { return position; }
    void SetPosition(std::int64_t position_);
    void AddObserver(StreamObserver* observer);
    void RemoveObserver(StreamObserver* observer);
private:
    std::int64_t position;
    std::vector<StreamObserver*> observers;
};

class StreamObserver
{
public:
    StreamObserver();
    virtual ~StreamObserver();
    virtual void PositionChanged(Stream* stream) {}
};

class Streams
{
public:
    Streams();
    Streams(Streams&& that) noexcept;
    Streams(const Streams&) = delete;
    Streams& operator=(Streams&& that) noexcept;
    Streams& operator=(const Streams&) = delete;
    ~Streams();
    void Add(Stream* stream);
    Stream* Get(int index) const;
    std::expected<Stream*, int> Back() const;
    inline int Count() const { return static_cast<int>(streams.size()); }
private:
    std::vector<std::unique_ptr<Stream>> streams;
};

} // util
