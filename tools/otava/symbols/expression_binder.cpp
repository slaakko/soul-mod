// =================================
// Copyright (c) 2022 Seppo Laakko
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
import otava.symbols.evaluator;
import otava.symbols.exception;
import otava.symbols.fundamental.type.symbol;
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
import otava.ast.identifier;
import otava.ast.punctuation;
import otava.ast.expression;
import otava.ast.literal;
import otava.ast.visitor;
import otava.ast.templates;
import otava.ast.statement;
import otava.ast.simple.type;
import util.unicode;
import util.text.util;
import std.core;

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

const std::u32string& OperatorGroupNameMap::GetGroupName(otava::ast::NodeKind nodeKind, const soul::ast::SourcePos& sourcePos, Context* context)
{
    auto it = operatorGroupNameMap.find(nodeKind);
    if (it != operatorGroupNameMap.cend())
    {
        return it->second;
    }
    else
    {
        ThrowException("group name for node kind '" + otava::ast::NodeKindStr(nodeKind) + "' not found", sourcePos, context);
    }
}

class GroupNameResolver : public DefaultBoundTreeVisitor
{
public:
    GroupNameResolver();
    const std::u32string& GetGroupName() const { return groupName; }
    void Visit(BoundFunctionGroupNode& node) override;
    void Visit(BoundVariableNode& node) override;
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
    BoundExpressionNode* GetFirstArg() const { return firstArg; }
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
    BoundExpressionNode* GetBoundExpression() const { return boundExpression; }
    Scope* GetScope() const { return scope; }
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
    void Visit(otava::ast::ThrowExprNode& node) override;
    void Visit(otava::ast::ExpressionListNode& node) override;
    void Visit(otava::ast::SizeOfTypeExprNode& node) override;
    void Visit(otava::ast::SizeOfUnaryExprNode& node) override;
    void Visit(otava::ast::NewExprNode& node) override;
    void Visit(otava::ast::DeletePtrNode& node) override;
private:
    void BindBinaryOp(otava::ast::NodeKind op, const soul::ast::SourcePos& sourcePos, BoundExpressionNode* left, BoundExpressionNode* right);
    void BindUnaryOp(otava::ast::NodeKind op, const soul::ast::SourcePos& sourcePos, BoundExpressionNode* operand);
    void BindClassArrow(BoundExpressionNode* operand, otava::ast::MemberExprNode* memberExprNode);
    void BindMemberExpr(otava::ast::MemberExprNode* node, BoundExpressionNode* subject);
    void BindDeref(const soul::ast::SourcePos& sourcePos, BoundExpressionNode* operand);
    void BindAddrOf(const soul::ast::SourcePos& sourcePos, BoundExpressionNode* operand);
    void BindPrefixInc(const soul::ast::SourcePos& sourcePos, BoundExpressionNode* operand, otava::ast::Node* child);
    void BindPrefixDec(const soul::ast::SourcePos& sourcePos, BoundExpressionNode* operand, otava::ast::Node* child);
    Context *context;
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
    std::u32string groupName = OperatorGroupNameMap::Instance().GetGroupName(op, sourcePos, context);
    std::vector<std::unique_ptr<BoundExpressionNode>> args;
    args.push_back(std::unique_ptr<BoundExpressionNode>(left));
    args.push_back(std::unique_ptr<BoundExpressionNode>(right));
    Exception ex;
    std::unique_ptr<BoundFunctionCallNode> functionCall = ResolveOverload(scope, groupName, args, sourcePos, context, ex);
    if (!functionCall)
    {
        TypeSymbol* type = args[0]->GetType()->AddPointer(context);
        args[0].reset(new BoundAddressOfNode(args[0].release(), sourcePos, type));
        Exception ex2;
        functionCall = ResolveOverload(scope, groupName, args, sourcePos, context, ex2);
    }
    if (!functionCall)
    {
        ThrowException(ex);
    }
    boundExpression = functionCall.release();
}

void ExpressionBinder::BindUnaryOp(otava::ast::NodeKind op, const soul::ast::SourcePos& sourcePos, BoundExpressionNode* operand)
{
    std::u32string groupName = OperatorGroupNameMap::Instance().GetGroupName(op, sourcePos, context);
    std::vector<std::unique_ptr<BoundExpressionNode>> args;
    args.push_back(std::unique_ptr<BoundExpressionNode>(operand));
    Exception ex;
    std::unique_ptr<BoundFunctionCallNode> functionCall = ResolveOverload(scope, groupName, args, sourcePos, context, ex);
    if (!functionCall)
    {
        TypeSymbol* type = args[0]->GetType()->AddPointer(context);
        args[0].reset(new BoundAddressOfNode(args[0].release(), sourcePos, type));
        functionCall = ResolveOverload(scope, groupName, args, sourcePos, context, ex);
    }
    if (!functionCall)
    {
        ThrowException(ex);
    }
    boundExpression = functionCall.release();
}

