// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.codegen;

import otava.symbols.emitter;
import otava.symbols.function.kind;
import otava.symbols.function.symbol;
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
import otava.symbols.error;
import otava.symbols.type.symbol;
import otava.symbols.value;
import otava.symbols.variable.symbol;
import otava.symbols.modules;
import otava.symbols.overload.resolution;
import otava.symbols.symbol.table;
import otava.symbols.enums;
import otava.opt;
import std;
import util;

namespace otava::codegen {

struct SwitchTarget
{
    SwitchTarget(otava::intermediate::BasicBlock* block_, otava::symbols::BoundStatementNode* statement_, 
        const std::vector<otava::symbols::BoundExpressionNode*>& exprs_);
    otava::intermediate::BasicBlock* block;
    otava::symbols::BoundStatementNode* statement;
    std::vector<otava::symbols::BoundExpressionNode*> exprs;
};

SwitchTarget::SwitchTarget(otava::intermediate::BasicBlock* block_, otava::symbols::BoundStatementNode* statement_, 
    const std::vector<otava::symbols::BoundExpressionNode*>& exprs_) :
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
    if (!Valid()) return;
    auto irv = node.GetValue()->IrValue(emitter, sourcePos, &context);
    if (!irv)
    {
        SetError(irv.error());
        return;
    }
    otava::intermediate::Value* irValue = *irv;
    emitter.Stack().Push(irValue);
}

void ConstantExpressionEvaluator::Visit(otava::symbols::BoundEnumConstant& node)
{
    if (!Valid()) return;
    auto irv = node.EnumConstant()->GetValue()->IrValue(emitter, sourcePos, &context);
    if (!irv)
    {
        SetError(irv.error());
        return;
    }
    otava::intermediate::Value* irValue = *irv;
    emitter.Stack().Push(irValue);
}

void ConstantExpressionEvaluator::Visit(otava::symbols::BoundVariableNode& node)
{
    if (!Valid()) return;
    otava::symbols::VariableSymbol* variable = node.GetVariable();
    otava::symbols::Value* value = variable->GetValue();
    if (!value)
    {
        std::unexpected<int> result = otava::symbols::Error("cannot evaluate statically", sourcePos, &context);
        SetError(result.error());
        return;
    }
    auto irv = value->IrValue(emitter, sourcePos, &context);
    if (!irv)
    {
        SetError(irv.error());
        return;
    }
    otava::intermediate::Value* irValue = *irv;
    emitter.Stack().Push(irValue);
}

void ConstantExpressionEvaluator::Visit(otava::symbols::BoundConversionNode& node)
{
    if (!Valid()) return;
    node.Subject()->Accept(*this);
    if (!Valid()) return;
    otava::intermediate::Value* value = emitter.Stack().Pop();
    if (value->IsIntegerValue())
    {
        std::int64_t val = value->GetIntegerValue();
        auto irt = node.GetType()->IrType(emitter, sourcePos, &context);
        if (!irt)
        {
            SetError(irt.error());
            return;
        }
        otava::intermediate::Type* type = *irt;
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
                    std::unexpected<int> result = otava::symbols::Error("cannot evaluate statically", sourcePos, &context);
                    SetError(result.error());
                    return;
                }
            }
            emitter.Stack().Push(value);
        }
        else
        {
            std::unexpected<int> result = otava::symbols::Error("cannot evaluate statically", sourcePos, &context);
            SetError(result.error());
            return;
        }
    }
    else
    {
        std::unexpected<int> result = otava::symbols::Error("cannot evaluate statically", sourcePos, &context);
        SetError(result.error());
        return;
    }
}

std::expected<bool, int> EvaluateConstantExpr(otava::symbols::Emitter& emitter, const soul::ast::SourcePos& sourcePos, otava::symbols::Context& context,
    otava::symbols::BoundExpressionNode* constantExpr)
{
    ConstantExpressionEvaluator evaluator(emitter, sourcePos, context);
    constantExpr->Accept(evaluator);
    if (emitter.Stack().IsEmpty())
    {
        std::unexpected<int> result = otava::symbols::Error("cannot evaluate statically", sourcePos, &context);
        return std::unexpected<int>(result.error());
    }
    if (!evaluator) return std::unexpected<int>(evaluator.GetError());
    return std::expected<bool, int>(true);
}

