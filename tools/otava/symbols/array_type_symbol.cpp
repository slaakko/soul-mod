// =================================
// Copyright (c) 2022 Seppo Laakko
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

std::u32string MakeArrayTypeName(TypeSymbol* elementType, int64_t size)
{
    std::u32string arrayTypeName;
    arrayTypeName.append(elementType->FullName()).append(U" [").append(util::ToUtf32(std::to_string(size))).append(U"]");
    return arrayTypeName;
}

ArrayTypeSymbol::ArrayTypeSymbol(const std::u32string& name_) : TypeSymbol(SymbolKind::arrayTypeSymbol, name_), bound(false)
{
    GetScope()->SetKind(ScopeKind::arrayScope);
}

ArrayTypeSymbol::ArrayTypeSymbol(TypeSymbol* elementType_, int64_t size_) : 
    TypeSymbol(SymbolKind::arrayTypeSymbol, MakeArrayTypeName(elementType_, size_)), elementType(elementType_), size(size_), bound(false)
{
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

void ArrayTypeSymbol::Write(Writer& writer)
{
    TypeSymbol::Write(writer);
    writer.GetBinaryStreamWriter().Write(bound);
    writer.GetBinaryStreamWriter().Write(elementType->Id());
    writer.GetBinaryStreamWriter().Write(size);
}

void ArrayTypeSymbol::Read(Reader& reader)
{
    TypeSymbol::Read(reader);
    bound = reader.GetBinaryStreamReader().ReadBool();
    reader.GetBinaryStreamReader().ReadUuid(elementTypeId);
    size = reader.GetBinaryStreamReader().ReadLong();
}

void ArrayTypeSymbol::Resolve(SymbolTable& symbolTable)
{
    TypeSymbol::Resolve(symbolTable);
    elementType = symbolTable.GetType(elementTypeId);
}

void ArrayTypeSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

otava::intermediate::Type* ArrayTypeSymbol::IrType(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context)
{
    return emitter.MakeArrayType(size, elementType->IrType(emitter, sourcePos, context));
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

void ArrayTypeDefaultCtor::Write(Writer& writer)
{
    FunctionSymbol::Write(writer);
    writer.GetBinaryStreamWriter().Write(arrayType->Id());
}

void ArrayTypeDefaultCtor::Read(Reader& reader)
{
    FunctionSymbol::Read(reader);
    reader.GetBinaryStreamReader().ReadUuid(arrayTypeId);
}

void ArrayTypeDefaultCtor::Resolve(SymbolTable& symbolTable)
{
    TypeSymbol* type = symbolTable.GetType(arrayTypeId);
    if (type->IsArrayTypeSymbol())
    {
        arrayType = static_cast<ArrayTypeSymbol*>(type);
    }
    else
    {
        otava::ast::SetExceptionThrown();
        throw std::runtime_error("otava.symbols.array.type.symbol: array type expected");
    }
}

void ArrayTypeDefaultCtor::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    if ((flags & OperationFlags::defaultInit) == OperationFlags::none) return;
    otava::intermediate::Value* loopIndexVar = emitter.EmitLocal(emitter.GetLongType());
    emitter.EmitStore(emitter.EmitLong(0), loopIndexVar);
    otava::intermediate::BasicBlock* condBlock = emitter.CreateBasicBlock();
    emitter.EmitJump(condBlock);
    emitter.SetCurrentBasicBlock(condBlock);
    otava::intermediate::Value* loopIndexValue = emitter.EmitLoad(loopIndexVar);
    otava::intermediate::Value* size = emitter.EmitLong(arrayType->Size());
    otava::intermediate::Value* less = emitter.EmitLess(loopIndexValue, size);
    otava::intermediate::BasicBlock* trueBlock = emitter.CreateBasicBlock();
    otava::intermediate::BasicBlock* nextBlock = emitter.CreateBasicBlock();
    emitter.EmitBranch(less, trueBlock, nextBlock);
    emitter.SetCurrentBasicBlock(trueBlock);
    otava::intermediate::Value* currentLoopIndexValue = emitter.EmitLoad(loopIndexVar);
    args[0]->Load(emitter, OperationFlags::none, sourcePos, context);
    otava::intermediate::Value* array = emitter.Stack().Pop();
    otava::intermediate::Value* elemAddr = emitter.EmitElemAddr(array, currentLoopIndexValue);
    otava::intermediate::Value* defaultValue = arrayType->ElementType()->IrType(emitter, sourcePos, context)->MakeDefaultValue(*emitter.GetIntermediateContext());
    emitter.EmitStore(defaultValue, elemAddr);
    otava::intermediate::Value* nextLoopIndexValue = emitter.EmitAdd(currentLoopIndexValue, emitter.EmitLong(1));
    emitter.EmitStore(nextLoopIndexValue, loopIndexVar);
    emitter.EmitJump(condBlock);
    emitter.SetCodeGenNextBlock(nextBlock);
    emitter.SetCurrentBasicBlock(nextBlock);
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

void ArrayTypeCopyCtor::Write(Writer& writer)
{
    FunctionSymbol::Write(writer);
    writer.GetBinaryStreamWriter().Write(arrayType->Id());
}

void ArrayTypeCopyCtor::Read(Reader& reader)
{
    FunctionSymbol::Read(reader);
    reader.GetBinaryStreamReader().ReadUuid(arrayTypeId);
}

void ArrayTypeCopyCtor::Resolve(SymbolTable& symbolTable)
{
    TypeSymbol* type = symbolTable.GetType(arrayTypeId);
    if (type->IsArrayTypeSymbol())
    {
        arrayType = static_cast<ArrayTypeSymbol*>(type);
    }
    else
    {
        otava::ast::SetExceptionThrown();
        throw std::runtime_error("otava.symbols.array.type.symbol: array type expected");
    }
}

void ArrayTypeCopyCtor::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    otava::intermediate::Value* loopIndexVar = emitter.EmitLocal(emitter.GetLongType());
    emitter.EmitStore(emitter.EmitLong(0), loopIndexVar);
    otava::intermediate::BasicBlock* condBlock = emitter.CreateBasicBlock();
    emitter.EmitJump(condBlock);
    emitter.SetCurrentBasicBlock(condBlock);
    otava::intermediate::Value* loopIndexValue = emitter.EmitLoad(loopIndexVar);
    otava::intermediate::Value* size = emitter.EmitLong(arrayType->Size());
    otava::intermediate::Value* less = emitter.EmitLess(loopIndexValue, size);
    otava::intermediate::BasicBlock* trueBlock = emitter.CreateBasicBlock();
    otava::intermediate::BasicBlock* nextBlock = emitter.CreateBasicBlock();
    emitter.EmitBranch(less, trueBlock, nextBlock);
    emitter.SetCurrentBasicBlock(trueBlock);
    otava::intermediate::Value* currentLoopIndexValue = emitter.EmitLoad(loopIndexVar);
    args[1]->Load(emitter, OperationFlags::none, sourcePos, context);
    otava::intermediate::Value* sourceArray = emitter.Stack().Pop();
    otava::intermediate::Value* sourceElemAddr = emitter.EmitElemAddr(sourceArray, currentLoopIndexValue);
    otava::intermediate::Value* sourceValue = emitter.EmitLoad(sourceElemAddr);
    args[0]->Load(emitter, OperationFlags::none, sourcePos, context);
    otava::intermediate::Value* targetArray = emitter.Stack().Pop();
    otava::intermediate::Value* targetElemAddr = emitter.EmitElemAddr(targetArray, currentLoopIndexValue);
    emitter.EmitStore(sourceValue, targetElemAddr);
    otava::intermediate::Value* nextLoopIndexValue = emitter.EmitAdd(currentLoopIndexValue, emitter.EmitLong(1));
    emitter.EmitStore(nextLoopIndexValue, loopIndexVar);
    emitter.EmitJump(condBlock);
    emitter.SetCodeGenNextBlock(nextBlock);
    emitter.SetCurrentBasicBlock(nextBlock);
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

void ArrayTypeMoveCtor::Write(Writer& writer)
{
    FunctionSymbol::Write(writer);
    writer.GetBinaryStreamWriter().Write(arrayType->Id());
}

void ArrayTypeMoveCtor::Read(Reader& reader)
{
    FunctionSymbol::Read(reader);
    reader.GetBinaryStreamReader().ReadUuid(arrayTypeId);
}

void ArrayTypeMoveCtor::Resolve(SymbolTable& symbolTable)
{
    TypeSymbol* type = symbolTable.GetType(arrayTypeId);
    if (type->IsArrayTypeSymbol())
    {
        arrayType = static_cast<ArrayTypeSymbol*>(type);
    }
    else
    {
        otava::ast::SetExceptionThrown();
        throw std::runtime_error("otava.symbols.array.type.symbol: array type expected");
    }
}

void ArrayTypeMoveCtor::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    otava::intermediate::Value* loopIndexVar = emitter.EmitLocal(emitter.GetLongType());
    emitter.EmitStore(emitter.EmitLong(0), loopIndexVar);
    otava::intermediate::BasicBlock* condBlock = emitter.CreateBasicBlock();
    emitter.EmitJump(condBlock);
    emitter.SetCurrentBasicBlock(condBlock);
    otava::intermediate::Value* loopIndexValue = emitter.EmitLoad(loopIndexVar);
    otava::intermediate::Value* size = emitter.EmitLong(arrayType->Size());
    otava::intermediate::Value* less = emitter.EmitLess(loopIndexValue, size);
    otava::intermediate::BasicBlock* trueBlock = emitter.CreateBasicBlock();
    otava::intermediate::BasicBlock* nextBlock = emitter.CreateBasicBlock();
    emitter.EmitBranch(less, trueBlock, nextBlock);
    emitter.SetCurrentBasicBlock(trueBlock);
    otava::intermediate::Value* currentLoopIndexValue = emitter.EmitLoad(loopIndexVar);
    args[1]->Load(emitter, OperationFlags::none, sourcePos, context);
    otava::intermediate::Value* sourceArray = emitter.Stack().Pop();
    otava::intermediate::Value* sourceElemAddr = emitter.EmitElemAddr(sourceArray, currentLoopIndexValue);
    otava::intermediate::Value* sourceValue = emitter.EmitLoad(sourceElemAddr);
    args[0]->Load(emitter, OperationFlags::none, sourcePos, context);
    otava::intermediate::Value* targetArray = emitter.Stack().Pop();
    otava::intermediate::Value* targetElemAddr = emitter.EmitElemAddr(targetArray, currentLoopIndexValue);
    emitter.EmitStore(sourceValue, targetElemAddr);
    otava::intermediate::Value* nextLoopIndexValue = emitter.EmitAdd(currentLoopIndexValue, emitter.EmitLong(1));
    emitter.EmitStore(nextLoopIndexValue, loopIndexVar);
    emitter.EmitJump(condBlock);
    emitter.SetCodeGenNextBlock(nextBlock);
    emitter.SetCurrentBasicBlock(nextBlock);
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

void ArrayTypeCopyAssignment::Write(Writer& writer)
{
    FunctionSymbol::Write(writer);
    writer.GetBinaryStreamWriter().Write(arrayType->Id());
}

void ArrayTypeCopyAssignment::Read(Reader& reader)
{
    FunctionSymbol::Read(reader);
    reader.GetBinaryStreamReader().ReadUuid(arrayTypeId);
}

void ArrayTypeCopyAssignment::Resolve(SymbolTable& symbolTable)
{
    TypeSymbol* type = symbolTable.GetType(arrayTypeId);
    if (type->IsArrayTypeSymbol())
    {
        arrayType = static_cast<ArrayTypeSymbol*>(type);
    }
    else
    {
        otava::ast::SetExceptionThrown();
        throw std::runtime_error("otava.symbols.array.type.symbol: array type expected");
    }
}
void ArrayTypeCopyAssignment::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    otava::intermediate::Value* loopIndexVar = emitter.EmitLocal(emitter.GetLongType());
    emitter.EmitStore(emitter.EmitLong(0), loopIndexVar);
    otava::intermediate::BasicBlock* condBlock = emitter.CreateBasicBlock();
    emitter.EmitJump(condBlock);
    emitter.SetCurrentBasicBlock(condBlock);
    otava::intermediate::Value* loopIndexValue = emitter.EmitLoad(loopIndexVar);
    otava::intermediate::Value* size = emitter.EmitLong(arrayType->Size());
    otava::intermediate::Value* less = emitter.EmitLess(loopIndexValue, size);
    otava::intermediate::BasicBlock* trueBlock = emitter.CreateBasicBlock();
    otava::intermediate::BasicBlock* nextBlock = emitter.CreateBasicBlock();
    emitter.EmitBranch(less, trueBlock, nextBlock);
    emitter.SetCurrentBasicBlock(trueBlock);
    otava::intermediate::Value* currentLoopIndexValue = emitter.EmitLoad(loopIndexVar);
    args[1]->Load(emitter, OperationFlags::none, sourcePos, context);
    otava::intermediate::Value* sourceArray = emitter.Stack().Pop();
    otava::intermediate::Value* sourceElemAddr = emitter.EmitElemAddr(sourceArray, currentLoopIndexValue);
    otava::intermediate::Value* sourceValue = emitter.EmitLoad(sourceElemAddr);
    args[0]->Load(emitter, OperationFlags::none, sourcePos, context);
    otava::intermediate::Value* targetArray = emitter.Stack().Pop();
    otava::intermediate::Value* targetElemAddr = emitter.EmitElemAddr(targetArray, currentLoopIndexValue);
    emitter.EmitStore(sourceValue, targetElemAddr);
    otava::intermediate::Value* nextLoopIndexValue = emitter.EmitAdd(currentLoopIndexValue, emitter.EmitLong(1));
    emitter.EmitStore(nextLoopIndexValue, loopIndexVar);
    emitter.EmitJump(condBlock);
    emitter.SetCodeGenNextBlock(nextBlock);
    emitter.SetCurrentBasicBlock(nextBlock);
    args[0]->Load(emitter, OperationFlags::none, sourcePos, context);
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

void ArrayTypeMoveAssignment::Write(Writer& writer)
{
    FunctionSymbol::Write(writer);
    writer.GetBinaryStreamWriter().Write(arrayType->Id());
}

void ArrayTypeMoveAssignment::Read(Reader& reader)
{
    FunctionSymbol::Read(reader);
    reader.GetBinaryStreamReader().ReadUuid(arrayTypeId);
}

void ArrayTypeMoveAssignment::Resolve(SymbolTable& symbolTable)
{
    TypeSymbol* type = symbolTable.GetType(arrayTypeId);
    if (type->IsArrayTypeSymbol())
    {
        arrayType = static_cast<ArrayTypeSymbol*>(type);
    }
    else
    {
        otava::ast::SetExceptionThrown();
        throw std::runtime_error("otava.symbols.array.type.symbol: array type expected");
    }
}

void ArrayTypeMoveAssignment::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    otava::intermediate::Value* loopIndexVar = emitter.EmitLocal(emitter.GetLongType());
    emitter.EmitStore(emitter.EmitLong(0), loopIndexVar);
    otava::intermediate::BasicBlock* condBlock = emitter.CreateBasicBlock();
    emitter.EmitJump(condBlock);
    emitter.SetCurrentBasicBlock(condBlock);
    otava::intermediate::Value* loopIndexValue = emitter.EmitLoad(loopIndexVar);
    otava::intermediate::Value* size = emitter.EmitLong(arrayType->Size());
    otava::intermediate::Value* less = emitter.EmitLess(loopIndexValue, size);
    otava::intermediate::BasicBlock* trueBlock = emitter.CreateBasicBlock();
    otava::intermediate::BasicBlock* nextBlock = emitter.CreateBasicBlock();
    emitter.EmitBranch(less, trueBlock, nextBlock);
    emitter.SetCurrentBasicBlock(trueBlock);
    otava::intermediate::Value* currentLoopIndexValue = emitter.EmitLoad(loopIndexVar);
    args[1]->Load(emitter, OperationFlags::none, sourcePos, context);
    otava::intermediate::Value* sourceArray = emitter.Stack().Pop();
    otava::intermediate::Value* sourceElemAddr = emitter.EmitElemAddr(sourceArray, currentLoopIndexValue);
    otava::intermediate::Value* sourceValue = emitter.EmitLoad(sourceElemAddr);
    args[0]->Load(emitter, OperationFlags::none, sourcePos, context);
    otava::intermediate::Value* targetArray = emitter.Stack().Pop();
    otava::intermediate::Value* targetElemAddr = emitter.EmitElemAddr(targetArray, currentLoopIndexValue);
    emitter.EmitStore(sourceValue, targetElemAddr);
    otava::intermediate::Value* nextLoopIndexValue = emitter.EmitAdd(currentLoopIndexValue, emitter.EmitLong(1));
    emitter.EmitStore(nextLoopIndexValue, loopIndexVar);
    emitter.EmitJump(condBlock);
    emitter.SetCodeGenNextBlock(nextBlock);
    emitter.SetCurrentBasicBlock(nextBlock);
    args[0]->Load(emitter, OperationFlags::none, sourcePos, context);
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

void ArrayTypeBegin::Write(Writer& writer)
{
    FunctionSymbol::Write(writer);
    writer.GetBinaryStreamWriter().Write(arrayType->Id());
}

void ArrayTypeBegin::Read(Reader& reader)
{
    FunctionSymbol::Read(reader);
    reader.GetBinaryStreamReader().ReadUuid(arrayTypeId);
}

void ArrayTypeBegin::Resolve(SymbolTable& symbolTable)
{
    TypeSymbol* type = symbolTable.GetType(arrayTypeId);
    if (type->IsArrayTypeSymbol())
    {
        arrayType = static_cast<ArrayTypeSymbol*>(type);
    }
    else
    {
        otava::ast::SetExceptionThrown();
        throw std::runtime_error("otava.symbols.array.type.symbol: array type expected");
    }
}

void ArrayTypeBegin::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    args[0]->Load(emitter, OperationFlags::none, sourcePos, context);
    otava::intermediate::Value* array = emitter.Stack().Pop();
    otava::intermediate::Value* elemAddr = emitter.EmitElemAddr(array, emitter.EmitLong(0));
    emitter.Stack().Push(elemAddr);
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

void ArrayTypeEnd::Write(Writer& writer)
{
    FunctionSymbol::Write(writer);
    writer.GetBinaryStreamWriter().Write(arrayType->Id());
}

void ArrayTypeEnd::Read(Reader& reader)
{
    FunctionSymbol::Read(reader);
    reader.GetBinaryStreamReader().ReadUuid(arrayTypeId);
}

void ArrayTypeEnd::Resolve(SymbolTable& symbolTable)
{
    TypeSymbol* type = symbolTable.GetType(arrayTypeId);
    if (type->IsArrayTypeSymbol())
    {
        arrayType = static_cast<ArrayTypeSymbol*>(type);
    }
    else
    {
        otava::ast::SetExceptionThrown();
        throw std::runtime_error("otava.symbols.array.type.symbol: array type expected");
    }
}

void ArrayTypeEnd::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    args[0]->Load(emitter, OperationFlags::none, sourcePos, context);
    otava::intermediate::Value* array = emitter.Stack().Pop();
    otava::intermediate::Value* elemAddr = emitter.EmitElemAddr(array, emitter.EmitLong(arrayType->Size()));
    emitter.Stack().Push(elemAddr);
}

} // namespace otava::symbols
