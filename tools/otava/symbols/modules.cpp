// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.modules;

import util;
import std.filesystem;
import otava.symbols.namespaces;
import otava.symbols.classes;
import otava.symbols.class_group.symbol;
import otava.symbols.enums;
import otava.symbols.enum_group.symbol;
import otava.symbols.reader;
import otava.symbols.writer;
import otava.symbols.visitor;
import otava.symbols.conversion.table;
import otava.symbols.templates;
import otava.ast.reader;
import otava.ast.writer;
import otava.ast.error;

namespace otava::symbols {

std::string MakeModuleFilePath(const std::string& root, const std::string& moduleName)
{
    return util::GetFullPath(util::Path::Combine(root, moduleName + ".module"));
}

Module::Module(const std::string& name_) : name(name_), symbolTable(), evaluationContext(symbolTable), file(-1), reading(false)
{
    symbolTable.SetModule(this);
}

Module::~Module()
{
}

int32_t Module::Id() const
{
    return static_cast<int32_t>(std::hash<std::string>()(name) & 0x7FFFFFFF);
}

void Module::SetFilePath(const std::string& filePath_)
{
    filePath = filePath_;
}

void Module::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
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
    if (importSet.find(that) == importSet.cend())
    {
        importSet.insert(that);
        that->Import(moduleMapper);
        symbolTable.Import(that->symbolTable);
        evaluationContext.Init();
    }
}

void Module::ResolveForwardDeclarations()
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

void Module::SetFile(otava::ast::File* astFile_)
{
    astFile.reset(astFile_);
}

void Module::LoadImplementationUnits(ModuleMapper& moduleMapper)
{
    for (const auto& implementationUnitName : implementationUnitNames)
    {
        Module* implementationUnit = moduleMapper.GetModule(implementationUnitName);
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

void Module::Write(Writer& writer)
{
    writer.GetBinaryStreamWriter().Write(name);
    writer.GetBinaryStreamWriter().Write(filePath);
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
    uint32_t implementationUnitNameCount = implementationUnitNames.size();
    writer.GetBinaryStreamWriter().WriteULEB128UInt(implementationUnitNameCount);
    for (const auto& implementationUnitName : implementationUnitNames)
    {
        writer.GetBinaryStreamWriter().Write(implementationUnitName);
    }
    symbolTable.Write(writer);
    evaluationContext.Write(writer);
    otava::ast::Writer astWriter(&writer.GetBinaryStreamWriter());
    astFile->Write(astWriter);
    symbolTable.WriteMaps(writer);
}

void Module::ReadHeader(Reader& reader, ModuleMapper& moduleMapper)
{
    if (reading)
    {
        otava::ast::SetExceptionThrown();
        throw std::runtime_error("circular module interface unit dependency for module '" + name + "' detected");
    }
    reading = true;
    name = reader.GetBinaryStreamReader().ReadUtf8String();
    filePath = reader.GetBinaryStreamReader().ReadUtf8String();
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
    uint32_t implementationUnitNameCount = reader.GetBinaryStreamReader().ReadULEB128UInt();
    for (uint32_t i = 0; i < implementationUnitNameCount; ++i)
    {
        implementationUnitNames.push_back(reader.GetBinaryStreamReader().ReadUtf8String());
    }
}

void Module::CompleteRead(Reader& reader, ModuleMapper& moduleMapper)
{
    reader.SetSymbolTable(&symbolTable);
    reader.SetSymbolMap(moduleMapper.GetSymbolMap());
    symbolTable.SetNodeMap(moduleMapper.GetNodeMap());
    symbolTable.SetSymbolMap(moduleMapper.GetSymbolMap());
    symbolTable.Read(reader);
    evaluationContext.Read(reader);
    otava::ast::Reader astReader(&reader.GetBinaryStreamReader());
    astReader.SetNodeMap(moduleMapper.GetNodeMap());
    astFile.reset(new otava::ast::File());
    astFile->Read(astReader);
    symbolTable.ReadMaps(reader, moduleMapper.GetNodeMap(), moduleMapper.GetSymbolMap());
    Import(moduleMapper);
    symbolTable.Resolve();
    evaluationContext.Resolve(symbolTable);
    reading = false;
}

bool ModuleNameLess::operator()(Module* left, Module* right) const
{
    return left->Name() < right->Name();
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

Module* ModuleMapper::GetModule(const std::string& moduleName)
{
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
            std::string moduleFilePath = MakeModuleFilePath(root, moduleName);
            if (std::filesystem::exists(moduleFilePath))
            {
                return LoadModule(moduleName, moduleFilePath);
            }
        }
        otava::ast::SetExceptionThrown();
        throw std::runtime_error("module '" + moduleName + "' not found");
    }
}

Module* ModuleMapper::LoadModule(const std::string& moduleName, const std::string& moduleFilePath)
{
    Reader reader(moduleFilePath);
    std::unique_ptr<Module> module(new Module(moduleName));
    module->SetFilePath(moduleFilePath);
    module->ReadHeader(reader, *this);
    Module* modulePtr = module.get();
    moduleMap[moduleName] = modulePtr;
    for (const std::string& importedModuleName : module->ImportModuleNames())
    {
        Module* importedModule = GetModule(importedModuleName);
        module->AddImportedModule(importedModule);
    }
    SetCurrentModule(module.get());
    module->CompleteRead(reader, *this);
    modules.push_back(std::move(module));
    return modulePtr;
}

#ifdef _WIN32

__declspec(thread) Module* currentModule = nullptr;

#else

__thread Module* currentModule = nullptr;

#endif 

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
    Module* module = GetCurrentModule();
    if (module)
    {
        module->GetSymbolTable()->RemoveNode(node);
    }
}

} // namespace otava::symbols
