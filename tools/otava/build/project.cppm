// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.build_project;

import std;
import soul.lexer.file.map;
import class_info_index;
import otava.symbols;
import otava.symbols.function_definition_symbol_set;

export namespace otava::build_project {}

export namespace otava::build {

struct Define
{
    Define(const std::string& symbol_, std::int64_t value_);
    std::string symbol;
    std::int64_t value;
};

enum class Target : std::int32_t
{
    program, library
};

class Project
{
public:
    Project(const std::string& filePath_, const std::string& name_);
    inline void SetFileMap(soul::lexer::FileMap* fileMap_) { fileMap = fileMap_; }
    inline const std::string& FilePath() const { return filePath; }
    inline const std::string& Name() const { return name; }
    std::int16_t Id() const;
    void AddInterfaceFilePath(const std::string& interfaceFilePath);
    inline const std::vector<std::string>& InterfaceFilePaths() const { return interfaceFilePaths; }
    void AddSourceFilePath(const std::string& sourceFilePath);
    inline const std::vector<std::string>& SourceFilePaths() const { return sourceFilePaths; }
    void AddResourceFilePath(const std::string& resourceFilePath);
    inline const std::vector<std::string>& ResourceFilePaths() const { return resourceFilePaths; }
    void AddReferenceFilePath(const std::string& referenceFilePath);
    inline const std::vector<std::string>& ReferenceFilePaths() const { return referenceFilePaths; }
    inline soul::lexer::FileMap& GetFileMap() { return *fileMap; }
    void SetModule(std::int32_t fileId, otava::symbols::Module* module);
    otava::symbols::Module* GetModule(const std::string& moduleName) const;
    otava::symbols::Module* GetModule(int file) const;
    otava::symbols::Module* ReleaseModule(int file);
    void MapFiles();
    inline const std::string& Root() const { return root; }
    void AddRoots(otava::symbols::ModuleMapper& moduleMapper);
    inline const std::vector<std::int32_t>& InterfaceFiles() const { return interfaceFiles; }
    inline const std::vector<std::int32_t>& SourceFiles() const { return sourceFiles; }
    const std::string& GetModuleSourceFilePath(std::int32_t fileId) const;
    void InitModules();
    void LoadModules(otava::symbols::ModuleMapper& moduleMapper, const std::string& config);
    bool UpToDate(const std::string& config) const;
    inline bool Scanned() const { return scanned; }
    inline void SetScanned() { scanned = true; }
    inline const std::vector<std::unique_ptr<otava::symbols::Module>>& Modules() const { return modules; }
    inline const std::vector<std::string>& ModuleNames() const { return moduleNames; }
    inline const std::vector<Define>& Defines() const { return defines; }
    void AddDefine(const std::string& symbol, std::int64_t value);
    void ResolveForwardDeclarationsAndAddDerivedClasses(otava::symbols::ModuleMapper& moduleMapper, const std::string& config);
    inline void SetTarget(Target target_) { target = target_; }
    inline Target GetTarget() const { return target; }
    inline info::class_index& Index() { return index; }
    inline otava::symbols::FunctionDefinitionSymbolSet* GetFunctionDefinitionSymbolSet() { return &functionDefinitionSymbolSet; }
private:
    soul::lexer::FileMap* fileMap;
    std::string filePath;
    std::string root;
    std::string name;
    Target target;
    std::vector<std::string> interfaceFilePaths;
    std::vector<std::string> sourceFilePaths;
    std::vector<std::string> resourceFilePaths;
    std::vector<std::string> referenceFilePaths;
    std::vector<std::unique_ptr<otava::symbols::Module>> modules;
    std::map<std::string, otava::symbols::Module*> moduleMap;
    std::map<std::int32_t, otava::symbols::Module*> fileIdModuleMap;
    std::vector<std::int32_t> interfaceFiles;
    std::vector<std::int32_t> sourceFiles;
    bool initialized;
    bool scanned;
    bool loaded;
    std::vector<std::string> moduleNames;
    std::vector<Define> defines;
    info::class_index index;
    otava::symbols::FunctionDefinitionSymbolSet functionDefinitionSymbolSet;
};

} // namespace otava::build
