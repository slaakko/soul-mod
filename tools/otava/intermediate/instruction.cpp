// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.intermediate.instruction;

import otava.intermediate.basic.block;
import otava.intermediate.error;
import otava.intermediate.function;
import otava.intermediate.metadata;
import otava.intermediate.type;
import otava.intermediate.util;
import otava.intermediate.visitor;
import util.text.util;

namespace otava::intermediate {

const char* opCodeStr[] =
{
    "store", "arg", "jmp", "branch", "call", "ret", "switch",
    "not", "neg", "signextend", "zeroextend", "truncate", "bitcast", "inttofloat", "floattoint", "inttoptr", "ptrtoint",
    "add", "sub", "mul", "div", "mod", "and", "or", "xor", "shl", "shr", "equal", "less",
    "param", "local", "load", "elemaddr", "ptroffset", "ptrdiff", "call", "trap", "phi",
    "nop"
};

RegValue::RegValue(const SourcePos& sourcePos_, Type* type_) : Value(sourcePos_, ValueKind::regValue, type_), reg(-1), inst(nullptr)
{
}

void Use::Set(Value* value_)
{
    if (value == value_)
    {
        return;
    }
    if (value->IsRegValue())
    {
        RegValue* regValue = static_cast<RegValue*>(value);
        Instruction* inst = regValue->Inst();
        if (inst)
        {
            inst->RemoveUser(user);
        }
    }
    value = value_;
    if (value->IsRegValue())
    {
        RegValue* regValue = static_cast<RegValue*>(value);
        Instruction* inst = regValue->Inst();
        if (inst)
        {
            inst->AddUser(user);
        }
    }
}

Instruction::Instruction(const SourcePos& sourcePos_, Type* type_, OpCode opCode_) : Value(sourcePos_, ValueKind::instruction, type_), opCode(opCode_), metadataRef(nullptr), index(-1)
{
}

void Instruction::SetRegNumber(Function& function)
{
}

void Instruction::WriteMetadataRef(util::CodeFormatter& formatter)
{
    if (metadataRef)
    {
        formatter.Write(" ");
        metadataRef->Write(formatter);
    }
}

std::string Instruction::Name() const
{
    return opCodeStr[static_cast<int>(opCode)];
}

BasicBlock* Instruction::Parent() const
{
    return static_cast<BasicBlock*>(GetContainer()->Parent());
}

bool Instruction::IsLeader() const
{
    BasicBlock* basicBlock = Parent();
    return this == basicBlock->FirstInstruction();
}

bool Instruction::IsTerminator() const
{
    switch (opCode)
    {
    case OpCode::jmp:
    case OpCode::branch:
    case OpCode::ret:
    case OpCode::switch_:
    {
        return true;
    }
    default:
    {
        return false;
    }
    }
}

bool Instruction::IsValueInstruction() const
{
    switch (opCode)
    {
    case OpCode::not_:
    case OpCode::neg:
    case OpCode::signextend:
    case OpCode::zeroextend:
    case OpCode::truncate:
    case OpCode::bitcast:
    case OpCode::inttofloat:
    case OpCode::floattoint:
    case OpCode::inttoptr:
    case OpCode::ptrtoint:
    case OpCode::add:
    case OpCode::sub:
    case OpCode::mul:
    case OpCode::div_:
    case OpCode::mod:
    case OpCode::and_:
    case OpCode::or_:
    case OpCode::xor_:
    case OpCode::shl:
    case OpCode::shr:
    case OpCode::equal:
    case OpCode::less:
    case OpCode::param:
    case OpCode::local:
    case OpCode::load:
    case OpCode::elemaddr:
    case OpCode::ptroffset:
    case OpCode::ptrdiff:
    case OpCode::function_call:
    case OpCode::trap:
    case OpCode::phi:
    {
        return true;
    }
    default:
    {
        return false;
    }
    }
}

bool Instruction::IsUnaryInstruction() const
{
    switch (opCode)
    {
    case OpCode::not_:
    case OpCode::neg:
    case OpCode::signextend:
    case OpCode::zeroextend:
    case OpCode::truncate:
    case OpCode::bitcast:
    case OpCode::inttofloat:
    case OpCode::floattoint:
    case OpCode::inttoptr:
    case OpCode::ptrtoint:
    {
        return true;
    }
    default:
    {
        return false;
    }
    }
}

bool Instruction::IsBinaryInstruction() const
{
    switch (opCode)
    {
    case OpCode::add:
    case OpCode::sub:
    case OpCode::mul:
    case OpCode::div_:
    case OpCode::mod:
    case OpCode::and_:
    case OpCode::or_:
    case OpCode::xor_:
    case OpCode::shl:
    case OpCode::shr:
    case OpCode::equal:
    case OpCode::less:
    {
        return true;
    }
    default:
    {
        return false;
    }
    }
}

bool Instruction::RequiresLocalRegister() const
{
    switch (opCode)
    {
    case OpCode::arg:
    case OpCode::procedure_call:
    case OpCode::not_:
    case OpCode::neg:
    case OpCode::signextend:
    case OpCode::zeroextend:
    case OpCode::truncate:
    case OpCode::bitcast:
    case OpCode::inttofloat:
    case OpCode::floattoint:
    case OpCode::inttoptr:
    case OpCode::ptrtoint:
    case OpCode::add:
    case OpCode::sub:
    case OpCode::mul:
    case OpCode::div_:
    case OpCode::mod:
    case OpCode::and_:
    case OpCode::or_:
    case OpCode::xor_:
    case OpCode::shl:
    case OpCode::shr:
    case OpCode::equal:
    case OpCode::less:
    case OpCode::param:
    case OpCode::load:
    case OpCode::elemaddr:
    case OpCode::ptroffset:
    case OpCode::ptrdiff:
    case OpCode::function_call:
    {
        return true;
    }
    default:
    {
        return false;
    }
    }
}

std::vector<BasicBlock*> Instruction::Successors() const
{
    std::vector<BasicBlock*> successors;
    switch (opCode)
    {
    case OpCode::jmp:
    {
        const JmpInstruction* jmp = static_cast<const JmpInstruction*>(this);
        AddPtrToSet(jmp->TargetBasicBlock(), successors);
        break;
    }
    case OpCode::branch:
    {
        const BranchInstruction* branch = static_cast<const BranchInstruction*>(this);
        AddPtrToSet(branch->TrueTargetBasicBlock(), successors);
        AddPtrToSet(branch->FalseTargetBasicBlock(), successors);
        break;
    }
    case OpCode::switch_:
    {
        const SwitchInstruction* switch_ = static_cast<const SwitchInstruction*>(this);
        AddPtrToSet(switch_->DefaultTargetBlock(), successors);
        for (const CaseTarget& caseTarget : switch_->CaseTargets())
        {
            AddPtrToSet(caseTarget.targetBlock, successors);
        }
        break;
    }
    }
    return successors;
}

void Instruction::AddUser(Instruction* user)
{
    AddPtrToSet(user, users);
}

void Instruction::RemoveUser(Instruction* user)
{
    RemovePtrFromSet(user, users);
}

std::vector<Use> Instruction::Uses()
{
    std::vector<Use> uses;
    switch (opCode)
    {
    case OpCode::store:
    {
        StoreInstruction* store = static_cast<StoreInstruction*>(this);
        store->AddToUses(uses);
        break;
    }
    case OpCode::arg:
    {
        ArgInstruction* arg = static_cast<ArgInstruction*>(this);
        arg->AddToUses(uses);
        break;
    }
    case OpCode::branch:
    {
        BranchInstruction* branch = static_cast<BranchInstruction*>(this);
        branch->AddToUses(uses);
        break;
    }
    case OpCode::procedure_call:
    {
        ProcedureCallInstruction* call = static_cast<ProcedureCallInstruction*>(this);
        call->AddToUses(uses);
        break;
    }
    case OpCode::ret:
    {
        RetInstruction* ret = static_cast<RetInstruction*>(this);
        ret->AddToUses(uses);
        break;
    }
    case OpCode::switch_:
    {
        SwitchInstruction* switch_ = static_cast<SwitchInstruction*>(this);
        switch_->AddToUses(uses);
        break;
    }
    case OpCode::not_:
    case OpCode::neg:
    case OpCode::signextend:
    case OpCode::zeroextend:
    case OpCode::truncate:
    case OpCode::bitcast:
    case OpCode::inttofloat:
    case OpCode::floattoint:
    case OpCode::inttoptr:
    case OpCode::ptrtoint:
    {
        UnaryInstruction* inst = static_cast<UnaryInstruction*>(this);
        inst->AddOperandToUses(uses);
        break;
    }
    case OpCode::add:
    case OpCode::sub:
    case OpCode::mul:
    case OpCode::div_:
    case OpCode::mod:
    case OpCode::and_:
    case OpCode::or_:
    case OpCode::xor_:
    case OpCode::shl:
    case OpCode::shr:
    case OpCode::equal:
    case OpCode::less:
    {
        BinaryInstruction* inst = static_cast<BinaryInstruction*>(this);
        inst->AddOperandsToUses(uses);
        break;
    }
    case OpCode::load:
    {
        LoadInstruction* load = static_cast<LoadInstruction*>(this);
        load->AddToUses(uses);
        break;
    }
    case OpCode::elemaddr:
    {
        ElemAddrInstruction* elemAddr = static_cast<ElemAddrInstruction*>(this);
        elemAddr->AddToUses(uses);
        break;
    }
    case OpCode::ptroffset:
    {
        PtrOffsetInstruction* ptrOffset = static_cast<PtrOffsetInstruction*>(this);
        ptrOffset->AddToUses(uses);
        break;
    }
    case OpCode::ptrdiff:
    {
        PtrDiffInstruction* ptrDiff = static_cast<PtrDiffInstruction*>(this);
        ptrDiff->AddToUses(uses);
        break;
    }
    case OpCode::function_call:
    {
        FunctionCallInstruction* call = static_cast<FunctionCallInstruction*>(this);
        call->AddToUses(uses);
        break;
    }
    case OpCode::trap:
    {
        TrapInstruction* trap = static_cast<TrapInstruction*>(this);
        trap->AddToUses(uses);
        break;
    }
    case OpCode::phi:
    {
        PhiInstruction* phi = static_cast<PhiInstruction*>(this);
        phi->AddToUses(uses);
        break;
    }
    }
    return uses;
}

void Instruction::ReplaceUsesWith(Value* value)
{
    std::vector<Instruction*> users = Users();
    for (Instruction* user : users)
    {
        std::vector<Use> uses = user->Uses();
        for (Use& use : uses)
        {
            use.Set(value);
        }
    }
}

std::unique_ptr<Instruction> Instruction::Remove()
{
    return Parent()->RemoveInst(this);
}

StoreInstruction::StoreInstruction(const SourcePos& sourcePos_, Value* value_, Value* ptr_) : Instruction(sourcePos_, nullptr, OpCode::store), value(value_), ptr(ptr_)
{
}

void StoreInstruction::Write(util::CodeFormatter& formatter)
{
    if (value->IsArrayValue())
    {
        return; // TODO!!!
    }
    formatter.Write(util::Format("store ", 8));
    formatter.Write(value->GetType()->Name());
    formatter.Write(" ");
    formatter.Write(value->ToString());
    formatter.Write(", ");
    formatter.Write(ptr->GetType()->Name());
    formatter.Write(" ");
    formatter.Write(ptr->ToString());
    WriteMetadataRef(formatter);
}

void StoreInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void StoreInstruction::AddUse()
{
    if (value->IsRegValue())
    {
        RegValue* regValue = static_cast<RegValue*>(value);
        Instruction* inst = regValue->Inst();
        if (inst)
        {
            inst->AddUser(this);
        }
    }
    if (ptr->IsRegValue())
    {
        RegValue* regValue = static_cast<RegValue*>(ptr);
        Instruction* inst = regValue->Inst();
        if (inst)
        {
            inst->AddUser(this);
        }
    }
}

void StoreInstruction::AddToUses(std::vector<Use>& uses)
{
    uses.push_back(Use(this, value));
    uses.push_back(Use(this, ptr));
}

ArgInstruction::ArgInstruction(const SourcePos& sourcePos_, Value* arg_) : Instruction(sourcePos_, nullptr, OpCode::arg), arg(arg_)
{
}

void ArgInstruction::Write(util::CodeFormatter& formatter)
{
    formatter.Write(util::Format("arg ", 8));
    formatter.Write(arg->GetType()->Name());
    formatter.Write(" ");
    formatter.Write(arg->ToString());
    WriteMetadataRef(formatter);
}

void ArgInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void ArgInstruction::AddUse()
{
    if (arg->IsRegValue())
    {
        RegValue* regValue = static_cast<RegValue*>(arg);
        Instruction* inst = regValue->Inst();
        if (inst)
        {
            inst->AddUser(this);
        }
    }
}

void ArgInstruction::AddToUses(std::vector<Use>& uses)
{
    uses.push_back(Use(this, arg));
}

JmpInstruction::JmpInstruction(const SourcePos& sourcePos_, int32_t targetLabelId_) :
    Instruction(sourcePos_, nullptr, OpCode::jmp), targetLabelId(targetLabelId_), targetBasicBlock(nullptr)
{
}

void JmpInstruction::Write(util::CodeFormatter& formatter)
{
    formatter.Write(util::Format("jmp ", 8));
    formatter.Write("@" + std::to_string(targetBasicBlock->Id()));
    WriteMetadataRef(formatter);
}

void JmpInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

BranchInstruction::BranchInstruction(const SourcePos& sourcePos_, Value* cond_, int32_t trueTargetLabelId_, int32_t falseTargetLabelId_) :
    Instruction(sourcePos_, nullptr, OpCode::branch),
    cond(cond_), trueTargetLabelId(trueTargetLabelId_), trueTargetBasicBlock(nullptr), falseTargetLabelId(falseTargetLabelId_), falseTargetBasicBlock(nullptr)
{
}

void BranchInstruction::Write(util::CodeFormatter& formatter)
{
    formatter.Write(util::Format("branch ", 8));
    formatter.Write(cond->GetType()->Name());
    formatter.Write(" ");
    formatter.Write(cond->ToString());
    formatter.Write(", ");
    formatter.Write("@" + std::to_string(trueTargetBasicBlock->Id()));
    formatter.Write(", ");
    formatter.Write("@" + std::to_string(falseTargetBasicBlock->Id()));
    WriteMetadataRef(formatter);
}

void BranchInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void BranchInstruction::AddUse()
{
    if (cond->IsRegValue())
    {
        RegValue* regValue = static_cast<RegValue*>(cond);
        Instruction* inst = regValue->Inst();
        if (inst)
        {
            inst->AddUser(this);
        }
    }
}

void BranchInstruction::AddToUses(std::vector<Use>& uses)
{
    uses.push_back(Use(this, cond));
}

ProcedureCallInstruction::ProcedureCallInstruction(const SourcePos& sourcePos_, Value* callee_) : Instruction(sourcePos_, nullptr, OpCode::procedure_call), callee(callee_)
{
}

void ProcedureCallInstruction::Write(util::CodeFormatter& formatter)
{
    formatter.Write(util::Format("call ", 8));
    formatter.Write(callee->GetType()->Name());
    formatter.Write(" ");
    if (callee->GetType()->IsPointerType())
    {
        formatter.Write(callee->ToString());
    }
    else
    {
        formatter.Write("@" + callee->ToString());
    }
    WriteMetadataRef(formatter);
}

void ProcedureCallInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void ProcedureCallInstruction::SetArgs(std::vector<Value*>&& args_)
{
    args = std::move(args_);
}

void ProcedureCallInstruction::AddUse()
{
    if (callee->IsRegValue())
    {
        RegValue* regValue = static_cast<RegValue*>(callee);
        Instruction* inst = regValue->Inst();
        if (inst)
        {
            inst->AddUser(this);
        }
    }
}

void ProcedureCallInstruction::AddToUses(std::vector<Use>& uses)
{
    uses.push_back(Use(this, callee));
}

RetInstruction::RetInstruction(const SourcePos& sourcePos_, Value* returnValue_) : Instruction(sourcePos_, nullptr, OpCode::ret), returnValue(returnValue_)
{
}

void RetInstruction::Write(util::CodeFormatter& formatter)
{
    formatter.Write(util::Format("ret ", 8));
    if (returnValue)
    {
        formatter.Write(returnValue->GetType()->Name());
        formatter.Write(" ");
        formatter.Write(returnValue->ToString());
    }
    else
    {
        formatter.Write("void");
    }
    WriteMetadataRef(formatter);
}

void RetInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void RetInstruction::AddUse()
{
    if (returnValue)
    {
        if (returnValue->IsRegValue())
        {
            RegValue* regValue = static_cast<RegValue*>(returnValue);
            Instruction* inst = regValue->Inst();
            if (inst)
            {
                inst->AddUser(this);
            }
        }
    }
}

void RetInstruction::AddToUses(std::vector<Use>& uses)
{
    if (returnValue)
    {
        uses.push_back(Use(this, returnValue));
    }
}

SwitchInstruction::SwitchInstruction(const SourcePos& sourcePos_, Value* cond_, int32_t defaultTargetId_) : 
    Instruction(sourcePos_, nullptr, OpCode::switch_), cond(cond_), defaultTargetId(defaultTargetId_), defaultTargetBlock()
{
}

void SwitchInstruction::SetDefaultTargetBlock(BasicBlock* defaultTargetBlock_)
{
    defaultTargetBlock = defaultTargetBlock_;
}

void SwitchInstruction::Write(util::CodeFormatter& formatter)
{
    formatter.Write(util::Format("switch ", 8));
    formatter.Write(cond->GetType()->Name());
    formatter.Write(" ");
    formatter.Write(cond->ToString());
    formatter.Write(" ");
    formatter.Write("@" + std::to_string(defaultTargetBlock->Id()));
    formatter.Write(", [");
    bool first = true;
    for (const auto& p : caseTargets)
    {
        if (first)
        {
            first = false;
        }
        else
        {
            formatter.Write(" : ");
        }
        Value* value = p.caseValue;
        BasicBlock* dest = p.targetBlock;
        formatter.Write(value->GetType()->Name());
        formatter.Write(" ");
        formatter.Write(value->ToString());
        formatter.Write(", ");
        formatter.Write("@" + std::to_string(dest->Id()));
    }
    formatter.Write("]");
    WriteMetadataRef(formatter);
}

void SwitchInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void SwitchInstruction::AddCaseTarget(const CaseTarget& caseTarget)
{
    caseTargets.push_back(caseTarget);
}

void SwitchInstruction::AddUse()
{
    if (cond->IsRegValue())
    {
        RegValue* regValue = static_cast<RegValue*>(cond);
        Instruction* inst = regValue->Inst();
        if (inst)
        {
            inst->AddUser(this);
        }
    }
    for (CaseTarget& caseTarget : caseTargets)
    {
        if (caseTarget.caseValue->IsRegValue())
        {
            RegValue* regValue = static_cast<RegValue*>(caseTarget.caseValue);
            Instruction* inst = regValue->Inst();
            if (inst)
            {
                inst->AddUser(this);
            }
        }
    }
}

void SwitchInstruction::AddToUses(std::vector<Use>& uses)
{
    uses.push_back(Use(this, cond));
    for (CaseTarget& caseTarget : caseTargets)
    {
        uses.push_back(Use(this, caseTarget.caseValue));
    }
}

ValueInstruction::ValueInstruction(const SourcePos& sourcePos_, RegValue* result_, OpCode opCode_) : 
    Instruction(sourcePos_, result_->GetType(), opCode_), result(result_)
{
}

void ValueInstruction::SetRegNumber(Function& function)
{
    result->SetReg(function.NextRegNumber());
}

void ValueInstruction::WriteResult(util::CodeFormatter& formatter)
{
    formatter.Write(Format(GetType()->Name(), 7, util::FormatWidth::min));
    formatter.Write(" $" + std::to_string(Result()->Reg()));
}

UnaryInstruction::UnaryInstruction(const SourcePos& sourcePos_, RegValue* result_, Value* operand_, OpCode opCode_) : 
    ValueInstruction(sourcePos_, result_, opCode_), operand(operand_)
{
}

void UnaryInstruction::WriteOperand(util::CodeFormatter& formatter)
{
    formatter.Write(operand->GetType()->Name());
    formatter.Write(" ");
    formatter.Write(operand->ToString());
}

void UnaryInstruction::AddUse()
{
    if (operand->IsRegValue())
    {
        RegValue* regValue = static_cast<RegValue*>(operand);
        Instruction* inst = regValue->Inst();
        if (inst)
        {
            inst->AddUser(this);
        }
    }
}

void UnaryInstruction::AddOperandToUses(std::vector<Use>& uses)
{
    uses.push_back(Use(this, operand));
}

NotInstruction::NotInstruction(const SourcePos& sourcePos_, RegValue* result_, Value* operand_) : UnaryInstruction(sourcePos_, result_, operand_, OpCode::not_)
{
}

void NotInstruction::Write(util::CodeFormatter& formatter)
{
    WriteResult(formatter);
    formatter.Write(" = not ");
    WriteOperand(formatter);
    WriteMetadataRef(formatter);
}

void NotInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

NegInstruction::NegInstruction(const SourcePos& sourcePos_, RegValue* result_, Value* operand_) : UnaryInstruction(sourcePos_, result_, operand_, OpCode::neg)
{
}

void NegInstruction::Write(util::CodeFormatter& formatter)
{
    WriteResult(formatter);
    formatter.Write(" = neg ");
    WriteOperand(formatter);
    WriteMetadataRef(formatter);
}

void NegInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

SignExtendInstruction::SignExtendInstruction(const SourcePos& sourcePos_, RegValue* result_, Value* operand_) : UnaryInstruction(sourcePos_, result_, operand_, OpCode::signextend)
{
}

void SignExtendInstruction::Write(util::CodeFormatter& formatter)
{
    WriteResult(formatter);
    formatter.Write(" = signextend ");
    WriteOperand(formatter);
    WriteMetadataRef(formatter);
}

void SignExtendInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ZeroExtendInstruction::ZeroExtendInstruction(const SourcePos& sourcePos_, RegValue* result_, Value* operand_) : UnaryInstruction(sourcePos_, result_, operand_, OpCode::zeroextend)
{
}

void ZeroExtendInstruction::Write(util::CodeFormatter& formatter)
{
    WriteResult(formatter);
    formatter.Write(" = zeroextend ");
    WriteOperand(formatter);
    WriteMetadataRef(formatter);
}

void ZeroExtendInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

TruncateInstruction::TruncateInstruction(const SourcePos& sourcePos_, RegValue* result_, Value* operand_) : UnaryInstruction(sourcePos_, result_, operand_, OpCode::truncate)
{
}

void TruncateInstruction::Write(util::CodeFormatter& formatter)
{
    WriteResult(formatter);
    formatter.Write(" = truncate ");
    WriteOperand(formatter);
    WriteMetadataRef(formatter);
}

void TruncateInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

BitcastInstruction::BitcastInstruction(const SourcePos& sourcePos_, RegValue* result_, Value* operand_) : UnaryInstruction(sourcePos_, result_, operand_, OpCode::bitcast)
{
}

void BitcastInstruction::Write(util::CodeFormatter& formatter)
{
    WriteResult(formatter);
    formatter.Write(" = bitcast ");
    WriteOperand(formatter);
    WriteMetadataRef(formatter);
}

void BitcastInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

IntToFloatInstruction::IntToFloatInstruction(const SourcePos& sourcePos_, RegValue* result_, Value* operand_) : UnaryInstruction(sourcePos_, result_, operand_, OpCode::inttofloat)
{
}

void IntToFloatInstruction::Write(util::CodeFormatter& formatter)
{
    WriteResult(formatter);
    formatter.Write(" = inttofloat ");
    WriteOperand(formatter);
    WriteMetadataRef(formatter);
}

void IntToFloatInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

FloatToIntInstruction::FloatToIntInstruction(const SourcePos& sourcePos_, RegValue* result_, Value* operand_) : UnaryInstruction(sourcePos_, result_, operand_, OpCode::floattoint)
{
}

void FloatToIntInstruction::Write(util::CodeFormatter& formatter)
{
    WriteResult(formatter);
    formatter.Write(" = floattoint ");
    WriteOperand(formatter);
    WriteMetadataRef(formatter);
}

void FloatToIntInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

IntToPtrInstruction::IntToPtrInstruction(const SourcePos& sourcePos_, RegValue* result_, Value* operand_) : UnaryInstruction(sourcePos_, result_, operand_, OpCode::inttoptr)
{
}

void IntToPtrInstruction::Write(util::CodeFormatter& formatter)
{
    WriteResult(formatter);
    formatter.Write(" = inttoptr ");
    WriteOperand(formatter);
    WriteMetadataRef(formatter);
}

void IntToPtrInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

PtrToIntInstruction::PtrToIntInstruction(const SourcePos& sourcePos_, RegValue* result_, Value* operand_) : UnaryInstruction(sourcePos_, result_, operand_, OpCode::ptrtoint)
{
}

void PtrToIntInstruction::Write(util::CodeFormatter& formatter)
{
    WriteResult(formatter);
    formatter.Write(" = ptrtoint ");
    WriteOperand(formatter);
    WriteMetadataRef(formatter);
}

void PtrToIntInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

BinaryInstruction::BinaryInstruction(const SourcePos& sourcePos_, RegValue* result_, Value* left_, Value* right_, OpCode opCode_) :
    ValueInstruction(sourcePos_, result_, opCode_), left(left_), right(right_)
{
}

void BinaryInstruction::WriteOperands(util::CodeFormatter& formatter)
{
    formatter.Write(left->GetType()->Name());
    formatter.Write(" ");
    formatter.Write(left->ToString());
    formatter.Write(", ");
    formatter.Write(right->GetType()->Name());
    formatter.Write(" ");
    formatter.Write(right->ToString());
}

void BinaryInstruction::AddUse()
{
    if (Left()->IsRegValue())
    {
        RegValue* regValue = static_cast<RegValue*>(Left());
        Instruction* inst = regValue->Inst();
        if (inst)
        {
            inst->AddUser(this);
        }
    }
    if (Right()->IsRegValue())
    {
        RegValue* regValue = static_cast<RegValue*>(Right());
        Instruction* inst = regValue->Inst();
        if (inst)
        {
            inst->AddUser(this);
        }
    }
}

void BinaryInstruction::AddOperandsToUses(std::vector<Use>& uses)
{
    uses.push_back(Use(this, left));
    uses.push_back(Use(this, right));
}

AddInstruction::AddInstruction(const SourcePos& sourcePos_, RegValue* result_, Value* left_, Value* right_) : BinaryInstruction(sourcePos_, result_, left_, right_, OpCode::add)
{
}

void AddInstruction::Write(util::CodeFormatter& formatter)
{
    WriteResult(formatter);
    formatter.Write(" = add ");
    WriteOperands(formatter);
    WriteMetadataRef(formatter);
}

void AddInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

SubInstruction::SubInstruction(const SourcePos& sourcePos_, RegValue* result_, Value* left_, Value* right_) : BinaryInstruction(sourcePos_, result_, left_, right_, OpCode::sub)
{
}

void SubInstruction::Write(util::CodeFormatter& formatter)
{
    WriteResult(formatter);
    formatter.Write(" = sub ");
    WriteOperands(formatter);
    WriteMetadataRef(formatter);
}

void SubInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

MulInstruction::MulInstruction(const SourcePos& sourcePos_, RegValue* result_, Value* left_, Value* right_) : BinaryInstruction(sourcePos_, result_, left_, right_, OpCode::mul)
{
}

void MulInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void MulInstruction::Write(util::CodeFormatter& formatter)
{
    WriteResult(formatter);
    formatter.Write(" = mul ");
    WriteOperands(formatter);
    WriteMetadataRef(formatter);
}

DivInstruction::DivInstruction(const SourcePos& sourcePos_, RegValue* result_, Value* left_, Value* right_) : BinaryInstruction(sourcePos_, result_, left_, right_, OpCode::div_)
{
}

void DivInstruction::Write(util::CodeFormatter& formatter)
{
    WriteResult(formatter);
    formatter.Write(" = div ");
    WriteOperands(formatter);
    WriteMetadataRef(formatter);
}

void DivInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ModInstruction::ModInstruction(const SourcePos& sourcePos_, RegValue* result_, Value* left_, Value* right_) : BinaryInstruction(sourcePos_, result_, left_, right_, OpCode::mod)
{
}

void ModInstruction::Write(util::CodeFormatter& formatter)
{
    WriteResult(formatter);
    formatter.Write(" = mod ");
    WriteOperands(formatter);
    WriteMetadataRef(formatter);
}

void ModInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

AndInstruction::AndInstruction(const SourcePos& sourcePos_, RegValue* result_, Value* left_, Value* right_) : BinaryInstruction(sourcePos_, result_, left_, right_, OpCode::and_)
{
}

void AndInstruction::Write(util::CodeFormatter& formatter)
{
    WriteResult(formatter);
    formatter.Write(" = and ");
    WriteOperands(formatter);
    WriteMetadataRef(formatter);
}

void AndInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

OrInstruction::OrInstruction(const SourcePos& sourcePos_, RegValue* result_, Value* left_, Value* right_) : BinaryInstruction(sourcePos_, result_, left_, right_, OpCode::or_)
{
}

void OrInstruction::Write(util::CodeFormatter& formatter)
{
    WriteResult(formatter);
    formatter.Write(" = or ");
    WriteOperands(formatter);
    WriteMetadataRef(formatter);
}

void OrInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

XorInstruction::XorInstruction(const SourcePos& sourcePos_, RegValue* result_, Value* left_, Value* right_) : BinaryInstruction(sourcePos_, result_, left_, right_, OpCode::xor_)
{
}

void XorInstruction::Write(util::CodeFormatter& formatter)
{
    WriteResult(formatter);
    formatter.Write(" = xor ");
    WriteOperands(formatter);
    WriteMetadataRef(formatter);
}

void XorInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ShlInstruction::ShlInstruction(const SourcePos& sourcePos_, RegValue* result_, Value* left_, Value* right_) : BinaryInstruction(sourcePos_, result_, left_, right_, OpCode::shl)
{
}

void ShlInstruction::Write(util::CodeFormatter& formatter)
{
    WriteResult(formatter);
    formatter.Write(" = shl ");
    WriteOperands(formatter);
    WriteMetadataRef(formatter);
}

void ShlInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ShrInstruction::ShrInstruction(const SourcePos& sourcePos_, RegValue* result_, Value* left_, Value* right_) : BinaryInstruction(sourcePos_, result_, left_, right_, OpCode::shr)
{
}

void ShrInstruction::Write(util::CodeFormatter& formatter)
{
    WriteResult(formatter);
    formatter.Write(" = shr ");
    WriteOperands(formatter);
    WriteMetadataRef(formatter);
}

void ShrInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

EqualInstruction::EqualInstruction(const SourcePos& sourcePos_, RegValue* result_, Value* left_, Value* right_) : BinaryInstruction(sourcePos_, result_, left_, right_, OpCode::equal)
{
}

void EqualInstruction::Write(util::CodeFormatter& formatter)
{
    WriteResult(formatter);
    formatter.Write(" = equal ");
    WriteOperands(formatter);
    WriteMetadataRef(formatter);
}

void EqualInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

LessInstruction::LessInstruction(const SourcePos& sourcePos_, RegValue* result_, Value* left_, Value* right_) : BinaryInstruction(sourcePos_, result_, left_, right_, OpCode::less)
{
}

void LessInstruction::Write(util::CodeFormatter& formatter)
{
    WriteResult(formatter);
    formatter.Write(" = less ");
    WriteOperands(formatter);
    WriteMetadataRef(formatter);
}

void LessInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ParamInstruction::ParamInstruction(const SourcePos& sourcePos_, RegValue* result_) : ValueInstruction(sourcePos_, result_, OpCode::param)
{
}

void ParamInstruction::Write(util::CodeFormatter& formatter)
{
    WriteResult(formatter);
    formatter.Write(" = param");
    WriteMetadataRef(formatter);
}

void ParamInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

LocalInstruction::LocalInstruction(const SourcePos& sourcePos_, RegValue* result_, Type* localType_) : 
    ValueInstruction(sourcePos_, result_, OpCode::local), localType(localType_)
{
}

void LocalInstruction::Write(util::CodeFormatter& formatter)
{
    WriteResult(formatter);
    formatter.Write(" = local ");
    formatter.Write(localType->Name());
    WriteMetadataRef(formatter);
}

void LocalInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

LoadInstruction::LoadInstruction(const SourcePos& sourcePos_, RegValue* result_, Value* ptr_) : ValueInstruction(sourcePos_, result_, OpCode::load), ptr(ptr_)
{
}

void LoadInstruction::Write(util::CodeFormatter& formatter)
{
    WriteResult(formatter);
    formatter.Write(" = load ");
    formatter.Write(ptr->GetType()->Name());
    formatter.Write(" ");
    formatter.Write(ptr->ToString());
    WriteMetadataRef(formatter);
}

void LoadInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void LoadInstruction::AddUse()
{
    if (ptr->IsRegValue())
    {
        RegValue* regValue = static_cast<RegValue*>(ptr);
        Instruction* inst = regValue->Inst();
        if (inst)
        {
            inst->AddUser(this);
        }
    }
}

void LoadInstruction::AddToUses(std::vector<Use>& uses)
{
    uses.push_back(Use(this, ptr));
}

ElemAddrInstruction::ElemAddrInstruction(const SourcePos& sourcePos_, RegValue* result_, Value* ptr_, Value* index_) :
    ValueInstruction(sourcePos_, result_, OpCode::elemaddr), ptr(ptr_), index(index_)
{
}

void ElemAddrInstruction::Write(util::CodeFormatter& formatter)
{
    WriteResult(formatter);
    formatter.Write(" = elemaddr ");
    formatter.Write(ptr->GetType()->Name());
    formatter.Write(" ");
    formatter.Write(ptr->ToString());
    formatter.Write(", ");
    formatter.Write(index->GetType()->Name());
    formatter.Write(" ");
    formatter.Write(index->ToString());
    WriteMetadataRef(formatter);
}

void ElemAddrInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void ElemAddrInstruction::AddUse()
{
    if (ptr->IsRegValue())
    {
        RegValue* regValue = static_cast<RegValue*>(ptr);
        Instruction* inst = regValue->Inst();
        if (inst)
        {
            inst->AddUser(this);
        }
    }
    if (index->IsRegValue())
    {
        RegValue* regValue = static_cast<RegValue*>(index);
        Instruction* inst = regValue->Inst();
        if (inst)
        {
            inst->AddUser(this);
        }
    }
}

void ElemAddrInstruction::AddToUses(std::vector<Use>& uses)
{
    uses.push_back(Use(this, ptr));
    uses.push_back(Use(this, index));
}

ElemAddrKind ElemAddrInstruction::GetElemAddrKind(Context* context) const
{
    if (ptr->GetType()->IsPointerType())
    {
        PointerType* ptrType = static_cast<PointerType*>(ptr->GetType());
        Type* pointeeType = ptrType->RemovePointer(GetSourcePos(), context);
        if (pointeeType->IsArrayType())
        {
            return ElemAddrKind::array;
        }
        else if (pointeeType->IsStructureType())
        {
            return ElemAddrKind::structure;
        }
    }
    Error("invalid elem addr kind", GetSourcePos(), context);
    return ElemAddrKind::none;
}

PtrOffsetInstruction::PtrOffsetInstruction(const SourcePos& sourcePos_, RegValue* result_, Value* ptr_, Value* offset_) :
    ValueInstruction(sourcePos_, result_, OpCode::ptroffset), ptr(ptr_), offset(offset_)
{
}

void PtrOffsetInstruction::Write(util::CodeFormatter& formatter)
{
    WriteResult(formatter);
    formatter.Write(" = ptroffset ");
    formatter.Write(ptr->GetType()->Name());
    formatter.Write(" ");
    formatter.Write(ptr->ToString());
    formatter.Write(", ");
    formatter.Write(offset->GetType()->Name());
    formatter.Write(" ");
    formatter.Write(offset->ToString());
    WriteMetadataRef(formatter);
}

void PtrOffsetInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void PtrOffsetInstruction::AddUse()
{
    if (ptr->IsRegValue())
    {
        RegValue* regValue = static_cast<RegValue*>(ptr);
        Instruction* inst = regValue->Inst();
        if (inst)
        {
            inst->AddUser(this);
        }
    }
    if (offset->IsRegValue())
    {
        RegValue* regValue = static_cast<RegValue*>(offset);
        Instruction* inst = regValue->Inst();
        if (inst)
        {
            inst->AddUser(this);
        }
    }
}

void PtrOffsetInstruction::AddToUses(std::vector<Use>& uses)
{
    uses.push_back(Use(this, ptr));
    uses.push_back(Use(this, offset));
}

PtrDiffInstruction::PtrDiffInstruction(const SourcePos& sourcePos_, RegValue* result_, Value* leftPtr_, Value* rightPtr_) :
    ValueInstruction(sourcePos_, result_, OpCode::ptrdiff), leftPtr(leftPtr_), rightPtr(rightPtr_)
{
}

void PtrDiffInstruction::Write(util::CodeFormatter& formatter)
{
    WriteResult(formatter);
    formatter.Write(" = ptrdiff ");
    formatter.Write(leftPtr->GetType()->Name());
    formatter.Write(" ");
    formatter.Write(leftPtr->ToString());
    formatter.Write(", ");
    formatter.Write(rightPtr->GetType()->Name());
    formatter.Write(" ");
    formatter.Write(rightPtr->ToString());
    WriteMetadataRef(formatter);
}

void PtrDiffInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void PtrDiffInstruction::AddUse()
{
    if (leftPtr->IsRegValue())
    {
        RegValue* regValue = static_cast<RegValue*>(leftPtr);
        Instruction* inst = regValue->Inst();
        if (inst)
        {
            inst->AddUser(this);
        }
    }
    if (rightPtr->IsRegValue())
    {
        RegValue* regValue = static_cast<RegValue*>(rightPtr);
        Instruction* inst = regValue->Inst();
        if (inst)
        {
            inst->AddUser(this);
        }
    }
}

void PtrDiffInstruction::AddToUses(std::vector<Use>& uses)
{
    uses.push_back(Use(this, leftPtr));
    uses.push_back(Use(this, rightPtr));
}

FunctionCallInstruction::FunctionCallInstruction(const SourcePos& sourcePos_, RegValue* result_, Value* callee_) :
    ValueInstruction(sourcePos_, result_, OpCode::function_call), callee(callee_)
{
}

void FunctionCallInstruction::Write(util::CodeFormatter& formatter)
{
    WriteResult(formatter);
    formatter.Write(" = call ");
    formatter.Write(callee->GetType()->Name());
    formatter.Write(" ");
    if (callee->GetType()->IsPointerType())
    {
        formatter.Write(callee->ToString());
    }
    else
    {
        formatter.Write("@" + callee->ToString());
    }
    WriteMetadataRef(formatter);
}

void FunctionCallInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void FunctionCallInstruction::SetArgs(std::vector<Value*>&& args_)
{
    args = std::move(args_);
}

void FunctionCallInstruction::AddUse()
{
    if (callee->IsRegValue())
    {
        RegValue* regValue = static_cast<RegValue*>(callee);
        Instruction* inst = regValue->Inst();
        if (inst)
        {
            inst->AddUser(this);
        }
    }
}

void FunctionCallInstruction::AddToUses(std::vector<Use>& uses)
{
    uses.push_back(Use(this, callee));
}

TrapInstruction::TrapInstruction(const SourcePos& sourcePos_, RegValue* result_, Value* op1_, Value* op2_, Value* op3_) :
    ValueInstruction(sourcePos_, result_, OpCode::trap), op1(op1_), op2(op2_), op3(op3_)
{
}

void TrapInstruction::Write(util::CodeFormatter& formatter)
{
    WriteResult(formatter);
    formatter.Write(" = trap ");
    formatter.Write(op1->GetType()->Name());
    formatter.Write(" ");
    formatter.Write(op1->ToString());
    formatter.Write(", ");
    formatter.Write(op2->GetType()->Name());
    formatter.Write(" ");
    formatter.Write(op2->ToString());
    formatter.Write(", ");
    formatter.Write(op3->GetType()->Name());
    formatter.Write(" ");
    formatter.Write(op3->ToString());
    WriteMetadataRef(formatter);
}

void TrapInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void TrapInstruction::SetArgs(std::vector<Value*>&& args_)
{
    args = std::move(args_);
}

void TrapInstruction::AddUse()
{
    if (op1->IsRegValue())
    {
        RegValue* regValue = static_cast<RegValue*>(op1);
        Instruction* inst = regValue->Inst();
        if (inst)
        {
            inst->AddUser(this);
        }
    }
    if (op2->IsRegValue())
    {
        RegValue* regValue = static_cast<RegValue*>(op2);
        Instruction* inst = regValue->Inst();
        if (inst)
        {
            inst->AddUser(this);
        }
    }
    if (op3->IsRegValue())
    {
        RegValue* regValue = static_cast<RegValue*>(op3);
        Instruction* inst = regValue->Inst();
        if (inst)
        {
            inst->AddUser(this);
        }
    }
    for (Value* arg : args)
    {
        if (arg->IsRegValue())
        {
            RegValue* regValue = static_cast<RegValue*>(arg);
            Instruction* inst = regValue->Inst();
            if (inst)
            {
                inst->AddUser(this);
            }
        }
    }
}

void TrapInstruction::AddToUses(std::vector<Use>& uses)
{
    uses.push_back(Use(this, op1));
    uses.push_back(Use(this, op2));
    uses.push_back(Use(this, op3));
    for (Value*& arg : args)
    {
        uses.push_back(Use(this, arg));
    }
}

BlockValue::BlockValue(Value* value_, BasicBlock* block_) : value(value_), blockId(block_->Id()), block(block_)
{
}

PhiInstruction::PhiInstruction(const SourcePos& sourcePos_, RegValue* result_) : ValueInstruction(sourcePos_, result_, OpCode::phi)
{
}

void PhiInstruction::Write(util::CodeFormatter& formatter)
{
    WriteResult(formatter);
    formatter.Write(" = phi [");
    for (auto& blockValue : blockValues)
    {
        formatter.Write(blockValue.value->GetType()->Name());
        formatter.Write(" ");
        formatter.Write(blockValue.value->ToString());
        formatter.Write(", ");
        formatter.Write(std::to_string(blockValue.block->Id()));
    }
    formatter.Write("]");
}

void PhiInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void PhiInstruction::AddBlockValue(const BlockValue& blockValue)
{
    blockValues.push_back(blockValue);
}

void PhiInstruction::AddUse()
{
    for (BlockValue& blockValue : blockValues)
    {
        if (blockValue.value->IsRegValue())
        {
            RegValue* regValue = static_cast<RegValue*>(blockValue.value);
            Instruction* inst = regValue->Inst();
            if (inst)
            {
                inst->AddUser(this);
            }
        }
    }
}

void PhiInstruction::AddToUses(std::vector<Use>& uses)
{
    for (BlockValue& blockValue : blockValues)
    {
        uses.push_back(Use(this, blockValue.value));
    }
}

NoOperationInstruction::NoOperationInstruction(const SourcePos& sourcePos_) : Instruction(sourcePos_, nullptr, OpCode::nop)
{
}

void NoOperationInstruction::Write(util::CodeFormatter& formatter)
{
    formatter.Write("nop");
    WriteMetadataRef(formatter);
}

void NoOperationInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

} // namespace otava::intermediate
