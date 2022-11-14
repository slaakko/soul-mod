// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.intermediate.code.generator;

import otava.intermediate.code;
import otava.intermediate.instruction;
import otava.intermediate.context;
import otava.intermediate.type;
import otava.intermediate.basic.block;
import otava.intermediate.value;
import otava.intermediate.data;
import otava.assembly.expr;
import otava.assembly.literal;
import otava.assembly.value;

namespace otava::intermediate {

CodeGenerator::CodeGenerator(Context* context_) : Visitor(context_)
{
}

CodeGenerator::~CodeGenerator()
{
}

void GenerateCode(Context& context, CodeGenerator& codeGenerator, bool verbose)
{
    context.GetData().VisitGlobalVariables(codeGenerator);
    context.GetCode().VisitFunctions(codeGenerator);
    codeGenerator.Write();
    if (verbose)
    {
        std::cout << "==> " << codeGenerator.AssemblyFile()->FilePath() << std::endl;
    }
}

void EmitPtrOperand(int64_t size, Value* value, otava::assembly::Instruction* instruction, CodeGenerator& codeGen);

void EmitFrameLocationOperand(int64_t size, const FrameLocation& frameLocation, otava::assembly::Instruction* instruction, CodeGenerator& codeGen)
{
    otava::assembly::Context& assemblyContext = codeGen.Ctx()->AssemblyContext();
    otava::assembly::Register* rbp = assemblyContext.GetGlobalReg(8, otava::assembly::RegisterGroupKind::rbp);
    instruction->AddOperand(assemblyContext.MakeSizePrefix(size,
        assemblyContext.MakeContent(assemblyContext.MakeBinaryExpr(rbp, assemblyContext.MakeLiteral(frameLocation.offset, 8), otava::assembly::Operator::sub))));
}

void EmitArgLocationOperand(int64_t size, const ArgLocation& argLocation, otava::assembly::Instruction* instruction, CodeGenerator& codeGen)
{
    otava::assembly::Context& assemblyContext = codeGen.Ctx()->AssemblyContext();
    otava::assembly::Register* rsp = assemblyContext.GetGlobalReg(8, otava::assembly::RegisterGroupKind::rsp);
    instruction->AddOperand(assemblyContext.MakeSizePrefix(size,
        assemblyContext.MakeContent(assemblyContext.MakeBinaryExpr(rsp, assemblyContext.MakeLiteral(argLocation.offset, 8), otava::assembly::Operator::sub))));
}

int64_t GetIndex(Value* index, CodeGenerator& codeGen)
{
    if (index->IsIntegerValue())
    {
        return index->GetIntegerValue();
    }
    else
    {
        codeGen.Error("error getting index: invalid index value kind");
    }
    return 0;
}

int64_t GetOffset(Type* type, int64_t index, CodeGenerator& codeGen)
{
    StructureType* structureType = type->GetStructurePointeeType(codeGen.GetSourcePos(), codeGen.Ctx());
    return structureType->GetFieldOffset(index);
}

int64_t GetElementSize(Type* type, CodeGenerator& codeGen)
{
    ArrayType* arrayType = type->GetArrayPointeeType(codeGen.GetSourcePos(), codeGen.Ctx());
    return arrayType->ElementType()->Size();
}

int64_t GetPointeeSize(Type* type, CodeGenerator& codeGen)
{
    if (type->IsPointerType())
    {
        PointerType* pointerType = static_cast<PointerType*>(type);
        Type* pointeeType = pointerType->RemovePointer(codeGen.GetSourcePos(), codeGen.Ctx());
        return pointeeType->Size();
    }
    else
    {
        codeGen.Error("error getting pointee size: pointer type expected");
    }
    return -1;
}

FrameLocation GetFrameLocation(Value* value, CodeGenerator& codeGen)
{
    Instruction* inst = nullptr;
    if (value->IsRegValue())
    {
        RegValue* regValue = static_cast<RegValue*>(value);
        inst = regValue->Inst();
        if (!inst)
        {
            codeGen.Error("error getting frame location: instruction for reg value not set");
        }
    }
    else if (value->IsInstruction())
    {
        inst = static_cast<Instruction*>(value);
    }
    if (inst)
    {
        Locations locs = codeGen.RegAllocator()->GetLocations(inst);
        if ((locs & Locations::frame) != Locations::none)
        {
            FrameLocation frameLocation = codeGen.RegAllocator()->GetFrameLocation(inst);
            if (frameLocation.Valid())
            {
                return frameLocation;
            }
            else
            {
                codeGen.Error("error getting frame location: frame location not valid");
            }
        }
        else
        {
            codeGen.Error("error getting frame location: value not in frame");
        }
    }
    else
    {
        codeGen.Error("error getting frame location: invalid value kind");
    }
    return FrameLocation();
}

otava::assembly::Register* MakeRegOperand(Value* value, otava::assembly::Register* reg, CodeGenerator& codeGen)
{
    int64_t size = std::min(value->GetType()->Size(), int64_t(reg->Size()));
    if (value->Kind() == ValueKind::regValue)
    {
        RegValue* regValue = static_cast<RegValue*>(value);
        Instruction* inst = regValue->Inst();
        if (inst)
        {
            if (inst->IsLocalInstruction())
            {
                otava::assembly::Instruction* leaInst = new otava::assembly::Instruction(otava::assembly::OpCode::LEA);
                leaInst->AddOperand(reg);
                EmitPtrOperand(size, value, leaInst, codeGen);
                codeGen.Emit(leaInst);
                return reg;
            }
            Locations locs = codeGen.RegAllocator()->GetLocations(inst);
            if ((locs & Locations::reg) != Locations::none)
            {
                otava::assembly::RegisterGroup* regGroup = codeGen.RegAllocator()->GetRegisterGroup(inst);
                if (regGroup)
                {
                    return regGroup->GetReg(size);
                }
                else
                {
                    codeGen.Error("error making reg operand: reg group not valid");
                }
            }
            else if ((locs & Locations::frame) != Locations::none)
            {
                FrameLocation frameLocation = codeGen.RegAllocator()->GetFrameLocation(inst);
                if (frameLocation.Valid())
                {
                    otava::assembly::Context& assemblyContext = codeGen.Ctx()->AssemblyContext();
                    otava::assembly::RegisterGroup* regGroup = assemblyContext.GetRegisterPool().GetGlobalRegisterGroup(reg->Group());
                    EmitLoad(size, frameLocation, regGroup, codeGen);
                }
                else
                {
                    codeGen.Error("error making reg operand: frame location not valid");
                }
            }
            else
            {
                codeGen.Error("error making reg operand: no locations for inst");
            }
        }
        else
        {
            codeGen.Error("error making reg operand: instruction for reg value not set");
        }
    }
    else if (value->IsAddressValue())
    {
        AddressValue* v = static_cast<AddressValue*>(value);
        otava::assembly::Instruction* movInst = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
        movInst->AddOperand(reg);
        otava::assembly::Context& assemblyContext = codeGen.Ctx()->AssemblyContext();
        movInst->AddOperand(assemblyContext.MakeSymbol(v->GetValue()->Name()));
        codeGen.Emit(movInst);
    }
    else
    {
        otava::assembly::Instruction* inst = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
        inst->AddOperand(reg);
        codeGen.Emit(inst);
        otava::assembly::Context& assemblyContext = codeGen.Ctx()->AssemblyContext();
        switch (value->Kind())
        {
            case ValueKind::boolValue:
            {
                BoolValue* v = static_cast<BoolValue*>(value);
                inst->AddOperand(assemblyContext.MakeLiteral(v->GetValue(), 1));
                break;
            }
            case ValueKind::sbyteValue:
            {
                SByteValue* v = static_cast<SByteValue*>(value);
                inst->AddOperand(assemblyContext.MakeLiteral(v->GetValue(), 1));
                break;
            }
            case ValueKind::byteValue:
            {
                ByteValue* v = static_cast<ByteValue*>(value);
                inst->AddOperand(assemblyContext.MakeLiteral(v->GetValue(), 1));
                break;
            }
            case ValueKind::shortValue:
            {
                ShortValue* v = static_cast<ShortValue*>(value);
                inst->AddOperand(assemblyContext.MakeLiteral(v->GetValue(), 2));
                break;
            }
            case ValueKind::ushortValue:
            {
                UShortValue* v = static_cast<UShortValue*>(value);
                inst->AddOperand(assemblyContext.MakeLiteral(v->GetValue(), 2));
                break;
            }
            case ValueKind::intValue:
            {
                IntValue* v = static_cast<IntValue*>(value);
                inst->AddOperand(assemblyContext.MakeLiteral(v->GetValue(), 4));
                break;
            }
            case ValueKind::uintValue:
            {
                UIntValue* v = static_cast<UIntValue*>(value);
                inst->AddOperand(assemblyContext.MakeLiteral(v->GetValue(), 4));
                break;
            }
            case ValueKind::longValue:
            {
                LongValue* v = static_cast<LongValue*>(value);
                inst->AddOperand(assemblyContext.MakeLiteral(v->GetValue(), 8));
                break;
            }
            case ValueKind::ulongValue:
            {
                ULongValue* v = static_cast<ULongValue*>(value);
                inst->AddOperand(assemblyContext.MakeLiteral(v->GetValue(), 8));
                break;
            }
            case ValueKind::floatValue:
            {
                FloatValue* v = static_cast<FloatValue*>(value);
                // todo
                throw std::runtime_error("floats not implemented");
            }
            case ValueKind::doubleValue:
            {
                DoubleValue* v = static_cast<DoubleValue*>(value);
                // todo
                throw std::runtime_error("floats not implemented");
            }
            case ValueKind::nullValue:
            {
                inst->AddOperand(assemblyContext.MakeLiteral(0, 8));
                break;
            }
            case ValueKind::symbolValue:
            {
                SymbolValue* v = static_cast<SymbolValue*>(value);
                inst->AddOperand(assemblyContext.MakeSymbol(v->Symbol()));
                break;
            }
            default:
            {
                codeGen.Error("error making reg operand: not implemented for value kind " + value->KindStr());
            }
        }
    }
    return reg;
}

void EmitPtrOperand(int64_t size, Value* value, otava::assembly::Instruction* instruction, CodeGenerator& codeGen)
{
    Instruction* inst = nullptr;
    if (value->IsRegValue())
    {
        RegValue* regValue = static_cast<RegValue*>(value);
        inst = regValue->Inst();
        if (!inst)
        {
            codeGen.Error("error emitting ptr operand: instruction for reg value not set");
        }
    }
    else if (value->IsInstruction())
    {
        inst = static_cast<Instruction*>(value);
    }
    else if (value->IsAddressValue())
    {
        otava::assembly::Context& assemblyContext = codeGen.Ctx()->AssemblyContext();
        AddressValue* addressValue = static_cast<AddressValue*>(value);
        GlobalVariable* globalVar = addressValue->GetValue();
        otava::assembly::Instruction* movInst = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
        movInst->AddOperand(assemblyContext.GetGlobalReg(size, otava::assembly::RegisterGroupKind::rax));
        movInst->AddOperand(assemblyContext.MakeSymbol(globalVar->Name()));
        codeGen.Emit(movInst);
        instruction->AddOperand(assemblyContext.GetGlobalReg(size, otava::assembly::RegisterGroupKind::rax));
        return;
    }
    if (inst)
    {
        if (inst->IsLocalInstruction())
        {
            FrameLocation frameLocation = GetFrameLocation(value, codeGen);
            EmitFrameLocationOperand(size, frameLocation, instruction, codeGen);
        }
        else
        {
            otava::assembly::Context& assemblyContext = codeGen.Ctx()->AssemblyContext();
            otava::assembly::Value* operand = assemblyContext.MakeSizePrefix(size, assemblyContext.MakeContent(
                MakeRegOperand(value, assemblyContext.GetGlobalReg(8, otava::assembly::RegisterGroupKind::rax), codeGen)));
            instruction->AddOperand(operand);
        }
    }
}

void EmitArgOperand(Instruction* argInst, int64_t size, Value* arg, otava::assembly::Instruction* instruction, CodeGenerator& codeGen)
{
    if (arg->IsRegValue())
    {
        RegValue* regValue = static_cast<RegValue*>(arg);
        Instruction* inst = regValue->Inst();
        if (inst->IsLocalInstruction()) 
        {
            otava::assembly::RegisterGroup* regGroup = codeGen.RegAllocator()->GetRegisterGroup(argInst);
            if (regGroup)
            {
                otava::assembly::Instruction* leaInst = new otava::assembly::Instruction(otava::assembly::OpCode::LEA);
                leaInst->AddOperand(regGroup->GetReg(8));
                FrameLocation frameLocation = GetFrameLocation(arg, codeGen);
                EmitFrameLocationOperand(1, frameLocation, leaInst, codeGen);
                codeGen.Emit(leaInst);
                instruction->AddOperand(regGroup->GetReg(8));
                return;
            }
            else
            {
                codeGen.Error("error emitting arg: reg group not valid");
            }
        }
    }
    otava::assembly::Context& assemblyContext = codeGen.Ctx()->AssemblyContext();
    instruction->AddOperand(MakeRegOperand(arg, assemblyContext.GetGlobalReg(size, otava::assembly::RegisterGroupKind::rax), codeGen));
}

void EmitParam(ParamInstruction& inst, CodeGenerator& codeGen)
{
    Type* type = inst.GetType();
    int64_t size = type->Size();
    otava::assembly::RegisterGroup* regGroup = codeGen.RegAllocator()->GetRegisterGroup(&inst);
    otava::assembly::Context& assemblyContext = codeGen.Ctx()->AssemblyContext();
    if (!regGroup)
    {
        codeGen.Error("error emitting param: reg group not valid");
    }
    switch (inst.Index())
    {
        case 0:
        {
            otava::assembly::Instruction* movInst = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
            otava::assembly::Register* paramReg = assemblyContext.GetGlobalReg(size, otava::assembly::RegisterGroupKind::rcx);
            movInst->AddOperand(regGroup->GetReg(size));
            movInst->AddOperand(paramReg);
            codeGen.Emit(movInst);
            break;
        }
        case 1:
        {
            otava::assembly::Instruction* movInst = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
            otava::assembly::Register* paramReg = assemblyContext.GetGlobalReg(size, otava::assembly::RegisterGroupKind::rdx);
            movInst->AddOperand(regGroup->GetReg(size));
            movInst->AddOperand(paramReg);
            codeGen.Emit(movInst);
            break;
        }
        case 2:
        {
            otava::assembly::Instruction* movInst = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
            otava::assembly::Register* paramReg = assemblyContext.GetGlobalReg(size, otava::assembly::RegisterGroupKind::r8);
            movInst->AddOperand(regGroup->GetReg(size));
            movInst->AddOperand(paramReg);
            codeGen.Emit(movInst);
            break;
        }
        case 3:
        {
            otava::assembly::Instruction* movInst = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
            otava::assembly::Register* paramReg = assemblyContext.GetGlobalReg(size, otava::assembly::RegisterGroupKind::r9);
            movInst->AddOperand(regGroup->GetReg(size));
            movInst->AddOperand(paramReg);
            codeGen.Emit(movInst);
            break;
        }
        default:
        {
            Locations locs = codeGen.RegAllocator()->GetLocations(&inst);
            if ((locs & Locations::frame) != Locations::none)
            {
                FrameLocation frameLocation = codeGen.RegAllocator()->GetFrameLocation(&inst);
                EmitLoad(size, frameLocation, regGroup, codeGen);
            }
            else
            {
                codeGen.Error("error emitting param: no frame location");
            }
        }
    }
}

void EmitLoad(int64_t size, const FrameLocation& frameLocation, otava::assembly::RegisterGroup* regGroup, CodeGenerator& codeGen)
{
    if (!frameLocation.Valid())
    {
        codeGen.Error("error emitting load: frame location not valid");
    }
    otava::assembly::Context& assemblyContext = codeGen.Ctx()->AssemblyContext();
    otava::assembly::Instruction* instruction = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
    instruction->AddOperand(regGroup->GetReg(size));
    EmitFrameLocationOperand(size, frameLocation, instruction, codeGen);
    codeGen.Emit(instruction);
}

void EmitStore(int64_t size, const FrameLocation& frameLocation, otava::assembly::RegisterGroup* regGroup, CodeGenerator& codeGen)
{
    if (!frameLocation.Valid())
    {
        codeGen.Error("error emitting store: frame location not valid");
    }
    otava::assembly::Context& assemblyContext = codeGen.Ctx()->AssemblyContext();
    otava::assembly::Instruction* instruction = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
    EmitFrameLocationOperand(size, frameLocation, instruction, codeGen);
    instruction->AddOperand(regGroup->GetReg(size));
}

otava::assembly::Value* MakeCalleeOperand(Value* value, otava::assembly::Register* reg, CodeGenerator& codeGen)
{
    if (value->Kind() == ValueKind::regValue)
    {
        return MakeRegOperand(value, reg, codeGen);
    }
    else
    {
        if (value->IsSymbolValue())
        {
            SymbolValue* symbolValue = static_cast<SymbolValue*>(value);
            otava::assembly::Context& assemblyContext = codeGen.Ctx()->AssemblyContext();
            return assemblyContext.MakeSymbol(symbolValue->Symbol());
        }
        else
        {
            codeGen.Error("error emitting callee operand: invalid value kind");
        }
    }
    return nullptr;
}

void EmitLoad(LoadInstruction& inst, CodeGenerator& codeGen)
{
    otava::assembly::RegisterGroup* regGroup = codeGen.RegAllocator()->GetRegisterGroup(&inst);
    if (!regGroup)
    {
        codeGen.Error("error emitting load: reg group not valid");
    }
    Type* type = inst.Result()->GetType();
    if (type->IsFundamentalType() || type->IsPointerType())
    {
        int64_t size = type->Size();
        otava::assembly::Instruction* instruction = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
        instruction->AddOperand(regGroup->GetReg(size));
        EmitPtrOperand(size, inst.Ptr(), instruction, codeGen);
        codeGen.Emit(instruction);
    }
    else
    {
        codeGen.Error("error emitting load: invalid type kind");
    }
}

void EmitStore(StoreInstruction& inst, CodeGenerator& codeGen)
{
    Type* type = inst.GetValue()->GetType();
    if (type->IsFundamentalType() || type->IsPointerType())
    {
        int64_t size = type->Size();
        otava::assembly::Context& assemblyContext = codeGen.Ctx()->AssemblyContext();
        otava::assembly::Instruction* instruction = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
        EmitPtrOperand(size, inst.GetPtr(), instruction, codeGen);
        instruction->AddOperand(MakeRegOperand(inst.GetValue(), assemblyContext.GetGlobalReg(size, otava::assembly::RegisterGroupKind::rax), codeGen));
        codeGen.Emit(instruction);
    }
    else
    {
        codeGen.Error("error emitting store: invalid type kind");
    }
}

void EmitElemAddr(ElemAddrInstruction& inst, CodeGenerator& codeGen)
{
    otava::assembly::Context& assemblyContext = codeGen.Ctx()->AssemblyContext();
    ElemAddrKind elemAddrKind = inst.GetElemAddrKind(codeGen.Ctx());
    if (elemAddrKind == ElemAddrKind::array)
    {
        otava::assembly::Register* indexReg = MakeRegOperand(inst.Index(), assemblyContext.GetGlobalReg(8, otava::assembly::RegisterGroupKind::rbx), codeGen);
        int64_t indexFactor = GetElementSize(inst.Ptr()->GetType(), codeGen);
        otava::assembly::Instruction* movInst = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
        otava::assembly::Register* rax = assemblyContext.GetGlobalReg(8, otava::assembly::RegisterGroupKind::rax);
        movInst->AddOperand(rax);
        movInst->AddOperand(assemblyContext.MakeLiteral(indexFactor, 8));
        codeGen.Emit(movInst);
        otava::assembly::Instruction* mulInst = new otava::assembly::Instruction(otava::assembly::OpCode::MUL);
        mulInst->AddOperand(indexReg);
        codeGen.Emit(mulInst);
        otava::assembly::RegisterGroup* regGroup = codeGen.RegAllocator()->GetRegisterGroup(&inst);
        if (regGroup)
        {
            otava::assembly::Register* resultReg = regGroup->GetReg(8);
            otava::assembly::Instruction* movResultInst = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
            movResultInst->AddOperand(resultReg);
            movResultInst->AddOperand(rax);
            codeGen.Emit(movResultInst);
        }
        else
        {
            codeGen.Error("error emitting elemaddr instruction: reg group for inst not found");
        }
    }
    else if (elemAddrKind == ElemAddrKind::structure)
    {
        otava::assembly::RegisterGroup* regGroup = codeGen.RegAllocator()->GetRegisterGroup(&inst);
        if (regGroup)
        {
            otava::assembly::Register* resultReg = regGroup->GetReg(8);
            int64_t index = GetIndex(inst.Index(), codeGen);
            int64_t offset = GetOffset(inst.Ptr()->GetType(), index, codeGen);
            otava::assembly::Instruction* movOffsetInst = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
            otava::assembly::Register* rbx = assemblyContext.GetGlobalReg(8, otava::assembly::RegisterGroupKind::rbx);
            movOffsetInst->AddOperand(rbx);
            movOffsetInst->AddOperand(assemblyContext.MakeLiteral(offset, 8));
            codeGen.Emit(movOffsetInst);
            otava::assembly::Instruction* leaPtrInst = new otava::assembly::Instruction(otava::assembly::OpCode::LEA);
            otava::assembly::Register* rcx = assemblyContext.GetGlobalReg(8, otava::assembly::RegisterGroupKind::rcx);
            leaPtrInst->AddOperand(rcx);
            EmitPtrOperand(8, inst.Ptr(), leaPtrInst, codeGen);
            codeGen.Emit(leaPtrInst);
            otava::assembly::Instruction* leaInst = new otava::assembly::Instruction(otava::assembly::OpCode::LEA);
            leaInst->AddOperand(resultReg);
            leaInst->AddOperand(assemblyContext.MakeSizePrefix(8, assemblyContext.MakeContent(assemblyContext.MakeBinaryExpr(rbx, rcx, otava::assembly::Operator::add))));
            codeGen.Emit(leaInst);
        }
        else
        {
            codeGen.Error("error emitting elemaddr instruction: reg group for inst not found");
        }
    }
    else
    {
        codeGen.Error("error emitting elemaddr: invalid elemaddr kind");
    }
}

void EmitPtrOffset(PtrOffsetInstruction& inst, CodeGenerator& codeGen)
{
    otava::assembly::Context& assemblyContext = codeGen.Ctx()->AssemblyContext();
    otava::assembly::Register* offsetReg = MakeRegOperand(inst.Offset(), assemblyContext.GetGlobalReg(8, otava::assembly::RegisterGroupKind::rbx), codeGen);
    int64_t offsetFactor = GetPointeeSize(inst.Ptr()->GetType(), codeGen);
    otava::assembly::Instruction* movInst = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
    otava::assembly::Register* rax = assemblyContext.GetGlobalReg(8, otava::assembly::RegisterGroupKind::rax);
    movInst->AddOperand(rax);
    movInst->AddOperand(assemblyContext.MakeLiteral(offsetFactor, 8));
    codeGen.Emit(movInst);
    otava::assembly::Instruction* mulInst = new otava::assembly::Instruction(otava::assembly::OpCode::MUL);
    mulInst->AddOperand(offsetReg);
    codeGen.Emit(mulInst);
    otava::assembly::Register* ptrReg = MakeRegOperand(inst.Ptr(), assemblyContext.GetGlobalReg(8, otava::assembly::RegisterGroupKind::rcx), codeGen);
    otava::assembly::Instruction* leaInst = new otava::assembly::Instruction(otava::assembly::OpCode::LEA);
    otava::assembly::RegisterGroup* regGroup = codeGen.RegAllocator()->GetRegisterGroup(&inst);
    if (regGroup)
    {
        otava::assembly::Register* resultReg = regGroup->GetReg(8);
        leaInst->AddOperand(resultReg);
        otava::assembly::Value* operand = assemblyContext.MakeSizePrefix(8, assemblyContext.MakeContent(
            assemblyContext.MakeBinaryExpr(rax, ptrReg, otava::assembly::Operator::add)));
        leaInst->AddOperand(operand);
        codeGen.Emit(leaInst);
    }
    else
    {
        codeGen.Error("error emitting ptroffset instruction: reg group for inst not found");
    }
}

void EmitPtrDiff(PtrDiffInstruction& inst, CodeGenerator& codeGen)
{
    otava::assembly::Context& assemblyContext = codeGen.Ctx()->AssemblyContext();
    int64_t scaleFactor = GetPointeeSize(inst.LeftPtr()->GetType(), codeGen);
    otava::assembly::Instruction* movInst = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
    otava::assembly::Register* rcx = assemblyContext.GetGlobalReg(8, otava::assembly::RegisterGroupKind::rcx);
    movInst->AddOperand(rcx);
    movInst->AddOperand(assemblyContext.MakeLiteral(scaleFactor, 8));
    otava::assembly::Instruction* subInst = new otava::assembly::Instruction(otava::assembly::OpCode::SUB);
    otava::assembly::RegisterGroup* regGroup = codeGen.RegAllocator()->GetRegisterGroup(&inst);
    if (regGroup)
    {
        otava::assembly::Register* resultReg = regGroup->GetReg(8);
        otava::assembly::Register* leftReg = MakeRegOperand(inst.LeftPtr(), assemblyContext.GetGlobalReg(8, otava::assembly::RegisterGroupKind::rax), codeGen);
        subInst->AddOperand(leftReg);
        otava::assembly::Register* rightReg = MakeRegOperand(inst.RightPtr(), assemblyContext.GetGlobalReg(8, otava::assembly::RegisterGroupKind::rbx), codeGen);
        subInst->AddOperand(rightReg);
        codeGen.Emit(subInst);
        otava::assembly::Register* rax = assemblyContext.GetGlobalReg(8, otava::assembly::RegisterGroupKind::rax);
        otava::assembly::Instruction* movInst = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
        movInst->AddOperand(rax);
        movInst->AddOperand(leftReg);
        codeGen.Emit(movInst);
        otava::assembly::Instruction* divInst = new otava::assembly::Instruction(otava::assembly::OpCode::DIV);
        divInst->AddOperand(rcx);
        codeGen.Emit(divInst);
        otava::assembly::Instruction* movResultInst = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
        movResultInst->AddOperand(resultReg);
        movResultInst->AddOperand(rax);
        codeGen.Emit(movResultInst);
    }
    else
    {
        codeGen.Error("error emitting ptrdiff instruction: reg group for inst not found");
    }
}

void EmitArg(ArgInstruction& inst, CallFrame* callFrame, int32_t index, CodeGenerator& codeGen)
{
    RegisterAllocationAction action = codeGen.RegAllocator()->Run(&inst);
    if (action == RegisterAllocationAction::spill)
    {
        for (const SpillData& spillData : codeGen.RegAllocator()->GetSpillData())
        {
            EmitStore(8, spillData.spillToFrameLocation, spillData.registerGroupToSpill, codeGen);
        }
    }
    otava::assembly::Context& assemblyContext = codeGen.Ctx()->AssemblyContext();
    int64_t size = inst.Arg()->GetType()->Size();
    switch (index)
    {
        case 0:
        {
            otava::assembly::Instruction* movInst = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
            movInst->AddOperand(assemblyContext.GetGlobalReg(size, otava::assembly::RegisterGroupKind::rcx));
            EmitArgOperand(&inst, size, inst.Arg(), movInst, codeGen);
            codeGen.Emit(movInst);
            break;
        }
        case 1:
        {
            otava::assembly::Instruction* movInst = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
            movInst->AddOperand(assemblyContext.GetGlobalReg(size, otava::assembly::RegisterGroupKind::rdx));
            EmitArgOperand(&inst, size, inst.Arg(), movInst, codeGen);
            codeGen.Emit(movInst);
            break;
        }
        case 2:
        {
            otava::assembly::Instruction* movInst = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
            movInst->AddOperand(assemblyContext.GetGlobalReg(size, otava::assembly::RegisterGroupKind::r8));
            EmitArgOperand(&inst, size, inst.Arg(), movInst, codeGen);
            codeGen.Emit(movInst);
            break;
        }
        case 3:
        {
            otava::assembly::Instruction* movInst = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
            movInst->AddOperand(assemblyContext.GetGlobalReg(size, otava::assembly::RegisterGroupKind::r9));
            EmitArgOperand(&inst, size, inst.Arg(), movInst, codeGen);
            codeGen.Emit(movInst);
            break;
        }
        default:
        {
            otava::assembly::Instruction* movInst = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
            otava::assembly::RegisterGroup* regGroup = codeGen.RegAllocator()->GetRegisterGroup(&inst);
            if (regGroup)
            {
                otava::assembly::Register* reg = regGroup->GetReg(size);
                movInst->AddOperand(reg);
                EmitArgOperand(&inst, size, inst.Arg(), movInst, codeGen);
                codeGen.Emit(movInst);
                otava::assembly::Instruction* pushToFrameInst = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
                ArgLocation argLocation = callFrame->GetArgLocation(index - 4);
                EmitArgLocationOperand(size, argLocation, pushToFrameInst, codeGen);
                pushToFrameInst->AddOperand(reg);
                codeGen.Emit(pushToFrameInst);
            }
            else
            {
                codeGen.Error("error emitting arg instruction: reg group for inst not found");
            }
            break;
        }
    }
}

void EmitArgs(const std::vector<ArgInstruction*>& args, CodeGenerator& codeGen)
{
    CallFrame callFrame;
    int n = args.size();
    for (int i = 4; i < n; ++i)
    {
        int64_t size = args[i]->Arg()->GetType()->Size();
        callFrame.AllocateArgLocation(size);
    }
    for (int i = n - 1; i >= 0; --i)
    {
        EmitArg(*args[i], &callFrame, i, codeGen);
    }
}

void EmitSignExtend(SignExtendInstruction& inst, CodeGenerator& codeGen)
{
    int64_t operandSize = inst.Operand()->GetType()->Size();
    int64_t resultSize = inst.Result()->GetType()->Size();
    otava::assembly::Context& assemblyContext = codeGen.Ctx()->AssemblyContext();
    otava::assembly::OpCode opCode = otava::assembly::OpCode::MOVSX;
    if (operandSize == 4)
    {
        opCode = otava::assembly::OpCode::MOVSXD;
    }
    otava::assembly::Instruction* movsxInst = new otava::assembly::Instruction(opCode);
    otava::assembly::RegisterGroup* regGroup = codeGen.RegAllocator()->GetRegisterGroup(&inst);
    if (regGroup)
    {
        otava::assembly::Register* reg = regGroup->GetReg(resultSize);
        movsxInst->AddOperand(reg);
        otava::assembly::Register* sourceReg = MakeRegOperand(inst.Operand(), assemblyContext.GetGlobalReg(operandSize, otava::assembly::RegisterGroupKind::rax), codeGen);
        movsxInst->AddOperand(sourceReg);
        codeGen.Emit(movsxInst);
    }
    else
    {
        codeGen.Error("error emitting sign extend instruction: reg group for inst not found");
    }
}

void EmitZeroExtend(ZeroExtendInstruction& inst, CodeGenerator& codeGen)
{
    int64_t operandSize = inst.Operand()->GetType()->Size();
    int64_t resultSize = inst.Result()->GetType()->Size();
    otava::assembly::Context& assemblyContext = codeGen.Ctx()->AssemblyContext();
    otava::assembly::OpCode opCode = otava::assembly::OpCode::MOVZX;
    otava::assembly::Instruction* movzxInst = new otava::assembly::Instruction(opCode);
    otava::assembly::RegisterGroup* regGroup = codeGen.RegAllocator()->GetRegisterGroup(&inst);
    if (regGroup)
    {
        otava::assembly::Register* reg = regGroup->GetReg(resultSize);
        movzxInst->AddOperand(reg);
        otava::assembly::Register* sourceReg = MakeRegOperand(inst.Operand(), assemblyContext.GetGlobalReg(operandSize, otava::assembly::RegisterGroupKind::rax), codeGen);
        movzxInst->AddOperand(sourceReg);
        codeGen.Emit(movzxInst);
    }
    else
    {
        codeGen.Error("error emitting zero extend instruction: reg group for inst not found");
    }
}

void EmitTruncate(TruncateInstruction& inst, CodeGenerator& codeGen)
{
    otava::assembly::Context& assemblyContext = codeGen.Ctx()->AssemblyContext();
    otava::assembly::RegisterGroup* regGroup = codeGen.RegAllocator()->GetRegisterGroup(&inst);
    if (regGroup)
    {
        int64_t resultSize = inst.Result()->GetType()->Size();
        otava::assembly::Register* resultReg = regGroup->GetReg(resultSize);
        otava::assembly::Register* sourceReg = MakeRegOperand(inst.Operand(), assemblyContext.GetGlobalReg(resultSize, otava::assembly::RegisterGroupKind::rax), codeGen);
        otava::assembly::Instruction* movInst = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
        movInst->AddOperand(resultReg);
        movInst->AddOperand(sourceReg);
        codeGen.Emit(movInst);
    }
    else
    {
        codeGen.Error("error emitting truncate instruction: reg group for inst not found");
    }
}

void EmitBitcast(BitcastInstruction& inst, CodeGenerator& codeGen)
{
    otava::assembly::Context& assemblyContext = codeGen.Ctx()->AssemblyContext();
    otava::assembly::RegisterGroup* regGroup = codeGen.RegAllocator()->GetRegisterGroup(&inst);
    if (regGroup)
    {
        Type* type = inst.Operand()->GetType();
        int64_t size = type->Size();
        otava::assembly::Register* resultReg = regGroup->GetReg(size);
        otava::assembly::Register* sourceReg = MakeRegOperand(inst.Operand(), assemblyContext.GetGlobalReg(size, otava::assembly::RegisterGroupKind::rax), codeGen);
        otava::assembly::Instruction* movInst = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
        movInst->AddOperand(resultReg);
        movInst->AddOperand(sourceReg);
        codeGen.Emit(movInst);
    }
    else
    {
        codeGen.Error("error emitting bitcast instruction: reg group for inst not found");
    }
}

void EmitIntToFloat(IntToFloatInstruction& inst, CodeGenerator& codeGen)
{
    // todo
}

void EmitFloatToInt(FloatToIntInstruction& inst, CodeGenerator& codeGen)
{
    // todo
}

void EmitIntToPtr(IntToPtrInstruction& inst, CodeGenerator& codeGen)
{
    otava::assembly::Context& assemblyContext = codeGen.Ctx()->AssemblyContext();
    otava::assembly::RegisterGroup* regGroup = codeGen.RegAllocator()->GetRegisterGroup(&inst);
    if (regGroup)
    {
        Type* type = inst.Operand()->GetType();
        int64_t size = type->Size();
        otava::assembly::Register* resultReg = regGroup->GetReg(size);
        otava::assembly::Register* sourceReg = MakeRegOperand(inst.Operand(), assemblyContext.GetGlobalReg(size, otava::assembly::RegisterGroupKind::rax), codeGen);
        otava::assembly::Instruction* movInst = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
        movInst->AddOperand(resultReg);
        movInst->AddOperand(sourceReg);
        codeGen.Emit(movInst);
    }
    else
    {
        codeGen.Error("error emitting inttoptr instruction: reg group for inst not found");
    }
}

void EmitPtrToInt(PtrToIntInstruction& inst, CodeGenerator& codeGen)
{
    otava::assembly::Context& assemblyContext = codeGen.Ctx()->AssemblyContext();
    otava::assembly::RegisterGroup* regGroup = codeGen.RegAllocator()->GetRegisterGroup(&inst);
    if (regGroup)
    {
        Type* type = inst.Operand()->GetType();
        int64_t size = type->Size();
        otava::assembly::Register* resultReg = regGroup->GetReg(size);
        otava::assembly::Register* sourceReg = MakeRegOperand(inst.Operand(), assemblyContext.GetGlobalReg(size, otava::assembly::RegisterGroupKind::rax), codeGen);
        otava::assembly::Instruction* movInst = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
        movInst->AddOperand(resultReg);
        movInst->AddOperand(sourceReg);
        codeGen.Emit(movInst);
    }
    else
    {
        codeGen.Error("error emitting ptrtoint instruction: reg group for inst not found");
    }
}

void EmitEqual(EqualInstruction& inst, CodeGenerator& codeGen)
{
    otava::assembly::Context& assemblyContext = codeGen.Ctx()->AssemblyContext();
    otava::assembly::RegisterGroup* regGroup = codeGen.RegAllocator()->GetRegisterGroup(&inst);
    if (regGroup)
    {
        int64_t resultSize = 1;
        int64_t size = inst.Left()->GetType()->Size();
        otava::assembly::Register* resultReg = regGroup->GetReg(resultSize);
        otava::assembly::Instruction* cmpInstruction = new otava::assembly::Instruction(otava::assembly::OpCode::CMP);
        otava::assembly::Register* leftOperandReg = MakeRegOperand(inst.Left(), assemblyContext.GetGlobalReg(size, otava::assembly::RegisterGroupKind::rcx), codeGen);
        cmpInstruction->AddOperand(leftOperandReg);
        otava::assembly::Register* rightOperandReg = MakeRegOperand(inst.Right(), assemblyContext.GetGlobalReg(size, otava::assembly::RegisterGroupKind::rdx), codeGen);
        cmpInstruction->AddOperand(rightOperandReg);
        codeGen.Emit(cmpInstruction);
        otava::assembly::Instruction* setInst = new otava::assembly::Instruction(otava::assembly::OpCode::SETE);
        setInst->AddOperand(resultReg);
        codeGen.Emit(setInst);
    }
    else
    {
        codeGen.Error("error emitting equal instruction: reg group for inst not found");
    }
}

void EmitLess(LessInstruction& inst, CodeGenerator& codeGen)
{
    otava::assembly::Context& assemblyContext = codeGen.Ctx()->AssemblyContext();
    otava::assembly::RegisterGroup* regGroup = codeGen.RegAllocator()->GetRegisterGroup(&inst);
    if (regGroup)
    {
        int64_t resultSize = 1;
        int64_t size = inst.Left()->GetType()->Size();
        otava::assembly::Register* resultReg = regGroup->GetReg(resultSize);
        otava::assembly::Instruction* cmpInstruction = new otava::assembly::Instruction(otava::assembly::OpCode::CMP);
        otava::assembly::Register* leftOperandReg = MakeRegOperand(inst.Left(), assemblyContext.GetGlobalReg(size, otava::assembly::RegisterGroupKind::rcx), codeGen);
        cmpInstruction->AddOperand(leftOperandReg);
        otava::assembly::Register* rightOperandReg = MakeRegOperand(inst.Right(), assemblyContext.GetGlobalReg(size, otava::assembly::RegisterGroupKind::rdx), codeGen);
        cmpInstruction->AddOperand(rightOperandReg);
        codeGen.Emit(cmpInstruction);
        otava::assembly::Instruction* setInst = new otava::assembly::Instruction(otava::assembly::OpCode::SETC);
        setInst->AddOperand(resultReg);
        codeGen.Emit(setInst);
    }
    else
    {
        codeGen.Error("error emitting less instruction: reg group for inst not found");
    }
}

void EmitJmp(JmpInstruction& inst, CodeGenerator& codeGen)
{
    otava::assembly::Context& assemblyContext = codeGen.Ctx()->AssemblyContext();
    otava::assembly::Instruction* jmpInstruction = new otava::assembly::Instruction(otava::assembly::OpCode::JMP);
    jmpInstruction->AddOperand(assemblyContext.MakeSymbol("@" + std::to_string(inst.TargetBasicBlock()->Id())));
    codeGen.Emit(jmpInstruction);
}

void EmitBranch(BranchInstruction& inst, CodeGenerator& codeGen)
{
    otava::assembly::Context& assemblyContext = codeGen.Ctx()->AssemblyContext();
    int size = 4;
    otava::assembly::Register* operandReg = MakeRegOperand(inst.Cond(), assemblyContext.GetGlobalReg(size, otava::assembly::RegisterGroupKind::rax), codeGen);
    otava::assembly::Instruction* orInstruction = new otava::assembly::Instruction(otava::assembly::OpCode::OR);
    orInstruction->AddOperand(operandReg);
    orInstruction->AddOperand(operandReg);
    codeGen.Emit(orInstruction);
    otava::assembly::Instruction* jnzInstruction = new otava::assembly::Instruction(otava::assembly::OpCode::JNZ);
    jnzInstruction->AddOperand(assemblyContext.MakeSymbol("@" + std::to_string(inst.TrueTargetBasicBlock()->Id())));
    codeGen.Emit(jnzInstruction);
    otava::assembly::Instruction* jmpInstruction = new otava::assembly::Instruction(otava::assembly::OpCode::JMP);
    jmpInstruction->AddOperand(assemblyContext.MakeSymbol("@" + std::to_string(inst.FalseTargetBasicBlock()->Id())));
    codeGen.Emit(jmpInstruction);
}

void EmitProcedureCall(ProcedureCallInstruction& inst, const std::vector<ArgInstruction*>& args, CodeGenerator& codeGen)
{
    EmitArgs(args, codeGen);
    RegisterAllocationAction action = codeGen.RegAllocator()->Run(&inst);
    if (action == RegisterAllocationAction::spill)
    {
        for (const SpillData& spillData : codeGen.RegAllocator()->GetSpillData())
        {
            EmitStore(8, spillData.spillToFrameLocation, spillData.registerGroupToSpill, codeGen);
        }
    }
    otava::assembly::Context& assemblyContext = codeGen.Ctx()->AssemblyContext();
    otava::assembly::RegisterGroup* regGroup = codeGen.RegAllocator()->GetRegisterGroup(&inst);
    otava::assembly::Register* reg = regGroup->GetReg(8);
    otava::assembly::Instruction* callInst = new otava::assembly::Instruction(otava::assembly::OpCode::CALL);
    callInst->AddOperand(MakeCalleeOperand(inst.Callee(), reg, codeGen));
    codeGen.Emit(callInst);
}

void EmitFunctionCall(FunctionCallInstruction& inst, const std::vector<ArgInstruction*>& args, CodeGenerator& codeGen)
{
    EmitArgs(args, codeGen);
    RegisterAllocationAction action = codeGen.RegAllocator()->Run(&inst);
    if (action == RegisterAllocationAction::spill)
    {
        for (const SpillData& spillData : codeGen.RegAllocator()->GetSpillData())
        {
            EmitStore(8, spillData.spillToFrameLocation, spillData.registerGroupToSpill, codeGen);
        }
    }
    otava::assembly::Context& assemblyContext = codeGen.Ctx()->AssemblyContext();
    otava::assembly::RegisterGroup* regGroup = codeGen.RegAllocator()->GetRegisterGroup(&inst);
    otava::assembly::Register* reg = regGroup->GetReg(8);
    otava::assembly::Instruction* callInst = new otava::assembly::Instruction(otava::assembly::OpCode::CALL);
    callInst->AddOperand(MakeCalleeOperand(inst.Callee(), reg, codeGen));
    codeGen.Emit(callInst);
    otava::assembly::Instruction* movInst = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
    movInst->AddOperand(reg);
    movInst->AddOperand(assemblyContext.GetGlobalReg(8, otava::assembly::RegisterGroupKind::rax));
    codeGen.Emit(movInst);
}

void EmitRet(RetInstruction& inst, CodeGenerator& codeGen)
{
    otava::assembly::Context& assemblyContext = codeGen.Ctx()->AssemblyContext();
    if (inst.ReturnValue())
    {
        otava::assembly::Instruction* movInst = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
        int64_t size = inst.ReturnValue()->GetType()->Size();
        movInst->AddOperand(assemblyContext.GetGlobalReg(size, otava::assembly::RegisterGroupKind::rax));
        movInst->AddOperand(MakeRegOperand(inst.ReturnValue(), assemblyContext.GetGlobalReg(size, otava::assembly::RegisterGroupKind::rbx), codeGen));
        codeGen.Emit(movInst);
    }
    int targetLabelId = codeGen.ExitLabelId();
    otava::assembly::Instruction* jmpInst = new otava::assembly::Instruction(otava::assembly::OpCode::JMP);
    jmpInst->AddOperand(assemblyContext.MakeSymbol("@" + std::to_string(targetLabelId)));
    codeGen.Emit(jmpInst);
}

void EmitIntegerBinOpInst(BinaryInstruction& inst, CodeGenerator& codeGen)
{
    otava::assembly::Context& assemblyContext = codeGen.Ctx()->AssemblyContext();
    int64_t size = inst.GetType()->Size();
    otava::assembly::OpCode opCode = otava::assembly::OpCode::ADD;
    switch (inst.GetOpCode())
    {
        case OpCode::add:
        {
            opCode = otava::assembly::OpCode::ADD;
            break;
        }
        case OpCode::sub:
        {
            opCode = otava::assembly::OpCode::SUB;
            break;
        }
        case OpCode::mul:
        {
            if (inst.GetType()->IsUnsignedType())
            {
                opCode = otava::assembly::OpCode::MUL;
            }
            else
            {
                opCode = otava::assembly::OpCode::IMUL;
            }
            break;
        }
        case OpCode::div_:
        {
            if (inst.GetType()->IsUnsignedType())
            {
                opCode = otava::assembly::OpCode::DIV;
            }
            else
            {
                opCode = otava::assembly::OpCode::IDIV;
            }
            break;
        }
        case OpCode::mod:
        {
            if (inst.GetType()->IsUnsignedType())
            {
                opCode = otava::assembly::OpCode::DIV;
            }
            else
            {
                opCode = otava::assembly::OpCode::IDIV;
            }
            break;
        }
        case OpCode::and_:
        {
            opCode = otava::assembly::OpCode::AND;
            break;
        }
        case OpCode::or_:
        {
            opCode = otava::assembly::OpCode::OR;
            break;
        }
        case OpCode::xor_:
        {
            opCode = otava::assembly::OpCode::XOR;
            break;
        }
        case OpCode::shl:
        {
            opCode = otava::assembly::OpCode::SHL;
            break;
        }
        case OpCode::shr:
        {
            if (inst.GetType()->IsUnsignedType())
            {
                opCode = otava::assembly::OpCode::SHR;
            }
            else
            {
                opCode = otava::assembly::OpCode::SAR;
            }
            break;
        }
    }
    otava::assembly::Instruction* instruction = new otava::assembly::Instruction(opCode);
    otava::assembly::Register* leftOperandReg = nullptr;
    otava::assembly::Register* rightOperandReg = nullptr;
    otava::assembly::Register* resultOperandReg = nullptr;
    switch (inst.GetOpCode())
    {
        case OpCode::add:
        case OpCode::sub:
        case OpCode::and_:
        case OpCode::or_:
        case OpCode::xor_:
        {
            leftOperandReg = MakeRegOperand(inst.Left(), assemblyContext.GetGlobalReg(size, otava::assembly::RegisterGroupKind::rax), codeGen);
            instruction->AddOperand(leftOperandReg);
            rightOperandReg = MakeRegOperand(inst.Right(), assemblyContext.GetGlobalReg(size, otava::assembly::RegisterGroupKind::rbx), codeGen);
            instruction->AddOperand(rightOperandReg);
            resultOperandReg = leftOperandReg;
            break;
        }
        case OpCode::mul:
        case OpCode::div_:
        {
            otava::assembly::Register* rax = assemblyContext.GetGlobalReg(size, otava::assembly::RegisterGroupKind::rax);
            leftOperandReg = MakeRegOperand(inst.Left(), assemblyContext.GetGlobalReg(size, otava::assembly::RegisterGroupKind::rax), codeGen);
            if (leftOperandReg->Group() != otava::assembly::RegisterGroupKind::rax)
            {
                otava::assembly::Instruction* movInstruction = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
                movInstruction->AddOperand(rax);
                movInstruction->AddOperand(leftOperandReg);
                codeGen.Emit(movInstruction);
            }
            resultOperandReg = rax;
            rightOperandReg = MakeRegOperand(inst.Right(), assemblyContext.GetGlobalReg(size, otava::assembly::RegisterGroupKind::rbx), codeGen);
            instruction->AddOperand(rightOperandReg);
            break;
        }
        case OpCode::mod:
        {
            otava::assembly::Register* rax = assemblyContext.GetGlobalReg(size, otava::assembly::RegisterGroupKind::rax);
            otava::assembly::Register* rdx = assemblyContext.GetGlobalReg(size, otava::assembly::RegisterGroupKind::rdx);
            leftOperandReg = MakeRegOperand(inst.Left(), assemblyContext.GetGlobalReg(size, otava::assembly::RegisterGroupKind::rax), codeGen);
            if (leftOperandReg->Group() != otava::assembly::RegisterGroupKind::rax)
            {
                otava::assembly::Instruction* movInstruction = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
                movInstruction->AddOperand(rax);
                movInstruction->AddOperand(leftOperandReg);
                codeGen.Emit(movInstruction);
            }
            rightOperandReg = MakeRegOperand(inst.Right(), assemblyContext.GetGlobalReg(size, otava::assembly::RegisterGroupKind::rbx), codeGen);
            instruction->AddOperand(rightOperandReg);
            resultOperandReg = rdx;
            break;
        }
        case OpCode::shl:
        case OpCode::shr:
        {
            leftOperandReg = MakeRegOperand(inst.Left(), assemblyContext.GetGlobalReg(size, otava::assembly::RegisterGroupKind::rax), codeGen);
            otava::assembly::Register* cl = assemblyContext.GetGlobalReg(1, otava::assembly::RegisterGroupKind::rcx);
            rightOperandReg = MakeRegOperand(inst.Right(), assemblyContext.GetGlobalReg(1, otava::assembly::RegisterGroupKind::rcx), codeGen);
            if (rightOperandReg->Group() != otava::assembly::RegisterGroupKind::rcx)
            {
                otava::assembly::Instruction* movInstruction = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
                movInstruction->AddOperand(cl);
                movInstruction->AddOperand(rightOperandReg);
                codeGen.Emit(movInstruction);
            }
            instruction->AddOperand(leftOperandReg);
            instruction->AddOperand(cl);
            resultOperandReg = leftOperandReg;
            break;
        }
    }
    codeGen.Emit(instruction);
    otava::assembly::Instruction* movInstruction = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
    otava::assembly::RegisterGroup* regGroup = codeGen.RegAllocator()->GetRegisterGroup(&inst);
    if (regGroup)
    {
        movInstruction->AddOperand(regGroup->GetReg(size));
        movInstruction->AddOperand(resultOperandReg);
        codeGen.Emit(movInstruction);
    }
    else
    {
        codeGen.Error("error emitting integer binary operation instruction: reg group for inst not found");
    }
}

void EmitNot(NotInstruction& inst, CodeGenerator& codeGen)
{
    otava::assembly::Context& assemblyContext = codeGen.Ctx()->AssemblyContext();
    otava::assembly::RegisterGroup* regGroup = codeGen.RegAllocator()->GetRegisterGroup(&inst);
    if (regGroup)
    {
        Type* type = inst.Operand()->GetType();
        int64_t size = type->Size();
        otava::assembly::Register* resultReg = regGroup->GetReg(size);
        otava::assembly::Register* operandReg = MakeRegOperand(inst.Operand(), assemblyContext.GetGlobalReg(size, otava::assembly::RegisterGroupKind::rax), codeGen);
        otava::assembly::Instruction* movInst = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
        movInst->AddOperand(resultReg);
        movInst->AddOperand(operandReg);
        codeGen.Emit(movInst);
        if (type->IsBooleanType())
        {
            otava::assembly::Instruction* xorInst = new otava::assembly::Instruction(otava::assembly::OpCode::XOR);
            xorInst->AddOperand(resultReg);;
            xorInst->AddOperand(assemblyContext.MakeLiteral(1, size));
            codeGen.Emit(xorInst);
        }
        else if (type->IsIntegerType())
        {
            otava::assembly::Instruction* notInst = new otava::assembly::Instruction(otava::assembly::OpCode::NOT);
            notInst->AddOperand(resultReg);
        }
    }
    else
    {
        codeGen.Error("error emitting not instruction: reg group for inst not found");
    }
}

void EmitNeg(NegInstruction& inst, CodeGenerator& codeGen)
{
    otava::assembly::Context& assemblyContext = codeGen.Ctx()->AssemblyContext();
    otava::assembly::RegisterGroup* regGroup = codeGen.RegAllocator()->GetRegisterGroup(&inst);
    if (regGroup)
    {
        Type* type = inst.Operand()->GetType();
        int64_t size = type->Size();
        otava::assembly::Register* resultReg = regGroup->GetReg(size);
        otava::assembly::Register* operandReg = MakeRegOperand(inst.Operand(), assemblyContext.GetGlobalReg(size, otava::assembly::RegisterGroupKind::rax), codeGen);
        otava::assembly::Instruction* movInst = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
        movInst->AddOperand(resultReg);
        movInst->AddOperand(operandReg);
        codeGen.Emit(movInst);
        otava::assembly::Instruction* negInst = new otava::assembly::Instruction(otava::assembly::OpCode::NEG);
        negInst->AddOperand(resultReg);
        codeGen.Emit(negInst);
    }
    else
    {
        codeGen.Error("error emitting neg instruction: reg group for inst not found");
    }
}

void EmitFloatingPointBinOpInst(BinaryInstruction& inst, CodeGenerator& codeGen)
{
    // todo
}

void EmitNop(NoOperationInstruction& inst, CodeGenerator& codeGen)
{
    otava::assembly::Instruction* nopInst = new otava::assembly::Instruction(otava::assembly::OpCode::NOP);
    codeGen.Emit(nopInst);
}

void EmitSwitch(SwitchInstruction& inst, CodeGenerator& codeGen)
{
    otava::assembly::Context& assemblyContext = codeGen.Ctx()->AssemblyContext();
    int64_t size = inst.Cond()->GetType()->Size();
    otava::assembly::Register* condReg = MakeRegOperand(inst.Cond(), assemblyContext.GetGlobalReg(size, otava::assembly::RegisterGroupKind::rbx), codeGen);
    for (const auto& caseTarget : inst.CaseTargets())
    {
        int64_t size = caseTarget.caseValue->GetType()->Size();
        otava::assembly::Register* caseReg = MakeRegOperand(caseTarget.caseValue, assemblyContext.GetGlobalReg(size, otava::assembly::RegisterGroupKind::rax), codeGen);
        otava::assembly::Instruction* cmpInst = new otava::assembly::Instruction(otava::assembly::OpCode::CMP);
        cmpInst->AddOperand(caseReg);
        cmpInst->AddOperand(condReg);
        codeGen.Emit(cmpInst);
        otava::assembly::Instruction* jeInst = new otava::assembly::Instruction(otava::assembly::OpCode::JE);
        jeInst->AddOperand(assemblyContext.MakeSymbol("@" + std::to_string(caseTarget.targetBlock->Id())));
        codeGen.Emit(jeInst);
    }
    otava::assembly::Instruction* jmpInst = new otava::assembly::Instruction(otava::assembly::OpCode::JMP);
    jmpInst->AddOperand(assemblyContext.MakeSymbol("@" + std::to_string(inst.DefaultTargetBlock()->Id())));
    codeGen.Emit(jmpInst);
}

void EmitPrologue(CodeGenerator& codeGen)
{
    otava::assembly::Context& assemblyContext = codeGen.Ctx()->AssemblyContext();

    otava::assembly::Instruction* pushRbp = new otava::assembly::Instruction(otava::assembly::OpCode::PUSH);
    pushRbp->AddOperand(assemblyContext.GetGlobalReg(8, otava::assembly::RegisterGroupKind::rbp));
    codeGen.Emit(pushRbp);

    otava::assembly::Instruction* movRbp = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
    movRbp->AddOperand(assemblyContext.GetGlobalReg(8, otava::assembly::RegisterGroupKind::rbp));
    movRbp->AddOperand(assemblyContext.GetGlobalReg(8, otava::assembly::RegisterGroupKind::rsp));
    codeGen.Emit(movRbp);

    Frame& frame = codeGen.RegAllocator()->GetFrame();

    otava::assembly::Instruction* subRsp = new otava::assembly::Instruction(otava::assembly::OpCode::SUB);
    subRsp->AddOperand(assemblyContext.GetGlobalReg(8, otava::assembly::RegisterGroupKind::rsp));
    subRsp->AddOperand(assemblyContext.MakeLiteral(frame.Size(), 8));
    codeGen.Emit(subRsp);

    for (const auto& regGroup : assemblyContext.GetRegisterPool().UsedLocalRegs())
    {
        otava::assembly::Instruction* pushReg = new otava::assembly::Instruction(otava::assembly::OpCode::PUSH);
        pushReg->AddOperand(regGroup->GetReg(8));
        codeGen.Emit(pushReg);
    }
    for (const auto& regGroup : assemblyContext.GetRegisterPool().UsedNonvolatileRegs())
    {
        otava::assembly::Instruction* pushReg = new otava::assembly::Instruction(otava::assembly::OpCode::PUSH);
        pushReg->AddOperand(regGroup->GetReg(8));
        codeGen.Emit(pushReg);
    }
}

void EmitEpilogue(CodeGenerator& codeGen)
{
    otava::assembly::Instruction* leaderInst = nullptr;
    otava::assembly::Context& assemblyContext = codeGen.Ctx()->AssemblyContext();

    std::vector<otava::assembly::RegisterGroup*> usedNVRegs;
    for (const auto& regGroup : assemblyContext.GetRegisterPool().UsedNonvolatileRegs())
    {
        usedNVRegs.push_back(regGroup);
    }

    std::reverse(usedNVRegs.begin(), usedNVRegs.end());
    for (const auto& regGroup : usedNVRegs)
    {
        otava::assembly::Instruction* popReg = new otava::assembly::Instruction(otava::assembly::OpCode::POP);
        if (!leaderInst)
        {
            leaderInst = popReg;
            leaderInst->SetLabel("@" + std::to_string(codeGen.ExitLabelId()));
        }
        popReg->AddOperand(regGroup->GetReg(8));
        codeGen.Emit(popReg);
    }

    std::vector<otava::assembly::RegisterGroup*> usedLocalRegs;
    for (const auto& regGroup : assemblyContext.GetRegisterPool().UsedLocalRegs())
    {
        usedLocalRegs.push_back(regGroup);
    }
    std::reverse(usedLocalRegs.begin(), usedLocalRegs.end());
    for (const auto& regGroup : usedLocalRegs)
    {
        otava::assembly::Instruction* popReg = new otava::assembly::Instruction(otava::assembly::OpCode::POP);
        if (!leaderInst)
        {
            leaderInst = popReg;
            leaderInst->SetLabel("@" + std::to_string(codeGen.ExitLabelId()));
        }
        popReg->AddOperand(regGroup->GetReg(8));
        codeGen.Emit(popReg);
    }

    otava::assembly::Instruction* movRsp = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
    if (!leaderInst)
    {
        leaderInst = movRsp;
        leaderInst->SetLabel("@" + std::to_string(codeGen.ExitLabelId()));
    }
    movRsp->AddOperand(assemblyContext.GetGlobalReg(8, otava::assembly::RegisterGroupKind::rsp));
    movRsp->AddOperand(assemblyContext.GetGlobalReg(8, otava::assembly::RegisterGroupKind::rbp));
    codeGen.Emit(movRsp);

    otava::assembly::Instruction* popRbp = new otava::assembly::Instruction(otava::assembly::OpCode::POP);
    popRbp->AddOperand(assemblyContext.GetGlobalReg(8, otava::assembly::RegisterGroupKind::rbp));
    codeGen.Emit(popRbp);

    otava::assembly::Instruction* ret = new otava::assembly::Instruction(otava::assembly::OpCode::RET);
    ret->AddOperand(assemblyContext.MakeLiteral(0, 1));
    codeGen.Emit(ret);
}

} // otava::intermediate
