export module otava.build.build;

import std;
import otava.build_project;
import otava.build_solution;
import otava.symbols.modules;
import soul.lexer.file.map;

export namespace otava::build {

enum class BuildFlags : std::int32_t
{
    none = 0, multithreadedBuild = 1 << 0, verbose = 1 << 1, debugParse = 1 << 2, xml = 1 << 3, symbolXml = 1 << 4, rebuild = 1 << 5, all = 1 << 6, seed = 1 << 7,
    debug = 1 << 8, gendoc = 1 << 9
};

constexpr BuildFlags operator|(BuildFlags left, BuildFlags right) noexcept
{
    return BuildFlags(std::int32_t(left) | std::int32_t(right));
}

constexpr BuildFlags operator&(BuildFlags left, BuildFlags right) noexcept
{
    return BuildFlags(std::int32_t(left) & std::int32_t(right));
}

constexpr BuildFlags operator~(BuildFlags flags) noexcept
{
    return BuildFlags(~std::int32_t(flags));
}

void ScanDependencies(Project* project, int file, bool implementationUnit, std::string& interfaceUnitName);
otava::symbols::Module* GetModule(otava::symbols::ModuleMapper& moduleMapper, const std::string& moduleName);
void Build(soul::lexer::FileMap& fileMap, Project* project, const std::string& config, int optLevel, BuildFlags flags, std::set<Project*, ProjectLess>& projectSet,
    std::ostream* outFile);
void Build(soul::lexer::FileMap& fileMap, Solution* solution, const std::string& config, int optLevel, BuildFlags flags, std::set<Project*, ProjectLess>& projectSet,
    std::ostream* outFile);

} // namespace otava::build
