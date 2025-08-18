// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.intermediate.code;

import otava.intermediate.data;
import util;
import std;

export namespace otava::intermediate {

namespace code {}

class Instruction;
class BasicBlock;
class MetadataRef;
class Function;
class Code;

class RegValue : public Value
{
public:
    RegValue(const soul::ast::Span& span_, Type* type_, std::int32_t reg_);
    ~RegValue();
    Value* Clone(CloneContext& cloneContext) const;
    inline std::int32_t Reg() const { return reg; }
    inline void SetReg(std::int32_t reg_) { reg = reg_; }
    inline void SetInst(Instruction* inst_) { inst = inst_; }
    inline Instruction* Inst() const { return inst; }
    std::string ToString() const override;
private:
    std::int32_t reg;
    Instruction* inst;
};

enum class OpCode : int
{
    store, arg, jmp, branch, procedure_call, ret, switch_,
    not_, neg, signextend, zeroextend, truncate, fpextend, bitcast, inttofloat, floattoint, inttoptr, ptrtoint,
    add, sub, mul, div_, mod, and_, or_, xor_, shl, shr, equal, less,
    param, local, load, elemaddr, ptroffset, ptrdiff, function_call,
    nop
};

void AddUser(Instruction* user, Value* value);
void RemoveUser(Instruction* user, Value* value);
void AddToUsesVec(std::vector<Instruction*>& uses, Value* value);

class Instruction : public Value, public util::Component
{
public:
    Instruction(const soul::ast::Span& span_, Type* type_, OpCode opCode_);
    void Check();
    std::string Name() const;
    virtual void Accept(Visitor& visitor) = 0;
    virtual Instruction* Clone(CloneContext& cloneContext) const = 0;
    BasicBlock* Parent() const;
    inline Instruction* Next() { return static_cast<Instruction*>(NextSibling()); }
    inline Instruction* Prev() { return static_cast<Instruction*>(PrevSibling()); }
    inline OpCode GetOpCode() const { return opCode; }
    inline void SetMetadataRef(MetadataRef* metadataRef_) { metadataRef = metadataRef_; }
    inline MetadataRef* GetMetadataRef() const { return metadataRef; }
    bool IsLeader() const;
    bool IsTerminator() const;
    bool IsValueInstruction() const;
    bool IsUnaryInstruction() const;
    bool IsBinaryInstruction() const;
    inline bool IsSwitchInstruction() const { return opCode == OpCode::switch_; }
    inline bool IsParamInstruction() const { return opCode == OpCode::param; }
    inline bool IsLocalInstruction() const { return opCode == OpCode::local; }
    inline bool IsLoadInstruction() const { return opCode == OpCode::load; }
    inline bool IsStoreInstruction() const { return opCode == OpCode::store; }
    inline bool IsElemAddrInstruction() const { return opCode == OpCode::elemaddr; }
    inline bool IsArgInstruction() const { return opCode == OpCode::arg; }
    inline bool IsFunctionCallInstruction() const { return opCode == OpCode::function_call; }
    inline bool IsProcedureCallInstruction() const { return opCode == OpCode::procedure_call; }
    inline bool IsRetInstruction() const { return opCode == OpCode::ret; }
    bool IsRetVoid() const;
    inline bool IsJumpInstruction() const { return opCode == OpCode::jmp; }
    inline bool IsBranchInstruction() const { return opCode == OpCode::branch; }
    inline bool IsNopInstruction() const { return opCode == OpCode::nop; }
    bool RequiresLocalRegister() const;
    virtual bool IsFloatingPointInstruction() const { return false; }
    std::vector<BasicBlock*> Successors() const;
    inline int Index() const { return index; }
    inline void SetIndex(int index_) { index = index_; }
    inline int RegValueIndex() const { return regValueIndex; }
    inline void SetRegValueIndex(int regValueIndex_) { regValueIndex = regValueIndex_; }
    inline const std::vector<Instruction*>& Users() const { return users; }
    void AddUser(Instruction* user);
    void RemoveUser(Instruction* user);
    virtual std::vector<Instruction*> Uses() const { return std::vector<Instruction*>(); }
    virtual void AddToUses();
    void ReplaceUsesWith(Value* value);
    void RemoveFromUses();
    virtual void ReplaceValue(Value* use, Value* value);
    virtual void Write(util::CodeFormatter& formatter) = 0;
    inline void SetAssemblyIndex(int assemblyIndex_) { assemblyIndex = assemblyIndex_; }
    inline int AssemblyIndex() const { return assemblyIndex; }
private:
    OpCode opCode;
    MetadataRef* metadataRef;
    int index;
    int regValueIndex;
    int assemblyIndex;
    std::vector<Instruction*> users;
};

class StoreInstruction : public Instruction
{
public:
    StoreInstruction(const soul::ast::Span& span_, Value* value_, Value* ptr_);
    void Accept(Visitor& visitor) override;
    Instruction* Clone(CloneContext& cloneContext) const override;
    void Write(util::CodeFormatter& formatter) override;
    inline Value* GetValue() const { return value; }
    inline Value* GetPtr() const { return ptr; }
    bool IsFloatingPointInstruction() const override { return value->GetType()->IsFloatingPointType(); }
    void AddToUses() override;
    void ReplaceValue(Value* use, Value* value) override;
    std::vector<Instruction*> Uses() const override;
private:
    Value* value;
    Value* ptr;
};

class ArgInstruction : public Instruction
{
public:
    ArgInstruction(const soul::ast::Span& span_, Value* arg_);
    void Accept(Visitor& visitor) override;
    Instruction* Clone(CloneContext& cloneContext) const override;
    void Write(util::CodeFormatter& formatter) override;
    inline Value* Arg() const { return arg; }
    bool IsFloatingPointInstruction() const override { return arg->GetType()->IsFloatingPointType(); }
    void AddToUses() override;
    void ReplaceValue(Value* use, Value* value) override;
    std::vector<Instruction*> Uses() const override;
private:
    Value* arg;
};

class JmpInstruction : public Instruction
{
public:
    JmpInstruction(const soul::ast::Span& span_, std::int32_t targetLabelId_);
    void Accept(Visitor& visitor) override;
    Instruction* Clone(CloneContext& cloneContext) const override;
    void Write(util::CodeFormatter& formatter) override;
    inline std::int32_t TargetLabelId() const { return targetLabelId; }
    inline BasicBlock* TargetBasicBlock() const { return targetBasicBlock; }
    inline void SetTargetBasicBlock(BasicBlock* targetBasicBlock_) { targetBasicBlock = targetBasicBlock_; }
private:
    std::int32_t targetLabelId;
    BasicBlock* targetBasicBlock;
};

class BranchInstruction : public Instruction
{
public:
    BranchInstruction(const soul::ast::Span& span_, Value* cond_, std::int32_t trueTargetLabelId_, std::int32_t falseTargetLabelId_);
    void Accept(Visitor& visitor) override;
    Instruction* Clone(CloneContext& cloneContext) const override;
    void Write(util::CodeFormatter& formatter) override;
    Value* Cond() const { return cond; }
    inline std::int32_t TrueTargetLabelId() const { return trueTargetLabelId; }
    inline BasicBlock* TrueTargetBasicBlock() const { return trueTargetBasicBlock; }
    inline void SetTrueTargetBasicBlock(BasicBlock* trueTargetBasicBlock_) { trueTargetBasicBlock = trueTargetBasicBlock_; }
    inline std::int32_t FalseTargetLabelId() const { return falseTargetLabelId; }
    inline BasicBlock* FalseTargetBasicBlock() const { return falseTargetBasicBlock; }
    inline void SetFalseTargetBasicBlock(BasicBlock* falseTargetBasicBlock_) { falseTargetBasicBlock = falseTargetBasicBlock_; }
    void AddToUses() override;
    void ReplaceValue(Value* use, Value* value) override;
    std::vector<Instruction*> Uses() const override;
private:
    Value* cond;
    std::int32_t trueTargetLabelId;
    BasicBlock* trueTargetBasicBlock;
    std::int32_t falseTargetLabelId;
    BasicBlock* falseTargetBasicBlock;
};

class ProcedureCallInstruction : public Instruction
{
public:
    ProcedureCallInstruction(const soul::ast::Span& span_, Value* callee_);
    void Accept(Visitor& visitor) override;
    Instruction* Clone(CloneContext& cloneContext) const override;
    void Write(util::CodeFormatter& formatter) override;
    inline Value* Callee() const { return callee; }
    Function* CalleeFn() const;
    inline const std::vector<Value*>& Args() const { return args; }
    void SetArgs(std::vector<Value*>&& args_);
    void AddToUses() override;
    void ReplaceValue(Value* use, Value* value) override;
    std::vector<Instruction*> Uses() const override;
private:
    Value* callee;
    std::vector<Value*> args;
};

class RetInstruction : public Instruction
{
public:
    RetInstruction(const soul::ast::Span& span_, Value* returnValue_);
    void Accept(Visitor& visitor) override;
    Instruction* Clone(CloneContext& cloneContext) const override;
    void Write(util::CodeFormatter& formatter) override;
    inline Value* ReturnValue() const { return returnValue; }
    bool IsFloatingPointInstruction() const override;
    void AddToUses() override;
    void ReplaceValue(Value* use, Value* value) override;
    std::vector<Instruction*> Uses() const override;
private:
    Value* returnValue;
};

struct CaseTarget
{
    CaseTarget();
    inline CaseTarget(Value* caseValue_, std::int32_t targetLabelId_) : caseValue(caseValue_), targetLabelId(targetLabelId_), targetBlock(nullptr) {}
    Value* caseValue;
    std::int32_t targetLabelId;
    BasicBlock* targetBlock;
};

class SwitchInstruction : public Instruction
{
public:
    SwitchInstruction(const soul::ast::Span& span_, Value* cond_, std::int32_t defaultTargetLabelId_);
    void Accept(Visitor& visitor) override;
    Instruction* Clone(CloneContext& cloneContext) const override;
    void Write(util::CodeFormatter& formatter) override;
    inline Value* Cond() const { return cond; }
    inline std::int32_t DefaultTargetLabelId() const { return defaultTargetLabelId; }
    void AddCaseTarget(const CaseTarget& caseTarget);
    inline const std::vector<CaseTarget>& CaseTargets() const { return caseTargets; }
    inline std::vector<CaseTarget>& CaseTargets() { return caseTargets; }
    inline BasicBlock* DefaultTargetBlock() const { return defaultTargetBlock; }
    inline void SetDefaultTargetBlock(BasicBlock* defaultTargetBlock_) { defaultTargetBlock = defaultTargetBlock_; }
    void AddToUses() override;
    void ReplaceValue(Value* use, Value* value) override;
    std::vector<Instruction*> Uses() const override;
private:
    Value* cond;
    std::int32_t defaultTargetLabelId;
    BasicBlock* defaultTargetBlock;
    std::vector<CaseTarget> caseTargets;
};

class ValueInstruction : public Instruction
{
public:
    ValueInstruction(const soul::ast::Span& span_, RegValue* result_, OpCode opCode_);
    ~ValueInstruction();
    inline RegValue* Result() const { return result; }
    inline void ResetResult() { result = nullptr; }
    void WriteResult(util::CodeFormatter& formatter);
    bool IsFloatingPointInstruction() const override { return result->GetType()->IsFloatingPointType(); }
    std::string ToString() const override { return result->ToString(); }
private:
    RegValue* result;
};

class UnaryInstruction : public ValueInstruction
{
public:
    UnaryInstruction(const soul::ast::Span& span_, RegValue* result_, Value* operand_, OpCode opCode_);
    void WriteArg(util::CodeFormatter& formatter);
    inline Value* Operand() const { return operand; }
    inline void SetOperand(Value* operand_) { operand = operand_; }
    void AddToUses() override;
    void ReplaceValue(Value* use, Value* value) override;
    std::vector<Instruction*> Uses() const override;
private:
    Value* operand;
};

class NotInstruction : public UnaryInstruction
{
public:
    NotInstruction(const soul::ast::Span& span_, RegValue* result_, Value* operand_);
    void Accept(Visitor& visitor) override;
    Instruction* Clone(CloneContext& cloneContext) const override;
    void Write(util::CodeFormatter& formatter) override;
};

class NegInstruction : public UnaryInstruction
{
public:
    NegInstruction(const soul::ast::Span& span_, RegValue* result_, Value* operand_);
    bool IsFloatingPointInstruction() const override { return Operand()->GetType()->IsFloatingPointType(); }
    void Accept(Visitor& visitor) override;
    Instruction* Clone(CloneContext& cloneContext) const override;
    void Write(util::CodeFormatter& formatter) override;
};

class SignExtendInstruction : public UnaryInstruction
{
public:
    SignExtendInstruction(const soul::ast::Span& span_, RegValue* result_, Value* operand_);
    void Accept(Visitor& visitor) override;
    Instruction* Clone(CloneContext& cloneContext) const override;
    void Write(util::CodeFormatter& formatter) override;
};

class ZeroExtendInstruction : public UnaryInstruction
{
public:
    ZeroExtendInstruction(const soul::ast::Span& span_, RegValue* result_, Value* operand_);
    void Accept(Visitor& visitor) override;
    Instruction* Clone(CloneContext& cloneContext) const override;
    void Write(util::CodeFormatter& formatter) override;
};

class FloatingPointExtendInstruction : public UnaryInstruction
{
public:
    FloatingPointExtendInstruction(const soul::ast::Span& span_, RegValue* result_, Value* operand_);
    void Accept(Visitor& visitor) override;
    Instruction* Clone(CloneContext& cloneContext) const override;
    void Write(util::CodeFormatter& formatter) override;
};

class TruncateInstruction : public UnaryInstruction
{
public:
    TruncateInstruction(const soul::ast::Span& span_, RegValue* result_, Value* operand_);
    void Accept(Visitor& visitor) override;
    Instruction* Clone(CloneContext& cloneContext) const override;
    void Write(util::CodeFormatter& formatter) override;
};

class BitcastInstruction : public UnaryInstruction
{
public:
    BitcastInstruction(const soul::ast::Span& span_, RegValue* result_, Value* operand_);
    void Accept(Visitor& visitor) override;
    Instruction* Clone(CloneContext& cloneContext) const override;
    void Write(util::CodeFormatter& formatter) override;
};

class IntToFloatInstruction : public UnaryInstruction
{
public:
    IntToFloatInstruction(const soul::ast::Span& span_, RegValue* result_, Value* operand_);
    bool IsFloatingPointInstruction() const override { return true; }
    void Accept(Visitor& visitor) override;
    Instruction* Clone(CloneContext& cloneContext) const override;
    void Write(util::CodeFormatter& formatter) override;
};

class FloatToIntInstruction : public UnaryInstruction
{
public:
    FloatToIntInstruction(const soul::ast::Span& span_, RegValue* result_, Value* operand_);
    bool IsFloatingPointInstruction() const override { return false; }
    void Accept(Visitor& visitor) override;
    Instruction* Clone(CloneContext& cloneContext) const override;
    void Write(util::CodeFormatter& formatter) override;
};

class IntToPtrInstruction : public UnaryInstruction
{
public:
    IntToPtrInstruction(const soul::ast::Span& span_, RegValue* result_, Value* operand_);
    void Accept(Visitor& visitor) override;
    Instruction* Clone(CloneContext& cloneContext) const override;
    void Write(util::CodeFormatter& formatter) override;
};

class PtrToIntInstruction : public UnaryInstruction
{
public:
    PtrToIntInstruction(const soul::ast::Span& span_, RegValue* result_, Value* operand_);
    void Accept(Visitor& visitor) override;
    Instruction* Clone(CloneContext& cloneContext) const override;
    void Write(util::CodeFormatter& formatter) override;
};

class BinaryInstruction : public ValueInstruction
{
public:
    BinaryInstruction(const soul::ast::Span& span_, RegValue* result_, Value* left_, Value* right_, OpCode opCode_);
    inline Value* Left() const { return left; }
    inline Value* Right() const { return right; }
    bool IsFloatingPointInstruction() const override { return Left()->GetType()->IsFloatingPointType(); }
    void AddToUses() override;
    void ReplaceValue(Value* use, Value* value) override;
    void WriteArgs(util::CodeFormatter& formatter);
    std::vector<Instruction*> Uses() const override;
private:
    Value* left;
    Value* right;
};

class AddInstruction : public BinaryInstruction
{
public:
    AddInstruction(const soul::ast::Span& span_, RegValue* result_, Value* left_, Value* right_);
    void Accept(Visitor& visitor) override;
    Instruction* Clone(CloneContext& cloneContext) const override;
    void Write(util::CodeFormatter& formatter) override;
};

class SubInstruction : public BinaryInstruction
{
public:
    SubInstruction(const soul::ast::Span& span_, RegValue* result_, Value* left_, Value* right_);
    void Accept(Visitor& visitor) override;
    Instruction* Clone(CloneContext& cloneContext) const override;
    void Write(util::CodeFormatter& formatter) override;
};

class MulInstruction : public BinaryInstruction
{
public:
    MulInstruction(const soul::ast::Span& span_, RegValue* result_, Value* left_, Value* right_);
    void Accept(Visitor& visitor) override;
    Instruction* Clone(CloneContext& cloneContext) const override;
    void Write(util::CodeFormatter& formatter) override;
};

class DivInstruction : public BinaryInstruction
{
public:
    DivInstruction(const soul::ast::Span& span_, RegValue* result_, Value* left_, Value* right_);
    void Accept(Visitor& visitor) override;
    Instruction* Clone(CloneContext& cloneContext) const override;
    void Write(util::CodeFormatter& formatter) override;
};

class ModInstruction : public BinaryInstruction
{
public:
    ModInstruction(const soul::ast::Span& span_, RegValue* result_, Value* left_, Value* right_);
    void Accept(Visitor& visitor) override;
    Instruction* Clone(CloneContext& cloneContext) const override;
    void Write(util::CodeFormatter& formatter) override;
};

class AndInstruction : public BinaryInstruction
{
public:
    AndInstruction(const soul::ast::Span& span_, RegValue* result_, Value* left_, Value* right_);
    void Accept(Visitor& visitor) override;
    Instruction* Clone(CloneContext& cloneContext) const override;
    void Write(util::CodeFormatter& formatter) override;
};

class OrInstruction : public BinaryInstruction
{
public:
    OrInstruction(const soul::ast::Span& span_, RegValue* result_, Value* left_, Value* right_);
    void Accept(Visitor& visitor) override;
    Instruction* Clone(CloneContext& cloneContext) const override;
    void Write(util::CodeFormatter& formatter) override;
};

class XorInstruction : public BinaryInstruction
{
public:
    XorInstruction(const soul::ast::Span& span_, RegValue* result_, Value* left_, Value* right_);
    void Accept(Visitor& visitor) override;
    Instruction* Clone(CloneContext& cloneContext) const override;
    void Write(util::CodeFormatter& formatter) override;
};

class ShlInstruction : public BinaryInstruction
{
public:
    ShlInstruction(const soul::ast::Span& span_, RegValue* result_, Value* left_, Value* right_);
    void Accept(Visitor& visitor) override;
    Instruction* Clone(CloneContext& cloneContext) const override;
    void Write(util::CodeFormatter& formatter) override;
};

class ShrInstruction : public BinaryInstruction
{
public:
    ShrInstruction(const soul::ast::Span& span_, RegValue* result_, Value* left_, Value* right_);
    void Accept(Visitor& visitor) override;
    Instruction* Clone(CloneContext& cloneContext) const override;
    void Write(util::CodeFormatter& formatter) override;
};

class EqualInstruction : public BinaryInstruction
{
public:
    EqualInstruction(const soul::ast::Span& span_, RegValue* result_, Value* left_, Value* right_);
    void Accept(Visitor& visitor) override;
    Instruction* Clone(CloneContext& cloneContext) const override;
    bool IsFloatingPointInstruction() const override { return false; }
    void Write(util::CodeFormatter& formatter) override;
};

class LessInstruction : public BinaryInstruction
{
public:
    LessInstruction(const soul::ast::Span& span_, RegValue* result_, Value* left_, Value* right_);
    void Accept(Visitor& visitor) override;
    Instruction* Clone(CloneContext& cloneContext) const override;
    bool IsFloatingPointInstruction() const override { return false; }
    void Write(util::CodeFormatter& formatter) override;
};

class ParamInstruction : public ValueInstruction
{
public:
    ParamInstruction(const soul::ast::Span& span_, RegValue* result_);
    void Accept(Visitor& visitor) override;
    Instruction* Clone(CloneContext& cloneContext) const override;
    void Write(util::CodeFormatter& formatter) override;
};

class LocalInstruction : public ValueInstruction
{
public:
    LocalInstruction(const soul::ast::Span& span_, RegValue* result_, Type* localType_);
    void Accept(Visitor& visitor) override;
    Instruction* Clone(CloneContext& cloneContext) const override;
    void Write(util::CodeFormatter& formatter) override;
    inline Type* LocalType() const { return localType; }
private:
    Type* localType;
};

class LoadInstruction : public ValueInstruction
{
public:
    LoadInstruction(const soul::ast::Span& span_, RegValue* result_, Value* ptr_);
    void Accept(Visitor& visitor) override;
    Instruction* Clone(CloneContext& cloneContext) const override;
    void Write(util::CodeFormatter& formatter) override;
    inline Value* Ptr() const { return ptr; }
    void AddToUses() override;
    void ReplaceValue(Value* use, Value* value) override;
    std::vector<Instruction*> Uses() const override;
private:
    Value* ptr;
};

enum class ElemAddrKind
{
    none, array, structure
};

class ElemAddrInstruction : public ValueInstruction
{
public:
    ElemAddrInstruction(const soul::ast::Span& span_, RegValue* result_, Value* ptr_, Value* indexValue_);
    void Accept(Visitor& visitor) override;
    Instruction* Clone(CloneContext& cloneContext) const override;
    void Write(util::CodeFormatter& formatter) override;
    inline Value* Ptr() const { return ptr; }
    inline Value* IndexValue() const { return indexValue; }
    ElemAddrKind GetElemAddrKind(Context* context) const;
    void AddToUses() override;
    void ReplaceValue(Value* use, Value* value) override;
    std::vector<Instruction*> Uses() const override;
private:
    Value* ptr;
    Value* indexValue;
};

class PtrOffsetInstruction : public ValueInstruction
{
public:
    PtrOffsetInstruction(const soul::ast::Span& span_, RegValue* result_, Value* ptr_, Value* offset_);
    void Accept(Visitor& visitor) override;
    Instruction* Clone(CloneContext& cloneContext) const override;
    void Write(util::CodeFormatter& formatter) override;
    inline Value* Ptr() const { return ptr; }
    inline Value* Offset() const { return offset; }
    void AddToUses() override;
    void ReplaceValue(Value* use, Value* value) override;
    std::vector<Instruction*> Uses() const override;
private:
    Value* ptr;
    Value* offset;
};

class PtrDiffInstruction : public ValueInstruction
{
public:
    PtrDiffInstruction(const soul::ast::Span& span_, RegValue* result_, Value* leftPtr_, Value* rightPtr_);
    void Accept(Visitor& visitor) override;
    Instruction* Clone(CloneContext& cloneContext) const override;
    void Write(util::CodeFormatter& formatter) override;
    inline Value* LeftPtr() const { return leftPtr; }
    inline Value* RightPtr() const { return rightPtr; }
    void AddToUses() override;
    void ReplaceValue(Value* use, Value* value) override;
    std::vector<Instruction*> Uses() const override;
private:
    Value* leftPtr;
    Value* rightPtr;
};

class FunctionCallInstruction : public ValueInstruction
{
public:
    FunctionCallInstruction(const soul::ast::Span& span_, RegValue* result_, Value* callee_);
    void Accept(Visitor& visitor) override;
    Instruction* Clone(CloneContext& cloneContext) const override;
    void Write(util::CodeFormatter& formatter) override;
    inline Value* Callee() const { return callee; }
    Function* CalleeFn() const;
    inline const std::vector<Value*>& Args() const { return args; }
    void SetArgs(std::vector<Value*>&& args_);
    void AddToUses() override;
    void ReplaceValue(Value* use, Value* value) override;
    std::vector<Instruction*> Uses() const override;
private:
    Value* callee;
    std::vector<Value*> args;
};

struct BlockValue
{
    inline BlockValue(Value* value_, std::int32_t blockId_) : value(value_), blockId(blockId_), block(nullptr) {}
    BlockValue(Value* value_, BasicBlock* block_);
    Value* value;
    std::int32_t blockId;
    BasicBlock* block;
};

class NoOperationInstruction : public Instruction
{
public:
    NoOperationInstruction(const soul::ast::Span& span_);
    void Accept(Visitor& visitor) override;
    Instruction* Clone(CloneContext& cloneContext) const override;
    void Write(util::CodeFormatter& formatter) override;
};

const std::int32_t entryBlockId = -1;
const std::int32_t exitBlockId = -2;

class BasicBlock : public util::Component
{
public:
    BasicBlock(const soul::ast::Span& span_, std::int32_t id_);
    void Check();
    void Accept(Visitor& visitor);
    BasicBlock* Clone(CloneContext& cloneContext) const;
    void CloneInstructions(CloneContext& cloneContext, BasicBlock* to);
    void VisitInstructions(Visitor& visitor);
    inline const soul::ast::Span& Span() const { return span; }
    std::string Name() const;
    inline std::int32_t Id() const { return id; }
    inline void SetId(std::int32_t id_) { id = id_; }
    Function* Parent() const;
    inline BasicBlock* Next() { return static_cast<BasicBlock*>(NextSibling()); }
    inline BasicBlock* Prev() { return static_cast<BasicBlock*>(PrevSibling()); }
    inline Instruction* FirstInstruction() { return static_cast<Instruction*>(instructions.FirstChild()); }
    inline Instruction* LastInstruction() { return static_cast<Instruction*>(instructions.LastChild()); }
    inline util::Container* Instructions() { return &instructions; }
    Instruction* Leader() const;
    bool IsLast() const;
    bool ContainsOnlyNops();
    void AddInstruction(Instruction* instruction);
    void AddInstruction(Instruction* instruction, bool mapInstruction);
    std::unique_ptr<Instruction> RemoveInstruction(Instruction* instruction);
    void InsertInstructionAfter(Instruction* instruction, Instruction* after);
    void InsertFront(Instruction* instruction);
    BasicBlock* SplitAfter(Instruction* instruction);
    inline bool IsEmpty() const { return instructions.IsEmpty(); }
    inline bool IsEntryBlock() const { return id == entryBlockId; }
    inline bool IsExitBlock() const { return id == exitBlockId; }
    inline const std::vector<BasicBlock*>& Successors() const { return successors; }
    void AddSuccessor(BasicBlock* successor);
    bool RemoveSuccessor(BasicBlock* successor);
    inline const std::vector<BasicBlock*>& Predecessors() const { return predecessors; }
    void AddPredecessor(BasicBlock* predecessor);
    bool RemovePredecessor(BasicBlock* predecessor);
    void ClearSuccessorsAndPredecessors();
    int IndexOf(Instruction* x);
    void Write(util::CodeFormatter& formatter);
private:
    soul::ast::Span span;
    std::int32_t id;
    util::Container instructions;
    std::vector<BasicBlock*> successors;
    std::vector<BasicBlock*> predecessors;
};

enum class FunctionFlags : int
{
    none = 0, defined = 1 << 0, inline_ = 1 << 1, linkOnce = 1 << 2
};

inline FunctionFlags operator|(FunctionFlags left, FunctionFlags right)
{
    return FunctionFlags(static_cast<int>(left) | static_cast<int>(right));
}

inline FunctionFlags operator&(FunctionFlags left, FunctionFlags right)
{
    return FunctionFlags(static_cast<int>(left) & static_cast<int>(right));
}

inline FunctionFlags operator~(FunctionFlags flags)
{
    return FunctionFlags(~static_cast<int>(flags));
}

class Function : public Value, public util::Component
{
public:
    Function(const soul::ast::Span& span_, FunctionType* functionType_, const std::string& name_, bool once_, bool definition_, bool createEntry, 
        MetadataRef* metadataRef_, Context* context);
    Function(const Function&) = delete;
    Function& operator=(const Function&) = delete;
    void CreateEntry(Context* context);
    void Check();
    inline bool GetFlag(FunctionFlags flag) const { return (flags & flag) != FunctionFlags::none; }
    inline void SetFlag(FunctionFlags flag) { flags = flags | flag; }
    inline void ResetFlag(FunctionFlags flag) { flags = flags & ~flag; }
    inline bool IsDefined() const { return GetFlag(FunctionFlags::defined); }
    inline bool IsExternal() const { return !IsDefined(); }
    inline void SetDefined() { SetFlag(FunctionFlags::defined); }
    inline bool IsInline() const { return GetFlag(FunctionFlags::inline_); }
    inline void SetInline() { SetFlag(FunctionFlags::inline_); }
    inline bool IsLinkOnce() const { return GetFlag(FunctionFlags::linkOnce); }
    inline void SetLinkOnce() { SetFlag(FunctionFlags::linkOnce); }
    inline int Arity() const { return type->Arity(); }
    void Accept(Visitor& visitor);
    Function* Clone() const;
    void VisitBasicBlocks(Visitor& visitor);
    Code* Parent() const;
    inline Function* Next() { return static_cast<Function*>(NextSibling()); }
    inline Function* Prev() { return static_cast<Function*>(PrevSibling()); }
    inline bool IsEmpty() const { return basicBlocks.IsEmpty(); }
    BasicBlock* GetBasicBlock(std::int32_t id) const;
    BasicBlock* CreateBasicBlock();
    BasicBlock* AddBasicBlock(const soul::ast::Span& span, std::int32_t id, Context* context);
    void AddBasicBlock(BasicBlock* basicBlock);
    inline util::Container* BasicBlocks() { return &basicBlocks; }
    void InsertBasicBlockBefore(BasicBlock* basicBlockToInsert, BasicBlock* before);
    void InsertBasicBlockAfter(BasicBlock* basicBlockToInsert, BasicBlock* after);
    std::unique_ptr<BasicBlock> RemoveBasicBlock(BasicBlock* block);
    inline BasicBlock* FirstBasicBlock() { return static_cast<BasicBlock*>(basicBlocks.FirstChild()); }
    inline BasicBlock* LastBasicBlock() { return static_cast<BasicBlock*>(basicBlocks.LastChild()); }
    const soul::ast::Span& Span() const { return span; }
    inline FunctionType* GetType() const { return type; }
    inline const std::string& Name() const { return name; }
    std::string ToString() const override { return "@" + name; }
    RegValue* GetRegValue(std::int32_t reg) const;
    RegValue* GetRegRef(const soul::ast::Span& span, Type* type, std::int32_t reg, Context* context) const;
    RegValue* MakeRegValue(const soul::ast::Span& span, Type* type, std::int32_t reg, Context* context);
    RegValue* MakeNextRegValue(const soul::ast::Span& span, Type* type, Context* context);
    void MapRegValue(RegValue* regValue);
    void RemoveRegValue(std::int32_t reg);
    Instruction* GetInstruction(std::int32_t reg) const;
    void MapInstruction(std::int32_t reg, Instruction* inst, Context* context);
    int NumBasicBlocks() const;
    inline const std::vector<BasicBlock*>& RetBlocks() const { return retBlocks; }
    void AddRetBlock(BasicBlock* retBlock);
    void AddEntryAndExitBlocks();
    void RemoveEntryAndExitBlocks();
    inline void SetNextRegNumber(std::int32_t nextRegNumber_) { nextRegNumber = nextRegNumber_; }
    inline std::int32_t NextRegNumber() const { return nextRegNumber; }
    inline std::int32_t GetNextRegNumber() { return nextRegNumber++; }
    inline std::int32_t GetNextBasicBlockNumber() { return nextBBNumber++; }
    Value* GetParam(int index) const;
    void SetNumbers();
    void MoveRegValues(Function* toFunction);
    inline void SetMdId(int mdId_) { mdId = mdId_; }
    inline int MdId() const { return mdId; }
    inline void SetMetadataRef(MetadataRef* metadataRef_) { metadataRef = metadataRef_; }
    inline MetadataRef* GetMetadataRef() const { return metadataRef; }
    void SetComment(const std::string& comment_);
    inline const std::string& Comment() const { return comment; }
    std::string ResolveFullName() const;
    void Write(util::CodeFormatter& formatter);
private:
    FunctionFlags flags;
    soul::ast::Span span;
    FunctionType* type;
    std::unique_ptr<BasicBlock> entryBlock;
    std::string name;
    std::vector<Instruction*> params;
    MetadataRef* metadataRef;
    std::string comment;
    util::Container basicBlocks;
    std::map<std::int32_t, BasicBlock*> basicBlockMap;
    std::map<std::int32_t, RegValue*> regValueMap;
    std::map<std::int32_t, Instruction*> instructionMap;
    std::vector<std::unique_ptr<RegValue>> regValues;
    std::vector<BasicBlock*> retBlocks;
    std::int32_t nextRegNumber;
    std::int32_t nextBBNumber;
    int mdId;
};

class Code : public util::Component
{
public:
    Code();
    Code(const Code&) = delete;
    Code& operator=(const Code&) = delete;
    inline Context* GetContext() const { return context; }
    inline void SetContext(Context* context_) { context = context_; }
    inline util::Container* Functions() const { return const_cast<util::Container*>(&functions); }
    inline Function* CurrentFunction() const { return currentFunction; }
    void SetCurrentFunction(Function* function);
    Function* GetOrInsertFunction(const std::string& functionId, FunctionType* functionType);
    Function* GetFunction(const std::string& functionId) const;
    Function* AddFunctionDefinition(const soul::ast::Span& span, FunctionType* functionType, const std::string& functionId, bool inline_, bool linkOnce, bool createEntry,
        MetadataRef* metadataRef);
    Function* AddFunctionDeclaration(const soul::ast::Span& span, FunctionType* functionType, const std::string& functionId);
    inline Function* FirstFunction() { return static_cast<Function*>(functions.FirstChild()); }
    inline Function* LastFunction() { return static_cast<Function*>(functions.LastChild()); }
    void VisitFunctions(Visitor& visitor);
    inline int TotalFunctions() const { return totalFunctions; }
private:
    Context* context;
    Function* currentFunction;
    util::Container functions;
    std::map<std::string, Function*> functionMap;
    int totalFunctions;
};

} // otava::intermediate
