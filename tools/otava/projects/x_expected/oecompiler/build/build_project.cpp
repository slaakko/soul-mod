// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.build_project;

import otava.symbols.conversion.table;
import otava.ast.node;
import util;

namespace otava::build {

std::int32_t MakeFileId(std::int16_t projectId, std::int16_t fileIndex)
{
    return static_cast<std::int32_t>(projectId) << 16 | static_cast<std::int32_t>(fileIndex);
}

Define::Define(const std::string& symbol_, std::int64_t value_) : symbol(symbol_), value(value_)
{
}

bool ProjectLess::operator()(Project* left, Project* right) const
{
    if (left->Id() < right->Id()) return true;
    if (left->Id() > right->Id()) return false;
    return left->Name() < right->Name();
}

std::expected<bool, int> LoadImportedModules(Project* project, otava::symbols::Module* module, otava::symbols::Module* importedModule, 
    otava::symbols::ModuleMapper& moduleMapper, const std::string& config, int optLevel)
{
    for (const std::string& importedModuleName : importedModule->ImportModuleNames())
    {
        otava::symbols::Module* projectModule = project->GetModule(importedModuleName);
        if (projectModule)
        {
            module->AddImportedModule(projectModule);
            module->AddDependsOnModule(projectModule);
            auto rv = LoadImportedModules(project, module, projectModule, moduleMapper, config, optLevel);
            if (!rv) return rv;
        }
        else
        {
            auto m = moduleMapper.GetModule(importedModuleName, config, optLevel);
            if (!m) return std::unexpected<int>(m.error());
            otava::symbols::Module* childModule = *m;
            module->AddImportedModule(childModule);
            module->AddDependsOnModule(childModule);
            auto rv = module->Import(childModule, moduleMapper, config, optLevel);
            if (!rv) return rv;
            rv = LoadImportedModules(project, module, childModule, moduleMapper, config, optLevel);
            if (!rv) return rv;
        }
    }
    return std::expected<bool, int>(true);
}

Project::Project(const std::string& filePath_, const std::string& name_) :
    fileMap(nullptr), filePath(filePath_), name(name_), initialized(false), scanned(false), loaded(false), target(Target::program)
{
    root = util::Path::GetDirectoryName(filePath);
}

Project::~Project()
{
    for (Project* referencedProject : referencedProjects)
    {
        delete referencedProject;
    }
}

std::int16_t Project::Id() const
{
    return static_cast<std::int16_t>(std::hash<std::string>()(name) & 0x7FFF);
}

void Project::AddDefine(const std::string& symbol, std::int64_t value)
{
    defines.push_back(Define(symbol, value));
}

std::expected<bool, int> Project::AddRoots(otava::symbols::ModuleMapper& moduleMapper)
{
    for (const auto& referenceFilePath : referenceFilePaths)
    {
        auto p = util::GetFullPath(util::Path::Combine(root, util::Path::GetDirectoryName(referenceFilePath)));
        if (!p) return std::unexpected<int>(p.error());
        std::string referenceRoot = *p;
        moduleMapper.AddRoot(referenceRoot);
    }
    return std::expected<bool, int>(true);
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

std::expected<bool, int> Project::InitModules()
{
    if (initialized) return std::expected<bool, int>(true);
    initialized = true;
    return MapFiles();
}

std::expected<bool, int> Project::LoadModules(otava::symbols::ModuleMapper& moduleMapper, const std::string& config, int optLevel)
{
    if (loaded) return std::expected<bool, int>(true);
    loaded = true;
#ifdef DEBUG_SYMBOL_IO
    std::cout << ">project '" << Name() << "' loading modules" << "\n";
#endif
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
#ifdef DEBUG_SYMBOL_IO
        std::cout << ">" << module->Name() << "\n";
#endif
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
                return std::unexpected<int>(util::AllocateError("exported module '" + exportedModuleName + "' not found"));
            }
        }
        for (const auto& importedModuleName : module->ImportModuleNames())
        {
            otava::symbols::Module* importedModule = GetModule(importedModuleName);
            bool loaded = false;
            if (!importedModule)
            {
                auto m = moduleMapper.GetModule(importedModuleName, config, optLevel);
                if (!m) return std::unexpected<int>(m.error());
                importedModule = *m;
                loaded = true;
            }
            module->AddImportedModule(importedModule);
            module->AddDependsOnModule(importedModule);
            auto rv = LoadImportedModules(this, module.get(), importedModule, moduleMapper, config, optLevel);
            if (!rv) return rv;
            if (loaded)
            {
                for (otava::symbols::Module* exportedModule : importedModule->ExportedModules())
                {
                    auto rv = module->Import(exportedModule, moduleMapper, config, optLevel);
                    if (!rv) return rv;
                }
            }
        }
#ifdef DEBUG_SYMBOL_IO
        std::cout << "<" << module->Name() << "\n";
#endif
    }
