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

std::string StdModuleFilePath(const std::string& moduleName);

class Module
{
public:
    Module(const std::string& name_);
    const std::string& Name() const { return name; }
    void Write(Writer& writer);
    void Read(Reader& reader);
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

} // namespace soul::cpp20::symbols
