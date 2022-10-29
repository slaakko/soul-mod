// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.build.gen_main_unit;

import std.core;

export namespace otava::build {

void GenerateMainUnit(const std::string& mainFilePath, const std::string& mainFunctionIrName, int numParams);

} // namespace otava::build
