// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.symbols.modules;

import std.core;
import soul.cpp20.symbols.symbol.table;
import soul.cpp20.symbols.compound.type.symbol;

export namespace soul::cpp20::symbols {

class Writer;
class Reader;

std::string MakeModuleFilePath(const std::string& root, const std::string& moduleName);

class ModuleMapper;

class Module
{
public:
    Module(const std::string& name_);
    const std::string& Name() const { return name; }
    void Import(ModuleMapper& moduleMapper);
    void Import(Module* that, ModuleMapper& moduleMapper);
    void Write(const std::string& root);
    void Write(Writer& writer);
    void Read(Reader& reader, ModuleMapper& moduleMapper);
    void Init();
    int File() const { return file; }
    void SetFile(int file_) { file = file_; }
    SymbolTable* GetSymbolTable() { return &symbolTable; }
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
private:
    int file;
    std::string name;
    std::vector<std::string> exportModuleNames;
    std::vector<Module*> exportedModules;
    std::vector<std::string> importModuleNames;
    std::vector<Module*> importedModules;
    SymbolTable symbolTable;
    std::vector<Module*> dependsOnModules;
};

class ModuleMapper
{
public:
    ModuleMapper();
    void AddModule(Module* module);
    Module* GetModule(const std::string& moduleName);
    void ClearModule(const std::string& moduleName);
    Module* LoadModule(const std::string& moduleName, const std::string& moduleFilePath);
private:
    std::map<std::string, Module*> moduleMap;
    std::vector<std::unique_ptr<Module>> modules;
    std::vector<std::string> roots;
};

} // namespace soul::cpp20::symbols
