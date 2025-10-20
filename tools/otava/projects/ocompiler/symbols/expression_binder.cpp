// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.expression.binder;

import otava.symbols.alias.group.symbol;
import otava.symbols.alias.type.symbol;
import otava.symbols.bound.tree;
import otava.symbols.bound.tree.visitor;
import otava.symbols.class_group.symbol;
import otava.symbols.classes;
import otava.symbols.context;
import otava.symbols.declaration;
import otava.symbols.enums;
import otava.symbols.enum_group.symbol;
import otava.symbols.evaluator;
import otava.symbols.error;
import otava.symbols.fundamental.type.symbol;
import otava.symbols.function.kind;
import otava.symbols.function.symbol;
import otava.symbols.function.group.symbol;
import otava.symbols.overload.resolution;
import otava.symbols.scope;
import otava.symbols.scope.resolver;
import otava.symbols.symbol.table;
import otava.symbols.type.resolver;
import otava.symbols.type.symbol;
import otava.symbols.variable.group.symbol;
import otava.symbols.variable.symbol;
import otava.symbols.argument.conversion.table;
import otava.symbols.statement.binder;
import otava.symbols.class_templates;
import otava.symbols.value;
import otava.symbols.namespaces;
import otava.symbols.array.type.symbol;
import otava.symbols.function.templates;
import otava.symbols.inline_functions;
import otava.symbols.operation.repository;
import otava.symbols.emitter;
import otava.symbols.modules;
import otava.ast.identifier;
import otava.ast.punctuation;
import otava.ast.expression;
import otava.ast.literal;
import otava.ast.visitor;
import otava.ast.templates;
import otava.ast.statement;
import otava.ast.simple.type;
import otava.ast.function;
import util.unicode;
import util.text.util;
import std;