void ExpressionBinder::BindClassArrow(BoundExpressionNode* operand, otava::ast::MemberExprNode* memberExprNode)
{
    if (operand->GetType()->IsReferenceType())
    {
        operand = new BoundRefToPtrNode(operand, memberExprNode->GetSourcePos(), operand->GetType()->RemoveReference(context)->AddPointer(context));
    }
    else
    {
        operand = new BoundAddressOfNode(operand, memberExprNode->GetSourcePos(), operand->GetType()->AddPointer(context));
    }
    BindUnaryOp(otava::ast::NodeKind::arrowNode, memberExprNode->GetSourcePos(), operand);
    while (boundExpression->GetType()->IsClassTypeSymbol())
    {
        BindUnaryOp(otava::ast::NodeKind::arrowNode, memberExprNode->GetSourcePos(), boundExpression);
    }
    BindMemberExpr(memberExprNode, boundExpression);
}

void ExpressionBinder::BindDeref(const soul::ast::SourcePos& sourcePos, BoundExpressionNode* operand)
{
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
            boundExpression = new BoundDereferenceNode(operand, sourcePos, operand->GetType()->RemovePointer(context));
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
            ThrowException("dereference needs pointer or class type argument", sourcePos, context);
        }
    }
}

void ExpressionBinder::BindAddrOf(const soul::ast::SourcePos& sourcePos, BoundExpressionNode* operand)
{
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
        ThrowException("cannot take address of this kind of expression", sourcePos, context);
    }
}

void ExpressionBinder::BindPrefixInc(const soul::ast::SourcePos& sourcePos, BoundExpressionNode* operand, otava::ast::Node* child)
{
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
    }
    else
    {
        otava::ast::BinaryExprNode assignmentExpr(sourcePos,
            new otava::ast::AssignNode(sourcePos),
            child->Clone(),
            new otava::ast::BinaryExprNode(sourcePos, new otava::ast::PlusNode(sourcePos), child->Clone(),
                new otava::ast::IntegerLiteralNode(sourcePos, 1, otava::ast::Suffix::none, otava::ast::Base::decimal, U"")));
        boundExpression = BindExpression(&assignmentExpr, context);
    }
}

void ExpressionBinder::BindPrefixDec(const soul::ast::SourcePos& sourcePos, BoundExpressionNode* operand, otava::ast::Node* child)
{
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
    }
    else
    {
        otava::ast::BinaryExprNode assignmentExpr(sourcePos,
            new otava::ast::AssignNode(sourcePos),
            child->Clone(),
            new otava::ast::BinaryExprNode(sourcePos, new otava::ast::MinusNode(sourcePos), child->Clone(),
                new otava::ast::IntegerLiteralNode(sourcePos, 1, otava::ast::Suffix::none, otava::ast::Base::decimal, U"")));
        boundExpression = BindExpression(&assignmentExpr, context);
    }
}

void ExpressionBinder::Visit(otava::ast::CppCastExprNode& node)
{
    TypeSymbol* resultType = ResolveType(node.TypeId(), DeclarationFlags::none, context);
    resultType = resultType->DirectType(context);
    node.Child()->Accept(*this);
    FunctionSymbol* conversion = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
        resultType, boundExpression->GetType(), node.GetSourcePos(), context);
    if (conversion)
    {
        boundExpression = new BoundConversionNode(boundExpression, conversion, node.GetSourcePos());
    }
    else
    {
        ThrowException("no conversion found", node.GetSourcePos(), context);
    }
}

otava::ast::Node* MakeTypeNameNodes(const soul::ast::SourcePos& sourcePos, const std::u32string& fullTypeName)
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
            nnsNode->AddNode(identifierNode);
            nnsNode->AddNode(new otava::ast::ColonColonNode(sourcePos));
            node = new otava::ast::QualifiedIdNode(sourcePos, nnsNode, node);
        }
        else
        {
            node = identifierNode;
        }
    }
    return node;
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

NewInitializerMaker::NewInitializerMaker(const soul::ast::SourcePos& sourcePos_)  : newInitializer(new otava::ast::NewInitializerNode(sourcePos_)), sourcePos(sourcePos_)
{
}

