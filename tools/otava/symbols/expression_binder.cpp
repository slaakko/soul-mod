// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.expression.binder;

import otava.symbols.alias.group.symbol;
import otava.symbols.alias.type.symbol;
import otava.symbols.bound.tree;
import otava.symbols.class_group.symbol;
import otava.symbols.classes;
import otava.symbols.context;
import otava.symbols.declaration;
import otava.symbols.enums;
import otava.symbols.evaluator;
import otava.symbols.exception;
import otava.symbols.function.symbol;
import otava.symbols.function.group.symbol;
import otava.symbols.overload.resolution;
import otava.symbols.scope;
import otava.symbols.scope.resolver;
import otava.symbols.symbol.table;
import otava.symbols.type.resolver;
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

void ExpressionBinder::Visit(otava::ast::IntegerLiteralNode& node) 
{
    boundExpression = new BoundLiteralNode(Evaluate(&node, context));
}

void ExpressionBinder::Visit(otava::ast::FloatingLiteralNode& node)
{
    boundExpression = new BoundLiteralNode(Evaluate(&node, context));
}

void ExpressionBinder::Visit(otava::ast::CharacterLiteralNode& node)
{
    boundExpression = new BoundLiteralNode(Evaluate(&node, context));
}

void ExpressionBinder::Visit(otava::ast::StringLiteralNode& node)
{
    boundExpression = new BoundLiteralNode(Evaluate(&node, context));
}

void ExpressionBinder::Visit(otava::ast::RawStringLiteralNode& node)
{
    boundExpression = new BoundLiteralNode(Evaluate(&node, context));
}

void ExpressionBinder::Visit(otava::ast::BooleanLiteralNode& node)
{
    boundExpression = new BoundLiteralNode(Evaluate(&node, context));
}

void ExpressionBinder::Visit(otava::ast::NullPtrLiteralNode& node)
{
    boundExpression = new BoundLiteralNode(Evaluate(&node, context));
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
                    boundExpression = new BoundVariableNode(variable);
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
                    boundExpression = new BoundTypeNode(cls);
                }
                break;
            }
            case SymbolKind::templateParameterSymbol:
            {
                TypeSymbol* type = static_cast<TypeSymbol*>(symbol);
                boundExpression = new BoundTypeNode(type);
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
                    boundExpression = new BoundTypeNode(referredType);
                }
                break;
            }
            case SymbolKind::enumTypeSymbol:
            {
                EnumeratedTypeSymbol* enm = static_cast<EnumeratedTypeSymbol*>(symbol);
                boundExpression = new BoundTypeNode(enm);
                break;
            }
            case SymbolKind::enumConstantSymbol:
            {
                EnumConstantSymbol* enumConstant = static_cast<EnumConstantSymbol*>(symbol);
                boundExpression = new BoundEnumConstant(enumConstant);
                break;
            }
            case SymbolKind::parameterSymbol:
            {
                ParameterSymbol* parameter = static_cast<ParameterSymbol*>(symbol);
                boundExpression = new BoundParameterNode(parameter);
                break;
            }
            case SymbolKind::functionGroupSymbol:
            {
                FunctionGroupSymbol* functionGroupSymbol = static_cast<FunctionGroupSymbol*>(symbol);
                boundExpression = new BoundFunctionGroupNode(functionGroupSymbol);
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
    boundExpression = new BoundTypeNode(type);
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
    boundExpression = new BoundMemberExprNode(subject.release(), boundExpression);
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
        std::u32string groupName = U"not implemented";
        std::unique_ptr<BoundFunctionCallNode> functionCall = ResolveOverload(subjectScope, groupName, args, node.GetSourcePos(), context);
        boundExpression = functionCall.release();
    }
    else
    {
        boundExpression = new BoundErrorNode();
    }
}

void ExpressionBinder::Visit(otava::ast::BinaryExprNode& node)
{
    std::unique_ptr<BoundExpressionNode> left(BindExpression(node.Left(), context));
    std::unique_ptr<BoundExpressionNode> right(BindExpression(node.Right(), context));
    std::u32string groupName = OperatorGroupNameMap::Instance().GetGroupName(node.Op()->Kind(), node.GetSourcePos(), context);
    std::vector<std::unique_ptr<BoundExpressionNode>> args;
    args.push_back(std::unique_ptr<BoundExpressionNode>(left.release()));
    args.push_back(std::unique_ptr<BoundExpressionNode>(right.release()));
    std::unique_ptr<BoundFunctionCallNode> functionCall = ResolveOverload(scope, groupName, args, node.GetSourcePos(), context);
    boundExpression = functionCall.release();
}

void ExpressionBinder::Visit(otava::ast::UnaryExprNode& node)
{
    std::unique_ptr<BoundExpressionNode> child(BindExpression(node.Child(), context));
}

BoundExpressionNode* BindExpression(otava::ast::Node* node, Context* context, SymbolGroupKind symbolGroups, Scope*& scope)
{
    if (node->GetSourcePos().file == 41 && node->GetSourcePos().line == 61)
    {
        int x = 0;
    }
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
