// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.variable.symbol;

import otava.symbols.modules;
import otava.symbols.symbol.table;
import otava.symbols.alias.type.symbol;
import otava.symbols.type.symbol;
import otava.symbols.reader;
import otava.symbols.writer;
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

void VariableSymbol::Write(Writer& writer)
{
    Symbol::Write(writer);
    writer.GetBinaryStreamWriter().Write(declaredType->Id());
    if (initializerType)
    {
        writer.GetBinaryStreamWriter().Write(initializerType->Id());
    }
    else
    {
        writer.GetBinaryStreamWriter().Write(util::nil_uuid());
    }
    bool hasValue = value != nullptr;
    writer.GetBinaryStreamWriter().Write(hasValue);
    if (hasValue)
    {
        writer.GetBinaryStreamWriter().Write(value->Id());
    }
    writer.GetBinaryStreamWriter().Write(layoutIndex);
    bool templateDeclaration = false;
    const Symbol* parent = Parent();
    if (parent)
    {
        parent = parent->Parent();
        if (parent && parent->IsTemplateDeclarationSymbol())
        {
            templateDeclaration = true;
        }
    }
    std::set<const Symbol*> visited;
    if (IsMemberVariable() && !IsStatic() && !templateDeclaration && !IsTemplateParameterInstantiation(writer.GetContext(), visited) && layoutIndex == -1)
    {
        int x = 0;
    }
}

void VariableSymbol::Read(Reader& reader)
{
    Symbol::Read(reader);
    reader.GetBinaryStreamReader().ReadUuid(declaredTypeId);
    reader.GetBinaryStreamReader().ReadUuid(initializerTypeId);
    bool hasValue = reader.GetBinaryStreamReader().ReadBool();
    if (hasValue)
    {
        reader.GetBinaryStreamReader().ReadUuid(valueId);
    }
    layoutIndex = reader.GetBinaryStreamReader().ReadInt();
}

void VariableSymbol::Resolve(SymbolTable& symbolTable, Context* context)
{
    Symbol::Resolve(symbolTable, context);
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

std::string VariableSymbol::IrName(Context* context) const
{
    std::string irName = "variable_";
    irName.append(util::ToUtf8(Name())).append("_");
    if (IsStatic())
    {
        irName.append(util::GetSha1MessageDigest(util::ToUtf8(FullName()) + context->GetBoundCompileUnit()->Id()));
    }
    else
    {
        irName.append(util::GetSha1MessageDigest(util::ToUtf8(FullName())));
    }
    return irName;
}

bool VariableSymbol::IsStatic() const
{
    return (GetDeclarationFlags() & DeclarationFlags::staticFlag) != DeclarationFlags::none;
}

bool VariableLess::operator()(VariableSymbol* left, VariableSymbol* right) const
{
    return left->Name() < right->Name();
}

void SetDeclaredVariableType(VariableSymbol* variable, const soul::ast::SourcePos& sourcePos, Context* context)
{
    TypeSymbol* variableBaseType = variable->GetType()->GetBaseType();
    if (variableBaseType->IsTemplateParameterSymbol())
    {
        Symbol* symbol = context->GetSymbolTable()->CurrentScope()->Lookup(variableBaseType->Name(), SymbolGroupKind::typeSymbolGroup, ScopeLookup::thisScope,
            sourcePos, context, LookupFlags::none);
        if (symbol && symbol->IsTypeSymbol())
        {
            TypeSymbol* typeSymbol = static_cast<TypeSymbol*>(symbol);
            TypeSymbol* specializedType = variable->GetType()->Unify(typeSymbol, context);
            variable->SetDeclaredType(specializedType);
        }
    }
}

} // namespace otava::symbols
