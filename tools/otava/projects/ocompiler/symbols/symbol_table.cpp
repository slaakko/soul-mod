// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.symbol.table;

import util.unicode;
import util.uuid;
import soul.lexer;
import soul.xml.dom;
import otava.intermediate.error;
import otava.symbols.alias.type.symbol;
import otava.symbols.alias.group.symbol;
import otava.symbols.alias.type.templates;
import otava.symbols.array.type.symbol;
import otava.symbols.bound.tree;
import otava.symbols.class_templates;
import otava.symbols.variable.group.symbol;
import otava.symbols.function.type.symbol;
import otava.symbols.enum_group.symbol;
import otava.symbols.block;
import otava.symbols.classes;
import otava.symbols.concept_group.symbol;
import otava.symbols.context;
import otava.symbols.compound.type.symbol;
import otava.symbols.declarator;
import otava.symbols.declaration;
import otava.symbols.enums;
import otava.symbols.modules;
import otava.symbols.namespaces;
import otava.symbols.function.kind;
import otava.symbols.function.symbol;
import otava.symbols.fundamental.type.symbol;
import otava.symbols.templates;
import otava.symbols.type.symbol;
import otava.symbols.variable.symbol;
import otava.symbols.reader;
import otava.symbols.writer;
import otava.symbols.error;
import otava.symbols.visitor;
import otava.symbols.bound.tree;
import otava.symbols.fundamental.type.operation;
import otava.symbols.symbol_map;
import otava.symbols.conversion.table;
import otava.symbols.friends;
import otava.symbols.function.templates;
import otava.symbols.inline_functions;
import otava.symbols.argument.conversion.table;
import otava.symbols.operation.repository;

