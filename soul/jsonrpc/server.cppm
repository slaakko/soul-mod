// =================================
// Copyright (c) 2023 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.json.rpc.server;

import util;
import std.core;

export namespace soul::json::rpc {

void ProcessRequest(util::Stream& stream);

} // namespace soul::json::rpc
