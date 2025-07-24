// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module;
#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>    
#include <Windows.h>
#pragma comment(lib, "ws2_32.lib")
#endif

module util_expected.socket;

import util_expected.error;
import util_expected.unicode;
import util_expected.memory.writer;
import util_expected.memory.reader;

namespace util {

std::expected<std::string, int> GetSocketErrorMessage(int errorCode)
{
    char16_t buf[2048];
    FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM, NULL, errorCode, 0, (LPWSTR)(&buf[0]), sizeof(buf) / 2, NULL);
    return ToUtf8(std::u16string(buf));
}

int GetLastSocketError()
{
    return WSAGetLastError();
}

class Sockets
{
public:
    static std::expected<bool, int> Init();
    static void Done();
};

std::expected<bool, int> Sockets::Init()
{
    WORD ver = MAKEWORD(2, 2);
    WSADATA wsaData;
    if (WSAStartup(ver, &wsaData) != 0)
    {
        int errorCode = GetLastSocketError();
        std::expected<std::string, int> rv = GetSocketErrorMessage(errorCode);
        if (!rv) return std::unexpected<int>(rv.error());
        std::string errorMessage = *rv;
        errorMessage = "socket initialization failed with error code " + std::to_string(errorCode) + ": " + errorMessage;
        return std::unexpected<int>(AllocateError(errorMessage));
    }
    return std::expected<bool, int>(true);
}

void Sockets::Done()
{
    WSACleanup();
}

std::expected<std::int64_t, int> CreateSocket()
{
    SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (s == INVALID_SOCKET)
    {
        int errorCode = GetLastSocketError();
        std::expected<std::string, int> rv = GetSocketErrorMessage(errorCode);
        if (!rv) return std::unexpected<int>(rv.error());
        std::string errorMessage = *rv;
        return std::unexpected<int>(AllocateError(errorMessage));
    }
    return std::expected<std::int64_t, int>(static_cast<std::int64_t>(s));
}