void NewInitializerMaker::Visit(otava::ast::InvokeExprNode& node)
{
    int n = node.Items().size();
    for (int i = 0; i < n; ++i)
    {
        otava::ast::Node* arg = node.Items()[i]->Clone();
        newInitializer->AddNode(arg);
    }
}

otava::ast::NewInitializerNode* MakeNewInitializer(otava::ast::ThrowExprNode& node)
{
    NewInitializerMaker maker(node.GetSourcePos());
    node.Accept(maker);
    return maker.GetNewInitializer();
}

void ExpressionBinder::Visit(otava::ast::ThrowExprNode& node)
{
    if (node.Exception())
    {
        node.Exception()->Accept(*this);
        otava::ast::NewInitializerNode* initializer = MakeNewInitializer(node);
        otava::ast::NewExprNode* newNode = new otava::ast::NewExprNode(node.GetSourcePos(), nullptr,
           MakeTypeNameNodes(node.GetSourcePos(), boundExpression->GetType()->FullName()), initializer, nullptr, node.GetSourcePos());
        newNode->Accept(*this);
    }
    else
    {
        boundExpression = nullptr;
    }
    boundExpression = new BoundThrowExpressionNode(boundExpression, node.GetSourcePos());
}

void ExpressionBinder::Visit(otava::ast::IntegerLiteralNode& node) 
{
    boundExpression = new BoundLiteralNode(Evaluate(&node, context), node.GetSourcePos());
}

void ExpressionBinder::Visit(otava::ast::FloatingLiteralNode& node)
{
    boundExpression = new BoundLiteralNode(Evaluate(&node, context), node.GetSourcePos());
}

void ExpressionBinder::Visit(otava::ast::CharacterLiteralNode& node)
{
    boundExpression = new BoundLiteralNode(Evaluate(&node, context), node.GetSourcePos());
}

void ExpressionBinder::Visit(otava::ast::StringLiteralNode& node)
{
    boundExpression = new BoundStringLiteralNode(Evaluate(&node, context), node.GetSourcePos());
}

void ExpressionBinder::Visit(otava::ast::RawStringLiteralNode& node)
{
    boundExpression = new BoundLiteralNode(Evaluate(&node, context), node.GetSourcePos());
}

void ExpressionBinder::Visit(otava::ast::BooleanLiteralNode& node)
{
    boundExpression = new BoundLiteralNode(Evaluate(&node, context), node.GetSourcePos());
}

void ExpressionBinder::Visit(otava::ast::NullPtrLiteralNode& node)
{
    boundExpression = new BoundLiteralNode(Evaluate(&node, context), node.GetSourcePos());
}

void ExpressionBinder::Visit(otava::ast::CharNode& node)
{
    boundExpression = new BoundTypeNode(context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::charType), node.GetSourcePos());
}

void ExpressionBinder::Visit(otava::ast::Char8Node& node)
{
    boundExpression = new BoundTypeNode(context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::char8Type), node.GetSourcePos());
}

void ExpressionBinder::Visit(otava::ast::Char16Node& node)
{
    boundExpression = new BoundTypeNode(context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::char16Type), node.GetSourcePos());
}

void ExpressionBinder::Visit(otava::ast::Char32Node& node)
{
    boundExpression = new BoundTypeNode(context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::char32Type), node.GetSourcePos());
}

void ExpressionBinder::Visit(otava::ast::WCharNode& node)
{
    boundExpression = new BoundTypeNode(context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::wcharType), node.GetSourcePos());
}

void ExpressionBinder::Visit(otava::ast::BoolNode& node)
{
    boundExpression = new BoundTypeNode(context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::boolType), node.GetSourcePos());
}

void ExpressionBinder::Visit(otava::ast::ShortNode& node)
{
    boundExpression = new BoundTypeNode(context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::shortIntType), node.GetSourcePos());
}

void ExpressionBinder::Visit(otava::ast::IntNode& node)
{
    boundExpression = new BoundTypeNode(context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::intType), node.GetSourcePos());
}

void ExpressionBinder::Visit(otava::ast::LongNode& node)
{
    boundExpression = new BoundTypeNode(context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::longIntType), node.GetSourcePos());
}

void ExpressionBinder::Visit(otava::ast::SignedNode& node)
{
    boundExpression = new BoundTypeNode(context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::intType), node.GetSourcePos());
}

void ExpressionBinder::Visit(otava::ast::UnsignedNode& node) 
{
    boundExpression = new BoundTypeNode(context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::unsignedIntType), node.GetSourcePos());
}

void ExpressionBinder::Visit(otava::ast::FloatNode& node)
{
    boundExpression = new BoundTypeNode(context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::floatType), node.GetSourcePos());
}

