// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.expression.binder;

import otava.symbols.alias.group.symbol;
import otava.symbols.alias.type.symbol;
import otava.symbols.bound.tree;
import otava.symbols.bound.node;
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
import otava.ast.identifier;
import otava.ast.expression;
import otava.ast.literal;
import otava.ast.visitor;
import otava.ast.templates;
import util.unicode;
import std.core;

namespace otava::symbols {

BoundExpressionNode* MakeAddressArg(BoundExpressionNode* node)
{
    if (node->GetType()->IsReferenceType())
    {
        return new BoundRefToPtrNode(node, node->GetSourcePos());
    }
    else
    {
        return new BoundAddressOfNode(node, node->GetSourcePos());
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

std::u32string GetGroupName(BoundNode* node)
{
    GroupNameResolver groupNameResolver;
    node->Accept(groupNameResolver);
    return groupNameResolver.GetGroupName();
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
    void Visit(otava::ast::IdentifierNode& node) override;
    void Visit(otava::ast::QualifiedIdNode& node) override;
    void Visit(otava::ast::TemplateIdNode& node) override;
    void Visit(otava::ast::MemberExprNode& node) override;
    void Visit(otava::ast::InvokeExprNode& node) override;
    void Visit(otava::ast::BinaryExprNode& node) override;
    void Visit(otava::ast::UnaryExprNode& node) override;
private:
    void BindBinaryOp(otava::ast::NodeKind op, const soul::ast::SourcePos& sourcePos, BoundExpressionNode* left, BoundExpressionNode* right);
    void BindUnaryOp(otava::ast::NodeKind op, const soul::ast::SourcePos& sourcePos, BoundExpressionNode* operand);
    void BindArrow(const soul::ast::SourcePos& sourcePos, BoundExpressionNode* operand);
    void BindDeref(const soul::ast::SourcePos& sourcePos, BoundExpressionNode* operand);
    void BindAddrOf(const soul::ast::SourcePos& sourcePos, BoundExpressionNode* operand);
    void BindPrefixInc(const soul::ast::SourcePos& sourcePos, BoundExpressionNode* operand);
    void BindPrefixDec(const soul::ast::SourcePos& sourcePos, BoundExpressionNode* operand);
    Context *context;
    BoundExpressionNode* boundExpression;
    Scope* scope;
    SymbolGroupKind symbolGroups;
};

ExpressionBinder::ExpressionBinder(Context* context_, SymbolGroupKind symbolGroups_) :
    context(context_), 
    boundExpression(nullptr), 
    scope(context->GetSymbolTable()->CurrentScope()),
    symbolGroups(symbolGroups_)
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
        args[0].reset(new BoundAddressOfNode(args[0].release(), sourcePos));
        functionCall = ResolveOverload(scope, groupName, args, sourcePos, context, ex);
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
        args[0].reset(new BoundAddressOfNode(args[0].release(), sourcePos));
        functionCall = ResolveOverload(scope, groupName, args, sourcePos, context, ex);
    }
    if (!functionCall)
    {
        ThrowException(ex);
    }
    boundExpression = functionCall.release();
}

void ExpressionBinder::BindArrow(const soul::ast::SourcePos& sourcePos, BoundExpressionNode* operand)
{
    // todo
}

void ExpressionBinder::BindDeref(const soul::ast::SourcePos& sourcePos, BoundExpressionNode* operand)
{
    // todo
}

void ExpressionBinder::BindAddrOf(const soul::ast::SourcePos& sourcePos, BoundExpressionNode* operand)
{
    // todo
}

void ExpressionBinder::BindPrefixInc(const soul::ast::SourcePos& sourcePos, BoundExpressionNode* operand)
{
    // todo
}

void ExpressionBinder::BindPrefixDec(const soul::ast::SourcePos& sourcePos, BoundExpressionNode* operand)
{
    // todo
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
    boundExpression = new BoundLiteralNode(Evaluate(&node, context), node.GetSourcePos());
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

void ExpressionBinder::Visit(otava::ast::IdentifierNode& node)
{
    Symbol* symbol = scope->Lookup(node.Str(), symbolGroups, ScopeLookup::allScopes, node.GetSourcePos(), context, LookupFlags::dontResolveSingle);
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
                boundExpression = new BoundParameterNode(parameter, node.GetSourcePos());
                break;
            }
            case SymbolKind::functionGroupSymbol:
            {
                FunctionGroupSymbol* functionGroupSymbol = static_cast<FunctionGroupSymbol*>(symbol);
                boundExpression = new BoundFunctionGroupNode(functionGroupSymbol, node.GetSourcePos());
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
    node.Right()->Accept(*this);
}

void ExpressionBinder::Visit(otava::ast::TemplateIdNode& node)
{
    context->GetSymbolTable()->BeginScope(scope);
    TypeSymbol* type = ResolveType(&node, DeclarationFlags::none, context);
    boundExpression = new BoundTypeNode(type, node.GetSourcePos());
    context->GetSymbolTable()->EndScope();
}

void ExpressionBinder::Visit(otava::ast::MemberExprNode& node)
{
    std::unique_ptr<BoundExpressionNode> subject(BindExpression(node.Child(), context));
    Scope* memberScope = subject->GetMemberScope(node.Op(), node.GetSourcePos(), context);
    if (memberScope)
    {
        scope = memberScope;
    }
    node.Id()->Accept(*this);
    std::unique_ptr<BoundExpressionNode> member(boundExpression);
    if (subject->IsBoundLocalVariable() && member->IsBoundMemberVariable())
    {
        BoundVariableNode* localVar = static_cast<BoundVariableNode*>(subject.release());
        BoundVariableNode* memberVar = static_cast<BoundVariableNode*>(member.release());
        memberVar->SetThisPtr(new BoundAddressOfNode(localVar, node.GetSourcePos()));
        boundExpression = memberVar;
    }
    else
    {
        boundExpression = new BoundMemberExprNode(subject.release(), member.release(), node.GetSourcePos());
    }
}

void ExpressionBinder::Visit(otava::ast::InvokeExprNode& node)
{
    Scope* subjectScope = scope;
    std::unique_ptr<BoundExpressionNode> subject(BindExpression(node.Subject(), context, SymbolGroupKind::functionSymbolGroup | SymbolGroupKind::typeSymbolGroup, subjectScope));
    if (subject)
    {
        std::vector<std::unique_ptr<BoundExpressionNode>> args;
        int n = node.Items().size();
        for (int i = 0; i < n; ++i)
        {
            otava::ast::Node* item = node.Items()[i];
            std::unique_ptr<BoundExpressionNode> arg(BindExpression(item, context));
            args.push_back(std::move(arg));
        }
        std::u32string groupName = GetGroupName(subject.get());
        std::unique_ptr<BoundFunctionCallNode> functionCall = ResolveOverloadThrow(subjectScope, groupName, args, node.GetSourcePos(), context);
        boundExpression = functionCall.release();
    }
    else
    {
        boundExpression = new BoundErrorNode(node.GetSourcePos());
    }
}

void ExpressionBinder::Visit(otava::ast::BinaryExprNode& node)
{
    std::unique_ptr<BoundExpressionNode> left(BindExpression(node.Left(), context));
    std::unique_ptr<BoundExpressionNode> right(BindExpression(node.Right(), context));
    otava::ast::NodeKind op = node.Op()->Kind();
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
        case otava::ast::NodeKind::arrowNode:
        {
            BindArrow(node.GetSourcePos(), child.release());
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
            BindPrefixInc(node.GetSourcePos(), child.release());
            break;
        }
        case otava::ast::NodeKind::prefixDecNode:
        {
            BindPrefixDec(node.GetSourcePos(), child.release());
            break;
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
    Scope* scope = nullptr;
    return BindExpression(node, context, SymbolGroupKind::all, scope);
}

void InitExpressionBinder()
{
    OperatorGroupNameMap::Instance().Init();
}

} // namespace otava::symbols

