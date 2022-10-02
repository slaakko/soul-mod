// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.intermediate.basic.block;

import otava.intermediate.code;
import otava.intermediate.function;
import otava.intermediate.instruction;
import otava.intermediate.util;
import otava.intermediate.visitor;
import util.text.util;

namespace otava::intermediate {

BasicBlock::BasicBlock(const SourcePos& sourcePos_, int32_t id_) : sourcePos(sourcePos_), id(id_), parent(nullptr), next(nullptr), prev(nullptr), first(nullptr), last(nullptr)
{
}

BasicBlock::~BasicBlock()
{
    Instruction* inst = first;
    while (inst)
    {
        Instruction* next = inst->Next();
        delete inst;
        inst = next;
    }
}

void BasicBlock::Write(util::CodeFormatter& formatter)
{
    int indent = formatter.IndentSize();
    bool indentDecremented = false;
    if (formatter.CurrentIndent() > 0)
    {
        formatter.DecIndent();
        indentDecremented = true;
    }
    formatter.Write(util::Format("@" + std::to_string(id), indent, util::FormatWidth::min));
    Instruction* inst = FirstInstruction();
    bool first = true;
    while (inst)
    {
        inst->Write(formatter);
        formatter.WriteLine();
        if (first)
        {
            if (indentDecremented)
            {
                formatter.IncIndent();
            }
            first = false;
        }
        inst = inst->Next();
    }
}

Function* BasicBlock::Parent() const
{
    return parent;
}

void BasicBlock::SetParent(Function* parent_)
{
    parent = parent_;
}

void BasicBlock::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void BasicBlock::VisitInstructions(Visitor& visitor)
{
    Instruction* inst = FirstInstruction();
    while (inst != nullptr)
    {
        inst->Accept(visitor);
        inst = inst->Next();
    }
}

std::string BasicBlock::Name() const
{
    if (id == entryBlockId)
    {
        return "entry";
    }
    else if (id == exitBlockId)
    {
        return "exit";
    }
    else
    {
        return std::to_string(id);
    }
}

void BasicBlock::AddInst(Instruction* inst)
{
    BasicBlock* container = inst->Parent();
    if (container)
    {
        std::unique_ptr<Instruction> removedChild = container->RemoveInst(inst);
        inst = removedChild.release();
    }
    if (last)
    {
        last->LinkAfter(inst);
    }
    if (!first)
    {
        first = inst;
    }
    inst->SetParent(this);
    last = inst;
}

void BasicBlock::InsertBefore(Instruction* inst, Instruction* before)
{
    if (!before)
    {
        AddInst(inst);
    }
    else
    {
        BasicBlock* container = inst->Parent();
        if (container)
        {
            std::unique_ptr<Instruction> removedChild = container->RemoveInst(inst);
            inst = removedChild.release();
        }
        inst->SetParent(this);
        if (first == before)
        {
            first = inst;
        }
        before->LinkBefore(inst);
    }
}

void BasicBlock::AddInstruction(Instruction* instruction, MetadataRef* metadataRef)
{
    instruction->SetMetadataRef(metadataRef);
    AddInst(instruction);
    if (instruction->IsValueInstruction())
    {
        ValueInstruction* valueInstruction = static_cast<ValueInstruction*>(instruction);
        Function* function = Parent();
        Code* code = function->Parent();
        Context* context = code->GetContext();
        function->MapInstruction(valueInstruction->Result()->Reg(), valueInstruction, context);
    }
}

void BasicBlock::AddInstruction(Instruction* instruction)
{
    AddInst(instruction);
}

std::unique_ptr<Instruction> BasicBlock::RemoveInst(Instruction* inst)
{
    inst->Unlink();
    if (inst == first)
    {
        first = inst->Next();
    }
    if (inst == last)
    {
        last = inst->Prev();
    }
    inst->SetParent(nullptr);
    inst->SetNext(nullptr);
    inst->SetPrev(nullptr);
    return std::unique_ptr<Instruction>(inst);
}

void BasicBlock::InsertFront(Instruction* instruction)
{
    if (IsEmpty())
    {
        AddInst(instruction);
    }
    else
    {
        InsertBefore(instruction, first);
    }
    if (instruction->IsValueInstruction())
    {
        ValueInstruction* valueInstruction = static_cast<ValueInstruction*>(instruction);
        Function* function = Parent();
        Context* context = function->Parent()->GetContext();
        function->MapInstruction(valueInstruction->Result()->Reg(), valueInstruction, context);
    }
}

void BasicBlock::AddSuccessor(BasicBlock* successor)
{
    AddPtrToSet(successor, successors);
}

bool BasicBlock::RemoveSuccessor(BasicBlock* successor)
{
    return RemovePtrFromSet(successor, successors);
}

void BasicBlock::AddPredecessor(BasicBlock* predecessor)
{
    AddPtrToSet(predecessor, predecessors);
}

bool BasicBlock::RemovePredecessor(BasicBlock* predecessor)
{
    return RemovePtrFromSet(predecessor, predecessors);
}

void BasicBlock::ClearSuccessorsAndPredecessors()
{
    successors.clear();
    predecessors.clear();
}

int BasicBlock::IndexOf(Instruction* x)
{
    int index = 0;
    Instruction* inst = FirstInstruction();
    while (inst)
    {
        if (inst == x)
        {
            return index;
        }
        ++index;
        inst = inst->Next();
    }
    return -1;
}

bool BasicBlock::HasPhiInstructions() 
{ 
    return FirstInstruction()->IsPhiInstruction(); 
}

} // namespace otava::intermediate
