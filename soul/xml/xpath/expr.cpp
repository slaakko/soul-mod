// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.xml.xpath.expr;

namespace soul::xml::xpath::expr {

Expr::Expr(ExprKind kind_) : kind(kind_)
{
}

Expr::~Expr()
{
}

UnaryExpr::UnaryExpr(Operator op_, Expr* operand_) : Expr(ExprKind::unaryExpr), op(op_), operand(operand_)
{
}

BinaryExpr::BinaryExpr(Operator op_, Expr* left_, Expr* right_) : Expr(ExprKind::binaryExpr), op(op_), left(left_), right(right_)
{
}

Root::Root() : Expr(ExprKind::root)
{
}

FilterExpr::FilterExpr(Expr* subject_, Expr* predicate_) : Expr(ExprKind::filterExpr), subject(subject_), predicate(predicate_)
{
}

NodeTest::NodeTest(NodeTestKind kind_) : kind(kind_)
{
}

NodeTest::~NodeTest()
{
}

PILiteralNodeTest::PILiteralNodeTest(Literal* literal_) : NodeTest(NodeTestKind::piLiteralTest), literal(literal_)
{
}

PrefixNodeTest::PrefixNodeTest(const std::string& name_) : NodeTest(NodeTestKind::prefixTest), name(name_)
{
}

NameNodeTest::NameNodeTest(const std::string& name_) : NodeTest(NodeTestKind::nameTest), name(name_)
{
}

LocationStepExpr::LocationStepExpr(soul::xml::Axis axis_, NodeTest* nodeTest_) : Expr(ExprKind::locationStepExpr), axis(axis_), nodeTest(nodeTest_)
{
}

void LocationStepExpr::AddPredicate(Expr* predicate)
{
    predicates.push_back(std::unique_ptr<Expr>(predicate));
}

VariableReference::VariableReference(const std::string& variableName_) : Expr(ExprKind::variableReference), variableName(variableName_)
{
}

Literal::Literal(const std::string& value_) : Expr(ExprKind::literal), value(value_)
{
}

NumberExpr::NumberExpr(double value_) : Expr(ExprKind::numberExpr), value(value_)
{
}

FunctionCall::FunctionCall(const std::string& functionName_) : Expr(ExprKind::functionCall), functionName(functionName_)
{
}

Expr* MakeSlashSlashExpr(Expr* left, Expr* right)
{
    return new BinaryExpr(Operator::slash, left,
        new BinaryExpr(Operator::slash, 
            new LocationStepExpr(soul::xml::Axis::descendantOrSelf, new NodeTest(NodeTestKind::anyNodeTest)),
            right));
}

} // namespace soul::xml::xpath::expr
