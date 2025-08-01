// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.enums;

import util;
import otava.ast;
import otava.symbols.context;
import otava.symbols.emitter;
import otava.symbols.exception;
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

void EnumeratedTypeSymbol::Write(Writer& writer)
{
    TypeSymbol::Write(writer);
    writer.GetBinaryStreamWriter().Write(bound);
    writer.GetBinaryStreamWriter().Write(static_cast<std::uint8_t>(kind));
    bool hasUnderlyingType = underlyingType != nullptr;
    writer.GetBinaryStreamWriter().Write(hasUnderlyingType);
    if (hasUnderlyingType)
    {
        writer.GetBinaryStreamWriter().Write(underlyingType->Id());
    }
}

void EnumeratedTypeSymbol::Read(Reader& reader)
{
    TypeSymbol::Read(reader);
    bound = reader.GetBinaryStreamReader().ReadBool();
    kind = static_cast<EnumTypeKind>(reader.GetBinaryStreamReader().ReadByte());
    bool hasUnderlyingType = reader.GetBinaryStreamReader().ReadBool();
    if (hasUnderlyingType)
    {
        reader.GetBinaryStreamReader().ReadUuid(underlyingTypeId);
    }
}

void EnumeratedTypeSymbol::Resolve(SymbolTable& symbolTable)
{
    TypeSymbol::Resolve(symbolTable);
    if (underlyingTypeId != util::nil_uuid())
    {
        underlyingType = symbolTable.GetType(underlyingTypeId);
    }
}

void EnumeratedTypeSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

