// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.project.build;

import std.core;
import soul.cpp20.symbols.modules;
import soul.cpp20.proj.ast;

export namespace soul::cpp20::project::build {

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

void ScanDependencies(soul::cpp20::proj::ast::Project* project, int file, bool implementationUnit, std::string& interfaceUnitName);
soul::cpp20::symbols::Module* GetModule(soul::cpp20::symbols::ModuleMapper& moduleMapper, const std::string& moduleName);
void Build(soul::cpp20::symbols::ModuleMapper& moduleMapper, soul::cpp20::proj::ast::Project* project, BuildFlags flags);
void Build(soul::cpp20::symbols::ModuleMapper& moduleMapper, soul::cpp20::proj::ast::Solution* solution, BuildFlags flags);

} // namespace soul::cpp20::project::build
