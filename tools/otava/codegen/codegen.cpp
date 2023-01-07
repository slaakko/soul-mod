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
import otava.intermediate.function;
import otava.symbols.type.resolver;
import otava.intermediate.simple.assembly.code.generator;
import otava.assembly;
import otava.symbols.bound.tree;
import otava.symbols.bound.tree.visitor;
import otava.symbols.classes;
import otava.symbols.exception;
import otava.symbols.type.symbol;
import otava.symbols.value;
import otava.symbols.variable.symbol;
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
    std::unique_ptr<SwitchTargets> GetSwitchTargets() { return std::move(switchTargets); }
    void Visit(otava::symbols::BoundCaseStatementNode& node) override;
    void Visit(otava::symbols::BoundDefaultStatementNode& node) override;
private:
    otava::symbols::Emitter& emitter;
    std::unique_ptr<SwitchTargets> switchTargets;
};

SwitchTargetCollector::SwitchTargetCollector(otava::symbols::Emitter& emitter_) : emitter(emitter_), switchTargets(new SwitchTargets())
{
}

void SwitchTargetCollector::Visit(otava::symbols::BoundCaseStatementNode& node)
{
    SwitchTarget* caseTarget = new SwitchTarget(emitter.CreateBasicBlock(), node.Statement(), node.CaseExpr());
    switchTargets->AddCase(caseTarget);
}

void SwitchTargetCollector::Visit(otava::symbols::BoundDefaultStatementNode& node)
{
    SwitchTarget* defaultTarget = new SwitchTarget(emitter.CreateBasicBlock(), node.Statement(), nullptr);
    switchTargets->SetDefault(defaultTarget);
}

std::unique_ptr<SwitchTargets> CollectSwitchTargets(otava::symbols::Emitter& emitter, otava::symbols::BoundStatementNode* statement)
{
    SwitchTargetCollector collector(emitter);
    statement->Accept(collector);
    std::unique_ptr<SwitchTargets> targets = collector.GetSwitchTargets();
    return std::move(targets);
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
    CodeGenerator(otava::symbols::Context& context_, const std::string& config_, bool verbose_, std::string& mainIrName_, int& mainFunctionParams_);
    void Reset();
    const std::string& GetAsmFileName() const { return asmFileName; }
    void Visit(otava::symbols::BoundCompileUnitNode& node) override;
    void Visit(otava::symbols::BoundClassNode& node) override;
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
    void Visit(otava::symbols::BoundSetVPtrStatementNode& node) override;
    void Visit(otava::symbols::BoundLiteralNode& node) override;
    void Visit(otava::symbols::BoundStringLiteralNode& node) override;
    void Visit(otava::symbols::BoundVariableNode& node) override;
    void Visit(otava::symbols::BoundParameterNode& node) override;
    void Visit(otava::symbols::BoundEnumConstant& node) override;
    void Visit(otava::symbols::BoundMemberExprNode& node) override;
    void Visit(otava::symbols::BoundFunctionCallNode& node) override;
    void Visit(otava::symbols::BoundExpressionSequenceNode& node) override;
    void Visit(otava::symbols::BoundConversionNode& node) override;
    void Visit(otava::symbols::BoundAddressOfNode& node) override;
    void Visit(otava::symbols::BoundDereferenceNode& node) override;
    void Visit(otava::symbols::BoundPtrToRefNode& node) override;
    void Visit(otava::symbols::BoundConstructTemporaryNode& node) override;
    void Visit(otava::symbols::BoundConstructExpressionNode& node) override;
    void Visit(otava::symbols::BoundDefaultInitNode& node) override;
    void Visit(otava::symbols::BoundTemporaryNode& node) override;
    void Visit(otava::symbols::BoundConjunctionNode& boundConjunction) override;
    void Visit(otava::symbols::BoundDisjunctionNode& boundDisjunction) override;
    void Visit(otava::symbols::BoundGlobalVariableDefinitionNode& node) override;
private:
    void StatementPrefix();
    void GenJumpingBoolCode();
    void GenerateVTab(otava::symbols::ClassTypeSymbol* cls, const soul::ast::SourcePos& sourcePos);
    otava::symbols::Context& context;
    std::string config;
    bool verbose;
    std::string& mainIrName;
    int& mainFunctionParams;
    otava::symbols::Emitter emitter;
    otava::intermediate::BasicBlock* entryBlock;
    otava::intermediate::BasicBlock* trueBlock;
    otava::intermediate::BasicBlock* falseBlock;
    otava::intermediate::BasicBlock* nextBlock;
    otava::intermediate::BasicBlock* defaultBlock;
    otava::intermediate::BasicBlock* breakBlock;
    otava::intermediate::BasicBlock* continueBlock;
    bool genJumpingBoolCode;
    bool prevWasTerminator;
    otava::symbols::BoundStatementNode* sequenceSecond;
    otava::intermediate::Value* lastLocal;
    std::string asmFileName;
};