void ExpressionBinder::Visit(otava::ast::DoubleNode& node)
{
    boundExpression = new BoundTypeNode(context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::doubleType), node.GetSourcePos());
}

void ExpressionBinder::Visit(otava::ast::IdentifierNode& node)
{
    Symbol* symbol = nullptr;
    if (qualifiedScope)
    {
        symbol = scope->Lookup(node.Str(), symbolGroups, ScopeLookup::thisScope, node.GetSourcePos(), context, LookupFlags::dontResolveSingle);
    }
    if (!symbol)
    {
        symbol = scope->Lookup(node.Str(), symbolGroups, ScopeLookup::allScopes, node.GetSourcePos(), context, LookupFlags::dontResolveSingle);
    }
    if (!symbol)
    {
        ClassTemplateSpecializationSymbol* sp = static_cast<ClassTemplateSpecializationSymbol*>(scope->GetClassTemplateSpecialization());
        if (sp)
        {
            symbol = sp->ClassTemplate()->GetScope()->Lookup(node.Str(), symbolGroups, ScopeLookup::allScopes, node.GetSourcePos(), context, LookupFlags::dontResolveSingle);
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
                if (sym->IsVariableSymbol())
                {
                    VariableSymbol* variable = static_cast<VariableSymbol*>(sym);
                    BoundVariableNode* boundVariable = new BoundVariableNode(variable, node.GetSourcePos());
                    if (variable->IsMemberVariable())
                    {
                        boundVariable->SetThisPtr(context->GetThisPtr(node.GetSourcePos()));
                    }
                    boundExpression = boundVariable;
                }
                break;
            }
            case SymbolKind::classGroupSymbol:
            {
                ClassGroupSymbol* classGroup = static_cast<ClassGroupSymbol*>(symbol);
                Symbol* sym = classGroup->GetSingleSymbol();
                if (sym->IsClassTypeSymbol())
                {
                    ClassTypeSymbol* cls = static_cast<ClassTypeSymbol*>(sym);
                    boundExpression = new BoundTypeNode(cls, node.GetSourcePos());
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
                if (sym->IsAliasTypeSymbol())
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
                boundExpression = new BoundParameterNode(parameter, node.GetSourcePos(), parameter->GetReferredType(context));
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
            default:
            {
                ThrowException("symbol '" + util::ToUtf8(node.Str()) + "' processing not implemented", node.GetSourcePos(), context);
            }
        }
    }
    else
    {
        ThrowException("symbol '" + util::ToUtf8(node.Str()) + "' not found", node.GetSourcePos(), context);
    }
}

void ExpressionBinder::Visit(otava::ast::QualifiedIdNode& node)
{
    scope = ResolveScope(node.Left(), context);
    bool prevQualifiedScope = qualifiedScope;
    qualifiedScope = true;
    node.Right()->Accept(*this);
    qualifiedScope = prevQualifiedScope;
}

void ExpressionBinder::Visit(otava::ast::DestructorIdNode& node)
{
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
    ParameterSymbol* thisParam = context->GetBoundFunction()->GetFunctionDefinitionSymbol()->ThisParam(context);
    if (thisParam)
    {
        boundExpression = new BoundParameterNode(thisParam, node.GetSourcePos(), thisParam->GetType());
    }
    else
    {
        ThrowException("'this' can only be used in member function context", node.GetSourcePos(), context);
    }
}

void ExpressionBinder::Visit(otava::ast::TemplateIdNode& node)
{
    context->GetSymbolTable()->BeginScope(scope);
    TypeSymbol* type = ResolveType(&node, DeclarationFlags::none, context);
    type = type->DirectType(context);
    boundExpression = new BoundTypeNode(type, node.GetSourcePos());
    context->GetSymbolTable()->EndScope();
}

void ExpressionBinder::Visit(otava::ast::MemberExprNode& node)
{
    std::unique_ptr<BoundExpressionNode> subject(BindExpression(node.Child(), context));
    BindMemberExpr(&node, subject.release());
}

void ExpressionBinder::BindMemberExpr(otava::ast::MemberExprNode* node, BoundExpressionNode* subject)
{
    if (node->Op()->Kind() == otava::ast::NodeKind::arrowNode && subject->GetType()->PlainType(context)->IsClassTypeSymbol())
    {
        BindClassArrow(subject, node);
        return;
    }
    Scope* memberScope = subject->GetMemberScope(node->Op(), node->GetSourcePos(), context);
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
        memberVar->SetThisPtr(new BoundAddressOfNode(localVar, node->GetSourcePos(), localVar->GetType()->AddPointer(context)));
        boundExpression = memberVar;
    }
    else if (subject->IsBoundParameterNode() && member->IsBoundMemberVariable())
    {
        BoundParameterNode* param = static_cast<BoundParameterNode*>(subject);
        if (param->GetType()->PlainType(context)->IsClassTypeSymbol())
        {
            BoundExpressionNode* thisPtr = nullptr;
            if (param->GetType()->IsReferenceType())
            {
                thisPtr = new BoundRefToPtrNode(param, node->GetSourcePos(), param->GetType()->RemoveReference(context)->AddPointer(context));
            }
            else
            {
                thisPtr = new BoundAddressOfNode(param, node->GetSourcePos(), param->GetType()->AddPointer(context));
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
    bool thisPtrAdded = false;
    VariableSymbol* temporary = nullptr;
    Scope* subjectScope = scope;
    OverloadResolutionFlags resolutionFlags = OverloadResolutionFlags::none;
    if (node.Subject()->IsQualifiedIdNode())
    {
        resolutionFlags = resolutionFlags | OverloadResolutionFlags::dontSearchArgumentScopes;
    }
    std::unique_ptr<BoundExpressionNode> subject(BindExpression(node.Subject(), context, 
        SymbolGroupKind::functionSymbolGroup | SymbolGroupKind::typeSymbolGroup | SymbolGroupKind::variableSymbolGroup, subjectScope));
    if (subject)
    {
        if (subject->IsBoundEmptyDestructorNode())
        {
            boundExpression = new BoundEmptyFunctionCallNode(node.GetSourcePos());
            return;
        }
        std::vector<std::unique_ptr<BoundExpressionNode>> args;
        if (subject->IsBoundTypeNode())
        {
            temporary = context->GetBoundFunction()->GetFunctionDefinitionSymbol()->CreateTemporary(subject->GetType());
            BoundAddressOfNode* boundAddrOfNode = new BoundAddressOfNode(new BoundVariableNode(temporary, node.GetSourcePos()), node.GetSourcePos(), 
                temporary->GetType()->AddPointer(context));
            args.push_back(std::unique_ptr<BoundExpressionNode>(boundAddrOfNode));
            resolutionFlags = resolutionFlags & ~OverloadResolutionFlags::dontSearchArgumentScopes;
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
            std::unique_ptr<BoundExpressionNode> arg(BindExpression(item, context));
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
        Exception ex;
        std::unique_ptr<BoundFunctionCallNode> functionCall = ResolveOverload(subjectScope, groupName, args, node.GetSourcePos(), context, ex, resolutionFlags);
        if (!functionCall && thisPtrAdded)
        {
            args.erase(args.begin());
            Exception ex2;
            functionCall = ResolveOverload(subjectScope, groupName, args, node.GetSourcePos(), context, ex2, resolutionFlags);
        }
        if (!functionCall)
        {
            ThrowException(ex);
        }
        FunctionSymbol* functionSymbol = functionCall->GetFunctionSymbol();
        if (functionSymbol->IsVirtual())
        {
            functionCall->SetFlag(BoundExpressionFlags::virtualCall);
        }
        VariableSymbol* classTemporary = nullptr;
        if (functionSymbol->ReturnsClass())
        {
            classTemporary = context->GetBoundFunction()->GetFunctionDefinitionSymbol()->CreateTemporary(functionSymbol->ReturnType());
            functionCall->AddArgument(new BoundAddressOfNode(
                new BoundVariableNode(classTemporary, node.GetSourcePos()), node.GetSourcePos(), classTemporary->GetType()->AddPointer(context)));
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
        ThrowException("unkown invoke subject", node.GetSourcePos(), context);
    }
}

void ExpressionBinder::Visit(otava::ast::BinaryExprNode& node)
{
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
    std::unique_ptr<BoundExpressionNode> left(BindExpression(node.Left(), context, booleanChild));
    std::unique_ptr<BoundExpressionNode> right(BindExpression(node.Right(), context, booleanChild));
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
            BindUnaryOp(otava::ast::NodeKind::notNode, node.GetSourcePos(), boundExpression);
            break;
        }
        case otava::ast::NodeKind::greaterOrEqualNode:
        {
            BindBinaryOp(otava::ast::NodeKind::lessNode, node.GetSourcePos(), left.release(), right.release());
            BindUnaryOp(otava::ast::NodeKind::notNode, node.GetSourcePos(), boundExpression);
            break;
        }
        case otava::ast::NodeKind::disjunctionNode:
        {
            TypeSymbol* boolType = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::boolType);
            BoundDisjunctionNode* boundDisjunction = new BoundDisjunctionNode(left.release(), right.release(), node.GetSourcePos(), boolType);
            VariableSymbol* temporary = context->GetBoundFunction()->GetFunctionDefinitionSymbol()->CreateTemporary(boolType);
            boundDisjunction->SetTemporary(new BoundVariableNode(temporary, node.GetSourcePos()));
            boundExpression = boundDisjunction;
            break;
        }
        case otava::ast::NodeKind::conjunctionNode:
        {
            TypeSymbol* boolType = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::boolType);
            BoundConjunctionNode* boundConjunction = new BoundConjunctionNode(left.release(), right.release(), node.GetSourcePos(), boolType);
            VariableSymbol* temporary = context->GetBoundFunction()->GetFunctionDefinitionSymbol()->CreateTemporary(boolType);
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
    std::unique_ptr<BoundExpressionNode> child(BindExpression(node.Child(), context));
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
    std::unique_ptr<BoundExpressionNode> subject(BindExpression(node.Child(), context));
    std::unique_ptr<BoundExpressionNode> index(BindExpression(node.Index(), context));
    TypeSymbol* plainSubjectType = subject->GetType()->PlainType(context);
    if (plainSubjectType->IsClassTypeSymbol())
    {
        BindBinaryOp(otava::ast::NodeKind::subscriptExprNode, node.GetSourcePos(), subject.release(), index.release());
    }
    else  if (plainSubjectType->IsPointerType())
    {
        BindBinaryOp(otava::ast::NodeKind::plusNode, node.GetSourcePos(), subject.release(), index.release());
        BindDeref(node.GetSourcePos(), boundExpression);
    }
    else if (plainSubjectType->IsArrayType())
    {
        ArrayTypeSymbol* arrayType = static_cast<ArrayTypeSymbol*>(plainSubjectType->GetBaseType());
        TypeSymbol* arrayPtrType = arrayType->AddPointer(context);
        std::unique_ptr<BoundExpressionNode> arrayPtr(new BoundAddressOfNode(subject->Clone(), node.GetSourcePos(), arrayPtrType));
        FunctionSymbol* conversion = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
            arrayType->ElementType()->AddPointer(context), arrayPtrType, node.GetSourcePos(), context);
        if (conversion)
        {
            BoundConversionNode* boundConversion = new BoundConversionNode(arrayPtr.release(), conversion, node.GetSourcePos());
            BindBinaryOp(otava::ast::NodeKind::plusNode, node.GetSourcePos(), boundConversion, index.release());
            BindDeref(node.GetSourcePos(), boundExpression);
        }
        else
        {
            ThrowException("no conversion found", node.GetSourcePos(), context);
        }
    }
    else
    {
        ThrowException("subscript operator can be applied only to pointer, array or class type subject", node.GetSourcePos(), context);
    }
}

void ExpressionBinder::Visit(otava::ast::ExpressionListNode& node)
{
    BoundExpressionListNode* boundExpressionListNode = new BoundExpressionListNode(node.GetSourcePos());
    for (int i = 0; i < node.Items().size(); ++i)
    {
        otava::ast::Node* itemNode = node.Items()[i];
        BoundExpressionNode* boundExpr = BindExpression(itemNode, context);
        boundExpressionListNode->AddExpression(boundExpr);
    }
    boundExpression = boundExpressionListNode;
}

void ExpressionBinder::Visit(otava::ast::SizeOfTypeExprNode& node)
{
    TypeSymbol* type = ResolveType(node.Child(), DeclarationFlags::none, context);
    type = type->DirectType(context);
    Emitter emitter(nullptr);
    otava::intermediate::Type* irType = type->IrType(emitter, node.GetSourcePos(), context);
    int64_t size = irType->Size();
    otava::ast::IdentifierNode size_t_node(node.GetSourcePos(), U"ssize_t");
    TypeSymbol* size_t_type = ResolveType(&size_t_node, DeclarationFlags::none, context);
    while (size_t_type->IsAliasTypeSymbol())
    {
        AliasTypeSymbol* aliasType = static_cast<AliasTypeSymbol*>(size_t_type);
        size_t_type = aliasType->ReferredType();
    }
    boundExpression = new BoundLiteralNode(new IntegerValue(size, util::ToUtf32(std::to_string(size)), size_t_type), node.GetSourcePos());
}

void ExpressionBinder::Visit(otava::ast::SizeOfUnaryExprNode& node)
{
    boundExpression = BindExpression(node.Child(), context);
    TypeSymbol* type = boundExpression->GetType();
    type = type->DirectType(context);
    Emitter emitter(nullptr);
    otava::intermediate::Type* irType = type->IrType(emitter, node.GetSourcePos(), context);
    int64_t size = irType->Size();
    otava::ast::IdentifierNode size_t_node(node.GetSourcePos(), U"size_t");
    TypeSymbol* size_t_type = ResolveType(&size_t_node, DeclarationFlags::none, context);
    while (size_t_type->IsAliasTypeSymbol())
    {
        AliasTypeSymbol* aliasType = static_cast<AliasTypeSymbol*>(size_t_type);
        size_t_type = aliasType->ReferredType();
    }
    boundExpression = new BoundLiteralNode(new IntegerValue(size, util::ToUtf32(std::to_string(size)), size_t_type), node.GetSourcePos());
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
            BoundExpressionNode* exprNode = BindExpression(initNode, context);
            boundExpressions.push_back(std::unique_ptr<BoundExpressionNode>(exprNode));
        }
    }
}

