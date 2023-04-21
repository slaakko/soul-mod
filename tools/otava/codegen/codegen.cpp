// =================================
// Copyright (c) 2023 Seppo Laakko
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
import otava.symbols.class_templates;
import otava.intermediate.simple.assembly.code.generator;
import otava.assembly;
import otava.symbols.bound.tree;
import otava.symbols.bound.tree.visitor;
import otava.symbols.classes;
import otava.symbols.exception;
import otava.symbols.type.symbol;
import otava.symbols.value;
import otava.symbols.variable.symbol;
import otava.symbols.modules;
import otava.symbols.overload.resolution;
import otava.symbols.symbol.table;
import otava.symbols.enums;
import std.core;
import std.filesystem;
import util;

namespace otava::codegen {

struct SwitchTarget
{
    SwitchTarget(otava::intermediate::BasicBlock* block_, otava::symbols::BoundStatementNode* statement_, const std::vector<otava::symbols::BoundExpressionNode*> exprs_);
    otava::intermediate::BasicBlock* block;
    otava::symbols::BoundStatementNode* statement;
    std::vector<otava::symbols::BoundExpressionNode*> exprs;
};

SwitchTarget::SwitchTarget(otava::intermediate::BasicBlock* block_, otava::symbols::BoundStatementNode* statement_, const std::vector<otava::symbols::BoundExpressionNode*> exprs_) :
    block(block_), statement(statement_), exprs(exprs_)
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
    std::vector<otava::symbols::BoundExpressionNode*> caseExprs;
    for (const auto& caseExpr : node.CaseExprs())
    {
        caseExprs.push_back(caseExpr.get());
    }
    SwitchTarget* caseTarget = new SwitchTarget(emitter.CreateBasicBlock(), node.Statement(), caseExprs);
    switchTargets->AddCase(caseTarget);
}

