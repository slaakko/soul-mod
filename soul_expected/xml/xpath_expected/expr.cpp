// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul_expected.xml.xpath.expr;

import util_expected;
import soul_expected.xml.xpath.function;
import soul_expected.xml.node.operation;
import soul_expected.xml.dom_expected;

namespace soul_expected::xml::xpath::expr {

std::string OperatorStr(Operator op)
{
    switch (op)
    {
    case Operator::or_: return "or";
    case Operator::and_: return "and";
    case Operator::equal: return "equal";
    case Operator::notEqual: return "not-equal";
    case Operator::less: return "less";
    case Operator::greater: return "greater";
    case Operator::lessOrEqual: return "less-or-equal";
    case Operator::greaterOrEqual: return "greater-or-equal";
    case Operator::plus: return "plus";
    case Operator::minus: return "minus";
    case Operator::mul: return "mul";
    case Operator::div: return "div";
    case Operator::mod: return "mod";
    case Operator::union_: return "union";
    case Operator::slash: return "slash";
    case Operator::slashSlash: return "slash-slash";
    case Operator::parens: return "parens";
    }
    return "<unknown operator>";
}

std::string ExprKindStr(ExprKind exprKind)
{
    switch (exprKind)
    {
    case ExprKind::unaryExpr:  return "unary-expr";
    case ExprKind::binaryExpr:  return "binary-expr";
    case ExprKind::root:  return "root";
    case ExprKind::filterExpr:  return "filter";
    case ExprKind::locationStepExpr:  return "location-step";
    case ExprKind::variableReference:  return "variable-reference";
    case ExprKind::literal:  return "literal";
    case ExprKind::numberExpr:  return "number";
    case ExprKind::functionCall:  return "function-call";
    }
    return "<unknown expression>";
}

class NodeSelectionOperation : public soul_expected::xml::NodeOperation
{
public:
    NodeSelectionOperation(NodeTest* nodeTest_, NodeSet& nodeSet_, soul_expected::xml::Axis axis_);
    void Apply(soul_expected::xml::Node* node) override;
private:
    NodeTest* nodeTest;
    NodeSet& nodeSet;
    soul_expected::xml::Axis axis;
};

NodeSelectionOperation::NodeSelectionOperation(NodeTest* nodeTest_, NodeSet& nodeSet_, soul_expected::xml::Axis axis_) : nodeTest(nodeTest_), nodeSet(nodeSet_), axis(axis_)
{
}

void NodeSelectionOperation::Apply(soul_expected::xml::Node* node)
{
    if (nodeTest->Select(node, axis))
    {
        nodeSet.Add(node);
    }
}

std::expected<NodeSet*, int> NodeSetCast(Object* object)
{
    if (object->IsNodeSet())
    {
        return static_cast<NodeSet*>(object);
    }
    else
    {
        return std::unexpected<int>(util::AllocateError("node-set object expected"));
    }
}

std::expected<Boolean*, int> BooleanCast(Object* object)
{
    if (object->IsBoolean())
    {
        return static_cast<Boolean*>(object);
    }
    else
    {
        return std::unexpected<int>(util::AllocateError("Boolean object expected"));
    }
}

std::expected<Number*, int> NumberCast(Object* object)
{
    if (object->IsNumber())
    {
        return static_cast<Number*>(object);
    }
    else
    {
        return std::unexpected<int>(util::AllocateError("number object expected"));
    }
}

bool Compare(const std::string& leftStr, const std::string& rightStr, Operator op)
{
    switch (op)
    {
    case Operator::equal:
    {
        return leftStr == rightStr;
    }
    case Operator::notEqual:
    {
        return leftStr != rightStr;
    }
    case Operator::less:
    {
        return leftStr < rightStr;
    }
    case Operator::greater:
    {
        return leftStr > rightStr;
    }
    case Operator::lessOrEqual:
    {
        return leftStr <= rightStr;
    }
    case Operator::greaterOrEqual:
    {
        return leftStr >= rightStr;
    }
    }
    return false;
}

bool Compare(Number* left, Number* right, Operator op)
{
    switch (op)
    {
    case Operator::equal:
    {
        return left->Value() == right->Value();
    }
    case Operator::notEqual:
    {
        return left->Value() != right->Value();
    }
    case Operator::less:
    {
        return left->Value() < right->Value();
    }
    case Operator::greater:
    {
        return left->Value() > right->Value();
    }
    case Operator::lessOrEqual:
    {
        return left->Value() <= right->Value();
    }
    case Operator::greaterOrEqual:
    {
        return left->Value() >= right->Value();
    }
    }
    return false;
}

bool Compare(Boolean* left, Boolean* right, Operator op)
{
    switch (op)
    {
    case Operator::equal:
    {
        return left->Value() == right->Value();
    }
    case Operator::notEqual:
    {
        return left->Value() != right->Value();
    }
    case Operator::less:
    {
        return static_cast<int>(left->Value()) < static_cast<int>(right->Value());
    }
    case Operator::greater:
    {
        return static_cast<int>(left->Value()) > static_cast<int>(right->Value());
    }
    case Operator::lessOrEqual:
    {
        return static_cast<int>(left->Value()) <= static_cast<int>(right->Value());
    }
    case Operator::greaterOrEqual:
    {
        return static_cast<int>(left->Value()) >= static_cast<int>(right->Value());
    }
    }
    return false;
}

std::expected<std::unique_ptr<soul_expected::xml::xpath::Object>, int> ToNumber(soul_expected::xml::xpath::Object* object, Context& context)
{
    auto f = GetFunction(FunctionKind::number);
    if (!f) return std::unexpected<int>(f.error());
    Function* numberFunction = *f;
    std::vector<Object*> args(1, object);
    return numberFunction->Evaluate(context, args);
}

std::expected<std::unique_ptr<soul_expected::xml::xpath::Object>, int> ToNumber(soul_expected::xml::Node* node, Context& context)
{
    std::unique_ptr<Object> stringValue(new String(StringValue(node)));
    return ToNumber(stringValue.get(), context);
}

std::expected<std::unique_ptr<soul_expected::xml::xpath::Object>, int> ToBoolean(soul_expected::xml::xpath::Object* object, Context& context)
{
    auto f = GetFunction(FunctionKind::boolean);
    if (!f) return std::unexpected<int>(f.error());
    Function* booleanFunction = *f;
    std::vector<Object*> args(1, object);
    return booleanFunction->Evaluate(context, args);
}

std::expected<std::unique_ptr<soul_expected::xml::xpath::Object>, int> EvaluateUnaryMinusExpr(Expr* operand, Context& context)
{
    auto r = operand->Evaluate(context);
    if (!r) return std::unexpected<int>(r.error());
    std::unique_ptr<Object> operandResult = std::move(*r);
    auto n = ToNumber(operandResult.get(), context);
    if (!n) return std::unexpected<int>(n.error());
    std::unique_ptr<Object> numberResult = std::move(*n);
    auto c = NumberCast(numberResult.get());
    if (!c) return std::unexpected<int>(c.error());
    Number* number = std::move(*c);
    return std::unique_ptr<Object>(new Number(-number->Value()));
}

std::expected<std::unique_ptr<soul_expected::xml::xpath::Object>, int> EvaluateParenExpr(Expr* operand, Context& context)
{
    return operand->Evaluate(context);
}

std::expected<std::unique_ptr<soul_expected::xml::xpath::Object>, int> EvaluateOrExpr(Expr* left, Expr* right, Context& context)
{
    auto f = GetFunction(FunctionKind::boolean);
    if (!f) return std::unexpected<int>(f.error());
    Function* booleanFunction = *f;
    auto l = left->Evaluate(context);
    if (!l) return std::unexpected<int>(l.error());
    std::unique_ptr<soul_expected::xml::xpath::Object> leftResult = std::move(*l);
    std::vector<Object*> leftArgs(1, leftResult.get());
    auto b = booleanFunction->Evaluate(context, leftArgs);
    if (!b) return std::unexpected<int>(b.error());
    std::unique_ptr<soul_expected::xml::xpath::Object> leftBooleanResult = std::move(*b);
    auto c = BooleanCast(leftBooleanResult.get());
    if (!c) return std::unexpected<int>(c.error());
    Boolean* leftAsBoolean = *c;
    if (leftAsBoolean->Value())
    {
        return leftBooleanResult;
    }
    auto r = right->Evaluate(context);
    if (!r) return std::unexpected<int>(r.error());
    std::unique_ptr<soul_expected::xml::xpath::Object> rightResult = std::move(*r);
    std::vector<Object*> rightArgs(1, rightResult.get());
    return booleanFunction->Evaluate(context, rightArgs);
}

std::expected<std::unique_ptr<soul_expected::xml::xpath::Object>, int> EvaluateAndExpr(Expr* left, Expr* right, Context& context)
{
    auto f = GetFunction(FunctionKind::boolean);
    if (!f) return std::unexpected<int>(f.error());
    Function* booleanFunction = *f;
    auto l = left->Evaluate(context);
    if (!l) return std::unexpected<int>(l.error());
    std::unique_ptr<soul_expected::xml::xpath::Object> leftResult = std::move(*l);
    std::vector<Object*> leftArgs(1, leftResult.get());
    auto b = booleanFunction->Evaluate(context, leftArgs);
    if (!b) return std::unexpected<int>(b.error());
    std::unique_ptr<soul_expected::xml::xpath::Object> leftBooleanResult = std::move(*b);
    auto c = BooleanCast(leftBooleanResult.get());
    if (!c) return std::unexpected<int>(c.error());
    Boolean* leftAsBoolean = *c;
    if (!leftAsBoolean->Value())
    {
        return leftBooleanResult;
    }
    auto r = right->Evaluate(context);
    if (!r) return std::unexpected<int>(r.error());
    std::unique_ptr<soul_expected::xml::xpath::Object> rightResult = std::move(*r);
    std::vector<Object*> rightArgs(1, rightResult.get());
    return booleanFunction->Evaluate(context, rightArgs);
}

std::expected<std::unique_ptr<soul_expected::xml::xpath::Object>, int> Compare(NodeSet* left, NodeSet* right, Operator op)
{
    int n = left->Count();
    for (int i = 0; i < n; ++i)
    {
        auto n = left->GetNode(i);
        if (!n) return std::unexpected<int>(n.error());
        soul_expected::xml::Node* leftNode = *n;
        std::string leftStringValue = StringValue(leftNode);
        int m = right->Count();
        for (int j = 0; j < m; ++j)
        {
            n = right->GetNode(j);
            if (!n) return std::unexpected<int>(n.error());
            soul_expected::xml::Node* rightNode = *n;
            std::string rightStringValue = StringValue(rightNode);
            if (Compare(leftStringValue, rightStringValue, op))
            {
                return std::unique_ptr<soul_expected::xml::xpath::Object>(new Boolean(true));
            }
        }
    }
    return std::unique_ptr<soul_expected::xml::xpath::Object>(new Boolean(false));
}

std::expected<std::unique_ptr<soul_expected::xml::xpath::Object>, int> Compare(NodeSet* left, Boolean* right, Operator op, Context& context)
{
    auto b = ToBoolean(left, context);
    if (!b) return std::unexpected<int>(b.error());
    std::unique_ptr<soul_expected::xml::xpath::Object> leftAsBoolean = std::move(*b);
    auto c = BooleanCast(leftAsBoolean.get());
    if (!c) return std::unexpected<int>(c.error());
    Boolean* leftBoolean = *c;
    return std::unique_ptr<soul_expected::xml::xpath::Object>(new Boolean(Compare(leftBoolean, right, op)));
}

std::expected<std::unique_ptr<soul_expected::xml::xpath::Object>, int> Compare(Boolean* left, NodeSet* right, Operator op, Context& context)
{
    auto b = ToBoolean(right, context);
    if (!b) return std::unexpected<int>(b.error());
    std::unique_ptr<soul_expected::xml::xpath::Object> rightAsBoolean = std::move(*b);
    auto c = BooleanCast(rightAsBoolean.get());
    if (!c) return std::unexpected<int>(c.error());
    Boolean* rightBoolean = *c;
    return std::unique_ptr<soul_expected::xml::xpath::Object>(new Boolean(Compare(left, rightBoolean, op)));
}

std::expected<std::unique_ptr<soul_expected::xml::xpath::Object>, int> Compare(Boolean* left, Number* right, Operator op, Context& context)
{
    auto b = ToBoolean(right, context);
    if (!b) return std::unexpected<int>(b.error());
    std::unique_ptr<soul_expected::xml::xpath::Object> rightAsBoolean = std::move(*b);
    auto c = BooleanCast(rightAsBoolean.get());
    if (!c) return std::unexpected<int>(c.error());
    Boolean* rightBoolean = *c;
    return std::unique_ptr<soul_expected::xml::xpath::Object>(new Boolean(Compare(left, rightBoolean, op)));
}

std::expected<std::unique_ptr<soul_expected::xml::xpath::Object>, int> Compare(Number* left, Boolean* right, Operator op, Context& context)
{
    auto b = ToBoolean(left, context);
    if (!b) return std::unexpected<int>(b.error());
    std::unique_ptr<soul_expected::xml::xpath::Object> leftAsBoolean = std::move(*b);
    auto c = BooleanCast(leftAsBoolean.get());
    if (!c) return std::unexpected<int>(c.error());
    Boolean* leftBoolean = *c;
    return std::unique_ptr<soul_expected::xml::xpath::Object>(new Boolean(Compare(leftBoolean, right, op)));
}

std::expected<std::unique_ptr<soul_expected::xml::xpath::Object>, int> Compare(Boolean* left, String* right, Operator op, Context& context)
{
    auto b = ToBoolean(right, context);
    if (!b) return std::unexpected<int>(b.error());
    std::unique_ptr<soul_expected::xml::xpath::Object> rightAsBoolean = std::move(*b);
    auto c = BooleanCast(rightAsBoolean.get());
    if (!c) return std::unexpected<int>(c.error());
    Boolean* rightBoolean = *c;
    return std::unique_ptr<soul_expected::xml::xpath::Object>(new Boolean(Compare(left, rightBoolean, op)));
}

std::expected<std::unique_ptr<soul_expected::xml::xpath::Object>, int> Compare(String* left, Boolean* right, Operator op, Context& context)
{
    auto b = ToBoolean(left, context);
    if (!b) return std::unexpected<int>(b.error());
    std::unique_ptr<soul_expected::xml::xpath::Object> leftAsBoolean = std::move(*b);
    auto c = BooleanCast(leftAsBoolean.get());
    if (!c) return std::unexpected<int>(c.error());
    Boolean* leftBoolean = *c;
    return std::unique_ptr<soul_expected::xml::xpath::Object>(new Boolean(Compare(leftBoolean, right, op)));
}

std::expected<std::unique_ptr<soul_expected::xml::xpath::Object>, int> Compare(NodeSet* left, Number* right, Operator op, Context& context)
{
    int n = left->Count();
    for (int i = 0; i < n; ++i)
    {
        auto n = left->GetNode(i);
        if (!n) return std::unexpected<int>(n.error());
        soul_expected::xml::Node* leftNode = *n;
        auto num = ToNumber(leftNode, context);
        if (!num) return std::unexpected<int>(num.error());
        std::unique_ptr<soul_expected::xml::xpath::Object> leftAsNumber = std::move(*num);
        auto c = NumberCast(leftAsNumber.get());
        if (!c) return std::unexpected<int>(c.error());
        Number* leftNumber = *c;
        if (Compare(leftNumber, right, op))
        {
            return std::unique_ptr<soul_expected::xml::xpath::Object>(new Boolean(true));
        }
    }
    return std::unique_ptr<soul_expected::xml::xpath::Object>(new Boolean(false));
}

std::expected<std::unique_ptr<soul_expected::xml::xpath::Object>, int> Compare(Number* left, NodeSet* right, Operator op, Context& context)
{
    int n = right->Count();
    for (int i = 0; i < n; ++i)
    {
        auto n = right->GetNode(i);
        if (!n) return std::unexpected<int>(n.error());
        soul_expected::xml::Node* rightNode = *n;
        auto num = ToNumber(rightNode, context);
        if (!num) return std::unexpected<int>(num.error());
        std::unique_ptr<soul_expected::xml::xpath::Object> rightAsNumber = std::move(*num);
        auto c = NumberCast(rightAsNumber.get());
        if (!c) return std::unexpected<int>(c.error());
        Number* rightNumber = *c;
        if (Compare(left, rightNumber, op))
        {
            return std::unique_ptr<soul_expected::xml::xpath::Object>(new Boolean(true));
        }
    }
    return std::unique_ptr<soul_expected::xml::xpath::Object>(new Boolean(false));
}

std::expected<std::unique_ptr<soul_expected::xml::xpath::Object>, int> Compare(NodeSet* left, String* right, Operator op, Context& context)
{
    int n = left->Count();
    for (int i = 0; i < n; ++i)
    {
        auto n = left->GetNode(i);
        if (!n) return std::unexpected<int>(n.error());
        soul_expected::xml::Node* leftNode = *n;
        std::string leftStringValue = StringValue(leftNode);
        if (Compare(leftStringValue, right->Value(), op))
        {
            return std::unique_ptr<soul_expected::xml::xpath::Object>(new Boolean(true));
        }
    }
    return std::unique_ptr<soul_expected::xml::xpath::Object>(new Boolean(false));
}

std::expected<std::unique_ptr<soul_expected::xml::xpath::Object>, int> Compare(String* left, NodeSet* right, Operator op, Context& context)
{
    int n = right->Count();
    for (int i = 0; i < n; ++i)
    {
        auto n = right->GetNode(i);
        if (!n) return std::unexpected<int>(n.error());
        soul_expected::xml::Node* rightNode = *n;
        std::string rightStringValue = StringValue(rightNode);
        if (Compare(left->Value(), rightStringValue, op))
        {
            return std::unique_ptr<soul_expected::xml::xpath::Object>(new Boolean(true));
        }
    }
    return std::unique_ptr<soul_expected::xml::xpath::Object>(new Boolean(false));
}

std::expected<std::unique_ptr<soul_expected::xml::xpath::Object>, int> Compare(Number* left, String* right, Operator op, Context& context)
{
    auto n = ToNumber(right, context);
    if (!n) return std::unexpected<int>(n.error());
    std::unique_ptr<soul_expected::xml::xpath::Object> rightAsNumber = std::move(*n);
    auto c = NumberCast(rightAsNumber.get());
    if (!c) return std::unexpected<int>(c.error());
    Number* rightNumber = *c;
    return std::unique_ptr<soul_expected::xml::xpath::Object>(new Boolean(Compare(left, rightNumber, op)));
}

std::expected<std::unique_ptr<soul_expected::xml::xpath::Object>, int> Compare(String* left, Number* right, Operator op, Context& context)
{
    auto n = ToNumber(left, context);
    if (!n) return std::unexpected<int>(n.error());
    std::unique_ptr<soul_expected::xml::xpath::Object> leftAsNumber = std::move(*n);
    auto c = NumberCast(leftAsNumber.get());
    if (!c) return std::unexpected<int>(c.error());
    Number* leftNumber = *c;
    return std::unique_ptr<soul_expected::xml::xpath::Object>(new Boolean(Compare(leftNumber, right, op)));
}

std::expected<std::unique_ptr<soul_expected::xml::xpath::Object>, int> Compare(Expr* left, Expr* right, Operator op, Context& context)
{
    auto l = left->Evaluate(context);
    if (!l) return std::unexpected<int>(l.error());
    std::unique_ptr<soul_expected::xml::xpath::Object> leftOperand = std::move(*l);
    auto r = right->Evaluate(context);
    if (!r) return std::unexpected<int>(r.error());
    std::unique_ptr<soul_expected::xml::xpath::Object> rightOperand = std::move(*r);
    switch (leftOperand->Kind())
    {
    case ObjectKind::nodeSet:
    {
        NodeSet* leftNodeSet = static_cast<NodeSet*>(leftOperand.get());
        switch (rightOperand->Kind())
        {
        case ObjectKind::nodeSet:
        {
            NodeSet* rightNodeSet = static_cast<NodeSet*>(rightOperand.get());
            return Compare(leftNodeSet, rightNodeSet, op);
        }
        case ObjectKind::boolean:
        {
            Boolean* rightBoolean = static_cast<Boolean*>(rightOperand.get());
            return Compare(leftNodeSet, rightBoolean, op, context);
        }
        case ObjectKind::number:
        {
            Number* rightNumber = static_cast<Number*>(rightOperand.get());
            return Compare(leftNodeSet, rightNumber, op, context);
        }
        case ObjectKind::string:
        {
            String* rightString = static_cast<String*>(rightOperand.get());
            return Compare(leftNodeSet, rightString, op, context);
        }
        }
        break;
    }
    case ObjectKind::boolean:
    {
        Boolean* leftBoolean = static_cast<Boolean*>(leftOperand.get());
        switch (rightOperand->Kind())
        {
        case ObjectKind::nodeSet:
        {
            NodeSet* rightNodeSet = static_cast<NodeSet*>(rightOperand.get());
            return Compare(leftBoolean, rightNodeSet, op, context);
        }
        case ObjectKind::boolean:
        {
            Boolean* rightBoolean = static_cast<Boolean*>(rightOperand.get());
            return std::unique_ptr<Object>(new Boolean(Compare(leftBoolean, rightBoolean, op)));
        }
        case ObjectKind::number:
        {
            Number* rightNumber = static_cast<Number*>(rightOperand.get());
            return Compare(leftBoolean, rightNumber, op, context);
        }
        case ObjectKind::string:
        {
            String* rightString = static_cast<String*>(rightOperand.get());
            return Compare(leftBoolean, rightString, op, context);
        }
        }
        break;
    }
    case ObjectKind::number:
    {
        Number* leftNumber = static_cast<Number*>(leftOperand.get());
        switch (rightOperand->Kind())
        {
        case ObjectKind::nodeSet:
        {
            NodeSet* rightNodeSet = static_cast<NodeSet*>(rightOperand.get());
            return Compare(leftNumber, rightNodeSet, op, context);
        }
        case ObjectKind::boolean:
        {
            Boolean* rightBoolean = static_cast<Boolean*>(rightOperand.get());
            return Compare(leftNumber, rightBoolean, op, context);
        }
        case ObjectKind::number:
        {
            Number* rightNumber = static_cast<Number*>(rightOperand.get());
            return std::unique_ptr<Object>(new Boolean(Compare(leftNumber, rightNumber, op)));
        }
        case ObjectKind::string:
        {
            String* rightString = static_cast<String*>(rightOperand.get());
            return Compare(leftNumber, rightString, op, context);
        }
        }
        break;
    }
    case ObjectKind::string:
    {
        String* leftString = static_cast<String*>(leftOperand.get());
        switch (rightOperand->Kind())
        {
        case ObjectKind::nodeSet:
        {
            NodeSet* rightNodeSet = static_cast<NodeSet*>(rightOperand.get());
            return Compare(leftString, rightNodeSet, op, context);
        }
        case ObjectKind::boolean:
        {
            Boolean* rightBoolean = static_cast<Boolean*>(rightOperand.get());
            return Compare(leftString, rightBoolean, op, context);
        }
        case ObjectKind::number:
        {
            Number* rightNumber = static_cast<Number*>(rightOperand.get());
            return Compare(leftString, rightNumber, op, context);
        }
        case ObjectKind::string:
        {
            String* rightString = static_cast<String*>(rightOperand.get());
            return std::unique_ptr<Object>(new Boolean(Compare(leftString->Value(), rightString->Value(), op)));
        }
        }
        break;
    }
    }
    return std::unique_ptr<soul_expected::xml::xpath::Object>(new Boolean(false));
}

std::expected<std::unique_ptr<soul_expected::xml::xpath::Object>, int> EvaluateArithmeticOp(Expr* left, Expr* right, Operator op, Context& context)
{
    auto l = left->Evaluate(context);
    if (!l) return std::unexpected<int>(l.error());
    std::unique_ptr<soul_expected::xml::xpath::Object> leftOperand = std::move(*l);
    auto n = ToNumber(leftOperand.get(), context);
    if (!n) return std::unexpected<int>(n.error());
    std::unique_ptr<soul_expected::xml::xpath::Object> leftAsNumber = std::move(*n);
    auto c = NumberCast(leftAsNumber.get());
    if (!c) return std::unexpected<int>(c.error());
    Number* leftNumber = *c;
    auto r = right->Evaluate(context);
    if (!r) return std::unexpected<int>(r.error());
    std::unique_ptr<soul_expected::xml::xpath::Object> rightOperand = std::move(*r);
    n = ToNumber(rightOperand.get(), context);
    if (!n) return std::unexpected<int>(n.error());
    std::unique_ptr<soul_expected::xml::xpath::Object> rightAsNumber = std::move(*n);
    c = NumberCast(rightAsNumber.get());
    if (!c) return std::unexpected<int>(c.error());
    Number* rightNumber = *c;
    switch (op)
    {
    case Operator::plus:
    {
        return std::unique_ptr<soul_expected::xml::xpath::Object>(new Number(leftNumber->Value() + rightNumber->Value()));
    }
    case Operator::minus:
    {
        return std::unique_ptr<soul_expected::xml::xpath::Object>(new Number(leftNumber->Value() - rightNumber->Value()));
    }
    case Operator::mul:
    {
        return std::unique_ptr<soul_expected::xml::xpath::Object>(new Number(leftNumber->Value() * rightNumber->Value()));
    }
    case Operator::div:
    {
        return std::unique_ptr<soul_expected::xml::xpath::Object>(new Number(leftNumber->Value() / rightNumber->Value()));
    }
    case Operator::mod:
    {
        return std::unique_ptr<soul_expected::xml::xpath::Object>(new Number(std::remainder(leftNumber->Value(), rightNumber->Value())));
    }
    }
    return std::unexpected<int>(util::AllocateError("arithmetic binary operator expected"));
}

std::expected<std::unique_ptr<soul_expected::xml::xpath::Object>, int> EvaluateUnionExpr(Expr* left, Expr* right, Context& context)
{
    auto l = left->Evaluate(context);
    if (!l) return std::unexpected<int>(l.error());
    std::unique_ptr<soul_expected::xml::xpath::Object> leftOperand = std::move(*l);
    auto c = NodeSetCast(leftOperand.get());
    if (!c) return std::unexpected<int>(c.error());
    NodeSet* leftNodeSet = *c;
    auto r = right->Evaluate(context);
    if (!r) return std::unexpected<int>(r.error());
    std::unique_ptr<soul_expected::xml::xpath::Object> rightOperand = std::move(*r);
    c = NodeSetCast(rightOperand.get());
    if (!c) return std::unexpected<int>(c.error());
    NodeSet* rightNodeSet = *c;
    std::unique_ptr<soul_expected::xml::xpath::NodeSet> result(new soul_expected::xml::xpath::NodeSet());
    int n = leftNodeSet->Count();
    for (int i = 0; i < n; ++i)
    {
        auto n = leftNodeSet->GetNode(i);
        if (!n) return std::unexpected<int>(n.error());
        result->Add(*n);
    }
    int m = rightNodeSet->Count();
    for (int j = 0; j < m; ++j)
    {
        auto n = rightNodeSet->GetNode(j);
        if (!n) return std::unexpected<int>(n.error());
        result->Add(*n);
    }
    return std::unique_ptr<soul_expected::xml::xpath::Object>(result.release());
}

std::expected<std::unique_ptr<soul_expected::xml::xpath::Object>, int> EvaluateCombineStepExpr(Expr* left, Expr* right, Context& context)
{
    auto l = left->Evaluate(context);
    if (!l) return std::unexpected<int>(l.error());
    std::unique_ptr<soul_expected::xml::xpath::Object> leftOperand = std::move(*l);
    auto c = NodeSetCast(leftOperand.get());
    if (!c) return std::unexpected<int>(c.error());
    NodeSet* leftNodeSet = *c;
    std::unique_ptr<soul_expected::xml::xpath::NodeSet> result(new soul_expected::xml::xpath::NodeSet());
    int count = leftNodeSet->Count();
    for (int i = 0; i < count; ++i)
    {
        auto n = leftNodeSet->GetNode(i);
        if (!n) return std::unexpected<int>(n.error());
        soul_expected::xml::Node* leftNode = *n;
        Context rightContext(leftNode, i + 1, count);
        auto r = right->Evaluate(rightContext);
        if (!r) return std::unexpected<int>(r.error());
        std::unique_ptr<soul_expected::xml::xpath::Object> rightOperand = std::move(*r);
        c = NodeSetCast(rightOperand.get());
        if (!c) return std::unexpected<int>(c.error());
        NodeSet* rightNodeSet = *c;
        int m = rightNodeSet->Count();
        for (int j = 0; j < m; ++j)
        {
            auto n = rightNodeSet->GetNode(j);
            if (!n) return std::unexpected<int>(n.error());
            soul_expected::xml::Node* rightNode = *n;
            result->Add(rightNode);
        }
    }
    return std::unique_ptr<soul_expected::xml::xpath::Object>(result.release());
}

Expr::Expr(ExprKind kind_) : kind(kind_)
{
}

Expr::~Expr()
{
}

void Expr::SetStr(const std::string& str_)
{
    str = str_;
}

std::expected<soul_expected::xml::Element*, int> Expr::ToXmlElement() const
{
    soul_expected::xml::Element* element = soul_expected::xml::MakeElement("expr");
    element->SetAttribute("kind", ExprKindStr(kind));
    return element;
}

UnaryExpr::UnaryExpr(Operator op_, Expr* operand_) : Expr(ExprKind::unaryExpr), op(op_), operand(operand_)
{
}

std::expected<std::unique_ptr<soul_expected::xml::xpath::Object>, int> UnaryExpr::Evaluate(Context& context) const
{
    switch (op)
    {
    case Operator::minus:
    {
        return EvaluateUnaryMinusExpr(operand.get(), context);
    }
    case Operator::parens:
    {
        return EvaluateParenExpr(operand.get(), context);
    }
    }
    return std::unexpected<int>(util::AllocateError("unary minus or parenthesis operator expected"));
}

std::expected<soul_expected::xml::Element*, int> UnaryExpr::ToXmlElement() const
{
    auto e = Expr::ToXmlElement();
    if (!e) return std::unexpected<int>(e.error());
    soul_expected::xml::Element* element = *e;
    element->SetAttribute("operator", OperatorStr(op));
    e = operand->ToXmlElement();
    if (!e) return std::unexpected<int>(e.error());
    soul_expected::xml::Element* child = *e;
    auto rv = element->AppendChild(child);
    if (!rv) return std::unexpected<int>(rv.error());
    return element;
}

BinaryExpr::BinaryExpr(Operator op_, Expr* left_, Expr* right_) : Expr(ExprKind::binaryExpr), op(op_), left(left_), right(right_)
{
}

std::expected<std::unique_ptr<soul_expected::xml::xpath::Object>, int> BinaryExpr::Evaluate(Context& context) const
{
    switch (op)
    {
    case Operator::or_:
    {
        return EvaluateOrExpr(left.get(), right.get(), context);
    }
    case Operator::and_:
    {
        return EvaluateAndExpr(left.get(), right.get(), context);
    }
    case Operator::equal:
    {
        return Compare(left.get(), right.get(), Operator::equal, context);
    }
    case Operator::notEqual:
    {
        return Compare(left.get(), right.get(), Operator::notEqual, context);
    }
    case Operator::less:
    {
        return Compare(left.get(), right.get(), Operator::less, context);
    }
    case Operator::greater:
    {
        return Compare(left.get(), right.get(), Operator::greater, context);
    }
    case Operator::lessOrEqual:
    {
        return Compare(left.get(), right.get(), Operator::lessOrEqual, context);
    }
    case Operator::greaterOrEqual:
    {
        return Compare(left.get(), right.get(), Operator::greaterOrEqual, context);
    }
    case Operator::plus:
    {
        return EvaluateArithmeticOp(left.get(), right.get(), Operator::plus, context);
    }
    case Operator::minus:
    {
        return EvaluateArithmeticOp(left.get(), right.get(), Operator::minus, context);
    }
    case Operator::mul:
    {
        return EvaluateArithmeticOp(left.get(), right.get(), Operator::mul, context);
    }
    case Operator::div:
    {
        return EvaluateArithmeticOp(left.get(), right.get(), Operator::div, context);
    }
    case Operator::mod:
    {
        return EvaluateArithmeticOp(left.get(), right.get(), Operator::mod, context);
    }
    case Operator::union_:
    {
        return EvaluateUnionExpr(left.get(), right.get(), context);
    }
    case Operator::slash:
    {
        return EvaluateCombineStepExpr(left.get(), right.get(), context);
    }
    }
    return std::unexpected<int>(util::AllocateError("binary operator expected"));
}

std::expected<soul_expected::xml::Element*, int> BinaryExpr::ToXmlElement() const
{
    auto e = Expr::ToXmlElement();
    if (!e) return e;
    soul_expected::xml::Element* element = *e;
    element->SetAttribute("operator", OperatorStr(op));
    e = left->ToXmlElement();
    soul_expected::xml::Element* leftElement = *e;
    if (!e) return e;
    auto rv = element->AppendChild(leftElement);
    if (!rv) return std::unexpected<int>(rv.error());
    e = right->ToXmlElement();
    if (!e) return e;
    soul_expected::xml::Element* rightElement = *e;
    rv = element->AppendChild(rightElement);
    if (!rv) return std::unexpected<int>(rv.error());
    return element;
}

Root::Root() : Expr(ExprKind::root)
{
}

std::expected<std::unique_ptr<soul_expected::xml::xpath::Object>, int> Root::Evaluate(Context& context) const
{
    std::unique_ptr<soul_expected::xml::xpath::NodeSet> nodeSet(new soul_expected::xml::xpath::NodeSet());
    if (context.Node()->IsDocumentNode())
    {
        nodeSet->Add(context.Node());
    }
    else if (context.Node()->OwnerDocument())
    {
        nodeSet->Add(context.Node()->OwnerDocument());
    }
    return std::unique_ptr<soul_expected::xml::xpath::Object>(nodeSet.release());
}

FilterExpr::FilterExpr(Expr* subject_, Expr* predicate_) : Expr(ExprKind::filterExpr), subject(subject_), predicate(predicate_)
{
}

std::expected<std::unique_ptr<soul_expected::xml::xpath::Object>, int> FilterExpr::Evaluate(Context& context) const
{
    auto s = subject->Evaluate(context);
    if (!s) return std::unexpected<int>(s.error());
    std::unique_ptr<soul_expected::xml::xpath::Object> subjectResult = std::move(*s);
    if (subjectResult->IsNodeSet())
    {
        std::unique_ptr<soul_expected::xml::xpath::NodeSet> nodeSet(static_cast<soul_expected::xml::xpath::NodeSet*>(subjectResult.release()));
        std::unique_ptr<soul_expected::xml::xpath::NodeSet> filteredNodeSet(new soul_expected::xml::xpath::NodeSet());
        int count = nodeSet->Count();
        for (int i = 0; i < count; ++i)
        {
            auto n = nodeSet->GetNode(i);
            if (!n) return std::unexpected<int>(n.error());
            soul_expected::xml::Node* node = *n;
            Context filterContext(node, i + 1, count);
            auto r = predicate->Evaluate(filterContext);
            if (!r) return std::unexpected<int>(r.error());
            std::unique_ptr<soul_expected::xml::xpath::Object> result = std::move(*r);
            bool include = false;
            if (result->IsNumber())
            {
                auto n = NumberCast(result.get());
                if (!n) return std::unexpected<int>(n.error());
                Number* number = *n;
                if (number->Value() == filterContext.Pos())
                {
                    include = true;
                }
            }
            else
            {
                auto b = ToBoolean(result.get(), filterContext);
                if (!b) return std::unexpected<int>(b.error());
                std::unique_ptr<soul_expected::xml::xpath::Object> booleanResult = std::move(*b);
                auto c = BooleanCast(booleanResult.get());
                if (!c) return std::unexpected<int>(c.error());
                Boolean* boolean = *c;
                include = boolean->Value();
            }
            if (include)
            {
                filteredNodeSet->Add(node);
            }
        }
        std::swap(nodeSet, filteredNodeSet);
        return std::unique_ptr<soul_expected::xml::xpath::Object>(nodeSet.release());
    }
    else
    {
        return std::unexpected<int>(util::AllocateError("node-set expected"));
    }
}

std::expected<soul_expected::xml::Element*, int> FilterExpr::ToXmlElement() const
{
    auto e = Expr::ToXmlElement();
    if (!e) return e;
    soul_expected::xml::Element* element = *e;
    e = subject->ToXmlElement();
    if (!e) return e;
    soul_expected::xml::Element* subjectElement = *e;
    auto rv = element->AppendChild(subjectElement);
    if (!rv) return std::unexpected<int>(rv.error());
    e = predicate->ToXmlElement();
    if (!e) return e;
    soul_expected::xml::Element* predicateElement = *e;
    rv = element->AppendChild(predicateElement);
    if (!rv) return std::unexpected<int>(rv.error());
    return element;
}

std::string NodeTestStr(NodeTestKind nodeTest)
{
    switch (nodeTest)
    {
    case NodeTestKind::piLiteralTest: return "pi-literal-test";
    case NodeTestKind::commentNodeTest: return "comment-node-test";
    case NodeTestKind::textNodeTest: return "text-node-test";
    case NodeTestKind::piNodeTest: return "pi-node-test";
    case NodeTestKind::anyNodeTest: return "any-node-test";
    case NodeTestKind::principalNodeTest: return "principal-node-test";
    case NodeTestKind::prefixTest: return "prefix-node-test";
    case NodeTestKind::nameTest: return "name-node-test";
    }
    return "<unknown node-test>";
}

NodeTest::NodeTest(NodeTestKind kind_) : kind(kind_)
{
}

NodeTest::~NodeTest()
{
}

bool NodeTest::Select(soul_expected::xml::Node* node, soul_expected::xml::Axis axis) const
{
    switch (kind)
    {
    case NodeTestKind::commentNodeTest:
    {
        return node->IsCommentNode();
    }
    case NodeTestKind::textNodeTest:
    {
        return node->IsTextNode();
    }
    case NodeTestKind::piNodeTest:
    {
        return node->IsProcessingInstructionNode();
    }
    case NodeTestKind::anyNodeTest:
    {
        return true;
    }
    case NodeTestKind::principalNodeTest:
    {
        if (axis == soul_expected::xml::Axis::attribute)
        {
            return node->IsAttributeNode();
        }
        else if (axis == soul_expected::xml::Axis::ns)
        {
            return false; // todo namespace axis not supported
        }
        else
        {
            return node->IsElementNode();
        }
    }
    }
    return false;
}

std::expected<soul_expected::xml::Element*, int> NodeTest::ToXmlElement() const
{
    soul_expected::xml::Element* element = soul_expected::xml::MakeElement("node-test");
    element->SetAttribute("kind", NodeTestStr(kind));
    return element;
}

PILiteralNodeTest::PILiteralNodeTest(Literal* literal_) : NodeTest(NodeTestKind::piLiteralTest), literal(literal_)
{
}

bool PILiteralNodeTest::Select(soul_expected::xml::Node* node, soul_expected::xml::Axis axis) const
{
    if (node->IsProcessingInstructionNode())
    {
        soul_expected::xml::ProcessingInstruction* pi = static_cast<soul_expected::xml::ProcessingInstruction*>(node);
        if (pi->Target() == literal->Value())
        {
            return true;
        }
    }
    return false;
}

std::expected<soul_expected::xml::Element*, int> PILiteralNodeTest::ToXmlElement() const
{
    auto e = NodeTest::ToXmlElement();
    if (!e) return e;
    soul_expected::xml::Element* element = *e;
    e = literal->ToXmlElement();
    if (!e) return e;
    auto rv = element->AppendChild(*e);
    if (!rv) return std::unexpected<int>(rv.error());
    return element;
}

PrefixNodeTest::PrefixNodeTest(const std::string& prefix_) : NodeTest(NodeTestKind::prefixTest), prefix(prefix_)
{
}

bool PrefixNodeTest::Select(soul_expected::xml::Node* node, soul_expected::xml::Axis axis) const
{
    if (axis == soul_expected::xml::Axis::attribute)
    {
        if (node->IsAttributeNode())
        {
            if (node->Prefix() == prefix)
            {
                return true;
            }
        }
    }
    else if (axis == soul_expected::xml::Axis::ns)
    {
        return false; // todo namespace axis not supported
    }
    else if (node->IsElementNode())
    {
        if (node->Prefix() == prefix)
        {
            return true;
        }
    }
    return false;
}

std::expected<soul_expected::xml::Element*, int> PrefixNodeTest::ToXmlElement() const
{
    auto e = NodeTest::ToXmlElement();
    if (!e) return e;
    soul_expected::xml::Element* element = *e;
    element->SetAttribute("prefix", prefix);
    return element;
}

NameNodeTest::NameNodeTest(const std::string& name_) : NodeTest(NodeTestKind::nameTest), name(name_)
{
}

bool NameNodeTest::Select(soul_expected::xml::Node* node, soul_expected::xml::Axis axis) const
{
    if (axis == soul_expected::xml::Axis::attribute)
    {
        if (node->IsAttributeNode())
        {
            if (node->Name() == name)
            {
                return true;
            }
        }
    }
    else if (axis == soul_expected::xml::Axis::ns)
    {
        return false; // todo namespace axis not supported
    }
    else
    {
        if (node->IsElementNode())
        {
            if (node->Name() == name)
            {
                return true;
            }
        }
    }
    return false;
}

std::expected<soul_expected::xml::Element*, int> NameNodeTest::ToXmlElement() const
{
    auto e = NodeTest::ToXmlElement();
    if (!e) return e;
    soul_expected::xml::Element* element = *e;
    element->SetAttribute("name", name);
    return element;
}

LocationStepExpr::LocationStepExpr(soul_expected::xml::Axis axis_, NodeTest* nodeTest_) : Expr(ExprKind::locationStepExpr), axis(axis_), nodeTest(nodeTest_)
{
}

void LocationStepExpr::AddPredicate(Expr* predicate)
{
    predicates.push_back(std::unique_ptr<Expr>(predicate));
}

std::expected<std::unique_ptr<soul_expected::xml::xpath::Object>, int> LocationStepExpr::Evaluate(Context& context) const
{
    std::unique_ptr<soul_expected::xml::xpath::NodeSet> nodeSet(new soul_expected::xml::xpath::NodeSet());
    NodeSelectionOperation selectNodes(nodeTest.get(), *nodeSet, axis);
    context.Node()->Walk(selectNodes, axis);
    for (const auto& predicate : predicates)
    {
        std::unique_ptr<soul_expected::xml::xpath::NodeSet> filteredNodeSet(new soul_expected::xml::xpath::NodeSet());
        int count = nodeSet->Count();
        for (int i = 0; i < count; ++i)
        {
            auto n = nodeSet->GetNode(i);
            if (!n) return std::unexpected<int>(n.error());
            soul_expected::xml::Node* node = *n;
            Context filterContext(node, i + 1, count);
            auto p = predicate->Evaluate(filterContext);
            if (!p) return std::unexpected<int>(p.error());
            std::unique_ptr<soul_expected::xml::xpath::Object> predicateResult = std::move(*p);
            bool include = false;
            if (predicateResult->IsNumber())
            {
                Number* number = static_cast<Number*>(predicateResult.get());
                if (number->Value() == filterContext.Pos())
                {
                    include = true;
                }
            }
            else
            {
                auto b = ToBoolean(predicateResult.get(), filterContext);
                if (!b) return std::unexpected<int>(b.error());
                std::unique_ptr<Object> booleanResult = std::move(*b);
                auto c = BooleanCast(booleanResult.get());
                if (!c) return std::unexpected<int>(c.error());
                Boolean* boolean = *c;
                include = boolean->Value();
            }
            if (include)
            {
                filteredNodeSet->Add(node);
            }
        }
        std::swap(nodeSet, filteredNodeSet);
    }
    return std::unique_ptr<soul_expected::xml::xpath::Object>(nodeSet.release());
}

std::expected<soul_expected::xml::Element*, int> LocationStepExpr::ToXmlElement() const
{
    auto e = Expr::ToXmlElement();
    if (!e) return e;
    soul_expected::xml::Element* element = *e;
    element->SetAttribute("axis", soul_expected::xml::AxisName(axis));
    e = nodeTest->ToXmlElement();
    if (!e) return e;
    auto rv = element->AppendChild(*e);
    if (!rv) return std::unexpected<int>(rv.error());
    soul_expected::xml::Element* predicatesElement = MakeElement("predicates");
    for (const auto& predicate : predicates)
    {
        e = predicate->ToXmlElement();
        if (!e) return e;
        rv = predicatesElement->AppendChild(*e);
        if (!rv) return std::unexpected<int>(rv.error());
    }
    rv = element->AppendChild(predicatesElement);
    if (!rv) return std::unexpected<int>(rv.error());
    return element;
}

VariableReference::VariableReference(const std::string& variableName_) : Expr(ExprKind::variableReference), variableName(variableName_)
{
}

std::expected<std::unique_ptr<soul_expected::xml::xpath::Object>, int> VariableReference::Evaluate(Context& context) const
{
    return std::unexpected<int>(util::AllocateError("error: variable references not implemented"));
}

std::expected<soul_expected::xml::Element*, int> VariableReference::ToXmlElement() const
{
    auto e = Expr::ToXmlElement();
    if (!e) return e;
    soul_expected::xml::Element* element = *e;
    element->SetAttribute("variable-name", variableName);
    return element;
}

Literal::Literal(const std::string& value_) : Expr(ExprKind::literal), value(value_)
{
}

std::expected<std::unique_ptr<soul_expected::xml::xpath::Object>, int> Literal::Evaluate(Context& context) const
{
    return std::unique_ptr<soul_expected::xml::xpath::Object>(new String(value));
}

std::expected<soul_expected::xml::Element*, int> Literal::ToXmlElement() const
{
    auto e = Expr::ToXmlElement();
    if (!e) return e;
    soul_expected::xml::Element* element = *e;
    element->SetAttribute("value", value);
    return element;
}

NumberExpr::NumberExpr(double value_) : Expr(ExprKind::numberExpr), value(value_)
{
}

std::expected<std::unique_ptr<soul_expected::xml::xpath::Object>, int> NumberExpr::Evaluate(Context& context) const
{
    return std::unique_ptr<soul_expected::xml::xpath::Object>(new Number(value));
}

std::expected<soul_expected::xml::Element*, int> NumberExpr::ToXmlElement() const
{
    auto e = Expr::ToXmlElement();
    if (!e) return e;
    soul_expected::xml::Element* element = *e;
    element->SetAttribute("value", std::to_string(value));
    return element;
}

FunctionCall::FunctionCall(const std::string& functionName_) : Expr(ExprKind::functionCall), functionName(functionName_)
{
}

void FunctionCall::AddArgument(Expr* argument)
{
    arguments.push_back(std::unique_ptr<Expr>(argument));
}

std::expected<std::unique_ptr<soul_expected::xml::xpath::Object>, int> FunctionCall::Evaluate(Context& context) const
{
    auto f = GetFunction(functionName);
    if (!f) return std::unexpected<int>(f.error());
    Function* function = *f;
    std::vector<std::unique_ptr<Object>> ownedArgs;
    std::vector<Object*> args;
    for (const auto& arg : arguments)
    {
        auto a = arg->Evaluate(context);
        if (!a) return std::unexpected<int>(a.error());
        auto argValue = std::move(*a);
        args.push_back(argValue.get());
        ownedArgs.push_back(std::move(argValue));
    }
    return function->Evaluate(context, args);
}

std::expected<soul_expected::xml::Element*, int> FunctionCall::ToXmlElement() const
{
    auto e = Expr::ToXmlElement();
    if (!e) return e;
    soul_expected::xml::Element* element = *e;
    element->SetAttribute("function-name", functionName);
    soul_expected::xml::Element* argumentsElement = soul_expected::xml::MakeElement("arguments");
    for (const auto& arg : arguments)
    {
        e = arg->ToXmlElement();
        if (!e) return e;
        auto rv = argumentsElement->AppendChild(*e);
        if (!rv) return std::unexpected<int>(rv.error());
    }
    auto rv = element->AppendChild(argumentsElement);
    if (!rv) return std::unexpected<int>(rv.error());
    return element;
}

Expr* MakeSlashSlashExpr(Expr* left, Expr* right)
{
    return new BinaryExpr(Operator::slash, left,
        new BinaryExpr(Operator::slash,
            new LocationStepExpr(soul_expected::xml::Axis::descendantOrSelf, new NodeTest(NodeTestKind::anyNodeTest)),
            right));
}

} // namespace soul_expected::xml::xpath::expr