namespace otava::symbols {

BoundExpressionNode* MakeAddressArg(BoundExpressionNode* node, Context* context)
{
    if (node->GetType()->IsReferenceType())
    {
        return new BoundRefToPtrNode(node, node->GetSourcePos(), node->GetType()->RemoveReference(context)->AddPointer(context));
    }
    else
    {
        return new BoundAddressOfNode(node, node->GetSourcePos(), node->GetType()->AddPointer(context));
    }
}

class OperatorGroupNameMap
{
public:
    static OperatorGroupNameMap& Instance();
    void Init();
    const std::u32string& GetGroupName(otava::ast::NodeKind nodeKind, const soul::ast::SourcePos& sourcePos, Context* context);
private:
    OperatorGroupNameMap();
    std::map<otava::ast::NodeKind, std::u32string> operatorGroupNameMap;
};

OperatorGroupNameMap& OperatorGroupNameMap::Instance()
{
    static OperatorGroupNameMap instance;
    return instance;
}

void OperatorGroupNameMap::Init()
{
}

OperatorGroupNameMap::OperatorGroupNameMap()
{
    operatorGroupNameMap[otava::ast::NodeKind::plusNode] = U"operator+";
    operatorGroupNameMap[otava::ast::NodeKind::minusNode] = U"operator-";
    operatorGroupNameMap[otava::ast::NodeKind::mulNode] = U"operator*";
    operatorGroupNameMap[otava::ast::NodeKind::divNode] = U"operator/";
    operatorGroupNameMap[otava::ast::NodeKind::modNode] = U"operator%";
    operatorGroupNameMap[otava::ast::NodeKind::andNode] = U"operator&";
    operatorGroupNameMap[otava::ast::NodeKind::inclusiveOrNode] = U"operator|";
    operatorGroupNameMap[otava::ast::NodeKind::exclusiveOrNode] = U"operator^";
    operatorGroupNameMap[otava::ast::NodeKind::shiftLeftNode] = U"operator<<";
    operatorGroupNameMap[otava::ast::NodeKind::shiftRightNode] = U"operator>>";
    operatorGroupNameMap[otava::ast::NodeKind::assignNode] = U"operator=";
    operatorGroupNameMap[otava::ast::NodeKind::plusAssignNode] = U"operator+=";
    operatorGroupNameMap[otava::ast::NodeKind::minusAssignNode] = U"operator-=";
    operatorGroupNameMap[otava::ast::NodeKind::mulAssignNode] = U"operator*=";
    operatorGroupNameMap[otava::ast::NodeKind::divAssignNode] = U"operator/=";
    operatorGroupNameMap[otava::ast::NodeKind::modAssignNode] = U"operator%=";
    operatorGroupNameMap[otava::ast::NodeKind::xorAssignNode] = U"operator^=";
    operatorGroupNameMap[otava::ast::NodeKind::andAssignNode] = U"operator&=";
    operatorGroupNameMap[otava::ast::NodeKind::orAssignNode] = U"operator|=";
    operatorGroupNameMap[otava::ast::NodeKind::shiftLeftAssignNode] = U"operator<<=";
    operatorGroupNameMap[otava::ast::NodeKind::shiftRightAssignNode] = U"operator>>=";
    operatorGroupNameMap[otava::ast::NodeKind::equalNode] = U"operator==";
    operatorGroupNameMap[otava::ast::NodeKind::lessNode] = U"operator<";
    operatorGroupNameMap[otava::ast::NodeKind::derefNode] = U"operator*";
    operatorGroupNameMap[otava::ast::NodeKind::addrOfNode] = U"operator&";
    operatorGroupNameMap[otava::ast::NodeKind::notNode] = U"operator!";
    operatorGroupNameMap[otava::ast::NodeKind::complementNode] = U"operator~";
    operatorGroupNameMap[otava::ast::NodeKind::prefixIncNode] = U"operator++";
    operatorGroupNameMap[otava::ast::NodeKind::prefixDecNode] = U"operator--";
    operatorGroupNameMap[otava::ast::NodeKind::arrowNode] = U"operator->";
    operatorGroupNameMap[otava::ast::NodeKind::subscriptExprNode] = U"operator[]";
}

std::expected<std::u32string, int> OperatorGroupNameMap::GetGroupName(otava::ast::NodeKind nodeKind, const soul::ast::SourcePos& sourcePos, Context* context)
{
    auto it = operatorGroupNameMap.find(nodeKind);
    if (it != operatorGroupNameMap.cend())
    {
        return std::expected<std::u32string, int>(it->second);
    }
    else
    {
        return Error("group name for node kind '" + otava::ast::NodeKindStr(nodeKind) + "' not found", sourcePos, context);
    }
}

class GroupNameResolver : public DefaultBoundTreeVisitor
{
public:
    GroupNameResolver();
    inline const std::u32string& GetGroupName() const { return groupName; }
    void Visit(BoundFunctionGroupNode& node) override;
    void Visit(BoundVariableNode& node) override;
    void Visit(BoundParameterNode& node) override;
    void Visit(BoundConstructTemporaryNode& node) override;
private:
    std::u32string groupName;
};

GroupNameResolver::GroupNameResolver()
{
}

void GroupNameResolver::Visit(BoundFunctionGroupNode& node)
{
    groupName = node.GetFunctionGroupSymbol()->Name();
}

void GroupNameResolver::Visit(BoundVariableNode& node)
{
    groupName = U"operator()";
}

void GroupNameResolver::Visit(BoundParameterNode& node)
{
    groupName = U"operator()";
}

void GroupNameResolver::Visit(BoundConstructTemporaryNode& node)
{
    groupName = U"operator()";
}

std::u32string GetGroupName(BoundNode* node)
{
    GroupNameResolver groupNameResolver;
    node->Accept(groupNameResolver);
    return groupNameResolver.GetGroupName();
}

class FirstArgResolver : public DefaultBoundTreeVisitor
{
public:
    FirstArgResolver(Context* context_);
    void Visit(BoundMemberExprNode& node) override;
    void Visit(BoundVariableNode& node) override;
    void Visit(BoundParameterNode& node) override;
    void Visit(BoundFunctionCallNode& node) override;
    void Visit(BoundConstructTemporaryNode& node) override;
    void Visit(BoundPtrToRefNode& node) override;
    inline BoundExpressionNode* GetFirstArg() const { return firstArg; }
private:
    Context* context;
    BoundExpressionNode* firstArg;
    otava::ast::NodeKind op;
};

FirstArgResolver::FirstArgResolver(Context* context_) : context(context_), firstArg(nullptr), op(otava::ast::NodeKind::nullNode)
{
}

void FirstArgResolver::Visit(BoundMemberExprNode& node)
{
    op = node.Op();
    node.Subject()->Accept(*this);
}

void FirstArgResolver::Visit(BoundVariableNode& node)
{
    bool hasConstDerivation = false;
    if (node.ThisPtr())
    {
        TypeSymbol* type = node.ThisPtr()->GetType();
        if (type->IsConstType())
        {
            hasConstDerivation = true;
        }
    }
    if (node.GetType()->IsReferenceType())
    {
        if (hasConstDerivation)
        {
            firstArg = new BoundRefToPtrNode(node.Clone(), node.GetSourcePos(), node.GetType()->RemoveReference(context)->AddPointer(context)->AddConst(context));
        }
        else
        {
            firstArg = new BoundRefToPtrNode(node.Clone(), node.GetSourcePos(), node.GetType()->RemoveReference(context)->AddPointer(context));
        }
    }
    else if (op == otava::ast::NodeKind::arrowNode)
    {
        firstArg = node.Clone();
    }
    else if (op == otava::ast::NodeKind::nullNode)
    {
        if (node.GetType()->IsClassTypeSymbol())
        {
            if (hasConstDerivation)
            {
                firstArg = new BoundAddressOfNode(node.Clone(), node.GetSourcePos(), node.GetType()->AddPointer(context)->AddConst(context));
            }
            else
            {
                firstArg = new BoundAddressOfNode(node.Clone(), node.GetSourcePos(), node.GetType()->AddPointer(context));
            }
        }
        else
        {
            firstArg = node.Clone();
        }
    }
    else
    {
        if (hasConstDerivation)
        {
            firstArg = new BoundAddressOfNode(node.Clone(), node.GetSourcePos(), node.GetType()->AddPointer(context)->AddConst(context));
        }
        else
        {
            firstArg = new BoundAddressOfNode(node.Clone(), node.GetSourcePos(), node.GetType()->AddPointer(context));
        }
    }
}

void FirstArgResolver::Visit(BoundParameterNode& node)
{
    if (node.GetType()->IsReferenceType())
    {
        firstArg = new BoundRefToPtrNode(node.Clone(), node.GetSourcePos(), node.GetType()->RemoveReference(context)->AddPointer(context));
    }
    else if (op == otava::ast::NodeKind::arrowNode)
    {
        firstArg = node.Clone();
    }
    else
    {
        firstArg = new BoundAddressOfNode(node.Clone(), node.GetSourcePos(), node.GetType()->AddPointer(context));
    }
}

void FirstArgResolver::Visit(BoundFunctionCallNode& node)
{
    if (op == otava::ast::NodeKind::arrowNode)
    {
        firstArg = node.Clone();
    }
    else if (op == otava::ast::NodeKind::dotNode && node.GetType()->IsReferenceType())
    {
        firstArg = new BoundRefToPtrNode(node.Clone(), node.GetSourcePos(), node.GetType()->RemoveReference(context)->AddPointer(context));
    }
}

void FirstArgResolver::Visit(BoundPtrToRefNode& node)
{
    firstArg = node.Subject()->Clone();
}

void FirstArgResolver::Visit(BoundConstructTemporaryNode& node)
{
    node.Temporary()->Accept(*this);
}

BoundExpressionNode* GetFirstArg(BoundNode* node, Context* context)
{
    FirstArgResolver resolver(context);
    node->Accept(resolver);
    return resolver.GetFirstArg();
}

class ExpressionBinder : public otava::ast::DefaultVisitor
{
public:
    ExpressionBinder(Context* context_, SymbolGroupKind symbolGroups_);
    inline BoundExpressionNode* GetBoundExpression() const { return boundExpression; }
    inline Scope* GetScope() const { return scope; }
    void Visit(otava::ast::IntegerLiteralNode& node) override;
    void Visit(otava::ast::FloatingLiteralNode& node) override;
    void Visit(otava::ast::CharacterLiteralNode& node) override;
    void Visit(otava::ast::StringLiteralNode& node) override;
    void Visit(otava::ast::RawStringLiteralNode& node) override;
    void Visit(otava::ast::BooleanLiteralNode& node) override;
    void Visit(otava::ast::NullPtrLiteralNode& node) override;
    void Visit(otava::ast::CharNode& node) override;
    void Visit(otava::ast::Char8Node& node) override;
    void Visit(otava::ast::Char16Node& node) override;
    void Visit(otava::ast::Char32Node& node) override;
    void Visit(otava::ast::WCharNode& node) override;
    void Visit(otava::ast::BoolNode& node) override;
    void Visit(otava::ast::ShortNode& node) override;
    void Visit(otava::ast::IntNode& node) override;
    void Visit(otava::ast::LongNode& node) override;
    void Visit(otava::ast::SignedNode& node) override;
    void Visit(otava::ast::UnsignedNode& node) override;
    void Visit(otava::ast::FloatNode& node) override;
    void Visit(otava::ast::DoubleNode& node) override;
    void Visit(otava::ast::IdentifierNode& node) override;
    void Visit(otava::ast::QualifiedIdNode& node) override;
    void Visit(otava::ast::DestructorIdNode& node) override;
    void Visit(otava::ast::ThisNode& node) override;
    void Visit(otava::ast::TemplateIdNode& node) override;
    void Visit(otava::ast::MemberExprNode& node) override;
    void Visit(otava::ast::InvokeExprNode& node) override;
    void Visit(otava::ast::BinaryExprNode& node) override;
    void Visit(otava::ast::UnaryExprNode& node) override;
    void Visit(otava::ast::SubscriptExprNode& node) override;
    void Visit(otava::ast::PostfixIncExprNode& node) override;
    void Visit(otava::ast::PostfixDecExprNode& node) override;
    void Visit(otava::ast::CppCastExprNode& node) override;
    void Visit(otava::ast::ExpressionListNode& node) override;
    void Visit(otava::ast::SizeOfTypeExprNode& node) override;
    void Visit(otava::ast::SizeOfUnaryExprNode& node) override;
    void Visit(otava::ast::NewExprNode& node) override;
    void Visit(otava::ast::DeletePtrNode& node) override;
    void Visit(otava::ast::BracedInitListNode& node) override;
private:
    void BindBinaryOp(otava::ast::NodeKind op, const soul::ast::SourcePos& sourcePos, BoundExpressionNode* left, BoundExpressionNode* right);
    void BindUnaryOp(otava::ast::NodeKind op, const soul::ast::SourcePos& sourcePos, BoundExpressionNode* operand);
    void BindClassArrow(BoundExpressionNode* operand, otava::ast::MemberExprNode* memberExprNode);
    void BindMemberExpr(otava::ast::MemberExprNode* node, BoundExpressionNode* subject);
    void BindDeref(const soul::ast::SourcePos& sourcePos, BoundExpressionNode* operand);
    void BindAddrOf(const soul::ast::SourcePos& sourcePos, BoundExpressionNode* operand);
    void BindPrefixInc(const soul::ast::SourcePos& sourcePos, BoundExpressionNode* operand, otava::ast::Node* child);
    void BindPrefixDec(const soul::ast::SourcePos& sourcePos, BoundExpressionNode* operand, otava::ast::Node* child);
    Context* context;
    BoundExpressionNode* boundExpression;
    Scope* scope;
    SymbolGroupKind symbolGroups;
    bool inhibitCompile;
    bool emptyDestructor;
    bool qualifiedScope;
};

ExpressionBinder::ExpressionBinder(Context* context_, SymbolGroupKind symbolGroups_) :
    context(context_),
    boundExpression(nullptr),
    scope(context->GetSymbolTable()->CurrentScope()),
    symbolGroups(symbolGroups_),
    inhibitCompile(false),
    emptyDestructor(false),
    qualifiedScope(false)
{
}

void ExpressionBinder::BindBinaryOp(otava::ast::NodeKind op, const soul::ast::SourcePos& sourcePos, BoundExpressionNode* left, BoundExpressionNode* right)
{
    if (!Valid()) return;
    bool isClassType = left->GetType()->IsClassTypeSymbol();
    if (!isClassType)
    {
        switch (op)
        {
            case otava::ast::NodeKind::plusAssignNode:
            {
                BoundExpressionNode* clone = left->Clone();
                BindBinaryOp(otava::ast::NodeKind::plusNode, sourcePos, left, right);
                if (!Valid()) return;
                BindBinaryOp(otava::ast::NodeKind::assignNode, sourcePos, clone, boundExpression);
                return;
            }
            case otava::ast::NodeKind::minusAssignNode:
            {
                BoundExpressionNode* clone = left->Clone();
                BindBinaryOp(otava::ast::NodeKind::minusNode, sourcePos, left, right);
                if (!Valid()) return;
                BindBinaryOp(otava::ast::NodeKind::assignNode, sourcePos, clone, boundExpression);
                return;
            }
            case otava::ast::NodeKind::mulAssignNode:
            {
                BoundExpressionNode* clone = left->Clone();
                BindBinaryOp(otava::ast::NodeKind::mulNode, sourcePos, left, right);
                if (!Valid()) return;
                BindBinaryOp(otava::ast::NodeKind::assignNode, sourcePos, clone, boundExpression);
                return;
            }
            case otava::ast::NodeKind::divAssignNode:
            {
                BoundExpressionNode* clone = left->Clone();
                BindBinaryOp(otava::ast::NodeKind::divNode, sourcePos, left, right);
                if (!Valid()) return;
                BindBinaryOp(otava::ast::NodeKind::assignNode, sourcePos, clone, boundExpression);
                return;
            }
            case otava::ast::NodeKind::modAssignNode:
            {
                BoundExpressionNode* clone = left->Clone();
                BindBinaryOp(otava::ast::NodeKind::modNode, sourcePos, left, right);
                if (!Valid()) return;
                BindBinaryOp(otava::ast::NodeKind::assignNode, sourcePos, clone, boundExpression);
                return;
            }
            case otava::ast::NodeKind::andAssignNode:
            {
                BoundExpressionNode* clone = left->Clone();
                BindBinaryOp(otava::ast::NodeKind::andNode, sourcePos, left, right);
                if (!Valid()) return;
                BindBinaryOp(otava::ast::NodeKind::assignNode, sourcePos, clone, boundExpression);
                return;
            }
            case otava::ast::NodeKind::orAssignNode:
            {
                BoundExpressionNode* clone = left->Clone();
                BindBinaryOp(otava::ast::NodeKind::inclusiveOrNode, sourcePos, left, right);
                if (!Valid()) return;
                BindBinaryOp(otava::ast::NodeKind::assignNode, sourcePos, clone, boundExpression);
                return;
            }
            case otava::ast::NodeKind::xorAssignNode:
            {
                BoundExpressionNode* clone = left->Clone();
                BindBinaryOp(otava::ast::NodeKind::exclusiveOrNode, sourcePos, left, right);
                if (!Valid()) return;
                BindBinaryOp(otava::ast::NodeKind::assignNode, sourcePos, clone, boundExpression);
                return;
            }
            case otava::ast::NodeKind::shiftLeftAssignNode:
            {
                BoundExpressionNode* clone = left->Clone();
                BindBinaryOp(otava::ast::NodeKind::shiftLeftNode, sourcePos, left, right);
                if (!Valid()) return;
                BindBinaryOp(otava::ast::NodeKind::assignNode, sourcePos, clone, boundExpression);
                return;
            }
            case otava::ast::NodeKind::shiftRightAssignNode:
            {
                BoundExpressionNode* clone = left->Clone();
                BindBinaryOp(otava::ast::NodeKind::shiftRightNode, sourcePos, left, right);
                if (!Valid()) return;
                BindBinaryOp(otava::ast::NodeKind::assignNode, sourcePos, clone, boundExpression);
                return;
            }
        }
    }
    std::expected<std::u32string, int> grv = OperatorGroupNameMap::Instance().GetGroupName(op, sourcePos, context);
    if (!grv)
    {
        SetError(grv.error());
        return;
    }
    std::u32string groupName = std::move(*grv);
    std::vector<std::unique_ptr<BoundExpressionNode>> args;
    args.push_back(std::unique_ptr<BoundExpressionNode>(left->Clone()));
    args.push_back(std::unique_ptr<BoundExpressionNode>(right->Clone()));
    std::unique_ptr<BoundFunctionCallNode> functionCall;
    FunctionMatch match1;
    std::vector<TypeSymbol*> templateArgs;
    std::expected<std::unique_ptr<BoundFunctionCallNode>, int> rv1 = ResolveOverload(scope, groupName, templateArgs, args, sourcePos, context, match1);
    std::unique_ptr<BoundFunctionCallNode> functionCall1;
    if (rv1)
    {
        functionCall1 = std::move(*rv1);
    }
    FunctionMatch match2;
    TypeSymbol* type = left->GetType()->AddPointer(context);
    std::vector<std::unique_ptr<BoundExpressionNode>> args2;
    args2.push_back(std::unique_ptr<BoundExpressionNode>(new BoundAddressOfNode(left, sourcePos, type)));
    args2.push_back(std::unique_ptr<BoundExpressionNode>(right));
    context->PushSetFlag(ContextFlags::noPtrOps);
    std::expected<std::unique_ptr<BoundFunctionCallNode>, int> rv2 = ResolveOverload(scope, groupName, templateArgs, args2, sourcePos, context, match2);
    std::unique_ptr<BoundFunctionCallNode> functionCall2;
    if (rv2)
    {
        functionCall2 = std::move(*rv2);
    }
    context->PopFlags();
    if (!functionCall1.get() && !functionCall2.get())
    {
        std::unexpected<int> result(util::AllocateError(util::GetErrorMessage(rv1.error()) + "\n" + util::GetErrorMessage(rv2.error())));
        SetError(result.error());
        return;
    }
    else if (functionCall1.get() && !functionCall2.get())
    {
        functionCall.reset(functionCall1.release());
        if (!match1.warning.empty())
        {
            std::cout << match1.warning << "\n";
        }
    }
    else if (functionCall2.get() && !functionCall1.get())
    {
        functionCall.reset(functionCall2.release());
        if (!match2.warning.empty())
        {
            std::cout << match2.warning << "\n";
        }
    }
    else
    {
        if (!match1.function || !match2.function)
        {
            if (match1.function)
            {
                functionCall.reset(functionCall1.release());
            }
            else if (match2.function)
            {
                functionCall.reset(functionCall2.release());
            }
            else
            {
                functionCall.reset(functionCall1.release());
            }
        }
        else
        {
            if (BetterFunctionMatch()(match1, match2))
            {
                functionCall.reset(functionCall1.release());
            }
            else if (BetterFunctionMatch()(match2, match1))
            {
                functionCall.reset(functionCall2.release());
            }
            else
            {
                functionCall.reset(functionCall1.release());
            }
        }
    }
    FunctionSymbol* functionSymbol = functionCall->GetFunctionSymbol();
    if (functionSymbol->IsVirtual())
    {
        functionCall->SetFlag(BoundExpressionFlags::virtualCall);
        auto rv = context->GetBoundCompileUnit()->AddBoundNodeForClass(functionSymbol->ParentClassType(), sourcePos, context);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
    }
    VariableSymbol* classTemporary = nullptr;
    if (functionSymbol->ReturnsClass())
    {
        std::expected<VariableSymbol*, int> rv = context->GetBoundFunction()->GetFunctionDefinitionSymbol()->CreateTemporary(functionSymbol->ReturnType());
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        classTemporary = *rv;
        functionCall->AddArgument(new BoundAddressOfNode(new BoundVariableNode(classTemporary, sourcePos), sourcePos, classTemporary->GetType()->AddPointer(context)));
    }
    boundExpression = functionCall.release();
    if (classTemporary)
    {
        boundExpression = new BoundConstructTemporaryNode(boundExpression, new BoundVariableNode(classTemporary, sourcePos), sourcePos);
        boundExpression->SetFlag(BoundExpressionFlags::bindToRvalueRef);
    }
}

void ExpressionBinder::BindUnaryOp(otava::ast::NodeKind op, const soul::ast::SourcePos& sourcePos, BoundExpressionNode* operand)
{
    if (!Valid()) return;
    std::expected<std::u32string, int> grv = OperatorGroupNameMap::Instance().GetGroupName(op, sourcePos, context);
    if (!grv)
    {
        SetError(grv.error());
        return;
    }
    std::u32string groupName = std::move(*grv);
    std::vector<std::unique_ptr<BoundExpressionNode>> args;
    args.push_back(std::unique_ptr<BoundExpressionNode>(operand));
    std::vector<TypeSymbol*> templateArgs;
    std::unique_ptr<BoundFunctionCallNode> functionCall;
    FunctionMatch match1;
    FunctionMatch match2;
    std::expected<std::unique_ptr<BoundFunctionCallNode>, int> rv1 = ResolveOverload(scope, groupName, templateArgs, args, sourcePos, context, match1);
    if (rv1)
    {
        functionCall = std::move(*rv1);
    }
    if (functionCall)
    {
        if (!match1.warning.empty())
        {
            std::cout << match1.warning << "\n";
        }
    }
    std::expected<std::unique_ptr<BoundFunctionCallNode>, int> rv2;
    if (!functionCall)
    {
        context->PushSetFlag(ContextFlags::skipFirstPtrToBooleanConversion);
        TypeSymbol* type = args[0]->GetType()->AddPointer(context);
        args[0].reset(new BoundAddressOfNode(args[0].release(), sourcePos, type));
        rv2 = ResolveOverload(scope, groupName, templateArgs, args, sourcePos, context, match2);
        if (rv2)
        {
            functionCall = std::move(*rv2);
        }
        context->PopFlags();
        if (functionCall)
        {
            if (!match2.warning.empty())
            {
                std::cout << match2.warning << "\n";
            }
        }
    }
    if (!functionCall)
    {
        std::unexpected<int> result(util::AllocateError(util::GetErrorMessage(rv1.error()) + "\n" + util::GetErrorMessage(rv2.error())));
        SetError(result.error());
        return;
    }
    FunctionSymbol* functionSymbol = functionCall->GetFunctionSymbol();
    if (functionSymbol->IsVirtual())
    {
        functionCall->SetFlag(BoundExpressionFlags::virtualCall);
        auto rv = context->GetBoundCompileUnit()->AddBoundNodeForClass(functionSymbol->ParentClassType(), sourcePos, context);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
    }
    VariableSymbol* classTemporary = nullptr;
    if (functionSymbol->ReturnsClass())
    {
        std::expected<VariableSymbol*, int> rv = context->GetBoundFunction()->GetFunctionDefinitionSymbol()->CreateTemporary(functionSymbol->ReturnType());
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        classTemporary = *rv;
        functionCall->AddArgument(new BoundAddressOfNode(new BoundVariableNode(classTemporary, sourcePos), sourcePos, classTemporary->GetType()->AddPointer(context)));
    }
    boundExpression = functionCall.release();
    if (classTemporary)
    {
        boundExpression = new BoundConstructTemporaryNode(boundExpression, new BoundVariableNode(classTemporary, sourcePos), sourcePos);
        boundExpression->SetFlag(BoundExpressionFlags::bindToRvalueRef);
    }
}

void ExpressionBinder::BindClassArrow(BoundExpressionNode* operand, otava::ast::MemberExprNode* memberExprNode)
{
    if (!Valid()) return;
    if (operand->GetType()->IsReferenceType())
    {
        operand = new BoundRefToPtrNode(operand, memberExprNode->GetSourcePos(), operand->GetType()->RemoveReference(context)->AddPointer(context));
    }
    else
    {
        operand = new BoundAddressOfNode(operand, memberExprNode->GetSourcePos(), operand->GetType()->AddPointer(context));
    }
    BindUnaryOp(otava::ast::NodeKind::arrowNode, memberExprNode->GetSourcePos(), operand);
    if (!Valid()) return;
    while (boundExpression->GetType()->IsClassTypeSymbol())
    {
        BindUnaryOp(otava::ast::NodeKind::arrowNode, memberExprNode->GetSourcePos(), boundExpression);
    }
    BindMemberExpr(memberExprNode, boundExpression);
}

void ExpressionBinder::BindDeref(const soul::ast::SourcePos& sourcePos, BoundExpressionNode* operand)
{
    if (!Valid()) return;
    if (operand->GetType()->IsPointerType())
    {
        if (operand->GetType()->RemovePointer(context)->IsClassTypeSymbol())
        {
            boundExpression = new BoundPtrToRefNode(operand, sourcePos, operand->GetType()->RemovePointer(context)->AddLValueRef(context));
        }
        else if (context->GetFlag(ContextFlags::returnRef))
        {
            boundExpression = new BoundPtrToRefNode(operand, sourcePos, operand->GetType()->RemovePointer(context)->AddLValueRef(context));
        }
        else
        {
            if (operand->IsBoundConversionNode())
            {
                boundExpression = new BoundDereferenceNode(operand, sourcePos, operand->GetType()->RemovePointer(context), OperationFlags::derefAfterConv);
            }
            else
            {
                boundExpression = new BoundDereferenceNode(operand, sourcePos, operand->GetType()->RemovePointer(context));
            }
        }
    }
    else
    {
        TypeSymbol* plainSubjectType = operand->GetType()->PlainType(context);
        if (plainSubjectType->IsClassTypeSymbol())
        {
            if (operand->GetType()->IsReferenceType())
            {
                boundExpression = new BoundRefToPtrNode(operand, sourcePos, operand->GetType()->RemoveReference(context)->AddPointer(context));
            }
            else
            {
                boundExpression = new BoundAddressOfNode(operand, sourcePos, operand->GetType()->AddPointer(context));
            }
            BindUnaryOp(otava::ast::NodeKind::derefNode, sourcePos, boundExpression);
        }
        else
        {
            std::unexpected<int> result = Error("dereference needs pointer or class type argument", sourcePos, context);
            SetError(result.error());
            return;
        }
    }
}

void ExpressionBinder::BindAddrOf(const soul::ast::SourcePos& sourcePos, BoundExpressionNode* operand)
{
    if (!Valid()) return;
    if (operand->IsLvalueExpression())
    {
        if (operand->GetType()->IsReferenceType())
        {
            boundExpression = new BoundRefToPtrNode(operand, sourcePos, operand->GetType()->RemoveReference(context)->AddPointer(context));
        }
        else
        {
            boundExpression = new BoundAddressOfNode(operand, sourcePos, operand->GetType()->AddPointer(context));
        }
    }
    else
    {
        std::unexpected<int> result = Error("cannot take address of this kind of expression", sourcePos, context);
        SetError(result.error());
        return;
    }
}

void ExpressionBinder::BindPrefixInc(const soul::ast::SourcePos& sourcePos, BoundExpressionNode* operand, otava::ast::Node* child)
{
    if (!Valid()) return;
    if (operand->GetType()->PlainType(context)->IsClassTypeSymbol())
    {
        if (operand->GetType()->IsReferenceType())
        {
            boundExpression = new BoundRefToPtrNode(operand, sourcePos, operand->GetType()->RemoveReference(context)->AddPointer(context));
        }
        else
        {
            boundExpression = new BoundAddressOfNode(operand, sourcePos, operand->GetType()->AddPointer(context));
        }
        BindUnaryOp(otava::ast::NodeKind::prefixIncNode, sourcePos, boundExpression);
        if (!Valid()) return;
    }
    else
    {
        otava::ast::BinaryExprNode assignmentExpr(sourcePos,
            new otava::ast::AssignNode(sourcePos),
            child->Clone(),
            new otava::ast::BinaryExprNode(sourcePos, new otava::ast::PlusNode(sourcePos), child->Clone(),
                new otava::ast::IntegerLiteralNode(sourcePos, 1, otava::ast::Suffix::none, otava::ast::Base::decimal, U"")));
        context->PushSetFlag(ContextFlags::suppress_warning);
        std::expected<BoundExpressionNode*, int> rv = BindExpression(&assignmentExpr, context);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        boundExpression = *rv;
        context->PopFlags();
    }
}

void ExpressionBinder::BindPrefixDec(const soul::ast::SourcePos& sourcePos, BoundExpressionNode* operand, otava::ast::Node* child)
{
    if (!Valid()) return;
    if (operand->GetType()->PlainType(context)->IsClassTypeSymbol())
    {
        if (operand->GetType()->IsReferenceType())
        {
            boundExpression = new BoundRefToPtrNode(operand, sourcePos, operand->GetType()->RemoveReference(context)->AddPointer(context));
        }
        else
        {
            boundExpression = new BoundAddressOfNode(operand, sourcePos, operand->GetType()->AddPointer(context));
        }
        BindUnaryOp(otava::ast::NodeKind::prefixDecNode, sourcePos, boundExpression);
        if (!Valid()) return;
    }
    else
    {
        otava::ast::BinaryExprNode assignmentExpr(sourcePos,
            new otava::ast::AssignNode(sourcePos),
            child->Clone(),
            new otava::ast::BinaryExprNode(sourcePos, new otava::ast::MinusNode(sourcePos), child->Clone(),
                new otava::ast::IntegerLiteralNode(sourcePos, 1, otava::ast::Suffix::none, otava::ast::Base::decimal, U"")));
        context->PushSetFlag(ContextFlags::suppress_warning);
        std::expected<BoundExpressionNode*, int> rv = BindExpression(&assignmentExpr, context);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        boundExpression = *rv;
        context->PopFlags();
    }
}

void ExpressionBinder::Visit(otava::ast::CppCastExprNode& node)
{
    if (!Valid()) return;
    std::expected<TypeSymbol*, int> rv = ResolveType(node.TypeId(), DeclarationFlags::none, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    TypeSymbol* resultType = *rv;
    rv = resultType->DirectType(context)->FinalType(node.GetSourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    resultType = *rv;
    node.Child()->Accept(*this);
    if (!Valid()) return;
    if (!boundExpression)
    {
        std::unexpected<int> result = Error("invalid cast", node.GetSourcePos(), context);
        SetError(result.error());
        return;
    }
    bool reinterpretCast = false;
    if (node.Op()->Kind() == otava::ast::NodeKind::reinterpretCastNode)
    {
        reinterpretCast = true;
        context->PushSetFlag(ContextFlags::reinterpretCast);
    }
    ArgumentMatch argumentMatch;
    FunctionMatch functionMatch;
    std::expected<TypeSymbol*, int> ftv = boundExpression->GetType()->DirectType(context)->FinalType(node.GetSourcePos(), context);
    if (!ftv)
    {
        SetError(ftv.error());
        return;
    }
    std::expected<FunctionSymbol*, int> arv = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
        resultType, *ftv, boundExpression, node.GetSourcePos(), argumentMatch, functionMatch, context);
    if (!arv)
    {
        SetError(arv.error());
        return;
    }
    FunctionSymbol* conversion = *arv;
    if (reinterpretCast)
    {
        context->PopFlags();
    }
    if (conversion)
    {
        if (argumentMatch.preConversionFlags == OperationFlags::addr)
        {
            boundExpression = new BoundAddressOfNode(MakeLvalueExpression(boundExpression, node.GetSourcePos(), context), node.GetSourcePos(),
                boundExpression->GetType()->AddPointer(context));
        }
        else if (argumentMatch.preConversionFlags == OperationFlags::deref)
        {
            boundExpression = new BoundDereferenceNode(boundExpression, node.GetSourcePos(), boundExpression->GetType()->RemoveReference(context));
        }
        boundExpression = new BoundConversionNode(boundExpression, conversion, node.GetSourcePos());
    }
    else
    {
        std::unexpected<int> result = Error("no conversion found", node.GetSourcePos(), context);
        SetError(result.error());
        return;
    }
}

std::expected<otava::ast::Node*, int> MakeTypeNameNodes(const soul::ast::SourcePos& sourcePos, const std::u32string& fullTypeName)
{
    otava::ast::Node* node = nullptr;
    std::vector<std::u32string> components = util::Split(fullTypeName, std::u32string(U"::"));
    int n = components.size();
    for (int i = n - 1; i >= 0; --i)
    {
        otava::ast::Node* identifierNode = new otava::ast::IdentifierNode(sourcePos, components[i]);
        if (node)
        {
            otava::ast::Node* nnsNode = new otava::ast::NestedNameSpecifierNode(sourcePos);
            std::expected<bool, int> rv = nnsNode->AddNode(identifierNode);
            if (!rv) return std::unexpected<int>(rv.error());
            rv = nnsNode->AddNode(new otava::ast::ColonColonNode(sourcePos));
            if (!rv) return std::unexpected<int>(rv.error());
            node = new otava::ast::QualifiedIdNode(sourcePos, nnsNode, node);
        }
        else
        {
            node = identifierNode;
        }
    }
    return std::expected<otava::ast::Node*, int>(node);
}

class NewInitializerMaker : public otava::ast::DefaultVisitor
{
public:
    NewInitializerMaker(const soul::ast::SourcePos& sourcePos_);
    void Visit(otava::ast::InvokeExprNode& node) override;
    otava::ast::NewInitializerNode* GetNewInitializer() const { return newInitializer; }
private:
    otava::ast::NewInitializerNode* newInitializer;
    soul::ast::SourcePos sourcePos;
};

NewInitializerMaker::NewInitializerMaker(const soul::ast::SourcePos& sourcePos_) : newInitializer(new otava::ast::NewInitializerNode(sourcePos_)), sourcePos(sourcePos_)
{
}

void NewInitializerMaker::Visit(otava::ast::InvokeExprNode& node)
{
    int n = node.Items().size();
    for (int i = 0; i < n; ++i)
    {
        otava::ast::Node* arg = node.Items()[i]->Clone();
        std::expected<bool, int> rv = newInitializer->AddNode(arg);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
    }
}

void ExpressionBinder::Visit(otava::ast::IntegerLiteralNode& node)
{
    if (!Valid()) return;
    std::expected<Value*, int> rv = Evaluate(&node, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    boundExpression = new BoundLiteralNode(*rv, node.GetSourcePos());
}

void ExpressionBinder::Visit(otava::ast::FloatingLiteralNode& node)
{
    if (!Valid()) return;
    std::expected<Value*, int> rv = Evaluate(&node, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    boundExpression = new BoundLiteralNode(*rv, node.GetSourcePos());
}

void ExpressionBinder::Visit(otava::ast::CharacterLiteralNode& node)
{
    if (!Valid()) return;
    std::expected<Value*, int> rv = Evaluate(&node, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    boundExpression = new BoundLiteralNode(*rv, node.GetSourcePos());
}

void ExpressionBinder::Visit(otava::ast::StringLiteralNode& node)
{
    if (!Valid()) return;
    std::expected<Value*, int> rv = Evaluate(&node, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    boundExpression = new BoundStringLiteralNode(*rv, node.GetSourcePos());
}

void ExpressionBinder::Visit(otava::ast::RawStringLiteralNode& node)
{
    if (!Valid()) return;
    std::expected<Value*, int> rv = Evaluate(&node, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    boundExpression = new BoundLiteralNode(*rv, node.GetSourcePos());
}

void ExpressionBinder::Visit(otava::ast::BooleanLiteralNode& node)
{
    if (!Valid()) return;
    std::expected<Value*, int> rv = Evaluate(&node, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    boundExpression = new BoundLiteralNode(*rv, node.GetSourcePos());
}

void ExpressionBinder::Visit(otava::ast::NullPtrLiteralNode& node)
{
    if (!Valid()) return;
    std::expected<Value*, int> rv = Evaluate(&node, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    boundExpression = new BoundLiteralNode(*rv, node.GetSourcePos());
}

void ExpressionBinder::Visit(otava::ast::CharNode& node)
{
    if (!Valid()) return;
    boundExpression = new BoundTypeNode(context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::charType), node.GetSourcePos());
}

void ExpressionBinder::Visit(otava::ast::Char8Node& node)
{
    if (!Valid()) return;
    boundExpression = new BoundTypeNode(context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::char8Type), node.GetSourcePos());
}

void ExpressionBinder::Visit(otava::ast::Char16Node& node)
{
    if (!Valid()) return;
    boundExpression = new BoundTypeNode(context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::char16Type), node.GetSourcePos());
}

void ExpressionBinder::Visit(otava::ast::Char32Node& node)
{
    if (!Valid()) return;
    boundExpression = new BoundTypeNode(context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::char32Type), node.GetSourcePos());
}

void ExpressionBinder::Visit(otava::ast::WCharNode& node)
{
    if (!Valid()) return;
    boundExpression = new BoundTypeNode(context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::wcharType), node.GetSourcePos());
}

void ExpressionBinder::Visit(otava::ast::BoolNode& node)
{
    if (!Valid()) return;
    boundExpression = new BoundTypeNode(context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::boolType), node.GetSourcePos());
}

void ExpressionBinder::Visit(otava::ast::ShortNode& node)
{
    if (!Valid()) return;
    boundExpression = new BoundTypeNode(context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::shortIntType), node.GetSourcePos());
}

void ExpressionBinder::Visit(otava::ast::IntNode& node)
{
    if (!Valid()) return;
    boundExpression = new BoundTypeNode(context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::intType), node.GetSourcePos());
}

void ExpressionBinder::Visit(otava::ast::LongNode& node)
{
    if (!Valid()) return;
    boundExpression = new BoundTypeNode(context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::longIntType), node.GetSourcePos());
}

