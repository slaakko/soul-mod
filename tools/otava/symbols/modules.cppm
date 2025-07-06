// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.modules;

import std;
import otava.symbols.symbol.table;
import otava.symbols.compound.type.symbol;
import otava.symbols.value;
import otava.symbols.symbol_map;
import otava.ast.file;
import otava.ast.node.map;
import otava.ast.node;

export namespace otava::symbols {

class Writer;
class Reader;
class Visitor;
class FunctionDefinitionSymbolSet;

std::string MakeModuleFilePath(const std::string& root, const std::string& config, const std::string& moduleName);

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
    void Import(ModuleMapper& moduleMapper, const std::string& config);
    void Import(Module* that, ModuleMapper& moduleMapper, const std::string& config);
    void ResolveForwardDeclarations();
    void ResolveAllForwardDeclarations();
    void AddDerivedClasses();
    void Write(const std::string& root, const std::string& config);
    void Write(Writer& writer);
    void ReadHeader(Reader& reader, ModuleMapper& moduleMapper);
    void CompleteRead(Reader& reader, ModuleMapper& moduleMapper, const std::string& config);
    void Init();
    std::int32_t FileId() const { return fileId; }
    void SetFileId(std::int32_t fileId_) { fileId = fileId_; }
    std::int32_t Id() const;
    std::int32_t Index() const { return index; }
    void SetIndex(std::int32_t index_) { index = index_; }
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
    void LoadImplementationUnits(ModuleMapper& moduleMapper, const std::string& config);
    otava::ast::NodeIdFactory* GetNodeIdFactory() { return &nodeIdFactory; }
private:
    std::int32_t fileId;
    std::int32_t index;
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
    Module* GetModule(const std::string& moduleName, const std::string& config);
    Module* LoadModule(const std::string& moduleName, const std::string& moduleFilePath, const std::string& config);
    void AddRoot(const std::string& root);
    otava::ast::NodeMap* GetNodeMap() { return &nodeMap; }
    SymbolMap* GetSymbolMap() { return &symbolMap; }
    void SetFunctionDefinitionSymbolSet(FunctionDefinitionSymbolSet* functionDefinitionSymbolSet_);
    FunctionDefinitionSymbolSet* GetFunctionDefinitionSymbolSet() const;
private:
    std::map<std::string, Module*> moduleMap;
    std::vector<std::unique_ptr<Module>> modules;
    std::vector<std::string> roots;
    std::recursive_mutex mtx;
    otava::ast::NodeMap nodeMap;
    SymbolMap symbolMap;
    FunctionDefinitionSymbolSet* functionDefinitionSymbolSet;
};

Module* GetCurrentModule();
void SetCurrentModule(Module* module);
void NodeDestroyed(otava::ast::Node* node);

} // namespace otava::symbols
