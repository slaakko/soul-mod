// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.intermediate.basic.block;

import std;
import util.code.formatter;
import util.component;
import soul.ast.source.pos;

export namespace otava::intermediate::basic::block {}

export namespace otava::intermediate {

using SourcePos = soul::ast::SourcePos;

class Function;
class Visitor;
class Instruction;
class MetadataRef;

const std::int32_t entryBlockId = -1;
const std::int32_t exitBlockId = -2;

class BasicBlock : public util::Component
{
public:
    BasicBlock(const SourcePos& sourcePos_, std::int32_t id_);
    void Write(util::CodeFormatter& formatter);
    void Accept(Visitor& visitor);
    void VisitInstructions(Visitor& visitor);
    const SourcePos& GetSourcePos() const { return sourcePos; }
    std::string Name() const;
    std::int32_t Id() const { return id; }
    void SetId(std::int32_t id_) { id = id_; }
    bool IsEmpty() const { return instructions.IsEmpty(); }
    Function* Parent() const;
    BasicBlock* Next() { return static_cast<BasicBlock*>(NextSibling()); }
    void SetNext(BasicBlock* next_) { SetNextSibling(next_); }
    BasicBlock* Prev() { return static_cast<BasicBlock*>(PrevSibling()); }
    void SetPrev(BasicBlock* prev_) { SetPrevSibling(prev_); }
    Instruction* FirstInstruction();
    Instruction* LastInstruction();
    bool HasPhiInstructions();
    void AddInstruction(Instruction* instruction, MetadataRef* metadataRef);
    void AddInstruction(Instruction* instruction);
    void InsertFront(Instruction* instruction);
    std::unique_ptr<Instruction> RemoveInst(Instruction* inst);
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
private:
    void AddInst(Instruction* inst);
    SourcePos sourcePos;
    std::int32_t id;
    std::vector<BasicBlock*> successors;
    std::vector<BasicBlock*> predecessors;
    util::Container instructions;
};

} // namespace otava::intermediate