otava::intermediate::Type* EnumeratedTypeSymbol::IrType(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (underlyingType)
    {
        return underlyingType->IrType(emitter, sourcePos, context);
    }
    else
    {
        return emitter.GetIntType();
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

void ForwardEnumDeclarationSymbol::Write(Writer& writer)
{
    TypeSymbol::Write(writer);
    writer.GetBinaryStreamWriter().Write(static_cast<std::uint8_t>(enumTypeKind));
    bool hasUnderlyingType = underlyingType != nullptr;
    writer.GetBinaryStreamWriter().Write(hasUnderlyingType);
    if (hasUnderlyingType)
    {
        writer.GetBinaryStreamWriter().Write(underlyingType->Id());
    }
    writer.GetBinaryStreamWriter().Write(enumTypeSymbol != nullptr);
    if (enumTypeSymbol)
    {
        writer.GetBinaryStreamWriter().Write(enumTypeSymbol->Id());
    }
}

void ForwardEnumDeclarationSymbol::Read(Reader& reader)
{
    TypeSymbol::Read(reader);
    enumTypeKind = static_cast<EnumTypeKind>(reader.GetBinaryStreamReader().ReadByte());
    bool hasUnderlyingType = reader.GetBinaryStreamReader().ReadBool();
    if (hasUnderlyingType)
    {
        reader.GetBinaryStreamReader().ReadUuid(underlyingTypeId);
    }
    bool hasEnumType = reader.GetBinaryStreamReader().ReadBool();
    if (hasEnumType)
    {
        reader.GetBinaryStreamReader().ReadUuid(enumTypeSymbolId);
    }
}

void ForwardEnumDeclarationSymbol::Resolve(SymbolTable& symbolTable)
{
    TypeSymbol::Resolve(symbolTable);
    if (underlyingTypeId != util::nil_uuid())
    {
        underlyingType = symbolTable.GetType(underlyingTypeId);
    }
    if (enumTypeSymbolId != util::nil_uuid())
    {
        TypeSymbol* type = symbolTable.GetType(enumTypeSymbolId);
        if (type->IsEnumeratedTypeSymbol())
        {
            enumTypeSymbol = static_cast<EnumeratedTypeSymbol*>(type);
        }
        else
        {
            otava::ast::SetExceptionThrown();
            throw std::runtime_error("otava.symbols.enums: enum type expected");
        }
    }
}

EnumConstantSymbol::EnumConstantSymbol(const std::u32string& name_) : Symbol(SymbolKind::enumConstantSymbol, name_), value(), valueId()
{
}

bool EnumConstantSymbol::IsValidDeclarationScope(ScopeKind scopeKind) const
{
    return scopeKind == ScopeKind::enumerationScope;
}

void EnumConstantSymbol::Write(Writer& writer)
{
    Symbol::Write(writer);
    writer.GetBinaryStreamWriter().Write(value->Id());
}

void EnumConstantSymbol::Read(Reader& reader)
{
    Symbol::Read(reader);
    reader.GetBinaryStreamReader().ReadUuid(valueId);
}

void EnumConstantSymbol::Resolve(SymbolTable& symbolTable)
{
    Symbol::Resolve(symbolTable);
    EvaluationContext* evaluationContext = symbolTable.GetModule()->GetEvaluationContext();
    value = evaluationContext->GetValue(valueId);
}

void EnumConstantSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

EnumeratedTypeSymbol* EnumConstantSymbol::GetType() const
{
    const Symbol* parent = Parent();
    if (parent && parent->IsEnumeratedTypeSymbol())
    {
        return const_cast<EnumeratedTypeSymbol*>(static_cast<const EnumeratedTypeSymbol*>(parent));
    }
    return nullptr;
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
    if (createEnumeratedType)
    {
        node.EnumHead()->Accept(*this);
    }
    else if (createEnumerators)
    {
        first = true;
        VisitListContent(node);
    }
}

void EnumCreator::Visit(otava::ast::EnumHeadNode& node)
{
    node.EnumKey()->Accept(*this);
    if (node.EnumBase())
    {
        node.EnumBase()->Accept(*this);
    }
    node.EnumHeadName()->Accept(*this);
}

void EnumCreator::Visit(otava::ast::EnumBaseNode& node)
{
    underlyingType = ResolveType(node.Child(), DeclarationFlags::none, context);
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
    Symbol* currentSymbol = context->GetSymbolTable()->CurrentScope()->GetSymbol();
    if (!currentSymbol->IsEnumeratedTypeSymbol())
    {
        ThrowException("otava.symbols.enums: EnumCreator(): enum scope expected", node.GetSourcePos(), context);
    }
    EnumeratedTypeSymbol* enumType = static_cast<EnumeratedTypeSymbol*>(currentSymbol);
    TypeSymbol* valueType = enumType->UnderlyingType();
    if (!valueType)
    {
        valueType = context->GetSymbolTable()->GetFundamentalTypeSymbol(FundamentalTypeKind::intType);
    }
    if (node.Value())
    {
        Value* val = Evaluate(node.Value(), context);
        if (val->IsIntegerValue())
        {
            IntegerValue* intVal = static_cast<IntegerValue*>(val);
            value = context->GetEvaluationContext()->GetIntegerValue(intVal->GetValue(), util::ToUtf32(std::to_string(intVal->GetValue())), valueType);
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
            value = context->GetEvaluationContext()->GetIntegerValue(0, util::ToUtf32(std::to_string(0)), valueType);
            prevValue = 0;
            first = false;
        }
        else
        {
            value = context->GetEvaluationContext()->GetIntegerValue(prevValue + 1, util::ToUtf32(std::to_string(prevValue + 1)), valueType);
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
    opaque = true;
    node.Child()->Accept(*this);
    opaque = false;
}

void EnumCreator::Visit(otava::ast::OpaqueEnumDeclarationNode& node)
{
    opaque = true;
    node.EnumKey()->Accept(*this);
    if (node.EnumBase())
    {
        node.EnumBase()->Accept(*this);
    }
    node.EnumHeadName()->Accept(*this);
    opaque = false;
}

void EnumCreator::Visit(otava::ast::QualifiedIdNode& node)
{
    scope = ResolveScope(node.Left(), context);
    node.Right()->Accept(*this);
}

void EnumCreator::Visit(otava::ast::IdentifierNode& node)
{
    if (createEnumeratedType)
    {
        context->GetSymbolTable()->BeginScope(scope);
        if (opaque)
        {
            context->GetSymbolTable()->AddForwardEnumDeclaration(node.Str(), enumTypeKind, underlyingType, &node, context);
        }
        else
        {
            context->GetSymbolTable()->BeginEnumeratedType(node.Str(), enumTypeKind, underlyingType, &node, context);
        }
    }
    if (createEnumerators)
    {
        context->GetSymbolTable()->AddEnumerator(node.Str(), value, &node, context);
    }
}

void EnumCreator::Visit(otava::ast::UnnamedNode& node)
{
    context->GetSymbolTable()->BeginScope(scope);
    context->GetSymbolTable()->BeginEnumeratedType(std::u32string(), enumTypeKind, underlyingType, &node, context);
}

void BeginEnumType(otava::ast::Node* node, Context* context)
{
    EnumCreator creator(context, true, false);
    node->Accept(creator);
}

void AddEnumerators(otava::ast::Node* node, Context* context)
{
    EnumCreator creator(context, false, true);
    node->Accept(creator);
}

void EndEnumType(otava::ast::Node* node, Context* context)
{
    Symbol* currentSymbol = context->GetSymbolTable()->CurrentScope()->GetSymbol();
    if (!currentSymbol->IsEnumeratedTypeSymbol())
    {
        ThrowException("cpp20.symbols.enums: EndEnumeratedType(): enum scope expected", node->GetSourcePos(), context);
    }
    EnumeratedTypeSymbol* enumType = static_cast<EnumeratedTypeSymbol*>(currentSymbol);
    context->GetSymbolTable()->EndEnumeratedType();
    context->GetSymbolTable()->EndScope();
    BindEnumType(enumType, node->GetSourcePos(), context);
}

void ProcessEnumForwardDeclaration(otava::ast::Node* node, Context* context)
{
    EnumCreator creator(context, true, false);
    node->Accept(creator);
    context->GetSymbolTable()->EndScope();
}

EnumTypeDefaultCtor::EnumTypeDefaultCtor(const std::u32string& name_) : FunctionSymbol(SymbolKind::enumTypeDefaultCtor, name_), enumType(nullptr)
{
}

EnumTypeDefaultCtor::EnumTypeDefaultCtor(EnumeratedTypeSymbol* enumType_, Context* context) : FunctionSymbol(SymbolKind::enumTypeDefaultCtor, U"@constructor"), enumType(enumType_)
{
    SetFunctionKind(FunctionKind::constructor);
    SetAccess(Access::public_);
    ParameterSymbol* thisParam = new ParameterSymbol(U"this", enumType->AddPointer(context));
    AddParameter(thisParam, soul::ast::SourcePos(), context);
}

void EnumTypeDefaultCtor::Write(Writer& writer)
{
    FunctionSymbol::Write(writer);
    writer.GetBinaryStreamWriter().Write(enumType->Id());
}

void EnumTypeDefaultCtor::Read(Reader& reader)
{
    FunctionSymbol::Read(reader);
    reader.GetBinaryStreamReader().ReadUuid(enumTypeId);
}

void EnumTypeDefaultCtor::Resolve(SymbolTable& symbolTable)
{
    FunctionSymbol::Resolve(symbolTable);
    TypeSymbol* type = symbolTable.GetType(enumTypeId);
    if (type->IsEnumeratedTypeSymbol())
    {
        enumType = static_cast<EnumeratedTypeSymbol*>(type);
    }
    else
    { 
        otava::ast::SetExceptionThrown();
        throw std::runtime_error("otava.symbols.enums: enum type expected");
    }
}

void EnumTypeDefaultCtor::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    if ((flags & OperationFlags::defaultInit) != OperationFlags::none)
    {
        emitter.Stack().Push(enumType->IrType(emitter, sourcePos, context)->DefaultValue());
        args[0]->Store(emitter, OperationFlags::none, sourcePos, context);
    }
}

EnumTypeCopyCtor::EnumTypeCopyCtor(const std::u32string& name_) : FunctionSymbol(SymbolKind::enumTypeCopyCtor, name_), enumType(nullptr)
{
}

EnumTypeCopyCtor::EnumTypeCopyCtor(EnumeratedTypeSymbol* enumType_, Context* context) : FunctionSymbol(SymbolKind::enumTypeCopyCtor, U"@constructor"), enumType(enumType_)
{
    SetFunctionKind(FunctionKind::constructor);
    SetAccess(Access::public_);
    ParameterSymbol* thisParam = new ParameterSymbol(U"this", enumType->AddPointer(context));
    AddParameter(thisParam, soul::ast::SourcePos(), context);
    ParameterSymbol* thatParam = new ParameterSymbol(U"that", enumType);
    AddParameter(thatParam, soul::ast::SourcePos(), context);
}

void EnumTypeCopyCtor::Write(Writer& writer)
{
    FunctionSymbol::Write(writer);
    writer.GetBinaryStreamWriter().Write(enumType->Id());
}

void EnumTypeCopyCtor::Read(Reader& reader)
{
    FunctionSymbol::Read(reader);
    reader.GetBinaryStreamReader().ReadUuid(enumTypeId);
}

void EnumTypeCopyCtor::Resolve(SymbolTable& symbolTable)
{
    FunctionSymbol::Resolve(symbolTable);
    TypeSymbol* type = symbolTable.GetType(enumTypeId);
    if (type->IsEnumeratedTypeSymbol())
    {
        enumType = static_cast<EnumeratedTypeSymbol*>(type);
    }
    else
    {
        otava::ast::SetExceptionThrown();
        throw std::runtime_error("otava.symbols.enums: enum type expected");
    }
}

void EnumTypeCopyCtor::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) 
{
    args[1]->Load(emitter, OperationFlags::none, sourcePos, context);
    OperationFlags storeFlags = OperationFlags::none;
    if ((flags & OperationFlags::storeDeref) != OperationFlags::none)
    {
        storeFlags = storeFlags | OperationFlags::deref;
    }
    args[0]->Store(emitter, storeFlags, sourcePos, context);
}

EnumTypeMoveCtor::EnumTypeMoveCtor(const std::u32string& name_) : FunctionSymbol(SymbolKind::enumTypeMoveCtor, name_), enumType(nullptr)
{
}

EnumTypeMoveCtor::EnumTypeMoveCtor(EnumeratedTypeSymbol* enumType_, Context* context) : FunctionSymbol(SymbolKind::enumTypeMoveCtor, U"@constructor"), enumType(enumType_)
{
    SetFunctionKind(FunctionKind::constructor);
    SetAccess(Access::public_);
    ParameterSymbol* thisParam = new ParameterSymbol(U"this", enumType->AddPointer(context));
    AddParameter(thisParam, soul::ast::SourcePos(), context);
    ParameterSymbol* thatParam = new ParameterSymbol(U"that", enumType->AddRValueRef(context));
    AddParameter(thatParam, soul::ast::SourcePos(), context);
}

void EnumTypeMoveCtor::Write(Writer& writer)
{
    FunctionSymbol::Write(writer);
    writer.GetBinaryStreamWriter().Write(enumType->Id());
}

void EnumTypeMoveCtor::Read(Reader& reader)
{
    FunctionSymbol::Read(reader);
    reader.GetBinaryStreamReader().ReadUuid(enumTypeId);
}

void EnumTypeMoveCtor::Resolve(SymbolTable& symbolTable)
{
    FunctionSymbol::Resolve(symbolTable);
    TypeSymbol* type = symbolTable.GetType(enumTypeId);
    if (type->IsEnumeratedTypeSymbol())
    {
        enumType = static_cast<EnumeratedTypeSymbol*>(type);
    }
    else
    {
        otava::ast::SetExceptionThrown();
        throw std::runtime_error("otava.symbols.enums: enum type expected");
    }
}

void EnumTypeMoveCtor::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) 
{
    args[1]->Load(emitter, OperationFlags::none, sourcePos, context);
    otava::intermediate::Value* rvalueRefValue = emitter.Stack().Pop();
    emitter.Stack().Push(emitter.EmitLoad(rvalueRefValue));
    OperationFlags storeFlags = OperationFlags::none;
    if ((flags & OperationFlags::storeDeref) != OperationFlags::none)
    {
        storeFlags = storeFlags | OperationFlags::deref;
    }
    args[0]->Store(emitter, storeFlags, sourcePos, context);
}

EnumTypeCopyAssignment::EnumTypeCopyAssignment(const std::u32string& name_) : FunctionSymbol(SymbolKind::enumTypeCopyAssignment, name_), enumType(nullptr)
{
}

EnumTypeCopyAssignment::EnumTypeCopyAssignment(EnumeratedTypeSymbol* enumType_, Context* context) : 
    FunctionSymbol(SymbolKind::enumTypeCopyAssignment, U"operator="), enumType(enumType_)
{
    SetFunctionKind(FunctionKind::special);
    SetAccess(Access::public_);
    ParameterSymbol* thisParam = new ParameterSymbol(U"this", enumType->AddPointer(context));
    AddParameter(thisParam, soul::ast::SourcePos(), context);
    ParameterSymbol* thatParam = new ParameterSymbol(U"that", enumType);
    AddParameter(thatParam, soul::ast::SourcePos(), context);
}

void EnumTypeCopyAssignment::Write(Writer& writer)
{
    FunctionSymbol::Write(writer);
    writer.GetBinaryStreamWriter().Write(enumType->Id());
}

void EnumTypeCopyAssignment::Read(Reader& reader)
{
    FunctionSymbol::Read(reader);
    reader.GetBinaryStreamReader().ReadUuid(enumTypeId);
}

void EnumTypeCopyAssignment::Resolve(SymbolTable& symbolTable)
{
    FunctionSymbol::Resolve(symbolTable);
    TypeSymbol* type = symbolTable.GetType(enumTypeId);
    if (type->IsEnumeratedTypeSymbol())
    {
        enumType = static_cast<EnumeratedTypeSymbol*>(type);
    }
    else
    {
        otava::ast::SetExceptionThrown();
        throw std::runtime_error("otava.symbols.enums: enum type expected");
    }
}

void EnumTypeCopyAssignment::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    args[1]->Load(emitter, OperationFlags::none, sourcePos, context);
    args[0]->Store(emitter, OperationFlags::none, sourcePos, context);
    emitter.Stack().Push(context->Ptr());
}

