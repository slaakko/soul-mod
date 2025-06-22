// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.ast.identifier;

import std;
import otava.ast.node;

export namespace otava::ast {

class IdentifierNode : public CompoundNode
{
public:
    IdentifierNode(const soul::ast::SourcePos& sourcePos_);
    IdentifierNode(const soul::ast::SourcePos& sourcePos_, const std::u32string& str_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    std::u32string Str() const override { return str; }
private:
    std::u32string str;
};

class UnnamedNode : public Node
{
public:
    UnnamedNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class ColonColonNode : public Node
{
public:
    ColonColonNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class NestedNameSpecifierNode : public SequenceNode
{
public:
    NestedNameSpecifierNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class QualifiedIdNode : public BinaryNode
{
public:
    QualifiedIdNode(const soul::ast::SourcePos& sourcePos_);
    QualifiedIdNode(const soul::ast::SourcePos& sourcePos_, Node* nns_, Node* unqualifiedId_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class IdentifierListNode : public ListNode
{
public:
    IdentifierListNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class ModuleNameNode : public Node
{
public:
    ModuleNameNode(const soul::ast::SourcePos& sourcePos_);
    ModuleNameNode(const soul::ast::SourcePos& sourcePos_, const std::u32string& str_);
    std::u32string Str() const override { return str; }
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
private:
    std::u32string str;
};

} // namespace otava::ast
