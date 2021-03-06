// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.ast.qualifier;

import soul.cpp20.ast.node;

export namespace soul::cpp20::ast {

class ConstNode : public Node
{
public:
    ConstNode(const soul::ast::SourcePos& sourcePos_);
    void Accept(Visitor& visitor) override;
};

class VolatileNode : public Node
{
public:
    VolatileNode(const soul::ast::SourcePos& sourcePos_);
    void Accept(Visitor& visitor) override;
};

class LvalueRefNode : public Node
{
public:
    LvalueRefNode(const soul::ast::SourcePos& sourcePos_);
    void Accept(Visitor& visitor) override;
};

class RvalueRefNode : public Node
{
public:
    RvalueRefNode(const soul::ast::SourcePos& sourcePos_);
    void Accept(Visitor& visitor) override;
};

class PtrNode : public Node
{
public:
    PtrNode(const soul::ast::SourcePos& sourcePos_);
    void Accept(Visitor& visitor) override;
};

class CVQualifierSequenceNode : public SequenceNode
{
public:
    CVQualifierSequenceNode(const soul::ast::SourcePos& sourcePos_);
    void Accept(Visitor& visitor) override;
};

} // namespace soul::cpp20::ast
