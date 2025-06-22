// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

import soul.json.rpc;
import util;
import std;

int main()
{
    try
    {
        util::Init();
        std::unique_ptr<util::JsonArray> params(new util::JsonArray());
        params->AddItem(std::unique_ptr<util::JsonValue>(new util::JsonNumber(1.5)));
        params->AddItem(std::unique_ptr<util::JsonValue>(new util::JsonNumber(2)));
        std::unique_ptr<util::JsonValue> request = soul::json::rpc::MakePositionalParamRequest("add", params.get(), 1);
        util::CodeFormatter formatter(std::cout);
        request->Write(formatter);
        std::unique_ptr<util::JsonValue> response = soul::json::rpc::SendReceive(57000, request.get());
        response->Write(formatter);
        util::Done();
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << "\n";
        return 1;
    }
}