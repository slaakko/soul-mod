// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.bound.tree;

import otava.symbols.context;
import otava.symbols.error;
import otava.symbols.value;
import otava.symbols.variable.symbol;
import otava.symbols.function.kind;
import otava.symbols.function.symbol;
import otava.symbols.emitter;
import otava.symbols.enums;
import otava.symbols.classes;
import otava.symbols.symbol.table;
import otava.symbols.type.resolver;
import otava.symbols.operation.repository;
import otava.symbols.argument.conversion.table;
import otava.symbols.bound.tree.visitor;
import otava.symbols.function.templates;
import otava.symbols.inline_functions;
import otava.symbols.class_templates;
import otava.symbols.type.symbol;
import otava.symbols.namespaces;
import otava.symbols.fundamental.type.symbol;
import otava.intermediate.code;

namespace otava::symbols {

std::string BoundNodeKindStr(BoundNodeKind nodeKind)
{
    switch (nodeKind)
    {
        case BoundNodeKind::boundCompileUnitNode:
        {
            return "boundCompileUnitNode";
        }
        case BoundNodeKind::boundFunctionNode:
        {
            return "boundFunctionNode";
        }
        case BoundNodeKind::boundCompoundStatementNode:
        {
            return "boundCompoundStatementNode";
        }
        case BoundNodeKind::boundIfStatementNode:
        {
            return "boundIfStatementNode";
        }
        case BoundNodeKind::boundSwitchStatementNode:
        {
            return "boundSwitchStatementNode";
        }
        case BoundNodeKind::boundCaseStatementNode:
        {
            return "boundCaseStatementNode";
        }
        case BoundNodeKind::boundDefaultStatementNode:
        {
            return "boundDefaultStatementNode";
        }
        case BoundNodeKind::boundWhileStatementNode:
        {
            return "boundWhileStatementNode";
        }
        case BoundNodeKind::boundDoStatementNode:
        {
            return "boundDoStatementNode";
        }
        case BoundNodeKind::boundForStatementNode:
        {
            return "boundForStatementNode";
        }
        case BoundNodeKind::boundBreakStatementNode:
        {
            return "boundBreakStatementNode";
        }
        case BoundNodeKind::boundContinueStatementNode:
        {
            return "boundContinueStatementNode";
        }
        case BoundNodeKind::boundReturnStatementNode:
        {
            return "boundReturnStatementNode";
        }
        case BoundNodeKind::boundGotoStatementNode:
        {
            return "boundGotoStatementNode";
        }
        case BoundNodeKind::boundConstructionStatementNode:
        {
            return "boundConstructionStatementNode";
        }
        case BoundNodeKind::boundExpressionStatementNode:
        {
            return "boundExpressionStatementNode";
        }
        case BoundNodeKind::boundSequenceStatementNode:
        {
            return "boundSequenceStatementNode";
        }
        case BoundNodeKind::boundSetVPtrStatementNode:
        {
            return "boundSetVPtrStatementNode";
        }
        case BoundNodeKind::boundTryStatementNode:
        {
            return "boundTryStatementNode";
        }
        case BoundNodeKind::boundHandlerNode:
        {
            return "boundHandlerNode";
        }
        case BoundNodeKind::boundValueNode:
        {
            return "boundValueNode";
        }
        case BoundNodeKind::boundLiteralNode:
        {
            return "boundLiteralNode";
        }
        case BoundNodeKind::boundVariableNode:
        {
            return "boundVariableNode";
        }
        case BoundNodeKind::boundParameterNode:
        {
            return "boundParameterNode";
        }
        case BoundNodeKind::boundEnumConstantNode:
        {
            return "boundEnumConstantNode";
        }
        case BoundNodeKind::boundFunctionGroupNode:
        {
            return "boundFunctionGroupNode";
        }
        case BoundNodeKind::boundTypeNode:
        {
            return "boundTypeNode";
        }
        case BoundNodeKind::boundMemberExprNode:
        {
            return "boundMemberExprNode";
        }
        case BoundNodeKind::boundFunctionCallNode:
        {
            return "boundFunctionCallNode";
        }
        case BoundNodeKind::boundEmptyFunctionCallNode:
        {
            return "boundEmptyFunctionCallNode";
        }
        case BoundNodeKind::boundExpressionSequenceNode:
        {
            return "boundExpressionSequenceNode";
        }
        case BoundNodeKind::boundExpressionListNode:
        {
            return "boundExpressionListNode";
        }
        case BoundNodeKind::boundDisjunctionNode:
        {
            return "boundDisjunctionNode";
        }
        case BoundNodeKind::boundConjunctionNode:
        {
            return "boundConjunctionNode";
        }
        case BoundNodeKind::boundConversionNode:
        {
            return "boundConversionNode";
        }
        case BoundNodeKind::boundAddressOfNode:
        {
            return "boundAddressOfNode";
        }
        case BoundNodeKind::boundDereferenceNode:
        {
            return "boundDereferenceNode";
        }
        case BoundNodeKind::boundRefToPtrNode:
        {
            return "boundRefToPtrNode";
        }
        case BoundNodeKind::boundPtrToRefNode:
        {
            return "boundPtrToRefNode";
        }
        case BoundNodeKind::boundDefaultInitNode:
        {
            return "boundDefaultInitNode";
        }
        case BoundNodeKind::boundConstructTemporaryNode:
        {
            return "boundConstructTemporaryNode";
        }
        case BoundNodeKind::boundConstructExpressionNode:
        {
            return "boundConstructExpressionNode";
        }
        case BoundNodeKind::boundClassNode:
        {
            return "boundClassNode";
        }
        case BoundNodeKind::boundEmptyDestructorNode:
        {
            return "boundEmptyDestructorNode";
        }
        case BoundNodeKind::boundThrowExpressionNode:
        {
            return "boundThrowExpressionNode";
        }
        case BoundNodeKind::boundFunctionValueNode:
        {
            return "boundFunctionValueNode";
        }
        case BoundNodeKind::boundVariableAsVoidPtrNode:
        {
            return "boundVariableAsVoidPtrNode";
        }
    }
    return "<unknown bound node>";
}

struct BoundNodeLess
{
    bool operator()(const std::unique_ptr<BoundNode>& left, const std::unique_ptr<BoundNode>& right) const;
};

bool BoundNodeLess::operator()(const std::unique_ptr<BoundNode>& left, const std::unique_ptr<BoundNode>& right) const
{
    if (left->Kind() < right->Kind()) return true;
    if (left->Kind() > right->Kind()) return false;
    return left->Index() < right->Index();
}

BoundNode::BoundNode(BoundNodeKind kind_, const soul::ast::SourcePos& sourcePos_) : kind(kind_), index(-1), sourcePos(sourcePos_)
{
}

BoundNode::~BoundNode()
{
}

BoundExpressionNode::BoundExpressionNode(BoundNodeKind kind_, const soul::ast::SourcePos& sourcePos_, TypeSymbol* type_) :
    BoundNode(kind_, sourcePos_), flags(BoundExpressionFlags::none), type(type_)
{
}

std::expected<bool, int> BoundExpressionNode::Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    return Error("LOAD not implemented for " + BoundNodeKindStr(Kind()), sourcePos, context);
}

std::expected<bool, int> BoundExpressionNode::Store(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    return Error("STORE not implemented for " + BoundNodeKindStr(Kind()), sourcePos, context);
}

std::expected<Scope*, int> BoundExpressionNode::GetMemberScope(otava::ast::Node* op, const soul::ast::SourcePos& sourcePos, Context* context) const
{
    if (type)
    {
        std::expected<TypeSymbol*, int> pt = type->PlainType(context);
        if (!pt) return std::unexpected<int>(pt.error());
        TypeSymbol* plainType = *pt;
        if (op->IsDotNode())
        {
            std::expected<TypeSymbol*, int> dt = type->DirectType(context);
            if (!dt) return std::unexpected<int>(dt.error());
            TypeSymbol* directType = *dt;
            std::expected<TypeSymbol*, int> rv = directType->FinalType(sourcePos, context);
            if (!rv) return std::unexpected<int>(rv.error());
            TypeSymbol* finalType = *rv;
            TypeSymbol* baseType = finalType->GetBaseType();
            return baseType->GetScope();
        }
        else if (op->IsArrowNode() && type->IsPointerType())
        {
            std::expected<TypeSymbol*, int> dt = type->DirectType(context);
            if (!dt) return std::unexpected<int>(dt.error());
            TypeSymbol* directType = *dt;
            std::expected<TypeSymbol*, int> rv = directType->FinalType(sourcePos, context);
            if (!rv) return std::unexpected<int>(rv.error());
            TypeSymbol* finalType = *rv;
            std::expected<TypeSymbol*, int> pt = finalType->RemovePointer(context);
            if (!pt) return std::unexpected<int>(pt.error());
            TypeSymbol* type = *pt;
            TypeSymbol* baseType = type->GetBaseType();
            return baseType->GetScope();
        }
        else if (op->IsArrowNode() && plainType->IsClassTypeSymbol())
        {
            std::expected<TypeSymbol*, int> dt = plainType->DirectType(context);
            if (!dt) return std::unexpected<int>(dt.error());
            TypeSymbol* directType = *dt;
            std::expected<TypeSymbol*, int> rv = directType->FinalType(sourcePos, context);
            if (!rv) return std::unexpected<int>(rv.error());
            TypeSymbol* finalType = *rv;
            TypeSymbol* baseType = finalType;
            return baseType->GetScope();
        }
    }
    return nullptr;
}

bool BoundExpressionNode::GetFlag(BoundExpressionFlags flag) const
{
    return (flags & flag) != BoundExpressionFlags::none;
}

void BoundExpressionNode::SetFlag(BoundExpressionFlags flag)
{
    flags = flags | flag;
}

std::expected<bool, int> BoundExpressionNode::ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (type)
    {
        std::expected<TypeSymbol*, int> dt = type->DirectType(context);
        if (!dt) return std::unexpected<int>(dt.error());
        TypeSymbol* directType = *dt;
        std::expected<TypeSymbol*, int> rv = directType->FinalType(sourcePos, context);
        if (!rv) return std::unexpected<int>(rv.error());
        TypeSymbol* finalType = *rv;
        type = finalType;
    }
    return std::expected<bool, int>(true);
}

BoundValueExpressionNode::BoundValueExpressionNode(otava::intermediate::Value* value_, TypeSymbol* type) :
    BoundExpressionNode(BoundNodeKind::boundValueNode, soul::ast::SourcePos(), type), value(value_)
{
}

void BoundValueExpressionNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

BoundExpressionNode* BoundValueExpressionNode::Clone() const
{
    return new BoundValueExpressionNode(value, GetType());
}

std::expected<bool, int> BoundValueExpressionNode::Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    emitter.Stack().Push(value);
    return std::expected<bool, int>(true);
}

BoundCompileUnitNode::BoundCompileUnitNode() :
    BoundNode(BoundNodeKind::boundCompileUnitNode, soul::ast::SourcePos()),
    operationRepository(new OperationRepository()),
    argumentConversionTable(new ArgumentConversionTable()),
    functionTemplateRepository(new FunctionTemplateRepository()),
    classTemplateRepository(new ClassTemplateRepository()),
    inlineFunctionRepository(new InlineFunctionRepository()),
    id(),
    compileUnitInitializationFunction(nullptr)
{
}

