// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module util.socket;

import util.error;
import util.unicode;
import util.memory.writer;
import util.memory.reader;

namespace util {

std::string GetSocketErrorMessage(int errorCode)
{
    char buf[4096];
    ort_get_windows_error_message(errorCode, buf, 4096);
    std::string msg(buf);
    return msg;
}

int GetLastSocketError()
{
    return ort_get_last_socket_error();
}

class Sockets
{
public:
    static Sockets& Instance();
    std::expected<bool, int> Init();
    ~Sockets();
private:
    bool initialized;
    Sockets();
};

static Sockets& Sockets::Instance()
{
    static Sockets instance;
    return instance;
}

Sockets::Sockets() : initialized(false)
{
}

std::expected<bool, int> Sockets::Init()
{
    if (initialized) return std::expected<bool, int>(true);
    initialized = true;
    if (!ort_init_sockets())
    {
        int errorCode = GetLastSocketError();
        std::string msg = GetSocketErrorMessage(errorCode);
        std::string errorMessage = "socket initialization failed with error code " + std::to_string(errorCode) + ": " + msg;
        return std::unexpected<int>(AllocateError(errorMessage));
    }
    return std::expected<bool, int>(true);
}

void Sockets::~Sockets()
{
    if (initialized)
    {
        ort_done_sockets();
    }
}

std::expected<std::int64_t, int> CreateSocket()
{
    std::expected<bool, int> init = Sockets::Instance().Init();
    if (!init) return std::unexpected<int>(init.error());
    std::int64_t s = ort_socket();
    if (s == -1)
    {
        int errorCode = GetLastSocketError();
        std::expected<std::string, int> rv = GetSocketErrorMessage(errorCode);
        if (!rv) return std::unexpected<int>(rv.error());
        std::string errorMessage = *rv;
        return std::unexpected<int>(AllocateError(errorMessage));
    }
    return std::expected<std::int64_t, int>(s);
}

std::expected<bool, int> BindSocket(std::int64_t socketHandle, int port)
{
    std::expected<bool, int> init = Sockets::Instance().Init();
    if (!init) return std::unexpected<int>(init.error());
    bool result = ort_bind_socket(socketHandle, port);
    if (!result)
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
    std::expected<bool, int> init = Sockets::Instance().Init();
    if (!init) return std::unexpected<int>(init.error());
    bool result = ort_listen_socket(socketHandle, backlog);
    if (!result)
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
    std::expected<bool, int> init = Sockets::Instance().Init();
    if (!init) return std::unexpected<int>(init.error());
    std::int64_t a = ort_accept_socket(socketHandle);
    if (a == -1)
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
    std::expected<bool, int> init = Sockets::Instance().Init();
    if (!init) return std::unexpected<int>(init.error());
    bool result = ort_close_socket(socketHandle);
    if (!result)
    {
        int errorCode = GetLastSocketError();
        std::expected<std::string, int> rv = GetSocketErrorMessage(errorCode);
        if (!rv) return std::unexpected<int>(rv.error());
        std::string errorMessage = *rv;
        return std::unexpected<int>(AllocateError(errorMessage));
    }
    return std::expected<bool, int>(true);
}

const int SD_RECEIVE = 0;
const int SD_SEND = 1;
const int SD_BOTH = 2;

std::expected<bool, int> ShutdownSocket(std::int64_t socketHandle, ShutdownMode mode)
{
    std::expected<bool, int> init = Sockets::Instance().Init();
    if (!init) return std::unexpected<int>(init.error());
    int how = SD_RECEIVE;
    switch (mode)
    {
        case ShutdownMode::receive: { how = SD_RECEIVE; break; }
        case ShutdownMode::send: { how = SD_SEND; break; }
        case ShutdownMode::both: { how = SD_BOTH; break; }
    }
    bool result = ort_shutdown_socket(socketHandle, how);
    if (!result)
    {
        int errorCode = GetLastSocketError();
        std::expected<std::string, int> rv = GetSocketErrorMessage(errorCode);
        if (!rv) return std::unexpected<int>(rv.error());
        std::string errorMessage = *rv;
        return std::unexpected<int>(AllocateError(errorMessage));
    }
    return std::expected<bool, int>(true);
}

std::expected<std::int64_t, int> ConnectSocket(const std::string& node, const std::string& service)
{
    std::expected<bool, int> init = Sockets::Instance().Init();
    if (!init) return std::unexpected<int>(init.error());
    std::int64_t s = ort_connect_socket(node.c_str(), service.c_str());
    if (s != -1)
    {
        return std::expected<std::int64_t, int>(s);
    }
    else
    {
        int errorCode = GetLastSocketError();
        std::expected<std::string, int> rv = GetSocketErrorMessage(errorCode);
        if (!rv) return std::unexpected<int>(rv.error());
        std::string msg = *rv;
        std::string errorMessage = "could not connect to " + node + ":" + service + ": " + msg;
        return std::unexpected<int>(AllocateError(errorMessage));
    }
}

std::expected<int, int> SendSocket(std::int64_t socketHandle, const std::uint8_t* buf, int len, int flags)
{
    std::expected<bool, int> init = Sockets::Instance().Init();
    if (!init) return std::unexpected<int>(init.error());
    int result = ort_send_socket(socketHandle, buf, len, flags);
    if (result < 0)
    {
        int errorCode = GetLastSocketError();
        std::expected<std::string, int> rv = GetSocketErrorMessage(errorCode);
        if (!rv) return std::unexpected<int>(rv.error());
        std::string errorMessage = *rv;
        return std::unexpected<int>(AllocateError(errorMessage));
    }
    return std::expected<int, int>(result);
}

std::expected<int, int> ReceiveSocket(std::int64_t socketHandle, std::uint8_t* buf, int len, int flags)
{
    std::expected<bool, int> init = Sockets::Instance().Init();
    if (!init) return std::unexpected<int>(init.error());
    int result = ort_recv_socket(socketHandle, buf, len, flags);
    if (result < 0)
    {
        int errorCode = GetLastSocketError();
        std::expected<std::string, int> rv = GetSocketErrorMessage(errorCode);
        if (!rv) return std::unexpected<int>(rv.error());
        std::string errorMessage = *rv;
        return std::unexpected<int>(AllocateError(errorMessage));
    }
    return std::expected<int, int>(result);
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
    std::expected<int64_t, int> rv = ConnectSocket(node, service);
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
    std::uint8_t buffer[4];
    MemoryWriter writer(&buffer[0], 4);
    std::expected<bool, int> rv = writer.Write(size);
    if (!rv) return rv;
    std::expected<bool, int> srv = socket.Send(&buffer[0], 4);
    if (!srv) return srv;
    return socket.Send(reinterpret_cast<const std::uint8_t*>(s.c_str()), size);
}

std::expected<std::string, int> ReadStr(TcpSocket& socket)
{
    std::int32_t size = 0;
    std::uint8_t buffer[4];
    int offset = 0;
    int bytesToReceive = 4;
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
    MemoryReader reader(&buffer[0], 4);
    std::expected<int32_t, int> irv = reader.ReadInt();
    if (!irv) return std::unexpected<int>(irv.error());
    size = *irv;
    if (size == 0)
    {
        return std::string();
    }
    std::unique_ptr<std::uint8_t> mem(static_cast<std::uint8_t*>(std::malloc(size)));
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

} // namespace util
