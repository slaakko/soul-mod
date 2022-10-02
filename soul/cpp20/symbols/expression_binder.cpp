// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.symbols.expression.binder;

import soul.cpp20.symbols.alias.group.symbol;
import soul.cpp20.symbols.alias.type.symbol;
import soul.cpp20.symbols.bound.tree;
import soul.cpp20.symbols.class_group.symbol;
import soul.cpp20.symbols.classes;
import soul.cpp20.symbols.context;
import soul.cpp20.symbols.declaration;
import soul.cpp20.symbols.enums;
import soul.cpp20.symbols.evaluator;
import soul.cpp20.symbols.exception;
import soul.cpp20.symbols.function.symbol;
import soul.cpp20.symbols.function.group.symbol;
import soul.cpp20.symbols.overload.resolution;
import soul.cpp20.symbols.scope;
import soul.cpp20.symbols.scope.resolver;
import soul.cpp20.symbols.symbol.table;
import soul.cpp20.symbols.type.resolver;
import soul.cpp20.symbols.variable.group.symbol;
import soul.cpp20.symbols.variable.symbol;
import soul.cpp20.ast.identifier;
import soul.cpp20.ast.expression;
import soul.cpp20.ast.literal;
import soul.cpp20.ast.visitor;
import soul.cpp20.ast.templates;
import util.unicode;

namespace soul::cpp20::symbols {

class ExpressionBinder : public soul::cpp20::ast::DefaultVisitor
{
public:    
    ExpressionBinder(Context* context_, SymbolGroupKind symbolGroups_);
    BoundExpressionNode* GetBoundExpression() const { return boundExpression; }
    Scope* GetScope() const { return scope; }
    void Visit(soul::cpp20::ast::IntegerLiteralNode& node) override;
    void Visit(soul::cpp20::ast::FloatingLiteralNode& node) override;
    void Visit(soul::cpp20::ast::CharacterLiteralNode& node) override;
    void Visit(soul::cpp20::ast::StringLiteralNode& node) override;
    void Visit(soul::cpp20::ast::RawStringLiteralNode& node) override;
    void Visit(soul::cpp20::ast::BooleanLiteralNode& node) override;
    void Visit(soul::cpp20::ast::NullPtrLiteralNode& node) override;
    void Visit(soul::cpp20::ast::IdentifierNode& node) override;
    void Visit(soul::cpp20::ast::QualifiedIdNode& node) override;
    void Visit(soul::cpp20::ast::TemplateIdNode& node) override;
    void Visit(soul::cpp20::ast::MemberExprNode& node) override;
    void Visit(soul::cpp20::ast::InvokeExprNode& node) override;
    void Visit(soul::cpp20::ast::BinaryExprNode& node) override;
    void Visit(soul::cpp20::ast::UnaryExprNode& node) override;
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

void ExpressionBinder::Visit(soul::cpp20::ast::IntegerLiteralNode& node) 
{
    boundExpression = new BoundLiteralNode(Evaluate(&node, context));
}

void ExpressionBinder::Visit(soul::cpp20::ast::FloatingLiteralNode& node)
{
    boundExpression = new BoundLiteralNode(Evaluate(&node, context));
}

void ExpressionBinder::Visit(soul::cpp20::ast::CharacterLiteralNode& node)
{
    boundExpression = new BoundLiteralNode(Evaluate(&node, context));
}

void ExpressionBinder::Visit(soul::cpp20::ast::StringLiteralNode& node)
{
    boundExpression = new BoundLiteralNode(Evaluate(&node, context));
}

void ExpressionBinder::Visit(soul::cpp20::ast::RawStringLiteralNode& node)
{
    boundExpression = new BoundLiteralNode(Evaluate(&node, context));
}

void ExpressionBinder::Visit(soul::cpp20::ast::BooleanLiteralNode& node)
{
    boundExpression = new BoundLiteralNode(Evaluate(&node, context));
}

void ExpressionBinder::Visit(soul::cpp20::ast::NullPtrLiteralNode& node)
{
    boundExpression = new BoundLiteralNode(Evaluate(&node, context));
}

void ExpressionBinder::Visit(soul::cpp20::ast::IdentifierNode& node)
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

void ExpressionBinder::Visit(soul::cpp20::ast::QualifiedIdNode& node)
{
    scope = ResolveScope(node.Left(), context);
    node.Right()->Accept(*this);
}

void ExpressionBinder::Visit(soul::cpp20::ast::TemplateIdNode& node)
{
    context->GetSymbolTable()->BeginScope(scope);
    TypeSymbol* type = ResolveType(&node, DeclarationFlags::none, context);
    boundExpression = new BoundTypeNode(type);
    context->GetSymbolTable()->EndScope();
}

void ExpressionBinder::Visit(soul::cpp20::ast::MemberExprNode& node)
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

void ExpressionBinder::Visit(soul::cpp20::ast::InvokeExprNode& node)
{
    Scope* subjectScope = scope;
    std::u32string groupName = U"operator+";
    std::unique_ptr<BoundExpressionNode> subject(BindExpression(node.Subject(), context, SymbolGroupKind::functionSymbolGroup | SymbolGroupKind::typeSymbolGroup, subjectScope));
    if (subject)
    {
        std::vector<std::unique_ptr<BoundExpressionNode>> args;
        int n = node.Items().size();
        for (int i = 0; i < n; ++i)
        {
            soul::cpp20::ast::Node* item = node.Items()[i];
            std::unique_ptr<BoundExpressionNode> arg(BindExpression(item, context));
            args.push_back(std::move(arg));
        }
        std::unique_ptr<BoundFunctionCallNode> functionCall = ResolveOverload(subjectScope, groupName, args, node.GetSourcePos(), context);
        boundExpression = functionCall.release();
    }
    else
    {
        boundExpression = new BoundErrorNode();
    }
}

void ExpressionBinder::Visit(soul::cpp20::ast::BinaryExprNode& node)
{
    std::unique_ptr<BoundExpressionNode> left(BindExpression(node.Left(), context));
    std::unique_ptr<BoundExpressionNode> right(BindExpression(node.Right(), context));
    boundExpression = new BoundBinaryExprNode(left.release(), right.release(), node.Op()->Kind());
}

void ExpressionBinder::Visit(soul::cpp20::ast::UnaryExprNode& node)
{
    std::unique_ptr<BoundExpressionNode> child(BindExpression(node.Child(), context));
    boundExpression = new BoundUnaryExprNode(child.release(), node.Op()->Kind());
}

BoundExpressionNode* BindExpression(soul::cpp20::ast::Node* node, Context* context, SymbolGroupKind symbolGroups, Scope*& scope)
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

BoundExpressionNode* BindExpression(soul::cpp20::ast::Node* node, Context* context)
{
    Scope* scope = nullptr;
    return BindExpression(node, context, SymbolGroupKind::all, scope);
}

} // namespace soul::cpp20::symbols
