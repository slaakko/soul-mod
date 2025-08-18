// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.ast.cpp;

namespace soul::ast::cpp {

std::string OperatorStr(Operator op)
{
    switch (op)
    {
    case Operator::deref: return "*";
    case Operator::addrOf: return "&";
    case Operator::plus: return "+";
    case Operator::minus: return "-";
    case Operator::and_: return "&&";
    case Operator::or_: return "||";
    case Operator::not_: return "!";
    case Operator::cpl: return "~";
    case Operator::dotStar: return ".*";
    case Operator::arrowStar: return "->*";
    case Operator::bitand_: return "&";
    case Operator::bitxor: return "^";
    case Operator::bitor_: return "|";
    case Operator::mul: return "*";
    case Operator::div: return "/";
    case Operator::rem: return "%";
    case Operator::shiftLeft: return "<<";
    case Operator::shiftRight: return ">>";
    case Operator::less: return "<";
    case Operator::greater: return ">";
    case Operator::lessOrEq: return "<=";
    case Operator::greaterOrEq: return ">=";
    case Operator::eq: return "==";
    case Operator::notEq: return "!=";
    case Operator::comma: return ",";
    case Operator::assign: return "=";
    case Operator::mulAssign: return "*=";
    case Operator::divAssign: return "/=";
    case Operator::remAssign: return "%=";
    case Operator::plusAssign: return "+=";
    case Operator::minusAssign: return "-=";
    case Operator::shiftLeftAssign: return "<<=";
    case Operator::shiftRightAssign: return ">>=";
    case Operator::andAssign: return "&=";
    case Operator::xorAssign: return "^=";
    case Operator::orAssign: return "|=";
    }
    return "";
}

Node::Node(NodeKind kind_, const soul::ast::SourcePos& sourcePos_) : kind(kind_), sourcePos(sourcePos_), parent(nullptr)
{
}

Node::~Node()
{
}

UnaryNode::UnaryNode(NodeKind kind_, const soul::ast::SourcePos& sourcePos_, Node* child_) : Node(kind_, sourcePos_), child(child_)
{
    child->SetParent(this);
}

void UnaryNode::Replace(Node* node, Node* replacement)
{
    if (child.get() == node)
    {
        child.reset(replacement);
    }
}

BinaryNode::BinaryNode(NodeKind kind_, const soul::ast::SourcePos& sourcePos_, Node* left_, Node* right_) : Node(kind_, sourcePos_), left(left_), right(right_)
{
    left->SetParent(this);
    right->SetParent(this);
}

void BinaryNode::Replace(Node* node, Node* replacement)
{
    if (left.get() == node)
    {
        left.reset(replacement);
    }
    else if (right.get() == node)
    {
        right.reset(replacement);
    }
}

ExprListNode::ExprListNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::exprListNode, sourcePos_)
{
}

Node* ExprListNode::Clone() const
{
    ExprListNode* clone = new ExprListNode(GetSourcePos());
    for (const auto& expr : exprs)
    {
        clone->Add(expr->Clone());
    }
    return clone;
}

void ExprListNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> ExprListNode::Write(CodeFormatter& formatter)
{
    std::expected<bool, int> rv = formatter.Write("(");
    if (!rv) return std::unexpected<int>(rv.error());
    bool first = true;
    for (const auto& expr : exprs)
    {
        if (first)
        {
            first = false;
        }
        else
        {
            rv = formatter.Write(", ");
            if (!rv) return std::unexpected<int>(rv.error());
        }
        rv = expr->Write(formatter);
        if (!rv) return std::unexpected<int>(rv.error());
    }
    return formatter.Write(")");
}

std::string ExprListNode::ToString() const
{
    std::string str = "(";
    bool first = true;
    for (const auto& expr : exprs)
    {
        if (first)
        {
            first = false;
        }
        else
        {
            str.append(", ");
        }
        str.append(expr->ToString());
    }
    str.append(")");
    return str;
}

void ExprListNode::Add(Node* node)
{
    node->SetParent(this);
    exprs.push_back(std::unique_ptr<Node>(node));
}

void ExprListNode::Replace(Node* node, Node* replacement)
{
    for (auto& expr : exprs)
    {
        if (expr.get() == node)
        {
            expr.reset(replacement);
            break;
        }
    }
}

ThisNode::ThisNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::thisNode, sourcePos_)
{
}

Node* ThisNode::Clone() const
{
    return new ThisNode(GetSourcePos());
}

void ThisNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> ThisNode::Write(CodeFormatter& formatter)
{
    return formatter.Write("this");
}

IdExprNode::IdExprNode(const soul::ast::SourcePos& sourcePos_, const std::string& id_) : Node(NodeKind::idExprNode, sourcePos_), id(id_)
{
}

void IdExprNode::SetId(const std::string& id_)
{
    id = id_;
}

Node* IdExprNode::Clone() const
{
    return new IdExprNode(GetSourcePos(), id);
}

void IdExprNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> IdExprNode::Write(CodeFormatter& formatter)
{
    return formatter.Write(id);
}

IndexExprNode::IndexExprNode(const soul::ast::SourcePos& sourcePos_, Node* child_, Node* index_) : UnaryNode(NodeKind::indexExprNode, sourcePos_, child_), index(index_)
{
    index->SetParent(this);
}

Node* IndexExprNode::Clone() const
{
    return new IndexExprNode(GetSourcePos(), Child()->Clone(), index->Clone());
}

void IndexExprNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> IndexExprNode::Write(CodeFormatter& formatter)
{
    std::expected<bool, int> rv = Child()->Write(formatter);
    if (!rv) return std::unexpected<int>(rv.error());
    rv = formatter.Write("[");
    if (!rv) return std::unexpected<int>(rv.error());
    rv = index->Write(formatter);
    if (!rv) return std::unexpected<int>(rv.error());
    return formatter.Write("]");
}

std::string IndexExprNode::ToString() const
{
    return Child()->ToString() + "[" + index->ToString() + "]";
}

InvokeNode::InvokeNode(const soul::ast::SourcePos& sourcePos_, Node* child_) : UnaryNode(NodeKind::invokeNode, sourcePos_, child_)
{
}

Node* InvokeNode::Clone() const
{
    InvokeNode* clone = new InvokeNode(GetSourcePos(), Child()->Clone());
    for (const auto& arg : args)
    {
        clone->Add(arg->Clone());
    }
    return clone;
}

void InvokeNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> InvokeNode::Write(CodeFormatter& formatter)
{
    std::expected<bool, int> rv = Child()->Write(formatter);
    if (!rv) return std::unexpected<int>(rv.error());
    rv = formatter.Write("(");
    if (!rv) return std::unexpected<int>(rv.error());
    bool first = true;
    for (const auto& arg : args)
    {
        if (first)
        {
            first = false;
        }
        else
        {
            rv = formatter.Write(", ");
            if (!rv) return std::unexpected<int>(rv.error());
        }
        rv = arg->Write(formatter);
        if (!rv) return std::unexpected<int>(rv.error());
    }
    return formatter.Write(")");
}

std::string InvokeNode::ToString() const
{
    std::string str = Child()->ToString();
    str.append(1, '(');
    bool first = true;
    for (const auto& arg : args)
    {
        if (first)
        {
            first = false;
        }
        else
        {
            str.append(", ");
        }
        str.append(arg->ToString());
    }
    str.append(1, ')');
    return str;
}

void InvokeNode::Add(Node* node)
{
    node->SetParent(this);
    args.push_back(std::unique_ptr<Node>(node));
}

void InvokeNode::Replace(Node* node, Node* replacement)
{
    for (auto& arg : args)
    {
        if (arg.get() == node)
        {
            arg.reset(replacement);
            break;
        }
    }
}

MemberAccessNode::MemberAccessNode(const soul::ast::SourcePos& sourcePos_, Node* child_, Node* member_) : UnaryNode(NodeKind::memberAccessNode, sourcePos_, child_), member(member_)
{
    member->SetParent(this);
}

Node* MemberAccessNode::Clone() const
{
    return new MemberAccessNode(GetSourcePos(), Child()->Clone(), member->Clone());
}

void MemberAccessNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> MemberAccessNode::Write(CodeFormatter& formatter)
{
    std::expected<bool, int> rv = Child()->Write(formatter);
    if (!rv) return std::unexpected<int>(rv.error());
    rv = formatter.Write(".");
    if (!rv) return std::unexpected<int>(rv.error());
    return member->Write(formatter);
}

std::string MemberAccessNode::ToString() const
{
    return Child()->ToString() + "." + member->ToString();
}

PtrMemberAccessNode::PtrMemberAccessNode(const soul::ast::SourcePos& sourcePos_, Node* child_, Node* member_) :
    UnaryNode(NodeKind::ptrMemberAccessNode, sourcePos_, child_), member(member_)
{
    member->SetParent(this);
}

Node* PtrMemberAccessNode::Clone() const
{
    return new PtrMemberAccessNode(GetSourcePos(), Child()->Clone(), member->Clone());
}

void PtrMemberAccessNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> PtrMemberAccessNode::Write(CodeFormatter& formatter)
{
    std::expected<bool, int> rv = Child()->Write(formatter);
    if (!rv) return std::unexpected<int>(rv.error());
    rv = formatter.Write("->");
    if (!rv) return std::unexpected<int>(rv.error());
    return member->Write(formatter);
}

std::string PtrMemberAccessNode::ToString() const
{
    return Child()->ToString() + "->" + member->ToString();
}

PostIncrementNode::PostIncrementNode(const soul::ast::SourcePos& sourcePos_, Node* child_) : UnaryNode(NodeKind::postIncrementNode, sourcePos_, child_)
{
}

Node* PostIncrementNode::Clone() const
{
    return new PostIncrementNode(GetSourcePos(), Child()->Clone());
}

void PostIncrementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> PostIncrementNode::Write(CodeFormatter& formatter)
{
    std::expected<bool, int> rv = Child()->Write(formatter);
    if (!rv) return std::unexpected<int>(rv.error());
    return formatter.Write("++");
}