class BlockExit
{
public:
    BlockExit();
    bool IsEmpty() const { return destructorCalls.empty(); }
    int Size() const { return destructorCalls.size(); }
    void AddDestructorCall(otava::symbols::BoundFunctionCallNode* destructorCall);
    std::expected<bool, int> Execute(otava::symbols::Emitter& emitter, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context, bool reset);
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

std::expected<bool, int> BlockExit::Execute(otava::symbols::Emitter& emitter, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context, bool reset)
{
    int n = destructorCalls.size();
    for (int i = n - 1; i >= 0; --i)
    {
        otava::symbols::BoundFunctionCallNode* destructorCall = destructorCalls[i].get();
        auto rv = destructorCall->Load(emitter, otava::symbols::OperationFlags::none, sourcePos, context);
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
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
    void Visit(otava::symbols::BoundGlobalVariableDefinitionNode& node) override;
private:
    void StatementPrefix();
    void GenJumpingBoolCode();
    void SetCurrentLineNumber(const soul::ast::SourcePos& sourcePos);
    std::expected<bool, int> AddClassInfo(otava::symbols::ClassTypeSymbol* cls);
    std::expected<bool, int> GenerateVTab(otava::symbols::ClassTypeSymbol* cls, const soul::ast::SourcePos& sourcePos);
    std::expected<bool, int> EmitReturn(const soul::ast::SourcePos& sourcePos);
    std::expected<bool, int> ExitBlocks(int sourceBlockId, int targetBlockId, const soul::ast::SourcePos& sourcePos);
    std::expected<bool, int> GenerateGlobalInitializationFunction();
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
    context(context_), emitter(context.GetEmitter()), config(config_), optLevel(optLevel_), verbose(verbose_), line(0),
    mainIrName(mainIrName_), mainFunctionParams(mainFunctionParams_),
    functionDefinition(nullptr), entryBlock(nullptr), trueBlock(nullptr), falseBlock(nullptr), defaultBlock(nullptr), breakBlock(nullptr),
    breakBlockId(-1), continueBlock(nullptr), continueBlockId(-1), genJumpingBoolCode(false), lastInstructionWasRet(false),
    prevWasTerminator(false), basicBlockOpen(false), destructorCallGenerated(false), sequenceSecond(nullptr), currentBlockId(-1), globalMain(globalMain_),
    compileUnitInitFnNames(compileUnitInitFnNames_), latestRet(nullptr), boundFunction(nullptr), currentBlock(nullptr), inLineNumberCode(false), 
    emitLineNumbers(false)
{
    std::string intermediateCodeFilePath;
    if (config == "release")
    {
        auto fp = util::GetFullPath(
            util::Path::Combine(
                util::Path::Combine(util::Path::Combine(util::Path::GetDirectoryName(context.FileName()), config),
                    std::to_string(otava::symbols::GetOptLevel(optLevel, true))), util::Path::GetFileName(context.FileName()) + ".i"));
        if (!fp)
        {
            SetError(fp.error());
            return;
        }
        intermediateCodeFilePath = *fp;
    }
    else
    {
        auto fp = util::GetFullPath(
            util::Path::Combine(
                util::Path::Combine(util::Path::GetDirectoryName(context.FileName()), config),
                util::Path::GetFileName(context.FileName()) + ".i"));
        if (!fp)
        {
            SetError(fp.error());
            return;
        }
        intermediateCodeFilePath = *fp;
    }
    emitter->SetFilePath(intermediateCodeFilePath);
    ort_create_directories(intermediateCodeFilePath.c_str());
    if (config == "release")
    {
        auto fp = util::GetFullPath(
            util::Path::Combine(util::Path::Combine(util::Path::Combine(util::Path::GetDirectoryName(context.FileName()), config),
                std::to_string(otava::symbols::GetOptLevel(optLevel, true))), util::Path::GetFileName(context.FileName()) + ".opt.i"));
        if (!fp)
        {
            SetError(fp.error());
            return;
        }
        optimizedIntermediateFilePath = *fp;
    }
    else
    {
        auto fp = util::GetFullPath(
            util::Path::Combine(util::Path::Combine(util::Path::GetDirectoryName(context.FileName()), config),
                util::Path::GetFileName(context.FileName()) + ".opt.i"));
        if (!fp)
        {
            SetError(fp.error());
            return;
        }
        optimizedIntermediateFilePath = *fp;
    }
}

void CodeGenerator::Reset()
{
    if (!Valid()) return;
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
    emitLineNumbers = !context.ReleaseConfig();
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
    if (!Valid()) return;
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

std::expected<bool, int> CodeGenerator::AddClassInfo(otava::symbols::ClassTypeSymbol* cls)
{
    std::set<const otava::symbols::Symbol*> visited;
    if (cls->IsTemplate() || cls->IsTemplateParameterInstantiation(&context, visited)) return std::expected<bool, int>(false);
    std::uint64_t clsidh = 0;
    std::uint64_t clsidl = 0;
    util::UuidToInts(cls->Id(), clsidh, clsidl);
    otava::symbols::class_id id = std::make_pair(clsidh, clsidl);
    otava::symbols::SymbolTable* symbolTable = context.GetSymbolTable();
    otava::symbols::class_index& index = symbolTable->ClassIndex();
    if (index.get_class_info(id)) return std::expected<bool, int>(false);
    std::expected<otava::intermediate::Type*, int> rv = cls->IrType(*emitter, soul::ast::SourcePos(), &context);
    if (!rv) return std::unexpected<int>(rv.error());
    otava::intermediate::Type* clsType = *rv;
    otava::symbols::ClassKind kind = cls->GetClassKind();
    otava::symbols::class_key key = otava::symbols::class_key::cls;
    switch (kind)
    {
        case otava::symbols::ClassKind::class_: { key = otava::symbols::class_key::cls; break; }
        case otava::symbols::ClassKind::struct_: { key = otava::symbols::class_key::strct; break; }
        case otava::symbols::ClassKind::union_: { key = otava::symbols::class_key::uni; break; }
    }
    std::expected<std::u32string, int> fname = cls->FullName();
    if (!fname) return std::unexpected<int>(fname.error());
    std::expected<std::string, int> sfname = util::ToUtf8(*fname);
    if (!sfname) return std::unexpected<int>(sfname.error());
    std::unique_ptr<otava::symbols::class_info> info(new otava::symbols::class_info(id, key, *sfname, clsType->Size()));
    for (otava::symbols::ClassTypeSymbol* base : cls->BaseClasses())
    {
        std::uint64_t h = 0;
        std::uint64_t l = 0;
        util::UuidToInts(base->Id(), h, l);
        info->add_base(std::make_pair(h, l));
    }
    index.add_class(info);
    return std::expected<bool, int>(true);
}

std::expected<bool, int> CodeGenerator::GenerateVTab(otava::symbols::ClassTypeSymbol* cls, const soul::ast::SourcePos& sourcePos)
{
    if (!Valid()) return std::unexpected<int>(GetError());
    if (!cls->IsPolymorphic()) return std::expected<bool, int>(false);
    if (!cls->IsClassTemplateSpecializationSymbol())
    {
        if (cls->GetFlag(otava::symbols::ClassTypeSymbolFlags::vtabGenerated)) return std::expected<bool, int>(false);
        cls->SetFlag(otava::symbols::ClassTypeSymbolFlags::vtabGenerated);
    }
    auto rv = cls->ComputeVTabName(&context);
    if (!rv) return rv;
    std::string vtabName = cls->VTabName(&context);
    if (emittedVTabNames.find(vtabName) != emittedVTabNames.end()) return std::expected<bool, int>(false);
    emittedVTabNames.insert(vtabName);
    context.SetFlag(otava::symbols::ContextFlags::generatingVTab);
    rv = cls->MakeVTab(&context, sourcePos);
    if (!rv) return rv;
    std::expected<otava::intermediate::Type*, int> t = emitter->MakePtrType(emitter->GetVoidType());
    if (!t) return std::unexpected<int>(t.error());
    otava::intermediate::Type* voidPtrIrType = *t;
    t = emitter->MakeArrayType(cls->VTab().size() * 2 + otava::symbols::vtabClassIdElementCount, voidPtrIrType);
    if (!t) return std::unexpected<int>(t.error());
    otava::intermediate::Type* arrayType = *t;
    t = emitter->MakePtrType(arrayType);
    if (!t) return std::unexpected<int>(t.error());
    otava::intermediate::Type* arrayPtrType = *t;
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
            t = functionSymbol->IrType(*emitter, sourcePos, &context);
            if (!t) return std::unexpected<int>(t.error());
            otava::intermediate::Type* irType = *t;
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
                    std::expected<std::string, int> irn = functionSymbol->IrName(&context);
                    if (!irn) return std::unexpected<int>(irn.error());
                    std::string irName = std::move(*irn);
                    std::expected<otava::intermediate::Function*, int> fn = emitter->GetOrInsertFunction(irName, functionType);
                    if (!fn) return std::unexpected<int>(fn.error());
                    otava::intermediate::Value* functionValue = emitter->EmitSymbolValue(functionType, irName);
                    std::expected<std::int64_t, int> p = otava::symbols::Delta(cls, functionSymbol->ParentClassType(), *emitter, &context);
                    if (!p)
                    {
                        auto fname = cls->FullName();
                        if (!fname) return std::unexpected<int>(fname.error());
                        auto sfname = util::ToUtf8(*fname);
                        if (!sfname) return std::unexpected<int>(sfname.error());
                        auto pfname = functionSymbol->ParentClassType()->FullName();
                        if (!pfname) return std::unexpected<int>(pfname.error());
                        auto spfname = util::ToUtf8(*pfname);
                        if (!spfname) return std::unexpected<int>(spfname.error());
                        return otava::symbols::Error("could not resolve delta for classes '" + *sfname + "' and '" + *spfname + "'", sourcePos, &context);
                    }
                    std::int64_t delta = *p;
                    otava::intermediate::Value* deltaValue = emitter->EmitLong(delta);
                    otava::intermediate::Value* element1Value = emitter->EmitConversionValue(voidPtrIrType, functionValue);
                    elements.push_back(element1Value);
                    otava::intermediate::Value* element2Value = emitter->EmitConversionValue(voidPtrIrType, deltaValue);
                    elements.push_back(element2Value);
                }
            }
            else
            {
                return otava::symbols::Error("function type expected", sourcePos, &context);
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
    std::expected<otava::intermediate::Value*, int> v = emitter->EmitGlobalVariable(arrayType, vtabName, arrayValue);
    if (!v) return std::unexpected<int>(v.error());
    otava::intermediate::Value* vtabVariable = *v;
    auto fname = cls->FullName();
    if (!fname) return std::unexpected<int>(fname.error());
    emitter->SetVTabVariable(*fname, vtabVariable);
    context.ResetFlag(otava::symbols::ContextFlags::generatingVTab);
    for (const auto& boundVTabFunction : context.BoundVTabFunctions())
    {
        boundVTabFunction->Accept(*this);
    }
    context.ClearBoundVTabFunctions();
    return std::expected<bool, int>(true);
}

std::expected<bool, int> CodeGenerator::ExitBlocks(int sourceBlockId, int targetBlockId, const soul::ast::SourcePos& sourcePos)
{
    if (!Valid()) return std::unexpected<int>(GetError());
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
    if (lastStatement && currentBlockLastStatement && lastStatement == currentBlockLastStatement && currentBlockLastStatement->IsReturnStatementNode())
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
                        auto rv = exit->Execute(*emitter, sourcePos, &context, false);
                        if (!rv) return rv;
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
                        auto rv = exit->Execute(*emitter, sourcePos, &context, true);
                        if (!rv) return rv;
                        destructorCallGenerated = true;
                    }
                }
            }
        }
    }
    emitLineNumbers = prevEmitLineNumbers;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> CodeGenerator::EmitReturn(const soul::ast::SourcePos& sourcePos)
{
    if (!Valid()) return std::unexpected<int>(GetError());
    if (functionDefinition->ReturnType() && !functionDefinition->ReturnType()->IsVoidType() && !functionDefinition->ReturnsClass())
    {
        std::expected<otava::symbols::TypeSymbol*, int> d = functionDefinition->ReturnType()->DirectType(&context);
        if (!d) return std::unexpected<int>(d.error());
        otava::symbols::TypeSymbol* dt = *d;
        d = dt->FinalType(sourcePos, &context);
        if (!d) return std::unexpected<int>(d.error());
        otava::symbols::TypeSymbol* ft = *d;
        std::expected<otava::intermediate::Type*, int> irt = ft->IrType(*emitter, sourcePos, &context);
        if (!irt) return std::unexpected<int>(irt.error());
        otava::intermediate::Type* irType = *irt;
        otava::intermediate::Value* returnValue = irType->DefaultValue();
        emitter->EmitRet(returnValue);
    }
    else
    {
        emitter->EmitRetVoid();
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> CodeGenerator::GenerateGlobalInitializationFunction()
{
    if (!Valid()) return std::unexpected<int>(GetError());
    Reset();
    std::expected<otava::intermediate::Type*, int> f = emitter->MakeFunctionType(emitter->GetVoidType(), std::vector<otava::intermediate::Type*>());
    if (!f) return std::unexpected<int>(f.error());
    otava::intermediate::Type* ft = *f;
    std::expected<otava::intermediate::Function*, int> fn = emitter->CreateFunction("__global_init__", ft, false, false);
    if (!fn) return std::unexpected<int>(fn.error());
    otava::intermediate::BasicBlock* initBlock = emitter->CreateBasicBlock();
    emitter->SetCurrentBasicBlock(initBlock);
    f = emitter->MakeFunctionType(emitter->GetVoidType(), std::vector<otava::intermediate::Type*>());
    if (!f) return std::unexpected<int>(f.error());
    ft = *f;
    otava::intermediate::FunctionType* initFunctionType = static_cast<otava::intermediate::FunctionType*>(ft);
    int n = compileUnitInitFnNames.size();
    for (int i = 0; i < n; ++i)
    {
        std::string initFnName = compileUnitInitFnNames[i];
        std::expected<otava::intermediate::Function*, int> f = emitter->GetOrInsertFunction(initFnName, initFunctionType);
        if (!f) return std::unexpected<int>(f.error());
        otava::intermediate::Function* initFn = *f;
        std::expected<otava::intermediate::Value*, int> c = emitter->EmitCall(initFn, std::vector<otava::intermediate::Value*>());
        if (!c) return std::unexpected<int>(c.error());
    }
    emitter->EmitRetVoid();
    return std::expected<bool, int>(true);
}

void CodeGenerator::Visit(otava::symbols::BoundCompileUnitNode& node)
{
    context.PushSetFlag(otava::symbols::ContextFlags::requireForwardResolved);
    if (globalMain)
    {
        auto rv = GenerateGlobalInitializationFunction();
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
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
    auto rv = emitter->ResolveReferences();
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    rv = emitter->Emit();
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    otava::intermediate::Context intermediateContext;
    otava::intermediate::Context optimizationContext;
    otava::intermediate::Context* finalContext = &intermediateContext;
    rv = otava::intermediate::Parse(emitter->FilePath(), intermediateContext, verbose);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    rv = otava::intermediate::Verify(intermediateContext);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    std::string assemblyFilePath;
    if (config == "release")
    {
        auto fp = util::GetFullPath(
            util::Path::Combine(
                util::Path::Combine(util::Path::Combine(util::Path::GetDirectoryName(context.FileName()), config),
                    std::to_string(otava::symbols::GetOptLevel(optLevel, true))),
                util::Path::GetFileName(context.FileName()) + ".asm"));
        if (!fp)
        {
            SetError(fp.error());
            return;
        }
        assemblyFilePath = *fp;
    }
    else
    {
        auto fp = util::GetFullPath(
            util::Path::Combine(
                util::Path::Combine(util::Path::GetDirectoryName(context.FileName()), config),
                util::Path::GetFileName(context.FileName()) + ".asm"));
        if (!fp)
        {
            SetError(fp.error());
            return;
        }
        assemblyFilePath = *fp;
    }
    std::unique_ptr<otava::intermediate::CodeGenerator> codeGenerator;
    if (context.ReleaseConfig())
    {
        intermediateContext.SetFilePath(optimizedIntermediateFilePath);
        rv = otava::optimizer::Optimize(&intermediateContext);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = intermediateContext.WriteFile();
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = otava::intermediate::Parse(optimizedIntermediateFilePath, optimizationContext, verbose);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = otava::intermediate::Verify(optimizationContext);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        finalContext = &optimizationContext;
        codeGenerator.reset(new otava::optimizer::OptimizingCodeGenerator(finalContext, assemblyFilePath));
    }
    else
    {
        codeGenerator.reset(new otava::intermediate::CodeGenerator(finalContext, assemblyFilePath));
    }
    rv = otava::intermediate::GenerateCode(*finalContext, *codeGenerator, verbose);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    asmFileName = util::Path::GetFileName(context.FileName()) + ".asm";
    context.PopFlags();
    context.SetTotalFunctionsCompiled(context.TotalFunctionsCompiled() + intermediateContext.TotalFunctions());
    context.SetTotalFunctionsCompiled(context.TotalFunctionsCompiled() + optimizationContext.TotalFunctions());
    context.SetFunctionsInlined(context.FunctionsInlined() + intermediateContext.FunctionsInlined());
    context.SetFunctionsInlined(context.FunctionsInlined() + optimizationContext.FunctionsInlined());
    context.SetFunctionCallsInlined(context.FunctionCallsInlined() + intermediateContext.InlinedFunctionCalls());
    context.SetFunctionCallsInlined(context.FunctionCallsInlined() + optimizationContext.InlinedFunctionCalls());
    for (otava::symbols::ClassTypeSymbol* cls : context.GetSymbolTable()->Classes())
    {
        rv = AddClassInfo(cls);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
    }
}

void CodeGenerator::Visit(otava::symbols::BoundClassNode& node)
{
    otava::symbols::ClassTypeSymbol* cls = node.GetClass();
    auto rv = cls->MakeObjectLayout(soul::ast::SourcePos(), &context);
    if (!rv)
    {
        SetError(rv.error());
    }
    rv = GenerateVTab(cls, node.GetSourcePos());
    if (!rv)
    {
        SetError(rv.error());
    }
}

void CodeGenerator::Visit(otava::symbols::BoundFunctionNode& node)
{
    boundFunction = &node;
    functionDefinition = node.GetFunctionDefinitionSymbol();
    auto fullname = functionDefinition->FullName();
    if (!fullname)
    {
        SetError(fullname.error());
        return;
    }
    auto sfullname = util::ToUtf8(*fullname);
    if (!sfullname)
    {
        SetError(sfullname.error());
        return;
    }
    if ((functionDefinition->Qualifiers() & otava::symbols::FunctionQualifiers::isDeleted) != otava::symbols::FunctionQualifiers::none)
    {
        return;
    }
    std::expected<std::string, int> irn = functionDefinition->IrName(&context);
    if (!irn)
    {
        SetError(irn.error());
        return;
    }
    std::string irName = std::move(*irn);
    if (functionDefinition->Name() == U"main")
    {
        mainIrName = irName;;
        mainFunctionParams = functionDefinition->Arity();
    }
    std::string functionDefinitionName = irName;
    std::expected<otava::intermediate::Type*, int> irt = functionDefinition->IrType(*emitter, node.GetSourcePos(), &context);
    if (!irt)
    {
        SetError(irt.error());
        return;
    }
    otava::intermediate::Type* functionType = *irt;
    bool once = false;
    bool inline_ = context.ReleaseConfig() && functionDefinition->IsInline();
    std::expected<otava::intermediate::Function*, int> f = emitter->CreateFunction(irName, functionType, inline_, once);
    if (!f)
    {
        SetError(f.error());
        return;
    }
    otava::intermediate::Function* function = *f;
    auto fname = functionDefinition->FullName();
    if (!fname)
    {
        SetError(fname.error());
        return;
    }
    auto sfname = util::ToUtf8(*fname);
    if (!sfname)
    {
        SetError(sfname.error());
        return;
    }
    function->SetComment(*sfname);
    otava::intermediate::MetadataStruct* mdStruct = emitter->CreateMetadataStruct();
    mdStruct->AddItem("nodeType", emitter->CreateMetadataLong(otava::intermediate::funcInfoNodeType));
    mdStruct->AddItem("fullName", emitter->CreateMetadataString(*sfname));
    function->SetMdId(mdStruct->Id());
    otava::intermediate::MetadataRef* mdRef = emitter->CreateMetadataRef(mdStruct->Id());
    function->SetMetadataRef(mdRef);
    entryBlock = emitter->CreateBasicBlock();
    emitter->SetCurrentBasicBlock(entryBlock);
    int np = functionDefinition->MemFunParameters(&context).size();
    for (int i = 0; i < np; ++i)
    {
        otava::symbols::ParameterSymbol* parameter = functionDefinition->MemFunParameters(&context)[i];
        std::expected<otava::symbols::TypeSymbol*, int> t = parameter->GetReferredType(&context);
        if (!t)
        {
            SetError(t.error());
            return;
        }
        otava::symbols::TypeSymbol* type = *t;
        if (type)
        {
            std::expected<otava::intermediate::Type*, int> irt = type->IrType(*emitter, node.GetSourcePos(), &context);
            if (!irt)
            {
                SetError(irt.error());
                return;
            }
            otava::intermediate::Type* irType = *irt;
            std::expected<otava::intermediate::Instruction*, int> l = emitter->EmitLocal(irType);
            if (!l)
            {
                SetError(l.error());
                return;
            }
            otava::intermediate::Value* local = *l;
            emitter->SetIrObject(parameter, local);
        }
        else
        {
            std::unexpected<int> result = otava::symbols::Error("parameter has no type", node.GetSourcePos(), &context);
            SetError(result.error());
            return;
        }
    }
    if (functionDefinition->ReturnsClass())
    {
        otava::symbols::ParameterSymbol* parameter = functionDefinition->ReturnValueParam();
        std::expected<otava::symbols::TypeSymbol*, int> t = parameter->GetReferredType(&context);
        if (!t)
        {
            SetError(t.error());
            return;
        }
        otava::symbols::TypeSymbol* type = *t;
        if (type)
        {
            std::expected<otava::intermediate::Type*, int> irt = type->IrType(*emitter, node.GetSourcePos(), &context);
            if (!irt)
            {
                SetError(irt.error());
                return;
            }
            otava::intermediate::Type* irType = *irt;
            std::expected<otava::intermediate::Instruction*, int> l = emitter->EmitLocal(irType);
            if (!l)
            {
                SetError(l.error());
                return;
            }
            otava::intermediate::Value* local = *l;
            emitter->SetIrObject(parameter, local);
        }
        else
        {
            std::unexpected<int> result = otava::symbols::Error("parameter has no type", node.GetSourcePos(), &context);
            SetError(result.error());
            return;
        }
    }
    int nlv = functionDefinition->LocalVariables().size();
    for (int i = 0; i < nlv; ++i)
    {
        otava::symbols::VariableSymbol* localVariable = functionDefinition->LocalVariables()[i];
        otava::symbols::TypeSymbol* type = localVariable->GetReferredType();
        if (type)
        {
            std::expected<otava::intermediate::Type*, int> irt = type->IrType(*emitter, node.GetSourcePos(), &context);
            if (!irt)
            {
                SetError(irt.error());
                return;
            }
            otava::intermediate::Type* irType = *irt;
            std::expected<otava::intermediate::Instruction*, int> l = emitter->EmitLocal(irType);
            if (!l)
            {
                SetError(l.error());
                return;
            }
            otava::intermediate::Value* local = *l;
            emitter->SetIrObject(localVariable, local);
        }
    }
    for (int i = 0; i < np; ++i)
    {
        std::expected<otava::intermediate::Value*, int> p = emitter->GetParam(i);
        if (!p)
        {
            SetError(p.error());
            return;
        }
        otava::intermediate::Value* param = *p;
        otava::symbols::ParameterSymbol* parameter = functionDefinition->MemFunParameters(&context)[i];
        if (!functionDefinition->Valid())
        {
            SetError(functionDefinition->GetError());
            return;
        }
        if (parameter->GetType()->IsClassTypeSymbol())
        {
            otava::symbols::ClassTypeSymbol* classTypeSymbol = static_cast<otava::symbols::ClassTypeSymbol*>(parameter->GetType());
            if (classTypeSymbol->CopyCtor())
            {
                std::expected<otava::intermediate::Type*, int> irt = classTypeSymbol->CopyCtor()->IrType(
                    *emitter, node.GetSourcePos(), &context);
                if (!irt)
                {
                    SetError(irt.error());
                    return;
                }
                otava::intermediate::Type* irType = *irt;
                otava::intermediate::FunctionType* copyCtorType = static_cast<otava::intermediate::FunctionType*>(irType);
                std::expected<std::string, int> irn = classTypeSymbol->CopyCtor()->IrName(&context);
                if (!irn)
                {
                    SetError(irn.error());
                    return;
                }
                std::string irName = std::move(*irn);
                std::expected<otava::intermediate::Function*, int> fn = emitter->GetOrInsertFunction(irName, copyCtorType);
                if (!fn)
                {
                    SetError(fn.error());
                    return;
                }
                otava::intermediate::Function* copyCtor = *fn;
                std::vector<otava::intermediate::Value*> args;
                args.push_back(static_cast<otava::intermediate::Value*>(parameter->IrObject(*emitter, node.GetSourcePos(), &context)));
                args.push_back(param);
                std::expected<otava::intermediate::Value*, int> c = emitter->EmitCall(copyCtor, args);
                if (!c)
                {
                    SetError(c.error());
                    return;
                }
            }
            else
            {
                auto fname = classTypeSymbol->FullName();
                if (!fname)
                {
                    SetError(fname.error());
                    return;
                }
                auto sfname = util::ToUtf8(*fname);
                if (!sfname)
                {
                    SetError(sfname.error());
                    return;
                }
                auto dfname = functionDefinition->FullName();
                if (!dfname)
                {
                    SetError(dfname.error());
                    return;
                }
                auto sdfname = util::ToUtf8(*dfname);
                if (!sdfname)
                {
                    SetError(sdfname.error());
                    return;
                }
                std::unexpected<int> result = otava::symbols::Error("class type '" + *sfname + "' has no copy constructor needed by function '" +
                    *sdfname + "'", node.GetSourcePos(), &context);
                SetError(result.error());
                return;
            }
        }
        else
        {
            emitter->EmitStore(param, static_cast<otava::intermediate::Value*>(parameter->IrObject(*emitter, node.GetSourcePos(), &context)));
        }
    }
    if (functionDefinition->ReturnsClass())
    {
        std::expected<otava::intermediate::Value*, int> p = emitter->GetParam(np);
        if (!p)
        {
            SetError(p.error());
            return;
        }
        otava::intermediate::Value* param = *p;
        otava::symbols::ParameterSymbol* parameter = functionDefinition->ReturnValueParam();
        emitter->EmitStore(param, static_cast<otava::intermediate::Value*>(parameter->IrObject(*emitter, node.GetSourcePos(), &context)));
    }
    otava::symbols::BoundCtorInitializerNode* ctorInitializer = node.CtorInitializer();
    if (ctorInitializer)
    {
        auto rv = ctorInitializer->GenerateCode(*this, *emitter, &context);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
    }
    otava::symbols::BoundDtorTerminatorNode* dtorTerminator = node.DtorTerminator();
    if (dtorTerminator)
    {
        for (const auto& setVPtrStatement : dtorTerminator->SetVPtrStatements())
        {
            setVPtrStatement->Accept(*this);
            if (!Valid()) return;
        }
    }
    node.Body()->Accept(*this);
    if (!Valid()) return;
    if (dtorTerminator)
    {
        auto rv = dtorTerminator->GenerateCode(*this, *emitter, &context);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        for (const auto& setVPtrStatement : dtorTerminator->SetVPtrStatements())
        {
            setVPtrStatement->Accept(*this);
            if (!Valid()) return;
        }
    }
    StatementPrefix();
    otava::symbols::BoundStatementNode* lastStatement = nullptr;
    if (!node.Body()->Statements().empty())
    {
        lastStatement = node.Body()->Statements().back().get();
    }
    if (!lastStatement || !lastStatement->IsReturnStatementNode() || lastStatement->IsReturnStatementNode() && destructorCallGenerated)
    {
        if (functionDefinition->ReturnType() && !functionDefinition->ReturnType()->IsVoidType() && !functionDefinition->ReturnsClass())
        {
            std::expected<otava::symbols::TypeSymbol*, int> d = functionDefinition->ReturnType()->DirectType(&context);
            if (!d)
            {
                SetError(d.error());
                return;
            }
            otava::symbols::TypeSymbol* t = *d;
            d = t->FinalType(node.GetSourcePos(), &context);
            if (!d)
            {
                SetError(d.error());
                return;
            }
            t = *d;
            std::expected<otava::intermediate::Type*, int> irt = t->IrType(*emitter, node.GetSourcePos(), &context);
            if (!irt)
            {
                SetError(irt.error());
                return;
            }
            otava::intermediate::Type* irType = *irt;
            otava::intermediate::Value* returnValue = irType->DefaultValue();
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
    if (!Valid()) return;
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
        if (!Valid()) return;
        prevWasTerminator = statement->EndsWithTerminator();
    }
    if (!prevWasTerminator && !blockExits[currentBlockId]->IsEmpty())
    {
        auto rv = ExitBlocks(currentBlockId, currentBlockId, node.GetSourcePos());
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
    }
    --currentBlockId;
    currentBlock = prevBlock;
}

void CodeGenerator::Visit(otava::symbols::BoundIfStatementNode& node)
{
    if (!Valid()) return;
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
    if (node.InitStatement())
    {
        node.InitStatement()->Accept(*this);
        if (!Valid()) return;
    }
    bool prevGenJumpingBoolCode = genJumpingBoolCode;
    genJumpingBoolCode = true;
    node.GetCondition()->Accept(*this);
    if (!Valid()) return;
    genJumpingBoolCode = prevGenJumpingBoolCode;
    emitter->SetCurrentBasicBlock(trueBlock);
    prevWasTerminator = false;
    node.ThenStatement()->Accept(*this);
    if (!Valid()) return;
    if (!node.ThenStatement()->EndsWithTerminator())
    {
        emitter->EmitJump(nextBlock);
    }
    if (node.ElseStatement())
    {
        emitter->SetCurrentBasicBlock(falseBlock);
        prevWasTerminator = false;
        node.ElseStatement()->Accept(*this);
        if (!Valid()) return;
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
    if (!Valid()) return;
    StatementPrefix();
    SetCurrentLineNumber(node.GetSourcePos());
    bool prevEmitLineNumbers = emitLineNumbers;
    emitLineNumbers = false;
    if (node.InitStatement())
    {
        node.InitStatement()->Accept(*this);
        if (!Valid()) return;
    }
    node.GetCondition()->Accept(*this);
    if (!Valid()) return;
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
        for (otava::symbols::BoundExpressionNode* expr : caseTarget->exprs)
        {
            auto rv = EvaluateConstantExpr(*emitter, node.GetSourcePos(), context, expr);
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
            otava::intermediate::Value* caseValue = emitter->Stack().Pop();
            otava::intermediate::CaseTarget target(caseValue, caseTarget->block->Id());
            switchInst->AddCaseTarget(target);
        }
        prevWasTerminator = false;
        caseTarget->statement->Accept(*this);
        if (!Valid()) return;
        if (basicBlockOpen)
        {
            emitter->EmitJump(nextBlock);
            basicBlockOpen = false;
        }
    }
    if (switchTargets->Default())
    {
        emitter->SetCurrentBasicBlock(defaultBlock);
        switchTargets->Default()->statement->Accept(*this);
        if (!Valid()) return;
        if (basicBlockOpen)
        {
            emitter->EmitJump(nextBlock);
            basicBlockOpen = false;
        }
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
    if (!Valid()) return;
    StatementPrefix();
    SetCurrentLineNumber(node.GetSourcePos());
    node.Statement()->Accept(*this);
}

void CodeGenerator::Visit(otava::symbols::BoundDefaultStatementNode& node)
{
    if (!Valid()) return;
    StatementPrefix();
    SetCurrentLineNumber(node.GetSourcePos());
    node.Statement()->Accept(*this);
}

void CodeGenerator::Visit(otava::symbols::BoundWhileStatementNode& node)
{
    if (!Valid()) return;
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
    if (!Valid()) return;
    genJumpingBoolCode = prevGenJumpingBoolCode;
    emitter->SetCurrentBasicBlock(trueBlock);
    node.Statement()->Accept(*this);
    if (!Valid()) return;
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
    if (!Valid()) return;
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
    if (!Valid()) return;
    emitter->EmitJump(condBlock);
    emitter->SetCurrentBasicBlock(condBlock);
    bool prevGenJumpingBoolCode = genJumpingBoolCode;
    genJumpingBoolCode = true;
    node.GetExpr()->Accept(*this);
    if (!Valid()) return;
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
    if (!Valid()) return;
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
        if (!Valid()) return;
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
        if (!Valid()) return;
    }
    else
    {
        emitter->EmitBool(true);
        GenJumpingBoolCode();
        if (!Valid()) return;
    }
    genJumpingBoolCode = prevGenJumpingBoolCode;
    emitter->SetCurrentBasicBlock(actionBlock);
    node.Statement()->Accept(*this);
    if (!Valid()) return;
    emitter->EmitJump(loopBlock);
    emitter->SetCurrentBasicBlock(loopBlock);
    if (node.GetLoopExpr())
    {
        node.GetLoopExpr()->Accept(*this);
        if (!Valid()) return;
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
    if (!Valid()) return;
    StatementPrefix();
    otava::symbols::BoundStatementNode* prevSequenceSecond = sequenceSecond;
    sequenceSecond = node.Second();
    node.First()->Accept(*this);
    if (!Valid()) return;
    sequenceSecond = prevSequenceSecond;
    if (!node.Second()->Generated())
    {
        node.Second()->Accept(*this);
    }
}

void CodeGenerator::Visit(otava::symbols::BoundReturnStatementNode& node)
{
    if (!Valid()) return;
    StatementPrefix();
    SetCurrentLineNumber(node.GetSourcePos());
    bool prevEmitLineNumbers = emitLineNumbers;
    emitLineNumbers = false;
    if (node.GetExpr())
    {
        node.GetExpr()->Accept(*this);
        if (!Valid()) return;
        otava::intermediate::Value* returnValue = emitter->Stack().Pop();
        if (sequenceSecond)
        {
            sequenceSecond->SetGenerated();
            sequenceSecond->Accept(*this);
        }
        auto rv = ExitBlocks(currentBlockId, -1, node.GetSourcePos());
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        emitter->EmitRet(returnValue);
        lastInstructionWasRet = true;
    }
    else
    {
        auto rv = ExitBlocks(currentBlockId, -1, node.GetSourcePos());
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
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
    if (!Valid()) return;
    StatementPrefix();
    SetCurrentLineNumber(node.GetSourcePos());
    auto rv = ExitBlocks(currentBlockId, breakBlockId + 1, node.GetSourcePos());
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
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
    if (!Valid()) return;
    StatementPrefix();
    SetCurrentLineNumber(node.GetSourcePos());
    auto rv = ExitBlocks(currentBlockId, continueBlockId + 1, node.GetSourcePos());
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    emitter->EmitJump(continueBlock);
}

void CodeGenerator::Visit(otava::symbols::BoundConstructionStatementNode& node)
{
    if (!Valid()) return;
    StatementPrefix();
    SetCurrentLineNumber(node.GetSourcePos());
    node.ConstructorCall()->Accept(*this);
    if (!Valid()) return;
    if (currentBlockId > 0)
    {
        if (node.DestructorCall())
        {
            blockExits[currentBlockId - 1]->AddDestructorCall(node.ReleaseDestructorCall());
        }
    }
}

void CodeGenerator::Visit(otava::symbols::BoundExpressionStatementNode& node)
{
    if (!Valid()) return;
    if (!inLineNumberCode)
    {
        StatementPrefix();
        SetCurrentLineNumber(node.GetSourcePos());
    }
    if (!node.GetExpr()) return;
    node.GetExpr()->Accept(*this);
    if (!Valid()) return;
    if (node.GetExpr()->HasValue())
    {
        emitter->Stack().Pop();
    }
}

void CodeGenerator::Visit(otava::symbols::BoundSetVPtrStatementNode& node)
{
    if (!Valid()) return;
    StatementPrefix();
    SetCurrentLineNumber(node.GetSourcePos());
    auto rv = node.ThisPtr()->Load(*emitter, otava::symbols::OperationFlags::none, node.GetSourcePos(), &context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    otava::intermediate::Value* thisPtr = emitter->Stack().Pop();
    otava::symbols::TypeSymbol* thisPtrType = node.ThisPtr()->GetType()->GetBaseType();
    if (thisPtrType->IsClassTypeSymbol())
    {
        otava::symbols::ClassTypeSymbol* classType = static_cast<otava::symbols::ClassTypeSymbol*>(thisPtrType);
        std::int32_t vptrIndex = classType->VPtrIndex();
        otava::symbols::ClassTypeSymbol* forClass = node.GetClass();
        std::expected<otava::intermediate::Value*, int> e = emitter->EmitElemAddr(thisPtr, emitter->EmitLong(vptrIndex));
        if (!e)
        {
            SetError(e.error());
            return;
        }
        otava::intermediate::Value* ptr = *e;
        std::expected<otava::intermediate::Value*, int> v = forClass->GetVTabVariable(*emitter, &context);
        if (!v)
        {
            SetError(v.error());
            return;
        }
        otava::intermediate::Value* vtabVar = *v;
        std::expected<otava::intermediate::Type*, int> p = emitter->MakePtrType(emitter->GetVoidType());
        if (!p)
        {
            SetError(p.error());
            return;
        }
        otava::intermediate::Type* type = *p;
        otava::intermediate::Value* vptr = emitter->EmitBitcast(vtabVar, type);
        emitter->EmitStore(vptr, ptr);
        otava::symbols::ClassTypeSymbol* vptrHolderClass = node.GetVPtrHolderClass();
        std::expected<std::int64_t, int> d = otava::symbols::Delta(vptrHolderClass, forClass, *emitter, &context);
        if (!d)
        {
            auto fname = forClass->FullName();
            if (!fname)
            {
                SetError(fname.error());
                return;
            }
            auto sfname = util::ToUtf8(*fname);
            if (!sfname)
            {
                SetError(sfname.error());
                return;
            }
            auto vfname = vptrHolderClass->FullName();
            if (!vfname)
            {
                SetError(vfname.error());
                return;
            }
            auto svfname = util::ToUtf8(*vfname);
            if (!svfname)
            {
                SetError(svfname.error());
                return;
            }
            std::unexpected<int> result = otava::symbols::Error("classes '" + *sfname + "' and '" + *svfname + "' have no inheritance relationship",
                node.GetSourcePos(), &context);
            SetError(result.error());
            return;
        }
        std::int64_t delta = *d;
        std::int32_t deltaIndex = classType->DeltaIndex();
        std::expected<otava::intermediate::Value*, int> ea = emitter->EmitElemAddr(thisPtr, emitter->EmitLong(deltaIndex));
        if (!ea)
        {
            SetError(ea.error());
            return;
        }
        otava::intermediate::Value* deltaPtrElem = *ea;
        std::expected<otava::intermediate::Type*, int> t = emitter->MakePtrType(emitter->GetLongType());
        if (!t)
        {
            SetError(t.error());
            return;
        }
        otava::intermediate::Type* ptrType = *t;
        otava::intermediate::Value* deltaPtr = emitter->EmitBitcast(deltaPtrElem, ptrType);
        otava::intermediate::Value* deltaValue = emitter->EmitLong(delta);
        emitter->EmitStore(deltaValue, deltaPtr);
    }
    else
    {
        std::unexpected<int> result = otava::symbols::Error("class type symbol expected", node.GetSourcePos(), &context);
        SetError(result.error());
        return;
    }
}

void CodeGenerator::Visit(otava::symbols::BoundLiteralNode& node)
{
    if (!Valid()) return;
    SetCurrentLineNumber(node.GetSourcePos());
    auto rv = node.Load(*emitter, otava::symbols::OperationFlags::none, node.GetSourcePos(), &context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    GenJumpingBoolCode();
}

void CodeGenerator::Visit(otava::symbols::BoundStringLiteralNode& node)
{
    if (!Valid()) return;
    SetCurrentLineNumber(node.GetSourcePos());
    auto rv = node.Load(*emitter, otava::symbols::OperationFlags::none, node.GetSourcePos(), &context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    GenJumpingBoolCode();
}

void CodeGenerator::Visit(otava::symbols::BoundVariableNode& node)
{
    if (!Valid()) return;
    SetCurrentLineNumber(node.GetSourcePos());
    auto rv = node.Load(*emitter, otava::symbols::OperationFlags::none, node.GetSourcePos(), &context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    GenJumpingBoolCode();
}

void CodeGenerator::Visit(otava::symbols::BoundParameterNode& node)
{
    if (!Valid()) return;
    SetCurrentLineNumber(node.GetSourcePos());
    auto rv = node.Load(*emitter, otava::symbols::OperationFlags::none, node.GetSourcePos(), &context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    GenJumpingBoolCode();
}

void CodeGenerator::Visit(otava::symbols::BoundEnumConstant& node)
{
    if (!Valid()) return;
    SetCurrentLineNumber(node.GetSourcePos());
    auto rv = node.Load(*emitter, otava::symbols::OperationFlags::none, node.GetSourcePos(), &context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    GenJumpingBoolCode();
}

void CodeGenerator::Visit(otava::symbols::BoundMemberExprNode& node)
{
    if (!Valid()) return;
    SetCurrentLineNumber(node.GetSourcePos());
    auto rv = node.Load(*emitter, otava::symbols::OperationFlags::none, node.GetSourcePos(), &context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    GenJumpingBoolCode();
}

void CodeGenerator::Visit(otava::symbols::BoundFunctionCallNode& node)
{
    if (!Valid()) return;
    SetCurrentLineNumber(node.GetSourcePos());
    auto rv = node.Load(*emitter, otava::symbols::OperationFlags::none, node.GetSourcePos(), &context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    if (node.IsNoReturnFunctionCall())
    {
        rv = EmitReturn(node.GetSourcePos());
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
    }
    GenJumpingBoolCode();
}

void CodeGenerator::Visit(otava::symbols::BoundFunctionPtrCallNode& node)
{
    if (!Valid()) return;
    SetCurrentLineNumber(node.GetSourcePos());
    auto rv = node.Load(*emitter, otava::symbols::OperationFlags::none, node.GetSourcePos(), &context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    GenJumpingBoolCode();
}

void CodeGenerator::Visit(otava::symbols::BoundExpressionSequenceNode& node)
{
    if (!Valid()) return;
    SetCurrentLineNumber(node.GetSourcePos());
    auto rv = node.Load(*emitter, otava::symbols::OperationFlags::none, node.GetSourcePos(), &context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    GenJumpingBoolCode();
}

void CodeGenerator::Visit(otava::symbols::BoundConversionNode& node)
{
    if (!Valid()) return;
    SetCurrentLineNumber(node.GetSourcePos());
    auto rv = node.Load(*emitter, otava::symbols::OperationFlags::none, node.GetSourcePos(), &context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    GenJumpingBoolCode();
}

void CodeGenerator::Visit(otava::symbols::BoundAddressOfNode& node)
{
    if (!Valid()) return;
    SetCurrentLineNumber(node.GetSourcePos());
    auto rv = node.Load(*emitter, otava::symbols::OperationFlags::none, node.GetSourcePos(), &context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    GenJumpingBoolCode();
}

void CodeGenerator::Visit(otava::symbols::BoundDereferenceNode& node)
{
    if (!Valid()) return;
    SetCurrentLineNumber(node.GetSourcePos());
    auto rv = node.Load(*emitter, otava::symbols::OperationFlags::none, node.GetSourcePos(), &context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    GenJumpingBoolCode();
}

void CodeGenerator::Visit(otava::symbols::BoundPtrToRefNode& node)
{
    if (!Valid()) return;
    SetCurrentLineNumber(node.GetSourcePos());
    auto rv = node.Load(*emitter, otava::symbols::OperationFlags::none, node.GetSourcePos(), &context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    GenJumpingBoolCode();
}

void CodeGenerator::Visit(otava::symbols::BoundConstructTemporaryNode& node)
{
    if (!Valid()) return;
    SetCurrentLineNumber(node.GetSourcePos());
    auto rv = node.Load(*emitter, otava::symbols::OperationFlags::none, node.GetSourcePos(), &context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    GenJumpingBoolCode();
}

void CodeGenerator::Visit(otava::symbols::BoundConstructExpressionNode& node)
{
    if (!Valid()) return;
    SetCurrentLineNumber(node.GetSourcePos());
    auto rv = node.Load(*emitter, otava::symbols::OperationFlags::none, node.GetSourcePos(), &context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    GenJumpingBoolCode();
}

void CodeGenerator::Visit(otava::symbols::BoundDefaultInitNode& node)
{
    if (!Valid()) return;
    SetCurrentLineNumber(node.GetSourcePos());
    auto rv = node.Load(*emitter, otava::symbols::OperationFlags::none, node.GetSourcePos(), &context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    GenJumpingBoolCode();
}

void CodeGenerator::Visit(otava::symbols::BoundTemporaryNode& node)
{
    if (!Valid()) return;
    SetCurrentLineNumber(node.GetSourcePos());
    auto rv = node.Load(*emitter, otava::symbols::OperationFlags::none, node.GetSourcePos(), &context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    GenJumpingBoolCode();
}

void CodeGenerator::Visit(otava::symbols::BoundConjunctionNode& boundConjunction)
{
    if (!Valid()) return;
    SetCurrentLineNumber(boundConjunction.GetSourcePos());
    if (genJumpingBoolCode)
    {
        otava::intermediate::BasicBlock* rightBlock = emitter->CreateBasicBlock();
        otava::intermediate::BasicBlock* prevTrueBlock = trueBlock;
        trueBlock = rightBlock;
        boundConjunction.Left()->Accept(*this);
        if (!Valid()) return;
        trueBlock = prevTrueBlock;
        emitter->SetCurrentBasicBlock(rightBlock);
        boundConjunction.Right()->Accept(*this);
        if (!Valid()) return;
    }
    else
    {
        auto rv = boundConjunction.Load(*emitter, otava::symbols::OperationFlags::none, boundConjunction.GetSourcePos(), &context);
        if (!rv)
        {
            SetError(rv.error());
        }
    }
}

void CodeGenerator::Visit(otava::symbols::BoundDisjunctionNode& boundDisjunction)
{
    if (!Valid()) return;
    SetCurrentLineNumber(boundDisjunction.GetSourcePos());
    if (genJumpingBoolCode)
    {
        otava::intermediate::BasicBlock* rightBlock = emitter->CreateBasicBlock();
        otava::intermediate::BasicBlock* prevFalseBlock = falseBlock;
        falseBlock = rightBlock;
        boundDisjunction.Left()->Accept(*this);
        if (!Valid()) return;
        emitter->SetCurrentBasicBlock(rightBlock);
        falseBlock = prevFalseBlock;
        boundDisjunction.Right()->Accept(*this);
        if (!Valid()) return;
    }
    else
    {
        auto rv = boundDisjunction.Load(*emitter, otava::symbols::OperationFlags::none, boundDisjunction.GetSourcePos(), &context);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
    }
}

void CodeGenerator::Visit(otava::symbols::BoundGlobalVariableDefinitionNode& node)
{
    if (!Valid()) return;
    SetCurrentLineNumber(node.GetSourcePos());
    otava::symbols::VariableSymbol* variable = node.GetGlobalVariable();
    std::expected<otava::symbols::TypeSymbol*, int> f = otava::symbols::ResolveFwdDeclaredType(variable->GetType(), node.GetSourcePos(), &context);
    if (!f)
    {
        SetError(f.error());
        return;
    }
    otava::symbols::TypeSymbol* type = *f;
    if (type->IsForwardClassDeclarationSymbol()) return;
    variable->SetDeclaredType(type);
    otava::intermediate::Value* initializer = nullptr;
    std::expected<otava::intermediate::Type*, int> irt = variable->GetType()->IrType(*emitter, node.GetSourcePos(), &context);
    if (!irt)
    {
        SetError(irt.error());
        return;
    }
    otava::intermediate::Type* irType = *irt;
    if (variable->GetValue() && !variable->GetType()->IsClassTypeSymbol())
    {
        std::unique_ptr<otava::symbols::Value> clonedVariableValue = otava::symbols::CloneAndSetType(variable->GetValue(), variable->GetType());
        std::expected<otava::intermediate::Value*, int> v = clonedVariableValue->IrValue(*emitter, node.GetSourcePos(), &context);
        if (!v)
        {
            SetError(v.error());
            return;
        }
        initializer = *v;
    }
    else
    {
        initializer = irType->MakeDefaultValue(*emitter->GetIntermediateContext());
    }
    std::expected<std::string, int> irn = variable->IrName(&context);
    if (!irn)
    {
        SetError(irn.error());
        return;
    }
    std::string irName = std::move(*irn);
    std::expected<otava::intermediate::Value*, int> v = emitter->EmitGlobalVariable(irType, irName, initializer);
    if (!v)
    {
        SetError(v.error());
        return;
    }
    otava::intermediate::Value* irVariable = *v;
    emitter->SetIrObject(variable, irVariable);
}

std::expected<std::string, int> GenerateCode(otava::symbols::Context& context, const std::string& config, int optLevel, bool verbose, std::string& mainIrName,
    int& mainFunctionParams, bool globalMain, const std::vector<std::string>& compileUnitInitFnNames)
{
    CodeGenerator codeGenerator(context, config, optLevel, verbose, mainIrName, mainFunctionParams, globalMain, compileUnitInitFnNames);
    context.GetBoundCompileUnit()->Accept(codeGenerator);
    if (!codeGenerator) return std::unexpected<int>(codeGenerator.GetError());
    return std::expected<std::string, int>(codeGenerator.GetAsmFileName());
}

} // namespace otava::codegen
