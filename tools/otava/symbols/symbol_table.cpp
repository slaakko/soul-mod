// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module;
#include <boost/uuid/uuid.hpp>

module otava.symbols.symbol.table;

import util.unicode;
import util.uuid;
import soul.lexer;
import otava.ast.error;
import otava.symbols.alias.type.symbol;
import otava.symbols.alias.group.symbol;
import otava.symbols.bound.node;
import otava.symbols.class_group.symbol;
import otava.symbols.function.group.symbol;
import otava.symbols.variable.group.symbol;
import otava.symbols.enum_group.symbol;
import otava.symbols.block;
import otava.symbols.classes;
import otava.symbols.concepts;
import otava.symbols.concept_group.symbol;
import otava.symbols.context;
import otava.symbols.compound.type.symbol;
import otava.symbols.declarator;
import otava.symbols.enums;
import otava.symbols.modules;
import otava.symbols.namespaces;
import otava.symbols.function.symbol;
import otava.symbols.fundamental.type.symbol;
import otava.symbols.templates;
import otava.symbols.type.symbol;
import otava.symbols.variable.symbol;
import otava.symbols.reader;
import otava.symbols.writer;
import otava.symbols.exception;
import otava.symbols.specialization;
import otava.symbols.visitor;
import otava.symbols.bound.tree;
import otava.symbols.fundamental.type.operation;
import otava.symbols.symbol_map;
import otava.symbols.conversion.table;

