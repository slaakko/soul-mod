// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.intermediate.function;

import std.core;
import util.code.formatter;
import soul.ast.source.pos;
import otava.intermediate.value;

export namespace otava::intermediate::function {}

export namespace otava::intermediate {

using SourcePos = soul::ast::SourcePos;

class FunctionType;
class MetadataRef;
class Visitor;
class Code;
class BasicBlock;
class Context;
class RegValue;
class Type;
class Instruction;

enum class FunctionFlags : int
{
    none = 0, defined = 1 << 0, once = 1 << 1
};

constexpr FunctionFlags operator|(FunctionFlags left, FunctionFlags right)
{
    return FunctionFlags(static_cast<int>(left) | static_cast<int>(right));
}

constexpr FunctionFlags operator&(FunctionFlags left, FunctionFlags right)
{
    return FunctionFlags(static_cast<int>(left) & static_cast<int>(right));
}

constexpr FunctionFlags operator~(FunctionFlags flags)
{
    return FunctionFlags(~static_cast<int>(flags));
}

class Function : public Value
{
public:
    Function(const SourcePos& sourcePos_, FunctionType* functionType_, const std::string& name_, bool once_, bool definition_, MetadataRef* metadataRef_, Context* context);
    ~Function();
    void Finalize();
    void Write(util::CodeFormatter& formatter);
    bool GetFlag(FunctionFlags flag) const { return (flags & flag) != FunctionFlags::none; }
    void SetFlag(FunctionFlags flag) { flags = flags | flag; }
    void ResetFlag(FunctionFlags flag) { flags = flags & ~flag; }
    bool IsDefined() const { return GetFlag(FunctionFlags::defined); }
    bool IsExternal() const { return !IsDefined(); }
    void SetDefined() { SetFlag(FunctionFlags::defined); }
    bool Once() const { return GetFlag(FunctionFlags::once); }
    int Arity() const;
    void Accept(Visitor& visitor);
    void VisitBasicBlocks(Visitor& visitor);
    Code* Parent() const;
    void SetParent(Code* parent_) { parent = parent_; }
    Function* Next() { return next; }
    void SetNext(Function* next_) { next = next_; }
    Function* Prev() { return prev; }
    void SetPrev(Function* prev_) { prev = prev_; }
    bool IsEmpty() const { return first == nullptr; }
    BasicBlock* GetBasicBlock(int32_t id) const;
    BasicBlock* CreateBasicBlock();
    BasicBlock* AddBasicBlock(const SourcePos& sourcePos, int32_t id, Context* context);
    std::unique_ptr<BasicBlock> RemoveBasicBlock(BasicBlock* bb);
    bool DoRemoveBasicBlock(BasicBlock* block);
    BasicBlock* FirstBasicBlock() { return first; }
    BasicBlock* LastBasicBlock() { return last; }
    const SourcePos& GetSourcePos() const { return sourcePos; }
    FunctionType* GetType() const { return type; }
    const std::string& Name() const { return name; }
    std::string ToString() const override { return name; }
    MetadataRef* GetMetadataRef() const { return metadataRef; }
    RegValue* GetRegValue(int32_t reg) const;
    RegValue* GetRegRef(const SourcePos& sourcePos, Type* type, int32_t reg, Context* context) const;
    RegValue* MakeRegValue(const SourcePos& sourcePos, Type* type, int32_t reg, Context* context);
    Instruction* GetInstruction(int32_t reg) const;
    void MapInstruction(int32_t reg, Instruction* inst, Context* context);
    int NumBasicBlocks() const;
    const std::vector<BasicBlock*>& RetBlocks() const { return retBlocks; }
    void AddRetBlock(BasicBlock* retBlock);
    void AddEntryAndExitBlocks();
    void RemoveEntryAndExitBlocks();
    void SetNextRegNumber(int32_t nextRegNumber_) { nextRegNumber = nextRegNumber_; }
    int32_t NextRegNumber() const { return nextRegNumber; }
    void LinkBefore(Function* fn)
    {
        if (prev)
        {
            prev->next = fn;
        }
        fn->prev = prev;
        fn->next = this;
        prev = fn;
    }
    void LinkAfter(Function* fn)
    {
        if (next)
        {
            next->prev = fn;
        }
        fn->prev = this;
        fn->next = next;
        next = fn;
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
    Value* GetParam(int index) const;
private:
    void AddBasicBlock(BasicBlock* bb);
    void InsertBefore(BasicBlock* bb, BasicBlock* before);
    FunctionFlags flags;
    SourcePos sourcePos;
    FunctionType* type;
    std::string name;
    std::vector<Instruction*> params;
    std::unique_ptr<BasicBlock> entryBlock;
    MetadataRef* metadataRef;
    std::map<int32_t, BasicBlock*> basicBlockMap;
    std::map<int32_t, RegValue*> regValueMap;
    std::map<int32_t, Instruction*> instructionMap;
    std::vector<std::unique_ptr<RegValue>> regValues;
    std::vector<BasicBlock*> retBlocks;
    int32_t nextRegNumber;
    Code* parent;
    Function* next;
    Function* prev;
    BasicBlock* first;
    BasicBlock* last;
    int32_t nextBasicBlockId;
};

} // otava::intermediate
