// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.build_project;

import std;
import soul.lexer.file.map;
import otava.symbols;
import otava.symbols.function_definition_symbol_set;

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

class Project;

struct ProjectLess
{
    bool operator()(Project* left, Project* right) const;
};

class Project
{
public:
    Project(const std::string& filePath_, const std::string& name_);
    ~Project();
    inline void SetFileMap(soul::lexer::FileMap* fileMap_) { fileMap = fileMap_; }
    inline const std::string& FilePath() const { return filePath; }
    inline const std::string& Name() const { return name; }
    inline const std::string& OutputFilePath() const { return outputFilePath; }
    void SetOutputFilePath(const std::string& outputFilePath_) { outputFilePath = outputFilePath_; }
    std::int16_t Id() const;
    void AddInterfaceFilePath(const std::string& interfaceFilePath);
    inline const std::vector<std::string>& InterfaceFilePaths() const { return interfaceFilePaths; }
    void AddSourceFilePath(const std::string& sourceFilePath);
    inline const std::vector<std::string>& SourceFilePaths() const { return sourceFilePaths; }
    void AddResourceFilePath(const std::string& resourceFilePath);
    inline const std::vector<std::string>& ResourceFilePaths() const { return resourceFilePaths; }
    void AddReferenceFilePath(const std::string& referenceFilePath);
    inline const std::vector<std::string>& ReferenceFilePaths() const { return referenceFilePaths; }
    void AddReferencedProject(Project* referencedProject);
    inline const std::vector<Project*>& ReferencedProjects() const { return referencedProjects; }
    inline soul::lexer::FileMap& GetFileMap() { return *fileMap; }
    void SetModule(std::int32_t fileId, otava::symbols::Module* module);
    otava::symbols::Module* GetModule(const std::string& moduleName) const;
    std::expected<otava::symbols::Module*, int> GetModule(std::int32_t fileId) const;
    std::expected<otava::symbols::Module*, int> ReleaseModule(std::int32_t fileId);
    std::expected<bool, int> MapFiles();
    inline const std::string& Root() const { return root; }
    std::expected<bool, int> AddRoots(otava::symbols::ModuleMapper& moduleMapper);
    inline const std::vector<std::int32_t>& InterfaceFiles() const { return interfaceFiles; }
    inline const std::vector<std::int32_t>& SourceFiles() const { return sourceFiles; }
    const std::string& GetModuleSourceFilePath(std::int32_t fileId) const;
    std::expected<bool, int> InitModules();
    std::expected<bool, int> LoadModules(otava::symbols::ModuleMapper& moduleMapper, const std::string& config, int optLevel);
    bool UpToDate(const std::string& config, int optLevel, int error) const;
    inline bool Scanned() const { return scanned; }
    inline void SetScanned() { scanned = true; }
    inline const std::vector<std::unique_ptr<otava::symbols::Module>>& Modules() const { return modules; }
    inline const std::vector<std::string>& ModuleNames() const { return moduleNames; }
    inline const std::vector<Define>& Defines() const { return defines; }
    void AddDefine(const std::string& symbol, std::int64_t value);
    std::expected<bool, int> ResolveForwardDeclarationsAndAddDerivedClasses(otava::symbols::ModuleMapper& moduleMapper, const std::string& config, int optLevel);
    inline void SetTarget(Target target_) { target = target_; }
    inline Target GetTarget() const { return target; }
    inline otava::symbols::class_index& Index() { return index; }
    inline otava::symbols::FunctionDefinitionSymbolSet* GetFunctionDefinitionSymbolSet() { return &functionDefinitionSymbolSet; }
    inline otava::symbols::TraceInfo& GetTraceInfo() { return traceInfo; };
    std::expected<bool, int> ReadTraceInfo(const std::string& moduleDir);
    std::expected<bool, int> WriteTraceInfo(const std::string& moduleDir);
    std::expected<bool, int> ReadClassIndex(const std::string& moduleDir);
    std::expected<bool, int> WriteClassIndex(const std::string& moduleDir);
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
    std::vector<Project*> referencedProjects;
    std::string outputFilePath;
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
    otava::symbols::class_index index;
    otava::symbols::FunctionDefinitionSymbolSet functionDefinitionSymbolSet;
    otava::symbols::TraceInfo traceInfo;
};

} // namespace otava::build