BoundCompileUnitNode::~BoundCompileUnitNode()
{
    if (compileUnitInitializationFunction) delete compileUnitInitializationFunction;
}

void BoundCompileUnitNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> BoundCompileUnitNode::AddBoundNode(std::unique_ptr<BoundNode>&& node, Context* context)
{
    if (node->IsBoundFunctionNode())
    {
        BoundFunctionNode* boundFunction = static_cast<BoundFunctionNode*>(node.get());
        std::set<const Symbol*> visited;
        if (boundFunction->GetFunctionDefinitionSymbol()->IsTemplateParameterInstantiation(context, visited))
        {
            return;
        }
        FunctionDefinitionSymbolSet* functionDefinitionSymbolSet = context->GetFunctionDefinitionSymbolSet();
        FunctionDefinitionSymbol* functionDefinition = boundFunction->GetFunctionDefinitionSymbol();
        functionDefinition->SetFlag(FunctionSymbolFlags::fixedIrName);
        std::expected<std::string, int> is = functionDefinition->IrName(context);
        if (!is) return std::unexpected<int>(is.error());
        if (functionDefinitionSymbolSet->FunctionDefinitionSymbolFound(functionDefinition))
        {
            return;
        }
        functionDefinitionSymbolSet->AddFunctionDefinitionSymbol(functionDefinition);
    }
    if (context->GetFlag(ContextFlags::generatingVTab))
    {
        if (node->IsBoundFunctionNode())
        {
            context->AddBoundVTabFunction(static_cast<BoundFunctionNode*>(node.release()));
        }
    }
    else
    {
        node->SetIndex(static_cast<int>(boundNodes.size()));
        boundNodes.push_back(std::move(node));
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> BoundCompileUnitNode::AddBoundNodeForClass(ClassTypeSymbol* cls, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::set<const Symbol*> visited;
    if (cls->IsTemplateParameterInstantiation(context, visited)) return std::expected<bool, int>(false);
    if (boundClasses.find(cls) != boundClasses.end()) return std::expected<bool, int>(false);
    boundClasses.insert(cls);
    std::expected<bool, int> rv = AddBoundNode(std::unique_ptr<BoundNode>(new BoundClassNode(cls, sourcePos)), context);
    if (!rv) return rv;
    for (ClassTypeSymbol* base : cls->BaseClasses())
    {
        rv = AddBoundNodeForClass(base, sourcePos, context);
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

void BoundCompileUnitNode::Sort()
{
    std::insertion_sort(boundNodes.begin(), boundNodes.end(), BoundNodeLess());
}

std::expected<otava::intermediate::Value*, int> BoundCompileUnitNode::CreateBoundGlobalVariable(
    VariableSymbol* globalVariableSymbol, Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context, bool definition)
{
    auto rv = otava::symbols::ResolveFwdDeclaredType(globalVariableSymbol->GetType(), sourcePos, context);
    if (!rv) return std::unexpected<int>(rv.error());
    otava::symbols::TypeSymbol* type = *rv;
    globalVariableSymbol->SetDeclaredType(type);
    otava::intermediate::Value* initializer = nullptr;
    std::expected<otava::intermediate::Type*, int> irv = globalVariableSymbol->GetType()->IrType(emitter, sourcePos, context);
    if (!irv) return std::unexpected<int>(irv.error());
    otava::intermediate::Type* irType = *irv;
    std::expected<otava::intermediate::Type*, int> prv = emitter.MakePtrType(irType);
    if (!prv) return std::unexpected<int>(prv.error());
    otava::intermediate::Type* ptrIrType = *prv;
    if (definition)
    {
        if (globalVariableSymbol->GetValue())
        {
            std::expected<otava::intermediate::Value*, int> irv = globalVariableSymbol->GetValue()->IrValue(emitter, sourcePos, context);
            if (!irv) return irv;
            otava::intermediate::Value* irValue = *irv;
            initializer = irValue;
        }
        else
        {
            initializer = irType->DefaultValue();
        }
    }
    std::expected<std::string, int> is = globalVariableSymbol->IrName(context);
    if (!is) return std::unexpected<int>(is.error());
    std::expected<otava::intermediate::Value*, int> grv = emitter.EmitGlobalVariable(irType, *is, initializer);
    if (!grv) return grv;
    otava::intermediate::Value* irVariable = *grv;
    emitter.SetIrObject(globalVariableSymbol, irVariable);
    return std::expected<otava::intermediate::Value*, int>(irVariable);
}

std::expected<bool, int> BoundCompileUnitNode::AddDynamicInitialization(BoundExpressionNode* dynamicInitialization, BoundExpressionNode* atExitCall,
    const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (!compileUnitInitializationFunction)
    {
        std::expected<std::u32string, int> srv = util::ToUtf32(id);
        if (!srv) return std::unexpected<int>(srv.error());
        FunctionDefinitionSymbol* compileUnitInitializationFunctionSymbol = new FunctionDefinitionSymbol(U"@dynamic_init_" + *srv);
        std::expected<bool, int> rv = context->GetSymbolTable()->GlobalNs()->AddSymbol(compileUnitInitializationFunctionSymbol, sourcePos, context);
        if (!rv) return rv;
        compileUnitInitializationFunction = new BoundFunctionNode(compileUnitInitializationFunctionSymbol, sourcePos);
        compileUnitInitializationFunction->SetBody(new BoundCompoundStatementNode(sourcePos));
    }
    BoundCompoundStatementNode* body = compileUnitInitializationFunction->Body();
    BoundExpressionStatementNode* initExprStmt = new BoundExpressionStatementNode(sourcePos);
    std::expected<bool, int> rv = initExprStmt->SetExpr(dynamicInitialization, sourcePos, context);
    if (!rv) return rv;
    body->AddStatement(initExprStmt);
    if (atExitCall)
    {
        BoundExpressionStatementNode* atExitStmt = new BoundExpressionStatementNode(sourcePos);
        std::expected<bool, int> rv = atExitStmt->SetExpr(atExitCall, sourcePos, context);
        if (!rv) return rv;
        body->AddStatement(atExitStmt);
    }
    return std::expected<bool, int>(true);
}

void BoundCompileUnitNode::AddClassToGenerateDestructorList(ClassTypeSymbol* classType)
{
    if (std::find(generateDestructorList.begin(), generateDestructorList.end(), classType) == generateDestructorList.end())
    {
        generateDestructorList.push_back(classType);
    }
}

BoundCtorInitializerNode::BoundCtorInitializerNode(const soul::ast::SourcePos& sourcePos_) : BoundNode(BoundNodeKind::boundCtorInitializerNode, sourcePos_)
{
}

void BoundCtorInitializerNode::AddBaseInitializer(BoundFunctionCallNode* baseInitializer)
{
    baseInitializers.push_back(std::unique_ptr<BoundFunctionCallNode>(baseInitializer));
}

void BoundCtorInitializerNode::AddSetVPtrStatement(BoundStatementNode* setVPtrStatement)
{
    setVPtrStatements.push_back(std::unique_ptr<BoundStatementNode>(setVPtrStatement));
}

void BoundCtorInitializerNode::AddMemberInitializer(BoundFunctionCallNode* memberInitializer)
{
    memberInitializers.push_back(std::unique_ptr<BoundFunctionCallNode>(memberInitializer));
}

std::expected<bool, int> BoundCtorInitializerNode::GenerateCode(BoundTreeVisitor& visitor, Emitter& emitter, Context* context)
{
    for (const auto& baseInitializer : baseInitializers)
    {
        std::expected<bool, int> rv = baseInitializer->Load(emitter, OperationFlags::defaultInit, GetSourcePos(), context);
        if (!rv) return rv;
    }
    for (const auto& setVPtrStatement : setVPtrStatements)
    {
        setVPtrStatement->Accept(visitor);
    }
    for (const auto& memberInitializer : memberInitializers)
    {
        std::expected<bool, int> rv = memberInitializer->Load(emitter, OperationFlags::defaultInit, GetSourcePos(), context);
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

void BoundCtorInitializerNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

BoundDtorTerminatorNode::BoundDtorTerminatorNode(const soul::ast::SourcePos& sourcePos_) : BoundNode(BoundNodeKind::boundDtorTerminatorNode, sourcePos_)
{
}

void BoundDtorTerminatorNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

void BoundDtorTerminatorNode::AddSetVPtrStatement(BoundStatementNode* setVPtrStatement)
{
    setVPtrStatements.push_back(std::unique_ptr<BoundStatementNode>(setVPtrStatement));
}

void BoundDtorTerminatorNode::AddMemberTerminator(BoundFunctionCallNode* memberTerminator)
{
    memberTerminators.push_back(std::unique_ptr<BoundFunctionCallNode>(memberTerminator));
}

std::expected<bool, int> BoundDtorTerminatorNode::GenerateCode(BoundTreeVisitor& visitor, Emitter& emitter, Context* context)
{
    for (const auto& memberTerminator : memberTerminators)
    {
        std::expected<bool, int> rv = memberTerminator->Load(emitter, OperationFlags::none, GetSourcePos(), context);
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

BoundClassNode::BoundClassNode(ClassTypeSymbol* cls_, const soul::ast::SourcePos& sourcePos_) : BoundNode(BoundNodeKind::boundClassNode, sourcePos_), cls(cls_)
{
}

void BoundClassNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

BoundFunctionNode::BoundFunctionNode(FunctionDefinitionSymbol* functionDefinitionSymbol_, const soul::ast::SourcePos& sourcePos_) :
    BoundNode(BoundNodeKind::boundFunctionNode, sourcePos_),
    functionDefinitionSymbol(functionDefinitionSymbol_),
    body(), serial(-1)
{
}

BoundFunctionNode::~BoundFunctionNode()
{
    for (FunctionSymbol* fn : defaultFunctionSymbols)
    {
        delete fn;
    }
}

void BoundFunctionNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

void BoundFunctionNode::SetBody(BoundCompoundStatementNode* body_)
{
    body.reset(body_);
}

void BoundFunctionNode::SetCtorInitializer(BoundCtorInitializerNode* ctorInitializer_)
{
    ctorInitializer.reset(ctorInitializer_);
}

void BoundFunctionNode::SetDtorTerminator(BoundDtorTerminatorNode* dtorTerminator_)
{
    dtorTerminator.reset(dtorTerminator_);
}

void BoundFunctionNode::AddDefaultFunctionSymbol(FunctionSymbol* defaultFunctionSymbol)
{
    defaultFunctionSymbols.push_back(defaultFunctionSymbol);
}

BoundStatementNode::BoundStatementNode(BoundNodeKind kind_, const soul::ast::SourcePos& sourcePos_) :
    BoundNode(kind_, sourcePos_), parent(nullptr), generated(false), postfix(false)
{
}

bool BoundStatementNode::IsConditionalStatementInBlock(BoundCompoundStatementNode* block) const
{
    if (this == block)
    {
        return false;
    }
    if (IsIfStatementNode() || IsSwitchStatementNode()) return true;
    BoundStatementNode* parent = Parent();
    if (parent)
    {
        return parent->IsConditionalStatementInBlock(block);
    }
    return false;
}

BoundCompoundStatementNode* BoundStatementNode::Block()
{
    if (IsBoundCompoundStatementNode()) return static_cast<BoundCompoundStatementNode*>(this);
    BoundStatementNode* parentStatement = Parent();
    if (parentStatement != nullptr)
    {
        return parentStatement->Block();
    }
    else
    {
        return nullptr;
    }
}

BoundCompoundStatementNode::BoundCompoundStatementNode(const soul::ast::SourcePos& sourcePos_) :
    BoundStatementNode(BoundNodeKind::boundCompoundStatementNode, sourcePos_)
{
}

void BoundCompoundStatementNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

int BoundCompoundStatementNode::IndexOf(BoundStatementNode* stmt)
{
    int n = statements.size();
    for (int i = 0; i < n; ++i)
    {
        BoundStatementNode* statement = statements[i].get();
        if (statement == stmt) return i;
    }
    return -1;
}

void BoundCompoundStatementNode::AddStatement(BoundStatementNode* statement)
{
    statement->SetParent(this);
    statements.push_back(std::unique_ptr<BoundStatementNode>(statement));
}

bool BoundCompoundStatementNode::EndsWithTerminator() const
{
    if (!statements.empty())
    {
        if (statements.back()->IsTerminator()) return true;
        if (statements.back()->IsBoundCompoundStatementNode() && statements.back()->EndsWithTerminator()) return true;
    }
    return false;
}

BoundIfStatementNode::BoundIfStatementNode(const soul::ast::SourcePos& sourcePos_) : BoundStatementNode(BoundNodeKind::boundIfStatementNode, sourcePos_)
{
}

void BoundIfStatementNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

void BoundIfStatementNode::SetInitStatement(BoundStatementNode* initStatement_)
{
    initStatement.reset(initStatement_);
}

void BoundIfStatementNode::SetCondition(BoundExpressionNode* condition_)
{
    condition.reset(condition_);
}

void BoundIfStatementNode::SetThenStatement(BoundStatementNode* thenStatement_)
{
    thenStatement.reset(thenStatement_);
}

void BoundIfStatementNode::SetElseStatement(BoundStatementNode* elseStatement_)
{
    elseStatement.reset(elseStatement_);
}

BoundSwitchStatementNode::BoundSwitchStatementNode(const soul::ast::SourcePos& sourcePos_) : BoundStatementNode(BoundNodeKind::boundSwitchStatementNode, sourcePos_)
{
}

void BoundSwitchStatementNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

void BoundSwitchStatementNode::SetInitStatement(BoundStatementNode* initStatement_)
{
    initStatement.reset(initStatement_);
}

void BoundSwitchStatementNode::SetCondition(BoundExpressionNode* condition_)
{
    condition.reset(condition_);
}

void BoundSwitchStatementNode::SetStatement(BoundStatementNode* statement_)
{
    statement.reset(statement_);
}

BoundCaseStatementNode::BoundCaseStatementNode(const soul::ast::SourcePos& sourcePos_) : BoundStatementNode(BoundNodeKind::boundCaseStatementNode, sourcePos_)
{
}

void BoundCaseStatementNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

void BoundCaseStatementNode::AddCaseExpr(BoundExpressionNode* caseExpr)
{
    caseExprs.push_back(std::unique_ptr<BoundExpressionNode>(caseExpr));
}

void BoundCaseStatementNode::InsertCaseExprToFront(BoundExpressionNode* caseExpr)
{
    caseExprs.insert(caseExprs.begin(), std::unique_ptr<BoundExpressionNode>(caseExpr));
}

void BoundCaseStatementNode::SetStatement(BoundStatementNode* stmt_)
{
    stmt.reset(stmt_);
}

BoundDefaultStatementNode::BoundDefaultStatementNode(const soul::ast::SourcePos& sourcePos_) : BoundStatementNode(BoundNodeKind::boundDefaultStatementNode, sourcePos_)
{
}

void BoundDefaultStatementNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

void BoundDefaultStatementNode::SetStatement(BoundStatementNode* stmt_)
{
    stmt.reset(stmt_);
}

BoundWhileStatementNode::BoundWhileStatementNode(const soul::ast::SourcePos& sourcePos_) : BoundStatementNode(BoundNodeKind::boundWhileStatementNode, sourcePos_)
{
}

void BoundWhileStatementNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

void BoundWhileStatementNode::SetCondition(BoundExpressionNode* condition_)
{
    condition.reset(condition_);
}

void BoundWhileStatementNode::SetStatement(BoundStatementNode* statement_)
{
    statement.reset(statement_);
}

BoundDoStatementNode::BoundDoStatementNode(const soul::ast::SourcePos& sourcePos_) : BoundStatementNode(BoundNodeKind::boundDoStatementNode, sourcePos_)
{
}

void BoundDoStatementNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

void BoundDoStatementNode::SetExpr(BoundExpressionNode* expr_)
{
    expr.reset(expr_);
}

void BoundDoStatementNode::SetStatement(BoundStatementNode* statement_)
{
    statement.reset(statement_);
}

BoundForStatementNode::BoundForStatementNode(const soul::ast::SourcePos& sourcePos_) : BoundStatementNode(BoundNodeKind::boundForStatementNode, sourcePos_)
{
}

void BoundForStatementNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

void BoundForStatementNode::SetInitStatement(BoundStatementNode* initStatement_)
{
    initStatement.reset(initStatement_);
}

void BoundForStatementNode::SetCondition(BoundExpressionNode* condition_)
{
    condition.reset(condition_);
}

void BoundForStatementNode::SetLoopExpr(BoundExpressionNode* loopExpr_)
{
    loopExpr.reset(loopExpr_);
}

void BoundForStatementNode::SetStatement(BoundStatementNode* statement_)
{
    statement.reset(statement_);
}

BoundSequenceStatementNode::BoundSequenceStatementNode(const soul::ast::SourcePos& sourcePos_, BoundStatementNode* first_, BoundStatementNode* second_) :
    BoundStatementNode(BoundNodeKind::boundSequenceStatementNode, sourcePos_), first(first_), second(second_)
{
}

void BoundSequenceStatementNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

BoundBreakStatementNode::BoundBreakStatementNode(const soul::ast::SourcePos& sourcePos_) : BoundStatementNode(BoundNodeKind::boundBreakStatementNode, sourcePos_)
{
}

void BoundBreakStatementNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

BoundContinueStatementNode::BoundContinueStatementNode(const soul::ast::SourcePos& sourcePos_) : BoundStatementNode(BoundNodeKind::boundContinueStatementNode, sourcePos_)
{
}

void BoundContinueStatementNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

BoundReturnStatementNode::BoundReturnStatementNode(const soul::ast::SourcePos& sourcePos_) : BoundStatementNode(BoundNodeKind::boundReturnStatementNode, sourcePos_)
{
}

void BoundReturnStatementNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> BoundReturnStatementNode::SetExpr(BoundExpressionNode* expr_, const soul::ast::SourcePos& sourcePos, Context* context)
{
    expr.reset(expr_);
    return expr->ModifyTypes(sourcePos, context);
}

BoundGotoStatementNode::BoundGotoStatementNode(const soul::ast::SourcePos& sourcePos_) : BoundStatementNode(BoundNodeKind::boundGotoStatementNode, sourcePos_)
{
}

void BoundGotoStatementNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

BoundConstructionStatementNode::BoundConstructionStatementNode(const soul::ast::SourcePos& sourcePos_, BoundFunctionCallNode* constructorCall_) :
    BoundStatementNode(BoundNodeKind::boundConstructionStatementNode, sourcePos_), constructorCall(constructorCall_)
{
}

void BoundConstructionStatementNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

void BoundConstructionStatementNode::SetDestructorCall(BoundFunctionCallNode* destructorCall_)
{
    destructorCall.reset(destructorCall_);
}

BoundExpressionStatementNode::BoundExpressionStatementNode(const soul::ast::SourcePos& sourcePos_) : BoundStatementNode(BoundNodeKind::boundExpressionStatementNode, sourcePos_)
{
}

void BoundExpressionStatementNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> BoundExpressionStatementNode::SetExpr(BoundExpressionNode* expr_, const soul::ast::SourcePos& sourcePos, Context* context)
{
    expr.reset(expr_);
    return expr->ModifyTypes(sourcePos, context);
}

bool BoundExpressionStatementNode::IsTerminator() const
{
    return expr.get() && (expr->IsNoReturnFunctionCall() || expr->IsBoundThrowExpression());
}

BoundSetVPtrStatementNode::BoundSetVPtrStatementNode(BoundExpressionNode* thisPtr_, ClassTypeSymbol* forClass_, ClassTypeSymbol* vptrHolderClass_,
    const soul::ast::SourcePos& sourcePos_) :
    BoundStatementNode(BoundNodeKind::boundSetVPtrStatementNode, sourcePos_), thisPtr(thisPtr_), forClass(forClass_), vptrHolderClass(vptrHolderClass_)
{
}

void BoundSetVPtrStatementNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

BoundLiteralNode::BoundLiteralNode(Value* value_, const soul::ast::SourcePos& sourcePos_) :
    BoundExpressionNode(BoundNodeKind::boundLiteralNode, sourcePos_, value_->GetType()), value(value_)
{
}

void BoundLiteralNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> BoundLiteralNode::Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<otava::intermediate::Value*, int> irv = value->IrValue(emitter, sourcePos, context);
    if (!irv) return std::unexpected<int>(irv.error());
    otava::intermediate::Value* irValue = *irv;
    emitter.Stack().Push(irValue);
    return std::expected<bool, int>(true);
}

BoundExpressionNode* BoundLiteralNode::Clone() const
{
    BoundExpressionNode* clone = new BoundLiteralNode(value, GetSourcePos());
    clone->SetFlags(Flags());
    return clone;
}

BoundStringLiteralNode::BoundStringLiteralNode(Value* value_, const soul::ast::SourcePos& sourcePos_) :
    BoundExpressionNode(BoundNodeKind::boundStringLiteralNode, sourcePos_, value_->GetType()), value(value_), irValue(nullptr)
{
}

void BoundStringLiteralNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> BoundStringLiteralNode::Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (!irValue)
    {
        std::expected<otava::intermediate::Value*, int> irv = value->IrValue(emitter, sourcePos, context);
        if (!irv) return std::unexpected<int>(irv.error());
        irValue = *irv;
    }
    emitter.Stack().Push(irValue);
    return std::expected<bool, int>(true);
}

BoundExpressionNode* BoundStringLiteralNode::Clone() const
{
    BoundExpressionNode* clone = new BoundStringLiteralNode(value, GetSourcePos());
    clone->SetFlags(Flags());
    return clone;
}

BoundVariableNode::BoundVariableNode(VariableSymbol* variable_, const soul::ast::SourcePos& sourcePos_) :
    BoundExpressionNode(BoundNodeKind::boundVariableNode, sourcePos_, variable_->GetReferredType()), variable(variable_)
{
}

void BoundVariableNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

void BoundVariableNode::SetThisPtr(BoundExpressionNode* thisPtr_)
{
    thisPtr.reset(thisPtr_);
}

std::expected<bool, int> BoundVariableNode::Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (variable->IsLocalVariable())
    {
        if ((flags & OperationFlags::addr) != OperationFlags::none || variable->GetType()->IsClassTypeSymbol())
        {
            emitter.Stack().Push(static_cast<otava::intermediate::Value*>(variable->IrObject(emitter, sourcePos, context)));
        }
        else if ((flags & OperationFlags::deref) != OperationFlags::none)
        {
            std::expected<otava::intermediate::Instruction*, int> rv = emitter.EmitLoad(
                static_cast<otava::intermediate::Value*>(variable->IrObject(emitter, sourcePos, context)));
            if (!rv) return std::unexpected<int>(rv.error());
            otava::intermediate::Value* value = *rv;
            std::uint8_t derefCount = GetDerefCount(flags);
            for (std::uint8_t i = 0; i < derefCount; ++i)
            {
                rv = emitter.EmitLoad(value);
                if (!rv) return std::unexpected<int>(rv.error());
                value = *rv;
            }
            emitter.Stack().Push(value);
        }
        else
        {
            std::expected<otava::intermediate::Instruction*, int> rv = emitter.EmitLoad(
                static_cast<otava::intermediate::Value*>(variable->IrObject(emitter, sourcePos, context)));
            if (!rv) return std::unexpected<int>(rv.error());
            emitter.Stack().Push(*rv);
        }
    }
    else if (variable->IsMemberVariable())
    {
        if (variable->IsStatic())
        {
            otava::intermediate::Value* ptr = static_cast<otava::intermediate::Value*>(variable->IrObject(emitter, sourcePos, context));
            if (!ptr)
            {
                std::expected<otava::intermediate::Value*, int> rv = context->GetBoundCompileUnit()->CreateBoundGlobalVariable(variable, emitter, sourcePos, context, true);
                if (!rv) return std::unexpected<int>(rv.error());
                ptr = *rv;
            }
            if ((flags & OperationFlags::addr) != OperationFlags::none)
            {
                emitter.Stack().Push(ptr);
            }
            else if ((flags & OperationFlags::deref) != OperationFlags::none)
            {
                std::expected<otava::intermediate::Instruction*, int> rv = emitter.EmitLoad(ptr);
                if (!rv) return std::unexpected<int>(rv.error());
                otava::intermediate::Value* value = *rv;
                std::uint8_t n = GetDerefCount(flags);
                for (std::uint8_t i = 0; i < n; ++i)
                {
                    rv = emitter.EmitLoad(value);
                    if (!rv) return std::unexpected<int>(rv.error());
                    value = *rv;
                }
                emitter.Stack().Push(value);
            }
            else
            {
                std::expected<otava::intermediate::Instruction*, int> rv = emitter.EmitLoad(ptr);
                if (!rv) return std::unexpected<int>(rv.error());
                emitter.Stack().Push(*rv);
            }
        }
        else
        {
            if (!thisPtr)
            {
                return Error("'this ptr' of bound member variable not set", sourcePos, context);
            }
            std::expected<bool, int> rv = thisPtr->Load(emitter, OperationFlags::none, sourcePos, context);
            if (!rv) return rv;
            otava::intermediate::Value* ptr = emitter.Stack().Pop();
            std::int32_t layoutIndex = variable->LayoutIndex();
            std::expected<otava::intermediate::Value*, int> erv = emitter.EmitElemAddr(ptr, emitter.EmitLong(layoutIndex));
            if (!erv) return std::unexpected<int>(erv.error());
            otava::intermediate::Value* elementPtr = *erv;
            if ((flags & OperationFlags::addr) != OperationFlags::none)
            {
                emitter.Stack().Push(elementPtr);
            }
            else if ((flags & OperationFlags::deref) != OperationFlags::none)
            {
                std::expected<otava::intermediate::Instruction*, int> rv = emitter.EmitLoad(elementPtr);
                if (!rv) return std::unexpected<int>(rv.error());
                otava::intermediate::Value* value = *rv;
                std::uint8_t n = GetDerefCount(flags);
                for (std::uint8_t i = 0; i < n; ++i)
                {
                    std::expected<otava::intermediate::Instruction*, int> rv = emitter.EmitLoad(value);
                    if (!rv) return std::unexpected<int>(rv.error());
                    value = *rv;
                }
                emitter.Stack().Push(value);
            }
            else
            {
                std::expected<otava::intermediate::Instruction*, int> rv = emitter.EmitLoad(elementPtr);
                if (!rv) return std::unexpected<int>(rv.error());
                emitter.Stack().Push(*rv);
            }
        }
    }
    else if (variable->IsGlobalVariable())
    {
        otava::intermediate::Value* ptr = static_cast<otava::intermediate::Value*>(variable->IrObject(emitter, sourcePos, context));
        if (!ptr)
        {
            std::expected<otava::intermediate::Value*, int> rv = context->GetBoundCompileUnit()->CreateBoundGlobalVariable(variable, emitter, sourcePos, context, false);
            if (!rv) return std::unexpected<int>(rv.error());
            ptr = *rv;
        }
        if ((flags & OperationFlags::addr) != OperationFlags::none)
        {
            emitter.Stack().Push(ptr);
        }
        else if ((flags & OperationFlags::deref) != OperationFlags::none)
        {
            std::expected<otava::intermediate::Instruction*, int> rv = emitter.EmitLoad(ptr);
            if (!rv) return std::unexpected<int>(rv.error());
            otava::intermediate::Value* value = *rv;
            std::uint8_t n = GetDerefCount(flags);
            for (std::uint8_t i = 0; i < n; ++i)
            {
                rv = emitter.EmitLoad(value);
                if (!rv) return std::unexpected<int>(rv.error());
                value = *rv;
            }
            emitter.Stack().Push(value);
        }
        else
        {
            std::expected<otava::intermediate::Instruction*, int> rv = emitter.EmitLoad(ptr);
            if (!rv) return std::unexpected<int>(rv.error());
            emitter.Stack().Push(*rv);
        }
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> BoundVariableNode::Store(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    if ((flags & OperationFlags::addr) != OperationFlags::none)
    {
        return Error("invalid operation flag 'addr' for variable store operation", sourcePos, context);
    }
    if (variable->IsLocalVariable())
    {
        otava::intermediate::Value* ptr = static_cast<otava::intermediate::Value*>(variable->IrObject(emitter, sourcePos, context));
        otava::intermediate::Value* value = emitter.Stack().Pop();
        if ((flags & OperationFlags::deref) != OperationFlags::none)
        {
            std::expected<otava::intermediate::Instruction*, int> rv = emitter.EmitLoad(ptr);
            if (!rv) return std::unexpected<int>(rv.error());
            ptr = *rv;
            std::uint8_t n = GetDerefCount(flags);
            for (std::uint8_t i = 1; i < n; ++i)
            {
                rv = emitter.EmitLoad(ptr);
                if (!rv) return std::unexpected<int>(rv.error());
                ptr = *rv;
            }
            if ((flags & OperationFlags::setPtr) != OperationFlags::none)
            {
                context->SetPtr(ptr);
            }
            emitter.EmitStore(value, ptr);
        }
        else
        {
            if ((flags & OperationFlags::setPtr) != OperationFlags::none)
            {
                context->SetPtr(ptr);
            }
            emitter.EmitStore(value, ptr);
        }
    }
    else if (variable->IsMemberVariable())
    {
        otava::intermediate::Value* value = emitter.Stack().Pop();
        if (!thisPtr)
        {
            return Error("'this ptr' of bound member variable not set", sourcePos, context);
        }
        std::expected<bool, int> rv = thisPtr->Load(emitter, OperationFlags::none, sourcePos, context);
        if (!rv) return rv;
        otava::intermediate::Value* ptr = emitter.Stack().Pop();
        std::int32_t layoutIndex = variable->LayoutIndex();
        std::expected<otava::intermediate::Value*, int> erv = emitter.EmitElemAddr(ptr, emitter.EmitLong(layoutIndex));
        if (!erv) return std::unexpected<int>(erv.error());
        otava::intermediate::Value* elementPtr = *erv;
        if ((flags & OperationFlags::deref) != OperationFlags::none)
        {
            std::expected<otava::intermediate::Instruction*, int> rv = emitter.EmitLoad(elementPtr);
            if (!rv) return std::unexpected<int>(rv.error());
            elementPtr = *rv;
            std::uint8_t n = GetDerefCount(flags);
            for (std::uint8_t i = 1; i < n; ++i)
            {
                rv = emitter.EmitLoad(elementPtr);
                if (!rv) return std::unexpected<int>(rv.error());
                elementPtr = *rv;
            }
            if ((flags & OperationFlags::setPtr) != OperationFlags::none)
            {
                context->SetPtr(elementPtr);
            }
            emitter.EmitStore(value, elementPtr);
        }
        else
        {
            if ((flags & OperationFlags::setPtr) != OperationFlags::none)
            {
                context->SetPtr(elementPtr);
            }
            emitter.EmitStore(value, elementPtr);
        }
    }
    else if (variable->IsGlobalVariable())
    {
        otava::intermediate::Value* value = emitter.Stack().Pop();
        otava::intermediate::Value* ptr = static_cast<otava::intermediate::Value*>(variable->IrObject(emitter, sourcePos, context));
        if (!ptr)
        {
            std::expected<otava::intermediate::Value*, int> rv = context->GetBoundCompileUnit()->CreateBoundGlobalVariable(variable, emitter, sourcePos, context, false);
            if (!rv) return std::unexpected<int>(rv.error());
            ptr = *rv;
        }
        if ((flags & OperationFlags::deref) != OperationFlags::none)
        {
            std::expected<otava::intermediate::Instruction*, int> rv = emitter.EmitLoad(ptr);
            if (!rv) return std::unexpected<int>(rv.error());
            ptr = *rv;
            std::uint8_t n = GetDerefCount(flags);
            for (std::uint8_t i = 1; i < n; ++i)
            {
                rv = emitter.EmitLoad(ptr);
                if (!rv) return std::unexpected<int>(rv.error());
                ptr = *rv;
            }
            if ((flags & OperationFlags::setPtr) != OperationFlags::none)
            {
                context->SetPtr(ptr);
            }
            emitter.EmitStore(value, ptr);
        }
        else
        {
            if ((flags & OperationFlags::setPtr) != OperationFlags::none)
            {
                context->SetPtr(ptr);
            }
            emitter.EmitStore(value, ptr);
        }
    }
    return std::expected<bool, int>(true);
}

BoundExpressionNode* BoundVariableNode::Clone() const
{
    BoundVariableNode* clone = new BoundVariableNode(variable, GetSourcePos());
    if (thisPtr)
    {
        clone->SetThisPtr(thisPtr->Clone());
    }
    clone->SetFlags(Flags());
    return clone;
}

bool BoundVariableNode::IsBoundLocalVariable() const
{
    return variable->IsLocalVariable();
}

bool BoundVariableNode::IsBoundMemberVariable() const
{
    return variable->IsMemberVariable();
}

std::expected<bool, int> BoundVariableNode::ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<bool, int> rv = BoundExpressionNode::ModifyTypes(sourcePos, context);
    if (!rv) return rv;
    if (thisPtr)
    {
        return thisPtr->ModifyTypes(sourcePos, context);
    }
    return std::expected<bool, int>(true);
}

BoundParameterNode::BoundParameterNode(ParameterSymbol* parameter_, const soul::ast::SourcePos& sourcePos_, TypeSymbol* type) :
    BoundExpressionNode(BoundNodeKind::boundParameterNode, sourcePos_, type), parameter(parameter_)
{
}

void BoundParameterNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> BoundParameterNode::Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    if ((flags & OperationFlags::addr) != OperationFlags::none)
    {
        emitter.Stack().Push(static_cast<otava::intermediate::Value*>(parameter->IrObject(emitter, sourcePos, context)));
    }
    else if ((flags & OperationFlags::deref) != OperationFlags::none)
    {
        otava::intermediate::Value* ptr = static_cast<otava::intermediate::Value*>(parameter->IrObject(emitter, sourcePos, context));
        std::expected<otava::intermediate::Instruction*, int> rv = emitter.EmitLoad(ptr);
        if (!rv) return std::unexpected<int>(rv.error());
        otava::intermediate::Value* value = *rv;
        std::uint8_t n = GetDerefCount(flags);
        for (std::uint8_t i = 0; i < n; ++i)
        {
            rv = emitter.EmitLoad(value);
            if (!rv) return std::unexpected<int>(rv.error());
            value = *rv;
        }
        emitter.Stack().Push(value);
    }
    else
    {
        std::expected<otava::intermediate::Instruction*, int> rv = emitter.EmitLoad(
            static_cast<otava::intermediate::Value*>(parameter->IrObject(emitter, sourcePos, context)));
        if (!rv) return std::unexpected<int>(rv.error());
        emitter.Stack().Push(*rv);
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> BoundParameterNode::Store(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    otava::intermediate::Value* ptr = static_cast<otava::intermediate::Value*>(parameter->IrObject(emitter, sourcePos, context));
    otava::intermediate::Value* value = emitter.Stack().Pop();
    if ((flags & OperationFlags::addr) != OperationFlags::none)
    {
        return Error("invalid operation flag 'addr' for parameter store operation", sourcePos, context);
    }
    else if ((flags & OperationFlags::deref) != OperationFlags::none)
    {
        std::expected<otava::intermediate::Instruction*, int> rv = emitter.EmitLoad(ptr);
        if (!rv) return std::unexpected<int>(rv.error());
        ptr = *rv;
        std::uint8_t n = GetDerefCount(flags);
        for (std::uint8_t i = 1; i < n; ++i)
        {
            rv = emitter.EmitLoad(ptr);
            if (!rv) return std::unexpected<int>(rv.error());
            ptr = *rv;
        }
        if ((flags & OperationFlags::setPtr) != OperationFlags::none)
        {
            context->SetPtr(ptr);
        }
        emitter.EmitStore(value, ptr);
    }
    else
    {
        if ((flags & OperationFlags::setPtr) != OperationFlags::none)
        {
            context->SetPtr(ptr);
        }
        emitter.EmitStore(value, ptr);
    }
    return std::expected<bool, int>(true);
}

BoundExpressionNode* BoundParameterNode::Clone() const
{
    BoundExpressionNode* clone = new BoundParameterNode(parameter, GetSourcePos(), GetType());
    clone->SetFlags(Flags());
    return clone;
}

BoundEnumConstant::BoundEnumConstant(EnumConstantSymbol* enumConstant_, const soul::ast::SourcePos& sourcePos_) :
    BoundExpressionNode(BoundNodeKind::boundEnumConstantNode, sourcePos_, enumConstant_->GetEnumType()), enumConstant(enumConstant_)
{
}

void BoundEnumConstant::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> BoundEnumConstant::Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    if ((flags & OperationFlags::addr) != OperationFlags::none)
    {
        return Error("cannot take address of an enumeration constant", sourcePos, context);
    }
    else if ((flags & OperationFlags::deref) != OperationFlags::none)
    {
        return Error("cannot dereference an enumeration constant", sourcePos, context);
    }
    else
    {
        std::expected<otava::intermediate::Value*, int> irv = enumConstant->GetValue()->IrValue(emitter, sourcePos, context);
        if (!irv) return std::unexpected<int>(irv.error());
        otava::intermediate::Value* irValue = *irv;
        emitter.Stack().Push(irValue);
    }
    return std::expected<bool, int>(true);
}

BoundExpressionNode* BoundEnumConstant::Clone() const
{
    BoundExpressionNode* clone = new BoundEnumConstant(enumConstant, GetSourcePos());
    clone->SetFlags(Flags());
    return clone;
}

BoundFunctionGroupNode::BoundFunctionGroupNode(FunctionGroupSymbol* functionGroupSymbol_, const soul::ast::SourcePos& sourcePos_, TypeSymbol* type_) :
    BoundExpressionNode(BoundNodeKind::boundFunctionGroupNode, sourcePos_, type_), functionGroupSymbol(functionGroupSymbol_)
{
}

void BoundFunctionGroupNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> BoundFunctionGroupNode::Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    emitter.Stack().Push(nullptr);
    return std::expected<bool, int>(true);
}

BoundExpressionNode* BoundFunctionGroupNode::Clone() const
{
    BoundFunctionGroupNode* clone = new BoundFunctionGroupNode(functionGroupSymbol, GetSourcePos(), GetType());
    for (auto templateArg : templateArgs)
    {
        clone->AddTemplateArg(templateArg);
    }
    clone->SetFlags(Flags());
    return clone;
}

void BoundFunctionGroupNode::AddTemplateArg(TypeSymbol* templateArg)
{
    templateArgs.push_back(templateArg);
}

BoundClassGroupNode::BoundClassGroupNode(ClassGroupSymbol* classGroupSymbol_, const soul::ast::SourcePos& sourcePos_, TypeSymbol* type_) :
    BoundExpressionNode(BoundNodeKind::boundClassGroupNode, sourcePos_, type_), classGroupSymbol(classGroupSymbol_)
{
}

void BoundClassGroupNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> BoundClassGroupNode::Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    emitter.Stack().Push(nullptr);
    return std::expected<bool, int>(true);
}

BoundExpressionNode* BoundClassGroupNode::Clone() const
{
    BoundClassGroupNode* clone = new BoundClassGroupNode(classGroupSymbol, GetSourcePos(), GetType());
    for (auto templateArg : templateArgs)
    {
        clone->AddTemplateArg(templateArg);
    }
    clone->SetFlags(Flags());
    return clone;
}

void BoundClassGroupNode::AddTemplateArg(TypeSymbol* templateArg)
{
    templateArgs.push_back(templateArg);
}

BoundAliasGroupNode::BoundAliasGroupNode(AliasGroupSymbol* aliasGroupSymbol_, const soul::ast::SourcePos& sourcePos_, TypeSymbol* type_) :
    BoundExpressionNode(BoundNodeKind::boundAliasGroupNode, sourcePos_, type_), aliasGroupSymbol(aliasGroupSymbol_)
{
}

void BoundAliasGroupNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> BoundAliasGroupNode::Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    emitter.Stack().Push(nullptr);
    return std::expected<bool, int>(true);
}

BoundExpressionNode* BoundAliasGroupNode::Clone() const
{
    BoundAliasGroupNode* clone = new BoundAliasGroupNode(aliasGroupSymbol, GetSourcePos(), GetType());
    for (auto templateArg : templateArgs)
    {
        clone->AddTemplateArg(templateArg);
    }
    clone->SetFlags(Flags());
    return clone;
}

void BoundAliasGroupNode::AddTemplateArg(TypeSymbol* templateArg)
{
    templateArgs.push_back(templateArg);
}

BoundTypeNode::BoundTypeNode(TypeSymbol* type_, const soul::ast::SourcePos& sourcePos_) :
    BoundExpressionNode(BoundNodeKind::boundTypeNode, sourcePos_, type_)
{
}

void BoundTypeNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

BoundExpressionNode* BoundTypeNode::Clone() const
{
    BoundExpressionNode* clone = new BoundTypeNode(GetType(), GetSourcePos());
    clone->SetFlags(Flags());
    return clone;
}

BoundMemberExprNode::BoundMemberExprNode(BoundExpressionNode* subject_, BoundExpressionNode* member_, otava::ast::NodeKind op_, const soul::ast::SourcePos& sourcePos_,
    TypeSymbol* type_) :
    BoundExpressionNode(BoundNodeKind::boundMemberExprNode, sourcePos_, type_), subject(subject_), member(member_), op(op_)
{
}

void BoundMemberExprNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

BoundExpressionNode* BoundMemberExprNode::Clone() const
{
    BoundExpressionNode* clone = new BoundMemberExprNode(subject->Clone(), member->Clone(), op, GetSourcePos(), GetType());
    clone->SetFlags(Flags());
    return clone;
}

std::expected<bool, int> BoundMemberExprNode::ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<bool, int> rv = BoundExpressionNode::ModifyTypes(sourcePos, context);
    if (!rv) return rv;
    rv = subject->ModifyTypes(sourcePos, context);
    if (!rv) return rv;
    rv = member->ModifyTypes(sourcePos, context);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

BoundFunctionCallNode::BoundFunctionCallNode(FunctionSymbol* functionSymbol_, const soul::ast::SourcePos& sourcePos_, TypeSymbol* type_) :
    BoundExpressionNode(BoundNodeKind::boundFunctionCallNode, sourcePos_, type_), functionSymbol(functionSymbol_)
{
}

void BoundFunctionCallNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

bool BoundFunctionCallNode::HasValue() const
{
    return functionSymbol->ReturnType() && !functionSymbol->ReturnType()->IsVoidType();
}

void BoundFunctionCallNode::AddArgument(BoundExpressionNode* arg)
{
    args.push_back(std::unique_ptr<BoundExpressionNode>(arg));
}

std::expected<bool, int> BoundFunctionCallNode::Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::vector<BoundExpressionNode*> arguments;
    for (const auto& arg : args)
    {
        arguments.push_back(arg.get());
    }
    if (GetFlag(BoundExpressionFlags::virtualCall))
    {
        flags = flags | OperationFlags::virtualCall;
    }
    std::expected<bool, int> rv = functionSymbol->GenerateCode(emitter, arguments, flags, sourcePos, context);
    if (!rv) return rv;
    if ((flags & OperationFlags::deref) != OperationFlags::none && functionSymbol->Name() != U"operator_bool")
    {
        otava::intermediate::Value* value = emitter.Stack().Pop();
        std::uint8_t n = GetDerefCount(flags);
        for (std::uint8_t i = 0; i < n; ++i)
        {
            std::expected<otava::intermediate::Instruction*, int> rv = emitter.EmitLoad(value);
            if (!rv) return std::unexpected<int>(rv.error());
            value = *rv;
        }
        emitter.Stack().Push(value);
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> BoundFunctionCallNode::Store(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    if ((flags & OperationFlags::addr) != OperationFlags::none)
    {
        return Error("cannot take address of a function call", sourcePos, context);
    }
    else
    {
        otava::intermediate::Value* value = emitter.Stack().Pop();
        std::vector<BoundExpressionNode*> arguments;
        for (const auto& arg : args)
        {
            arguments.push_back(arg.get());
        }
        OperationFlags callFlags = OperationFlags::none;
        if (GetFlag(BoundExpressionFlags::virtualCall))
        {
            callFlags = callFlags | OperationFlags::virtualCall;
        }
        std::expected<bool, int> rv = functionSymbol->GenerateCode(emitter, arguments, callFlags, sourcePos, context);
        if (!rv) return rv;
        otava::intermediate::Value* ptr = emitter.Stack().Pop();
        if ((flags & OperationFlags::deref) != OperationFlags::none || GetFlag(BoundExpressionFlags::deref))
        {
            std::uint8_t n = GetDerefCount(flags);
            for (std::uint8_t i = 1; i < n; ++i)
            {
                std::expected<otava::intermediate::Instruction*, int> rv = emitter.EmitLoad(ptr);
                if (!rv) return std::unexpected<int>(rv.error());
                ptr = *rv;
            }
            if ((flags & OperationFlags::setPtr) != OperationFlags::none)
            {
                context->SetPtr(ptr);
            }
            emitter.EmitStore(value, ptr);
        }
        else
        {
            if ((flags & OperationFlags::setPtr) != OperationFlags::none)
            {
                context->SetPtr(ptr);
            }
            std::expected<otava::intermediate::Instruction*, int> rv = emitter.EmitLoad(value);
            if (!rv) return std::unexpected<int>(rv.error());
            emitter.EmitStore(*rv, ptr);
        }
    }
    return std::expected<bool, int>(true);
}

bool BoundFunctionCallNode::IsLvalueExpression() const
{
    if (functionSymbol->IsArrayElementAccess()) return true;
    TypeSymbol* returnType = functionSymbol->ReturnType();
    if (returnType && !returnType->IsVoidType())
    {
        return !returnType->IsConstType() && returnType->IsLValueRefType();
    }
    return false;
}

BoundExpressionNode* BoundFunctionCallNode::Clone() const
{
    BoundFunctionCallNode* clone = new BoundFunctionCallNode(functionSymbol, GetSourcePos(), GetType());
    for (auto& arg : args)
    {
        clone->AddArgument(arg->Clone());
    }
    clone->SetFlags(Flags());
    return clone;
}

bool BoundFunctionCallNode::CallsClassConstructor(ClassTypeSymbol*& cls, BoundExpressionNode*& firstArg, FunctionDefinitionSymbol*& destructor) const
{
    if (functionSymbol->GetFunctionKind() != otava::symbols::FunctionKind::constructor) return false;
    if (args.empty()) return false;
    firstArg = args[0].get();
    if (!firstArg->IsBoundAddressOfNode()) return false;
    BoundAddressOfNode* addrOf = static_cast<BoundAddressOfNode*>(firstArg);
    TypeSymbol* subjectType = addrOf->Subject()->GetType();
    if (!subjectType->IsClassTypeSymbol()) return false;
    cls = static_cast<ClassTypeSymbol*>(subjectType);
    destructor = functionSymbol->Destructor();
    return true;
}

bool BoundFunctionCallNode::IsNoReturnFunctionCall() const
{
    if ((functionSymbol->Qualifiers() & FunctionQualifiers::noreturn) != FunctionQualifiers::none)
    {
        return true;
    }
    return false;
}

std::expected<bool, int> BoundFunctionCallNode::ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<bool, int> rv = BoundExpressionNode::ModifyTypes(sourcePos, context);
    if (!rv) return rv;
    for (auto& arg : args)
    {
        rv = arg->ModifyTypes(sourcePos, context);
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

BoundEmptyFunctionCallNode::BoundEmptyFunctionCallNode(const soul::ast::SourcePos& sourcePos_) :
    BoundExpressionNode(BoundNodeKind::boundEmptyFunctionCallNode, sourcePos_, nullptr)
{
}

void BoundEmptyFunctionCallNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> BoundEmptyFunctionCallNode::Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    return std::expected<bool, int>(true);
}

BoundExpressionNode* BoundEmptyFunctionCallNode::Clone() const
{
    BoundExpressionNode* clone = new BoundEmptyFunctionCallNode(GetSourcePos());
    clone->SetFlags(Flags());
    return clone;
}

BoundFunctionPtrCallNode::BoundFunctionPtrCallNode(const soul::ast::SourcePos& sourcePos_, TypeSymbol* type_) :
    BoundExpressionNode(BoundNodeKind::boundFunctionPtrCallNode, sourcePos_, type_)
{
}

void BoundFunctionPtrCallNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

void BoundFunctionPtrCallNode::AddArgument(BoundExpressionNode* arg)
{
    args.push_back(std::unique_ptr<BoundExpressionNode>(arg));
}

std::expected<bool, int> BoundFunctionPtrCallNode::Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    otava::intermediate::Value* callee = nullptr;
    std::vector<otava::intermediate::Value*> irArgs;
    bool first = true;
    for (const auto& arg : args)
    {
        std::expected<bool, int> rv = arg->Load(emitter, OperationFlags::none, sourcePos, context);
        if (!rv) return rv;
        otava::intermediate::Value* irArg = emitter.Stack().Pop();
        if (first)
        {
            callee = irArg;
            first = false;
        }
        else
        {
            irArgs.push_back(irArg);
        }
    }
    std::expected<otava::intermediate::Value*, int> rv = emitter.EmitCall(callee, irArgs);
    if (!rv) return std::unexpected<int>(rv.error());
    otava::intermediate::Value* value = *rv;
    emitter.Stack().Push(value);
    return std::expected<bool, int>(true);
}

BoundExpressionNode* BoundFunctionPtrCallNode::Clone() const
{
    BoundFunctionPtrCallNode* clone = new BoundFunctionPtrCallNode(GetSourcePos(), GetType());
    for (auto& arg : args)
    {
        clone->AddArgument(arg->Clone());
    }
    clone->SetFlags(Flags());
    return clone;
}

std::expected<bool, int> BoundFunctionPtrCallNode::ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<bool, int> rv = BoundExpressionNode::ModifyTypes(sourcePos, context);
    if (!rv) return rv;
    for (auto& arg : args)
    {
        rv = arg->ModifyTypes(sourcePos, context);
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

BoundExpressionSequenceNode::BoundExpressionSequenceNode(const soul::ast::SourcePos& sourcePos_, BoundExpressionNode* left_, BoundExpressionNode* right_) :
    BoundExpressionNode(BoundNodeKind::boundExpressionSequenceNode, sourcePos_, right_->GetType()), left(left_), right(right_)
{
}

void BoundExpressionSequenceNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

bool BoundExpressionSequenceNode::IsLvalueExpression() const
{
    return right->IsLvalueExpression();
}

BoundExpressionNode* BoundExpressionSequenceNode::Clone() const
{
    BoundExpressionSequenceNode* clone = new BoundExpressionSequenceNode(GetSourcePos(), left->Clone(), right->Clone());
    clone->SetFlags(Flags());
    return clone;
}

std::expected<bool, int> BoundExpressionSequenceNode::Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<bool, int> rv = left->Load(emitter, flags, sourcePos, context);
    if (!rv) return rv;
    if (left->HasValue())
    {
        emitter.Stack().Pop();
    }
    rv = right->Load(emitter, flags, sourcePos, context);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> BoundExpressionSequenceNode::Store(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<bool, int> rv = left->Load(emitter, flags, sourcePos, context);
    if (!rv) return rv;
    if (left->HasValue())
    {
        emitter.Stack().Pop();
    }
    rv = right->Store(emitter, flags, sourcePos, context);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

bool BoundExpressionSequenceNode::HasValue() const
{
    return right->HasValue();
}

std::expected<bool, int> BoundExpressionSequenceNode::ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<bool, int> rv = BoundExpressionNode::ModifyTypes(sourcePos, context);
    if (!rv) return rv;
    rv = left->ModifyTypes(sourcePos, context);
    if (!rv) return rv;
    rv = right->ModifyTypes(sourcePos, context);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

BoundExpressionListNode::BoundExpressionListNode(const soul::ast::SourcePos& sourcePos_) :
    BoundExpressionNode(BoundNodeKind::boundExpressionListNode, sourcePos_, nullptr)
{
}

void BoundExpressionListNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

BoundExpressionNode* BoundExpressionListNode::Clone() const
{
    BoundExpressionListNode* clone = new BoundExpressionListNode(GetSourcePos());
    for (auto& expr : exprs)
    {
        clone->AddExpression(expr->Clone());
    }
    clone->SetFlags(Flags());
    return clone;
}

void BoundExpressionListNode::AddExpression(BoundExpressionNode* expr)
{
    if (exprs.empty())
    {
        SetType(expr->GetType());
    }
    else
    {
        SetType(nullptr);
    }
    exprs.push_back(std::unique_ptr<BoundExpressionNode>(expr));
}

std::expected<bool, int> BoundExpressionListNode::ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<bool, int> rv = BoundExpressionNode::ModifyTypes(sourcePos, context);
    if (!rv) return rv;
    for (auto& expr : exprs)
    {
        rv = expr->ModifyTypes(sourcePos, context);
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

BoundConjunctionNode::BoundConjunctionNode(BoundExpressionNode* left_, BoundExpressionNode* right_, const soul::ast::SourcePos& sourcePos_, TypeSymbol* boolType) :
    BoundExpressionNode(BoundNodeKind::boundConjunctionNode, sourcePos_, boolType), left(left_), right(right_)
{
}

void BoundConjunctionNode::SetTemporary(BoundVariableNode* temporary_)
{
    temporary.reset(temporary_);
}

void BoundConjunctionNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

bool BoundConjunctionNode::HasValue() const
{
    return true;
}

std::expected<bool, int> BoundConjunctionNode::Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<bool, int> rv = temporary->Load(emitter, OperationFlags::addr, sourcePos, context);
    if (!rv) return rv;
    otava::intermediate::Value* temp = emitter.Stack().Pop();
    rv = left->Load(emitter, OperationFlags::none, sourcePos, context);
    if (!rv) return rv;
    otava::intermediate::Value* leftValue = emitter.Stack().Pop();
    otava::intermediate::BasicBlock* trueBlock = emitter.CreateBasicBlock();
    otava::intermediate::BasicBlock* rightBlock = emitter.CreateBasicBlock();
    otava::intermediate::BasicBlock* falseBlock = emitter.CreateBasicBlock();
    otava::intermediate::BasicBlock* nextBlock = emitter.CreateBasicBlock();
    emitter.EmitBranch(leftValue, rightBlock, falseBlock);
    emitter.SetCurrentBasicBlock(rightBlock);
    rv = right->Load(emitter, OperationFlags::none, sourcePos, context);
    if (!rv) return rv;
    otava::intermediate::Value* rightValue = emitter.Stack().Pop();
    emitter.EmitBranch(rightValue, trueBlock, falseBlock);
    emitter.SetCurrentBasicBlock(trueBlock);
    emitter.EmitStore(emitter.EmitBool(true), temp);
    emitter.EmitJump(nextBlock);
    emitter.SetCurrentBasicBlock(falseBlock);
    emitter.EmitStore(emitter.EmitBool(false), temp);
    emitter.EmitJump(nextBlock);
    emitter.SetCurrentBasicBlock(nextBlock);
    std::expected<otava::intermediate::Instruction*, int> lrv = emitter.EmitLoad(temp);
    if (!lrv) return std::unexpected<int>(lrv.error());
    otava::intermediate::Value* value = *lrv;
    emitter.Stack().Push(value);
    return std::expected<bool, int>(true);
}

BoundExpressionNode* BoundConjunctionNode::Clone() const
{
    BoundConjunctionNode* clone = new BoundConjunctionNode(left->Clone(), right->Clone(), GetSourcePos(), GetType());
    if (temporary)
    {
        clone->SetTemporary(static_cast<BoundVariableNode*>(temporary->Clone()));
    }
    clone->SetFlags(Flags());
    return clone;
}

std::expected<bool, int> BoundConjunctionNode::ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<bool, int> rv = BoundExpressionNode::ModifyTypes(sourcePos, context);
    if (!rv) return rv;
    rv = left->ModifyTypes(sourcePos, context);
    if (!rv) return rv;
    rv = right->ModifyTypes(sourcePos, context);
    if (!rv) return rv;
    if (temporary)
    {
        rv = temporary->ModifyTypes(sourcePos, context);
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

BoundDisjunctionNode::BoundDisjunctionNode(BoundExpressionNode* left_, BoundExpressionNode* right_, const soul::ast::SourcePos& sourcePos_, TypeSymbol* boolType) :
    BoundExpressionNode(BoundNodeKind::boundDisjunctionNode, sourcePos_, boolType), left(left_), right(right_)
{
}

void BoundDisjunctionNode::SetTemporary(BoundVariableNode* temporary_)
{
    temporary.reset(temporary_);
}

void BoundDisjunctionNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

bool BoundDisjunctionNode::HasValue() const
{
    return true;
}

std::expected<bool, int> BoundDisjunctionNode::Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<bool, int> rv = temporary->Load(emitter, OperationFlags::addr, sourcePos, context);
    if (!rv) return rv;
    otava::intermediate::Value* temp = emitter.Stack().Pop();
    rv = left->Load(emitter, OperationFlags::none, sourcePos, context);
    if (!rv) return rv;
    otava::intermediate::Value* leftValue = emitter.Stack().Pop();
    otava::intermediate::BasicBlock* trueBlock = emitter.CreateBasicBlock();
    otava::intermediate::BasicBlock* rightBlock = emitter.CreateBasicBlock();
    otava::intermediate::BasicBlock* falseBlock = emitter.CreateBasicBlock();
    otava::intermediate::BasicBlock* nextBlock = emitter.CreateBasicBlock();
    emitter.EmitBranch(leftValue, trueBlock, rightBlock);
    emitter.SetCurrentBasicBlock(rightBlock);
    rv = right->Load(emitter, OperationFlags::none, sourcePos, context);
    if (!rv) return rv;
    otava::intermediate::Value* rightValue = emitter.Stack().Pop();
    emitter.EmitBranch(rightValue, trueBlock, falseBlock);
    emitter.SetCurrentBasicBlock(trueBlock);
    emitter.EmitStore(emitter.EmitBool(true), temp);
    emitter.EmitJump(nextBlock);
    emitter.SetCurrentBasicBlock(falseBlock);
    emitter.EmitStore(emitter.EmitBool(false), temp);
    emitter.EmitJump(nextBlock);
    emitter.SetCurrentBasicBlock(nextBlock);
    std::expected<otava::intermediate::Instruction*, int> lrv = emitter.EmitLoad(temp);
    if (!lrv) return std::unexpected<int>(lrv.error());
    otava::intermediate::Value* value = *lrv;
    emitter.Stack().Push(value);
    return std::expected<bool, int>(true);
}

BoundExpressionNode* BoundDisjunctionNode::Clone() const
{
    BoundDisjunctionNode* clone = new BoundDisjunctionNode(left->Clone(), right->Clone(), GetSourcePos(), GetType());
    if (temporary)
    {
        clone->SetTemporary(static_cast<BoundVariableNode*>(temporary->Clone()));
    }
    clone->SetFlags(Flags());
    return clone;
}

std::expected<bool, int> BoundDisjunctionNode::ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<bool, int> rv = BoundExpressionNode::ModifyTypes(sourcePos, context);
    if (!rv) return rv;
    rv = left->ModifyTypes(sourcePos, context);
    if (!rv) return rv;
    rv = right->ModifyTypes(sourcePos, context);
    if (!rv) return rv;
    if (temporary)
    {
        rv = temporary->ModifyTypes(sourcePos, context);
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

BoundConversionNode::BoundConversionNode(BoundExpressionNode* subject_, FunctionSymbol* conversionFunction_, const soul::ast::SourcePos& sourcePos_) :
    BoundExpressionNode(BoundNodeKind::boundConversionNode, sourcePos_, conversionFunction_->ReturnType()), subject(subject_), conversionFunction(conversionFunction_)
{
}

void BoundConversionNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> BoundConversionNode::Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<bool, int> rv = subject->Load(emitter, flags, sourcePos, context);
    if (!rv) return rv;
    std::vector<BoundExpressionNode*> args;
    rv = conversionFunction->GenerateCode(emitter, args, flags, sourcePos, context);
    if (!rv) return rv;
    if ((flags & OperationFlags::derefAfterConv) != OperationFlags::none)
    {
        otava::intermediate::Value* value = emitter.Stack().Pop();
        std::uint8_t derefCount = GetDerefCount(flags);
        for (std::uint8_t i = 0; i < derefCount; ++i)
        {
            std::expected<otava::intermediate::Instruction*, int> rv = emitter.EmitLoad(value);
            if (!rv) return std::unexpected<int>(rv.error());
            value = *rv;
        }
        emitter.Stack().Push(value);
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> BoundConversionNode::Store(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<bool, int> rv = Load(emitter, flags, sourcePos, context);
    if (!rv) return rv;
    rv = subject->Store(emitter, flags, sourcePos, context);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

bool BoundConversionNode::IsLvalueExpression() const
{
    return false; // todo???
}

BoundExpressionNode* BoundConversionNode::Clone() const
{
    BoundExpressionNode* clone = new BoundConversionNode(subject->Clone(), conversionFunction, GetSourcePos());
    clone->SetFlags(Flags());
    return clone;
}

std::expected<bool, int> BoundConversionNode::ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<bool, int> rv = BoundExpressionNode::ModifyTypes(sourcePos, context);
    if (!rv) return rv;
    rv = subject->ModifyTypes(sourcePos, context);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

BoundAddressOfNode::BoundAddressOfNode(BoundExpressionNode* subject_, const soul::ast::SourcePos& sourcePos_, TypeSymbol* type_) :
    BoundExpressionNode(BoundNodeKind::boundAddressOfNode, sourcePos_, type_), subject(subject_)
{
}

void BoundAddressOfNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> BoundAddressOfNode::Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (!subject->IsBoundDereferenceNode())
    {
        std::expected<bool, int> rv = subject->Load(emitter, OperationFlags::addr, sourcePos, context);
        if (!rv) return rv;
    }
    else
    {
        BoundDereferenceNode* derefExpr = static_cast<BoundDereferenceNode*>(subject.get());
        std::expected<bool, int> rv = derefExpr->Subject()->Load(emitter, flags, sourcePos, context);
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> BoundAddressOfNode::Store(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (!subject->IsBoundDereferenceNode())
    {
        std::expected<bool, int> rv = subject->Store(emitter, OperationFlags::addr | (flags & OperationFlags::setPtr), sourcePos, context);
        if (!rv) return rv;
    }
    else
    {
        BoundDereferenceNode* derefExpr = static_cast<BoundDereferenceNode*>(subject.get());
        std::expected<bool, int> rv = derefExpr->Subject()->Store(emitter, flags, sourcePos, context);
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

BoundExpressionNode* BoundAddressOfNode::Clone() const
{
    BoundExpressionNode* clone = new BoundAddressOfNode(subject->Clone(), GetSourcePos(), GetType());
    clone->SetFlags(Flags());
    return clone;
}

std::expected<bool, int> BoundAddressOfNode::ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<bool, int> rv = BoundExpressionNode::ModifyTypes(sourcePos, context);
    if (!rv) return rv;
    rv = subject->ModifyTypes(sourcePos, context);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

BoundDereferenceNode::BoundDereferenceNode(BoundExpressionNode* subject_, const soul::ast::SourcePos& sourcePos_, TypeSymbol* type_) :
    BoundExpressionNode(BoundNodeKind::boundDereferenceNode, sourcePos_, type_), subject(subject_), kind(OperationFlags::deref)
{
}

BoundDereferenceNode::BoundDereferenceNode(BoundExpressionNode* subject_, const soul::ast::SourcePos& sourcePos_, TypeSymbol* type_, OperationFlags kind_) :
    BoundExpressionNode(BoundNodeKind::boundDereferenceNode, sourcePos_, type_), subject(subject_), kind(kind_)
{
}

void BoundDereferenceNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> BoundDereferenceNode::Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (!subject->IsBoundAddressOfNode())
    {
        if (GetDerefCount(flags) == 0 && (flags & OperationFlags::addr) != OperationFlags::none)
        {
            std::expected<bool, int> rv = subject->Load(emitter, OperationFlags::none, sourcePos, context);
            if (!rv) return rv;
        }
        else
        {
            std::expected<bool, int> rv = subject->Load(emitter, SetDerefCount(kind, GetDerefCount(flags) + static_cast<std::uint8_t>(1)), sourcePos, context);
            if (!rv) return rv;
        }
    }
    else
    {
        BoundAddressOfNode* addressOfExpr = static_cast<BoundAddressOfNode*>(subject.get());
        std::expected<bool, int> rv = addressOfExpr->Subject()->Load(emitter, flags, sourcePos, context);
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> BoundDereferenceNode::Store(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (!subject->IsBoundAddressOfNode())
    {
        std::expected<bool, int> rv = subject->Store(emitter, SetDerefCount(OperationFlags::deref | (flags & OperationFlags::setPtr), 
            GetDerefCount(flags) + static_cast<std::uint8_t>(1)), sourcePos, context);
        if (!rv) return rv;
    }
    else
    {
        BoundAddressOfNode* addressOfExpr = static_cast<BoundAddressOfNode*>(subject.get());
        std::expected<bool, int> rv = addressOfExpr->Subject()->Store(emitter, flags, sourcePos, context);
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

BoundExpressionNode* BoundDereferenceNode::Clone() const
{
    BoundExpressionNode* clone = new BoundDereferenceNode(subject->Clone(), GetSourcePos(), GetType(), kind);
    clone->SetFlags(Flags());
    return clone;
}

std::expected<bool, int> BoundDereferenceNode::ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<bool, int> rv = BoundExpressionNode::ModifyTypes(sourcePos, context);
    if (!rv) return rv;
    rv = subject->ModifyTypes(sourcePos, context);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

BoundRefToPtrNode::BoundRefToPtrNode(BoundExpressionNode* subject_, const soul::ast::SourcePos& sourcePos_, TypeSymbol* type_) :
    BoundExpressionNode(BoundNodeKind::boundRefToPtrNode, sourcePos_, type_), subject(subject_)
{
}

void BoundRefToPtrNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> BoundRefToPtrNode::Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    return subject->Load(emitter, flags, sourcePos, context);
}

std::expected<bool, int> BoundRefToPtrNode::Store(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    return subject->Store(emitter, flags, sourcePos, context);
}

BoundExpressionNode* BoundRefToPtrNode::Clone() const
{
    BoundExpressionNode* clone = new BoundRefToPtrNode(subject->Clone(), GetSourcePos(), GetType());
    clone->SetFlags(Flags());
    return clone;
}

std::expected<bool, int> BoundRefToPtrNode::ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<bool, int> rv = BoundExpressionNode::ModifyTypes(sourcePos, context);
    if (!rv) return rv;
    rv = subject->ModifyTypes(sourcePos, context);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

BoundPtrToRefNode::BoundPtrToRefNode(BoundExpressionNode* subject_, const soul::ast::SourcePos& sourcePos_, TypeSymbol* type_) :
    BoundExpressionNode(BoundNodeKind::boundPtrToRefNode, sourcePos_, type_), subject(subject_)
{
}

void BoundPtrToRefNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

BoundExpressionNode* BoundPtrToRefNode::Clone() const
{
    BoundExpressionNode* clone = new BoundPtrToRefNode(subject->Clone(), GetSourcePos(), GetType());
    clone->SetFlags(Flags());
    return clone;
}

std::expected<bool, int> BoundPtrToRefNode::Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    return subject->Load(emitter, flags, sourcePos, context);
}

std::expected<bool, int> BoundPtrToRefNode::Store(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    return subject->Store(emitter, flags, sourcePos, context);
}

std::expected<bool, int> BoundPtrToRefNode::ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<bool, int> rv = BoundExpressionNode::ModifyTypes(sourcePos, context);
    if (!rv) return rv;
    rv = subject->ModifyTypes(sourcePos, context);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

BoundDefaultInitNode::BoundDefaultInitNode(BoundExpressionNode* subject_, const soul::ast::SourcePos& sourcePos_) :
    BoundExpressionNode(BoundNodeKind::boundDefaultInitNode, sourcePos_, subject_->GetType()), subject(subject_)
{
}

void BoundDefaultInitNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> BoundDefaultInitNode::Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    return subject->Load(emitter, flags | OperationFlags::defaultInit, sourcePos, context);
}

std::expected<bool, int> BoundDefaultInitNode::Store(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    return subject->Store(emitter, flags | OperationFlags::defaultInit, sourcePos, context);
}

BoundExpressionNode* BoundDefaultInitNode::Clone() const
{
    BoundExpressionNode* clone = new BoundDefaultInitNode(subject->Clone(), GetSourcePos());
    clone->SetFlags(Flags());
    return clone;
}

std::expected<bool, int> BoundDefaultInitNode::ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<bool, int> rv = BoundExpressionNode::ModifyTypes(sourcePos, context);
    if (!rv) return rv;
    rv = subject->ModifyTypes(sourcePos, context);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

BoundTemporaryNode::BoundTemporaryNode(BoundExpressionNode* rvalueExpr_, BoundVariableNode* backingStore_, const soul::ast::SourcePos& sourcePos_) :
    BoundExpressionNode(BoundNodeKind::boundTemporaryNode, sourcePos_, rvalueExpr_->GetType()), rvalueExpr(rvalueExpr_), backingStore(backingStore_)
{
}

std::expected<bool, int> BoundTemporaryNode::Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (!backingStore)
    {
        return Error("backing store of temporary not set", sourcePos, context);
    }
    std::expected<bool, int> rv = rvalueExpr->Load(emitter, OperationFlags::none, sourcePos, context);
    if (!rv) return rv;
    rv = backingStore->Store(emitter, OperationFlags::none, sourcePos, context);
    if (!rv) return rv;
    if ((flags & OperationFlags::addr) != OperationFlags::none)
    {
        rv = backingStore->Load(emitter, OperationFlags::addr, sourcePos, context);
        if (!rv) return rv;
    }
    else if ((flags & OperationFlags::deref) != OperationFlags::none)
    {
        rv = backingStore->Load(emitter, SetDerefCount(OperationFlags::deref, GetDerefCount(flags) + static_cast<std::uint8_t>(1)), sourcePos, context);
        if (!rv) return rv;
    }
    else
    {
        rv = backingStore->Load(emitter, OperationFlags::none, sourcePos, context);
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> BoundTemporaryNode::Store(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    return backingStore->Store(emitter, OperationFlags::none, sourcePos, context);
}

void BoundTemporaryNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

BoundExpressionNode* BoundTemporaryNode::Clone() const
{
    BoundExpressionNode* clone = new BoundTemporaryNode(rvalueExpr->Clone(), static_cast<BoundVariableNode*>(backingStore->Clone()), GetSourcePos());
    clone->SetFlags(Flags());
    return clone;
}

std::expected<bool, int> BoundTemporaryNode::ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<bool, int> rv = BoundExpressionNode::ModifyTypes(sourcePos, context);
    if (!rv) return rv;
    rv = rvalueExpr->ModifyTypes(sourcePos, context);
    if (!rv) return rv;
    rv = backingStore->ModifyTypes(sourcePos, context);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

BoundConstructTemporaryNode::BoundConstructTemporaryNode(BoundExpressionNode* constructorCall_, BoundExpressionNode* temporary_, const soul::ast::SourcePos& sourcePos_) :
    BoundExpressionNode(BoundNodeKind::boundConstructTemporaryNode, sourcePos_, temporary_->GetType()), constructorCall(constructorCall_), temporary(temporary_)
{
}

std::expected<bool, int> BoundConstructTemporaryNode::Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<bool, int> rv = constructorCall->Load(emitter, OperationFlags::defaultInit, sourcePos, context);
    if (!rv) return rv;
    rv = temporary->Load(emitter, flags, sourcePos, context);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> BoundConstructTemporaryNode::Store(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    return temporary->Store(emitter, flags, sourcePos, context);
}

void BoundConstructTemporaryNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

BoundExpressionNode* BoundConstructTemporaryNode::Clone() const
{
    BoundExpressionNode* clone = new BoundConstructTemporaryNode(constructorCall->Clone(), temporary->Clone(), GetSourcePos());
    clone->SetFlags(Flags());
    return clone;
}

std::expected<bool, int> BoundConstructTemporaryNode::ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<bool, int> rv = BoundExpressionNode::ModifyTypes(sourcePos, context);
    if (!rv) return rv;
    rv = constructorCall->ModifyTypes(sourcePos, context);
    if (!rv) return rv;
    rv = temporary->ModifyTypes(sourcePos, context);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

BoundConstructExpressionNode::BoundConstructExpressionNode(BoundExpressionNode* allocation_, BoundExpressionNode* constructObjectCall_, TypeSymbol* type_,
    bool hasPlacement_, const soul::ast::SourcePos& sourcePos_) :
    BoundExpressionNode(BoundNodeKind::boundConstructExpressionNode, sourcePos_, type_), allocation(allocation_), constructObjectCall(constructObjectCall_),
    hasPlacement(hasPlacement_)
{
}

std::expected<bool, int> BoundConstructExpressionNode::Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<bool, int> rv = allocation->Load(emitter, flags | OperationFlags::dup, sourcePos, context);
    if (!rv) return rv;
    rv = constructObjectCall->Load(emitter, flags | OperationFlags::storeDeref, sourcePos, context);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

void BoundConstructExpressionNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

BoundExpressionNode* BoundConstructExpressionNode::Clone() const
{
    BoundExpressionNode* clone = new BoundConstructExpressionNode(allocation->Clone(), constructObjectCall->Clone(), GetType(), hasPlacement, GetSourcePos());
    clone->SetFlags(Flags());
    return clone;
}

std::expected<bool, int> BoundConstructExpressionNode::ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<bool, int> rv = BoundExpressionNode::ModifyTypes(sourcePos, context);
    if (!rv) return rv;
    rv = allocation->ModifyTypes(sourcePos, context);
    if (!rv) return rv;
    rv = constructObjectCall->ModifyTypes(sourcePos, context);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

BoundGlobalVariableDefinitionNode::BoundGlobalVariableDefinitionNode(VariableSymbol* globalVariable_, const soul::ast::SourcePos& sourcePos_) :
    BoundNode(BoundNodeKind::boundGlobalVariableDefinitionNode, sourcePos_), globalVariable(globalVariable_)
{
}

void BoundGlobalVariableDefinitionNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

BoundEmptyDestructorNode::BoundEmptyDestructorNode(const soul::ast::SourcePos& sourcePos_) : BoundExpressionNode(BoundNodeKind::boundEmptyDestructorNode, sourcePos_, nullptr)
{
}

void BoundEmptyDestructorNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

BoundExpressionNode* BoundEmptyDestructorNode::Clone() const
{
    BoundExpressionNode* clone = new BoundEmptyDestructorNode(GetSourcePos());
    clone->SetFlags(Flags());
    return clone;
}

std::expected<bool, int> BoundEmptyDestructorNode::Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    return std::expected<bool, int>(true);
}

BoundFunctionValueNode::BoundFunctionValueNode(FunctionSymbol* function_, const soul::ast::SourcePos& sourcePos_, TypeSymbol* type_) :
    BoundExpressionNode(BoundNodeKind::boundFunctionValueNode, sourcePos_, type_), function(function_)
{
}

void BoundFunctionValueNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

BoundExpressionNode* BoundFunctionValueNode::Clone() const
{
    BoundExpressionNode* clone = new BoundFunctionValueNode(function, GetSourcePos(), GetType());
    clone->SetFlags(Flags());
    return clone;
}

std::expected<bool, int> BoundFunctionValueNode::Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<std::string, int> is = function->IrName(context);
    if (!is) return std::unexpected<int>(is.error());
    std::expected<otava::intermediate::Type*, int> trv = function->IrType(emitter, sourcePos, context);
    if (!trv) return std::unexpected<int>(trv.error());
    otava::intermediate::Type* irType = *trv;
    std::expected<otava::intermediate::Function*, int> rv = emitter.GetOrInsertFunction(*is, static_cast<otava::intermediate::FunctionType*>(irType));
    if (!rv) return std::unexpected<int>(rv.error());
    otava::intermediate::Value* functionValue = emitter.EmitSymbolValue(irType, *is);
    std::expected<otava::intermediate::Type*, int> vrv = emitter.MakePtrType(emitter.GetVoidType());
    if (!vrv) return std::unexpected<int>(vrv.error());
    otava::intermediate::Type* voidPtrIrType = *vrv;
    otava::intermediate::Value* functionValueAsVoidPtr = emitter.EmitBitcast(functionValue, voidPtrIrType);
    emitter.Stack().Push(functionValueAsVoidPtr);
    return std::expected<bool, int>(true);
}

BoundVariableAsVoidPtrNode::BoundVariableAsVoidPtrNode(BoundExpressionNode* addrOfBoundVariable_, const soul::ast::SourcePos& sourcePos_, TypeSymbol* type_) :
    BoundExpressionNode(BoundNodeKind::boundVariableAsVoidPtrNode, sourcePos_, type_), addrOfBoundVariable(addrOfBoundVariable_)
{
}

void BoundVariableAsVoidPtrNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

BoundExpressionNode* BoundVariableAsVoidPtrNode::Clone() const
{
    BoundExpressionNode* clone = new BoundVariableAsVoidPtrNode(addrOfBoundVariable->Clone(), GetSourcePos(), GetType());
    clone->SetFlags(Flags());
    return clone;
}

std::expected<bool, int> BoundVariableAsVoidPtrNode::Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<bool, int> rv = addrOfBoundVariable->Load(emitter, flags, sourcePos, context);
    if (!rv) return rv;
    otava::intermediate::Value* variableValue = emitter.Stack().Pop();
    std::expected<otava::intermediate::Type*, int> trv = emitter.MakePtrType(emitter.GetVoidType());
    if (!trv) return std::unexpected<int>(trv.error());
    otava::intermediate::Type* voidPtrIrType = *trv;
    otava::intermediate::Value* variableAsVoidPtr = emitter.EmitBitcast(variableValue, voidPtrIrType);
    emitter.Stack().Push(variableAsVoidPtr);
    return std::expected<bool, int>(true);
}

std::expected<bool, int> BoundVariableAsVoidPtrNode::ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<bool, int> rv = BoundExpressionNode::ModifyTypes(sourcePos, context);
    if (!rv) return rv;
    rv = addrOfBoundVariable->ModifyTypes(sourcePos, context);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

bool InDirectSwitchStatement(BoundStatementNode* statement)
{
    BoundStatementNode* parent = statement->Parent();
    while (parent)
    {
        if (parent->IsSwitchStatementNode()) return true;
        if (parent->IsWhileStatementNode() || parent->IsDoStatementNode() || parent->IsForStatementNode()) return false;
        parent = parent->Parent();
    }
    return false;
}

} // namespace otava::symbols