void SwitchTargetCollector::Visit(otava::symbols::BoundDefaultStatementNode& node)
{
    SwitchTarget* defaultTarget = new SwitchTarget(emitter.CreateBasicBlock(), node.Statement(), std::vector<otava::symbols::BoundExpressionNode*>());
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
    void Visit(otava::symbols::BoundEnumConstant& node) override;
    void Visit(otava::symbols::BoundVariableNode& node) override;
    void Visit(otava::symbols::BoundConversionNode& node) override;
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

void ConstantExpressionEvaluator::Visit(otava::symbols::BoundEnumConstant& node)
{
    emitter.Stack().Push(node.EnumConstant()->GetValue()->IrValue(emitter, sourcePos, &context));
}

void ConstantExpressionEvaluator::Visit(otava::symbols::BoundVariableNode& node)
{
    otava::symbols::VariableSymbol* variable = node.GetVariable();
    otava::symbols::Value* value = variable->GetValue();
    if (!value)
    {
        ThrowException("cannot evaluate statically", sourcePos, &context);
    }
    otava::intermediate::Value* irValue = value->IrValue(emitter, sourcePos, &context);
    emitter.Stack().Push(irValue);
}

void ConstantExpressionEvaluator::Visit(otava::symbols::BoundConversionNode& node)
{
    node.Subject()->Accept(*this);
    otava::intermediate::Value* value = emitter.Stack().Pop();
    if (value->IsIntegerValue())
    {
        int64_t val = value->GetIntegerValue();
        otava::intermediate::Type* type = node.GetType()->IrType(emitter, sourcePos, &context);
        if (type->IsIntegerType())
        {
            switch (type->Id())
            {
                case otava::intermediate::sbyteTypeId:
                {
                    value = emitter.GetIntermediateContext()->GetSByteValue(static_cast<int8_t>(val));
                    break;
                }
                case otava::intermediate::byteTypeId:
                {
                    value = emitter.GetIntermediateContext()->GetByteValue(static_cast<uint8_t>(val));
                    break;
                }
                case otava::intermediate::shortTypeId:
                {
                    value = emitter.GetIntermediateContext()->GetShortValue(static_cast<int16_t>(val));
                    break;
                }
                case otava::intermediate::ushortTypeId:
                {
                    value = emitter.GetIntermediateContext()->GetUShortValue(static_cast<uint16_t>(val));
                    break;
                }
                case otava::intermediate::intTypeId:
                {
                    value = emitter.GetIntermediateContext()->GetIntValue(static_cast<int32_t>(val));
                    break;
                }
                case otava::intermediate::uintTypeId:
                {
                    value = emitter.GetIntermediateContext()->GetUIntValue(static_cast<uint32_t>(val));
                    break;
                }
                case otava::intermediate::longTypeId:
                {
                    value = emitter.GetIntermediateContext()->GetLongValue(static_cast<int64_t>(val));
                    break;
                }
                case otava::intermediate::ulongTypeId:
                {
                    value = emitter.GetIntermediateContext()->GetULongValue(static_cast<uint64_t>(val));
                    break;
                }
                default:
                {
                    ThrowException("cannot evaluate statically", sourcePos, &context);
                }
            }
            emitter.Stack().Push(value);
        }
        else
        {
            ThrowException("cannot evaluate statically", sourcePos, &context);
        }
    }
    else
    {
        ThrowException("cannot evaluate statically", sourcePos, &context);
    }
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

class BlockExit
{
public:
    BlockExit();
    bool IsEmpty() const { return destructorCalls.empty(); }
    int Size() const { return destructorCalls.size(); }
    void AddDestructorCall(otava::symbols::BoundFunctionCallNode* destructorCall);
    void Execute(otava::symbols::Emitter& emitter, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context, bool reset);
private:
    std::vector<std::unique_ptr<otava::symbols::BoundFunctionCallNode>> destructorCalls;
};

BlockExit::BlockExit()
{
}

void BlockExit::AddDestructorCall(otava::symbols::BoundFunctionCallNode* destructorCall)
{
    destructorCalls.push_back(std::unique_ptr<otava::symbols::BoundFunctionCallNode>(destructorCall));
}

void BlockExit::Execute(otava::symbols::Emitter& emitter, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context, bool reset)
{
    int n = destructorCalls.size();
    for (int i = n - 1; i >= 0; --i)
    {
        otava::symbols::BoundFunctionCallNode* destructorCall = destructorCalls[i].get();
        destructorCall->Load(emitter, otava::symbols::OperationFlags::none, sourcePos, context);
    }
    if (n > 0)
    {
        emitter.GetCleanupList().Remove(n);
        emitter.GetCleanupList().GeneratePopContext(emitter, reset);
    }
}

class CodeGenerator : public otava::symbols::DefaultBoundTreeVisitor, public otava::symbols::CodeGenerator
{
public:
    CodeGenerator(otava::symbols::Context& context_, const std::string& config_, bool verbose_, std::string& mainIrName_, int& mainFunctionParams_, bool globalMain,
        const std::vector<std::string>& compileUnitInitFnNames_);
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
    void Visit(otava::symbols::BoundTryStatementNode& node) override;
    void Visit(otava::symbols::BoundHandlerNode& node) override;
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
    void Visit(otava::symbols::BoundThrowExpressionNode& node) override;
    void Visit(otava::symbols::BoundDefaultInitNode& node) override;
    void Visit(otava::symbols::BoundTemporaryNode& node) override;
    void Visit(otava::symbols::BoundConjunctionNode& boundConjunction) override;
    void Visit(otava::symbols::BoundDisjunctionNode& boundDisjunction) override;
    void Visit(otava::symbols::BoundGlobalVariableDefinitionNode& node) override;
    void SetNextBlock(otava::intermediate::BasicBlock* nextBlock_) override;
private:
    void StatementPrefix();
    void GenJumpingBoolCode();
    void GenerateVTab(otava::symbols::ClassTypeSymbol* cls, const soul::ast::SourcePos& sourcePos);
    void EmitReturn(const soul::ast::SourcePos& sourcePos);
    void ExitBlocks(int sourceBlockId, int targetBlockId, const soul::ast::SourcePos& sourcePos);
    void GenerateGlobalInitializationFunction();
    otava::symbols::Context& context;
    std::string config;
    bool verbose;
    std::string& mainIrName;
    int& mainFunctionParams;
    otava::symbols::Emitter emitter;
    otava::symbols::FunctionDefinitionSymbol* functionDefinition;
    otava::intermediate::BasicBlock* entryBlock;
    otava::intermediate::BasicBlock* trueBlock;
    otava::intermediate::BasicBlock* falseBlock;
    otava::intermediate::BasicBlock* nextBlock;
    otava::intermediate::BasicBlock* defaultBlock;
    otava::intermediate::BasicBlock* breakBlock;
    otava::intermediate::BasicBlock* continueAfterTryBlock;
    int breakBlockId;
    otava::intermediate::BasicBlock* continueBlock;
    int continueBlockId;
    int currentBlockId;
    std::vector<std::unique_ptr<BlockExit>> blockExits;
    bool genJumpingBoolCode;
    bool prevWasTerminator;
    otava::symbols::BoundStatementNode* sequenceSecond;
    std::string asmFileName;
    bool globalMain;
    std::vector<std::string> compileUnitInitFnNames;
    bool elseEndsWithTerminator;
};

CodeGenerator::CodeGenerator(otava::symbols::Context& context_, const std::string& config_, bool verbose_, std::string& mainIrName_, int& mainFunctionParams_, bool globalMain_,
    const std::vector<std::string>& compileUnitInitFnNames_) :
    context(context_), emitter(this), config(config_), verbose(verbose_), mainIrName(mainIrName_), mainFunctionParams(mainFunctionParams_),
    functionDefinition(nullptr), entryBlock(nullptr), trueBlock(nullptr), falseBlock(nullptr), nextBlock(nullptr), defaultBlock(nullptr), 
    breakBlock(nullptr), breakBlockId(-1), continueBlock(nullptr), continueBlockId(-1), continueAfterTryBlock(nullptr), genJumpingBoolCode(false), prevWasTerminator(false),
    sequenceSecond(nullptr), currentBlockId(-1), globalMain(globalMain_), compileUnitInitFnNames(compileUnitInitFnNames_), elseEndsWithTerminator(false)
{
    std::string intermediateCodeFilePath = util::GetFullPath(
        util::Path::Combine(
            util::Path::Combine(util::Path::GetDirectoryName(context.FileName()), config),
            util::Path::GetFileName(context.FileName()) + ".i"));
    emitter.SetFilePath(intermediateCodeFilePath);
    std::filesystem::create_directories(util::Path::GetDirectoryName(intermediateCodeFilePath));
}

void CodeGenerator::SetNextBlock(otava::intermediate::BasicBlock* nextBlock_) 
{
    nextBlock = nextBlock_;
    emitter.SetNextBlock(nextBlock);
}

void CodeGenerator::Reset()
{
    functionDefinition = nullptr;
    entryBlock = nullptr;
    trueBlock = nullptr;
    falseBlock = nullptr;
    nextBlock = nullptr;
    defaultBlock = nullptr;
    breakBlock = nullptr;
    breakBlockId = -1;
    continueBlock = nullptr;
    continueBlockId = -1;
    genJumpingBoolCode = false;
    prevWasTerminator = false;
    sequenceSecond = nullptr;
    currentBlockId = -1;
    blockExits.clear();
    emitter.GetCleanupList().Clear();
    emitter.SetNextBlock(nullptr);
    emitter.SetRetValue(nullptr);
}

void CodeGenerator::StatementPrefix()
{
    if (prevWasTerminator)
    {
        if (!nextBlock)
        {
            nextBlock = emitter.CreateBasicBlock();
            emitter.SetNextBlock(nextBlock);
        }
    }
    if (nextBlock)
    {
        emitter.SetCurrentBasicBlock(nextBlock);
        emitter.SetNextBlock(nullptr);
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
    if (cls->VTabInitialized()) return;
    context.SetFlag(otava::symbols::ContextFlags::generatingVTab);
    cls->SetVTabInitialized();
    cls->ComputeVTabName(&context);
    cls->MakeVTab(&context, sourcePos);
    otava::intermediate::Type* voidPtrIrType = emitter.MakePtrType(emitter.GetVoidType());
    otava::intermediate::Type* arrayType = emitter.MakeArrayType(cls->VTab().size() * 2 + otava::symbols::vtabClassIdElementCount, voidPtrIrType);
    otava::intermediate::Type* arrayPtrType = emitter.MakePtrType(arrayType);
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
    context.ResetFlag(otava::symbols::ContextFlags::generatingVTab);
    for (const auto& boundVTabFunction : context.BoundVTabFunctions())
    {
        boundVTabFunction->Accept(*this);
    }
    context.ClearBoundVTabFunctions();
}

void CodeGenerator::ExitBlocks(int sourceBlockId, int targetBlockId, const soul::ast::SourcePos& sourcePos)
{
    if (targetBlockId == -1)
    {
        for (int i = sourceBlockId; i >= 0; --i)
        {
            if (i >= 0 && i < blockExits.size())
            {
                BlockExit* exit = blockExits[i].get();
                if (exit)
                {
                    exit->Execute(emitter, sourcePos, &context, false);
                }
            }
        }
    }
    else
    {
        for (int i = sourceBlockId; i >= targetBlockId; --i)
        {
            if (i >= 0 && i < blockExits.size())
            {
                BlockExit* exit = blockExits[i].get();
                if (exit)
                {
                    exit->Execute(emitter, sourcePos, &context, true);
                }
            }
        }
    }
}

void CodeGenerator::EmitReturn(const soul::ast::SourcePos& sourcePos)
{
    if (functionDefinition->ReturnType() && !functionDefinition->ReturnType()->IsVoidType() && !functionDefinition->ReturnsClass())
    {
        otava::intermediate::Value* returnValue = functionDefinition->ReturnType()->DirectType(&context)->FinalType(sourcePos, &context)->IrType(
            emitter, sourcePos, &context)->DefaultValue();
        emitter.EmitRet(returnValue);
    }
    else
    {
        emitter.EmitRetVoid();
    }
}

void CodeGenerator::GenerateGlobalInitializationFunction()
{
    Reset();
    emitter.CreateFunction("__global_init__", emitter.MakeFunctionType(emitter.GetVoidType(), std::vector<otava::intermediate::Type*>()), false);
    otava::intermediate::BasicBlock* initBlock = emitter.CreateBasicBlock();
    emitter.SetCurrentBasicBlock(initBlock);
    otava::intermediate::FunctionType* initFunctionType = static_cast<otava::intermediate::FunctionType*>(emitter.MakeFunctionType(emitter.GetVoidType(),
        std::vector<otava::intermediate::Type*>()));
    int n = compileUnitInitFnNames.size();
    for (int i = 0; i < n; ++i)
    {
        otava::intermediate::Function* initFn = emitter.GetOrInsertFunction(compileUnitInitFnNames[i], initFunctionType);
        emitter.EmitCall(initFn, std::vector<otava::intermediate::Value*>());
    }
    emitter.EmitRetVoid();
}

void CodeGenerator::Visit(otava::symbols::BoundCompileUnitNode& node)
{
    context.PushSetFlag(otava::symbols::ContextFlags::requireForwardResolved);
    if (globalMain)
    {
        GenerateGlobalInitializationFunction();
    }
    node.Sort();
    emitter.SetCompileUnitInfo(node.Id(), context.FileName());
    int n = node.BoundNodes().size();
    for (int i = 0; i < n; ++i)
    {
        otava::symbols::BoundNode* boundNode = node.BoundNodes()[i].get();
        Reset();
        boundNode->Accept(*this);
    }
    otava::symbols::BoundFunctionNode* initFunction = node.GetCompileUnitInitializationFunction();
    if (initFunction)
    {
        Reset();
        initFunction->Accept(*this);
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
    context.PopFlags();
}

void CodeGenerator::Visit(otava::symbols::BoundClassNode& node)
{
    otava::symbols::ClassTypeSymbol* cls = node.GetClass();
    if (cls->IsClassTemplateSpecializationSymbol())
    {
        if (cls->Name() == U"basic_ostream<char>")
        {
            otava::symbols::ClassTemplateSpecializationSymbol* sp = static_cast<otava::symbols::ClassTemplateSpecializationSymbol*>(cls);
            if (sp->TemplateArguments().size() == 1)
            {
                if (sp->TemplateArguments()[0]->Name() == U"char")
                {
                    int x = 0;
                }
            }
        }
    }
    GenerateVTab(cls, node.GetSourcePos());
}

void CodeGenerator::Visit(otava::symbols::BoundFunctionNode& node)
{
    functionDefinition = node.GetFunctionDefinitionSymbol();
    otava::intermediate::Value* retValue = nullptr;
    if (functionDefinition->ReturnType() && !functionDefinition->ReturnType()->IsVoidType() && !functionDefinition->ReturnsClass())
    {
        retValue = functionDefinition->ReturnType()->DirectType(&context)->FinalType(node.GetSourcePos(), &context)->IrType(emitter, node.GetSourcePos(), &context)->DefaultValue();
    }
    emitter.SetRetValue(retValue);
    if ((functionDefinition->Qualifiers() & otava::symbols::FunctionQualifiers::isDeleted) != otava::symbols::FunctionQualifiers::none)
    {
        return;
    }
    if (functionDefinition->Name() == U"main")
    {
        mainIrName = functionDefinition->IrName(&context);
        mainFunctionParams = functionDefinition->Arity();
    }
    std::string functionDefinitionName = functionDefinition->IrName(&context);
    otava::intermediate::Type* functionType = functionDefinition->IrType(emitter, node.GetSourcePos(), &context);
    bool once = false;
    emitter.CreateFunction(functionDefinition->IrName(&context), functionType, once);
    entryBlock = emitter.CreateBasicBlock();
    emitter.SetCurrentBasicBlock(entryBlock);
    int np = functionDefinition->MemFunParameters(&context).size();
    for (int i = 0; i < np; ++i)
    {
        otava::symbols::ParameterSymbol* parameter = functionDefinition->MemFunParameters(&context)[i];
        otava::symbols::TypeSymbol* type = parameter->GetReferredType(&context);
        if (type)
        {
            otava::intermediate::Value* local = emitter.EmitLocal(type->IrType(emitter, node.GetSourcePos(), &context));
            emitter.SetIrObject(parameter, local);
        }
        else
        {
            otava::symbols::ThrowException("parameter has no type", node.GetSourcePos(), &context);
        }
    }
    if (functionDefinition->ReturnsClass())
    {
        otava::symbols::ParameterSymbol* parameter = functionDefinition->ReturnValueParam();
        otava::symbols::TypeSymbol* type = parameter->GetReferredType(&context);
        if (type)
        {
            otava::intermediate::Value* local = emitter.EmitLocal(parameter->GetReferredType(&context)->IrType(emitter, node.GetSourcePos(), &context));
            emitter.SetIrObject(parameter, local);
        }
        else
        {
            otava::symbols::ThrowException("parameter has no type", node.GetSourcePos(), &context);
        }
    }
    int nlv = functionDefinition->LocalVariables().size();
    for (int i = 0; i < nlv; ++i)
    {
        otava::symbols::VariableSymbol* localVariable = functionDefinition->LocalVariables()[i];
        otava::symbols::TypeSymbol* type = localVariable->GetReferredType();
        if (type)
        {
            otava::intermediate::Value* local = emitter.EmitLocal(type->IrType(emitter, node.GetSourcePos(), &context));
            emitter.SetIrObject(localVariable, local);
        }
        else
        {
            otava::symbols::ThrowException("variable has no type", node.GetSourcePos(), &context);
        }
    }
    for (int i = 0; i < np; ++i)
    {
        otava::intermediate::Value* param = emitter.GetParam(i);
        otava::symbols::ParameterSymbol* parameter = functionDefinition->MemFunParameters(&context)[i];
        if (parameter->GetType()->IsClassTypeSymbol())
        {
            otava::symbols::ClassTypeSymbol* classTypeSymbol = static_cast<otava::symbols::ClassTypeSymbol*>(parameter->GetType());
            if (classTypeSymbol->CopyCtor())
            {
                otava::intermediate::FunctionType* copyCtorType = static_cast<otava::intermediate::FunctionType*>(classTypeSymbol->CopyCtor()->IrType(
                    emitter, node.GetSourcePos(), &context));
                otava::intermediate::Function* copyCtor = emitter.GetOrInsertFunction(classTypeSymbol->CopyCtor()->IrName(&context), copyCtorType);
                std::vector<otava::intermediate::Value*> args;
                args.push_back(static_cast<otava::intermediate::Value*>(parameter->IrObject(emitter, node.GetSourcePos(), &context)));
                args.push_back(param);
                emitter.EmitCall(copyCtor, args);
            }
            else
            {
                otava::symbols::ThrowException("class type '" + util::ToUtf8(classTypeSymbol->FullName()) + "' has no copy constructor needed by function '" +
                    util::ToUtf8(functionDefinition->FullName()) + "'", node.GetSourcePos(), &context);
            }
        }
        else
        {
            emitter.EmitStore(param, static_cast<otava::intermediate::Value*>(parameter->IrObject(emitter, node.GetSourcePos(), &context)));
        }
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
    if (!lastStatement || !lastStatement->IsReturnStatementNode() || !blockExits.front()->IsEmpty())
    {
        if (functionDefinition->ReturnType() && !functionDefinition->ReturnType()->IsVoidType() && !functionDefinition->ReturnsClass())
        {
            otava::intermediate::Value* returnValue = functionDefinition->ReturnType()->DirectType(&context)->FinalType(node.GetSourcePos(), &context)->IrType(
                emitter, node.GetSourcePos(), &context)->DefaultValue();
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
    ++currentBlockId;
    while (currentBlockId >= blockExits.size()) blockExits.push_back(std::unique_ptr<BlockExit>());
    blockExits[currentBlockId].reset(new BlockExit());
    StatementPrefix();
    int n = node.Statements().size();
    for (int i = 0; i < n; ++i)
    {
        otava::symbols::BoundStatementNode* statement = node.Statements()[i].get();
        statement->Accept(*this);
        prevWasTerminator = statement->EndsWithTerminator();
    }
    if (nextBlock && !prevWasTerminator)
    {
        StatementPrefix();
    }
    if (!prevWasTerminator && !blockExits[currentBlockId]->IsEmpty())
    {
        StatementPrefix();
        ExitBlocks(currentBlockId, currentBlockId, node.GetSourcePos());
    }
    --currentBlockId;
}

void CodeGenerator::Visit(otava::symbols::BoundIfStatementNode& node)
{
    StatementPrefix();
    elseEndsWithTerminator = false;
    otava::intermediate::BasicBlock* prevTrueBlock = trueBlock;
    otava::intermediate::BasicBlock* prevFalseBlock = falseBlock;
    trueBlock = emitter.CreateBasicBlock();
    nextBlock = emitter.CreateBasicBlock();
    emitter.SetNextBlock(nextBlock);
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
    emitter.SetNextBlock(nextBlock);
    prevWasTerminator = false;
    node.ThenStatement()->Accept(*this);
    nextBlock = prevNextBlock;
    emitter.SetNextBlock(nextBlock);
    if (!node.ThenStatement()->EndsWithTerminator())
    {
        emitter.EmitJump(nextBlock);
    }
    if (node.ElseStatement())
    {
        emitter.SetCurrentBasicBlock(falseBlock);
        otava::intermediate::BasicBlock* prevNextBlock = nextBlock;
        nextBlock = nullptr;
        emitter.SetNextBlock(nextBlock);
        prevWasTerminator = false;
        node.ElseStatement()->Accept(*this);
        nextBlock = prevNextBlock;
        emitter.SetNextBlock(nextBlock);
        if (!node.ElseStatement()->EndsWithTerminator())
        {
            if (!elseEndsWithTerminator)
            {
                emitter.EmitJump(nextBlock);
                emitter.SetCurrentBasicBlock(nextBlock);
            }
        }
        else
        {
            elseEndsWithTerminator = true;
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
    int prevBreakBlockId = breakBlockId;
    otava::intermediate::Value* condition = emitter.Stack().Pop();
    std::unique_ptr<SwitchTargets> switchTargets = CollectSwitchTargets(emitter, node.Statement());
    if (switchTargets->Default())
    {
        defaultBlock = switchTargets->Default()->block;
        nextBlock = emitter.CreateBasicBlock();
        emitter.SetNextBlock(nextBlock);
    }
    else
    {
        nextBlock = emitter.CreateBasicBlock();
        emitter.SetNextBlock(nextBlock);
        defaultBlock = nextBlock;
    }
    breakBlock = nextBlock;
    breakBlockId = currentBlockId;
    otava::intermediate::SwitchInstruction* switchInst = emitter.EmitSwitch(condition, defaultBlock);
    int n = switchTargets->Cases().size();
    for (int i = 0; i < n; ++i)
    {
        const auto& caseTarget = switchTargets->Cases()[i];
        emitter.SetCurrentBasicBlock(caseTarget->block);
        for (const auto& expr : caseTarget->exprs)
        {
            EvaluateConstantExpr(emitter, node.GetSourcePos(), context, expr);
            otava::intermediate::Value* caseValue = emitter.Stack().Pop();
            otava::intermediate::CaseTarget target(caseValue, caseTarget->block->Id());
            switchInst->AddCaseTarget(target);
        }
        otava::intermediate::BasicBlock* prevNextBlock = nextBlock;
        nextBlock = nullptr;
        emitter.SetNextBlock(nextBlock);
        prevWasTerminator = false;
        caseTarget->statement->Accept(*this);
        nextBlock = prevNextBlock;
        emitter.SetNextBlock(nextBlock);
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
        emitter.SetNextBlock(nextBlock);
        prevWasTerminator = false;
        switchTargets->Default()->statement->Accept(*this);
        nextBlock = prevNextBlock;
        emitter.SetNextBlock(nextBlock);
        if (!switchTargets->Default()->statement->EndsWithTerminator())
        {
            emitter.EmitJump(nextBlock);
        }
    }
    defaultBlock = prevDefaultBlock;
    breakBlock = prevBreakBlock;
    breakBlockId = prevBreakBlockId;
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
    int prevBreakBlockId = breakBlockId;
    otava::intermediate::BasicBlock* prevContinueBlock = continueBlock;
    int prevContinueBlockId = continueBlockId;
    trueBlock = emitter.CreateBasicBlock();
    falseBlock = emitter.CreateBasicBlock();
    breakBlock = falseBlock;
    breakBlockId = currentBlockId;
    if (emitter.GetCleanupList().IsDirty())
    {
        emitter.GetCleanupList().GenerateCleanup(emitter, node.GetSourcePos(), &context);
    }
    otava::intermediate::BasicBlock* condBlock = emitter.CreateBasicBlock();
    emitter.EmitJump(condBlock);
    emitter.SetCurrentBasicBlock(condBlock);
    continueBlock = condBlock;
    continueBlockId = currentBlockId;
    bool prevGenJumpingBoolCode = genJumpingBoolCode;
    genJumpingBoolCode = true;
    node.GetCondition()->Accept(*this);
    genJumpingBoolCode = prevGenJumpingBoolCode;
    emitter.SetCurrentBasicBlock(trueBlock);
    node.Statement()->Accept(*this);
    emitter.EmitJump(condBlock);
    emitter.SetCurrentBasicBlock(falseBlock);
    continueBlock = prevContinueBlock;
    continueBlockId = prevContinueBlockId;
    breakBlock = prevBreakBlock;
    breakBlockId = prevBreakBlockId;
    falseBlock = prevFalseBlock;
    trueBlock = prevTrueBlock;
}

void CodeGenerator::Visit(otava::symbols::BoundDoStatementNode& node)
{
    StatementPrefix();
    otava::intermediate::BasicBlock* prevTrueBlock = trueBlock;
    otava::intermediate::BasicBlock* prevFalseBlock = falseBlock;
    otava::intermediate::BasicBlock* prevBreakBlock = breakBlock;
    int prevBreakBlockId = breakBlockId;
    otava::intermediate::BasicBlock* prevContinueBlock = continueBlock;
    int prevContinueBlockId = continueBlockId;
    otava::intermediate::BasicBlock* doBlock = emitter.CreateBasicBlock();
    otava::intermediate::BasicBlock* condBlock = emitter.CreateBasicBlock();
    trueBlock = doBlock;
    falseBlock = emitter.CreateBasicBlock();
    breakBlock = falseBlock;
    breakBlockId = currentBlockId;
    continueBlock = condBlock;
    continueBlockId = currentBlockId;
    if (emitter.GetCleanupList().IsDirty())
    {
        emitter.GetCleanupList().GenerateCleanup(emitter, node.GetSourcePos(), &context);
    }
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
    emitter.SetNextBlock(nextBlock);
    continueBlock = prevContinueBlock;
    continueBlockId = prevContinueBlockId;
    breakBlock = prevBreakBlock;
    breakBlockId = prevBreakBlockId;
    falseBlock = prevFalseBlock;
    trueBlock = prevTrueBlock;
}

void CodeGenerator::Visit(otava::symbols::BoundForStatementNode& node)
{
    StatementPrefix();
    otava::intermediate::BasicBlock* prevTrueBlock = trueBlock;
    otava::intermediate::BasicBlock* prevFalseBlock = falseBlock;
    otava::intermediate::BasicBlock* prevBreakBlock = breakBlock;
    int prevBreakBlockId = breakBlockId;
    otava::intermediate::BasicBlock* prevContinueBlock = continueBlock;
    int prevContinueBlockId = continueBlockId;
    if (node.InitStatement())
    {
        node.InitStatement()->Accept(*this);
    }
    if (emitter.GetCleanupList().IsDirty())
    {
        emitter.GetCleanupList().GenerateCleanup(emitter, node.GetSourcePos(), &context);
    }
    otava::intermediate::BasicBlock* condBlock = emitter.CreateBasicBlock();
    otava::intermediate::BasicBlock* actionBlock = emitter.CreateBasicBlock();
    otava::intermediate::BasicBlock* loopBlock = emitter.CreateBasicBlock();
    trueBlock = actionBlock;
    falseBlock = emitter.CreateBasicBlock();
    breakBlock = falseBlock;
    breakBlockId = currentBlockId;
    continueBlock = loopBlock;
    continueBlockId = currentBlockId;
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
    emitter.SetNextBlock(nextBlock);
    continueBlock = prevContinueBlock;
    continueBlockId = prevContinueBlockId;
    breakBlock = prevBreakBlock;
    breakBlockId = prevBreakBlockId;
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
        emitter.GetCleanupList().GeneratePopContext(emitter, false);
        ExitBlocks(currentBlockId, -1, node.GetSourcePos());
        emitter.EmitRet(returnValue);
    }
    else
    {
        emitter.GetCleanupList().GeneratePopContext(emitter, false);
        ExitBlocks(currentBlockId, -1, node.GetSourcePos());
        emitter.EmitRetVoid();
    }
}

void CodeGenerator::Visit(otava::symbols::BoundBreakStatementNode& node)
{
    StatementPrefix();
    ExitBlocks(currentBlockId, breakBlockId + 1, node.GetSourcePos());
    if (node.Parent())
    {
        int index = node.Parent()->IndexOf(&node);
        if (index > 0)
        {
            otava::symbols::BoundCompoundStatementNode* parent = static_cast<otava::symbols::BoundCompoundStatementNode*>(node.Parent());
            otava::symbols::BoundStatementNode* prev = parent->Statements()[index - 1].get();
            if (prev->EndsWithTerminator())
            {
                return;
            }
        }
    }
    emitter.EmitJump(breakBlock);
}

void CodeGenerator::Visit(otava::symbols::BoundContinueStatementNode& node)
{
    StatementPrefix();
    ExitBlocks(currentBlockId, continueBlockId + 1, node.GetSourcePos());
    emitter.EmitJump(continueBlock);
}

void CodeGenerator::Visit(otava::symbols::BoundConstructionStatementNode& node)
{
    StatementPrefix();
    node.ConstructorCall()->Accept(*this);
    if (currentBlockId > 0)
    {
        if (node.DestructorCall())
        {
            emitter.GetCleanupList().Add(static_cast<otava::symbols::BoundFunctionCallNode*>(node.DestructorCall()->Clone()));
            blockExits[currentBlockId - 1]->AddDestructorCall(node.ReleaseDestructorCall());
        }
    }
}

void CodeGenerator::Visit(otava::symbols::BoundExpressionStatementNode& node)
{
    StatementPrefix();
    if (!node.GetExpr()) return;
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

void CodeGenerator::Visit(otava::symbols::BoundTryStatementNode& node)
{
    StatementPrefix();
    otava::intermediate::BasicBlock* tryBlock = emitter.CreateBasicBlock();
    otava::intermediate::BasicBlock* handlerBlock = emitter.CreateBasicBlock();
    otava::intermediate::BasicBlock* prevContinueAfterTryBlock = continueAfterTryBlock;
    continueAfterTryBlock = emitter.CreateBasicBlock();
    otava::intermediate::Value* ctx = emitter.EmitCall(emitter.EhFunctions().PushContextFunction(), std::vector<otava::intermediate::Value*>());
    otava::intermediate::Value* intValue = emitter.EmitCall(emitter.EhFunctions().SaveContextFunction(), std::vector<otava::intermediate::Value*>(1, ctx));
    otava::intermediate::Value* boolValue = emitter.EmitEqual(intValue, emitter.EmitInt(0));
    emitter.EmitBranch(boolValue, tryBlock, handlerBlock);
    emitter.SetCurrentBasicBlock(tryBlock);
    node.TryBlock()->Accept(*this);
    if (!node.TryBlock()->EndsWithTerminator())
    {
        emitter.EmitJump(continueAfterTryBlock);
    }
    emitter.SetCurrentBasicBlock(handlerBlock);
    int n = node.Handlers().size();
    for (int i = 0; i < n; ++i)
    {
        otava::symbols::BoundHandlerNode* handler = node.Handlers()[i].get();
        handler->Accept(*this);
        StatementPrefix();
    }
    otava::intermediate::Value* nextCtx = emitter.EmitCall(emitter.EhFunctions().PopContextFunction(), std::vector<otava::intermediate::Value*>());
    std::vector<otava::intermediate::Value*> restoreContextArgs;
    restoreContextArgs.push_back(nextCtx);
    restoreContextArgs.push_back(emitter.EmitInt(1));
    emitter.EmitCall(emitter.EhFunctions().RestoreContextFunction(), restoreContextArgs);
    emitter.EmitJump(continueAfterTryBlock);
    nextBlock = continueAfterTryBlock;
    emitter.SetNextBlock(nextBlock);
    continueAfterTryBlock = prevContinueAfterTryBlock;
}

void CodeGenerator::Visit(otava::symbols::BoundHandlerNode& node)
{
    uint64_t hth = 0;
    uint64_t htl = 0;
    util::UuidToInts(node.ExceptionTypeId(), hth, htl);
    std::vector<otava::intermediate::Value*> handleExceptionArgs;
    handleExceptionArgs.push_back(emitter.EmitULong(hth));
    handleExceptionArgs.push_back(emitter.EmitULong(htl));
    otava::intermediate::Value* handleValue = emitter.EmitCall(emitter.EhFunctions().HandleExceptionFunction(), handleExceptionArgs);
    otava::intermediate::BasicBlock* catchBlock = emitter.CreateBasicBlock();
    otava::intermediate::BasicBlock* nextCatchBlock = emitter.CreateBasicBlock();
    emitter.EmitBranch(handleValue, catchBlock, nextCatchBlock);
    emitter.SetCurrentBasicBlock(catchBlock);
    prevWasTerminator = false;
    node.CatchBlock()->Accept(*this);
    if (!node.CatchBlock()->EndsWithTerminator())
    {
        emitter.EmitJump(continueAfterTryBlock);
    }
    nextBlock = nextCatchBlock;
    emitter.SetNextBlock(nextBlock);
    prevWasTerminator = false;
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
    if (node.IsNoreturnFunctionCall())
    {
        EmitReturn(node.GetSourcePos());
    }
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

void CodeGenerator::Visit(otava::symbols::BoundThrowExpressionNode& node)
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
    else
    {
        boundConjunction.Load(emitter, otava::symbols::OperationFlags::none, boundConjunction.GetSourcePos(), &context);
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
    else
    {
        boundDisjunction.Load(emitter, otava::symbols::OperationFlags::none, boundDisjunction.GetSourcePos(), &context);
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
    if (variable->GetValue() && !variable->GetType()->IsClassTypeSymbol())
    {
        variable->GetValue()->SetType(variable->GetType());
        initializer = variable->GetValue()->IrValue(emitter, node.GetSourcePos(), &context);
    }
    else
    {
        initializer = irType->MakeDefaultValue(*emitter.GetIntermediateContext());
    }
    otava::intermediate::Value* irVariable = emitter.EmitGlobalVariable(irType, variable->IrName(&context), initializer);
    emitter.SetIrObject(variable, irVariable);
}

std::string GenerateCode(otava::symbols::Context& context, const std::string& config, bool verbose, std::string& mainIrName, int& mainFunctionParams, bool globalMain,
    const std::vector<std::string>& compileUnitInitFnNames)
{
    CodeGenerator codeGenerator(context, config, verbose, mainIrName, mainFunctionParams, globalMain, compileUnitInitFnNames);
    context.GetBoundCompileUnit()->Accept(codeGenerator);
    return codeGenerator.GetAsmFileName();
}

} // namespace otava::codegen
