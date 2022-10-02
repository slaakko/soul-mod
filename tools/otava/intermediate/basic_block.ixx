// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.intermediate.basic.block;

import std.core;
import util.code.formatter;
import soul.ast.source.pos;

export namespace otava::intermediate::basic::block {}

export namespace otava::intermediate {

using SourcePos = soul::ast::SourcePos;

class Function;
class Visitor;
class Instruction;
class MetadataRef;

const int32_t entryBlockId = -1;
const int32_t exitBlockId = -2;

class BasicBlock
{
public:
    BasicBlock(const SourcePos& sourcePos_, int32_t id_);
    ~BasicBlock();
    void Write(util::CodeFormatter& formatter);
    void Accept(Visitor& visitor);
    void VisitInstructions(Visitor& visitor);
    const SourcePos& GetSourcePos() const { return sourcePos; }
    std::string Name() const;
    int32_t Id() const { return id; }
    void SetId(int32_t id_) { id = id_; }
    Function* Parent() const;
    void SetParent(Function* parent_);
    BasicBlock* Next() { return next; }
    void SetNext(BasicBlock* next_) { next = next_; }
    BasicBlock* Prev() { return prev; }
    void SetPrev(BasicBlock* prev_) { prev = prev_; }
    Instruction* FirstInstruction() { return first; }
    Instruction* LastInstruction() { return last; }
    bool HasPhiInstructions();
    void AddInstruction(Instruction* instruction, MetadataRef* metadataRef);
    void AddInstruction(Instruction* instruction);
    void InsertFront(Instruction* instruction);
    std::unique_ptr<Instruction> RemoveInst(Instruction* inst);
    bool IsEmpty() const { return first == nullptr; }
    bool IsEntryBlock() const { return id == entryBlockId; }
    bool IsExitBlock() const { return id == exitBlockId; }
    const std::vector<BasicBlock*>& Successors() const { return successors; }
    void AddSuccessor(BasicBlock* successor);
    bool RemoveSuccessor(BasicBlock* successor);
    const std::vector<BasicBlock*>& Predecessors() const { return predecessors; }
    void AddPredecessor(BasicBlock* predecessor);
    bool RemovePredecessor(BasicBlock* predecessor);
    void ClearSuccessorsAndPredecessors();
    int IndexOf(Instruction* x);
    void LinkBefore(BasicBlock* bb)
    {
        if (prev)
        {
            prev->next = bb;
        }
        bb->prev = prev;
        bb->next = this;
        prev = bb;
    }
    void LinkAfter(BasicBlock* bb)
    {
        if (next)
        {
            next->prev = bb;
        }
        bb->prev = this;
        bb->next = next;
        next = bb;
    }
    void Unlink()
    {
        if (prev)
        {
            prev->next = next;
        }
        if (next)
        {
            next->prev = prev;
        }
    }
private:
    void AddInst(Instruction* inst);
    void InsertBefore(Instruction* inst, Instruction* before);
    SourcePos sourcePos;
    int32_t id;
    std::vector<BasicBlock*> successors;
    std::vector<BasicBlock*> predecessors;
    Function* parent;
    BasicBlock* next;
    BasicBlock* prev;
    Instruction* first;
    Instruction* last;
};

} // namespace otava::intermediate