void ExpressionBinder::Visit(otava::ast::NewExprNode& node)
{
    TypeSymbol* type = ResolveType(node.Child(), DeclarationFlags::none, context);
    type = type->DirectType(context);
    otava::ast::SizeOfTypeExprNode sizeOfNode(node.GetSourcePos(), node.Child()->Clone(), soul::ast::SourcePos(), soul::ast::SourcePos());
    std::unique_ptr<BoundExpressionNode> size(BindExpression(&sizeOfNode, context));
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
            BoundExpressionNode* boundItem = BindExpression(item, context);
            args.push_back(std::unique_ptr<BoundExpressionNode>(boundItem));
        }
    }
    std::unique_ptr<BoundFunctionCallNode> opNewCall = ResolveOverloadThrow(context->GetSymbolTable()->CurrentScope(), U"operator new", args, node.GetSourcePos(), context);
    TypeSymbol* voidPtrType = context->GetSymbolTable()->GetFundamentalTypeSymbol(FundamentalTypeKind::voidType)->AddPointer(context);
    VariableSymbol* tempVarSymbol = context->GetBoundFunction()->GetFunctionDefinitionSymbol()->CreateTemporary(type->AddPointer(context));
    std::vector<std::unique_ptr<BoundExpressionNode>> ctorArgs;
    std::unique_ptr<BoundVariableNode> tempVar(new BoundVariableNode(tempVarSymbol, node.GetSourcePos()));
    TypeSymbol* tempVarPtrType = tempVar->GetType()->AddPointer(context);
    ctorArgs.push_back(std::unique_ptr<BoundExpressionNode>(new BoundAddressOfNode(tempVar.release(), node.GetSourcePos(), tempVarPtrType)));
    FunctionSymbol* conversion = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
        type->AddPointer(context), voidPtrType, node.GetSourcePos(), context);
    if (conversion)
    {
        BoundConversionNode* boundConversion = new BoundConversionNode(opNewCall.release(), conversion, node.GetSourcePos());
        ctorArgs.push_back(std::unique_ptr<BoundExpressionNode>(boundConversion));
    }
    else
    {
        ThrowException("no conversion found", node.GetSourcePos(), context);
    }
    std::unique_ptr<BoundFunctionCallNode> allocation = ResolveOverloadThrow(
        context->GetSymbolTable()->CurrentScope(), U"@constructor", ctorArgs, node.GetSourcePos(), context);
    std::vector<std::unique_ptr<BoundExpressionNode>> constructObjectArgs;
    std::unique_ptr<BoundVariableNode> tempVar2(new BoundVariableNode(tempVarSymbol, node.GetSourcePos()));
    constructObjectArgs.push_back(std::unique_ptr<BoundExpressionNode>(tempVar2.release()));
    NewInitializerBinder initializerAdder(context, constructObjectArgs);
    node.Initializer()->Accept(initializerAdder);
    std::unique_ptr<BoundFunctionCallNode> constructObjectCall = ResolveOverloadThrow(
        context->GetSymbolTable()->CurrentScope(), U"@constructor", constructObjectArgs, node.GetSourcePos(), context);
    boundExpression = new BoundConstructExpressionNode(allocation.release(), constructObjectCall.release(), tempVarSymbol->GetType(), hasPlacement, node.GetSourcePos());
}

