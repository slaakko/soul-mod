// =================================
// Copyright (c) 2023 Seppo Laakko
// Distributed under the MIT license
// =================================

import soul.json.rpc;
import json.rpc.math.server;
import util;
import std.core;
import std.filesystem;

int main()
{
    try
    {
        util::Init();
        soul::json::rpc::Config::Instance().SetLogDir(util::GetFullPath(util::Path::Combine(util::SoulRoot(), "log")));
        std::filesystem::create_directories(soul::json::rpc::Config::Instance().LogDir());
        json::rpc::math::server::Init();
        soul::json::rpc::RunServer(57000, false);
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << "\n";
        return 1;
    }
    return 0;
}