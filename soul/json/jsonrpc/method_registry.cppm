// =================================
// Copyright (c) 2026 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.json.rpc.method.registry;

import std;
import soul.json.rpc.method;

export namespace soul::json::rpc {

void AddMethod(Method* method);
Method* GetMethod(const std::string& methodName);

} // namespace soul::json::rpc
