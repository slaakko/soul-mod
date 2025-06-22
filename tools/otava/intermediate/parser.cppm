// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.intermediate.parser;

import std.core;

export namespace otava::intermediate {

class Context;

void ParseIntermediateCodeFile(const std::string& filePath, Context& context);

} // namespace otava::intermediate