std::string PostIncrementNode::ToString() const
{
    return Child()->ToString() + "++";
}

PostDecrementNode::PostDecrementNode(const soul::ast::SourcePos& sourcePos_, Node* child_) : UnaryNode(NodeKind::postDecrementNode, sourcePos_, child_)
{
}

Node* PostDecrementNode::Clone() const
{
    return new PostDecrementNode(GetSourcePos(), Child()->Clone());
}

void PostDecrementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> PostDecrementNode::Write(CodeFormatter& formatter)
{
    std::expected<bool, int> rv = Child()->Write(formatter);
    if (!rv) return std::unexpected<int>(rv.error());
    return formatter.Write("--");
}

std::string PostDecrementNode::ToString() const
{
    return Child()->ToString() + "--";
}

CppCastNode::CppCastNode(NodeKind kind_, const soul::ast::SourcePos& sourcePos_) : Node(kind_, sourcePos_)
{
}

StaticCastNode::StaticCastNode(const soul::ast::SourcePos& sourcePos_) : CppCastNode(NodeKind::staticCastNode, sourcePos_)
{
}

Node* StaticCastNode::Clone() const
{
    return new StaticCastNode(GetSourcePos());
}

void StaticCastNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> StaticCastNode::Write(CodeFormatter& formatter)
{
    return formatter.Write("static_cast");
}

DynamicCastNode::DynamicCastNode(const soul::ast::SourcePos& sourcePos_) : CppCastNode(NodeKind::dynamicCastNode, sourcePos_)
{
}

Node* DynamicCastNode::Clone() const
{
    return new DynamicCastNode(GetSourcePos());
}

void DynamicCastNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> DynamicCastNode::Write(CodeFormatter& formatter)
{
    return formatter.Write("dynamic_cast");
}

ReinterpretCastNode::ReinterpretCastNode(const soul::ast::SourcePos& sourcePos_) : CppCastNode(NodeKind::reinterpretCastNode, sourcePos_)
{
}

Node* ReinterpretCastNode::Clone() const
{
    return new ReinterpretCastNode(GetSourcePos());
}

void ReinterpretCastNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> ReinterpretCastNode::Write(CodeFormatter& formatter)
{
    return formatter.Write("reinterpret_cast");
}

ConstCastNode::ConstCastNode(const soul::ast::SourcePos& sourcePos_) : CppCastNode(NodeKind::constCastNode, sourcePos_)
{
}

Node* ConstCastNode::Clone() const
{
    return new ConstCastNode(GetSourcePos());
}

void ConstCastNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> ConstCastNode::Write(CodeFormatter& formatter)
{
    return formatter.Write("const_cast");
}

PostCastNode::PostCastNode(const soul::ast::SourcePos& sourcePos_, CppCastNode* cppCastNode_, Node* type_, Node* child_) :
    UnaryNode(NodeKind::postCastNode, sourcePos_, child_), cppCastNode(cppCastNode_), type(type_)
{
    cppCastNode->SetParent(this);
    type->SetParent(this);
}

Node* PostCastNode::Clone() const
{
    return new PostCastNode(GetSourcePos(), static_cast<CppCastNode*>(cppCastNode->Clone()), type->Clone(), Child()->Clone());
}

void PostCastNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> PostCastNode::Write(CodeFormatter& formatter)
{
    std::expected<bool, int> rv = cppCastNode->Write(formatter);
    if (!rv) return std::unexpected<int>(rv.error());
    rv = formatter.Write("<");
    if (!rv) return std::unexpected<int>(rv.error());
    rv = type->Write(formatter);
    if (!rv) return std::unexpected<int>(rv.error());
    rv = formatter.Write(">(");
    if (!rv) return std::unexpected<int>(rv.error());
    rv = Child()->Write(formatter);
    return formatter.Write(")");
}

std::string PostCastNode::ToString() const
{
    std::string str = cppCastNode->ToString();
    str.append(1, '<');
    str.append(type->ToString());
    str.append(1, '>');
    str.append(1, '(');
    str.append(Child()->ToString());
    str.append(1, ')');
    return str;
}

TypeIdExprNode::TypeIdExprNode(const soul::ast::SourcePos& sourcePos_, Node* child_) : UnaryNode(NodeKind::typeIdExprNode, sourcePos_, child_)
{
}

Node* TypeIdExprNode::Clone() const
{
    return new TypeIdExprNode(GetSourcePos(), Child()->Clone());
}

void TypeIdExprNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> TypeIdExprNode::Write(CodeFormatter& formatter)
{
    std::expected<bool, int> rv = formatter.Write("typeid(");
    if (!rv) return std::unexpected<int>(rv.error());
    rv = Child()->Write(formatter);
    if (!rv) return std::unexpected<int>(rv.error());
    return formatter.Write(")");
}

std::string TypeIdExprNode::ToString() const
{
    return "typeid(" + Child()->ToString() + ")";
}

PreIncrementNode::PreIncrementNode(const soul::ast::SourcePos& sourcePos_, Node* child_) : UnaryNode(NodeKind::preIncrementNode, sourcePos_, child_)
{
}

Node* PreIncrementNode::Clone() const
{
    return new PreIncrementNode(GetSourcePos(), Child()->Clone());
}

void PreIncrementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> PreIncrementNode::Write(CodeFormatter& formatter)
{
    std::expected<bool, int> rv = formatter.Write("++");
    if (!rv) return std::unexpected<int>(rv.error());
    return Child()->Write(formatter);
}

std::string PreIncrementNode::ToString() const
{
    return "++" + Child()->ToString();
}

PreDecrementNode::PreDecrementNode(const soul::ast::SourcePos& sourcePos_, Node* child_) : UnaryNode(NodeKind::preDecrementNode, sourcePos_, child_)
{
}

Node* PreDecrementNode::Clone() const
{
    return new PreDecrementNode(GetSourcePos(), Child()->Clone());
}

void PreDecrementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> PreDecrementNode::Write(CodeFormatter& formatter)
{
    std::expected<bool, int> rv = formatter.Write("--");
    if (!rv) return std::unexpected<int>(rv.error());
    return Child()->Write(formatter);
}

std::string PreDecrementNode::ToString() const
{
    return "--" + Child()->ToString();
}

UnaryOpExprNode::UnaryOpExprNode(const soul::ast::SourcePos& sourcePos_, Operator op_, Node* child_) : UnaryNode(NodeKind::unaryOpExprNode, sourcePos_, child_), op(op_)
{
}

Node* UnaryOpExprNode::Clone() const
{
    return new UnaryOpExprNode(GetSourcePos(), op, Child()->Clone());
}

void UnaryOpExprNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> UnaryOpExprNode::Write(CodeFormatter& formatter)
{
    std::expected<bool, int> rv = formatter.Write(OperatorStr(op));
    if (!rv) return std::unexpected<int>(rv.error());
    return Child()->Write(formatter);
}

std::string UnaryOpExprNode::ToString() const
{
    return OperatorStr(op) + Child()->ToString();
}

SizeOfNode::SizeOfNode(const soul::ast::SourcePos& sourcePos_, Node* child_, bool parens_) : UnaryNode(NodeKind::sizeOfNode, sourcePos_, child_), parens(parens_)
{
}

Node* SizeOfNode::Clone() const
{
    return new SizeOfNode(GetSourcePos(), Child()->Clone(), parens);
}

void SizeOfNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> SizeOfNode::Write(CodeFormatter& formatter)
{
    std::expected<bool, int> rv = formatter.Write("sizeof");
    if (!rv) return std::unexpected<int>(rv.error());
    if (parens)
    {
        rv = formatter.Write("(");
        if (!rv) return std::unexpected<int>(rv.error());
    }
    else
    {
        rv = formatter.Write(" ");
        if (!rv) return std::unexpected<int>(rv.error());
    }
    rv = Child()->Write(formatter);
    if (!rv) return std::unexpected<int>(rv.error());
    if (parens)
    {
        rv = formatter.Write(")");
        if (!rv) return std::unexpected<int>(rv.error());
    }
    return std::expected<bool, int>(true);
}

std::string SizeOfNode::ToString() const
{
    std::string str = "sizeof";
    if (parens)
    {
        str.append(1, '(');
    }
    else
    {
        str.append(1, ' ');
    }
    str.append(Child()->ToString());
    if (parens)
    {
        str.append(1, ')');
    }
    return str;
}

CastNode::CastNode(const soul::ast::SourcePos& sourcePos_, Node* type_, Node* child_) : UnaryNode(NodeKind::castNode, sourcePos_, child_), type(type_)
{
    type->SetParent(this);
}

Node* CastNode::Clone() const
{
    return new CastNode(GetSourcePos(), type->Clone(), Child()->Clone());
}

void CastNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> CastNode::Write(CodeFormatter& formatter)
{
    std::expected<bool, int> rv = formatter.Write("(");
    if (!rv) return std::unexpected<int>(rv.error());
    rv = type->Write(formatter);
    if (!rv) return std::unexpected<int>(rv.error());
    rv = formatter.Write(")");
    if (!rv) return std::unexpected<int>(rv.error());
    return Child()->Write(formatter);
}

std::string CastNode::ToString() const
{
    return "(" + type->ToString() + ")" + Child()->ToString();
}

BinaryOpExprNode::BinaryOpExprNode(const soul::ast::SourcePos& sourcePos_, Operator op_, Node* left_, Node* right_) :
    BinaryNode(NodeKind::binaryOpExprNode, sourcePos_, left_, right_), op(op_)
{
}

Node* BinaryOpExprNode::Clone() const
{
    return new BinaryOpExprNode(GetSourcePos(), op, Left()->Clone(), Right()->Clone());
}

void BinaryOpExprNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> BinaryOpExprNode::Write(CodeFormatter& formatter)
{
    std::expected<bool, int> rv = Left()->Write(formatter);
    if (!rv) return std::unexpected<int>(rv.error());
    rv = formatter.Write(" ");
    if (!rv) return std::unexpected<int>(rv.error());
    rv = formatter.Write(OperatorStr(op));
    if (!rv) return std::unexpected<int>(rv.error());
    rv = formatter.Write(" ");
    if (!rv) return std::unexpected<int>(rv.error());
    return Right()->Write(formatter);
}

std::string BinaryOpExprNode::ToString() const
{
    return Left()->ToString() + " " + OperatorStr(op) + " " + Right()->ToString();
}

ConditionalNode::ConditionalNode(const soul::ast::SourcePos& sourcePos_, Node* condition_, Node* thenExpr_, Node* elseExpr_) :
    Node(NodeKind::conditionalNode, sourcePos_), condition(condition_), thenExpr(thenExpr_), elseExpr(elseExpr_)
{
    condition->SetParent(this);
    thenExpr->SetParent(this);
    elseExpr->SetParent(this);
}

Node* ConditionalNode::Clone() const
{
    return new ConditionalNode(GetSourcePos(), condition->Clone(), thenExpr->Clone(), elseExpr->Clone());
}

void ConditionalNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> ConditionalNode::Write(CodeFormatter& formatter)
{
    std::expected<bool, int> rv = condition->Write(formatter);
    if (!rv) return std::unexpected<int>(rv.error());
    rv = formatter.Write(" ? ");
    if (!rv) return std::unexpected<int>(rv.error());
    rv = thenExpr->Write(formatter);
    if (!rv) return std::unexpected<int>(rv.error());
    rv = formatter.Write(" : ");
    return elseExpr->Write(formatter);
}

std::string ConditionalNode::ToString() const
{
    return condition->ToString() + " ? " + thenExpr->ToString() + " : " + elseExpr->ToString();
}

NewNode::NewNode(const soul::ast::SourcePos& sourcePos_, bool global_) : Node(NodeKind::newNode, sourcePos_), global(global_), parens(false), addToPlacement(false), addToInitializer(false)
{
}

void NewNode::Add(Node* node)
{
    node->SetParent(this);
    if (addToPlacement)
    {
        placement.push_back(std::unique_ptr<Node>(node));
    }
    else if (addToInitializer)
    {
        initializer.push_back(std::unique_ptr<Node>(node));
    }
}

void NewNode::SetTypeId(Node* typeId_)
{
    typeId.reset(typeId_);
    typeId->SetParent(this);
}

Node* NewNode::Clone() const
{
    NewNode* clone = new NewNode(GetSourcePos(), global);
    if (typeId)
    {
        clone->SetTypeId(typeId->Clone());
    }
    clone->BeginAddToPlacement();
    for (const auto& node : placement)
    {
        clone->Add(node->Clone());
    }
    clone->EndAddToPlacement();
    clone->BeginAddToInitializer();
    for (const auto& node : initializer)
    {
        clone->Add(node->Clone());
    }
    clone->EndAddToInitializer();
    return clone;
}

void NewNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> NewNode::Write(CodeFormatter& formatter)
{
    if (global)
    {
        std::expected<bool, int> rv = formatter.Write("::");
        if (!rv) return std::unexpected<int>(rv.error());
    }
    std::expected<bool, int> rv = formatter.Write("new");
    if (!rv) return std::unexpected<int>(rv.error());
    if (!placement.empty())
    {
        rv = formatter.Write("(");
        if (!rv) return std::unexpected<int>(rv.error());
        bool first = true;
        for (const auto& node : placement)
        {
            if (first)
            {
                first = false;
            }
            else
            {
                rv = formatter.Write(", ");
                if (!rv) return std::unexpected<int>(rv.error());
            }
            rv = node->Write(formatter);
            if (!rv) return std::unexpected<int>(rv.error());
        }
        rv = formatter.Write(")");
        if (!rv) return std::unexpected<int>(rv.error());
    }
    if (parens)
    {
        rv = formatter.Write("(");
        if (!rv) return std::unexpected<int>(rv.error());
    }
    rv = formatter.Write(" ");
    if (!rv) return std::unexpected<int>(rv.error());
    rv = typeId->Write(formatter);
    if (!rv) return std::unexpected<int>(rv.error());
    if (parens)
    {
        rv = formatter.Write(")");
        if (!rv) return std::unexpected<int>(rv.error());
    }
    if (!initializer.empty())
    {
        rv = formatter.Write("(");
        if (!rv) return std::unexpected<int>(rv.error());
        bool first = true;
        for (const auto& node : initializer)
        {
            if (first)
            {
                first = false;
            }
            else
            {
                rv = formatter.Write(", ");
                if (!rv) return std::unexpected<int>(rv.error());
            }
            rv = node->Write(formatter);
            if (!rv) return std::unexpected<int>(rv.error());
        }
        rv = formatter.Write(")");
        if (!rv) return std::unexpected<int>(rv.error());
    }
    return std::expected<bool, int>(true);
}

std::string NewNode::ToString() const
{
    std::string str;
    if (global)
    {
        str.append("::");
    }
    str.append("new");
    if (!placement.empty())
    {
        str.append("(");
        bool first = true;
        for (const auto& node : placement)
        {
            if (first)
            {
                first = false;
            }
            else
            {
                str.append(", ");
            }
            str.append(node->ToString());
        }
        str.append(")");
    }
    if (parens)
    {
        str.append("(");
    }
    str.append(" ");
    str.append(typeId->ToString());
    if (parens)
    {
        str.append(")");
    }
    if (!initializer.empty())
    {
        str.append("(");
        bool first = true;
        for (const auto& node : initializer)
        {
            if (first)
            {
                first = false;
            }
            else
            {
                str.append(", ");
            }
            str.append(node->ToString());
        }
        str.append(")");
    }
    return str;
}

DeleteNode::DeleteNode(const soul::ast::SourcePos& sourcePos_, bool global_, bool isArray_, Node* child_) :
    UnaryNode(NodeKind::deleteNode, sourcePos_, child_), global(global_), isArray(isArray_)
{
}

Node* DeleteNode::Clone() const
{
    return new DeleteNode(GetSourcePos(), global, isArray, Child()->Clone());
}

void DeleteNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> DeleteNode::Write(CodeFormatter& formatter)
{
    if (global)
    {
        std::expected<bool, int> rv = formatter.Write("::");
        if (!rv) return std::unexpected<int>(rv.error());
    }
    std::expected<bool, int> rv = formatter.Write("delete");
    if (!rv) return std::unexpected<int>(rv.error());
    if (isArray)
    {
        rv = formatter.Write("[]");
        if (!rv) return std::unexpected<int>(rv.error());
    }
    rv = formatter.Write(" ");
    if (!rv) return std::unexpected<int>(rv.error());
    return Child()->Write(formatter);
}

std::string DeleteNode::ToString() const
{
    std::string str;
    if (global)
    {
        str.append("::");
    }
    str.append("delete");
    if (isArray)
    {
        str.append("[]");
    }
    str.append(1, ' ');
    str.append(Child()->ToString());
    return str;
}

ParenExprNode::ParenExprNode(const soul::ast::SourcePos& sourcePos_, Node* child_) : UnaryNode(NodeKind::parenExprNode, sourcePos_, child_)
{
}

Node* ParenExprNode::Clone() const
{
    return new ParenExprNode(GetSourcePos(), Child()->Clone());
}

void ParenExprNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> ParenExprNode::Write(CodeFormatter& formatter)
{
    std::expected<bool, int> rv = formatter.Write("(");
    if (!rv) return std::unexpected<int>(rv.error());
    rv = Child()->Write(formatter);
    if (!rv) return std::unexpected<int>(rv.error());
    return formatter.Write(")");
}

std::string ParenExprNode::ToString() const
{
    return "(" + Child()->ToString() + ")";
}

LiteralNode::LiteralNode(const soul::ast::SourcePos& sourcePos_, const std::string& rep_) : Node(NodeKind::literalNode, sourcePos_), rep(rep_)
{
}

Node* LiteralNode::Clone() const
{
    return new LiteralNode(GetSourcePos(), rep);
}

void LiteralNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> LiteralNode::Write(CodeFormatter& formatter)
{
    return formatter.Write(rep);
}

StatementNode::StatementNode(NodeKind kind_, const soul::ast::SourcePos& sourcePos_) : Node(kind_, sourcePos_)
{
}

LabeledStatementNode::LabeledStatementNode(const soul::ast::SourcePos& sourcePos_, const std::string& label_, StatementNode* stmt_) :
    StatementNode(NodeKind::labeledStatementNode, sourcePos_), label(label_), stmt(stmt_)
{
    stmt->SetParent(this);
}

Node* LabeledStatementNode::Clone() const
{
    return new LabeledStatementNode(GetSourcePos(), label, static_cast<StatementNode*>(stmt->Clone()));
}

void LabeledStatementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> LabeledStatementNode::Write(CodeFormatter& formatter)
{
    std::expected<bool, int >rv = formatter.Write(label);
    if (!rv) return std::unexpected<int>(rv.error());
    rv = formatter.Write(" : ");
    if (!rv) return std::unexpected<int>(rv.error());
    return stmt->Write(formatter);
}

CaseStatementNode::CaseStatementNode(const soul::ast::SourcePos& sourcePos_, Node* caseExpr_, StatementNode* stmt_) :
    StatementNode(NodeKind::caseStatementNode, sourcePos_), caseExpr(caseExpr_), stmt(stmt_)
{
    caseExpr->SetParent(this);
    stmt->SetParent(this);
}

Node* CaseStatementNode::Clone() const
{
    return new CaseStatementNode(GetSourcePos(), caseExpr->Clone(), static_cast<StatementNode*>(stmt->Clone()));
}

void CaseStatementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> CaseStatementNode::Write(CodeFormatter& formatter)
{
    std::expected<bool, int> rv = formatter.Write("case ");
    if (!rv) return std::unexpected<int>(rv.error());
    rv = caseExpr->Write(formatter);
    if (!rv) return std::unexpected<int>(rv.error());
    rv = formatter.Write(": ");
    if (!rv) return std::unexpected<int>(rv.error());
    return stmt->Write(formatter);
}

