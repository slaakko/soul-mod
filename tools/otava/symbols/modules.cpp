// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.modules;

import util;
import otava.symbols.namespaces;
import otava.symbols.classes;
import otava.symbols.class_group.symbol;
import otava.symbols.context;
import otava.symbols.enums;
import otava.symbols.enum_group.symbol;
import otava.symbols.reader;
import otava.symbols.writer;
import otava.symbols.visitor;
import otava.symbols.conversion.table;
import otava.symbols.templates;
import otava.symbols.function.symbol;
import otava.ast.reader;
import otava.ast.writer;
import otava.ast.error;

namespace otava::symbols {

std::string MakeModuleFilePath(const std::string& root, const std::string& config, int optLevel, const std::string& moduleName)
{
    if (config == "release")
    {
        return util::GetFullPath(util::Path::Combine(util::Path::Combine(util::Path::Combine(root, config), 
            std::to_string(otava::symbols::GetOptLevel(optLevel, true))), moduleName + ".module"));
    }
    else
    {
        return util::GetFullPath(util::Path::Combine(util::Path::Combine(root, config), moduleName + ".module"));
    }
}

std::string MakeProjectFilePath(const std::string& root, const std::string& moduleName)
{
    return util::GetFullPath(util::Path::Combine(root, moduleName + ".project"));
}

bool ModuleLess::operator()(Module* left, Module* right) const
{
    if (left->ImportIndex() < right->ImportIndex()) return true;
    if (left->ImportIndex() > right->ImportIndex()) return false;
    return left->Id() < right->Id();
}

util::uuid MakeProjectId(const std::string& projectName)
{
    std::uint64_t hashCode = std::hash<std::string>()(projectName);
    util::uuid projectId;
    util::IntsToUuid(hashCode, 0, projectId);
    return projectId;
}

Module::Module(const std::string& name_) : 
    kind(ModuleKind::interfaceModule), name(name_), symbolTable(), evaluationContext(symbolTable), fileId(-1), index(-1), importIndex(-1), reading(false)
{
    symbolTable.SetModule(this);
}

Module::~Module()
{
}

void Module::SetProjectId(const util::uuid& projectId_)
{
    projectId = projectId_;
}

std::int32_t Module::Id() const
{
    return static_cast<std::int32_t>(std::hash<std::string>()(name) & 0x7FFFFFFF);
}

void Module::SetFilePath(const std::string& filePath_)
{
    filePath = filePath_;
}

void Module::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void Module::Import(ModuleMapper& moduleMapper, const std::string& config, int optLevel)
{
    for (const auto& exportedModuleName : exportModuleNames)
    {
        Module* exportedModule = moduleMapper.GetModule(exportedModuleName, config, optLevel);
        AddExportedModule(exportedModule);
        AddDependsOnModule(exportedModule);
    }
    for (const auto& importedModuleName : importModuleNames)
    {
        Module* importedModule = moduleMapper.GetModule(importedModuleName, config, optLevel);
        AddImportedModule(importedModule);
        AddDependsOnModule(importedModule);
    }
    for (auto dependsOnModule : dependsOnModules)
    {
        Import(dependsOnModule, moduleMapper, config, optLevel);
    }
}

void Module::Import(Module* that, ModuleMapper& moduleMapper, const std::string& config, int optLevel)
{
    if (importSet.find(that) == importSet.cend())
    {
        importSet.insert(that);
        that->Import(moduleMapper, config, optLevel);
        symbolTable.Import(that->symbolTable, moduleMapper.GetFunctionDefinitionSymbolSet());
        evaluationContext.Init();
    }
}

void Module::ResolveForwardDeclarations()
{
    for (const auto& fwdSymbol : symbolTable.ForwardDeclarations())
    {
        if (fwdSymbol->IsForwardClassDeclarationSymbol())
        {
            ForwardClassDeclarationSymbol* fwd = static_cast<ForwardClassDeclarationSymbol*>(fwdSymbol);
            if (fwd->GetClassTypeSymbol() == nullptr)
            {
                Symbol* group = symbolTable.LookupSymbol(fwd);
                if (group)
                {
                    if (group->IsClassGroupSymbol())
                    {
                        ClassGroupSymbol* classGroupSymbol = static_cast<ClassGroupSymbol*>(group);
                        ClassTypeSymbol* classTypeSymbol = classGroupSymbol->GetClass(fwd->Arity());
                        if (classTypeSymbol)
                        {
                            fwd->SetClassTypeSymbol(classTypeSymbol);
                        }
                    }
                }
            }
        }
        else if (fwdSymbol->IsForwardEnumDeclarationSymbol())
        {
            ForwardEnumDeclarationSymbol* fwd = static_cast<ForwardEnumDeclarationSymbol*>(fwdSymbol);
            if (fwd->GetEnumeratedTypeSymbol() == nullptr)
            {
                Symbol* group = symbolTable.LookupSymbol(fwd);
                if (group)
                {
                    if (group->IsEnumGroupSymbol())
                    {
                        EnumGroupSymbol* enumGroupSymbol = static_cast<EnumGroupSymbol*>(group);
                        EnumeratedTypeSymbol* enumTypeSymbol = enumGroupSymbol->GetEnumType();
                        if (enumTypeSymbol)
                        {
                            fwd->SetEnumeratedTypeSymbol(enumTypeSymbol);
                        }
                    }
                }
            }
        }
    }
}

void Module::ResolveAllForwardDeclarations()
{
    for (const auto& fwdSymbol : symbolTable.AllForwardDeclarations())
    {
        if (fwdSymbol->IsForwardClassDeclarationSymbol())
        {
            ForwardClassDeclarationSymbol* fwd = static_cast<ForwardClassDeclarationSymbol*>(fwdSymbol);
            if (fwd->GetClassTypeSymbol() == nullptr)
            {
                Symbol* group = symbolTable.LookupSymbol(fwd);
                if (group)
                {
                    if (group->IsClassGroupSymbol())
                    {
                        ClassGroupSymbol* classGroupSymbol = static_cast<ClassGroupSymbol*>(group);
                        ClassTypeSymbol* classTypeSymbol = classGroupSymbol->GetClass(fwd->Arity());
                        if (classTypeSymbol)
                        {
                            fwd->SetClassTypeSymbol(classTypeSymbol);
                        }
                    }
                }
            }
        }
        else if (fwdSymbol->IsForwardEnumDeclarationSymbol())
        {
            ForwardEnumDeclarationSymbol* fwd = static_cast<ForwardEnumDeclarationSymbol*>(fwdSymbol);
            if (fwd->GetEnumeratedTypeSymbol() == nullptr)
            {
                Symbol* group = symbolTable.LookupSymbol(fwd);
                if (group)
                {
                    if (group->IsEnumGroupSymbol())
                    {
                        EnumGroupSymbol* enumGroupSymbol = static_cast<EnumGroupSymbol*>(group);
                        EnumeratedTypeSymbol* enumTypeSymbol = enumGroupSymbol->GetEnumType();
                        if (enumTypeSymbol)
                        {
                            fwd->SetEnumeratedTypeSymbol(enumTypeSymbol);
                        }
                    }
                }
            }
        }
    }
}

void Module::AddDerivedClasses()
{
    for (auto cls : symbolTable.Classes())
    {
        for (auto baseClass : cls->BaseClasses())
        {
            if (baseClass->IsClassTypeSymbol())
            {
                static_cast<ClassTypeSymbol*>(baseClass)->AddDerivedClass(cls);
            }
        }
    }
}

void Module::Write(const std::string& root, const std::string& config, int optLevel, Context* context)
{
    std::string moduleFilePath = MakeModuleFilePath(root, config, optLevel, name);
    Writer writer(moduleFilePath);
    writer.SetContext(context);
    Write(writer, context);
}

void Module::Init()
{
    symbolTable.Init();
}

void Module::SetFile(otava::ast::File* astFile_)
{
    astFile.reset(astFile_);
}

void Module::LoadImplementationUnits(ModuleMapper& moduleMapper, const std::string& config, int optLevel)
{
    for (const auto& implementationUnitName : implementationUnitNames)
    {
        Module* implementationUnit = moduleMapper.GetModule(implementationUnitName, config, optLevel);
        AddImplementationUnit(implementationUnit);
    }
}

void Module::AddImplementationUnit(Module* implementationUnit)
{
    implementationUnits.push_back(implementationUnit);
}

void Module::SetImplementationUnitNames(const std::vector<std::string>& names)
{
    implementationUnitNames = names;
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

void Module::Write(Writer& writer, Context* context)
{
    writer.GetBinaryStreamWriter().Write(static_cast<std::int8_t>(kind));
    writer.GetBinaryStreamWriter().Write(name);
    writer.GetBinaryStreamWriter().Write(filePath);
    writer.GetBinaryStreamWriter().Write(projectId);
    writer.GetBinaryStreamWriter().Write(importIndex);
    std::uint32_t expCount = exportModuleNames.size();
    writer.GetBinaryStreamWriter().WriteULEB128UInt(expCount);
    for (const auto& exportedModuleName : exportModuleNames)
    {
        writer.GetBinaryStreamWriter().Write(exportedModuleName);
    }
    std::uint32_t impCount = importModuleNames.size();
    writer.GetBinaryStreamWriter().WriteULEB128UInt(impCount);
    for (const auto& importedModuleName : importModuleNames)
    {
        writer.GetBinaryStreamWriter().Write(importedModuleName);
    }
    std::uint32_t implementationUnitNameCount = implementationUnitNames.size();
    writer.GetBinaryStreamWriter().WriteULEB128UInt(implementationUnitNameCount);
    for (const auto& implementationUnitName : implementationUnitNames)
    {
        writer.GetBinaryStreamWriter().Write(implementationUnitName);
    }
    symbolTable.Write(writer, context);
    evaluationContext.Write(writer, context);
    otava::ast::Writer astWriter(&writer.GetBinaryStreamWriter());
    astFile->Write(astWriter);
    symbolTable.WriteMaps(writer, context);
}

void Module::ReadHeader(Reader& reader, ModuleMapper& moduleMapper)
{
    if (reading)
    {
        otava::ast::SetExceptionThrown();
        throw std::runtime_error("circular module interface unit dependency for module '" + name + "' detected");
    }
    reading = true;
    kind = static_cast<ModuleKind>(reader.GetBinaryStreamReader().ReadSByte());
    name = reader.GetBinaryStreamReader().ReadUtf8String();
    filePath = reader.GetBinaryStreamReader().ReadUtf8String();
    reader.GetBinaryStreamReader().ReadUuid(projectId);
    importIndex = reader.GetBinaryStreamReader().ReadInt();
    std::uint32_t expCount = reader.GetBinaryStreamReader().ReadULEB128UInt();
    for (std::uint32_t i = 0; i < expCount; ++i)
    {
        AddExportModuleName(reader.GetBinaryStreamReader().ReadUtf8String());
    }
    std::uint32_t impCount = reader.GetBinaryStreamReader().ReadULEB128UInt();
    for (std::uint32_t i = 0; i < impCount; ++i)
    {
        AddImportModuleName(reader.GetBinaryStreamReader().ReadUtf8String());
    }
    std::uint32_t implementationUnitNameCount = reader.GetBinaryStreamReader().ReadULEB128UInt();
    for (std::uint32_t i = 0; i < implementationUnitNameCount; ++i)
    {
        implementationUnitNames.push_back(reader.GetBinaryStreamReader().ReadUtf8String());
    }
}

void Module::CompleteRead(Reader& reader, ModuleMapper& moduleMapper, const std::string& config, int optLevel)
{
    reader.SetSymbolTable(&symbolTable);
    reader.SetFunctionDefinitionSymbolSet(moduleMapper.GetFunctionDefinitionSymbolSet());
    symbolTable.SetNodeMap(moduleMapper.GetNodeMap());
#ifdef DEBUG_WRITE_MAPS
    std::cout << ">module '" << Name() << "' read symbol table" << "\n";
#endif
    symbolTable.Read(reader);
#ifdef DEBUG_WRITE_MAPS
    std::cout << "<module '" << Name() << "' read symbol table" << "\n";
#endif
#ifdef DEBUG_WRITE_MAPS
    std::cout << ">module '" << Name() << "' read evaluation context" << "\n";
#endif
    evaluationContext.Read(reader);
#ifdef DEBUG_WRITE_MAPS
    std::cout << "<module '" << Name() << "' read evaluation context" << "\n";
#endif
    otava::ast::Reader astReader(&reader.GetBinaryStreamReader());
    astReader.SetNodeMap(moduleMapper.GetNodeMap());
    astFile.reset(new otava::ast::File());
    astFile->Read(astReader);
#ifdef DEBUG_WRITE_MAPS
    std::cout << ">module '" << Name() << "' import" << "\n";
#endif
    Import(moduleMapper, config, optLevel);
#ifdef DEBUG_WRITE_MAPS
    std::cout << "<module '" << Name() << "' import" << "\n";
#endif
#ifdef DEBUG_WRITE_MAPS
    std::cout << ">module '" << Name() << "' read maps" << "\n";
#endif
    symbolTable.ReadMaps(reader, moduleMapper.GetNodeMap());
#ifdef DEBUG_WRITE_MAPS
    std::cout << "<module '" << Name() << "' read maps" << "\n";
#endif
#ifdef DEBUG_WRITE_MAPS
    std::cout << ">module '" << Name() << "' resolve symbols" << "\n";
#endif
    symbolTable.Resolve(reader.GetContext());
#ifdef DEBUG_WRITE_MAPS
    std::cout << "<module '" << Name() << "' resolve symbols" << "\n";
#endif
#ifdef DEBUG_WRITE_MAPS
    std::cout << ">module '" << Name() << "' resolve evaluation context" << "\n";
#endif
    evaluationContext.Resolve(symbolTable);
#ifdef DEBUG_WRITE_MAPS
    std::cout << "<module '" << Name() << "' resolve evaluation context" << "\n";
#endif
#ifdef DEBUG_WRITE_MAPS
    std::cout << ">module '" << Name() << "' import after resolve" << "\n";
#endif
    symbolTable.ImportAfterResolve();
#ifdef DEBUG_WRITE_MAPS
    std::cout << "<module '" << Name() << "' import after resolve" << "\n";
#endif
    reading = false;
}

void Module::ToXml(const std::string& xmlFilePath) const
{
    symbolTable.ToXml(xmlFilePath);
}

ModuleMapper::ModuleMapper() 
{
    roots.push_back(util::GetFullPath(util::Path::Combine(util::Path::Combine(util::Path::Combine(util::SoulRoot(), "tools"), "otava"), "std")));
}

void ModuleMapper::AddRoot(const std::string& root)
{
    if (std::find(roots.cbegin(), roots.cend(), root) == roots.cend())
    {
        roots.push_back(root);
    }
}

void ModuleMapper::AddModule(Module* module)
{
    std::lock_guard<std::recursive_mutex> lock(mtx);
    moduleMap[module->Name()] = module;
    modules.push_back(std::unique_ptr<Module>(module));
}

std::string ModuleMapper::GetProjectFilePath(const std::string& moduleName) const
{
    for (const auto& root : roots)
    {
        std::string projectFilePath = MakeProjectFilePath(root, moduleName);
        if (std::filesystem::exists(projectFilePath))
        {
            return projectFilePath;
        }
    }
    return std::string();
}

std::string ModuleMapper::GetModuleFilePath(const std::string& moduleName, const std::string& config, int optLevel) const
{
    for (const auto& root : roots)
    {
        std::string moduleFilePath = MakeModuleFilePath(root, config, optLevel, moduleName);
        if (std::filesystem::exists(moduleFilePath))
        {
            return moduleFilePath;
        }
    }
    return std::string();
}

Module* ModuleMapper::GetModule(const std::string& moduleName, const std::string& config, int optLevel)
{
#ifdef DEBUG_WRITE_MAPS
    std::cout << ">module mapper get module '" << moduleName << "'" << "\n";
#endif
    std::lock_guard<std::recursive_mutex> lock(mtx);
    auto it = moduleMap.find(moduleName);
    if (it != moduleMap.cend())
    {
        return it->second;
    }
    else
    {
        for (const auto& root : roots)
        {
            std::string moduleFilePath = MakeModuleFilePath(root, config, optLevel, moduleName);
            if (std::filesystem::exists(moduleFilePath))
            {
                return LoadModule(moduleName, moduleFilePath, config, optLevel);
            }
        }
        otava::ast::SetExceptionThrown();
        throw std::runtime_error("module '" + moduleName + "' not found");
    }
}

Module* ModuleMapper::LoadModule(const std::string& moduleName, const std::string& moduleFilePath, const std::string& config, int optLevel)
{
#ifdef DEBUG_WRITE_MAPS
    std::cout << ">module mapper load module '" << moduleName << "'" << "\n";
#endif
    Reader reader(moduleFilePath);
    std::unique_ptr<Module> module(new Module(moduleName));
    module->SetFilePath(moduleFilePath);
#ifdef DEBUG_WRITE_MAPS
    std::cout << ">module mapper read header '" << moduleName << "'" << "\n";
#endif
    module->ReadHeader(reader, *this);
#ifdef DEBUG_WRITE_MAPS
    std::cout << "<module mapper read header '" << moduleName << "'" << "\n";
#endif
    Module* modulePtr = module.get();
    moduleMap[moduleName] = modulePtr;
    for (const std::string& importedModuleName : module->ImportModuleNames())
    {
#ifdef DEBUG_WRITE_MAPS
        std::cout << ">module mapper import '" << moduleName << "' <- '" << importedModuleName << "'" << "\n";
#endif
        Module* importedModule = GetModule(importedModuleName, config, optLevel);
        module->AddImportedModule(importedModule);
#ifdef DEBUG_WRITE_MAPS
        std::cout << "<module mapper import '" << moduleName << "' <- '" << importedModuleName << "'" << "\n";
#endif
    }
    SetCurrentModule(module.get());
#ifdef DEBUG_WRITE_MAPS
    std::cout << ">module mapper complete read '" << moduleName << "'" << "\n";
#endif
    module->CompleteRead(reader, *this, config, optLevel);
#ifdef DEBUG_WRITE_MAPS
    std::cout << "<module mapper complete read '" << moduleName << "'" << "\n";
#endif
    modules.push_back(std::move(module));
#ifdef DEBUG_WRITE_MAPS
    std::cout << ">module mapper load module '" << moduleName << "'" << "\n";
#endif
    return modulePtr;
}

void ModuleMapper::SetFunctionDefinitionSymbolSet(FunctionDefinitionSymbolSet* functionDefinitionSymbolSet_)
{
    functionDefinitionSymbolSet = functionDefinitionSymbolSet_;
}

FunctionDefinitionSymbolSet* ModuleMapper::GetFunctionDefinitionSymbolSet() const
{
    return functionDefinitionSymbolSet;
}

int32_t ModuleMapper::ModuleCount() const
{
    return modules.size();
}

thread_local ModuleMapper* moduleMapper = nullptr;

ModuleMapper* GetModuleMapper()
{
    return moduleMapper;
}

void SetModuleMapper(ModuleMapper* moduleMapper_)
{
    moduleMapper = moduleMapper_;
}

thread_local Module* currentModule = nullptr;

Module* GetCurrentModule()
{
    return currentModule;
}

void SetCurrentModule(Module* module)
{
    currentModule = module;
}

void NodeDestroyed(otava::ast::Node* node)
{
    Module* m = GetCurrentModule();
    if (m)
    {
        m->GetSymbolTable()->RemoveNode(node);
    }
}

void SymbolDestroyed(Symbol* symbol)
{
    Module* m = GetCurrentModule();
    if (m)
    {
        m->GetSymbolTable()->RemoveSymbol(symbol);
    }
}

} // namespace otava::symbols
