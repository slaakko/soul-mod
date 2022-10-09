// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.codegen;

import otava.symbols.emitter;
import otava.symbols.function.symbol;
import otava.intermediate.code;
import otava.intermediate.compile.unit;
import otava.intermediate.context;
import otava.intermediate.metadata;
import otava.intermediate.parser;
import otava.intermediate.register_allocator;
import otava.intermediate.verify;
import otava.intermediate.code.generator;
import otava.intermediate.instruction;
import otava.intermediate.basic.block;
import otava.symbols.bound.tree;
import otava.symbols.bound.tree.visitor;
import otava.symbols.exception;
import otava.symbols.value;
import std.core;
import std.filesystem;
import util;

namespace otava::codegen {

struct SwitchTarget
{
    SwitchTarget(otava::intermediate::BasicBlock* block_, otava::symbols::BoundStatementNode* statement_, otava::symbols::BoundExpressionNode* expr_);
    otava::intermediate::BasicBlock* block;
    otava::symbols::BoundStatementNode* statement;
    otava::symbols::BoundExpressionNode* expr;
};

SwitchTarget::SwitchTarget(otava::intermediate::BasicBlock* block_, otava::symbols::BoundStatementNode* statement_, otava::symbols::BoundExpressionNode* expr_) :
    block(block_), statement(statement_), expr(expr_)
{
}

class SwitchTargets
{
public:
    SwitchTargets();
    SwitchTarget* Default() const { return defaultTarget.get(); }
    void AddCase(SwitchTarget* caseTarget);
    void SetDefault(SwitchTarget* defaultTarget_);
    const std::vector<std::unique_ptr<SwitchTarget>>& Cases() const { return caseTargets; }
private:
    std::unique_ptr<SwitchTarget> defaultTarget;
    std::vector<std::unique_ptr<SwitchTarget>> caseTargets;
};

SwitchTargets::SwitchTargets()
{
}

void SwitchTargets::SetDefault(SwitchTarget* defaultTarget_)
{
    defaultTarget.reset(defaultTarget_);
}

void SwitchTargets::AddCase(SwitchTarget* caseTarget)
{
    caseTargets.push_back(std::unique_ptr<SwitchTarget>(caseTarget));
}

class SwitchTargetCollector : public otava::symbols::DefaultBoundTreeVisitor
{
public:
    SwitchTargetCollector(otava::symbols::Emitter& emitter_);
    SwitchTargets GetSwitchTargets() { return std::move(switchTargets); }
    void Visit(otava::symbols::BoundCaseStatementNode& node) override;
    void Visit(otava::symbols::BoundDefaultStatementNode& node) override;
private:
    otava::symbols::Emitter& emitter;
    SwitchTargets switchTargets;
};

SwitchTargetCollector::SwitchTargetCollector(otava::symbols::Emitter& emitter_) : emitter(emitter_)
{
}

void SwitchTargetCollector::Visit(otava::symbols::BoundCaseStatementNode& node)
{
    SwitchTarget* caseTarget = new SwitchTarget(emitter.CreateBasicBlock(), node.Statement(), node.CaseExpr());
    switchTargets.AddCase(caseTarget);
}

void SwitchTargetCollector::Visit(otava::symbols::BoundDefaultStatementNode& node)
{
    SwitchTarget* defaultTarget = new SwitchTarget(emitter.CreateBasicBlock(), node.Statement(), nullptr);
    switchTargets.SetDefault(defaultTarget);
}

SwitchTargets CollectSwitchTargets(otava::symbols::Emitter& emitter, otava::symbols::BoundStatementNode* statement)
{
    SwitchTargetCollector collector(emitter);
    statement->Accept(collector);
    SwitchTargets targets = collector.GetSwitchTargets();
    return targets;
}

class ConstantExpressionEvaluator : public otava::symbols::DefaultBoundTreeVisitor
{
public:
    ConstantExpressionEvaluator(otava::symbols::Emitter& emitter_, const soul::ast::SourcePos& sourcePos_, otava::symbols::Context& context_);
    void Visit(otava::symbols::BoundLiteralNode& node) override;
private:
    otava::symbols::Emitter& emitter;
    soul::ast::SourcePos sourcePos;
    otava::symbols::Context& context;
};

ConstantExpressionEvaluator::ConstantExpressionEvaluator(otava::symbols::Emitter& emitter_, const soul::ast::SourcePos& sourcePos_, otava::symbols::Context& context_) : 
    emitter(emitter_), sourcePos(sourcePos_), context(context_)
{
}

void ConstantExpressionEvaluator::Visit(otava::symbols::BoundLiteralNode& node)
{
    emitter.Stack().Push(node.GetValue()->IrValue(emitter, sourcePos, &context));
}

void EvaluateConstantExpr(otava::symbols::Emitter& emitter, const soul::ast::SourcePos& sourcePos, otava::symbols::Context& context, 
    otava::symbols::BoundExpressionNode* constantExpr)
{
    ConstantExpressionEvaluator evaluator(emitter, sourcePos, context);
    constantExpr->Accept(evaluator);
    if (emitter.Stack().IsEmpty())
    {
        ThrowException("cannot evaluate statically", sourcePos, &context);
    }
}

class CodeGenerator : public otava::symbols::DefaultBoundTreeVisitor
{
public:
    CodeGenerator(otava::symbols::Context& context_, bool verbose_);
    void Visit(otava::symbols::BoundCompileUnitNode& node) override;
    void Visit(otava::symbols::BoundFunctionNode& node) override;
    void Visit(otava::symbols::BoundCompoundStatementNode& node) override;
    void Visit(otava::symbols::BoundIfStatementNode& node) override;
    void Visit(otava::symbols::BoundSwitchStatementNode& node) override;
    void Visit(otava::symbols::BoundCaseStatementNode& node) override;
    void Visit(otava::symbols::BoundDefaultStatementNode& node) override;
    void Visit(otava::symbols::BoundWhileStatementNode& node) override;
    void Visit(otava::symbols::BoundDoStatementNode& node) override;
    void Visit(otava::symbols::BoundForStatementNode& node) override;
    void Visit(otava::symbols::BoundSequenceStatementNode& node) override;
    void Visit(otava::symbols::BoundReturnStatementNode& node) override;
    void Visit(otava::symbols::BoundBreakStatementNode& node) override;
    void Visit(otava::symbols::BoundContinueStatementNode& node) override;
    void Visit(otava::symbols::BoundConstructionStatementNode& node) override;
    void Visit(otava::symbols::BoundExpressionStatementNode& node) override;
    void Visit(otava::symbols::BoundLiteralNode& node) override;
    void Visit(otava::symbols::BoundVariableNode& node) override;
    void Visit(otava::symbols::BoundParameterNode& node) override;
    void Visit(otava::symbols::BoundEnumConstant& node) override;
    void Visit(otava::symbols::BoundMemberExprNode& node) override;
    void Visit(otava::symbols::BoundFunctionCallNode& node) override;
    void Visit(otava::symbols::BoundConversionNode& node) override;
private:
    void StatementPrefix();
    void GenJumpingBoolCode();
    otava::symbols::Context& context;
    bool verbose;
    otava::symbols::Emitter emitter;
    otava::intermediate::BasicBlock* trueBlock;
    otava::intermediate::BasicBlock* falseBlock;
    otava::intermediate::BasicBlock* nextBlock;
    otava::intermediate::BasicBlock* defaultBlock;
    otava::intermediate::BasicBlock* breakBlock;
    otava::intermediate::BasicBlock* continueBlock;
    bool genJumpingBoolCode;
    bool prevWasTerminator;
    otava::symbols::BoundStatementNode* sequenceSecond;
};

CodeGenerator::CodeGenerator(otava::symbols::Context& context_, bool verbose_) : 
    context(context_), verbose(verbose_), trueBlock(nullptr), falseBlock(nullptr), nextBlock(nullptr), defaultBlock(nullptr), breakBlock(nullptr), continueBlock(nullptr), 
    genJumpingBoolCode(false), prevWasTerminator(false), sequenceSecond(nullptr)
{
    std::string config = "debug";
    std::string intermediateCodeFilePath = util::GetFullPath(
        util::Path::Combine(
            util::Path::Combine(util::Path::GetDirectoryName(context.FileName()), config),
            util::Path::GetFileName(context.FileName()) + ".i"));
    emitter.SetFilePath(intermediateCodeFilePath);
    std::filesystem::create_directories(util::Path::GetDirectoryName(intermediateCodeFilePath));
}

void CodeGenerator::StatementPrefix()
{
    if (prevWasTerminator)
    {
        if (!nextBlock)
        {
            nextBlock = emitter.CreateBasicBlock();
        }
    }
    if (nextBlock)
    {
        emitter.SetCurrentBasicBlock(nextBlock);
        nextBlock = nullptr;
    }
}

void CodeGenerator::GenJumpingBoolCode()
{
    if (!genJumpingBoolCode) return;
    otava::intermediate::Value* cond = emitter.Stack().Pop();
    if (sequenceSecond)
    {
        genJumpingBoolCode = false;
        sequenceSecond->SetGenerated();
        sequenceSecond->Accept(*this);
        genJumpingBoolCode = true;
    }
    emitter.EmitBranch(cond, trueBlock, falseBlock);
}

void CodeGenerator::Visit(otava::symbols::BoundCompileUnitNode& node)
{
    emitter.SetCompileUnitInfo(node.Id(), context.FileName());
    int n = node.BoundNodes().size();
    for (int i = 0; i < n; ++i)
    {
        otava::symbols::BoundNode* boundNode = node.BoundNodes()[i].get();
        boundNode->Accept(*this);
    }
    emitter.Emit();
    otava::intermediate::Context intermediateContext;
    otava::intermediate::ParseIntermediateCodeFile(emitter.FilePath(), intermediateContext);
    otava::intermediate::Verify(intermediateContext);
    otava::intermediate::GenerateCode(intermediateContext, verbose);
}

void CodeGenerator::Visit(otava::symbols::BoundFunctionNode& node)
{
    otava::symbols::FunctionDefinitionSymbol* functionDefinition = node.GetFunctionDefinitionSymbol();
    otava::intermediate::Type* functionType = functionDefinition->IrType(emitter, node.GetSourcePos(), &context);
    bool once = false;
    emitter.CreateFunction(functionDefinition->IrName(), functionType, once);
    node.Body()->Accept(*this);
}

void CodeGenerator::Visit(otava::symbols::BoundCompoundStatementNode& node)
{
    StatementPrefix();
    int n = node.Statements().size();
    for (int i = 0; i < n; ++i)
    {
        otava::symbols::BoundStatementNode* statement = node.Statements()[i].get();
        statement->Accept(*this);
        prevWasTerminator = statement->IsTerminator();
    }
}

void CodeGenerator::Visit(otava::symbols::BoundIfStatementNode& node)
{
    StatementPrefix();
    otava::intermediate::BasicBlock* prevTrueBlock = trueBlock;
    otava::intermediate::BasicBlock* prevFalseBlock = falseBlock;
    trueBlock = emitter.CreateBasicBlock();
    nextBlock = emitter.CreateBasicBlock();
    if (node.ElseStatement())
    {
        falseBlock = emitter.CreateBasicBlock();
    }
    else
    {
        falseBlock = nextBlock;
    }
    node.InitStatement()->Accept(*this);
    bool prevGenJumpingBoolCode = genJumpingBoolCode;
    genJumpingBoolCode = true;
    node.GetCondition()->Accept(*this);
    genJumpingBoolCode = prevGenJumpingBoolCode;
    emitter.SetCurrentBasicBlock(trueBlock);
    node.ThenStatement()->Accept(*this);
    emitter.EmitJump(nextBlock);
    if (node.ElseStatement())
    {
        emitter.SetCurrentBasicBlock(falseBlock);
        node.ElseStatement()->Accept(*this);
        emitter.EmitJump(nextBlock);
    }
    trueBlock = prevTrueBlock;
    falseBlock = prevFalseBlock;
}

void CodeGenerator::Visit(otava::symbols::BoundSwitchStatementNode& node)
{
    StatementPrefix();
    node.InitStatement()->Accept(*this);
    node.GetCondition()->Accept(*this);
    otava::intermediate::BasicBlock* prevDefaultBlock = defaultBlock;
    otava::intermediate::BasicBlock* prevBreakBlock = breakBlock;
    otava::intermediate::Value* condition = emitter.Stack().Pop();
    SwitchTargets switchTargets = CollectSwitchTargets(emitter, node.Statement());
    if (switchTargets.Default())
    {
        defaultBlock = switchTargets.Default()->block;
        nextBlock = emitter.CreateBasicBlock();
    }
    else
    {
        nextBlock = emitter.CreateBasicBlock();
        defaultBlock = nextBlock;
    }
    breakBlock = nextBlock;
    otava::intermediate::SwitchInstruction* switchInst = emitter.EmitSwitch(condition, defaultBlock);
    int n = switchTargets.Cases().size();
    for (int i = 0; i < n; ++i)
    {
        const auto& caseTarget = switchTargets.Cases()[i];
        emitter.SetCurrentBasicBlock(caseTarget->block);
        EvaluateConstantExpr(emitter, node.GetSourcePos(), context, caseTarget->expr);
        otava::intermediate::Value* caseValue = emitter.Stack().Pop();
        otava::intermediate::CaseTarget target(caseValue, caseTarget->block->Id());
        switchInst->AddCaseTarget(target);
        caseTarget->statement->Accept(*this);
        if (!caseTarget->statement->EndsWithTerminator())
        {
            if (i < n - 1)
            {
                emitter.EmitJump(switchTargets.Cases()[i + 1]->block);
            }
            else
            {
                emitter.EmitJump(nextBlock);
            }
        }
    }
    if (switchTargets.Default())
    {
        emitter.SetCurrentBasicBlock(defaultBlock);
        switchTargets.Default()->statement->Accept(*this);
        if (!switchTargets.Default()->statement->EndsWithTerminator())
        {
            emitter.EmitJump(nextBlock);
        }
    }
    defaultBlock = prevDefaultBlock;
    breakBlock = prevBreakBlock;
}

void CodeGenerator::Visit(otava::symbols::BoundCaseStatementNode& node)
{
    StatementPrefix();
    node.Statement()->Accept(*this);
}

void CodeGenerator::Visit(otava::symbols::BoundDefaultStatementNode& node)
{
    StatementPrefix();
    node.Statement()->Accept(*this);
}

void CodeGenerator::Visit(otava::symbols::BoundWhileStatementNode& node)
{
    StatementPrefix();
    otava::intermediate::BasicBlock* prevTrueBlock = trueBlock;
    otava::intermediate::BasicBlock* prevFalseBlock = falseBlock;
    otava::intermediate::BasicBlock* prevBreakBlock = breakBlock;
    otava::intermediate::BasicBlock* prevContinueBlock = continueBlock;
    trueBlock = emitter.CreateBasicBlock();
    falseBlock = emitter.CreateBasicBlock();
    breakBlock = falseBlock;
    otava::intermediate::BasicBlock* condBlock = emitter.CreateBasicBlock();
    emitter.EmitJump(condBlock);
    emitter.SetCurrentBasicBlock(condBlock);
    continueBlock = condBlock;
    bool prevGenJumpingBoolCode = genJumpingBoolCode;
    genJumpingBoolCode = true;
    node.GetCondition()->Accept(*this);
    genJumpingBoolCode = prevGenJumpingBoolCode;
    emitter.SetCurrentBasicBlock(trueBlock);
    node.Statement()->Accept(*this);
    emitter.EmitJump(condBlock);
    nextBlock = falseBlock;
    continueBlock = prevContinueBlock;
    breakBlock = prevBreakBlock;
    falseBlock = prevFalseBlock;
    trueBlock = prevTrueBlock;
}

void CodeGenerator::Visit(otava::symbols::BoundDoStatementNode& node)
{
    StatementPrefix();
    otava::intermediate::BasicBlock* prevTrueBlock = trueBlock;
    otava::intermediate::BasicBlock* prevFalseBlock = falseBlock;
    otava::intermediate::BasicBlock* prevBreakBlock = breakBlock;
    otava::intermediate::BasicBlock* prevContinueBlock = continueBlock;
    otava::intermediate::BasicBlock* doBlock = emitter.CreateBasicBlock();
    otava::intermediate::BasicBlock* condBlock = emitter.CreateBasicBlock();
    trueBlock = doBlock;
    falseBlock = emitter.CreateBasicBlock();
    breakBlock = falseBlock;
    continueBlock = condBlock;
    emitter.EmitJump(doBlock);
    emitter.SetCurrentBasicBlock(doBlock);
    node.Statement()->Accept(*this);
    emitter.EmitJump(condBlock);
    emitter.SetCurrentBasicBlock(condBlock);
    bool prevGenJumpingBoolCode = genJumpingBoolCode;
    genJumpingBoolCode = true;
    node.GetExpr()->Accept(*this);
    genJumpingBoolCode = prevGenJumpingBoolCode;
    nextBlock = falseBlock;
    continueBlock = prevContinueBlock;
    breakBlock = prevBreakBlock;
    falseBlock = prevFalseBlock;
    trueBlock = prevTrueBlock;
}

void CodeGenerator::Visit(otava::symbols::BoundForStatementNode& node)
{
    StatementPrefix();
    otava::intermediate::BasicBlock* prevTrueBlock = trueBlock;
    otava::intermediate::BasicBlock* prevFalseBlock = falseBlock;
    otava::intermediate::BasicBlock* prevBreakBlock = breakBlock;
    otava::intermediate::BasicBlock* prevContinueBlock = continueBlock;
    if (node.InitStatement())
    {
        node.InitStatement()->Accept(*this);
    }
    otava::intermediate::BasicBlock* condBlock = emitter.CreateBasicBlock();
    otava::intermediate::BasicBlock* actionBlock = emitter.CreateBasicBlock();
    otava::intermediate::BasicBlock* loopBlock = emitter.CreateBasicBlock();
    trueBlock = actionBlock;
    falseBlock = emitter.CreateBasicBlock();
    breakBlock = falseBlock;
    continueBlock = loopBlock;
    emitter.EmitJump(condBlock);
    emitter.SetCurrentBasicBlock(condBlock);
    bool prevGenJumpingBoolCode = genJumpingBoolCode;
    genJumpingBoolCode = true;
    if (node.GetCondition())
    {
        node.GetCondition()->Accept(*this);
    }
    else
    {
        emitter.EmitBool(true);
        GenJumpingBoolCode();
    }
    genJumpingBoolCode = prevGenJumpingBoolCode;
    emitter.SetCurrentBasicBlock(actionBlock);
    node.Statement()->Accept(*this);
    emitter.EmitJump(loopBlock);
    emitter.SetCurrentBasicBlock(loopBlock);
    if (node.GetLoopExpr())
    {
        node.GetLoopExpr()->Accept(*this);
    }
    emitter.EmitJump(condBlock);
    nextBlock = falseBlock;
    continueBlock = prevContinueBlock;
    breakBlock = prevBreakBlock;
    falseBlock = prevFalseBlock;
    trueBlock = prevTrueBlock;
}

void CodeGenerator::Visit(otava::symbols::BoundSequenceStatementNode& node)
{
    StatementPrefix();
    otava::symbols::BoundStatementNode* prevSequenceSecond = sequenceSecond;
    sequenceSecond = node.Second();
    node.First()->Accept(*this);
    sequenceSecond = prevSequenceSecond;
    if (!node.Second()->Generated())
    {
        node.Second()->Accept(*this);
    }
}

void CodeGenerator::Visit(otava::symbols::BoundReturnStatementNode& node)
{
    StatementPrefix();
    if (node.GetExpr())
    {
        node.GetExpr()->Accept(*this);
        otava::intermediate::Value* returnValue = emitter.Stack().Pop();
        if (sequenceSecond)
        {
            sequenceSecond->SetGenerated();
            sequenceSecond->Accept(*this);
        }
        emitter.EmitRet(returnValue);
    }
    else
    {
        emitter.EmitRetVoid();
    }
}

void CodeGenerator::Visit(otava::symbols::BoundBreakStatementNode& node)
{
    StatementPrefix();
    emitter.EmitJump(breakBlock);
}

void CodeGenerator::Visit(otava::symbols::BoundContinueStatementNode& node)
{
    StatementPrefix();
    emitter.EmitJump(continueBlock);
}

void CodeGenerator::Visit(otava::symbols::BoundConstructionStatementNode& node)
{
    StatementPrefix();
    // todo
}

void CodeGenerator::Visit(otava::symbols::BoundExpressionStatementNode& node)
{
    StatementPrefix();
    node.GetExpr()->Accept(*this);
    if (node.GetExpr()->HasValue())
    {
        emitter.Stack().Pop();
    }
}

void CodeGenerator::Visit(otava::symbols::BoundLiteralNode& node)
{
    node.Load(emitter, otava::symbols::OperationFlags::none, node.GetSourcePos(), &context);
    GenJumpingBoolCode();
}

void CodeGenerator::Visit(otava::symbols::BoundVariableNode& node)
{
    node.Load(emitter, otava::symbols::OperationFlags::none, node.GetSourcePos(), &context);
    GenJumpingBoolCode();
}

void CodeGenerator::Visit(otava::symbols::BoundParameterNode& node)
{
    node.Load(emitter, otava::symbols::OperationFlags::none, node.GetSourcePos(), &context);
    GenJumpingBoolCode();
}

void CodeGenerator::Visit(otava::symbols::BoundEnumConstant& node)
{
    node.Load(emitter, otava::symbols::OperationFlags::none, node.GetSourcePos(), &context);
    GenJumpingBoolCode();
}

void CodeGenerator::Visit(otava::symbols::BoundMemberExprNode& node)
{
    node.Load(emitter, otava::symbols::OperationFlags::none, node.GetSourcePos(), &context);
    GenJumpingBoolCode();
}

void CodeGenerator::Visit(otava::symbols::BoundFunctionCallNode& node)
{
    node.Load(emitter, otava::symbols::OperationFlags::none, node.GetSourcePos(), &context);
    GenJumpingBoolCode();
}

void CodeGenerator::Visit(otava::symbols::BoundConversionNode& node)
{
    node.Load(emitter, otava::symbols::OperationFlags::none, node.GetSourcePos(), &context);
    GenJumpingBoolCode();
}

void GenerateCode(otava::symbols::Context& context, bool verbose)
{
    CodeGenerator codeGenerator(context, verbose);
    context.GetBoundCompileUnit()->Accept(codeGenerator);
}

} // namespace otava::ast