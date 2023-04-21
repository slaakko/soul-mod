// =================================
// Copyright (c) 2023 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.ast.qualifier;

import std.core;
import otava.ast.node;

export namespace otava::ast {

class ConstNode : public Node
{
public:
    ConstNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class VolatileNode : public Node
{
public:
    VolatileNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class LvalueRefNode : public Node
{
public:
    LvalueRefNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class RvalueRefNode : public Node
{
public:
    RvalueRefNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class PtrNode : public Node
{
public:
    PtrNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class CVQualifierSequenceNode : public SequenceNode
{
public:
    CVQualifierSequenceNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

} // namespace otava::ast
