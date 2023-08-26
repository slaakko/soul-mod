// =================================
// Copyright (c) 2023 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.json.rpc.socket_server;

import soul.json.rpc.server;
import util;

namespace soul::json::rpc {

class SocketServer
{
public:
    static SocketServer& Instance();
    void Start(int port);
    void Stop();
    void Run(int port);
private:
    SocketServer();
    int port;
    std::thread thread;
    bool exiting;
};

SocketServer& SocketServer::Instance()
{
    static SocketServer instance;
    return instance;
}

SocketServer::SocketServer() : port(0)
{
}

void RunServer(SocketServer* server, int port)
{
    server->Run(port);
}

void SocketServer::Start(int port)
{
    thread = std::thread(RunServer, this, port);
}

void SocketServer::Stop()
{
    if (port != 0)
    {
        exiting = true;
        util::TcpSocket socket("127.0.0.1", std::to_string(port));
        thread.join();
    }
}

void SocketServer::Run(int port)
{
    try
    {
        this->port = port;
        util::TcpSocket socket;
        socket.Bind(port);
        socket.Listen(10);
        while (!exiting)
        {
            util::TcpSocket clientSocket = socket.Accept();
            if (exiting) break;
            util::SocketStream socketStream(std::move(clientSocket));
            util::BufferedStream bufferedStream(socketStream);
            soul::json::rpc::ProcessRequest(bufferedStream);
        }
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << "\n";
    }
}

void StartServer(int port)
{
    SocketServer::Instance().Start(port);
}

void StopServer()
{
    SocketServer::Instance().Stop();
}

} // namespace soul::json::rpc
