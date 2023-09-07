// =================================
// Copyright (c) 2023 Seppo Laakko
// Distributed under the MIT license
// =================================

import soul.json.rpc.socket_server;
import json.rpc.math.server;
import util;
import std.core;

int main()
{
    try
    {
        util::Init();
        json::rpc::math::server::Init();
        soul::json::rpc::StartServer(57000);
        std::string line;
        std::getline(std::cin, line);
        soul::json::rpc::StopServer();
        util::Done();
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << "\n";
        return 1;
    }
    return 0;
}