EnumTypeMoveAssignment::EnumTypeMoveAssignment(const std::u32string& name_) : FunctionSymbol(SymbolKind::enumTypeMoveAssignment, name_), enumType(nullptr)
{
}

EnumTypeMoveAssignment::EnumTypeMoveAssignment(EnumeratedTypeSymbol* enumType_, Context* context) : 
    FunctionSymbol(SymbolKind::enumTypeMoveAssignment, U"operator="), enumType(enumType_)
{
    SetFunctionKind(FunctionKind::special);
    SetAccess(Access::public_);
    ParameterSymbol* thisParam = new ParameterSymbol(U"this", enumType->AddPointer(context));
    AddParameter(thisParam, soul::ast::SourcePos(), context);
    ParameterSymbol* thatParam = new ParameterSymbol(U"that", enumType->AddRValueRef(context));
    AddParameter(thatParam, soul::ast::SourcePos(), context);
}

void EnumTypeMoveAssignment::Write(Writer& writer)
{
    FunctionSymbol::Write(writer);
    writer.GetBinaryStreamWriter().Write(enumType->Id());
}

void EnumTypeMoveAssignment::Read(Reader& reader)
{
    FunctionSymbol::Read(reader);
    reader.GetBinaryStreamReader().ReadUuid(enumTypeId);
}

