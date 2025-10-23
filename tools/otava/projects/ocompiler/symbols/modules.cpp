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
import otava.symbols.function.kind;
import otava.symbols.function.symbol;

namespace otava::symbols {

std::expected<std::string, int> MakeModuleFilePath(const std::string& root, const std::string& config, int optLevel, const std::string& moduleName)
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

std::expected<std::string, int> MakeProjectFilePath(const std::string& root, const std::string& moduleName)
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

std::expected<bool, int> Module::Import(ModuleMapper& moduleMapper, const std::string& config, int optLevel)
{
    for (const auto& exportedModuleName : exportModuleNames)
    {
        std::expected<Module*, int> mrv = moduleMapper.GetModule(exportedModuleName, config, optLevel);
        if (!mrv) return std::unexpected<int>(mrv.error());
        Module* exportedModule = *mrv;
        AddExportedModule(exportedModule);
        AddDependsOnModule(exportedModule);
    }
    for (const auto& importedModuleName : importModuleNames)
    {
        std::expected<Module*, int> mrv = moduleMapper.GetModule(importedModuleName, config, optLevel);
        if (!mrv) return std::unexpected<int>(mrv.error());
        Module* importedModule = *mrv;
        AddImportedModule(importedModule);
        AddDependsOnModule(importedModule);
    }
    for (Module* dependsOnModule : dependsOnModules)
    {
        std::expected<bool, int> rv = Import(dependsOnModule, moduleMapper, config, optLevel);
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> Module::Import(Module* that, ModuleMapper& moduleMapper, const std::string& config, int optLevel)
{
    if (importSet.find(that) == importSet.cend())
    {
        importSet.insert(that);
        std::expected<bool, int>  rv = that->Import(moduleMapper, config, optLevel);
        if (!rv) return rv;
        rv = symbolTable.Import(that->symbolTable, moduleMapper.GetFunctionDefinitionSymbolSet());
        if (!rv) return rv;
        evaluationContext.Init();
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> Module::ResolveForwardDeclarations()
{
    for (Symbol* fwdSymbol : symbolTable.ForwardDeclarations())
    {
        if (fwdSymbol->IsForwardClassDeclarationSymbol())
        {
            ForwardClassDeclarationSymbol* fwd = static_cast<ForwardClassDeclarationSymbol*>(fwdSymbol);
            if (fwd->GetClassTypeSymbol() == nullptr)
            {
                std::expected<Symbol*, int> rv = symbolTable.LookupSymbol(fwd);
                if (!rv) return std::unexpected<int>(rv.error());
                Symbol* group = *rv;
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
                std::expected<Symbol*, int> rv = symbolTable.LookupSymbol(fwd);
                if (!rv) return std::unexpected<int>(rv.error());
                Symbol* group = *rv;
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
    return std::expected<bool, int>(true);
}

std::expected<bool, int> Module::ResolveAllForwardDeclarations()
{
    for (Symbol* fwdSymbol : symbolTable.AllForwardDeclarations())
    {
        if (fwdSymbol->IsForwardClassDeclarationSymbol())
        {
            ForwardClassDeclarationSymbol* fwd = static_cast<ForwardClassDeclarationSymbol*>(fwdSymbol);
            if (fwd->GetClassTypeSymbol() == nullptr)
            {
                std::expected<Symbol*, int> rv = symbolTable.LookupSymbol(fwd);
                if (!rv) return std::unexpected<int>(rv.error());
                Symbol* group = *rv;
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
                std::expected<Symbol*, int> rv = symbolTable.LookupSymbol(fwd);
                if (!rv) return std::unexpected<int>(rv.error());
                Symbol* group = *rv;
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
    return std::expected<bool, int>(true);
}

void Module::AddDerivedClasses()
{
    for (ClassTypeSymbol* cls : symbolTable.Classes())
    {
        for (ClassTypeSymbol* baseClass : cls->BaseClasses())
        {
            baseClass->AddDerivedClass(cls);
        }
    }
}

std::expected<bool, int> Module::Write(const std::string& root, const std::string& config, int optLevel, Context* context)
{
    std::expected<std::string, int> rv = MakeModuleFilePath(root, config, optLevel, name);
    if (!rv) return std::unexpected<int>(rv.error());
    std::string moduleFilePath = std::move(*rv);
    Writer writer(moduleFilePath);
    writer.SetContext(context);
    return Write(writer, context);
}

void Module::Init()
{
    symbolTable.Init();
}

void Module::SetFile(otava::ast::File* astFile_)
{
    astFile.reset(astFile_);
}

std::expected<bool, int> Module::LoadImplementationUnits(ModuleMapper& moduleMapper, const std::string& config, int optLevel)
{
    for (const auto& implementationUnitName : implementationUnitNames)
    {
        std::expected<Module*, int> mrv = moduleMapper.GetModule(implementationUnitName, config, optLevel);
        if (!mrv) return std::unexpected<int>(mrv.error());
        Module* implementationUnit = *mrv;
        AddImplementationUnit(implementationUnit);
    }
    return std::expected<bool, int>(true);
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

std::expected<bool, int> Module::Write(Writer& writer, Context* context)
{
    std::expected<bool, int> rv = writer.GetBinaryStreamWriter().Write(static_cast<std::uint8_t>(kind));
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(name);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(filePath);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(projectId);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(importIndex);
    if (!rv) return rv;
    std::uint32_t expCount = exportModuleNames.size();
    rv = writer.GetBinaryStreamWriter().WriteULEB128UInt(expCount);
    if (!rv) return rv;
    for (const auto& exportedModuleName : exportModuleNames)
    {
        rv = writer.GetBinaryStreamWriter().Write(exportedModuleName);
        if (!rv) return rv;
    }
    std::uint32_t impCount = importModuleNames.size();
    rv = writer.GetBinaryStreamWriter().WriteULEB128UInt(impCount);
    if (!rv) return rv;
    for (const auto& importedModuleName : importModuleNames)
    {
        rv = writer.GetBinaryStreamWriter().Write(importedModuleName);
        if (!rv) return rv;
    }
    std::uint32_t implementationUnitNameCount = implementationUnitNames.size();
    rv = writer.GetBinaryStreamWriter().WriteULEB128UInt(implementationUnitNameCount);
    if (!rv) return rv;
    for (const auto& implementationUnitName : implementationUnitNames)
    {
        rv = writer.GetBinaryStreamWriter().Write(implementationUnitName);
        if (!rv) return rv;
    }
    rv = symbolTable.Write(writer, context);
    if (!rv) return rv;
    rv = evaluationContext.Write(writer, context);
    if (!rv) return rv;
    otava::ast::Writer astWriter(&writer.GetBinaryStreamWriter());
    rv = astFile->Write(astWriter);
    if (!rv) return rv;
    rv = symbolTable.WriteMaps(writer, context);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> Module::ReadHeader(Reader& reader, ModuleMapper& moduleMapper)
{
    if (reading)
    {
        return std::unexpected<int>(util::AllocateError("circular module interface unit dependency for module '" + name + "' detected"));
    }
    reading = true;
    std::expected<std::uint8_t, int> brv = reader.GetBinaryStreamReader().ReadByte();
    if (!brv) return std::unexpected<int>(brv.error());
    std::uint8_t b = *brv;
    kind = static_cast<ModuleKind>(b);
    std::expected<std::string, int> srv = reader.GetBinaryStreamReader().ReadUtf8String();
    if (!srv) return std::unexpected<int>(srv.error());
    name = *srv;
    srv = reader.GetBinaryStreamReader().ReadUtf8String();
    if (!srv) return std::unexpected<int>(srv.error());
    filePath = *srv;
    std::expected<bool, int> rv = reader.GetBinaryStreamReader().ReadUuid(projectId);
    if (!rv) return rv;
    std::expected<std::int32_t, int> irv = reader.GetBinaryStreamReader().ReadInt();
    if (!irv) return std::unexpected<int>(irv.error());
    importIndex = *irv;
    std::expected<std::uint32_t, int> urv = reader.GetBinaryStreamReader().ReadULEB128UInt();
    if (!urv) return std::unexpected<int>(urv.error());
    std::uint32_t expCount = *urv;
    for (std::int32_t i = 0; i < static_cast<std::int32_t>(expCount); ++i)
    {
        srv = reader.GetBinaryStreamReader().ReadUtf8String();
        if (!srv) return std::unexpected<int>(srv.error());
        AddExportModuleName(*srv);
    }
    urv = reader.GetBinaryStreamReader().ReadULEB128UInt();
    if (!urv) return std::unexpected<int>(urv.error());
    std::uint32_t impCount = *urv;
    for (std::int32_t i = 0; i < static_cast<std::int32_t>(impCount); ++i)
    {
        srv = reader.GetBinaryStreamReader().ReadUtf8String();
        if (!srv) return std::unexpected<int>(srv.error());
        AddImportModuleName(*srv);
    }
    urv = reader.GetBinaryStreamReader().ReadULEB128UInt();
    if (!urv) return std::unexpected<int>(urv.error());
    std::uint32_t implementationUnitNameCount = *urv;
    for (std::int32_t i = 0; i < static_cast<std::int32_t>(implementationUnitNameCount); ++i)
    {
        srv = reader.GetBinaryStreamReader().ReadUtf8String();
        if (!srv) return std::unexpected<int>(srv.error());
        implementationUnitNames.push_back(*srv);
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> Module::CompleteRead(Reader& reader, ModuleMapper& moduleMapper, const std::string& config, int optLevel)
{
    reader.SetSymbolTable(&symbolTable);
    symbolTable.SetSymbolMap(moduleMapper.GetSymbolMap());
    reader.SetFunctionDefinitionSymbolSet(moduleMapper.GetFunctionDefinitionSymbolSet());
    symbolTable.SetNodeMap(moduleMapper.GetNodeMap());
#ifdef DEBUG_WRITE_MAPS
    std::cout << ">module '" << Name() << "' read symbol table" << "\n";
#endif
    std::expected<bool, int> rv = symbolTable.Read(reader);
    if (!rv) return rv;
#ifdef DEBUG_WRITE_MAPS
    std::cout << "<module '" << Name() << "' read symbol table" << "\n";
#endif
    #ifdef DEBUG_WRITE_MAPS
    std::cout << ">module '" << Name() << "' read evaluation context" << "\n";
#endif
    rv = evaluationContext.Read(reader);
    if (!rv) return rv;
#ifdef DEBUG_WRITE_MAPS
    std::cout << "<module '" << Name() << "' read evaluation context" << "\n";
#endif
    otava::ast::Reader astReader(&reader.GetBinaryStreamReader());
    astReader.SetNodeMap(moduleMapper.GetNodeMap());
    astFile.reset(new otava::ast::File());
    rv = astFile->Read(astReader);
    /*
if (!rv) return rv;
#ifdef DEBUG_WRITE_MAPS
    std::cout << ">module '" << Name() << "' import" << "\n";
#endif
    rv = Import(moduleMapper, config, optLevel);
    if (!rv) return rv;
#ifdef DEBUG_WRITE_MAPS
    std::cout << "<module '" << Name() << "' import" << "\n";
#endif
#ifdef DEBUG_WRITE_MAPS
    std::cout << ">module '" << Name() << "' read maps" << "\n";
#endif
    rv = symbolTable.ReadMaps(reader, moduleMapper.GetNodeMap());
    if (!rv) return rv;
#ifdef DEBUG_WRITE_MAPS
    std::cout << "<module '" << Name() << "' read maps" << "\n";
#endif
#ifdef DEBUG_WRITE_MAPS
    std::cout << ">module '" << Name() << "' resolve symbols" << "\n";
#endif
    rv = symbolTable.Resolve(reader.GetContext());
    if (!rv) return rv;
#ifdef DEBUG_WRITE_MAPS
    std::cout << "<module '" << Name() << "' resolve symbols" << "\n";
#endif
#ifdef DEBUG_WRITE_MAPS
    std::cout << ">module '" << Name() << "' resolve evaluation context" << "\n";
#endif
    rv = evaluationContext.Resolve(symbolTable, reader.GetContext());
    if (!rv) return rv;
#ifdef DEBUG_WRITE_MAPS
    std::cout << "<module '" << Name() << "' resolve evaluation context" << "\n";
#endif
#ifdef DEBUG_WRITE_MAPS
    std::cout << ">module '" << Name() << "' import after resolve" << "\n";
#endif
    rv = symbolTable.ImportAfterResolve();
    if (!rv) return rv;
#ifdef DEBUG_WRITE_MAPS
    std::cout << "<module '" << Name() << "' import after resolve" << "\n";
#endif
*/
    reading = false;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> Module::ToXml(const std::string& xmlFilePath) const
{
    return symbolTable.ToXml(xmlFilePath);
}

ModuleMapper::ModuleMapper() : error(0)
{
    std::expected<std::string, int> rv = util::SoulRoot();
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    rv = util::GetFullPath(util::Path::Combine(util::Path::Combine(util::Path::Combine(*rv, "tools"), "otava"), "std"));
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    roots.push_back(*rv);
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

std::expected<std::string, int> ModuleMapper::GetProjectFilePath(const std::string& moduleName) const
{
    for (const auto& root : roots)
    {
        std::expected<std::string, int> rv = MakeProjectFilePath(root, moduleName);
        if (!rv) return rv;
        std::string projectFilePath = *rv;
        if (std::filesystem::exists(projectFilePath))
        {
            return std::expected<std::string, int>(projectFilePath);
        }
    }
    return std::expected<std::string, int>(std::string());
}

std::expected<std::string, int> ModuleMapper::GetModuleFilePath(const std::string& moduleName, const std::string& config, int optLevel) const
{
    for (const auto& root : roots)
    {
        std::expected<std::string, int> rv = MakeModuleFilePath(root, config, optLevel, moduleName);
        if (!rv) return rv;
        std::string  moduleFilePath = *rv;
        if (std::filesystem::exists(moduleFilePath))
        {
            return std::expected<std::string, int>(moduleFilePath);
        }
    }
    return std::expected<std::string, int>(std::string());
}

std::expected<Module*, int> ModuleMapper::GetModule(const std::string& moduleName, const std::string& config, int optLevel)
{
#ifdef DEBUG_WRITE_MAPS
    std::cout << ">module mapper get module '" << moduleName << "'" << "\n";
#endif
    std::lock_guard<std::recursive_mutex> lock(mtx);
    auto it = moduleMap.find(moduleName);
    if (it != moduleMap.cend())
    {
        return std::expected<Module*, int>(it->second);
    }
    else
    {
        for (const auto& root : roots)
        {
            std::expected<std::string, int> rv = MakeModuleFilePath(root, config, optLevel, moduleName);
            if (!rv) return std::unexpected<int>(rv.error());
            std::string moduleFilePath = *rv;
            if (std::filesystem::exists(moduleFilePath))
            {
                return LoadModule(moduleName, moduleFilePath, config, optLevel);
            }
        }
        return std::unexpected<int>(util::AllocateError("module '" + moduleName + "' not found"));
    }
    return std::expected<Module*, int>(nullptr);
}

std::expected<Module*, int> ModuleMapper::LoadModule(const std::string& moduleName, const std::string& moduleFilePath, const std::string& config, int optLevel)
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
    std::expected<bool, int> rv = module->ReadHeader(reader, *this);
    if (!rv) return std::unexpected<int>(rv.error());
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
        std::expected<Module*, int> mrv = GetModule(importedModuleName, config, optLevel);
        if (!mrv) return mrv;
        Module* importedModule = *mrv;
        module->AddImportedModule(importedModule);
#ifdef DEBUG_WRITE_MAPS
        std::cout << "<module mapper import '" << moduleName << "' <- '" << importedModuleName << "'" << "\n";
#endif
    }
    SetCurrentModule(module.get());
#ifdef DEBUG_WRITE_MAPS
    std::cout << ">module mapper complete read '" << moduleName << "'" << "\n";
#endif
    rv = module->CompleteRead(reader, *this, config, optLevel);
    if (!rv) return std::unexpected<int>(rv.error());
#ifdef DEBUG_WRITE_MAPS
    std::cout << "<module mapper complete read '" << moduleName << "'" << "\n";
#endif
    modules.push_back(std::move(module));
#ifdef DEBUG_WRITE_MAPS
    std::cout << ">module mapper load module '" << moduleName << "'" << "\n";
#endif
    return std::expected<Module*, int>(modulePtr);
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