DefaultStatementNode::DefaultStatementNode(const soul::ast::SourcePos& sourcePos_, StatementNode* stmt_) : StatementNode(NodeKind::defaultStatementNode, sourcePos_), stmt(stmt_)
{
    stmt->SetParent(this);
}

Node* DefaultStatementNode::Clone() const
{
    return new DefaultStatementNode(GetSourcePos(), static_cast<StatementNode*>(stmt->Clone()));
}

void DefaultStatementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> DefaultStatementNode::Write(CodeFormatter& formatter)
{
    std::expected<bool, int> rv = formatter.Write("default: ");
    if (!rv) return std::unexpected<int>(rv.error());
    return stmt->Write(formatter);
}

EmptyStatementNode::EmptyStatementNode(const soul::ast::SourcePos& sourcePos_) : StatementNode(NodeKind::emptyStatementNode, sourcePos_)
{
}

Node* EmptyStatementNode::Clone() const
{
    return new EmptyStatementNode(GetSourcePos());
}

void EmptyStatementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> EmptyStatementNode::Write(CodeFormatter& formatter)
{
    return formatter.WriteLine(";");
}

ExpressionStatementNode::ExpressionStatementNode(const soul::ast::SourcePos& sourcePos_, Node* expr_) : StatementNode(NodeKind::expressionStatementNode, sourcePos_), expr(expr_)
{
    expr->SetParent(this);
}

Node* ExpressionStatementNode::Clone() const
{
    return new ExpressionStatementNode(GetSourcePos(), expr->Clone());
}

void ExpressionStatementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> ExpressionStatementNode::Write(CodeFormatter& formatter)
{
    std::expected<bool, int> rv = expr->Write(formatter);
    if (!rv) return std::unexpected<int>(rv.error());
    return formatter.WriteLine(";");
}

CompoundStatementNode::CompoundStatementNode(const soul::ast::SourcePos& sourcePos_) : StatementNode(NodeKind::compoundStatementNode, sourcePos_)
{
}

void CompoundStatementNode::InsertFront(StatementNode* stmt)
{
    stmt->SetParent(this);
    statements.insert(statements.begin(), std::unique_ptr<StatementNode>(stmt));
}

void CompoundStatementNode::Add(StatementNode* stmt)
{
    stmt->SetParent(this);
    statements.push_back(std::unique_ptr<StatementNode>(stmt));
}

void CompoundStatementNode::Replace(Node* node, Node* replacement)
{
    for (auto& stmt : statements)
    {
        Node* s = stmt.get();
        if (s == node)
        {
            stmt.reset(static_cast<StatementNode*>(replacement));
        }
    }
}

Node* CompoundStatementNode::Clone() const
{
    CompoundStatementNode* clone = new CompoundStatementNode(GetSourcePos());
    for (const auto& stmt : statements)
    {
        clone->Add(static_cast<StatementNode*>(stmt->Clone()));
    }
    return clone;
}

void CompoundStatementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> CompoundStatementNode::Write(CodeFormatter& formatter)
{
    std::expected<bool, int> rv = formatter.WriteLine("{");
    if (!rv) return std::unexpected<int>(rv.error());
    formatter.IncIndent();
    for (const auto& stmt : statements)
    {
        rv = stmt->Write(formatter);
        if (!rv) return std::unexpected<int>(rv.error());
    }
    formatter.DecIndent();
    return formatter.WriteLine("}");
}

IfStatementNode::IfStatementNode(const soul::ast::SourcePos& sourcePos_, Node* cond_, StatementNode* thenStmt_, StatementNode* elseStmt_) :
    StatementNode(NodeKind::ifStatementNode, sourcePos_), cond(cond_), thenStmt(thenStmt_), elseStmt(elseStmt_)
{
    cond->SetParent(this);
    thenStmt->SetParent(this);
    if (elseStmt)
    {
        elseStmt->SetParent(this);
    }
}

Node* IfStatementNode::Clone() const
{
    StatementNode* clonedElseStmt = nullptr;
    if (elseStmt)
    {
        clonedElseStmt = static_cast<StatementNode*>(elseStmt->Clone());
    }
    return new IfStatementNode(GetSourcePos(), cond->Clone(), static_cast<StatementNode*>(thenStmt->Clone()), clonedElseStmt);
}

void IfStatementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> IfStatementNode::Write(CodeFormatter& formatter)
{
    std::expected<bool, int> rv = formatter.Write("if (");
    if (!rv) return std::unexpected<int>(rv.error());
    rv = cond->Write(formatter);
    if (!rv) return std::unexpected<int>(rv.error());
    rv = formatter.Write(")");
    if (!rv) return std::unexpected<int>(rv.error());
    if (thenStmt->IsCompoundStatementNode())
    {
        formatter.NewLine();
    }
    else
    {
        rv = formatter.Write(" ");
        if (!rv) return std::unexpected<int>(rv.error());
    }
    rv = thenStmt->Write(formatter);
    if (!rv) return std::unexpected<int>(rv.error());
    if (elseStmt)
    {
        rv = formatter.Write("else");
        if (!rv) return std::unexpected<int>(rv.error());
        if (elseStmt->IsCompoundStatementNode())
        {
            formatter.NewLine();
        }
        else
        {
            rv = formatter.Write(" ");
            if (!rv) return std::unexpected<int>(rv.error());
        }
        rv = elseStmt->Write(formatter);
        if (!rv) return std::unexpected<int>(rv.error());
    }
    return std::expected<bool, int>(true);
}

SwitchStatementNode::SwitchStatementNode(const soul::ast::SourcePos& sourcePos_, Node* cond_, StatementNode* stmt_) :
    StatementNode(NodeKind::switchStatementNode, sourcePos_), cond(cond_), stmt(stmt_)
{
    cond->SetParent(this);
    stmt->SetParent(this);
}

Node* SwitchStatementNode::Clone() const
{
    return new SwitchStatementNode(GetSourcePos(), cond->Clone(), static_cast<StatementNode*>(stmt->Clone()));
}

void SwitchStatementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> SwitchStatementNode::Write(CodeFormatter& formatter)
{
    std::expected<bool, int> rv = formatter.Write("switch (");
    if (!rv) return std::unexpected<int>(rv.error());
    rv = cond->Write(formatter);
    if (!rv) return std::unexpected<int>(rv.error());
    rv = formatter.WriteLine(")");
    if (!rv) return std::unexpected<int>(rv.error());
    return stmt->Write(formatter);
}

WhileStatementNode::WhileStatementNode(const soul::ast::SourcePos& sourcePos_, Node* cond_, StatementNode* stmt_) :
    StatementNode(NodeKind::whileStatementNode, sourcePos_), cond(cond_), stmt(stmt_)
{
    cond->SetParent(this);
    stmt->SetParent(this);
}

Node* WhileStatementNode::Clone() const
{
    return new WhileStatementNode(GetSourcePos(), cond->Clone(), static_cast<StatementNode*>(stmt->Clone()));
}

void WhileStatementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> WhileStatementNode::Write(CodeFormatter& formatter)
{
    std::expected<bool, int> rv = formatter.Write("while (");
    if (!rv) return std::unexpected<int>(rv.error());
    rv = cond->Write(formatter);
    if (!rv) return std::unexpected<int>(rv.error());
    rv = formatter.Write(")");
    if (!rv) return std::unexpected<int>(rv.error());
    if (stmt->IsCompoundStatementNode())
    {
        formatter.NewLine();
    }
    else
    {
        rv = formatter.Write(" ");
        if (!rv) return std::unexpected<int>(rv.error());
    }
    return stmt->Write(formatter);
}

DoStatementNode::DoStatementNode(const soul::ast::SourcePos& sourcePos_, Node* cond_, StatementNode* stmt_) :
    StatementNode(NodeKind::doStatementNode, sourcePos_), cond(cond_), stmt(stmt_)
{
    cond->SetParent(this);
    stmt->SetParent(this);
}

Node* DoStatementNode::Clone() const
{
    return new DoStatementNode(GetSourcePos(), cond->Clone(), static_cast<StatementNode*>(stmt->Clone()));
}

void DoStatementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> DoStatementNode::Write(CodeFormatter& formatter)
{
    std::expected<bool, int> rv = formatter.Write("do");
    if (!rv) return std::unexpected<int>(rv.error());
    if (stmt->IsCompoundStatementNode())
    {
        formatter.NewLine();
    }
    else
    {
        rv = formatter.Write(" ");
        if (!rv) return std::unexpected<int>(rv.error());
    }
    rv = stmt->Write(formatter);
    if (!rv) return std::unexpected<int>(rv.error());
    rv = formatter.Write("while (");
    if (!rv) return std::unexpected<int>(rv.error());
    rv = cond->Write(formatter);
    if (!rv) return std::unexpected<int>(rv.error());
    return formatter.WriteLine(");");
}

ForStatementNode::ForStatementNode(const soul::ast::SourcePos& sourcePos_, Node* init_, Node* cond_, Node* iter_, StatementNode* stmt_) :
    StatementNode(NodeKind::forStatementNode, sourcePos_), init(init_), cond(cond_), iter(iter_), stmt(stmt_)
{
    if (init)
    {
        init->SetParent(this);
    }
    if (cond)
    {
        cond->SetParent(this);
    }
    if (iter)
    {
        iter->SetParent(this);
    }
    stmt->SetParent(this);
}

Node* ForStatementNode::Clone() const
{
    Node* clonedInit = nullptr;
    if (init)
    {
        clonedInit = init->Clone();
    }
    Node* clonedCond = nullptr;
    if (cond)
    {
        clonedCond = cond->Clone();
    }
    Node* clonedIter = nullptr;
    if (iter)
    {
        clonedIter = iter->Clone();
    }
    return new ForStatementNode(GetSourcePos(), clonedInit, clonedCond, clonedIter, static_cast<StatementNode*>(stmt->Clone()));
}

void ForStatementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> ForStatementNode::Write(CodeFormatter& formatter)
{
    std::expected<bool, int> rv = formatter.Write("for (");
    if (!rv) return std::unexpected<int>(rv.error());
    if (init)
    {
        rv = init->Write(formatter);
        if (!rv) return std::unexpected<int>(rv.error());
    }
    rv = formatter.Write("; ");
    if (!rv) return std::unexpected<int>(rv.error());
    if (cond)
    {
        rv = cond->Write(formatter);
        if (!rv) return std::unexpected<int>(rv.error());
    }
    rv = formatter.Write("; ");
    if (!rv) return std::unexpected<int>(rv.error());
    if (iter)
    {
        rv = iter->Write(formatter);
        if (!rv) return std::unexpected<int>(rv.error());
    }
    rv = formatter.Write(")");
    if (!rv) return std::unexpected<int>(rv.error());
    if (stmt->IsCompoundStatementNode())
    {
        formatter.NewLine();
    }
    else
    {
        rv = formatter.Write(" ");
        if (!rv) return std::unexpected<int>(rv.error());
    }
    return stmt->Write(formatter);
}

BreakStatementNode::BreakStatementNode(const soul::ast::SourcePos& sourcePos_) : StatementNode(NodeKind::breakStatementNode, sourcePos_)
{
}

Node* BreakStatementNode::Clone() const
{
    return new BreakStatementNode(GetSourcePos());
}

void BreakStatementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> BreakStatementNode::Write(CodeFormatter& formatter)
{
    return formatter.WriteLine("break;");
}

ContinueStatementNode::ContinueStatementNode(const soul::ast::SourcePos& sourcePos_) : StatementNode(NodeKind::continueStatementNode, sourcePos_)
{
}

Node* ContinueStatementNode::Clone() const
{
    return new ContinueStatementNode(GetSourcePos());
}

void ContinueStatementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> ContinueStatementNode::Write(CodeFormatter& formatter)
{
    return formatter.WriteLine("continue;");
}

GotoStatementNode::GotoStatementNode(const soul::ast::SourcePos& sourcePos_, const std::string& target_) : StatementNode(NodeKind::gotoStatementNode, sourcePos_), target(target_)
{
}

Node* GotoStatementNode::Clone() const
{
    return new GotoStatementNode(GetSourcePos(), target);
}

void GotoStatementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> GotoStatementNode::Write(CodeFormatter& formatter)
{
    std::expected<bool, int> rv = formatter.Write("goto ");
    if (!rv) return std::unexpected<int>(rv.error());
    rv = formatter.Write(target);
    if (!rv) return std::unexpected<int>(rv.error());
    return formatter.WriteLine(";");
}

ReturnStatementNode::ReturnStatementNode(const soul::ast::SourcePos& sourcePos_, Node* expr_) : StatementNode(NodeKind::returnStatementNode, sourcePos_), expr(expr_)
{
    if (expr)
    {
        expr->SetParent(this);
    }
}

void ReturnStatementNode::SetExpr(Node* expr_)
{
    expr.reset(expr_);
}

Node* ReturnStatementNode::Clone() const
{
    Node* clonedExpr = nullptr;
    if (expr)
    {
        clonedExpr = expr->Clone();
    }
    return new ReturnStatementNode(GetSourcePos(), clonedExpr);
}

void ReturnStatementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> ReturnStatementNode::Write(CodeFormatter& formatter)
{
    std::expected<bool, int> rv = formatter.Write("return");
    if (!rv) return std::unexpected<int>(rv.error());
    if (expr)
    {
        rv = formatter.Write(" ");
        if (!rv) return std::unexpected<int>(rv.error());
        rv = expr->Write(formatter);
        if (!rv) return std::unexpected<int>(rv.error());
    }
    return formatter.WriteLine(";");
}

ConditionWithDeclaratorNode::ConditionWithDeclaratorNode(const soul::ast::SourcePos& sourcePos_, TypeIdNode* type_, const std::string& declarator_, Node* expression_) :
    Node(NodeKind::conditionWithDeclaratorNode, sourcePos_), type(type_), declarator(declarator_), expression(expression_)
{
    type->SetParent(this);
    expression->SetParent(this);
}

Node* ConditionWithDeclaratorNode::Clone() const
{
    return new ConditionWithDeclaratorNode(GetSourcePos(), static_cast<TypeIdNode*>(type->Clone()), declarator, expression->Clone());
}

void ConditionWithDeclaratorNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> ConditionWithDeclaratorNode::Write(CodeFormatter& formatter)
{
    std::expected<bool, int> rv = type->Write(formatter);
    if (!rv) return std::unexpected<int>(rv.error());
    rv = formatter.Write(" " + declarator + " = ");
    if (!rv) return std::unexpected<int>(rv.error());
    return expression->Write(formatter);
}

ForRangeDeclarationNode::ForRangeDeclarationNode(const soul::ast::SourcePos& sourcePos_) :
    Node(NodeKind::forRangeDeclarationNode, sourcePos_), declaration(new SimpleDeclarationNode(sourcePos_)), declarator()
{
    declaration->SetParent(this);
}

void ForRangeDeclarationNode::SetDeclarator(const std::string& declarator_)
{
    declarator = declarator_;
}

Node* ForRangeDeclarationNode::Clone() const
{
    ForRangeDeclarationNode* clone = new ForRangeDeclarationNode(GetSourcePos());
    clone->SetDeclarator(declarator);
    return clone;
}

void ForRangeDeclarationNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> ForRangeDeclarationNode::Write(CodeFormatter& formatter)
{
    std::expected<bool, int> rv = declaration->Write(formatter);
    if (!rv) return std::unexpected<int>(rv.error());
    rv = formatter.Write(" ");
    if (!rv) return std::unexpected<int>(rv.error());
    return formatter.Write(declarator);
}

RangeForStatementNode::RangeForStatementNode(const soul::ast::SourcePos& sourcePos_, ForRangeDeclarationNode* declaration_, Node* container_, StatementNode* stmt_) :
    StatementNode(NodeKind::rangeForStatementNode, sourcePos_), declaration(declaration_), container(container_), stmt(stmt_)
{
    declaration->SetParent(this);
    container->SetParent(this);
    stmt->SetParent(this);
}

Node* RangeForStatementNode::Clone() const
{
    return new RangeForStatementNode(GetSourcePos(), static_cast<ForRangeDeclarationNode*>(declaration->Clone()), container->Clone(), static_cast<StatementNode*>(stmt->Clone()));
}

void RangeForStatementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> RangeForStatementNode::Write(CodeFormatter& formatter)
{
    std::expected<bool, int> rv = formatter.Write("for (");
    if (!rv) return std::unexpected<int>(rv.error());
    rv = declaration->Write(formatter);
    if (!rv) return std::unexpected<int>(rv.error());
    rv = formatter.Write(" : ");
    if (!rv) return std::unexpected<int>(rv.error());
    rv = container->Write(formatter);
    if (!rv) return std::unexpected<int>(rv.error());
    rv = formatter.Write(")");
    if (!rv) return std::unexpected<int>(rv.error());
    if (stmt->IsCompoundStatementNode())
    {
        formatter.NewLine();
    }
    else
    {
        rv = formatter.Write(" ");
        if (!rv) return std::unexpected<int>(rv.error());
    }
    return stmt->Write(formatter);
}

DeclarationStatementNode::DeclarationStatementNode(const soul::ast::SourcePos& sourcePos_, Node* declaration_) :
    StatementNode(NodeKind::declarationStatementNode, sourcePos_), declaration(declaration_)
{
    declaration->SetParent(this);
}

Node* DeclarationStatementNode::Clone() const
{
    return new DeclarationStatementNode(GetSourcePos(), declaration->Clone());
}

void DeclarationStatementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> DeclarationStatementNode::Write(CodeFormatter& formatter)
{
    std::expected<bool, int> rv = declaration->Write(formatter);
    if (!rv) return std::unexpected<int>(rv.error());
    return formatter.WriteLine(";");
}

IfdefStatementNode::IfdefStatementNode(const soul::ast::SourcePos& sourcePos_, Node* symbol_) : StatementNode(NodeKind::ifdefStatementNode, sourcePos_), symbol(symbol_)
{
    symbol->SetParent(this);
}

Node* IfdefStatementNode::Clone() const
{
    return new IfdefStatementNode(GetSourcePos(), symbol->Clone());
}

void IfdefStatementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> IfdefStatementNode::Write(CodeFormatter& formatter)
{
    std::expected<bool, int> rv = formatter.Write("#ifdef ");
    if (!rv) return std::unexpected<int>(rv.error());
    rv = symbol->Write(formatter);
    if (!rv) return std::unexpected<int>(rv.error());
    formatter.WriteLine();
    return std::expected<bool, int>(true);
}

EndIfStatementNode::EndIfStatementNode(const soul::ast::SourcePos& sourcePos_) : StatementNode(NodeKind::endIfStatementNode, sourcePos_)
{
}

Node* EndIfStatementNode::Clone() const
{
    return new EndIfStatementNode(GetSourcePos());
}

void EndIfStatementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> EndIfStatementNode::Write(CodeFormatter& formatter)
{
    return formatter.WriteLine("#endif");
}

AssignInitNode::AssignInitNode(const soul::ast::SourcePos& sourcePos_, Node* assignmentExpr_) : Node(NodeKind::assignInitNode, sourcePos_), assignmentExpr(assignmentExpr_)
{
    if (assignmentExpr)
    {
        assignmentExpr->SetParent(this);
    }
}

void AssignInitNode::Add(AssignInitNode* subInit)
{
    subInit->SetParent(this);
    subInits.push_back(std::unique_ptr<AssignInitNode>(subInit));
}

