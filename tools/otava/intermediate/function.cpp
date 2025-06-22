// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.intermediate.function;

import otava.intermediate.basic.block;
import otava.intermediate.code;
import otava.intermediate.context;
import otava.intermediate.error;
import otava.intermediate.instruction;
import otava.intermediate.metadata;
import otava.intermediate.type;
import otava.intermediate.util;
import otava.intermediate.visitor;

namespace otava::intermediate {

Function::Function(const SourcePos& sourcePos_, FunctionType* type_, const std::string& name_, bool once_, bool definition_, MetadataRef* metadataRef_, Context* context) :
    Value(sourcePos_, ValueKind::function, type_),
    flags(FunctionFlags::none), sourcePos(sourcePos_), type(type_), name(name_), metadataRef(metadataRef_), nextRegNumber(0), basicBlocks(this), nextBasicBlockId(0)
{
    entryBlock.reset(new BasicBlock(sourcePos_, nextBasicBlockId++));
    std::int32_t n = type->ParamTypeRefs().size();
    for (std::int32_t index = 0; index < n; ++index)
    {
        const TypeRef& paramTypeRef = type->ParamTypeRefs()[index];
        RegValue* regValue = new RegValue(sourcePos_, paramTypeRef.GetType());
        Instruction* paramInst = new ParamInstruction(sourcePos_, regValue);
        context->AddLineInfo(paramInst);
        entryBlock->AddInstruction(paramInst);
        params.push_back(paramInst);
    }
    if (once_)
    {
        SetFlag(FunctionFlags::once);
    }
    if (definition_)
    {
        SetFlag(FunctionFlags::defined);
    }
}

Code* Function::Parent() const
{
    return static_cast<Code*>(GetContainer()->Parent());
}

BasicBlock* Function::FirstBasicBlock()
{ 
    return static_cast<BasicBlock*>(basicBlocks.FirstChild()); 
}

BasicBlock* Function::LastBasicBlock()
{ 
    return static_cast<BasicBlock*>(basicBlocks.LastChild()); 
}

void Function::Finalize()
{
    int nextBBNumber = 0;
    BasicBlock* bb = FirstBasicBlock();
    while (bb)
    {
        if (bb->IsEmpty())
        {
            bb = bb->Next();
            continue;
        }
        bb->SetId(nextBBNumber++);
        bb = bb->Next();
    }
}

bool Function::Write(util::CodeFormatter& formatter)
{
    if (!IsDefined())
    {
        formatter.WriteLine("extern function " + type->Name() + " " + name);
        return true;
    }
    else
    {
        Finalize();
        std::string once;
        if (Once())
        {
            once = " once";
        }
        std::string mdIdStr;
        if (metadataRef)
        {
            mdIdStr = " !" + std::to_string(metadataRef->NodeId());
        }
        formatter.WriteLine("function " + type->Name() + once + " " + name + mdIdStr);
        formatter.WriteLine("{");
        formatter.IncIndent();
        bool first = true;
        BasicBlock* bb = FirstBasicBlock();
        while (bb)
        {
            if (bb->IsEmpty())
            {
                bb = bb->Next();
                continue;
            }
            if (first)
            {
                first = false;
            }
            else
            {
                formatter.WriteLine();
            }
            bb->Write(formatter);
            bb = bb->Next();
        }
        formatter.DecIndent();
        formatter.WriteLine("}");
        return true;
    }
}

void Function::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void Function::VisitBasicBlocks(Visitor& visitor)
{
    BasicBlock* basicBlock = FirstBasicBlock();
    while (basicBlock)
    {
        basicBlock->Accept(visitor);
        basicBlock = basicBlock->Next();
    }
}

BasicBlock* Function::CreateBasicBlock()
{
    if (!FirstBasicBlock())
    {
        BasicBlock* eb = entryBlock.release();
        AddBasicBlock(eb);
        basicBlockMap[eb->Id()] = eb;
        return eb;
    }
    BasicBlock* bb = new BasicBlock(SourcePos(), nextBasicBlockId++);
    AddBasicBlock(bb);
    basicBlockMap[bb->Id()] = bb;
    return bb;
}

BasicBlock* Function::GetBasicBlock(std::int32_t id) const
{
    auto it = basicBlockMap.find(id);
    if (it != basicBlockMap.cend())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}

void Function::AddBasicBlock(BasicBlock* bb)
{
    basicBlocks.AddChild(bb);
}

void Function::InsertBefore(BasicBlock* bb, BasicBlock* before)
{
    basicBlocks.InsertBefore(bb, before);
}

std::unique_ptr<BasicBlock> Function::RemoveBasicBlock(BasicBlock* bb)
{
    return std::unique_ptr<BasicBlock>(static_cast<BasicBlock*>(basicBlocks.RemoveChild(bb).release()));
}

BasicBlock* Function::AddBasicBlock(const SourcePos& sourcePos, std::int32_t id, Context* context)
{
    BasicBlock* prev = GetBasicBlock(id);
    if (prev)
    {
        Error("error adding basic block: basic block id not unique", sourcePos, context, prev->GetSourcePos());
    }
    BasicBlock* basicBlock = new BasicBlock(sourcePos, id);
    AddBasicBlock(basicBlock);
    basicBlockMap[id] = basicBlock;
    return basicBlock;
}

bool Function::DoRemoveBasicBlock(BasicBlock* block)
{
    if (!GetBasicBlock(block->Id())) return false;
    RemovePtrFromSet(block, retBlocks);
    basicBlockMap.erase(block->Id());
    for (BasicBlock* successor : block->Successors())
    {
        successor->RemovePredecessor(block);
    }
    for (BasicBlock* predecessor : block->Predecessors())
    {
        predecessor->RemoveSuccessor(block);
    }
    RemoveBasicBlock(block);
    return true;
}

RegValue* Function::GetRegValue(std::int32_t reg) const
{
    auto it = regValueMap.find(reg);
    if (it != regValueMap.cend())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}

RegValue* Function::GetRegRef(const SourcePos& sourcePos, Type* type, std::int32_t reg, Context* context) const
{
    RegValue* regValue = GetRegValue(reg);
    if (regValue)
    {
        if (regValue->GetType() == type)
        {
            return regValue;
        }
        else
        {
            Error("error referencing register value " + std::to_string(reg) + ": type conflict", sourcePos, context, regValue->GetSourcePos());
        }
    }
    else
    {
        Error("error referencing register: register " + std::to_string(reg) + " not found", sourcePos, context);
    }
    return nullptr;
}

RegValue* Function::MakeRegValue(const SourcePos& sourcePos, Type* type, std::int32_t reg, Context* context)
{
    RegValue* prev = GetRegValue(reg);
    if (prev)
    {
        Error("error adding register " + std::to_string(reg) + ": register not unique", sourcePos, context, prev->GetSourcePos());
    }
    RegValue* regValue = new RegValue(sourcePos, type);
    regValue->SetReg(reg);
    regValues.push_back(std::unique_ptr<RegValue>(regValue));
    regValueMap[reg] = regValue;
    return regValue;
}

Instruction* Function::GetInstruction(std::int32_t reg) const
{
    auto it = instructionMap.find(reg);
    if (it != instructionMap.cend())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}

void Function::MapInstruction(std::int32_t reg, Instruction* inst, Context* context)
{
    Instruction* prev = GetInstruction(reg);
    if (prev)
    {
        Error("error mappint instruction " + std::to_string(reg) + ": register number not unique", sourcePos, context, prev->GetSourcePos());
    }
    instructionMap[reg] = inst;
}

int Function::NumBasicBlocks() const
{
    return basicBlockMap.size();
}

void Function::AddRetBlock(BasicBlock* retBlock)
{
    AddPtrToSet(retBlock, retBlocks);
}

void Function::AddEntryAndExitBlocks()
{
    if (basicBlocks.IsEmpty())
    {
        Error("error adding entry and exit blocks: function '" + Name() + "' has no basic blocks", GetSourcePos(), Parent()->GetContext());
    }
    BasicBlock* prevEntryBlock = GetBasicBlock(entryBlockId);
    if (prevEntryBlock)
    {
        Error("error adding entry and exit blocks: function '" + Name() + "' has already an entry block", GetSourcePos(), Parent()->GetContext());
    }
    BasicBlock* prevExitBlock = GetBasicBlock(exitBlockId);
    if (prevExitBlock)
    {
        Error("error adding entry and exit blocks: function '" + Name() + "' has already an exit block", GetSourcePos(), Parent()->GetContext());
    }
    if (RetBlocks().empty())
    {
        Error("error adding entry and exit blocks: function '" + Name() + "' has no ret blocks", GetSourcePos(), Parent()->GetContext());
    }
    BasicBlock* firstBasicBlock = FirstBasicBlock();
    BasicBlock* entryBlock = new BasicBlock(GetSourcePos(), entryBlockId);
    basicBlockMap[entryBlock->Id()] = entryBlock;
    entryBlock->AddSuccessor(firstBasicBlock);
    firstBasicBlock->AddPredecessor(entryBlock);
    InsertBefore(entryBlock, firstBasicBlock);
    BasicBlock* exitBlock = new BasicBlock(GetSourcePos(), exitBlockId);
    for (BasicBlock* retBlock : RetBlocks())
    {
        retBlock->AddSuccessor(exitBlock);
        exitBlock->AddPredecessor(retBlock);
    }
    AddBasicBlock(exitBlock);
}

void Function::RemoveEntryAndExitBlocks()
{
    BasicBlock* entryBlock = GetBasicBlock(entryBlockId);
    if (!entryBlock)
    {
        Error("error removing entry and exit blocks: function '" + Name() + "' has no entry block", GetSourcePos(), Parent()->GetContext());
    }
    BasicBlock* exitBlock = GetBasicBlock(exitBlockId);
    if (!exitBlock)
    {
        Error("error removing entry and exit blocks: function '" + Name() + "' has no exit block", GetSourcePos(), Parent()->GetContext());
    }
    BasicBlock* firstBasicBlock = entryBlock->Next();
    if (!firstBasicBlock)
    {
        Error("error removing entry and exit blocks: function '" + Name() + "' has no basic blocks other than entry and exit blocks", GetSourcePos(), Parent()->GetContext());
    }
    if (!firstBasicBlock->RemovePredecessor(entryBlock))
    {
        Error("error removing entry and exit blocks: function '" + Name() + "' old first block does not have the entry block as a predecessor", GetSourcePos(), Parent()->GetContext());
    }
    RemoveBasicBlock(entryBlock);
    basicBlockMap.erase(entryBlockId);
    for (BasicBlock* retBlock : RetBlocks())
    {
        if (!retBlock->RemoveSuccessor(exitBlock))
        {
            Error("error removing entry and exit blocks: function '" + Name() + "' ret block does not have the exit block as a successor", GetSourcePos(), Parent()->GetContext());
        }
    }
    RemoveBasicBlock(exitBlock);
    basicBlockMap.erase(exitBlockId);
}

Value* Function::GetParam(int index) const
{
    if (index >= 0 && index < params.size())
    {
        return params[index];
    }
    else
    {
        Error("invalid param index", GetSourcePos(), Parent()->GetContext());
        return nullptr;
    }
}

void Function::SetRegNumbers()
{
    nextRegNumber = 0;
    BasicBlock* bb = FirstBasicBlock();
    while (bb)
    {
        Instruction* inst = bb->FirstInstruction();
        while (inst)
        {
            inst->SetRegNumber(*this);
            inst = inst->Next();
        }
        bb = bb->Next();
    }
}

int Function::Arity() const 
{ 
    return type->Arity(); 
}

} // otava::intermediate
