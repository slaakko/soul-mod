// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.array.type.symbol;

import otava.symbols.writer;
import otava.symbols.reader;
import otava.symbols.symbol.table;
import otava.symbols.visitor;
import otava.symbols.emitter;
import otava.symbols.function.group.symbol;
import otava.ast;
import util.unicode;

namespace otava::symbols {

std::expected<std::u32string, int> MakeArrayTypeName(TypeSymbol* elementType, std::int64_t size)
{
    std::u32string arrayTypeName;
    std::expected<std::u32string, int> rv = util::ToUtf32(std::to_string(size));
    if (!rv) return std::unexpected<int>(rv.error());
    arrayTypeName.append(elementType->FullName()).append(U" [").append(*rv).append(U"]");
    return std::expected<std::u32string, int>(arrayTypeName);
}

ArrayTypeSymbol::ArrayTypeSymbol(const std::u32string& name_) : TypeSymbol(SymbolKind::arrayTypeSymbol, name_), elementType(), size(-1), bound(false), error(0)
{
    GetScope()->SetKind(ScopeKind::arrayScope);
}

ArrayTypeSymbol::ArrayTypeSymbol(TypeSymbol* elementType_, std::int64_t size_) :
    TypeSymbol(SymbolKind::arrayTypeSymbol, std::u32string()), elementType(elementType_), size(size_), bound(false), error(0)
{
    std::expected<std::u32string, int> rv = MakeArrayTypeName(elementType, size);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    SetName(*rv);
    GetScope()->SetKind(ScopeKind::arrayScope);
}

bool ArrayTypeSymbol::IsValidDeclarationScope(ScopeKind scopeKind) const
{
    switch (scopeKind)
    {
        case ScopeKind::namespaceScope:
        case ScopeKind::classScope:
        case ScopeKind::functionScope:
        {
            return true;
        }
    }
    return false;
}

std::expected<bool, int> ArrayTypeSymbol::Write(Writer& writer)
{
    std::expected<bool, int> rv = TypeSymbol::Write(writer);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(bound);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(elementType->Id());
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(size);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ArrayTypeSymbol::Read(Reader& reader)
{
    std::expected<bool, int> rv = TypeSymbol::Read(reader);
    if (!rv) return rv;
    std::expected<bool, int> brv = reader.GetBinaryStreamReader().ReadBool();
    if (!brv) return brv;
    bound = *brv;
    rv = reader.GetBinaryStreamReader().ReadUuid(elementTypeId);
    if (!rv) return rv;
    std::expected<std::int64_t, int> lrv = reader.GetBinaryStreamReader().ReadLong();
    if (!lrv) return std::unexpected<int>(lrv.error());
    size = *lrv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ArrayTypeSymbol::Resolve(SymbolTable& symbolTable, Context* context)
{
    std::expected<bool, int> rv = TypeSymbol::Resolve(symbolTable, context);
    if (!rv) return rv;
    elementType = symbolTable.GetType(elementTypeId);
    symbolTable.AddArrayTypeToSet(this);
    return std::expected<bool, int>(true);
}

void ArrayTypeSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<otava::intermediate::Type*, int> ArrayTypeSymbol::IrType(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context)
{
    otava::intermediate::Type* type = emitter.GetType(Id());
    if (!type)
    {
        std::expected<otava::intermediate::Type*, int> irv = elementType->IrType(emitter, sourcePos, context);
        if (!irv) return irv;
        type = emitter.MakeArrayType(size, *irv);
        emitter.SetType(Id(), type);
    }
    return type;
}

void ArrayTypeSymbol::Bind(const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (IsBound()) return;
    SetBound();
    FunctionGroupSymbol* constructorGroup = GetScope()->GetOrInsertFunctionGroup(U"@constructor", sourcePos, context);

    ArrayTypeDefaultCtor* arrayTypeDefaultCtor = new ArrayTypeDefaultCtor(this, context);
    GetScope()->AddSymbol(arrayTypeDefaultCtor, sourcePos, context);
    constructorGroup->AddFunction(arrayTypeDefaultCtor);

    ArrayTypeCopyCtor* arrayTypeCopyCtor = new ArrayTypeCopyCtor(this, context);
    GetScope()->AddSymbol(arrayTypeCopyCtor, sourcePos, context);
    constructorGroup->AddFunction(arrayTypeCopyCtor);

    ArrayTypeMoveCtor* arrayTypeMoveCtor = new ArrayTypeMoveCtor(this, context);
    GetScope()->AddSymbol(arrayTypeMoveCtor, sourcePos, context);
    constructorGroup->AddFunction(arrayTypeMoveCtor);

    FunctionGroupSymbol* assignmentGroup = GetScope()->GetOrInsertFunctionGroup(U"operator=", sourcePos, context);

    ArrayTypeCopyAssignment* arrayTypeCopyAssignment = new ArrayTypeCopyAssignment(this, context);
    GetScope()->AddSymbol(arrayTypeCopyAssignment, sourcePos, context);
    assignmentGroup->AddFunction(arrayTypeCopyAssignment);

    ArrayTypeMoveAssignment* arrayTypeMoveAssignment = new ArrayTypeMoveAssignment(this, context);
    GetScope()->AddSymbol(arrayTypeMoveAssignment, sourcePos, context);
    assignmentGroup->AddFunction(arrayTypeMoveAssignment);

    FunctionGroupSymbol* beginGroup = GetScope()->GetOrInsertFunctionGroup(U"begin", sourcePos, context);

    ArrayTypeBegin* arrayTypeBegin = new ArrayTypeBegin(this, context);
    GetScope()->AddSymbol(arrayTypeBegin, sourcePos, context);
    beginGroup->AddFunction(arrayTypeBegin);

    FunctionGroupSymbol* endGroup = GetScope()->GetOrInsertFunctionGroup(U"end", sourcePos, context);

    ArrayTypeEnd* arrayTypeEnd = new ArrayTypeEnd(this, context);
    GetScope()->AddSymbol(arrayTypeEnd, sourcePos, context);
    endGroup->AddFunction(arrayTypeEnd);
}

ArrayTypeDefaultCtor::ArrayTypeDefaultCtor(const std::u32string& name_) : FunctionSymbol(SymbolKind::arrayTypeDefaultCtor, name_), arrayType(nullptr)
{
}

ArrayTypeDefaultCtor::ArrayTypeDefaultCtor(ArrayTypeSymbol* arrayType_, Context* context) :
    FunctionSymbol(SymbolKind::arrayTypeDefaultCtor, U"@constructor"), arrayType(arrayType_)
{
    SetFunctionKind(FunctionKind::constructor);
    SetAccess(Access::public_);
    ParameterSymbol* thisParam = new ParameterSymbol(U"this", arrayType->AddPointer(context));
    AddParameter(thisParam, soul::ast::SourcePos(), context);
}

std::expected<bool, int> ArrayTypeDefaultCtor::Write(Writer& writer)
{
    std::expected<bool, int> rv = FunctionSymbol::Write(writer);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(arrayType->Id());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ArrayTypeDefaultCtor::Read(Reader& reader)
{
    std::expected<bool, int> rv = FunctionSymbol::Read(reader);
    if (!rv) return rv;
    rv = reader.GetBinaryStreamReader().ReadUuid(arrayTypeId);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ArrayTypeDefaultCtor::Resolve(SymbolTable& symbolTable, Context* context)
{
    TypeSymbol* type = symbolTable.GetType(arrayTypeId);
    if (type && type->IsArrayTypeSymbol())
    {
        arrayType = static_cast<ArrayTypeSymbol*>(type);
    }
    else
    {
        return std::unexpected<int>(util::AllocateError("otava.symbols.array.type.symbol: array type expected"));
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ArrayTypeDefaultCtor::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    if ((flags & OperationFlags::defaultInit) == OperationFlags::none) return;
    std::expected<otava::intermediate::Instruction*, int> rv = emitter.EmitLocal(emitter.GetLongType());
    if (!rv) return std::unexpected<int>(rv.error());
    otava::intermediate::Value* loopIndexVar = *rv;
    emitter.EmitStore(emitter.EmitLong(0), loopIndexVar);
    otava::intermediate::BasicBlock* condBlock = emitter.CreateBasicBlock();
    emitter.EmitJump(condBlock);
    emitter.SetCurrentBasicBlock(condBlock);
    rv = emitter.EmitLoad(loopIndexVar);
    if (!rv) return std::unexpected<int>(rv.error());
    otava::intermediate::Value* loopIndexValue = *rv;
    otava::intermediate::Value* size = emitter.EmitLong(arrayType->Size());
    otava::intermediate::Value* less = emitter.EmitLess(loopIndexValue, size);
    otava::intermediate::BasicBlock* trueBlock = emitter.CreateBasicBlock();
    otava::intermediate::BasicBlock* nextBlock = emitter.CreateBasicBlock();
    emitter.EmitBranch(less, trueBlock, nextBlock);
    emitter.SetCurrentBasicBlock(trueBlock);
    rv = emitter.EmitLoad(loopIndexVar);
    if (!rv) return std::unexpected<int>(rv.error());
    otava::intermediate::Value* currentLoopIndexValue = *rv;
    std::expected<bool, int> arv = args[0]->Load(emitter, OperationFlags::none, sourcePos, context);
    if (!arv) return arv;
    otava::intermediate::Value* array = emitter.Stack().Pop();
    std::expected<otava::intermediate::Value*, int> erv = emitter.EmitElemAddr(array, currentLoopIndexValue);
    if (!erv) return std::unexpected<int>(erv.error());
    otava::intermediate::Value* elemAddr = *erv;
    std::expected<otava::intermediate::Type*, int> irv = arrayType->ElementType()->IrType(emitter, sourcePos, context);
    if (!irv) return std::unexpected<int>(irv.error());
    otava::intermediate::Type* elementIrType = *irv;
    otava::intermediate::Value* defaultValue = elementIrType->MakeDefaultValue(*emitter.GetIntermediateContext());
    emitter.EmitStore(defaultValue, elemAddr);
    otava::intermediate::Value* nextLoopIndexValue = emitter.EmitAdd(currentLoopIndexValue, emitter.EmitLong(1));
    emitter.EmitStore(nextLoopIndexValue, loopIndexVar);
    emitter.EmitJump(condBlock);
    emitter.SetCurrentBasicBlock(nextBlock);
    return std::expected<bool, int>(true);
}

ArrayTypeCopyCtor::ArrayTypeCopyCtor(const std::u32string& name_) : FunctionSymbol(SymbolKind::arrayTypeCopyCtor, name_), arrayType(nullptr)
{
}

ArrayTypeCopyCtor::ArrayTypeCopyCtor(ArrayTypeSymbol* arrayType_, Context* context) : FunctionSymbol(SymbolKind::arrayTypeCopyCtor, U"@constructor"), arrayType(arrayType_)
{
    SetFunctionKind(FunctionKind::constructor);
    SetAccess(Access::public_);
    ParameterSymbol* thisParam = new ParameterSymbol(U"this", arrayType->AddPointer(context));
    AddParameter(thisParam, soul::ast::SourcePos(), context);
    ParameterSymbol* thatParam = new ParameterSymbol(U"that", arrayType->AddConst(context)->AddLValueRef(context));
    AddParameter(thatParam, soul::ast::SourcePos(), context);
}

std::expected<bool, int> ArrayTypeCopyCtor::Write(Writer& writer)
{
    std::expected<bool, int> rv = FunctionSymbol::Write(writer);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(arrayType->Id());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ArrayTypeCopyCtor::Read(Reader& reader)
{
    std::expected<bool, int> rv = FunctionSymbol::Read(reader);
    if (!rv) return rv;
    rv = reader.GetBinaryStreamReader().ReadUuid(arrayTypeId);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ArrayTypeCopyCtor::Resolve(SymbolTable& symbolTable, Context* context)
{
    TypeSymbol* type = symbolTable.GetType(arrayTypeId);
    if (type && type->IsArrayTypeSymbol())
    {
        arrayType = static_cast<ArrayTypeSymbol*>(type);
    }
    else
    {
        return std::unexpected<int>(util::AllocateError("otava.symbols.array.type.symbol: array type expected"));
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ArrayTypeCopyCtor::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    std::expected<otava::intermediate::Instruction*, int> rv = emitter.EmitLocal(emitter.GetLongType());
    if (!rv) return std::unexpected<int>(rv.error());
    otava::intermediate::Value* loopIndexVar = *rv;
    emitter.EmitStore(emitter.EmitLong(0), loopIndexVar);
    otava::intermediate::BasicBlock* condBlock = emitter.CreateBasicBlock();
    emitter.EmitJump(condBlock);
    emitter.SetCurrentBasicBlock(condBlock);
    rv = emitter.EmitLoad(loopIndexVar);
    if (!rv) return std::unexpected<int>(rv.error());
    otava::intermediate::Value* loopIndexValue = *rv;
    otava::intermediate::Value* size = emitter.EmitLong(arrayType->Size());
    otava::intermediate::Value* less = emitter.EmitLess(loopIndexValue, size);
    otava::intermediate::BasicBlock* trueBlock = emitter.CreateBasicBlock();
    otava::intermediate::BasicBlock* nextBlock = emitter.CreateBasicBlock();
    emitter.EmitBranch(less, trueBlock, nextBlock);
    emitter.SetCurrentBasicBlock(trueBlock);
    rv = emitter.EmitLoad(loopIndexVar);
    if (!rv) return std::unexpected<int>(rv.error());
    otava::intermediate::Value* currentLoopIndexValue = *rv;
    std::expected<bool, int> arv = args[1]->Load(emitter, OperationFlags::none, sourcePos, context);
    if (!arv) return arv;
    otava::intermediate::Value* sourceArray = emitter.Stack().Pop();
    std::expected<otava::intermediate::Value*, int> erv = emitter.EmitElemAddr(sourceArray, currentLoopIndexValue);
    if (!erv) return std::unexpected<int>(erv.error());
    otava::intermediate::Value* sourceElemAddr = *erv;
    rv = emitter.EmitLoad(sourceElemAddr);
    if (!rv) return std::unexpected<int>(rv.error());
    otava::intermediate::Value* sourceValue = *rv;
    arv = args[0]->Load(emitter, OperationFlags::none, sourcePos, context);
    if (!arv) return arv;
    otava::intermediate::Value* targetArray = emitter.Stack().Pop();
    erv = emitter.EmitElemAddr(targetArray, currentLoopIndexValue);
    if (!erv) return std::unexpected<int>(erv.error());
    otava::intermediate::Value* targetElemAddr = *erv;
    emitter.EmitStore(sourceValue, targetElemAddr);
    otava::intermediate::Value* nextLoopIndexValue = emitter.EmitAdd(currentLoopIndexValue, emitter.EmitLong(1));
    emitter.EmitStore(nextLoopIndexValue, loopIndexVar);
    emitter.EmitJump(condBlock);
    emitter.SetCurrentBasicBlock(nextBlock);
    return std::expected<bool, int>(true);
}

ArrayTypeMoveCtor::ArrayTypeMoveCtor(const std::u32string& name_) : FunctionSymbol(SymbolKind::arrayTypeMoveCtor, name_), arrayType(nullptr)
{
}

ArrayTypeMoveCtor::ArrayTypeMoveCtor(ArrayTypeSymbol* arrayType_, Context* context) : FunctionSymbol(SymbolKind::arrayTypeMoveCtor, U"@constructor"), arrayType(arrayType_)
{
    SetFunctionKind(FunctionKind::constructor);
    SetAccess(Access::public_);
    ParameterSymbol* thisParam = new ParameterSymbol(U"this", arrayType->AddPointer(context));
    AddParameter(thisParam, soul::ast::SourcePos(), context);
    ParameterSymbol* thatParam = new ParameterSymbol(U"that", arrayType->AddRValueRef(context));
    AddParameter(thatParam, soul::ast::SourcePos(), context);
}

std::expected<bool, int> ArrayTypeMoveCtor::Write(Writer& writer)
{
    std::expected<bool, int> rv = FunctionSymbol::Write(writer);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(arrayType->Id());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ArrayTypeMoveCtor::Read(Reader& reader)
{
    std::expected<bool, int> rv = FunctionSymbol::Read(reader);
    if (!rv) return rv;
    rv = reader.GetBinaryStreamReader().ReadUuid(arrayTypeId);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ArrayTypeMoveCtor::Resolve(SymbolTable& symbolTable, Context* context)
{
    TypeSymbol* type = symbolTable.GetType(arrayTypeId);
    if (type && type->IsArrayTypeSymbol())
    {
        arrayType = static_cast<ArrayTypeSymbol*>(type);
    }
    else
    {
        return std::unexpected<int>(util::AllocateError("otava.symbols.array.type.symbol: array type expected"));
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ArrayTypeMoveCtor::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    std::expected<otava::intermediate::Instruction*, int> rv = emitter.EmitLocal(emitter.GetLongType());
    if (!rv) return std::unexpected<int>(rv.error());
    otava::intermediate::Value* loopIndexVar = *rv;
    emitter.EmitStore(emitter.EmitLong(0), loopIndexVar);
    otava::intermediate::BasicBlock* condBlock = emitter.CreateBasicBlock();
    emitter.EmitJump(condBlock);
    emitter.SetCurrentBasicBlock(condBlock);
    rv = emitter.EmitLoad(loopIndexVar);
    if (!rv) return std::unexpected<int>(rv.error());
    otava::intermediate::Value* loopIndexValue = *rv;
    otava::intermediate::Value* size = emitter.EmitLong(arrayType->Size());
    otava::intermediate::Value* less = emitter.EmitLess(loopIndexValue, size);
    otava::intermediate::BasicBlock* trueBlock = emitter.CreateBasicBlock();
    otava::intermediate::BasicBlock* nextBlock = emitter.CreateBasicBlock();
    emitter.EmitBranch(less, trueBlock, nextBlock);
    emitter.SetCurrentBasicBlock(trueBlock);
    rv = emitter.EmitLoad(loopIndexVar);
    if (!rv) return std::unexpected<int>(rv.error());
    otava::intermediate::Value* currentLoopIndexValue = *rv;
    std::expected<bool, int> arv = args[1]->Load(emitter, OperationFlags::none, sourcePos, context);
    if (!arv) return arv;
    otava::intermediate::Value* sourceArray = emitter.Stack().Pop();
    std::expected<otava::intermediate::Value*, int> erv = emitter.EmitElemAddr(sourceArray, currentLoopIndexValue);
    if (!erv) return std::unexpected<int>(erv.error());
    otava::intermediate::Value* sourceElemAddr = *erv;
    rv = emitter.EmitLoad(sourceElemAddr);
    if (!rv) return std::unexpected<int>(rv.error());
    otava::intermediate::Value* sourceValue = *rv;
    arv = args[0]->Load(emitter, OperationFlags::none, sourcePos, context);
    if (!arv) return arv;
    otava::intermediate::Value* targetArray = emitter.Stack().Pop();
    erv = emitter.EmitElemAddr(targetArray, currentLoopIndexValue);
    if (!erv) return std::unexpected<int>(erv.error());
    otava::intermediate::Value* targetElemAddr = *erv;
    emitter.EmitStore(sourceValue, targetElemAddr);
    otava::intermediate::Value* nextLoopIndexValue = emitter.EmitAdd(currentLoopIndexValue, emitter.EmitLong(1));
    emitter.EmitStore(nextLoopIndexValue, loopIndexVar);
    emitter.EmitJump(condBlock);
    emitter.SetCurrentBasicBlock(nextBlock);
    return std::expected<bool, int>(true);
}

ArrayTypeCopyAssignment::ArrayTypeCopyAssignment(const std::u32string& name_) : FunctionSymbol(SymbolKind::arrayTypeCopyAssignment, name_), arrayType(nullptr)
{
}

ArrayTypeCopyAssignment::ArrayTypeCopyAssignment(ArrayTypeSymbol* arrayType_, Context* context) :
    FunctionSymbol(SymbolKind::arrayTypeCopyAssignment, U"operator="), arrayType(arrayType_)
{
    SetFunctionKind(FunctionKind::special);
    SetAccess(Access::public_);
    ParameterSymbol* thisParam = new ParameterSymbol(U"this", arrayType->AddPointer(context));
    AddParameter(thisParam, soul::ast::SourcePos(), context);
    ParameterSymbol* thatParam = new ParameterSymbol(U"that", arrayType->AddConst(context)->AddLValueRef(context));
    AddParameter(thatParam, soul::ast::SourcePos(), context);
    SetReturnType(arrayType->AddLValueRef(context), context);
}

std::expected<bool, int> ArrayTypeCopyAssignment::Write(Writer& writer)
{
    std::expected<bool, int> rv = FunctionSymbol::Write(writer);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(arrayType->Id());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ArrayTypeCopyAssignment::Read(Reader& reader)
{
    std::expected<bool, int> rv = FunctionSymbol::Read(reader);
    if (!rv) return rv;
    rv = reader.GetBinaryStreamReader().ReadUuid(arrayTypeId);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ArrayTypeCopyAssignment::Resolve(SymbolTable& symbolTable, Context* context)
{
    TypeSymbol* type = symbolTable.GetType(arrayTypeId);
    if (type && type->IsArrayTypeSymbol())
    {
        arrayType = static_cast<ArrayTypeSymbol*>(type);
    }
    else
    {
        return std::unexpected<int>(util::AllocateError("otava.symbols.array.type.symbol: array type expected"));
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ArrayTypeCopyAssignment::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    std::expected<otava::intermediate::Instruction*, int> rv = emitter.EmitLocal(emitter.GetLongType());
    if (!rv) return std::unexpected<int>(rv.error());
    otava::intermediate::Value* loopIndexVar = *rv;
    emitter.EmitStore(emitter.EmitLong(0), loopIndexVar);
    otava::intermediate::BasicBlock* condBlock = emitter.CreateBasicBlock();
    emitter.EmitJump(condBlock);
    emitter.SetCurrentBasicBlock(condBlock);
    rv = emitter.EmitLoad(loopIndexVar);
    if (!rv) return std::unexpected<int>(rv.error());
    otava::intermediate::Value* loopIndexValue = *rv;
    otava::intermediate::Value* size = emitter.EmitLong(arrayType->Size());
    otava::intermediate::Value* less = emitter.EmitLess(loopIndexValue, size);
    otava::intermediate::BasicBlock* trueBlock = emitter.CreateBasicBlock();
    otava::intermediate::BasicBlock* nextBlock = emitter.CreateBasicBlock();
    emitter.EmitBranch(less, trueBlock, nextBlock);
    emitter.SetCurrentBasicBlock(trueBlock);
    rv = emitter.EmitLoad(loopIndexVar);
    if (!rv) return std::unexpected<int>(rv.error());
    otava::intermediate::Value* currentLoopIndexValue = *rv;
    std::expected<bool, int> arv = args[1]->Load(emitter, OperationFlags::none, sourcePos, context);
    if (!arv) return arv;
    otava::intermediate::Value* sourceArray = emitter.Stack().Pop();
    std::expected<otava::intermediate::Value*, int> erv = emitter.EmitElemAddr(sourceArray, currentLoopIndexValue);
    if (!erv) return std::unexpected<int>(erv.error());
    otava::intermediate::Value* sourceElemAddr = *erv;
    rv = emitter.EmitLoad(sourceElemAddr);
    if (!rv) return std::unexpected<int>(rv.error());
    otava::intermediate::Value* sourceValue = *rv;
    arv = args[0]->Load(emitter, OperationFlags::none, sourcePos, context);
    if (!arv) return arv;
    otava::intermediate::Value* targetArray = emitter.Stack().Pop();
    erv = emitter.EmitElemAddr(targetArray, currentLoopIndexValue);
    if (!erv) return std::unexpected<int>(erv.error());
    otava::intermediate::Value* targetElemAddr = *erv;
    emitter.EmitStore(sourceValue, targetElemAddr);
    otava::intermediate::Value* nextLoopIndexValue = emitter.EmitAdd(currentLoopIndexValue, emitter.EmitLong(1));
    emitter.EmitStore(nextLoopIndexValue, loopIndexVar);
    emitter.EmitJump(condBlock);
    emitter.SetCurrentBasicBlock(nextBlock);
    arv = args[0]->Load(emitter, OperationFlags::none, sourcePos, context);
    if (!arv) return arv;
    return std::expected<bool, int>(true);
}

ArrayTypeMoveAssignment::ArrayTypeMoveAssignment(const std::u32string& name_) : FunctionSymbol(SymbolKind::arrayTypeMoveAssignment, name_), arrayType(nullptr)
{
}

ArrayTypeMoveAssignment::ArrayTypeMoveAssignment(ArrayTypeSymbol* arrayType_, Context* context) :
    FunctionSymbol(SymbolKind::arrayTypeCopyAssignment, U"operator="), arrayType(arrayType_)
{
    SetFunctionKind(FunctionKind::special);
    SetAccess(Access::public_);
    ParameterSymbol* thisParam = new ParameterSymbol(U"this", arrayType->AddPointer(context));
    AddParameter(thisParam, soul::ast::SourcePos(), context);
    ParameterSymbol* thatParam = new ParameterSymbol(U"that", arrayType->AddRValueRef(context));
    AddParameter(thatParam, soul::ast::SourcePos(), context);
    SetReturnType(arrayType->AddLValueRef(context), context);
}

std::expected<bool, int> ArrayTypeMoveAssignment::Write(Writer& writer)
{
    std::expected<bool, int> rv = FunctionSymbol::Write(writer);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(arrayType->Id());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ArrayTypeMoveAssignment::Read(Reader& reader)
{
    std::expected<bool, int> rv = FunctionSymbol::Read(reader);
    if (!rv) return rv;
    rv = reader.GetBinaryStreamReader().ReadUuid(arrayTypeId);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ArrayTypeMoveAssignment::Resolve(SymbolTable& symbolTable, Context* context)
{
    TypeSymbol* type = symbolTable.GetType(arrayTypeId);
    if (type && type->IsArrayTypeSymbol())
    {
        arrayType = static_cast<ArrayTypeSymbol*>(type);
    }
    else
    {
        return std::unexpected<int>(util::AllocateError("otava.symbols.array.type.symbol: array type expected"));
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ArrayTypeMoveAssignment::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    std::expected<otava::intermediate::Instruction*, int> rv = emitter.EmitLocal(emitter.GetLongType());
    if (!rv) return std::unexpected<int>(rv.error());
    otava::intermediate::Value* loopIndexVar = *rv;
    emitter.EmitStore(emitter.EmitLong(0), loopIndexVar);
    otava::intermediate::BasicBlock* condBlock = emitter.CreateBasicBlock();
    emitter.EmitJump(condBlock);
    emitter.SetCurrentBasicBlock(condBlock);
    rv = emitter.EmitLoad(loopIndexVar);
    if (!rv) return std::unexpected<int>(rv.error());
    otava::intermediate::Value* loopIndexValue = *rv;
    otava::intermediate::Value* size = emitter.EmitLong(arrayType->Size());
    otava::intermediate::Value* less = emitter.EmitLess(loopIndexValue, size);
    otava::intermediate::BasicBlock* trueBlock = emitter.CreateBasicBlock();
    otava::intermediate::BasicBlock* nextBlock = emitter.CreateBasicBlock();
    emitter.EmitBranch(less, trueBlock, nextBlock);
    emitter.SetCurrentBasicBlock(trueBlock);
    rv = emitter.EmitLoad(loopIndexVar);
    if (!rv) return std::unexpected<int>(rv.error());
    otava::intermediate::Value* currentLoopIndexValue = *rv;
    std::expected<bool, int> arv = args[1]->Load(emitter, OperationFlags::none, sourcePos, context);
    if (!arv) return arv;
    otava::intermediate::Value* sourceArray = emitter.Stack().Pop();
    std::expected<otava::intermediate::Value*, int> erv = emitter.EmitElemAddr(sourceArray, currentLoopIndexValue);
    if (!erv) return std::unexpected<int>(erv.error());
    otava::intermediate::Value* sourceElemAddr = *erv;
    rv = emitter.EmitLoad(sourceElemAddr);
    if (!rv) return std::unexpected<int>(rv.error());
    otava::intermediate::Value* sourceValue = *rv;
    arv = args[0]->Load(emitter, OperationFlags::none, sourcePos, context);
    if (!arv) return arv;
    otava::intermediate::Value* targetArray = emitter.Stack().Pop();
    erv = emitter.EmitElemAddr(targetArray, currentLoopIndexValue);
    if (!erv) return std::unexpected<int>(erv.error());
    otava::intermediate::Value* targetElemAddr = *erv;
    emitter.EmitStore(sourceValue, targetElemAddr);
    otava::intermediate::Value* nextLoopIndexValue = emitter.EmitAdd(currentLoopIndexValue, emitter.EmitLong(1));
    emitter.EmitStore(nextLoopIndexValue, loopIndexVar);
    emitter.EmitJump(condBlock);
    emitter.SetCurrentBasicBlock(nextBlock);
    arv = args[0]->Load(emitter, OperationFlags::none, sourcePos, context);
    if (!arv) return arv;
    return std::expected<bool, int>(true);
}

ArrayTypeBegin::ArrayTypeBegin(const std::u32string& name_) : FunctionSymbol(SymbolKind::arrayTypeBegin, name_), arrayType(nullptr)
{
}

ArrayTypeBegin::ArrayTypeBegin(ArrayTypeSymbol* arrayType_, Context* context) :
    FunctionSymbol(SymbolKind::arrayTypeBegin, U"begin"), arrayType(arrayType_)
{
    SetFunctionKind(FunctionKind::function);
    SetAccess(Access::public_);
    ParameterSymbol* thisParam = new ParameterSymbol(U"this", arrayType->AddPointer(context));
    AddParameter(thisParam, soul::ast::SourcePos(), context);
    SetReturnType(arrayType->ElementType()->AddPointer(context), context);
}

std::expected<bool, int> ArrayTypeBegin::Write(Writer& writer)
{
    std::expected<bool, int> rv = FunctionSymbol::Write(writer);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(arrayType->Id());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ArrayTypeBegin::Read(Reader& reader)
{
    std::expected<bool, int> rv = FunctionSymbol::Read(reader);
    if (!rv) return rv;
    rv = reader.GetBinaryStreamReader().ReadUuid(arrayTypeId);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ArrayTypeBegin::Resolve(SymbolTable& symbolTable, Context* context)
{
    TypeSymbol* type = symbolTable.GetType(arrayTypeId);
    if (type && type->IsArrayTypeSymbol())
    {
        arrayType = static_cast<ArrayTypeSymbol*>(type);
    }
    else
    {
        return std::unexpected<int>(util::AllocateError("otava.symbols.array.type.symbol: array type expected"));
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ArrayTypeBegin::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    std::expected<bool, int> arv = args[0]->Load(emitter, OperationFlags::none, sourcePos, context);
    if (!arv) return arv;
    otava::intermediate::Value* array = emitter.Stack().Pop();
    std::expected<otava::intermediate::Value*, int> erv = emitter.EmitElemAddr(array, emitter.EmitLong(0));
    if (!erv) return std::unexpected<int>(erv.error());
    otava::intermediate::Value* elemAddr = *erv;
    emitter.Stack().Push(elemAddr);
    return std::expected<bool, int>(true);
}

ArrayTypeEnd::ArrayTypeEnd(const std::u32string& name_) : FunctionSymbol(SymbolKind::arrayTypeEnd, name_), arrayType(nullptr)
{
}

ArrayTypeEnd::ArrayTypeEnd(ArrayTypeSymbol* arrayType_, Context* context) :
    FunctionSymbol(SymbolKind::arrayTypeEnd, U"end"), arrayType(arrayType_)
{
    SetFunctionKind(FunctionKind::function);
    SetAccess(Access::public_);
    ParameterSymbol* thisParam = new ParameterSymbol(U"this", arrayType->AddPointer(context));
    AddParameter(thisParam, soul::ast::SourcePos(), context);
    SetReturnType(arrayType->ElementType()->AddPointer(context), context);
}

std::expected<bool, int> ArrayTypeEnd::Write(Writer& writer)
{
    std::expected<bool, int> rv = FunctionSymbol::Write(writer);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(arrayType->Id());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ArrayTypeEnd::Read(Reader& reader)
{
    std::expected<bool, int> rv = FunctionSymbol::Read(reader);
    if (!rv) return rv;
    rv = reader.GetBinaryStreamReader().ReadUuid(arrayTypeId);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ArrayTypeEnd::Resolve(SymbolTable& symbolTable, Context* context)
{
    TypeSymbol* type = symbolTable.GetType(arrayTypeId);
    if (type && type->IsArrayTypeSymbol())
    {
        arrayType = static_cast<ArrayTypeSymbol*>(type);
    }
    else
    {
        return std::unexpected<int>(util::AllocateError("otava.symbols.array.type.symbol: array type expected"));
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ArrayTypeEnd::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    std::expected<bool, int> arv = args[0]->Load(emitter, OperationFlags::none, sourcePos, context);
    if (!arv) return arv;
    otava::intermediate::Value* array = emitter.Stack().Pop();
    std::expected<otava::intermediate::Value*, int> erv = emitter.EmitElemAddr(array, emitter.EmitLong(arrayType->Size()));
    if (!erv) return std::unexpected<int>(erv.error());
    otava::intermediate::Value* elemAddr = *erv;
    emitter.Stack().Push(elemAddr);
    return std::expected<bool, int>(true);
}

} // namespace otava::symbols
