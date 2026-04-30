// =================================
// Copyright (c) 2026 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.json.rpc.server;

import util;
import std;

export namespace soul::json::rpc {

bool ProcessRequest(util::Stream& stream, bool& wait);

} // namespace soul::json::rpc