std::expected<bool, int> BindSocket(std::int64_t socketHandle, int port)
{
    int result = 0;
    SOCKET s = static_cast<SOCKET>(socketHandle);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
#pragma warning(suppress : 4996)
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(port);
    result = bind(s, (struct sockaddr*)&addr, sizeof(addr));
    if (result != 0)
    {
        int errorCode = GetLastSocketError();
        std::expected<std::string, int> rv = GetSocketErrorMessage(errorCode);
        if (!rv) return std::unexpected<int>(rv.error());
        std::string errorMessage = *rv;
        return std::unexpected<int>(AllocateError(errorMessage));
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ListenSocket(std::int64_t socketHandle, int backlog)
{
    int result = 0;
    SOCKET s = static_cast<SOCKET>(socketHandle);
    result = listen(s, backlog);
    if (result != 0)
    {
        int errorCode = GetLastSocketError();
        std::expected<std::string, int> rv = GetSocketErrorMessage(errorCode);
        if (!rv) return std::unexpected<int>(rv.error());
        std::string errorMessage = *rv;
        return std::unexpected<int>(AllocateError(errorMessage));
    }
    return std::expected<bool, int>(true);
}

std::expected<std::int64_t, int> AcceptSocket(std::int64_t socketHandle)
{
    SOCKET s = static_cast<SOCKET>(socketHandle);
    SOCKET a = accept(s, NULL, NULL);
    if (a == INVALID_SOCKET)
    {
        int errorCode = GetLastSocketError();
        std::expected<std::string, int> rv = GetSocketErrorMessage(errorCode);
        if (!rv) return std::unexpected<int>(rv.error());
        std::string errorMessage = *rv;
        return std::unexpected<int>(AllocateError(errorMessage));
    }
    return std::expected<std::int64_t, int>(static_cast<std::int64_t>(a));
}

std::expected<bool, int> CloseSocket(std::int64_t socketHandle)
{
    int result = 0;
    SOCKET s = static_cast<SOCKET>(socketHandle);
    result = closesocket(s);
    if (result != 0)
    {
        int errorCode = GetLastSocketError();
        std::expected<std::string, int> rv = GetSocketErrorMessage(errorCode);
        if (!rv) return std::unexpected<int>(rv.error());
        std::string errorMessage = *rv;
        return std::unexpected<int>(AllocateError(errorMessage));
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ShutdownSocket(std::int64_t socketHandle, ShutdownMode mode)
{
    int result = 0;
    int how = SD_RECEIVE;
    switch (mode)
    {
    case ShutdownMode::receive: how = SD_RECEIVE; break;
    case ShutdownMode::send: how = SD_SEND; break;
    case ShutdownMode::both: how = SD_BOTH; break;
    }
    SOCKET s = static_cast<SOCKET>(socketHandle);
    result = shutdown(s, how);
    if (result != 0)
    {
        int errorCode = GetLastSocketError();
        std::expected<std::string, int> rv = GetSocketErrorMessage(errorCode);
        if (!rv) return std::unexpected<int>(rv.error());
        std::string errorMessage = *rv;
        return std::unexpected<int>(AllocateError(errorMessage));
    }
    return std::expected<bool, int>(true);
}

std::expected<std::int64_t, int>  ConnectSocket(const std::string& node, const std::string& service)
{
    struct addrinfo hint;
    struct addrinfo* rp;
    struct addrinfo* res;
    memset(&hint, 0, sizeof(struct addrinfo));
    hint.ai_flags = 0;
    hint.ai_family = AF_INET;
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_protocol = IPPROTO_TCP;
    hint.ai_addrlen = 0;
    hint.ai_addr = 0;
    hint.ai_canonname = 0;
    hint.ai_next = 0;
    int result = getaddrinfo(node.c_str(), service.c_str(), &hint, &res);
    if (result != 0)
    {
        int errorCode = GetLastSocketError();
        std::expected<std::string, int> rv = GetSocketErrorMessage(errorCode);
        if (!rv) return std::unexpected<int>(rv.error());
        std::string errorMessage = *rv;
        return std::unexpected<int>(AllocateError(errorMessage));
    }
    else
    {
        for (rp = res; rp != 0; rp = rp->ai_next)
        {
            SOCKET s = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
            if (s == -1)
            {
                continue;
            }
            int result = connect(s, rp->ai_addr, (int)rp->ai_addrlen);
            if (result == 0)
            {
                freeaddrinfo(res);
                return std::expected<std::int64_t, int>(static_cast<std::int64_t>(s));
            }
            else
            {
                freeaddrinfo(res);
                int errorCode = GetLastSocketError();
                std::expected<std::string, int> rv = GetSocketErrorMessage(errorCode);
                if (!rv) return std::unexpected<int>(rv.error());
                std::string errorMessage = *rv;
                return std::unexpected<int>(AllocateError(errorMessage));
            }
        }
    }
    std::string errorMessage = "could not connect to " + node + ":" + service;
    return std::unexpected<int>(AllocateError(errorMessage));
}

std::expected<int, int> SendSocket(std::int64_t socketHandle, const std::uint8_t* buf, int len, int flags)
{
    int result = 0;
    SOCKET s = static_cast<SOCKET>(socketHandle);
    result = send(s, (const char*)buf, len, flags);
    if (result < 0)
    {
        int errorCode = GetLastSocketError();
        std::expected<std::string, int> rv = GetSocketErrorMessage(errorCode);
        if (!rv) return std::unexpected<int>(rv.error());
        std::string errorMessage = *rv;
        return std::unexpected<int>(AllocateError(errorMessage));
    }
    return std::expected<int, int> (result);
}

std::expected<int, int> ReceiveSocket(std::int64_t socketHandle, std::uint8_t* buf, int len, int flags)
{
    int result = 0;
    SOCKET s = static_cast<SOCKET>(socketHandle);
    result = recv(s, (char*)buf, len, flags);
    if (result < 0)
    {
        int errorCode = GetLastSocketError();
        std::expected<std::string, int> rv = GetSocketErrorMessage(errorCode);
        if (!rv) return std::unexpected<int>(rv.error());
        std::string errorMessage = *rv;
        return std::unexpected<int>(AllocateError(errorMessage));
    }
    return std::expected<int, int> (result);
}

std::expected<bool, int> InitSocket()
{
    return Sockets::Init();
}

void DoneSocket()
{
    Sockets::Done();
}

TcpSocket::TcpSocket() : handle(-1), connected(false), shutdown(false), error(0)
{
    std::expected<int64_t, int> rv = CreateSocket();
    if (!rv)
    {
        error = rv.error();
        return;
    }
    handle = *rv;
}

TcpSocket::TcpSocket(const std::string& node, const std::string& service) : handle(-1), connected(false), shutdown(false), error(0)
{
    std::expected<int64_t, int> rv = ConnectSocket(node.c_str(), service.c_str());
    if (!rv)
    {
        error = rv.error();
        return;
    }
    handle = *rv;
    connected = true;
}

TcpSocket::TcpSocket(std::int64_t handle_) noexcept : handle(handle_), connected(true), shutdown(false), error(0)
{
}

TcpSocket::TcpSocket(TcpSocket&& that) noexcept : handle(that.handle), connected(that.connected), shutdown(that.shutdown), error(that.error)
{
    that.handle = -1;
    that.connected = false;
    that.shutdown = false;
}

TcpSocket& TcpSocket::operator=(TcpSocket&& that) noexcept
{
    std::swap(handle, that.handle);
    std::swap(connected, that.connected);
    std::swap(shutdown, that.shutdown);
    std::swap(error, that.error);
    return *this;
}

TcpSocket::~TcpSocket()
{
    if (handle != -1)
    {
        if (connected && !shutdown)
        {
            std::expected<bool, int> rv = Shutdown(ShutdownMode::both);
        }
        std::expected<bool, int> rv = CloseSocket(handle);
    }
}

std::expected<bool, int> TcpSocket::Close()
{
    if (handle != -1)
    {
        if (connected && !shutdown)
        {
            std::expected<bool, int> rv = Shutdown(ShutdownMode::both);
            if (!rv) return rv;
        }
        std::int64_t s = handle;
        handle = -1;
        connected = false;
        std::expected<bool, int> rv = CloseSocket(s);
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> TcpSocket::Connect(const std::string& node, const std::string& service)
{
    std::expected<bool, int> rv = Close();
    if (!rv) return rv;
    std::expected<int64_t, int> rvc = ConnectSocket(node.c_str(), service.c_str());
    if (!rvc) return std::unexpected<int>(rvc.error());
    handle = *rvc;
    connected = true;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> TcpSocket::Bind(int port)
{
    return BindSocket(handle, port);
}

std::expected<bool, int> TcpSocket::Listen(int backlog)
{
    return ListenSocket(handle, backlog);
}

std::expected<TcpSocket, int> TcpSocket::Accept()
{
    std::expected<std::int64_t, int> rv = AcceptSocket(handle);
    if (!rv) return std::unexpected<int>(rv.error());
    std::int64_t acceptedHandle = *rv;
    return std::expected<TcpSocket, int>(TcpSocket(acceptedHandle));
}

std::expected<bool, int> TcpSocket::Shutdown(ShutdownMode mode)
{
    shutdown = true;
    return ShutdownSocket(handle, mode);
}

std::expected<bool, int> TcpSocket::Send(const std::uint8_t* buffer, int count)
{
    int offset = 0;
    int bytesToSend = count;
    while (bytesToSend > 0)
    {
        std::expected<int, int> rv = SendSocket(handle, buffer + offset, count, 0);
        if (!rv) return std::unexpected<int>(rv.error());
        int result = *rv;
        if (result >= 0)
        {
            bytesToSend = bytesToSend - result;
            offset = offset + result;
        }
    }
    return std::expected<bool, int>(true);
}

std::expected<int, int> TcpSocket::Receive(std::uint8_t* buffer, int count)
{
    return ReceiveSocket(handle, buffer, count, 0);
}

std::expected<bool, int> Write(TcpSocket& socket, const std::string& s)
{
    std::int32_t size = static_cast<int32_t>(s.length());
    std::uint8_t buffer[sizeof(size)];
    MemoryWriter writer(&buffer[0], sizeof(size));
    std::expected<bool, int> rv = writer.Write(size);
    if (!rv) return rv;
    std::expected<bool, int> srv = socket.Send(&buffer[0], sizeof(size));
    if (!srv) return srv;
    return socket.Send(reinterpret_cast<const std::uint8_t*>(s.c_str()), size);
}

std::expected<std::string, int> ReadStr(TcpSocket& socket)
{
    std::int32_t size = 0;
    std::uint8_t buffer[sizeof(size)];
    int offset = 0;
    int bytesToReceive = sizeof(size);
    std::expected<int, int> rv = socket.Receive(&buffer[offset], bytesToReceive);
    if (!rv) return std::unexpected<int>(rv.error());
    int bytesReceived = *rv;
    if (bytesReceived == 0)
    {
        return std::string();
    }
    bytesToReceive = bytesToReceive - bytesReceived;
    offset = offset + bytesReceived;
    while (bytesToReceive > 0)
    {
        std::expected<int, int> rv = socket.Receive(&buffer[offset], bytesToReceive);
        if (!rv) return std::unexpected<int>(rv.error());
        bytesReceived = *rv;
        if (bytesReceived == 0)
        {
            return std::string();
        }
        bytesToReceive = bytesToReceive - bytesReceived;
        offset = offset + bytesReceived;
    }
    MemoryReader reader(&buffer[0], sizeof(size));
    std::expected<int32_t, int> irv = reader.ReadInt();
    if (!irv) return std::unexpected<int>(irv.error());
    size = *irv;
    if (size == 0)
    {
        return std::string();
    }
    std::unique_ptr<std::uint8_t[]> mem(new std::uint8_t[size]);
    offset = 0;
    bytesToReceive = size;
    std::expected<int, int> rrv = socket.Receive(mem.get() + offset, bytesToReceive);
    if (!rrv) return std::unexpected<int>(rrv.error());
    bytesReceived = *rrv;
    if (bytesReceived == 0)
    {
        return std::string();
    }
    bytesToReceive = bytesToReceive - bytesReceived;
    offset = offset + bytesReceived;
    while (bytesToReceive > 0)
    {
        rrv = socket.Receive(mem.get() + offset, bytesToReceive);
        if (!rrv) return std::unexpected<int>(rrv.error());
        bytesReceived = *rrv;
        if (bytesReceived == 0)
        {
            return std::string();
        }
        bytesToReceive = bytesToReceive - bytesReceived;
        offset = offset + bytesReceived;
    }
    std::string str(reinterpret_cast<const char*>(mem.get()), size);
    return std::expected<std::string, int>(str);
}

std::expected<bool, int> SocketInit()
{
    return Sockets::Init();
}

void SocketDone()
{
    Sockets::Done();
}

} // namespace util
