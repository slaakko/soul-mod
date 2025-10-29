// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.enums;

import util;
import otava.ast;
import otava.symbols.emitter;
import otava.symbols.error;
import otava.symbols.modules;
import otava.symbols.symbol.table;
import otava.symbols.scope.resolver;
import otava.symbols.type.resolver;
import otava.symbols.writer;
import otava.symbols.reader;
import otava.symbols.value;
import otava.symbols.visitor;
import otava.symbols.function.group.symbol;
import otava.symbols.fundamental.type.operation;
import otava.symbols.evaluator;
import otava.symbols.fundamental.type.symbol;

namespace otava::symbols {

EnumeratedTypeSymbol::EnumeratedTypeSymbol(const std::u32string& name_) :
    TypeSymbol(SymbolKind::enumTypeSymbol, name_), bound(false), underlyingType(nullptr), kind(EnumTypeKind::enum_), underlyingTypeId()
{
    GetScope()->SetKind(ScopeKind::enumerationScope);
}

bool EnumeratedTypeSymbol::IsValidDeclarationScope(ScopeKind scopeKind) const
{
    switch (scopeKind)
    {
        case ScopeKind::namespaceScope:
        case ScopeKind::classScope:
        {
            return true;
        }
    }
    return false;
}

std::expected<bool, int> EnumeratedTypeSymbol::Write(Writer& writer)
{
    std::expected<bool, int> rv = TypeSymbol::Write(writer);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(bound);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(static_cast<std::uint8_t>(kind));
    if (!rv) return rv;
    bool hasUnderlyingType = underlyingType != nullptr;
    rv = writer.GetBinaryStreamWriter().Write(hasUnderlyingType);
    if (!rv) return rv;
    if (hasUnderlyingType)
    {
        rv = writer.GetBinaryStreamWriter().Write(underlyingType->Id());
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EnumeratedTypeSymbol::Read(Reader& reader)
{
    std::expected<bool, int> rv = TypeSymbol::Read(reader);
    if (!rv) return rv;
    std::expected<bool, int> brv = reader.GetBinaryStreamReader().ReadBool();
    if (!brv) return brv;
    bound = *brv;
    std::expected<std::uint8_t, int> urv = reader.GetBinaryStreamReader().ReadByte();
    if (!urv) return std::unexpected<int>(urv.error());
    std::uint8_t u = *urv;
    kind = static_cast<EnumTypeKind>(u);
    brv = reader.GetBinaryStreamReader().ReadBool();
    if (!brv) return brv;
    bool hasUnderlyingType = *brv;
    if (hasUnderlyingType)
    {
        rv = reader.GetBinaryStreamReader().ReadUuid(underlyingTypeId);
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EnumeratedTypeSymbol::Resolve(SymbolTable& symbolTable, Context* context)
{
    std::expected<bool, int> rv = TypeSymbol::Resolve(symbolTable, context);
    if (!rv) return rv;
    if (underlyingTypeId != util::nil_uuid())
    {
        underlyingType = symbolTable.GetType(underlyingTypeId);
    }
    return std::expected<bool, int>(true);
}

void EnumeratedTypeSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<otava::intermediate::Type*, int> EnumeratedTypeSymbol::IrType(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (underlyingType)
    {
        return underlyingType->IrType(emitter, sourcePos, context);
    }
    else
    {
        return std::expected<otava::intermediate::Type*, int>(emitter.GetIntType());
    }
}

ForwardEnumDeclarationSymbol::ForwardEnumDeclarationSymbol(const std::u32string& name_) :
    TypeSymbol(SymbolKind::forwardEnumDeclarationSymbol, name_),
    underlyingType(nullptr),
    enumTypeKind(EnumTypeKind::enum_),
    enumTypeSymbol(),
    enumTypeSymbolId(),
    underlyingTypeId()
{
    GetScope()->SetKind(ScopeKind::enumerationScope);
}

bool ForwardEnumDeclarationSymbol::IsValidDeclarationScope(ScopeKind scopeKind) const
{
    switch (scopeKind)
    {
        case ScopeKind::namespaceScope:
        case ScopeKind::classScope:
        {
            return true;
        }
    }
    return false;
}

void ForwardEnumDeclarationSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> ForwardEnumDeclarationSymbol::Write(Writer& writer)
{
    std::expected<bool, int> rv = TypeSymbol::Write(writer);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(static_cast<std::uint8_t>(enumTypeKind));
    if (!rv) return rv;
    bool hasUnderlyingType = underlyingType != nullptr;
    rv = writer.GetBinaryStreamWriter().Write(hasUnderlyingType);
    if (!rv) return rv;
    if (hasUnderlyingType)
    {
        rv = writer.GetBinaryStreamWriter().Write(underlyingType->Id());
        if (!rv) return rv;
    }
    rv = writer.GetBinaryStreamWriter().Write(enumTypeSymbol != nullptr);
    if (!rv) return rv;
    if (enumTypeSymbol)
    {
        rv = writer.GetBinaryStreamWriter().Write(enumTypeSymbol->Id());
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ForwardEnumDeclarationSymbol::Read(Reader& reader)
{
    std::expected<bool, int> rv = TypeSymbol::Read(reader);
    if (!rv) return rv;
    std::expected<std::uint8_t, int> urv = reader.GetBinaryStreamReader().ReadByte();
    if (!urv) return std::unexpected<int>(urv.error());
    std::uint8_t u = *urv;
    enumTypeKind = static_cast<EnumTypeKind>(u);
    std::expected<bool, int> brv = reader.GetBinaryStreamReader().ReadBool();
    if (!brv) return brv;
    bool hasUnderlyingType = *brv;
    if (hasUnderlyingType)
    {
        rv = reader.GetBinaryStreamReader().ReadUuid(underlyingTypeId);
        if (!rv) return rv;
    }
    brv = reader.GetBinaryStreamReader().ReadBool();
    if (!brv) return brv;
    bool hasEnumType = *brv;
    if (hasEnumType)
    {
        rv = reader.GetBinaryStreamReader().ReadUuid(enumTypeSymbolId);
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ForwardEnumDeclarationSymbol::Resolve(SymbolTable& symbolTable, Context* context)
{
    std::expected<bool, int> rv = TypeSymbol::Resolve(symbolTable, context);
    if (!rv) return rv;
    if (underlyingTypeId != util::nil_uuid())
    {
        underlyingType = symbolTable.GetType(underlyingTypeId);
    }
    if (enumTypeSymbolId != util::nil_uuid())
    {
        TypeSymbol* type = symbolTable.GetType(enumTypeSymbolId);
        if (type && type->IsEnumeratedTypeSymbol())
        {
            enumTypeSymbol = static_cast<EnumeratedTypeSymbol*>(type);
        }
        else
        {
            return std::unexpected<int>(util::AllocateError("otava.symbols.enums: enum type expected"));
        }
    }
    return std::expected<bool, int>(true);
}

EnumConstantSymbol::EnumConstantSymbol(const std::u32string& name_) : Symbol(SymbolKind::enumConstantSymbol, name_), value(), valueId(), enumType(nullptr)
{
}

bool EnumConstantSymbol::IsValidDeclarationScope(ScopeKind scopeKind) const
{
    if (enumType->GetEnumTypeKind() == EnumTypeKind::enumClass || enumType->GetEnumTypeKind() == EnumTypeKind::enumStruct)
    {
        return scopeKind == ScopeKind::enumerationScope;
    }
    else
    {
        switch (scopeKind)
        {
            case ScopeKind::namespaceScope:
            case ScopeKind::classScope:
            {
                return true;
            }
        }
    }
    return false;
}

std::expected<bool, int> EnumConstantSymbol::Write(Writer& writer)
{
    std::expected<bool, int> rv = Symbol::Write(writer);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(value->Id());
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(enumType->Id());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EnumConstantSymbol::Read(Reader& reader)
{
    std::expected<bool, int> rv = Symbol::Read(reader);
    if (!rv) return rv;
    rv = reader.GetBinaryStreamReader().ReadUuid(valueId);
    if (!rv) return rv;
    rv = reader.GetBinaryStreamReader().ReadUuid(enumTypeId);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EnumConstantSymbol::Resolve(SymbolTable& symbolTable, Context* context)
{
    std::expected<bool, int> rv = Symbol::Resolve(symbolTable, context);
    if (!rv) return rv;
    EvaluationContext* evaluationContext = symbolTable.GetModule()->GetEvaluationContext();
    value = evaluationContext->GetValue(valueId);
    TypeSymbol* type = symbolTable.GetType(enumTypeId);
    if (type && type->IsEnumeratedTypeSymbol())
    {
        enumType = static_cast<EnumeratedTypeSymbol*>(type);
    }
    return std::expected<bool, int>(true);
}

void EnumConstantSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

bool EnumTypeLessFunctor::operator()(EnumeratedTypeSymbol* left, EnumeratedTypeSymbol* right) const
{
    return left->Name() < right->Name();
}

class EnumCreator : public otava::ast::DefaultVisitor
{
public:
    EnumCreator(Context* context_, bool createEnumeratedType_, bool createEnumerators_);
    void Visit(otava::ast::EnumSpecifierNode& node) override;
    void Visit(otava::ast::EnumHeadNode& node) override;
    void Visit(otava::ast::EnumBaseNode& node) override;
    void Visit(otava::ast::EnumClassNode& node) override;
    void Visit(otava::ast::EnumStructNode& node) override;
    void Visit(otava::ast::EnumNode& node) override;
    void Visit(otava::ast::EnumeratorDefinitionNode& node) override;
    void Visit(otava::ast::EnumeratorNode& node) override;
    void Visit(otava::ast::ElaboratedEnumSpecifierNode& node) override;
    void Visit(otava::ast::OpaqueEnumDeclarationNode& node) override;
    void Visit(otava::ast::QualifiedIdNode& node) override;
    void Visit(otava::ast::IdentifierNode& node) override;
    void Visit(otava::ast::UnnamedNode& node) override;
private:
    Context* context;
    EnumTypeKind enumTypeKind;
    TypeSymbol* underlyingType;
    Scope* scope;
    Value* value;
    std::int64_t prevValue;
    bool first;
    bool createEnumeratedType;
    bool createEnumerators;
    bool opaque;
};

EnumCreator::EnumCreator(Context* context_, bool createEnumeratedType_, bool createEnumerators_) :
    context(context_),
    enumTypeKind(EnumTypeKind::enum_),
    underlyingType(nullptr),
    scope(context->GetSymbolTable()->CurrentScope()),
    value(nullptr),
    prevValue(0),
    first(false),
    createEnumeratedType(createEnumeratedType_),
    createEnumerators(createEnumerators_),
    opaque(false)
{
}

void EnumCreator::Visit(otava::ast::EnumSpecifierNode& node)
{
    if (!Valid()) return;
    if (createEnumeratedType)
    {
        node.EnumHead()->Accept(*this);
        if (!Valid()) return;
    }
    else if (createEnumerators)
    {
        first = true;
        VisitListContent(node);
    }
}

void EnumCreator::Visit(otava::ast::EnumHeadNode& node)
{
    if (!Valid()) return;
    node.EnumKey()->Accept(*this);
    if (!Valid()) return;
    if (node.EnumBase())
    {
        node.EnumBase()->Accept(*this);
        if (!Valid()) return;
    }
    node.EnumHeadName()->Accept(*this);
}

void EnumCreator::Visit(otava::ast::EnumBaseNode& node)
{
    if (!Valid()) return;
    std::expected<TypeSymbol*, int> rv = ResolveType(node.Child(), DeclarationFlags::none, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    underlyingType = *rv;
}

void EnumCreator::Visit(otava::ast::EnumClassNode& node)
{
    enumTypeKind = EnumTypeKind::enumClass;
}

void EnumCreator::Visit(otava::ast::EnumStructNode& node)
{
    enumTypeKind = EnumTypeKind::enumStruct;
}

void EnumCreator::Visit(otava::ast::EnumNode& node)
{
    enumTypeKind = EnumTypeKind::enum_;
}

void EnumCreator::Visit(otava::ast::EnumeratorDefinitionNode& node)
{
    if (!Valid()) return;
    Symbol* currentSymbol = context->GetSymbolTable()->CurrentScope()->GetSymbol();
    if (!currentSymbol->IsEnumeratedTypeSymbol())
    {
        std::unexpected<int> result = Error("otava.symbols.enums: EnumCreator(): enum scope expected", node.GetSourcePos(), context);
        SetError(result.error());
        return;
    }
    EnumeratedTypeSymbol* enumType = static_cast<EnumeratedTypeSymbol*>(currentSymbol);
    TypeSymbol* valueType = enumType->UnderlyingType();
    if (!valueType)
    {
        std::expected<TypeSymbol*, int> rv = context->GetSymbolTable()->GetFundamentalTypeSymbol(FundamentalTypeKind::intType);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        valueType = *rv;
    }
    if (node.Value())
    {
        auto rv = Evaluate(node.Value(), context);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        Value* val = *rv;
        if (val->IsIntegerValue())
        {
            IntegerValue* intVal = static_cast<IntegerValue*>(val);
            auto rv = util::ToUtf32(std::to_string(intVal->GetValue()));
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
            value = context->GetEvaluationContext()->GetIntegerValue(intVal->GetValue(), *rv, valueType);
        }
        if (value && value->IsIntegerValue())
        {
            IntegerValue* integerValue = static_cast<IntegerValue*>(value);
            prevValue = integerValue->GetValue();
        }
        if (first)
        {
            first = false;
        }
    }
    else
    {
        if (first)
        {
            auto rv = util::ToUtf32(std::to_string(0));
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
            value = context->GetEvaluationContext()->GetIntegerValue(0, *rv, valueType);
            prevValue = 0;
            first = false;
        }
        else
        {
            auto rv = util::ToUtf32(std::to_string(prevValue + 1));
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
            value = context->GetEvaluationContext()->GetIntegerValue(prevValue + 1, *rv, valueType);
            ++prevValue;
        }
    }
    node.Enumerator()->Accept(*this);
}

void EnumCreator::Visit(otava::ast::EnumeratorNode& node)
{
    node.Identifier()->Accept(*this);
}

void EnumCreator::Visit(otava::ast::ElaboratedEnumSpecifierNode& node)
{
    if (!Valid()) return;
    opaque = true;
    node.Child()->Accept(*this);
    if (!Valid()) return;
    opaque = false;
}

void EnumCreator::Visit(otava::ast::OpaqueEnumDeclarationNode& node)
{
    if (!Valid()) return;
    opaque = true;
    node.EnumKey()->Accept(*this);
    if (!Valid()) return;
    if (node.EnumBase())
    {
        node.EnumBase()->Accept(*this);
        if (!Valid()) return;
    }
    node.EnumHeadName()->Accept(*this);
    if (!Valid()) return;
    opaque = false;
}

void EnumCreator::Visit(otava::ast::QualifiedIdNode& node)
{
    if (!Valid()) return;
    std::expected<Scope*, int> rv = ResolveScope(node.Left(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    scope = *rv;
    node.Right()->Accept(*this);
}

void EnumCreator::Visit(otava::ast::IdentifierNode& node)
{
    if (!Valid()) return;
    if (createEnumeratedType)
    {
        context->GetSymbolTable()->BeginScope(scope);
        if (opaque)
        {
            std::expected<bool, int> rv = context->GetSymbolTable()->AddForwardEnumDeclaration(node.Str(), enumTypeKind, underlyingType, &node, context);
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
        }
        else
        {
            std::expected<bool, int> rv = context->GetSymbolTable()->BeginEnumeratedType(node.Str(), enumTypeKind, underlyingType, &node, context);
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
        }
    }
    if (createEnumerators)
    {
        std::expected<bool, int> rv = context->GetSymbolTable()->AddEnumerator(node.Str(), value, &node, context);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
    }
}

void EnumCreator::Visit(otava::ast::UnnamedNode& node)
{
    if (!Valid()) return;
    context->GetSymbolTable()->BeginScope(scope);
    std::expected<bool, int> rv = context->GetSymbolTable()->BeginEnumeratedType(std::u32string(), enumTypeKind, underlyingType, &node, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

std::expected<bool, int> BeginEnumType(otava::ast::Node* node, Context* context)
{
    EnumCreator creator(context, true, false);
    node->Accept(creator);
    if (!creator) return std::unexpected<int>(creator.Error());
    return std::expected<bool, int>(true);
}

std::expected<bool, int> AddEnumerators(otava::ast::Node* node, Context* context)
{
    EnumCreator creator(context, false, true);
    node->Accept(creator);
    if (!creator) return std::unexpected<int>(creator.Error());
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EndEnumType(otava::ast::Node* node, Context* context)
{
    Symbol* currentSymbol = context->GetSymbolTable()->CurrentScope()->GetSymbol();
    if (!currentSymbol->IsEnumeratedTypeSymbol())
    {
        return Error("otava.symbols.enums: EndEnumeratedType(): enum scope expected", node->GetSourcePos(), context);
    }
    EnumeratedTypeSymbol* enumType = static_cast<EnumeratedTypeSymbol*>(currentSymbol);
    std::expected<bool, int> rv = context->GetSymbolTable()->EndEnumeratedType();
    if (!rv) return rv;
    rv = context->GetSymbolTable()->EndScope();
    if (!rv) return std::unexpected<int>(rv.error());
    rv = BindEnumType(enumType, node->GetSourcePos(), context);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ProcessEnumForwardDeclaration(otava::ast::Node* node, Context* context)
{
    EnumCreator creator(context, true, false);
    node->Accept(creator);
    if (!creator) return std::unexpected<int>(creator.Error());
    std::expected<bool, int> erv = context->GetSymbolTable()->EndScope();
    if (!erv) return std::unexpected<int>(erv.error());
    return std::expected<bool, int>(true);
}

EnumTypeDefaultCtor::EnumTypeDefaultCtor(const std::u32string& name_) : FunctionSymbol(SymbolKind::enumTypeDefaultCtor, name_), enumType(nullptr)
{
}

EnumTypeDefaultCtor::EnumTypeDefaultCtor(EnumeratedTypeSymbol* enumType_, Context* context) : 
    FunctionSymbol(SymbolKind::enumTypeDefaultCtor, U"@constructor"), enumType(enumType_)
{
    SetFunctionKind(FunctionKind::constructor);
    SetAccess(Access::public_);
    std::expected<TypeSymbol*, int> pt = enumType->AddPointer(context);
    if (!pt)
    {
        SetError(pt.error());
        return;
    }
    ParameterSymbol* thisParam = new ParameterSymbol(U"this", *pt);
    std::expected<bool, int> rv = AddParameter(thisParam, soul::ast::SourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

std::expected<bool, int> EnumTypeDefaultCtor::Write(Writer& writer)
{
    std::expected<bool, int> rv = FunctionSymbol::Write(writer);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(enumType->Id());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EnumTypeDefaultCtor::Read(Reader& reader)
{
    std::expected<bool, int> rv = FunctionSymbol::Read(reader);
    if (!rv) return rv;
    rv = reader.GetBinaryStreamReader().ReadUuid(enumTypeId);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EnumTypeDefaultCtor::Resolve(SymbolTable& symbolTable, Context* context)
{
    std::expected<bool, int> rv = FunctionSymbol::Resolve(symbolTable, context);
    TypeSymbol* type = symbolTable.GetType(enumTypeId);
    if (type && type->IsEnumeratedTypeSymbol())
    {
        enumType = static_cast<EnumeratedTypeSymbol*>(type);
    }
    else
    {
        return std::unexpected<int>(util::AllocateError("otava.symbols.enums: enum type expected"));
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EnumTypeDefaultCtor::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    if ((flags & OperationFlags::defaultInit) != OperationFlags::none)
    {
        auto rv = enumType->IrType(emitter, sourcePos, context);
        if (!rv) return std::unexpected<int>(rv.error());
        otava::intermediate::Type* irType = *rv;
        emitter.Stack().Push(irType->DefaultValue());
        OperationFlags storeFlags = OperationFlags::none;
        if ((flags & OperationFlags::storeDeref) != OperationFlags::none)
        {
            storeFlags = storeFlags | OperationFlags::deref;
        }
        std::expected<bool, int> srv = args[0]->Store(emitter, storeFlags, sourcePos, context);
        if (!srv) return srv;
    }
    return std::expected<bool, int>(true);
}

EnumTypeCopyCtor::EnumTypeCopyCtor(const std::u32string& name_) : FunctionSymbol(SymbolKind::enumTypeCopyCtor, name_), enumType(nullptr)
{
}

EnumTypeCopyCtor::EnumTypeCopyCtor(EnumeratedTypeSymbol* enumType_, Context* context) : FunctionSymbol(SymbolKind::enumTypeCopyCtor, U"@constructor"), enumType(enumType_)
{
    SetFunctionKind(FunctionKind::constructor);
    SetAccess(Access::public_);
    std::expected<TypeSymbol*, int> pt = enumType->AddPointer(context);
    if (!pt)
    {
        SetError(pt.error());
        return;
    }
    ParameterSymbol* thisParam = new ParameterSymbol(U"this", *pt);
    std::expected<bool, int> rv = AddParameter(thisParam, soul::ast::SourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    ParameterSymbol* thatParam = new ParameterSymbol(U"that", enumType);
    rv = AddParameter(thatParam, soul::ast::SourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

std::expected<bool, int> EnumTypeCopyCtor::Write(Writer& writer)
{
    std::expected<bool, int> rv = FunctionSymbol::Write(writer);
    if (!rv)  return rv;
    rv = writer.GetBinaryStreamWriter().Write(enumType->Id());
    if (!rv)  return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EnumTypeCopyCtor::Read(Reader& reader)
{
    std::expected<bool, int> rv = FunctionSymbol::Read(reader);
    if (!rv)  return rv;
    rv = reader.GetBinaryStreamReader().ReadUuid(enumTypeId);
    if (!rv)  return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EnumTypeCopyCtor::Resolve(SymbolTable& symbolTable, Context* context)
{
    std::expected<bool, int> rv = FunctionSymbol::Resolve(symbolTable, context);
    if (!rv) return rv;
    TypeSymbol* type = symbolTable.GetType(enumTypeId);
    if (type && type->IsEnumeratedTypeSymbol())
    {
        enumType = static_cast<EnumeratedTypeSymbol*>(type);
    }
    else
    {
        return std::unexpected<int>(util::AllocateError("otava.symbols.enums: enum type expected"));
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EnumTypeCopyCtor::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    std::expected<bool, int> lrv = args[1]->Load(emitter, OperationFlags::none, sourcePos, context);
    if (!lrv.error()) return lrv;
    OperationFlags storeFlags = OperationFlags::none;
    if ((flags & OperationFlags::storeDeref) != OperationFlags::none)
    {
        storeFlags = storeFlags | OperationFlags::deref;
    }
    std::expected<bool, int> srv = args[0]->Store(emitter, storeFlags, sourcePos, context);
    if (!srv) return srv;
    return std::expected<bool, int>(true);
}

EnumTypeMoveCtor::EnumTypeMoveCtor(const std::u32string& name_) : FunctionSymbol(SymbolKind::enumTypeMoveCtor, name_), enumType(nullptr)
{
}

EnumTypeMoveCtor::EnumTypeMoveCtor(EnumeratedTypeSymbol* enumType_, Context* context) : FunctionSymbol(SymbolKind::enumTypeMoveCtor, U"@constructor"), enumType(enumType_)
{
    SetFunctionKind(FunctionKind::constructor);
    SetAccess(Access::public_);
    std::expected<TypeSymbol*, int> pt = enumType->AddPointer(context);
    if (!pt)
    {
        SetError(pt.error());
        return;
    }
    ParameterSymbol* thisParam = new ParameterSymbol(U"this", *pt);
    std::expected<bool, int> rv = AddParameter(thisParam, soul::ast::SourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    pt = enumType->AddRValueRef(context);
    if (!pt)
    {
        SetError(pt.error());
        return;
    }
    TypeSymbol* type = *pt;
    ParameterSymbol* thatParam = new ParameterSymbol(U"that", type);
    rv = AddParameter(thatParam, soul::ast::SourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

std::expected<bool, int> EnumTypeMoveCtor::Write(Writer& writer)
{
    std::expected<bool, int> rv = FunctionSymbol::Write(writer);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(enumType->Id());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EnumTypeMoveCtor::Read(Reader& reader)
{
    std::expected<bool, int> rv = FunctionSymbol::Read(reader);
    if (!rv) return rv;
    rv = reader.GetBinaryStreamReader().ReadUuid(enumTypeId);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EnumTypeMoveCtor::Resolve(SymbolTable& symbolTable, Context* context)
{
    std::expected<bool, int> rv = FunctionSymbol::Resolve(symbolTable, context);
    if (!rv) return rv;
    TypeSymbol* type = symbolTable.GetType(enumTypeId);
    if (type && type->IsEnumeratedTypeSymbol())
    {
        enumType = static_cast<EnumeratedTypeSymbol*>(type);
    }
    else
    {
        return std::unexpected<int>(util::AllocateError("otava.symbols.enums: enum type expected"));
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EnumTypeMoveCtor::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    std::expected<bool, int> lrv = args[1]->Load(emitter, OperationFlags::none, sourcePos, context);
    if (!lrv) return lrv;
    otava::intermediate::Value* rvalueRefValue = emitter.Stack().Pop();
    std::expected<otava::intermediate::Instruction*, int> rv = emitter.EmitLoad(rvalueRefValue);
    if (!rv) return std::unexpected<int>(rv.error());
    emitter.Stack().Push(*rv);
    OperationFlags storeFlags = OperationFlags::none;
    if ((flags & OperationFlags::storeDeref) != OperationFlags::none)
    {
        storeFlags = storeFlags | OperationFlags::deref;
    }
    std::expected<bool, int> srv = args[0]->Store(emitter, storeFlags, sourcePos, context);
    if (!srv) return srv;
    return std::expected<bool, int>(true);
}

EnumTypeCopyAssignment::EnumTypeCopyAssignment(const std::u32string& name_) : FunctionSymbol(SymbolKind::enumTypeCopyAssignment, name_), enumType(nullptr)
{
}

EnumTypeCopyAssignment::EnumTypeCopyAssignment(EnumeratedTypeSymbol* enumType_, Context* context) :
    FunctionSymbol(SymbolKind::enumTypeCopyAssignment, U"operator="), enumType(enumType_)
{
    SetFunctionKind(FunctionKind::special);
    SetAccess(Access::public_);
    std::expected<TypeSymbol*, int> pt = enumType->AddPointer(context);
    if (!pt)
    {
        SetError(pt.error());
        return;
    }
    ParameterSymbol* thisParam = new ParameterSymbol(U"this", *pt);
    std::expected<bool, int> rv = AddParameter(thisParam, soul::ast::SourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    ParameterSymbol* thatParam = new ParameterSymbol(U"that", enumType);
    rv = AddParameter(thatParam, soul::ast::SourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

std::expected<bool, int> EnumTypeCopyAssignment::Write(Writer& writer)
{
    std::expected<bool, int> rv = FunctionSymbol::Write(writer);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(enumType->Id());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EnumTypeCopyAssignment::Read(Reader& reader)
{
    std::expected<bool, int> rv = FunctionSymbol::Read(reader);
    if (!rv) return rv;
    rv = reader.GetBinaryStreamReader().ReadUuid(enumTypeId);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EnumTypeCopyAssignment::Resolve(SymbolTable& symbolTable, Context* context)
{
    std::expected<bool, int> rv = FunctionSymbol::Resolve(symbolTable, context);
    if (!rv) return rv;
    TypeSymbol* type = symbolTable.GetType(enumTypeId);
    if (type && type->IsEnumeratedTypeSymbol())
    {
        enumType = static_cast<EnumeratedTypeSymbol*>(type);
    }
    else
    {
        return std::unexpected<int>(util::AllocateError("otava.symbols.enums: enum type expected"));
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EnumTypeCopyAssignment::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    std::expected<bool, int> lrv = args[1]->Load(emitter, OperationFlags::none, sourcePos, context);
    if (!lrv) return lrv;
    std::expected<bool, int> srv = args[0]->Store(emitter, OperationFlags::none, sourcePos, context);
    if (!srv) return srv;
    emitter.Stack().Push(context->Ptr());
    return std::expected<bool, int>(true);
}

EnumTypeMoveAssignment::EnumTypeMoveAssignment(const std::u32string& name_) : FunctionSymbol(SymbolKind::enumTypeMoveAssignment, name_), enumType(nullptr)
{
}

EnumTypeMoveAssignment::EnumTypeMoveAssignment(EnumeratedTypeSymbol* enumType_, Context* context) :
    FunctionSymbol(SymbolKind::enumTypeMoveAssignment, U"operator="), enumType(enumType_)
{
    SetFunctionKind(FunctionKind::special);
    SetAccess(Access::public_);
    std::expected<TypeSymbol*, int> pt = enumType->AddPointer(context);
    if (!pt)
    {
        SetError(pt.error());
        return;
    }
    ParameterSymbol* thisParam = new ParameterSymbol(U"this", *pt);
    std::expected<bool, int> rv = AddParameter(thisParam, soul::ast::SourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    pt = enumType->AddRValueRef(context);
    if (!pt)
    {
        SetError(pt.error());
        return;
    }
    TypeSymbol* type = *pt;
    ParameterSymbol* thatParam = new ParameterSymbol(U"that", type);
    rv = AddParameter(thatParam, soul::ast::SourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

std::expected<bool, int> EnumTypeMoveAssignment::Write(Writer& writer)
{
    std::expected<bool, int> rv = FunctionSymbol::Write(writer);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(enumType->Id());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EnumTypeMoveAssignment::Read(Reader& reader)
{
    std::expected<bool, int> rv = FunctionSymbol::Read(reader);
    if (!rv) return rv;
    rv = reader.GetBinaryStreamReader().ReadUuid(enumTypeId);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EnumTypeMoveAssignment::Resolve(SymbolTable& symbolTable, Context* context)
{
    std::expected<bool, int> rv = FunctionSymbol::Resolve(symbolTable, context);
    if (!rv) return rv;
    TypeSymbol* type = symbolTable.GetType(enumTypeId);
    if (type && type->IsEnumeratedTypeSymbol())
    {
        enumType = static_cast<EnumeratedTypeSymbol*>(type);
    }
    else
    {
        return std::unexpected<int>(util::AllocateError("otava.symbols.enums: enum type expected"));
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EnumTypeMoveAssignment::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    std::expected<bool, int> lrv = args[1]->Load(emitter, OperationFlags::none, sourcePos, context);
    if (!lrv) return lrv;
    otava::intermediate::Value* refValue = emitter.Stack().Pop();
    std::expected<otava::intermediate::Instruction*, int> rv = emitter.EmitLoad(refValue);
    if (!rv) return std::unexpected<int>(rv.error());
    emitter.Stack().Push(*rv);
    std::expected<bool, int> srv = args[0]->Store(emitter, OperationFlags::setPtr, sourcePos, context);
    if (!srv) return srv;
    emitter.Stack().Push(context->Ptr());
    return std::expected<bool, int>(true);
}

EnumTypeEqual::EnumTypeEqual(const std::u32string& name_) : FunctionSymbol(SymbolKind::enumTypeEqual, name_), enumType(nullptr)
{
}

EnumTypeEqual::EnumTypeEqual(EnumeratedTypeSymbol* enumType_, Context* context) : FunctionSymbol(SymbolKind::enumTypeEqual, U"operator=="), enumType(enumType_)
{
    SetFunctionKind(FunctionKind::function);
    SetAccess(Access::public_);
    ParameterSymbol* leftParam = new ParameterSymbol(U"left", enumType);
    std::expected<bool, int> rv = AddParameter(leftParam, soul::ast::SourcePos(), nullptr);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    ParameterSymbol* rightParam = new ParameterSymbol(U"right", enumType);
    rv = AddParameter(rightParam, soul::ast::SourcePos(), nullptr);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    TypeSymbol* boolType = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::boolType);
    rv = SetReturnType(boolType, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

std::expected<bool, int> EnumTypeEqual::Write(Writer& writer)
{
    std::expected<bool, int> rv = FunctionSymbol::Write(writer);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(enumType->Id());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EnumTypeEqual::Read(Reader& reader)
{
    std::expected<bool, int> rv = FunctionSymbol::Read(reader);
    if (!rv) return rv;
    rv = reader.GetBinaryStreamReader().ReadUuid(enumTypeId);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EnumTypeEqual::Resolve(SymbolTable& symbolTable, Context* context)
{
    std::expected<bool, int> rv = FunctionSymbol::Resolve(symbolTable, context);
    if (!rv) return rv;
    TypeSymbol* type = symbolTable.GetType(enumTypeId);
    if (type && type->IsEnumeratedTypeSymbol())
    {
        enumType = static_cast<EnumeratedTypeSymbol*>(type);
    }
    else
    {
        return std::unexpected<int>(util::AllocateError("otava.symbols.enums: enum type expected"));
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EnumTypeEqual::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    std::expected<bool, int> lrv = args[0]->Load(emitter, flags, sourcePos, context);
    if (!lrv) return lrv;
    otava::intermediate::Value* left = emitter.Stack().Pop();
    lrv = args[1]->Load(emitter, OperationFlags::none, sourcePos, context);
    if (!lrv) return lrv;
    otava::intermediate::Value* right = emitter.Stack().Pop();
    emitter.Stack().Push(emitter.EmitEqual(left, right));
    return std::expected<bool, int>(true);
}

EnumTypeLess::EnumTypeLess(const std::u32string& name_) : FunctionSymbol(SymbolKind::enumTypeLess, name_), enumType(nullptr)
{
}

EnumTypeLess::EnumTypeLess(EnumeratedTypeSymbol* enumType_, Context* context) : FunctionSymbol(SymbolKind::enumTypeLess, U"operator<"), enumType(enumType_)
{
    SetFunctionKind(FunctionKind::function);
    SetAccess(Access::public_);
    ParameterSymbol* leftParam = new ParameterSymbol(U"left", enumType);
    std::expected<bool, int> rv = AddParameter(leftParam, soul::ast::SourcePos(), nullptr);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    ParameterSymbol* rightParam = new ParameterSymbol(U"right", enumType);
    rv = AddParameter(rightParam, soul::ast::SourcePos(), nullptr);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    TypeSymbol* boolType = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::boolType);
    rv = SetReturnType(boolType, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

std::expected<bool, int> EnumTypeLess::Write(Writer& writer)
{
    std::expected<bool, int> rv = FunctionSymbol::Write(writer);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(enumType->Id());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EnumTypeLess::Read(Reader& reader)
{
    std::expected<bool, int> rv = FunctionSymbol::Read(reader);
    if (!rv) return rv;
    rv = reader.GetBinaryStreamReader().ReadUuid(enumTypeId);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EnumTypeLess::Resolve(SymbolTable& symbolTable, Context* context)
{
    std::expected<bool, int> rv = FunctionSymbol::Resolve(symbolTable, context);
    if (!rv) return rv;
    TypeSymbol* type = symbolTable.GetType(enumTypeId);
    if (type && type->IsEnumeratedTypeSymbol())
    {
        enumType = static_cast<EnumeratedTypeSymbol*>(type);
    }
    else
    {
        return std::unexpected<int>(util::AllocateError("otava.symbols.enums: enum type expected"));
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EnumTypeLess::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    std::expected<bool, int> lrv = args[0]->Load(emitter, flags, sourcePos, context);
    if (!lrv) return lrv;
    otava::intermediate::Value* left = emitter.Stack().Pop();
    lrv = args[1]->Load(emitter, OperationFlags::none, sourcePos, context);
    if (!lrv) return lrv;
    otava::intermediate::Value* right = emitter.Stack().Pop();
    emitter.Stack().Push(emitter.EmitLess(left, right));
    return std::expected<bool, int>(true);
}

std::expected<bool, int> BindEnumType(EnumeratedTypeSymbol* enumType, const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (enumType->IsBound()) return std::expected<bool, int>(false);
    enumType->SetBound();
    Scope* scope = enumType->GetScope();
    std::expected<FunctionGroupSymbol*, int> frv = scope->GetOrInsertFunctionGroup(U"@constructor", sourcePos, context);
    if (!frv) return std::unexpected<int>(frv.error());
    FunctionGroupSymbol * constructorGroup = *frv;
    EnumTypeDefaultCtor* enumTypeDefaultCtor = new EnumTypeDefaultCtor(enumType, context);
    std::expected<bool, int> rv = scope->AddSymbol(enumTypeDefaultCtor, sourcePos, context);
    if (!rv) return rv;
    constructorGroup->AddFunction(enumTypeDefaultCtor);
    EnumTypeCopyCtor* enumTypeCopyCtor = new EnumTypeCopyCtor(enumType, context);
    rv = scope->AddSymbol(enumTypeCopyCtor, sourcePos, context);
    if (!rv) return rv;
    constructorGroup->AddFunction(enumTypeCopyCtor);
    EnumTypeMoveCtor* enumTypeMoveCtor = new EnumTypeMoveCtor(enumType, context);
    rv = scope->AddSymbol(enumTypeMoveCtor, sourcePos, context);
    if (!rv) return rv;
    constructorGroup->AddFunction(enumTypeMoveCtor);

    frv = scope->GetOrInsertFunctionGroup(U"@destructor", sourcePos, context);
    if (!frv) return std::unexpected<int>(frv.error());
    FunctionGroupSymbol* destructorGroup = *frv;
    TrivialDestructor* trivialDestructor = new TrivialDestructor(enumType, context);
    rv = scope->AddSymbol(trivialDestructor, sourcePos, context);
    if (!rv) return rv;
    destructorGroup->AddFunction(trivialDestructor);

    frv = scope->GetOrInsertFunctionGroup(U"operator=", sourcePos, context);
    if (!frv) return std::unexpected<int>(frv.error());
    FunctionGroupSymbol* assignmentGroup = *frv;
    EnumTypeCopyAssignment* enumTypeCopyAssignment = new EnumTypeCopyAssignment(enumType, context);
    rv = scope->AddSymbol(enumTypeCopyAssignment, sourcePos, context);
    if (!rv) return rv;
    assignmentGroup->AddFunction(enumTypeCopyAssignment);
    EnumTypeMoveAssignment* enumTypeMoveAssignment = new EnumTypeMoveAssignment(enumType, context);
    rv = scope->AddSymbol(enumTypeMoveAssignment, sourcePos, context);
    if (!rv) return rv;
    assignmentGroup->AddFunction(enumTypeMoveAssignment);

    frv = scope->GetOrInsertFunctionGroup(U"operator==", sourcePos, context);
    if (!frv) return std::unexpected<int>(frv.error());
    FunctionGroupSymbol* equalGroup = *frv;
    EnumTypeEqual* enumTypeEqual = new EnumTypeEqual(enumType, context);
    rv = scope->AddSymbol(enumTypeEqual, sourcePos, context);
    if (!rv) return rv;
    equalGroup->AddFunction(enumTypeEqual);

    frv = scope->GetOrInsertFunctionGroup(U"operator<", sourcePos, context);
    if (!frv) return std::unexpected<int>(frv.error());
    FunctionGroupSymbol* lessGroup = *frv;
    EnumTypeLess* enumTypeLess = new EnumTypeLess(enumType, context);
    rv = scope->AddSymbol(enumTypeLess, sourcePos, context);
    if (!rv) return rv;
    lessGroup->AddFunction(enumTypeLess);
    return std::expected<bool, int>(true);
}

} // namespace otava::symbols
