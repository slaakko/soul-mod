// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.symbols.modules;

import util;
import soul.cpp20.symbols.namespaces;
import soul.cpp20.symbols.reader;
import soul.cpp20.symbols.writer;

namespace soul::cpp20::symbols {

std::string StdModuleFilePath(const std::string& moduleName)
{
    std::string moduleFilePath = util::GetFullPath(util::Path::Combine(util::SoulRoot(), "soul/cpp20/std/" + moduleName +".module"));
    return moduleFilePath;
}

Module::Module(const std::string& name_) : name(name_), symbolTable(), file(-1)
{
    symbolTable.SetModule(this);
    Init();
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
    symbolTable.Write(writer);
}

void Module::Read(Reader& reader)
{
    name = reader.GetBinaryStreamReader().ReadUtf8String();
    symbolTable.Read(reader);
}

} // namespace soul::cpp20::symbols