void EnumTypeMoveAssignment::Resolve(SymbolTable& symbolTable)
{
    FunctionSymbol::Resolve(symbolTable);
    TypeSymbol* type = symbolTable.GetType(enumTypeId);
    if (type->IsEnumeratedTypeSymbol())
    {
        enumType = static_cast<EnumeratedTypeSymbol*>(type);
    }
    else
    {
        otava::ast::SetExceptionThrown();
        throw std::runtime_error("otava.symbols.enums: enum type expected");
    }
}

void EnumTypeMoveAssignment::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    args[1]->Load(emitter, OperationFlags::none, sourcePos, context);
    otava::intermediate::Value* refValue = emitter.Stack().Pop();
    emitter.Stack().Push(emitter.EmitLoad(refValue));
    args[0]->Store(emitter, OperationFlags::setPtr, sourcePos, context);
    emitter.Stack().Push(context->Ptr());
}

EnumTypeEqual::EnumTypeEqual(const std::u32string& name_) : FunctionSymbol(SymbolKind::enumTypeEqual, name_), enumType(nullptr)
{
}

EnumTypeEqual::EnumTypeEqual(EnumeratedTypeSymbol* enumType_, Context* context) : FunctionSymbol(SymbolKind::enumTypeEqual, U"operator=="), enumType(enumType_)
{
    SetFunctionKind(FunctionKind::function);
    SetAccess(Access::public_);
    ParameterSymbol* leftParam = new ParameterSymbol(U"left", enumType);
    AddParameter(leftParam, soul::ast::SourcePos(), nullptr);
    ParameterSymbol* rightParam = new ParameterSymbol(U"right", enumType);
    AddParameter(rightParam, soul::ast::SourcePos(), nullptr);
    TypeSymbol* boolType = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::boolType);
    SetReturnType(boolType, context);
}

