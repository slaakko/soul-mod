// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.symbols.evaluator;

import soul.cpp20.ast.literal;
import soul.cpp20.ast.identifier;
import soul.cpp20.ast.visitor;
import soul.cpp20.ast.expression;
import soul.cpp20.symbols.context;
import soul.cpp20.symbols.scope.resolver;
import soul.cpp20.symbols.symbol.table;
import soul.cpp20.symbols.value;

namespace soul::cpp20::symbols {

class Evaluator : public soul::cpp20::ast::DefaultVisitor
{
public:
    Evaluator(Context* context_);
    Value* GetValue() { return value; }
    void Visit(soul::cpp20::ast::IntegerLiteralNode& node) override;
    void Visit(soul::cpp20::ast::FloatingLiteralNode& node) override;
    void Visit(soul::cpp20::ast::CharacterLiteralNode& node) override;
    void Visit(soul::cpp20::ast::StringLiteralNode& node) override;
    void Visit(soul::cpp20::ast::BooleanLiteralNode& node) override;
    void Visit(soul::cpp20::ast::NullPtrLiteralNode& node) override;
    void Visit(soul::cpp20::ast::QualifiedIdNode& node) override;
    void Visit(soul::cpp20::ast::IdentifierNode& node) override;
    void Visit(soul::cpp20::ast::AssignmentInitNode& node) override;
    void Visit(soul::cpp20::ast::UnaryExprNode& node) override;
    void Visit(soul::cpp20::ast::BinaryExprNode& node) override;
    void Visit(soul::cpp20::ast::InvokeExprNode& node) override;
private:
    Context* context;
    Value* value;
    Scope* scope;
};

Evaluator::Evaluator(Context* context_) : context(context_), value(nullptr), scope(context->GetSymbolTable()->CurrentScope())
{
}

void Evaluator::Visit(soul::cpp20::ast::IntegerLiteralNode& node)
{
    value = context->GetEvaluationContext()->GetIntegerValue(node.Value(), node.Rep());
}

void Evaluator::Visit(soul::cpp20::ast::FloatingLiteralNode& node)
{
    value = context->GetEvaluationContext()->GetFloatingValue(node.Value(), node.Rep());
}

void Evaluator::Visit(soul::cpp20::ast::CharacterLiteralNode& node)
{
    // todo
}

void Evaluator::Visit(soul::cpp20::ast::StringLiteralNode& node)
{
    // todo
}

void Evaluator::Visit(soul::cpp20::ast::BooleanLiteralNode& node)
{
    value = context->GetEvaluationContext()->GetBoolValue(node.Value());
}

void Evaluator::Visit(soul::cpp20::ast::NullPtrLiteralNode& node)
{
    value = context->GetEvaluationContext()->GetNullPtrValue();
}

void Evaluator::Visit(soul::cpp20::ast::QualifiedIdNode& node)
{
    scope = ResolveScope(node.Left(), context);
    node.Right()->Accept(*this);
}

void Evaluator::Visit(soul::cpp20::ast::IdentifierNode& node)
{
    Symbol* symbol = scope->Lookup(node.Str(), SymbolGroupKind::variableSymbolGroup | SymbolGroupKind::typeSymbolGroup, ScopeLookup::allScopes, node.GetSourcePos(), context, LookupFlags::none);
    if (symbol)
    {
        value = context->GetEvaluationContext()->GetSymbolValue(symbol);
    }
    else
    {
        throw std::runtime_error("symbol not found");
    }
}

void Evaluator::Visit(soul::cpp20::ast::AssignmentInitNode& node)
{
    node.Child()->Accept(*this);
}

void Evaluator::Visit(soul::cpp20::ast::UnaryExprNode& node)
{
    value = Evaluate(node.Child(), context);
    switch (node.Op()->Kind())
    {
        case soul::cpp20::ast::NodeKind::plusNode:
        {
            if (value->IsIntegerValue())
            {
                IntegerValue* integerValue = static_cast<IntegerValue*>(value);
                value = context->GetEvaluationContext()->GetIntegerValue(integerValue->GetValue(), U"+" + value->Rep());
            }
            else if (value->IsFloatingValue())
            {
                FloatingValue* floatingValue = static_cast<FloatingValue*>(value);
                value = context->GetEvaluationContext()->GetFloatingValue(floatingValue->GetValue(), U"+" + value->Rep());
            }
            break;
        }
        case soul::cpp20::ast::NodeKind::minusNode:
        {
            if (value->IsIntegerValue())
            {
                IntegerValue* integerValue = static_cast<IntegerValue*>(value);
                value = context->GetEvaluationContext()->GetIntegerValue(-integerValue->GetValue(), U"-" + value->Rep());
            }
            else if (value->IsFloatingValue())
            {
                FloatingValue* floatingValue = static_cast<FloatingValue*>(value);
                value = context->GetEvaluationContext()->GetFloatingValue(-floatingValue->GetValue(), U"-" + value->Rep());
            }
            break;
        }
        case soul::cpp20::ast::NodeKind::complementNode:
        {
            if (value->IsIntegerValue())
            {
                IntegerValue* integerValue = static_cast<IntegerValue*>(value);
                value = context->GetEvaluationContext()->GetIntegerValue(~integerValue->GetValue(), U"~" + value->Rep());
            }
        }
        case soul::cpp20::ast::NodeKind::notNode:
        {
            if (value->IsBoolValue())
            {
                BoolValue* boolValue = static_cast<BoolValue*>(value);
                value = context->GetEvaluationContext()->GetBoolValue(!boolValue->GetValue());
            }
            break;
        }
    }
}

void Evaluator::Visit(soul::cpp20::ast::BinaryExprNode& node)
{
    Value* left = Evaluate(node.Left(), context);
    Value* right = Evaluate(node.Right(), context);
    ValueKind commonKind = CommonValueKind(left->GetValueKind(), right->GetValueKind());
    EvaluationContext* evaluationContext = context->GetEvaluationContext();
    Value* leftConv = left->Convert(commonKind, *evaluationContext);
    Value* rightConv = right->Convert(commonKind, *evaluationContext);
    switch (commonKind)
    {
        case ValueKind::integerValue:
        {
            IntegerValue* leftInt = static_cast<IntegerValue*>(leftConv);
            IntegerValue* rightInt = static_cast<IntegerValue*>(rightConv);
            switch (node.Op()->Kind())
            {
                case soul::cpp20::ast::NodeKind::plusNode:
                {
                    value = evaluationContext->GetIntegerValue(leftInt->GetValue() + rightInt->GetValue(), left->Rep() + U" + " + right->Rep());
                    break;
                }
                case soul::cpp20::ast::NodeKind::minusNode:
                {
                    value = evaluationContext->GetIntegerValue(leftInt->GetValue() - rightInt->GetValue(), left->Rep() + U" - " + right->Rep());
                    break;
                }
                case soul::cpp20::ast::NodeKind::mulNode:
                {
                    value = evaluationContext->GetIntegerValue(leftInt->GetValue() * rightInt->GetValue(), left->Rep() + U" * " + right->Rep());
                    break;
                }
                case soul::cpp20::ast::NodeKind::divNode:
                {
                    value = evaluationContext->GetIntegerValue(leftInt->GetValue() / rightInt->GetValue(), left->Rep() + U" / " + right->Rep());
                    break;
                }
                case soul::cpp20::ast::NodeKind::modNode:
                {
                    value = evaluationContext->GetIntegerValue(leftInt->GetValue() % rightInt->GetValue(), left->Rep() + U" % " + right->Rep());
                    break;
                }
                case soul::cpp20::ast::NodeKind::shiftLeftNode:
                {
                    value = evaluationContext->GetIntegerValue(leftInt->GetValue() << rightInt->GetValue(), left->Rep() + U" << " + right->Rep());
                    break;
                }
                case soul::cpp20::ast::NodeKind::shiftRightNode:
                {
                    value = evaluationContext->GetIntegerValue(leftInt->GetValue() >> rightInt->GetValue(), left->Rep() + U" >> " + right->Rep());
                    break;
                }
                case soul::cpp20::ast::NodeKind::inclusiveOrNode:
                {
                    value = evaluationContext->GetIntegerValue(leftInt->GetValue() | rightInt->GetValue(), left->Rep() + U" | " + right->Rep());
                    break;
                }
                case soul::cpp20::ast::NodeKind::exclusiveOrNode:
                {
                    value = evaluationContext->GetIntegerValue(leftInt->GetValue() ^ rightInt->GetValue(), left->Rep() + U" ^ " + right->Rep());
                    break;
                }
                case soul::cpp20::ast::NodeKind::andNode:
                {
                    value = evaluationContext->GetIntegerValue(leftInt->GetValue() & rightInt->GetValue(), left->Rep() + U" & " + right->Rep());
                    break;
                }
                case soul::cpp20::ast::NodeKind::equalNode:
                {
                    value = evaluationContext->GetBoolValue(leftInt->GetValue() == rightInt->GetValue());
                    break;
                }
                case soul::cpp20::ast::NodeKind::notEqualNode:
                {
                    value = evaluationContext->GetBoolValue(leftInt->GetValue() != rightInt->GetValue());
                    break;
                }
                case soul::cpp20::ast::NodeKind::greaterNode:
                {
                    value = evaluationContext->GetBoolValue(leftInt->GetValue() > rightInt->GetValue());
                    break;
                }
                case soul::cpp20::ast::NodeKind::lessNode:
                {
                    value = evaluationContext->GetBoolValue(leftInt->GetValue() < rightInt->GetValue());
                    break;
                }
                case soul::cpp20::ast::NodeKind::greaterOrEqualNode:
                {
                    value = evaluationContext->GetBoolValue(leftInt->GetValue() >= rightInt->GetValue());
                    break;
                }
                case soul::cpp20::ast::NodeKind::lessOrEqualNode:
                {
                    value = evaluationContext->GetBoolValue(leftInt->GetValue() <= rightInt->GetValue());
                    break;
                }
            }
            break;
        }
        case ValueKind::floatingValue:
        {
            FloatingValue* leftFloat = static_cast<FloatingValue*>(leftConv);
            FloatingValue* rightFloat = static_cast<FloatingValue*>(rightConv);
            switch (node.Op()->Kind())
            {
                case soul::cpp20::ast::NodeKind::plusNode:
                {
                    value = evaluationContext->GetFloatingValue(leftFloat->GetValue() + rightFloat->GetValue(), left->Rep() + U" + " + right->Rep());
                    break;
                }
                case soul::cpp20::ast::NodeKind::minusNode:
                {
                    value = evaluationContext->GetFloatingValue(leftFloat->GetValue() - rightFloat->GetValue(), left->Rep() + U" - " + right->Rep());
                    break;
                }
                case soul::cpp20::ast::NodeKind::mulNode:
                {
                    value = evaluationContext->GetFloatingValue(leftFloat->GetValue() * rightFloat->GetValue(), left->Rep() + U" * " + right->Rep());
                    break;
                }
                case soul::cpp20::ast::NodeKind::divNode:
                {
                    value = evaluationContext->GetFloatingValue(leftFloat->GetValue() / rightFloat->GetValue(), left->Rep() + U" / " + right->Rep());
                    break;
                }
                case soul::cpp20::ast::NodeKind::equalNode:
                {
                    value = evaluationContext->GetBoolValue(leftFloat->GetValue() == rightFloat->GetValue());
                    break;
                }
                case soul::cpp20::ast::NodeKind::notEqualNode:
                {
                    value = evaluationContext->GetBoolValue(leftFloat->GetValue() != rightFloat->GetValue());
                    break;
                }
                case soul::cpp20::ast::NodeKind::greaterNode:
                {
                    value = evaluationContext->GetBoolValue(leftFloat->GetValue() > rightFloat->GetValue());
                    break;
                }
                case soul::cpp20::ast::NodeKind::lessNode:
                {
                    value = evaluationContext->GetBoolValue(leftFloat->GetValue() < rightFloat->GetValue());
                    break;
                }
                case soul::cpp20::ast::NodeKind::greaterOrEqualNode:
                {
                    value = evaluationContext->GetBoolValue(leftFloat->GetValue() >= rightFloat->GetValue());
                    break;
                }
                case soul::cpp20::ast::NodeKind::lessOrEqualNode:
                {
                    value = evaluationContext->GetBoolValue(leftFloat->GetValue() <= rightFloat->GetValue());
                    break;
                }
            }
            break;
        }
        case ValueKind::boolValue:
        {
            BoolValue* leftBool = static_cast<BoolValue*>(leftConv);
            BoolValue* rightBool = static_cast<BoolValue*>(rightConv);
            switch (node.Op()->Kind())
            {
                case soul::cpp20::ast::NodeKind::disjunctionNode:
                {
                    value = evaluationContext->GetBoolValue(leftBool->GetValue() || rightBool->GetValue());
                    break;
                }
                case soul::cpp20::ast::NodeKind::conjunctionNode:
                {
                    value = evaluationContext->GetBoolValue(leftBool->GetValue() && rightBool->GetValue());
                    break;
                }
                case soul::cpp20::ast::NodeKind::equalNode:
                {
                    value = evaluationContext->GetBoolValue(leftBool->GetValue() == rightBool->GetValue());
                    break;
                }
                case soul::cpp20::ast::NodeKind::notEqualNode:
                {
                    value = evaluationContext->GetBoolValue(leftBool->GetValue() != rightBool->GetValue());
                    break;
                }
            }
            break;
        }
        default:
        {
            throw std::runtime_error("soul.cpp20.symbols.evaluator: invalid binary operation");
        }
    }
}

void Evaluator::Visit(soul::cpp20::ast::InvokeExprNode& node)
{
    value = Evaluate(node.Subject(), context);
    EvaluationContext* evaluationContext = context->GetEvaluationContext();
    value = evaluationContext->GetInvokeValue(value);
}

Value* Evaluate(soul::cpp20::ast::Node* node, Context* context)
{
    Evaluator evaluator(context);
    node->Accept(evaluator);
    return evaluator.GetValue();
}

} // namespace soul::cpp20::symbols
