// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module gendoc.project;

import std;
import otava.build_project;
import otava.build_solution;
import otava.symbols;
import soul.lexer;
import soul.xml.dom;
import gendoc.namespace_symbols;

export namespace gendoc {

class Project
{
public:
    Project(const std::string& path_, bool verbose_, bool force_, bool multithreaded_, otava::build::Project& init_);
    void SetParent(Project* parent_) { parent = parent_; }
    void Build(Project* nsProject);
    std::string FullName() const;
    const std::string& RootDir() const { return rootDir; }
    void AddToNamespace(otava::symbols::NamespaceSymbol* ns, otava::symbols::Symbol* symbol);
    otava::build::Project* Init() { return &init; }
    inline const std::set<std::string>& Configurations() const noexcept { return configurations; }
    inline otava::build::Project* BuildProject() const noexcept { return buildProject; }
    inline void SetBuildProject(otava::build::Project* buildProject_) noexcept { buildProject = buildProject_; }
    inline const std::vector<std::unique_ptr<Project>>& SubProjects() const { return subProjects; }
    inline const std::string& CppProjectFilePath() const noexcept { return cppProjectFilePath; }
private:
    otava::build::Solution* MakeSolution();
    void BuildSolution(otava::build::Solution* solution);
    void GenerateDocs(Project* nsProject);
    void GenerateProjectDocs();
    void GenerateModuleDocs(Project* nsProject);
    void GenerateModuleDoc(const std::string& moduleName, Project* nsProject);
    void GenerateNamespaceDocs();
    void GenerateMainIndex();
    NamespaceSymbols* GetOrInsertNamespaceSymbols(const std::string& nsDocName, const std::string& namespaceName);
    Project* parent;
    std::string path;
    otava::build::Project& init;
    std::string name;
    std::string rootDir;
    std::string cppProjectFilePath;
    bool verbose;
    bool force;
    bool multithreaded;
    bool generateNamespaceDocs;
    std::vector<std::unique_ptr<Project>> subProjects;
    otava::build::Project* buildProject;
    std::vector<std::unique_ptr<NamespaceSymbols>> nsSymbols;
    std::map<std::string, NamespaceSymbols*> nsSymbolMap;
    soul::lexer::FileMap fileMap;
    std::set<otava::build::Project*, otava::build::ProjectLess> projectSet;
    std::set<std::string> configurations;
};

void BuildProject(const std::string& path, bool verbose, bool force, bool multithreaded);

} // namespace gendoc