std::expected<bool, int> AssignInitNode::Write(CodeFormatter& formatter)
{
    if (assignmentExpr)
    {
        std::expected<bool, int> rv = assignmentExpr->Write(formatter);
        if (!rv) return std::unexpected<int>(rv.error());
    }
    else
    {
        std::expected<bool, int> rv = formatter.Write("{ ");
        if (!rv) return std::unexpected<int>(rv.error());
        bool first = true;
        for (const auto& subInit : subInits)
        {
            if (first)
            {
                first = false;
            }
            else
            {
                rv = formatter.Write(", ");
                if (!rv) return std::unexpected<int>(rv.error());
            }
            rv = subInit->Write(formatter);
            if (!rv) return std::unexpected<int>(rv.error());
        }
        rv = formatter.Write(" }");
        if (!rv) return std::unexpected<int>(rv.error());
    }
    return std::expected<bool, int>(true);
}

std::string AssignInitNode::ToString() const
{
    if (assignmentExpr)
    {
        return assignmentExpr->ToString();
    }
    else
    {
        std::string str;
        str.append("{ ");
        bool first = true;
        for (const auto& subInit : subInits)
        {
            if (first)
            {
                first = false;
            }
            else
            {
                str.append(", ");
            }
            str.append(subInit->ToString());
        }
        str.append(" }");
        return str;
    }
}

Node* AssignInitNode::Clone() const
{
    Node* clonedAssignmentExprNode = nullptr;
    if (assignmentExpr)
    {
        clonedAssignmentExprNode = assignmentExpr->Clone();
    }
    AssignInitNode* clone = new AssignInitNode(GetSourcePos(), clonedAssignmentExprNode);
    for (const auto& subInit : subInits)
    {
        clone->Add(static_cast<AssignInitNode*>(subInit->Clone()));
    }
    return clone;
}

void AssignInitNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

InitializerNode::InitializerNode(const soul::ast::SourcePos& sourcePos_, AssignInitNode* assignInit_) : Node(NodeKind::initializerNode, sourcePos_), assignInit(assignInit_)
{
    if (assignInit)
    {
        assignInit->SetParent(this);
    }
}

void InitializerNode::Add(Node* expr)
{
    expr->SetParent(this);
    expressionList.push_back(std::unique_ptr<Node>(expr));
}

std::expected<bool, int> InitializerNode::Write(CodeFormatter& formatter)
{
    if (assignInit)
    {
        std::expected<bool, int> rv = formatter.Write(" = ");
        if (!rv) return std::unexpected<int>(rv.error());
        rv = assignInit->Write(formatter);
        if (!rv) return std::unexpected<int>(rv.error());
    }
    else if (!expressionList.empty())
    {
        std::expected<bool, int> rv = formatter.Write("(");
        if (!rv) return std::unexpected<int>(rv.error());
        bool first = true;
        for (const auto& expr : expressionList)
        {
            if (first)
            {
                first = false;
            }
            else
            {
                rv = formatter.Write(", ");
                if (!rv) return std::unexpected<int>(rv.error());
            }
            rv = expr->Write(formatter);
            if (!rv) return std::unexpected<int>(rv.error());
        }
        rv = formatter.Write(")");
        if (!rv) return std::unexpected<int>(rv.error());
    }
    return std::expected<bool, int>(true);
}

std::string InitializerNode::ToString() const
{
    std::string str;
    if (assignInit)
    {
        return " = " + assignInit->ToString();
    }
    else if (!expressionList.empty())
    {
        str.append("(");
        bool first = true;
        for (const auto& expr : expressionList)
        {
            if (first)
            {
                first = false;
            }
            else
            {
                str.append(", ");
            }
            str.append(expr->ToString());
        }
        str.append(")");
    }
    return str;
}

Node* InitializerNode::Clone() const
{
    AssignInitNode* clonedAssignInitNode = nullptr;
    if (assignInit)
    {
        clonedAssignInitNode = static_cast<AssignInitNode*>(assignInit->Clone());
    }
    InitializerNode* clone = new InitializerNode(GetSourcePos(), clonedAssignInitNode);
    for (const auto& expr : expressionList)
    {
        clone->Add(expr->Clone());
    }
    return clone;
}

void InitializerNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

InitDeclaratorNode::InitDeclaratorNode(const soul::ast::SourcePos& sourcePos_, const std::string& declarator_, InitializerNode* initializer_) :
    Node(NodeKind::initDeclaratorNode, sourcePos_), declarator(declarator_), initializer(initializer_)
{
    if (initializer)
    {
        initializer->SetParent(this);
    }
}

std::expected<bool, int> InitDeclaratorNode::Write(CodeFormatter& formatter)
{
    std::expected<bool, int> rv = formatter.Write(declarator);
    if (!rv) return std::unexpected<int>(rv.error());
    if (initializer)
    {
        rv = initializer->Write(formatter);
        if (!rv) return std::unexpected<int>(rv.error());
    }
    return std::expected<bool, int>(true);
}

std::string InitDeclaratorNode::ToString() const
{
    std::string str;
    str.append(declarator);
    if (initializer)
    {
        str.append(initializer->ToString());
    }
    return str;
}

Node* InitDeclaratorNode::Clone() const
{
    InitializerNode* clonedInitializer = nullptr;
    if (initializer)
    {
        clonedInitializer = static_cast<InitializerNode*>(initializer->Clone());
    }
    return new InitDeclaratorNode(GetSourcePos(), declarator, clonedInitializer);
}

void InitDeclaratorNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

InitDeclaratorListNode::InitDeclaratorListNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::initDeclaratorListNode, sourcePos_)
{
}

void InitDeclaratorListNode::Add(InitDeclaratorNode* initDeclarator)
{
    initDeclarator->SetParent(this);
    initDeclarators.push_back(std::unique_ptr<InitDeclaratorNode>(initDeclarator));
}

std::expected<bool, int> InitDeclaratorListNode::Write(CodeFormatter& formatter)
{
    bool first = true;
    for (const auto& initDeclarator : initDeclarators)
    {
        if (first)
        {
            first = false;
        }
        else
        {
            std::expected<bool, int> rv = formatter.Write(", ");
            if (!rv) return std::unexpected<int>(rv.error());
        }
        std::expected<bool, int> rv = initDeclarator->Write(formatter);
        if (!rv) return std::unexpected<int>(rv.error());
    }
    return std::expected<bool, int>(true);
}

std::string InitDeclaratorListNode::ToString() const
{
    std::string str;
    bool first = true;
    for (const auto& initDeclarator : initDeclarators)
    {
        if (first)
        {
            first = false;
        }
        else
        {
            str.append(", ");
        }
        str.append(initDeclarator->ToString());
    }
    return str;
}

Node* InitDeclaratorListNode::Clone() const
{
    InitDeclaratorListNode* clone = new InitDeclaratorListNode(GetSourcePos());
    for (const auto& initDeclarator : initDeclarators)
    {
        clone->Add(static_cast<InitDeclaratorNode*>(initDeclarator->Clone()));
    }
    return clone;
}

void InitDeclaratorListNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

DeclSpecifierNode::DeclSpecifierNode(NodeKind kind_, const soul::ast::SourcePos& sourcePos_, const std::string& name_) : Node(kind_, sourcePos_), name(name_)
{
}

void DeclSpecifierNode::SetName(const std::string& name_)
{
    name = name_;
}

TypedefNode::TypedefNode(const soul::ast::SourcePos& sourcePos_) : DeclSpecifierNode(NodeKind::typedefNode, sourcePos_, "typedef")
{
}

Node* TypedefNode::Clone() const
{
    return new TypedefNode(GetSourcePos());
}

void TypedefNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> TypedefNode::Write(CodeFormatter& formatter)
{
    return formatter.Write(Name());
}

std::string TypedefNode::ToString() const
{
    return Name();
}

TypeSpecifierNode::TypeSpecifierNode(const soul::ast::SourcePos& sourcePos_, const std::string& name_) :
    DeclSpecifierNode(NodeKind::typeSpecifierNode, sourcePos_, name_)
{
}

TypeSpecifierNode::TypeSpecifierNode(const soul::ast::SourcePos& sourcePos_, NodeKind kind_, const std::string& name_) :
    DeclSpecifierNode(kind_, sourcePos_, name_)
{
}

Node* TypeSpecifierNode::Clone() const
{
    return new TypeSpecifierNode(GetSourcePos(), Kind(), Name());
}

void TypeSpecifierNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> TypeSpecifierNode::Write(CodeFormatter& formatter)
{
    return formatter.Write(Name());
}

ConstNode::ConstNode(const soul::ast::SourcePos& sourcePos_) : TypeSpecifierNode(sourcePos_, NodeKind::constNode, "const")
{
}

Node* ConstNode::Clone() const
{
    return new ConstNode(GetSourcePos());
}

void ConstNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

VolatileNode::VolatileNode(const soul::ast::SourcePos& sourcePos_) : TypeSpecifierNode(sourcePos_, NodeKind::volatileNode, "volatile")
{
}

Node* VolatileNode::Clone() const
{
    return new VolatileNode(GetSourcePos());
}

void VolatileNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

TypeNameNode::TypeNameNode(const soul::ast::SourcePos& sourcePos_, const std::string& name_) :
    TypeSpecifierNode(sourcePos_, NodeKind::typeNameNode, name_), isTemplate(false)
{
}

void TypeNameNode::AddTemplateArgument(Node* templateArgument)
{
    templateArgument->SetParent(this);
    templateArguments.push_back(std::unique_ptr<Node>(templateArgument));
}

std::string TypeNameNode::ToString() const
{
    std::string str(Name());
    if (isTemplate)
    {
        str.append("<");
        bool first = true;
        for (const auto& templateArgument : templateArguments)
        {
            if (first)
            {
                first = false;
            }
            else
            {
                str.append(", ");
            }
            str.append(templateArgument->ToString());
        }
        str.append(">");
    }
    return str;
}

std::expected<bool, int> TypeNameNode::Write(CodeFormatter& formatter)
{
    return formatter.Write(ToString());
}

