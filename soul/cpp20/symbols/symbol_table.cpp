// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module;
#include <boost/uuid/uuid.hpp>

module soul.cpp20.symbols.symbol.table;

import util.unicode;
import util.uuid;
import soul.lexer;
import soul.cpp20.symbols.alias.type.symbol;
import soul.cpp20.symbols.alias.group.symbol;
import soul.cpp20.symbols.class_group.symbol;
import soul.cpp20.symbols.function.group.symbol;
import soul.cpp20.symbols.variable.group.symbol;
import soul.cpp20.symbols.block;
import soul.cpp20.symbols.classes;
import soul.cpp20.symbols.context;
import soul.cpp20.symbols.compound.type.symbol;
import soul.cpp20.symbols.enums;
import soul.cpp20.symbols.modules;
import soul.cpp20.symbols.namespaces;
import soul.cpp20.symbols.function.symbol;
import soul.cpp20.symbols.fundamental.type.symbol;
import soul.cpp20.symbols.templates;
import soul.cpp20.symbols.type.symbol;
import soul.cpp20.symbols.variable.symbol;
import soul.cpp20.symbols.reader;
import soul.cpp20.symbols.writer;
import soul.cpp20.symbols.exception;
import soul.cpp20.symbols.specialization;
import soul.cpp20.symbols.visitor;

