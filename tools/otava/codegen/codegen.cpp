// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.codegen;

import otava.codegen.goto_target_map_builder;
import otava.symbols.emitter;
import otava.symbols.function.kind;
import otava.symbols.function.symbol;
import otava.symbols.fundamental.type.symbol;
import otava.symbols.project;
import otava.intermediate.code;
import otava.intermediate.compile_unit;
import otava.intermediate.context;
import otava.intermediate.metadata;
import otava.intermediate.parser;
import otava.intermediate.register_allocator;
import otava.intermediate.verify;
import otava.intermediate.code_generator;
import otava.intermediate.main.parser;
import otava.symbols.type.resolver;
import otava.symbols.class_templates;
import otava.symbols.function.templates;
import otava.symbols.inline_functions;
import otava.symbols.argument.conversion.table;
import otava.symbols.operation.repository;
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
import otava.symbols.expression.binder;
import otava.symbols.expr.parser;
import otava.symbols.stmt.parser;
import otava.symbols.statement.binder;
import otava.ast;
import class_info_index;
import otava.opt;
import std;
import util;

namespace otava::codegen {

struct SwitchTarget
{
    SwitchTarget(otava::intermediate::BasicBlock* block_, otava::symbols::BoundStatementNode* statement_, const std::vector<otava::symbols::BoundExpressionNode*>& exprs_);
    otava::intermediate::BasicBlock* block;
    otava::symbols::BoundStatementNode* statement;
    std::vector<otava::symbols::BoundExpressionNode*> exprs;
};

SwitchTarget::SwitchTarget(otava::intermediate::BasicBlock* block_, otava::symbols::BoundStatementNode* statement_, 
    const std::vector<otava::symbols::BoundExpressionNode*>& exprs_) : block(block_), statement(statement_), exprs(exprs_)
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
        std::int64_t val = value->GetIntegerValue();
        otava::intermediate::Type* type = node.GetType()->IrType(emitter, sourcePos, &context);
        if (type->IsIntegerType())
        {
            switch (type->Id())
            {
                case otava::intermediate::sbyteTypeId:
                {
                    value = emitter.GetIntermediateContext()->GetSByteValue(static_cast<std::int8_t>(val));
                    break;
                }
                case otava::intermediate::byteTypeId:
                {
                    value = emitter.GetIntermediateContext()->GetByteValue(static_cast<std::uint8_t>(val));
                    break;
                }
                case otava::intermediate::shortTypeId:
                {
                    value = emitter.GetIntermediateContext()->GetShortValue(static_cast<std::int16_t>(val));
                    break;
                }
                case otava::intermediate::ushortTypeId:
                {
                    value = emitter.GetIntermediateContext()->GetUShortValue(static_cast<std::uint16_t>(val));
                    break;
                }
                case otava::intermediate::intTypeId:
                {
                    value = emitter.GetIntermediateContext()->GetIntValue(static_cast<std::int32_t>(val));
                    break;
                }
                case otava::intermediate::uintTypeId:
                {
                    value = emitter.GetIntermediateContext()->GetUIntValue(static_cast<std::uint32_t>(val));
                    break;
                }
                case otava::intermediate::longTypeId:
                {
                    value = emitter.GetIntermediateContext()->GetLongValue(static_cast<std::int64_t>(val));
                    break;
                }
                case otava::intermediate::ulongTypeId:
                {
                    value = emitter.GetIntermediateContext()->GetULongValue(static_cast<std::uint64_t>(val));
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
}

class CodeGenerator : public otava::symbols::DefaultBoundTreeVisitor
{
public:
    CodeGenerator(otava::symbols::Context& context_, const std::string& config_, int optLevel_, bool verbose_, std::string& mainIrName_, 
        int& mainFunctionParams_, bool globalMain, const std::vector<std::string>& compileUnitInitFnNames_);
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
    void Visit(otava::symbols::BoundFunctionPtrCallNode& node) override;
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
    void Visit(otava::symbols::BoundConditionalExprNode& boundConditionalExpr) override;
    void Visit(otava::symbols::BoundGlobalVariableDefinitionNode& node) override;
    void Visit(otava::symbols::BoundGotoStatementNode& node) override;
    void Visit(otava::symbols::BoundLabeledStatementNode& node) override;
private:
    void StatementPrefix();
    void GenJumpingBoolCode();
    void GenerateVTab(otava::symbols::ClassTypeSymbol* cls, const soul::ast::SourcePos& sourcePos);
    void AddClassInfo(otava::symbols::ClassTypeSymbol* cls);
    void EmitReturn(const soul::ast::SourcePos& sourcePos);
    void ExitBlocks(int sourceBlockId, int targetBlockId, const soul::ast::SourcePos& sourcePos);
    void GenerateGlobalInitializationFunction();
    void SetCurrentLineNumber(const soul::ast::SourcePos& sourcePos);
    std::string optimizedIntermediateFilePath;
    otava::symbols::Context& context;
    otava::symbols::Emitter* emitter;
    std::string config;
    int optLevel;
    bool verbose;
    int line;
    std::string& mainIrName;
    int& mainFunctionParams;
    otava::symbols::FunctionDefinitionSymbol* functionDefinition;
    otava::intermediate::BasicBlock* entryBlock;
    otava::intermediate::BasicBlock* trueBlock;
    otava::intermediate::BasicBlock* falseBlock;
    otava::intermediate::BasicBlock* defaultBlock;
    otava::intermediate::BasicBlock* breakBlock;
    int breakBlockId;
    otava::intermediate::BasicBlock* continueBlock;
    int continueBlockId;
    int currentBlockId;
    std::vector<std::unique_ptr<BlockExit>> blockExits;
    bool genJumpingBoolCode;
    bool lastInstructionWasRet;
    bool prevWasTerminator;
    bool basicBlockOpen;
    bool destructorCallGenerated;
    bool inLineNumberCode;
    bool emitLineNumbers;
    otava::symbols::BoundFunctionNode* boundFunction;
    otava::symbols::BoundCompoundStatementNode* currentBlock;
    otava::symbols::BoundReturnStatementNode* latestRet;
    otava::symbols::BoundStatementNode* sequenceSecond;
    std::string asmFileName;
    bool globalMain;
    std::vector<std::string> compileUnitInitFnNames;
    std::set<std::string> emittedVTabNames;
};

CodeGenerator::CodeGenerator(otava::symbols::Context& context_, const std::string& config_, int optLevel_, bool verbose_, std::string& mainIrName_, 
    int& mainFunctionParams_, bool globalMain_, const std::vector<std::string>& compileUnitInitFnNames_) :
    context(context_), emitter(context.GetEmitter()), config(config_), optLevel(optLevel_), verbose(verbose_), 
    mainIrName(mainIrName_), mainFunctionParams(mainFunctionParams_),
    functionDefinition(nullptr), entryBlock(nullptr), trueBlock(nullptr), falseBlock(nullptr), defaultBlock(nullptr), breakBlock(nullptr), 
    breakBlockId(-1), continueBlock(nullptr), continueBlockId(-1), genJumpingBoolCode(false), lastInstructionWasRet(false), 
    prevWasTerminator(false), basicBlockOpen(false), destructorCallGenerated(false), sequenceSecond(nullptr), currentBlockId(-1), globalMain(globalMain_),
    compileUnitInitFnNames(compileUnitInitFnNames_), latestRet(nullptr), boundFunction(nullptr), currentBlock(nullptr), line(0), inLineNumberCode(false),
    emitLineNumbers(false)
{
    std::string intermediateCodeFilePath;
    if (config == "release")
    {
        intermediateCodeFilePath = util::GetFullPath(
            util::Path::Combine(
                util::Path::Combine(util::Path::Combine(util::Path::GetDirectoryName(context.FileName()), config), 
                    std::to_string(otava::symbols::GetOptLevel(optLevel, true))), util::Path::GetFileName(context.FileName()) + ".i"));
    }
    else
    {
        intermediateCodeFilePath = util::GetFullPath(
            util::Path::Combine(
                util::Path::Combine(util::Path::GetDirectoryName(context.FileName()), config),
                util::Path::GetFileName(context.FileName()) + ".i"));
    }
    emitter->SetFilePath(intermediateCodeFilePath);
    std::filesystem::create_directories(util::Path::GetDirectoryName(intermediateCodeFilePath));
    if (config == "release")
    {
        optimizedIntermediateFilePath = util::GetFullPath(
            util::Path::Combine(util::Path::Combine(util::Path::Combine(util::Path::GetDirectoryName(context.FileName()), config), 
                std::to_string(otava::symbols::GetOptLevel(optLevel, true))), util::Path::GetFileName(context.FileName()) + ".opt.i"));
    }
    else
    {
        optimizedIntermediateFilePath = util::GetFullPath(
            util::Path::Combine(util::Path::Combine(util::Path::GetDirectoryName(context.FileName()), config),
                util::Path::GetFileName(context.FileName()) + ".opt.i"));
    }
}

void CodeGenerator::Reset()
{
    functionDefinition = nullptr;
    entryBlock = nullptr;
    trueBlock = nullptr;
    falseBlock = nullptr;
    defaultBlock = nullptr;
    breakBlock = nullptr;
    breakBlockId = -1;
    continueBlock = nullptr;
    continueBlockId = -1;
    genJumpingBoolCode = false;
    lastInstructionWasRet = false;
    prevWasTerminator = false;
    basicBlockOpen = false;
    destructorCallGenerated = false;
    latestRet = nullptr;
    sequenceSecond = nullptr;
    currentBlockId = -1;
    blockExits.clear();
    boundFunction = nullptr;
    currentBlock = nullptr;
    line = 0;
    emitLineNumbers = !context.ReleaseConfig() || context.CurrentProject() && context.CurrentProject()->HasDefine("TRACE");
}

void CodeGenerator::StatementPrefix()
{
    basicBlockOpen = false;
    lastInstructionWasRet = false; 
    latestRet = nullptr;
    destructorCallGenerated = false;
}

void CodeGenerator::GenJumpingBoolCode()
{
    if (!genJumpingBoolCode) return;
    otava::intermediate::Value* cond = emitter->Stack().Pop();
    if (sequenceSecond)
    {
        genJumpingBoolCode = false;
        sequenceSecond->SetGenerated();
        sequenceSecond->Accept(*this);
        genJumpingBoolCode = true;
    }
    emitter->EmitBranch(cond, trueBlock, falseBlock);
}

void CodeGenerator::GenerateVTab(otava::symbols::ClassTypeSymbol* cls, const soul::ast::SourcePos& sourcePos)
{
    if (!cls->IsPolymorphic()) return;
    if (!cls->IsClassTemplateSpecializationSymbol())
    {
        if (cls->GetFlag(otava::symbols::ClassTypeSymbolFlags::vtabGenerated)) return;
        cls->SetFlag(otava::symbols::ClassTypeSymbolFlags::vtabGenerated);
    }
    cls->ComputeVTabName(&context);
    std::string vtabName = cls->VTabName(&context);
    if (emittedVTabNames.find(vtabName) != emittedVTabNames.end()) return;
    emittedVTabNames.insert(vtabName);
    context.SetFlag(otava::symbols::ContextFlags::generatingVTab);
    cls->MakeVTab(&context, sourcePos);
    otava::intermediate::Type* voidPtrIrType = emitter->MakePtrType(emitter->GetVoidType());
    otava::intermediate::Type* arrayType = emitter->MakeArrayType(cls->VTab().size() * 2 + otava::symbols::vtabClassIdElementCount, voidPtrIrType);
    otava::intermediate::Type* arrayPtrType = emitter->MakePtrType(arrayType);
    std::vector<otava::intermediate::Value*> elements;
    util::uuid classId = cls->Id();
    std::uint64_t classIdFirst;
    std::uint64_t classIdSecond;
    util::UuidToInts(classId, classIdFirst, classIdSecond);
    otava::intermediate::Value* classIdFirstValue = emitter->EmitConversionValue(voidPtrIrType, emitter->EmitULong(classIdFirst));
    elements.push_back(classIdFirstValue);
    otava::intermediate::Value* classIdSecondValue = emitter->EmitConversionValue(voidPtrIrType, emitter->EmitULong(classIdSecond));
    elements.push_back(classIdSecondValue);
    for (otava::symbols::FunctionSymbol* functionSymbol : cls->VTab())
    {
        if (functionSymbol)
        {
            otava::intermediate::Type* irType = functionSymbol->IrType(*emitter, sourcePos, &context);
            if (irType->IsFunctionType())
            {
                if (functionSymbol->IsPure())
                {
                    otava::intermediate::Value* functionValue = emitter->EmitNull(voidPtrIrType);
                    otava::intermediate::Value* deltaValue = emitter->EmitLong(0);
                    otava::intermediate::Value* element1Value = emitter->EmitConversionValue(voidPtrIrType, functionValue);
                    elements.push_back(element1Value);
                    otava::intermediate::Value* element2Value = emitter->EmitConversionValue(voidPtrIrType, deltaValue);
                    elements.push_back(element2Value);
                }
                else
                {
                    otava::intermediate::FunctionType* functionType = static_cast<otava::intermediate::FunctionType*>(irType);
                    emitter->GetOrInsertFunction(functionSymbol->IrName(&context), functionType);
                    otava::intermediate::Value* functionValue = emitter->EmitSymbolValue(functionType, functionSymbol->IrName(&context));
                    auto [succeeded, delta] = otava::symbols::Delta(cls, functionSymbol->ParentClassType(), *emitter, &context);
                    if (!succeeded)
                    {
                        otava::symbols::ThrowException("could not resolve delta for classes '" + util::ToUtf8(cls->FullName()) + "' and '" + 
                            util::ToUtf8(functionSymbol->ParentClassType()->FullName()) + "'", sourcePos, &context);
                    }
                    otava::intermediate::Value* deltaValue = emitter->EmitLong(delta);
                    otava::intermediate::Value* element1Value = emitter->EmitConversionValue(voidPtrIrType, functionValue);
                    elements.push_back(element1Value);
                    otava::intermediate::Value* element2Value = emitter->EmitConversionValue(voidPtrIrType, deltaValue);
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
            otava::intermediate::Value* element1Value = emitter->EmitNull(voidPtrIrType);
            elements.push_back(element1Value);
            otava::intermediate::Value* deltaValue = emitter->EmitLong(0);
            otava::intermediate::Value* element2Value = emitter->EmitConversionValue(voidPtrIrType, deltaValue);
            elements.push_back(element2Value);
        }
    }
    otava::intermediate::Value* arrayValue = emitter->EmitArrayValue(elements, static_cast<otava::intermediate::ArrayType*>(arrayType));
    otava::intermediate::Value* vtabVariable = emitter->EmitGlobalVariable(arrayType, vtabName, arrayValue);
    emitter->SetVTabVariable(cls->FullName(), vtabVariable);
    context.ResetFlag(otava::symbols::ContextFlags::generatingVTab);
    for (const auto& boundVTabFunction : context.BoundVTabFunctions())
    {
        boundVTabFunction->Accept(*this);
    }
    context.ClearBoundVTabFunctions();
}

void CodeGenerator::ExitBlocks(int sourceBlockId, int targetBlockId, const soul::ast::SourcePos& sourcePos)
{
    bool prevEmitLineNumbers = emitLineNumbers;
    emitLineNumbers = false;
    bool createBasicBlock = false;
    otava::symbols::BoundStatementNode* lastStatement = nullptr;
    if (boundFunction->Body() && !boundFunction->Body()->Statements().empty())
    {
        lastStatement = boundFunction->Body()->Statements().back().get();
    }
    otava::symbols::BoundStatementNode* currentBlockLastStatement = nullptr;
    if (currentBlock && !currentBlock->Statements().empty())
    {
        currentBlockLastStatement = currentBlock->Statements().back().get();
    }
    if (lastStatement && currentBlockLastStatement && lastStatement == currentBlockLastStatement && currentBlockLastStatement->IsReturnOrSequenceReturnStatementNode())
    {
        createBasicBlock = true; 
    }
    if (targetBlockId == -1)
    {
        for (int i = sourceBlockId; i >= 0; --i)
        {
            if (i >= 0 && i < blockExits.size())
            {
                BlockExit* exit = blockExits[i].get();
                if (exit)
                {
                    if (!exit->IsEmpty())
                    {
                        if (createBasicBlock)
                        {
                            otava::intermediate::BasicBlock* nextBlock = emitter->CreateBasicBlock();
                            if (!lastInstructionWasRet)
                            {
                                emitter->EmitJump(nextBlock);
                            }
                            emitter->SetCurrentBasicBlock(nextBlock);
                            createBasicBlock = false;
                        }
                        exit->Execute(*emitter, sourcePos, &context, false);
                        destructorCallGenerated = true;
                    }
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
                    if (!exit->IsEmpty())
                    {
                        if (createBasicBlock)
                        {
                            otava::intermediate::BasicBlock* nextBlock = emitter->CreateBasicBlock();
                            if (!lastInstructionWasRet)
                            {
                                emitter->EmitJump(nextBlock);
                            }
                            emitter->SetCurrentBasicBlock(nextBlock);
                            createBasicBlock = false;
                        }
                        exit->Execute(*emitter, sourcePos, &context, true);
                        destructorCallGenerated = true;
                    }
                }
            }
        }
    }
    emitLineNumbers = prevEmitLineNumbers;
}

void CodeGenerator::EmitReturn(const soul::ast::SourcePos& sourcePos)
{
    if (functionDefinition->ReturnType() && !functionDefinition->ReturnType()->IsVoidType() && !functionDefinition->ReturnsClass())
    {
        otava::intermediate::Value* returnValue = functionDefinition->ReturnType()->DirectType(&context)->FinalType(sourcePos, &context)->IrType(
            *emitter, sourcePos, &context)->DefaultValue();
        emitter->EmitRet(returnValue);
    }
    else
    {
        emitter->EmitRetVoid();
    }
}

void CodeGenerator::GenerateGlobalInitializationFunction()
{
    Reset();
    std::u32string setBadAllocExStr;
    std::uint64_t ext1 = 0;
    std::uint64_t ext2 = 0;
    otava::symbols::FunctionDefinitionSymbol* globalInit(new otava::symbols::FunctionDefinitionSymbol(U"__global_init__"));
    globalInit->SetLinkage(otava::symbols::Linkage::c_linkage);
    otava::ast::NestedNameSpecifierNode* nnsNode = new otava::ast::NestedNameSpecifierNode(soul::ast::SourcePos());
    nnsNode->AddNode(new otava::ast::IdentifierNode(soul::ast::SourcePos(), U"std"));
    otava::ast::QualifiedIdNode badAllocNode(soul::ast::SourcePos(), nnsNode, new otava::ast::IdentifierNode(soul::ast::SourcePos(), U"bad_alloc"));
    otava::symbols::TypeSymbol* badAllocType = otava::symbols::ResolveType(&badAllocNode, otava::symbols::DeclarationFlags::none, &context);
    util::UuidToInts(badAllocType->Id(), ext1, ext2);
    setBadAllocExStr.append(U"ort_set_bad_alloc(new std::bad_alloc(), ").append(util::ToUtf32(std::to_string(ext1)).append(U"ull, ").
        append(util::ToUtf32(std::to_string(ext2)).append(U"ull);")));
    std::unique_ptr<otava::ast::Node> setBadAllocStmtNode = otava::symbols::ParseStatement(setBadAllocExStr, &context);
    std::unique_ptr<otava::symbols::BoundFunctionNode> boundFunction(new otava::symbols::BoundFunctionNode(globalInit, soul::ast::SourcePos()));
    context.PushBoundFunction(boundFunction.release());
    std::unique_ptr<otava::symbols::BoundStatementNode> setBadAllocStmt(otava::symbols::BindStatement(setBadAllocStmtNode.get(), nullptr, &context));
    setBadAllocStmt->SetSource(setBadAllocStmtNode.release());
    std::unique_ptr<otava::symbols::BoundCompoundStatementNode> compoundStmt(new otava::symbols::BoundCompoundStatementNode(soul::ast::SourcePos()));
    compoundStmt->AddStatement(setBadAllocStmt.release());
    context.PushSetFlag(otava::symbols::ContextFlags::makeCompileUnitInitFn);
    int n = compileUnitInitFnNames.size();
    for (int i = 0; i < n; ++i)
    {
        std::unique_ptr<otava::ast::Node> callInitFunctionNode = otava::symbols::ParseStatement(util::ToUtf32(compileUnitInitFnNames[i]) + U"();", &context);
        std::unique_ptr<otava::symbols::BoundStatementNode> initFnCall(otava::symbols::BindStatement(callInitFunctionNode.get(), globalInit, &context));
        initFnCall->SetSource(callInitFunctionNode.release());
        compoundStmt->AddStatement(initFnCall.release());
    }
    context.PopFlags();
    context.GetBoundFunction()->SetBody(compoundStmt.release());
    context.GetBoundFunction()->Accept(*this);
}

void CodeGenerator::SetCurrentLineNumber(const soul::ast::SourcePos& sourcePos)
{
    if (!emitLineNumbers) return;
    if (!sourcePos.IsValid()) return;
    if (inLineNumberCode) return;
    if (boundFunction)
    {
        if (line != sourcePos.line)
        {
            line = sourcePos.line;
            emitter->SetLine(line);
            if (boundFunction->GetBoundSetLineStatement())
            {
                inLineNumberCode = true;
                bool prevGenJumpingBoolCode = genJumpingBoolCode;
                genJumpingBoolCode = false;
                boundFunction->GetBoundSetLineStatement()->Accept(*this);
                genJumpingBoolCode = prevGenJumpingBoolCode;
                inLineNumberCode = false;
            }
            emitter->SetLine(0);
        }
    }
}

void CodeGenerator::Visit(otava::symbols::BoundCompileUnitNode& node)
{
    context.PushSetFlag(otava::symbols::ContextFlags::requireForwardResolved);
    if (globalMain)
    {
        GenerateGlobalInitializationFunction();
    }
    node.Sort();
    emitter->SetCompileUnitInfo(node.Id(), context.FileName());
    for (int i = 0; i < node.BoundNodes().size(); ++i)
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
    emitter->ResolveReferences();
    emitter->Emit();
    otava::intermediate::Context intermediateContext;
    otava::intermediate::Context optimizationContext;
    otava::intermediate::Context* finalContext = &intermediateContext;
    otava::intermediate::Parse(emitter->FilePath(), intermediateContext, verbose);
    otava::intermediate::Verify(intermediateContext);
    std::string assemblyFilePath;
    if (config == "release")
    {
        assemblyFilePath = util::GetFullPath(
            util::Path::Combine(
                util::Path::Combine(util::Path::Combine(util::Path::GetDirectoryName(context.FileName()), config), std::to_string(otava::symbols::GetOptLevel(optLevel, true))),
                util::Path::GetFileName(context.FileName()) + ".asm"));
    }
    else
    {
        assemblyFilePath = util::GetFullPath(
            util::Path::Combine(
                util::Path::Combine(util::Path::GetDirectoryName(context.FileName()), config),
                util::Path::GetFileName(context.FileName()) + ".asm"));
    }
    std::unique_ptr<otava::intermediate::CodeGenerator> codeGenerator;
    if (context.ReleaseConfig())
    {
        intermediateContext.SetFilePath(optimizedIntermediateFilePath);
        otava::optimizer::Optimize(&intermediateContext);
        intermediateContext.WriteFile();
        otava::intermediate::Parse(optimizedIntermediateFilePath, optimizationContext, verbose);
        otava::intermediate::Verify(optimizationContext);
        finalContext = &optimizationContext;
        codeGenerator.reset(new otava::optimizer::OptimizingCodeGenerator(finalContext, assemblyFilePath));
    }
    else
    {
        codeGenerator.reset(new otava::intermediate::CodeGenerator(finalContext, assemblyFilePath));
    }
    otava::intermediate::GenerateCode(*finalContext, *codeGenerator, verbose);
    asmFileName = util::Path::GetFileName(context.FileName()) + ".asm";
    context.PopFlags();
    context.SetTotalFunctionsCompiled(context.TotalFunctionsCompiled() + intermediateContext.TotalFunctions());
    context.SetTotalFunctionsCompiled(context.TotalFunctionsCompiled() + optimizationContext.TotalFunctions());
    context.SetFunctionsInlined(context.FunctionsInlined() + intermediateContext.FunctionsInlined());
    context.SetFunctionsInlined(context.FunctionsInlined() + optimizationContext.FunctionsInlined());
    context.SetFunctionCallsInlined(context.FunctionCallsInlined() + intermediateContext.InlinedFunctionCalls());
    context.SetFunctionCallsInlined(context.FunctionCallsInlined() + optimizationContext.InlinedFunctionCalls());
    for (const auto& cls : context.GetSymbolTable()->Classes())
    {
        AddClassInfo(cls);
    }
}

void CodeGenerator::Visit(otava::symbols::BoundClassNode& node)
{
    otava::symbols::ClassTypeSymbol* cls = node.GetClass();
    cls->MakeObjectLayout(soul::ast::SourcePos(), &context);
    GenerateVTab(cls, node.GetSourcePos());
}

void CodeGenerator::AddClassInfo(otava::symbols::ClassTypeSymbol* cls)
{
    std::set<const otava::symbols::Symbol*> visited;
    if (cls->IsTemplate() || cls->IsTemplateParameterInstantiation(&context, visited)) return;
    std::uint64_t clsidh = 0;
    std::uint64_t clsidl = 0;
    util::UuidToInts(cls->Id(), clsidh, clsidl);
    info::class_id id = std::make_pair(clsidh, clsidl);
    otava::symbols::SymbolTable* symbolTable = context.GetSymbolTable();
    info::class_index& index = symbolTable->ClassIndex();
    if (index.get_class_info(id)) return;
    otava::intermediate::Type* clsType = cls->IrType(*emitter, soul::ast::SourcePos(),  &context);
    otava::symbols::ClassKind kind = cls->GetClassKind();
    info::class_key key = info::class_key::cls;
    switch (kind)
    {
        case otava::symbols::ClassKind::class_: key = info::class_key::cls; break;
        case otava::symbols::ClassKind::struct_: key = info::class_key::strct; break;
        case otava::symbols::ClassKind::union_: key = info::class_key::uni; break;
    }
    std::unique_ptr<info::class_info> info(new info::class_info(id, key, util::ToUtf8(cls->FullName()), clsType->Size()));
    for (otava::symbols::ClassTypeSymbol* base : cls->BaseClasses())
    {
        std::uint64_t h = 0;
        std::uint64_t l = 0;
        util::UuidToInts(base->Id(), h, l);
        info->add_base(std::make_pair(h, l));
    }
    index.add_class(info);
}

void CodeGenerator::Visit(otava::symbols::BoundFunctionNode& node)
{
    boundFunction = &node;
    functionDefinition = node.GetFunctionDefinitionSymbol();
    if ((functionDefinition->Qualifiers() & otava::symbols::FunctionQualifiers::isDeleted) != otava::symbols::FunctionQualifiers::none)
    {
        return;
    }
    if (functionDefinition->ContainsGotosOrLabels())
    {
        BuildGotoTargetMap(node.Body(), &context);
    }
    if (functionDefinition->Name() == U"main")
    {
        mainIrName = functionDefinition->IrName(&context);
        mainFunctionParams = functionDefinition->Arity();
    }
    std::string functionDefinitionName = functionDefinition->IrName(&context);
    if (functionDefinitionName == "fn_invoke_2_compile_unit_D968A6AB65476A511EF6CA9D3F4C16215B7168E8_1527501DB2EDDADD855E83B3DF2FBFDA86C4EB64")
    {
        int x = 0;
    }
    otava::intermediate::Type* functionType = functionDefinition->IrType(*emitter, node.GetSourcePos(), &context);
    bool once = false;
    bool inline_ = context.ReleaseConfig() && functionDefinition->IsInline();
    bool child = functionDefinition->ParentFn() != nullptr;
    otava::intermediate::Function* function = emitter->CreateFunction(functionDefinitionName, functionType, inline_, once, child);
    if (child)
    {
        function->SetComment(util::ToUtf8(functionDefinition->FullName()) + ", parent=" + util::ToUtf8(functionDefinition->ParentFn()->FullName()));
    }
    else
    {
        function->SetComment(util::ToUtf8(functionDefinition->FullName()));
    }
    otava::intermediate::MetadataStruct* mdStruct = emitter->CreateMetadataStruct();
    mdStruct->AddItem("nodeType", emitter->CreateMetadataLong(otava::intermediate::funcInfoNodeType));
    mdStruct->AddItem("fullName", emitter->CreateMetadataString(util::ToUtf8(functionDefinition->FullName())));
    if (child)
    {
        mdStruct->AddItem("parentName", emitter->CreateMetadataString(util::ToUtf8(functionDefinition->ParentFn()->FullName())));
    }
    function->SetMdId(mdStruct->Id());
    otava::intermediate::MetadataRef* mdRef = emitter->CreateMetadataRef(mdStruct->Id());
    function->SetMetadataRef(mdRef);
    entryBlock = emitter->CreateBasicBlock();
    emitter->SetCurrentBasicBlock(entryBlock);
    if (functionDefinition->ParentFn())
    {
        otava::symbols::FunctionDefinitionSymbol* parentFn = functionDefinition->ParentFn();
        int level = 0;
        while (parentFn)
        {
            int np = parentFn->MemFunParameters(&context).size();
            for (int i = 0; i < np; ++i)
            {
                otava::symbols::ParameterSymbol* parameter = parentFn->MemFunParameters(&context)[i];
                otava::symbols::TypeSymbol* type = parameter->GetReferredType(&context);
                if (type)
                {
                    otava::intermediate::Value* plocal = emitter->EmitPLocal(type->IrType(*emitter, node.GetSourcePos(), &context), level);
                    emitter->SetIrObject(parameter, plocal);
                }
                else
                {
                    otava::symbols::PrintWarning("type of parameter '" + util::ToUtf8(parameter->Name()) + "' not set", node.GetSourcePos(), &context);
                }
            }
            if (parentFn->ReturnsClass())
            {
                otava::symbols::ParameterSymbol* parameter = parentFn->ReturnValueParam();
                otava::symbols::TypeSymbol* type = parameter->GetReferredType(&context);
                if (type)
                {
                    otava::intermediate::Value* plocal = emitter->EmitPLocal(
                        parameter->GetReferredType(&context)->IrType(*emitter, node.GetSourcePos(), &context), level);
                    emitter->SetIrObject(parameter, plocal);
                }
                else
                {
                    otava::symbols::PrintWarning("type of parameter '" + util::ToUtf8(parameter->Name()) + "' not set", node.GetSourcePos(), &context);
                }
            }
            int nlv = parentFn->LocalVariables().size();
            for (int i = 0; i < nlv; ++i)
            {
                otava::symbols::VariableSymbol* localVariable = parentFn->LocalVariables()[i];
                otava::symbols::TypeSymbol* type = localVariable->GetReferredType();
                if (type)
                {
                    otava::intermediate::Value* plocal = emitter->EmitPLocal(type->IrType(*emitter, node.GetSourcePos(), &context), level);
                    emitter->SetIrObject(localVariable, plocal);
                }
                else
                {
                    otava::symbols::PrintWarning("type of local variable '" + util::ToUtf8(localVariable->Name()) + "' not set", node.GetSourcePos(), &context);
                }
            }
            parentFn = parentFn->ParentFn();
            ++level;
        }
    }
    int np = functionDefinition->MemFunParameters(&context).size();
    for (int i = 0; i < np; ++i)
    {
        otava::symbols::ParameterSymbol* parameter = functionDefinition->MemFunParameters(&context)[i];
        otava::symbols::TypeSymbol* type = parameter->GetReferredType(&context);
        if (type)
        {
            otava::intermediate::Value* local = emitter->EmitLocal(type->IrType(*emitter, node.GetSourcePos(), &context));
            emitter->SetIrObject(parameter, local);
        }
        else
        {
            otava::symbols::PrintWarning("type of parameter '" + util::ToUtf8(parameter->Name()) + "' not set", node.GetSourcePos(), &context);
        }
    }
    if (functionDefinition->ReturnsClass())
    {
        otava::symbols::ParameterSymbol* parameter = functionDefinition->ReturnValueParam();
        otava::symbols::TypeSymbol* type = parameter->GetReferredType(&context);
        if (type)
        {
            otava::intermediate::Value* local = emitter->EmitLocal(parameter->GetReferredType(&context)->IrType(*emitter, node.GetSourcePos(), &context));
            emitter->SetIrObject(parameter, local);
        }
        else
        {
            otava::symbols::PrintWarning("type of parameter '" + util::ToUtf8(parameter->Name()) + "' not set", node.GetSourcePos(), &context);
        }
    }
    int nlv = functionDefinition->LocalVariables().size();
    for (int i = 0; i < nlv; ++i)
    {
        otava::symbols::VariableSymbol* localVariable = functionDefinition->LocalVariables()[i];
        otava::symbols::TypeSymbol* type = localVariable->GetReferredType();
        if (type)
        {
            otava::intermediate::Value* local = emitter->EmitLocal(type->IrType(*emitter, node.GetSourcePos(), &context));
            emitter->SetIrObject(localVariable, local);
        }
        else
        {
            otava::symbols::PrintWarning("type of local variable '" + util::ToUtf8(localVariable->Name()) + "' not set", node.GetSourcePos(), &context);
        }
    }
    for (int i = 0; i < np; ++i)
    {
        otava::intermediate::Value* param = emitter->GetParam(i);
        otava::symbols::ParameterSymbol* parameter = functionDefinition->MemFunParameters(&context)[i];
        if (parameter->GetType()->IsClassTypeSymbol())
        {
            otava::symbols::ClassTypeSymbol* classTypeSymbol = static_cast<otava::symbols::ClassTypeSymbol*>(parameter->GetType());
            if (classTypeSymbol->CopyCtor())
            {
                otava::intermediate::FunctionType* copyCtorType = static_cast<otava::intermediate::FunctionType*>(classTypeSymbol->CopyCtor()->IrType(
                    *emitter, node.GetSourcePos(), &context));
                otava::intermediate::Function* copyCtor = emitter->GetOrInsertFunction(classTypeSymbol->CopyCtor()->IrName(&context), copyCtorType);
                std::vector<otava::intermediate::Value*> args;
                args.push_back(static_cast<otava::intermediate::Value*>(parameter->IrObject(*emitter, node.GetSourcePos(), &context)));
                args.push_back(param);
                emitter->EmitCall(copyCtor, args);
            }
            else
            {
                otava::symbols::ThrowException("class type '" + util::ToUtf8(classTypeSymbol->FullName()) + "' has no copy constructor needed by function '" +
                    util::ToUtf8(functionDefinition->FullName()) + "'", node.GetSourcePos(), &context);
            }
        }
        else
        {
            emitter->EmitStore(param, static_cast<otava::intermediate::Value*>(parameter->IrObject(*emitter, node.GetSourcePos(), &context)));
        }
    }
    if (functionDefinition->ReturnsClass())
    {
        otava::intermediate::Value* param = emitter->GetParam(np);
        otava::symbols::ParameterSymbol* parameter = functionDefinition->ReturnValueParam();
        emitter->EmitStore(param, static_cast<otava::intermediate::Value*>(parameter->IrObject(*emitter, node.GetSourcePos(), &context)));
    }
    otava::symbols::BoundCtorInitializerNode* ctorInitializer = node.CtorInitializer();
    if (ctorInitializer)
    {
        ctorInitializer->GenerateCode(*this, *emitter, &context);
    }
    otava::symbols::BoundDtorTerminatorNode* dtorTerminator = node.DtorTerminator();
    if (dtorTerminator)
    {
        for (const auto& setVPtrStatement : dtorTerminator->SetVPtrStatements())
        {
            setVPtrStatement->Accept(*this);
        }
    }
    node.Body()->Accept(*this);
    if (dtorTerminator)
    {
        dtorTerminator->GenerateCode(*this, *emitter, &context);
        for (const auto& setVPtrStatement : dtorTerminator->SetVPtrStatements())
        {
            setVPtrStatement->Accept(*this);
        }
    }
    StatementPrefix();
    otava::symbols::BoundStatementNode* lastStatement = nullptr;
    if (!node.Body()->Statements().empty())
    {
        lastStatement = node.Body()->Statements().back().get();
    }
    if (!lastStatement || !lastStatement->IsReturnOrSequenceReturnStatementNode() || lastStatement->IsReturnOrSequenceReturnStatementNode() && destructorCallGenerated)
    {
        if (functionDefinition->ReturnType() && !functionDefinition->ReturnType()->IsVoidType() && !functionDefinition->ReturnsClass())
        {
            otava::intermediate::Value* returnValue = functionDefinition->ReturnType()->DirectType(&context)->FinalType(node.GetSourcePos(), &context)->IrType(
                *emitter, node.GetSourcePos(), &context)->DefaultValue();
            emitter->EmitRet(returnValue);
            lastInstructionWasRet = true;
        }
        else
        {
            emitter->EmitRetVoid();
            lastInstructionWasRet = true;
        }
    }
    emitter->SetRegNumbers();
}

void CodeGenerator::Visit(otava::symbols::BoundCompoundStatementNode& node)
{
    otava::symbols::BoundCompoundStatementNode* prevBlock = currentBlock;
    currentBlock = &node;
    ++currentBlockId;
    while (currentBlockId >= blockExits.size()) blockExits.push_back(std::unique_ptr<BlockExit>());
    blockExits[currentBlockId].reset(new BlockExit());
    StatementPrefix();
    SetCurrentLineNumber(node.GetSourcePos());
    int n = node.Statements().size();
    for (int i = 0; i < n; ++i)
    {
        otava::symbols::BoundStatementNode* statement = node.Statements()[i].get();
        statement->Accept(*this);
        prevWasTerminator = statement->EndsWithTerminator();
    }
    if (!prevWasTerminator && !blockExits[currentBlockId]->IsEmpty())
    {
        ExitBlocks(currentBlockId, currentBlockId, node.GetSourcePos());
    }
    --currentBlockId;
    currentBlock = prevBlock;
}

void CodeGenerator::Visit(otava::symbols::BoundIfStatementNode& node)
{
    StatementPrefix();
    SetCurrentLineNumber(node.GetSourcePos());
    otava::intermediate::BasicBlock* prevTrueBlock = trueBlock;
    otava::intermediate::BasicBlock* prevFalseBlock = falseBlock;
    trueBlock = emitter->CreateBasicBlock();
    otava::intermediate::BasicBlock* nextBlock = emitter->CreateBasicBlock();
    if (node.ElseStatement())
    {
        falseBlock = emitter->CreateBasicBlock();
    }
    else
    {
        falseBlock = nextBlock;
    }
    bool prevGenJumpingBoolCode = genJumpingBoolCode;
    genJumpingBoolCode = true;
    node.GetCondition()->Accept(*this);
    genJumpingBoolCode = prevGenJumpingBoolCode;
    emitter->SetCurrentBasicBlock(trueBlock);
    prevWasTerminator = false;
    node.ThenStatement()->Accept(*this);
    if (!node.ThenStatement()->EndsWithTerminator())
    {
        emitter->EmitJump(nextBlock);
    }
    if (node.ElseStatement())
    {
        emitter->SetCurrentBasicBlock(falseBlock);
        prevWasTerminator = false;
        node.ElseStatement()->Accept(*this);
        emitter->EmitJump(nextBlock);
        emitter->SetCurrentBasicBlock(nextBlock);
    }
    else
    {
        emitter->SetCurrentBasicBlock(nextBlock);
    }
    basicBlockOpen = true;
    trueBlock = prevTrueBlock;
    falseBlock = prevFalseBlock;
}

void CodeGenerator::Visit(otava::symbols::BoundSwitchStatementNode& node)
{
    StatementPrefix();
    SetCurrentLineNumber(node.GetSourcePos());
    bool prevEmitLineNumbers = emitLineNumbers;
    emitLineNumbers = false;
    node.GetCondition()->Accept(*this);
    otava::intermediate::BasicBlock* prevDefaultBlock = defaultBlock;
    otava::intermediate::BasicBlock* prevBreakBlock = breakBlock;
    int prevBreakBlockId = breakBlockId;
    otava::intermediate::Value* condition = emitter->Stack().Pop();
    std::unique_ptr<SwitchTargets> switchTargets = CollectSwitchTargets(*emitter, node.Statement());
    otava::intermediate::BasicBlock* nextBlock = nullptr;
    if (switchTargets->Default())
    {
        defaultBlock = switchTargets->Default()->block;
        nextBlock = emitter->CreateBasicBlock();
    }
    else
    {
        nextBlock = emitter->CreateBasicBlock();
        defaultBlock = nextBlock;
    }
    breakBlock = nextBlock;
    breakBlockId = currentBlockId;
    otava::intermediate::SwitchInstruction* switchInst = emitter->EmitSwitch(condition, defaultBlock);
    int n = switchTargets->Cases().size();
    for (int i = 0; i < n; ++i)
    {
        const auto& caseTarget = switchTargets->Cases()[i];
        emitter->SetCurrentBasicBlock(caseTarget->block);
        for (const auto& expr : caseTarget->exprs)
        {
            EvaluateConstantExpr(*emitter, node.GetSourcePos(), context, expr);
            otava::intermediate::Value* caseValue = emitter->Stack().Pop();
            otava::intermediate::CaseTarget target(caseValue, caseTarget->block->Id());
            switchInst->AddCaseTarget(target);
        }
        prevWasTerminator = false;
        caseTarget->statement->Accept(*this);
        if (basicBlockOpen)
        {
            emitter->EmitJump(nextBlock);
            basicBlockOpen = false;
        }
/*
        if (!caseTarget->statement->EndsWithTerminator())
        {
            if (i < n - 1)
            {
                emitter->EmitJump(switchTargets->Cases()[i + 1]->block);
            }
            else
            {
                emitter->EmitJump(nextBlock);
            }
        }
*/
    }
    if (switchTargets->Default())
    {
        emitter->SetCurrentBasicBlock(defaultBlock);
        switchTargets->Default()->statement->Accept(*this);
        if (basicBlockOpen)
        {
            emitter->EmitJump(nextBlock);
            basicBlockOpen = false;
        }
/*
        if (!switchTargets->Default()->statement->EndsWithTerminator())
        {
            emitter->EmitJump(nextBlock);
        }
*/
    }
    emitter->SetCurrentBasicBlock(nextBlock);
    basicBlockOpen = true;
    defaultBlock = prevDefaultBlock;
    breakBlock = prevBreakBlock;
    breakBlockId = prevBreakBlockId;
    emitLineNumbers = prevEmitLineNumbers;
}

void CodeGenerator::Visit(otava::symbols::BoundCaseStatementNode& node)
{
    StatementPrefix();
    SetCurrentLineNumber(node.GetSourcePos());
    node.Statement()->Accept(*this);
}

void CodeGenerator::Visit(otava::symbols::BoundDefaultStatementNode& node)
{
    StatementPrefix();
    SetCurrentLineNumber(node.GetSourcePos());
    node.Statement()->Accept(*this);
}

void CodeGenerator::Visit(otava::symbols::BoundWhileStatementNode& node)
{
    StatementPrefix();
    SetCurrentLineNumber(node.GetSourcePos());
    otava::intermediate::BasicBlock* prevTrueBlock = trueBlock;
    otava::intermediate::BasicBlock* prevFalseBlock = falseBlock;
    otava::intermediate::BasicBlock* prevBreakBlock = breakBlock;
    int prevBreakBlockId = breakBlockId;
    otava::intermediate::BasicBlock* prevContinueBlock = continueBlock;
    int prevContinueBlockId = continueBlockId;
    trueBlock = emitter->CreateBasicBlock();
    falseBlock = emitter->CreateBasicBlock();
    breakBlock = falseBlock;
    breakBlockId = currentBlockId;
    otava::intermediate::BasicBlock* condBlock = emitter->CreateBasicBlock();
    emitter->EmitJump(condBlock);
    emitter->SetCurrentBasicBlock(condBlock);
    continueBlock = condBlock;
    continueBlockId = currentBlockId;
    bool prevGenJumpingBoolCode = genJumpingBoolCode;
    genJumpingBoolCode = true;
    node.GetCondition()->Accept(*this);
    genJumpingBoolCode = prevGenJumpingBoolCode;
    emitter->SetCurrentBasicBlock(trueBlock);
    node.Statement()->Accept(*this);
    emitter->EmitJump(condBlock);
    emitter->SetCurrentBasicBlock(falseBlock);
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
    SetCurrentLineNumber(node.GetSourcePos());
    otava::intermediate::BasicBlock* prevTrueBlock = trueBlock;
    otava::intermediate::BasicBlock* prevFalseBlock = falseBlock;
    otava::intermediate::BasicBlock* prevBreakBlock = breakBlock;
    int prevBreakBlockId = breakBlockId;
    otava::intermediate::BasicBlock* prevContinueBlock = continueBlock;
    int prevContinueBlockId = continueBlockId;
    otava::intermediate::BasicBlock* doBlock = emitter->CreateBasicBlock();
    otava::intermediate::BasicBlock* condBlock = emitter->CreateBasicBlock();
    trueBlock = doBlock;
    falseBlock = emitter->CreateBasicBlock();
    breakBlock = falseBlock;
    breakBlockId = currentBlockId;
    continueBlock = condBlock;
    continueBlockId = currentBlockId;
    emitter->EmitJump(doBlock);
    emitter->SetCurrentBasicBlock(doBlock);
    node.Statement()->Accept(*this);
    emitter->EmitJump(condBlock);
    emitter->SetCurrentBasicBlock(condBlock);
    bool prevGenJumpingBoolCode = genJumpingBoolCode;
    genJumpingBoolCode = true;
    node.GetExpr()->Accept(*this);
    genJumpingBoolCode = prevGenJumpingBoolCode;
    emitter->SetCurrentBasicBlock(falseBlock);
    basicBlockOpen = true;
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
    SetCurrentLineNumber(node.GetSourcePos());
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
    otava::intermediate::BasicBlock* condBlock = emitter->CreateBasicBlock();
    otava::intermediate::BasicBlock* actionBlock = emitter->CreateBasicBlock();
    otava::intermediate::BasicBlock* loopBlock = emitter->CreateBasicBlock();
    trueBlock = actionBlock;
    falseBlock = emitter->CreateBasicBlock();
    breakBlock = falseBlock;
    breakBlockId = currentBlockId;
    continueBlock = loopBlock;
    continueBlockId = currentBlockId;
    emitter->EmitJump(condBlock);
    emitter->SetCurrentBasicBlock(condBlock);
    bool prevGenJumpingBoolCode = genJumpingBoolCode;
    genJumpingBoolCode = true;
    if (node.GetCondition())
    {
        node.GetCondition()->Accept(*this);
    }
    else
    {
        emitter->EmitBool(true);
        GenJumpingBoolCode();
    }
    genJumpingBoolCode = prevGenJumpingBoolCode;
    emitter->SetCurrentBasicBlock(actionBlock);
    node.Statement()->Accept(*this);
    emitter->EmitJump(loopBlock);
    emitter->SetCurrentBasicBlock(loopBlock);
    if (node.GetLoopExpr())
    {
        node.GetLoopExpr()->Accept(*this);
    }
    emitter->EmitJump(condBlock);
    emitter->SetCurrentBasicBlock(falseBlock);
    basicBlockOpen = true;
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
    SetCurrentLineNumber(node.GetSourcePos());
    bool prevEmitLineNumbers = emitLineNumbers;
    emitLineNumbers = false;
    if (node.GetExpr())
    {
        node.GetExpr()->Accept(*this);
        otava::intermediate::Value* returnValue = emitter->Stack().Pop();
        if (sequenceSecond)
        {
            sequenceSecond->SetGenerated();
            sequenceSecond->Accept(*this);
        }
        ExitBlocks(currentBlockId, -1, node.GetSourcePos());
        emitter->EmitRet(returnValue);
        lastInstructionWasRet = true;
    }
    else
    {
        ExitBlocks(currentBlockId, -1, node.GetSourcePos());
        emitter->EmitRetVoid();
        lastInstructionWasRet = true;
    }
    otava::symbols::BoundCompoundStatementNode* body = boundFunction->Body();
    otava::symbols::BoundStatementNode* lastStatement = nullptr;
    if (!body->Statements().empty())
    {
        lastStatement = body->Statements().back().get();
    }
    if (lastStatement && lastStatement != &node)
    {
        otava::intermediate::BasicBlock* nextBlock = emitter->CreateBasicBlock();
        emitter->SetCurrentBasicBlock(nextBlock);
        basicBlockOpen = true;
        lastInstructionWasRet = false;
    }
    latestRet = &node;
    emitLineNumbers = prevEmitLineNumbers;
}

void CodeGenerator::Visit(otava::symbols::BoundBreakStatementNode& node)
{
    StatementPrefix();
    SetCurrentLineNumber(node.GetSourcePos());
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
    emitter->EmitJump(breakBlock);
    if (!otava::symbols::InDirectSwitchStatement(&node) || (latestRet && !latestRet->IsConditionalStatementInBlock(latestRet->Block())))
    {
        otava::intermediate::BasicBlock* nextBlock = emitter->CreateBasicBlock();
        emitter->SetCurrentBasicBlock(nextBlock);
        basicBlockOpen = true;
    }
}

void CodeGenerator::Visit(otava::symbols::BoundContinueStatementNode& node)
{
    StatementPrefix();
    SetCurrentLineNumber(node.GetSourcePos());
    ExitBlocks(currentBlockId, continueBlockId + 1, node.GetSourcePos());
    emitter->EmitJump(continueBlock);
}

void CodeGenerator::Visit(otava::symbols::BoundConstructionStatementNode& node)
{
    StatementPrefix();
    SetCurrentLineNumber(node.GetSourcePos());
    node.ConstructorCall()->Accept(*this);
    if (node.DestructorCall())
    {
        blockExits[currentBlockId]->AddDestructorCall(node.ReleaseDestructorCall());
    }
}

void CodeGenerator::Visit(otava::symbols::BoundExpressionStatementNode& node)
{
    if (!inLineNumberCode)
    {
        StatementPrefix();
        SetCurrentLineNumber(node.GetSourcePos());
    }
    if (!node.GetExpr()) return;
    node.GetExpr()->Accept(*this);
    if (node.GetExpr()->HasValue())
    {
        emitter->Stack().Pop();
    }
}

void CodeGenerator::Visit(otava::symbols::BoundSetVPtrStatementNode& node)
{
    StatementPrefix();
    SetCurrentLineNumber(node.GetSourcePos());
    node.ThisPtr()->Load(*emitter, otava::symbols::OperationFlags::none, node.GetSourcePos(), &context);
    otava::intermediate::Value* thisPtr = emitter->Stack().Pop();
    otava::symbols::TypeSymbol* thisPtrType = node.ThisPtr()->GetType()->GetBaseType();
    if (thisPtrType->IsClassTypeSymbol())
    {
        otava::symbols::ClassTypeSymbol* classType = static_cast<otava::symbols::ClassTypeSymbol*>(thisPtrType);
        std::int32_t vptrIndex = classType->VPtrIndex();
        otava::symbols::ClassTypeSymbol* forClass = node.GetClass();
        otava::intermediate::Value* ptr = emitter->EmitElemAddr(thisPtr, emitter->EmitLong(vptrIndex));
        otava::intermediate::Value* vptr = emitter->EmitBitcast(forClass->GetVTabVariable(*emitter, &context), 
            emitter->MakePtrType(emitter->GetVoidType()));
        emitter->EmitStore(vptr, ptr);
        otava::symbols::ClassTypeSymbol* vptrHolderClass = node.GetVPtrHolderClass();
        auto [succeeded, delta] = otava::symbols::Delta(vptrHolderClass, forClass, *emitter, &context);
        if (!succeeded)
        {
            otava::symbols::ThrowException("classes '" + util::ToUtf8(forClass->FullName()) + "' and '" + util::ToUtf8(vptrHolderClass->FullName()) +
                "' have no inheritance relationship", node.GetSourcePos(), &context);
        }
        std::int32_t deltaIndex = classType->DeltaIndex();
        otava::intermediate::Value* deltaPtrElem = emitter->EmitElemAddr(thisPtr, emitter->EmitLong(deltaIndex));
        otava::intermediate::Value* deltaPtr = emitter->EmitBitcast(deltaPtrElem, emitter->MakePtrType(emitter->GetLongType()));
        otava::intermediate::Value* deltaValue = emitter->EmitLong(delta);
        emitter->EmitStore(deltaValue, deltaPtr);
    }
    else
    {
        otava::symbols::ThrowException("class type symbol expected", node.GetSourcePos(), &context);
    }
}

void CodeGenerator::Visit(otava::symbols::BoundLiteralNode& node)
{
    SetCurrentLineNumber(node.GetSourcePos());
    if (inLineNumberCode)
    {
        node.SetValue(context.GetEvaluationContext()->GetIntegerValue(line, util::ToUtf32(std::to_string(line)), 
            context.GetSymbolTable()->GetFundamentalTypeSymbol(otava::symbols::FundamentalTypeKind::intType)));
    }
    else
    {
        node.Load(*emitter, otava::symbols::OperationFlags::none, node.GetSourcePos(), &context);
    }
    GenJumpingBoolCode();
}

void CodeGenerator::Visit(otava::symbols::BoundStringLiteralNode& node)
{
    SetCurrentLineNumber(node.GetSourcePos());
    node.Load(*emitter, otava::symbols::OperationFlags::none, node.GetSourcePos(), &context);
    GenJumpingBoolCode();
}

void CodeGenerator::Visit(otava::symbols::BoundVariableNode& node)
{
    SetCurrentLineNumber(node.GetSourcePos());
    node.Load(*emitter, otava::symbols::OperationFlags::none, node.GetSourcePos(), &context);
    GenJumpingBoolCode();
}

void CodeGenerator::Visit(otava::symbols::BoundParameterNode& node)
{
    SetCurrentLineNumber(node.GetSourcePos());
    node.Load(*emitter, otava::symbols::OperationFlags::none, node.GetSourcePos(), &context);
    GenJumpingBoolCode();
}

void CodeGenerator::Visit(otava::symbols::BoundEnumConstant& node)
{
    SetCurrentLineNumber(node.GetSourcePos());
    node.Load(*emitter, otava::symbols::OperationFlags::none, node.GetSourcePos(), &context);
    GenJumpingBoolCode();
}

void CodeGenerator::Visit(otava::symbols::BoundMemberExprNode& node)
{
    SetCurrentLineNumber(node.GetSourcePos());
    node.Load(*emitter, otava::symbols::OperationFlags::none, node.GetSourcePos(), &context);
    GenJumpingBoolCode();
}

void CodeGenerator::Visit(otava::symbols::BoundFunctionCallNode& node)
{
    SetCurrentLineNumber(node.GetSourcePos());
    node.Load(*emitter, otava::symbols::OperationFlags::none, node.GetSourcePos(), &context);
    if (node.IsNoReturnFunctionCall())
    {
        EmitReturn(node.GetSourcePos());
    }
    GenJumpingBoolCode();
}

void CodeGenerator::Visit(otava::symbols::BoundFunctionPtrCallNode& node)
{
    SetCurrentLineNumber(node.GetSourcePos());
    node.Load(*emitter, otava::symbols::OperationFlags::none, node.GetSourcePos(), &context);
    GenJumpingBoolCode();
}

void CodeGenerator::Visit(otava::symbols::BoundExpressionSequenceNode& node)
{
    SetCurrentLineNumber(node.GetSourcePos());
    node.Load(*emitter, otava::symbols::OperationFlags::none, node.GetSourcePos(), &context);
    GenJumpingBoolCode();
}

void CodeGenerator::Visit(otava::symbols::BoundConversionNode& node)
{
    SetCurrentLineNumber(node.GetSourcePos());
    node.Load(*emitter, otava::symbols::OperationFlags::none, node.GetSourcePos(), &context);
    GenJumpingBoolCode();
}

void CodeGenerator::Visit(otava::symbols::BoundAddressOfNode& node)
{
    SetCurrentLineNumber(node.GetSourcePos());
    node.Load(*emitter, otava::symbols::OperationFlags::none, node.GetSourcePos(), &context);
    GenJumpingBoolCode();
}

void CodeGenerator::Visit(otava::symbols::BoundDereferenceNode& node)
{
    SetCurrentLineNumber(node.GetSourcePos());
    node.Load(*emitter, otava::symbols::OperationFlags::none, node.GetSourcePos(), &context);
    GenJumpingBoolCode();
}

void CodeGenerator::Visit(otava::symbols::BoundPtrToRefNode& node)
{
    SetCurrentLineNumber(node.GetSourcePos());
    node.Load(*emitter, otava::symbols::OperationFlags::none, node.GetSourcePos(), &context);
    GenJumpingBoolCode();
}

void CodeGenerator::Visit(otava::symbols::BoundConstructTemporaryNode& node)
{
    SetCurrentLineNumber(node.GetSourcePos());
    node.Load(*emitter, otava::symbols::OperationFlags::none, node.GetSourcePos(), &context);
    GenJumpingBoolCode();
}

void CodeGenerator::Visit(otava::symbols::BoundConstructExpressionNode& node)
{
    SetCurrentLineNumber(node.GetSourcePos());
    node.Load(*emitter, otava::symbols::OperationFlags::none, node.GetSourcePos(), &context);
    GenJumpingBoolCode();
}

void CodeGenerator::Visit(otava::symbols::BoundDefaultInitNode& node)
{
    SetCurrentLineNumber(node.GetSourcePos());
    node.Load(*emitter, otava::symbols::OperationFlags::none, node.GetSourcePos(), &context);
    GenJumpingBoolCode();
}

void CodeGenerator::Visit(otava::symbols::BoundTemporaryNode& node)
{
    SetCurrentLineNumber(node.GetSourcePos());
    node.Load(*emitter, otava::symbols::OperationFlags::none, node.GetSourcePos(), &context);
    GenJumpingBoolCode();
}

void CodeGenerator::Visit(otava::symbols::BoundConjunctionNode& boundConjunction)
{
    SetCurrentLineNumber(boundConjunction.GetSourcePos());
    if (genJumpingBoolCode)
    {
        otava::intermediate::BasicBlock* rightBlock = emitter->CreateBasicBlock();
        otava::intermediate::BasicBlock* prevTrueBlock = trueBlock;
        trueBlock = rightBlock;
        boundConjunction.Left()->Accept(*this);
        trueBlock = prevTrueBlock;
        emitter->SetCurrentBasicBlock(rightBlock);
        boundConjunction.Right()->Accept(*this);
    }
    else
    {
        boundConjunction.Load(*emitter, otava::symbols::OperationFlags::none, boundConjunction.GetSourcePos(), &context);
    }
}

void CodeGenerator::Visit(otava::symbols::BoundDisjunctionNode& boundDisjunction)
{
    SetCurrentLineNumber(boundDisjunction.GetSourcePos());
    if (genJumpingBoolCode)
    {
        otava::intermediate::BasicBlock* rightBlock = emitter->CreateBasicBlock();
        otava::intermediate::BasicBlock* prevFalseBlock = falseBlock;
        falseBlock = rightBlock;
        boundDisjunction.Left()->Accept(*this);
        emitter->SetCurrentBasicBlock(rightBlock);
        falseBlock = prevFalseBlock;
        boundDisjunction.Right()->Accept(*this);
    }
    else
    {
        boundDisjunction.Load(*emitter, otava::symbols::OperationFlags::none, boundDisjunction.GetSourcePos(), &context);
    }
}

void CodeGenerator::Visit(otava::symbols::BoundConditionalExprNode& boundConditionalExpr)
{
    SetCurrentLineNumber(boundConditionalExpr.GetSourcePos());
    boundConditionalExpr.Load(*emitter, otava::symbols::OperationFlags::none, boundConditionalExpr.GetSourcePos(), &context);
}

void CodeGenerator::Visit(otava::symbols::BoundGlobalVariableDefinitionNode& node)
{
    SetCurrentLineNumber(node.GetSourcePos());
    otava::symbols::VariableSymbol* variable = node.GetGlobalVariable();
    otava::symbols::TypeSymbol* type = otava::symbols::ResolveFwdDeclaredType(variable->GetType(), node.GetSourcePos(), &context);
    if (type->IsForwardClassDeclarationSymbol()) return;
    variable->SetDeclaredType(type);
    otava::intermediate::Value* initializer = nullptr;
    otava::intermediate::Type* irType = variable->GetType()->IrType(*emitter, node.GetSourcePos(), &context);
    if (variable->GetValue() && !variable->GetType()->IsClassTypeSymbol())
    {
        std::unique_ptr<otava::symbols::Value> clonedVariableValue = otava::symbols::CloneAndSetType(variable->GetValue(), variable->GetType());
        initializer = clonedVariableValue->IrValue(*emitter, node.GetSourcePos(), &context);
    }
    else
    {
        initializer = irType->MakeDefaultValue(*emitter->GetIntermediateContext());
    }
    otava::intermediate::Value* irVariable = emitter->EmitGlobalVariable(irType, variable->IrName(&context), initializer);
    emitter->SetIrObject(variable, irVariable);
}

void CodeGenerator::Visit(otava::symbols::BoundGotoStatementNode& node)
{
    otava::intermediate::BasicBlock* bb = node.GetBB(*emitter);
    emitter->EmitJump(bb);
}

void CodeGenerator::Visit(otava::symbols::BoundLabeledStatementNode& node)
{
    otava::intermediate::BasicBlock* bb = node.GetBB(*emitter);
    emitter->EmitJump(bb);
    emitter->SetCurrentBasicBlock(bb);
    basicBlockOpen = true;
    node.Stmt()->Accept(*this);
}

std::string GenerateCode(otava::symbols::Context& context, const std::string& config, int optLevel, bool verbose, std::string& mainIrName, 
    int& mainFunctionParams, bool globalMain, const std::vector<std::string>& compileUnitInitFnNames)
{
    CodeGenerator codeGenerator(context, config, optLevel, verbose, mainIrName, mainFunctionParams, globalMain, compileUnitInitFnNames);
    context.GetBoundCompileUnit()->Accept(codeGenerator);
    return codeGenerator.GetAsmFileName();
}

} // namespace otava::codegen
