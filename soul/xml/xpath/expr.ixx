// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.xml.xpath.expr;

import std.core;
import soul.xml.xpath.object;
import soul.xml.axis;

export namespace soul::xml::xpath::expr {

enum class Operator
{
    or_, and_, equal, notEqual, less, greater, lessOrEqual, greaterOrEqual, plus, minus, mul, div, mod, union_, combineStep, slash, slashSlash
};

enum class ExprKind
{
    unaryExpr, binaryExpr, root, filterExpr, locationStepExpr, variableReference, literal, numberExpr, functionCall
};

class Expr
{
public:
    Expr(ExprKind kind_);
    virtual ~Expr();
    ExprKind Kind() const { return kind; }
private:
    ExprKind kind;
};

class UnaryExpr : public Expr
{
public:
    UnaryExpr(Operator op_, Expr* operand_);
    Operator Op() const { return op; }
    Expr* Operand() const { return operand.get(); }
private:
    Operator op;
    std::unique_ptr<Expr> operand;
};

class BinaryExpr : public Expr
{
public:
    BinaryExpr(Operator op_, Expr* left_, Expr* right_);
    Operator Op() const { return op; }
    Expr* Left() const { return left.get(); }
    Expr* Right() const { return right.get(); }
private:
    Operator op;
    std::unique_ptr<Expr> left;
    std::unique_ptr<Expr> right;
};

class Root : public Expr
{
public:
    Root();
};

class FilterExpr : public Expr
{
public:
    FilterExpr(Expr* subject_, Expr* predicate_);
    Expr* Subject() const { return subject.get(); }
    Expr* Predicate() const { return predicate.get(); }
private:
    std::unique_ptr<Expr> subject;
    std::unique_ptr<Expr> predicate;
};

enum class NodeTestKind
{
    piLiteralTest, commentNodeTest, textNodeTest, piNodeTest, anyNodeTest, principalNodeTest, prefixTest, nameTest
};

class NodeTest
{
public:
    NodeTest(NodeTestKind kind_);
    virtual ~NodeTest();
    NodeTestKind Kind() const { return kind; }
private:
    NodeTestKind kind;
};

class Literal;

class PILiteralNodeTest : public NodeTest
{
public:
    PILiteralNodeTest(Literal* literal_);
    Literal* Lit() const { return literal.get(); }
private:
    std::unique_ptr<Literal> literal;
};

class PrefixNodeTest : public NodeTest
{
public:
    PrefixNodeTest(const std::string& name_);
    const std::string& Name() const { return name; }
private:
    std::string name;
};

class NameNodeTest : public NodeTest
{
public:
    NameNodeTest(const std::string& name_);
    const std::string& Name() const { return name; }
private:
    std::string name;
};

class LocationStepExpr : public Expr
{
public:
    LocationStepExpr(soul::xml::Axis axis_, NodeTest* nodeTest_);
    NodeTest* GetNodeTest() const { return nodeTest.get(); }
    void AddPredicate(Expr* predicate);
    const std::vector<std::unique_ptr<Expr>>& Predicates() const { return predicates; }
private:
    soul::xml::Axis axis;
    std::unique_ptr<NodeTest> nodeTest;
    std::vector<std::unique_ptr<Expr>> predicates;
};

class VariableReference : public Expr
{
public:
    VariableReference(const std::string& variableName_);
    const std::string& VariableName() const { return variableName; }
private:
    std::string variableName;
};

class Literal : public Expr
{
public:
    Literal(const std::string& value_);
    const std::string& Value() const { return value; }
private:
    std::string value;
};

class NumberExpr : public Expr
{
public:
    NumberExpr(double value_);
    double Value() const { return value; }
private:
    double value;
};

class FunctionCall : public Expr
{
public:
    FunctionCall(const std::string& functionName_);
    const std::string& FunctionName() const { return functionName; }
private:
    std::string functionName;
};

Expr* MakeSlashSlashExpr(Expr* left, Expr* right);

} // namespace soul::xml::xpath::expr
