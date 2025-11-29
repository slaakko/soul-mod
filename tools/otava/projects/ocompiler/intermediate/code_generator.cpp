// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.intermediate.code_generator;

import otava.intermediate.data;
import otava.intermediate.types;
import otava.intermediate.location;
import otava.intermediate.register_allocator;
import otava.intermediate.linear_scan_register_allocator;
import otava.intermediate.error;
import util;

namespace otava::intermediate {

std::expected<bool, int> EmitIntegerLoad(std::int64_t size, const FrameLocation& frameLocation, otava::assembly::RegisterGroup* regGroup, CodeGenerator& codeGenerator);
std::expected<bool, int> EmitFloatingPointLoad(std::int64_t size, const FrameLocation& frameLocation, otava::assembly::RegisterGroup* regGroup, CodeGenerator& codeGenerator);
std::expected<otava::assembly::Register*, int> MakeFloatingPointRegOperand(Value* value, otava::assembly::Register* reg, CodeGenerator& codeGenerator);
std::expected<FrameLocation, int> GetFrameLocation(Value* value, CodeGenerator& codeGenerator);
std::expected<bool, int> EmitFrameLocationOperand(std::int64_t size, const FrameLocation& frameLocation, otava::assembly::Instruction* instruction, CodeGenerator& codeGenerator);

std::expected<bool, int> EmitPrologue(CodeGenerator& codeGenerator)
{
    otava::assembly::Context* assemblyContext = codeGenerator.Ctx()->AssemblyContext();

    int numPushes = 0;
    otava::assembly::Instruction* pushRbp = new otava::assembly::Instruction(otava::assembly::OpCode::PUSH);
    std::expected<otava::assembly::Register*, int> regRv = assemblyContext->GetGlobalReg(8, otava::assembly::RegisterGroupKind::rbp);
    if (!regRv) return std::unexpected<int>(regRv.error());
    pushRbp->AddOperand(*regRv);
    codeGenerator.Emit(pushRbp);
    ++numPushes;

    for (const otava::assembly::RegisterGroup* regGroup : assemblyContext->GetRegisterPool()->UsedLocalRegs())
    {
        otava::assembly::Instruction* pushReg = new otava::assembly::Instruction(otava::assembly::OpCode::PUSH);
        std::expected<const otava::assembly::Register*, int> regRv = regGroup->GetReg(8);
        if (!regRv) return std::unexpected<int>(regRv.error());
        pushReg->AddOperand(*regRv);
        codeGenerator.Emit(pushReg);
        ++numPushes;
    }
    for (const otava::assembly::RegisterGroup* regGroup : assemblyContext->GetRegisterPool()->UsedNonvolatileRegs())
    {
        otava::assembly::Instruction* pushReg = new otava::assembly::Instruction(otava::assembly::OpCode::PUSH);
        std::expected<const otava::assembly::Register*, int> regRv = regGroup->GetReg(8);
        if (!regRv) return std::unexpected<int>(regRv.error());
        pushReg->AddOperand(*regRv);
        codeGenerator.Emit(pushReg);
        ++numPushes;
    }

    Frame& frame = codeGenerator.RegAllocator()->GetFrame();

    if ((numPushes % 2) == 0)
    {
        otava::assembly::Instruction* pushReg = new otava::assembly::Instruction(otava::assembly::OpCode::PUSH);
        std::expected<otava::assembly::Register*, int> regRv = assemblyContext->GetGlobalReg(8, otava::assembly::RegisterGroupKind::rbx, false);
        if (!regRv) return std::unexpected<int>(regRv.error());
        pushReg->AddOperand(*regRv);
        codeGenerator.Emit(pushReg);
        frame.SetRbxPushed();
    }

    int nxmmregs = assemblyContext->GetRegisterPool()->UsedLocalXMMRegs().size() + assemblyContext->GetRegisterPool()->UsedNonvolatileXMMRegs().size();
    frame.SetNumUsedXMMRegs(nxmmregs);
    frame.SetMacroValues(assemblyContext);

    if (frame.Size() > 4096)
    {
        assemblyContext->GetFile()->GetDeclarationSection().AddFunctionDeclaration(new otava::assembly::FunctionDeclaration("__chkstk"));
        otava::assembly::Instruction* movEax = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
        std::expected<otava::assembly::Register*, int> regRv = assemblyContext->GetGlobalReg(4, otava::assembly::RegisterGroupKind::rax);
        if (!regRv) return std::unexpected<int>(regRv.error());
        movEax->AddOperand(*regRv);
        movEax->AddOperand(assemblyContext->MakeIntegerLiteral(frame.Size(), 8));
        codeGenerator.Emit(movEax);
        otava::assembly::Value* chkstk = assemblyContext->MakeSymbol("__chkstk");
        otava::assembly::Instruction* checkStackCall = new otava::assembly::Instruction(otava::assembly::OpCode::CALL);
        checkStackCall->AddOperand(chkstk);
        codeGenerator.Emit(checkStackCall);
    }

    otava::assembly::Instruction* subRsp = new otava::assembly::Instruction(otava::assembly::OpCode::SUB);
    regRv = assemblyContext->GetGlobalReg(8, otava::assembly::RegisterGroupKind::rsp);
    if (!regRv) return std::unexpected<int>(regRv.error());
    subRsp->AddOperand(*regRv);
    subRsp->AddOperand(assemblyContext->MakeIntegerLiteral(frame.Size(), 8));
    codeGenerator.Emit(subRsp);

    if (nxmmregs > 0)
    {
        int xmmRegIndex = 0;
        for (const otava::assembly::RegisterGroup* regGroup : assemblyContext->GetRegisterPool()->UsedLocalXMMRegs())
        {
            otava::assembly::Instruction* movReg = new otava::assembly::Instruction(otava::assembly::OpCode::MOVSD);
            regRv = assemblyContext->GetGlobalReg(8, otava::assembly::RegisterGroupKind::rsp);
            if (!regRv) return std::unexpected<int>(regRv.error());
            std::expected<otava::assembly::Value*, int> srv = assemblyContext->MakeSizePrefix(8, assemblyContext->MakeContent(assemblyContext->MakeBinaryExpr(
                *regRv, assemblyContext->MakeIntegerLiteral(xmmRegIndex * 16, 8), otava::assembly::Operator::add)));
            if (!srv) return std::unexpected<int>(srv.error());
            movReg->AddOperand(*srv);
            std::expected<const otava::assembly::Register*, int> rrv = regGroup->GetReg(16);
            if (!rrv) return std::unexpected<int>(rrv.error());
            movReg->AddOperand(*rrv);
            codeGenerator.Emit(movReg);
            ++xmmRegIndex;
        }
        for (const otava::assembly::RegisterGroup* regGroup : assemblyContext->GetRegisterPool()->UsedNonvolatileXMMRegs())
        {
            otava::assembly::Instruction* movReg = new otava::assembly::Instruction(otava::assembly::OpCode::MOVSD);
            regRv = assemblyContext->GetGlobalReg(8, otava::assembly::RegisterGroupKind::rsp);
            if (!regRv) return std::unexpected<int>(regRv.error());
            std::expected<otava::assembly::Value*, int> srv = assemblyContext->MakeSizePrefix(8, assemblyContext->MakeContent(assemblyContext->MakeBinaryExpr(
                *regRv, assemblyContext->MakeIntegerLiteral(xmmRegIndex * 16, 8), otava::assembly::Operator::add)));
            if (!srv) return std::unexpected<int>(srv.error());
            movReg->AddOperand(*srv);
            std::expected<const otava::assembly::Register*, int> rrv = regGroup->GetReg(16);
            if (!rrv) return std::unexpected<int>(rrv.error());
            movReg->AddOperand(*rrv);
            codeGenerator.Emit(movReg);
            ++xmmRegIndex;
        }
    }

    otava::assembly::Instruction* leaRbp = new otava::assembly::Instruction(otava::assembly::OpCode::LEA);
    regRv = assemblyContext->GetGlobalReg(8, otava::assembly::RegisterGroupKind::rbp);
    if (!regRv) return std::unexpected<int>(regRv.error());
    leaRbp->AddOperand(*regRv);
    regRv = assemblyContext->GetGlobalReg(8, otava::assembly::RegisterGroupKind::rsp);
    if (!regRv) return std::unexpected<int>(regRv.error());
    std::expected<otava::assembly::Value*, int> srv = assemblyContext->MakeSizePrefix(8, assemblyContext->MakeContent(
        assemblyContext->MakeBinaryExpr(*regRv,
            assemblyContext->MakeIntegerLiteral(frame.CalleeParamAreaSize() + frame.XMMSaveRegSize(), 8), otava::assembly::Operator::add)));
    if (!srv) return std::unexpected<int>(srv.error());
    leaRbp->AddOperand(*srv);
    codeGenerator.Emit(leaRbp);
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EmitEpilogue(CodeGenerator& codeGenerator)
{
    otava::assembly::Instruction* leaderInst = nullptr;
    otava::assembly::Context* assemblyContext = codeGenerator.Ctx()->AssemblyContext();

    Frame& frame = codeGenerator.RegAllocator()->GetFrame();

    int nxmmregs = frame.GetNumUsedXMMRegs();

    if (nxmmregs > 0)
    {
        int xmmRegIndex = nxmmregs - 1;

        std::vector<otava::assembly::RegisterGroup*> usedNVXMMRegs;
        for (const otava::assembly::RegisterGroup* regGroup : assemblyContext->GetRegisterPool()->UsedNonvolatileXMMRegs())
        {
            usedNVXMMRegs.push_back(regGroup);
        }
        std::reverse(usedNVXMMRegs.begin(), usedNVXMMRegs.end());
        for (const otava::assembly::RegisterGroup* regGroup : usedNVXMMRegs)
        {
            otava::assembly::Instruction* movReg = new otava::assembly::Instruction(otava::assembly::OpCode::MOVSD);
            if (!leaderInst)
            {
                leaderInst = movReg;
                leaderInst->SetLabel("@" + std::to_string(codeGenerator.ExitLabelId()));
            }
            std::expected<const otava::assembly::Register*, int> rrv = regGroup->GetReg(16);
            if (!rrv) return std::unexpected<int>(rrv.error());
            movReg->AddOperand(*rrv);
            std::expected<otava::assembly::Register*, int> regRv = assemblyContext->GetGlobalReg(8, otava::assembly::RegisterGroupKind::rsp);
            if (!regRv) return std::unexpected<int>(regRv.error());
            std::expected<otava::assembly::Value*, int> srv = assemblyContext->MakeSizePrefix(8, assemblyContext->MakeContent(assemblyContext->MakeBinaryExpr(
                *regRv,
                assemblyContext->MakeIntegerLiteral(xmmRegIndex * 16, 8), otava::assembly::Operator::add)));
            if (!srv) return std::unexpected<int>(srv.error());
            movReg->AddOperand(*srv);
            codeGenerator.Emit(movReg);
            --xmmRegIndex;
        }

        std::vector<otava::assembly::RegisterGroup*> usedLocalXMMRegs;
        for (const otava::assembly::RegisterGroup* regGroup : assemblyContext->GetRegisterPool()->UsedLocalXMMRegs())
        {
            usedLocalXMMRegs.push_back(regGroup);
        }
        std::reverse(usedLocalXMMRegs.begin(), usedLocalXMMRegs.end());
        for (const otava::assembly::RegisterGroup* regGroup : usedLocalXMMRegs)
        {
            otava::assembly::Instruction* movReg = new otava::assembly::Instruction(otava::assembly::OpCode::MOVSD);
            if (!leaderInst)
            {
                leaderInst = movReg;
                leaderInst->SetLabel("@" + std::to_string(codeGenerator.ExitLabelId()));
            }
            std::expected<const otava::assembly::Register*, int> rrv = regGroup->GetReg(16);
            if (!rrv) return std::unexpected<int>(rrv.error());
            movReg->AddOperand(*rrv);
            std::expected<otava::assembly::Register*, int> regRv = assemblyContext->GetGlobalReg(8, otava::assembly::RegisterGroupKind::rsp);
            if (!regRv) return std::unexpected<int>(regRv.error());
            std::expected<otava::assembly::Value*, int> srv = assemblyContext->MakeSizePrefix(8, assemblyContext->MakeContent(assemblyContext->MakeBinaryExpr(
                *regRv, assemblyContext->MakeIntegerLiteral(xmmRegIndex * 16, 8), otava::assembly::Operator::add)));
            if (!srv) return std::unexpected<int>(srv.error());
            movReg->AddOperand(*srv);
            codeGenerator.Emit(movReg);
            --xmmRegIndex;
        }
    }

    otava::assembly::Instruction* leaRsp = new otava::assembly::Instruction(otava::assembly::OpCode::LEA);
    if (!leaderInst)
    {
        leaderInst = leaRsp;
        leaderInst->SetLabel("@" + std::to_string(codeGenerator.ExitLabelId()));
    }
    std::expected<otava::assembly::Register*, int> regRv = assemblyContext->GetGlobalReg(8, otava::assembly::RegisterGroupKind::rsp);
    if (!regRv) return std::unexpected<int>(regRv.error());
    leaRsp->AddOperand(*regRv);
    regRv = assemblyContext->GetGlobalReg(8, otava::assembly::RegisterGroupKind::rbp);
    if (!regRv) return std::unexpected<int>(regRv.error());
    std::expected<otava::assembly::Value*, int> srv = assemblyContext->MakeSizePrefix(8, assemblyContext->MakeContent(
        assemblyContext->MakeBinaryExpr(*regRv,
            assemblyContext->MakeIntegerLiteral(frame.Size() - frame.CalleeParamAreaSize() - frame.XMMSaveRegSize(), 8), otava::assembly::Operator::add)));
    if (!srv) return std::unexpected<int>(srv.error());
    leaRsp->AddOperand(*srv);
    codeGenerator.Emit(leaRsp);

    if (frame.RbxPushed())
    {
        otava::assembly::Instruction* popReg = new otava::assembly::Instruction(otava::assembly::OpCode::POP);
        regRv = assemblyContext->GetGlobalReg(8, otava::assembly::RegisterGroupKind::rbx, false);
        if (!regRv) return std::unexpected<int>(regRv.error());
        popReg->AddOperand(*regRv);
        codeGenerator.Emit(popReg);
    }

    std::vector<otava::assembly::RegisterGroup*> usedNVRegs;
    for (const otava::assembly::RegisterGroup* regGroup : assemblyContext->GetRegisterPool()->UsedNonvolatileRegs())
    {
        usedNVRegs.push_back(regGroup);
    }
    std::reverse(usedNVRegs.begin(), usedNVRegs.end());
    for (const otava::assembly::RegisterGroup* regGroup : usedNVRegs)
    {
        otava::assembly::Instruction* popReg = new otava::assembly::Instruction(otava::assembly::OpCode::POP);
        std::expected<const otava::assembly::Register*, int> rrv = regGroup->GetReg(8);
        if (!rrv) return std::unexpected<int>(rrv.error());
        popReg->AddOperand(*rrv);
        codeGenerator.Emit(popReg);
    }

    std::vector<otava::assembly::RegisterGroup*> usedLocalRegs;
    for (const otava::assembly::RegisterGroup* regGroup : assemblyContext->GetRegisterPool()->UsedLocalRegs())
    {
        usedLocalRegs.push_back(regGroup);
    }
    std::reverse(usedLocalRegs.begin(), usedLocalRegs.end());
    for (const otava::assembly::RegisterGroup* regGroup : usedLocalRegs)
    {
        otava::assembly::Instruction* popReg = new otava::assembly::Instruction(otava::assembly::OpCode::POP);
        std::expected<const otava::assembly::Register*, int> rrv = regGroup->GetReg(8);
        if (!rrv) return std::unexpected<int>(rrv.error());
        popReg->AddOperand(*rrv);
        codeGenerator.Emit(popReg);
    }

    otava::assembly::Instruction* popRbp = new otava::assembly::Instruction(otava::assembly::OpCode::POP);
    regRv = assemblyContext->GetGlobalReg(8, otava::assembly::RegisterGroupKind::rbp);
    if (!regRv) return std::unexpected<int>(regRv.error());
    popRbp->AddOperand(*regRv);
    codeGenerator.Emit(popRbp);

    otava::assembly::Instruction* ret = new otava::assembly::Instruction(otava::assembly::OpCode::RET);
    ret->AddOperand(assemblyContext->MakeIntegerLiteral(0, 1));
    codeGenerator.Emit(ret);
    return std::expected<bool, int>(true);
}

std::expected<FrameLocation, int> GetFrameLocation(Value* value, CodeGenerator& codeGenerator)
{
    Instruction* inst = nullptr;
    if (value->IsRegValue())
    {
        RegValue* regValue = static_cast<RegValue*>(value);
        inst = regValue->Inst();
        if (!inst)
        {
            return codeGenerator.Error("error getting frame location: instruction for reg value not set");
        }
    }
    else if (value->IsInstruction())
    {
        inst = static_cast<Instruction*>(value);
    }
    if (inst)
    {
        Locations locs = codeGenerator.RegAllocator()->GetLocations(inst);
        if ((locs & Locations::frame) != Locations::none)
        {
            FrameLocation frameLocation = codeGenerator.RegAllocator()->GetFrameLocation(inst);
            if (frameLocation.Valid())
            {
                return std::expected<FrameLocation, int>(frameLocation);
            }
            else
            {
                return codeGenerator.Error("error getting frame location: frame location not valid");
            }
        }
        else
        {
            return codeGenerator.Error("error getting frame location: value not in frame");
        }
    }
    else
    {
        return codeGenerator.Error("error getting frame location: invalid value kind");
    }
}

std::expected<bool, int> EmitFrameLocationOperand(std::int64_t size, const FrameLocation& frameLocation, otava::assembly::Instruction* instruction, CodeGenerator& codeGenerator)
{
    otava::assembly::Context* assemblyContext = codeGenerator.Ctx()->AssemblyContext();
    std::expected<otava::assembly::Register*, int> regRv = assemblyContext->GetGlobalReg(8, frameLocation.reg);
    if (!regRv) return std::unexpected<int>(regRv.error());
    otava::assembly::Register* reg = *regRv;
    otava::assembly::Value* frameLoc = assemblyContext->MakeIntegerLiteral(frameLocation.offset, 8);
    if (frameLocation.macro)
    {
        frameLoc = assemblyContext->MakeSymbol(frameLocation.macro->Name());
    }
    std::expected<otava::assembly::Value*, int> srv = assemblyContext->MakeSizePrefix(size, assemblyContext->MakeContent(
        assemblyContext->MakeBinaryExpr(reg, frameLoc, otava::assembly::Operator::add)));
    if (!srv) return std::unexpected<int>(srv.error());
    instruction->AddOperand(*srv);
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EmitIntegerPtrOperand(std::int64_t size, Value* value, otava::assembly::Instruction* instruction, CodeGenerator& codeGenerator)
{
    Instruction* inst = nullptr;
    if (value->IsRegValue())
    {
        RegValue* regValue = static_cast<RegValue*>(value);
        inst = regValue->Inst();
        if (!inst)
        {
            return codeGenerator.Error("error emitting ptr operand: instruction for reg value not set");
        }
    }
    else if (value->IsInstruction())
    {
        inst = static_cast<Instruction*>(value);
    }
    else if (value->IsAddressValue())
    {
        otava::assembly::Context* assemblyContext = codeGenerator.Ctx()->AssemblyContext();
        AddressValue* addressValue = static_cast<AddressValue*>(value);
        GlobalVariable* globalVar = addressValue->GetValue();
        otava::assembly::Instruction* leaInst = new otava::assembly::Instruction(otava::assembly::OpCode::LEA);
        std::expected<otava::assembly::Register*, int> regRv = assemblyContext->GetGlobalReg(8, otava::assembly::RegisterGroupKind::rdx);
        if (!regRv) return std::unexpected<int>(regRv.error());
        leaInst->AddOperand(*regRv);
        leaInst->AddOperand(assemblyContext->MakeSymbol(globalVar->Name()));
        codeGenerator.Emit(leaInst);
        regRv = assemblyContext->GetGlobalReg(8, otava::assembly::RegisterGroupKind::rdx);
        if (!regRv) return std::unexpected<int>(regRv.error());
        std::expected<otava::assembly::Value*, int> srv = assemblyContext->MakeSizePrefix(size, assemblyContext->MakeContent(*regRv));
        if (!srv) return std::unexpected<int>(srv.error());
        instruction->AddOperand(*srv);
        return std::expected<bool, int>(true);
    }
    if (inst)
    {
        if (inst->IsLocalInstruction())
        {
            std::expected<FrameLocation, int> rv = GetFrameLocation(value, codeGenerator);
            if (!rv) return std::unexpected<int>(rv.error());
            FrameLocation frameLocation = *rv;
            std::expected<bool, int> frv = EmitFrameLocationOperand(size, frameLocation, instruction, codeGenerator);
            if (!frv) return frv;
        }
        else
        {
            otava::assembly::Context* assemblyContext = codeGenerator.Ctx()->AssemblyContext();
            std::expected<otava::assembly::Register*, int> rrv = assemblyContext->GetGlobalReg(8, otava::assembly::RegisterGroupKind::rax);
            if (!rrv) return std::unexpected<int>(rrv.error());
            std::expected<otava::assembly::Register*, int> regRv = MakeIntegerRegOperand(value, *rrv, codeGenerator);
            if (!regRv) return std::unexpected<int>(regRv.error());
            std::expected<otava::assembly::Value*, int> srv = assemblyContext->MakeSizePrefix(size, assemblyContext->MakeContent(*regRv));
            if (!srv) return std::unexpected<int>(srv.error());
            otava::assembly::Value* operand = *srv;
            instruction->AddOperand(operand);
        }
    }
    else
    {
        return codeGenerator.Error("error emitting ptr operand: invalid value kind");
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EmitFloatingPointPtrOperand(std::int64_t size, Value* value, otava::assembly::Instruction* instruction, CodeGenerator& codeGenerator)
{
    Instruction* inst = nullptr;
    if (value->IsRegValue())
    {
        RegValue* regValue = static_cast<RegValue*>(value);
        inst = regValue->Inst();
        if (!inst)
        {
            return codeGenerator.Error("error emitting ptr operand: instruction for reg value not set");
        }
    }
    else if (value->IsInstruction())
    {
        inst = static_cast<Instruction*>(value);
    }
    else if (value->IsAddressValue())
    {
        otava::assembly::Context* assemblyContext = codeGenerator.Ctx()->AssemblyContext();
        AddressValue* addressValue = static_cast<AddressValue*>(value);
        GlobalVariable* globalVar = addressValue->GetValue();
        otava::assembly::Instruction* leaInst = new otava::assembly::Instruction(otava::assembly::OpCode::LEA);
        std::expected<otava::assembly::Register*, int> regRv = assemblyContext->GetGlobalReg(8, otava::assembly::RegisterGroupKind::rdx);
        if (!regRv) return std::unexpected<int>(regRv.error());
        leaInst->AddOperand(*regRv);
        leaInst->AddOperand(assemblyContext->MakeSymbol(globalVar->Name()));
        codeGenerator.Emit(leaInst);
        std::expected<otava::assembly::Register*, int> xrv = assemblyContext->GetGlobalReg(8, otava::assembly::RegisterGroupKind::xmm1);
        if (!xrv) return std::unexpected<int>(xrv.error());
        std::expected<otava::assembly::Value*, int> srv = assemblyContext->MakeSizePrefix(size, assemblyContext->MakeContent(*xrv));
        if (!srv) return std::unexpected<int>(srv.error());
        instruction->AddOperand(*srv);
        return std::expected<bool, int>(true);
    }
    if (inst)
    {
        if (inst->IsLocalInstruction())
        {
            std::expected<FrameLocation, int> rv = GetFrameLocation(value, codeGenerator);
            if (!rv) return std::unexpected<int>(rv.error());
            FrameLocation frameLocation = *rv;
            std::expected<bool, int> frv = EmitFrameLocationOperand(size, frameLocation, instruction, codeGenerator);
            if (!frv) return frv;
        }
        else
        {
            otava::assembly::Context* assemblyContext = codeGenerator.Ctx()->AssemblyContext();
            std::expected<otava::assembly::Register*, int> xrv = assemblyContext->GetGlobalReg(16, otava::assembly::RegisterGroupKind::xmm0);
            if (!xrv) return std::unexpected<int>(xrv.error());
            std::expected<otava::assembly::Register*, int> regRv = MakeFloatingPointRegOperand(value, *xrv, codeGenerator);
            if (!regRv) return std::unexpected<int>(regRv.error());
            std::expected<otava::assembly::Value*, int> srv = assemblyContext->MakeSizePrefix(size, assemblyContext->MakeContent(*regRv));
            if (!srv) return std::unexpected<int>(srv.error());
            otava::assembly::Value* operand = *srv;
            instruction->AddOperand(operand);
        }
    }
    return std::expected<bool, int>(true);
}

std::expected<std::int64_t, int> GetIndex(Value* index, CodeGenerator& codeGen)
{
    if (index->IsIntegerValue())
    {
        return std::expected<std::int64_t, int>(index->GetIntegerValue());
    }
    else
    {
        return codeGen.Error("error getting index: invalid index value kind");
    }
    return std::expected<std::int64_t, int>(0);
}

std::expected<std::int64_t, int> GetOffset(Type* type, std::int64_t index, CodeGenerator& codeGenerator)
{
    std::expected<StructureType*, int> rv = type->GetStructurePointeeType(codeGenerator.Span(), codeGenerator.Ctx());
    if (!rv) return std::unexpected<int>(rv.error());
    StructureType* structureType = *rv;
    return structureType->GetFieldOffset(index);
}

std::expected<std::int64_t, int> GetElementSize(Type* type, CodeGenerator& codeGenerator)
{
    std::expected<ArrayType*, int> rv = type->GetArrayPointeeType(codeGenerator.Span(), codeGenerator.Ctx());
    if (!rv) return std::unexpected<int>(rv.error());
    ArrayType* arrayType = *rv;
    return arrayType->ElementType()->Size();
}

std::expected<std::int64_t, int> GetPointeeSize(Type* type, CodeGenerator& codeGenerator)
{
    if (type->IsPointerType())
    {
        PointerType* pointerType = static_cast<PointerType*>(type);
        std::expected<Type*, int> rv = pointerType->RemovePointer(codeGenerator.Span(), codeGenerator.Ctx());
        if (!rv) return std::unexpected<int>(rv.error());
        Type* pointeeType = *rv;
        return std::expected<std::int64_t, int>(pointeeType->Size());
    }
    else
    {
        return codeGenerator.Error("error getting pointee size: pointer type expected");
    }
}

std::expected<otava::assembly::Register*, int> MakeIntegerRegOperand(Value* value, otava::assembly::Register* reg, CodeGenerator& codeGenerator)
{
    std::int64_t size = std::min(value->GetType()->Size(), std::int64_t(reg->Size()));
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
                std::expected<bool, int> rv = EmitIntegerPtrOperand(size, value, leaInst, codeGenerator);
                if (!rv) return std::unexpected<int>(rv.error());
                codeGenerator.Emit(leaInst);
                return std::expected<otava::assembly::Register*, int>(reg);
            }
            Locations locs = codeGenerator.RegAllocator()->GetLocations(inst);
            if ((locs & Locations::reg) != Locations::none)
            {
                otava::assembly::RegisterGroup* regGroup = codeGenerator.RegAllocator()->GetRegisterGroup(inst);
                if (regGroup)
                {
                    return regGroup->GetReg(size);
                }
                else
                {
                    return codeGenerator.Error("error making reg operand: reg group not valid");
                }
            }
            else if ((locs & Locations::frame) != Locations::none)
            {
                FrameLocation frameLocation = codeGenerator.RegAllocator()->GetFrameLocation(inst);
                if (frameLocation.Valid())
                {
                    otava::assembly::Context* assemblyContext = codeGenerator.Ctx()->AssemblyContext();
                    otava::assembly::RegisterGroup* regGroup = assemblyContext->GetRegisterPool()->GetRegisterGroup(reg->Group(), true);
                    std::expected<bool, int > rv = EmitIntegerLoad(size, frameLocation, regGroup, codeGenerator);
                    if (!rv) return std::unexpected<int>(rv.error());
                }
                else
                {
                    return codeGenerator.Error("error making reg operand: frame location not valid");
                }
            }
            else
            {
                return codeGenerator.Error("error making reg operand: no locations for inst");
            }
        }
        else
        {
            return codeGenerator.Error("error making reg operand: instruction for reg value not set");
        }
    }
    else if (value->IsAddressValue())
    {
        AddressValue* v = static_cast<AddressValue*>(value);
        otava::assembly::Instruction* leaInst = new otava::assembly::Instruction(otava::assembly::OpCode::LEA);
        leaInst->AddOperand(reg);
        otava::assembly::Context* assemblyContext = codeGenerator.Ctx()->AssemblyContext();
        leaInst->AddOperand(assemblyContext->MakeSymbol(v->GetValue()->Name()));
        codeGenerator.Emit(leaInst);
    }
    else
    {
        otava::assembly::Instruction* inst = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
        inst->AddOperand(reg);
        otava::assembly::Context* assemblyContext = codeGenerator.Ctx()->AssemblyContext();
        switch (value->Kind())
        {
            case ValueKind::boolValue:
            {
                BoolValue* v = static_cast<BoolValue*>(value);
                inst->AddOperand(assemblyContext->MakeIntegerLiteral(static_cast<std::int64_t>(v->GetValue()), 1));
                break;
            }
            case ValueKind::sbyteValue:
            {
                SByteValue* v = static_cast<SByteValue*>(value);
                inst->AddOperand(assemblyContext->MakeIntegerLiteral(v->GetValue(), 1));
                break;
            }
            case ValueKind::byteValue:
            {
                ByteValue* v = static_cast<ByteValue*>(value);
                inst->AddOperand(assemblyContext->MakeIntegerLiteral(v->GetValue(), 1));
                break;
            }
            case ValueKind::shortValue:
            {
                ShortValue* v = static_cast<ShortValue*>(value);
                inst->AddOperand(assemblyContext->MakeIntegerLiteral(v->GetValue(), 2));
                break;
            }
            case ValueKind::ushortValue:
            {
                UShortValue* v = static_cast<UShortValue*>(value);
                inst->AddOperand(assemblyContext->MakeIntegerLiteral(v->GetValue(), 2));
                break;
            }
            case ValueKind::intValue:
            {
                IntValue* v = static_cast<IntValue*>(value);
                inst->AddOperand(assemblyContext->MakeIntegerLiteral(v->GetValue(), 4));
                break;
            }
            case ValueKind::uintValue:
            {
                UIntValue* v = static_cast<UIntValue*>(value);
                inst->AddOperand(assemblyContext->MakeIntegerLiteral(v->GetValue(), 4));
                break;
            }
            case ValueKind::longValue:
            {
                LongValue* v = static_cast<LongValue*>(value);
                inst->AddOperand(assemblyContext->MakeIntegerLiteral(v->GetValue(), 8));
                break;
            }
            case ValueKind::ulongValue:
            {
                ULongValue* v = static_cast<ULongValue*>(value);
                inst->AddOperand(assemblyContext->MakeIntegerLiteral(v->GetValue(), 8));
                break;
            }
            case ValueKind::nullValue:
            {
                inst->AddOperand(assemblyContext->MakeIntegerLiteral(0, 8));
                break;
            }
            case ValueKind::symbolValue:
            {
                SymbolValue* v = static_cast<SymbolValue*>(value);
                inst->AddOperand(assemblyContext->MakeSymbol(v->GetSymbol()));
                break;
            }
            default:
            {
                return codeGenerator.Error("error making reg operand: not implemented for value kind " + value->KindStr());
            }
        }
        codeGenerator.Emit(inst);

    }
    return std::expected<otava::assembly::Register*, int>(reg);
}

std::expected<otava::assembly::Register*, int> MakeFloatingPointRegOperand(Value* value, otava::assembly::Register* reg, CodeGenerator& codeGenerator)
{
    std::int64_t size = std::min(value->GetType()->Size(), std::int64_t(reg->Size()));
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
                std::expected<bool, int> rv = EmitFloatingPointPtrOperand(size, value, leaInst, codeGenerator);
                if (!rv) return std::unexpected<int>(rv.error());
                codeGenerator.Emit(leaInst);
                return reg;
            }
            Locations locs = codeGenerator.RegAllocator()->GetLocations(inst);
            if ((locs & Locations::reg) != Locations::none)
            {
                otava::assembly::RegisterGroup* regGroup = codeGenerator.RegAllocator()->GetRegisterGroup(inst);
                if (regGroup)
                {
                    return regGroup->GetReg(size);
                }
                else
                {
                    return codeGenerator.Error("error making reg operand: reg group not valid");
                }
            }
            else if ((locs & Locations::frame) != Locations::none)
            {
                FrameLocation frameLocation = codeGenerator.RegAllocator()->GetFrameLocation(inst);
                if (frameLocation.Valid())
                {
                    otava::assembly::Context* assemblyContext = codeGenerator.Ctx()->AssemblyContext();
                    otava::assembly::RegisterGroup* regGroup = assemblyContext->GetRegisterPool()->GetRegisterGroup(reg->Group(), true);
                    std::expected<bool, int> rv = EmitFloatingPointLoad(size, frameLocation, regGroup, codeGenerator);
                    if (!rv) return std::unexpected<int>(rv.error());
                }
                else
                {
                    return codeGenerator.Error("error making reg operand: frame location not valid");
                }
            }
            else
            {
                return codeGenerator.Error("error making reg operand: no locations for inst");
            }
        }
        else
        {
            return codeGenerator.Error("error making reg operand: instruction for reg value not set");
        }
    }
    else if (value->IsAddressValue())
    {
        AddressValue* v = static_cast<AddressValue*>(value);
        otava::assembly::Instruction* leaInst = new otava::assembly::Instruction(otava::assembly::OpCode::LEA);
        leaInst->AddOperand(reg);
        otava::assembly::Context* assemblyContext = codeGenerator.Ctx()->AssemblyContext();
        leaInst->AddOperand(assemblyContext->MakeSymbol(v->GetValue()->Name()));
        codeGenerator.Emit(leaInst);
    }
    else
    {
        otava::assembly::OpCode opCode = otava::assembly::OpCode::NOP;
        if (size == 4)
        {
            opCode = otava::assembly::OpCode::MOVSS;
        }
        else if (size == 8)
        {
            opCode = otava::assembly::OpCode::MOVSD;
        }
        else
        {
            return codeGenerator.Error("error making reg operand: invalid value size");
        }
        otava::assembly::Instruction* inst = new otava::assembly::Instruction(opCode);
        inst->AddOperand(reg);
        otava::assembly::Context* assemblyContext = codeGenerator.Ctx()->AssemblyContext();
        switch (value->Kind())
        {
            case ValueKind::floatValue:
            {
                FloatValue* v = static_cast<FloatValue*>(value);
                std::expected<otava::assembly::Value*, int> rv = assemblyContext->MakeFloatLiteralSymbol(v->GetValue());
                if (!rv) return std::unexpected<int>(rv.error());
                inst->AddOperand(*rv);
                break;
            }
            case ValueKind::doubleValue:
            {
                DoubleValue* v = static_cast<DoubleValue*>(value);
                std::expected<otava::assembly::Value*, int> rv = assemblyContext->MakeDoubleLiteralSymbol(v->GetValue());
                if (!rv) return std::unexpected<int>(rv.error());
                inst->AddOperand(*rv);
                break;
            }
            default:
            {
                return codeGenerator.Error("error making reg operand: invalid value kind " + value->KindStr());
            }
        }
        codeGenerator.Emit(inst);
    }
    return std::expected<otava::assembly::Register*, int>(reg);
}

