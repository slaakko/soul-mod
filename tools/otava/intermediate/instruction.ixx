// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.intermediate.instruction;

import std.core;
import soul.ast.source.pos;
import util.code.formatter;
import util.component;
import otava.intermediate.data;
import otava.intermediate.value;

export namespace otava::intermediate::instruction {}

export namespace otava::intermediate {

class Instruction;
class MetadataRef;
class BasicBlock;
class Context;

using SourcePos = soul::ast::SourcePos;

class RegValue : public Value
{
public:
    RegValue(const SourcePos& sourcePos_, Type* type_);
    int32_t Reg() const { return reg; }
    void SetReg(int32_t reg_) { reg = reg_; }
    void SetInst(Instruction* inst_) { inst = inst_; }
    Instruction* Inst() const { return inst; }
private:
    int32_t reg;
    Instruction* inst;
};

enum class OpCode : int
{
    store, arg, jmp, branch, procedure_call, ret, switch_,
    not_, neg, signextend, zeroextend, truncate, bitcast, inttofloat, floattoint, inttoptr, ptrtoint,
    add, sub, mul, div_, mod, and_, or_, xor_, shl, shr, equal, less,
    param, local, load, elemaddr, ptroffset, ptrdiff, function_call, trap, phi,
    nop
};

class Use
{
public:
    Use(Instruction* user_, Value*& value_) : user(user_), value(value_) {}
    Instruction* User() const { return user; }
    Value* Get() const { return value; }
    void Set(Value* value_);
private:
    Instruction* user;
    Value*& value;
};

class Instruction : public Value, public util::Component
{
public:
    Instruction(const SourcePos& sourcePos_, Type* type_, OpCode opCode_);
    virtual void Write(util::CodeFormatter& formatter) = 0;
    virtual void SetRegNumber(Function& function);
    void WriteMetadataRef(util::CodeFormatter& formatter);
    std::string Name() const;
    virtual void Accept(Visitor& visitor) = 0;
    Instruction* Next() { return static_cast<Instruction*>(NextSibling()); }
    Instruction* Prev() { return static_cast<Instruction*>(PrevSibling()); }
    BasicBlock* Parent() const;
    OpCode GetOpCode() const { return opCode; }
    void SetMetadataRef(MetadataRef* metadataRef_) { metadataRef = metadataRef_; }
    MetadataRef* GetMetadataRef() const { return metadataRef; }
    bool IsLeader() const;
    bool IsTerminator() const;
    bool IsValueInstruction() const;
    bool IsUnaryInstruction() const;
    bool IsBinaryInstruction() const;
    bool IsSwitchInstruction() const { return opCode == OpCode::switch_; }
    bool IsParamInstruction() const { return opCode == OpCode::param; }
    bool IsLocalInstruction() const { return opCode == OpCode::local; }
    bool IsArgInstruction() const { return opCode == OpCode::arg; }
    bool IsProcedureCallInstruction() const { return opCode == OpCode::procedure_call; }
    bool IsFunctionCallInstruction() const { return opCode == OpCode::function_call; }
    bool IsLoadInstruction() const { return opCode == OpCode::load; }
    bool IsStoreInstruction() const { return opCode == OpCode::store; }
    bool IsElemAddrInstruction() const { return opCode == OpCode::elemaddr; }
    bool IsPhiInstruction() const { return opCode == OpCode::phi; }
    bool IsNoOperation() const { return opCode == OpCode::nop; }
    bool RequiresLocalRegister() const;
    std::vector<BasicBlock*> Successors() const;
    const std::vector<Instruction*>& Users() const { return users; }
    void AddUser(Instruction* user);
    void RemoveUser(Instruction* user);
    std::vector<Use> Uses();
    std::unique_ptr<Instruction> Remove();
    void ReplaceUsesWith(Value* value);
    int Index() const { return index; }
    void SetIndex(int index_) { index = index_; }
private:
    OpCode opCode;
    MetadataRef* metadataRef;
    std::vector<Instruction*> users;
    int index;
};

class StoreInstruction : public Instruction
{
public:
    StoreInstruction(const SourcePos& sourcePos_, Value* value_, Value* ptr_);
    void Write(util::CodeFormatter& formatter) override;
    void Accept(Visitor& visitor) override;
    Value* GetValue() const { return value; }
    Value* GetPtr() const { return ptr; }
    void AddUse();
    void AddToUses(std::vector<Use>& uses);
private:
    Value* value;
    Value* ptr;
};

class ArgInstruction : public Instruction
{
public:
    ArgInstruction(const SourcePos& sourcePos_, Value* arg_);
    void Write(util::CodeFormatter& formatter) override;
    void Accept(Visitor& visitor) override;
    Value* Arg() const { return arg; }
    void AddUse();
    void AddToUses(std::vector<Use>& uses);
private:
    Value* arg;
};

class JmpInstruction : public Instruction
{
public:
    JmpInstruction(const SourcePos& sourcePos_, int32_t targetLabelId_);
    void Write(util::CodeFormatter& formatter) override;
    void Accept(Visitor& visitor) override;
    int32_t TargetLabelId() const { return targetLabelId; }
    BasicBlock* TargetBasicBlock() const { return targetBasicBlock; }
    void SetTargetBasicBlock(BasicBlock* targetBasicBlock_) { targetBasicBlock = targetBasicBlock_; }
private:
    int32_t targetLabelId;
    BasicBlock* targetBasicBlock;
};

class BranchInstruction : public Instruction
{
public:
    BranchInstruction(const SourcePos& sourcePos_, Value* cond_, int32_t trueTargetLabelId_, int32_t falseTargetLabelId_);
    void Write(util::CodeFormatter& formatter) override;
    void Accept(Visitor& visitor) override;
    Value* Cond() const { return cond; }
    int32_t TrueTargetLabelId() const { return trueTargetLabelId; }
    BasicBlock* TrueTargetBasicBlock() const { return trueTargetBasicBlock; }
    void SetTrueTargetBasicBlock(BasicBlock* trueTargetBasicBlock_) { trueTargetBasicBlock = trueTargetBasicBlock_; }
    int32_t FalseTargetLabelId() const { return falseTargetLabelId; }
    BasicBlock* FalseTargetBasicBlock() const { return falseTargetBasicBlock; }
    void SetFalseTargetBasicBlock(BasicBlock* falseTargetBasicBlock_) { falseTargetBasicBlock = falseTargetBasicBlock_; }
    void AddUse();
    void AddToUses(std::vector<Use>& uses);
private:
    Value* cond;
    int32_t trueTargetLabelId;
    BasicBlock* trueTargetBasicBlock;
    int32_t falseTargetLabelId;
    BasicBlock* falseTargetBasicBlock;
};

class ProcedureCallInstruction : public Instruction
{
public:
    ProcedureCallInstruction(const SourcePos& sourcePos_, Value* callee_);
    void Write(util::CodeFormatter& formatter) override;
    void Accept(Visitor& visitor) override;
    Value* Callee() const { return callee; }
    const std::vector<Value*>& Args() const { return args; }
    void SetArgs(std::vector<Value*>&& args_);
    void AddUse();
    void AddToUses(std::vector<Use>& uses);
private:
    Value* callee;
    std::vector<Value*> args;
};

class RetInstruction : public Instruction
{
public:
    RetInstruction(const SourcePos& sourcePos_, Value* returnValue_);
    void Write(util::CodeFormatter& formatter) override;
    void Accept(Visitor& visitor) override;
    Value* ReturnValue() const { return returnValue; }
    void AddUse();
    void AddToUses(std::vector<Use>& uses);
private:
    Value* returnValue;
};

struct CaseTarget
{
    CaseTarget(Value* caseValue_, int32_t targetBlockId_) : caseValue(caseValue_), targetBlockId(targetBlockId_), targetBlock(nullptr) {}
    Value* caseValue;
    int32_t targetBlockId;
    BasicBlock* targetBlock;
};

class SwitchInstruction : public Instruction
{
public:
    SwitchInstruction(const SourcePos& sourcePos_, Value* cond_, int32_t defaultTargetId_);
    void Write(util::CodeFormatter& formatter) override;
    void Accept(Visitor& visitor) override;
    Value* Cond() const { return cond; }
    int32_t DefaultTargetId() const { return defaultTargetId; }
    void SetDefaultTargetBlock(BasicBlock* defaultTargetBlock_);
    void AddCaseTarget(const CaseTarget& caseTarget);
    const std::vector<CaseTarget>& CaseTargets() const { return caseTargets; }
    std::vector<CaseTarget>& CaseTargets() { return caseTargets; }
    BasicBlock* DefaultTargetBlock() const { return defaultTargetBlock; }
    void AddUse();
    void AddToUses(std::vector<Use>& uses);
private:
    Value* cond;
    int32_t defaultTargetId;
    BasicBlock* defaultTargetBlock;
    std::vector<CaseTarget> caseTargets;
};

class ValueInstruction : public Instruction
{
public:
    ValueInstruction(const SourcePos& sourcePos_, RegValue* result_, OpCode opCode_);
    RegValue* Result() const { return result; }
    void WriteResult(util::CodeFormatter& formatter);
    std::string ToString() const override { return "$" + std::to_string(result->Reg()); }
    void SetRegNumber(Function& function) override;
private:
    RegValue* result;
};

class UnaryInstruction : public ValueInstruction
{
public:
    UnaryInstruction(const SourcePos& sourcePos_, RegValue* result_, Value* operand_, OpCode opCode_);
    void WriteOperand(util::CodeFormatter& formatter);
    Value* Operand() const { return operand; }
    void SetOperand(Value* operand_) { operand = operand_; }
    void AddUse();
    void AddOperandToUses(std::vector<Use>& uses);
private:
    Value* operand;
};

class NotInstruction : public UnaryInstruction
{
public:
    NotInstruction(const SourcePos& sourcePos_, RegValue* result_, Value* operand_);
    void Write(util::CodeFormatter& formatter) override;
    void Accept(Visitor& visitor) override;
};

class NegInstruction : public UnaryInstruction
{
public:
    NegInstruction(const SourcePos& sourcePos_, RegValue* result_, Value* operand_);
    void Write(util::CodeFormatter& formatter) override;
    void Accept(Visitor& visitor) override;
};

class SignExtendInstruction : public UnaryInstruction
{
public:
    SignExtendInstruction(const SourcePos& sourcePos_, RegValue* result_, Value* operand_);
    void Write(util::CodeFormatter& formatter) override;
    void Accept(Visitor& visitor) override;
};

class ZeroExtendInstruction : public UnaryInstruction
{
public:
    ZeroExtendInstruction(const SourcePos& sourcePos_, RegValue* result_, Value* operand_);
    void Write(util::CodeFormatter& formatter) override;
    void Accept(Visitor& visitor) override;
};

class TruncateInstruction : public UnaryInstruction
{
public:
    TruncateInstruction(const SourcePos& sourcePos_, RegValue* result_, Value* operand_);
    void Write(util::CodeFormatter& formatter) override;
    void Accept(Visitor& visitor) override;
};

class BitcastInstruction : public UnaryInstruction
{
public:
    BitcastInstruction(const SourcePos& sourcePos_, RegValue* result_, Value* operand_);
    void Write(util::CodeFormatter& formatter) override;
    void Accept(Visitor& visitor) override;
};

class IntToFloatInstruction : public UnaryInstruction
{
public:
    IntToFloatInstruction(const SourcePos& sourcePos_, RegValue* result_, Value* operand_);
    void Write(util::CodeFormatter& formatter) override;
    void Accept(Visitor& visitor) override;
};

class FloatToIntInstruction : public UnaryInstruction
{
public:
    FloatToIntInstruction(const SourcePos& sourcePos_, RegValue* result_, Value* operand_);
    void Write(util::CodeFormatter& formatter) override;
    void Accept(Visitor& visitor) override;
};

class IntToPtrInstruction : public UnaryInstruction
{
public:
    IntToPtrInstruction(const SourcePos& sourcePos_, RegValue* result_, Value* operand_);
    void Write(util::CodeFormatter& formatter) override;
    void Accept(Visitor& visitor) override;
};

class PtrToIntInstruction : public UnaryInstruction
{
public:
    PtrToIntInstruction(const SourcePos& sourcePos_, RegValue* result_, Value* operand_);
    void Write(util::CodeFormatter& formatter) override;
    void Accept(Visitor& visitor) override;
};

class BinaryInstruction : public ValueInstruction
{
public:
    BinaryInstruction(const SourcePos& sourcePos_, RegValue* result_, Value* left_, Value* right_, OpCode opCode_);
    void WriteOperands(util::CodeFormatter& formatter);
    Value* Left() const { return left; }
    Value* Right() const { return right; }
    void AddUse();
    void AddOperandsToUses(std::vector<Use>& uses);
private:
    Value* left;
    Value* right;
};

class AddInstruction : public BinaryInstruction
{
public:
    AddInstruction(const SourcePos& sourcePos_, RegValue* result_, Value* left_, Value* right_);
    void Write(util::CodeFormatter& formatter) override;
    void Accept(Visitor& visitor) override;
};

class SubInstruction : public BinaryInstruction
{
public:
    SubInstruction(const SourcePos& sourcePos_, RegValue* result_, Value* left_, Value* right_);
    void Write(util::CodeFormatter& formatter) override;
    void Accept(Visitor& visitor) override;
};

class MulInstruction : public BinaryInstruction
{
public:
    MulInstruction(const SourcePos& sourcePos_, RegValue* result_, Value* left_, Value* right_);
    void Write(util::CodeFormatter& formatter) override;
    void Accept(Visitor& visitor) override;
};

class DivInstruction : public BinaryInstruction
{
public:
    DivInstruction(const SourcePos& sourcePos_, RegValue* result_, Value* left_, Value* right_);
    void Write(util::CodeFormatter& formatter) override;
    void Accept(Visitor& visitor) override;
};

class ModInstruction : public BinaryInstruction
{
public:
    ModInstruction(const SourcePos& sourcePos_, RegValue* result_, Value* left_, Value* right_);
    void Write(util::CodeFormatter& formatter) override;
    void Accept(Visitor& visitor) override;
};

class AndInstruction : public BinaryInstruction
{
public:
    AndInstruction(const SourcePos& sourcePos_, RegValue* result_, Value* left_, Value* right_);
    void Write(util::CodeFormatter& formatter) override;
    void Accept(Visitor& visitor) override;
};

class OrInstruction : public BinaryInstruction
{
public:
    OrInstruction(const SourcePos& sourcePos_, RegValue* result_, Value* left_, Value* right_);
    void Write(util::CodeFormatter& formatter) override;
    void Accept(Visitor& visitor) override;
};

class XorInstruction : public BinaryInstruction
{
public:
    XorInstruction(const SourcePos& sourcePos_, RegValue* result_, Value* left_, Value* right_);
    void Write(util::CodeFormatter& formatter) override;
    void Accept(Visitor& visitor) override;
};

class ShlInstruction : public BinaryInstruction
{
public:
    ShlInstruction(const SourcePos& sourcePos_, RegValue* result_, Value* left_, Value* right_);
    void Write(util::CodeFormatter& formatter) override;
    void Accept(Visitor& visitor) override;
};

class ShrInstruction : public BinaryInstruction
{
public:
    ShrInstruction(const SourcePos& sourcePos_, RegValue* result_, Value* left_, Value* right_);
    void Write(util::CodeFormatter& formatter) override;
    void Accept(Visitor& visitor) override;
};

class EqualInstruction : public BinaryInstruction
{
public:
    EqualInstruction(const SourcePos& sourcePos_, RegValue* result_, Value* left_, Value* right_);
    void Write(util::CodeFormatter& formatter) override;
    void Accept(Visitor& visitor) override;
};

class LessInstruction : public BinaryInstruction
{
public:
    LessInstruction(const SourcePos& sourcePos_, RegValue* result_, Value* left_, Value* right_);
    void Write(util::CodeFormatter& formatter) override;
    void Accept(Visitor& visitor) override;
};

class ParamInstruction : public ValueInstruction
{
public:
    ParamInstruction(const SourcePos& sourcePos_, RegValue* result_);
    void Write(util::CodeFormatter& formatter) override;
    void Accept(Visitor& visitor) override;
};

class LocalInstruction : public ValueInstruction
{
public:
    LocalInstruction(const SourcePos& sourcePos_, RegValue* result_, Type* localType_);
    void Write(util::CodeFormatter& formatter) override;
    void Accept(Visitor& visitor) override;
    Type* LocalType() const { return localType; }
private:
    Type* localType;
};

class LoadInstruction : public ValueInstruction
{
public:
    LoadInstruction(const SourcePos& sourcePos_, RegValue* result_, Value* ptr_);
    void Write(util::CodeFormatter& formatter) override;
    void Accept(Visitor& visitor) override;
    Value* Ptr() const { return ptr; }
    void AddUse();
    void AddToUses(std::vector<Use>& uses);
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
    ElemAddrInstruction(const SourcePos& sourcePos_, RegValue* result_, Value* ptr_, Value* index_);
    void Write(util::CodeFormatter& formatter) override;
    void Accept(Visitor& visitor) override;
    Value* Ptr() const { return ptr; }
    Value* Index() const { return index; }
    void AddUse();
    void AddToUses(std::vector<Use>& uses);
    ElemAddrKind GetElemAddrKind(Context* context) const;
private:
    Value* ptr;
    Value* index;
};

class PtrOffsetInstruction : public ValueInstruction
{
public:
    PtrOffsetInstruction(const SourcePos& sourcePos_, RegValue* result_, Value* ptr_, Value* offset_);
    void Write(util::CodeFormatter& formatter) override;
    void Accept(Visitor& visitor) override;
    Value* Ptr() const { return ptr; }
    Value* Offset() const { return offset; }
    void AddUse();
    void AddToUses(std::vector<Use>& uses);
private:
    Value* ptr;
    Value* offset;
};

class PtrDiffInstruction : public ValueInstruction
{
public:
    PtrDiffInstruction(const SourcePos& sourcePos_, RegValue* result_, Value* leftPtr_, Value* rightPtr_);
    void Write(util::CodeFormatter& formatter) override;
    void Accept(Visitor& visitor) override;
    Value* LeftPtr() const { return leftPtr; }
    Value* RightPtr() const { return rightPtr; }
    void AddUse();
    void AddToUses(std::vector<Use>& uses);
private:
    Value* leftPtr;
    Value* rightPtr;
};

class FunctionCallInstruction : public ValueInstruction
{
public:
    FunctionCallInstruction(const SourcePos& sourcePos_, RegValue* result_, Value* callee_);
    void Write(util::CodeFormatter& formatter) override;
    void Accept(Visitor& visitor) override;
    Value* Callee() const { return callee; }
    const std::vector<Value*>& Args() const { return args; }
    void SetArgs(std::vector<Value*>&& args_);
    void AddUse();
    void AddToUses(std::vector<Use>& uses);
private:
    Value* callee;
    std::vector<Value*> args;
};

class NopInstruction : public Instruction
{
public:
    NopInstruction(const SourcePos& sourcePos_);
};

class TrapInstruction : public ValueInstruction
{
public:
    TrapInstruction(const SourcePos& sourcePos_, RegValue* result_, Value* op1_, Value* op2_, Value* op3_);
    void Write(util::CodeFormatter& formatter) override;
    void Accept(Visitor& visitor) override;
    Value* Op1() const { return op1; }
    Value* Op2() const { return op2; }
    Value* Op3() const { return op3; }
    const std::vector<Value*>& Args() const { return args; }
    void SetArgs(std::vector<Value*>&& args_);
    void AddUse();
    void AddToUses(std::vector<Use>& uses);
private:
    Value* op1;
    Value* op2;
    Value* op3;
    std::vector<Value*> args;
};

struct BlockValue
{
    BlockValue(Value* value_, int32_t blockId_) : value(value_), blockId(blockId_), block(nullptr) {}
    BlockValue(Value* value_, BasicBlock* block_);
    Value* value;
    int32_t blockId;
    BasicBlock* block;
};

class PhiInstruction : public ValueInstruction
{
public:
    PhiInstruction(const SourcePos& sourcePos_, RegValue* result_);
    void Write(util::CodeFormatter& formatter) override;
    void Accept(Visitor& visitor) override;
    void AddBlockValue(const BlockValue& blockValue);
    const std::vector<BlockValue>& BlockValues() const { return blockValues; }
    std::vector<BlockValue>& BlockValues() { return blockValues; }
    void AddUse();
    void AddToUses(std::vector<Use>& uses);
private:
    std::vector<BlockValue> blockValues;
};

class NoOperationInstruction : public Instruction
{
public:
    NoOperationInstruction(const SourcePos& sourcePos_);
    void Write(util::CodeFormatter& formatter) override;
    void Accept(Visitor& visitor) override;
};

} // namespace otava::intermediate
