// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.ast.simple.type;

import soul.cpp20.ast.node;

export namespace soul::cpp20::ast {

class CharNode : public Node
{
public:
    CharNode(const soul::ast::SourcePos& sourcePos_);
    void Accept(Visitor& visitor) override;
};

class Char8Node : public Node
{
public:
    Char8Node(const soul::ast::SourcePos& sourcePos_);
    void Accept(Visitor& visitor) override;
};

class Char16Node : public Node
{
public:
    Char16Node(const soul::ast::SourcePos& sourcePos_);
    void Accept(Visitor& visitor) override;
};

class Char32Node : public Node
{
public:
    Char32Node(const soul::ast::SourcePos& sourcePos_);
    void Accept(Visitor& visitor) override;
};

class WCharNode : public Node
{
public:
    WCharNode(const soul::ast::SourcePos& sourcePos_);
    void Accept(Visitor& visitor) override;
};

class BoolNode : public Node
{
public:
    BoolNode(const soul::ast::SourcePos& sourcePos_);
    void Accept(Visitor& visitor) override;
};

class ShortNode : public Node
{
public:
    ShortNode(const soul::ast::SourcePos& sourcePos_);
    void Accept(Visitor& visitor) override;
};

class IntNode : public Node
{
public:
    IntNode(const soul::ast::SourcePos& sourcePos_);
    void Accept(Visitor& visitor) override;
};

class LongNode : public Node
{
public:
    LongNode(const soul::ast::SourcePos& sourcePos_);
    void Accept(Visitor& visitor) override;
};

class SignedNode : public Node
{
public:
    SignedNode(const soul::ast::SourcePos& sourcePos_);
    void Accept(Visitor& visitor) override;
};

class UnsignedNode : public Node
{
public:
    UnsignedNode(const soul::ast::SourcePos& sourcePos_);
    void Accept(Visitor& visitor) override;
};

class FloatNode : public Node
{
public:
    FloatNode(const soul::ast::SourcePos& sourcePos_);
    void Accept(Visitor& visitor) override;
};

class DoubleNode : public Node
{
public:
    DoubleNode(const soul::ast::SourcePos& sourcePos_);
    void Accept(Visitor& visitor) override;
};

class VoidNode : public Node
{
public:
    VoidNode(const soul::ast::SourcePos& sourcePos_);
    void Accept(Visitor& visitor) override;
};

} // namespace soul::cpp20::ast
