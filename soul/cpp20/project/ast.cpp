// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.proj.ast;

namespace soul::cpp20::proj::ast {

Project::Project(const std::string& filePath_, const std::string& name_) : filePath(filePath_), name(name_)
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

void Project::AddDependencies(soul::cpp20::symbols::ModuleMapper& moduleMapper)
{
    for (const auto& module : modules)
    {
        moduleMap[module->Name()] = module.get();
    }
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

} // namespace soul::cpp20::proj::ast
