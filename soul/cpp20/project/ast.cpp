// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.proj.ast;

import std.filesystem;
import util;
import soul.cpp20.ast.node;

namespace soul::cpp20::proj::ast {

Project::Project(const std::string& filePath_, const std::string& name_) : filePath(filePath_), name(name_), initialized(false), scanned(false), loaded(false)
{
}

void Project::Resize()
{
    fileMap.Resize();
    modules.resize(fileMap.Count());
}

void Project::AddInterfaceFilePath(const std::string& interfaceFilePath)
{
    interfaceFilePaths.push_back(interfaceFilePath);
}

void Project::AddSourceFilePath(const std::string& sourceFilePath)
{
    sourceFilePaths.push_back(sourceFilePath);
}

const std::string& Project::GetModuleSourceFilePath(int file) const
{
    return fileMap.GetFilePath(file);
}

void Project::InitModules()
{
    if (initialized) return;
    initialized = true;
    MapFiles();
    Resize();
}

void Project::LoadModules(soul::cpp20::ast::NodeIdFactory* nodeIdFactory, soul::cpp20::symbols::ModuleMapper& moduleMapper, soul::cpp20::symbols::Symbols* symbols)
{
    if (loaded) return;
    loaded = true;
    for (const auto& module : modules)
    {
        moduleMap[module->Name()] = module.get();
        moduleNames.push_back(module->Name());
    }
    soul::cpp20::ast::SetNodeIdFactory(nodeIdFactory);
    soul::cpp20::symbols::SetSymbols(symbols);
    for (const auto& module : modules)
    {
        for (const auto& exportedModuleName : module->ExportModuleNames())
        {
            soul::cpp20::symbols::Module* exportedModule = GetModule(exportedModuleName);
            if (exportedModule)
            {
                module->AddExportedModule(exportedModule);
                module->AddDependsOnModule(exportedModule);
            }
            else
            {
                throw std::runtime_error("exported module '" + exportedModuleName + "' not found");
            }
        }
        for (const auto& importedModuleName : module->ImportModuleNames())
        {
            soul::cpp20::symbols::Module* importedModule = GetModule(importedModuleName);
            if (!importedModule)
            {
                importedModule = moduleMapper.GetModule(importedModuleName);
            }
            module->AddImportedModule(importedModule);
            module->AddDependsOnModule(importedModule);
            for (soul::cpp20::symbols::Module* exportedModule : importedModule->ExportedModules())
            {
                module->Import(exportedModule, moduleMapper);
            }
        }
    }
}

void Project::SetModule(int file, soul::cpp20::symbols::Module* module)
{
    if (file >= 0 && file < modules.size())
    {
        modules[file].reset(module);
    }
    else
    {
        throw std::runtime_error("invalid file index");
    }
}

soul::cpp20::symbols::Module* Project::GetModule(const std::string& moduleName) const
{
    auto it = moduleMap.find(moduleName);
    if (it != moduleMap.cend())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}

soul::cpp20::symbols::Module* Project::GetModule(int file) const
{
    if (file >= 0 && file < modules.size())
    {
        return modules[file].get();
    }
    else
    {
        throw std::runtime_error("invalid file index");
    }
}

soul::cpp20::symbols::Module* Project::ReleaseModule(int file)
{
    if (file >= 0 && file < modules.size())
    {
        return modules[file].release();
    }
    else
    {
        throw std::runtime_error("invalid file index");
    }
}

void Project::MapFiles()
{
    root = util::Path::GetDirectoryName(filePath);
    for (const auto& interfaceFileName : interfaceFilePaths)
    {
        std::string interfaceFilePath = util::GetFullPath(util::Path::Combine(root, interfaceFileName));
        interfaceFiles.push_back(fileMap.AddFilePath(interfaceFilePath));
    }
    for (const auto& sourceFileName : sourceFilePaths)
    {
        std::string sourceFilePath = util::GetFullPath(util::Path::Combine(root, sourceFileName));
        sourceFiles.push_back(fileMap.AddFilePath(sourceFilePath));
    }
}

bool Project::UpToDate() const
{
    for (const auto& module : modules)
    {
        const std::string& moduleSourceFilePath = GetModuleSourceFilePath(module->File());
        std::string moduleFilePath = soul::cpp20::symbols::MakeModuleFilePath(root, module->Name());
        if (!std::filesystem::exists(moduleFilePath) || std::filesystem::last_write_time(moduleFilePath) < std::filesystem::last_write_time(moduleSourceFilePath))
        {
            return false;
        }
    }
    return true;
}

} // namespace soul::cpp20::proj::ast
