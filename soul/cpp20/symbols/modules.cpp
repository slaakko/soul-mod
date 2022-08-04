// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.symbols.modules;

import util;
import std.filesystem;
import soul.cpp20.symbols.namespaces;
import soul.cpp20.symbols.reader;
import soul.cpp20.symbols.writer;

namespace soul::cpp20::symbols {

std::string MakeModuleFilePath(const std::string& root, const std::string& moduleName)
{
    return util::GetFullPath(util::Path::Combine(root, moduleName + ".module"));
}

Module::Module(const std::string& name_) : name(name_), symbolTable(), file(-1)
{
    symbolTable.SetModule(this);
}

void Module::Import(ModuleMapper& moduleMapper)
{
    for (const auto& exportedModuleName : exportModuleNames)
    {
        Module* exportedModule = moduleMapper.GetModule(exportedModuleName);
        AddExportedModule(exportedModule);
        AddDependsOnModule(exportedModule);
    }
    for (const auto& importedModuleName : importModuleNames)
    {
        Module* importedModule = moduleMapper.GetModule(importedModuleName);
        AddImportedModule(importedModule);
        AddDependsOnModule(importedModule);
    }
    for (auto dependsOnModule : dependsOnModules)
    {
        Import(dependsOnModule, moduleMapper);
    }
}

void Module::Import(Module* that, ModuleMapper& moduleMapper)
{
    that->Import(moduleMapper);
    symbolTable.Import(that->symbolTable);
}

void Module::Write(const std::string& root)
{
    std::string moduleFilePath = MakeModuleFilePath(root, name);
    Writer writer(moduleFilePath);
    Write(writer);
}

void Module::Init()
{
    symbolTable.Init();
}

void Module::AddExportModuleName(const std::string& exportModuleName)
{
    exportModuleNames.push_back(exportModuleName);
}

void Module::AddExportedModule(Module* exportedModule)
{
    if (std::find(exportedModules.cbegin(), exportedModules.cend(), exportedModule) == exportedModules.cend())
    {
        exportedModules.push_back(exportedModule);
    }
}

void Module::AddImportModuleName(const std::string& importModuleName)
{
    if (std::find(importModuleNames.cbegin(), importModuleNames.cend(), importModuleName) == importModuleNames.cend())
    {
        importModuleNames.push_back(importModuleName);
    }
}

void Module::AddImportedModule(Module* importedModule)
{
    if (std::find(importedModules.cbegin(), importedModules.cend(), importedModule) == importedModules.cend())
    {
        importedModules.push_back(importedModule);
    }
}

void Module::AddDependsOnModule(Module* dependsOnModule)
{
    if (std::find(dependsOnModules.cbegin(), dependsOnModules.cend(), dependsOnModule) == dependsOnModules.cend())
    {
        dependsOnModules.push_back(dependsOnModule);
    }
}

void Module::Write(Writer& writer)
{
    writer.GetBinaryStreamWriter().Write(name);
    uint32_t expCount = exportModuleNames.size();
    writer.GetBinaryStreamWriter().WriteULEB128UInt(expCount);
    for (const auto& exportedModuleName : exportModuleNames)
    {
        writer.GetBinaryStreamWriter().Write(exportedModuleName);
    }
    uint32_t impCount = importModuleNames.size();
    writer.GetBinaryStreamWriter().WriteULEB128UInt(impCount);
    for (const auto& importedModuleName : importModuleNames)
    {
        writer.GetBinaryStreamWriter().Write(importedModuleName);
    }
    symbolTable.Write(writer);
}

void Module::Read(Reader& reader, ModuleMapper& moduleMapper)
{
    name = reader.GetBinaryStreamReader().ReadUtf8String();
    uint32_t expCount = reader.GetBinaryStreamReader().ReadULEB128UInt();
    for (uint32_t i = 0; i < expCount; ++i)
    {
        AddExportModuleName(reader.GetBinaryStreamReader().ReadUtf8String());
    }
    uint32_t impCount = reader.GetBinaryStreamReader().ReadULEB128UInt();
    for (uint32_t i = 0; i < impCount; ++i)
    {
        AddImportModuleName(reader.GetBinaryStreamReader().ReadUtf8String());
    }
    symbolTable.Read(reader);
    Import(moduleMapper);
    symbolTable.Resolve();
}

ModuleMapper::ModuleMapper()
{
    roots.push_back(util::GetFullPath(util::Path::Combine(util::SoulRoot(), "soul/cpp20/std")));
}

void ModuleMapper::AddModule(Module* module)
{
    moduleMap[module->Name()] = module;
    modules.push_back(std::unique_ptr<Module>(module));
}

Module* ModuleMapper::GetModule(const std::string& moduleName)
{
    auto it = moduleMap.find(moduleName);
    if (it != moduleMap.cend())
    {
        return it->second;
    }
    else
    {
        for (const auto& root : roots)
        {
            std::string moduleFilePath = MakeModuleFilePath(root, moduleName);
            if (std::filesystem::exists(moduleFilePath))
            {
                return LoadModule(moduleName, moduleFilePath);
            }
        }
        throw std::runtime_error("module '" + moduleName + "' not found");
    }
}

void ModuleMapper::ClearModule(const std::string& moduleName)
{
    Module* module = nullptr;
    auto it = moduleMap.find(moduleName);
    if (it != moduleMap.cend())
    {
        module = it->second;
    }
    if (module)
    {
        for (auto& mod : modules)
        {
            if (mod.get() == module)
            {
                mod.reset();
            }
        }
    }
    moduleMap.erase(moduleName);
}

Module* ModuleMapper::LoadModule(const std::string& moduleName, const std::string& moduleFilePath)
{
    Reader reader(moduleFilePath);
    std::unique_ptr<Module> module(new Module(moduleName));
    module->Read(reader, *this);
    Module* modulePtr = module.get();
    moduleMap[moduleName] = modulePtr;
    modules.push_back(std::move(module));
    return modulePtr;
}

} // namespace soul::cpp20::symbols