void ExpressionBinder::Visit(otava::ast::SignedNode& node)
{
    if (!Valid()) return;
    boundExpression = new BoundTypeNode(context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::intType), node.GetSourcePos());
}

void ExpressionBinder::Visit(otava::ast::UnsignedNode& node)
{
    if (!Valid()) return;
    boundExpression = new BoundTypeNode(context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::unsignedIntType), node.GetSourcePos());
}

void ExpressionBinder::Visit(otava::ast::FloatNode& node)
{
    if (!Valid()) return;
    boundExpression = new BoundTypeNode(context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::floatType), node.GetSourcePos());
}

void ExpressionBinder::Visit(otava::ast::DoubleNode& node)
{
    if (!Valid()) return;
    boundExpression = new BoundTypeNode(context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::doubleType), node.GetSourcePos());
}

void ExpressionBinder::Visit(otava::ast::IdentifierNode& node)
{
    if (!Valid()) return;
    SymbolGroupKind groups = symbolGroups;
    if ((groups & SymbolGroupKind::functionSymbolGroup) != SymbolGroupKind::none)
    {
        groups = groups & ~SymbolGroupKind::functionSymbolGroup;
    }
    Symbol* symbol = nullptr;
    if (qualifiedScope)
    {
        symbol = scope->Lookup(node.Str(), groups, ScopeLookup::thisAndBaseScopes, node.GetSourcePos(), context, LookupFlags::dontResolveSingle);
    }
    if (!symbol)
    {
        symbol = scope->Lookup(node.Str(), groups, ScopeLookup::allScopes, node.GetSourcePos(), context, LookupFlags::dontResolveSingle);
    }
    if (!symbol)
    {
        std::set<Scope*> visited;
        ClassTemplateSpecializationSymbol* sp = static_cast<ClassTemplateSpecializationSymbol*>(scope->GetClassTemplateSpecialization(visited));
        if (sp)
        {
            symbol = sp->ClassTemplate()->GetScope()->Lookup(node.Str(), groups, ScopeLookup::allScopes, node.GetSourcePos(), context, LookupFlags::dontResolveSingle);
        }
    }
    if (!symbol && boundExpression && boundExpression->IsBoundTypeNode())
    {
        TypeSymbol* type = static_cast<TypeSymbol*>(boundExpression->GetType());
        symbol = type->GetScope()->Lookup(node.Str(), groups, ScopeLookup::allScopes, node.GetSourcePos(), context, LookupFlags::dontResolveSingle);
    }
    if (!symbol && (symbolGroups & SymbolGroupKind::functionSymbolGroup) != SymbolGroupKind::none)
    {
        groups = SymbolGroupKind::functionSymbolGroup;
        if (qualifiedScope)
        {
            symbol = scope->Lookup(node.Str(), groups, ScopeLookup::thisAndBaseScopes, node.GetSourcePos(), context, LookupFlags::dontResolveSingle);
        }
        if (!symbol)
        {
            symbol = scope->Lookup(node.Str(), groups, ScopeLookup::allScopes, node.GetSourcePos(), context, LookupFlags::dontResolveSingle);
        }
        if (!symbol)
        {
            std::set<Scope*> visited;
            ClassTemplateSpecializationSymbol* sp = static_cast<ClassTemplateSpecializationSymbol*>(scope->GetClassTemplateSpecialization(visited));
            if (sp)
            {
                symbol = sp->ClassTemplate()->GetScope()->Lookup(node.Str(), groups, ScopeLookup::allScopes, node.GetSourcePos(), context, LookupFlags::dontResolveSingle);
            }
        }
        if (!symbol && boundExpression && boundExpression->IsBoundTypeNode())
        {
            TypeSymbol* type = static_cast<TypeSymbol*>(boundExpression->GetType());
            symbol = type->GetScope()->Lookup(node.Str(), groups, ScopeLookup::allScopes, node.GetSourcePos(), context, LookupFlags::dontResolveSingle);
        }
    }
    if (symbol)
    {
        switch (symbol->Kind())
        {
            case SymbolKind::variableGroupSymbol:
            {
                VariableGroupSymbol* variableGroup = static_cast<VariableGroupSymbol*>(symbol);
                Symbol* sym = variableGroup->GetSingleSymbol();
                if (sym && sym->IsVariableSymbol())
                {
                    VariableSymbol* variable = static_cast<VariableSymbol*>(sym);
                    variable = variable->Final();
                    BoundVariableNode* boundVariable = new BoundVariableNode(variable, node.GetSourcePos());
                    if (variable->IsMemberVariable())
                    {
                        boundVariable->SetThisPtr(context->GetThisPtr(node.GetSourcePos()));
                    }
                    boundExpression = boundVariable;
                }
                else
                {
                    std::expected<std::string, int> name = util::ToUtf8(variableGroup->Name());
                    if (!name)
                    {
                        SetError(name.error());
                        return;
                    }
                    std::unexpected<int> result = Error("ambiguous reference to variable '" + *name + "'", node.GetSourcePos(), context);
                    SetError(result.error());
                    return;
                }
                break;
            }
            case SymbolKind::classGroupSymbol:
            {
                ClassGroupSymbol* classGroup = static_cast<ClassGroupSymbol*>(symbol);
                Symbol* sym = classGroup->GetSingleSymbol();
                if (sym && sym->IsClassTypeSymbol())
                {
                    ClassTypeSymbol* cls = static_cast<ClassTypeSymbol*>(sym);
                    boundExpression = new BoundTypeNode(cls, node.GetSourcePos());
                }
                else if (sym && sym == classGroup)
                {
                    ClassGroupSymbol* classGroupSymbol = static_cast<ClassGroupSymbol*>(symbol);
                    ClassGroupTypeSymbol* classGroupType = context->GetSymbolTable()->MakeClassGroupTypeSymbol(classGroupSymbol);
                    boundExpression = new BoundClassGroupNode(classGroupSymbol, node.GetSourcePos(), classGroupType);
                }
                else
                {
                    std::expected<std::string, int> name = util::ToUtf8(classGroup->Name());
                    if (!name)
                    {
                        SetError(name.error());
                        return;
                    }
                    std::unexpected<int> result = Error("ambiguous reference to class '" + *name + "'", node.GetSourcePos(), context);
                    SetError(result.error());
                    return;
                }
                break;
            }
            case SymbolKind::templateParameterSymbol:
            {
                TypeSymbol* type = static_cast<TypeSymbol*>(symbol);
                boundExpression = new BoundTypeNode(type, node.GetSourcePos());
                break;
            }
            case SymbolKind::aliasGroupSymbol:
            {
                AliasGroupSymbol* aliasGroup = static_cast<AliasGroupSymbol*>(symbol);
                Symbol* sym = aliasGroup->GetSingleSymbol();
                if (sym && sym->IsAliasTypeSymbol())
                {
                    AliasTypeSymbol* aliasType = static_cast<AliasTypeSymbol*>(sym);
                    TypeSymbol* referredType = aliasType->ReferredType();
                    while (referredType->IsAliasTypeSymbol())
                    {
                        aliasType = static_cast<AliasTypeSymbol*>(referredType);
                        referredType = aliasType->ReferredType();
                    }
                    boundExpression = new BoundTypeNode(referredType, node.GetSourcePos());
                }
                else if (sym && sym == aliasGroup)
                {
                    AliasGroupTypeSymbol* aliasGroupType = context->GetSymbolTable()->MakeAliasGroupTypeSymbol(aliasGroup);
                    boundExpression = new BoundAliasGroupNode(aliasGroup, node.GetSourcePos(), aliasGroupType);
                }
                else
                {
                    std::expected<std::string, int> name = util::ToUtf8(aliasGroup->Name());
                    if (!name)
                    {
                        SetError(name.error());
                        return;
                    }
                    std::unexpected<int> result = Error("ambiguous reference to type alias '" + *name + "'", node.GetSourcePos(), context);
                    SetError(result.error());
                    return;
                }
                break;
            }
            case SymbolKind::enumGroupSymbol:
            {
                EnumGroupSymbol* enumGroup = static_cast<EnumGroupSymbol*>(symbol);
                EnumeratedTypeSymbol* enm = enumGroup->GetEnumType();
                if (enm)
                {
                    boundExpression = new BoundTypeNode(enm, node.GetSourcePos());
                }
                else
                {
                    std::expected<std::string, int> name = util::ToUtf8(enumGroup->Name());
                    if (!name)
                    {
                        SetError(name.error());
                        return;
                    }
                    std::unexpected<int> result = Error("enumerated type not found from enum group '" + *name + "'", node.GetSourcePos(), context);
                    SetError(result.error());
                    return;
                }
                break;
            }
            case SymbolKind::enumTypeSymbol:
            {
                EnumeratedTypeSymbol* enm = static_cast<EnumeratedTypeSymbol*>(symbol);
                boundExpression = new BoundTypeNode(enm, node.GetSourcePos());
                break;
            }
            case SymbolKind::enumConstantSymbol:
            {
                EnumConstantSymbol* enumConstant = static_cast<EnumConstantSymbol*>(symbol);
                boundExpression = new BoundEnumConstant(enumConstant, node.GetSourcePos());
                break;
            }
            case SymbolKind::parameterSymbol:
            {
                ParameterSymbol* parameter = static_cast<ParameterSymbol*>(symbol);
                std::expected<TypeSymbol*, int> rrv = parameter->GetReferredType(context);
                if (!rrv)
                {
                    SetError(rrv.error());
                    return;
                }
                TypeSymbol* referredType = *rrv;
                boundExpression = new BoundParameterNode(parameter, node.GetSourcePos(), referredType);
                break;
            }
            case SymbolKind::functionGroupSymbol:
            {
                FunctionGroupSymbol* functionGroupSymbol = static_cast<FunctionGroupSymbol*>(symbol);
                FunctionGroupTypeSymbol* functionGroupType = context->GetSymbolTable()->MakeFunctionGroupTypeSymbol(functionGroupSymbol);
                boundExpression = new BoundFunctionGroupNode(functionGroupSymbol, node.GetSourcePos(), functionGroupType);
                break;
            }
            case SymbolKind::fundamentalTypeSymbol:
            {
                boundExpression = new BoundTypeNode(static_cast<TypeSymbol*>(symbol), node.GetSourcePos());
                break;
            }
            case SymbolKind::namespaceSymbol:
            {
                NamespaceSymbol* ns = static_cast<NamespaceSymbol*>(symbol);
                scope = ns->GetScope();
                qualifiedScope = true;
                break;
            }
            default:
            {
                std::expected<std::string, int> name = util::ToUtf8(node.Str());
                if (!name)
                {
                    SetError(name.error());
                    return;
                }
                std::unexpected<int> result = Error("symbol '" + *name + "' processing not implemented", node.GetSourcePos(), context);
                SetError(result.error());
                return;
            }
        }
    }
    else
    {
        std::expected<std::string, int> name = util::ToUtf8(node.Str());
        if (!name)
        {
            SetError(name.error());
            return;
        }
        std::unexpected<int> result = Error("symbol '" + *name + "' not found", node.GetSourcePos(), context);
        SetError(result.error());
        return;
    }
}

