// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module util_expected.socket;

import std;

export namespace util {

enum class ShutdownMode
{
    receive = 0, send = 1, both = 2
};

std::expected<std::int64_t, int> CreateSocket();
std::expected<bool, int> BindSocket(std::int64_t socketHandle, int port);
std::expected<bool, int> ListenSocket(std::int64_t socketHandle, int backLog);
std::expected<std::int64_t, int> AcceptSocket(std::int64_t socketHandle);
std::expected<bool, int> CloseSocket(std::int64_t socketHandle);
std::expected<bool, int> ShutdownSocket(std::int64_t socketHandle, ShutdownMode mode);
std::expected<std::int64_t, int> ConnectSocket(const std::string& node, const std::string& service);
std::expected<int, int> SendSocket(std::int64_t socketHandle, const std::uint8_t* buf, int len, int flags);
std::expected<int, int> ReceiveSocket(std::int64_t socketHandle, std::uint8_t* buf, int len, int flags);
std::expected<bool, int> SocketInit();
void SocketDone();

class TcpSocket
{
public:
    TcpSocket();
    TcpSocket(const std::string& node, const std::string& service);
    TcpSocket(std::int64_t handle_) noexcept;
    TcpSocket(const TcpSocket&) = delete;
    TcpSocket& operator=(const TcpSocket&) = delete;
    TcpSocket(TcpSocket&& that) noexcept;
    TcpSocket& operator=(TcpSocket&& that) noexcept;
    ~TcpSocket();
    std::expected<bool, int> Close();
    std::expected<bool, int> Connect(const std::string& node, const std::string& service);
    std::expected<bool, int> Bind(int port);
    std::expected<bool, int> Listen(int backlog);
    std::expected<TcpSocket, int> Accept();
    std::expected<bool, int> Shutdown(ShutdownMode mode);
    std::expected<bool, int> Send(const std::uint8_t* buffer, int count);
    std::expected<int, int> Receive(std::uint8_t* buffer, int count);
    inline bool Valid() const { return error == 0; }
    inline explicit operator bool() const { return Valid(); }
    inline int Error() const { return error; }
private:
    std::int64_t handle;
    bool connected;
    bool shutdown;
    int error;
};

std::expected<bool, int> Write(TcpSocket& socket, const std::string& s);
std::expected<std::string, int> ReadStr(TcpSocket& socket);

} // namespace util