CodeGenerator::CodeGenerator(otava::symbols::Context& context_, const std::string& config_, bool verbose_, std::string& mainIrName_, int& mainFunctionParams_) :
    context(context_), config(config_), verbose(verbose_), mainIrName(mainIrName_), mainFunctionParams(mainFunctionParams_),
    entryBlock(nullptr), trueBlock(nullptr), falseBlock(nullptr), nextBlock(nullptr), defaultBlock(nullptr), breakBlock(nullptr), continueBlock(nullptr),
    genJumpingBoolCode(false), prevWasTerminator(false), sequenceSecond(nullptr), lastLocal(nullptr)
{
    std::string intermediateCodeFilePath = util::GetFullPath(
        util::Path::Combine(
            util::Path::Combine(util::Path::GetDirectoryName(context.FileName()), config),
            util::Path::GetFileName(context.FileName()) + ".i"));
    emitter.SetFilePath(intermediateCodeFilePath);
    std::filesystem::create_directories(util::Path::GetDirectoryName(intermediateCodeFilePath));
}

void CodeGenerator::Reset()
{
    entryBlock = nullptr;
    trueBlock = nullptr;
    falseBlock = nullptr;
    nextBlock = nullptr;
    defaultBlock = nullptr;
    breakBlock = nullptr;
    continueBlock = nullptr;
    genJumpingBoolCode = false;
    prevWasTerminator = false;
    sequenceSecond = nullptr;
    lastLocal = nullptr;
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

void CodeGenerator::GenerateVTab(otava::symbols::ClassTypeSymbol* cls, const soul::ast::SourcePos& sourcePos)
{
    if (!cls->IsPolymorphic()) return;
    cls->MakeVTab(&context, sourcePos);
    otava::intermediate::Type* voidPtrIrType = emitter.MakePtrType(emitter.GetVoidType());
    otava::intermediate::Type* arrayType = emitter.MakeArrayType(cls->VTab().size() * 2 + otava::symbols::vtabClassIdElementCount, voidPtrIrType);
    std::vector<otava::intermediate::Value*> elements;
    util::uuid classId = cls->Id();
    uint64_t classIdFirst;
    uint64_t classIdSecond;
    util::UuidToInts(classId, classIdFirst, classIdSecond);
    otava::intermediate::Value* classIdFirstValue = emitter.EmitConversionValue(voidPtrIrType, emitter.EmitULong(classIdFirst));
    elements.push_back(classIdFirstValue);
    otava::intermediate::Value* classIdSecondValue = emitter.EmitConversionValue(voidPtrIrType, emitter.EmitULong(classIdSecond));
    elements.push_back(classIdSecondValue);
    for (otava::symbols::FunctionSymbol* functionSymbol : cls->VTab())
    {
        if (functionSymbol)
        {
            otava::intermediate::Type* irType = functionSymbol->IrType(emitter, sourcePos, &context);
            if (irType->IsFunctionType())
            {
                if (functionSymbol->IsPure())
                {
                    otava::intermediate::Value* functionValue = emitter.EmitNull(voidPtrIrType);
                    otava::intermediate::Value* deltaValue = emitter.EmitLong(0);
                    otava::intermediate::Value* element1Value = emitter.EmitConversionValue(voidPtrIrType, functionValue);
                    elements.push_back(element1Value);
                    otava::intermediate::Value* element2Value = emitter.EmitConversionValue(voidPtrIrType, deltaValue);
                    elements.push_back(element2Value);
                }
                else
                {
                    otava::intermediate::FunctionType* functionType = static_cast<otava::intermediate::FunctionType*>(irType);
                    emitter.GetOrInsertFunction(functionSymbol->IrName(&context), functionType);
                    otava::intermediate::Value* functionValue = emitter.EmitSymbolValue(functionType, "@" + functionSymbol->IrName(&context));
                    otava::intermediate::Value* deltaValue = emitter.EmitLong(0);
                    otava::intermediate::Value* element1Value = emitter.EmitConversionValue(voidPtrIrType, functionValue);
                    elements.push_back(element1Value);
                    otava::intermediate::Value* element2Value = emitter.EmitConversionValue(voidPtrIrType, deltaValue);
                    elements.push_back(element2Value);
                }
            }
            else
            {
                ThrowException("function type expected", sourcePos, &context);
            }
        }
        else
        {
            otava::intermediate::Value* element1Value = emitter.EmitNull(voidPtrIrType);
            elements.push_back(element1Value);
            otava::intermediate::Value* deltaValue = emitter.EmitLong(0);
            otava::intermediate::Value* element2Value = emitter.EmitConversionValue(voidPtrIrType, deltaValue);
            elements.push_back(element2Value);
        }
    }
    otava::intermediate::Value* arrayValue = emitter.EmitArrayValue(elements);
    std::string vtabName = cls->VTabName(&context);
    otava::intermediate::Value* vtabVariable = emitter.EmitGlobalVariable(arrayType, vtabName, arrayValue);
    emitter.SetVTabVariable(cls, vtabVariable);
}

void CodeGenerator::Visit(otava::symbols::BoundCompileUnitNode& node)
{
    node.Sort();
    emitter.SetCompileUnitInfo(node.Id(), context.FileName());
    int n = node.BoundNodes().size();
    for (int i = 0; i < n; ++i)
    {
        otava::symbols::BoundNode* boundNode = node.BoundNodes()[i].get();
        Reset();
        boundNode->Accept(*this);
    }
    emitter.ResolveReferences();
    emitter.Emit();
    otava::intermediate::Context intermediateContext;
    otava::intermediate::ParseIntermediateCodeFile(emitter.FilePath(), intermediateContext);
    otava::intermediate::Verify(intermediateContext);
    std::string assemblyFilePath = util::GetFullPath(
        util::Path::Combine(
            util::Path::Combine(util::Path::GetDirectoryName(context.FileName()), config),
            util::Path::GetFileName(context.FileName()) + ".asm"));
    otava::intermediate::SimpleAssemblyCodeGenerator assemblyCodeGenerator(&intermediateContext, assemblyFilePath);
    otava::intermediate::GenerateCode(intermediateContext, assemblyCodeGenerator, verbose);
    asmFileName = util::Path::GetFileName(context.FileName()) + ".asm";
}

void CodeGenerator::Visit(otava::symbols::BoundClassNode& node)
{
    otava::symbols::ClassTypeSymbol* cls = node.GetClass();
    GenerateVTab(cls, node.GetSourcePos());
}

void CodeGenerator::Visit(otava::symbols::BoundFunctionNode& node)
{
    otava::symbols::FunctionDefinitionSymbol* functionDefinition = node.GetFunctionDefinitionSymbol();
    if ((functionDefinition->Qualifiers() & otava::symbols::FunctionQualifiers::isDeleted) != otava::symbols::FunctionQualifiers::none)
    {
        return;
    }
    if (functionDefinition->Name() == U"main")
    {
        mainIrName = functionDefinition->IrName(&context);
        mainFunctionParams = functionDefinition->Arity();
    }
    otava::intermediate::Type* functionType = functionDefinition->IrType(emitter, node.GetSourcePos(), &context);
    bool once = false;
    emitter.CreateFunction(functionDefinition->IrName(&context), functionType, once);
    entryBlock = emitter.CreateBasicBlock();
    emitter.SetCurrentBasicBlock(entryBlock);
    int np = functionDefinition->MemFunParameters(&context).size();
    for (int i = 0; i < np; ++i)
    {
        otava::symbols::ParameterSymbol* parameter = functionDefinition->MemFunParameters(&context)[i];
        otava::intermediate::Value* local = emitter.EmitLocal(parameter->GetReferredType(&context)->IrType(emitter, node.GetSourcePos(), &context));
        emitter.SetIrObject(parameter, local);
        lastLocal = local;
    }
    if (functionDefinition->ReturnsClass())
    {
        otava::symbols::ParameterSymbol* parameter = functionDefinition->ReturnValueParam();
        otava::intermediate::Value* local = emitter.EmitLocal(parameter->GetReferredType(&context)->IrType(emitter, node.GetSourcePos(), &context));
        emitter.SetIrObject(parameter, local);
        lastLocal = local;
    }
    int nlv = functionDefinition->LocalVariables().size();
    for (int i = 0; i < nlv; ++i)
    {
        otava::symbols::VariableSymbol* localVariable = functionDefinition->LocalVariables()[i];
        otava::intermediate::Value* local = emitter.EmitLocal(localVariable->GetReferredType()->IrType(emitter, node.GetSourcePos(), &context));
        emitter.SetIrObject(localVariable, local);
        lastLocal = local;
    }
    for (int i = 0; i < np; ++i)
    {
        otava::intermediate::Value* param = emitter.GetParam(i);
        otava::symbols::ParameterSymbol* parameter = functionDefinition->MemFunParameters(&context)[i];
        emitter.EmitStore(param, static_cast<otava::intermediate::Value*>(parameter->IrObject(emitter, node.GetSourcePos(), &context)));
    }
    if (functionDefinition->ReturnsClass())
    {
        otava::intermediate::Value* param = emitter.GetParam(np);
        otava::symbols::ParameterSymbol* parameter = functionDefinition->ReturnValueParam();
        emitter.EmitStore(param, static_cast<otava::intermediate::Value*>(parameter->IrObject(emitter, node.GetSourcePos(), &context)));
    }
    otava::symbols::BoundCtorInitializerNode* ctorInitializer = node.CtorInitializer();
    if (ctorInitializer)
    {
        ctorInitializer->GenerateCode(*this, emitter, &context);
    }
    otava::symbols::BoundDtorTerminatorNode* dtorTerminator = node.DtorTerminator();
    if (dtorTerminator)
    {
        otava::symbols::BoundStatementNode* setVPtrStatement = dtorTerminator->GetSetVPtrStatement();
        if (setVPtrStatement)
        {
            setVPtrStatement->Accept(*this);
        }
    }
    node.Body()->Accept(*this);
    if (dtorTerminator)
    {
        dtorTerminator->GenerateCode(*this, emitter, &context);
    }
    StatementPrefix();
    otava::symbols::BoundStatementNode* lastStatement = nullptr;
    if (!node.Body()->Statements().empty())
    {
        lastStatement = node.Body()->Statements().back().get();
    }
    if (!lastStatement || !lastStatement->IsReturnStatementNode())
    {
        if (functionDefinition->ReturnType() && !functionDefinition->ReturnType()->IsVoidType() && !functionDefinition->ReturnsClass())
        {
            otava::intermediate::Value* returnValue = functionDefinition->ReturnType()->DirectType(&context)->IrType(emitter, node.GetSourcePos(), &context)->DefaultValue();
            emitter.EmitRet(returnValue);
        }
        else
        {
            emitter.EmitRetVoid();
        }
    }
    emitter.SetRegNumbers();
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
    if (node.InitStatement())
    {
        node.InitStatement()->Accept(*this);
    }
    bool prevGenJumpingBoolCode = genJumpingBoolCode;
    genJumpingBoolCode = true;
    node.GetCondition()->Accept(*this);
    genJumpingBoolCode = prevGenJumpingBoolCode;
    emitter.SetCurrentBasicBlock(trueBlock);
    otava::intermediate::BasicBlock* prevNextBlock = nextBlock;
    nextBlock = nullptr;
    node.ThenStatement()->Accept(*this);
    nextBlock = prevNextBlock;
    if (!node.ThenStatement()->EndsWithTerminator())
    {
        emitter.EmitJump(nextBlock);
    }
    if (node.ElseStatement())
    {
        emitter.SetCurrentBasicBlock(falseBlock);
        otava::intermediate::BasicBlock* prevNextBlock = nextBlock;
        nextBlock = nullptr;
        node.ElseStatement()->Accept(*this);
        nextBlock = prevNextBlock;
        if (!node.ElseStatement()->EndsWithTerminator())
        {
            emitter.EmitJump(nextBlock);
        }
    }
    else
    {
        emitter.SetCurrentBasicBlock(nextBlock);
    }
    trueBlock = prevTrueBlock;
    falseBlock = prevFalseBlock;
}

void CodeGenerator::Visit(otava::symbols::BoundSwitchStatementNode& node)
{
    StatementPrefix();
    if (node.InitStatement())
    {
        node.InitStatement()->Accept(*this);
    }
    node.GetCondition()->Accept(*this);
    otava::intermediate::BasicBlock* prevDefaultBlock = defaultBlock;
    otava::intermediate::BasicBlock* prevBreakBlock = breakBlock;
    otava::intermediate::Value* condition = emitter.Stack().Pop();
    std::unique_ptr<SwitchTargets> switchTargets = CollectSwitchTargets(emitter, node.Statement());
    if (switchTargets->Default())
    {
        defaultBlock = switchTargets->Default()->block;
        nextBlock = emitter.CreateBasicBlock();
    }
    else
    {
        nextBlock = emitter.CreateBasicBlock();
        defaultBlock = nextBlock;
    }
    breakBlock = nextBlock;
    otava::intermediate::SwitchInstruction* switchInst = emitter.EmitSwitch(condition, defaultBlock);
    int n = switchTargets->Cases().size();
    for (int i = 0; i < n; ++i)
    {
        const auto& caseTarget = switchTargets->Cases()[i];
        emitter.SetCurrentBasicBlock(caseTarget->block);
        EvaluateConstantExpr(emitter, node.GetSourcePos(), context, caseTarget->expr);
        otava::intermediate::Value* caseValue = emitter.Stack().Pop();
        otava::intermediate::CaseTarget target(caseValue, caseTarget->block->Id());
        switchInst->AddCaseTarget(target);
        otava::intermediate::BasicBlock* prevNextBlock = nextBlock;
        nextBlock = nullptr;
        prevWasTerminator = false;
        caseTarget->statement->Accept(*this);
        nextBlock = prevNextBlock;
        if (!caseTarget->statement->EndsWithTerminator())
        {
            if (i < n - 1)
            {
                emitter.EmitJump(switchTargets->Cases()[i + 1]->block);
            }
            else
            {
                emitter.EmitJump(nextBlock);
            }
        }
    }
    if (switchTargets->Default())
    {
        emitter.SetCurrentBasicBlock(defaultBlock);
        otava::intermediate::BasicBlock* prevNextBlock = nextBlock;
        nextBlock = nullptr;
        prevWasTerminator = false;
        switchTargets->Default()->statement->Accept(*this);
        nextBlock = prevNextBlock;
        if (!switchTargets->Default()->statement->EndsWithTerminator())
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
    emitter.SetCurrentBasicBlock(falseBlock);
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
    node.ConstructorCall()->Accept(*this);
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

void CodeGenerator::Visit(otava::symbols::BoundSetVPtrStatementNode& node)
{
    StatementPrefix();
    node.ThisPtr()->Load(emitter, otava::symbols::OperationFlags::none, node.GetSourcePos(), &context);
    otava::intermediate::Value* thisPtr = emitter.Stack().Pop();
    otava::symbols::TypeSymbol* thisPtrType = node.ThisPtr()->GetType()->GetBaseType();
    if (thisPtrType->IsClassTypeSymbol())
    {
        otava::symbols::ClassTypeSymbol* classType = static_cast<otava::symbols::ClassTypeSymbol*>(thisPtrType);
        int32_t vptrIndex = classType->VPtrIndex();
        otava::symbols::ClassTypeSymbol* forClass = node.GetClass();
        otava::intermediate::Value* ptr = emitter.EmitElemAddr(thisPtr, emitter.EmitLong(vptrIndex));
        otava::intermediate::Value* vptr = emitter.EmitBitcast(forClass->GetVTabVariable(emitter, &context), emitter.MakePtrType(emitter.GetVoidType()));
        emitter.EmitStore(vptr, ptr);
    }
}

void CodeGenerator::Visit(otava::symbols::BoundLiteralNode& node)
{
    node.Load(emitter, otava::symbols::OperationFlags::none, node.GetSourcePos(), &context);
    GenJumpingBoolCode();
}

void CodeGenerator::Visit(otava::symbols::BoundStringLiteralNode& node)
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

void CodeGenerator::Visit(otava::symbols::BoundExpressionSequenceNode& node)
{
    node.Load(emitter, otava::symbols::OperationFlags::none, node.GetSourcePos(), &context);
    GenJumpingBoolCode();
}

void CodeGenerator::Visit(otava::symbols::BoundConversionNode& node)
{
    node.Load(emitter, otava::symbols::OperationFlags::none, node.GetSourcePos(), &context);
    GenJumpingBoolCode();
}

void CodeGenerator::Visit(otava::symbols::BoundAddressOfNode& node)
{
    node.Load(emitter, otava::symbols::OperationFlags::none, node.GetSourcePos(), &context);
    GenJumpingBoolCode();
}

void CodeGenerator::Visit(otava::symbols::BoundDereferenceNode& node)
{
    node.Load(emitter, otava::symbols::OperationFlags::none, node.GetSourcePos(), &context);
    GenJumpingBoolCode();
}

void CodeGenerator::Visit(otava::symbols::BoundPtrToRefNode& node)
{
    node.Load(emitter, otava::symbols::OperationFlags::none, node.GetSourcePos(), &context);
    GenJumpingBoolCode();
}

void CodeGenerator::Visit(otava::symbols::BoundConstructTemporaryNode& node)
{
    node.Load(emitter, otava::symbols::OperationFlags::none, node.GetSourcePos(), &context);
    GenJumpingBoolCode();
}

void CodeGenerator::Visit(otava::symbols::BoundConstructExpressionNode& node)
{
    node.Load(emitter, otava::symbols::OperationFlags::none, node.GetSourcePos(), &context);
    GenJumpingBoolCode();
}

void CodeGenerator::Visit(otava::symbols::BoundDefaultInitNode& node)
{
    node.Load(emitter, otava::symbols::OperationFlags::none, node.GetSourcePos(), &context);
    GenJumpingBoolCode();
}

void CodeGenerator::Visit(otava::symbols::BoundTemporaryNode& node)
{
    node.Load(emitter, otava::symbols::OperationFlags::none, node.GetSourcePos(), &context);
    GenJumpingBoolCode();
}

void CodeGenerator::Visit(otava::symbols::BoundConjunctionNode& boundConjunction)
{
    if (genJumpingBoolCode)
    {
        otava::intermediate::BasicBlock* rightBlock = emitter.CreateBasicBlock();
        otava::intermediate::BasicBlock* prevTrueBlock = trueBlock;
        trueBlock = rightBlock;
        boundConjunction.Left()->Accept(*this);
        trueBlock = prevTrueBlock;
        emitter.SetCurrentBasicBlock(rightBlock);
        boundConjunction.Right()->Accept(*this);
    }
}

void CodeGenerator::Visit(otava::symbols::BoundDisjunctionNode& boundDisjunction)
{
    if (genJumpingBoolCode)
    {
        otava::intermediate::BasicBlock* rightBlock = emitter.CreateBasicBlock();
        otava::intermediate::BasicBlock* prevFalseBlock = falseBlock;
        falseBlock = rightBlock;
        boundDisjunction.Left()->Accept(*this);
        emitter.SetCurrentBasicBlock(rightBlock);
        falseBlock = prevFalseBlock;
        boundDisjunction.Right()->Accept(*this);
    }
}

void CodeGenerator::Visit(otava::symbols::BoundGlobalVariableDefinitionNode& node)
{
    otava::symbols::VariableSymbol* variable = node.GetGlobalVariable();
    otava::symbols::TypeSymbol* type = otava::symbols::ResolveFwdDeclaredType(variable->GetType(), node.GetSourcePos(), &context);
    if (type->IsForwardClassDeclarationSymbol()) return;
    variable->SetDeclaredType(type);
    otava::intermediate::Value* initializer = nullptr;
    otava::intermediate::Type* irType = variable->GetType()->IrType(emitter, node.GetSourcePos(), &context);
    if (variable->GetValue())
    {
        initializer = variable->GetValue()->IrValue(emitter, node.GetSourcePos(), &context);
    }
    else
    {
        initializer = irType->DefaultValue();
    }
    otava::intermediate::Value* irVariable = emitter.EmitGlobalVariable(irType, variable->IrName(), initializer);
    emitter.SetIrObject(variable, irVariable);
}

std::string GenerateCode(otava::symbols::Context& context, const std::string& config, bool verbose, std::string& mainIrName, int& mainFunctionParams)
{
    CodeGenerator codeGenerator(context, config, verbose, mainIrName, mainFunctionParams);
    context.GetBoundCompileUnit()->Accept(codeGenerator);
    return codeGenerator.GetAsmFileName();
}

} // namespace otava::codegen