void ExpressionBinder::Visit(otava::ast::DeletePtrNode& node)
{
    std::unique_ptr<BoundExpressionNode> ptr(BindExpression(node.Child(), context));
    std::vector<std::unique_ptr<BoundExpressionNode>> dtorArgs;
    dtorArgs.push_back(std::unique_ptr<BoundExpressionNode>(ptr->Clone()));
    std::unique_ptr<BoundFunctionCallNode> dtor = ResolveOverloadThrow(
        context->GetSymbolTable()->CurrentScope(), U"@destructor", dtorArgs, node.GetSourcePos(), context);
    std::vector<std::unique_ptr<BoundExpressionNode>> opDeleteArgs;
    opDeleteArgs.push_back(std::unique_ptr<BoundExpressionNode>(ptr->Clone()));
    if (dtor->GetFunctionSymbol()->IsVirtual())
    {
        dtor->SetFlag(BoundExpressionFlags::virtualCall);
    }
    std::unique_ptr<BoundFunctionCallNode> opDeleteCall = ResolveOverloadThrow(context->GetSymbolTable()->CurrentScope()->GetNamespaceScope(), U"operator delete",
        opDeleteArgs, node.GetSourcePos(), context);
    if (!dtor->GetFunctionSymbol()->IsTrivialDestructor())
    {
        boundExpression = new BoundExpressionSequenceNode(node.GetSourcePos(), dtor.release(), opDeleteCall.release());
    }
    else
    {
        boundExpression = opDeleteCall.release();
    }
}