Node* TypeNameNode::Clone() const
{
    TypeNameNode* clone = new TypeNameNode(GetSourcePos(), Name());
    if (isTemplate)
    {
        clone->SetTemplate();
    }
    for (const auto& templateArg : templateArguments)
    {
        clone->AddTemplateArgument(templateArg->Clone());
    }
    return clone;
}

void TypeNameNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

TypeNode::TypeNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::typeNode, sourcePos_)
{
}

void TypeNode::Add(TypeSpecifierNode* typeSpecifier)
{
    typeSpecifier->SetParent(this);
    typeSpecifiers.push_back(std::unique_ptr<TypeSpecifierNode>(typeSpecifier));
}

std::string TypeNode::ToString() const
{
    std::string str;
    bool first = true;
    for (const auto& typeSpecifier : typeSpecifiers)
    {
        if (first)
        {
            first = false;
        }
        else
        {
            str.append(1, ' ');
        }
        str.append(typeSpecifier->ToString());
    }
    return str;
}

std::expected<bool, int> TypeNode::Write(CodeFormatter& formatter)
{
    return formatter.Write(ToString());
}

Node* TypeNode::Clone() const
{
    TypeNode* clone = new TypeNode(GetSourcePos());
    for (const auto& typeSpecifier : typeSpecifiers)
    {
        clone->Add(static_cast<TypeSpecifierNode*>(typeSpecifier->Clone()));
    }
    return clone;
}

void TypeNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

StorageClassSpecifierNode::StorageClassSpecifierNode(const soul::ast::SourcePos& sourcePos_, const std::string& name_) :
    DeclSpecifierNode(NodeKind::storageClassSpecifierNode, sourcePos_, name_)
{
}

Node* StorageClassSpecifierNode::Clone() const
{
    return new StorageClassSpecifierNode(GetSourcePos(), Name());
}

void StorageClassSpecifierNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> StorageClassSpecifierNode::Write(CodeFormatter& formatter)
{
    return formatter.Write(Name());
}

std::string StorageClassSpecifierNode::ToString() const
{
    return Name();
}

TypeIdNode::TypeIdNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::typeIdNode, sourcePos_)
{
}

void TypeIdNode::Add(TypeSpecifierNode* typeSpecifier)
{
    typeSpecifier->SetParent(this);
    typeSpecifiers.push_back(std::unique_ptr<TypeSpecifierNode>(typeSpecifier));
}

void TypeIdNode::SetDeclarator(const std::string& declarator_)
{
    declarator = declarator_;
}

Node* TypeIdNode::Clone() const
{
    TypeIdNode* clone = new TypeIdNode(GetSourcePos());
    clone->SetDeclarator(declarator);
    for (const auto& typeSpecifier : typeSpecifiers)
    {
        clone->Add(static_cast<TypeSpecifierNode*>(typeSpecifier->Clone()));
    }
    return clone;
}

void TypeIdNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> TypeIdNode::Write(CodeFormatter& formatter)
{
    bool first = true;
    for (const auto& typeSpecifier : typeSpecifiers)
    {
        if (first)
        {
            first = false;
        }
        else
        {
            std::expected<bool, int> rv = formatter.Write(" ");
            if (!rv) return std::unexpected<int>(rv.error());
        }
        std::expected<bool, int> rv = typeSpecifier->Write(formatter);
        if (!rv) return std::unexpected<int>(rv.error());
    }
    return formatter.Write(declarator);
}

std::expected<bool, int> TypeIdNode::WriteNonPtrType(CodeFormatter& formatter)
{
    if (IsPtrType())
    {
        bool first = true;
        for (const auto& typeSpecifier : typeSpecifiers)
        {
            if (first)
            {
                first = false;
            }
            else
            {
                std::expected<bool, int> rv = formatter.Write(" ");
                if (!rv) return std::unexpected<int>(rv.error());
            }
            std::expected<bool, int> rv = typeSpecifier->Write(formatter);
            if (!rv) return std::unexpected<int>(rv.error());
        }
        if (!declarator.empty())
        {
            std::expected<bool, int> rv = formatter.Write(declarator.substr(0, declarator.size() - 1));
            if (!rv) return std::unexpected<int>(rv.error());
        }
    }
    else
    {
        std::expected<bool, int> rv = Write(formatter);
        if (!rv) return std::unexpected<int>(rv.error());
    }
    return std::expected<bool, int>(true);
}

std::string TypeIdNode::ToString() const
{
    std::string str;
    bool first = true;
    for (const auto& typeSpecifier : typeSpecifiers)
    {
        if (first)
        {
            first = false;
        }
        else
        {
            str.append(" ");
        }
        str.append(typeSpecifier->ToString());
    }
    str.append(declarator);
    return str;
}

bool TypeIdNode::IsPtrType() const
{
    if (!declarator.empty())
    {
        return declarator.back() == '*';
    }
    else
    {
        return false;
    }
}

SimpleDeclarationNode::SimpleDeclarationNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::simpleDeclarationNode, sourcePos_)
{
}

void SimpleDeclarationNode::Add(DeclSpecifierNode* declSpecifier)
{
    declSpecifier->SetParent(this);
    declSpecifiers.push_back(std::unique_ptr<DeclSpecifierNode>(declSpecifier));
}

void SimpleDeclarationNode::SetInitDeclaratorList(InitDeclaratorListNode* initDeclaratorList_)
{
    initDeclaratorList.reset(initDeclaratorList_);
    initDeclaratorList->SetParent(this);
}

std::expected<bool, int> SimpleDeclarationNode::Write(CodeFormatter& formatter)
{
    bool first = true;
    for (const auto& declSpecifier : declSpecifiers)
    {
        if (first)
        {
            first = false;
        }
        else
        {
            std::expected<bool, int> rv = formatter.Write(" ");
            if (!rv) return std::unexpected<int>(rv.error());
        }
        std::expected<bool, int> rv = declSpecifier->Write(formatter);
        if (!rv) return std::unexpected<int>(rv.error());
    }
    if (!declSpecifiers.empty())
    {
        std::expected<bool, int> rv = formatter.Write(" ");
        if (!rv) return std::unexpected<int>(rv.error());
    }
    if (initDeclaratorList)
    {
        std::expected<bool, int> rv = initDeclaratorList->Write(formatter);
        if (!rv) return std::unexpected<int>(rv.error());
    }
    return std::expected<bool, int>(true);
}

Node* SimpleDeclarationNode::Clone() const
{
    SimpleDeclarationNode* clone = new SimpleDeclarationNode(GetSourcePos());
    for (const auto& declSpecifier : declSpecifiers)
    {
        clone->Add(static_cast<DeclSpecifierNode*>(declSpecifier->Clone()));
    }
    if (initDeclaratorList)
    {
        clone->SetInitDeclaratorList(static_cast<InitDeclaratorListNode*>(initDeclaratorList->Clone()));
    }
    return clone;
}

void SimpleDeclarationNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

UsingObjectNode::UsingObjectNode(NodeKind kind_, const soul::ast::SourcePos& sourcePos_, const std::string& name_) : Node(kind_, sourcePos_), name(name_)
{
}

NamespaceAliasNode::NamespaceAliasNode(const soul::ast::SourcePos& sourcePos_, const std::string& aliasName_, const std::string& namespaceName_) :
    UsingObjectNode(NodeKind::namespaceAliasNode, sourcePos_, "namespaceAlias"), aliasName(aliasName_), namespaceName(namespaceName_)
{
}

std::expected<bool, int> NamespaceAliasNode::Write(CodeFormatter& formatter)
{
    return formatter.WriteLine("namespace " + aliasName + " = " + namespaceName + ";");
}

Node* NamespaceAliasNode::Clone() const
{
    return new NamespaceAliasNode(GetSourcePos(), aliasName, namespaceName);
}

void NamespaceAliasNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

UsingDeclarationNode::UsingDeclarationNode(const soul::ast::SourcePos& sourcePos_, const std::string& usingId_) :
    UsingObjectNode(NodeKind::usingDeclarationNode, sourcePos_, "usingDeclaration"), usingId(usingId_)
{
}

std::expected<bool, int> UsingDeclarationNode::Write(CodeFormatter& formatter)
{
    return formatter.WriteLine("using " + usingId + ";");
}

Node* UsingDeclarationNode::Clone() const
{
    return new UsingDeclarationNode(GetSourcePos(), usingId);
}

void UsingDeclarationNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

UsingDirectiveNode::UsingDirectiveNode(const soul::ast::SourcePos& sourcePos_, const std::string& usingNs_) :
    UsingObjectNode(NodeKind::usingDirectiveNode, sourcePos_, "usingDirective"), usingNs(usingNs_)
{
}

std::expected<bool, int> UsingDirectiveNode::Write(CodeFormatter& formatter)
{
    return formatter.WriteLine("using namespace " + usingNs + ";");
}

Node* UsingDirectiveNode::Clone() const
{
    return new UsingDirectiveNode(GetSourcePos(), usingNs);
}

void UsingDirectiveNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

DefaultVisitor::DefaultVisitor() : error(0)
{
}

void DefaultVisitor::Visit(ExprListNode& node)
{
    if (!Valid()) return;
    for (const auto& expr : node.Exprs())
    {
        expr->Accept(*this);
        if (!Valid()) return;
    }
}

void DefaultVisitor::Visit(IndexExprNode& node)
{
    if (!Valid()) return;
    node.Child()->Accept(*this);
    if (!Valid()) return;
    node.Index()->Accept(*this);
}

void DefaultVisitor::Visit(InvokeNode& node)
{
    if (!Valid()) return;
    node.Child()->Accept(*this);
    if (!Valid()) return;
    for (const auto& arg : node.Args())
    {
        arg->Accept(*this);
        if (!Valid()) return;
    }
}

void DefaultVisitor::Visit(MemberAccessNode& node)
{
    if (!Valid()) return;
    node.Child()->Accept(*this);
    if (!Valid()) return;
    node.Member()->Accept(*this);
}

