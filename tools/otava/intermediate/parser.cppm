// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.intermediate.main.parser;

import otava.intermediate.context;
import std;

export namespace otava::intermediate {

void Parse(const std::string& filePath, Context& context, bool verbose);

} // otava::intermediate
