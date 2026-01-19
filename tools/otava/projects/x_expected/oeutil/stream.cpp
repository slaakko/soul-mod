// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module util.stream;

import std;
import util.error;

namespace util {

StreamObserver::StreamObserver()
{
}

StreamObserver::~StreamObserver()
{
}

Stream::Stream()
{
}

Stream::~Stream()
{
}

std::expected<bool, int> Stream::Flush()
{
    return std::expected<bool, int>(true);
}

std::expected<bool, int> Stream::Seek(std::int64_t pos, Origin origin)
{
    return std::unexpected<int>(AllocateError("seek not supported"));
}

std::expected<std::int64_t, int> Stream::Tell()
{
    return std::unexpected<int>(AllocateError("tell not supported"));
}

void Stream::AddObserver(StreamObserver* observer)
{
    if (std::find(observers.begin(), observers.end(), observer) == observers.end())
    {
        observers.push_back(observer);
    }
}

void Stream::RemoveObserver(StreamObserver* observer)
{
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

std::expected<bool, int> Stream::CopyTo(Stream& destination)
{
    return CopyTo(destination, 16384);
}

std::expected<bool, int> Stream::CopyTo(Stream& destination, std::int64_t bufferSize)
{
    std::unique_ptr<std::uint8_t> buf(static_cast<std::uint8_t*>(std::malloc(bufferSize)));
    std::expected<std::int64_t, int> bytesReadResult = Read(buf.get(), bufferSize);
    if (!bytesReadResult) return std::unexpected<int>(bytesReadResult.error());
    std::int64_t bytesRead = *bytesReadResult;
    while (bytesRead > 0)
    {
        std::expected<bool, int> writeResult = destination.Write(buf.get(), bytesRead);
        if (!writeResult) return writeResult;
        bytesReadResult = Read(buf.get(), bufferSize);
        if (!bytesReadResult) return std::unexpected<int>(bytesReadResult.error());
        bytesRead = *bytesReadResult;
    }
    return std::expected<bool, int>(true);
}

void Stream::SetPosition(std::int64_t position_)
{
    if (position != position_)
    {
        position = position_;
        for (StreamObserver* observer : observers)
        {
            observer->PositionChanged(this);
        }
    }
}

Streams::Streams() : streams()
{
}

Streams::Streams(Streams&& that) noexcept : streams(std::move(that.streams))
{
}

Streams& Streams::operator=(Streams&& that) noexcept
{
    std::swap(streams, that.streams);
    return *this;
}

Streams::~Streams()
{
    int n = Count();
    for (int i = n - 1; i >= 0; --i)
    {
        streams[i].reset();
    }
    streams.clear();
}

void Streams::Add(Stream* stream)
{
    streams.push_back(std::unique_ptr<Stream>(stream));
}

Stream* Streams::Get(int index) const
{
    return streams[index].get();
}

std::expected<Stream*, int> Streams::Back() const
{
    if (streams.empty())
    {
        return std::unexpected<int>(AllocateError("streams empty"));
    }
    return std::expected<Stream*, int>(streams.back().get());
}

} // util