void EnumTypeEqual::Write(Writer& writer)
{
    FunctionSymbol::Write(writer);
    writer.GetBinaryStreamWriter().Write(enumType->Id());
}

void EnumTypeEqual::Read(Reader& reader)
{
    FunctionSymbol::Read(reader);
    reader.GetBinaryStreamReader().ReadUuid(enumTypeId);
}

void EnumTypeEqual::Resolve(SymbolTable& symbolTable)
{
    FunctionSymbol::Resolve(symbolTable);
    TypeSymbol* type = symbolTable.GetType(enumTypeId);
    if (type->IsEnumeratedTypeSymbol())
    {
        enumType = static_cast<EnumeratedTypeSymbol*>(type);
    }
    else
    {
        otava::ast::SetExceptionThrown();
        throw std::runtime_error("otava.symbols.enums: enum type expected");
    }
}

void EnumTypeEqual::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    args[0]->Load(emitter, flags, sourcePos, context);
    otava::intermediate::Value* left = emitter.Stack().Pop();
    args[1]->Load(emitter, OperationFlags::none, sourcePos, context);
    otava::intermediate::Value* right = emitter.Stack().Pop();
    emitter.Stack().Push(emitter.EmitEqual(left, right));
}

EnumTypeLess::EnumTypeLess(const std::u32string& name_) : FunctionSymbol(SymbolKind::enumTypeLess, name_), enumType(nullptr)
{
}

