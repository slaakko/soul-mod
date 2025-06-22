// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.cleanup_list;

import otava.symbols.bound.tree;
import otava.symbols.emitter;
import otava.intermediate;

namespace otava::symbols {

CleanupList::CleanupList(Emitter& emitter) : dirty(false)
{
}

void CleanupList::Add(BoundFunctionCallNode* destructorCall)
{
    list.push_back(std::unique_ptr<BoundFunctionCallNode>(destructorCall));
    dirty = true;
}

void CleanupList::Remove(int count)
{
    if (list.size() >= count)
    {
        list.erase(list.begin() + list.size() - count, list.end());
        dirty = true;
    }
    else
    {
        list.clear();
        dirty = true;
    }
}

void CleanupList::Clear()
{
    list.clear();
    dirty = false;
}

void CleanupList::GenerateCleanup(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context)
{
    Reset();
    otava::intermediate::BasicBlock* trueBlock = emitter.CreateBasicBlock();
    otava::intermediate::BasicBlock* falseBlock = emitter.CreateBasicBlock();
    otava::intermediate::Value* ctx = emitter.EmitCall(emitter.EhFunctions().PushContextFunction(), std::vector<otava::intermediate::Value*>());
    otava::intermediate::Value* intValue = emitter.EmitCall(emitter.EhFunctions().SaveContextFunction(), std::vector<otava::intermediate::Value*>(1, ctx));
    otava::intermediate::Value* boolValue = emitter.EmitNot(emitter.EmitEqual(intValue, emitter.EmitInt(0)));
    emitter.EmitBranch(boolValue, trueBlock, falseBlock);
    emitter.SetCurrentBasicBlock(trueBlock);
    int n = list.size();
    for (int i = n - 1; i >= 0; --i)
    {
        BoundFunctionCallNode* destructorCall = list[i].get();
        destructorCall->Load(emitter, OperationFlags::none, sourcePos, context);
    }
    otava::intermediate::Value* poppedCtx = emitter.EmitCall(emitter.EhFunctions().PopContextFunction(), std::vector<otava::intermediate::Value*>());
    std::vector<otava::intermediate::Value*> restoreContextArgs;
    restoreContextArgs.push_back(poppedCtx);
    restoreContextArgs.push_back(emitter.EmitInt(1));
    emitter.EmitCall(emitter.EhFunctions().RestoreContextFunction(), restoreContextArgs);
    emitter.EmitRet(emitter.RetValue());
    emitter.SetCurrentBasicBlock(falseBlock);
}

void CleanupList::GeneratePopContext(Emitter& emitter, bool reset)
{
    if (!dirty) return;
    emitter.EmitCall(emitter.EhFunctions().PopContextFunction(), std::vector<otava::intermediate::Value*>());
    if (reset)
    {
        Reset();
    }
}

} // namespace otava::symbols
