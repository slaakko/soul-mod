// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.build_project;

import otava.symbols.conversion.table;
import otava.ast.node;
import otava.ast.error;
import std.filesystem;
import util;

namespace otava::build {

Define::Define(const std::string& symbol_, int64_t value_) : symbol(symbol_), value(value_)
{
}

void LoadImportedModules(Project* project, otava::symbols::Module* module, otava::symbols::Module* importedModule, otava::symbols::ModuleMapper& moduleMapper)
{
    for (const std::string& importedModuleName : importedModule->ImportModuleNames())
    {
        otava::symbols::Module* projectModule = project->GetModule(importedModuleName);
        if (projectModule)
        {
            module->AddImportedModule(projectModule);
            module->AddDependsOnModule(projectModule);
            LoadImportedModules(project, module, projectModule, moduleMapper);
        }
        else
        {
            otava::symbols::Module* childModule = moduleMapper.GetModule(importedModuleName);
            module->AddImportedModule(childModule);
            module->AddDependsOnModule(childModule);
            module->Import(childModule, moduleMapper);
            LoadImportedModules(project, module, childModule, moduleMapper);
        }
    }
}

Project::Project(const std::string& filePath_, const std::string& name_) : filePath(filePath_), name(name_), initialized(false), scanned(false), loaded(false)
{
    root = util::Path::GetDirectoryName(filePath);
}

void Project::AddDefine(const std::string& symbol, int64_t value)
{
    defines.push_back(Define(symbol, value));
}

void Project::AddRoots(otava::symbols::ModuleMapper& moduleMapper)
{
    for (const auto& referenceFilePath : referenceFilePaths)
    {
        std::string referenceRoot = util::GetFullPath(util::Path::Combine(root, util::Path::GetDirectoryName(referenceFilePath)));
        moduleMapper.AddRoot(referenceRoot);
    }
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

const std::string& Project::GetModuleSourceFilePath(int32_t file) const
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

void Project::LoadModules(otava::symbols::ModuleMapper& moduleMapper)
{
    if (loaded) return;
    loaded = true;
    for (const auto& module : modules)
    {
        if (module)
        {
            moduleMap[module->Name()] = module.get();
            moduleNames.push_back(module->Name());
        }
    }
    for (const auto& module : modules)
    {
        if (!module) continue;
        for (const auto& exportedModuleName : module->ExportModuleNames())
        {
            otava::symbols::Module* exportedModule = GetModule(exportedModuleName);
            if (exportedModule)
            {
                module->AddExportedModule(exportedModule);
                module->AddDependsOnModule(exportedModule);
            }
            else
            {
                otava::ast::SetExceptionThrown();
                throw std::runtime_error("exported module '" + exportedModuleName + "' not found");
            }
        }
        for (const auto& importedModuleName : module->ImportModuleNames())
        {
            otava::symbols::Module* importedModule = GetModule(importedModuleName);
            bool loaded = false;
            if (!importedModule)
            {
                importedModule = moduleMapper.GetModule(importedModuleName);
                loaded = true;
            }
            module->AddImportedModule(importedModule);
            module->AddDependsOnModule(importedModule);
            LoadImportedModules(this, module.get(), importedModule, moduleMapper);
            if (loaded)
            {
                for (otava::symbols::Module* exportedModule : importedModule->ExportedModules())
                {
                    module->Import(exportedModule, moduleMapper);
                }
            }
        }
    }
}

void Project::SetModule(int32_t file, otava::symbols::Module* module)
{
    if (file >= 0 && file < modules.size())
    {
        modules[file].reset(module);
    }
    else
    {
        otava::ast::SetExceptionThrown();
        throw std::runtime_error("invalid file index");
    }
}

otava::symbols::Module* Project::GetModule(const std::string& moduleName) const
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

otava::symbols::Module* Project::GetModule(int32_t file) const
{
    if (file >= 0 && file < modules.size())
    {
        return modules[file].get();
    }
    else
    {
        otava::ast::SetExceptionThrown();
        throw std::runtime_error("invalid file index");
    }
}

otava::symbols::Module* Project::ReleaseModule(int32_t file)
{
    if (file >= 0 && file < modules.size())
    {
        return modules[file].release();
    }
    else
    {
        otava::ast::SetExceptionThrown();
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
        if (module)
        {
            const std::string& moduleSourceFilePath = GetModuleSourceFilePath(module->File());
            std::string moduleFilePath = otava::symbols::MakeModuleFilePath(root, module->Name());
            if (!std::filesystem::exists(moduleFilePath) || std::filesystem::last_write_time(moduleFilePath) < std::filesystem::last_write_time(moduleSourceFilePath))
            {
                return false;
            }
        }
    }
    return true;
}

void Project::AddReferenceFilePath(const std::string& referenceFilePath)
{
    referenceFilePaths.push_back(referenceFilePath);
}

void Project::ResolveForwardDeclarationsAndAddDerivedClasses(otava::symbols::ModuleMapper& moduleMapper)
{
    otava::symbols::Module projectModule(Name() + ".#project");
    for (const auto& moduleName : moduleNames)
    {
        otava::symbols::Module* module = moduleMapper.GetModule(moduleName);
        projectModule.Import(module, moduleMapper);
    }
    projectModule.ResolveForwardDeclarations();
    projectModule.AddDerivedClasses();
}

} // namespace otava::build