namespace soul::cpp20::symbols {

SymbolTable::SymbolTable() : 
    module(nullptr), 
    globalNs(new NamespaceSymbol(std::u32string())), 
    currentScope(globalNs->GetScope()), 
    typenameConstraintSymbol(nullptr),
    errorTypeSymbol(nullptr),
    topScopeIndex(0)
{
    globalNs->SetSymbolTable(this);
}

void SymbolTable::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void SymbolTable::PushScope()
{
    scopeStack.push_back(currentScope);
}

void SymbolTable::PopScope()
{
    if (scopeStack.empty())
    {
        throw std::runtime_error("scope stack is empty");
    }
    currentScope = scopeStack.back();
    scopeStack.pop_back();
}

void SymbolTable::BeginScope(Scope* scope)
{
    PushScope();
    currentScope = scope;
}

void SymbolTable::EndScope()
{
    PopScope();
}

void SymbolTable::PushTopScopeIndex()
{
    topScopeIndexStack.push(topScopeIndex);
    topScopeIndex = scopeStack.size() - 1;
}

void SymbolTable::PopTopScopeIndex()
{
    topScopeIndex = topScopeIndexStack.top();
    topScopeIndexStack.pop();
}

void SymbolTable::Init()
{
    if (module->Name() == "std.type.fundamental")
    {
        CreateFundamentalTypes();
        CreateCoreSymbols();
    }
}

void SymbolTable::Import(const SymbolTable& that)
{
    Context context;
    context.SetSymbolTable(this);
    globalNs->Import(that.globalNs.get(), &context);
    ImportSpecializations();
    ImportCompoundTypeMap(that);
    ImportFundamentalTypeMap(that);
    ImportNodeSymbolMap(that);
    ImportSymbolNodeMap(that);
    ImportTypeMap(that);
    ImportFunctionMap(that);
    ImportVariableMap(that);
    ImportConstraintMap(that);
    typenameConstraintSymbol = that.typenameConstraintSymbol;
    errorTypeSymbol = that.errorTypeSymbol;
    MapConstraint(typenameConstraintSymbol);
}

void SymbolTable::ImportSpecializations()
{
    for (const auto& s : specializationSet)
    {
        specializationSet.insert(s);
    }
}

void SymbolTable::ImportCompoundTypeMap(const SymbolTable& that)
{
    for (const auto& p : that.compoundTypeMap)
    {
        compoundTypeMap.insert(p);
    }
}

void SymbolTable::ImportFundamentalTypeMap(const SymbolTable& that)
{
    for (const auto& p : that.fundamentalTypeMap)
    {
        fundamentalTypeMap.insert(p);
    }
}

void SymbolTable::ImportNodeSymbolMap(const SymbolTable& that)
{
    for (const auto& p : that.allNodeSymbolMap)
    {
        allNodeSymbolMap.insert(p);
    }
}

void SymbolTable::ImportSymbolNodeMap(const SymbolTable& that)
{
    for (const auto& p : that.allSymbolNodeMap)
    {
        allSymbolNodeMap.insert(p);
    }
}

void SymbolTable::ImportTypeMap(const SymbolTable& that)
{
    for (const auto& p : that.typeMap)
    {
        typeMap.insert(p);
    }
}

void SymbolTable::ImportFunctionMap(const SymbolTable& that)
{
    for (const auto& p : that.functionMap)
    {
        functionMap.insert(p);
    }
}

void SymbolTable::ImportVariableMap(const SymbolTable& that)
{
    for (const auto& p : that.variableMap)
    {
        variableMap.insert(p);
    }
}

void SymbolTable::ImportConstraintMap(const SymbolTable& that)
{
    for (const auto& p : that.constraintMap)
    {
        constraintMap.insert(p);
    }
}

void SymbolTable::WriteMaps(Writer& writer)
{
    uint32_t nns = nodeSymbolMap.size();
    writer.GetBinaryStreamWriter().WriteULEB128UInt(nns);
    for (const auto& m : nodeSymbolMap)
    {
        int32_t nodeId = m.first->Id();
        writer.GetBinaryStreamWriter().Write(nodeId);
        const util::uuid& uuid = m.second->Id();
        writer.GetBinaryStreamWriter().Write(uuid);
    }
    uint32_t nsn = symbolNodeMap.size();
    writer.GetBinaryStreamWriter().WriteULEB128UInt(nsn);
    for (const auto& m : symbolNodeMap)
    {
        const util::uuid& uuid = m.first->Id();
        writer.GetBinaryStreamWriter().Write(uuid);
        int32_t nodeId = m.second->Id();
        writer.GetBinaryStreamWriter().Write(nodeId);
    }
}

void SymbolTable::ReadMaps(Reader& reader, soul::cpp20::ast::Reader& astReader)
{
    uint32_t nns = reader.GetBinaryStreamReader().ReadULEB128UInt();
    for (uint32_t i = 0; i < nns; ++i)
    {
        int32_t nodeId = reader.GetBinaryStreamReader().ReadInt();
        util::uuid symbolId;
        reader.GetBinaryStreamReader().ReadUuid(symbolId);
        soul::cpp20::ast::Node* node = astReader.GetNode(nodeId);
        Symbol* symbol = soul::cpp20::symbols::GetSymbol(symbolId);
        nodeSymbolMap[node] = symbol;
        allNodeSymbolMap[node] = symbol;
    }
    uint32_t nsn = reader.GetBinaryStreamReader().ReadULEB128UInt();
    for (uint32_t i = 0; i < nsn; ++i)
    {
        util::uuid symbolId;
        reader.GetBinaryStreamReader().ReadUuid(symbolId);
        int32_t nodeId = reader.GetBinaryStreamReader().ReadInt();
        Symbol* symbol = soul::cpp20::symbols::GetSymbol(symbolId);
        soul::cpp20::ast::Node* node = astReader.GetNode(nodeId);
        symbolNodeMap[symbol] = node;
        allSymbolNodeMap[symbol] = node;
    }
}

void SymbolTable::Write(Writer& writer)
{
    globalNs->Write(writer);
    uint32_t scount = specializations.size();
    writer.GetBinaryStreamWriter().WriteULEB128UInt(scount);
    for (const auto& specialization : specializations)
    {
        writer.Write(specialization.get());
    }
    uint32_t ccount = compoundTypes.size();
    writer.GetBinaryStreamWriter().WriteULEB128UInt(ccount);
    for (const auto& compoundType : compoundTypes)
    {
        writer.Write(compoundType.get());
    }
}

void SymbolTable::Read(Reader& reader)
{
    Context context;
    context.SetSymbolTable(this);
    reader.SetContext(&context);
    globalNs->Read(reader);
    uint32_t scount = reader.GetBinaryStreamReader().ReadULEB128UInt();
    for (uint32_t i = 0; i < scount; ++i)
    {
        Symbol* symbol = reader.ReadSymbol();
        if (symbol->IsSpecializationSymbol())
        {
            SpecializationSymbol* specialization = static_cast<SpecializationSymbol*>(symbol);
            specializations.push_back(std::unique_ptr<Symbol>(specialization));
        }
        else
        {
            throw std::runtime_error("soul.cpp20.symbols.symbol_table: specialization expected");
        }
    }
    uint32_t ccount = reader.GetBinaryStreamReader().ReadULEB128UInt();
    for (uint32_t i = 0; i < ccount; ++i)
    {
        Symbol* symbol = reader.ReadSymbol();
        if (symbol->IsCompoundTypeSymbol())
        {
            CompoundTypeSymbol* compoundType = static_cast<CompoundTypeSymbol*>(symbol);
            compoundTypes.push_back(std::unique_ptr<CompoundTypeSymbol>(compoundType));
        }
        else
        {
            throw std::runtime_error("soul.cpp20.symbols.symbol_table: compound type expected");
        }
    }
}

void SymbolTable::Resolve()
{
    for (const auto& specialization : specializations)
    {
        SpecializationSymbol* s = static_cast<SpecializationSymbol*>(specialization.get());
        specialization->Resolve(*this);
        MapType(s);
        specializationSet.insert(s);
    }
    for (const auto& compoundType : compoundTypes)
    {
        compoundType->Resolve(*this);
        MapType(compoundType.get());
        bool found = false;
        std::vector<CompoundTypeSymbol*>& compoundTypeVec = compoundTypeMap[compoundType->BaseType()];
        for (CompoundTypeSymbol* ct: compoundTypeVec)
        {
            if (ct == compoundType.get())
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            compoundTypeVec.push_back(compoundType.get());
        }
    }
    for (const auto& specialization : specializations)
    {
        SpecializationSymbol* s = static_cast<SpecializationSymbol*>(specialization.get());
        s->ResolveTemplateArgs(*this);
    }
    globalNs->Resolve(*this);
}

Symbol* SymbolTable::Lookup(const std::u32string& name, SymbolGroupKind symbolGroupKind, const soul::ast::SourcePos& sourcePos, Context* context) 
{
    return Lookup(name, symbolGroupKind, sourcePos, context, LookupFlags::none);
}

Symbol* SymbolTable::Lookup(const std::u32string& name, SymbolGroupKind symbolGroupKind, const soul::ast::SourcePos& sourcePos, Context* context, LookupFlags flags)
{
    Symbol* symbol = currentScope->Lookup(name, symbolGroupKind, ScopeLookup::allScopes, sourcePos, context, flags);
    if (!symbol)
    {
        for (int i = scopeStack.size() - 1; i >= topScopeIndex; --i)
        {
            Scope* scope = scopeStack[i];
            symbol = scope->Lookup(name, symbolGroupKind, ScopeLookup::allScopes, sourcePos, context, flags);
            if (symbol)
            {
                break;
            }
        }
    }
    return symbol;
}

void SymbolTable::MapNode(soul::cpp20::ast::Node* node)
{
    Symbol* symbol = currentScope->GetSymbol();
    MapNode(node, symbol);
}

void SymbolTable::MapNode(soul::cpp20::ast::Node* node, Symbol* symbol)
{
    MapNode(node, symbol, MapKind::both);
}

void SymbolTable::MapNode(soul::cpp20::ast::Node* node, Symbol* symbol, MapKind kind)
{
    if ((kind & MapKind::nodeToSymbol) != MapKind::none)
    {
        nodeSymbolMap[node] = symbol;
        allNodeSymbolMap[node] = symbol;
    }
    if ((kind & MapKind::symbolToNode) != MapKind::none)
    {
        symbolNodeMap[symbol] = node;
        allSymbolNodeMap[symbol] = node;
    }
}

soul::cpp20::ast::Node* SymbolTable::GetNodeNothrow(Symbol* symbol) const
{
    auto it = allSymbolNodeMap.find(symbol);
    if (it != allSymbolNodeMap.cend())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}

soul::cpp20::ast::Node* SymbolTable::GetNode(Symbol* symbol) const
{
    soul::cpp20::ast::Node* node = GetNodeNothrow(symbol);
    if (node)
    {
        return node;
    }
    else
    {
        throw std::runtime_error("node for symbol '" + util::ToUtf8(symbol->Name()) + "' not found");
    }
}

void SymbolTable::RemoveNode(soul::cpp20::ast::Node* node)
{
    if (soul::lexer::parsing_error_thrown || ExceptionThrown()) return;
    nodeSymbolMap.erase(node);
}

Symbol* SymbolTable::GetSymbolNothrow(soul::cpp20::ast::Node* node) const
{
    auto it = allNodeSymbolMap.find(node);
    if (it != allNodeSymbolMap.cend())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}

Symbol* SymbolTable::GetSymbol(soul::cpp20::ast::Node* node) const
{
    Symbol* symbol = GetSymbolNothrow(node);
    if (symbol)
    {
        return symbol;
    }
    else
    {
        throw std::runtime_error("symbol for node not found");
    }
}

TypeSymbol* SymbolTable::GetTypeNothrow(const util::uuid& id) const
{
    auto it = typeMap.find(id);
    if (it != typeMap.cend())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}

TypeSymbol* SymbolTable::GetType(const util::uuid& id) const
{
    TypeSymbol* type = GetTypeNothrow(id);
    if (type)
    {
        return type;
    }
    else
    {
        throw std::runtime_error("type for id '" + util::ToString(id) + "' not found");
    }
}

void SymbolTable::MapType(TypeSymbol* type)
{
    typeMap[type->Id()] = type;
}

void SymbolTable::AddVariable(const std::u32string& name, soul::cpp20::ast::Node* node, TypeSymbol* type, Value* value, Context* context)
{
    VariableGroupSymbol* variableGroup = currentScope->GroupScope()->GetOrInsertVariableGroup(name, node->GetSourcePos(), context);
    VariableSymbol* variableSymbol = new VariableSymbol(name);
    variableSymbol->SetType(type);
    variableSymbol->SetValue(value);
    currentScope->AddSymbol(variableSymbol, node->GetSourcePos(), context);
    variableGroup->AddVariable(variableSymbol);
    MapNode(node, variableSymbol);
}

void SymbolTable::AddAliasType(soul::cpp20::ast::Node* node, TypeSymbol* type, Context* context)
{
    std::u32string id = node->Str();
    AliasGroupSymbol* aliasGroup = currentScope->GroupScope()->GetOrInsertAliasGroup(id, node->GetSourcePos(), context);
    AliasTypeSymbol* aliasTypeSymbol = new AliasTypeSymbol(id, type);
    currentScope->AddSymbol(aliasTypeSymbol, node->GetSourcePos(), context);
    aliasGroup->AddAliasTypeSymbol(aliasTypeSymbol);
    MapNode(node, aliasTypeSymbol);
}

void SymbolTable::AddUsingDeclaration(soul::cpp20::ast::Node* node, Symbol* symbol, Context* context)
{
    currentScope->AddUsingDeclaration(symbol, node->GetSourcePos(), context);
    MapNode(node, symbol, MapKind::nodeToSymbol);
}

void SymbolTable::AddUsingDirective(NamespaceSymbol* ns, soul::cpp20::ast::Node* node, Context* context)
{
    currentScope->AddUsingDirective(ns, node->GetSourcePos(), context);
    MapNode(node, ns, MapKind::nodeToSymbol);
}

void SymbolTable::BeginNamespace(const std::u32string& name, soul::cpp20::ast::Node* node, Context* context)
{
    soul::ast::SourcePos sourcePos;
    if (node)
    {
        sourcePos = node->GetSourcePos();
    }
    if (name.empty())
    {
        BeginScope(currentScope);
    }
    else
    {
        Symbol* symbol = currentScope->Lookup(name, SymbolGroupKind::typeSymbolGroup, ScopeLookup::thisScope, sourcePos, context, LookupFlags::dontResolveSingle);
        if (symbol)
        {
            if (symbol->IsNamespaceSymbol())
            {
                NamespaceSymbol* namespaceSymbol = static_cast<NamespaceSymbol*>(symbol);
                if (node)
                {
                    MapNode(node, namespaceSymbol);
                }
                BeginScope(namespaceSymbol->GetScope());
                return;
            }
            else
            {
                ThrowException("name of namespace '" + util::ToUtf8(name) + " conflicts with earlier declaration", sourcePos, context);
            }
        }
        NamespaceSymbol* namespaceSymbol = new NamespaceSymbol(name);
        if (node)
        {
            MapNode(node, namespaceSymbol);
        }
        currentScope->AddSymbol(namespaceSymbol, sourcePos, context);
        BeginScope(namespaceSymbol->GetScope());
    }
}

void SymbolTable::EndNamespace()
{
    EndScope();
}

void SymbolTable::BeginNamespace(soul::cpp20::ast::Node* node, Context* context)
{
    BeginNamespace(node->Str(), node, context);
}

void SymbolTable::EndNamespace(int level)
{
    for (int i = 0; i < level; ++i)
    {
        EndNamespace();
    }
}

void SymbolTable::BeginClass(const std::u32string& name, ClassKind classKind, soul::cpp20::ast::Node* node, Context* context)
{
    Symbol* symbol = currentScope->Lookup(name, SymbolGroupKind::typeSymbolGroup, ScopeLookup::thisScope, node->GetSourcePos(), context, LookupFlags::dontResolveSingle);
    if (symbol && symbol->IsClassGroupSymbol())
    {
        ClassGroupSymbol* classGroup = static_cast<ClassGroupSymbol*>(symbol);
        ClassTypeSymbol* classTypeSymbol = classGroup->GetClass(0);
        if (classTypeSymbol)
        {
            classTypeSymbol->SetClassKind(classKind);
            BeginScope(classTypeSymbol->GetScope());
            return;
        }
    }
    ClassGroupSymbol* classGroup = currentScope->GroupScope()->GetOrInsertClassGroup(name, node->GetSourcePos(), context);
    ClassTypeSymbol* classTypeSymbol = new ClassTypeSymbol(name);
    classTypeSymbol->SetClassKind(classKind);
    currentScope->AddSymbol(classTypeSymbol, node->GetSourcePos(), context);
    classGroup->AddClass(classTypeSymbol);
    MapNode(node, classTypeSymbol);
    BeginScope(classTypeSymbol->GetScope());
}

void SymbolTable::EndClass()
{
    EndScope();
}

void SymbolTable::BeginEnumeratedType(const std::u32string& name, EnumTypeKind kind, TypeSymbol* underlyingType, soul::cpp20::ast::Node* node, Context* context)
{
    Symbol* symbol = currentScope->Lookup(name, SymbolGroupKind::typeSymbolGroup, ScopeLookup::thisScope, node->GetSourcePos(), context, LookupFlags::dontResolveSingle);
    if (symbol && symbol->IsEnumeratedTypeSymbol())
    {
        EnumeratedTypeSymbol* enumTypeSymbol = static_cast<EnumeratedTypeSymbol*>(symbol);
        enumTypeSymbol->SetEnumTypeKind(kind);
        enumTypeSymbol->SetUnderlyingType(underlyingType);
        BeginScope(enumTypeSymbol->GetScope());
        return;
    }
    EnumeratedTypeSymbol* enumTypeSymbol = new EnumeratedTypeSymbol(name);
    enumTypeSymbol->SetEnumTypeKind(kind);
    enumTypeSymbol->SetUnderlyingType(underlyingType);
    currentScope->AddSymbol(enumTypeSymbol, node->GetSourcePos(), context);
    MapNode(node, enumTypeSymbol);
    BeginScope(enumTypeSymbol->GetScope());
}

void SymbolTable::EndEnumeratedType()
{
    EndScope();
}

void SymbolTable::AddEnumerator(const std::u32string& name, Value* value, soul::cpp20::ast::Node* node, Context* context)
{
    EnumConstantSymbol* enumConstantSymbol = new EnumConstantSymbol(name);
    enumConstantSymbol->SetValue(value);
    currentScope->AddSymbol(enumConstantSymbol, node->GetSourcePos(), context);
    MapNode(node, enumConstantSymbol);
}

void SymbolTable::BeginBlock(const soul::ast::SourcePos& sourcePos, Context* context)
{
    BlockSymbol* blockSymbol = new BlockSymbol(); 
    currentScope->AddSymbol(blockSymbol, sourcePos, context);
    BeginScope(blockSymbol->GetScope());
}

void SymbolTable::EndBlock()
{
    EndScope();
}

void SymbolTable::RemoveBlock()
{
    Symbol* symbol = currentScope->GetSymbol();
    if (symbol && symbol->IsBlockSymbol())
    {
        EndScope();
        currentScope->RemoveSymbol(symbol);
    }
    else
    {
        throw std::runtime_error("soul.cpp20.symbols.symbol_table: block expected");
    }
}

void SymbolTable::BeginTemplateDeclaration(soul::cpp20::ast::Node* node, Context* context)
{
    TemplateDeclarationSymbol* templateDeclarationSymbol = new TemplateDeclarationSymbol();
    currentScope->AddSymbol(templateDeclarationSymbol, node->GetSourcePos(), context);
    BeginScope(templateDeclarationSymbol->GetScope());
}

void SymbolTable::EndTemplateDeclaration()
{
    EndScope();
}

void SymbolTable::RemoveTemplateDeclaration()
{
/*
    Symbol* symbol = currentScope->GetSymbol();
    if (symbol && symbol->IsTemplateDeclarationSymbol())
    {
        EndScope();
        currentScope->RemoveSymbol(symbol);
    }
*/
}

void SymbolTable::AddTemplateParameter(const std::u32string& name, soul::cpp20::ast::Node* node, Symbol* constraint, int index, Context* context)
{
    TemplateParameterSymbol* templateParameterSymbol = new TemplateParameterSymbol(constraint, name, index);
    currentScope->AddSymbol(templateParameterSymbol, node->GetSourcePos(), context);
    MapNode(node, templateParameterSymbol);
}

FunctionSymbol* SymbolTable::AddFunction(const std::u32string& name, soul::cpp20::ast::Node* node, FunctionKind kind, FunctionQualifiers qualifiers, Context* context)
{
    FunctionGroupSymbol* functionGroup = currentScope->GroupScope()->GetOrInsertFunctionGroup(name, node->GetSourcePos(), context);
    FunctionSymbol* functionSymbol = new FunctionSymbol(name);
    functionSymbol->SetFunctionKind(kind);
    functionSymbol->SetFunctionQualifiers(qualifiers);
    currentScope->AddSymbol(functionSymbol, node->GetSourcePos(), context);
    functionGroup->AddFunction(functionSymbol);
    MapNode(node, functionSymbol);
    return functionSymbol;
}

ParameterSymbol* SymbolTable::CreateParameter(const std::u32string& name, soul::cpp20::ast::Node* node, TypeSymbol* type, Context* context)
{
    ParameterSymbol* parameterSymbol = new ParameterSymbol(name, type);
    if (node)
    {
        MapNode(node, parameterSymbol);
    }
    return parameterSymbol;
}

TypeSymbol* SymbolTable::MakeCompoundType(TypeSymbol* baseType, const Derivations& derivations)
{
    Derivations drv = derivations;
    if (baseType->IsCompoundTypeSymbol())
    {
        CompoundTypeSymbol* compoundTypeSymbol = static_cast<CompoundTypeSymbol*>(baseType);
        drv = Merge(drv, compoundTypeSymbol->GetDerivations());
        baseType = compoundTypeSymbol->BaseType();
    }
    if (drv.IsEmpty())
    {
        return baseType;
    }
    std::vector<CompoundTypeSymbol*>& compoundTypeVec = compoundTypeMap[baseType];
    for (const auto& compoundType : compoundTypeVec)
    {
        if (compoundType->GetDerivations() == drv)
        {
            return compoundType;
        }
    }
    CompoundTypeSymbol* compoundType = new CompoundTypeSymbol(baseType, drv);
    compoundTypeVec.push_back(compoundType);
    compoundTypes.push_back(std::unique_ptr<CompoundTypeSymbol>(compoundType));
    MapType(compoundType);
    return compoundType;
}

SpecializationSymbol* SymbolTable::MakeSpecialization(TypeSymbol* classTemplate, const std::vector<TypeSymbol*>& templateArguments)
{
    std::unique_ptr<SpecializationSymbol> symbol(new SpecializationSymbol(MakeSpecializationName(classTemplate, templateArguments)));
    symbol->SetClassTemplate(classTemplate);
    for (TypeSymbol* templateArg : templateArguments)
    {
        symbol->AddTemplateArgument(templateArg);
    }
    auto it = specializationSet.find(symbol.get());
    if (it != specializationSet.cend())
    {
        return *it;
    }
    SpecializationSymbol* sym = symbol.get();
    specializationSet.insert(sym);
    specializations.push_back(std::move(symbol));
    MapType(sym);
    return sym;
}

void SymbolTable::CreateFundamentalTypes()
{
    AddFundamentalType(FundamentalTypeKind::charType);
    AddFundamentalType(FundamentalTypeKind::char8Type);
    AddFundamentalType(FundamentalTypeKind::char16Type);
    AddFundamentalType(FundamentalTypeKind::char32Type);
    AddFundamentalType(FundamentalTypeKind::wcharType);
    AddFundamentalType(FundamentalTypeKind::boolType);
    AddFundamentalType(FundamentalTypeKind::shortIntType);
    AddFundamentalType(FundamentalTypeKind::intType);
    AddFundamentalType(FundamentalTypeKind::longIntType);
    AddFundamentalType(FundamentalTypeKind::longLongIntType);
    AddFundamentalType(FundamentalTypeKind::floatType);
    AddFundamentalType(FundamentalTypeKind::doubleType);
    AddFundamentalType(FundamentalTypeKind::voidType);
    AddFundamentalType(FundamentalTypeKind::signedCharType);
    AddFundamentalType(FundamentalTypeKind::unsignedCharType);
    AddFundamentalType(FundamentalTypeKind::unsignedShortIntType);
    AddFundamentalType(FundamentalTypeKind::unsignedIntType);
    AddFundamentalType(FundamentalTypeKind::unsignedLongIntType);
    AddFundamentalType(FundamentalTypeKind::unsignedLongLongIntType);
    AddFundamentalType(FundamentalTypeKind::longDoubleType);
    AddFundamentalType(FundamentalTypeKind::autoType);
    AddFundamentalType(FundamentalTypeKind::nullPtrType);
}

void SymbolTable::AddFundamentalType(FundamentalTypeKind kind)
{
    FundamentalTypeSymbol* fundamentalTypeSymbol = new FundamentalTypeSymbol(kind);
    Context context;
    context.SetSymbolTable(this);
    globalNs->AddSymbol(fundamentalTypeSymbol, soul::ast::SourcePos(), &context);
    MapFundamentalType(fundamentalTypeSymbol);
}

void SymbolTable::MapFundamentalType(FundamentalTypeSymbol* fundamentalTypeSymbol)
{
    FundamentalTypeKind kind = fundamentalTypeSymbol->GetFundamentalTypeKind();
    fundamentalTypeMap[static_cast<int32_t>(kind)] = fundamentalTypeSymbol;
}

TypeSymbol* SymbolTable::GetFundamentalTypeSymbol(FundamentalTypeKind kind)
{
    auto it = fundamentalTypeMap.find(static_cast<int32_t>(kind));
    if (it != fundamentalTypeMap.cend())
    {
        return it->second;
    }
    else
    {
        throw std::runtime_error("fundamental type " + std::to_string(static_cast<int32_t>(kind)) + " not found");
    }
}

void SymbolTable::MapFunction(FunctionSymbol* function)
{
    functionMap[function->Id()] = function;
}

void SymbolTable::MapVariable(VariableSymbol* variable)
{
    variableMap[variable->Id()] = variable;
}

void SymbolTable::MapConstraint(Symbol* constraint)
{
    constraintMap[constraint->Id()] = constraint;
}

FunctionSymbol* SymbolTable::GetFunction(const util::uuid& id) const
{
    auto it = functionMap.find(id);
    if (it != functionMap.cend())
    {
        return it->second;
    }
    else
    {
        throw std::runtime_error("soul.cpp20.symbols.symbol_table: function for id '" + util::ToString(id) + "' not found");
    }
}

AliasTypeSymbol* SymbolTable::GetAliasType(const util::uuid& id) const
{
    TypeSymbol* type = GetType(id);
    if (type->IsAliasTypeSymbol())
    {
        return static_cast<AliasTypeSymbol*>(type);
    }
    else
    {
        throw std::runtime_error("soul.cpp20.symbols.symbol_table: alias type expected");
    }
}

ClassTypeSymbol* SymbolTable::GetClass(const util::uuid& id) const
{
    TypeSymbol* type = GetType(id);
    if (type->IsClassTypeSymbol())
    {
        return static_cast<ClassTypeSymbol*>(type);
    }
    else
    {
        throw std::runtime_error("soul.cpp20.symbols.symbol_table: class type expected");
    }
}

VariableSymbol* SymbolTable::GetVariable(const util::uuid& id) const
{
    auto it = variableMap.find(id);
    if (it != variableMap.cend())
    {
        return it->second;
    }
    else
    {
        throw std::runtime_error("variable for id '" + util::ToString(id) + "' not found");
    }
}

Symbol* SymbolTable::GetConstraint(const util::uuid& id) const
{
    auto it = constraintMap.find(id);
    if (it != constraintMap.cend())
    {
        return it->second;
    }
    else
    {
        throw std::runtime_error("constraint for id '" + util::ToString(id) + "' not found");
    }
}

void SymbolTable::CreateCoreSymbols()
{
    typenameConstraintSymbol = new TypenameConstraintSymbol();
    errorTypeSymbol = new ErrorTypeSymbol();
    MapConstraint(typenameConstraintSymbol);
    Context context;
    context.SetSymbolTable(this);
    globalNs->AddSymbol(typenameConstraintSymbol, soul::ast::SourcePos(), &context);
    globalNs->AddSymbol(errorTypeSymbol, soul::ast::SourcePos(), &context);
}

Symbols::Symbols()
{
}

void Symbols::AddSymbol(Symbol* symbol)
{
    symbolMap[symbol->Id()] = symbol;
}

Symbol* Symbols::GetSymbol(const util::uuid& symbolId)
{
    auto it = symbolMap.find(symbolId);
    if (it != symbolMap.cend())
    {
        return it->second;
    }
    else
    {
        throw std::runtime_error("soul.cpp20.symbols.Reader: symbol id " + util::ToString(symbolId) + " not found");
    }
}

Symbols* symbols = nullptr;

void SetSymbols(Symbols* symbols_)
{
    symbols = symbols_;
}

void AddSymbol(Symbol* symbol)
{
    symbols->AddSymbol(symbol);
}

Symbol* GetSymbol(const util::uuid& symbolId)
{
    return symbols->GetSymbol(symbolId);
}

} // namespace soul::cpp20::symbols
