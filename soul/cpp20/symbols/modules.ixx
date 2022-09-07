// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.symbols.modules;

import std.core;
import soul.cpp20.symbols.symbol.table;
import soul.cpp20.symbols.compound.type.symbol;
import soul.cpp20.symbols.value;
import soul.cpp20.ast.file;
import soul.cpp20.ast.node.map;

export namespace soul::cpp20::symbols {

class Writer;
class Reader;
class Visitor;

std::string MakeModuleFilePath(const std::string& root, const std::string& moduleName);

class ModuleMapper;

class Module
{
public:
    Module(const std::string& name_);
    const std::string& Name() const { return name; }
    void Accept(Visitor& visitor);
    void Import(ModuleMapper& moduleMapper);
    void Import(Module* that, ModuleMapper& moduleMapper);
    void ResolveForwardDeclarations();
    void AddDerivedClasses();
    void Write(const std::string& root);
    void Write(Writer& writer);
    void ReadHeader(Reader& reader, ModuleMapper& moduleMapper);
    void CompleteRead(Reader& reader, ModuleMapper& moduleMapper, soul::cpp20::ast::NodeMap* nodeMap);
    void Init();
    int File() const { return file; }
    void SetFile(int file_) { file = file_; }
    SymbolTable* GetSymbolTable() { return &symbolTable; }
    EvaluationContext* GetEvaluationContext() { return &evaluationContext; }
    void AddExportModuleName(const std::string& exportModuleName);
    const std::vector<std::string>& ExportModuleNames() const { return exportModuleNames; }
    void AddExportedModule(Module* exportedModule);
    const std::vector<Module*>& ExportedModules() const { return exportedModules; }
    void AddImportModuleName(const std::string& importModuleName);
    const std::vector<std::string>& ImportModuleNames() const { return importModuleNames; }
    void AddImportedModule(Module* importedModule);
    const std::vector<Module*>& ImportedModules() const { return importedModules; }
    void AddDependsOnModule(Module* dependsOnModule);
    const std::vector<Module*>& DependsOnModules() const { return dependsOnModules; }
    void SetFile(soul::cpp20::ast::File* astFile_);
    soul::cpp20::ast::File* GetFile() { return astFile.get(); }
    const std::vector<Module*>& ImplementationUnits() const { return implementationUnits; }
    void AddImplementationUnit(Module* implementationUnit);
private:
    int file;
    std::string name;
    std::vector<std::string> exportModuleNames;
    std::vector<Module*> exportedModules;
    std::vector<std::string> importModuleNames;
    std::vector<Module*> importedModules;
    SymbolTable symbolTable;
    EvaluationContext evaluationContext;
    std::vector<Module*> implementationUnits;
    std::vector<Module*> dependsOnModules;
    std::unique_ptr<soul::cpp20::ast::File> astFile;
    std::set<Module*> importSet;
    bool reading;
};

struct ModuleNameLess
{
    bool operator()(Module* left, Module* right) const;
};

class ModuleMapper
{
public:
    ModuleMapper();
    void AddModule(Module* module);
    Module* GetModule(const std::string& moduleName);
    Module* LoadModule(const std::string& moduleName, const std::string& moduleFilePath);
    void AddRoot(const std::string& root);
    void ClearNodeMap();
private:
    std::map<std::string, Module*> moduleMap;
    std::vector<std::unique_ptr<Module>> modules;
    std::vector<std::string> roots;
    std::recursive_mutex mtx;
    soul::cpp20::ast::NodeMap nodeMap;
};

Module* GetCurrentModule();
void SetCurrentModule(Module* module);
void NodeDestroyed(soul::cpp20::ast::Node* node);

} // namespace soul::cpp20::symbols