EnumTypeLess::EnumTypeLess(EnumeratedTypeSymbol* enumType_, Context* context) : FunctionSymbol(SymbolKind::enumTypeLess, U"operator<"), enumType(enumType_)
{
    SetFunctionKind(FunctionKind::function);
    SetAccess(Access::public_);
    ParameterSymbol* leftParam = new ParameterSymbol(U"left", enumType);
    AddParameter(leftParam, soul::ast::SourcePos(), nullptr);
    ParameterSymbol* rightParam = new ParameterSymbol(U"right", enumType);
    AddParameter(rightParam, soul::ast::SourcePos(), nullptr);
    TypeSymbol* boolType = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::boolType);
    SetReturnType(boolType, context);
}

void EnumTypeLess::Write(Writer& writer)
{
    FunctionSymbol::Write(writer);
    writer.GetBinaryStreamWriter().Write(enumType->Id());
}

void EnumTypeLess::Read(Reader& reader)
{
    FunctionSymbol::Read(reader);
    reader.GetBinaryStreamReader().ReadUuid(enumTypeId);
}

void EnumTypeLess::Resolve(SymbolTable& symbolTable)
{
    FunctionSymbol::Resolve(symbolTable);
    TypeSymbol* type = symbolTable.GetType(enumTypeId);
    if (type->IsEnumeratedTypeSymbol())
    {
        enumType = static_cast<EnumeratedTypeSymbol*>(type);
    }
    else
    {
        otava::ast::SetExceptionThrown();
        throw std::runtime_error("otava.symbols.enums: enum type expected");
    }
}

