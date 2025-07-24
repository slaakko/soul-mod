// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module util_expected.socket_stream;

namespace util {

SocketStream::SocketStream(TcpSocket&& socket_) : Stream(), socket(std::move(socket_))
{
}

std::expected<int, int> SocketStream::ReadByte()
{
    std::uint8_t x;
    std::expected<std::int64_t, int> rv = Read(&x, 1);
    if (!rv) return std::unexpected<int>(rv.error());
    std::int64_t bytesRead = *rv;
    if (bytesRead > 0)
    {
        return std::expected<int, int>(x);
    }
    else
    {
        return std::expected<int, int>(-1);
    }
}

std::expected<std::int64_t, int> SocketStream::Read(std::uint8_t* buf, std::int64_t count)
{
    return socket.Receive(buf, static_cast<int>(count));
}

std::expected<bool, int> SocketStream::Write(std::uint8_t x)
{
    return Write(&x, 1);
}

std::expected<bool, int> SocketStream::Write(std::uint8_t* buf, std::int64_t count)
{
    return socket.Send(buf, static_cast<int>(count));
}

} // util
