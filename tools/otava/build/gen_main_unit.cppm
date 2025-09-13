// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.build.gen_main_unit;

import std;
import otava.symbols.modules;

export namespace otava::build {

std::string GenerateMainUnit(otava::symbols::ModuleMapper& moduleMapper, const std::string& mainFilePath, const std::string& mainFunctionIrName, int numParams, 
    const std::vector<std::string>& compileUnitInitFnNames, const std::string& config, int optLevel);

} // namespace otava::build