void ExpressionBinder::Visit(otava::ast::QualifiedIdNode& node)
{
    if (!Valid()) return;
    std::expected<Scope*, int> rv = ResolveScope(node.Left(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    scope = *rv;
    bool prevQualifiedScope = qualifiedScope;
    qualifiedScope = true;
    node.Right()->Accept(*this);
    if (!Valid()) return;
    qualifiedScope = prevQualifiedScope;
}

void ExpressionBinder::Visit(otava::ast::DestructorIdNode& node)
{
    if (!Valid()) return;
    Symbol* s = scope->GetSymbol();
    if (s->IsFundamentalTypeSymbol())
    {
        scope = context->GetSymbolTable()->GlobalNs()->GetScope();
    }
    else
    {
        if (s->IsClassTemplateSpecializationSymbol())
        {
            ClassTemplateSpecializationSymbol* sp = static_cast<ClassTemplateSpecializationSymbol*>(s);
            s = sp->ClassTemplate();
        }
        scope = s->GetScope();
    }
    Symbol* symbol = scope->Lookup(U"@destructor", SymbolGroupKind::functionSymbolGroup, ScopeLookup::thisScope, node.GetSourcePos(), context, LookupFlags::dontResolveSingle);
    if (symbol && symbol->IsFunctionGroupSymbol())
    {
        FunctionGroupSymbol* functionGroupSymbol = static_cast<FunctionGroupSymbol*>(symbol);
        FunctionGroupTypeSymbol* functionGroupType = context->GetSymbolTable()->MakeFunctionGroupTypeSymbol(functionGroupSymbol);
        boundExpression = new BoundFunctionGroupNode(static_cast<FunctionGroupSymbol*>(symbol), node.GetSourcePos(), functionGroupType);
    }
    else
    {
        emptyDestructor = true;
        boundExpression = nullptr;
    }
}

void ExpressionBinder::Visit(otava::ast::ThisNode& node)
{
    if (!Valid()) return;
    ParameterSymbol* thisParam = context->GetBoundFunction()->GetFunctionDefinitionSymbol()->ThisParam(context);
    if (thisParam)
    {
        boundExpression = new BoundParameterNode(thisParam, node.GetSourcePos(), thisParam->GetType());
    }
    else
    {
        std::unexpected<int> result = Error("'this' can only be used in member function context", node.GetSourcePos(), context);
        SetError(result.error());
        return;
    }
}

void ExpressionBinder::Visit(otava::ast::TemplateIdNode& node)
{
    if (!Valid()) return;
    Scope* currentScope = context->GetSymbolTable()->CurrentScope();
    currentScope->PushParentScope(scope);
    std::expected<TypeSymbol*, int> rv = ResolveType(&node, DeclarationFlags::none, context);
    TypeSymbol* type = nullptr;
    if (rv)
    {
        type = *rv;
    }
    if (type)
    {
        rv = type->DirectType(context)->FinalType(node.GetSourcePos(), context);
        if (rv)
        {
            type = *rv;
            boundExpression = new BoundTypeNode(type, node.GetSourcePos());
        }
    }
    else
    {
        std::expected<BoundExpressionNode*, int> rv = BindExpression(node.TemplateName(), context);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        std::unique_ptr<BoundExpressionNode> subject(*rv);
        if (subject->IsBoundFunctionGroupNode())
        {
            BoundFunctionGroupNode* boundFunctionGroup = static_cast<BoundFunctionGroupNode*>(subject.get());
            for (otava::ast::Node* item : node.Items())
            {
                std::expected<TypeSymbol*, int> rv = ResolveType(item, DeclarationFlags::none, context);
                if (!rv)
                {
                    SetError(rv.error());
                    return;
                }
                TypeSymbol* templateArg = *rv;
                boundFunctionGroup->AddTemplateArg(templateArg);
            }
            boundExpression = subject.release();
        }
        else
        {
            std::expected<std::string, int> name = util::ToUtf8(node.TemplateName()->Str());
            if (!name)
            {
                SetError(name.error());
                return;
            }
            std::unexpected<int> result = Error("expression.binder: error binding template id '" + *name +  "': type or function group expected", node.GetSourcePos(), 
                context);
            SetError(result.error());
            return;
        }
    }
    currentScope->PopParentScope();
}

void ExpressionBinder::Visit(otava::ast::MemberExprNode& node)
{
    if (!Valid()) return;
    std::expected<BoundExpressionNode*, int> rv = BindExpression(node.Child(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    std::unique_ptr<BoundExpressionNode> subject(*rv);
    BindMemberExpr(&node, subject.release());
}

void ExpressionBinder::BindMemberExpr(otava::ast::MemberExprNode* node, BoundExpressionNode* subject)
{
    if (!Valid()) return;
    if (node->Op()->Kind() == otava::ast::NodeKind::arrowNode && subject->GetType()->PlainType(context)->IsClassTypeSymbol())
    {
        BindClassArrow(subject, node);
        return;
    }
    std::expected<Scope*, int> rv = subject->GetMemberScope(node->Op(), node->GetSourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    Scope* memberScope = *rv;
    if (memberScope)
    {
        scope = memberScope;
    }
    node->Id()->Accept(*this);
    if (emptyDestructor)
    {
        boundExpression = new BoundEmptyDestructorNode(node->GetSourcePos());
        return;
    }
    std::unique_ptr<BoundExpressionNode> member(boundExpression);
    if (subject->IsBoundLocalVariable() && member->IsBoundMemberVariable())
    {
        BoundVariableNode* localVar = static_cast<BoundVariableNode*>(subject);
        BoundVariableNode* memberVar = static_cast<BoundVariableNode*>(member.release());
        if (node->Op()->Kind() == otava::ast::NodeKind::arrowNode)
        {
            memberVar->SetThisPtr(localVar->Clone());
        }
        else
        {
            BoundExpressionNode* thisPtr = nullptr;
            if (localVar->GetType()->IsReferenceType())
            {
                thisPtr = new BoundRefToPtrNode(localVar, node->GetSourcePos(), localVar->GetType()->RemoveReference(context)->AddPointer(context));
            }
            else
            {
                thisPtr = new BoundAddressOfNode(localVar, node->GetSourcePos(), localVar->GetType()->AddPointer(context));
            }
            memberVar->SetThisPtr(thisPtr);
        }
        boundExpression = memberVar;
    }
    else if (subject->IsBoundMemberVariable() && member->IsBoundMemberVariable())
    {
        BoundVariableNode* subjectVar = static_cast<BoundVariableNode*>(subject);
        BoundVariableNode* memberVar = static_cast<BoundVariableNode*>(member.release());
        if (node->Op()->Kind() == otava::ast::NodeKind::arrowNode)
        {
            memberVar->SetThisPtr(subjectVar->Clone());
        }
        else
        {
            BoundExpressionNode* thisPtr = nullptr;
            if (subjectVar->GetType()->IsReferenceType())
            {
                thisPtr = new BoundRefToPtrNode(subjectVar, node->GetSourcePos(), subjectVar->GetType()->RemoveReference(context)->AddPointer(context));
            }
            else
            {
                thisPtr = new BoundAddressOfNode(subjectVar, node->GetSourcePos(), subjectVar->GetType()->AddPointer(context));
            }
            memberVar->SetThisPtr(thisPtr);
        }
        boundExpression = memberVar;
    }
    else if (subject->IsBoundParameterNode() && member->IsBoundMemberVariable())
    {
        BoundParameterNode* param = static_cast<BoundParameterNode*>(subject);
        if (param->GetType()->GetBaseType()->IsClassTypeSymbol())
        {
            BoundExpressionNode* thisPtr = nullptr;
            if (node->Op()->Kind() == otava::ast::NodeKind::arrowNode)
            {
                thisPtr = param->Clone();
            }
            else
            {
                if (param->GetType()->IsReferenceType())
                {
                    thisPtr = new BoundRefToPtrNode(param, node->GetSourcePos(), param->GetType()->RemoveReference(context)->AddPointer(context));
                }
                else
                {
                    thisPtr = new BoundAddressOfNode(param, node->GetSourcePos(), param->GetType()->AddPointer(context));
                }
            }
            BoundVariableNode* memberVar = static_cast<BoundVariableNode*>(member.release());
            memberVar->SetThisPtr(thisPtr);
            boundExpression = memberVar;
        }
        else
        {
            boundExpression = new BoundMemberExprNode(subject, member.release(), node->Op()->Kind(), node->GetSourcePos(), nullptr);
        }
    }
    else if (subject->IsBoundFunctionCallNode() && member->IsBoundMemberVariable())
    {
        BoundVariableNode* memberVar = static_cast<BoundVariableNode*>(member.release());
        memberVar->SetThisPtr(subject->Clone());
        boundExpression = memberVar;
    }
    else
    {
        boundExpression = new BoundMemberExprNode(subject, member.release(), node->Op()->Kind(), node->GetSourcePos(), nullptr);
    }
}

void ExpressionBinder::Visit(otava::ast::InvokeExprNode& node)
{
    if (!Valid()) return;
    bool thisPtrAdded = false;
    bool suppressWarning = false;
    VariableSymbol* temporary = nullptr;
    Scope* subjectScope = scope;
    OverloadResolutionFlags resolutionFlags = OverloadResolutionFlags::none;
    if (node.Subject()->IsQualifiedIdNode())
    {
        resolutionFlags = resolutionFlags | OverloadResolutionFlags::dontSearchArgumentScopes;
    }
    std::expected<BoundExpressionNode*, int> rv = BindExpression(node.Subject(), context,
        SymbolGroupKind::functionSymbolGroup | SymbolGroupKind::typeSymbolGroup | SymbolGroupKind::variableSymbolGroup, subjectScope);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    std::unique_ptr<BoundExpressionNode> subject(*rv);
    if (subject)
    {
        TypeSymbol* subjectType = subject->GetType();
        if (subjectType && subjectType->IsFunctionPtrType())
        {
            std::unique_ptr<BoundFunctionPtrCallNode> call(new BoundFunctionPtrCallNode(node.GetSourcePos(), subjectType));
            call->AddArgument(subject.release());
            int n = node.Items().size();
            for (int i = 0; i < n; ++i)
            {
                otava::ast::Node* item = node.Items()[i];
                std::expected<BoundExpressionNode*, int> rv = BindExpression(item, context);
                if (!rv)
                {
                    SetError(rv.error());
                    return;
                }
                std::unique_ptr<BoundExpressionNode> arg(*rv);
                call->AddArgument(arg.release());
            }
            boundExpression = call.release();
            return;
        }
        if (subject->IsBoundEmptyDestructorNode())
        {
            boundExpression = new BoundEmptyFunctionCallNode(node.GetSourcePos());
            return;
        }
        std::vector<std::unique_ptr<BoundExpressionNode>> args;
        if (subject->IsBoundTypeNode())
        {
            std::expected<VariableSymbol*, int> rv = context->GetBoundFunction()->GetFunctionDefinitionSymbol()->CreateTemporary(subject->GetType());
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
            temporary = *rv;
            BoundAddressOfNode* boundAddrOfNode = new BoundAddressOfNode(new BoundVariableNode(temporary, node.GetSourcePos()), node.GetSourcePos(),
                temporary->GetType()->AddPointer(context));
            args.push_back(std::unique_ptr<BoundExpressionNode>(boundAddrOfNode));
            resolutionFlags = resolutionFlags & ~OverloadResolutionFlags::dontSearchArgumentScopes;
            suppressWarning = true;
        }
        else
        {
            BoundExpressionNode* firstArg = GetFirstArg(subject.get(), context);
            if (firstArg)
            {
                args.push_back(std::unique_ptr<BoundExpressionNode>(firstArg));
            }
            else
            {
                BoundExpressionNode* thisPtr = context->GetThisPtr(node.GetSourcePos());
                if (thisPtr)
                {
                    args.push_back(std::unique_ptr<BoundExpressionNode>(thisPtr));
                    thisPtrAdded = true;
                }
            }
        }
        int n = node.Items().size();
        for (int i = 0; i < n; ++i)
        {
            otava::ast::Node* item = node.Items()[i];
            std::expected<BoundExpressionNode*, int> rv = BindExpression(item, context);
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
            std::unique_ptr<BoundExpressionNode> arg(*rv);
            args.push_back(std::move(arg));
        }
        std::u32string groupName;
        if (subject->IsBoundTypeNode())
        {
            groupName = U"@constructor";
        }
        else
        {
            groupName = GetGroupName(subject.get());
        }
        FunctionMatch match1;
        FunctionMatch match2;
        std::vector<TypeSymbol*> templateArgs;
        if (subject->IsBoundFunctionGroupNode())
        {
            BoundFunctionGroupNode* boundFunctionGroup = static_cast<BoundFunctionGroupNode*>(subject.get());
            templateArgs = boundFunctionGroup->TemplateArgs();
        }
        bool flagsPushed = false;
        if (suppressWarning)
        {
            context->PushSetFlag(ContextFlags::suppress_warning);
            flagsPushed = true;
        }
        std::unique_ptr<BoundFunctionCallNode> functionCall;
        std::expected<std::unique_ptr<BoundFunctionCallNode>, int> rv1 = ResolveOverload(subjectScope, groupName, templateArgs, args, node.GetSourcePos(), context, match1,
            resolutionFlags);
        if (rv1)
        {
            functionCall = std::move(*rv1);
        }
        if (flagsPushed)
        {
            context->PopFlags();
            flagsPushed = false;
        }
        if (functionCall)
        {
            if (!match1.warning.empty())
            {
                std::cout << match1.warning << "\n";
            }
        }
        std::expected<std::unique_ptr<BoundFunctionCallNode>, int> rv2;
        if (!functionCall && thisPtrAdded)
        {
            args.erase(args.begin());
            if (suppressWarning)
            {
                context->PushSetFlag(ContextFlags::suppress_warning);
                flagsPushed = true;
            }
            resolutionFlags = resolutionFlags | OverloadResolutionFlags::noMemberFunctions;
            rv2 = ResolveOverload(subjectScope, groupName, templateArgs, args, node.GetSourcePos(), context, match2, resolutionFlags);
            if (rv2)
            {
                functionCall = std::move(*rv2);
            }
            if (flagsPushed)
            {
                context->PopFlags();
                flagsPushed = false;
            }
            if (functionCall)
            {
                if (!match2.warning.empty())
                {
                    std::cout << match2.warning << "\n";
                }
            }
        }
        if (!functionCall)
        {
            int error = util::AllocateError(util::GetErrorMessage(rv1.error()) + "\n" + util::GetErrorMessage(rv2.error()));
            SetError(error);
            return;
        }
        FunctionSymbol* functionSymbol = functionCall->GetFunctionSymbol();
        if (functionSymbol->IsVirtual() && !node.Subject()->IsQualifiedIdNode())
        {
            functionCall->SetFlag(BoundExpressionFlags::virtualCall);
            auto rv = context->GetBoundCompileUnit()->AddBoundNodeForClass(functionSymbol->ParentClassType(), node.GetSourcePos(), context);
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
            if (!functionCall->Args().empty())
            {
                BoundExpressionNode* firstArg = functionCall->Args()[0].get();
                TypeSymbol* firstArgType = firstArg->GetType()->GetBaseType();
                if (firstArgType->IsClassTypeSymbol())
                {
                    ClassTypeSymbol* classType = static_cast<ClassTypeSymbol*>(firstArgType);
                    auto rv = context->GetBoundCompileUnit()->AddBoundNodeForClass(classType, node.GetSourcePos(), context);
                    if (!rv)
                    {
                        SetError(rv.error());
                        return;
                    }
                }
            }
        }
        VariableSymbol* classTemporary = nullptr;
        if (functionSymbol->ReturnsClass())
        {
            std::expected<VariableSymbol*, int> rv = context->GetBoundFunction()->GetFunctionDefinitionSymbol()->CreateTemporary(functionSymbol->ReturnType());
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
            classTemporary = *rv;
            functionCall->AddArgument(new BoundAddressOfNode(new BoundVariableNode(classTemporary, node.GetSourcePos()), node.GetSourcePos(), 
                classTemporary->GetType()->AddPointer(context)));
        }
        boundExpression = functionCall.release();
        if (classTemporary)
        {
            boundExpression = new BoundConstructTemporaryNode(boundExpression, new BoundVariableNode(classTemporary, node.GetSourcePos()), node.GetSourcePos());
            boundExpression->SetFlag(BoundExpressionFlags::bindToRvalueRef);
        }
        if (subject->IsBoundTypeNode())
        {
            boundExpression = new BoundConstructTemporaryNode(boundExpression, new BoundVariableNode(temporary, node.GetSourcePos()), node.GetSourcePos());
            boundExpression->SetFlag(BoundExpressionFlags::bindToRvalueRef);
        }
    }
    else
    {
        std::unexpected<int> result = Error("unkown invoke subject", node.GetSourcePos(), context);
        SetError(result.error());
        return;
    }
}

void ExpressionBinder::Visit(otava::ast::BinaryExprNode& node)
{
    if (!Valid()) return;
    bool booleanChild = false;
    otava::ast::NodeKind op = node.Op()->Kind();
    switch (op)
    {
        case otava::ast::NodeKind::disjunctionNode:
        case otava::ast::NodeKind::conjunctionNode:
        {
            booleanChild = true;
            break;
        }
    }
    std::expected<BoundExpressionNode*, int> lrv = BindExpression(node.Left(), context, booleanChild);
    if (!lrv)
    {
        SetError(lrv.error());
        return;
    }
    std::unique_ptr<BoundExpressionNode> left(*lrv);
    std::expected<BoundExpressionNode*, int> rrv = BindExpression(node.Right(), context, booleanChild);
    if (!rrv)
    {
        SetError(rrv.error());
        return;
    }
    std::unique_ptr<BoundExpressionNode> right(*rrv);
    switch (op)
    {
        case otava::ast::NodeKind::assignNode:
        case otava::ast::NodeKind::plusAssignNode:
        case otava::ast::NodeKind::minusAssignNode:
        case otava::ast::NodeKind::mulAssignNode:
        case otava::ast::NodeKind::divAssignNode:
        case otava::ast::NodeKind::modAssignNode:
        case otava::ast::NodeKind::xorAssignNode:
        case otava::ast::NodeKind::andAssignNode:
        case otava::ast::NodeKind::orAssignNode:
        case otava::ast::NodeKind::shiftLeftAssignNode:
        case otava::ast::NodeKind::shiftRightAssignNode:
        case otava::ast::NodeKind::inclusiveOrNode:
        case otava::ast::NodeKind::exclusiveOrNode:
        case otava::ast::NodeKind::andNode:
        case otava::ast::NodeKind::equalNode:
        case otava::ast::NodeKind::lessNode:
        case otava::ast::NodeKind::compareNode:
        case otava::ast::NodeKind::shiftLeftNode:
        case otava::ast::NodeKind::shiftRightNode:
        case otava::ast::NodeKind::plusNode:
        case otava::ast::NodeKind::minusNode:
        case otava::ast::NodeKind::mulNode:
        case otava::ast::NodeKind::divNode:
        case otava::ast::NodeKind::modNode:
        {
            BindBinaryOp(op, node.GetSourcePos(), left.release(), right.release());
            break;
        }
        case otava::ast::NodeKind::notEqualNode:
        {
            BindBinaryOp(otava::ast::NodeKind::equalNode, node.GetSourcePos(), left.release(), right.release());
            if (!Valid()) return;
            BindUnaryOp(otava::ast::NodeKind::notNode, node.GetSourcePos(), boundExpression);
            break;
        }
        case otava::ast::NodeKind::greaterNode:
        {
            BindBinaryOp(otava::ast::NodeKind::lessNode, node.GetSourcePos(), right.release(), left.release());
            break;
        }
        case otava::ast::NodeKind::lessOrEqualNode:
        {
            BindBinaryOp(otava::ast::NodeKind::lessNode, node.GetSourcePos(), right.release(), left.release());
            if (!Valid()) return;
            BindUnaryOp(otava::ast::NodeKind::notNode, node.GetSourcePos(), boundExpression);
            break;
        }
        case otava::ast::NodeKind::greaterOrEqualNode:
        {
            BindBinaryOp(otava::ast::NodeKind::lessNode, node.GetSourcePos(), left.release(), right.release());
            if (!Valid()) return;
            BindUnaryOp(otava::ast::NodeKind::notNode, node.GetSourcePos(), boundExpression);
            break;
        }
        case otava::ast::NodeKind::disjunctionNode:
        {
            TypeSymbol* boolType = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::boolType);
            BoundDisjunctionNode* boundDisjunction = new BoundDisjunctionNode(left.release(), right.release(), node.GetSourcePos(), boolType);
            std::expected<VariableSymbol*, int> rv = context->GetBoundFunction()->GetFunctionDefinitionSymbol()->CreateTemporary(boolType);
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
            VariableSymbol* temporary = *rv;
            boundDisjunction->SetTemporary(new BoundVariableNode(temporary, node.GetSourcePos()));
            boundExpression = boundDisjunction;
            break;
        }
        case otava::ast::NodeKind::conjunctionNode:
        {
            TypeSymbol* boolType = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::boolType);
            BoundConjunctionNode* boundConjunction = new BoundConjunctionNode(left.release(), right.release(), node.GetSourcePos(), boolType);
            std::expected<VariableSymbol*, int> rv = context->GetBoundFunction()->GetFunctionDefinitionSymbol()->CreateTemporary(boolType);
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
            VariableSymbol* temporary = *rv;
            boundConjunction->SetTemporary(new BoundVariableNode(temporary, node.GetSourcePos()));
            boundExpression = boundConjunction;
            break;
        }
        case otava::ast::NodeKind::commaNode:
        {
            boundExpression = new BoundExpressionSequenceNode(node.GetSourcePos(), left.release(), right.release());
            break;
        }
    }
}

void ExpressionBinder::Visit(otava::ast::UnaryExprNode& node)
{
    if (!Valid()) return;
    std::expected<BoundExpressionNode*, int> rv = BindExpression(node.Child(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    std::unique_ptr<BoundExpressionNode> child(*rv);
    otava::ast::NodeKind op = node.Op()->Kind();
    switch (op)
    {
        case otava::ast::NodeKind::notNode:
        case otava::ast::NodeKind::plusNode:
        case otava::ast::NodeKind::minusNode:
        case otava::ast::NodeKind::complementNode:
        {
            BindUnaryOp(op, node.GetSourcePos(), child.release());
            break;
        }
        case otava::ast::NodeKind::derefNode:
        {
            BindDeref(node.GetSourcePos(), child.release());
            break;
        }
        case otava::ast::NodeKind::addrOfNode:
        {
            BindAddrOf(node.GetSourcePos(), child.release());
            break;
        }
        case otava::ast::NodeKind::prefixIncNode:
        {
            BindPrefixInc(node.GetSourcePos(), child.release(), node.Child());
            break;
        }
        case otava::ast::NodeKind::prefixDecNode:
        {
            BindPrefixDec(node.GetSourcePos(), child.release(), node.Child());
            break;
        }
    }
}

void ExpressionBinder::Visit(otava::ast::SubscriptExprNode& node)
{
    if (!Valid()) return;
    std::expected<BoundExpressionNode*, int> srv = BindExpression(node.Child(), context);
    if (!srv)
    {
        SetError(srv.error());
        return;
    }
    std::unique_ptr<BoundExpressionNode> subject(*srv);
    std::expected<BoundExpressionNode*, int> irv = BindExpression(node.Index(), context);
    if (!irv)
    {
        SetError(irv.error());
        return;
    }
    std::unique_ptr<BoundExpressionNode> index(*irv);
    TypeSymbol* plainSubjectType = subject->GetType()->PlainType(context);
    if (plainSubjectType->IsClassTypeSymbol())
    {
        BindBinaryOp(otava::ast::NodeKind::subscriptExprNode, node.GetSourcePos(), subject.release(), index.release());
    }
    else  if (plainSubjectType->IsPointerType())
    {
        BindBinaryOp(otava::ast::NodeKind::plusNode, node.GetSourcePos(), subject.release(), index.release());
        if (!Valid()) return;
        BindDeref(node.GetSourcePos(), boundExpression);
    }
    else if (plainSubjectType->IsArrayType())
    {
        ArrayTypeSymbol* arrayType = static_cast<ArrayTypeSymbol*>(plainSubjectType->GetBaseType());
        TypeSymbol* arrayPtrType = arrayType->AddPointer(context);
        std::unique_ptr<BoundExpressionNode> arrayPtr(new BoundAddressOfNode(subject->Clone(), node.GetSourcePos(), arrayPtrType));
        std::expected<FunctionSymbol*, int> rv = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
            arrayType->ElementType()->AddPointer(context), arrayPtrType, node.GetSourcePos(), context);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        FunctionSymbol* conversion = *rv;
        if (conversion)
        {
            BoundConversionNode* boundConversion = new BoundConversionNode(arrayPtr.release(), conversion, node.GetSourcePos());
            BindBinaryOp(otava::ast::NodeKind::plusNode, node.GetSourcePos(), boundConversion, index.release());
            BindDeref(node.GetSourcePos(), boundExpression);
        }
        else
        {
            std::unexpected<int> result = Error("no conversion found", node.GetSourcePos(), context);
            SetError(result.error());
            return;
        }
    }
    else
    {
        std::unexpected<int> result = Error("subscript operator can be applied only to pointer, array or class type subject", node.GetSourcePos(), context);
        SetError(result.error());
        return;
    }
}

void ExpressionBinder::Visit(otava::ast::ExpressionListNode& node)
{
    if (!Valid()) return;
    BoundExpressionListNode* boundExpressionListNode = new BoundExpressionListNode(node.GetSourcePos());
    for (int i = 0; i < node.Items().size(); ++i)
    {
        otava::ast::Node* itemNode = node.Items()[i];
        std::expected<BoundExpressionNode*, int> rv = BindExpression(itemNode, context);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        BoundExpressionNode* boundExpr = *rv;
        boundExpressionListNode->AddExpression(boundExpr);
    }
    boundExpression = boundExpressionListNode;
}

void ExpressionBinder::Visit(otava::ast::SizeOfTypeExprNode& node)
{
    if (!Valid()) return;
    std::expected<TypeSymbol*, int> trv = ResolveType(node.Child(), DeclarationFlags::none, context);
    if (!trv)
    {
        SetError(trv.error());
        return;
    }
    TypeSymbol* type = *trv;
    trv = type->DirectType(context)->FinalType(node.GetSourcePos(), context);
    if (!trv)
    {
        SetError(trv.error());
        return;
    }
    type = *trv;
    std::expected<otava::intermediate::Type*, int> irv = type->IrType(*context->GetEmitter(), node.GetSourcePos(), context);
    if (!irv)
    {
        SetError(irv.error());
        return;
    }
    otava::intermediate::Type* irType = *irv;
    std::int64_t size = irType->Size();
    otava::ast::IdentifierNode size_t_node(node.GetSourcePos(), U"ssize_t");
    trv = ResolveType(&size_t_node, DeclarationFlags::none, context);
    if (!trv)
    {
        SetError(trv.error());
        return;
    }
    TypeSymbol* size_t_type = *trv;
    while (size_t_type->IsAliasTypeSymbol())
    {
        AliasTypeSymbol* aliasType = static_cast<AliasTypeSymbol*>(size_t_type);
        size_t_type = aliasType->ReferredType();
    }
    std::expected<std::u32string, int> name = util::ToUtf32(std::to_string(size));
    if (!name)
    {
        SetError(name.error());
        return;
    }
    boundExpression = new BoundLiteralNode(new IntegerValue(size, *name, size_t_type), node.GetSourcePos());
}

void ExpressionBinder::Visit(otava::ast::SizeOfUnaryExprNode& node)
{
    if (!Valid()) return;
    std::expected<BoundExpressionNode*, int> rv = BindExpression(node.Child(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    boundExpression = *rv;
    TypeSymbol* type = boundExpression->GetType();
    std::expected<TypeSymbol*, int> trv = type->DirectType(context)->FinalType(node.GetSourcePos(), context);
    if (!trv)
    {
        SetError(trv.error());
        return;
    }
    type = *trv;
    std::expected<otava::intermediate::Type*, int> irv = type->IrType(*context->GetEmitter(), node.GetSourcePos(), context);
    if (!irv)
    {
        SetError(irv.error());
        return;
    }
    otava::intermediate::Type* irType = *irv;
    std::int64_t size = irType->Size();
    otava::ast::IdentifierNode size_t_node(node.GetSourcePos(), U"size_t");
    trv = ResolveType(&size_t_node, DeclarationFlags::none, context);
    if (!trv)
    {
        SetError(trv.error());
        return;
    }
    TypeSymbol* size_t_type = *trv;
    while (size_t_type->IsAliasTypeSymbol())
    {
        AliasTypeSymbol* aliasType = static_cast<AliasTypeSymbol*>(size_t_type);
        size_t_type = aliasType->ReferredType();
    }
    std::expected<std::u32string, int> rep = util::ToUtf32(std::to_string(size));
    if (!rep)
    {
        SetError(rep.error());
        return;
    }
    boundExpression = new BoundLiteralNode(new IntegerValue(size, *rep, size_t_type), node.GetSourcePos());
}

class NewInitializerBinder : public otava::ast::DefaultVisitor
{
public:
    NewInitializerBinder(Context* context_, std::vector<std::unique_ptr<BoundExpressionNode>>& boundExpressions_);
    void Visit(otava::ast::NewInitializerNode& node) override;
private:
    Context* context;
    std::vector<std::unique_ptr<BoundExpressionNode>>& boundExpressions;
};

NewInitializerBinder::NewInitializerBinder(Context* context_, std::vector<std::unique_ptr<BoundExpressionNode>>& boundExpressions_) : context(context_), boundExpressions(boundExpressions_)
{
}

void NewInitializerBinder::Visit(otava::ast::NewInitializerNode& node)
{
    int n = node.Count();
    for (int i = 0; i < n; ++i)
    {
        otava::ast::Node* initNode = node.Nodes()[i];
        if (!initNode->IsCommaNode())
        {
            std::expected<BoundExpressionNode*, int> rv = BindExpression(initNode, context);
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
            BoundExpressionNode* exprNode = *rv;
            boundExpressions.push_back(std::unique_ptr<BoundExpressionNode>(exprNode));
        }
    }
}

void ExpressionBinder::Visit(otava::ast::NewExprNode& node)
{
    if (!Valid()) return;
    std::expected<TypeSymbol*, int> trv = ResolveType(node.Child(), DeclarationFlags::none, context);
    if (!trv)
    {
        SetError(trv.error());
        return;
    }
    TypeSymbol* type = *trv;
    trv = type->DirectType(context)->FinalType(node.GetSourcePos(), context);
    if (!trv)
    {
        SetError(trv.error());
        return;
    }
    type = *trv;
    otava::ast::SizeOfTypeExprNode sizeOfNode(node.GetSourcePos(), node.Child()->Clone(), soul::ast::SourcePos(), soul::ast::SourcePos());
    std::expected<BoundExpressionNode*, int> rv = BindExpression(&sizeOfNode, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    std::unique_ptr<BoundExpressionNode> size(*rv);
    std::vector<std::unique_ptr<BoundExpressionNode>> args;
    args.push_back(std::unique_ptr<BoundExpressionNode>(size.release()));
    bool hasPlacement = false;
    if (node.Placement() && node.Placement()->IsNewPlacementNode())
    {
        hasPlacement = true;
        otava::ast::NewPlacementNode* placement = static_cast<otava::ast::NewPlacementNode*>(node.Placement());
        int n = placement->Items().size();
        for (int i = 0; i < n; ++i)
        {
            otava::ast::Node* item = placement->Items()[i];
            std::expected<BoundExpressionNode*, int> rv = BindExpression(item, context);
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
            BoundExpressionNode* boundItem = *rv;
            args.push_back(std::unique_ptr<BoundExpressionNode>(boundItem));
        }
    }
    std::vector<TypeSymbol*> templateArgs;
    std::expected<std::unique_ptr<BoundFunctionCallNode>, int> rrv = ResolveOverload(context->GetSymbolTable()->CurrentScope(), U"operator new", templateArgs, args, 
        node.GetSourcePos(), context);
    if (!rrv)
    {
        SetError(rrv.error());
        return;
    }
    std::unique_ptr<BoundFunctionCallNode> opNewCall = std::move(*rrv);
    std::expected<TypeSymbol*, int> frv = context->GetSymbolTable()->GetFundamentalTypeSymbol(FundamentalTypeKind::voidType);
    if (!frv)
    {
        SetError(frv.error());
        return;
    }
    TypeSymbol* voidType = *frv;
    TypeSymbol* voidPtrType = voidType->AddPointer(context);
    std::expected < VariableSymbol*, int> ttv = context->GetBoundFunction()->GetFunctionDefinitionSymbol()->CreateTemporary(type->AddPointer(context));
    if (!ttv)
    {
        SetError(ttv.error());
        return;
    }
    VariableSymbol* tempVarSymbol = *ttv;
    std::vector<std::unique_ptr<BoundExpressionNode>> ctorArgs;
    std::unique_ptr<BoundVariableNode> tempVar(new BoundVariableNode(tempVarSymbol, node.GetSourcePos()));
    TypeSymbol* tempVarPtrType = tempVar->GetType()->AddPointer(context);
    ctorArgs.push_back(std::unique_ptr<BoundExpressionNode>(new BoundAddressOfNode(tempVar.release(), node.GetSourcePos(), tempVarPtrType)));
    std::expected<FunctionSymbol*, int> arv = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
        type->AddPointer(context), voidPtrType, node.GetSourcePos(), context);
    if (!arv)
    {
        SetError(arv.error());
        return;
    }
    FunctionSymbol* conversion = *arv;
    if (conversion)
    {
        BoundConversionNode* boundConversion = new BoundConversionNode(opNewCall.release(), conversion, node.GetSourcePos());
        ctorArgs.push_back(std::unique_ptr<BoundExpressionNode>(boundConversion));
    }
    else
    {
        std::unexpected<int> result = Error("no conversion found", node.GetSourcePos(), context);
        SetError(result.error());
        return;
    }
    std::expected<std::unique_ptr<BoundFunctionCallNode>, int> orv = ResolveOverload(context->GetSymbolTable()->CurrentScope(), U"@constructor", templateArgs, ctorArgs, 
        node.GetSourcePos(), context);
    if (!orv)
    {
        SetError(orv.error());
        return;
    }
    std::unique_ptr<BoundFunctionCallNode> allocation = std::move(*orv);
    std::vector<std::unique_ptr<BoundExpressionNode>> constructObjectArgs;
    std::unique_ptr<BoundVariableNode> tempVar2(new BoundVariableNode(tempVarSymbol, node.GetSourcePos()));
    constructObjectArgs.push_back(std::unique_ptr<BoundExpressionNode>(tempVar2.release()));
    NewInitializerBinder initializerAdder(context, constructObjectArgs);
    if (node.Initializer())
    {
        node.Initializer()->Accept(initializerAdder);
        if (!initializerAdder)
        {
            SetError(initializerAdder.Error());
            return;
        }
        orv = ResolveOverload(context->GetSymbolTable()->CurrentScope(), U"@constructor", templateArgs, constructObjectArgs, node.GetSourcePos(), context);
        if (!orv)
        {
            SetError(orv.error());
            return;
        }
        std::unique_ptr<BoundFunctionCallNode> constructObjectCall = std::move(*orv);
        boundExpression = new BoundConstructExpressionNode(allocation.release(), constructObjectCall.release(), tempVarSymbol->GetType(), hasPlacement, node.GetSourcePos());
    }
    else
    {
        std::unexpected<int> result = Error("initializer not found", node.GetSourcePos(), context);
        SetError(result.error());
        return;
    }
}

void ExpressionBinder::Visit(otava::ast::DeletePtrNode& node)
{
    if (!Valid()) return;
    std::expected<BoundExpressionNode*, int> rv = BindExpression(node.Child(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    std::unique_ptr<BoundExpressionNode> ptr(*rv);
    std::vector<std::unique_ptr<BoundExpressionNode>> dtorArgs;
    dtorArgs.push_back(std::unique_ptr<BoundExpressionNode>(ptr->Clone()));
    std::vector<TypeSymbol*> templateArgs;
    std::expected<std::unique_ptr<BoundFunctionCallNode>, int> orv = ResolveOverload(context->GetSymbolTable()->CurrentScope(), U"@destructor", templateArgs, dtorArgs, 
        node.GetSourcePos(), context);
    if (!orv)
    {
        SetError(orv.error());
        return;
    }
    std::unique_ptr<BoundFunctionCallNode> dtor = std::move(*orv);
    std::vector<std::unique_ptr<BoundExpressionNode>> opDeleteArgs;
    opDeleteArgs.push_back(std::unique_ptr<BoundExpressionNode>(ptr->Clone()));
    if (dtor->GetFunctionSymbol()->IsVirtual())
    {
        dtor->SetFlag(BoundExpressionFlags::virtualCall);
    }
    orv = ResolveOverload(context->GetSymbolTable()->CurrentScope()->GetNamespaceScope(), U"operator delete", templateArgs, opDeleteArgs, node.GetSourcePos(), context);
    if (!orv)
    {
        SetError(orv.error());
        return;
    }
    std::unique_ptr<BoundFunctionCallNode> opDeleteCall = std::move(*orv);
    if (!dtor->GetFunctionSymbol()->IsTrivialDestructor())
    {
        boundExpression = new BoundExpressionSequenceNode(node.GetSourcePos(), dtor.release(), opDeleteCall.release());
    }
    else
    {
        boundExpression = opDeleteCall.release();
    }
}

void ExpressionBinder::Visit(otava::ast::BracedInitListNode& node)
{
    if (!Valid()) return;
    std::expected<Value*, int> rv = Evaluate(&node, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    Value* value = *rv;
    if (value)
    {
        boundExpression = new BoundLiteralNode(value, node.GetSourcePos());
        std::expected<bool, int> rv = context->GetBoundCompileUnit()->AddBoundNode(std::unique_ptr<BoundNode>(boundExpression), context);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
    }
}

void ExpressionBinder::Visit(otava::ast::PostfixIncExprNode& node)
{
    if (!Valid()) return;
    bool prevInhibitCompile = inhibitCompile;
    inhibitCompile = true;
    node.Child()->Accept(*this);
    if (!Valid()) return;
    inhibitCompile = prevInhibitCompile;
    if (!inhibitCompile)
    {
        if (boundExpression->GetType()->PlainType(context)->IsClassTypeSymbol())
        {
            std::vector<std::unique_ptr<BoundExpressionNode>> args;
            if (boundExpression->GetType()->IsReferenceType())
            {
                args.push_back(std::unique_ptr<BoundExpressionNode>(new BoundRefToPtrNode(boundExpression, node.GetSourcePos(),
                    boundExpression->GetType()->RemoveReference(context)->AddPointer(context))));
            }
            else
            {
                args.push_back(std::unique_ptr<BoundExpressionNode>(new BoundAddressOfNode(boundExpression, node.GetSourcePos(), boundExpression->GetType()->AddPointer(context))));
            }
            std::expected<TypeSymbol*, int> rv = context->GetSymbolTable()->GetFundamentalTypeSymbol(FundamentalTypeKind::intType);
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
            args.push_back(std::unique_ptr<BoundExpressionNode>(new BoundTypeNode(*rv, node.GetSourcePos())));
            std::vector<TypeSymbol*> templateArgs;
            std::expected< std::unique_ptr<BoundFunctionCallNode>, int> orv = ResolveOverload(scope, U"operator++", templateArgs, args, node.GetSourcePos(), context);
            if (!orv)
            {
                SetError(orv.error());
                return;
            }
            std::unique_ptr<BoundFunctionCallNode> functionCall = std::move(*orv);
            boundExpression = functionCall.release();
        }
        else
        {
            TypeSymbol* type = boundExpression->GetType();
            std::expected<std::u32string, int> trv = context->GetBoundFunction()->GetFunctionDefinitionSymbol()->NextTemporaryName();
            if (!trv)
            {
                SetError(trv.error());
                return;
            }
            VariableSymbol* temporary = context->GetSymbolTable()->AddVariable(*trv, &node, type, type, nullptr, DeclarationFlags::none, context);
            std::u32string temporaryName = temporary->Name();
            otava::ast::BinaryExprNode expr(node.GetSourcePos(),
                new otava::ast::CommaNode(node.GetSourcePos()),
                new otava::ast::BinaryExprNode(node.GetSourcePos(),
                    new otava::ast::CommaNode(node.GetSourcePos()),
                    new otava::ast::BinaryExprNode(node.GetSourcePos(),
                        new otava::ast::AssignNode(node.GetSourcePos()),
                        new otava::ast::IdentifierNode(node.GetSourcePos(), temporaryName),
                        node.Child()->Clone()),
                    new otava::ast::BinaryExprNode(node.GetSourcePos(),
                        new otava::ast::AssignNode(node.GetSourcePos()),
                        node.Child()->Clone(),
                        new otava::ast::BinaryExprNode(node.GetSourcePos(), new otava::ast::PlusNode(node.GetSourcePos()), node.Child()->Clone(),
                            new otava::ast::IntegerLiteralNode(node.GetSourcePos(), 1, otava::ast::Suffix::none, otava::ast::Base::decimal, U"")))),
                new otava::ast::IdentifierNode(node.GetSourcePos(), temporaryName));
            context->PushSetFlag(ContextFlags::suppress_warning);
            std::expected<BoundExpressionNode*, int> rv = BindExpression(&expr, context);
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
            boundExpression = *rv;
            context->PopFlags();
        }
    }
}

void ExpressionBinder::Visit(otava::ast::PostfixDecExprNode& node)
{
    if (!Valid()) return;
    bool prevInhibitCompile = inhibitCompile;
    inhibitCompile = true;
    node.Child()->Accept(*this);
    if (!Valid()) return;
    inhibitCompile = prevInhibitCompile;
    if (!inhibitCompile)
    {
        if (boundExpression->GetType()->PlainType(context)->IsClassTypeSymbol())
        {
            std::vector<std::unique_ptr<BoundExpressionNode>> args;
            if (boundExpression->GetType()->IsReferenceType())
            {
                args.push_back(std::unique_ptr<BoundExpressionNode>(new BoundRefToPtrNode(boundExpression, node.GetSourcePos(),
                    boundExpression->GetType()->RemoveReference(context)->AddPointer(context))));
            }
            else
            {
                args.push_back(std::unique_ptr<BoundExpressionNode>(new BoundAddressOfNode(boundExpression, node.GetSourcePos(), boundExpression->GetType()->AddPointer(context))));
            }
            std::expected<TypeSymbol*, int> rv = context->GetSymbolTable()->GetFundamentalTypeSymbol(FundamentalTypeKind::intType);
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
            args.push_back(std::unique_ptr<BoundExpressionNode>(new BoundTypeNode(*rv, node.GetSourcePos())));
            std::vector<TypeSymbol*> templateArgs;
            std::expected<std::unique_ptr<BoundFunctionCallNode>, int> orv = ResolveOverload(scope, U"operator--", templateArgs, args, node.GetSourcePos(), context);
            if (!orv)
            {
                SetError(orv.error());
                return;
            }
            std::unique_ptr<BoundFunctionCallNode> functionCall = std::move(*orv);
            boundExpression = functionCall.release();
        }
        else
        {
            TypeSymbol* type = boundExpression->GetType();
            std::expected<std::u32string, int> trv = context->GetBoundFunction()->GetFunctionDefinitionSymbol()->NextTemporaryName();
            if (!trv)
            {
                SetError(trv.error());
                return;
            }
            VariableSymbol* temporary = context->GetSymbolTable()->AddVariable(*trv, &node, type, type, nullptr, DeclarationFlags::none, context);
            std::u32string temporaryName = temporary->Name();
            otava::ast::BinaryExprNode expr(node.GetSourcePos(),
                new otava::ast::CommaNode(node.GetSourcePos()),
                new otava::ast::BinaryExprNode(node.GetSourcePos(),
                    new otava::ast::CommaNode(node.GetSourcePos()),
                    new otava::ast::BinaryExprNode(node.GetSourcePos(),
                        new otava::ast::AssignNode(node.GetSourcePos()),
                        new otava::ast::IdentifierNode(node.GetSourcePos(), temporaryName),
                        node.Child()->Clone()),
                    new otava::ast::BinaryExprNode(node.GetSourcePos(),
                        new otava::ast::AssignNode(node.GetSourcePos()),
                        node.Child()->Clone(),
                        new otava::ast::BinaryExprNode(node.GetSourcePos(), new otava::ast::MinusNode(node.GetSourcePos()), node.Child()->Clone(),
                            new otava::ast::IntegerLiteralNode(node.GetSourcePos(), 1, otava::ast::Suffix::none, otava::ast::Base::decimal, U"")))),
                new otava::ast::IdentifierNode(node.GetSourcePos(), temporaryName));
            std::expected<BoundExpressionNode*, int> rv = BindExpression(&expr, context);
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
            boundExpression = *rv;
        }
    }
}

std::expected<BoundExpressionNode*, int> BindExpression(otava::ast::Node* node, Context* context, SymbolGroupKind symbolGroups, Scope*& scope)
{
    ExpressionBinder binder(context, symbolGroups);
    node->Accept(binder);
    if (!binder) return std::unexpected<int>(binder.Error());
    scope = binder.GetScope();
    return std::expected<BoundExpressionNode*, int>(binder.GetBoundExpression());
}

std::expected<BoundExpressionNode*, int> BindExpression(otava::ast::Node* node, Context* context)
{
    return BindExpression(node, context, false);
}

std::expected<BoundExpressionNode*, int> BindExpression(otava::ast::Node* node, Context* context, bool booleanChild)
{
    Scope* scope = nullptr;
    std::expected<BoundExpressionNode*, int> rv = BindExpression(node, context, SymbolGroupKind::all, scope);
    if (!rv) return rv;
    BoundExpressionNode* expr = *rv;
    if (booleanChild && !expr->GetType()->IsBoolType())
    {
        std::expected<FunctionSymbol*, int> arv = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
            context->GetSymbolTable()->GetFundamentalType(otava::symbols::FundamentalTypeKind::boolType), expr->GetType(), node->GetSourcePos(), context);
        if (!arv)
        {
            return std::unexpected<int>(arv.error());
        }
        FunctionSymbol* conversionFunction = *arv;
        if (!conversionFunction)
        {
            return Error("expression must be convertible to Boolean type value", expr->GetSourcePos(), context);
        }
        expr = new BoundConversionNode(expr, conversionFunction, expr->GetSourcePos());
    }
    return std::expected<BoundExpressionNode*, int>(expr);
}

void InitExpressionBinder()
{
    OperatorGroupNameMap::Instance().Init();
}

} // namespace otava::symbols
