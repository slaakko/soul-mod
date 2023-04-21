// =================================
// Copyright (c) 2023 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.build.gen_main_unit;

import std.core;
import otava.symbols.modules;

export namespace otava::build {

std::string GenerateMainUnit(otava::symbols::ModuleMapper& moduleMapper, const std::string& mainFilePath, const std::string& mainFunctionIrName, int numParams, 
    const std::vector<std::string>& compileUnitInitFnNames, const std::string& config);

} // namespace otava::build
