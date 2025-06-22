// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.codegen;

import std.core;
import otava.symbols.context;

export namespace otava::codegen {

std::string GenerateCode(otava::symbols::Context& context, const std::string& config, bool verbose, std::string& mainIrName, int& mainFunctionParams, bool globalMain,
    const std::vector<std::string>& compileUnitInitFnNames);

} // namespace otava::codegen
