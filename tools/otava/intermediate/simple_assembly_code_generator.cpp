// =================================
// Copyright (c) 2023 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.intermediate.simple.assembly.code.generator;

import otava.intermediate.error;
import otava.intermediate.instruction;
import otava.intermediate.basic.block;
import otava.intermediate.context;
import otava.intermediate.function;
import otava.intermediate.linear_scan_register_allocator;
import otava.intermediate.type;
import otava.intermediate.data;
import otava.intermediate.data_item_adder;
import otava.assembly.function;
import otava.assembly.literal;
import otava.assembly.symbol;

namespace otava::intermediate {

SimpleAssemblyCodeGenerator::SimpleAssemblyCodeGenerator(Context* context_, const std::string& assemblyFilePath_) : 
    CodeGenerator(context_), context(context_), file(assemblyFilePath_), currentFunction(nullptr), currentInst(nullptr), leader(false), assemblyFunction(), lineNumber(),
    registerAllocator()
{
}

const SourcePos& SimpleAssemblyCodeGenerator::GetSourcePos() const
{
    return currentInst->GetSourcePos();
}

void SimpleAssemblyCodeGenerator::Emit(otava::assembly::Instruction* assemblyInstruction)
{
    if (leader)
    {
        leader = false;
        assemblyInstruction->SetLabel("@" + std::to_string(currentInst->Parent()->Id()));
    }
    assemblyFunction->AddInstruction(assemblyInstruction);
}

int SimpleAssemblyCodeGenerator::ExitLabelId() const
{
    return currentInst->Parent()->Parent()->LastBasicBlock()->Id() + 1;
}

void SimpleAssemblyCodeGenerator::Error(const std::string& message)
{
    otava::intermediate::Error(message, currentInst->GetSourcePos(), GetContext());
}

void SimpleAssemblyCodeGenerator::AddFrameLocation(otava::assembly::UniqueLiteral* frameLoc)
{
    frameLocations.push_back(frameLoc);
}

void SimpleAssemblyCodeGenerator::Write() 
{
    file.Write();
}

void SimpleAssemblyCodeGenerator::Visit(GlobalVariable& globalVariable)
{
    Type* type = globalVariable.GetType(); 
    if (type->IsBytePtrType())
    {
        if (globalVariable.Initializer())
        {
            PointerType* pointerType = static_cast<PointerType*>(type);
            Type* baseType = pointerType->BaseType();
            otava::assembly::Data* variable = new otava::assembly::Data(globalVariable.Name(), baseType->DataInstruction());
            file.GetDeclarationSection().AddPublicDataDeclaration(new otava::assembly::PublicDataDeclaration(globalVariable.Name()));
            DataItemAdder adder(context, variable);
            globalVariable.Initializer()->Accept(adder);
            file.GetDataSection().AddData(variable);
        }
        else
        {
            file.GetDeclarationSection().AddExternalDataDeclaration(new otava::assembly::ExternalDataDeclaration(globalVariable.Name()));
        }
    }
    else
    {
        if (globalVariable.Initializer())
        {
            otava::assembly::Data* variable = new otava::assembly::Data(globalVariable.Name(), type->DataInstruction());
            file.GetDeclarationSection().AddPublicDataDeclaration(new otava::assembly::PublicDataDeclaration(globalVariable.Name()));
            DataItemAdder adder(context, variable);
            globalVariable.Initializer()->Accept(adder);
            file.GetDataSection().AddData(variable);
        }
        else
        {
            file.GetDeclarationSection().AddExternalDataDeclaration(new otava::assembly::ExternalDataDeclaration(globalVariable.Name()));
        }
    }
}

void SimpleAssemblyCodeGenerator::Visit(Function& function)
{
    if (!function.IsDefined())
    {
        file.GetDeclarationSection().AddFunctionDeclaration(new otava::assembly::FunctionDeclaration(function.Name()));
    }
    else
    {
        file.GetDeclarationSection().AddPublicDataDeclaration(new otava::assembly::PublicDataDeclaration(function.Name()));
        currentFunction = &function;
        Ctx()->AssemblyContext().ResetRegisterPool();
        frameLocations.clear();
        std::unique_ptr<RegisterAllocator> linearScanRregisterAllocator = LinearScanRegisterAllocation(function, Ctx());
        registerAllocator = linearScanRregisterAllocator.get();
        assemblyFunction = file.GetCodeSection().CreateFunction(function.Name());
        function.VisitBasicBlocks(*this);
        PatchFrameLocations();
        assemblyFunction->SetActiveFunctionPart(otava::assembly::FunctionPart::prologue);
        EmitPrologue(*this);
        assemblyFunction->SetActiveFunctionPart(otava::assembly::FunctionPart::epilogue);
        EmitEpilogue(*this);
    }
}

void SimpleAssemblyCodeGenerator::PatchFrameLocations()
{
/*
    Frame& frame = registerAllocator->GetFrame();
    int64_t frameSize = frame.Size();
    for (auto& frameLoc : frameLocations)
    {
        int64_t offset = frameLoc->GetValue();
        int64_t newOffset = frameSize - offset;
        frameLoc->SetValue(newOffset);
    }
*/
}

void SimpleAssemblyCodeGenerator::Visit(BasicBlock& basicBlock)
{
    Instruction* inst = basicBlock.FirstInstruction();
    leader = true;
    while (inst)
    {
        currentInst = inst;
        if (inst->IsArgInstruction() || inst->IsProcedureCallInstruction() || inst->IsFunctionCallInstruction())
        {
            inst->Accept(*this);
        }
        else
        {
            RegisterAllocationAction action = registerAllocator->Run(inst);
            if (action == RegisterAllocationAction::spill)
            {
                for (const SpillData& spillData : registerAllocator->GetSpillData())
                {
                    EmitStore(8, spillData.spillToFrameLocation, spillData.registerGroupToSpill, *this);
                }
            }
            inst->Accept(*this);
        }
        inst = inst->Next();
    }
}

void SimpleAssemblyCodeGenerator::Visit(StoreInstruction& inst)
{
    EmitStore(inst, *this);
}

void SimpleAssemblyCodeGenerator::Visit(LoadInstruction& inst)
{
    EmitLoad(inst, *this);
}

void SimpleAssemblyCodeGenerator::Visit(ElemAddrInstruction& inst)
{
    EmitElemAddr(inst, *this);
}

void SimpleAssemblyCodeGenerator::Visit(PtrOffsetInstruction& inst)
{
    EmitPtrOffset(inst, *this);
}

void SimpleAssemblyCodeGenerator::Visit(PtrDiffInstruction& inst)
{
    EmitPtrDiff(inst, *this);
}

void SimpleAssemblyCodeGenerator::Visit(ArgInstruction& inst)
{
    args.push_back(&inst);
}

void SimpleAssemblyCodeGenerator::Visit(ParamInstruction& inst)
{
    EmitParam(inst, *this);
}

void SimpleAssemblyCodeGenerator::Visit(RetInstruction& inst)
{
    EmitRet(inst, *this);
}

void SimpleAssemblyCodeGenerator::Visit(AddInstruction& inst)
{
    if (inst.GetType()->IsIntegerType())
    {
        EmitIntegerBinOpInst(inst, *this);
    }
    else if (inst.GetType()->IsFloatingPointType())
    {
        EmitFloatingPointBinOpInst(inst, *this);
    }
}

void SimpleAssemblyCodeGenerator::Visit(SubInstruction& inst)
{
    if (inst.GetType()->IsIntegerType())
    {
        EmitIntegerBinOpInst(inst, *this);
    }
    else if (inst.GetType()->IsFloatingPointType())
    {
        EmitFloatingPointBinOpInst(inst, *this);
    }
}

void SimpleAssemblyCodeGenerator::Visit(MulInstruction& inst)
{
    if (inst.GetType()->IsIntegerType())
    {
        EmitIntegerBinOpInst(inst, *this);
    }
    else if (inst.GetType()->IsFloatingPointType())
    {
        EmitFloatingPointBinOpInst(inst, *this);
    }
}

void SimpleAssemblyCodeGenerator::Visit(DivInstruction& inst)
{
    if (inst.GetType()->IsIntegerType())
    {
        EmitIntegerBinOpInst(inst, *this);
    }
    else if (inst.GetType()->IsFloatingPointType())
    {
        EmitFloatingPointBinOpInst(inst, *this);
    }
}

void SimpleAssemblyCodeGenerator::Visit(ModInstruction& inst)
{
    EmitIntegerBinOpInst(inst, *this);
}

void SimpleAssemblyCodeGenerator::Visit(AndInstruction& inst)
{
    EmitIntegerBinOpInst(inst, *this);
}

void SimpleAssemblyCodeGenerator::Visit(OrInstruction& inst)
{
    EmitIntegerBinOpInst(inst, *this);
}

void SimpleAssemblyCodeGenerator::Visit(XorInstruction& inst)
{
    EmitIntegerBinOpInst(inst, *this);
}

void SimpleAssemblyCodeGenerator::Visit(ShlInstruction& inst)
{
    EmitIntegerBinOpInst(inst, *this);
}

void SimpleAssemblyCodeGenerator::Visit(ShrInstruction& inst)
{
    EmitIntegerBinOpInst(inst, *this);
}

void SimpleAssemblyCodeGenerator::Visit(SignExtendInstruction& inst)
{
    EmitSignExtend(inst, *this);
}

void SimpleAssemblyCodeGenerator::Visit(ZeroExtendInstruction& inst)
{
    EmitZeroExtend(inst, *this);
}

void SimpleAssemblyCodeGenerator::Visit(TruncateInstruction& inst)
{
    EmitTruncate(inst, *this);
}

void SimpleAssemblyCodeGenerator::Visit(BitcastInstruction& inst)
{
    EmitBitcast(inst, *this);
}

void SimpleAssemblyCodeGenerator::Visit(IntToFloatInstruction& inst)
{
    EmitIntToFloat(inst, *this);
}

void SimpleAssemblyCodeGenerator::Visit(FloatToIntInstruction& inst)
{
    EmitFloatToInt(inst, *this);
}

void SimpleAssemblyCodeGenerator::Visit(IntToPtrInstruction& inst)
{
    EmitIntToPtr(inst, *this);
}

void SimpleAssemblyCodeGenerator::Visit(PtrToIntInstruction& inst)
{
    EmitPtrToInt(inst, *this);
}

void SimpleAssemblyCodeGenerator::Visit(EqualInstruction& inst)
{
    EmitEqual(inst, *this);
}

void SimpleAssemblyCodeGenerator::Visit(LessInstruction& inst)
{
    EmitLess(inst, *this);
}

void SimpleAssemblyCodeGenerator::Visit(JmpInstruction& inst)
{
    EmitJmp(inst, *this);
}

void SimpleAssemblyCodeGenerator::Visit(BranchInstruction& inst)
{
    EmitBranch(inst, *this);
}

void SimpleAssemblyCodeGenerator::Visit(ProcedureCallInstruction& inst) 
{
    EmitProcedureCall(inst, args, *this);
    args.clear();
}

void SimpleAssemblyCodeGenerator::Visit(FunctionCallInstruction& inst)
{
    EmitFunctionCall(inst, args, *this);
    args.clear();
}

void SimpleAssemblyCodeGenerator::Visit(NotInstruction& inst)
{
    EmitNot(inst, *this);
}

void SimpleAssemblyCodeGenerator::Visit(NegInstruction& inst)
{
    EmitNeg(inst, *this);
}

void SimpleAssemblyCodeGenerator::Visit(NoOperationInstruction& inst)
{
    EmitNop(inst, *this);
}

void SimpleAssemblyCodeGenerator::Visit(SwitchInstruction& inst)
{
    EmitSwitch(inst, *this);
}

} // otava::intermediate
