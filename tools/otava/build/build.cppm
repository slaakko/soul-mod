// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.build.build;

import std.core;
import otava.symbols.modules;
import soul.lexer.file.map;

export namespace otava::build {

class Project;
class Solution;

enum class BuildFlags : int32_t
{
    none = 0, multithreadedBuild = 1 << 0, verbose = 1 << 1, debugParse = 1 << 2, xml = 1 << 3
};

constexpr BuildFlags operator|(BuildFlags left, BuildFlags right)
{
    return BuildFlags(int32_t(left) | int32_t(right));
}

constexpr BuildFlags operator&(BuildFlags left, BuildFlags right)
{
    return BuildFlags(int32_t(left) & int32_t(right));
}

constexpr BuildFlags operator~(BuildFlags flags)
{
    return BuildFlags(~int32_t(flags));
}

void ScanDependencies(Project* project, int file, bool implementationUnit, std::string& interfaceUnitName);
otava::symbols::Module* GetModule(otava::symbols::ModuleMapper& moduleMapper, const std::string& moduleName);
void Build(otava::symbols::ModuleMapper& moduleMapper, Project* project, const std::string& config, BuildFlags flags);
void Build(otava::symbols::ModuleMapper& moduleMapper, soul::lexer::FileMap& fileMap, Solution* solution, const std::string& config, BuildFlags flags);

} // namespace otava::build