#ifdef DEBUG_SYMBOL_IO
    std::cout << "<project '" << Name() << "' modules loaded" << "\n";
#endif
    return std::expected<bool, int>(true);
}

void Project::SetModule(std::int32_t fileId, otava::symbols::Module* module)
{
    module->SetIndex(static_cast<int>(modules.size()));
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

std::expected<otava::symbols::Module*, int> Project::GetModule(std::int32_t fileId) const
{
    auto it = fileIdModuleMap.find(fileId);
    if (it != fileIdModuleMap.end())
    {
        return it->second;
    }
    else
    {
        return std::unexpected<int>(util::AllocateError("invalid module file id"));
    }
}

std::expected<otava::symbols::Module*, int> Project::ReleaseModule(std::int32_t fileId)
{
    std::expected<otava::symbols::Module*, int> m = GetModule(fileId);
    if (!m) return m;
    otava::symbols::Module* module = *m;
    return std::expected<otava::symbols::Module*, int>(modules[module->Index()].release());
}

std::expected<bool, int> Project::MapFiles()
{
    root = util::Path::GetDirectoryName(filePath);
    std::int16_t fileIndex = 0;
    for (const auto& interfaceFileName : interfaceFilePaths)
    {
        auto p = util::GetFullPath(util::Path::Combine(root, interfaceFileName));
        if (!p) return std::unexpected<int>(p.error());
        std::string interfaceFilePath = std::move(*p);
        std::int32_t interfaceFileId = MakeFileId(Id(), fileIndex++);
        fileMap->MapFile(interfaceFilePath, interfaceFileId);
        interfaceFiles.push_back(interfaceFileId);
    }
    for (const auto& sourceFileName : sourceFilePaths)
    {
        auto p = util::GetFullPath(util::Path::Combine(root, sourceFileName));
        if (!p) return std::unexpected<int>(p.error());
        std::string sourceFilePath = std::move(*p);
        std::int32_t sourceFileId = MakeFileId(Id(), fileIndex++);
        fileMap->MapFile(sourceFilePath, sourceFileId);
        sourceFiles.push_back(sourceFileId);
    }
    return std::expected<bool, int>(true);
}

bool Project::UpToDate(const std::string& config, int optLevel, int error) const
{
    error = 0;
    if (!ort_path_exists(outputFilePath.c_str()))
    {
        return false;
    }
    for (Project* reference : referencedProjects)
    {
        std::string p = outputFilePath;
        std::string r = reference->OutputFilePath();
        if (!ort_path_exists(r.c_str()) || ort_last_write_time(p.c_str()) < ort_last_write_time(r.c_str()))
        {
            return false;
        }
    }
    for (const auto& module : modules)
    {
        if (module)
        {
            const std::string& moduleSourceFilePath = module->FilePath();
            if (module->Kind() == otava::symbols::ModuleKind::interfaceModule)
            {
                std::expected<std::string, int> p = otava::symbols::MakeModuleFilePath(root, config, optLevel, module->Name());
                if (!p)
                {
                    error = p.error();
                    return false;
                }
                std::string moduleFilePath = *p;
                if (!ort_path_exists(moduleFilePath.c_str()) || ort_last_write_time(moduleFilePath.c_str()) < ort_last_write_time(moduleSourceFilePath.c_str()))
                {
                    return false;
                }
                if (ort_last_write_time(outputFilePath.c_str()) < ort_last_write_time(moduleSourceFilePath.c_str()))
                {
                    return false;
                }
            }
        }
    }
    for (const auto& sourceFileName : sourceFilePaths)
    {
        std::string sourceFilePath = util::Path::Combine(util::Path::GetDirectoryName(FilePath()), sourceFileName);
        if (!ort_path_exists(sourceFilePath.c_str()) ||
            ort_last_write_time(outputFilePath.c_str()) < ort_last_write_time(sourceFilePath.c_str()))
        {
            return false;
        }
    }
    return true;
}

void Project::AddReferenceFilePath(const std::string& referenceFilePath)
{
    referenceFilePaths.push_back(referenceFilePath);
}

void Project::AddReferencedProject(Project* referencedProject)
{
    referencedProjects.push_back(referencedProject);
}

std::expected<bool, int> Project::ResolveForwardDeclarationsAndAddDerivedClasses(otava::symbols::ModuleMapper& moduleMapper, const std::string& config, int optLevel)
{
    otava::symbols::Module projectModule(Name() + ".#project");
    for (const auto& moduleName : moduleNames)
    {
        std::expected<otava::symbols::Module*, int> m = moduleMapper.GetModule(moduleName, config, optLevel);
        if (!m) return std::unexpected<int>(m.error());
        otava::symbols::Module* module = *m;
        auto rv = projectModule.Import(module, moduleMapper, config, optLevel);
        if (!rv) return rv;
    }
    auto rv = projectModule.ResolveForwardDeclarations();
    if (!rv) return rv;
    projectModule.AddDerivedClasses();
    return std::expected<bool, int>(true);
}


std::expected<bool, int> Project::ReadTraceInfo(const std::string& moduleDir)
{
    std::expected<std::string, int> srv = util::GetFullPath(util::Path::Combine(moduleDir, "trace.info"));
    if (!srv) return std::unexpected<int>(srv.error());
    std::string traceInfoFilePath = *srv;
    util::FileStream file(traceInfoFilePath, util::OpenMode::read | util::OpenMode::binary);
    if (!file) return std::unexpected<int>(util::AllocateError("could not open file '" + traceInfoFilePath + "'"));
    util::BufferedStream bufStream(file);
    util::BinaryStreamReader reader(bufStream);
    std::expected<bool, int> rv = traceInfo.Read(reader);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> Project::WriteTraceInfo(const std::string& moduleDir)
{
    std::expected<std::string, int> srv = util::GetFullPath(util::Path::Combine(moduleDir, "trace.info"));
    if (!srv) return std::unexpected<int>(srv.error());
    std::string traceInfoFilePath = *srv;
    util::FileStream file(traceInfoFilePath, util::OpenMode::write | util::OpenMode::binary);
    if (!file) return std::unexpected<int>(util::AllocateError("could not create file '" + traceInfoFilePath + "'"));
    util::BufferedStream bufStream(file);
    util::BinaryStreamWriter writer(bufStream);
    std::expected<bool, int> rv = traceInfo.Write(writer);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> Project::ReadClassIndex(const std::string& moduleDir)
{
    std::expected<std::string, int> srv = util::GetFullPath(util::Path::Combine(moduleDir, "class.index"));
    if (!srv) return std::unexpected<int>(srv.error());
    std::string classIndexFilePath = *srv;
    util::FileStream file(classIndexFilePath, util::OpenMode::read | util::OpenMode::binary);
    if (!file) return std::unexpected<int>(util::AllocateError("could not open file '" + classIndexFilePath + "'"));
    util::BufferedStream bufStream(file);
    util::BinaryStreamReader reader(bufStream);
    std::expected<bool, int> rv = index.read(reader);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> Project::WriteClassIndex(const std::string& moduleDir)
{
    std::expected<std::string, int> srv = util::GetFullPath(util::Path::Combine(moduleDir, "class.index"));
    if (!srv) return std::unexpected<int>(srv.error());
    std::string classIndexFilePath = *srv;
    util::FileStream file(classIndexFilePath, util::OpenMode::write | util::OpenMode::binary);
    if (!file) return std::unexpected<int>(util::AllocateError("could not create file '" + classIndexFilePath + "'"));
    util::BufferedStream bufStream(file);
    util::BinaryStreamWriter writer(bufStream);
    std::expected<bool, int> rv = index.write(writer);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

} // namespace otava::build