std::expected<bool, int> EmitIntegerRet(RetInstruction& inst, CodeGenerator& codeGenerator)
{
    otava::assembly::Context* assemblyContext = codeGenerator.Ctx()->AssemblyContext();
    if (inst.ReturnValue())
    {
        otava::assembly::Instruction* movInst = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
        std::int64_t size = inst.ReturnValue()->GetType()->Size();
        std::expected<otava::assembly::Register*, int> regRv = assemblyContext->GetGlobalReg(size, otava::assembly::RegisterGroupKind::rax);
        if (!regRv) return std::unexpected<int>(regRv.error());
        movInst->AddOperand(*regRv);
        regRv = assemblyContext->GetGlobalReg(size, otava::assembly::RegisterGroupKind::rbx);
        if (!regRv) return std::unexpected<int>(regRv.error());
        regRv = MakeIntegerRegOperand(inst.ReturnValue(), *regRv, codeGenerator);
        if (!regRv) return std::unexpected<int>(regRv.error());
        movInst->AddOperand(*regRv);
        codeGenerator.Emit(movInst);
    }
    codeGenerator.EmitJumpToExit(inst);
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EmitFloatingPointRet(RetInstruction& inst, CodeGenerator& codeGenerator)
{
    otava::assembly::Context* assemblyContext = codeGenerator.Ctx()->AssemblyContext();
    if (inst.ReturnValue())
    {
        std::int64_t size = inst.ReturnValue()->GetType()->Size();
        otava::assembly::OpCode opCode = otava::assembly::OpCode::NOP;
        if (size == 4)
        {
            opCode = otava::assembly::OpCode::MOVSS;
        }
        else if (size == 8)
        {
            opCode = otava::assembly::OpCode::MOVSD;
        }
        else
        {
            return codeGenerator.Error("error making floating point ret: invalid value size");
        }
        otava::assembly::Instruction* movInst = new otava::assembly::Instruction(opCode);
        std::expected<otava::assembly::Register*, int> xrv = assemblyContext->GetGlobalReg(16, otava::assembly::RegisterGroupKind::xmm0);
        if (!xrv) return std::unexpected<int>(xrv.error());
        movInst->AddOperand(*xrv);
        xrv = assemblyContext->GetGlobalReg(16, otava::assembly::RegisterGroupKind::xmm1);
        if (!xrv) return std::unexpected<int>(xrv.error());
        std::expected<otava::assembly::Register*, int> regRv = MakeFloatingPointRegOperand(inst.ReturnValue(), *xrv, codeGenerator);
        if (!regRv) return std::unexpected<int>(regRv.error());
        movInst->AddOperand(*regRv);
        codeGenerator.Emit(movInst);
    }
    codeGenerator.EmitJumpToExit(inst);
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EmitSignExtend(SignExtendInstruction& inst, CodeGenerator& codeGenerator)
{
    std::int64_t operandSize = inst.Operand()->GetType()->Size();
    std::int64_t resultSize = inst.Result()->GetType()->Size();
    otava::assembly::Context* assemblyContext = codeGenerator.Ctx()->AssemblyContext();
    otava::assembly::OpCode opCode = otava::assembly::OpCode::MOVSX;
    if (operandSize == 4)
    {
        opCode = otava::assembly::OpCode::MOVSXD;
    }
    otava::assembly::Instruction* movsxInst = new otava::assembly::Instruction(opCode);
    otava::assembly::RegisterGroup* regGroup = codeGenerator.RegAllocator()->GetRegisterGroup(&inst);
    if (regGroup)
    {
        std::expected<otava::assembly::Register*, int> rrv = regGroup->GetReg(resultSize);
        if (!rrv) return std::unexpected<int>(rrv.error());
        otava::assembly::Register* reg = *rrv;
        movsxInst->AddOperand(reg);
        std::expected<otava::assembly::Register*, int> regRv = assemblyContext->GetGlobalReg(operandSize, otava::assembly::RegisterGroupKind::rax);
        if (!regRv) return std::unexpected<int>(regRv.error());
        regRv = MakeIntegerRegOperand(inst.Operand(), *regRv, codeGenerator);
        if (!regRv) return std::unexpected<int>(regRv.error());
        otava::assembly::Register* sourceReg = *regRv;
        movsxInst->AddOperand(sourceReg);
        codeGenerator.Emit(movsxInst);
    }
    else
    {
        return codeGenerator.Error("error emitting sign extend instruction: reg group for inst not found");
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EmitZeroExtend(ZeroExtendInstruction& inst, CodeGenerator& codeGenerator)
{
    std::int64_t operandSize = inst.Operand()->GetType()->Size();
    std::int64_t resultSize = inst.Result()->GetType()->Size();
    otava::assembly::Context* assemblyContext = codeGenerator.Ctx()->AssemblyContext();
    otava::assembly::OpCode opCode = otava::assembly::OpCode::MOV;
    if (operandSize <= 2 && operandSize != resultSize)
    {
        opCode = otava::assembly::OpCode::MOVZX;
    }
    else if (resultSize == 8)
    {
        resultSize = 4;
    }
    otava::assembly::Instruction* movInst = new otava::assembly::Instruction(opCode);
    otava::assembly::RegisterGroup* regGroup = codeGenerator.RegAllocator()->GetRegisterGroup(&inst);
    if (regGroup)
    {
        std::expected< otava::assembly::Register*, int> rrv = regGroup->GetReg(resultSize);
        if (!rrv) return std::unexpected<int>(rrv.error());
        otava::assembly::Register* reg = *rrv;
        movInst->AddOperand(reg);
        std::expected<otava::assembly::Register*, int> regRv = assemblyContext->GetGlobalReg(operandSize, otava::assembly::RegisterGroupKind::rax);
        if (!regRv) return std::unexpected<int>(regRv.error());
        regRv = MakeIntegerRegOperand(inst.Operand(), *regRv, codeGenerator);
        if (!regRv) return std::unexpected<int>(regRv.error());
        otava::assembly::Register* sourceReg = *regRv;
        movInst->AddOperand(sourceReg);
        codeGenerator.Emit(movInst);
    }
    else
    {
        return codeGenerator.Error("error emitting zero extend instruction: reg group for inst not found");
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EmitFloatingPointExtend(FloatingPointExtendInstruction& inst, CodeGenerator& codeGenerator)
{
    otava::assembly::Context* assemblyContext = codeGenerator.Ctx()->AssemblyContext();
    otava::assembly::RegisterGroup* regGroup = codeGenerator.RegAllocator()->GetRegisterGroup(&inst);
    if (regGroup)
    {
        std::int64_t resultSize = inst.Result()->GetType()->Size();
        std::int64_t operandSize = inst.Operand()->GetType()->Size();
        std::expected<otava::assembly::Register*, int> rrv = regGroup->GetReg(resultSize);
        if (!rrv) return std::unexpected<int>(rrv.error());
        otava::assembly::Register* resultReg = *rrv;
        std::expected<otava::assembly::Register*, int> xrv = assemblyContext->GetGlobalReg(operandSize, otava::assembly::RegisterGroupKind::xmm0);
        if (!xrv) return std::unexpected<int>(xrv.error());
        std::expected<otava::assembly::Register*, int> regRv = MakeFloatingPointRegOperand(inst.Operand(), *xrv, codeGenerator);
        if (!regRv) return std::unexpected<int>(regRv.error());
        otava::assembly::Register* sourceReg = *regRv;
        otava::assembly::OpCode opCode = otava::assembly::OpCode::NOP;
        if (resultSize == 8 && operandSize == 4)
        {
            opCode = otava::assembly::OpCode::CVTSS2SD;
        }
        else
        {
            return codeGenerator.Error("error emitting fpextend instruction: invalid floating-point types");
        }
        otava::assembly::Instruction* convertInst = new otava::assembly::Instruction(opCode);
        convertInst->AddOperand(resultReg);
        convertInst->AddOperand(sourceReg);
        codeGenerator.Emit(convertInst);
    }
    else
    {
        return codeGenerator.Error("error emitting fpextend instruction: reg group for inst not found");
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EmitIntegerTruncate(TruncateInstruction& inst, CodeGenerator& codeGenerator)
{
    otava::assembly::Context* assemblyContext = codeGenerator.Ctx()->AssemblyContext();
    otava::assembly::RegisterGroup* regGroup = codeGenerator.RegAllocator()->GetRegisterGroup(&inst);
    if (regGroup)
    {
        std::int64_t resultSize = inst.Result()->GetType()->Size();
        std::expected< otava::assembly::Register*, int> rrv = regGroup->GetReg(resultSize);
        if (!rrv) return std::unexpected<int>(rrv.error());
        otava::assembly::Register* resultReg = *rrv;
        std::expected<otava::assembly::Register*, int> regRv = assemblyContext->GetGlobalReg(resultSize, otava::assembly::RegisterGroupKind::rax);
        if (!regRv) return std::unexpected<int>(regRv.error());
        regRv = MakeIntegerRegOperand(inst.Operand(), *regRv, codeGenerator);
        if (!regRv) return std::unexpected<int>(regRv.error());
        otava::assembly::Register* sourceReg = *regRv;
        otava::assembly::Instruction* movInst = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
        movInst->AddOperand(resultReg);
        movInst->AddOperand(sourceReg);
        codeGenerator.Emit(movInst);
    }
    else
    {
        return codeGenerator.Error("error emitting truncate instruction: reg group for inst not found");
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EmitFloatingPointTruncate(TruncateInstruction& inst, CodeGenerator& codeGenerator)
{
    otava::assembly::Context* assemblyContext = codeGenerator.Ctx()->AssemblyContext();
    otava::assembly::RegisterGroup* regGroup = codeGenerator.RegAllocator()->GetRegisterGroup(&inst);
    if (regGroup)
    {
        std::int64_t resultSize = inst.Result()->GetType()->Size();
        std::int64_t operandSize = inst.Operand()->GetType()->Size();
        std::expected< otava::assembly::Register*, int> rrv = regGroup->GetReg(resultSize);
        if (!rrv) return std::unexpected<int>(rrv.error());
        otava::assembly::Register* resultReg = *rrv;
        std::expected<otava::assembly::Register*, int> xrv = assemblyContext->GetGlobalReg(operandSize, otava::assembly::RegisterGroupKind::xmm0);
        if (!xrv) return std::unexpected<int>(xrv.error());
        std::expected<otava::assembly::Register*, int> regRv = MakeFloatingPointRegOperand(inst.Operand(), *xrv, codeGenerator);
        if (!regRv) return std::unexpected<int>(regRv.error());
        otava::assembly::Register* sourceReg = *regRv;
        otava::assembly::OpCode opCode = otava::assembly::OpCode::NOP;
        if (resultSize == 4 && operandSize == 8)
        {
            opCode = otava::assembly::OpCode::CVTSD2SS;
        }
        else
        {
            return codeGenerator.Error("error emitting truncate instruction: invalid floating-point truncation types");
        }
        otava::assembly::Instruction* convertInst = new otava::assembly::Instruction(opCode);
        convertInst->AddOperand(resultReg);
        convertInst->AddOperand(sourceReg);
        codeGenerator.Emit(convertInst);
    }
    else
    {
        return codeGenerator.Error("error emitting truncate instruction: reg group for inst not found");
    }
}

std::expected<bool, int> EmitIntegerBinOpInst(BinaryInstruction& inst, CodeGenerator& codeGenerator)
{
    otava::assembly::Context* assemblyContext = codeGenerator.Ctx()->AssemblyContext();
    std::int64_t size = inst.GetType()->Size();
    otava::assembly::OpCode opCode = otava::assembly::OpCode::ADD;
    bool smallMod = false;
    bool smallDiv = false;
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
            std::expected<otava::assembly::Register*, int> regRv = assemblyContext->GetGlobalReg(size, otava::assembly::RegisterGroupKind::rax);
            if (!regRv) return std::unexpected<int>(regRv.error());
            regRv = MakeIntegerRegOperand(inst.Left(), *regRv, codeGenerator);
            if (!regRv) return std::unexpected<int>(regRv.error());
            leftOperandReg = *regRv;
            instruction->AddOperand(leftOperandReg);
            regRv = assemblyContext->GetGlobalReg(size, otava::assembly::RegisterGroupKind::rbx);
            if (!regRv) return std::unexpected<int>(regRv.error());
            regRv = MakeIntegerRegOperand(inst.Right(), *regRv, codeGenerator);
            if (!regRv) return std::unexpected<int>(regRv.error());
            rightOperandReg = *regRv;
            instruction->AddOperand(rightOperandReg);
            resultOperandReg = leftOperandReg;
            break;
        }
        case OpCode::div_:
        {
            std::expected<otava::assembly::Register*, int> regRv = assemblyContext->GetGlobalReg(size, otava::assembly::RegisterGroupKind::rdx);
            if (!regRv) return std::unexpected<int>(regRv.error());
            otava::assembly::Register* rdx = *regRv;
            otava::assembly::Instruction* xorInst = new otava::assembly::Instruction(otava::assembly::OpCode::XOR);
            xorInst->AddOperand(rdx);
            xorInst->AddOperand(rdx);
            codeGenerator.Emit(xorInst);
            regRv = assemblyContext->GetGlobalReg(size, otava::assembly::RegisterGroupKind::rax);
            if (!regRv) return std::unexpected<int>(regRv.error());
            otava::assembly::Register* rax = *regRv;
            regRv = MakeIntegerRegOperand(inst.Left(), rax, codeGenerator);
            if (!regRv) return std::unexpected<int>(regRv.error());
            leftOperandReg = *regRv;
            if (leftOperandReg->Group() != otava::assembly::RegisterGroupKind::rax)
            {
                otava::assembly::Instruction* movInstruction = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
                movInstruction->AddOperand(rax);
                movInstruction->AddOperand(leftOperandReg);
                codeGenerator.Emit(movInstruction);
            }
            resultOperandReg = rax;
            if (size < 2)
            {
                smallDiv = true;
            }
            regRv = assemblyContext->GetGlobalReg(size, otava::assembly::RegisterGroupKind::rbx);
            if (!regRv) return std::unexpected<int>(regRv.error());
            regRv = MakeIntegerRegOperand(inst.Right(), *regRv, codeGenerator);
            if (!regRv) return std::unexpected<int>(regRv.error());
            rightOperandReg = *regRv;
            instruction->AddOperand(rightOperandReg);
            break;
        }
        case OpCode::mul:
        {
            std::expected<otava::assembly::Register*, int> regRv = assemblyContext->GetGlobalReg(size, otava::assembly::RegisterGroupKind::rax);
            if (!regRv) return std::unexpected<int>(regRv.error());
            otava::assembly::Register* rax = *regRv;
            regRv = MakeIntegerRegOperand(inst.Left(), rax, codeGenerator);
            if (!regRv) return std::unexpected<int>(regRv.error());
            leftOperandReg = *regRv;
            if (leftOperandReg->Group() != otava::assembly::RegisterGroupKind::rax)
            {
                otava::assembly::Instruction* movInstruction = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
                movInstruction->AddOperand(rax);
                movInstruction->AddOperand(leftOperandReg);
                codeGenerator.Emit(movInstruction);
            }
            resultOperandReg = rax;
            regRv = assemblyContext->GetGlobalReg(size, otava::assembly::RegisterGroupKind::rbx);
            if (!regRv) return std::unexpected<int>(regRv.error());
            regRv = MakeIntegerRegOperand(inst.Right(), *regRv, codeGenerator);
            if (!regRv) return std::unexpected<int>(regRv.error());
            rightOperandReg = *regRv;
            instruction->AddOperand(rightOperandReg);
            break;
        }
        case OpCode::mod:
        {
            std::expected<otava::assembly::Register*, int> regRv = assemblyContext->GetGlobalReg(size, otava::assembly::RegisterGroupKind::rdx);
            if (!regRv) return std::unexpected<int>(regRv.error());
            otava::assembly::Register* rdx = *regRv;
            otava::assembly::Instruction* xorInst = new otava::assembly::Instruction(otava::assembly::OpCode::XOR);
            xorInst->AddOperand(rdx);
            xorInst->AddOperand(rdx);
            codeGenerator.Emit(xorInst);
            regRv = assemblyContext->GetGlobalReg(size, otava::assembly::RegisterGroupKind::rax);
            if (!regRv) return std::unexpected<int>(regRv.error());
            otava::assembly::Register* rax = *regRv;
            regRv = MakeIntegerRegOperand(inst.Left(), rax, codeGenerator);
            if (!regRv) return std::unexpected<int>(regRv.error());
            leftOperandReg = *regRv;
            if (leftOperandReg->Group() != otava::assembly::RegisterGroupKind::rax)
            {
                otava::assembly::Instruction* movInstruction = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
                movInstruction->AddOperand(rax);
                movInstruction->AddOperand(leftOperandReg);
                codeGenerator.Emit(movInstruction);
            }
            regRv = assemblyContext->GetGlobalReg(size, otava::assembly::RegisterGroupKind::rbx);
            if (!regRv) return std::unexpected<int>(regRv.error());
            regRv = MakeIntegerRegOperand(inst.Right(), *regRv, codeGenerator);
            if (!regRv) return std::unexpected<int>(regRv.error());
            rightOperandReg = *regRv;
            instruction->AddOperand(rightOperandReg);
            if (size > 1)
            {
                resultOperandReg = rdx;
            }
            else
            {
                resultOperandReg = rax;
                smallMod = true;
            }
            break;
        }
        case OpCode::shl:
        case OpCode::shr:
        {
            std::expected<otava::assembly::Register*, int> regRv = assemblyContext->GetGlobalReg(size, otava::assembly::RegisterGroupKind::rax);
            if (!regRv) return std::unexpected<int>(regRv.error());
            regRv = MakeIntegerRegOperand(inst.Left(), *regRv, codeGenerator);
            if (!regRv) return std::unexpected<int>(regRv.error());
            leftOperandReg = *regRv;
            regRv = assemblyContext->GetGlobalReg(1, otava::assembly::RegisterGroupKind::rcx);
            if (!regRv) return std::unexpected<int>(regRv.error());
            otava::assembly::Register* cl = *regRv;
            regRv = MakeIntegerRegOperand(inst.Right(), cl, codeGenerator);
            if (!regRv) return std::unexpected<int>(regRv.error());
            rightOperandReg = *regRv;
            if (rightOperandReg->Group() != otava::assembly::RegisterGroupKind::rcx)
            {
                otava::assembly::Instruction* movInstruction = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
                movInstruction->AddOperand(cl);
                movInstruction->AddOperand(rightOperandReg);
                codeGenerator.Emit(movInstruction);
            }
            instruction->AddOperand(leftOperandReg);
            instruction->AddOperand(cl);
            resultOperandReg = leftOperandReg;
            break;
        }
    }
    if (size == 1 && (smallMod || smallDiv) && inst.GetType()->IsSignedType())
    {
        otava::assembly::Instruction* cbwInstruction = new otava::assembly::Instruction(otava::assembly::OpCode::CBW);
        codeGenerator.Emit(cbwInstruction);
    }
    else if (size == 2 && (inst.GetOpCode() == OpCode::div_ || inst.GetOpCode() == OpCode::mod) && inst.GetType()->IsSignedType())
    {
        otava::assembly::Instruction* cwdInstruction = new otava::assembly::Instruction(otava::assembly::OpCode::CWD);
        codeGenerator.Emit(cwdInstruction);
    }
    else if (size == 4 && (inst.GetOpCode() == OpCode::div_ || inst.GetOpCode() == OpCode::mod) && inst.GetType()->IsSignedType())
    {
        otava::assembly::Instruction* cdqInstruction = new otava::assembly::Instruction(otava::assembly::OpCode::CDQ);
        codeGenerator.Emit(cdqInstruction);
    }
    else if (size == 8 && (inst.GetOpCode() == OpCode::div_ || inst.GetOpCode() == OpCode::mod) && inst.GetType()->IsSignedType())
    {
        otava::assembly::Instruction* cqoInstruction = new otava::assembly::Instruction(otava::assembly::OpCode::CQO);
        codeGenerator.Emit(cqoInstruction);
    }
    codeGenerator.Emit(instruction);
    if (smallMod)
    {
        otava::assembly::Instruction* shrInstruction = new otava::assembly::Instruction(otava::assembly::OpCode::SHR);
        std::expected<otava::assembly::Register*, int> regRv = assemblyContext->GetGlobalReg(2, otava::assembly::RegisterGroupKind::rax);
        if (!regRv) return std::unexpected<int>(regRv.error());
        shrInstruction->AddOperand(*regRv);
        shrInstruction->AddOperand(assemblyContext->MakeIntegerLiteral(8, 1));
        codeGenerator.Emit(shrInstruction);
    }
    otava::assembly::Instruction* movInstruction = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
    otava::assembly::RegisterGroup* regGroup = codeGenerator.RegAllocator()->GetRegisterGroup(&inst);
    if (regGroup)
    {
        if (smallDiv)
        {
            otava::assembly::Instruction* xorInstruction = new otava::assembly::Instruction(otava::assembly::OpCode::XOR);
            std::expected<otava::assembly::Register*, int> regRv = assemblyContext->GetGlobalReg(
                otava::assembly::highByteRegSize, otava::assembly::RegisterGroupKind::rax);
            if (!regRv) return std::unexpected<int>(regRv.error());
            otava::assembly::Register* ah = *regRv;
            xorInstruction->AddOperand(ah);
            xorInstruction->AddOperand(ah);
            codeGenerator.Emit(xorInstruction);
        }
        std::expected<otava::assembly::Register*, int> rrv = regGroup->GetReg(size);
        if (!rrv) return std::unexpected<int>(rrv.error());
        movInstruction->AddOperand(*rrv);
        movInstruction->AddOperand(resultOperandReg);
        codeGenerator.Emit(movInstruction);
    }
    else
    {
        return codeGenerator.Error("error emitting integer binary operation instruction: reg group for inst not found");
    }
}

std::expected<bool, int> EmitFloatingPointBinOpInst(BinaryInstruction& inst, CodeGenerator& codeGenerator)
{
    otava::assembly::Context* assemblyContext = codeGenerator.Ctx()->AssemblyContext();
    std::int64_t size = inst.GetType()->Size();
    if (size != 4 && size != 8)
    {
        return codeGenerator.Error("error emitting integer binary operation instruction: invalid size");
    }
    otava::assembly::OpCode opCode = otava::assembly::OpCode::NOP;
    switch (inst.GetOpCode())
    {
        case OpCode::add:
        {
            if (size == 4)
            {
                opCode = otava::assembly::OpCode::ADDSS;
            }
            else if (size == 8)
            {
                opCode = otava::assembly::OpCode::ADDSD;
            }
            break;
        }
        case OpCode::sub:
        {
            if (size == 4)
            {
                opCode = otava::assembly::OpCode::SUBSS;
            }
            else if (size == 8)
            {
                opCode = otava::assembly::OpCode::SUBSD;
            }
            break;
        }
        case OpCode::mul:
        {
            if (size == 4)
            {
                opCode = otava::assembly::OpCode::MULSS;
            }
            else if (size == 8)
            {
                opCode = otava::assembly::OpCode::MULSD;
            }
            break;
        }
        case OpCode::div_:
        {
            if (size == 4)
            {
                opCode = otava::assembly::OpCode::DIVSS;
            }
            else if (size == 8)
            {
                opCode = otava::assembly::OpCode::DIVSD;
            }
            break;
        }
    }
    otava::assembly::Instruction* instruction = new otava::assembly::Instruction(opCode);
    std::expected<otava::assembly::Register*, int> xrv = assemblyContext->GetGlobalReg(size, otava::assembly::RegisterGroupKind::xmm0);
    if (!xrv) return std::unexpected<int>(xrv.error());
    std::expected<otava::assembly::Register*, int> regRv = MakeFloatingPointRegOperand(inst.Left(), *xrv, codeGenerator);
    if (!regRv) return std::unexpected<int>(regRv.error());
    otava::assembly::Register* leftOperandReg = *regRv;
    instruction->AddOperand(leftOperandReg);
    xrv = assemblyContext->GetGlobalReg(size, otava::assembly::RegisterGroupKind::xmm1);
    if (!xrv) return std::unexpected<int>(xrv.error());
    regRv = MakeFloatingPointRegOperand(inst.Right(), *xrv, codeGenerator);
    if (!regRv) return std::unexpected<int>(regRv.error());
    otava::assembly::Register* rightOperandReg = *regRv;
    instruction->AddOperand(rightOperandReg);
    otava::assembly::Register* resultOperandReg = leftOperandReg;
    codeGenerator.Emit(instruction);
    otava::assembly::OpCode movOpCode = otava::assembly::OpCode::NOP;
    if (size == 4)
    {
        movOpCode = otava::assembly::OpCode::MOVSS;
    }
    else if (size == 8)
    {
        movOpCode = otava::assembly::OpCode::MOVSD;
    }
    otava::assembly::Instruction* movInstruction = new otava::assembly::Instruction(movOpCode);
    otava::assembly::RegisterGroup* regGroup = codeGenerator.RegAllocator()->GetRegisterGroup(&inst);
    if (regGroup)
    {
        std::expected<otava::assembly::Register*, int> rrv = regGroup->GetReg(size);
        if (!rrv) return std::unexpected<int>(rrv.error());
        movInstruction->AddOperand(*rrv);
        movInstruction->AddOperand(resultOperandReg);
        codeGenerator.Emit(movInstruction);
    }
    else
    {
        return codeGenerator.Error("error emitting floating-point binary operation instruction: reg group for inst not found");
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EmitBitcast(BitcastInstruction& inst, CodeGenerator& codeGenerator)
{
    otava::assembly::Context* assemblyContext = codeGenerator.Ctx()->AssemblyContext();
    otava::assembly::RegisterGroup* regGroup = codeGenerator.RegAllocator()->GetRegisterGroup(&inst);
    if (regGroup)
    {
        Type* type = inst.Operand()->GetType();
        std::int64_t size = type->Size();
        std::expected<otava::assembly::Register*, int> rrv = regGroup->GetReg(size);
        if (!rrv) return std::unexpected<int>(rrv.error());
        otava::assembly::Register* resultReg = *rrv;
        std::expected<otava::assembly::Register*, int> regRv = assemblyContext->GetGlobalReg(size, otava::assembly::RegisterGroupKind::rax);
        if (!regRv) return std::unexpected<int>(regRv.error());
        regRv = MakeIntegerRegOperand(inst.Operand(), *regRv, codeGenerator);
        if (!regRv) return std::unexpected<int>(regRv.error());
        otava::assembly::Register* sourceReg = *regRv;
        otava::assembly::Instruction* movInst = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
        movInst->AddOperand(resultReg);
        movInst->AddOperand(sourceReg);
        codeGenerator.Emit(movInst);
    }
    else
    {
        return codeGenerator.Error("error emitting bitcast instruction: reg group for inst not found");
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EmitIntToFloat(IntToFloatInstruction& inst, CodeGenerator& codeGenerator)
{
    otava::assembly::Context* assemblyContext = codeGenerator.Ctx()->AssemblyContext();
    Value* operand = inst.Operand();
    Type* operandType = operand->GetType();
    std::int64_t operandSize = operandType->Size();
    Type* resultType = inst.Result()->GetType();
    std::int64_t resultSize = resultType->Size();
    std::expected<otava::assembly::Register*, int> regRv = assemblyContext->GetGlobalReg(operandSize, otava::assembly::RegisterGroupKind::rbx);
    if (!regRv) return std::unexpected<int>(regRv.error());
    regRv = MakeIntegerRegOperand(inst.Operand(), *regRv, codeGenerator);
    if (!regRv) return std::unexpected<int>(regRv.error());
    otava::assembly::Register* sourceReg = *regRv;
    if (operandSize < 4)
    {
        otava::assembly::OpCode opCode = otava::assembly::OpCode::MOVSX;
        if (operandType->IsUnsignedType())
        {
            opCode = otava::assembly::OpCode::MOVZX;
        }
        otava::assembly::Instruction* extendInst = new otava::assembly::Instruction(opCode);
        regRv = assemblyContext->GetGlobalReg(4, otava::assembly::RegisterGroupKind::rax);
        if (!regRv) return std::unexpected<int>(regRv.error());
        otava::assembly::Register* rax = *regRv;
        extendInst->AddOperand(rax);
        extendInst->AddOperand(sourceReg);
        codeGenerator.Emit(extendInst);
        sourceReg = rax;
    }
    otava::assembly::RegisterGroup* regGroup = codeGenerator.RegAllocator()->GetRegisterGroup(&inst);
    if (regGroup)
    {
        std::expected<otava::assembly::Register*, int> rrv = regGroup->GetReg(resultSize);
        if (!rrv) return std::unexpected<int>(rrv.error());
        otava::assembly::Register* resultReg = *rrv;
        otava::assembly::OpCode opCode = otava::assembly::OpCode::NOP;
        if (resultSize == 4)
        {
            opCode = otava::assembly::OpCode::CVTSI2SS;
        }
        else if (resultSize == 8)
        {
            opCode = otava::assembly::OpCode::CVTSI2SD;
        }
        else
        {
            return codeGenerator.Error("error emitting inttofloat instruction: invalid result size");
        }
        otava::assembly::Instruction* convertInstruction = new otava::assembly::Instruction(opCode);
        convertInstruction->AddOperand(resultReg);
        convertInstruction->AddOperand(sourceReg);
        codeGenerator.Emit(convertInstruction);
    }
    else
    {
        return codeGenerator.Error("error emitting inttofloat instruction: reg group for inst not found");
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EmitFloatToInt(FloatToIntInstruction& inst, CodeGenerator& codeGenerator)
{
    otava::assembly::Context* assemblyContext = codeGenerator.Ctx()->AssemblyContext();
    Value* operand = inst.Operand();
    Type* operandType = operand->GetType();
    std::int64_t operandSize = operandType->Size();
    Type* resultType = inst.Result()->GetType();
    std::int64_t resultSize = resultType->Size();
    otava::assembly::RegisterGroup* regGroup = codeGenerator.RegAllocator()->GetRegisterGroup(&inst);
    if (regGroup)
    {
        std::expected<otava::assembly::Register*, int> rrv = regGroup->GetReg(resultSize);
        if (!rrv) return std::unexpected<int>(rrv.error());
        otava::assembly::Register* resultReg = *rrv;
        std::expected<otava::assembly::Register*, int> xrv = assemblyContext->GetGlobalReg(operandSize, otava::assembly::RegisterGroupKind::xmm0);
        if (!xrv) return std::unexpected<int>(xrv.error());
        std::expected<otava::assembly::Register*, int> regRv = MakeFloatingPointRegOperand(inst.Operand(), *xrv, codeGenerator);
        if (!regRv) return std::unexpected<int>(regRv.error());
        otava::assembly::Register* sourceReg = *regRv;
        otava::assembly::OpCode opCode = otava::assembly::OpCode::NOP;
        if (operandSize == 4)
        {
            opCode = otava::assembly::OpCode::CVTTSS2SI;
        }
        else if (operandSize == 8)
        {
            opCode = otava::assembly::OpCode::CVTTSD2SI;
        }
        else
        {
            return codeGenerator.Error("error emitting floattoint instruction: invalid operand size");
        }
        otava::assembly::Instruction* convertInstruction = new otava::assembly::Instruction(opCode);
        convertInstruction->AddOperand(resultReg);
        convertInstruction->AddOperand(sourceReg);
        codeGenerator.Emit(convertInstruction);
    }
    else
    {
        return codeGenerator.Error("error emitting floattoint instruction: reg group for inst not found");
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EmitIntToPtr(IntToPtrInstruction& inst, CodeGenerator& codeGenerator)
{
    otava::assembly::Context* assemblyContext = codeGenerator.Ctx()->AssemblyContext();
    otava::assembly::RegisterGroup* regGroup = codeGenerator.RegAllocator()->GetRegisterGroup(&inst);
    if (regGroup)
    {
        Type* type = inst.Operand()->GetType();
        std::int64_t size = type->Size();
        std::expected<otava::assembly::Register*, int> rrv = regGroup->GetReg(size);
        if (!rrv) return std::unexpected<int>(rrv.error());
        otava::assembly::Register* resultReg = *rrv;
        std::expected<otava::assembly::Register*, int> regRv = assemblyContext->GetGlobalReg(size, otava::assembly::RegisterGroupKind::rax);
        if (!regRv) return std::unexpected<int>(regRv.error());
        regRv = MakeIntegerRegOperand(inst.Operand(), *regRv, codeGenerator);
        if (!regRv) return std::unexpected<int>(regRv.error());
        otava::assembly::Register* sourceReg = *regRv;
        otava::assembly::Instruction* movInst = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
        movInst->AddOperand(resultReg);
        movInst->AddOperand(sourceReg);
        codeGenerator.Emit(movInst);
    }
    else
    {
        return codeGenerator.Error("error emitting inttoptr instruction: reg group for inst not found");
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EmitPtrToInt(PtrToIntInstruction& inst, CodeGenerator& codeGenerator)
{
    otava::assembly::Context* assemblyContext = codeGenerator.Ctx()->AssemblyContext();
    otava::assembly::RegisterGroup* regGroup = codeGenerator.RegAllocator()->GetRegisterGroup(&inst);
    if (regGroup)
    {
        Type* type = inst.Operand()->GetType();
        std::int64_t size = type->Size();
        std::expected<otava::assembly::Register*, int> rrv = regGroup->GetReg(size);
        if (!rrv) return std::unexpected<int>(rrv.error());
        otava::assembly::Register* resultReg = *rrv;
        std::expected<otava::assembly::Register*, int> regRv = assemblyContext->GetGlobalReg(size, otava::assembly::RegisterGroupKind::rax);
        if (!regRv) return std::unexpected<int>(regRv.error());
        regRv = MakeIntegerRegOperand(inst.Operand(), *regRv, codeGenerator);
        if (!regRv) return std::unexpected<int>(regRv.error());
        otava::assembly::Register* sourceReg = *regRv;
        otava::assembly::Instruction* movInst = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
        movInst->AddOperand(resultReg);
        movInst->AddOperand(sourceReg);
        codeGenerator.Emit(movInst);
    }
    else
    {
        return codeGenerator.Error("error emitting ptrtoint instruction: reg group for inst not found");
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EmitIntegerEqual(EqualInstruction& inst, CodeGenerator& codeGenerator)
{
    otava::assembly::Context* assemblyContext = codeGenerator.Ctx()->AssemblyContext();
    otava::assembly::RegisterGroup* regGroup = codeGenerator.RegAllocator()->GetRegisterGroup(&inst);
    if (regGroup)
    {
        std::int64_t resultSize = 1;
        std::int64_t size = inst.Left()->GetType()->Size();
        std::expected<otava::assembly::Register*, int> rrv = regGroup->GetReg(resultSize);
        if (!rrv) return std::unexpected<int>(rrv.error());
        otava::assembly::Register* resultReg = *rrv;
        otava::assembly::Instruction* cmpInstruction = new otava::assembly::Instruction(otava::assembly::OpCode::CMP);
        std::expected<otava::assembly::Register*, int> regRv = assemblyContext->GetGlobalReg(size, otava::assembly::RegisterGroupKind::rcx);
        if (!regRv) return std::unexpected<int>(regRv.error());
        regRv = MakeIntegerRegOperand(inst.Left(), *regRv, codeGenerator);
        if (!regRv) return std::unexpected<int>(regRv.error());
        otava::assembly::Register* leftOperandReg = *regRv;
        cmpInstruction->AddOperand(leftOperandReg);
        regRv = assemblyContext->GetGlobalReg(size, otava::assembly::RegisterGroupKind::rdx);
        if (!regRv) return std::unexpected<int>(regRv.error());
        regRv = MakeIntegerRegOperand(inst.Right(), *regRv, codeGenerator);
        if (!regRv) return std::unexpected<int>(regRv.error());
        otava::assembly::Register* rightOperandReg = *regRv;
        cmpInstruction->AddOperand(rightOperandReg);
        codeGenerator.Emit(cmpInstruction);
        otava::assembly::Instruction* setInst = new otava::assembly::Instruction(otava::assembly::OpCode::SETE);
        setInst->AddOperand(resultReg);
        codeGenerator.Emit(setInst);
    }
    else
    {
        return codeGenerator.Error("error emitting equal instruction: reg group for inst not found");
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EmitFloatingPointEqual(EqualInstruction& inst, CodeGenerator& codeGenerator)
{
    otava::assembly::Context* assemblyContext = codeGenerator.Ctx()->AssemblyContext();
    Value* leftOperand = inst.Left();
    Type* leftOperandType = leftOperand->GetType();
    std::int64_t operandSize = leftOperandType->Size();
    otava::assembly::RegisterGroup* regGroup = codeGenerator.RegAllocator()->GetRegisterGroup(&inst);
    if (regGroup)
    {
        std::int64_t resultSize = 1;
        std::expected<otava::assembly::Register*, int> rrv = regGroup->GetReg(resultSize);
        if (!rrv) return std::unexpected<int>(rrv.error());
        otava::assembly::Register* resultReg = *rrv;
        otava::assembly::OpCode opCode = otava::assembly::OpCode::NOP;
        if (operandSize == 4)
        {
            opCode = otava::assembly::OpCode::UCOMISS;
        }
        else if (operandSize == 8)
        {
            opCode = otava::assembly::OpCode::UCOMISD;
        }
        else
        {
            return codeGenerator.Error("error emitting equal instruction: invalid operand size");
        }
        otava::assembly::Instruction* instruction = new otava::assembly::Instruction(opCode);
        std::expected<otava::assembly::Register*, int> xrv = assemblyContext->GetGlobalReg(operandSize, otava::assembly::RegisterGroupKind::xmm1);
        if (!xrv) return std::unexpected<int>(xrv.error());
        std::expected<otava::assembly::Register*, int> regRv = MakeFloatingPointRegOperand(inst.Left(), *xrv, codeGenerator);
        if (!regRv) return std::unexpected<int>(regRv.error());
        otava::assembly::Register* leftOperandReg = *regRv;
        instruction->AddOperand(leftOperandReg);
        xrv = assemblyContext->GetGlobalReg(operandSize, otava::assembly::RegisterGroupKind::xmm2);
        if (!xrv) return std::unexpected<int>(xrv.error());
        regRv = MakeFloatingPointRegOperand(inst.Right(), *xrv, codeGenerator);
        if (!regRv) return std::unexpected<int>(regRv.error());
        otava::assembly::Register* rightOperandReg = *regRv;
        instruction->AddOperand(rightOperandReg);
        codeGenerator.Emit(instruction);
        otava::assembly::Instruction* setInst = new otava::assembly::Instruction(otava::assembly::OpCode::SETE);
        setInst->AddOperand(resultReg);
        codeGenerator.Emit(setInst);
    }
    else
    {
        return codeGenerator.Error("error emitting equal instruction: reg group for inst not found");
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EmitIntegerLess(LessInstruction& inst, CodeGenerator& codeGenerator)
{
    otava::assembly::Context* assemblyContext = codeGenerator.Ctx()->AssemblyContext();
    otava::assembly::RegisterGroup* regGroup = codeGenerator.RegAllocator()->GetRegisterGroup(&inst);
    if (regGroup)
    {
        std::int64_t resultSize = 1;
        std::int64_t size = inst.Left()->GetType()->Size();
        std::expected<otava::assembly::Register*, int> rrv = regGroup->GetReg(resultSize);
        if (!rrv) return std::unexpected<int>(rrv.error());
        otava::assembly::Register* resultReg = *rrv;
        otava::assembly::Instruction* cmpInstruction = new otava::assembly::Instruction(otava::assembly::OpCode::CMP);
        std::expected<otava::assembly::Register*, int> regRv = assemblyContext->GetGlobalReg(size, otava::assembly::RegisterGroupKind::rcx);
        if (!regRv) return std::unexpected<int>(regRv.error());
        regRv = MakeIntegerRegOperand(inst.Left(), *regRv, codeGenerator);
        if (!regRv) return std::unexpected<int>(regRv.error());
        otava::assembly::Register* leftOperandReg = *regRv;
        cmpInstruction->AddOperand(leftOperandReg);
        regRv = assemblyContext->GetGlobalReg(size, otava::assembly::RegisterGroupKind::rdx);
        if (!regRv) return std::unexpected<int>(regRv.error());
        regRv = MakeIntegerRegOperand(inst.Right(), *regRv, codeGenerator);
        if (!regRv) return std::unexpected<int>(regRv.error());
        otava::assembly::Register* rightOperandReg = *regRv;
        cmpInstruction->AddOperand(rightOperandReg);
        codeGenerator.Emit(cmpInstruction);
        otava::assembly::OpCode opCode = otava::assembly::OpCode::SETL;
        if (inst.Left()->GetType()->IsUnsignedType())
        {
            opCode = otava::assembly::OpCode::SETC;
        }
        otava::assembly::Instruction* setInst = new otava::assembly::Instruction(opCode);
        setInst->AddOperand(resultReg);
        codeGenerator.Emit(setInst);
    }
    else
    {
        return codeGenerator.Error("error emitting less instruction: reg group for inst not found");
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EmitFloatingPointLess(LessInstruction& inst, CodeGenerator& codeGenerator)
{
    otava::assembly::Context* assemblyContext = codeGenerator.Ctx()->AssemblyContext();
    Value* leftOperand = inst.Left();
    Type* leftOperandType = leftOperand->GetType();
    std::int64_t operandSize = leftOperandType->Size();
    otava::assembly::RegisterGroup* regGroup = codeGenerator.RegAllocator()->GetRegisterGroup(&inst);
    if (regGroup)
    {
        std::int64_t resultSize = 1;
        std::expected<otava::assembly::Register*, int> rrv = regGroup->GetReg(resultSize);
        if (!rrv) return std::unexpected<int>(rrv.error());
        otava::assembly::Register* resultReg = *rrv;
        otava::assembly::OpCode opCode = otava::assembly::OpCode::NOP;
        if (operandSize == 4)
        {
            opCode = otava::assembly::OpCode::COMISS;
        }
        else if (operandSize == 8)
        {
            opCode = otava::assembly::OpCode::COMISD;
        }
        else
        {
            return codeGenerator.Error("error emitting less instruction: invalid operand size");
        }
        otava::assembly::Instruction* instruction = new otava::assembly::Instruction(opCode);
        std::expected<otava::assembly::Register*, int> xrv = assemblyContext->GetGlobalReg(operandSize, otava::assembly::RegisterGroupKind::xmm1);
        if (!xrv) return std::unexpected<int>(xrv.error());
        std::expected<otava::assembly::Register*, int> regRv = MakeFloatingPointRegOperand(inst.Left(), *xrv, codeGenerator);
        if (!regRv) return std::unexpected<int>(regRv.error());
        otava::assembly::Register* leftOperandReg = *regRv;
        instruction->AddOperand(leftOperandReg);
        xrv = assemblyContext->GetGlobalReg(operandSize, otava::assembly::RegisterGroupKind::xmm2);
        if (!xrv) return std::unexpected<int>(xrv.error());
        regRv = MakeFloatingPointRegOperand(inst.Right(), *xrv, codeGenerator);
        if (!regRv) return std::unexpected<int>(regRv.error());
        otava::assembly::Register* rightOperandReg = *regRv;
        instruction->AddOperand(rightOperandReg);
        codeGenerator.Emit(instruction);
        otava::assembly::Instruction* setInst = new otava::assembly::Instruction(otava::assembly::OpCode::SETC);
        setInst->AddOperand(resultReg);
        codeGenerator.Emit(setInst);
    }
    else
    {
        return codeGenerator.Error("error emitting less instruction: reg group for inst not found");
    }
    return std::expected<bool, int>(true);
}

void EmitJmp(JmpInstruction& inst, CodeGenerator& codeGenerator)
{
    otava::assembly::Context* assemblyContext = codeGenerator.Ctx()->AssemblyContext();
    otava::assembly::Instruction* jmpInstruction = new otava::assembly::Instruction(otava::assembly::OpCode::JMP);
    jmpInstruction->AddOperand(assemblyContext->MakeSymbol("@" + std::to_string(inst.TargetBasicBlock()->Id())));
    codeGenerator.Emit(jmpInstruction);
}

std::expected<bool, int> EmitBranch(BranchInstruction& inst, CodeGenerator& codeGenerator)
{
    otava::assembly::Context* assemblyContext = codeGenerator.Ctx()->AssemblyContext();
    int size = 4;
    std::expected<otava::assembly::Register*, int> regRv = assemblyContext->GetGlobalReg(size, otava::assembly::RegisterGroupKind::rax);
    if (!regRv) return std::unexpected<int>(regRv.error());
    regRv = MakeIntegerRegOperand(inst.Cond(), *regRv, codeGenerator);
    if (!regRv) return std::unexpected<int>(regRv.error());
    otava::assembly::Register* operandReg = *regRv;
    otava::assembly::Instruction* orInstruction = new otava::assembly::Instruction(otava::assembly::OpCode::OR);
    orInstruction->AddOperand(operandReg);
    orInstruction->AddOperand(operandReg);
    codeGenerator.Emit(orInstruction);
    codeGenerator.EmitBranchJumps(inst);
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EmitNot(NotInstruction& inst, CodeGenerator& codeGenerator)
{
    otava::assembly::Context* assemblyContext = codeGenerator.Ctx()->AssemblyContext();
    otava::assembly::RegisterGroup* regGroup = codeGenerator.RegAllocator()->GetRegisterGroup(&inst);
    if (regGroup)
    {
        Type* type = inst.Operand()->GetType();
        std::int64_t size = type->Size();
        std::expected<otava::assembly::Register*, int> rrv = regGroup->GetReg(size);
        if (!rrv) return std::unexpected<int>(rrv.error());
        otava::assembly::Register* resultReg = *rrv;
        std::expected<otava::assembly::Register*, int> regRv = assemblyContext->GetGlobalReg(size, otava::assembly::RegisterGroupKind::rax);
        if (!regRv) return std::unexpected<int>(regRv.error());
        regRv = MakeIntegerRegOperand(inst.Operand(), *regRv, codeGenerator);
        if (!regRv) return std::unexpected<int>(regRv.error());
        otava::assembly::Register* operandReg = *regRv;
        otava::assembly::Instruction* movInst = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
        movInst->AddOperand(resultReg);
        movInst->AddOperand(operandReg);
        codeGenerator.Emit(movInst);
        if (type->IsBooleanType())
        {
            otava::assembly::Instruction* xorInst = new otava::assembly::Instruction(otava::assembly::OpCode::XOR);
            xorInst->AddOperand(resultReg);
            xorInst->AddOperand(assemblyContext->MakeIntegerLiteral(1, int(size)));
            codeGenerator.Emit(xorInst);
        }
        else if (type->IsIntegerType())
        {
            otava::assembly::Instruction* notInst = new otava::assembly::Instruction(otava::assembly::OpCode::NOT);
            notInst->AddOperand(resultReg);
            codeGenerator.Emit(notInst);
        }
        else
        {
            return codeGenerator.Error("error emitting not instruction: integer or boolean type expected");
        }
    }
    else
    {
        return codeGenerator.Error("error emitting not instruction: reg group for inst not found");
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EmitIntegerNeg(NegInstruction& inst, CodeGenerator& codeGenerator)
{
    otava::assembly::Context* assemblyContext = codeGenerator.Ctx()->AssemblyContext();
    otava::assembly::RegisterGroup* regGroup = codeGenerator.RegAllocator()->GetRegisterGroup(&inst);
    if (regGroup)
    {
        Type* type = inst.Operand()->GetType();
        std::int64_t size = type->Size();
        std::expected<otava::assembly::Register*, int> rrv = regGroup->GetReg(size);
        if (!rrv) return std::unexpected<int>(rrv.error());
        otava::assembly::Register* resultReg = *rrv;
        std::expected<otava::assembly::Register*, int> regRv = assemblyContext->GetGlobalReg(size, otava::assembly::RegisterGroupKind::rax);
        if (!regRv) return std::unexpected<int>(regRv.error());
        regRv = MakeIntegerRegOperand(inst.Operand(), *regRv, codeGenerator);
        if (!regRv) return std::unexpected<int>(regRv.error());
        otava::assembly::Register* operandReg = *regRv;
        otava::assembly::Instruction* movInst = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
        movInst->AddOperand(resultReg);
        movInst->AddOperand(operandReg);
        codeGenerator.Emit(movInst);
        otava::assembly::Instruction* negInst = new otava::assembly::Instruction(otava::assembly::OpCode::NEG);
        negInst->AddOperand(resultReg);
        codeGenerator.Emit(negInst);
    }
    else
    {
        return codeGenerator.Error("error emitting neg instruction: reg group for inst not found");
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EmitFloatingPointNeg(NegInstruction& inst, CodeGenerator& codeGenerator)
{
    otava::assembly::Context* assemblyContext = codeGenerator.Ctx()->AssemblyContext();
    otava::assembly::RegisterGroup* regGroup = codeGenerator.RegAllocator()->GetRegisterGroup(&inst);
    if (regGroup)
    {
        Type* type = inst.Operand()->GetType();
        std::int64_t size = type->Size();
        std::expected<otava::assembly::Register*, int> rrv = regGroup->GetReg(size);
        if (!rrv) return std::unexpected<int>(rrv.error());
        otava::assembly::Register* resultReg = *rrv;
        std::expected<otava::assembly::Register*, int> xrv = assemblyContext->GetGlobalReg(size, otava::assembly::RegisterGroupKind::xmm0);
        if (!xrv) return std::unexpected<int>(xrv.error());
        std::expected<otava::assembly::Register*, int> regRv = MakeFloatingPointRegOperand(inst.Operand(), *xrv, codeGenerator);
        return std::unexpected<int>(regRv.error());
        otava::assembly::Register* operandReg = *regRv;
        otava::assembly::OpCode mulOpCode = otava::assembly::OpCode::NOP;
        std::unique_ptr<Value> value(nullptr);
        if (size == 4)
        {
            value.reset(new FloatValue(-1.0f, codeGenerator.Ctx()->GetTypes().GetFloatType()));
            mulOpCode = otava::assembly::OpCode::MULSS;
        }
        else if (size == 8)
        {
            value.reset(new DoubleValue(-1.0, codeGenerator.Ctx()->GetTypes().GetDoubleType()));
            mulOpCode = otava::assembly::OpCode::MULSD;
        }
        else
        {
            return codeGenerator.Error("error emitting neg instruction: invalid operand size");
        }
        xrv = assemblyContext->GetGlobalReg(size, otava::assembly::RegisterGroupKind::xmm1);
        if (!xrv) return std::unexpected<int>(xrv.error());
        regRv = MakeFloatingPointRegOperand(value.get(), *xrv, codeGenerator);
        if (!regRv) return std::unexpected<int>(regRv.error());
        otava::assembly::Register* minusOneReg = *regRv;
        otava::assembly::Instruction* instruction = new otava::assembly::Instruction(mulOpCode);
        instruction->AddOperand(operandReg);
        instruction->AddOperand(minusOneReg);
        codeGenerator.Emit(instruction);
        otava::assembly::OpCode movOpCode = otava::assembly::OpCode::NOP;
        if (size == 4)
        {
            movOpCode = otava::assembly::OpCode::MOVSS;
        }
        else if (size == 8)
        {
            movOpCode = otava::assembly::OpCode::MOVSD;
        }
        else
        {
            return codeGenerator.Error("error emitting neg instruction: invalid operand size");
        }
        otava::assembly::Instruction* movInstruction = new otava::assembly::Instruction(movOpCode);
        movInstruction->AddOperand(resultReg);
        movInstruction->AddOperand(operandReg);
        codeGenerator.Emit(movInstruction);
    }
    else
    {
        return codeGenerator.Error("error emitting neg instruction: reg group for inst not found");
    }
    return std::expected<bool, int>(true);
}

void EmitNop(NoOperationInstruction& inst, CodeGenerator& codeGenerator)
{
    otava::assembly::Instruction* nopInst = new otava::assembly::Instruction(otava::assembly::OpCode::NOP);
    codeGenerator.Emit(nopInst);
}

std::expected<bool, int> EmitSwitch(SwitchInstruction& inst, CodeGenerator& codeGenerator)
{
    otava::assembly::Context* assemblyContext = codeGenerator.Ctx()->AssemblyContext();
    std::int64_t size = inst.Cond()->GetType()->Size();
    std::expected<otava::assembly::Register*, int> regRv = assemblyContext->GetGlobalReg(size, otava::assembly::RegisterGroupKind::rbx);
    if (!regRv) return std::unexpected<int>(regRv.error());
    regRv = MakeIntegerRegOperand(inst.Cond(), *regRv, codeGenerator);
    if (!regRv) return std::unexpected<int>(regRv.error());
    otava::assembly::Register* condReg = *regRv;
    for (const auto& caseTarget : inst.CaseTargets())
    {
        std::int64_t size = caseTarget.caseValue->GetType()->Size();
        regRv = assemblyContext->GetGlobalReg(size, otava::assembly::RegisterGroupKind::rax);
        if (!regRv) return std::unexpected<int>(regRv.error());
        regRv = MakeIntegerRegOperand(caseTarget.caseValue, *regRv, codeGenerator);
        if (!regRv) return std::unexpected<int>(regRv.error());
        otava::assembly::Register* caseReg = *regRv;
        otava::assembly::Instruction* cmpInst = new otava::assembly::Instruction(otava::assembly::OpCode::CMP);
        cmpInst->AddOperand(caseReg);
        cmpInst->AddOperand(condReg);
        codeGenerator.Emit(cmpInst);
        otava::assembly::Instruction* jeInst = new otava::assembly::Instruction(otava::assembly::OpCode::JE);
        jeInst->AddOperand(assemblyContext->MakeSymbol("@" + std::to_string(caseTarget.targetBlock->Id())));
        codeGenerator.Emit(jeInst);
    }
    otava::assembly::Instruction* jmpInst = new otava::assembly::Instruction(otava::assembly::OpCode::JMP);
    jmpInst->AddOperand(assemblyContext->MakeSymbol("@" + std::to_string(inst.DefaultTargetBlock()->Id())));
    codeGenerator.Emit(jmpInst);
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EmitIntegerLoad(std::int64_t size, const FrameLocation& frameLocation, otava::assembly::RegisterGroup* regGroup, CodeGenerator& codeGenerator)
{
    if (!frameLocation.Valid())
    {
        return codeGenerator.Error("error emitting load: frame location not valid");
    }
    otava::assembly::Context* assemblyContext = codeGenerator.Ctx()->AssemblyContext();
    otava::assembly::Instruction* instruction = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
    std::expected<otava::assembly::Register*, int> rrv = regGroup->GetReg(size);
    if (!rrv) return std::unexpected<int>(rrv.error());
    instruction->AddOperand(*rrv);
    std::expected<bool, int> frv = EmitFrameLocationOperand(size, frameLocation, instruction, codeGenerator);
    if (!frv) return frv;
    codeGenerator.Emit(instruction);
    return std::expected<bool, int>(true);
}

std::expected<otava::assembly::Instruction*, int> EmitIntegerStore(std::int64_t size, const FrameLocation& frameLocation, otava::assembly::RegisterGroup* regGroup,
    CodeGenerator& codeGenerator)
{
    if (!frameLocation.Valid())
    {
        return codeGenerator.Error("error emitting store: frame location not valid");
    }
    otava::assembly::Context* assemblyContext = codeGenerator.Ctx()->AssemblyContext();
    otava::assembly::Instruction* instruction = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
    std::expected<bool, int> frv = EmitFrameLocationOperand(size, frameLocation, instruction, codeGenerator);
    if (!frv) return std::unexpected<int>(frv.error());
    std::expected<otava::assembly::Register*, int> rrv = regGroup->GetReg(size);
    if (!rrv) return std::unexpected<int>(rrv.error());
    instruction->AddOperand(*rrv);
    codeGenerator.Emit(instruction);
    return std::expected<otava::assembly::Instruction*, int>(instruction);
}

std::expected<bool, int> EmitFloatingPointLoad(std::int64_t size, const FrameLocation& frameLocation, otava::assembly::RegisterGroup* regGroup, CodeGenerator& codeGenerator)
{
    if (!frameLocation.Valid())
    {
        return codeGenerator.Error("error emitting load: frame location not valid");
    }
    otava::assembly::Context* assemblyContext = codeGenerator.Ctx()->AssemblyContext();
    otava::assembly::OpCode opCode = otava::assembly::OpCode::NOP;
    if (size == 4)
    {
        opCode = otava::assembly::OpCode::MOVSS;
    }
    else if (size == 8)
    {
        opCode = otava::assembly::OpCode::MOVSD;
    }
    else
    {
        return codeGenerator.Error("error emitting load: invalid size");
    }
    otava::assembly::Instruction* instruction = new otava::assembly::Instruction(opCode);
    std::expected<otava::assembly::Register*, int> rrv = regGroup->GetReg(size);
    if (!rrv) return std::unexpected<int>(rrv.error());
    instruction->AddOperand(*rrv);
    std::expected<bool, int> frv = EmitFrameLocationOperand(size, frameLocation, instruction, codeGenerator);
    if (!frv) return frv;
    codeGenerator.Emit(instruction);
    return std::expected<bool, int>(true);
}

std::expected<otava::assembly::Instruction*, int> EmitFloatingPointStore(std::int64_t size, const FrameLocation& frameLocation, otava::assembly::RegisterGroup* regGroup, CodeGenerator& codeGenerator)
{
    if (!frameLocation.Valid())
    {
        return codeGenerator.Error("error emitting store: frame location not valid");
    }
    otava::assembly::Context* assemblyContext = codeGenerator.Ctx()->AssemblyContext();
    otava::assembly::OpCode opCode = otava::assembly::OpCode::NOP;
    if (size == 4)
    {
        opCode = otava::assembly::OpCode::MOVSS;
    }
    else if (size == 8)
    {
        opCode = otava::assembly::OpCode::MOVSD;
    }
    else
    {
        return codeGenerator.Error("error emitting load: invalid size");
    }
    otava::assembly::Instruction* instruction = new otava::assembly::Instruction(opCode);
    std::expected<bool, int> frv = EmitFrameLocationOperand(size, frameLocation, instruction, codeGenerator);
    if (!frv) return std::unexpected<int>(frv.error());
    std::expected<otava::assembly::Register*, int> rrv = regGroup->GetReg(size);
    if (!rrv) return std::unexpected<int>(rrv.error());
    instruction->AddOperand(*rrv);
    codeGenerator.Emit(instruction);
    return std::expected<otava::assembly::Instruction*, int>(instruction);
}

std::expected<bool, int> EmitIntegerLoad(LoadInstruction& inst, CodeGenerator& codeGenerator)
{
    otava::assembly::RegisterGroup* regGroup = codeGenerator.RegAllocator()->GetRegisterGroup(&inst);
    if (!regGroup)
    {
        return codeGenerator.Error("error emitting load: reg group not valid");
    }
    Type* type = inst.Result()->GetType();
    if (type->IsFundamentalType() || type->IsPointerType())
    {
        std::int64_t size = type->Size();
        otava::assembly::Instruction* instruction = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
        std::expected<otava::assembly::Register*, int> rrv = regGroup->GetReg(size);
        if (!rrv) return std::unexpected<int>(rrv.error());
        instruction->AddOperand(*rrv);
        std::expected<bool, int> rv = EmitIntegerPtrOperand(size, inst.Ptr(), instruction, codeGenerator);
        if (!rv) return rv;
        codeGenerator.Emit(instruction);
    }
    else
    {
        return codeGenerator.Error("error emitting load: invalid type kind");
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EmitIntegerStore(StoreInstruction& inst, CodeGenerator& codeGenerator)
{
    Type* type = inst.GetValue()->GetType();
    if (type->IsFundamentalType() || type->IsPointerType())
    {
        std::int64_t size = type->Size();
        otava::assembly::Context* assemblyContext = codeGenerator.Ctx()->AssemblyContext();
        otava::assembly::Instruction* instruction = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
        std::expected<bool, int> rv = EmitIntegerPtrOperand(size, inst.GetPtr(), instruction, codeGenerator);
        if (!rv) return rv;
        std::expected<otava::assembly::Register*, int> regRv = assemblyContext->GetGlobalReg(size, otava::assembly::RegisterGroupKind::rax);
        if (!regRv) return std::unexpected<int>(regRv.error());
        regRv = MakeIntegerRegOperand(inst.GetValue(), *regRv, codeGenerator);
        if (!regRv) return std::unexpected<int>(regRv.error());
        instruction->AddOperand(*regRv);
        codeGenerator.Emit(instruction);
    }
    else
    {
        return codeGenerator.Error("error emitting store: invalid type kind");
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EmitFloatingPointLoad(LoadInstruction& inst, CodeGenerator& codeGenerator)
{
    otava::assembly::RegisterGroup* regGroup = codeGenerator.RegAllocator()->GetRegisterGroup(&inst);
    if (!regGroup)
    {
        return codeGenerator.Error("error emitting load: reg group not valid");
    }
    Type* type = inst.Result()->GetType();
    if (type->IsFloatingPointType())
    {
        std::int64_t size = type->Size();
        otava::assembly::OpCode opCode = otava::assembly::OpCode::NOP;
        if (size == 4)
        {
            opCode = otava::assembly::OpCode::MOVSS;
        }
        else if (size == 8)
        {
            opCode = otava::assembly::OpCode::MOVSD;
        }
        else
        {
            return codeGenerator.Error("error emitting load: invalid size");
        }
        otava::assembly::Instruction* instruction = new otava::assembly::Instruction(opCode);
        std::expected<otava::assembly::Register*, int> rrv = regGroup->GetReg(size);
        if (!rrv) return std::unexpected<int>(rrv.error());
        instruction->AddOperand(*rrv);
        std::expected<bool, int> rv = EmitFloatingPointPtrOperand(size, inst.Ptr(), instruction, codeGenerator);
        if (!rv) return rv;
        codeGenerator.Emit(instruction);
    }
    else
    {
        return codeGenerator.Error("error emitting load: invalid type kind");
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EmitFloatingPointStore(StoreInstruction& inst, CodeGenerator& codeGenerator)
{
    Type* type = inst.GetValue()->GetType();
    if (type->IsFloatingPointType())
    {
        std::int64_t size = type->Size();
        otava::assembly::OpCode opCode = otava::assembly::OpCode::NOP;
        if (size == 4)
        {
            opCode = otava::assembly::OpCode::MOVSS;
        }
        else if (size == 8)
        {
            opCode = otava::assembly::OpCode::MOVSD;
        }
        else
        {
            return codeGenerator.Error("error emitting store: invalid size");
        }
        otava::assembly::Context* assemblyContext = codeGenerator.Ctx()->AssemblyContext();
        otava::assembly::Instruction* instruction = new otava::assembly::Instruction(opCode);
        std::expected<bool, int> rv = EmitFloatingPointPtrOperand(size, inst.GetPtr(), instruction, codeGenerator);
        if (!rv) return rv;
        std::expected<otava::assembly::Register*, int> xrv = assemblyContext->GetGlobalReg(size, otava::assembly::RegisterGroupKind::xmm0);
        if (!xrv) return std::unexpected<int>(xrv.error());
        std::expected<otava::assembly::Register*, int> regRv = MakeFloatingPointRegOperand(inst.GetValue(), *xrv, codeGenerator);
        if (!regRv) return std::unexpected<int>(regRv.error());
        instruction->AddOperand(*regRv);
        codeGenerator.Emit(instruction);
    }
    else
    {
        return codeGenerator.Error("error emitting store: invalid type kind");
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EmitIntegerParam(ParamInstruction& inst, CodeGenerator& codeGenerator)
{
    Type* type = inst.GetType();
    std::int64_t size = type->Size();
    otava::assembly::RegisterGroup* regGroup = codeGenerator.RegAllocator()->GetRegisterGroup(&inst);
    otava::assembly::Context* assemblyContext = codeGenerator.Ctx()->AssemblyContext();
    if (!regGroup)
    {
        return codeGenerator.Error("error emitting param: reg group not valid");
    }
    switch (inst.Index())
    {
        case 0:
        {
            otava::assembly::Instruction* movInst = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
            std::expected<otava::assembly::Register*, int> regRv = assemblyContext->GetGlobalReg(size, otava::assembly::RegisterGroupKind::rcx);
            if (!regRv) return std::unexpected<int>(regRv.error());
            otava::assembly::Register* paramReg = *regRv;
            std::expected<otava::assembly::Register*, int> rrv = regGroup->GetReg(size);
            if (!rrv) return std::unexpected<int>(rrv.error());
            movInst->AddOperand(*rrv);
            movInst->AddOperand(paramReg);
            codeGenerator.Emit(movInst);
            break;
        }
        case 1:
        {
            otava::assembly::Instruction* movInst = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
            std::expected<otava::assembly::Register*, int> regRv = assemblyContext->GetGlobalReg(size, otava::assembly::RegisterGroupKind::rdx);
            if (!regRv) return std::unexpected<int>(regRv.error());
            otava::assembly::Register* paramReg = *regRv;
            std::expected<otava::assembly::Register*, int> rrv = regGroup->GetReg(size);
            if (!rrv) return std::unexpected<int>(rrv.error());
            movInst->AddOperand(*rrv);
            movInst->AddOperand(paramReg);
            codeGenerator.Emit(movInst);
            break;
        }
        case 2:
        {
            otava::assembly::Instruction* movInst = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
            std::expected<otava::assembly::Register*, int> regRv = assemblyContext->GetGlobalReg(size, otava::assembly::RegisterGroupKind::r8);
            if (!regRv) return std::unexpected<int>(regRv.error());
            otava::assembly::Register* paramReg = *regRv;
            std::expected<otava::assembly::Register*, int> rrv = regGroup->GetReg(size);
            if (!rrv) return std::unexpected<int>(rrv.error());
            movInst->AddOperand(*rrv);
            movInst->AddOperand(paramReg);
            codeGenerator.Emit(movInst);
            break;
        }
        case 3:
        {
            otava::assembly::Instruction* movInst = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
            std::expected<otava::assembly::Register*, int> regRv = assemblyContext->GetGlobalReg(size, otava::assembly::RegisterGroupKind::r9);
            if (!regRv) return std::unexpected<int>(regRv.error());
            otava::assembly::Register* paramReg = *regRv;
            std::expected<otava::assembly::Register*, int> rrv = regGroup->GetReg(size);
            if (!rrv) return std::unexpected<int>(rrv.error());
            movInst->AddOperand(*rrv);
            movInst->AddOperand(paramReg);
            codeGenerator.Emit(movInst);
            break;
        }
        default:
        {
            Locations locs = codeGenerator.RegAllocator()->GetLocations(&inst);
            if ((locs & Locations::frame) != Locations::none)
            {
                FrameLocation frameLocation = codeGenerator.RegAllocator()->GetFrameLocation(&inst);
                std::expected<bool, int> rv = EmitIntegerLoad(size, frameLocation, regGroup, codeGenerator);
                if (!rv) return rv;
            }
            else
            {
                return codeGenerator.Error("error emitting param: no frame location");
            }
            break;
        }
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EmitFloatingPointParam(ParamInstruction& inst, CodeGenerator& codeGenerator)
{
    Type* type = inst.GetType();
    std::int64_t size = type->Size();
    otava::assembly::RegisterGroup* regGroup = codeGenerator.RegAllocator()->GetRegisterGroup(&inst);
    otava::assembly::Context* assemblyContext = codeGenerator.Ctx()->AssemblyContext();
    if (!regGroup)
    {
        return codeGenerator.Error("error emitting param: reg group not valid");
    }
    otava::assembly::OpCode movOpCode = otava::assembly::OpCode::NOP;
    if (size == 4)
    {
        movOpCode = otava::assembly::OpCode::MOVSS;
    }
    else if (size == 8)
    {
        movOpCode = otava::assembly::OpCode::MOVSD;
    }
    else
    {
        return codeGenerator.Error("error emitting param: invalid operand size");
    }
    switch (inst.Index())
    {
        case 0:
        {
            otava::assembly::Instruction* movInst = new otava::assembly::Instruction(movOpCode);
            std::expected<otava::assembly::Register*, int> xrv = assemblyContext->GetGlobalReg(size, otava::assembly::RegisterGroupKind::xmm0);
            if (!xrv) return std::unexpected<int>(xrv.error());
            otava::assembly::Register* paramReg = *xrv;
            std::expected<otava::assembly::Register*, int> rrv = regGroup->GetReg(size);
            if (!rrv) return std::unexpected<int>(rrv.error());
            movInst->AddOperand(*rrv);
            movInst->AddOperand(paramReg);
            codeGenerator.Emit(movInst);
            break;
        }
        case 1:
        {
            otava::assembly::Instruction* movInst = new otava::assembly::Instruction(movOpCode);
            std::expected<otava::assembly::Register*, int> xrv = assemblyContext->GetGlobalReg(size, otava::assembly::RegisterGroupKind::xmm1);
            if (!xrv) return std::unexpected<int>(xrv.error());
            otava::assembly::Register* paramReg = *xrv;
            std::expected<otava::assembly::Register*, int> rrv = regGroup->GetReg(size);
            if (!rrv) return std::unexpected<int>(rrv.error());
            movInst->AddOperand(*rrv);
            movInst->AddOperand(paramReg);
            codeGenerator.Emit(movInst);
            break;
        }
        case 2:
        {
            otava::assembly::Instruction* movInst = new otava::assembly::Instruction(movOpCode);
            std::expected<otava::assembly::Register*, int> xrv = assemblyContext->GetGlobalReg(size, otava::assembly::RegisterGroupKind::xmm2);
            if (!xrv) return std::unexpected<int>(xrv.error());
            otava::assembly::Register* paramReg = *xrv;
            std::expected<otava::assembly::Register*, int> rrv = regGroup->GetReg(size);
            if (!rrv) return std::unexpected<int>(rrv.error());
            movInst->AddOperand(*rrv);
            movInst->AddOperand(paramReg);
            codeGenerator.Emit(movInst);
            break;
        }
        case 3:
        {
            otava::assembly::Instruction* movInst = new otava::assembly::Instruction(movOpCode);
            std::expected<otava::assembly::Register*, int> xrv = assemblyContext->GetGlobalReg(size, otava::assembly::RegisterGroupKind::xmm3);
            if (!xrv) return std::unexpected<int>(xrv.error());
            otava::assembly::Register* paramReg = *xrv;
            std::expected<otava::assembly::Register*, int> rrv = regGroup->GetReg(size);
            if (!rrv) return std::unexpected<int>(rrv.error());
            movInst->AddOperand(*rrv);
            movInst->AddOperand(paramReg);
            codeGenerator.Emit(movInst);
            break;
        }
        default:
        {
            Locations locs = codeGenerator.RegAllocator()->GetLocations(&inst);
            if ((locs & Locations::frame) != Locations::none)
            {
                FrameLocation frameLocation = codeGenerator.RegAllocator()->GetFrameLocation(&inst);
                std::expected<bool, int> rv = EmitFloatingPointLoad(size, frameLocation, regGroup, codeGenerator);
                if (!rv) return rv;
            }
            else
            {
                return codeGenerator.Error("error emitting param: no frame location");
            }
            break;
        }
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EmitIntegerArgOperand(Instruction* argInst, std::int64_t size, Value* arg, otava::assembly::Instruction* instruction, CodeGenerator& codeGenerator)
{
    if (arg->IsRegValue())
    {
        RegValue* regValue = static_cast<RegValue*>(arg);
        Instruction* inst = regValue->Inst();
        if (inst->IsLocalInstruction())
        {
            otava::assembly::RegisterGroup* regGroup = codeGenerator.RegAllocator()->GetRegisterGroup(argInst);
            if (regGroup)
            {
                otava::assembly::Instruction* leaInst = new otava::assembly::Instruction(otava::assembly::OpCode::LEA);
                std::expected<otava::assembly::Register*, int> rrv = regGroup->GetReg(8);
                if (!rrv) return std::unexpected<int>(rrv.error());
                leaInst->AddOperand(*rrv);
                std::expected<FrameLocation, int> rv = GetFrameLocation(arg, codeGenerator);
                if (!rv) return std::unexpected<int>(rv.error());
                FrameLocation frameLocation = *rv;
                std::expected<bool, int> frv = EmitFrameLocationOperand(1, frameLocation, leaInst, codeGenerator);
                if (!frv) return frv;
                codeGenerator.Emit(leaInst);
                rrv = regGroup->GetReg(8);
                if (!rrv) return std::unexpected<int>(rrv.error());
                instruction->AddOperand(*rrv);
                return std::expected<bool, int>(true);
            }
            else
            {
                return  codeGenerator.Error("error emitting arg: reg group not valid");
            }
        }
    }
    otava::assembly::Context* assemblyContext = codeGenerator.Ctx()->AssemblyContext();
    std::expected<otava::assembly::Register*, int> regRv = assemblyContext->GetGlobalReg(size, otava::assembly::RegisterGroupKind::rax);
    if (!regRv) return std::unexpected<int>(regRv.error());
    regRv = MakeIntegerRegOperand(arg, *regRv, codeGenerator);
    if (!regRv) return std::unexpected<int>(regRv.error());
    instruction->AddOperand(*regRv);
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EmitFloatingPointArgOperand(Instruction* argInst, std::int64_t size, Value* arg, otava::assembly::Instruction* instruction, CodeGenerator& codeGenerator)
{
    if (arg->IsRegValue())
    {
        RegValue* regValue = static_cast<RegValue*>(arg);
        Instruction* inst = regValue->Inst();
        if (inst->IsLocalInstruction())
        {
            otava::assembly::RegisterGroup* regGroup = codeGenerator.RegAllocator()->GetRegisterGroup(argInst);
            if (regGroup)
            {
                otava::assembly::Instruction* leaInst = new otava::assembly::Instruction(otava::assembly::OpCode::LEA);
                std::expected<otava::assembly::Register*, int> rrv = regGroup->GetReg(8);
                if (!rrv) return std::unexpected<int>(rrv.error());
                leaInst->AddOperand(*rrv);
                std::expected<FrameLocation, int> rv = GetFrameLocation(arg, codeGenerator);
                if (!rv) return std::unexpected<int>(rv.error());
                FrameLocation frameLocation = *rv;
                std::expected<bool, int> frv = EmitFrameLocationOperand(1, frameLocation, leaInst, codeGenerator);
                if (!frv) return frv;
                codeGenerator.Emit(leaInst);
                rrv = regGroup->GetReg(8);
                if (!rrv) return std::unexpected<int>(rrv.error());
                instruction->AddOperand(*rrv);
                return std::expected<bool, int>(true);
            }
            else
            {
                return codeGenerator.Error("error emitting arg: reg group not valid");
            }
        }
    }
    otava::assembly::Context* assemblyContext = codeGenerator.Ctx()->AssemblyContext();
    std::expected<otava::assembly::Register*, int> xrv = assemblyContext->GetGlobalReg(size, otava::assembly::RegisterGroupKind::xmm0);
    if (!xrv) return std::unexpected<int>(xrv.error());
    std::expected<otava::assembly::Register*, int> regRv = MakeFloatingPointRegOperand(arg, *xrv, codeGenerator);
    if (!regRv) return std::unexpected<int>(regRv.error());
    instruction->AddOperand(*regRv);
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EmitArgLocationOperand(std::int64_t size, const ArgLocation& argLocation, otava::assembly::Instruction* instruction, CodeGenerator& codeGenerator)
{
    otava::assembly::Context* assemblyContext = codeGenerator.Ctx()->AssemblyContext();
    std::expected<otava::assembly::Register*, int> regRv = assemblyContext->GetGlobalReg(8, argLocation.reg);
    if (!regRv) return std::unexpected<int>(regRv.error());
    otava::assembly::Register* reg = *regRv;
    std::expected < otava::assembly::Value*, int> srv = assemblyContext->MakeSizePrefix(size,
        assemblyContext->MakeContent(assemblyContext->MakeBinaryExpr(reg, assemblyContext->MakeIntegerLiteral(argLocation.offset, 8),
            otava::assembly::Operator::add)));
    if (!srv) return std::unexpected<int>(srv.error());
    instruction->AddOperand(*srv);
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EmitIntegerArg(ArgInstruction& inst, CallFrame* callFrame, std::int32_t index, CodeGenerator& codeGenerator)
{
    std::expected<RegisterAllocationAction, int> rv = codeGenerator.RegAllocator()->Run(&inst);
    if (!rv) return std::unexpected<int>(rv.error());
    RegisterAllocationAction action = *rv;
    if (action == RegisterAllocationAction::spill)
    {
        for (const SpillData& spillData : codeGenerator.RegAllocator()->GetSpillData())
        {
            std::expected<otava::assembly::Instruction*, int> rv = EmitIntegerStore(8, spillData.spillToFrameLocation, spillData.registerGroupToSpill, codeGenerator);
            if (!rv) return std::unexpected<int>(rv.error());
            otava::assembly::Instruction* storeInst = *rv;
            Instruction* instToSpill = spillData.instToSpill;
            otava::assembly::Instruction* assemblyInstruction = instToSpill->AssemblyInstruction();
            if (assemblyInstruction)
            {
                assemblyInstruction->LinkAfter(storeInst->Clone());
            }
            else
            {
                codeGenerator.AssemblyFunction()->AddInstruction(storeInst->Clone());
            }
            codeGenerator.RegAllocator()->RemoveFromRegisterGroups(instToSpill);
        }
    }
    otava::assembly::Context* assemblyContext = codeGenerator.Ctx()->AssemblyContext();
    std::int64_t size = inst.Arg()->GetType()->Size();
    switch (index)
    {
        case 0:
        {
            otava::assembly::Instruction* movInst = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
            std::expected<otava::assembly::Register*, int> regRv = assemblyContext->GetGlobalReg(size, otava::assembly::RegisterGroupKind::rcx);
            if (!regRv) return std::unexpected<int>(regRv.error());
            movInst->AddOperand(*regRv);
            std::expected<bool, int> rv = EmitIntegerArgOperand(&inst, size, inst.Arg(), movInst, codeGenerator);
            if (!rv) return rv;
            codeGenerator.Emit(movInst);
            break;
        }
        case 1:
        {
            otava::assembly::Instruction* movInst = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
            std::expected<otava::assembly::Register*, int> regRv = assemblyContext->GetGlobalReg(size, otava::assembly::RegisterGroupKind::rdx);
            if (!regRv) return std::unexpected<int>(regRv.error());
            movInst->AddOperand(*regRv);
            std::expected<bool, int> rv = EmitIntegerArgOperand(&inst, size, inst.Arg(), movInst, codeGenerator);
            if (!rv) return rv;
            codeGenerator.Emit(movInst);
            break;
        }
        case 2:
        {
            otava::assembly::Instruction* movInst = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
            std::expected<otava::assembly::Register*, int> regRv = assemblyContext->GetGlobalReg(size, otava::assembly::RegisterGroupKind::r8);
            if (!regRv) return std::unexpected<int>(regRv.error());
            movInst->AddOperand(*regRv);
            std::expected<bool, int> rv = EmitIntegerArgOperand(&inst, size, inst.Arg(), movInst, codeGenerator);
            if (!rv) return rv;
            codeGenerator.Emit(movInst);
            break;
        }
        case 3:
        {
            otava::assembly::Instruction* movInst = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
            std::expected<otava::assembly::Register*, int> regRv = assemblyContext->GetGlobalReg(size, otava::assembly::RegisterGroupKind::r9);
            if (!regRv) return std::unexpected<int>(regRv.error());
            movInst->AddOperand(*regRv);
            std::expected<bool, int> rv = EmitIntegerArgOperand(&inst, size, inst.Arg(), movInst, codeGenerator);
            if (!rv) return rv;
            codeGenerator.Emit(movInst);
            break;
        }
        default:
        {
            otava::assembly::Instruction* movInst = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
            otava::assembly::RegisterGroup* regGroup = codeGenerator.RegAllocator()->GetRegisterGroup(&inst);
            if (regGroup)
            {
                std::expected<otava::assembly::Register*, int> rrv = regGroup->GetReg(size);
                if (!rrv) return std::unexpected<int>(rrv.error());
                otava::assembly::Register* reg = *rrv;
                movInst->AddOperand(reg);
                std::expected<bool, int> rv = EmitIntegerArgOperand(&inst, size, inst.Arg(), movInst, codeGenerator);
                if (!rv) return rv;
                codeGenerator.Emit(movInst);
                otava::assembly::Instruction* pushToFrameInst = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
                ArgLocation argLocation = callFrame->GetArgLocation(index);
                rv = EmitArgLocationOperand(size, argLocation, pushToFrameInst, codeGenerator);
                if (!rv) return std::unexpected<int>(rv.error());
                pushToFrameInst->AddOperand(reg);
                codeGenerator.Emit(pushToFrameInst);
            }
            else
            {
                return codeGenerator.Error("error emitting arg instruction: reg group for inst not found");
            }
            break;
        }
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EmitFloatingPointArg(ArgInstruction& inst, CallFrame* callFrame, std::int32_t index, CodeGenerator& codeGenerator)
{
    std::expected<RegisterAllocationAction, int> rv = codeGenerator.RegAllocator()->Run(&inst);
    if (!rv) return std::unexpected<int>(rv.error());
    RegisterAllocationAction action = *rv;
    if (action == RegisterAllocationAction::spill)
    {
        for (const SpillData& spillData : codeGenerator.RegAllocator()->GetSpillData())
        {
            std::expected<otava::assembly::Instruction*, int> rv = EmitFloatingPointStore(
                8, spillData.spillToFrameLocation, spillData.registerGroupToSpill, codeGenerator);
            if (!rv)  return std::unexpected<int>(rv.error());
            otava::assembly::Instruction* storeInst = *rv;
            Instruction* instToSpill = spillData.instToSpill;
            otava::assembly::Instruction* assemblyInstruction = instToSpill->AssemblyInstruction();
            if (assemblyInstruction)
            {
                assemblyInstruction->LinkAfter(storeInst->Clone());
            }
            else
            {
                codeGenerator.AssemblyFunction()->AddInstruction(storeInst->Clone());
            }
            codeGenerator.RegAllocator()->RemoveFromRegisterGroups(instToSpill);
        }
    }
    otava::assembly::Context* assemblyContext = codeGenerator.Ctx()->AssemblyContext();
    std::int64_t size = inst.Arg()->GetType()->Size();
    otava::assembly::OpCode movOpCode = otava::assembly::OpCode::NOP;
    if (size == 4)
    {
        movOpCode = otava::assembly::OpCode::MOVSS;
    }
    else if (size == 8)
    {
        movOpCode = otava::assembly::OpCode::MOVSD;
    }
    else
    {
        return codeGenerator.Error("error emitting arg instruction: invalid operand size");
    }
    switch (index)
    {
        case 0:
        {
            otava::assembly::Instruction* movInst = new otava::assembly::Instruction(movOpCode);
            std::expected<otava::assembly::Register*, int> xrv = assemblyContext->GetGlobalReg(size, otava::assembly::RegisterGroupKind::xmm0);
            if (!xrv) return std::unexpected<int>(xrv.error());
            movInst->AddOperand(*xrv);
            std::expected<bool, int> rv = EmitFloatingPointArgOperand(&inst, size, inst.Arg(), movInst, codeGenerator);
            if (!rv) return std::unexpected<int>(rv.error());
            codeGenerator.Emit(movInst);
            break;
        }
        case 1:
        {
            otava::assembly::Instruction* movInst = new otava::assembly::Instruction(movOpCode);
            std::expected<otava::assembly::Register*, int> xrv = assemblyContext->GetGlobalReg(size, otava::assembly::RegisterGroupKind::xmm1);
            if (!xrv) return std::unexpected<int>(xrv.error());
            movInst->AddOperand(*xrv);
            std::expected<bool, int> rv = EmitFloatingPointArgOperand(&inst, size, inst.Arg(), movInst, codeGenerator);
            if (!rv) return std::unexpected<int>(rv.error());
            codeGenerator.Emit(movInst);
            break;
        }
        case 2:
        {
            otava::assembly::Instruction* movInst = new otava::assembly::Instruction(movOpCode);
            std::expected<otava::assembly::Register*, int> xrv = assemblyContext->GetGlobalReg(size, otava::assembly::RegisterGroupKind::xmm2);
            if (!xrv) return std::unexpected<int>(xrv.error());
            movInst->AddOperand(*xrv);
            std::expected<bool, int> rv = EmitFloatingPointArgOperand(&inst, size, inst.Arg(), movInst, codeGenerator);
            if (!rv) return std::unexpected<int>(rv.error());
            codeGenerator.Emit(movInst);
            break;
        }
        case 3:
        {
            otava::assembly::Instruction* movInst = new otava::assembly::Instruction(movOpCode);
            std::expected<otava::assembly::Register*, int> xrv = assemblyContext->GetGlobalReg(size, otava::assembly::RegisterGroupKind::xmm3);
            if (!xrv) return std::unexpected<int>(xrv.error());
            movInst->AddOperand(*xrv);
            std::expected<bool, int> rv = EmitFloatingPointArgOperand(&inst, size, inst.Arg(), movInst, codeGenerator);
            if (!rv) return std::unexpected<int>(rv.error());
            codeGenerator.Emit(movInst);
            break;
        }
        default:
        {
            otava::assembly::Instruction* movInst = new otava::assembly::Instruction(movOpCode);
            otava::assembly::RegisterGroup* regGroup = codeGenerator.RegAllocator()->GetRegisterGroup(&inst);
            if (regGroup)
            {
                std::expected<otava::assembly::Register*, int> rrv = regGroup->GetReg(size);
                if (!rrv) return std::unexpected<int>(rrv.error());
                otava::assembly::Register* reg = *rrv;
                movInst->AddOperand(reg);
                std::expected<bool, int> rv = EmitFloatingPointArgOperand(&inst, size, inst.Arg(), movInst, codeGenerator);
                if (!rv) return std::unexpected<int>(rv.error());
                codeGenerator.Emit(movInst);
                otava::assembly::Instruction* pushToFrameInst = new otava::assembly::Instruction(movOpCode);
                ArgLocation argLocation = callFrame->GetArgLocation(index);
                rv = EmitArgLocationOperand(size, argLocation, pushToFrameInst, codeGenerator);
                if (!rv) return std::unexpected<int>(rv.error());
                pushToFrameInst->AddOperand(reg);
                codeGenerator.Emit(pushToFrameInst);
            }
            else
            {
                return codeGenerator.Error("error emitting arg instruction: reg group for inst not found");
            }
            break;
        }
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EmitArgs(const std::vector<ArgInstruction*>& args, CodeGenerator& codeGenerator)
{
    CallFrame callFrame;
    int n = args.size();
    std::int64_t calleeParamAreaSize = n * 8;
    Frame& frame = codeGenerator.RegAllocator()->GetFrame();
    frame.SetCalleeParamAreaSize(std::max(frame.CalleeParamAreaSize(), calleeParamAreaSize));
    for (int i = 0; i < n; ++i)
    {
        std::int64_t size = args[i]->Arg()->GetType()->Size();
        callFrame.AllocateArgLocation(size);
    }
    for (int i = n - 1; i >= 0; --i)
    {
        ArgInstruction* arg = args[i];
        if (arg->IsFloatingPointInstruction())
        {
            std::expected<bool, int> rv = EmitFloatingPointArg(*arg, &callFrame, i, codeGenerator);
            if (!rv) return rv;
        }
        else
        {
            std::expected<bool, int> rv =EmitIntegerArg(*arg, &callFrame, i, codeGenerator);
            if (!rv) return rv;
        }
    }
    return std::expected<bool, int>(true);
}

std::expected<otava::assembly::Value*, int> MakeCalleeOperand(Value* value, otava::assembly::Register* reg, CodeGenerator& codeGenerator)
{
    if (value->Kind() == ValueKind::regValue)
    {
        std::expected<otava::assembly::Register*, int> rv = MakeIntegerRegOperand(value, reg, codeGenerator);
        if (!rv) return std::unexpected<int>(rv.error());
        return std::expected<otava::assembly::Value*, int>(static_cast<otava::assembly::Value*>(*rv));
    }
    else
    {
        if (value->IsSymbolValue())
        {
            SymbolValue* symbolValue = static_cast<SymbolValue*>(value);
            otava::assembly::Context* assemblyContext = codeGenerator.Ctx()->AssemblyContext();
            otava::assembly::Value* symbol = assemblyContext->MakeSymbol(symbolValue->GetSymbol());
            return std::expected<otava::assembly::Value*, int>(symbol);
        }
        else
        {
            return codeGenerator.Error("error emitting callee operand: invalid value kind");
        }
    }
}

std::expected<bool, int> EmitProcedureCall(ProcedureCallInstruction& inst, const std::vector<ArgInstruction*>& args, CodeGenerator& codeGenerator)
{
    std::expected<bool, int> rv = EmitArgs(args, codeGenerator);
    if (!rv) return rv;
    std::expected<RegisterAllocationAction, int> runRv = codeGenerator.RegAllocator()->Run(&inst);
    if (!runRv) return std::unexpected<int>(runRv.error());
    RegisterAllocationAction action = *runRv;
    if (action == RegisterAllocationAction::spill)
    {
        for (const SpillData& spillData : codeGenerator.RegAllocator()->GetSpillData())
        {
            otava::assembly::Instruction* storeInst = nullptr;
            if (spillData.registerGroupToSpill->IsFloatingPointReg())
            {
                std::expected<otava::assembly::Instruction*, int> rv = EmitFloatingPointStore(
                    8, spillData.spillToFrameLocation, spillData.registerGroupToSpill, codeGenerator);
                if (!rv) return std::unexpected<int>(rv.error());
                storeInst = *rv;
            }
            else
            {
                std::expected<otava::assembly::Instruction*, int> rv = EmitIntegerStore(8, spillData.spillToFrameLocation, spillData.registerGroupToSpill, codeGenerator);
                if (!rv) return std::unexpected<int>(rv.error());
                storeInst = *rv;
            }
            Instruction* instToSpill = spillData.instToSpill;
            otava::assembly::Instruction* assemblyInstruction = instToSpill->AssemblyInstruction();
            if (assemblyInstruction)
            {
                assemblyInstruction->LinkAfter(storeInst->Clone());
            }
            else
            {
                codeGenerator.AssemblyFunction()->AddInstruction(storeInst->Clone());
            }
            codeGenerator.RegAllocator()->RemoveFromRegisterGroups(instToSpill);
        }
    }
    otava::assembly::Context* assemblyContext = codeGenerator.Ctx()->AssemblyContext();
    otava::assembly::RegisterGroup* regGroup = codeGenerator.RegAllocator()->GetRegisterGroup(&inst);
    std::expected<otava::assembly::Register*, int> rrv = regGroup->GetReg(8);
    if (!rrv) return std::unexpected<int>(rrv.error());
    otava::assembly::Register * reg = *rrv;
    otava::assembly::Instruction* callInst = new otava::assembly::Instruction(otava::assembly::OpCode::CALL);
    std::expected<otava::assembly::Value*, int> crv = MakeCalleeOperand(inst.Callee(), reg, codeGenerator);
    if (!crv) return std::unexpected<int>(crv.error());
    callInst->AddOperand(*crv);
    codeGenerator.Emit(callInst);
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EmitFunctionCall(FunctionCallInstruction& inst, const std::vector<ArgInstruction*>& args, CodeGenerator& codeGenerator)
{
    std::expected<bool, int> rv = EmitArgs(args, codeGenerator);
    if (!rv) return rv;
    std::expected<RegisterAllocationAction, int> runRv = codeGenerator.RegAllocator()->Run(&inst);
    if (!runRv) return std::unexpected<int>(runRv.error());
    RegisterAllocationAction action = *runRv;
    if (action == RegisterAllocationAction::spill)
    {
        for (const SpillData& spillData : codeGenerator.RegAllocator()->GetSpillData())
        {
            otava::assembly::Instruction* storeInst = nullptr;
            if (spillData.registerGroupToSpill->IsFloatingPointReg())
            {
                std::expected<otava::assembly::Instruction*, int> rv = EmitFloatingPointStore(
                    8, spillData.spillToFrameLocation, spillData.registerGroupToSpill, codeGenerator);
                if (!rv) return std::unexpected<int>(rv.error());
                storeInst = *rv;
            }
            else
            {
                std::expected<otava::assembly::Instruction*, int> rv = EmitIntegerStore(8, spillData.spillToFrameLocation, spillData.registerGroupToSpill, codeGenerator);
                if (!rv) return std::unexpected<int>(rv.error());
                storeInst = *rv;
            }
            Instruction* instToSpill = spillData.instToSpill;
            otava::assembly::Instruction* assemblyInstruction = instToSpill->AssemblyInstruction();
            if (assemblyInstruction)
            {
                assemblyInstruction->LinkAfter(storeInst->Clone());
            }
            else
            {
                codeGenerator.AssemblyFunction()->AddInstruction(storeInst->Clone());
            }
            codeGenerator.RegAllocator()->RemoveFromRegisterGroups(instToSpill);
        }
    }
    otava::assembly::Context* assemblyContext = codeGenerator.Ctx()->AssemblyContext();
    otava::assembly::RegisterGroup* regGroup = codeGenerator.RegAllocator()->GetRegisterGroup(&inst);
    otava::assembly::Instruction* callInst = new otava::assembly::Instruction(otava::assembly::OpCode::CALL);
    Type* type = inst.Result()->GetType();
    int size = static_cast<int>(type->Size());
    if (!type->IsFloatingPointType())
    {
        size = 8;
    }
    std::expected<otava::assembly::Register*, int> rrv = regGroup->GetReg(size);
    if (!rrv) return std::unexpected<int>(rrv.error());
    otava::assembly::Register* reg = *rrv;
    rrv = regGroup->GetReg(8);
    if (!rrv) return std::unexpected<int>(rrv.error());
    otava::assembly::Register* callReg = *rrv;
    std::expected<otava::assembly::Value*, int> crv = MakeCalleeOperand(inst.Callee(), callReg, codeGenerator);
    if (!crv) return std::unexpected<int>(crv.error());
    callInst->AddOperand(*crv);
    codeGenerator.Emit(callInst);
    if (type->IsFloatingPointType())
    {
        otava::assembly::OpCode opCode = otava::assembly::OpCode::NOP;
        if (size == 4)
        {
            opCode = otava::assembly::OpCode::MOVSS;
        }
        else if (size == 8)
        {
            opCode = otava::assembly::OpCode::MOVSD;
        }
        else
        {
            return codeGenerator.Error("error emitting function call: invalid result size");
        }
        otava::assembly::Instruction* movInst = new otava::assembly::Instruction(opCode);
        movInst->AddOperand(reg);
        std::expected<otava::assembly::Register*, int> xrv = assemblyContext->GetGlobalReg(size, otava::assembly::RegisterGroupKind::xmm0);
        if (!xrv) return std::unexpected<int>(xrv.error());
        movInst->AddOperand(*xrv);
        codeGenerator.Emit(movInst);
    }
    else
    {
        otava::assembly::Instruction* movInst = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
        movInst->AddOperand(reg);
        std::expected<otava::assembly::Register*, int> regRv = assemblyContext->GetGlobalReg(8, otava::assembly::RegisterGroupKind::rax);
        if (!regRv) return std::unexpected<int>(regRv.error());
        movInst->AddOperand(*regRv);
        codeGenerator.Emit(movInst);
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EmitElemAddr(ElemAddrInstruction& inst, CodeGenerator& codeGenerator)
{
    otava::assembly::Context* assemblyContext = codeGenerator.Ctx()->AssemblyContext();
    std::expected<ElemAddrKind, int> rv = inst.GetElemAddrKind(codeGenerator.Ctx());
    if (!rv) return std::unexpected<int>(rv.error());
    ElemAddrKind elemAddrKind = *rv;
    if (elemAddrKind == ElemAddrKind::array)
    {
        std::expected<otava::assembly::Register*, int> regRv = assemblyContext->GetGlobalReg(8, otava::assembly::RegisterGroupKind::rbx);
        if (!regRv) return std::unexpected<int>(regRv.error());
        regRv = MakeIntegerRegOperand(inst.IndexValue(), *regRv, codeGenerator);
        if (!regRv) return std::unexpected<int>(regRv.error());
        otava::assembly::Register* indexReg = *regRv;
        std::expected<std::int64_t, int> irv = GetElementSize(inst.Ptr()->GetType(), codeGenerator);
        if (!irv) return std::unexpected<int>(irv.error());
        std::int64_t indexFactor = *irv;
        otava::assembly::Instruction* movInst = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
        regRv = assemblyContext->GetGlobalReg(8, otava::assembly::RegisterGroupKind::rax);
        if (!regRv) return std::unexpected<int>(regRv.error());
        otava::assembly::Register* rax = *regRv;
        movInst->AddOperand(rax);
        movInst->AddOperand(assemblyContext->MakeIntegerLiteral(indexFactor, 8));
        codeGenerator.Emit(movInst);
        otava::assembly::Instruction* mulInst = new otava::assembly::Instruction(otava::assembly::OpCode::MUL);
        mulInst->AddOperand(indexReg);
        codeGenerator.Emit(mulInst);
        otava::assembly::Instruction* leaPtrInst = new otava::assembly::Instruction(otava::assembly::OpCode::LEA);
        regRv = assemblyContext->GetGlobalReg(8, otava::assembly::RegisterGroupKind::rcx);
        if (!regRv) return std::unexpected<int>(regRv.error());
        otava::assembly::Register* rcx = *regRv;
        leaPtrInst->AddOperand(rcx);
        std::expected<bool, int> prv = EmitIntegerPtrOperand(8, inst.Ptr(), leaPtrInst, codeGenerator);
        if (!prv) return prv;
        codeGenerator.Emit(leaPtrInst);
        otava::assembly::RegisterGroup* regGroup = codeGenerator.RegAllocator()->GetRegisterGroup(&inst);
        if (regGroup)
        {
            std::expected<otava::assembly::Register*, int> rrv = regGroup->GetReg(8);
            if (!rrv) return std::unexpected<int>(rrv.error());
            otava::assembly::Register* resultReg = *rrv;
            otava::assembly::Instruction* leaInst = new otava::assembly::Instruction(otava::assembly::OpCode::LEA);
            leaInst->AddOperand(resultReg);
            std::expected<otava::assembly::Value*, int> srv = assemblyContext->MakeSizePrefix(
                8, assemblyContext->MakeContent(assemblyContext->MakeBinaryExpr(rax, rcx, otava::assembly::Operator::add)));
            if (!srv) return std::unexpected<int>(srv.error());
            leaInst->AddOperand(*srv);
            codeGenerator.Emit(leaInst);
        }
        else
        {
            return codeGenerator.Error("error emitting elemaddr instruction: reg group for inst not found");
        }
    }
    else if (elemAddrKind == ElemAddrKind::structure)
    {
        otava::assembly::RegisterGroup* regGroup = codeGenerator.RegAllocator()->GetRegisterGroup(&inst);
        if (regGroup)
        {
            std::expected<otava::assembly::Register*, int> rrv = regGroup->GetReg(8);
            if (!rrv) return std::unexpected<int>(rrv.error());
            otava::assembly::Register* resultReg = *rrv;
            std::expected<std::int64_t, int> indexRv = GetIndex(inst.IndexValue(), codeGenerator);
            if (!indexRv) return std::unexpected<int>(indexRv.error());
            std::int64_t index = *indexRv;
            std::expected<std::int64_t, int> irv = GetOffset(inst.Ptr()->GetType(), index, codeGenerator);
            if (!irv) return std::unexpected<int>(irv.error());
            std::int64_t offset = *irv;
            otava::assembly::Instruction* movOffsetInst = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
            std::expected<otava::assembly::Register*, int> regRv = assemblyContext->GetGlobalReg(8, otava::assembly::RegisterGroupKind::rbx);
            if (!regRv) return std::unexpected<int>(regRv.error());
            otava::assembly::Register* rbx = *regRv;
            movOffsetInst->AddOperand(rbx);
            movOffsetInst->AddOperand(assemblyContext->MakeIntegerLiteral(offset, 8));
            codeGenerator.Emit(movOffsetInst);
            otava::assembly::Instruction* leaPtrInst = new otava::assembly::Instruction(otava::assembly::OpCode::LEA);
            regRv = assemblyContext->GetGlobalReg(8, otava::assembly::RegisterGroupKind::rcx);
            if (!regRv) return std::unexpected<int>(regRv.error());
            otava::assembly::Register* rcx = *regRv;
            leaPtrInst->AddOperand(rcx);
            std::expected<bool, int> rv = EmitIntegerPtrOperand(8, inst.Ptr(), leaPtrInst, codeGenerator);
            if (!rv) return rv;
            codeGenerator.Emit(leaPtrInst);
            otava::assembly::Instruction* leaInst = new otava::assembly::Instruction(otava::assembly::OpCode::LEA);
            leaInst->AddOperand(resultReg);
            std::expected<otava::assembly::Value*, int> srv = assemblyContext->MakeSizePrefix(
                8, assemblyContext->MakeContent(assemblyContext->MakeBinaryExpr(rbx, rcx, otava::assembly::Operator::add)));
            if (!srv) return std::unexpected<int>(srv.error());
            leaInst->AddOperand(*srv);
            codeGenerator.Emit(leaInst);
        }
        else
        {
            return codeGenerator.Error("error emitting elemaddr instruction: reg group for inst not found");
        }
    }
    else
    {
        return codeGenerator.Error("error emitting elemaddr: invalid elemaddr kind");
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EmitPtrOffset(PtrOffsetInstruction& inst, CodeGenerator& codeGenerator)
{
    otava::assembly::Context* assemblyContext = codeGenerator.Ctx()->AssemblyContext();
    std::expected<otava::assembly::Register*, int> regRv = assemblyContext->GetGlobalReg(8, otava::assembly::RegisterGroupKind::rbx);
    if (!regRv) return std::unexpected<int>(regRv.error());
    regRv = MakeIntegerRegOperand(inst.Offset(), *regRv, codeGenerator);
    if (!regRv) return std::unexpected<int>(regRv.error());
    otava::assembly::Register* offsetReg = *regRv;
    std::expected<std::int64_t, int> srv = GetPointeeSize(inst.Ptr()->GetType(), codeGenerator);
    if (!srv) return std::unexpected<int>(srv.error());
    std::int64_t offsetFactor = *srv;
    otava::assembly::Instruction* movInst = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
    regRv = assemblyContext->GetGlobalReg(8, otava::assembly::RegisterGroupKind::rax);
    if (!regRv) return std::unexpected<int>(regRv.error());
    otava::assembly::Register* rax = *regRv;
    movInst->AddOperand(rax);
    movInst->AddOperand(assemblyContext->MakeIntegerLiteral(offsetFactor, 8));
    codeGenerator.Emit(movInst);
    otava::assembly::Instruction* mulInst = new otava::assembly::Instruction(otava::assembly::OpCode::MUL);
    mulInst->AddOperand(offsetReg);
    codeGenerator.Emit(mulInst);
    regRv = assemblyContext->GetGlobalReg(8, otava::assembly::RegisterGroupKind::rcx);
    if (!regRv) return std::unexpected<int>(regRv.error());
    regRv = MakeIntegerRegOperand(inst.Ptr(), *regRv, codeGenerator);
    if (!regRv) return std::unexpected<int>(regRv.error());
    otava::assembly::Register* ptrReg = *regRv;
    otava::assembly::Instruction* leaInst = new otava::assembly::Instruction(otava::assembly::OpCode::LEA);
    otava::assembly::RegisterGroup* regGroup = codeGenerator.RegAllocator()->GetRegisterGroup(&inst);
    if (regGroup)
    {
        std::expected<otava::assembly::Register*, int> rrv = regGroup->GetReg(8);
        if (!rrv) return std::unexpected<int>(rrv.error());
        otava::assembly::Register* resultReg = *rrv;
        leaInst->AddOperand(resultReg);
        std::expected<otava::assembly::Value*, int> srv = assemblyContext->MakeSizePrefix(
            8, assemblyContext->MakeContent(assemblyContext->MakeBinaryExpr(rax, ptrReg, otava::assembly::Operator::add)));
        if (!srv) return std::unexpected<int>(srv.error());
        otava::assembly::Value* operand = *srv;
        leaInst->AddOperand(operand);
        codeGenerator.Emit(leaInst);
    }
    else
    {
        return codeGenerator.Error("error emitting ptroffset instruction: reg group for inst not found");
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EmitPtrDiff(PtrDiffInstruction& inst, CodeGenerator& codeGenerator)
{
    otava::assembly::Context* assemblyContext = codeGenerator.Ctx()->AssemblyContext();
    std::expected<std::int64_t, int> srv = GetPointeeSize(inst.LeftPtr()->GetType(), codeGenerator);
    if (!srv) return std::unexpected<int>(srv.error());
    std::int64_t scaleFactor = *srv;
    otava::assembly::Instruction* movInst = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
    std::expected<otava::assembly::Register*, int> regRv = assemblyContext->GetGlobalReg(8, otava::assembly::RegisterGroupKind::rcx);
    if (!regRv) return std::unexpected<int>(regRv.error());
    otava::assembly::Register* rcx = *regRv;
    movInst->AddOperand(rcx);
    movInst->AddOperand(assemblyContext->MakeIntegerLiteral(scaleFactor, 8));
    codeGenerator.Emit(movInst);
    otava::assembly::Instruction* subInst = new otava::assembly::Instruction(otava::assembly::OpCode::SUB);
    otava::assembly::RegisterGroup* regGroup = codeGenerator.RegAllocator()->GetRegisterGroup(&inst);
    if (regGroup)
    {
        std::expected<otava::assembly::Register*, int> rrv = regGroup->GetReg(8);
        if (!rrv) return std::unexpected<int>(rrv.error());
        otava::assembly::Register* resultReg = *rrv;
        regRv = assemblyContext->GetGlobalReg(8, otava::assembly::RegisterGroupKind::rax);
        if (!regRv) return std::unexpected<int>(regRv.error());
        regRv = MakeIntegerRegOperand(inst.LeftPtr(), *regRv, codeGenerator);
        if (!regRv) return std::unexpected<int>(regRv.error());
        otava::assembly::Register* leftReg = *regRv;
        subInst->AddOperand(leftReg);
        regRv = assemblyContext->GetGlobalReg(8, otava::assembly::RegisterGroupKind::rbx);
        if (!regRv) return std::unexpected<int>(regRv.error());
        regRv = MakeIntegerRegOperand(inst.RightPtr(), *regRv, codeGenerator);
        if (!regRv) return std::unexpected<int>(regRv.error());
        otava::assembly::Register* rightReg = *regRv;
        subInst->AddOperand(rightReg);
        codeGenerator.Emit(subInst);
        regRv = assemblyContext->GetGlobalReg(8, otava::assembly::RegisterGroupKind::rdx);
        if (!regRv) return std::unexpected<int>(regRv.error());
        otava::assembly::Register* rdx = *regRv;
        otava::assembly::Instruction* xorInst = new otava::assembly::Instruction(otava::assembly::OpCode::XOR);
        xorInst->AddOperand(rdx);
        xorInst->AddOperand(rdx);
        codeGenerator.Emit(xorInst);
        regRv = assemblyContext->GetGlobalReg(8, otava::assembly::RegisterGroupKind::rax);
        if (!regRv) return std::unexpected<int>(regRv.error());
        otava::assembly::Register* rax = *regRv;
        otava::assembly::Instruction* movInst = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
        movInst->AddOperand(rax);
        movInst->AddOperand(leftReg);
        codeGenerator.Emit(movInst);
        otava::assembly::Instruction* divInst = new otava::assembly::Instruction(otava::assembly::OpCode::DIV);
        divInst->AddOperand(rcx);
        codeGenerator.Emit(divInst);
        otava::assembly::Instruction* movResultInst = new otava::assembly::Instruction(otava::assembly::OpCode::MOV);
        movResultInst->AddOperand(resultReg);
        movResultInst->AddOperand(rax);
        codeGenerator.Emit(movResultInst);
    }
    else
    {
        return codeGenerator.Error("error emitting ptrdiff instruction: reg group for inst not found");
    }
    return std::expected<bool, int>(true);
}

CodeGenerator::CodeGenerator(Context* context_, const std::string& assemblyFilePath_) :
    Visitor(context_), context(context_), file(assemblyFilePath_), currentFunction(nullptr), currentInst(nullptr), assemblyFunction(nullptr), leader(false),
    registerAllocator(nullptr), data(nullptr), label(), dataInstruction(nullptr), prevDataOpCode(otava::assembly::OpCode::DB), currentOffset(0)
{
    context->AssemblyContext()->SetFile(&file);
}

const soul::ast::Span& CodeGenerator::Span() const
{
    return currentInst->Span();
}

int CodeGenerator::ExitLabelId() const
{
    return currentInst->Parent()->Parent()->LastBasicBlock()->Id() + 1;
}

void CodeGenerator::Emit(otava::assembly::Instruction* assemblyInstruction)
{
    if (leader)
    {
        leader = false;
        assemblyInstruction->SetLabel("@" + std::to_string(currentInst->Parent()->Id()));
    }
    currentInst->SetAssemblyInstruction(assemblyInstruction);
    assemblyFunction->AddInstruction(assemblyInstruction);
}

void CodeGenerator::EmitDataValue(std::unique_ptr<otava::assembly::Value>&& dataValue, otava::assembly::OpCode dataOpCode)
{
    if (prevDataOpCode != dataOpCode)
    {
        if (dataInstruction)
        {
            data->AddInstruction(std::move(dataInstruction));
            dataInstruction.reset();
        }
    }
    if (!dataInstruction)
    {
        dataInstruction.reset(new otava::assembly::Instruction(dataOpCode));
        dataInstruction->SetNoColon();
    }
    if (leader)
    {
        leader = false;
        if (!dataInstruction->Label().empty())
        {
            data->AddInstruction(std::move(dataInstruction));
            dataInstruction.reset(new otava::assembly::Instruction(dataOpCode));
            dataInstruction->SetNoColon();
        }
        dataInstruction->SetLabel(label);
        label.clear();
    }
    while (dataInstruction->Length() + dataValue->Length() > otava::assembly::maxAssemblyLineLength && dataValue->CanSplit())
    {
        std::unique_ptr<otava::assembly::Value> next(dataValue->Split(otava::assembly::maxAssemblyLineLength - dataInstruction->Length()));
        dataInstruction->AddOperand(dataValue.release());
        data->AddInstruction(std::move(dataInstruction));
        dataInstruction.reset(new otava::assembly::Instruction(dataOpCode));
        dataInstruction->SetNoColon();
        dataValue.reset(next.release());
    }
    dataInstruction->AddOperand(dataValue.release());
    data->AddInstruction(std::move(dataInstruction));
    dataInstruction.reset(new otava::assembly::Instruction(dataOpCode));
    dataInstruction->SetNoColon();
    prevDataOpCode = dataOpCode;
}

void CodeGenerator::Visit(GlobalVariable& globalVariable)
{
    if (!Valid()) return;
    if (data && dataInstruction.get())
    {
        data->AddInstruction(std::move(dataInstruction));
        dataInstruction.reset();
    }
    if (globalVariable.Initializer())
    {
        file.GetDeclarationSection().AddPublicDeclaration(new otava::assembly::PublicDeclaration(globalVariable.Name()));
        label = globalVariable.Name();
        data = new otava::assembly::Data();
        file.GetDataSection().AddData(data);
        leader = true;
        currentOffset = 0;
        globalVariable.Initializer()->Accept(*this);
        if (!Valid()) return;
        ByteType* byteType = context->GetTypes().GetByteType();
        while ((currentOffset & 7) != 0)
        {
            ByteValue value(0u, byteType);
            Visit(value);
        }
    }
    else
    {
        file.GetDeclarationSection().AddExternalDataDeclaration(new otava::assembly::ExternalDataDeclaration(globalVariable.Name()));
    }
}

void CodeGenerator::Visit(Function& function)
{
    if (!Valid()) return;
    context->IncTotalFunctions();
    if (!function.IsDefined())
    {
        file.GetDeclarationSection().AddFunctionDeclaration(new otava::assembly::FunctionDeclaration(function.Name()));
    }
    else
    {
        std::string fullFunctionName = function.ResolveFullName();
        if (function.IsLinkOnce())
        {
            file.GetDeclarationSection().AddLinkOnceDeclaration(new otava::assembly::LinkOnceDeclaration(function.Name()));
        }
        else
        {
            file.GetDeclarationSection().AddPublicDeclaration(new otava::assembly::PublicDeclaration(function.Name()));
        }
        currentFunction = &function;
        context->AssemblyContext()->ResetRegisterPool();
        assemblyFunction = file.GetCodeSection().CreateFunction(function.Name());
        if (!fullFunctionName.empty())
        {
            assemblyFunction->SetComment(fullFunctionName);
        }
        context->AssemblyContext()->SetCurrentFunction(assemblyFunction);
        std::unique_ptr<RegisterAllocator> linearScanRregisterAllocator = CreateLinearScanRegisterAllocator(function, Ctx());
        registerAllocator = linearScanRregisterAllocator.get();
        function.VisitBasicBlocks(*this);
        assemblyFunction->SetActiveFunctionPart(otava::assembly::FunctionPart::prologue);
        std::expected<bool, int> rv = EmitPrologue(*this);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        assemblyFunction->SetActiveFunctionPart(otava::assembly::FunctionPart::epilogue);
        rv = EmitEpilogue(*this);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
    }
}

void CodeGenerator::Visit(BasicBlock& basicBlock)
{
    if (!Valid()) return;
    Instruction* inst = basicBlock.FirstInstruction();
    leader = true;
    while (inst)
    {
        currentInst = inst;
        if (inst->IsArgInstruction() || inst->IsProcedureCallInstruction() || inst->IsFunctionCallInstruction())
        {
            inst->Accept(*this);
            if (!Valid()) return;
        }
        else
        {
            std::expected<RegisterAllocationAction, int> runRv = registerAllocator->Run(inst);
            if (!runRv)
            {
                SetError(runRv.error());
                return;
            }
            RegisterAllocationAction action = *runRv;
            if (action == RegisterAllocationAction::spill)
            {
                for (const SpillData& spillData : registerAllocator->GetSpillData())
                {
                    otava::assembly::Instruction* storeInst = nullptr;
                    if (spillData.registerGroupToSpill->IsFloatingPointReg())
                    {
                        std::expected<otava::assembly::Instruction*, int> rv = EmitFloatingPointStore(
                            8, spillData.spillToFrameLocation, spillData.registerGroupToSpill, *this);
                        if (!rv)
                        {
                            SetError(rv.error());
                            return;
                        }
                        storeInst = *rv;
                    }
                    else
                    {
                        std::expected<otava::assembly::Instruction*, int> rv = EmitIntegerStore(8, spillData.spillToFrameLocation, spillData.registerGroupToSpill, *this);
                        if (!rv)
                        {
                            SetError(rv.error());
                            return;
                        }
                        storeInst = *rv;
                    }
                    Instruction* instToSpill = spillData.instToSpill;
                    otava::assembly::Instruction* assemblyInstruction = instToSpill->AssemblyInstruction();
                    if (assemblyInstruction)
                    {
                        assemblyInstruction->LinkAfter(storeInst->Clone());
                    }
                    else
                    {
                        assemblyFunction->AddInstruction(storeInst->Clone());
                    }
                    registerAllocator->RemoveFromRegisterGroups(instToSpill);
                }
            }
            inst->Accept(*this);
            if (!Valid()) return;
        }
        inst = inst->Next();
    }
}

void CodeGenerator::Visit(RetInstruction& inst)
{
    if (!Valid()) return;
    if (inst.IsFloatingPointInstruction())
    {
        auto rv = EmitFloatingPointRet(inst, *this);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
    }
    else
    {
        auto rv = EmitIntegerRet(inst, *this);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
    }
}

void CodeGenerator::Visit(SignExtendInstruction& inst)
{
    if (!Valid()) return;
    auto rv = EmitSignExtend(inst, *this);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

void CodeGenerator::Visit(ZeroExtendInstruction& inst)
{
    if (!Valid()) return;
    auto rv = EmitZeroExtend(inst, *this);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

void CodeGenerator::Visit(FloatingPointExtendInstruction& inst)
{
    if (!Valid()) return;
    auto rv = EmitFloatingPointExtend(inst, *this);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

void CodeGenerator::Visit(ParamInstruction& inst)
{
    if (!Valid()) return;
    if (inst.IsFloatingPointInstruction())
    {
        auto rv = EmitFloatingPointParam(inst, *this);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
    }
    else
    {
        std::expected<bool, int> rv = EmitIntegerParam(inst, *this);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
    }
}

void CodeGenerator::Visit(LoadInstruction& inst)
{
    if (!Valid()) return;
    if (inst.IsFloatingPointInstruction())
    {
        std::expected<bool, int> rv = EmitFloatingPointLoad(inst, *this);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
    }
    else
    {
        std::expected<bool, int> rv = EmitIntegerLoad(inst, *this);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
    }
}

void CodeGenerator::Visit(StoreInstruction& inst)
{
    if (!Valid()) return;
    if (inst.IsFloatingPointInstruction())
    {
        auto rv = EmitFloatingPointStore(inst, *this);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
    }
    else
    {
        auto rv = EmitIntegerStore(inst, *this);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
    }
}

void CodeGenerator::Visit(ArgInstruction& inst)
{
    if (!Valid()) return;
    args.push_back(&inst);
}

void CodeGenerator::Visit(ProcedureCallInstruction& inst)
{
    if (!Valid()) return;
    auto rv = EmitProcedureCall(inst, args, *this);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    args.clear();
}

void CodeGenerator::Visit(FunctionCallInstruction& inst)
{
    if (!Valid()) return;
    auto rv = EmitFunctionCall(inst, args, *this);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    args.clear();
}

void CodeGenerator::Visit(ElemAddrInstruction& inst)
{
    if (!Valid()) return;
    std::expected<bool, int> rv = EmitElemAddr(inst, *this);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

void CodeGenerator::Visit(PtrOffsetInstruction& inst)
{
    if (!Valid()) return;
    auto rv = EmitPtrOffset(inst, *this);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

void CodeGenerator::Visit(PtrDiffInstruction& inst)
{
    if (!Valid()) return;
    auto rv = EmitPtrDiff(inst, *this);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

void CodeGenerator::Visit(TruncateInstruction& inst)
{
    if (!Valid()) return;
    if (inst.GetType()->IsIntegerType() || inst.GetType()->IsBooleanType())
    {
        auto rv = EmitIntegerTruncate(inst, *this);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
    }
    else if (inst.GetType()->IsFloatingPointType())
    {
        auto rv = EmitFloatingPointTruncate(inst, *this);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
    }
}

void CodeGenerator::Visit(AddInstruction& inst)
{
    if (!Valid()) return;
    if (inst.GetType()->IsIntegerType())
    {
        auto rv = EmitIntegerBinOpInst(inst, *this);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
    }
    else if (inst.GetType()->IsFloatingPointType())
    {
        auto rv = EmitFloatingPointBinOpInst(inst, *this);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
    }
}

void CodeGenerator::Visit(SubInstruction& inst)
{
    if (!Valid()) return;
    if (inst.GetType()->IsIntegerType())
    {
        auto rv = EmitIntegerBinOpInst(inst, *this);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
    }
    else if (inst.GetType()->IsFloatingPointType())
    {
        auto rv = EmitFloatingPointBinOpInst(inst, *this);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
    }
}

void CodeGenerator::Visit(MulInstruction& inst)
{
    if (!Valid()) return;
    if (inst.GetType()->IsIntegerType())
    {
        auto rv = EmitIntegerBinOpInst(inst, *this);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
    }
    else if (inst.GetType()->IsFloatingPointType())
    {
        auto rv = EmitFloatingPointBinOpInst(inst, *this);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
    }
}

void CodeGenerator::Visit(DivInstruction& inst)
{
    if (!Valid()) return;
    if (inst.GetType()->IsIntegerType())
    {
        auto rv = EmitIntegerBinOpInst(inst, *this);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
    }
    else if (inst.GetType()->IsFloatingPointType())
    {
        auto rv = EmitFloatingPointBinOpInst(inst, *this);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
    }
}

void CodeGenerator::Visit(ModInstruction& inst)
{
    if (!Valid()) return;
    auto rv = EmitIntegerBinOpInst(inst, *this);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

void CodeGenerator::Visit(AndInstruction& inst)
{
    if (!Valid()) return;
    auto rv = EmitIntegerBinOpInst(inst, *this);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

void CodeGenerator::Visit(OrInstruction& inst)
{
    if (!Valid()) return;
    auto rv = EmitIntegerBinOpInst(inst, *this);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

void CodeGenerator::Visit(XorInstruction& inst)
{
    if (!Valid()) return;
    auto rv = EmitIntegerBinOpInst(inst, *this);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

void CodeGenerator::Visit(ShlInstruction& inst)
{
    if (!Valid()) return;
    auto rv = EmitIntegerBinOpInst(inst, *this);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

void CodeGenerator::Visit(ShrInstruction& inst)
{
    if (!Valid()) return;
    auto rv = EmitIntegerBinOpInst(inst, *this);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

void CodeGenerator::Visit(BitcastInstruction& inst)
{
    if (!Valid()) return;
    auto rv = EmitBitcast(inst, *this);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

void CodeGenerator::Visit(IntToFloatInstruction& inst)
{
    if (!Valid()) return;
    auto rv = EmitIntToFloat(inst, *this);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

void CodeGenerator::Visit(FloatToIntInstruction& inst)
{
    if (!Valid()) return;
    auto rv = EmitFloatToInt(inst, *this);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

void CodeGenerator::Visit(IntToPtrInstruction& inst)
{
    if (!Valid()) return;
    auto rv = EmitIntToPtr(inst, *this);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

void CodeGenerator::Visit(PtrToIntInstruction& inst)
{
    if (!Valid()) return;
    auto rv = EmitPtrToInt(inst, *this);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

void CodeGenerator::Visit(EqualInstruction& inst)
{
    if (!Valid()) return;
    if (inst.Left()->GetType()->IsFloatingPointType())
    {
        auto rv = EmitFloatingPointEqual(inst, *this);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
    }
    else
    {
        auto rv = EmitIntegerEqual(inst, *this);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
    }
}

void CodeGenerator::Visit(LessInstruction& inst)
{
    if (!Valid()) return;
    if (inst.Left()->GetType()->IsFloatingPointType())
    {
        auto rv = EmitFloatingPointLess(inst, *this);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
    }
    else
    {
        auto rv = EmitIntegerLess(inst, *this);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
    }
}

void CodeGenerator::Visit(JmpInstruction& inst)
{
    if (!Valid()) return;
    EmitJmp(inst, *this);
}

void CodeGenerator::Visit(BranchInstruction& inst)
{
    if (!Valid()) return;
    auto rv = EmitBranch(inst, *this);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

void CodeGenerator::Visit(NotInstruction& inst)
{
    if (!Valid()) return;
    auto rv = EmitNot(inst, *this);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

void CodeGenerator::Visit(NegInstruction& inst)
{
    if (!Valid()) return;
    if (inst.IsFloatingPointInstruction())
    {
        auto rv = EmitFloatingPointNeg(inst, *this);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
    }
    else
    {
        auto rv = EmitIntegerNeg(inst, *this);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
    }
}

void CodeGenerator::Visit(NoOperationInstruction& inst)
{
    if (!Valid()) return;
    EmitNop(inst, *this);
}

void CodeGenerator::Visit(SwitchInstruction& inst)
{
    if (!Valid()) return;
    auto rv = EmitSwitch(inst, *this);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

void CodeGenerator::Visit(BoolValue& value)
{
    if (!Valid()) return;
    EmitDataValue(std::unique_ptr<otava::assembly::Value>(new otava::assembly::IntegerLiteral(value.ToInteger(), 1)), otava::assembly::OpCode::DB);
    currentOffset += 1;
}

void CodeGenerator::Visit(SByteValue& value)
{
    if (!Valid()) return;
    EmitDataValue(std::unique_ptr<otava::assembly::Value>(new otava::assembly::IntegerLiteral(value.GetValue(), 1)), otava::assembly::OpCode::DB);
    currentOffset += 1;
}

void CodeGenerator::Visit(ByteValue& value)
{
    if (!Valid()) return;
    EmitDataValue(std::unique_ptr<otava::assembly::Value>(new otava::assembly::IntegerLiteral(value.GetValue(), 1)), otava::assembly::OpCode::DB);
    currentOffset += 1;
}

void CodeGenerator::Visit(ShortValue& value)
{
    if (!Valid()) return;
    EmitDataValue(std::unique_ptr<otava::assembly::Value>(new otava::assembly::IntegerLiteral(value.GetValue(), 2)), otava::assembly::OpCode::DW);
    currentOffset += 2;
}

void CodeGenerator::Visit(UShortValue& value)
{
    if (!Valid()) return;
    EmitDataValue(std::unique_ptr<otava::assembly::Value>(new otava::assembly::IntegerLiteral(value.GetValue(), 2)), otava::assembly::OpCode::DW);
    currentOffset += 2;
}

void CodeGenerator::Visit(IntValue& value)
{
    if (!Valid()) return;
    EmitDataValue(std::unique_ptr<otava::assembly::Value>(new otava::assembly::IntegerLiteral(value.GetValue(), 4)), otava::assembly::OpCode::DD);
    currentOffset += 4;
}

void CodeGenerator::Visit(UIntValue& value)
{
    if (!Valid()) return;
    EmitDataValue(std::unique_ptr<otava::assembly::Value>(new otava::assembly::IntegerLiteral(value.GetValue(), 4)), otava::assembly::OpCode::DD);
    currentOffset += 4;
}

void CodeGenerator::Visit(LongValue& value)
{
    if (!Valid()) return;
    EmitDataValue(std::unique_ptr<otava::assembly::Value>(new otava::assembly::IntegerLiteral(value.GetValue(), 8)), otava::assembly::OpCode::DQ);
    currentOffset += 8;
}

void CodeGenerator::Visit(ULongValue& value)
{
    if (!Valid()) return;
    EmitDataValue(std::unique_ptr<otava::assembly::Value>(new otava::assembly::IntegerLiteral(value.GetValue(), 8)), otava::assembly::OpCode::DQ);
    currentOffset += 8;
}

void CodeGenerator::Visit(FloatValue& value)
{
    if (!Valid()) return;
    EmitDataValue(std::unique_ptr<otava::assembly::Value>(new otava::assembly::FloatLiteral(value.GetValue())), otava::assembly::OpCode::REAL4);
    currentOffset += 4;
}

void CodeGenerator::Visit(DoubleValue& value)
{
    if (!Valid()) return;
    EmitDataValue(std::unique_ptr<otava::assembly::Value>(new otava::assembly::DoubleLiteral(value.GetValue())), otava::assembly::OpCode::REAL8);
    currentOffset += 8;
}

void CodeGenerator::Visit(NullValue& value)
{
    if (!Valid()) return;
    EmitDataValue(std::unique_ptr<otava::assembly::Value>(new otava::assembly::IntegerLiteral(0, 8)), otava::assembly::OpCode::DQ);
    currentOffset += 8;
}

void CodeGenerator::Visit(AddressValue& value)
{
    if (!Valid()) return;
    EmitDataValue(std::unique_ptr<otava::assembly::Value>(new otava::assembly::Symbol(value.GetValue()->Name())), otava::assembly::OpCode::DQ);
    currentOffset += 8;
}

void CodeGenerator::Visit(ArrayValue& value)
{
    if (!Valid()) return;
    Type* type = value.GetType();
    std::int64_t start = currentOffset;
    Value* zero = context->GetByteValue(static_cast<std::uint8_t>(0u));
    for (const Value* element : value.Elements())
    {
        Type* elementType = element->GetType();
        element->Accept(*this);
        if (!Valid()) return;
        if (currentOffset > 0)
        {
            std::int64_t alignment = elementType->Alignment();
            std::int64_t elementOffset = alignment * ((currentOffset - 1) / alignment + 1);
            while (currentOffset < elementOffset)
            {
                zero->Accept(*this);
                if (!Valid()) return;
            }
        }
    }
    while (currentOffset - start < type->Size())
    {
        zero->Accept(*this);
        if (!Valid()) return;
    }
}

void CodeGenerator::Visit(StructureValue& value)
{
    if (!Valid()) return;
    StructureType* structureType = nullptr;
    Type* type = value.GetType();
    if (type->IsStructureType())
    {
        structureType = static_cast<StructureType*>(type);
    }
    else
    {
        std::unexpected<int> err = Error("structure type expected");
        SetError(err.error());
        return;
    }
    std::int64_t start = currentOffset;
    std::int64_t n = value.FieldValues().size();
    Value* zero = context->GetByteValue(static_cast<std::uint8_t>(0u));
    for (std::int64_t i = 0; i < n; ++i)
    {
        std::int64_t fieldOffset = structureType->GetFieldOffset(i);
        while (currentOffset - start < fieldOffset)
        {
            zero->Accept(*this);
            if (!Valid()) return;
        }
        Value* fieldValue = value.FieldValues()[i];
        fieldValue->Accept(*this);
        if (!Valid()) return;
    }
    while (currentOffset - start < structureType->Size())
    {
        zero->Accept(*this);
        if (!Valid()) return;
    }
}

void CodeGenerator::Visit(StringValue& value)
{
    if (!Valid()) return;
    std::string hexByteStr;
    std::string stringValue;
    int state = 0;
    std::string val = value.ToString();
    val = val.substr(1, val.length() - 2);
    for (char c : val)
    {
        switch (state)
        {
            case 0:
            {
                if (c == '\\')
                {
                    if (!stringValue.empty())
                    {
                        EmitDataValue(std::unique_ptr<otava::assembly::Value>(new otava::assembly::StringLiteral(stringValue)), otava::assembly::OpCode::DB);
                        stringValue.clear();
                    }
                    state = 1;
                }
                else
                {
                    stringValue.append(1, c);
                    currentOffset += 1;
                }
                break;
            }
            case 1:
            {
                hexByteStr.append(1, c);
                state = 2;
                break;
            }
            case 2:
            {
                hexByteStr.append(1, c);
                std::uint8_t value = util::ParseHexByte(hexByteStr);
                EmitDataValue(std::unique_ptr<otava::assembly::Value>(new otava::assembly::IntegerLiteral(value, 1)), otava::assembly::OpCode::DB);
                currentOffset += 1;
                hexByteStr.clear();
                state = 0;
                break;
            }
        }
    }
    if (!stringValue.empty())
    {
        EmitDataValue(std::unique_ptr<otava::assembly::Value>(new otava::assembly::StringLiteral(stringValue)), otava::assembly::OpCode::DB);
        stringValue.clear();
    }
}

void CodeGenerator::Visit(StringArrayValue& value)
{
    if (!Valid()) return;
    for (auto elementValue : value.Elements())
    {
        elementValue->Accept(*this);
        if (!Valid()) return;
    }
}

void CodeGenerator::Visit(ConversionValue& value)
{
    if (!Valid()) return;
    value.From()->Accept(*this);
}

void CodeGenerator::Visit(SymbolValue& value)
{
    if (!Valid()) return;
    EmitDataValue(std::unique_ptr<otava::assembly::Value>(new otava::assembly::Symbol(value.GetSymbol())), otava::assembly::OpCode::DQ);
    currentOffset += 8;
}

std::unexpected<int> CodeGenerator::Error(const std::string& message)
{
    return otava::intermediate::Error(message, currentInst->Span(), context);
}

void CodeGenerator::WriteOutputFile(bool verbose)
{
    if (data && dataInstruction.get())
    {
        data->AddInstruction(std::move(dataInstruction));
    }
    file.Write();
    if (verbose)
    {
        std::cout << "==> " << file.FilePath() << "\n";
    }
}

void CodeGenerator::EmitJumpToExit(RetInstruction& retInst)
{
    int targetLabelId = ExitLabelId();
    otava::assembly::Instruction* jmpInst = new otava::assembly::Instruction(otava::assembly::OpCode::JMP);
    jmpInst->AddOperand(context->AssemblyContext()->MakeSymbol("@" + std::to_string(targetLabelId)));
    Emit(jmpInst);
}

void CodeGenerator::EmitBranchJumps(BranchInstruction& branchInst)
{
    otava::assembly::Context* assemblyContext = context->AssemblyContext();
    otava::assembly::Instruction* jnzInstruction = new otava::assembly::Instruction(otava::assembly::OpCode::JNZ);
    jnzInstruction->AddOperand(assemblyContext->MakeSymbol("@" + std::to_string(branchInst.TrueTargetBasicBlock()->Id())));
    Emit(jnzInstruction);
    otava::assembly::Instruction* jmpInstruction = new otava::assembly::Instruction(otava::assembly::OpCode::JMP);
    jmpInstruction->AddOperand(assemblyContext->MakeSymbol("@" + std::to_string(branchInst.FalseTargetBasicBlock()->Id())));
    Emit(jmpInstruction);
}

std::expected<bool, int> GenerateCode(Context& context, CodeGenerator& codeGenerator, bool verbose)
{
    if (!codeGenerator) return std::unexpected<int>(codeGenerator.GetError());
    codeGenerator.Ctx()->GetData().VisitGlobalVariables(codeGenerator);
    if (!codeGenerator) return std::unexpected<int>(codeGenerator.GetError());
    codeGenerator.Ctx()->GetCode().VisitFunctions(codeGenerator);
    if (!codeGenerator) return std::unexpected<int>(codeGenerator.GetError());
    codeGenerator.WriteOutputFile(verbose);
    if (!codeGenerator) return std::unexpected<int>(codeGenerator.GetError());
    return std::expected<bool, int>(true);
}

} // otava::intermediate
