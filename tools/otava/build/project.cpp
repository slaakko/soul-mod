// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.build_project;

import otava.symbols.conversion.table;
import otava.ast.node;
import otava.ast.error;
import std.filesystem;
import util;

namespace otava::build {

std::int32_t MakeFileId(std::int16_t projectId, std::int16_t fileIndex)
{
    return static_cast<std::int32_t>(projectId) << 16 | static_cast<std::int32_t>(fileIndex);
}

Define::Define(const std::string& symbol_, std::int64_t value_) : symbol(symbol_), value(value_)
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
            if (project->GetTarget() == Target::program)
            {
                project->Index().imp(projectModule->GetSymbolTable()->ClassIndex(), true);
            }
        }
        else
        {
            otava::symbols::Module* childModule = moduleMapper.GetModule(importedModuleName);
            module->AddImportedModule(childModule);
            module->AddDependsOnModule(childModule);
            module->Import(childModule, moduleMapper);
            LoadImportedModules(project, module, childModule, moduleMapper);
            if (project->GetTarget() == Target::program)
            {
                project->Index().imp(childModule->GetSymbolTable()->ClassIndex(), true);
            }
        }
    }
}

Project::Project(const std::string& filePath_, const std::string& name_) : 
    fileMap(nullptr), filePath(filePath_), name(name_), initialized(false), scanned(false), loaded(false), target(Target::program)
{
    root = util::Path::GetDirectoryName(filePath);
}

std::int16_t Project::Id() const
{
    return static_cast<std::int16_t>(std::hash<std::string>()(name) & 0x7FFF);
}

void Project::AddDefine(const std::string& symbol, std::int64_t value)
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

void Project::AddInterfaceFilePath(const std::string& interfaceFilePath)
{
    interfaceFilePaths.push_back(interfaceFilePath);
}

void Project::AddSourceFilePath(const std::string& sourceFilePath)
{
    sourceFilePaths.push_back(sourceFilePath);
}

void Project::AddResourceFilePath(const std::string& resourceFilePath)
{
    resourceFilePaths.push_back(resourceFilePath);
}

const std::string& Project::GetModuleSourceFilePath(std::int32_t fileId) const
{
    return fileMap->GetFilePath(fileId);
}

void Project::InitModules()
{
    if (initialized) return;
    initialized = true;
    MapFiles();
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
                    if (GetTarget() == Target::program)
                    {
                        index.imp(module->GetSymbolTable()->ClassIndex(), true);
                    }
                }
            }
        }
    }
}

void Project::SetModule(std::int32_t fileId, otava::symbols::Module* module)
{
    module->SetIndex(modules.size());
    modules.push_back(std::unique_ptr<otava::symbols::Module>(module));
    fileIdModuleMap[fileId] = module;
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

otava::symbols::Module* Project::GetModule(std::int32_t fileId) const
{
    auto it = fileIdModuleMap.find(fileId);
    if (it != fileIdModuleMap.end())
    {
        return it->second;
    }
    else
    {
        otava::ast::SetExceptionThrown();
        throw std::runtime_error("invalid file id");
    }
}

otava::symbols::Module* Project::ReleaseModule(std::int32_t fileId)
{
    otava::symbols::Module* module = GetModule(fileId);
    return modules[module->Index()].release();
}

void Project::MapFiles()
{
    root = util::Path::GetDirectoryName(filePath);
    std::int16_t fileIndex = 0;
    for (const auto& interfaceFileName : interfaceFilePaths)
    {
        std::string interfaceFilePath = util::GetFullPath(util::Path::Combine(root, interfaceFileName));
        std::int32_t interfaceFileId = MakeFileId(Id(), fileIndex++);
        fileMap->MapFile(interfaceFilePath, interfaceFileId);
        interfaceFiles.push_back(interfaceFileId);
    }
    for (const auto& sourceFileName : sourceFilePaths)
    {
        std::string sourceFilePath = util::GetFullPath(util::Path::Combine(root, sourceFileName));
        std::int32_t sourceFileId = MakeFileId(Id(), fileIndex++);
        fileMap->MapFile(sourceFilePath, sourceFileId);
        sourceFiles.push_back(sourceFileId);
    }
}

bool Project::UpToDate() const
{
    for (const auto& module : modules)
    {
        if (module)
        {
            const std::string& moduleSourceFilePath = GetModuleSourceFilePath(module->FileId());
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