namespace otava::symbols {

SymbolTable::SymbolTable() : 
    module(nullptr), 
    globalNs(new NamespaceSymbol(std::u32string())), 
    currentScope(globalNs->GetScope()), 
    typenameConstraintSymbol(nullptr),
    errorTypeSymbol(nullptr),
    topScopeIndex(0),
    addToRecomputeNameSet(false), 
    currentAccess(Access::none),
    nodeMap(nullptr),
    symbolMap(nullptr),
    classLevel(0),
    conversionTable(new ConversionTable())
{
    globalNs->SetSymbolTable(this);
}

void SymbolTable::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void SymbolTable::SetCurrentScope(Scope* scope)
{
    currentScope = scope;
}

void SymbolTable::PushScope()
{
    scopeStack.push_back(currentScope);
}

void SymbolTable::PopScope()
{
    if (scopeStack.empty())
    {
        otava::ast::SetExceptionThrown();
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

void SymbolTable::SetCurrentAccess(Access access)
{
    currentAccess = access;
}

void SymbolTable::PushAccess(Access access)
{
    accessStack.push(currentAccess);
    currentAccess = access;
}

void SymbolTable::PopAccess()
{
    currentAccess = accessStack.top();
    accessStack.pop();
}

void SymbolTable::AddClass(ClassTypeSymbol* cls)
{
    classes.insert(cls);
    allClasses.insert(cls);
}

BoundExpressionNode* SymbolTable::MakeBooleanConversion(BoundExpressionNode* subject, Context* context)
{
    FunctionSymbol* conversionFunction = conversionTable->GetConversion(GetFundamentalType(FundamentalTypeKind::boolType), subject->GetType());
    if (!conversionFunction)
    {
        ThrowException("condition must be convertible to Boolean type value", subject->GetSourcePos(), context);
        return nullptr;
    }
    return new BoundConversionNode(subject, conversionFunction, subject->GetSourcePos());
}

void SymbolTable::Init()
{
    if (module->Name() == "std.type.fundamental")
    {
        CreateFundamentalTypes();
        AddFundamentalTypeOperations();
        CreateCoreSymbols();
        module->GetEvaluationContext()->Init();
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
    ImportFunctionDefinitionMap(that);
    ImportVariableMap(that);
    ImportConstraintMap(that);
    ImportForwardDeclarations(that);
    ImportSpecifierMap(that);
    ImportClasses(that);
    typenameConstraintSymbol = that.typenameConstraintSymbol;
    errorTypeSymbol = that.errorTypeSymbol;
    MapConstraint(typenameConstraintSymbol);
    conversionTable->Import(that.GetConversionTable());
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

void SymbolTable::ImportFunctionDefinitionMap(const SymbolTable& that)
{
    for (const auto& p : that.functionDefinitionMap)
    {
        functionDefinitionMap.insert(p);
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

void SymbolTable::ImportForwardDeclarations(const SymbolTable& that)
{
    for (const auto& fwd : that.allForwardDeclarations)
    {
        allForwardDeclarations.insert(fwd);
    }
}

void SymbolTable::ImportSpecifierMap(const SymbolTable& that)
{
    for (const auto& spec : that.allSpecifierNodeMap)
    {
        allSpecifierNodeMap.insert(spec);
    }
}

void SymbolTable::ImportClasses(const SymbolTable& that)
{
    for (auto cls : that.allClasses)
    {
        allClasses.insert(cls);
    }
}

void SymbolTable::WriteMaps(Writer& writer)
{
    uint32_t nns = nodeSymbolMap.size();
    writer.GetBinaryStreamWriter().WriteULEB128UInt(nns);
    for (const auto& m : nodeSymbolMap)
    {
        int64_t nodeId = m.first->Id();
        if (nodeId == 0xcdcdcdcdcdcdcdcd)
        {
            int x = 0;
        }
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
        int64_t nodeId = m.second->Id();
        if (nodeId == 0xcdcdcdcdcdcdcdcd)
        {
            int x = 0;
        }
        writer.GetBinaryStreamWriter().Write(nodeId);
    }
    uint32_t nfwd = forwardDeclarations.size();
    writer.GetBinaryStreamWriter().WriteULEB128UInt(nfwd);
    for (const auto& fwd : forwardDeclarations)
    {
        writer.GetBinaryStreamWriter().Write(fwd->Id());
    }
    uint32_t nspec = specifierNodeMap.size();
    writer.GetBinaryStreamWriter().WriteULEB128UInt(nspec);
    for (const auto& spec : specifierNodeMap)
    {
        const util::uuid& uuid = spec.first->Id();
        writer.GetBinaryStreamWriter().Write(uuid);
        int64_t nodeId = spec.second->Id();
        if (nodeId == 0xcdcdcdcdcdcdcdcd)
        {
            int x = 0;
        }
        writer.GetBinaryStreamWriter().Write(nodeId);
    }
    uint32_t nc = classes.size();
    writer.GetBinaryStreamWriter().WriteULEB128UInt(nc);
    for (auto cls : classes)
    {
        const util::uuid& uuid = cls->Id();
        writer.GetBinaryStreamWriter().Write(uuid);
    }
}

void SymbolTable::ReadMaps(Reader& reader, otava::ast::NodeMap* nodeMap, SymbolMap* symbolMap)
{
    uint32_t nns = reader.GetBinaryStreamReader().ReadULEB128UInt();
    for (uint32_t i = 0; i < nns; ++i)
    {
        int64_t nodeId = reader.GetBinaryStreamReader().ReadLong();
        util::uuid symbolId;
        reader.GetBinaryStreamReader().ReadUuid(symbolId);
        otava::ast::Node* node = nodeMap->GetNode(nodeId);
        Symbol* symbol = symbolMap->GetSymbol(symbolId);
        nodeSymbolMap[node] = symbol;
        allNodeSymbolMap[node] = symbol;
    }
    uint32_t nsn = reader.GetBinaryStreamReader().ReadULEB128UInt();
    for (uint32_t i = 0; i < nsn; ++i)
    {
        util::uuid symbolId;
        reader.GetBinaryStreamReader().ReadUuid(symbolId);
        int64_t nodeId = reader.GetBinaryStreamReader().ReadLong();
        Symbol* symbol = symbolMap->GetSymbol(symbolId);
        otava::ast::Node* node = nodeMap->GetNode(nodeId);
        symbolNodeMap[symbol] = node;
        allSymbolNodeMap[symbol] = node;
    }
    uint32_t nfwd = reader.GetBinaryStreamReader().ReadULEB128UInt();
    for (uint32_t i = 0; i < nfwd; ++i)
    {
        util::uuid fwdId;
        reader.GetBinaryStreamReader().ReadUuid(fwdId);
        Symbol* symbol = symbolMap->GetSymbol(fwdId);
        forwardDeclarations.insert(symbol);
        allForwardDeclarations.insert(symbol);
    }
    uint32_t nspec = reader.GetBinaryStreamReader().ReadULEB128UInt();
    for (uint32_t i = 0; i < nspec; ++i)
    {
        util::uuid symbolId;
        reader.GetBinaryStreamReader().ReadUuid(symbolId);
        int64_t nodeId = reader.GetBinaryStreamReader().ReadLong();
        Symbol* symbol = symbolMap->GetSymbol(symbolId);
        otava::ast::Node* node = nodeMap->GetNode(nodeId);
        specifierNodeMap[symbol] = node;
        allSpecifierNodeMap[symbol] = node;
    }
    uint32_t nc = reader.GetBinaryStreamReader().ReadULEB128UInt();
    for (uint32_t i = 0; i < nc; ++i)
    {
        util::uuid clsId;
        reader.GetBinaryStreamReader().ReadUuid(clsId);
        Symbol* symbol = symbolMap->GetSymbol(clsId);
        if (symbol->IsClassTypeSymbol())
        {
            classes.insert(static_cast<ClassTypeSymbol*>(symbol));
            allClasses.insert(static_cast<ClassTypeSymbol*>(symbol));
        }
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
            otava::ast::SetExceptionThrown();
            throw std::runtime_error("otava.symbols.symbol_table: specialization expected");
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
            otava::ast::SetExceptionThrown();
            throw std::runtime_error("otava.symbols.symbol_table: compound type expected");
        }
    }
}

void SymbolTable::Resolve()
{
    for (auto& specialization : specializations)
    {
        MapType(static_cast<TypeSymbol*>(specialization.get()));
    }
    for (auto& compoundType : compoundTypes)
    {
        MapType(compoundType.get());
        compoundType->Resolve(*this);
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
    globalNs->Resolve(*this);
    for (const auto& specialization : specializations)
    {
        SpecializationSymbol* s = static_cast<SpecializationSymbol*>(specialization.get());
        s->Resolve(*this);
    }
    conversionTable->Make();
}

Symbol* SymbolTable::Lookup(const std::u32string& name, SymbolGroupKind symbolGroupKind, const soul::ast::SourcePos& sourcePos, Context* context) 
{
    Symbol* symbol = Lookup(name, symbolGroupKind, sourcePos, context, LookupFlags::none);
    if (!symbol)
    {
        symbol = LookupInScopeStack(name, symbolGroupKind, sourcePos, context, LookupFlags::none);
    }
    return symbol;
}

Symbol* SymbolTable::LookupInScopeStack(const std::u32string& name, SymbolGroupKind symbolGroupKind, const soul::ast::SourcePos& sourcePos, Context* context, LookupFlags flags)
{
    if (topScopeIndex == -1) return nullptr;
    for (int i = scopeStack.size() - 1; i >= topScopeIndex; --i)
    {
        Scope* scope = scopeStack[i];
        Symbol* symbol = scope->Lookup(name, symbolGroupKind, ScopeLookup::allScopes, sourcePos, context, flags);
        if (symbol)
        {
            return symbol;
        }
    }
    return nullptr;
}

Symbol* SymbolTable::Lookup(const std::u32string& name, SymbolGroupKind symbolGroupKind, const soul::ast::SourcePos& sourcePos, Context* context, LookupFlags flags)
{
    return currentScope->Lookup(name, symbolGroupKind, ScopeLookup::allScopes, sourcePos, context, flags);
}

Symbol* SymbolTable::LookupSymbol(Symbol* symbol)
{
    std::vector<Symbol*> components;
    while (symbol)
    {
        if (!symbol->Name().empty())
        {
            components.push_back(symbol);
        }
        symbol = symbol->Parent();
    }
    Scope* scope = globalNs->GetScope();
    for (int i = components.size() - 1; i >= 0; --i)
    {
        if (!scope) break;
        Symbol* lookupSymbol = components[i];
        std::vector<Symbol*> symbols;
        std::set<Scope*> visited;
        scope->Lookup(lookupSymbol->Name(), SymbolGroupKind::typeSymbolGroup, ScopeLookup::thisScope, LookupFlags::none, symbols, visited, nullptr);
        if (symbols.size() == 1)
        {
            Symbol* found = symbols.front();
            if (i == 0)
            {
                return found;
            }
            scope = found->GetScope();
        }
    }
    return nullptr;
}

void SymbolTable::CollectViableFunctions(Scope* scope, const std::u32string& groupName, int arity, std::vector<FunctionSymbol*>& viableFunctions, Context* context)
{
    std::vector<Symbol*> symbols;
    std::set<Scope*> visited;
    scope->Lookup(groupName, SymbolGroupKind::functionSymbolGroup, ScopeLookup::allScopes, LookupFlags::dontResolveSingle | LookupFlags::all, symbols, visited, context);
    for (Symbol* symbol : symbols)
    {
        if (symbol->IsFunctionGroupSymbol())
        {
            FunctionGroupSymbol* functionGroup = static_cast<FunctionGroupSymbol*>(symbol);
            functionGroup->CollectViableFunctions(arity, viableFunctions);
        }
    }
}

void SymbolTable::MapNode(otava::ast::Node* node)
{
    Symbol* symbol = currentScope->GetSymbol();
    MapNode(node, symbol);
}

void SymbolTable::MapNode(otava::ast::Node* node, Symbol* symbol)
{
    MapNode(node, symbol, MapKind::both);
}

void SymbolTable::MapNode(otava::ast::Node* node, Symbol* symbol, MapKind kind)
{
    if (symbol->IsTemplateParameterSymbol())
    {
        int x = 0;
    }
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

otava::ast::Node* SymbolTable::GetNodeNothrow(Symbol* symbol) const
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

otava::ast::Node* SymbolTable::GetNode(Symbol* symbol) const
{
    otava::ast::Node* node = GetNodeNothrow(symbol);
    if (node)
    {
        return node;
    }
    else
    {
        otava::ast::SetExceptionThrown();
        throw std::runtime_error("node for symbol '" + util::ToUtf8(symbol->Name()) + "' not found");
    }
}

void SymbolTable::RemoveNode(otava::ast::Node* node)
{
    if (soul::lexer::parsing_error_thrown || ExceptionThrown() || otava::ast::ExceptionThrown()) return;
    Symbol* symbol = nullptr;
    auto it = nodeSymbolMap.find(node);
    if (it != nodeSymbolMap.cend())
    {
        symbol = it->second;
        nodeSymbolMap.erase(node);
    }
    if (symbol)
    {
        symbolNodeMap.erase(symbol);
    }
}

otava::ast::Node* SymbolTable::GetSpecifierNode(Symbol* symbol) const
{
    auto it = allSpecifierNodeMap.find(symbol);
    if (it != allSpecifierNodeMap.cend())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}

void SymbolTable::SetSpecifierNode(Symbol* symbol, otava::ast::Node* node)
{
    specifierNodeMap[symbol] = node;
    allSpecifierNodeMap[symbol] = node;
}

Symbol* SymbolTable::GetSymbolNothrow(otava::ast::Node* node) const
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

Symbol* SymbolTable::GetSymbol(otava::ast::Node* node) const
{
    Symbol* symbol = GetSymbolNothrow(node);
    if (symbol)
    {
        return symbol;
    }
    else
    {
        otava::ast::SetExceptionThrown();
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
        otava::ast::SetExceptionThrown();
        throw std::runtime_error("type for id '" + util::ToString(id) + "' not found");
    }
}

void SymbolTable::MapType(TypeSymbol* type)
{
    typeMap[type->Id()] = type;
}

VariableSymbol* SymbolTable::AddVariable(const std::u32string& name, otava::ast::Node* node, TypeSymbol* declaredType, TypeSymbol* initializerType, 
    Value* value, DeclarationFlags flags, Context* context)
{
    VariableGroupSymbol* variableGroup = currentScope->GroupScope()->GetOrInsertVariableGroup(name, node->GetSourcePos(), context);
    VariableSymbol* variableSymbol = new VariableSymbol(name);
    variableSymbol->SetAccess(CurrentAccess());
    variableSymbol->SetDeclaredType(declaredType);
    variableSymbol->SetInitializerType(initializerType);
    variableSymbol->SetValue(value);
    variableSymbol->SetDeclarationFlags(flags);
    currentScope->SymbolScope()->AddSymbol(variableSymbol, node->GetSourcePos(), context);
    variableGroup->AddVariable(variableSymbol);
    MapNode(node, variableSymbol);
    return variableSymbol;
}

void SymbolTable::AddAliasType(otava::ast::Node* node, TypeSymbol* type, Context* context)
{
    std::u32string id = node->Str();
    AliasGroupSymbol* aliasGroup = currentScope->GroupScope()->GetOrInsertAliasGroup(id, node->GetSourcePos(), context);
    AliasTypeSymbol* aliasTypeSymbol = new AliasTypeSymbol(id, type);
    aliasTypeSymbol->SetAccess(currentAccess);
    currentScope->SymbolScope()->AddSymbol(aliasTypeSymbol, node->GetSourcePos(), context);
    aliasGroup->AddAliasTypeSymbol(aliasTypeSymbol);
    MapNode(node, aliasTypeSymbol);
}

void SymbolTable::AddUsingDeclaration(otava::ast::Node* node, Symbol* symbol, Context* context)
{
    currentScope->SymbolScope()->AddUsingDeclaration(symbol, node->GetSourcePos(), context);
    MapNode(node, symbol, MapKind::nodeToSymbol);
}

void SymbolTable::AddUsingDirective(NamespaceSymbol* ns, otava::ast::Node* node, Context* context)
{
    currentScope->SymbolScope()->AddUsingDirective(ns, node->GetSourcePos(), context);
    MapNode(node, ns, MapKind::nodeToSymbol);
}

void SymbolTable::BeginNamespace(const std::u32string& name, otava::ast::Node* node, Context* context)
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
        currentScope->SymbolScope()->AddSymbol(namespaceSymbol, sourcePos, context);
        BeginScope(namespaceSymbol->GetScope());
    }
}

void SymbolTable::EndNamespace()
{
    EndScope();
}

void SymbolTable::BeginNamespace(otava::ast::Node* node, Context* context)
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

void SymbolTable::BeginClass(const std::u32string& name, ClassKind classKind, otava::ast::Node* node, Context* context)
{
    Symbol* symbol = currentScope->Lookup(name, SymbolGroupKind::typeSymbolGroup, ScopeLookup::thisScope, node->GetSourcePos(), context, LookupFlags::dontResolveSingle);
    if (symbol && symbol->IsClassGroupSymbol())
    {
        ClassGroupSymbol* classGroup = static_cast<ClassGroupSymbol*>(symbol);
        int arity = 0;
        Symbol* symbol = currentScope->GetSymbol();
        if (symbol && symbol->IsTemplateDeclarationSymbol())
        {
            TemplateDeclarationSymbol* templateDeclarationSymbol = static_cast<TemplateDeclarationSymbol*>(symbol);
            arity = templateDeclarationSymbol->Arity();
        }
        ClassTypeSymbol* classTypeSymbol = classGroup->GetClass(arity);
        if (classTypeSymbol)
        {
            classTypeSymbol->SetClassKind(classKind);
            BeginScope(classTypeSymbol->GetScope());
            return;
        }
    }
    ClassGroupSymbol* classGroup = currentScope->GroupScope()->GetOrInsertClassGroup(name, node->GetSourcePos(), context);
    ClassTypeSymbol* classTypeSymbol = new ClassTypeSymbol(name);
    classTypeSymbol->SetLevel(classLevel++);
    AddClass(classTypeSymbol);
    classTypeSymbol->SetAccess(CurrentAccess());
    classTypeSymbol->SetClassKind(classKind);
    currentScope->SymbolScope()->AddSymbol(classTypeSymbol, node->GetSourcePos(), context);
    classGroup->AddClass(classTypeSymbol);
    MapNode(node, classTypeSymbol);
    SetSpecifierNode(classTypeSymbol, node);
    BeginScope(classTypeSymbol->GetScope());
    switch (classKind)
    {
        case ClassKind::class_:
        {
            PushAccess(Access::private_);
            break;
        }
        case ClassKind::struct_:
        case ClassKind::union_:
        {
            PushAccess(Access::public_);
            break;
        }
    }
}

void SymbolTable::AddBaseClass(TypeSymbol* baseClass, const soul::ast::SourcePos& sourcePos, Context* context)
{
    Symbol* symbol = currentScope->GetSymbol();
    if (symbol->IsClassTypeSymbol())
    {
        ClassTypeSymbol* classTypeSymbol = static_cast<ClassTypeSymbol*>(symbol);
        classTypeSymbol->AddBaseClass(baseClass, sourcePos, context);
    }
    else
    {
        ThrowException("class type symbol expected", sourcePos, context);
    }
}

void SymbolTable::EndClass()
{
    --classLevel;
    PopAccess();
    EndScope();
}

void SymbolTable::AddForwardClassDeclaration(const std::u32string& name, ClassKind classKind, otava::ast::Node* node, Context* context)
{
    Symbol* symbol = currentScope->Lookup(name, SymbolGroupKind::typeSymbolGroup, ScopeLookup::thisScope, node->GetSourcePos(), context, LookupFlags::dontResolveSingle);
    if (symbol && symbol->IsClassGroupSymbol())
    {
        ClassGroupSymbol* classGroup = static_cast<ClassGroupSymbol*>(symbol);
        int arity = 0;
        Symbol* symbol = currentScope->GetSymbol();
        if (symbol && symbol->IsTemplateDeclarationSymbol())
        {
            TemplateDeclarationSymbol* templateDeclarationSymbol = static_cast<TemplateDeclarationSymbol*>(symbol);
            arity = templateDeclarationSymbol->Arity();
        }
        ForwardClassDeclarationSymbol* forwardDeclarationSymbol = classGroup->GetForwardDeclaration(arity);
        if (forwardDeclarationSymbol)
        {
            forwardDeclarationSymbol->SetClassKind(classKind);
            return;
        }
    }
    ClassGroupSymbol* classGroup = currentScope->GroupScope()->GetOrInsertClassGroup(name, node->GetSourcePos(), context);
    ForwardClassDeclarationSymbol* forwardDeclarationSymbol = new ForwardClassDeclarationSymbol(name);
    forwardDeclarationSymbol->SetAccess(CurrentAccess());
    forwardDeclarationSymbol->SetClassKind(classKind);
    currentScope->SymbolScope()->AddSymbol(forwardDeclarationSymbol, node->GetSourcePos(), context);
    classGroup->AddForwardDeclaration(forwardDeclarationSymbol);
    MapNode(node, forwardDeclarationSymbol);
    forwardDeclarations.insert(forwardDeclarationSymbol);
    allForwardDeclarations.insert(forwardDeclarationSymbol);
}

void SymbolTable::BeginEnumeratedType(const std::u32string& name, EnumTypeKind kind, TypeSymbol* underlyingType, otava::ast::Node* node, Context* context)
{
    EnumGroupSymbol* enumGroup = currentScope->GroupScope()->GetOrInsertEnumGroup(name, node->GetSourcePos(), context);
    EnumeratedTypeSymbol* enumType = enumGroup->GetEnumType();
    if (enumType)
    {
        ThrowException("enumerated type '" + util::ToUtf8(name) + "' not unique", node->GetSourcePos(), context);
    }
    EnumeratedTypeSymbol* enumTypeSymbol = new EnumeratedTypeSymbol(name);
    enumTypeSymbol->SetAccess(CurrentAccess());
    enumTypeSymbol->SetEnumTypeKind(kind);
    enumTypeSymbol->SetUnderlyingType(underlyingType);
    currentScope->SymbolScope()->AddSymbol(enumTypeSymbol, node->GetSourcePos(), context);
    MapNode(node, enumTypeSymbol);
    enumGroup->SetEnumType(enumTypeSymbol);
    BeginScope(enumTypeSymbol->GetScope());
}

void SymbolTable::EndEnumeratedType()
{
    EndScope();
}

void SymbolTable::AddForwardEnumDeclaration(const std::u32string& name, EnumTypeKind enumTypeKind, TypeSymbol* underlyingType, otava::ast::Node* node, Context* context)
{
    EnumGroupSymbol* enumGroup = currentScope->GroupScope()->GetOrInsertEnumGroup(name, node->GetSourcePos(), context);
    if (enumGroup->GetForwardDeclaration())
    {
        return;
    }
    ForwardEnumDeclarationSymbol* forwardDeclarationSymbol = new ForwardEnumDeclarationSymbol(name);
    forwardDeclarationSymbol->SetAccess(CurrentAccess());
    forwardDeclarationSymbol->SetEnumTypeKind(enumTypeKind);
    forwardDeclarationSymbol->SetUnderlyingType(underlyingType);
    currentScope->SymbolScope()->AddSymbol(forwardDeclarationSymbol, node->GetSourcePos(), context);
    enumGroup->SetForwardDeclaration(forwardDeclarationSymbol);
    MapNode(node, forwardDeclarationSymbol);
    forwardDeclarations.insert(forwardDeclarationSymbol);
    allForwardDeclarations.insert(forwardDeclarationSymbol);
}

void SymbolTable::AddEnumerator(const std::u32string& name, Value* value, otava::ast::Node* node, Context* context)
{
    EnumConstantSymbol* enumConstantSymbol = new EnumConstantSymbol(name);
    enumConstantSymbol->SetValue(value);
    currentScope->SymbolScope()->AddSymbol(enumConstantSymbol, node->GetSourcePos(), context);
    MapNode(node, enumConstantSymbol);
}

void SymbolTable::BeginBlock(const soul::ast::SourcePos& sourcePos, Context* context)
{
    BlockSymbol* blockSymbol = new BlockSymbol(); 
    currentScope->SymbolScope()->AddSymbol(blockSymbol, sourcePos, context);
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
        otava::ast::SetExceptionThrown();
        throw std::runtime_error("otava.symbols.symbol_table: block expected");
    }
}

void SymbolTable::BeginTemplateDeclaration(otava::ast::Node* node, Context* context)
{
    TemplateDeclarationSymbol* templateDeclarationSymbol = new TemplateDeclarationSymbol();
    currentScope->SymbolScope()->AddSymbol(templateDeclarationSymbol, node->GetSourcePos(), context);
    BeginScope(templateDeclarationSymbol->GetScope());
}

void SymbolTable::EndTemplateDeclaration()
{
    EndScope();
}

void SymbolTable::RemoveTemplateDeclaration()
{
    Symbol* symbol = currentScope->GetSymbol();
    if (symbol && symbol->IsTemplateDeclarationSymbol())
    {
        EndScope();
        currentScope->RemoveSymbol(symbol);
    }
}

void SymbolTable::AddTemplateParameter(const std::u32string& name, otava::ast::Node* node, Symbol* constraint, int index, ParameterSymbol* parameter, otava::ast::Node* defaultTemplateArgNode, 
    Context* context)
{
    TemplateParameterSymbol* templateParameterSymbol = new TemplateParameterSymbol(constraint, name, index, defaultTemplateArgNode);
    if (parameter)
    {
        templateParameterSymbol->AddSymbol(parameter, node->GetSourcePos(), context);
    }
    currentScope->SymbolScope()->AddSymbol(templateParameterSymbol, node->GetSourcePos(), context);
    MapNode(node, templateParameterSymbol);
}

FunctionSymbol* SymbolTable::AddFunction(const std::u32string& name, otava::ast::Node* node, FunctionKind kind, FunctionQualifiers qualifiers, DeclarationFlags flags, Context* context)
{
    FunctionGroupSymbol* functionGroup = currentScope->GroupScope()->GetOrInsertFunctionGroup(name, node->GetSourcePos(), context);
    FunctionSymbol* functionSymbol = new FunctionSymbol(name);
    functionSymbol->SetAccess(CurrentAccess());
    functionSymbol->SetFunctionKind(kind);
    functionSymbol->SetFunctionQualifiers(qualifiers);
    functionSymbol->SetDeclarationFlags(flags);
    currentScope->SymbolScope()->AddSymbol(functionSymbol, node->GetSourcePos(), context);
    functionGroup->AddFunction(functionSymbol);
    MapNode(node, functionSymbol);
    return functionSymbol;
}

void SymbolTable::AddFunctionSymbol(Scope* scope, FunctionSymbol* functionSymbol, Context* context)
{
    FunctionGroupSymbol* functionGroup = currentScope->GroupScope()->GetOrInsertFunctionGroup(functionSymbol->Name(), soul::ast::SourcePos(), context);
    scope->SymbolScope()->AddSymbol(functionSymbol, soul::ast::SourcePos(), context);
    functionGroup->AddFunction(functionSymbol);
}

FunctionDefinitionSymbol* SymbolTable::AddFunctionDefinition(Scope* scope, const std::u32string& name, const std::vector<TypeSymbol*>& parameterTypes, 
    FunctionQualifiers qualifiers, otava::ast::Node* node, FunctionSymbol* declaration, Context* context)
{
    FunctionGroupSymbol* functionGroup = scope->GroupScope()->GetOrInsertFunctionGroup(name, node->GetSourcePos(), context);
    FunctionDefinitionSymbol* prev = functionGroup->GetFunctionDefinition(parameterTypes, qualifiers);
    if (prev)
    {
        PrintWarning("function definition '" + util::ToUtf8(name) + "' not unique", node->GetSourcePos(), context);
    }
    FunctionDefinitionSymbol* functionDefinition = new FunctionDefinitionSymbol(name);
    functionDefinition->SetFunctionQualifiers(qualifiers);
    functionDefinition->SetDeclaration(declaration);
    if (declaration)
    {
        functionDefinition->SetAccess(declaration->GetAccess());
    }
    currentScope->SymbolScope()->AddSymbol(functionDefinition, node->GetSourcePos(), context);
    functionGroup->AddFunctionDefinition(functionDefinition);
    return functionDefinition;
}

ParameterSymbol* SymbolTable::CreateParameter(const std::u32string& name, otava::ast::Node* node, TypeSymbol* type, Context* context)
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
    if (AddToRecomputeNameSet())
    {
        AddToRecomputeNameSet(compoundType);
    }
    compoundType->SetSymbolTable(this);
    return compoundType;
}

TypeSymbol* SymbolTable::MakeConstCharPtrType()
{
    Derivations derivations;
    derivations.vec.push_back(Derivation::constDerivation);
    derivations.vec.push_back(Derivation::pointerDerivation);
    return MakeCompoundType(GetFundamentalType(FundamentalTypeKind::charType), derivations);
}

TypeSymbol* SymbolTable::MakeConstChar8PtrType()
{
    Derivations derivations;
    derivations.vec.push_back(Derivation::constDerivation);
    derivations.vec.push_back(Derivation::pointerDerivation);
    return MakeCompoundType(GetFundamentalType(FundamentalTypeKind::char8Type), derivations);
}

TypeSymbol* SymbolTable::MakeConstChar16PtrType()
{
    Derivations derivations;
    derivations.vec.push_back(Derivation::constDerivation);
    derivations.vec.push_back(Derivation::pointerDerivation);
    return MakeCompoundType(GetFundamentalType(FundamentalTypeKind::char16Type), derivations);
}

TypeSymbol* SymbolTable::MakeConstChar32PtrType()
{
    Derivations derivations;
    derivations.vec.push_back(Derivation::constDerivation);
    derivations.vec.push_back(Derivation::pointerDerivation);
    return MakeCompoundType(GetFundamentalType(FundamentalTypeKind::char32Type), derivations);
}

TypeSymbol* SymbolTable::MakeConstWCharPtrType()
{
    Derivations derivations;
    derivations.vec.push_back(Derivation::constDerivation);
    derivations.vec.push_back(Derivation::pointerDerivation);
    return MakeCompoundType(GetFundamentalType(FundamentalTypeKind::wcharType), derivations);
}

ConceptSymbol* SymbolTable::AddConcept(const std::u32string& name, otava::ast::Node* node, Context* context)
{
    ConceptGroupSymbol* conceptGroup = currentScope->GroupScope()->GetOrInsertConceptGroup(name, node->GetSourcePos(), context);
    ConceptSymbol* conceptSymbol = new ConceptSymbol(name);
    conceptGroup->AddConcept(conceptSymbol);
    currentScope->SymbolScope()->AddSymbol(conceptSymbol, node->GetSourcePos(), context);
    MapNode(node, conceptSymbol);
    return conceptSymbol;
}

SpecializationSymbol* SymbolTable::MakeSpecialization(TypeSymbol* classTemplate, const std::vector<Symbol*>& templateArguments)
{
    std::unique_ptr<SpecializationSymbol> symbol(new SpecializationSymbol(MakeSpecializationName(classTemplate, templateArguments)));
    symbol->SetSymbolTable(this);
    symbol->SetClassTemplate(classTemplate);
    for (Symbol* templateArg : templateArguments)
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

void SymbolTable::AddFundamentalTypeOperations()
{
    Context context;
    context.SetSymbolTable(this);
    AddFundamentalTypeOperationsToSymbolTable(&context);
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
        otava::ast::SetExceptionThrown();
        throw std::runtime_error("fundamental type " + std::to_string(static_cast<int32_t>(kind)) + " not found");
    }
}

void SymbolTable::MapFunction(FunctionSymbol* function)
{
    functionMap[function->Id()] = function;
}

void SymbolTable::MapFunctionDefinition(FunctionDefinitionSymbol* functionDefinition)
{
    functionDefinitionMap[functionDefinition->Id()] = functionDefinition;
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
        otava::ast::SetExceptionThrown();
        throw std::runtime_error("otava.symbols.symbol_table: function for id '" + util::ToString(id) + "' not found");
    }
}

FunctionDefinitionSymbol* SymbolTable::GetFunctionDefinition(const util::uuid& id) const
{
    auto it = functionDefinitionMap.find(id);
    if (it != functionDefinitionMap.cend())
    {
        return it->second;
    }
    else
    {
        otava::ast::SetExceptionThrown();
        throw std::runtime_error("otava.symbols.symbol_table: function definition for id '" + util::ToString(id) + "' not found");
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
        otava::ast::SetExceptionThrown();
        throw std::runtime_error("otava.symbols.symbol_table: alias type expected");
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
        otava::ast::SetExceptionThrown();
        throw std::runtime_error("otava.symbols.symbol_table: class type expected");
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
        otava::ast::SetExceptionThrown();
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
        otava::ast::SetExceptionThrown();
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

void SymbolTable::AddToRecomputeNameSet(CompoundTypeSymbol* compoundTypeSymbol)
{
    recomputeNameSet.insert(compoundTypeSymbol);
}

void SymbolTable::RecomputeNames()
{
    for (const auto& compoundType : recomputeNameSet)
    {
        compoundType->SetName(MakeCompoundTypeName(compoundType->BaseType(), compoundType->GetDerivations()));
    }
    recomputeNameSet.clear();
}

TypeSymbol* SymbolTable::GetFundamentalType(FundamentalTypeKind kind) const
{
    auto it = fundamentalTypeMap.find(static_cast<int32_t>(kind));
    if (it != fundamentalTypeMap.cend())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}

} // namespace otava::symbols