void DefaultVisitor::Visit(PtrMemberAccessNode& node)
{
    if (!Valid()) return;
    node.Child()->Accept(*this);
    if (!Valid()) return;
    node.Member()->Accept(*this);
}

void DefaultVisitor::Visit(PostIncrementNode& node)
{
    if (!Valid()) return;
    node.Child()->Accept(*this);
}

void DefaultVisitor::Visit(PostDecrementNode& node)
{
    if (!Valid()) return;
    node.Child()->Accept(*this);
}

void DefaultVisitor::Visit(PostCastNode& node)
{
    if (!Valid()) return;
    node.Child()->Accept(*this);
    if (!Valid()) return;
    node.GetCppCastNode()->Accept(*this);
    if (!Valid()) return;
    node.Type()->Accept(*this);
}

void DefaultVisitor::Visit(TypeIdExprNode& node)
{
    if (!Valid()) return;
    node.Child()->Accept(*this);
}

void DefaultVisitor::Visit(PreIncrementNode& node)
{
    if (!Valid()) return;
    node.Child()->Accept(*this);
}

void DefaultVisitor::Visit(PreDecrementNode& node)
{
    if (!Valid()) return;
    node.Child()->Accept(*this);
}

void DefaultVisitor::Visit(UnaryOpExprNode& node)
{
    if (!Valid()) return;
    node.Child()->Accept(*this);
}

void DefaultVisitor::Visit(SizeOfNode& node)
{
    if (!Valid()) return;
    node.Child()->Accept(*this);
}

void DefaultVisitor::Visit(CastNode& node)
{
    if (!Valid()) return;
    node.Child()->Accept(*this);
    if (!Valid()) return;
    node.Type()->Accept(*this);
}

void DefaultVisitor::Visit(BinaryOpExprNode& node)
{
    if (!Valid()) return;
    node.Left()->Accept(*this);
    if (!Valid()) return;
    node.Right()->Accept(*this);
}

void DefaultVisitor::Visit(ConditionalNode& node)
{
    if (!Valid()) return;
    node.Condition()->Accept(*this);
    if (!Valid()) return;
    node.ThenExpr()->Accept(*this);
    if (!Valid()) return;
    node.ElseExpr()->Accept(*this);
}

void DefaultVisitor::Visit(NewNode& node)
{
    if (!Valid()) return;
    for (const auto& placementNode : node.Placement())
    {
        placementNode->Accept(*this);
        if (!Valid()) return;
    }
    node.TypeId()->Accept(*this);
    if (!Valid()) return;
    for (const auto& initializerNode : node.Initializer())
    {
        initializerNode->Accept(*this);
        if (!Valid()) return;
    }
}

void DefaultVisitor::Visit(DeleteNode& node)
{
    if (!Valid()) return;
    node.Child()->Accept(*this);
}

void DefaultVisitor::Visit(ParenExprNode& node)
{
    if (!Valid()) return;
    node.Child()->Accept(*this);
}

void DefaultVisitor::Visit(LabeledStatementNode& node)
{
    if (!Valid()) return;
    node.Stmt()->Accept(*this);
}

void DefaultVisitor::Visit(CaseStatementNode& node)
{
    if (!Valid()) return;
    node.CaseExpr()->Accept(*this);
    if (!Valid()) return;
    node.Stmt()->Accept(*this);
}

void DefaultVisitor::Visit(DefaultStatementNode& node)
{
    if (!Valid()) return;
    node.Stmt()->Accept(*this);
}

void DefaultVisitor::Visit(ExpressionStatementNode& node)
{
    if (!Valid()) return;
    node.Expr()->Accept(*this);
}

void DefaultVisitor::Visit(CompoundStatementNode& node)
{
    if (!Valid()) return;
    for (const auto& stmt : node.Statements())
    {
        stmt->Accept(*this);
        if (!Valid()) return;
    }
}

void DefaultVisitor::Visit(IfStatementNode& node)
{
    if (!Valid()) return;
    node.Cond()->Accept(*this);
    if (!Valid()) return;
    node.ThenStmt()->Accept(*this);
    if (!Valid()) return;
    if (node.ElseStmt())
    {
        node.ElseStmt()->Accept(*this);
    }
}

void DefaultVisitor::Visit(SwitchStatementNode& node)
{
    if (!Valid()) return;
    node.Cond()->Accept(*this);
    if (!Valid()) return;
    node.Stmt()->Accept(*this);
}

void DefaultVisitor::Visit(WhileStatementNode& node)
{
    if (!Valid()) return;
    node.Cond()->Accept(*this);
    if (!Valid()) return;
    node.Stmt()->Accept(*this);
}

void DefaultVisitor::Visit(DoStatementNode& node)
{
    if (!Valid()) return;
    node.Cond()->Accept(*this);
    if (!Valid()) return;
    node.Stmt()->Accept(*this);
}

void DefaultVisitor::Visit(ForStatementNode& node)
{
    if (!Valid()) return;
    if (node.Init())
    {
        node.Init()->Accept(*this);
        if (!Valid()) return;
    }
    if (node.Cond())
    {
        node.Cond()->Accept(*this);
        if (!Valid()) return;
    }
    if (node.Iter())
    {
        node.Iter()->Accept(*this);
        if (!Valid()) return;
    }
    node.Stmt()->Accept(*this);
}

void DefaultVisitor::Visit(ReturnStatementNode& node)
{
    if (!Valid()) return;
    if (node.Expr())
    {
        node.Expr()->Accept(*this);
    }
}

void DefaultVisitor::Visit(ConditionWithDeclaratorNode& node)
{
    if (!Valid()) return;
    node.Type()->Accept(*this);
    if (!Valid()) return;
    node.Expression()->Accept(*this);
}

void DefaultVisitor::Visit(ForRangeDeclarationNode& node)
{
    if (!Valid()) return;
    node.Declaration()->Accept(*this);
}

void DefaultVisitor::Visit(RangeForStatementNode& node)
{
    if (!Valid()) return;
    node.Declaration()->Accept(*this);
    if (!Valid()) return;
    node.Container()->Accept(*this);
    if (!Valid()) return;
    node.Stmt()->Accept(*this);
}

void DefaultVisitor::Visit(DeclarationStatementNode& node)
{
    if (!Valid()) return;
    node.Declaration()->Accept(*this);
}

void DefaultVisitor::Visit(IfdefStatementNode& node)
{
    if (!Valid()) return;
    node.Symbol()->Accept(*this);
}

void DefaultVisitor::Visit(AssignInitNode& node)
{
    if (!Valid()) return;
    if (node.AssignmentExpr())
    {
        node.AssignmentExpr()->Accept(*this);
        if (!Valid()) return;
    }
    for (const auto& subInit : node.SubInits())
    {
        subInit->Accept(*this);
        if (!Valid()) return;
    }
}

void DefaultVisitor::Visit(InitializerNode& node)
{
    if (!Valid()) return;
    if (node.GetAssignInit())
    {
        node.GetAssignInit()->Accept(*this);
        if (!Valid()) return;
    }
    for (const auto& expr : node.GetExpressionList())
    {
        expr->Accept(*this);
        if (!Valid()) return;
    }
}

void DefaultVisitor::Visit(InitDeclaratorNode& node)
{
    if (!Valid()) return;
    if (node.GetInitializer())
    {
        node.GetInitializer()->Accept(*this);
    }
}

void DefaultVisitor::Visit(InitDeclaratorListNode& node)
{
    if (!Valid()) return;
    for (const auto& initDeclarator : node.InitDeclarators())
    {
        initDeclarator->Accept(*this);
        if (!Valid()) return;
    }
}

void DefaultVisitor::Visit(TypeNameNode& node)
{
    if (!Valid()) return;
    for (const auto& templateArg : node.TemplateArgs())
    {
        templateArg->Accept(*this);
        if (!Valid()) return;
    }
}

void DefaultVisitor::Visit(TypeNode& node)
{
    if (!Valid()) return;
    for (const auto& typeSpecifier : node.TypeSpecifiers())
    {
        typeSpecifier->Accept(*this);
        if (!Valid()) return;
    }
}

void DefaultVisitor::Visit(TypeIdNode& node)
{
    if (!Valid()) return;
    for (const auto& typeSpecifier : node.TypeSpecifiers())
    {
        typeSpecifier->Accept(*this);
        if (!Valid()) return;
    }
}

void DefaultVisitor::Visit(SimpleDeclarationNode& node)
{
    if (!Valid()) return;
    for (const auto& declSpecifier : node.DeclSpecifiers())
    {
        declSpecifier->Accept(*this);
        if (!Valid()) return;
    }
    node.GetInitDeclaratorList()->Accept(*this);
}

CodeEvaluationVisitor::CodeEvaluationVisitor() : hasReturn(false), hasPass(false), hasVars(false)
{
}

void CodeEvaluationVisitor::Visit(ReturnStatementNode& node)
{
    DefaultVisitor::Visit(node);
    hasReturn = true;
}

void CodeEvaluationVisitor::Visit(TypeNameNode& node)
{
    Visitor::Visit(node);
    if (node.Name() == "pass")
    {
        hasPass = true;
    }
    else if (node.Name() == "vars")
    {
        hasVars = true;
    }
}

void CodeEvaluationVisitor::Visit(IdExprNode& node)
{
    Visitor::Visit(node);
    if (node.Id() == "pass")
    {
        hasPass = true;
    }
    else if (node.Id() == "vars")
    {
        hasVars = true;
    }
}

Context::Context() : parsingTemplateId(false)
{
}

void Context::BeginParsingTemplateId()
{
    parsingTemplateIdStack.push(parsingTemplateId);
    parsingTemplateId = true;
}

void Context::EndParsingTemplateId()
{
    parsingTemplateId = parsingTemplateIdStack.top();
    parsingTemplateIdStack.pop();
}

} // namespace soul::ast::cpp