void EnumTypeLess::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    args[0]->Load(emitter, flags, sourcePos, context);
    otava::intermediate::Value* left = emitter.Stack().Pop();
    args[1]->Load(emitter, OperationFlags::none, sourcePos, context);
    otava::intermediate::Value* right = emitter.Stack().Pop();
    emitter.Stack().Push(emitter.EmitLess(left, right));
}

void BindEnumType(EnumeratedTypeSymbol* enumType, const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (enumType->IsBound()) return;
    enumType->SetBound();
    FunctionGroupSymbol* constructorGroup = enumType->GetScope()->GetOrInsertFunctionGroup(U"@constructor", sourcePos, context);
    EnumTypeDefaultCtor* enumTypeDefaultCtor = new EnumTypeDefaultCtor(enumType, context);
    enumType->GetScope()->AddSymbol(enumTypeDefaultCtor, sourcePos, context);
    constructorGroup->AddFunction(enumTypeDefaultCtor);
    EnumTypeCopyCtor* enumTypeCopyCtor = new EnumTypeCopyCtor(enumType, context);
    enumType->GetScope()->AddSymbol(enumTypeCopyCtor, sourcePos, context);
    constructorGroup->AddFunction(enumTypeCopyCtor);
    EnumTypeMoveCtor* enumTypeMoveCtor = new EnumTypeMoveCtor(enumType, context);
    enumType->GetScope()->AddSymbol(enumTypeMoveCtor, sourcePos, context);
    constructorGroup->AddFunction(enumTypeMoveCtor);

    FunctionGroupSymbol* destructorGroup = enumType->GetScope()->GetOrInsertFunctionGroup(U"@destructor", sourcePos, context);
    TrivialDestructor* trivialDestructor = new TrivialDestructor(enumType, context);
    enumType->GetScope()->AddSymbol(trivialDestructor, sourcePos, context);
    destructorGroup->AddFunction(trivialDestructor);

    FunctionGroupSymbol* assignmentGroup = enumType->GetScope()->GetOrInsertFunctionGroup(U"operator=", sourcePos, context);
    EnumTypeCopyAssignment* enumTypeCopyAssignment = new EnumTypeCopyAssignment(enumType, context);
    enumType->GetScope()->AddSymbol(enumTypeCopyAssignment, sourcePos, context);
    assignmentGroup->AddFunction(enumTypeCopyAssignment);
    EnumTypeMoveAssignment* enumTypeMoveAssignment = new EnumTypeMoveAssignment(enumType, context);
    enumType->GetScope()->AddSymbol(enumTypeMoveAssignment, sourcePos, context);
    assignmentGroup->AddFunction(enumTypeMoveAssignment);

    FunctionGroupSymbol* equalGroup = enumType->GetScope()->GetOrInsertFunctionGroup(U"operator==", sourcePos, context);
    EnumTypeEqual* enumTypeEqual = new EnumTypeEqual(enumType, context);
    enumType->GetScope()->AddSymbol(enumTypeEqual, sourcePos, context);
    equalGroup->AddFunction(enumTypeEqual);

    FunctionGroupSymbol* lessGroup = enumType->GetScope()->GetOrInsertFunctionGroup(U"operator<", sourcePos, context);
    EnumTypeLess* enumTypeLess = new EnumTypeLess(enumType, context);
    enumType->GetScope()->AddSymbol(enumTypeLess, sourcePos, context);
    lessGroup->AddFunction(enumTypeLess);
}

} // namespace otava::symbols
