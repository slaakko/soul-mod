// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.optimizer.inliner;

namespace otava::optimizer {

std::expected<bool, int> ReplaceParamsWithArgs(otava::intermediate::Instruction* callInst, otava::intermediate::ArgInstruction* firstArg, 
    otava::intermediate::Function* callee, otava::intermediate::Function* originalCallee, otava::intermediate::Context* context)
{
    otava::intermediate::BasicBlock* bb = callee->FirstBasicBlock();
    while (bb)
    {
        otava::intermediate::Instruction* inst = bb->FirstInstruction();
        while (inst)
        {
            otava::intermediate::Instruction* next = inst->Next();
            if (inst->IsParamInstruction())
            {
                if (firstArg)
                {
                    std::expected<bool, int> rv = inst->ReplaceUsesWith(firstArg->Arg());
                    if (!rv) return rv;
                    otava::intermediate::Instruction* nextArg = firstArg->Next();
                    firstArg->RemoveFromUses();
                    firstArg->Parent()->RemoveInstruction(firstArg);
                    if (nextArg && nextArg->IsArgInstruction())
                    {
                        firstArg = static_cast<otava::intermediate::ArgInstruction*>(nextArg);
                    }
                    else
                    {
                        firstArg = nullptr;
                    }
                }
                else
                {
                    return otava::intermediate::Error("number of arguments and parameters do not match", callInst->Span(), context, originalCallee->Span());
                }
                inst->RemoveFromUses();
                inst->Parent()->RemoveInstruction(inst);
            }
            else
            {
                break;
            }
            inst = next;
        }
        bb = bb->Next();
    }
    return std::expected<bool, int>(true);
}

void MoveInstructions(otava::intermediate::BasicBlock* fromBasicBlock, otava::intermediate::Instruction* afterCallInst,
    std::vector<otava::intermediate::RetInstruction*>& rets)
{
    otava::intermediate::Instruction* inst = fromBasicBlock->FirstInstruction();
    while (inst)
    {
        otava::intermediate::Instruction* next = inst->Next();
        std::unique_ptr<otava::intermediate::Instruction> instToMove(inst->Parent()->RemoveInstruction(inst));
        if (instToMove->IsRetInstruction())
        {
            rets.push_back(static_cast<otava::intermediate::RetInstruction*>(instToMove.get()));
        }
        afterCallInst->Parent()->InsertInstructionAfter(instToMove.release(), afterCallInst);
        afterCallInst = afterCallInst->Next();
        inst = next;
    }
}

std::expected<bool, int> MergeSingleBasicBlock(otava::intermediate::Function* fn, otava::intermediate::BasicBlock* basicBlock, 
    otava::intermediate::Instruction* callInst, otava::intermediate::Context* context)
{
    std::vector<otava::intermediate::RetInstruction*> rets;
    MoveInstructions(basicBlock, callInst, rets);
    otava::intermediate::Function* callee = basicBlock->Parent();
    callee->MoveRegValues(fn);
    fn->SetNumbers();
    if (callInst->IsFunctionCallInstruction())
    {
        if (rets.size() == 1)
        {
            otava::intermediate::RetInstruction* ret = rets.front();
            if (ret->ReturnValue())
            {
                std::expected<bool, int> rv = callInst->ReplaceUsesWith(ret->ReturnValue());
                if (!rv) return rv;
            }
            else
            {
                return otava::intermediate::Error("return value expected", ret->Span(), context);
            }
        }
        else
        {
            return otava::intermediate::Error("single ret instruction expected", callee->Span(), context);
        }
    }
    for (otava::intermediate::RetInstruction* ret : rets)
    {
        ret->RemoveFromUses();
        ret->Parent()->RemoveInstruction(ret);
    }
    callInst->RemoveFromUses();
    callInst->Parent()->RemoveInstruction(callInst);
    return std::expected<bool, int>(true);
}

std::expected<bool, int> MergeManyBasicBlocks(otava::intermediate::Function* fn, otava::intermediate::Function* callee, otava::intermediate::Instruction* callInst,
    otava::intermediate::Context* context)
{
    otava::intermediate::Instruction* lastInst = callInst;
    otava::intermediate::LocalInstruction* localInst = nullptr;
    otava::intermediate::Type* returnType = nullptr;
    otava::intermediate::BasicBlock* targetBB = callInst->Parent()->SplitAfter(callInst);
    if (callInst->IsFunctionCallInstruction())
    {
        returnType = callee->GetType()->ReturnType();
        std::expected<otava::intermediate::Instruction*, int> rv = context->CreateLocal(returnType);
        if (!rv) return std::unexpected<int>(rv.error());
        otava::intermediate::Instruction* inst = *rv;
        localInst = static_cast<otava::intermediate::LocalInstruction*>(inst);
        callInst->Parent()->InsertInstructionAfter(localInst, callInst);
        lastInst = localInst;
    }
    otava::intermediate::BasicBlock* firstMergedBasicBlock = callee->FirstBasicBlock();
    otava::intermediate::BasicBlock* toMerge = firstMergedBasicBlock;
    while (toMerge)
    {
        otava::intermediate::BasicBlock* next = toMerge->Next();
        std::unique_ptr<otava::intermediate::BasicBlock> removedBasicBlock = callee->RemoveBasicBlock(toMerge);
        removedBasicBlock->SetId(fn->GetNextBasicBlockNumber());
        removedBasicBlock->SetContainer(fn->BasicBlocks());
        otava::intermediate::Instruction* last = removedBasicBlock->LastInstruction();
        if (last->IsRetInstruction())
        {
            otava::intermediate::RetInstruction* ret = static_cast<otava::intermediate::RetInstruction*>(last);
            if (callInst->IsFunctionCallInstruction())
            {
                if (ret->ReturnValue())
                {
                    otava::intermediate::StoreInstruction* store = static_cast<otava::intermediate::StoreInstruction*>(
                        context->CreateStore(ret->ReturnValue(), localInst->Result()));
                    store->AddToUses();
                    ret->Parent()->InsertInstructionAfter(store, ret);
                    last = store;
                }
                else
                {
                    return otava::intermediate::Error("return value expected", ret->Span(), context);
                }
            }
            otava::intermediate::JmpInstruction* jmp = static_cast<otava::intermediate::JmpInstruction*>(context->CreateJump(targetBB));
            last->Parent()->InsertInstructionAfter(jmp, last);
            ret->RemoveFromUses();
            removedBasicBlock->RemoveInstruction(ret);
        }
        removedBasicBlock->SetContainer(nullptr);
        fn->InsertBasicBlockBefore(removedBasicBlock.release(), targetBB);
        toMerge = next;
    }
    if (callInst->IsFunctionCallInstruction())
    {
        std::expected<otava::intermediate::Instruction*, int> rv = context->CreateLoad(localInst->Result());
        if (!rv) return std::unexpected<int>(rv.error());
        otava::intermediate::Instruction* inst = *rv;
        otava::intermediate::LoadInstruction* load = static_cast<otava::intermediate::LoadInstruction*>(inst);
        targetBB->InsertFront(load);
        load->AddToUses();
        std::expected<bool, int> brv = callInst->ReplaceUsesWith(load->Result());
        if (!brv) return brv;
    }
    otava::intermediate::JmpInstruction* jmp = static_cast<otava::intermediate::JmpInstruction*>(context->CreateJump(firstMergedBasicBlock));
    callInst->Parent()->InsertInstructionAfter(jmp, lastInst);
    callInst->RemoveFromUses();
    callInst->Parent()->RemoveInstruction(callInst);
    callee->MoveRegValues(fn);
    return std::expected<bool, int>(true);
}

std::expected<bool, int> MergeBasicBlocks(otava::intermediate::Function* fn, otava::intermediate::Function* callee, otava::intermediate::Instruction* callInst,
    otava::intermediate::Context* context)
{
    if (callee->NumBasicBlocks() == 1)
    {
        std::expected<bool, int> rv = MergeSingleBasicBlock(fn, callee->FirstBasicBlock(), callInst, context);
        if (!rv) return rv;
    }
    else if (callee->NumBasicBlocks() > 1)
    {
        std::expected<bool, int> rv = MergeManyBasicBlocks(fn, callee, callInst, context);
        if (!rv) return rv;
    }
    else
    {
        return otava::intermediate::Error("callee has no basic blocks", callee->Span(), context);
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> Inline(otava::intermediate::Function* fn, otava::intermediate::Instruction* callInst, otava::intermediate::ArgInstruction* firstArg,
    otava::intermediate::Function* callee, otava::intermediate::Context* context)
{
    std::expected<otava::intermediate::Function*, int> crv = callee->Clone();
    if (!crv) return std::unexpected<int>(crv.error());
    std::unique_ptr<otava::intermediate::Function> clonedCallee(*crv);
    std::expected<bool, int> rv = ReplaceParamsWithArgs(callInst, firstArg, clonedCallee.get(), callee, context);
    if (!rv) return rv;
    rv = MergeBasicBlocks(fn, clonedCallee.get(), callInst, context);
    if (!rv) return rv;
    fn->SetNumbers();
    return std::expected<bool, int>(true);
}

std::expected<bool, int> Inline(otava::intermediate::Function* fn, otava::intermediate::Context* context)
{
    bool fnInlined = false;
    bool inlined = false;
    int inlineDepth = context->InlineDepth();
    int inlineCount = 0;
    do
    {
        inlined = false;
        otava::intermediate::ArgInstruction* firstArg = nullptr;
        otava::intermediate::BasicBlock* bb = fn->FirstBasicBlock();
        while (bb)
        {
            otava::intermediate::Instruction* inst = bb->FirstInstruction();
            while (inst)
            {
                otava::intermediate::Instruction* next = inst->Next();
                if (inst->IsArgInstruction())
                {
                    if (!firstArg)
                    {
                        firstArg = static_cast<otava::intermediate::ArgInstruction*>(inst);
                    }
                }
                otava::intermediate::Function* callee = nullptr;
                bool isCallInst = false;
                if (inst->IsProcedureCallInstruction())
                {
                    otava::intermediate::ProcedureCallInstruction* procedureCall = static_cast<otava::intermediate::ProcedureCallInstruction*>(inst);
                    callee = procedureCall->CalleeFn();
                    isCallInst = true;
                }
                else if (inst->IsFunctionCallInstruction())
                {
                    otava::intermediate::FunctionCallInstruction* functionCall = static_cast<otava::intermediate::FunctionCallInstruction*>(inst);
                    callee = functionCall->CalleeFn();
                    isCallInst = true;
                }
                if (callee)
                {
                    if (callee != fn)
                    {
                        if (callee->IsInline())
                        {
                            std::expected<bool, int> rv = Inline(fn, inst, firstArg, callee, context);
                            if (!rv) return rv;
                            context->IncInlinedFunctionCalls();
                            fnInlined = true;
                            inlined = true;
                        }
                    }
                }
                if (isCallInst)
                {
                    firstArg = nullptr;
                }
                inst = next;
            }
            bb = bb->Next();
        }
    } while (inlined && ++inlineCount < inlineDepth);
    if (fnInlined)
    {
        context->IncFunctionsInlined();
    }
    return std::expected<bool, int>(true);
}

} // namespace otava::optimizer
