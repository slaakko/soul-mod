// =================================
// Copyright (c) 2023 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.intermediate.function;

import std.core;
import util.code.formatter;
import util.component;
import soul.ast.source.pos;
import otava.intermediate.value;
import otava.intermediate.instruction;

export namespace otava::intermediate::function {}

export namespace otava::intermediate {

using SourcePos = soul::ast::SourcePos;

class FunctionType;
class MetadataRef;
class Visitor;
class Code;
class BasicBlock;
class Context;
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

class Function : public Value, public util::Component
{
public:
    Function(const SourcePos& sourcePos_, FunctionType* functionType_, const std::string& name_, bool once_, bool definition_, MetadataRef* metadataRef_, Context* context);
    void Finalize();
    bool Write(util::CodeFormatter& formatter);
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
    Function* Next() { return static_cast<Function*>(NextSibling()); }
    void SetNext(Function* next_) { SetNextSibling(next_); }
    Function* Prev() { return static_cast<Function*>(PrevSibling()); }
    void SetPrev(Function* prev_) { SetPrevSibling(prev_); }
    BasicBlock* GetBasicBlock(int32_t id) const;
    BasicBlock* CreateBasicBlock();
    BasicBlock* AddBasicBlock(const SourcePos& sourcePos, int32_t id, Context* context);
    std::unique_ptr<BasicBlock> RemoveBasicBlock(BasicBlock* bb);
    bool DoRemoveBasicBlock(BasicBlock* block);
    BasicBlock* FirstBasicBlock();
    BasicBlock* LastBasicBlock();
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
    void SetRegNumbers();
    int32_t NextRegNumber() { return nextRegNumber++; }
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
    util::Container basicBlocks;
    int32_t nextBasicBlockId;
};

} // otava::intermediate
