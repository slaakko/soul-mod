// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module gendoc.project;

import std.core;
import soul.cpp20.project.init;
import soul.cpp20.proj.ast;
import gendoc.namespace_symbols;

export namespace gendoc {

class Project
{
public:
    Project(const std::string& path_, bool verbose_, bool force_, bool multithreaded_, soul::cpp20::project::init::Init& init_);
    void SetParent(Project* parent_) { parent = parent_; }
    void Build(Project* nsProject);
    std::string FullName() const;
    const std::string& RootDir() const { return rootDir; }
    void AddToNamespace(soul::cpp20::symbols::NamespaceSymbol* ns, soul::cpp20::symbols::Symbol* symbol);
private:
    void BuildCppProject();
    void GenerateDocs(Project* nsProject);
    void GenerateModuleDocs(Project* nsProject);
    void GenerateModuleDoc(const std::string& moduleName, Project* nsProject);
    void GenerateNamespaceDocs();
    NamespaceSymbols* GetOrInsertNamespaceSymbols(const std::string& nsDocName, const std::string& namespaceName);
    Project* parent;
    std::string path;
    soul::cpp20::project::init::Init& init;
    std::string name;
    std::string rootDir;
    std::string cppProjectFilePath;
    bool verbose;
    bool force;
    bool multithreaded;
    bool generateNamespaceDocs;
    std::vector<std::unique_ptr<Project>> subProjects;
    std::unique_ptr<soul::cpp20::proj::ast::Project> project;
    std::vector<std::unique_ptr<NamespaceSymbols>> nsSymbols;
    std::map<std::string, NamespaceSymbols*> nsSymbolMap;
};

void BuildProject(const std::string& path, bool verbose, bool force, bool multithreaded);

} // namespace gendoc