void ExpressionBinder::Visit(otava::ast::PostfixIncExprNode& node)
{
    bool prevInhibitCompile = inhibitCompile;
    inhibitCompile = true;
    node.Child()->Accept(*this);
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
            args.push_back(std::unique_ptr<BoundExpressionNode>(new BoundTypeNode(context->GetSymbolTable()->GetFundamentalTypeSymbol(FundamentalTypeKind::intType), 
                node.GetSourcePos())));
            std::unique_ptr<BoundFunctionCallNode> functionCall = ResolveOverloadThrow(scope, U"operator++", args, node.GetSourcePos(), context);
            boundExpression = functionCall.release();
        }
        else
        {
            TypeSymbol* type = boundExpression->GetType();
            VariableSymbol* temporary = context->GetSymbolTable()->AddVariable(context->GetBoundFunction()->GetFunctionDefinitionSymbol()->NextTemporaryName(),
                &node, type, type, nullptr, DeclarationFlags::none, context);
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
            boundExpression = BindExpression(&expr, context);
        }
    }
}

void ExpressionBinder::Visit(otava::ast::PostfixDecExprNode& node)
{
    bool prevInhibitCompile = inhibitCompile;
    inhibitCompile = true;
    node.Child()->Accept(*this);
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
            args.push_back(std::unique_ptr<BoundExpressionNode>(new BoundTypeNode(context->GetSymbolTable()->GetFundamentalTypeSymbol(FundamentalTypeKind::intType),
                node.GetSourcePos())));
            std::unique_ptr<BoundFunctionCallNode> functionCall = ResolveOverloadThrow(scope, U"operator--", args, node.GetSourcePos(), context);
            boundExpression = functionCall.release();
        }
        else
        {
            TypeSymbol* type = boundExpression->GetType();
            VariableSymbol* temporary = context->GetSymbolTable()->AddVariable(context->GetBoundFunction()->GetFunctionDefinitionSymbol()->NextTemporaryName(),
                &node, type, type, nullptr, DeclarationFlags::none, context);
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
            boundExpression = BindExpression(&expr, context);
        }
    }
}

