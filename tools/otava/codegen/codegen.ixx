// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.codegen;

import std.core;
import otava.symbols.context;

export namespace otava::codegen {

std::string GenerateCode(otava::symbols::Context& context, const std::string& config, bool verbose, std::string& mainIrName, int& mainFunctionParams);

} // namespace otava::ast
