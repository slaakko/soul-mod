// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.intermediate.code;

import otava.intermediate.context;
import otava.intermediate.visitor;
import otava.intermediate.error;
import otava.intermediate.util;
import util;

namespace otava::intermediate {

std::string OpCodeStr(OpCode opCode)
{
    switch (opCode)
    {
        case OpCode::store: return "store";
        case OpCode::arg: return "arg";
        case OpCode::jmp: return "jmp";
        case OpCode::branch: return "branch";
        case OpCode::procedure_call: return "call";
        case OpCode::ret: return "ret";
        case OpCode::switch_: return "switch";
        case OpCode::not_: return "not";
        case OpCode::neg: return "neg";
        case OpCode::signextend: return "signextend";
        case OpCode::zeroextend: return "zeroextend";
        case OpCode::fpextend: return "fpextend";
        case OpCode::truncate: return "truncate";
        case OpCode::bitcast: return "bitcast";
        case OpCode::inttofloat: return "inttofloat";
        case OpCode::floattoint: return "floattoint";
        case OpCode::inttoptr: return "inttoptr";
        case OpCode::ptrtoint: return "ptrtoint";
        case OpCode::add: return "add";
        case OpCode::sub: return "sub";
        case OpCode::mul: return "mul";
        case OpCode::div_: return "div";
        case OpCode::mod: return "mod";
        case OpCode::and_: return "and";
        case OpCode::or_: return "or";
        case OpCode::xor_: return "xor";
        case OpCode::shl: return "shl";
        case OpCode::shr: return "shr";
        case OpCode::equal: return "equal";
        case OpCode::less: return "less";
        case OpCode::param: return "param";
        case OpCode::local: return "local";
        case OpCode::load: return "load";
        case OpCode::elemaddr: return "elemaddr";
        case OpCode::ptroffset: return "ptroffset";
        case OpCode::ptrdiff: return "ptrdiff";
        case OpCode::function_call: return "call";
        case OpCode::nop: return "nop";
    }
    return "<opcode>";
}

RegValue::RegValue(const soul::ast::Span& span_, Type* type_, std::int32_t reg_) : Value(span_, ValueKind::regValue, type_), reg(reg_), inst(nullptr)
{
}

RegValue::~RegValue()
{
    if (inst && inst->IsValueInstruction())
    {
        ValueInstruction* valueInst = static_cast<ValueInstruction*>(inst);
        valueInst->ResetResult();
    }
}

std::string RegValue::ToString() const
{
    return "$" + std::to_string(inst->RegValueIndex());
}

std::expected<Value*, int> RegValue::Clone(CloneContext& cloneContext) const
{
    RegValue* regValue = cloneContext.CurrentFunction()->GetRegValue(reg);
    if (regValue)
    {
        return std::expected<Value*, int>(regValue);
    }
    RegValue* clone = cloneContext.CurrentFunction()->MakeRegValue(Span(), GetType(), reg, cloneContext.GetContext());
    Instruction* mappedInst = cloneContext.GetMappedInstruction(inst);
    if (mappedInst)
    {
        clone->SetInst(mappedInst);
    }
    else
    {
        cloneContext.AddUnmappedInstruction(inst, clone);
    }
    return std::expected<Value*, int>(static_cast<Value*>(clone));
}

void AddUser(Instruction* user, Value* value)
{
    if (value)
    {
        if (value->IsRegValue())
        {
            RegValue* regValue = static_cast<RegValue*>(value);
            if (regValue->Inst())
            {
                regValue->Inst()->AddUser(user);
            }
        }
    }
}

void RemoveUser(Instruction* user, Value* value)
{
    if (value)
    {
        if (value->IsRegValue())
        {
            RegValue* regValue = static_cast<RegValue*>(value);
            if (regValue->Inst())
            {
                regValue->Inst()->RemoveUser(user);
            }
        }
    }
}

void AddToUsesVec(std::vector<Instruction*>& uses, Value* value)
{
    if (value)
    {
        if (value->IsRegValue())
        {
            RegValue* regValue = static_cast<RegValue*>(value);
            if (regValue->Inst())
            {
                uses.push_back(regValue->Inst());
            }
        }
    }
}

Instruction::Instruction(const soul::ast::Span& span_, Type* type_, OpCode opCode_) :
    Value(span_, ValueKind::instruction, type_), util::Component(), opCode(opCode_), metadataRef(nullptr), index(-1), regValueIndex(-1), assemblyInstruction(nullptr)
{
}

std::expected<bool, int> Instruction::Check()
{
    for (Instruction* user : users)
    {
        if (user->opCode < OpCode::store || user->opCode > OpCode::nop)
        {
            return std::unexpected<int>(util::AllocateError("invalid instruction"));
        }
    }
    return std::expected<bool, int>(true);
}

std::string Instruction::Name() const
{
    return OpCodeStr(opCode);
}

bool Instruction::IsLeader() const
{
    BasicBlock* basicBlock = Parent();
    return this == basicBlock->Leader();
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
        case OpCode::fpextend:
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
        case OpCode::fpextend:
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
        case OpCode::fpextend:
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

BasicBlock* Instruction::Parent() const
{
    return static_cast<BasicBlock*>(GetContainer()->Parent());
}

void Instruction::AddUser(Instruction* user)
{
    AddPtrToSet(user, users);
}

void Instruction::RemoveUser(Instruction* user)
{
    RemovePtrFromSet(user, users);
}

void Instruction::AddToUses()
{
}

std::expected<bool, int> Instruction::ReplaceUsesWith(Value* value)
{
    Function* fn = Parent()->Parent();
    RegValue* use = fn->GetRegValue(RegValueIndex());
    if (use)
    {
        std::vector<Instruction*> copiedUsers = users;
        for (Instruction* user : copiedUsers)
        {
            user->ReplaceValue(use, value);
        }
    }
    else
    {
        Code* code = fn->Parent();
        Context* context = code->GetContext();
        return Error("reg value " + std::to_string(RegValueIndex()) + "not found", Span(), context);
    }
    return std::expected<bool, int>(true);
}

void Instruction::RemoveFromUses()
{
    std::vector<Instruction*> uses = Uses();
    for (Instruction* use : uses)
    {
        use->RemoveUser(this);
    }
}

void Instruction::ReplaceValue(Value* use, Value* value)
{
}

bool Instruction::IsRetVoid() const
{
    if (IsRetInstruction())
    {
        const RetInstruction* retInst = static_cast<const RetInstruction*>(this);
        return retInst->ReturnValue() == nullptr;
    }
    return false;
}

StoreInstruction::StoreInstruction(const soul::ast::Span& span_, Value* value_, Value* ptr_) : Instruction(span_, nullptr, OpCode::store), value(value_), ptr(ptr_)
{
}

void StoreInstruction::AddToUses()
{
    otava::intermediate::AddUser(this, value);
    otava::intermediate::AddUser(this, ptr);
}

void StoreInstruction::ReplaceValue(Value* use, Value* value)
{
    if (this->value == use)
    {
        otava::intermediate::RemoveUser(this, this->value);
        this->value = value;
        otava::intermediate::AddUser(this, this->value);
    }
    if (ptr == use)
    {
        otava::intermediate::RemoveUser(this, ptr);
        ptr = value;
        otava::intermediate::AddUser(this, ptr);
    }
}

std::vector<Instruction*> StoreInstruction::Uses() const
{
    std::vector<Instruction*> uses;
    AddToUsesVec(uses, value);
    AddToUsesVec(uses, ptr);
    return uses;
}

void StoreInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<Value*, int> StoreInstruction::Clone(CloneContext& cloneContext) const
{
    std::expected<Value*, int> rv = value->Clone(cloneContext);
    if (!rv) return rv;
    Value* clonedValue = *rv;
    rv = ptr->Clone(cloneContext);
    if (!rv) return rv;
    Value* clonedPtr = *rv;
    StoreInstruction* clone = new StoreInstruction(Span(), clonedValue, clonedPtr);
    clone->SetIndex(Index());
    clone->SetRegValueIndex(RegValueIndex());
    clone->AddToUses();
    return std::expected<Value*, int>(static_cast<Value*>(clone));
}

void StoreInstruction::Write(util::CodeFormatter& formatter)
{
    formatter.Write(util::Format("store ", 8));
    formatter.Write(value->GetType()->Name());
    formatter.Write(" ");
    formatter.Write(value->ToString());
    formatter.Write(", ");
    formatter.Write(ptr->GetType()->Name());
    formatter.Write(" ");
    formatter.Write(ptr->ToString());
}

ArgInstruction::ArgInstruction(const soul::ast::Span& span_, Value* arg_) : Instruction(span_, nullptr, OpCode::arg), arg(arg_)
{
}

void ArgInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<Value*, int> ArgInstruction::Clone(CloneContext& cloneContext) const
{
    std::expected<Value*, int> rv = arg->Clone(cloneContext);
    if (!rv) return rv;
    Value* clonedArg = *rv;
    ArgInstruction* clone = new ArgInstruction(Span(), clonedArg);
    clone->SetIndex(Index());
    clone->SetRegValueIndex(RegValueIndex());
    clone->AddToUses();
    return std::expected<Value*, int>(static_cast<Value*>(clone));
}

void ArgInstruction::AddToUses()
{
    otava::intermediate::AddUser(this, arg);
}

void ArgInstruction::ReplaceValue(Value* use, Value* value)
{
    if (arg == use)
    {
        otava::intermediate::RemoveUser(this, arg);
        arg = value;
        otava::intermediate::AddUser(this, arg);
    }
}

std::vector<Instruction*> ArgInstruction::Uses() const
{
    std::vector<Instruction*> uses;
    AddToUsesVec(uses, arg);
    return uses;
}

void ArgInstruction::Write(util::CodeFormatter& formatter)
{
    formatter.Write(util::Format("arg ", 8));
    formatter.Write(arg->GetType()->Name());
    formatter.Write(" ");
    formatter.Write(arg->ToString());
}

JmpInstruction::JmpInstruction(const soul::ast::Span& span_, std::int32_t targetLabelId_) :
    Instruction(span_, nullptr, OpCode::jmp), targetLabelId(targetLabelId_), targetBasicBlock(nullptr)
{
}

void JmpInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<Value*, int> JmpInstruction::Clone(CloneContext& cloneContext) const
{
    JmpInstruction* clone = new JmpInstruction(Span(), targetBasicBlock->Id());
    clone->SetIndex(Index());
    clone->SetRegValueIndex(RegValueIndex());
    BasicBlock* bb = cloneContext.GetMappedBasicBlock(targetBasicBlock);
    if (bb)
    {
        clone->SetTargetBasicBlock(bb);
    }
    else
    {
        return Error("mapped basic block not found", Span(), cloneContext.GetContext());
    }
    clone->AddToUses();
    return std::expected<Value*, int>(static_cast<Value*>(clone));
}

void JmpInstruction::Write(util::CodeFormatter& formatter)
{
    formatter.Write(util::Format("jmp ", 8));
    formatter.Write("@" + std::to_string(targetBasicBlock->Id()));
}

BranchInstruction::BranchInstruction(const soul::ast::Span& span_, Value* cond_, std::int32_t trueTargetLabelId_, std::int32_t falseTargetLabelId_) :
    Instruction(span_, nullptr, OpCode::branch),
    cond(cond_), trueTargetLabelId(trueTargetLabelId_), trueTargetBasicBlock(nullptr), falseTargetLabelId(falseTargetLabelId_), falseTargetBasicBlock(nullptr)
{
}

void BranchInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<Value*, int> BranchInstruction::Clone(CloneContext& cloneContext) const
{
    std::expected<Value*, int> rv = cond->Clone(cloneContext);
    if (!rv) return rv;
    Value* clonedCond = *rv;
    BranchInstruction* clone = new BranchInstruction(Span(), clonedCond, trueTargetBasicBlock->Id(), falseTargetBasicBlock->Id());
    clone->SetIndex(Index());
    clone->SetRegValueIndex(RegValueIndex());
    BasicBlock* trueBB = cloneContext.GetMappedBasicBlock(trueTargetBasicBlock);
    if (trueBB)
    {
        clone->SetTrueTargetBasicBlock(trueBB);
    }
    else
    {
        return Error("mapped basic block not found", trueTargetBasicBlock->Span(), cloneContext.GetContext());
    }
    BasicBlock* falseBB = cloneContext.GetMappedBasicBlock(falseTargetBasicBlock);
    if (falseBB)
    {
        clone->SetFalseTargetBasicBlock(falseBB);
    }
    else
    {
        return Error("mapped basic block not found", falseTargetBasicBlock->Span(), cloneContext.GetContext());
    }
    clone->AddToUses();
    return std::expected<Value*, int>(static_cast<Value*>(clone));
}

void BranchInstruction::AddToUses()
{
    otava::intermediate::AddUser(this, cond);
}

void BranchInstruction::ReplaceValue(Value* use, Value* value)
{
    if (cond == use)
    {
        otava::intermediate::RemoveUser(this, cond);
        cond = value;
        otava::intermediate::AddUser(this, cond);
    }
}

std::vector<Instruction*> BranchInstruction::Uses() const
{
    std::vector<Instruction*> uses;
    AddToUsesVec(uses, cond);
    return uses;
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
}

ProcedureCallInstruction::ProcedureCallInstruction(const soul::ast::Span& span_, Value* callee_) : Instruction(span_, nullptr, OpCode::procedure_call), callee(callee_)
{
}

void ProcedureCallInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<Value*, int> ProcedureCallInstruction::Clone(CloneContext& cloneContext) const
{
    std::expected<Value*, int> rv = callee->Clone(cloneContext);
    if (!rv) return rv;
    Value* clonedCallee = *rv;
    ProcedureCallInstruction* clone = new ProcedureCallInstruction(Span(), clonedCallee);
    clone->SetIndex(Index());
    clone->SetRegValueIndex(RegValueIndex());
    std::vector<Value*> clonedArgs;
    for (Value* arg : args)
    {
        rv = arg->Clone(cloneContext);
        if (!rv) return rv;
        Value* clonedArg = *rv;
        clonedArgs.push_back(clonedArg);
    }
    clone->SetArgs(std::move(clonedArgs));
    clone->AddToUses();
    return std::expected<Value*, int>(static_cast<Value*>(clone));
}

void ProcedureCallInstruction::SetArgs(std::vector<Value*>&& args_)
{
    args = std::move(args_);
}

Function* ProcedureCallInstruction::CalleeFn() const
{
    if (callee->IsSymbolValue())
    {
        SymbolValue* symbolValue = static_cast<SymbolValue*>(callee);
        return symbolValue->GetFunction();
    }
    return nullptr;
}

void ProcedureCallInstruction::AddToUses()
{
    otava::intermediate::AddUser(this, callee);
    for (Value* arg : args)
    {
        otava::intermediate::AddUser(this, arg);
    }
}

void ProcedureCallInstruction::ReplaceValue(Value* use, Value* value)
{
    if (callee == use)
    {
        otava::intermediate::RemoveUser(this, callee);
        callee = value;
        otava::intermediate::AddUser(this, callee);
    }
    for (Value* arg : args)
    {
        if (arg == use)
        {
            otava::intermediate::RemoveUser(this, arg);
            arg = value;
            otava::intermediate::AddUser(this, arg);
        }
    }
}

std::vector<Instruction*> ProcedureCallInstruction::Uses() const
{
    std::vector<Instruction*> uses;
    AddToUsesVec(uses, callee);
    for (Value* arg : args)
    {
        AddToUsesVec(uses, arg);
    }
    return uses;
}

void ProcedureCallInstruction::Write(util::CodeFormatter& formatter)
{
    formatter.Write(util::Format("call ", 8));
    formatter.Write(callee->GetType()->Name());
    formatter.Write(" ");
    formatter.Write(callee->ToString());
}

RetInstruction::RetInstruction(const soul::ast::Span& span_, Value* returnValue_) : Instruction(span_, nullptr, OpCode::ret), returnValue(returnValue_)
{
}

void RetInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<Value*, int> RetInstruction::Clone(CloneContext& cloneContext) const
{
    Value* clonedReturnValue = nullptr;
    if (returnValue)
    {
        std::expected<Value*, int> rv = returnValue->Clone(cloneContext);
        if (!rv) return rv;
        clonedReturnValue = *rv;
    }
    RetInstruction* clone = new RetInstruction(Span(), clonedReturnValue);
    clone->SetIndex(Index());
    clone->SetRegValueIndex(RegValueIndex());
    clone->AddToUses();
    return std::expected<Value*, int>(static_cast<Value*>(clone));
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
}

bool RetInstruction::IsFloatingPointInstruction() const
{
    if (returnValue)
    {
        return returnValue->GetType()->IsFloatingPointType();
    }
    return false;
}

void RetInstruction::AddToUses()
{
    otava::intermediate::AddUser(this, returnValue);
}

void RetInstruction::ReplaceValue(Value* use, Value* value)
{
    if (returnValue == use)
    {
        otava::intermediate::RemoveUser(this, returnValue);
        returnValue = value;
        otava::intermediate::AddUser(this, returnValue);
    }
}

std::vector<Instruction*> RetInstruction::Uses() const
{
    std::vector<Instruction*> uses;
    if (returnValue)
    {
        AddToUsesVec(uses, returnValue);
    }
    return uses;
}

CaseTarget::CaseTarget() : caseValue(nullptr), targetLabelId(-1), targetBlock(nullptr)
{
}

SwitchInstruction::SwitchInstruction(const soul::ast::Span& span_, Value* cond_, std::int32_t defaultTargetLabelId_) :
    Instruction(span_, nullptr, OpCode::switch_), cond(cond_), defaultTargetLabelId(defaultTargetLabelId_), defaultTargetBlock(nullptr)
{
}

void SwitchInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<Value*, int> SwitchInstruction::Clone(CloneContext& cloneContext) const
{
    std::expected<Value*, int> rv = cond->Clone(cloneContext);
    if (!rv) return rv;
    Value* clonedCond = *rv;
    SwitchInstruction* clone = new SwitchInstruction(Span(), clonedCond, defaultTargetBlock->Id());
    clone->SetIndex(Index());
    clone->SetRegValueIndex(RegValueIndex());
    BasicBlock* bb = cloneContext.GetMappedBasicBlock(defaultTargetBlock);
    if (bb)
    {
        clone->SetDefaultTargetBlock(bb);
    }
    else
    {
        return Error("mapped basic block not found", defaultTargetBlock->Span(), cloneContext.GetContext());
    }
    for (const auto& caseTarget : caseTargets)
    {
        CaseTarget clonedCaseTarget;
        rv = caseTarget.caseValue->Clone(cloneContext);
        if (!rv) return rv;
        clonedCaseTarget.caseValue = *rv;
        BasicBlock* bb = cloneContext.GetMappedBasicBlock(caseTarget.targetBlock);
        if (bb)
        {
            clonedCaseTarget.targetBlock = bb;
        }
        else
        {
            return Error("mapped basic block not found", caseTarget.targetBlock->Span(), cloneContext.GetContext());
        }
        clone->AddCaseTarget(clonedCaseTarget);
    }
    clone->AddToUses();
    return std::expected<Value*, int>(static_cast<Value*>(clone));
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
}

void SwitchInstruction::AddCaseTarget(const CaseTarget& caseTarget)
{
    caseTargets.push_back(caseTarget);
}

void SwitchInstruction::AddToUses()
{
    otava::intermediate::AddUser(this, cond);
    for (auto& caseTarget : caseTargets)
    {
        otava::intermediate::AddUser(this, caseTarget.caseValue);
    }
}

void SwitchInstruction::ReplaceValue(Value* use, Value* value)
{
    if (cond == use)
    {
        otava::intermediate::RemoveUser(this, cond);
        cond = value;
        otava::intermediate::AddUser(this, cond);
    }
    for (auto& caseTarget : caseTargets)
    {
        if (caseTarget.caseValue == use)
        {
            otava::intermediate::RemoveUser(this, caseTarget.caseValue);
            caseTarget.caseValue = value;
            otava::intermediate::AddUser(this, caseTarget.caseValue);
        }
    }
}

std::vector<Instruction*> SwitchInstruction::Uses() const
{
    std::vector<Instruction*> uses;
    AddToUsesVec(uses, cond);
    for (const CaseTarget& caseTarget : caseTargets)
    {
        AddToUsesVec(uses, caseTarget.caseValue);
    }
    return uses;
}

ValueInstruction::ValueInstruction(const soul::ast::Span& span_, RegValue* result_, OpCode opCode_) : Instruction(span_, result_->GetType(), opCode_), result(result_)
{
    result->SetInst(this);
}

ValueInstruction::~ValueInstruction()
{
    if (result)
    {
        result->SetInst(nullptr);
    }
}

void ValueInstruction::WriteResult(util::CodeFormatter& formatter)
{
    formatter.Write(util::Format(result->GetType()->Name(), 7, util::FormatWidth::min));
    formatter.Write(" " + result->ToString());
}

UnaryInstruction::UnaryInstruction(const soul::ast::Span& span_, RegValue* result_, Value* operand_, OpCode opCode_) :
    ValueInstruction(span_, result_, opCode_), operand(operand_)
{
}

void UnaryInstruction::AddToUses()
{
    otava::intermediate::AddUser(this, operand);
}

void UnaryInstruction::ReplaceValue(Value* use, Value* value)
{
    if (operand == use)
    {
        otava::intermediate::RemoveUser(this, operand);
        operand = value;
        otava::intermediate::AddUser(this, operand);
    }
}

std::vector<Instruction*> UnaryInstruction::Uses() const
{
    std::vector<Instruction*> uses;
    AddToUsesVec(uses, operand);
    return uses;
}

void UnaryInstruction::WriteArg(util::CodeFormatter& formatter)
{
    formatter.Write(operand->GetType()->Name());
    formatter.Write(" ");
    formatter.Write(operand->ToString());
}

NotInstruction::NotInstruction(const soul::ast::Span& span_, RegValue* result_, Value* operand_) : UnaryInstruction(span_, result_, operand_, OpCode::not_)
{
}

void NotInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<Value*, int> NotInstruction::Clone(CloneContext& cloneContext) const
{
    RegValue* result = cloneContext.CurrentFunction()->MakeRegValue(Span(), GetType(), Result()->Reg(), cloneContext.GetContext());
    std::expected<Value*, int> rv = Operand()->Clone(cloneContext);
    if (!rv) return rv;
    Value* clonedOperand = *rv;
    NotInstruction* clone = new NotInstruction(Span(), result, clonedOperand);
    clone->SetIndex(Index());
    clone->SetRegValueIndex(RegValueIndex());
    result->SetInst(clone);
    clone->AddToUses();
    return std::expected<Value*, int>(static_cast<Value*>(clone));
}

void NotInstruction::Write(util::CodeFormatter& formatter)
{
    WriteResult(formatter);
    formatter.Write(" = not ");
    WriteArg(formatter);
}

NegInstruction::NegInstruction(const soul::ast::Span& span_, RegValue* result_, Value* operand_) : UnaryInstruction(span_, result_, operand_, OpCode::neg)
{
}

void NegInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<Value*, int> NegInstruction::Clone(CloneContext& cloneContext) const
{
    RegValue* result = cloneContext.CurrentFunction()->MakeRegValue(Span(), GetType(), Result()->Reg(), cloneContext.GetContext());
    std::expected<Value*, int> rv = Operand()->Clone(cloneContext);
    if (!rv) return rv;
    Value* clonedOperand = *rv;
    NegInstruction* clone = new NegInstruction(Span(), result, clonedOperand);
    clone->SetIndex(Index());
    clone->SetRegValueIndex(RegValueIndex());
    result->SetInst(clone);
    clone->AddToUses();
    return std::expected<Value*, int>(static_cast<Value*>(clone));
}

void NegInstruction::Write(util::CodeFormatter& formatter)
{
    WriteResult(formatter);
    formatter.Write(" = neg ");
    WriteArg(formatter);
}

SignExtendInstruction::SignExtendInstruction(const soul::ast::Span& span_, RegValue* result_, Value* operand_) : UnaryInstruction(span_, result_, operand_, OpCode::signextend)
{
}

void SignExtendInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<Value*, int> SignExtendInstruction::Clone(CloneContext& cloneContext) const
{
    RegValue* result = cloneContext.CurrentFunction()->MakeRegValue(Span(), GetType(), Result()->Reg(), cloneContext.GetContext());
    std::expected<Value*, int> rv = Operand()->Clone(cloneContext);
    if (!rv) return rv;
    Value* clonedOperand = *rv;
    SignExtendInstruction* clone = new SignExtendInstruction(Span(), result, clonedOperand);
    clone->SetIndex(Index());
    clone->SetRegValueIndex(RegValueIndex());
    result->SetInst(clone);
    clone->AddToUses();
    return std::expected<Value*, int>(static_cast<Value*>(clone));
}

void SignExtendInstruction::Write(util::CodeFormatter& formatter)
{
    WriteResult(formatter);
    formatter.Write(" = signextend ");
    WriteArg(formatter);
}

ZeroExtendInstruction::ZeroExtendInstruction(const soul::ast::Span& span_, RegValue* result_, Value* operand_) : UnaryInstruction(span_, result_, operand_, OpCode::zeroextend)
{
}

void ZeroExtendInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<Value*, int> ZeroExtendInstruction::Clone(CloneContext& cloneContext) const
{
    RegValue* result = cloneContext.CurrentFunction()->MakeRegValue(Span(), GetType(), Result()->Reg(), cloneContext.GetContext());
    std::expected<Value*, int> rv = Operand()->Clone(cloneContext);
    if (!rv) return rv;
    Value* clonedOperand = *rv;
    ZeroExtendInstruction* clone = new ZeroExtendInstruction(Span(), result, clonedOperand);
    clone->SetIndex(Index());
    clone->SetRegValueIndex(RegValueIndex());
    result->SetInst(clone);
    clone->AddToUses();
    return std::expected<Value*, int>(static_cast<Value*>(clone));
}

void ZeroExtendInstruction::Write(util::CodeFormatter& formatter)
{
    WriteResult(formatter);
    formatter.Write(" = zeroextend ");
    WriteArg(formatter);
}

FloatingPointExtendInstruction::FloatingPointExtendInstruction(const soul::ast::Span& span_, RegValue* result_, Value* operand_) :
    UnaryInstruction(span_, result_, operand_, OpCode::fpextend)
{
}

void FloatingPointExtendInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<Value*, int> FloatingPointExtendInstruction::Clone(CloneContext& cloneContext) const
{
    RegValue* result = cloneContext.CurrentFunction()->MakeRegValue(Span(), GetType(), Result()->Reg(), cloneContext.GetContext());
    std::expected<Value*, int> rv = Operand()->Clone(cloneContext);
    if (!rv) return rv;
    Value* clonedOperand = *rv;
    FloatingPointExtendInstruction* clone = new FloatingPointExtendInstruction(Span(), result, clonedOperand);
    clone->SetIndex(Index());
    clone->SetRegValueIndex(RegValueIndex());
    result->SetInst(clone);
    clone->AddToUses();
    return std::expected<Value*, int>(static_cast<Value*>(clone));
}

void FloatingPointExtendInstruction::Write(util::CodeFormatter& formatter)
{
    WriteResult(formatter);
    formatter.Write(" = fpextend ");
    WriteArg(formatter);
}

TruncateInstruction::TruncateInstruction(const soul::ast::Span& span_, RegValue* result_, Value* operand_) : UnaryInstruction(span_, result_, operand_, OpCode::truncate)
{
}

void TruncateInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<Value*, int> TruncateInstruction::Clone(CloneContext& cloneContext) const
{
    RegValue* result = cloneContext.CurrentFunction()->MakeRegValue(Span(), GetType(), Result()->Reg(), cloneContext.GetContext());
    std::expected<Value*, int> rv = Operand()->Clone(cloneContext);
    if (!rv) return rv;
    Value* clonedOperand = *rv;
    TruncateInstruction* clone = new TruncateInstruction(Span(), result, clonedOperand);
    clone->SetIndex(Index());
    clone->SetRegValueIndex(RegValueIndex());
    result->SetInst(clone);
    clone->AddToUses();
    return std::expected<Value*, int>(static_cast<Value*>(clone));
}

void TruncateInstruction::Write(util::CodeFormatter& formatter)
{
    WriteResult(formatter);
    formatter.Write(" = truncate ");
    WriteArg(formatter);
}

BitcastInstruction::BitcastInstruction(const soul::ast::Span& span_, RegValue* result_, Value* operand_) : UnaryInstruction(span_, result_, operand_, OpCode::bitcast)
{
}

void BitcastInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<Value*, int> BitcastInstruction::Clone(CloneContext& cloneContext) const
{
    RegValue* result = cloneContext.CurrentFunction()->MakeRegValue(Span(), GetType(), Result()->Reg(), cloneContext.GetContext());
    std::expected<Value*, int> rv = Operand()->Clone(cloneContext);
    if (!rv) return rv;
    Value* clonedOperand = *rv;
    BitcastInstruction* clone = new BitcastInstruction(Span(), result, clonedOperand);
    clone->SetIndex(Index());
    clone->SetRegValueIndex(RegValueIndex());
    result->SetInst(clone);
    clone->AddToUses();
    return std::expected<Value*, int>(static_cast<Value*>(clone));
}

void BitcastInstruction::Write(util::CodeFormatter& formatter)
{
    WriteResult(formatter);
    formatter.Write(" = bitcast ");
    WriteArg(formatter);
}

IntToFloatInstruction::IntToFloatInstruction(const soul::ast::Span& span_, RegValue* result_, Value* operand_) : UnaryInstruction(span_, result_, operand_, OpCode::inttofloat)
{
}

void IntToFloatInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<Value*, int> IntToFloatInstruction::Clone(CloneContext& cloneContext) const
{
    RegValue* result = cloneContext.CurrentFunction()->MakeRegValue(Span(), GetType(), Result()->Reg(), cloneContext.GetContext());
    std::expected<Value*, int> rv = Operand()->Clone(cloneContext);
    if (!rv) return rv;
    Value* clonedOperand = *rv;
    IntToFloatInstruction* clone = new IntToFloatInstruction(Span(), result, clonedOperand);
    clone->SetIndex(Index());
    clone->SetRegValueIndex(RegValueIndex());
    result->SetInst(clone);
    clone->AddToUses();
    return std::expected<Value*, int>(static_cast<Value*>(clone));
}

void IntToFloatInstruction::Write(util::CodeFormatter& formatter)
{
    WriteResult(formatter);
    formatter.Write(" = inttofloat ");
    WriteArg(formatter);
}

FloatToIntInstruction::FloatToIntInstruction(const soul::ast::Span& span_, RegValue* result_, Value* operand_) : UnaryInstruction(span_, result_, operand_, OpCode::floattoint)
{
}

void FloatToIntInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<Value*, int> FloatToIntInstruction::Clone(CloneContext& cloneContext) const
{
    RegValue* result = cloneContext.CurrentFunction()->MakeRegValue(Span(), GetType(), Result()->Reg(), cloneContext.GetContext());
    std::expected<Value*, int> rv = Operand()->Clone(cloneContext);
    if (!rv) return rv;
    Value* clonedOperand = *rv;
    FloatToIntInstruction* clone = new FloatToIntInstruction(Span(), result, clonedOperand);
    clone->SetIndex(Index());
    clone->SetRegValueIndex(RegValueIndex());
    result->SetInst(clone);
    clone->AddToUses();
    return std::expected<Value*, int>(static_cast<Value*>(clone));
}

void FloatToIntInstruction::Write(util::CodeFormatter& formatter)
{
    WriteResult(formatter);
    formatter.Write(" = floattoint ");
    WriteArg(formatter);
}

IntToPtrInstruction::IntToPtrInstruction(const soul::ast::Span& span_, RegValue* result_, Value* operand_) : UnaryInstruction(span_, result_, operand_, OpCode::inttoptr)
{
}

void IntToPtrInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<Value*, int> IntToPtrInstruction::Clone(CloneContext& cloneContext) const
{
    RegValue* result = cloneContext.CurrentFunction()->MakeRegValue(Span(), GetType(), Result()->Reg(), cloneContext.GetContext());
    std::expected<Value*, int> rv = Operand()->Clone(cloneContext);
    if (!rv) return rv;
    Value* clonedOperand = *rv;
    IntToPtrInstruction* clone = new IntToPtrInstruction(Span(), result, clonedOperand);
    clone->SetIndex(Index());
    clone->SetRegValueIndex(RegValueIndex());
    result->SetInst(clone);
    clone->AddToUses();
    return std::expected<Value*, int>(static_cast<Value*>(clone));
}

void IntToPtrInstruction::Write(util::CodeFormatter& formatter)
{
    WriteResult(formatter);
    formatter.Write(" = inttoptr ");
    WriteArg(formatter);
}

PtrToIntInstruction::PtrToIntInstruction(const soul::ast::Span& span_, RegValue* result_, Value* operand_) : UnaryInstruction(span_, result_, operand_, OpCode::ptrtoint)
{
}

void PtrToIntInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<Value*, int> PtrToIntInstruction::Clone(CloneContext& cloneContext) const
{
    RegValue* result = cloneContext.CurrentFunction()->MakeRegValue(Span(), GetType(), Result()->Reg(), cloneContext.GetContext());
    std::expected<Value*, int> rv = Operand()->Clone(cloneContext);
    if (!rv) return rv;
    Value* clonedOperand = *rv;
    PtrToIntInstruction* clone = new PtrToIntInstruction(Span(), result, clonedOperand);
    clone->SetIndex(Index());
    clone->SetRegValueIndex(RegValueIndex());
    result->SetInst(clone);
    clone->AddToUses();
    return std::expected<Value*, int>(static_cast<Value*>(clone));
}

void PtrToIntInstruction::Write(util::CodeFormatter& formatter)
{
    WriteResult(formatter);
    formatter.Write(" = ptrtoint ");
    WriteArg(formatter);
}

BinaryInstruction::BinaryInstruction(const soul::ast::Span& span_, RegValue* result_, Value* left_, Value* right_, OpCode opCode_) :
    ValueInstruction(span_, result_, opCode_), left(left_), right(right_)
{
}

void BinaryInstruction::AddToUses()
{
    otava::intermediate::AddUser(this, left);
    otava::intermediate::AddUser(this, right);
}

void BinaryInstruction::ReplaceValue(Value* use, Value* value)
{
    if (left == use)
    {
        otava::intermediate::RemoveUser(this, left);
        left = value;
        otava::intermediate::AddUser(this, left);
    }
    if (right == use)
    {
        otava::intermediate::RemoveUser(this, right);
        right = value;
        otava::intermediate::AddUser(this, right);
    }
}

std::vector<Instruction*> BinaryInstruction::Uses() const
{
    std::vector<Instruction*> uses;
    AddToUsesVec(uses, left);
    AddToUsesVec(uses, right);
    return uses;
}

void BinaryInstruction::WriteArgs(util::CodeFormatter& formatter)
{
    formatter.Write(left->GetType()->Name());
    formatter.Write(" ");
    formatter.Write(left->ToString());
    formatter.Write(", ");
    formatter.Write(right->GetType()->Name());
    formatter.Write(" ");
    formatter.Write(right->ToString());
}

AddInstruction::AddInstruction(const soul::ast::Span& span_, RegValue* result_, Value* left_, Value* right_) : BinaryInstruction(span_, result_, left_, right_, OpCode::add)
{
}

void AddInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<Value*, int> AddInstruction::Clone(CloneContext& cloneContext) const
{
    RegValue* result = cloneContext.CurrentFunction()->MakeRegValue(Span(), GetType(), Result()->Reg(), cloneContext.GetContext());
    std::expected<Value*, int> rv = Left()->Clone(cloneContext);
    if (!rv) return rv;
    Value* clonedLeft = *rv;
    rv = Right()->Clone(cloneContext);
    if (!rv) return rv;
    Value* clonedRight = *rv;
    AddInstruction* clone = new AddInstruction(Span(), result, clonedLeft, clonedRight);
    clone->SetIndex(Index());
    clone->SetRegValueIndex(RegValueIndex());
    result->SetInst(clone);
    clone->AddToUses();
    return std::expected<Value*, int>(static_cast<Value*>(clone));
}

void AddInstruction::Write(util::CodeFormatter& formatter)
{
    WriteResult(formatter);
    formatter.Write(" = add ");
    WriteArgs(formatter);
}

SubInstruction::SubInstruction(const soul::ast::Span& span_, RegValue* result_, Value* left_, Value* right_) : BinaryInstruction(span_, result_, left_, right_, OpCode::sub)
{
}

void SubInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<Value*, int> SubInstruction::Clone(CloneContext& cloneContext) const
{
    RegValue* result = cloneContext.CurrentFunction()->MakeRegValue(Span(), GetType(), Result()->Reg(), cloneContext.GetContext());
    std::expected<Value*, int> rv = Left()->Clone(cloneContext);
    if (!rv) return rv;
    Value* clonedLeft = *rv;
    rv = Right()->Clone(cloneContext);
    if (!rv) return rv;
    Value* clonedRight = *rv;
    SubInstruction* clone = new SubInstruction(Span(), result, clonedLeft, clonedRight);
    clone->SetIndex(Index());
    clone->SetRegValueIndex(RegValueIndex());
    result->SetInst(clone);
    clone->AddToUses();
    return std::expected<Value*, int>(static_cast<Value*>(clone));
}

void SubInstruction::Write(util::CodeFormatter& formatter)
{
    WriteResult(formatter);
    formatter.Write(" = sub ");
    WriteArgs(formatter);
}

MulInstruction::MulInstruction(const soul::ast::Span& span_, RegValue* result_, Value* left_, Value* right_) : BinaryInstruction(span_, result_, left_, right_, OpCode::mul)
{
}

void MulInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<Value*, int> MulInstruction::Clone(CloneContext& cloneContext) const
{
    RegValue* result = cloneContext.CurrentFunction()->MakeRegValue(Span(), GetType(), Result()->Reg(), cloneContext.GetContext());
    std::expected<Value*, int> rv = Left()->Clone(cloneContext);
    if (!rv) return rv;
    Value* clonedLeft = *rv;
    rv = Right()->Clone(cloneContext);
    if (!rv) return rv;
    Value* clonedRight = *rv;
    MulInstruction* clone = new MulInstruction(Span(), result, clonedLeft, clonedRight);
    clone->SetIndex(Index());
    clone->SetRegValueIndex(RegValueIndex());
    result->SetInst(clone);
    clone->AddToUses();
    return std::expected<Value*, int>(static_cast<Value*>(clone));
}

void MulInstruction::Write(util::CodeFormatter& formatter)
{
    WriteResult(formatter);
    formatter.Write(" = mul ");
    WriteArgs(formatter);
}

DivInstruction::DivInstruction(const soul::ast::Span& span_, RegValue* result_, Value* left_, Value* right_) : BinaryInstruction(span_, result_, left_, right_, OpCode::div_)
{
}

void DivInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<Value*, int> DivInstruction::Clone(CloneContext& cloneContext) const
{
    RegValue* result = cloneContext.CurrentFunction()->MakeRegValue(Span(), GetType(), Result()->Reg(), cloneContext.GetContext());
    std::expected<Value*, int> rv = Left()->Clone(cloneContext);
    if (!rv) return rv;
    Value* clonedLeft = *rv;
    rv = Right()->Clone(cloneContext);
    if (!rv) return rv;
    Value* clonedRight = *rv;
    DivInstruction* clone = new DivInstruction(Span(), result, clonedLeft, clonedRight);
    clone->SetIndex(Index());
    clone->SetRegValueIndex(RegValueIndex());
    result->SetInst(clone);
    clone->AddToUses();
    return std::expected<Value*, int>(static_cast<Value*>(clone));
}

void DivInstruction::Write(util::CodeFormatter& formatter)
{
    WriteResult(formatter);
    formatter.Write(" = div ");
    WriteArgs(formatter);
}

ModInstruction::ModInstruction(const soul::ast::Span& span_, RegValue* result_, Value* left_, Value* right_) : BinaryInstruction(span_, result_, left_, right_, OpCode::mod)
{
}

void ModInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<Value*, int> ModInstruction::Clone(CloneContext& cloneContext) const
{
    RegValue* result = cloneContext.CurrentFunction()->MakeRegValue(Span(), GetType(), Result()->Reg(), cloneContext.GetContext());
    std::expected<Value*, int> rv = Left()->Clone(cloneContext);
    if (!rv) return rv;
    Value* clonedLeft = *rv;
    rv = Right()->Clone(cloneContext);
    if (!rv) return rv;
    Value* clonedRight = *rv;
    ModInstruction* clone = new ModInstruction(Span(), result, clonedLeft, clonedRight);
    clone->SetIndex(Index());
    clone->SetRegValueIndex(RegValueIndex());
    result->SetInst(clone);
    clone->AddToUses();
    return std::expected<Value*, int>(static_cast<Value*>(clone));
}

void ModInstruction::Write(util::CodeFormatter& formatter)
{
    WriteResult(formatter);
    formatter.Write(" = mod ");
    WriteArgs(formatter);
}

AndInstruction::AndInstruction(const soul::ast::Span& span_, RegValue* result_, Value* left_, Value* right_) : BinaryInstruction(span_, result_, left_, right_, OpCode::and_)
{
}

void AndInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<Value*, int> AndInstruction::Clone(CloneContext& cloneContext) const
{
    RegValue* result = cloneContext.CurrentFunction()->MakeRegValue(Span(), GetType(), Result()->Reg(), cloneContext.GetContext());
    std::expected<Value*, int> rv = Left()->Clone(cloneContext);
    if (!rv) return rv;
    Value* clonedLeft = *rv;
    rv = Right()->Clone(cloneContext);
    if (!rv) return rv;
    Value* clonedRight = *rv;
    AndInstruction* clone = new AndInstruction(Span(), result, clonedLeft, clonedRight);
    clone->SetIndex(Index());
    clone->SetRegValueIndex(RegValueIndex());
    result->SetInst(clone);
    clone->AddToUses();
    return std::expected<Value*, int>(static_cast<Value*>(clone));
}

void AndInstruction::Write(util::CodeFormatter& formatter)
{
    WriteResult(formatter);
    formatter.Write(" = and ");
    WriteArgs(formatter);
}

OrInstruction::OrInstruction(const soul::ast::Span& span_, RegValue* result_, Value* left_, Value* right_) : BinaryInstruction(span_, result_, left_, right_, OpCode::or_)
{
}

void OrInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<Value*, int> OrInstruction::Clone(CloneContext& cloneContext) const
{
    RegValue* result = cloneContext.CurrentFunction()->MakeRegValue(Span(), GetType(), Result()->Reg(), cloneContext.GetContext());
    std::expected<Value*, int> rv = Left()->Clone(cloneContext);
    if (!rv) return rv;
    Value* clonedLeft = *rv;
    rv = Right()->Clone(cloneContext);
    if (!rv) return rv;
    Value* clonedRight = *rv;
    OrInstruction* clone = new OrInstruction(Span(), result, clonedLeft, clonedRight);
    clone->SetIndex(Index());
    clone->SetRegValueIndex(RegValueIndex());
    result->SetInst(clone);
    clone->AddToUses();
    return std::expected<Value*, int>(static_cast<Value*>(clone));
}

void OrInstruction::Write(util::CodeFormatter& formatter)
{
    WriteResult(formatter);
    formatter.Write(" = or ");
    WriteArgs(formatter);
}

XorInstruction::XorInstruction(const soul::ast::Span& span_, RegValue* result_, Value* left_, Value* right_) : BinaryInstruction(span_, result_, left_, right_, OpCode::xor_)
{
}

void XorInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<Value*, int>XorInstruction::Clone(CloneContext& cloneContext) const
{
    RegValue* result = cloneContext.CurrentFunction()->MakeRegValue(Span(), GetType(), Result()->Reg(), cloneContext.GetContext());
    std::expected<Value*, int> rv = Left()->Clone(cloneContext);
    if (!rv) return rv;
    Value* clonedLeft = *rv;
    rv = Right()->Clone(cloneContext);
    if (!rv) return rv;
    Value* clonedRight = *rv;
    XorInstruction* clone = new XorInstruction(Span(), result, clonedLeft, clonedRight);
    clone->SetIndex(Index());
    clone->SetRegValueIndex(RegValueIndex());
    result->SetInst(clone);
    clone->AddToUses();
    return std::expected<Value*, int>(static_cast<Value*>(clone));
}

void XorInstruction::Write(util::CodeFormatter& formatter)
{
    WriteResult(formatter);
    formatter.Write(" = xor ");
    WriteArgs(formatter);
}

ShlInstruction::ShlInstruction(const soul::ast::Span& span_, RegValue* result_, Value* left_, Value* right_) : BinaryInstruction(span_, result_, left_, right_, OpCode::shl)
{
}

void ShlInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<Value*, int> ShlInstruction::Clone(CloneContext& cloneContext) const
{
    RegValue* result = cloneContext.CurrentFunction()->MakeRegValue(Span(), GetType(), Result()->Reg(), cloneContext.GetContext());
    std::expected<Value*, int> rv = Left()->Clone(cloneContext);
    if (!rv) return rv;
    Value* clonedLeft = *rv;
    rv = Right()->Clone(cloneContext);
    if (!rv) return rv;
    Value* clonedRight = *rv;
    ShlInstruction* clone = new ShlInstruction(Span(), result, clonedLeft, clonedRight);
    clone->SetIndex(Index());
    clone->SetRegValueIndex(RegValueIndex());
    result->SetInst(clone);
    clone->AddToUses();
    return std::expected<Value*, int>(static_cast<Value*>(clone));
}

void ShlInstruction::Write(util::CodeFormatter& formatter)
{
    WriteResult(formatter);
    formatter.Write(" = shl ");
    WriteArgs(formatter);
}

ShrInstruction::ShrInstruction(const soul::ast::Span& span_, RegValue* result_, Value* left_, Value* right_) : BinaryInstruction(span_, result_, left_, right_, OpCode::shr)
{
}

void ShrInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<Value*, int> ShrInstruction::Clone(CloneContext& cloneContext) const
{
    RegValue* result = cloneContext.CurrentFunction()->MakeRegValue(Span(), GetType(), Result()->Reg(), cloneContext.GetContext());
    std::expected<Value*, int> rv = Left()->Clone(cloneContext);
    if (!rv) return rv;
    Value* clonedLeft = *rv;
    rv = Right()->Clone(cloneContext);
    if (!rv) return rv;
    Value* clonedRight = *rv;
    ShrInstruction* clone = new ShrInstruction(Span(), result, clonedLeft, clonedRight);
    clone->SetIndex(Index());
    clone->SetRegValueIndex(RegValueIndex());
    result->SetInst(clone);
    clone->AddToUses();
    return std::expected<Value*, int>(static_cast<Value*>(clone));
}

void ShrInstruction::Write(util::CodeFormatter& formatter)
{
    WriteResult(formatter);
    formatter.Write(" = shr ");
    WriteArgs(formatter);
}

EqualInstruction::EqualInstruction(const soul::ast::Span& span_, RegValue* result_, Value* left_, Value* right_) : BinaryInstruction(span_, result_, left_, right_, OpCode::equal)
{
}

void EqualInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<Value*, int> EqualInstruction::Clone(CloneContext& cloneContext) const
{
    RegValue* result = cloneContext.CurrentFunction()->MakeRegValue(Span(), GetType(), Result()->Reg(), cloneContext.GetContext());
    std::expected<Value*, int> rv = Left()->Clone(cloneContext);
    if (!rv) return rv;
    Value* clonedLeft = *rv;
    rv = Right()->Clone(cloneContext);
    if (!rv) return rv;
    Value* clonedRight = *rv;
    EqualInstruction* clone = new EqualInstruction(Span(), result, clonedLeft, clonedRight);
    clone->SetIndex(Index());
    clone->SetRegValueIndex(RegValueIndex());
    result->SetInst(clone);
    clone->AddToUses();
    return std::expected<Value*, int>(static_cast<Value*>(clone));
}

void EqualInstruction::Write(util::CodeFormatter& formatter)
{
    WriteResult(formatter);
    formatter.Write(" = equal ");
    WriteArgs(formatter);
}

LessInstruction::LessInstruction(const soul::ast::Span& span_, RegValue* result_, Value* left_, Value* right_) : BinaryInstruction(span_, result_, left_, right_, OpCode::less)
{
}

void LessInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<Value*, int> LessInstruction::Clone(CloneContext& cloneContext) const
{
    RegValue* result = cloneContext.CurrentFunction()->MakeRegValue(Span(), GetType(), Result()->Reg(), cloneContext.GetContext());
    std::expected<Value*, int> rv = Left()->Clone(cloneContext);
    if (!rv) return rv;
    Value* clonedLeft = *rv;
    rv = Right()->Clone(cloneContext);
    if (!rv) return rv;
    Value* clonedRight = *rv;
    LessInstruction* clone = new LessInstruction(Span(), result, clonedLeft, clonedRight);
    clone->SetIndex(Index());
    clone->SetRegValueIndex(RegValueIndex());
    result->SetInst(clone);
    clone->AddToUses();
    return std::expected<Value*, int>(static_cast<Value*>(clone));
}

void LessInstruction::Write(util::CodeFormatter& formatter)
{
    WriteResult(formatter);
    formatter.Write(" = less ");
    WriteArgs(formatter);
}

ParamInstruction::ParamInstruction(const soul::ast::Span& span_, RegValue* result_) : ValueInstruction(span_, result_, OpCode::param)
{
}

void ParamInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<Value*, int> ParamInstruction::Clone(CloneContext& cloneContext) const
{
    RegValue* result = cloneContext.CurrentFunction()->MakeRegValue(Span(), GetType(), Result()->Reg(), cloneContext.GetContext());
    ParamInstruction* clone = new ParamInstruction(Span(), result);
    clone->SetIndex(Index());
    clone->SetRegValueIndex(RegValueIndex());
    result->SetInst(clone);
    clone->AddToUses();
    return std::expected<Value*, int>(static_cast<Value*>(clone));
}

void ParamInstruction::Write(util::CodeFormatter& formatter)
{
    WriteResult(formatter);
    formatter.Write(" = param");
}

LocalInstruction::LocalInstruction(const soul::ast::Span& span_, RegValue* result_, Type* localType_) : ValueInstruction(span_, result_, OpCode::local), localType(localType_)
{
}

void LocalInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<Value*, int> LocalInstruction::Clone(CloneContext& cloneContext) const
{
    RegValue* result = cloneContext.CurrentFunction()->MakeRegValue(Span(), GetType(), Result()->Reg(), cloneContext.GetContext());
    LocalInstruction* clone = new LocalInstruction(Span(), result, localType);
    clone->SetIndex(Index());
    clone->SetRegValueIndex(RegValueIndex());
    result->SetInst(clone);
    clone->AddToUses();
    return std::expected<Value*, int>(static_cast<Value*>(clone));
}

void LocalInstruction::Write(util::CodeFormatter& formatter)
{
    WriteResult(formatter);
    formatter.Write(" = local ");
    formatter.Write(localType->Name());
}

LoadInstruction::LoadInstruction(const soul::ast::Span& span_, RegValue* result_, Value* ptr_) : ValueInstruction(span_, result_, OpCode::load), ptr(ptr_)
{
}

void LoadInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<Value*, int> LoadInstruction::Clone(CloneContext& cloneContext) const
{
    RegValue* result = cloneContext.CurrentFunction()->MakeRegValue(Span(), GetType(), Result()->Reg(), cloneContext.GetContext());
    std::expected<Value*, int> rv = ptr->Clone(cloneContext);
    if (!rv) return rv;
    Value* clonedPtr = *rv;
    LoadInstruction* clone = new LoadInstruction(Span(), result, clonedPtr);
    clone->SetIndex(Index());
    clone->SetRegValueIndex(RegValueIndex());
    result->SetInst(clone);
    clone->AddToUses();
    return std::expected<Value*, int>(static_cast<Value*>(clone));
}

void LoadInstruction::Write(util::CodeFormatter& formatter)
{
    WriteResult(formatter);
    formatter.Write(" = load ");
    formatter.Write(ptr->GetType()->Name());
    formatter.Write(" ");
    formatter.Write(ptr->ToString());
}

void LoadInstruction::AddToUses()
{
    otava::intermediate::AddUser(this, ptr);
}

void LoadInstruction::ReplaceValue(Value* use, Value* value)
{
    if (ptr == use)
    {
        otava::intermediate::RemoveUser(this, ptr);
        ptr = value;
        otava::intermediate::AddUser(this, ptr);
    }
}

std::vector<Instruction*> LoadInstruction::Uses() const
{
    std::vector<Instruction*> uses;
    AddToUsesVec(uses, ptr);
    return uses;
}

ElemAddrInstruction::ElemAddrInstruction(const soul::ast::Span& span_, RegValue* result_, Value* ptr_, Value* indexValue_) :
    ValueInstruction(span_, result_, OpCode::elemaddr), ptr(ptr_), indexValue(indexValue_)
{
}

void ElemAddrInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<Value*, int> ElemAddrInstruction::Clone(CloneContext& cloneContext) const
{
    RegValue* result = cloneContext.CurrentFunction()->MakeRegValue(Span(), GetType(), Result()->Reg(), cloneContext.GetContext());
    std::expected<Value*, int> rv = Ptr()->Clone(cloneContext);
    if (!rv) return rv;
    Value* clonedPtr = *rv;
    rv = IndexValue()->Clone(cloneContext);
    if (!rv) return rv;
    Value* clonedIndex = *rv;
    ElemAddrInstruction* clone = new ElemAddrInstruction(Span(), result, clonedPtr, clonedIndex);
    clone->SetIndex(Index());
    clone->SetRegValueIndex(RegValueIndex());
    result->SetInst(clone);
    clone->AddToUses();
    return std::expected<Value*, int>(static_cast<Value*>(clone));
}

void ElemAddrInstruction::Write(util::CodeFormatter& formatter)
{
    WriteResult(formatter);
    formatter.Write(" = elemaddr ");
    formatter.Write(ptr->GetType()->Name());
    formatter.Write(" ");
    formatter.Write(ptr->ToString());
    formatter.Write(", ");
    formatter.Write(indexValue->GetType()->Name());
    formatter.Write(" ");
    formatter.Write(indexValue->ToString());
}

std::expected<ElemAddrKind, int> ElemAddrInstruction::GetElemAddrKind(Context* context) const
{
    if (ptr->GetType()->IsPointerType())
    {
        PointerType* ptrType = static_cast<PointerType*>(ptr->GetType());
        std::expected<Type*, int> rv = ptrType->RemovePointer(Span(), context);
        if (!rv) return std::unexpected<int>(rv.error());
        Type* pointeeType = *rv;
        if (pointeeType->IsArrayType())
        {
            return std::expected<ElemAddrKind, int>(ElemAddrKind::array);
        }
        else if (pointeeType->IsStructureType())
        {
            return std::expected<ElemAddrKind, int>(ElemAddrKind::structure);
        }
    }
    return Error("invalid elem addr kind", Span(), context);
}

void ElemAddrInstruction::AddToUses()
{
    otava::intermediate::AddUser(this, ptr);
    otava::intermediate::AddUser(this, indexValue);
}

void ElemAddrInstruction::ReplaceValue(Value* use, Value* value)
{
    if (ptr == use)
    {
        otava::intermediate::RemoveUser(this, ptr);
        ptr = value;
        otava::intermediate::AddUser(this, ptr);
    }
    if (indexValue == use)
    {
        otava::intermediate::RemoveUser(this, indexValue);
        indexValue = value;
        otava::intermediate::AddUser(this, indexValue);
    }
}

std::vector<Instruction*> ElemAddrInstruction::Uses() const
{
    std::vector<Instruction*> uses;
    AddToUsesVec(uses, ptr);
    AddToUsesVec(uses, indexValue);
    return uses;
}

PtrOffsetInstruction::PtrOffsetInstruction(const soul::ast::Span& span_, RegValue* result_, Value* ptr_, Value* offset_) :
    ValueInstruction(span_, result_, OpCode::ptroffset), ptr(ptr_), offset(offset_)
{
}

void PtrOffsetInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<Value*, int> PtrOffsetInstruction::Clone(CloneContext& cloneContext) const
{
    RegValue* result = cloneContext.CurrentFunction()->MakeRegValue(Span(), GetType(), Result()->Reg(), cloneContext.GetContext());
    std::expected<Value*, int> rv = Ptr()->Clone(cloneContext);
    if (!rv) return rv;
    Value* clonedPtr = *rv;
    rv = offset->Clone(cloneContext);
    if (!rv) return rv;
    Value* clonedOffset = *rv;
    PtrOffsetInstruction* clone = new PtrOffsetInstruction(Span(), result, clonedPtr, clonedOffset);
    clone->SetIndex(Index());
    clone->SetRegValueIndex(RegValueIndex());
    result->SetInst(clone);
    clone->AddToUses();
    return std::expected<Value*, int>(static_cast<Value*>(clone));
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
}

void PtrOffsetInstruction::AddToUses()
{
    otava::intermediate::AddUser(this, ptr);
    otava::intermediate::AddUser(this, offset);
}

void PtrOffsetInstruction::ReplaceValue(Value* use, Value* value)
{
    if (ptr == use)
    {
        otava::intermediate::RemoveUser(this, ptr);
        ptr = value;
        otava::intermediate::AddUser(this, ptr);
    }
    if (offset == use)
    {
        otava::intermediate::RemoveUser(this, offset);
        offset = value;
        otava::intermediate::AddUser(this, offset);
    }
}

std::vector<Instruction*> PtrOffsetInstruction::Uses() const
{
    std::vector<Instruction*> uses;
    AddToUsesVec(uses, ptr);
    AddToUsesVec(uses, offset);
    return uses;
}

PtrDiffInstruction::PtrDiffInstruction(const soul::ast::Span& span_, RegValue* result_, Value* leftPtr_, Value* rightPtr_) :
    ValueInstruction(span_, result_, OpCode::ptrdiff), leftPtr(leftPtr_), rightPtr(rightPtr_)
{
}

void PtrDiffInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<Value*, int> PtrDiffInstruction::Clone(CloneContext& cloneContext) const
{
    RegValue* result = cloneContext.CurrentFunction()->MakeRegValue(Span(), GetType(), Result()->Reg(), cloneContext.GetContext());
    std::expected<Value*, int> rv = leftPtr->Clone(cloneContext);
    if (!rv) return rv;
    Value* clonedLeft = *rv;
    rv = rightPtr->Clone(cloneContext);
    if (!rv) return rv;
    Value* clonedRight = *rv;
    PtrDiffInstruction* clone = new PtrDiffInstruction(Span(), result, clonedLeft, clonedRight);
    clone->SetIndex(Index());
    clone->SetRegValueIndex(RegValueIndex());
    result->SetInst(clone);
    clone->AddToUses();
    return std::expected<Value*, int>(static_cast<Value*>(clone));
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
}

void PtrDiffInstruction::AddToUses()
{
    otava::intermediate::AddUser(this, leftPtr);
    otava::intermediate::AddUser(this, rightPtr);
}

void PtrDiffInstruction::ReplaceValue(Value* use, Value* value)
{
    if (leftPtr == use)
    {
        otava::intermediate::RemoveUser(this, leftPtr);
        leftPtr = value;
        otava::intermediate::AddUser(this, leftPtr);
    }
    if (rightPtr == use)
    {
        otava::intermediate::RemoveUser(this, rightPtr);
        rightPtr = value;
        otava::intermediate::AddUser(this, rightPtr);
    }
}

std::vector<Instruction*> PtrDiffInstruction::Uses() const
{
    std::vector<Instruction*> uses;
    AddToUsesVec(uses, leftPtr);
    AddToUsesVec(uses, rightPtr);
    return uses;
}

FunctionCallInstruction::FunctionCallInstruction(const soul::ast::Span& span_, RegValue* result_, Value* callee_) :
    ValueInstruction(span_, result_, OpCode::function_call), callee(callee_)
{
}

void FunctionCallInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<Value*, int> FunctionCallInstruction::Clone(CloneContext& cloneContext) const
{
    RegValue* result = cloneContext.CurrentFunction()->MakeRegValue(Span(), GetType(), Result()->Reg(), cloneContext.GetContext());
    std::expected<Value*, int> rv = callee->Clone(cloneContext);
    if (!rv) return rv;
    Value* clonedCallee = *rv;
    FunctionCallInstruction* clone = new FunctionCallInstruction(Span(), result, clonedCallee);
    clone->SetIndex(Index());
    clone->SetRegValueIndex(RegValueIndex());
    result->SetInst(clone);
    std::vector<Value*> clonedArgs;
    for (Value* arg : args)
    {
        rv = arg->Clone(cloneContext);
        if (!rv) return rv;
        Value* clonedArg = *rv;
        clonedArgs.push_back(clonedArg);
    }
    clone->SetArgs(std::move(clonedArgs));
    clone->AddToUses();
    return std::expected<Value*, int>(static_cast<Value*>(clone));
}

void FunctionCallInstruction::SetArgs(std::vector<Value*>&& args_)
{
    args = std::move(args_);
}

Function* FunctionCallInstruction::CalleeFn() const
{
    if (callee->IsSymbolValue())
    {
        SymbolValue* symbolValue = static_cast<SymbolValue*>(callee);
        return symbolValue->GetFunction();
    }
    return nullptr;
}

void FunctionCallInstruction::AddToUses()
{
    otava::intermediate::AddUser(this, callee);
    for (Value* arg : args)
    {
        otava::intermediate::AddUser(this, arg);
    }
}

void FunctionCallInstruction::ReplaceValue(Value* use, Value* value)
{
    if (callee == use)
    {
        otava::intermediate::RemoveUser(this, callee);
        callee = value;
        otava::intermediate::AddUser(this, callee);
    }
    for (Value* arg : args)
    {
        if (arg == use)
        {
            otava::intermediate::RemoveUser(this, arg);
            arg = value;
            otava::intermediate::AddUser(this, arg);
        }
    }
}

void FunctionCallInstruction::Write(util::CodeFormatter& formatter)
{
    WriteResult(formatter);
    formatter.Write(" = call ");
    formatter.Write(callee->GetType()->Name());
    formatter.Write(" ");
    formatter.Write(callee->ToString());
}

std::vector<Instruction*> FunctionCallInstruction::Uses() const
{
    std::vector<Instruction*> uses;
    AddToUsesVec(uses, callee);
    for (Value* arg : args)
    {
        AddToUsesVec(uses, arg);
    }
    return uses;
}

BlockValue::BlockValue(Value* value_, BasicBlock* block_) : value(value_), blockId(block_->Id()), block(block_)
{
}

NoOperationInstruction::NoOperationInstruction(const soul::ast::Span& span_) : Instruction(span_, nullptr, OpCode::nop)
{
}

void NoOperationInstruction::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<Value*, int> NoOperationInstruction::Clone(CloneContext& cloneContext) const
{
    NoOperationInstruction* clone = new NoOperationInstruction(Span());
    clone->SetIndex(Index());
    clone->SetRegValueIndex(RegValueIndex());
    clone->AddToUses();
    return std::expected<Value*, int>(static_cast<Value*>(clone));
}

void NoOperationInstruction::Write(util::CodeFormatter& formatter)
{
    formatter.Write("nop");
}

BasicBlock::BasicBlock(const soul::ast::Span& span_, std::int32_t id_) : util::Component(), span(span_), id(id_), instructions(this)
{
}

std::expected<bool, int> BasicBlock::Check()
{
    Instruction* inst = FirstInstruction();
    while (inst)
    {
        std::expected<bool, int> rv = inst->Check();
        if (!rv) return rv;
        inst = inst->Next();
    }
    return std::expected<bool, int>(true);
}

void BasicBlock::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

BasicBlock* BasicBlock::Clone(CloneContext& cloneContext) const
{
    BasicBlock* clone = new BasicBlock(Span(), id);
    cloneContext.MapBasicBlock(const_cast<BasicBlock*>(this), clone);
    return clone;
}

std::expected<bool, int> BasicBlock::CloneInstructions(CloneContext& cloneContext, BasicBlock* to)
{
    Instruction* inst = FirstInstruction();
    while (inst)
    {
        std::expected<Value*, int> rv = inst->Clone(cloneContext);
        if (!rv) return std::unexpected<int>(rv.error());
        Instruction* clonedInst = static_cast<Instruction*>(*rv);
        cloneContext.MapInstruction(inst, clonedInst);
        to->DoAddInstruction(clonedInst);
        inst = inst->Next();
    }
    return std::expected<bool, int>(true);
}

void BasicBlock::VisitInstructions(Visitor& visitor)
{
    Instruction* inst = FirstInstruction();
    while (inst)
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

bool BasicBlock::IsLast() const
{
    Function* fn = Parent();
    return this == fn->LastBasicBlock();
}

bool BasicBlock::ContainsOnlyNops()
{
    Instruction* inst = FirstInstruction();
    while (inst && !inst->IsTerminator())
    {
        if (!inst->IsNopInstruction())
        {
            return false;
        }
        inst = inst->Next();
    }
    return true;
}

void BasicBlock::DoAddInstruction(Instruction* instruction, bool mapInstruction)
{
    instructions.AddChild(instruction);
    Function* fn = Parent();
    int nextRegNumber = fn->NextRegNumber();
    if (mapInstruction && instruction->IsValueInstruction())
    {
        ValueInstruction* valueInstruction = static_cast<ValueInstruction*>(instruction);
        Context* context = fn->Parent()->GetContext();
        fn->MapInstruction(valueInstruction->Result()->Reg(), valueInstruction, context);
        nextRegNumber = std::max(valueInstruction->Result()->Reg() + 1, nextRegNumber);
    }
    fn->SetNextRegNumber(nextRegNumber);
}

void BasicBlock::DoAddInstruction(Instruction* instruction)
{
    DoAddInstruction(instruction, true);
}

std::unique_ptr<Instruction> BasicBlock::RemoveInstruction(Instruction* instruction)
{
    return std::unique_ptr<Instruction>(static_cast<Instruction*>(instructions.RemoveChild(instruction).release()));
}

void BasicBlock::InsertInstructionAfter(Instruction* instruction, Instruction* after)
{
    instructions.InsertAfter(instruction, after);
    Function* fn = Parent();
    int nextRegNumber = fn->NextRegNumber();
    if (instruction->IsValueInstruction())
    {
        ValueInstruction* valueInstruction = static_cast<ValueInstruction*>(instruction);
        Context* context = fn->Parent()->GetContext();
        fn->MapInstruction(valueInstruction->Result()->Reg(), valueInstruction, context);
        nextRegNumber = std::max(valueInstruction->Result()->Reg() + 1, nextRegNumber);
    }
    fn->SetNextRegNumber(nextRegNumber);
}

void BasicBlock::InsertFront(Instruction* instruction)
{
    Function* fn = Parent();
    int nextRegNumber = fn->NextRegNumber();
    if (instructions.IsEmpty())
    {
        instructions.AddChild(instruction);
    }
    else
    {
        instructions.InsertBefore(instruction, instructions.FirstChild());
    }
    if (instruction->IsValueInstruction())
    {
        ValueInstruction* valueInstruction = static_cast<ValueInstruction*>(instruction);
        Context* context = fn->Parent()->GetContext();
        fn->MapInstruction(valueInstruction->Result()->Reg(), valueInstruction, context);
        nextRegNumber = std::max(valueInstruction->Result()->Reg() + 1, nextRegNumber);
    }
    fn->SetNextRegNumber(nextRegNumber);
}

BasicBlock* BasicBlock::SplitAfter(Instruction* instruction)
{
    Function* fn = Parent();
    Context* context = fn->Parent()->GetContext();
    std::unique_ptr<BasicBlock> newBB(new BasicBlock(Span(), fn->GetNextBasicBlockNumber()));
    BasicBlock* nbb = newBB.get();
    fn->InsertBasicBlockAfter(newBB.release(), instruction->Parent());
    instruction = instruction->Next();
    while (instruction)
    {
        Instruction* next = instruction->Next();
        std::unique_ptr<Instruction> removedInst = instruction->Parent()->RemoveInstruction(instruction);
        if (removedInst->IsValueInstruction())
        {
            ValueInstruction* valueInst = static_cast<ValueInstruction*>(removedInst.get());
            valueInst->SetRegValueIndex(fn->GetNextRegNumber());
            valueInst->Result()->SetReg(valueInst->RegValueIndex());
            fn->MapRegValue(valueInst->Result());
        }
        nbb->DoAddInstruction(removedInst.release(), false);
        instruction = next;
    }
    return nbb;
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

Function* BasicBlock::Parent() const
{
    return static_cast<Function*>(GetContainer()->Parent());
}

Instruction* BasicBlock::Leader() const
{
    Instruction* leader = const_cast<BasicBlock*>(this)->FirstInstruction();
    while (leader && leader->IsNopInstruction())
    {
        leader = leader->Next();
    }
    return leader;
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
    bool first = true;
    Instruction* inst = FirstInstruction();
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

Function::Function(const soul::ast::Span& span_, FunctionType* type_, const std::string& name_, bool once_, bool definition_, bool createEntry,
    MetadataRef* metadataRef_, Context* context) :
    Value(span_, ValueKind::function, type_),
    util::Component(),
    flags(FunctionFlags::none), span(span_), type(type_), name(name_), metadataRef(metadataRef_), 
    basicBlocks(this), nextRegNumber(0), nextBBNumber(0), mdId(-1)
{
    SetContainer(context->GetCode().Functions());
    if (createEntry)
    {
        CreateEntry(context);
    }
    if (once_)
    {
        SetFlag(FunctionFlags::linkOnce);
    }
    if (definition_)
    {
        SetFlag(FunctionFlags::defined);
    }
}

void Function::CreateEntry(Context* context)
{
    if (entryBlock) return;
    entryBlock.reset(new BasicBlock(Span(), nextBBNumber++));
    entryBlock->SetContainer(&basicBlocks);
    std::int32_t n = type->ParamTypeRefs().size();
    for (std::int32_t index = 0; index < n; ++index)
    {
        const TypeRef& paramTypeRef = type->ParamTypeRefs()[index];
        RegValue* regValue = new RegValue(Span(), paramTypeRef.GetType(), nextRegNumber++);
        Instruction* paramInst = new ParamInstruction(Span(), regValue);
        context->AddLineInfo(paramInst);
        entryBlock->DoAddInstruction(paramInst);
        params.push_back(paramInst);
    }
}

std::expected<bool, int> Function::Check()
{
    BasicBlock* bb = FirstBasicBlock();
    while (bb)
    {
        std::expected<bool, int> rv = bb->Check();
        if (!rv) return rv;
        bb = bb->Next();
    }
    return std::expected<bool, int>(true);
}

void Function::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<Function*, int> Function::Clone() const
{
    Code* code = Parent();
    Function* clone = new Function(Span(), type, name, IsLinkOnce(), IsDefined(), false, metadataRef, Parent()->GetContext());
    clone->SetMdId(mdId);
    std::string fullName = ResolveFullName();
    if (!fullName.empty())
    {
        clone->SetComment(fullName);
    }
    clone->SetContainer(code->Functions());
    CloneContext cloneContext;
    cloneContext.SetContext(code->GetContext());
    cloneContext.SetCurrentFunction(clone);
    BasicBlock* bb = const_cast<Function*>(this)->FirstBasicBlock();
    while (bb)
    {
        BasicBlock* clonedBB = bb->Clone(cloneContext);
        clone->AddBasicBlock(clonedBB);
        bb = bb->Next();
    }
    bb = const_cast<Function*>(this)->FirstBasicBlock();
    while (bb)
    {
        BasicBlock* clonedBB = cloneContext.GetMappedBasicBlock(bb);
        if (clonedBB)
        {
            std::expected<bool, int> rv = bb->CloneInstructions(cloneContext, clonedBB);
            if (!rv) return std::unexpected<int>(rv.error());
        }
        else
        {
            return Error("mapped basic block not found", bb->Span(), code->GetContext());
        }
        bb = bb->Next();
    }
    for (const auto& instRegValuePair : cloneContext.UnmappedInstructions())
    {
        Instruction* inst = instRegValuePair.first;
        RegValue* regValue = instRegValuePair.second;
        Instruction* mappedInst = cloneContext.GetMappedInstruction(inst);
        if (mappedInst)
        {
            regValue->SetInst(mappedInst);
        }
        else
        {
            return Error("mapped instruction not found", inst->Span(), code->GetContext());
        }
    }
    return std::expected<Function*, int>(clone);
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
    return static_cast<Code*>(GetContainer()->Parent());
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

BasicBlock* Function::CreateBasicBlock()
{
    if (!FirstBasicBlock())
    {
        BasicBlock* eb = entryBlock.release();
        AddBasicBlock(eb);
        basicBlockMap[eb->Id()] = eb;
        return eb;
    }
    BasicBlock* bb = new BasicBlock(soul::ast::Span(), nextBBNumber++);
    AddBasicBlock(bb);
    basicBlockMap[bb->Id()] = bb;
    return bb;
}

std::expected<BasicBlock*, int> Function::AddBasicBlock(const soul::ast::Span& span, std::int32_t id, Context* context)
{
    BasicBlock* prev = GetBasicBlock(id);
    if (prev)
    {
        return Error("error adding basic block: basic block id not unique", span, context, prev->Span());
    }
    BasicBlock* basicBlock = new BasicBlock(span, id);
    basicBlocks.AddChild(basicBlock);
    basicBlockMap[id] = basicBlock;
    nextBBNumber = std::max(id + 1, nextBBNumber);
    return std::expected<BasicBlock*, int>(basicBlock);
}

void Function::AddBasicBlock(BasicBlock* basicBlock)
{
    basicBlocks.AddChild(basicBlock);
    basicBlockMap[basicBlock->Id()] = basicBlock;
    nextBBNumber = std::max(basicBlock->Id() + 1, nextBBNumber);
}

void Function::InsertBasicBlockBefore(BasicBlock* basicBlockToInsert, BasicBlock* before)
{
    basicBlocks.InsertBefore(basicBlockToInsert, before);
    basicBlockMap[basicBlockToInsert->Id()] = basicBlockToInsert;
    nextBBNumber = std::max(basicBlockToInsert->Id() + 1, nextBBNumber);
}

void Function::InsertBasicBlockAfter(BasicBlock* basicBlockToInsert, BasicBlock* after)
{
    basicBlocks.InsertAfter(basicBlockToInsert, after);
    basicBlockMap[basicBlockToInsert->Id()] = basicBlockToInsert;
    nextBBNumber = std::max(basicBlockToInsert->Id() + 1, nextBBNumber);
}

std::unique_ptr<BasicBlock> Function::RemoveBasicBlock(BasicBlock* block)
{
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
    return std::unique_ptr<BasicBlock>(static_cast<BasicBlock*>(basicBlocks.RemoveChild(block).release()));
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

std::expected<RegValue*, int> Function::GetRegRef(const soul::ast::Span& span, Type* type, std::int32_t reg, Context* context) const
{
    RegValue* regValue = GetRegValue(reg);
    if (regValue)
    {
        if (regValue->GetType() == type)
        {
            return std::expected<RegValue*, int>(regValue);
        }
        else
        {
            return Error("error referencing register value " + std::to_string(reg) + ": type conflict", span, context, regValue->Span());
        }
    }
    else
    {
        return Error("error referencing register: register " + std::to_string(reg) + " not found", span, context);
    }
}

RegValue* Function::MakeRegValue(const soul::ast::Span& span, Type* type, std::int32_t reg, Context* context)
{
    RegValue* regValue = new RegValue(span, type, reg);
    regValues.push_back(std::unique_ptr<RegValue>(regValue));
    regValueMap[reg] = regValue;
    return regValue;
}

RegValue* Function::MakeNextRegValue(const soul::ast::Span& span, Type* type, Context* context)
{
    return MakeRegValue(span, type, GetNextRegNumber(), context);
}

void Function::MapRegValue(RegValue* regValue)
{
    regValueMap[regValue->Reg()] = regValue;
}

void Function::RemoveRegValue(std::int32_t reg)
{
    regValueMap.erase(reg);
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

std::expected<bool, int> Function::AddEntryAndExitBlocks()
{
    if (basicBlocks.IsEmpty())
    {
        return Error("error adding entry and exit blocks: function '" + Name() + "' has no basic blocks", Span(), Parent()->GetContext());
    }
    BasicBlock* prevEntryBlock = GetBasicBlock(entryBlockId);
    if (prevEntryBlock)
    {
        return Error("error adding entry and exit blocks: function '" + Name() + "' has already an entry block", Span(), Parent()->GetContext());
    }
    BasicBlock* prevExitBlock = GetBasicBlock(exitBlockId);
    if (prevExitBlock)
    {
        return Error("error adding entry and exit blocks: function '" + Name() + "' has already an exit block", Span(), Parent()->GetContext());
    }
    if (RetBlocks().empty())
    {
        return Error("error adding entry and exit blocks: function '" + Name() + "' has no ret blocks", Span(), Parent()->GetContext());
    }
    BasicBlock* firstBasicBlock = FirstBasicBlock();
    BasicBlock* entryBlock = new BasicBlock(Span(), entryBlockId);
    basicBlockMap[entryBlock->Id()] = entryBlock;
    entryBlock->AddSuccessor(firstBasicBlock);
    firstBasicBlock->AddPredecessor(entryBlock);
    basicBlocks.InsertBefore(entryBlock, firstBasicBlock);
    BasicBlock* exitBlock = new BasicBlock(Span(), exitBlockId);
    for (BasicBlock* retBlock : RetBlocks())
    {
        retBlock->AddSuccessor(exitBlock);
        exitBlock->AddPredecessor(retBlock);
    }
    basicBlocks.AddChild(exitBlock);
    return std::expected<bool, int>(true);
}

std::expected<bool, int> Function::RemoveEntryAndExitBlocks()
{
    BasicBlock* entryBlock = GetBasicBlock(entryBlockId);
    if (!entryBlock)
    {
        return Error("error removing entry and exit blocks: function '" + Name() + "' has no entry block", Span(), Parent()->GetContext());
    }
    BasicBlock* exitBlock = GetBasicBlock(exitBlockId);
    if (!exitBlock)
    {
        return Error("error removing entry and exit blocks: function '" + Name() + "' has no exit block", Span(), Parent()->GetContext());
    }
    BasicBlock* firstBasicBlock = entryBlock->Next();
    if (!firstBasicBlock)
    {
        return Error("error removing entry and exit blocks: function '" + Name() + "' has no basic blocks other than entry and exit blocks", Span(), Parent()->GetContext());
    }
    if (!firstBasicBlock->RemovePredecessor(entryBlock))
    {
        return Error("error removing entry and exit blocks: function '" + Name() + "' old first block does not have the entry block as a predecessor", Span(), Parent()->GetContext());
    }
    basicBlocks.RemoveChild(entryBlock);
    basicBlockMap.erase(entryBlockId);
    for (BasicBlock* retBlock : RetBlocks())
    {
        if (!retBlock->RemoveSuccessor(exitBlock))
        {
            return Error("error removing entry and exit blocks: function '" + Name() + "' ret block does not have the exit block as a successor", Span(), Parent()->GetContext());
        }
    }
    basicBlocks.RemoveChild(exitBlock);
    basicBlockMap.erase(exitBlockId);
    return std::expected<bool, int>(true);
}

std::expected<Value*, int> Function::GetParam(int index) const
{
    if (index >= 0 && index < params.size())
    {
        return std::expected<Value*, int>(params[index]);
    }
    else
    {
        return Error("invalid param index", Span(), Parent()->GetContext());
    }
}

void Function::SetNumbers()
{
    Context* context = Parent()->GetContext();
    basicBlockMap.clear();
    regValueMap.clear();
    instructionMap.clear();
    nextBBNumber = 0;
    BasicBlock* bb = FirstBasicBlock();
    while (bb)
    {
        bb->SetId(nextBBNumber++);
        basicBlockMap[bb->Id()] = bb;
        bb = bb->Next();
    }
    int instructionIndex = 0;
    nextRegNumber = 0;
    bb = FirstBasicBlock();
    while (bb)
    {
        Instruction* inst = bb->FirstInstruction();
        while (inst)
        {
            inst->SetIndex(instructionIndex++);
            if (inst->IsValueInstruction())
            {
                ValueInstruction* valueInst = static_cast<ValueInstruction*>(inst);
                valueInst->SetRegValueIndex(nextRegNumber++);
                valueInst->Result()->SetReg(valueInst->RegValueIndex());
                MapRegValue(valueInst->Result());
                MapInstruction(valueInst->RegValueIndex(), valueInst, context);
            }
            inst = inst->Next();
        }
        bb = bb->Next();
    }
}

void Function::MoveRegValues(Function* toFunction)
{
    for (auto& regValue : regValues)
    {
        if (!regValue->Inst()) continue;
        regValue->SetReg(toFunction->GetNextRegNumber());
        toFunction->MapRegValue(regValue.get());
        toFunction->regValues.push_back(std::move(regValue));
    }
}

void Function::SetComment(const std::string& comment_)
{
    comment = comment_;
}

std::string Function::ResolveFullName() const
{
    if (metadataRef)
    {
        MetadataStruct* metadataStruct = metadataRef->GetMetadataStruct();
        if (metadataStruct)
        {
            MetadataItem* metadataItem = metadataStruct->GetItem("fullName");
            if (metadataItem)
            {
                if (metadataItem->IsMetadataString())
                {
                    MetadataString* metadataString = static_cast<MetadataString*>(metadataItem);
                    return metadataString->GetValue();
                }
            }
        }
    }
    return std::string();
}

std::expected<bool, int> Function::Write(util::CodeFormatter& formatter)
{
    if (metadataRef)
    {
        SetComment(ResolveFullName());
    }
    if (!comment.empty())
    {
        formatter.WriteLine("// " + comment);
        formatter.WriteLine();
    }
    if (basicBlocks.IsEmpty())
    {
        formatter.Write("extern ");
    }
    else if (IsInline())
    {
        formatter.Write("inline ");
    }
    if (IsLinkOnce())
    {
        formatter.Write("link_once ");
    }
    Context* context = Parent()->GetContext();
    std::expected<Type*, int> rv = type->AddPointer(context);
    if (!rv) return std::unexpected<int>(rv.error());
    Type* ptrType = *rv;
    if (metadataRef)
    {
        mdId = metadataRef->NodeId();
    }
    std::string mdIdStr;
    if (mdId != -1)
    {
        mdIdStr.append(" !").append(std::to_string(mdId));
    }
    formatter.WriteLine("function " + ptrType->Name() + " " + name + mdIdStr);
    if (basicBlocks.IsEmpty())
    {
        return std::expected<bool, int>(true);
    }
    SetNumbers();
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
    return std::expected<bool, int>(true);
}

Code::Code() : util::Component(), context(nullptr), currentFunction(nullptr), functions(this), totalFunctions(0)
{
}

void Code::SetCurrentFunction(Function* function)
{
    currentFunction = function;
}

std::expected<Function*, int> Code::GetOrInsertFunction(const std::string& functionId, FunctionType* functionType)
{
    Function* function = GetFunction(functionId);
    if (function)
    {
        if (function->GetType() != functionType)
        {
            return Error("function type conflicts with earlier declaration", soul::ast::Span(), context);
        }
        else
        {
            return std::expected<Function*, int>(function);
        }
    }
    else
    {
        return AddFunctionDeclaration(soul::ast::Span(), functionType, functionId);
    }
}

Function* Code::GetFunction(const std::string& functionId) const
{
    auto it = functionMap.find(functionId);
    if (it != functionMap.cend())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}

std::expected<Function*, int> Code::AddFunctionDefinition(const soul::ast::Span& span, FunctionType* functionType, const std::string& functionId, 
    bool inline_, bool linkOnce, bool createEntry, MetadataRef* metadataRef)
{
    Function* prev = GetFunction(functionId);
    if (prev)
    {
        if (prev->IsDefined())
        {
            return Error("error adding function '" + functionId + "': function id not unique", span, context, prev->Span());
        }
        else
        {
            if (prev->GetType() != functionType)
            {
                return Error("error adding function '" + functionId + "': type '" + functionType->Name() + 
                    "' conflicts with earlier declaration (" + prev->GetType()->Name() + ")", span, context, prev->Span());
            }
            prev->SetDefined();
            prev->CreateEntry(context);
            return std::expected<Function*, int>(prev);
        }
    }
    Function* function = new Function(span, functionType, functionId, linkOnce, true, createEntry, metadataRef, context);
    if (inline_)
    {
        function->SetInline();
    }
    if (linkOnce)
    {
        function->SetLinkOnce();
    }
    functions.AddChild(function);
    functionMap[function->Name()] = function;
    return std::expected<Function*, int>(function);
}

std::expected<Function*, int> Code::AddFunctionDeclaration(const soul::ast::Span& span, FunctionType* functionType, const std::string& functionId)
{
    Function* prev = GetFunction(functionId);
    if (prev)
    {
        if (prev->GetType() != functionType)
        {
            return Error("error adding function declaration '" + functionId + "': type '" + functionType->Name() + "' conflicts with earlier declaration", span, context, prev->Span());
        }
        return prev;
    }
    Function* function = new Function(span, functionType, functionId, false, false, false, nullptr, context);
    functions.AddChild(function);
    functionMap[function->Name()] = function;
    return std::expected<Function*, int>(function);
}

void Code::VisitFunctions(Visitor& visitor)
{
    totalFunctions = 0;
    Function* function = FirstFunction();
    while (function)
    {
        function->Accept(visitor);
        if (!visitor) return;
        ++totalFunctions;
        function = function->Next();
    }
}

} // otava::intermediate