BoundExpressionNode* BindExpression(otava::ast::Node* node, Context* context, SymbolGroupKind symbolGroups, Scope*& scope)
{
    ExpressionBinder binder(context, symbolGroups);
    node->Accept(binder);
    scope = binder.GetScope();
    return binder.GetBoundExpression();
}

BoundExpressionNode* BindExpression(otava::ast::Node* node, Context* context)
{
    return BindExpression(node, context, false);
}

BoundExpressionNode* BindExpression(otava::ast::Node* node, Context* context, bool booleanChild)
{
    Scope* scope = nullptr;
    BoundExpressionNode* expr = BindExpression(node, context, SymbolGroupKind::all, scope);
    if (booleanChild && !expr->GetType()->IsBoolType())
    {
        FunctionSymbol* conversionFunction = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
            context->GetSymbolTable()->GetFundamentalType(otava::symbols::FundamentalTypeKind::boolType), expr->GetType(), node->GetSourcePos(), context);
        if (!conversionFunction)
        {
            ThrowException("expression must be convertible to Boolean type value", expr->GetSourcePos(), context);
        }
        expr = new BoundConversionNode(expr, conversionFunction, expr->GetSourcePos());
    }
    return expr;
}

void InitExpressionBinder()
{
    OperatorGroupNameMap::Instance().Init();
}

} // namespace otava::symbols