namespace otava::symbols {

bool projectReady = false;

bool ProjectReady()
{
    return projectReady;
}

void SetProjectReady(bool projectReady_)
{
    projectReady = projectReady_;
}

ClassTemplateNameLess::ClassTemplateNameLess() : error(0)
{
}

bool ClassTemplateNameLess::operator()(ClassTemplateSpecializationSymbol* left, ClassTemplateSpecializationSymbol* right) const
{
    std::expected<std::u32string, int> l = left->FullName();
    std::expected<std::u32string, int> r = right->FullName();
    if (!l)
    {
        error = l.error();
        return false;
    }
    if (!r)
    {
        error = r.error();
        return false;
    }
    return *l < *r;
}

SymbolTable::SymbolTable() :
    module(nullptr),
    symbolMap(nullptr),
    globalNs(new NamespaceSymbol(std::u32string())),
    currentScope(globalNs->GetScope()),
    typenameConstraintSymbol(nullptr),
    errorTypeSymbol(nullptr),
    topScopeIndex(0),
    addToRecomputeNameSet(false),
    currentAccess(Access::none),
    nodeMap(nullptr),
    classLevel(0),
    conversionTable(new ConversionTable(this)),
    currentLinkage(Linkage::cpp_linkage)
{
}

void SymbolTable::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void SymbolTable::SetCurrentScope(Scope* scope)
{
    currentScope = scope;
}

std::expected<Scope*, int> SymbolTable::GetNamespaceScope(const std::u32string& nsName, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<Symbol*, int> lrv = Lookup(nsName, SymbolGroupKind::typeSymbolGroup, sourcePos, context);
    if (!lrv) return std::unexpected<int>(lrv.error());
    Symbol* ns = *lrv;
    if (ns)
    {
        return std::expected<Scope*, int>(ns->GetScope());
    }
    else
    {
        return std::expected<Scope*, int>(nullptr);
    }
}

void SymbolTable::PushScope()
{
    scopeStack.push_back(currentScope);
}

std::expected<bool, int> SymbolTable::PopScope()
{
    if (scopeStack.empty())
    {
        return std::unexpected<int>(util::AllocateError("scope stack is empty"));
    }
    currentScope = scopeStack.back();
    scopeStack.pop_back();
    return std::expected<bool, int>(true);
}

void SymbolTable::BeginScope(Scope* scope)
{
    PushScope();
    currentScope = scope;
}

std::expected<bool, int> SymbolTable::EndScope()
{
    return PopScope();
}

std::expected<bool, int> SymbolTable::BeginScopeGeneric(Scope* scope, Context* context)
{
    if (context->GetFlag(ContextFlags::instantiateFunctionTemplate) ||
        context->GetFlag(ContextFlags::instantiateMemFnOfClassTemplate) ||
        context->GetFlag(ContextFlags::instantiateInlineFunction))
    {
        return CurrentScope()->PushParentScope(scope);
    }
    else
    {
        BeginScope(scope);
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> SymbolTable::EndScopeGeneric(Context* context)
{
    if (context->GetFlag(ContextFlags::instantiateFunctionTemplate) ||
        context->GetFlag(ContextFlags::instantiateMemFnOfClassTemplate) ||
        context->GetFlag(ContextFlags::instantiateInlineFunction))
    {
        return CurrentScope()->PopParentScope();
    }
    else
    {
        return EndScope();
    }
    return std::expected<bool, int>(true);
}

void SymbolTable::PushTopScopeIndex()
{
    topScopeIndexStack.push(topScopeIndex);
    topScopeIndex = static_cast<int>(scopeStack.size()) - 1;
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

std::expected<bool, int> SymbolTable::Init()
{
    if (module->Name() == "std.type.fundamental")
    {
        InitCompoundTypeIds();
        InitTemplateParameterIds();
        InitLevelIds();
        std::expected<bool, int> rv = CreateFundamentalTypes();
        if (!rv) return rv;
        rv = AddFundamentalTypeOperations();
        if (!rv) return rv;
        rv = CreateCoreSymbols();
        if (!rv) return rv;
        module->GetEvaluationContext()->Init();
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> SymbolTable::Import(const SymbolTable& that, FunctionDefinitionSymbolSet* functionDefinitionSymbolSet)
{
#ifdef DEBUG_SYMBOL_IO
    std::cout << ">import symbol table '" << module->Name() << "' <- '" << that.GetModule()->Name() << "'\n";
#endif
    Context context;
    context.SetSymbolTable(this);
    context.SetFunctionDefinitionSymbolSet(functionDefinitionSymbolSet);
    std::expected<bool, int> rv = globalNs->Import(that.globalNs.get(), &context);
    if (!rv) return rv;
    ImportSpecializations(that);
    ImportArrayTypes(that);
    ImportDependentTypes(that);
    ImportCompoundTypeMap(that, &context);
    ImportFundamentalTypeMap(that);
    ImportNodeSymbolMap(that);
    ImportSymbolNodeMap(that);
    ImportTypeMap(that);
    ImportFunctionMap(that);
    ImportFunctionDefinitionMap(that);
    ImportVariableMap(that);
    ImportConceptMap(that);
    ImportConstraintMap(that);
    ImportForwardDeclarations(that);
    ImportSpecifierMap(that);
    ImportClasses(that);
    rv = ImportExplicitInstantiations(that);
    if (!rv) return rv;
    ImportClassGroups(that);
    ImportAliasGroups(that);
    ImportFunctionGroupTypes(that);
    ImportClassGroupTypes(that);
    ImportAliasGroupTypes(that);
    typenameConstraintSymbol = that.typenameConstraintSymbol;
    errorTypeSymbol = that.errorTypeSymbol;
    MapConstraint(typenameConstraintSymbol);
    conversionTable->Import(that.GetConversionTable());
    AddImportAfterResolve(&that);
    templateParameterIds = that.templateParameterIds;
    compoundTypeIds = that.compoundTypeIds;
    levelIds = that.levelIds;
#ifdef DEBUG_SYMBOL_IO
    std::cout << "<import symbol table '" << module->Name() << "' <- '" << that.GetModule()->Name() << "'\n";
#endif
    return std::expected<bool, int>(true);
}

void SymbolTable::AddImportAfterResolve(const SymbolTable* that)
{
    if (std::find(importAfterResolve.begin(), importAfterResolve.end(), that) == importAfterResolve.end())
    {
        importAfterResolve.push_back(that);
    }
}

void SymbolTable::ImportSpecializations(const SymbolTable& that)
{
    for (const auto& s : that.classTemplateSpecializationMap)
    {
        classTemplateSpecializationMap.erase(s.first);
        classTemplateSpecializationMap.insert(s);
    }
    for (AliasTypeTemplateSpecializationSymbol* a : that.aliasTypeTemplateSpecializationSet)
    {
        aliasTypeTemplateSpecializationSet.insert(a);
    }
}

void SymbolTable::ImportArrayTypes(const SymbolTable& that)
{
    for (ArrayTypeSymbol* s : that.arrayTypeSet)
    {
        arrayTypeSet.insert(s);
    }
}

void SymbolTable::ImportDependentTypes(const SymbolTable& that)
{
    for (const auto& dependentType : that.dependentTypeSymbols)
    {
        dependentTypeSet.insert(dependentType.get());
    }
    for (DependentTypeSymbol* dependentType : that.dependentTypeSet)
    {
        dependentTypeSet.insert(dependentType);
    }
}

void SymbolTable::ImportCompoundTypeMap(const SymbolTable& that, Context* context)
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

void SymbolTable::ImportConceptMap(const SymbolTable& that)
{
    for (const auto& p : that.conceptMap)
    {
        conceptMap.insert(p);
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
    for (Symbol* fwd : that.allForwardDeclarations)
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
    for (ClassTypeSymbol* cls : that.allClasses)
    {
        allClasses.insert(cls);
    }
}

std::expected<bool, int> SymbolTable::ImportExplicitInstantiations(const SymbolTable& that)
{
    for (const auto& instantiation : that.explicitInstantiationMap)
    {
        explicitInstantiationMap.insert(instantiation);
        int error = explicitInstantiationMap.key_comp().error;
        if (error != 0)
        {
            return std::unexpected<int>(error);
        }
    }
    return std::expected<bool, int>(true);
}

void SymbolTable::ImportClassGroups(const SymbolTable& that)
{
    for (const auto& classGroup : that.classGroupMap)
    {
        classGroupMap.insert(classGroup);
    }
}

void SymbolTable::ImportAliasGroups(const SymbolTable& that)
{
    for (const auto& aliasGroup : that.aliasGroupMap)
    {
        aliasGroupMap.insert(aliasGroup);
    }
}

void SymbolTable::ImportFunctionGroupTypes(const SymbolTable& that)
{
    for (const auto& functionGroupType : that.functionGroupTypeMap)
    {
        functionGroupTypeMap.insert(functionGroupType);
    }
}

void SymbolTable::ImportClassGroupTypes(const SymbolTable& that)
{
    for (const auto& classGroupType : that.classGroupTypeMap)
    {
        classGroupTypeMap.insert(classGroupType);
    }
}

void SymbolTable::ImportAliasGroupTypes(const SymbolTable& that)
{
    for (const auto& aliasGroupType : that.aliasGroupTypeMap)
    {
        aliasGroupTypeMap.insert(aliasGroupType);
    }
}

std::expected<bool, int> SymbolTable::WriteMaps(Writer& writer, Context* context)
{
    std::vector<std::pair<otava::ast::Node*, Symbol*>> exportNodeSymbols;
    for (const auto& m : nodeSymbolMap)
    {
        otava::ast::Node* node = m.first;
        Symbol* symbol = m.second;
        if (symbol->IsExportMapSymbol(context))
        {
            exportNodeSymbols.push_back(std::make_pair(node, symbol));
        }
    }
    std::uint32_t nns = exportNodeSymbols.size();
    std::expected<bool, int> rv = writer.GetBinaryStreamWriter().WriteULEB128UInt(nns);
    if (!rv) return rv;
    for (const auto& m : exportNodeSymbols)
    {
        otava::ast::Node* node = m.first;
        Symbol* symbol = m.second;
        std::int64_t nodeId = node->InternalId();
        if (node->IsInternallyMapped())
        {
            nodeId = -1;
        }
        rv = writer.GetBinaryStreamWriter().Write(static_cast<std::uint16_t>(node->Kind()));
        if (!rv) return rv;
        rv = writer.GetBinaryStreamWriter().Write(nodeId);
        if (!rv) return rv;
        rv = writer.GetBinaryStreamWriter().Write(symbol->Id());
        if (!rv) return rv;
    }
    std::vector<std::pair<Symbol*, otava::ast::Node*>> exportSymbolNodes;
    for (const auto& m : symbolNodeMap)
    {
        Symbol* symbol = m.first;
        otava::ast::Node* node = m.second;
        if (symbol->IsExportSymbol(context))
        {
            exportSymbolNodes.push_back(std::make_pair(symbol, node));
        }
    }
    std::uint32_t nsn = exportSymbolNodes.size();
    rv = writer.GetBinaryStreamWriter().WriteULEB128UInt(nsn);
    if (!rv) return rv;
    for (const auto& m : exportSymbolNodes)
    {
        Symbol* symbol = m.first;
        otava::ast::Node* node = m.second;
        rv = writer.GetBinaryStreamWriter().Write(symbol->Id());
        if (!rv) return rv;
        std::int64_t nodeId = node->InternalId();
        if (node->IsInternallyMapped())
        {
            nodeId = -1;
        }
        rv = writer.GetBinaryStreamWriter().Write(nodeId);
        if (!rv) return rv;
    }
    std::uint32_t nfwd = forwardDeclarations.size();
    rv = writer.GetBinaryStreamWriter().WriteULEB128UInt(nfwd);
    if (!rv) return rv;
    for (Symbol* fwd : forwardDeclarations)
    {
        rv = writer.GetBinaryStreamWriter().Write(fwd->Id());
        if (!rv) return rv;
    }
    std::uint32_t nspec = specifierNodeMap.size();
    rv = writer.GetBinaryStreamWriter().WriteULEB128UInt(nspec);
    if (!rv) return rv;
    for (const auto& spec : specifierNodeMap)
    {
        const util::uuid& uuid = spec.first->Id();
        rv = writer.GetBinaryStreamWriter().Write(uuid);
        if (!rv) return rv;
        std::int64_t nodeId = spec.second->InternalId();
        rv = writer.GetBinaryStreamWriter().Write(nodeId);
        if (!rv) return rv;
    }
    std::uint32_t nc = classes.size();
    rv = writer.GetBinaryStreamWriter().WriteULEB128UInt(nc);
    if (!rv) return rv;
    for (ClassTypeSymbol* cls : classes)
    {
        const util::uuid& uuid = cls->Id();
        rv = writer.GetBinaryStreamWriter().Write(uuid);
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> SymbolTable::ReadMaps(Reader& reader, otava::ast::NodeMap* nodeMap)
{
#ifdef DEBUG_SYMBOL_IO
    std::cout << ">read maps " << GetModule()->Name() << "\n";
#endif
    std::expected<std::uint32_t, int> nrv = reader.GetBinaryStreamReader().ReadULEB128UInt();
    if (!nrv) return std::unexpected<int>(nrv.error());
    std::uint32_t nns = *nrv;
#ifdef DEBUG_SYMBOL_IO
    std::cout << nns << " node symbol map" << "\n";
#endif
    for (std::int32_t i = 0; i < static_cast<std::int32_t>(nns); ++i)
    {
        std::expected<std::uint16_t, int> urv = reader.GetBinaryStreamReader().ReadUShort();
        if (!urv) return std::unexpected<int>(urv.error());
        std::uint16_t k = *urv;
        otava::ast::NodeKind kind = static_cast<otava::ast::NodeKind>(k);
        std::expected<std::int64_t, int> n = reader.GetBinaryStreamReader().ReadLong();
        if (!n) return std::unexpected<int>(n.error());
        std::int64_t nodeId = *n;
        util::uuid symbolId;
        std::expected<bool, int> rv = reader.GetBinaryStreamReader().ReadUuid(symbolId);
        if (!rv)  return rv;
        if (nodeId != -1)
        {
            std::expected<otava::ast::Node*, int> n = nodeMap->GetNode(nodeId);
            if (!n) return std::unexpected<int>(n.error());
            otava::ast::Node* node = *n;
            Symbol* symbol = symbolMap->GetSymbol(symbolId);
            if (symbol)
            {
                nodeSymbolMap[node] = symbol;
                allNodeSymbolMap[node] = symbol;
            }
            else
            {
                std::cout << "SymbolTable::ReadMaps: warning: node-symbol map: symbol for id '" + util::ToString(symbolId) + "' not found" << "\n";
            }
        }
    }
    nrv = reader.GetBinaryStreamReader().ReadULEB128UInt();
    if (!nrv) return std::unexpected<int>(nrv.error());
    std::uint32_t nsn = *nrv;
#ifdef DEBUG_SYMBOL_IO
    std::cout << nsn << " symbol node map" << "\n";
#endif
    for (std::int32_t i = 0; i < static_cast<std::int32_t>(nsn); ++i)
    {
        util::uuid symbolId;
        std::expected<bool, int> rv = reader.GetBinaryStreamReader().ReadUuid(symbolId);
        if (!rv)  return rv;
        std::expected<std::int64_t, int> lrv = reader.GetBinaryStreamReader().ReadLong();
        if (!lrv) return std::unexpected<int>(lrv.error());
        std::int64_t nodeId = *lrv;
        if (nodeId != -1)
        {
            Symbol* symbol = symbolMap->GetSymbol(symbolId);
            if (symbol)
            {
                std::expected<otava::ast::Node*, int> n = nodeMap->GetNode(nodeId);
                if (!n) return std::unexpected<int>(n.error());
                otava::ast::Node* node = *n;
                symbolNodeMap[symbol] = node;
                allSymbolNodeMap[symbol] = node;
            }
            else
            {
                std::cout << "SymbolTable::ReadMaps: warning: symbol-node map: symbol for id '" + util::ToString(symbolId) + "' not found";
                std::cout << "\n";
            }
        }
    }
    nrv = reader.GetBinaryStreamReader().ReadULEB128UInt();
    if (!nrv) return std::unexpected<int>(nrv.error());
    std::uint32_t nfwd = *nrv;
#ifdef DEBUG_SYMBOL_IO
    std::cout << nfwd << " forward declarations" << "\n";
#endif
    for (std::int32_t i = 0; i < static_cast<std::int32_t>(nfwd); ++i)
    {
        util::uuid fwdId;
        std::expected<bool, int> rv = reader.GetBinaryStreamReader().ReadUuid(fwdId);
        if (!rv) return std::unexpected<int>(rv.error());
        std::expected<Symbol*, int> srv = symbolMap->GetSymbol(GetModule(), SymbolKind::null, fwdId);
        if (!srv) return std::unexpected<int>(srv.error());
        Symbol* symbol = *srv;
        forwardDeclarations.insert(symbol);
        allForwardDeclarations.insert(symbol);
    }
    nrv = reader.GetBinaryStreamReader().ReadULEB128UInt();
    if (!nrv) return std::unexpected<int>(nrv.error());
    std::uint32_t nspec = *nrv;
#ifdef DEBUG_SYMBOL_IO
    std::cout << nspec << " specifier node map" << "\n";
#endif
    for (std::int32_t i = 0; i < static_cast<std::int32_t>(nspec); ++i)
    {
        util::uuid symbolId;
        std::expected<bool, int> rv = reader.GetBinaryStreamReader().ReadUuid(symbolId);
        if (!rv) return std::unexpected<int>(rv.error());
        std::expected<std::int64_t, int> lrv = reader.GetBinaryStreamReader().ReadLong();
        if (!lrv) return std::unexpected<int>(lrv.error());
        std::int64_t nodeId = *lrv;
        std::expected<Symbol*, int> srv = symbolMap->GetSymbol(GetModule(), SymbolKind::null, symbolId);
        if (!srv) return std::unexpected<int>(srv.error());
        Symbol* symbol = *srv;
        std::expected<otava::ast::Node*, int> n = nodeMap->GetNode(nodeId);
        if (!n) return std::unexpected<int>(n.error());
        otava::ast::Node* node = *n;
        specifierNodeMap[symbol] = node;
        allSpecifierNodeMap[symbol] = node;
    }
    nrv = reader.GetBinaryStreamReader().ReadULEB128UInt();
    if (!nrv) return std::unexpected<int>(nrv.error());
    std::uint32_t nc = *nrv;
#ifdef DEBUG_SYMBOL_IO
    std::cout << nc << " classes " << "\n";
#endif
    for (std::int32_t i = 0; i < static_cast<std::int32_t>(nc); ++i)
    {
        util::uuid clsId;
        std::expected<bool, int> rv = reader.GetBinaryStreamReader().ReadUuid(clsId);
        if (!rv) return std::unexpected<int>(rv.error());
        std::expected<Symbol*, int> srv = symbolMap->GetSymbol(GetModule(), SymbolKind::null, clsId);
        if (!srv) return std::unexpected<int>(srv.error());
        Symbol* symbol = *srv;
        if (symbol->IsClassTypeSymbol())
        {
            classes.insert(static_cast<ClassTypeSymbol*>(symbol));
            allClasses.insert(static_cast<ClassTypeSymbol*>(symbol));
        }
    }
#ifdef DEBUG_SYMBOL_IO
    std::cout << "<read maps " << GetModule()->Name() << "\n";
#endif
    return std::expected<bool, int>(true);
}

std::expected<bool, int> SymbolTable::Write(Writer& writer, Context* context)
{
    if (module->Name() == "std.type.fundamental")
    {
        int n = templateParameterIds.size();
        std::expected<bool, int> rv = writer.GetBinaryStreamWriter().Write(static_cast<std::uint8_t>(n));
        if (!rv) return rv;
        for (int i = 0; i < n; ++i)
        {
            rv = writer.GetBinaryStreamWriter().Write(templateParameterIds[i]);
            if (!rv) return rv;
        }
        int cn = compoundTypeIds.size();
        rv = writer.GetBinaryStreamWriter().Write(cn);
        if (!rv) return rv;
        for (int i = 0; i < cn; ++i)
        {
            rv = writer.GetBinaryStreamWriter().Write(compoundTypeIds[i]);
            if (!rv) return rv;
        }
        int ln = levelIds.size();
        rv = writer.GetBinaryStreamWriter().Write(static_cast<std::uint8_t>(ln));
        if (!rv) return rv;
        for (int i = 0; i < ln; ++i)
        {
            rv = writer.GetBinaryStreamWriter().Write(levelIds[i]);
            if (!rv) return rv;
        }
    }
    std::expected<bool, int> rv = globalNs->Write(writer);
    if (!rv) return rv;
    std::uint32_t scount = classTemplateSpecializations.size();
    rv = writer.GetBinaryStreamWriter().WriteULEB128UInt(scount);
    if (!rv) return rv;
    for (const auto& specialization : classTemplateSpecializations)
    {
        rv = writer.Write(specialization.get());
        if (!rv) return rv;
    }
    std::uint32_t cscount = changedClassTemplateSpecializations.size();
    rv = writer.GetBinaryStreamWriter().WriteULEB128UInt(cscount);
    if (!rv) return rv;
    for (ClassTemplateSpecializationSymbol* specialization : changedClassTemplateSpecializations)
    {
        rv = writer.Write(specialization);
        if (!rv) return rv;
    }
    std::uint32_t acount = aliasTypeTemplateSpecializations.size();
    rv = writer.GetBinaryStreamWriter().WriteULEB128UInt(acount);
    if (!rv) return rv;
    for (const auto& specialization : aliasTypeTemplateSpecializations)
    {
        rv = writer.Write(specialization.get());
        if (!rv) return rv;
    }
    std::uint32_t arrayCount = arrayTypes.size();
    rv = writer.GetBinaryStreamWriter().WriteULEB128UInt(arrayCount);
    if (!rv) return rv;
    for (const auto& arrayType : arrayTypes)
    {
        rv = writer.Write(arrayType.get());
        if (!rv) return rv;
    }
    std::uint32_t dependentTypeCount = dependentTypeSymbols.size();
    rv = writer.GetBinaryStreamWriter().WriteULEB128UInt(dependentTypeCount);
    if (!rv) return rv;
    for (const auto& dependentType : dependentTypeSymbols)
    {
        rv = writer.Write(dependentType.get());
        if (!rv) return rv;
    }
    std::vector<CompoundTypeSymbol*> exportCompoundTypes;
    for (const auto& compoundType : compoundTypes)
    {
        if (compoundType->IsExportSymbol(context))
        {
            exportCompoundTypes.push_back(compoundType.get());
        }
    }
    std::uint32_t ccount = exportCompoundTypes.size();
    rv = writer.GetBinaryStreamWriter().WriteULEB128UInt(ccount);
    if (!rv) return rv;
    for (auto compoundType : exportCompoundTypes)
    {
        rv = writer.Write(compoundType);
        if (!rv) return rv;
    }
    std::uint32_t ecount = explicitInstantiations.size();
    rv = writer.GetBinaryStreamWriter().WriteULEB128UInt(ecount);
    if (!rv) return rv;
    for (const auto& explicitInstantiation : explicitInstantiations)
    {
        rv = writer.Write(explicitInstantiation.get());
        if (!rv) return rv;
    }
    std::uint32_t fcount = functionGroupTypes.size();
    rv = writer.GetBinaryStreamWriter().WriteULEB128UInt(fcount);
    if (!rv) return rv;
    for (const auto& functionGroupType : functionGroupTypes)
    {
        rv = writer.Write(functionGroupType.get());
        if (!rv) return rv;
    }
    std::uint32_t ctcount = classGroupTypes.size();
    rv = writer.GetBinaryStreamWriter().WriteULEB128UInt(ctcount);
    if (!rv) return rv;
    for (const auto& classGroupType : classGroupTypes)
    {
        rv = writer.Write(classGroupType.get());
        if (!rv) return rv;
    }
    std::uint32_t atcount = aliasGroupTypes.size();
    rv = writer.GetBinaryStreamWriter().WriteULEB128UInt(atcount);
    if (!rv) return rv;
    for (const auto& aliasGroupType : aliasGroupTypes)
    {
        rv = writer.Write(aliasGroupType.get());
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> SymbolTable::Read(Reader& reader)
{
    Context context;
    context.SetFunctionDefinitionSymbolSet(reader.GetFunctionDefinitionSymbolSet());
    context.SetSymbolTable(this);
    reader.SetContext(&context);
    if (module->Name() == "std.type.fundamental")
    {
        templateParameterIds.clear();
        std::expected<std::uint8_t, int> brv = reader.GetBinaryStreamReader().ReadByte();
        if (!brv) return std::unexpected<int>(brv.error());
        int n = *brv;
        for (int i = 0; i < n; ++i)
        {
            util::uuid id;
            std::expected<bool, int> rv = reader.GetBinaryStreamReader().ReadUuid(id);
            if (!rv) return rv;
            templateParameterIds.push_back(id);
        }
        compoundTypeIds.clear();
        std::expected<std::int32_t, int> i = reader.GetBinaryStreamReader().ReadInt();
        if (!i) return std::unexpected<int>(i.error());
        int cn = *i;
        for (int i = 0; i < cn; ++i)
        {
            util::uuid id;
            std::expected<bool, int> rv = reader.GetBinaryStreamReader().ReadUuid(id);
            if (!rv) return rv;
            compoundTypeIds.push_back(id);
        }
        levelIds.clear();
        brv = reader.GetBinaryStreamReader().ReadByte();
        if (!brv) return std::unexpected<int>(brv.error());
        int ln = *brv;
        for (int i = 0; i < ln; ++i)
        {
            util::uuid id;
            std::expected<bool, int> rv = reader.GetBinaryStreamReader().ReadUuid(id);
            if (!rv) return rv;
            levelIds.push_back(id);
        }
    }
    std::expected<bool, int> rv = globalNs->Read(reader);
    if (!rv) return rv;
    std::expected<std::uint32_t, int> urv = reader.GetBinaryStreamReader().ReadULEB128UInt();
    if (!urv) return std::unexpected<int>(urv.error());
    std::uint32_t scount = *urv;
    for (std::int32_t i = 0; i < static_cast<std::int32_t>(scount); ++i)
    {
        std::expected<Symbol*, int> srv = reader.ReadSymbol();
        if (!srv) return std::unexpected<int>(srv.error());
        Symbol* symbol = *srv;
        if (symbol->IsClassTemplateSpecializationSymbol())
        {
            ClassTemplateSpecializationSymbol* specialization = static_cast<ClassTemplateSpecializationSymbol*>(symbol);
            classTemplateSpecializations.push_back(std::unique_ptr<Symbol>(specialization));
        }
        else
        {
            return std::unexpected<int>(util::AllocateError("otava.symbols.symbol_table: class template specialization expected"));
        }
    }
    urv = reader.GetBinaryStreamReader().ReadULEB128UInt();
    if (!urv) return std::unexpected<int>(urv.error());
    std::uint32_t cscount = *urv;
    for (std::int32_t i = 0; i < static_cast<std::int32_t>(cscount); ++i)
    {
        std::expected<Symbol*, int> srv = reader.ReadSymbol();
        if (!srv) return std::unexpected<int>(srv.error());
        Symbol* symbol = *srv;
        if (symbol->IsClassTemplateSpecializationSymbol())
        {
            ClassTemplateSpecializationSymbol* specialization = static_cast<ClassTemplateSpecializationSymbol*>(symbol);
            classTemplateSpecializations.push_back(std::unique_ptr<Symbol>(specialization));
        }
        else
        {
            return std::unexpected<int>(util::AllocateError("otava.symbols.symbol_table: class template specialization expected"));
        }
    }
    urv = reader.GetBinaryStreamReader().ReadULEB128UInt();
    if (!urv) return std::unexpected<int>(urv.error());
    std::uint32_t acount = *urv;
    for (std::int32_t i = 0; i < static_cast<std::int32_t>(acount); ++i)
    {
        std::expected<Symbol*, int> srv = reader.ReadSymbol();
        if (!srv) return std::unexpected<int>(srv.error());
        Symbol* symbol = *srv;
        if (symbol->IsAliasTypeTemplateSpecializationSymbol())
        {
            AliasTypeTemplateSpecializationSymbol* specialization = static_cast<AliasTypeTemplateSpecializationSymbol*>(symbol);
            aliasTypeTemplateSpecializations.push_back(std::unique_ptr<Symbol>(specialization));
        }
        else
        {
            return std::unexpected<int>(util::AllocateError("otava.symbols.symbol_table: alias type template specialization expected"));
        }
    }
    urv = reader.GetBinaryStreamReader().ReadULEB128UInt();
    if (!urv) return std::unexpected<int>(urv.error());
    std::uint32_t arrayCount = *urv;
    for (std::int32_t i = 0; i < static_cast<std::int32_t>(arrayCount); ++i)
    {
        std::expected<Symbol*, int> srv = reader.ReadSymbol();
        if (!srv) return std::unexpected<int>(srv.error());
        Symbol* symbol = *srv;
        if (symbol->IsArrayTypeSymbol())
        {
            ArrayTypeSymbol* arrayTypeSymbol = static_cast<ArrayTypeSymbol*>(symbol);
            arrayTypes.push_back(std::unique_ptr<Symbol>(arrayTypeSymbol));
        }
        else
        {
            return std::unexpected<int>(util::AllocateError("otava.symbols.symbol_table: array type expected"));
        }
    }
    urv = reader.GetBinaryStreamReader().ReadULEB128UInt();
    if (!urv) return std::unexpected<int>(urv.error());
    std::uint32_t dependentTypeCount = *urv;
    for (std::int32_t i = 0; i < static_cast<std::int32_t>(dependentTypeCount); ++i)
    {
        std::expected<Symbol*, int> srv = reader.ReadSymbol();
        if (!srv) return std::unexpected<int>(srv.error());
        Symbol* symbol = *srv;
        if (symbol->IsDependentTypeSymbol())
        {
            DependentTypeSymbol* dependentTypeSymbol = static_cast<DependentTypeSymbol*>(symbol);
            dependentTypeSymbols.push_back(std::unique_ptr<DependentTypeSymbol>(dependentTypeSymbol));
        }
        else
        {
            return std::unexpected<int>(util::AllocateError("otava.symbols.symbol_table: dependent type expected"));
        }
    }
    urv = reader.GetBinaryStreamReader().ReadULEB128UInt();
    if (!urv) return std::unexpected<int>(urv.error());
    std::uint32_t ccount = *urv;
    for (std::int32_t i = 0; i < static_cast<std::int32_t>(ccount); ++i)
    {
        std::expected<Symbol*, int> srv = reader.ReadSymbol();
        if (!srv) return std::unexpected<int>(srv.error());
        Symbol* symbol = *srv;
        if (symbol->IsCompoundTypeSymbol())
        {
            CompoundTypeSymbol* compoundType = static_cast<CompoundTypeSymbol*>(symbol);
            compoundTypes.push_back(std::unique_ptr<CompoundTypeSymbol>(compoundType));
        }
        else
        {
            return std::unexpected<int>(util::AllocateError("otava.symbols.symbol_table: compound type expected"));
        }
    }
    urv = reader.GetBinaryStreamReader().ReadULEB128UInt();
    if (!urv) return std::unexpected<int>(urv.error());
    std::uint32_t ecount = *urv;
    for (std::int32_t i = 0; i < static_cast<std::int32_t>(ecount); ++i)
    {
        std::expected<Symbol*, int> srv = reader.ReadSymbol();
        if (!srv) return std::unexpected<int>(srv.error());
        Symbol* symbol = *srv;
        if (symbol->IsExplicitInstantiationSymbol())
        {
            ExplicitInstantiationSymbol* explicitInstantiation = static_cast<ExplicitInstantiationSymbol*>(symbol);
            explicitInstantiations.push_back(std::unique_ptr<ExplicitInstantiationSymbol>(explicitInstantiation));
        }
        else
        {
            return std::unexpected<int>(util::AllocateError("otava.symbols.symbol_table: explicit instantiation symbol expected"));
        }
    }
    urv = reader.GetBinaryStreamReader().ReadULEB128UInt();
    if (!urv) return std::unexpected<int>(urv.error());
    std::uint32_t fcount = *urv;
    for (std::int32_t i = 0; i < static_cast<std::int32_t>(fcount); ++i)
    {
        std::expected<Symbol*, int> srv = reader.ReadSymbol();
        if (!srv) return std::unexpected<int>(srv.error());
        Symbol* symbol = *srv;
        if (symbol->IsFunctionGroupTypeSymbol())
        {
            FunctionGroupTypeSymbol* functionGroupType = static_cast<FunctionGroupTypeSymbol*>(symbol);
            functionGroupTypes.push_back(std::unique_ptr<FunctionGroupTypeSymbol>(functionGroupType));
        }
        else
        {
            return std::unexpected<int>(util::AllocateError("otava.symbols.symbol_table: function group type symbol expected"));
        }
    }
    urv = reader.GetBinaryStreamReader().ReadULEB128UInt();
    if (!urv) return std::unexpected<int>(urv.error());
    std::uint32_t ctcount = *urv;
    for (std::int32_t i = 0; i < static_cast<std::int32_t>(ctcount); ++i)
    {
        std::expected<Symbol*, int> srv = reader.ReadSymbol();
        if (!srv) return std::unexpected<int>(srv.error());
        Symbol* symbol = *srv;
        if (symbol->IsClassGroupTypeSymbol())
        {
            ClassGroupTypeSymbol* classGroupType = static_cast<ClassGroupTypeSymbol*>(symbol);
            classGroupTypes.push_back(std::unique_ptr<ClassGroupTypeSymbol>(classGroupType));
        }
        else
        {
            return std::unexpected<int>(util::AllocateError("otava.symbols.symbol_table: class group type symbol expected"));
        }
    }
    urv = reader.GetBinaryStreamReader().ReadULEB128UInt();
    if (!urv) return std::unexpected<int>(urv.error());
    std::uint32_t atcount = *urv;
    for (std::int32_t i = 0; i < static_cast<std::int32_t>(atcount); ++i)
    {
        std::expected<Symbol*, int> srv = reader.ReadSymbol();
        if (!srv) return std::unexpected<int>(srv.error());
        Symbol* symbol = *srv;
        if (symbol->IsAliasGroupTypeSymbol())
        {
            AliasGroupTypeSymbol* aliasGroupType = static_cast<AliasGroupTypeSymbol*>(symbol);
            aliasGroupTypes.push_back(std::unique_ptr<AliasGroupTypeSymbol>(aliasGroupType));
        }
        else
        {
            return std::unexpected<int>(util::AllocateError("otava.symbols.symbol_table: class group type symbol expected"));
        }
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> SymbolTable::Resolve(Context* context)
{
    for (auto& specialization : classTemplateSpecializations)
    {
        MapClassTemplateSpecialization(static_cast<ClassTemplateSpecializationSymbol*>(specialization.get()));
    }
    for (auto& specialization : aliasTypeTemplateSpecializations)
    {
        MapType(static_cast<TypeSymbol*>(specialization.get()));
    }
    for (auto& compoundType : compoundTypes)
    {
        MapCompoundType(compoundType.get());
    }
    for (auto& arrayType : arrayTypes)
    {
        MapType(static_cast<TypeSymbol*>(arrayType.get()));
    }
    for (ClassTypeSymbol* cls : classes)
    {
        MapType(static_cast<TypeSymbol*>(cls));
    }
    for (auto& dependentTypeSymbol : dependentTypeSymbols)
    {
        MapType(static_cast<TypeSymbol*>(dependentTypeSymbol.get()));
    }
    std::expected<bool, int> rv = globalNs->Resolve(*this, context);
    if (!rv) return rv;
    for (const auto& specialization : classTemplateSpecializations)
    {
        if (specialization->Kind() == SymbolKind::classTemplateSpecializationSymbol)
        {
            ClassTemplateSpecializationSymbol* s = static_cast<ClassTemplateSpecializationSymbol*>(specialization.get());
            rv = s->Resolve(*this, context);
            if (!rv) return rv;
        }
        else
        {
            return Error("class template specialization expected", soul::ast::SourcePos(), context);
        }
    }
    for (const auto& specialization : aliasTypeTemplateSpecializations)
    {
        if (specialization->Kind() == SymbolKind::aliasTypeTemplateSpecializationSymbol)
        {
            AliasTypeTemplateSpecializationSymbol* s = static_cast<AliasTypeTemplateSpecializationSymbol*>(specialization.get());
            rv = s->Resolve(*this, context);
            if (!rv) return rv;
        }
        else
        {
            return Error("alias type template specialization expected", soul::ast::SourcePos(), context);
        }
    }
    for (const auto& arrayType : arrayTypes)
    {
        ArrayTypeSymbol* a = static_cast<ArrayTypeSymbol*>(arrayType.get());
        rv = a->Resolve(*this, context);
        if (!rv) return rv;
    }
    for (const auto& instantiation : explicitInstantiations)
    {
        rv = instantiation->Resolve(*this, context);
        if (!rv) return rv;
    }
    for (auto& compoundType : compoundTypes)
    {
        rv = compoundType->Resolve(*this, context);
        if (!rv) return rv;
    }
    rv = conversionTable->Make();
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<Symbol*, int> SymbolTable::Lookup(const std::u32string& name, SymbolGroupKind symbolGroupKind, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<Symbol*, int> lrv = Lookup(name, symbolGroupKind, sourcePos, context, LookupFlags::none);
    if (!lrv) return lrv;
    Symbol* symbol = *lrv;
    if (!symbol)
    {
        lrv = LookupInScopeStack(name, symbolGroupKind, sourcePos, context, LookupFlags::none);
        if (!lrv) return lrv;
        symbol = *lrv;
    }
    return std::expected<Symbol*, int>(symbol);
}

std::expected<Symbol*, int> SymbolTable::LookupInScopeStack(const std::u32string& name, SymbolGroupKind symbolGroupKind, const soul::ast::SourcePos& sourcePos, 
    Context* context, LookupFlags flags)
{
    if (topScopeIndex == -1) return std::expected<Symbol*, int>(nullptr);
    for (int i = scopeStack.size() - 1; i >= topScopeIndex; --i)
    {
        Scope* scope = scopeStack[i];
        std::expected<Symbol*, int> lrv = scope->Lookup(name, symbolGroupKind, ScopeLookup::allScopes, sourcePos, context, flags);
        if (!lrv) return lrv;
        Symbol* symbol = *lrv;
        if (symbol)
        {
            return std::expected<Symbol*, int>(symbol);
        }
    }
    return std::expected<Symbol*, int>(nullptr);
}

std::expected<Symbol*, int> SymbolTable::Lookup(const std::u32string& name, SymbolGroupKind symbolGroupKind, const soul::ast::SourcePos& sourcePos, 
    Context* context, LookupFlags flags)
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

void SymbolTable::ResolveForwardDeclarations()
{
    std::vector<Symbol*> resolvedFwdDeclarations;
    for (Symbol* symbol : allForwardDeclarations)
    {
        if (symbol->IsForwardDeclarationSymbol())
        {
            ForwardClassDeclarationSymbol* forwardDeclaration = static_cast<ForwardClassDeclarationSymbol*>(symbol);
            Symbol* group = LookupSymbol(forwardDeclaration);
            if (group)
            {
                if (group->IsClassGroupSymbol())
                {
                    ClassGroupSymbol* classGroupSymbol = static_cast<ClassGroupSymbol*>(group);
                    ClassTypeSymbol* classTypeSymbol = classGroupSymbol->GetClass(forwardDeclaration->Arity());
                    if (classTypeSymbol)
                    {
                        forwardDeclaration->SetClassTypeSymbol(classTypeSymbol);
                        resolvedFwdDeclarations.push_back(forwardDeclaration);
                    }
                }
            }
        }
    }
    for (Symbol* symbol : resolvedFwdDeclarations)
    {
        forwardDeclarations.erase(symbol);
        allForwardDeclarations.erase(symbol);
    }
}

std::expected<bool, int> SymbolTable::CollectViableFunctions(const std::vector<std::pair<Scope*, ScopeLookup>>& scopeLookups, const std::u32string& groupName, 
    const std::vector<TypeSymbol*>& templateArgs, int arity, std::vector<FunctionSymbol*>& viableFunctions, Context* context)
{
    std::vector<Symbol*> symbols;
    std::set<Scope*> visited;
    for (const std::pair<Scope*, ScopeLookup>& s : scopeLookups)
    {
        Scope* scope = s.first;
        ScopeLookup lookup = s.second;
        scope->Lookup(groupName, SymbolGroupKind::functionSymbolGroup, lookup, LookupFlags::dontResolveSingle | LookupFlags::all, symbols, visited, context);
        Scope* scp = scope;
        Scope* classScope = scp->GetClassScope();
        if (classScope)
        {
            Symbol* symbol = classScope->GetSymbol();
            if (symbol->IsClassTemplateSpecializationSymbol())
            {
                ClassTemplateSpecializationSymbol* specialization = static_cast<ClassTemplateSpecializationSymbol*>(symbol);
                scp = specialization->ClassTemplate()->GetScope();
            }
        }
        if (scp != scope)
        {
            scp->Lookup(groupName, SymbolGroupKind::functionSymbolGroup, lookup, LookupFlags::dontResolveSingle | LookupFlags::all, symbols, visited, context);
        }
    }
    for (Symbol* symbol : symbols)
    {
        if (symbol->IsFunctionGroupSymbol())
        {
            FunctionGroupSymbol* functionGroup = static_cast<FunctionGroupSymbol*>(symbol);
            std::expected<bool, int> m = functionGroup->CollectViableFunctions(arity, templateArgs, viableFunctions, context);
            if (!m) return m;
        }
    }
    return std::expected<bool, int>(true);
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
    if (!node) return;
    if (!symbol) return;
    Symbol* prevSymbol = nullptr;
    if (symbol->IsFunctionSymbol() && !symbol->IsFunctionDefinitionSymbol())
    {
        prevSymbol = GetSymbolNothrow(node);
    }
    if ((kind & MapKind::nodeToSymbol) != MapKind::none)
    {
        if (!prevSymbol)
        {
            nodeSymbolMap[node] = symbol;
            allNodeSymbolMap[node] = symbol;
        }
    }
    if ((kind & MapKind::symbolToNode) != MapKind::none)
    {
        symbolNodeMap[symbol] = node;
        allSymbolNodeMap[symbol] = node;
    }
    if (symbol->Parent() && symbol->Parent()->IsClassTemplateSpecializationSymbol())
    {
        ClassTemplateSpecializationSymbol* specialization = static_cast<ClassTemplateSpecializationSymbol*>(symbol->Parent());
        specialization->SetProject();
        AddChangedClassTemplateSpecialization(specialization);
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

std::expected<otava::ast::Node*, int> SymbolTable::GetNode(Symbol* symbol) const
{
    otava::ast::Node* node = GetNodeNothrow(symbol);
    if (node)
    {
        return std::expected<otava::ast::Node*, int>(node);
    }
    else
    {
        std::expected<std::string, int> sname = util::ToUtf8(symbol->Name());
        if (!sname) return std::unexpected<int>(sname.error());
        return std::unexpected<int>(util::AllocateError("node for symbol '" + *sname + "' not found"));
    }
}

void SymbolTable::RemoveNode(otava::ast::Node* node)
{
    //if (ProjectReady() || soul::lexer::parsing_error_thrown || ExceptionThrown() || otava::ast::ExceptionThrown() || otava::intermediate::ExceptionThrown()) return; TODO
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

void SymbolTable::RemoveSymbol(Symbol* symbol)
{
    //if (ProjectReady() || soul::lexer::parsing_error_thrown || ExceptionThrown() || otava::ast::ExceptionThrown() || otava::intermediate::ExceptionThrown()) return; TODO
    otava::ast::Node* node = nullptr;
    auto it = symbolNodeMap.find(symbol);
    if (it != symbolNodeMap.end())
    {
        node = it->second;
        symbolNodeMap.erase(symbol);
    }
    if (node)
    {
        nodeSymbolMap.erase(node);
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

std::expected<Symbol*, int> SymbolTable::GetSymbol(otava::ast::Node* node) const
{
    Symbol* symbol = GetSymbolNothrow(node);
    if (symbol)
    {
        return symbol;
    }
    else
    {
        return std::unexpected<int>(util::AllocateError("symbol for node not found"));
    }
}

TypeSymbol* SymbolTable::GetTypeNoThrow(const util::uuid& id) const
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
    TypeSymbol* type = GetTypeNoThrow(id);
    if (type)
    {
        return type;
    }
    else
    {
        std::cout << "SymbolTable::GetType(): warning: type for id '" + util::ToString(id) + "' not found" << "\n";
    }
    return nullptr;
}

void SymbolTable::MapType(TypeSymbol* type)
{
    typeMap[type->Id()] = type;
}

void SymbolTable::UnmapType(TypeSymbol* type)
{
    auto it = symbolNodeMap.find(static_cast<Symbol*>(type));
    if (it != symbolNodeMap.end())
    {
        otava::ast::Node* node = it->second;
        nodeSymbolMap.erase(node);
    }
    symbolNodeMap.erase(static_cast<Symbol*>(type));
    typeMap.erase(type->Id());
}

std::expected<VariableSymbol*, int> SymbolTable::AddVariable(const std::u32string& name, otava::ast::Node* node, TypeSymbol* declaredType, 
    TypeSymbol* initializerType, Value* value, DeclarationFlags flags, Context* context)
{
    std::expected<VariableGroupSymbol*, int> v = currentScope->GroupScope()->GetOrInsertVariableGroup(name, node->GetSourcePos(), context);
    if (!v) return std::unexpected<int>(v.error());
    VariableGroupSymbol* variableGroup = *v;
    VariableSymbol* variableSymbol = new VariableSymbol(name);
    variableSymbol->SetAccess(CurrentAccess());
    variableSymbol->SetDeclaredType(declaredType);
    variableSymbol->SetInitializerType(initializerType);
    variableSymbol->SetValue(value);
    variableSymbol->SetDeclarationFlags(flags);
    std::expected<bool, int> rv = currentScope->SymbolScope()->AddSymbol(variableSymbol, node->GetSourcePos(), context);
    if (!rv) return std::unexpected<int>(rv.error());
    variableGroup->AddVariable(variableSymbol);
    return std::expected<VariableSymbol*, int>(variableSymbol);
}

std::expected<AliasTypeSymbol*, int> SymbolTable::AddAliasType(otava::ast::Node* idNode, otava::ast::Node* aliasTypeNode, TypeSymbol* type, Context* context)
{
    std::u32string id = idNode->Str();
    std::expected<AliasGroupSymbol*, int> a = currentScope->GroupScope()->GetOrInsertAliasGroup(id, idNode->GetSourcePos(), context);
    if (!a) return std::unexpected<int>(a.error());
    AliasGroupSymbol* aliasGroup = *a;
    AliasTypeSymbol* aliasTypeSymbol = new AliasTypeSymbol(id, type);
    aliasTypeSymbol->SetAccess(currentAccess);
    std::expected<bool, int> rv = currentScope->SymbolScope()->AddSymbol(aliasTypeSymbol, idNode->GetSourcePos(), context);
    if (!rv) return std::unexpected<int>(rv.error());
    aliasGroup->AddAliasTypeSymbol(aliasTypeSymbol, context);
    MapNode(aliasTypeNode, aliasTypeSymbol);
    return std::expected<AliasTypeSymbol*, int>(aliasTypeSymbol);
}

std::expected<bool, int> SymbolTable::AddUsingDeclaration(otava::ast::Node* node, Symbol* symbol, Context* context)
{
    std::expected<bool, int> rv = currentScope->SymbolScope()->AddUsingDeclaration(symbol, node->GetSourcePos(), context);
    if (!rv) return rv;
    MapNode(node, symbol, MapKind::nodeToSymbol);
    return std::expected<bool, int>(true);
}

std::expected<bool, int> SymbolTable::AddUsingDirective(NamespaceSymbol* ns, otava::ast::Node* node, Context* context)
{
    std::expected<bool, int> rv = currentScope->SymbolScope()->AddUsingDirective(ns, node->GetSourcePos(), context);
    if (!rv) return rv;
    MapNode(node, ns, MapKind::nodeToSymbol);
    return std::expected<bool, int>(true);
}

std::expected<bool, int> SymbolTable::BeginNamespace(const std::u32string& name, otava::ast::Node* node, Context* context)
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
        std::expected<Symbol*, int> s = currentScope->Lookup(name, SymbolGroupKind::typeSymbolGroup, ScopeLookup::thisScope, sourcePos, 
            context, LookupFlags::dontResolveSingle);
        if (!s)
        {
            return std::unexpected<int>(s.error());
        }
        Symbol* symbol = *s;
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
                return std::expected<bool, int>(true);
            }
            else
            {
                std::expected<std::string, int> n = util::ToUtf8(name);
                if (!n) return std::unexpected<int>(n.error());
                return Error("name of namespace '" + *n + " conflicts with earlier declaration", sourcePos, context);
            }
        }
        NamespaceSymbol* namespaceSymbol = new NamespaceSymbol(name);
        if (node)
        {
            MapNode(node, namespaceSymbol);
        }
        std::expected<bool, int> rv = currentScope->SymbolScope()->AddSymbol(namespaceSymbol, sourcePos, context);
        if (!rv)
        {
            return rv;
        }
        BeginScope(namespaceSymbol->GetScope());
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> SymbolTable::EndNamespace()
{
    return EndScope();
}

std::expected<bool, int> SymbolTable::BeginNamespace(otava::ast::Node* node, Context* context)
{
    return BeginNamespace(node->Str(), node, context);
}

std::expected<bool, int> SymbolTable::EndNamespace(int level)
{
    for (int i = 0; i < level; ++i)
    {
        std::expected<bool, int>  rv = EndNamespace();
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> SymbolTable::BeginClass(const std::u32string& name, ClassKind classKind, TypeSymbol* specialization, otava::ast::Node* node, Context* context)
{
    std::expected<Symbol*, int> s = currentScope->Lookup(name, SymbolGroupKind::typeSymbolGroup, ScopeLookup::thisScope, node->GetSourcePos(), 
        context, LookupFlags::dontResolveSingle);
    if (!s) return std::unexpected<int>(s.error());
    Symbol* symbol = *s;
    std::expected<ClassGroupSymbol*, int> c = currentScope->GroupScope()->GetOrInsertClassGroup(name, node->GetSourcePos(), context);
    if (!c) return std::unexpected<int>(c.error());
    ClassGroupSymbol* classGroup = *c;
    ClassTypeSymbol* classTypeSymbol = new ClassTypeSymbol(name);
    classTypeSymbol->SetLevel(classLevel++);
    AddClass(classTypeSymbol);
    classTypeSymbol->SetAccess(CurrentAccess());
    classTypeSymbol->SetClassKind(classKind);
    classTypeSymbol->SetSpecialization(specialization, context);
    std::expected<bool, int> rv = currentScope->SymbolScope()->AddSymbol(classTypeSymbol, node->GetSourcePos(), context);
    if (!rv) return rv;
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
    return std::expected<bool, int>(true);
}

std::expected<bool, int> SymbolTable::AddBaseClass(ClassTypeSymbol* baseClass, const soul::ast::SourcePos& sourcePos, Context* context)
{
    Symbol* symbol = currentScope->GetSymbol();
    if (symbol->IsClassTypeSymbol())
    {
        ClassTypeSymbol* classTypeSymbol = static_cast<ClassTypeSymbol*>(symbol);
        std::expected<bool, int> rv = classTypeSymbol->AddBaseClass(baseClass, sourcePos, context);
        if (!rv) return rv;
    }
    else
    {
        return Error("class type symbol expected", sourcePos, context);
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> SymbolTable::EndClass()
{
    --classLevel;
    PopAccess();
    return EndScope();
}

std::expected<bool, int> SymbolTable::AddForwardClassDeclaration(const std::u32string& name, ClassKind classKind, TypeSymbol* specialization, 
    otava::ast::Node* node, Context* context)
{
    std::expected<Symbol*, int> s = currentScope->Lookup(name, SymbolGroupKind::typeSymbolGroup, ScopeLookup::thisScope, node->GetSourcePos(), 
        context, LookupFlags::dontResolveSingle);
    if (!s) return std::unexpected<int>(s.error());
    Symbol* symbol = *s;
    std::expected<ClassGroupSymbol*, int> c = currentScope->GroupScope()->GetOrInsertClassGroup(name, node->GetSourcePos(), context);
    if (!c) return std::unexpected<int>(c.error());
    ClassGroupSymbol* classGroup = *c;
    std::unique_ptr<ForwardClassDeclarationSymbol> forwardDeclarationSymbol(new ForwardClassDeclarationSymbol(name));
    forwardDeclarationSymbol->SetAccess(CurrentAccess());
    forwardDeclarationSymbol->SetClassKind(classKind);
    forwardDeclarationSymbol->SetSpecialization(specialization);
    forwardDeclarationSymbol->SetParent(currentScope->SymbolScope()->GetSymbol());
    ForwardClassDeclarationSymbol* fwdDeclaration = classGroup->GetForwardDeclaration(forwardDeclarationSymbol->Arity());
    if (!fwdDeclaration)
    {
        Symbol* s = forwardDeclarationSymbol.get();
        classGroup->AddForwardDeclaration(forwardDeclarationSymbol.get());
        MapNode(node, s);
        forwardDeclarations.insert(s);
        allForwardDeclarations.insert(s);
        std::expected<bool, int> rv = currentScope->SymbolScope()->AddSymbol(static_cast<Symbol*>(forwardDeclarationSymbol.release()), node->GetSourcePos(), context);
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> SymbolTable::AddFriend(const std::u32string& name, otava::ast::Node* node, Context* context)
{
    FriendSymbol* friendSymbol = new FriendSymbol(name);
    std::expected<bool, int> rv = currentScope->SymbolScope()->AddSymbol(friendSymbol, node->GetSourcePos(), context);
    if (!rv) return rv;
    MapNode(node, friendSymbol);
    return std::expected<bool, int>(true);
}

std::expected<bool, int> SymbolTable::BeginEnumeratedType(const std::u32string& name, EnumTypeKind kind, TypeSymbol* underlyingType, otava::ast::Node* node, 
    Context* context)
{
    std::expected<EnumGroupSymbol*, int> e = currentScope->GroupScope()->GetOrInsertEnumGroup(name, node->GetSourcePos(), context);
    if (!e) return std::unexpected<int>(e.error());
    EnumGroupSymbol* enumGroup = *e;
    EnumeratedTypeSymbol* enumType = enumGroup->GetEnumType();
    if (enumType)
    {
        std::expected<std::string, int> n = util::ToUtf8(name);
        if (!n) return std::unexpected<int>(n.error());
        return Error("enumerated type '" + *n + "' not unique", node->GetSourcePos(), context);
    }
    EnumeratedTypeSymbol* enumTypeSymbol = new EnumeratedTypeSymbol(name);
    enumTypeSymbol->SetAccess(CurrentAccess());
    enumTypeSymbol->SetEnumTypeKind(kind);
    enumTypeSymbol->SetUnderlyingType(underlyingType);
    std::expected<bool, int> rv = currentScope->SymbolScope()->AddSymbol(enumTypeSymbol, node->GetSourcePos(), context);
    if (!rv) return rv;
    MapNode(node, enumTypeSymbol);
    enumGroup->SetEnumType(enumTypeSymbol);
    BeginScope(enumTypeSymbol->GetScope());
    return std::expected<bool, int>(true);
}

std::expected<bool, int> SymbolTable::EndEnumeratedType()
{
    return EndScope();
}

std::expected<bool, int> SymbolTable::AddForwardEnumDeclaration(const std::u32string& name, EnumTypeKind enumTypeKind, TypeSymbol* underlyingType, 
    otava::ast::Node* node, Context* context)
{
    std::expected<EnumGroupSymbol*, int> e = currentScope->GroupScope()->GetOrInsertEnumGroup(name, node->GetSourcePos(), context);
    if (!e) return std::unexpected<int>(e.error());
    EnumGroupSymbol* enumGroup = *e;
    if (enumGroup->GetForwardDeclaration())
    {
        return std::expected<bool, int>(false);
    }
    ForwardEnumDeclarationSymbol* forwardDeclarationSymbol = new ForwardEnumDeclarationSymbol(name);
    forwardDeclarationSymbol->SetAccess(CurrentAccess());
    forwardDeclarationSymbol->SetEnumTypeKind(enumTypeKind);
    forwardDeclarationSymbol->SetUnderlyingType(underlyingType);
    std::expected<bool, int> rv = currentScope->SymbolScope()->AddSymbol(forwardDeclarationSymbol, node->GetSourcePos(), context);
    if (!rv) return rv;
    enumGroup->SetForwardDeclaration(forwardDeclarationSymbol);
    Symbol* s = forwardDeclarationSymbol;
    MapNode(node, s);
    forwardDeclarations.insert(s);
    allForwardDeclarations.insert(s);
    return std::expected<bool, int>(true);
}

std::expected<bool, int> SymbolTable::AddEnumerator(const std::u32string& name, Value* value, otava::ast::Node* node, Context* context)
{
    EnumeratedTypeSymbol* enumTypeSymbol = nullptr;
    Scope* scope = currentScope->SymbolScope();
    if (scope->IsContainerScope())
    {
        ContainerScope* containerScope = static_cast<ContainerScope*>(scope);
        if (containerScope)
        {
            ContainerSymbol* containerSymbol = containerScope->GetContainerSymbol();
            if (containerSymbol && containerSymbol->IsEnumeratedTypeSymbol())
            {
                enumTypeSymbol = static_cast<EnumeratedTypeSymbol*>(containerSymbol);
                EnumTypeKind kind = enumTypeSymbol->GetEnumTypeKind();
                if (kind == EnumTypeKind::enum_)
                {
                    scope = enumTypeSymbol->Parent()->GetScope();
                }
            }
        }
    }
    if (!enumTypeSymbol)
    {
        return Error("could not add enumerator to symbol table: enumerated type not found", node->GetSourcePos(), context);
    }
    EnumConstantSymbol* enumConstantSymbol = new EnumConstantSymbol(name);
    enumConstantSymbol->SetEnumType(enumTypeSymbol);
    enumConstantSymbol->SetValue(value);
    std::expected<bool, int> rv = scope->AddSymbol(enumConstantSymbol, node->GetSourcePos(), context);
    if (!rv) return rv;
    MapNode(node, enumConstantSymbol);
    return std::expected<bool, int>(true);
}

std::expected<BlockSymbol*, int> SymbolTable::BeginBlock(const soul::ast::SourcePos& sourcePos, Context* context)
{
    BlockSymbol* blockSymbol = new BlockSymbol();
    std::expected<bool, int> rv = currentScope->SymbolScope()->AddSymbol(blockSymbol, sourcePos, context);
    if (!rv) return std::unexpected<int>(rv.error());
    rv = BeginScopeGeneric(blockSymbol->GetScope(), context);
    if (!rv) return std::unexpected<int>(rv.error());
    return std::expected<BlockSymbol*, int>(blockSymbol);
}

std::expected<bool, int> SymbolTable::EndBlock(Context* context)
{
    return EndScopeGeneric(context);
}

std::expected<bool, int> SymbolTable::RemoveBlock()
{
    Symbol* symbol = currentScope->GetSymbol();
    if (symbol && symbol->IsBlockSymbol())
    {
        std::expected<bool, int> rv = EndScope();
        if (!rv) return rv;
        std::expected<std::unique_ptr<Symbol>, int> s = currentScope->RemoveSymbol(symbol);
        if (!s) return std::unexpected<int>(s.error());
    }
    else
    {
        return std::unexpected<int>(util::AllocateError("otava.symbols.symbol_table: block expected"));
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> SymbolTable::BeginTemplateDeclaration(otava::ast::Node* node, Context* context)
{
    TemplateDeclarationSymbol* templateDeclarationSymbol = new TemplateDeclarationSymbol();
    std::expected<bool, int> rv = currentScope->SymbolScope()->AddSymbol(templateDeclarationSymbol, node->GetSourcePos(), context);
    if (!rv) return rv;
    BeginScope(templateDeclarationSymbol->GetScope());
    return std::expected<bool, int>(true);
}

std::expected<bool, int> SymbolTable::EndTemplateDeclaration()
{
    return EndScope();
}

std::expected<bool, int> SymbolTable::RemoveTemplateDeclaration()
{
    Symbol* symbol = currentScope->GetSymbol();
    if (symbol && symbol->IsTemplateDeclarationSymbol())
    {
        std::expected<bool, int> rv = EndScope();
        if (!rv) return rv;
        std::expected<std::unique_ptr<Symbol>, int> s = currentScope->RemoveSymbol(symbol);
        if (!s) return std::unexpected<int>(s.error());
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> SymbolTable::AddTemplateParameter(const std::u32string& name, otava::ast::Node* node, Symbol* constraint, int index, ParameterSymbol* parameter,
    otava::ast::Node* defaultTemplateArgNode, Context* context)
{
    std::expected<util::uuid, int> i = GetTemplateParameterId(index);
    if (!i) return std::unexpected<int>(i.error());
    TemplateParameterSymbol* templateParameterSymbol = new TemplateParameterSymbol(constraint, name, *i, index, defaultTemplateArgNode);
    if (parameter)
    {
        std::expected<bool, int> rv = templateParameterSymbol->AddSymbol(parameter, node->GetSourcePos(), context);
        if (!rv) return rv;
    }
    std::expected<bool, int> rv = currentScope->SymbolScope()->AddSymbol(templateParameterSymbol, node->GetSourcePos(), context);
    if (!rv) return rv;
    MapNode(node, templateParameterSymbol);
    return std::expected<bool, int>(true);
}

std::expected<FunctionSymbol*, int> SymbolTable::AddFunction(const std::u32string& name, const std::vector<TypeSymbol*>& specialization, 
    otava::ast::Node* node, FunctionKind kind, FunctionQualifiers qualifiers, DeclarationFlags flags, Context* context)
{
    std::u32string groupName = name;
    if (kind == FunctionKind::constructor)
    {
        groupName = U"@constructor";
    }
    else if (kind == FunctionKind::destructor)
    {
        groupName = U"@destructor";
    }
    std::expected<FunctionGroupSymbol*, int> f = currentScope->GroupScope()->GetOrInsertFunctionGroup(groupName, node->GetSourcePos(), context);
    if (!f) return std::unexpected<int>(f.error());
    FunctionGroupSymbol* functionGroup = *f;
    FunctionSymbol* functionSymbol = new FunctionSymbol(name);
    functionSymbol->SetAccess(CurrentAccess());
    functionSymbol->SetFunctionKind(kind);
    functionSymbol->SetFunctionQualifiers(qualifiers);
    functionSymbol->SetLinkage(currentLinkage);
    functionSymbol->SetDeclarationFlags(flags);
    if (node) functionSymbol->SetSourcePos(node->GetSourcePos());
    if ((flags & (DeclarationFlags::inlineFlag | DeclarationFlags::constExprFlag)) != DeclarationFlags::none)
    {
        functionSymbol->SetInline();
    }
    functionSymbol->SetSpecialization(specialization);
    std::expected<bool, int> rv = currentScope->SymbolScope()->AddSymbol(functionSymbol, node->GetSourcePos(), context);
    if (!rv) return std::unexpected<int>(rv.error());
    functionGroup->AddFunction(functionSymbol);
    MapNode(node, functionSymbol);
    return std::expected<FunctionSymbol*, int>(functionSymbol);
}

std::expected<bool, int> SymbolTable::AddFunctionSymbol(Scope* scope, FunctionSymbol* functionSymbol, Context* context)
{
    std::expected<FunctionGroupSymbol*, int> f = currentScope->GroupScope()->GetOrInsertFunctionGroup(functionSymbol->GroupName(), soul::ast::SourcePos(), context);
    if (!f) return std::unexpected<int>(f.error());
    FunctionGroupSymbol* functionGroup = *f;
    functionSymbol->SetLinkage(currentLinkage);
    std::expected<bool, int> rv = scope->SymbolScope()->AddSymbol(functionSymbol, soul::ast::SourcePos(), context);
    if (!rv) return rv;
    functionGroup->AddFunction(functionSymbol);
    return std::expected<bool, int>(true);
}

std::expected<FunctionDefinitionSymbol*, int> SymbolTable::AddOrGetFunctionDefinition(Scope* scope, const std::u32string& name, 
    const std::vector<TypeSymbol*>& specialization, const std::vector<TypeSymbol*>& parameterTypes, FunctionQualifiers qualifiers, 
    FunctionKind kind, DeclarationFlags declarationFlags, otava::ast::Node* node, otava::ast::Node* functionNode, bool& get, Context* context)
{
    get = false;
    std::u32string groupName = name;
    Symbol* containerSymbol = scope->SymbolScope()->GetSymbol();
    if (containerSymbol && containerSymbol->SimpleName() == name)
    {
        kind = FunctionKind::constructor;
    }
    if (kind == FunctionKind::constructor)
    {
        groupName = U"@constructor";
    }
    else if (kind == FunctionKind::destructor)
    {
        groupName = U"@destructor";
    }
    std::expected<FunctionGroupSymbol*, int> f = scope->GroupScope()->GetOrInsertFunctionGroup(groupName, node->GetSourcePos(), context);
    if (!f) return std::unexpected<int>(f.error());
    FunctionGroupSymbol * functionGroup = *f;
    std::unique_ptr<FunctionDefinitionSymbol> functionDefinition(new FunctionDefinitionSymbol(name));
    functionDefinition->SetGroup(functionGroup);
    functionDefinition->SetDeclarationFlags(declarationFlags);
    if (context->GetFlag(ContextFlags::instantiateFunctionTemplate) ||
        context->GetFlag(ContextFlags::instantiateMemFnOfClassTemplate) ||
        context->GetFlag(ContextFlags::instantiateInlineFunction))
    {
        functionDefinition->SetSpecialization();
    }
    if ((declarationFlags & (DeclarationFlags::inlineFlag | DeclarationFlags::constExprFlag)) != DeclarationFlags::none)
    {
        functionDefinition->SetInline();
    }
    functionDefinition->SetLinkage(currentLinkage);
    functionDefinition->SetFunctionKind(kind);
    functionDefinition->SetFunctionQualifiers(qualifiers);
    functionDefinition->SetSpecialization(specialization);
    functionDefinition->SetParent(currentScope->SymbolScope()->GetSymbol());
    if (node) functionDefinition->SetSourcePos(node->GetSourcePos());
    int index = 0;
    for (TypeSymbol* parameterType : parameterTypes)
    {
        std::expected<bool, int> rv = functionDefinition->AddTemporaryParameter(parameterType, index++);
        if (!rv) return std::unexpected<int>(rv.error());
    }
    if (functionDefinition->IsVirtual())
    {
        ClassTemplateSpecializationSymbol* csp = context->GetClassTemplateSpecialization(functionNode);
        if (csp)
        {
            FunctionSymbol* prev = csp->GetMatchingVirtualFunctionSpecialization(functionDefinition.get(), context);
            if (prev && prev->IsFunctionDefinitionSymbol())
            {
                get = true;
                return static_cast<FunctionDefinitionSymbol*>(prev);
            }
        }
    }
    functionDefinition->ClearTemporaryParameters();
    MapNode(node, functionDefinition.get());
    if (context->MemFunDefSymbolIndex() != -1)
    {
        functionDefinition->SetDefIndex(context->MemFunDefSymbolIndex());
        context->SetMemFunDefSymbolIndex(-1);
    }
    FunctionDefinitionSymbol* definition = functionDefinition.get();
    std::expected<bool, int> rv = currentScope->SymbolScope()->AddSymbol(functionDefinition.release(), node->GetSourcePos(), context);
    if (!rv) return std::unexpected<int>(rv.error());
    FunctionSymbol* declaration = functionGroup->ResolveFunction(parameterTypes, qualifiers, specialization, definition->ParentTemplateDeclaration(),
        definition->IsSpecialization(), context);
    if (declaration)
    {
        definition->SetDeclaration(declaration);
        definition->SetAccess(declaration->GetAccess());
    }
    return std::expected<FunctionDefinitionSymbol*, int>(definition);
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

std::expected<TypeSymbol*, int> SymbolTable::MakeCompoundType(TypeSymbol* baseType, Derivations derivations)
{
    MapType(baseType);
    Derivations drv = derivations;
    if (baseType->IsCompoundTypeSymbol())
    {
        CompoundTypeSymbol* compoundTypeSymbol = static_cast<CompoundTypeSymbol*>(baseType);
        drv = Merge(drv, compoundTypeSymbol->GetDerivations());
        baseType = compoundTypeSymbol->BaseType();
    }
    if (drv == Derivations::none)
    {
        return baseType;
    }
    std::expected<util::uuid, int> i = MakeCompoundTypeId(baseType, drv, *this);
    if (!i) return std::unexpected<int>(i.error());
    util::uuid id = *i;
    CompoundTypeSymbol* compoundType = GetCompoundType(id);
    if (compoundType)
    {
        return std::expected<TypeSymbol*, int>(compoundType);
    }
    CompoundTypeSymbol* compoundTypeSymbol = new CompoundTypeSymbol(baseType, drv, id);
    AddCompoundType(compoundTypeSymbol);
    MapCompoundType(compoundTypeSymbol);
    if (AddToRecomputeNameSet())
    {
        AddToRecomputeNameSet(compoundTypeSymbol);
    }
    return std::expected<TypeSymbol*, int>(compoundTypeSymbol);
}

void SymbolTable::AddCompoundType(CompoundTypeSymbol* compoundType)
{
    compoundTypes.push_back(std::unique_ptr<CompoundTypeSymbol>(compoundType));
}

void SymbolTable::MapCompoundType(CompoundTypeSymbol* compoundType)
{
    compoundTypeMap[compoundType->Id()] = compoundType;
    MapType(compoundType);
}

CompoundTypeSymbol* SymbolTable::GetCompoundType(const util::uuid& compoundTypeId) const
{
    auto it = compoundTypeMap.find(compoundTypeId);
    if (it != compoundTypeMap.end())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}

std::expected<TypeSymbol*, int> SymbolTable::MakeConstCharPtrType()
{
    Derivations derivations = Derivations::constDerivation;
    derivations = SetPointerCount(derivations, 1);
    return MakeCompoundType(GetFundamentalType(FundamentalTypeKind::charType), derivations);
}

std::expected<TypeSymbol*, int> SymbolTable::MakeConstChar8PtrType()
{
    Derivations derivations = Derivations::constDerivation;
    derivations = SetPointerCount(derivations, 1);
    return MakeCompoundType(GetFundamentalType(FundamentalTypeKind::char8Type), derivations);
}

std::expected<TypeSymbol*, int> SymbolTable::MakeConstChar16PtrType()
{
    Derivations derivations = Derivations::constDerivation;
    derivations = SetPointerCount(derivations, 1);
    return MakeCompoundType(GetFundamentalType(FundamentalTypeKind::char16Type), derivations);
}

std::expected<TypeSymbol*, int> SymbolTable::MakeConstChar32PtrType()
{
    Derivations derivations = Derivations::constDerivation;
    derivations = SetPointerCount(derivations, 1);
    return MakeCompoundType(GetFundamentalType(FundamentalTypeKind::char32Type), derivations);
}

std::expected<TypeSymbol*, int> SymbolTable::MakeConstWCharPtrType()
{
    Derivations derivations = Derivations::constDerivation;
    derivations = SetPointerCount(derivations, 1);
    return MakeCompoundType(GetFundamentalType(FundamentalTypeKind::wcharType), derivations);
}

FunctionTypeSymbol* SymbolTable::MakeFunctionTypeSymbol(FunctionSymbol* functionSymbol)
{
    std::unique_ptr<FunctionTypeSymbol> symbol(new FunctionTypeSymbol());
    int n = functionSymbol->Parameters().size();
    for (int i = 0; i < n; ++i)
    {
        symbol->AddParameterType(functionSymbol->Parameters()[i]->GetType());
    }
    symbol->SetReturnType(functionSymbol->ReturnType());
    auto it = functionTypeSet.find(symbol.get());
    if (it != functionTypeSet.cend())
    {
        return *it;
    }
    FunctionTypeSymbol* sym = symbol.get();
    sym->MakeName();
    functionTypeSet.insert(sym);
    functionTypes.push_back(std::unique_ptr<Symbol>(symbol.release()));
    MapType(sym);
    return sym;
}

FunctionGroupTypeSymbol* SymbolTable::MakeFunctionGroupTypeSymbol(FunctionGroupSymbol* functionGroup)
{
    auto it = functionGroupTypeMap.find(functionGroup);
    if (it != functionGroupTypeMap.cend())
    {
        return it->second;
    }
    FunctionGroupTypeSymbol* functionGroupType = new FunctionGroupTypeSymbol(functionGroup);
    functionGroupTypeMap[functionGroup] = functionGroupType;
    functionGroupTypes.push_back(std::unique_ptr<FunctionGroupTypeSymbol>(functionGroupType));
    return functionGroupType;
}

ClassGroupTypeSymbol* SymbolTable::MakeClassGroupTypeSymbol(ClassGroupSymbol* classGroup)
{
    auto it = classGroupTypeMap.find(classGroup);
    if (it != classGroupTypeMap.cend())
    {
        return it->second;
    }
    ClassGroupTypeSymbol* classGroupType = new ClassGroupTypeSymbol(classGroup);
    classGroupTypeMap[classGroup] = classGroupType;
    classGroupTypes.push_back(std::unique_ptr<ClassGroupTypeSymbol>(classGroupType));
    return classGroupType;
}

AliasGroupTypeSymbol* SymbolTable::MakeAliasGroupTypeSymbol(AliasGroupSymbol* aliasGroup)
{
    auto it = aliasGroupTypeMap.find(aliasGroup);
    if (it != aliasGroupTypeMap.cend())
    {
        return it->second;
    }
    AliasGroupTypeSymbol* aliasGroupType = new AliasGroupTypeSymbol(aliasGroup);
    aliasGroupTypeMap[aliasGroup] = aliasGroupType;
    aliasGroupTypes.push_back(std::unique_ptr<AliasGroupTypeSymbol>(aliasGroupType));
    return aliasGroupType;
}

std::expected<ConceptSymbol*, int> SymbolTable::AddConcept(const std::u32string& name, otava::ast::Node* node, Context* context)
{
    std::expected<ConceptGroupSymbol*, int> c = currentScope->GroupScope()->GetOrInsertConceptGroup(name, node->GetSourcePos(), context);
    if (!c) return std::unexpected<int>(c.error());
    ConceptGroupSymbol* conceptGroup = *c;
    ConceptSymbol* conceptSymbol = new ConceptSymbol(name);
    conceptGroup->AddConcept(conceptSymbol);
    std::expected<bool, int> rv = currentScope->SymbolScope()->AddSymbol(conceptSymbol, node->GetSourcePos(), context);
    if (!rv) return std::unexpected<int>(rv.error());
    MapNode(node, conceptSymbol);
    return std::expected<ConceptSymbol*, int>(conceptSymbol);
}

std::expected<ClassTemplateSpecializationSymbol*, int> SymbolTable::MakeClassTemplateSpecialization(
    ClassTypeSymbol* classTemplate, const std::vector<Symbol*>& templateArguments)
{
    std::expected<util::uuid, int> u = MakeClassTemplateSpecializationSymbolId(classTemplate, templateArguments, *this);
    if (!u) return std::unexpected<int>(u.error());
    util::uuid id = *u;
    auto it = classTemplateSpecializationMap.find(id);
    if (it != classTemplateSpecializationMap.end())
    {
        return std::expected<ClassTemplateSpecializationSymbol*, int>(it->second);
    }
    std::unique_ptr<ClassTemplateSpecializationSymbol> symbol(new ClassTemplateSpecializationSymbol(id, MakeSpecializationName(classTemplate, templateArguments)));
    symbol->SetClassTemplate(classTemplate);
    for (Symbol* templateArg : templateArguments)
    {
        symbol->AddTemplateArgument(templateArg);
    }
    ClassTemplateSpecializationSymbol* sp = symbol.release();
    AddClassTemplateSpecialization(sp);
    MapClassTemplateSpecialization(sp);
    return std::expected<ClassTemplateSpecializationSymbol*, int>(sp);
}

AliasTypeTemplateSpecializationSymbol* SymbolTable::MakeAliasTypeTemplateSpecialization(TypeSymbol* aliasTypeTemplate, const std::vector<Symbol*>& templateArguments)
{
    std::unique_ptr<AliasTypeTemplateSpecializationSymbol> symbol(new AliasTypeTemplateSpecializationSymbol(MakeSpecializationName(aliasTypeTemplate, templateArguments)));
    symbol->SetAliasTypeTemplate(aliasTypeTemplate);
    for (Symbol* templateArg : templateArguments)
    {
        symbol->AddTemplateArgument(templateArg);
    }
    auto it = aliasTypeTemplateSpecializationSet.find(symbol.get());
    if (it != aliasTypeTemplateSpecializationSet.cend())
    {
        return *it;
    }
    AliasTypeTemplateSpecializationSymbol* sym = symbol.get();
    aliasTypeTemplateSpecializationSet.insert(sym);
    aliasTypeTemplateSpecializations.push_back(std::unique_ptr<Symbol>(symbol.release()));
    MapType(sym);
    return sym;
}

ArrayTypeSymbol* SymbolTable::MakeArrayType(TypeSymbol* elementType, std::int64_t size)
{
    std::unique_ptr<ArrayTypeSymbol> symbol(new ArrayTypeSymbol(elementType, size));
    auto it = arrayTypeSet.find(symbol.get());
    if (it != arrayTypeSet.cend())
    {
        return *it;
    }
    ArrayTypeSymbol* sym = symbol.get();
    arrayTypeSet.insert(sym);
    arrayTypes.push_back(std::unique_ptr<Symbol>(symbol.release()));
    MapType(sym);
    return sym;
}

DependentTypeSymbol* SymbolTable::MakeDependentTypeSymbol(otava::ast::Node* node)
{
    DependentTypeSymbol* dependentTypeSymbol = new DependentTypeSymbol(node);
    dependentTypeSet.insert(dependentTypeSymbol);
    MapType(dependentTypeSymbol);
    dependentTypeSymbols.push_back(std::unique_ptr<DependentTypeSymbol>(dependentTypeSymbol));
    return dependentTypeSymbol;
}

std::expected<bool, int> SymbolTable::CreateFundamentalTypes()
{
    std::expected<bool, int> rv = AddFundamentalType(FundamentalTypeKind::charType);
    if (!rv) return rv;
    rv = AddFundamentalType(FundamentalTypeKind::char8Type);
    if (!rv) return rv;
    rv = AddFundamentalType(FundamentalTypeKind::char16Type);
    if (!rv) return rv;
    rv = AddFundamentalType(FundamentalTypeKind::char32Type);
    if (!rv) return rv;
    rv = AddFundamentalType(FundamentalTypeKind::wcharType);
    if (!rv) return rv;
    rv = AddFundamentalType(FundamentalTypeKind::boolType);
    if (!rv) return rv;
    rv = AddFundamentalType(FundamentalTypeKind::shortIntType);
    if (!rv) return rv;
    rv = AddFundamentalType(FundamentalTypeKind::intType);
    if (!rv) return rv;
    rv = AddFundamentalType(FundamentalTypeKind::longIntType);
    if (!rv) return rv;
    rv = AddFundamentalType(FundamentalTypeKind::longLongIntType);
    if (!rv) return rv;
    rv = AddFundamentalType(FundamentalTypeKind::floatType);
    if (!rv) return rv;
    rv = AddFundamentalType(FundamentalTypeKind::doubleType);
    if (!rv) return rv;
    rv = AddFundamentalType(FundamentalTypeKind::voidType);
    if (!rv) return rv;
    rv = AddFundamentalType(FundamentalTypeKind::signedCharType);
    if (!rv) return rv;
    rv = AddFundamentalType(FundamentalTypeKind::unsignedCharType);
    if (!rv) return rv;
    rv = AddFundamentalType(FundamentalTypeKind::unsignedShortIntType);
    if (!rv) return rv;
    rv = AddFundamentalType(FundamentalTypeKind::unsignedIntType);
    if (!rv) return rv;
    rv = AddFundamentalType(FundamentalTypeKind::unsignedLongIntType);
    if (!rv) return rv;
    rv = AddFundamentalType(FundamentalTypeKind::unsignedLongLongIntType);
    if (!rv) return rv;
    rv = AddFundamentalType(FundamentalTypeKind::longDoubleType);
    if (!rv) return rv;
    rv = AddFundamentalType(FundamentalTypeKind::autoType);
    if (!rv) return rv;
    rv = AddFundamentalType(FundamentalTypeKind::nullPtrType);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> SymbolTable::AddFundamentalType(FundamentalTypeKind kind)
{
    FundamentalTypeSymbol* fundamentalTypeSymbol = new FundamentalTypeSymbol(kind);
    Context context;
    context.SetSymbolTable(this);
    std::expected<bool, int> rv = globalNs->AddSymbol(fundamentalTypeSymbol, soul::ast::SourcePos(), &context);
    if (!rv) return rv;
    MapFundamentalType(fundamentalTypeSymbol);
    return std::expected<bool, int>(true);
}

std::expected<bool, int> SymbolTable::AddFundamentalTypeOperations()
{
    Context context;
    context.SetSymbolTable(this);
    return AddFundamentalTypeOperationsToSymbolTable(&context);
}

void SymbolTable::MapFundamentalType(FundamentalTypeSymbol* fundamentalTypeSymbol)
{
    FundamentalTypeKind kind = fundamentalTypeSymbol->GetFundamentalTypeKind();
    fundamentalTypeMap[static_cast<std::int32_t>(kind)] = fundamentalTypeSymbol;
}

std::expected<TypeSymbol*, int> SymbolTable::GetFundamentalTypeSymbol(FundamentalTypeKind kind)
{
    auto it = fundamentalTypeMap.find(static_cast<std::int32_t>(kind));
    if (it != fundamentalTypeMap.cend())
    {
        return it->second;
    }
    else
    {
        return std::unexpected<int>(util::AllocateError("fundamental type " + std::to_string(static_cast<std::int32_t>(kind)) + " not found"));
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

void SymbolTable::MapFunctionGroup(FunctionGroupSymbol* functionGroup)
{
    functionGroupMap[functionGroup->Id()] = functionGroup;
}

void SymbolTable::MapClassGroup(ClassGroupSymbol* classGroup)
{
    classGroupMap[classGroup->Id()] = classGroup;
}

void SymbolTable::MapAliasGroup(AliasGroupSymbol* aliasGroup)
{
    aliasGroupMap[aliasGroup->Id()] = aliasGroup;
}

void SymbolTable::MapConcept(ConceptSymbol* cncp)
{
    conceptMap[cncp->Id()] = cncp;
}

std::expected<FunctionSymbol*, int> SymbolTable::GetFunction(const util::uuid& id) const
{
    auto it = functionMap.find(id);
    if (it != functionMap.cend())
    {
        return std::expected<FunctionSymbol*, int>(it->second);
    }
    else
    {
        return std::unexpected<int>(util::AllocateError("otava.symbols.symbol_table: function for id '" + util::ToString(id) + "' not found"));
    }
}

std::expected<FunctionDefinitionSymbol*, int> SymbolTable::GetFunctionDefinition(const util::uuid& id) const
{
    auto it = functionDefinitionMap.find(id);
    if (it != functionDefinitionMap.cend())
    {
        return std::expected<FunctionDefinitionSymbol*, int>(it->second);
    }
    else
    {
        return std::unexpected<int>(util::AllocateError("otava.symbols.symbol_table: function definition for id '" + util::ToString(id) + "' not found"));
    }
}

std::expected<AliasTypeSymbol*, int> SymbolTable::GetAliasType(const util::uuid& id) const
{
    TypeSymbol* type = GetType(id);
    if (type && type->IsAliasTypeSymbol())
    {
        return std::expected<AliasTypeSymbol*, int>(static_cast<AliasTypeSymbol*>(type));
    }
    else
    {
        return std::unexpected<int>(util::AllocateError("otava.symbols.symbol_table: alias type expected"));
    }
}

std::expected<ClassTypeSymbol*, int> SymbolTable::GetClass(const util::uuid& id) const
{
    TypeSymbol* type = GetType(id);
    if (type && type->IsClassTypeSymbol())
    {
        return std::expected<ClassTypeSymbol*, int>(static_cast<ClassTypeSymbol*>(type));
    }
    else
    {
        return std::unexpected<int>(util::AllocateError("otava.symbols.symbol_table: class type expected: id=" + util::ToString(id)));
    }
}

std::expected<VariableSymbol*, int> SymbolTable::GetVariable(const util::uuid& id) const
{
    auto it = variableMap.find(id);
    if (it != variableMap.cend())
    {
        return std::expected<VariableSymbol*, int>(it->second);
    }
    else
    {
        return std::unexpected<int>(util::AllocateError("variable for id '" + util::ToString(id) + "' not found"));
    }
}

std::expected<ConceptSymbol*, int> SymbolTable::GetConcept(const util::uuid& id) const
{
    auto it = conceptMap.find(id);
    if (it != conceptMap.end())
    {
        return std::expected<ConceptSymbol*, int>(it->second);
    }
    else
    {
        return std::unexpected<int>(util::AllocateError("concept for id '" + util::ToString(id) + "' not found"));
    }
}

std::expected<Symbol*, int> SymbolTable::GetConstraint(const util::uuid& id) const
{
    auto it = constraintMap.find(id);
    if (it != constraintMap.cend())
    {
        return std::expected<Symbol*, int>(it->second);
    }
    else
    {
        return std::unexpected<int>(util::AllocateError("constraint for id '" + util::ToString(id) + "' not found"));
    }
}

std::expected<FunctionGroupSymbol*, int> SymbolTable::GetFunctionGroup(const util::uuid& id) const
{
    auto it = functionGroupMap.find(id);
    if (it != functionGroupMap.cend())
    {
        return std::expected<FunctionGroupSymbol*, int>(it->second);
    }
    else
    {
        return std::unexpected<int>(util::AllocateError("function group for id '" + util::ToString(id) + "' not found"));
    }
}

std::expected<ClassGroupSymbol*, int> SymbolTable::GetClassGroup(const util::uuid& id) const
{
    auto it = classGroupMap.find(id);
    if (it != classGroupMap.cend())
    {
        return std::expected<ClassGroupSymbol*, int>(it->second);
    }
    else
    {
        return std::unexpected<int>(util::AllocateError("class group for id '" + util::ToString(id) + "' not found"));
    }
}

std::expected<AliasGroupSymbol*, int> SymbolTable::GetAliasGroup(const util::uuid& id) const
{
    auto it = aliasGroupMap.find(id);
    if (it != aliasGroupMap.cend())
    {
        return std::expected<AliasGroupSymbol*, int>(it->second);
    }
    else
    {
        return std::unexpected<int>(util::AllocateError("alias group for id '" + util::ToString(id) + "' not found"));
    }
}

std::expected<bool, int> SymbolTable::CreateCoreSymbols()
{
    typenameConstraintSymbol = new TypenameConstraintSymbol();
    errorTypeSymbol = new ErrorTypeSymbol();
    MapConstraint(typenameConstraintSymbol);
    Context context;
    context.SetSymbolTable(this);
    std::expected<bool, int> rv = globalNs->AddSymbol(typenameConstraintSymbol, soul::ast::SourcePos(), &context);
    if (!rv) return rv;
    rv = globalNs->AddSymbol(errorTypeSymbol, soul::ast::SourcePos(), &context);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

void SymbolTable::AddToRecomputeNameSet(CompoundTypeSymbol* compoundTypeSymbol)
{
    recomputeNameSet.insert(compoundTypeSymbol);
}

void SymbolTable::RecomputeNames()
{
    for (CompoundTypeSymbol* compoundType : recomputeNameSet)
    {
        compoundType->SetName(MakeCompoundTypeName(compoundType->BaseType(), compoundType->GetDerivations()));
    }
    recomputeNameSet.clear();
}

TypeSymbol* SymbolTable::GetFundamentalType(FundamentalTypeKind kind) const
{
    auto it = fundamentalTypeMap.find(static_cast<std::int32_t>(kind));
    if (it != fundamentalTypeMap.cend())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}

void SymbolTable::PushLinkage(Linkage linkage_)
{
    linkageStack.push(currentLinkage);
    currentLinkage = linkage_;
}

void SymbolTable::PopLinkage()
{
    currentLinkage = linkageStack.top();
    linkageStack.pop();
}

std::expected<ExplicitInstantiationSymbol*, int> SymbolTable::GetExplicitInstantiation(ClassTemplateSpecializationSymbol* classTemplateSpecialization) const
{
    auto it = explicitInstantiationMap.find(classTemplateSpecialization);
    if (it != explicitInstantiationMap.cend())
    {
        int error = explicitInstantiationMap.key_comp().error;
        if (error != 0)
        {
            return std::unexpected<int>(error);
        }
        return std::expected<ExplicitInstantiationSymbol*, int>(it->second);
    }
    else
    {
        int error = explicitInstantiationMap.key_comp().error;
        if (error != 0)
        {
            return std::unexpected<int>(error);
        }
        return std::expected<ExplicitInstantiationSymbol*, int>(static_cast<ExplicitInstantiationSymbol*>(nullptr));
    }
}

void SymbolTable::AddExplicitInstantiation(ExplicitInstantiationSymbol* explicitInstantition)
{
    explicitInstantiations.push_back(std::unique_ptr<ExplicitInstantiationSymbol>(explicitInstantition));
    MapExplicitInstantiation(explicitInstantition);
}

void SymbolTable::MapExplicitInstantiation(ExplicitInstantiationSymbol* explicitInstantition)
{
    explicitInstantiationMap[explicitInstantition->Specialization()] = explicitInstantition;
}

ClassTemplateSpecializationSymbol* SymbolTable::GetClassTemplateSpecialization(const util::uuid& id) const
{
    auto it = classTemplateSpecializationMap.find(id);
    if (it != classTemplateSpecializationMap.end())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}

void SymbolTable::AddClassTemplateSpecialization(ClassTemplateSpecializationSymbol* sp)
{
    classTemplateSpecializations.push_back(std::unique_ptr<Symbol>(sp));
}

void SymbolTable::MapClassTemplateSpecialization(ClassTemplateSpecializationSymbol* sp)
{
    classTemplateSpecializationMap[sp->Id()] = sp;
    MapType(sp);
}

void SymbolTable::AddChangedClassTemplateSpecialization(ClassTemplateSpecializationSymbol* sp)
{
    changedClassTemplateSpecializations.insert(sp);
}

void SymbolTable::UnmapClassTemplateSpecialization(ClassTemplateSpecializationSymbol* sp)
{
    classTemplateSpecializationMap.erase(sp->Id());
    UnmapType(sp);
}

void SymbolTable::AddAliasTypeTemplateSpecializationToSet(AliasTypeTemplateSpecializationSymbol* at)
{
    aliasTypeTemplateSpecializationSet.insert(at);
}

void SymbolTable::AddArrayTypeToSet(ArrayTypeSymbol* a)
{
    arrayTypeSet.insert(a);
}

void SymbolTable::ImportAfterResolve()
{
    for (const SymbolTable* st : importAfterResolve)
    {
        ImportSpecializations(*st);
        ImportArrayTypes(*st);
    }
    importAfterResolve.clear();
}

std::expected<bool, int> SymbolTable::ToXml(const std::string& xmlFilePath) const
{
    soul::xml::Document doc;
    Module* mod = GetModule();
    soul::xml::Element* root = soul::xml::MakeElement("module");
    root->SetAttribute("name", mod->Name());
    root->SetAttribute("filePath", mod->FilePath());
    std::expected<bool, int> rv = doc.AppendChild(root);
    if (!rv) return rv;
    std::ofstream xmlFile(xmlFilePath);
    if (!xmlFile)
    {
        return std::unexpected<int>(util::AllocateError("could not create file '" + xmlFilePath + "'"));
    }
    std::expected<soul::xml::Element*, int> x = globalNs->ToXml();
    if (!x) return std::unexpected<int>(x.error());
    rv = root->AppendChild(*x);
    if (!rv) return rv;
    soul::xml::Element* specializationsElement = soul::xml::MakeElement("specializations");
    rv = root->AppendChild(specializationsElement);
    if (!rv) return rv;
    for (const auto& specialization : classTemplateSpecializations)
    {
        x = specialization->ToXml();
        if (!x) return std::unexpected<int>(x.error());
        rv = specializationsElement->AppendChild(*x);
        if (!rv) return rv;
    }
    util::CodeFormatter formatter(xmlFile);
    formatter.SetIndentSize(1);
    rv = doc.Write(formatter);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

void SymbolTable::InitTemplateParameterIds()
{
    for (int i = 0; i < maxTemplateParameters; ++i)
    {
        templateParameterIds.push_back(util::uuid::random());
    }
}

void SymbolTable::InitCompoundTypeIds()
{
    for (int i = 0; i < numCompoundTypeIds; ++i)
    {
        compoundTypeIds.push_back(util::uuid::random());
    }
}

void SymbolTable::InitLevelIds()
{
    for (int i = 0; i < maxLevels; ++i)
    {
        levelIds.push_back(util::uuid::random());
    }
}

std::expected<util::uuid, int> SymbolTable::GetTemplateParameterId(int index) const
{
    if (index >= 0 && index < templateParameterIds.size())
    {
        return templateParameterIds[index];
    }
    else
    {
        return std::unexpected<int>(util::AllocateError("too many template parameters (max=" + std::to_string(templateParameterIds.size()) + ")"));
    }
}

std::expected<util::uuid, int> SymbolTable::GetCompoundTypeId(int index) const
{
    if (index >= 0 && index < compoundTypeIds.size())
    {
        return compoundTypeIds[index];
    }
    else
    {
        return std::unexpected<int>(util::AllocateError("invalid compound type id index (max=" + std::to_string(compoundTypeIds.size()) + ")"));
    }
}

std::expected<util::uuid, int> SymbolTable::GetLevelId(int level) const
{
    if (level >= 0 && level < levelIds.size())
    {
        return levelIds[level];
    }
    else
    {
        return std::unexpected<int>(util::AllocateError("invalid level id index (max=" + std::to_string(levelIds.size()) + ")"));
    }
}

} // namespace otava::symbols
