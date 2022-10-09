// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.intermediate.function;

import otava.intermediate.basic.block;
import otava.intermediate.code;
import otava.intermediate.error;
import otava.intermediate.instruction;
import otava.intermediate.metadata;
import otava.intermediate.type;
import otava.intermediate.util;
import otava.intermediate.visitor;

namespace otava::intermediate {

Function::Function(const SourcePos& sourcePos_, FunctionType* type_, const std::string& name_, bool once_, bool definition_, MetadataRef* metadataRef_) :
    flags(FunctionFlags::none), sourcePos(sourcePos_), type(type_), name(name_), metadataRef(metadataRef_), nextRegNumber(0),
    parent(nullptr), next(nullptr), prev(nullptr), first(nullptr), last(nullptr), nextBasicBlockId(0)
{
    if (once_)
    {
        SetFlag(FunctionFlags::once);
    }
    if (definition_)
    {
        SetFlag(FunctionFlags::defined);
    }
}

Function::~Function()
{
    BasicBlock* bb = first;
    while (bb)
    {
        BasicBlock* next = bb->Next();
        delete bb;
        bb = next;
    }
}

void Function::Finalize()
{
    int nextBBNumber = 0;
    BasicBlock* bb = first;
    while (bb)
    {
        if (bb->IsEmpty())
        {
            continue;
        }
        bb->SetId(nextBBNumber++);
        bb = bb->Next();
    }
}

void Function::Write(util::CodeFormatter& formatter)
{
    if (IsEmpty()) return;
    if (!IsDefined()) return;
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

Code* Function::Parent() const
{
    return parent;
}

BasicBlock* Function::CreateBasicBlock()
{
    BasicBlock* bb = new BasicBlock(SourcePos(), nextBasicBlockId++);
    AddBasicBlock(bb);
    return bb;
}

BasicBlock* Function::GetBasicBlock(int32_t id) const
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
    Function* container = bb->Parent();
    if (container)
    {
        std::unique_ptr<BasicBlock> removedChild = container->RemoveBasicBlock(bb);
        bb = removedChild.release();
    }
    if (last)
    {
        last->LinkAfter(bb);
    }
    if (!first)
    {
        first = bb;
    }
    bb->SetParent(this);
    last = bb;
}

void Function::InsertBefore(BasicBlock* bb, BasicBlock* before)
{
    if (!before)
    {
        AddBasicBlock(bb);
    }
    else
    {
        Function* container = bb->Parent();
        if (container)
        {
            std::unique_ptr<BasicBlock> removedChild = container->RemoveBasicBlock(bb);
            bb = removedChild.release();
        }
        bb->SetParent(this);
        if (first == before)
        {
            first = bb;
        }
        before->LinkBefore(bb);
    }
}

std::unique_ptr<BasicBlock> Function::RemoveBasicBlock(BasicBlock* bb)
{
    bb->Unlink();
    if (bb == first)
    {
        first = bb->Next();
    }
    if (bb == last)
    {
        last = bb->Prev();
    }
    bb->SetParent(nullptr);
    bb->SetNext(nullptr);
    bb->SetPrev(nullptr);
    return std::unique_ptr<BasicBlock>(bb);
}

BasicBlock* Function::AddBasicBlock(const SourcePos& sourcePos, int32_t id, Context* context)
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

RegValue* Function::GetRegValue(int32_t reg) const
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

RegValue* Function::GetRegRef(const SourcePos& sourcePos, Type* type, int32_t reg, Context* context) const
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
            Error("error referencing register value " + std::to_string(reg) + ": type conflick", sourcePos, context, regValue->GetSourcePos());
        }
    }
    else
    {
        Error("error referencing register: register " + std::to_string(reg) + " not found", sourcePos, context);
    }
    return nullptr;
}

RegValue* Function::MakeRegValue(const SourcePos& sourcePos, Type* type, int32_t reg, Context* context)
{
    RegValue* prev = GetRegValue(reg);
    if (prev)
    {
        Error("error adding register " + std::to_string(reg) + ": register not unique", sourcePos, context, prev->GetSourcePos());
    }
    RegValue* regValue = new RegValue(sourcePos, type, reg);
    regValues.push_back(std::unique_ptr<RegValue>(regValue));
    regValueMap[reg] = regValue;
    return regValue;
}

Instruction* Function::GetInstruction(int32_t reg) const
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

void Function::MapInstruction(int32_t reg, Instruction* inst, Context* context)
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
    if (IsEmpty())
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

/*
soul::xml::Element* Function::ToXml()
{
    soul::xml::Element* element = soul::xml::MakeElement(U"function");
    element->SetAttribute(U"name", ToUtf32(Name()));
    BasicBlock* block = FirstBasicBlock();
    while (block)
    {
        sngxml::dom::Element* blockElement = new sngxml::dom::Element(U"block");
        blockElement->SetAttribute(U"id", ToUtf32(block->Name()));
        for (BasicBlock* successor : block->Successors())
        {
            sngxml::dom::Element* successorElement = new sngxml::dom::Element(U"successor");
            successorElement->SetAttribute(U"id", ToUtf32(successor->Name()));
            blockElement->AppendChild(std::unique_ptr<sngxml::dom::Node>(successorElement));
        }
        for (BasicBlock* predecessor : block->Predecessors())
        {
            sngxml::dom::Element* predecessorElement = new sngxml::dom::Element(U"predecessor");
            predecessorElement->SetAttribute(U"id", ToUtf32(predecessor->Name()));
            blockElement->AppendChild(std::unique_ptr<sngxml::dom::Node>(predecessorElement));
        }
        element->AppendChild(std::unique_ptr<sngxml::dom::Node>(blockElement));
        block = block->Next();
    }
    return element;
}

void Function::WriteXmlDocument(const std::string& filePath)
{
    sngxml::dom::Element* element = ToXml();
    sngxml::dom::Document document;
    document.AppendChild(std::unique_ptr<sngxml::dom::Node>(element));
    std::ofstream file(filePath);
    CodeFormatter formatter(file);
    formatter.SetIndentSize(1);
    document.Write(formatter);
}
*/

int Function::Arity() const 
{ 
    return type->Arity(); 
}

} // otava::intermediate