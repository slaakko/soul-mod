// =================================
// Copyright (c) 2023 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.build_project;

import std.core;
import soul.lexer.file.map;
import otava.symbols;
import otava.symbols.function_definition_symbol_set;

export namespace otava::build_project {}

export namespace otava::build {

struct Define
{
    Define(const std::string& symbol_, int64_t value_);
    std::string symbol;
    int64_t value;
};

enum class Target : int32_t
{
    program, library
};

class Project
{
public:
    Project(const std::string& filePath_, const std::string& name_);
    void SetFileMap(soul::lexer::FileMap* fileMap_) { fileMap = fileMap_; }
    const std::string& FilePath() const { return filePath; }
    const std::string& Name() const { return name; }
    int16_t Id() const;
    void AddInterfaceFilePath(const std::string& interfaceFilePath);
    const std::vector<std::string>& InterfaceFilePaths() const { return interfaceFilePaths; }
    void AddSourceFilePath(const std::string& sourceFilePath);
    const std::vector<std::string>& SourceFilePaths() const { return sourceFilePaths; }
    void AddReferenceFilePath(const std::string& referenceFilePath);
    const std::vector<std::string>& ReferenceFilePaths() const { return referenceFilePaths; }
    soul::lexer::FileMap& GetFileMap() { return *fileMap; }
    void SetModule(int32_t fileId, otava::symbols::Module* module);
    otava::symbols::Module* GetModule(const std::string& moduleName) const;
    otava::symbols::Module* GetModule(int file) const;
    otava::symbols::Module* ReleaseModule(int file);
    void MapFiles();
    const std::string& Root() const { return root; }
    void AddRoots(otava::symbols::ModuleMapper& moduleMapper);
    const std::vector<int32_t>& InterfaceFiles() const { return interfaceFiles; }
    const std::vector<int32_t>& SourceFiles() const { return sourceFiles; }
    const std::string& GetModuleSourceFilePath(int32_t fileId) const;
    void InitModules();
    void LoadModules(otava::symbols::ModuleMapper& moduleMapper);
    bool UpToDate() const;
    bool Scanned() const { return scanned; }
    void SetScanned() { scanned = true; }
    const std::vector<std::unique_ptr<otava::symbols::Module>>& Modules() const { return modules; }
    const std::vector<std::string>& ModuleNames() const { return moduleNames; }
    const std::vector<Define>& Defines() const { return defines; }
    void AddDefine(const std::string& symbol, int64_t value);
    void ResolveForwardDeclarationsAndAddDerivedClasses(otava::symbols::ModuleMapper& moduleMapper);
    void SetTarget(Target target_) { target = target_; }
    Target GetTarget() const { return target; }
    info::class_index& Index() { return index; }
    otava::symbols::FunctionDefinitionSymbolSet* GetFunctionDefinitionSymbolSet() { return &functionDefinitionSymbolSet; }
private:
    soul::lexer::FileMap* fileMap;
    std::string filePath;
    std::string root;
    std::string name;
    Target target;
    std::vector<std::string> interfaceFilePaths;
    std::vector<std::string> sourceFilePaths;
    std::vector<std::string> referenceFilePaths;
    std::vector<std::unique_ptr<otava::symbols::Module>> modules;
    std::map<std::string, otava::symbols::Module*> moduleMap;
    std::map<int32_t, otava::symbols::Module*> fileIdModuleMap;
    std::vector<int32_t> interfaceFiles;
    std::vector<int32_t> sourceFiles;
    bool initialized;
    bool scanned;
    bool loaded;
    std::vector<std::string> moduleNames;
    std::vector<Define> defines;
    info::class_index index;
    otava::symbols::FunctionDefinitionSymbolSet functionDefinitionSymbolSet;
};

} // namespace otava::build
