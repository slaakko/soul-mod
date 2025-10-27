// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.variable.symbol;

import otava.symbols.modules;
import otava.symbols.symbol.table;
import otava.symbols.alias.type.symbol;
import otava.symbols.type.symbol;
import otava.symbols.value;
import otava.symbols.visitor;
import otava.symbols.context;
import otava.symbols.declaration;
import otava.symbols.bound.tree;
import otava.symbols.function.templates;
import otava.symbols.inline_functions;
import otava.symbols.argument.conversion.table;
import otava.symbols.operation.repository;
import otava.symbols.function.kind;
import otava.symbols.function.symbol;
import util.unicode;
import util.sha1;

namespace otava::symbols {

VariableSymbol::VariableSymbol(const std::u32string& name_) :
    Symbol(SymbolKind::variableSymbol, name_),
    declaredType(nullptr),
    declaredTypeId(util::nil_uuid()),
    initializerType(nullptr),
    initializerTypeId(util::nil_uuid()),
    value(nullptr),
    valueId(util::nil_uuid()),
    layoutIndex(-1),
    index(-1),
    global(nullptr)
{
}

std::expected<bool, int> VariableSymbol::Write(Writer& writer)
{
    std::expected<bool, int> rv = Symbol::Write(writer);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(declaredType->Id());
    if (!rv) return rv;
    if (initializerType)
    {
        rv = writer.GetBinaryStreamWriter().Write(initializerType->Id());
        if (!rv) return rv;
    }
    else
    {
        rv = writer.GetBinaryStreamWriter().Write(util::nil_uuid());
        if (!rv) return rv;
    }
    bool hasValue = value != nullptr;
    rv = writer.GetBinaryStreamWriter().Write(hasValue);
    if (!rv) return rv;
    if (hasValue)
    {
        rv = writer.GetBinaryStreamWriter().Write(value->Id());
        if (!rv) return rv;
    }
    rv = writer.GetBinaryStreamWriter().Write(layoutIndex);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> VariableSymbol::Read(Reader& reader)
{
    std::expected<bool, int> rv = Symbol::Read(reader);
    if (!rv) return rv;
    rv = reader.GetBinaryStreamReader().ReadUuid(declaredTypeId);
    if (!rv) return rv;
    rv = reader.GetBinaryStreamReader().ReadUuid(initializerTypeId);
    if (!rv) return rv;
    rv = reader.GetBinaryStreamReader().ReadBool();
    if (!rv) return rv;
    bool hasValue = *rv;
    if (hasValue)
    {
        rv = reader.GetBinaryStreamReader().ReadUuid(valueId);
        if (!rv) return rv;
    }
    std::expected<std::int32_t, int> irv = reader.GetBinaryStreamReader().ReadInt();
    if (!irv) return std::unexpected<int>(irv.error());
    layoutIndex = *irv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> VariableSymbol::Resolve(SymbolTable& symbolTable, Context* context)
{
    std::expected<bool, int> rv = Symbol::Resolve(symbolTable, context);
    declaredType = symbolTable.GetType(declaredTypeId);
    if (!declaredType)
    {
        std::cout << "VariableSymbol::Resolve(): warning: declared type not resolved" << "\n";
    }
    if (initializerTypeId != util::nil_uuid())
    {
        initializerType = symbolTable.GetType(initializerTypeId);
        if (!initializerType)
        {
            std::cout << "VariableSymbol::Resolve(): warning: initializer type not resolved" << "\n";
        }
    }
    if (valueId != util::nil_uuid())
    {
        EvaluationContext* evaluationContext = symbolTable.GetModule()->GetEvaluationContext();
        value = evaluationContext->GetValue(valueId);
    }
    return std::expected<bool, int>(true);
}

void VariableSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

bool VariableSymbol::IsLocalVariable() const
{
    return Parent()->IsFunctionSymbol() || Parent()->IsBlockSymbol();
}

bool VariableSymbol::IsMemberVariable() const
{
    return Parent()->IsClassTypeSymbol();
}

bool VariableSymbol::IsGlobalVariable() const
{
    return Parent()->IsNamespaceSymbol();
}

void VariableSymbol::SetInitializerType(TypeSymbol* initializerType_)
{
    initializerType = initializerType_;
}

TypeSymbol* VariableSymbol::GetType() const
{
    if (declaredType->GetBaseType()->IsAutoTypeSymbol())
    {
        return initializerType;
    }
    else
    {
        return declaredType;
    }
}

TypeSymbol* VariableSymbol::GetReferredType() const
{
    TypeSymbol* referredType = GetType();
    if (!referredType)
    {
        return nullptr;
    }
    while (referredType->IsAliasTypeSymbol())
    {
        AliasTypeSymbol* aliasType = static_cast<AliasTypeSymbol*>(referredType);
        referredType = aliasType->ReferredType();
    }
    return referredType;
}

bool VariableSymbol::IsTemplateParameterInstantiation(Context* context, std::set<const Symbol*>& visited) const
{
    if (visited.find(this) == visited.end())
    {
        visited.insert(this);
        TypeSymbol* type = GetType();
        if (type)
        {
            if (type->IsTemplateParameterInstantiation(context, visited))
            {
                return true;
            }
        }
    }
    return false;
}

std::expected<std::string, int> VariableSymbol::IrName(Context* context) const
{
    std::string irName = "variable_";
    std::expected<std::string, int> irn = util::ToUtf8(Name());
    if (!irn) return irn;
    irName.append(*irn).append("_");
    if (IsStatic())
    {
        std::expected<std::u32string, int> fname = FullName();
        if (!fname) return std::unexpected<int>(fname.error());
        std::expected<std::string, int> sfname = util::ToUtf8(*fname);
        if (!sfname) return std::unexpected<int>(sfname.error());
        irName.append(util::GetSha1MessageDigest(*sfname)).append(context->GetBoundCompileUnit()->Id());
    }
    else
    {
        std::expected<std::u32string, int> fname = FullName();
        if (!fname) return std::unexpected<int>(fname.error());
        std::expected<std::string, int> sfname = util::ToUtf8(*fname);
        if (!sfname) return std::unexpected<int>(sfname.error());
        irName.append(util::GetSha1MessageDigest(*sfname));
    }
    return std::expected<std::string, int>(irName);
}

bool VariableSymbol::IsStatic() const
{
    return (GetDeclarationFlags() & DeclarationFlags::staticFlag) != DeclarationFlags::none;
}

bool VariableLess::operator()(VariableSymbol* left, VariableSymbol* right) const
{
    return left->Name() < right->Name();
}

std::expected<bool, int> SetDeclaredVariableType(VariableSymbol* variable, const soul::ast::SourcePos& sourcePos, Context* context)
{
    TypeSymbol* variableBaseType = variable->GetType()->GetBaseType();
    if (variableBaseType->IsTemplateParameterSymbol())
    {
        std::expected<Symbol*, int> s = context->GetSymbolTable()->CurrentScope()->Lookup(
            variableBaseType->Name(), SymbolGroupKind::typeSymbolGroup, ScopeLookup::thisScope, sourcePos, context, LookupFlags::none);
        if (!s) return std::unexpected<int>(s.error());
        Symbol* symbol = *s;
        if (symbol && symbol->IsTypeSymbol())
        {
            TypeSymbol* typeSymbol = static_cast<TypeSymbol*>(symbol);
            std::expected<TypeSymbol*, int> pt = variable->GetType()->Unify(typeSymbol, context);
            if (!pt) return std::unexpected<int>(pt.error());
            TypeSymbol* specializedType = *pt;
            variable->SetDeclaredType(specializedType);
        }
    }
    return std::expected<bool, int>(true);
}

} // namespace otava::symbols
