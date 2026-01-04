// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.ast.qualifier;

import std;
import otava.ast.node;

export namespace otava::ast {

class ConstNode : public Node
{
public:
    ConstNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::u32string Str() const override { return U"const"; }
};

class VolatileNode : public Node
{
public:
    VolatileNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::u32string Str() const override { return U"volatile"; }
};

class LvalueRefNode : public Node
{
public:
    LvalueRefNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::u32string Str() const override { return U"&"; }
};

class RvalueRefNode : public Node
{
public:
    RvalueRefNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::u32string Str() const override { return U"&&"; }
};

class PtrNode : public Node
{
public:
    PtrNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::u32string Str() const override { return U"*"; }
};

class CVQualifierSequenceNode : public SequenceNode
{
public:
    CVQualifierSequenceNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

} // namespace otava::ast
