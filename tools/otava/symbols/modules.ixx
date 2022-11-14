// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.modules;

import std.core;
import otava.symbols.symbol.table;
import otava.symbols.compound.type.symbol;
import otava.symbols.value;
import otava.symbols.symbol_map;
import otava.ast.file;
import otava.ast.node.map;

export namespace otava::symbols {

class Writer;
class Reader;
class Visitor;

std::string MakeModuleFilePath(const std::string& root, const std::string& moduleName);

class ModuleMapper;

class Module
{
public:
    Module(const std::string& name_);
    ~Module();
    void SetFilePath(const std::string& filePath_);
    const std::string& FilePath() const { return filePath; }
    const std::string& Name() const { return name; }
    void Accept(Visitor& visitor);
    void Import(ModuleMapper& moduleMapper);
    void Import(Module* that, ModuleMapper& moduleMapper);
    void ResolveForwardDeclarations();
    void AddDerivedClasses();
    void Write(const std::string& root);
    void Write(Writer& writer);
    void ReadHeader(Reader& reader, ModuleMapper& moduleMapper);
    void CompleteRead(Reader& reader, ModuleMapper& moduleMapper);
    void Init();
    int32_t File() const { return file; }
    void SetFile(int32_t file_) { file = file_; }
    int32_t Id() const;
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
    void SetFile(otava::ast::File* astFile_);
    otava::ast::File* GetFile() { return astFile.get(); }
    const std::vector<std::string>& ImplementationUnitNames() const { return implementationUnitNames; }
    void SetImplementationUnitNames(const std::vector<std::string>& names);
    const std::vector<Module*>& ImplementationUnits() const { return implementationUnits; }
    void AddImplementationUnit(Module* implementationUnit);
    void LoadImplementationUnits(ModuleMapper& moduleMapper);
    otava::ast::NodeIdFactory* GetNodeIdFactory() { return &nodeIdFactory; }
private:
    int32_t file;
    std::string name;
    std::string filePath;
    std::vector<std::string> exportModuleNames;
    std::vector<Module*> exportedModules;
    std::vector<std::string> importModuleNames;
    std::vector<Module*> importedModules;
    std::vector<std::string> implementationUnitNames;
    SymbolTable symbolTable;
    EvaluationContext evaluationContext;
    std::vector<Module*> implementationUnits;
    std::vector<Module*> dependsOnModules;
    std::unique_ptr<otava::ast::File> astFile;
    std::set<Module*> importSet;
    bool reading;
    otava::ast::NodeIdFactory nodeIdFactory;
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
    otava::ast::NodeMap* GetNodeMap() { return &nodeMap; }
    SymbolMap* GetSymbolMap() { return &symbolMap; }
private:
    std::map<std::string, Module*> moduleMap;
    std::vector<std::unique_ptr<Module>> modules;
    std::vector<std::string> roots;
    std::recursive_mutex mtx;
    otava::ast::NodeMap nodeMap;
    SymbolMap symbolMap;
};

Module* GetCurrentModule();
void SetCurrentModule(Module* module);
void NodeDestroyed(otava::ast::Node* node);

} // namespace otava::symbols
