// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.ast.attribute;

import std;
import otava.ast.node;

export namespace otava::ast {

class AttributeSpecifierSequenceNode : public SequenceNode
{
public:
    AttributeSpecifierSequenceNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class AttributeSpecifierNode : public ListNode
{
public:
    AttributeSpecifierNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline void SetUsingPrefix(Node* usingPrefix_) { usingPrefix.reset(usingPrefix_); }
    inline Node* UsingPrefix() const { return usingPrefix.get(); }
    void SetBracketPositions(const soul::ast::SourcePos& lbPos1_, const soul::ast::SourcePos& lbPos2_, const soul::ast::SourcePos& rbPos1_, const soul::ast::SourcePos& rbPos2_);
    inline const soul::ast::SourcePos& LBracketPos1() const { return lbPos1; }
    inline const soul::ast::SourcePos& LBracketPos2() const { return lbPos2; }
    inline const soul::ast::SourcePos& RBracketPos1() const { return rbPos1; }
    inline const soul::ast::SourcePos& RBracketPos2() const { return rbPos2; }
private:
    std::unique_ptr<Node> usingPrefix;
    soul::ast::SourcePos lbPos1;
    soul::ast::SourcePos lbPos2;
    soul::ast::SourcePos rbPos1;
    soul::ast::SourcePos rbPos2;
};

class AttributeUsingPrefixNode : public UnaryNode
{
public:
    AttributeUsingPrefixNode(const soul::ast::SourcePos& sourcePos_);
    AttributeUsingPrefixNode(const soul::ast::SourcePos& sourcePos_, Node* attributeNamespace_, const soul::ast::SourcePos& colonPos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline const soul::ast::SourcePos& ColonPos() const { return colonPos; }
private:
    soul::ast::SourcePos colonPos;
};

class AttributeNode : public CompoundNode
{
public:
    AttributeNode(const soul::ast::SourcePos& sourcePos_);
    AttributeNode(const soul::ast::SourcePos& sourcePos_, Node* attributeToken_, Node* attributeArgs_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* AttributeToken() const { return attributeToken.get(); }
    inline Node* AttributeArgs() const { return attributeArgs.get(); }
private:
    std::unique_ptr<Node> attributeToken;
    std::unique_ptr<Node> attributeArgs;
};

class AttributeScopedTokenNode : public CompoundNode
{
public:
    AttributeScopedTokenNode(const soul::ast::SourcePos& sourcePos_);
    AttributeScopedTokenNode(const soul::ast::SourcePos& sourcePos_, Node* ns_, Node* colonColon_, Node* identifier_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Ns() const { return ns.get(); }
    inline Node* ColonColon() const { return colonColon.get(); }
    inline Node* Identifier() const { return identifier.get(); }
private:
    std::unique_ptr<Node> ns;
    std::unique_ptr<Node> colonColon;
    std::unique_ptr<Node> identifier;
};

class AttributeArgumentsNode : public CompoundNode
{
public:
    AttributeArgumentsNode(const soul::ast::SourcePos& sourcePos_);
    AttributeArgumentsNode(const soul::ast::SourcePos& sourcePos_, Node* balancedTokenSequence_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* BalancedTokenSequence() const { return balancedTokenSequence.get(); }
    inline const soul::ast::SourcePos& LParenPos() const { return lpPos; }
    inline const soul::ast::SourcePos& RParenPos() const { return rpPos; }
private:
    std::unique_ptr<Node> balancedTokenSequence;
    soul::ast::SourcePos lpPos;
    soul::ast::SourcePos rpPos;
};

class BalancedTokenSequenceNode : public SequenceNode
{
public:
    BalancedTokenSequenceNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class TokenNode : public CompoundNode
{
public:
    TokenNode(const soul::ast::SourcePos& sourcePos_);
    TokenNode(const soul::ast::SourcePos& sourcePos_, const std::u32string& str_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline std::u32string Str() const override { return str; }
private:
    std::u32string str;
};

class AlignmentSpecifierNode : public CompoundNode
{
public:
    AlignmentSpecifierNode(const soul::ast::SourcePos& sourcePos_);
    AlignmentSpecifierNode(const soul::ast::SourcePos& sourcePos_, Node* alignment_, Node* ellipsis_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Alignment() const { return alignment.get(); }
    inline Node* Ellipsis() const { return ellipsis.get(); }
    inline const soul::ast::SourcePos& LParenPos() const { return lpPos; }
    inline const soul::ast::SourcePos& RParenPos() const { return rpPos; }
private:
    std::unique_ptr<Node> alignment;
    std::unique_ptr<Node> ellipsis;
    soul::ast::SourcePos lpPos;
    soul::ast::SourcePos rpPos;
};

} // namespace otava::ast
