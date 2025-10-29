// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.modules;

import std;
import util.uuid;
import otava.symbols.symbol.table;
import otava.symbols.compound.type.symbol;
import otava.symbols.evaluation_context;
import otava.symbols.value;
import otava.symbols.symbol_map;
import otava.ast.file;
import otava.ast.node.map;
import otava.ast.node;
import otava.ast.reader;
import otava.ast.writer;

export namespace otava::symbols {

class Writer;
class Reader;
class Visitor;
class FunctionDefinitionSymbolSet;

std::expected<std::string, int> MakeModuleFilePath(const std::string& root, const std::string& config, int optLevel, const std::string& moduleName);

class ModuleMapper;

struct ModuleLess
{
    bool operator()(Module* left, Module* right) const;
};

enum class ModuleKind : std::uint8_t
{
    interfaceModule, implementationModule,
};

util::uuid MakeProjectId(const std::string& projectName);

class Module
{
public:
    Module(const std::string& name_);
    ~Module();
    void SetProjectId(const util::uuid& projectId_);
    const util::uuid& GetProjectId() const { return projectId; }
    void SetKind(ModuleKind kind_) { kind = kind_; }
    ModuleKind Kind() const { return kind; }
    void SetFilePath(const std::string& filePath_);
    inline const std::string& FilePath() const { return filePath; }
    inline const std::string& Name() const { return name; }
    void Accept(Visitor& visitor);
    std::expected<bool, int> Import(ModuleMapper& moduleMapper, const std::string& config, int optLevel);
    std::expected<bool, int> Import(Module* that, ModuleMapper& moduleMapper, const std::string& config, int optLevel);
    std::expected<bool, int> ResolveForwardDeclarations();
    std::expected<bool, int> ResolveAllForwardDeclarations();
    void AddDerivedClasses();
    std::expected<bool, int> Write(const std::string& root, const std::string& config, int optLevel, Context* context);
    std::expected<bool, int> Write(Writer& writer, Context* context);
    std::expected<bool, int> ReadHeader(Reader& reader, ModuleMapper& moduleMapper);
    std::expected<bool, int> CompleteRead(Reader& reader, ModuleMapper& moduleMapper, const std::string& config, int optLevel);
    std::expected<bool, int> Init();
    inline std::int32_t FileId() const { return fileId; }
    inline void SetFileId(std::int32_t fileId_) { fileId = fileId_; }
    std::int32_t Id() const;
    inline std::int32_t Index() const { return index; }
    inline void SetIndex(std::int32_t index_) { index = index_; }
    inline std::int32_t ImportIndex() const { return importIndex; }
    inline void SetImportIndex(std::int32_t importIndex_) { importIndex = importIndex_; }
    inline SymbolTable* GetSymbolTable() { return &symbolTable; }
    inline EvaluationContext* GetEvaluationContext() { return &evaluationContext; }
    void AddExportModuleName(const std::string& exportModuleName);
    inline const std::vector<std::string>& ExportModuleNames() const { return exportModuleNames; }
    void AddExportedModule(Module* exportedModule);
    inline const std::vector<Module*>& ExportedModules() const { return exportedModules; }
    void AddImportModuleName(const std::string& importModuleName);
    inline const std::vector<std::string>& ImportModuleNames() const { return importModuleNames; }
    void AddImportedModule(Module* importedModule);
    inline const std::vector<Module*>& ImportedModules() const { return importedModules; }
    void AddDependsOnModule(Module* dependsOnModule);
    inline const std::vector<Module*>& DependsOnModules() const { return dependsOnModules; }
    void SetFile(otava::ast::File* astFile_);
    otava::ast::File* GetFile() { return astFile.get(); }
    inline const std::vector<std::string>& ImplementationUnitNames() const { return implementationUnitNames; }
    void SetImplementationUnitNames(const std::vector<std::string>& names);
    inline const std::vector<Module*>& ImplementationUnits() const { return implementationUnits; }
    void AddImplementationUnit(Module* implementationUnit);
    std::expected<bool, int> LoadImplementationUnits(ModuleMapper& moduleMapper, const std::string& config, int optLevel);
    inline otava::ast::NodeIdFactory* GetNodeIdFactory() { return &nodeIdFactory; }
    std::expected<bool, int> ToXml(const std::string& xmlFilePath) const;
private:
    ModuleKind kind;
    util::uuid projectId;
    std::int32_t fileId;
    std::int32_t index;
    std::int32_t importIndex;
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
    std::set<Module*, ModuleLess> importSet;
    bool reading;
    otava::ast::NodeIdFactory nodeIdFactory;
};

class ModuleMapper
{
public:
    ModuleMapper();
    void AddModule(Module* module);
    std::expected<std::string, int> GetModuleFilePath(const std::string& moduleName, const std::string& config, int optLevel) const;
    std::expected<std::string, int> GetProjectFilePath(const std::string& moduleName) const;
    std::expected<Module*, int> GetModule(const std::string& moduleName, const std::string& config, int optLevel);
    std::expected<Module*, int> LoadModule(const std::string& moduleName, const std::string& moduleFilePath, const std::string& config, int optLevel);
    void AddRoot(const std::string& root);
    inline otava::ast::NodeMap* GetNodeMap() { return &nodeMap; }
    inline SymbolMap* GetSymbolMap() { return &symbolMap; }
    void SetFunctionDefinitionSymbolSet(FunctionDefinitionSymbolSet* functionDefinitionSymbolSet_);
    FunctionDefinitionSymbolSet* GetFunctionDefinitionSymbolSet() const;
    int32_t ModuleCount() const;
    const std::vector<std::unique_ptr<Module>>& Modules() const { return modules; }
    inline bool Valid() const { return error == 0; }
    inline explicit operator bool() const { return Valid(); }
    inline int GetError() const { return error; }
    inline void SetError(int error_) { error = error_; }
private:
    std::map<std::string, Module*> moduleMap;
    std::vector<std::unique_ptr<Module>> modules;
    std::vector<std::string> roots;
    std::recursive_mutex mtx;
    otava::ast::NodeMap nodeMap;
    SymbolMap symbolMap;
    FunctionDefinitionSymbolSet* functionDefinitionSymbolSet;
    int error;
};

ModuleMapper* GetModuleMapper();
void SetModuleMapper(ModuleMapper* moduleMapper_);
Module* GetCurrentModule();
void SetCurrentModule(Module* module);
void NodeDestroyed(otava::ast::Node* node);
void SymbolDestroyed(Symbol* symbol);

} // namespace otava::symbols
