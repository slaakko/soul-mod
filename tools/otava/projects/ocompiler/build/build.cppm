// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.build.build;

import std;
import otava.build_project;
import otava.build_solution;
import otava.symbols.modules;
import soul.lexer.file.map;

export namespace otava::build {

enum class BuildFlags : std::int32_t
{
    none = 0, multithreadedBuild = 1 << 0, verbose = 1 << 1, debugParse = 1 << 2, xml = 1 << 3, symbolXml = 1 << 4, rebuild = 1 << 5, all = 1 << 6, seed = 1 << 7
};

constexpr BuildFlags operator|(BuildFlags left, BuildFlags right)
{
    return BuildFlags(std::int32_t(left) | std::int32_t(right));
}

constexpr BuildFlags operator&(BuildFlags left, BuildFlags right)
{
    return BuildFlags(std::int32_t(left) & std::int32_t(right));
}

constexpr BuildFlags operator~(BuildFlags flags)
{
    return BuildFlags(~std::int32_t(flags));
}

std::expected<bool, int> ScanDependencies(Project* project, int file, bool implementationUnit, std::string& interfaceUnitName);
otava::symbols::Module* GetModule(otava::symbols::ModuleMapper& moduleMapper, const std::string& moduleName);
std::expected<bool, int> Build(soul::lexer::FileMap& fileMap, Project* project, const std::string& config, int optLevel, BuildFlags flags, 
    std::set<Project*, ProjectLess>& projectSet);
std::expected<bool, int> Build(soul::lexer::FileMap& fileMap, Solution* solution, const std::string& config, int optLevel, BuildFlags flags, 
    std::set<Project*, ProjectLess>& projectSet);

} // namespace otava::build
