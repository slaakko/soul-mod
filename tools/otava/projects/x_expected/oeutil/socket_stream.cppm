// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module util.socket_stream;

import util.stream;
import util.socket;
import std;

export namespace util {

class SocketStream : public Stream
{
public:
    SocketStream(TcpSocket&& socket_);
    inline const TcpSocket& Socket() const { return socket; }
    inline TcpSocket& Socket() { return socket; }
    std::expected<int, int> ReadByte() override;
    std::expected<std::int64_t, int> Read(std::uint8_t* buf, std::int64_t count) override;
    std::expected<bool, int> Write(std::uint8_t x) override;
    std::expected<bool, int> Write(std::uint8_t* buf, std::int64_t count) override;
private:
    TcpSocket socket;
};

} // util
