// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.proj.ast;

import std.core;
import soul.lexer.file.map;
import soul.cpp20.symbols;

export namespace soul::cpp20::proj::ast {

class Project
{
public:
    Project(const std::string& filePath_, const std::string& name_);
    void Resize();
    const std::string& FilePath() const { return filePath; }
    const std::string& Name() const { return name; }
    void AddInterfaceFilePath(const std::string& interfaceFilePath);
    const std::vector<std::string>& InterfaceFilePaths() const { return interfaceFilePaths; }
    void AddSourceFilePath(const std::string& sourceFilePath);
    const std::vector<std::string>& SourceFilePaths() const { return sourceFilePaths; }
    soul::lexer::FileMap& GetFileMap() { return fileMap; }
    void SetModule(int file, soul::cpp20::symbols::Module* module);
    soul::cpp20::symbols::Module* GetModule(const std::string& moduleName) const;
    soul::cpp20::symbols::Module* GetModule(int file) const;
    soul::cpp20::symbols::Module* ReleaseModule(int file);
    void MapFiles();
    const std::string& Root() const { return root; }
    const std::vector<int>& InterfaceFiles() const { return interfaceFiles; }
    const std::vector<int>& SourceFiles() const { return sourceFiles; }
    const std::string& GetModuleSourceFilePath(int file) const;
    void InitModules();
    void LoadModules(soul::cpp20::ast::NodeIdFactory* nodeIdFactory, soul::cpp20::symbols::ModuleMapper& moduleMapper, soul::cpp20::symbols::Symbols* symbols);
    bool UpToDate() const;
    bool Scanned() const { return scanned; }
    void SetScanned() { scanned = true; }
    const std::vector<std::unique_ptr<soul::cpp20::symbols::Module>>& Modules() const { return modules; }
    const std::vector<std::string>& ModuleNames() const { return moduleNames; }
private:
    std::string filePath;
    std::string root;
    std::string name;
    std::vector<std::string> interfaceFilePaths;
    std::vector<std::string> sourceFilePaths;
    soul::lexer::FileMap fileMap;
    std::vector<std::unique_ptr<soul::cpp20::symbols::Module>> modules;
    std::map<std::string, soul::cpp20::symbols::Module*> moduleMap;
    std::vector<int> interfaceFiles;
    std::vector<int> sourceFiles;
    bool initialized;
    bool scanned;
    bool loaded;
    std::vector<std::string> moduleNames;
};

} // namespace soul::cpp20::proj::ast
