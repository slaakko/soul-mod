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
    AttributeSpecifierSequenceNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class AttributeSpecifierNode : public ListNode
{
public:
    AttributeSpecifierNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline void SetUsingPrefix(Node* usingPrefix_) noexcept { usingPrefix.reset(usingPrefix_); }
    inline Node* UsingPrefix() const noexcept { return usingPrefix.get(); }
    void SetBracketPositions(const soul::ast::SourcePos& lbPos1_, const soul::ast::SourcePos& lbPos2_, const soul::ast::SourcePos& rbPos1_, 
        const soul::ast::SourcePos& rbPos2_) noexcept;
    inline const soul::ast::SourcePos& LBracketPos1() const noexcept { return lbPos1; }
    inline const soul::ast::SourcePos& LBracketPos2() const noexcept { return lbPos2; }
    inline const soul::ast::SourcePos& RBracketPos1() const noexcept { return rbPos1; }
    inline const soul::ast::SourcePos& RBracketPos2() const noexcept { return rbPos2; }
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
    AttributeUsingPrefixNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    AttributeUsingPrefixNode(const soul::ast::SourcePos& sourcePos_, Node* attributeNamespace_, const soul::ast::SourcePos& colonPos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline const soul::ast::SourcePos& ColonPos() const noexcept { return colonPos; }
private:
    soul::ast::SourcePos colonPos;
};

class AttributeNode : public CompoundNode
{
public:
    AttributeNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    AttributeNode(const soul::ast::SourcePos& sourcePos_, Node* attributeToken_, Node* attributeArgs_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* AttributeToken() const noexcept { return attributeToken.get(); }
    inline Node* AttributeArgs() const noexcept { return attributeArgs.get(); }
private:
    std::unique_ptr<Node> attributeToken;
    std::unique_ptr<Node> attributeArgs;
};

class AttributeScopedTokenNode : public CompoundNode
{
public:
    AttributeScopedTokenNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    AttributeScopedTokenNode(const soul::ast::SourcePos& sourcePos_, Node* ns_, Node* colonColon_, Node* identifier_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Ns() const noexcept { return ns.get(); }
    inline Node* ColonColon() const noexcept { return colonColon.get(); }
    inline Node* Identifier() const noexcept { return identifier.get(); }
private:
    std::unique_ptr<Node> ns;
    std::unique_ptr<Node> colonColon;
    std::unique_ptr<Node> identifier;
};

class AttributeArgumentsNode : public CompoundNode
{
public:
    AttributeArgumentsNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    AttributeArgumentsNode(const soul::ast::SourcePos& sourcePos_, Node* balancedTokenSequence_, const soul::ast::SourcePos& lpPos_, 
        const soul::ast::SourcePos& rpPos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* BalancedTokenSequence() const noexcept { return balancedTokenSequence.get(); }
    inline const soul::ast::SourcePos& LParenPos() const noexcept { return lpPos; }
    inline const soul::ast::SourcePos& RParenPos() const noexcept { return rpPos; }
private:
    std::unique_ptr<Node> balancedTokenSequence;
    soul::ast::SourcePos lpPos;
    soul::ast::SourcePos rpPos;
};

class BalancedTokenSequenceNode : public SequenceNode
{
public:
    BalancedTokenSequenceNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class TokenNode : public CompoundNode
{
public:
    TokenNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    TokenNode(const soul::ast::SourcePos& sourcePos_, const std::u32string& str_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    std::u32string Str() const override { return str; }
private:
    std::u32string str;
};

class AlignmentSpecifierNode : public CompoundNode
{
public:
    AlignmentSpecifierNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    AlignmentSpecifierNode(const soul::ast::SourcePos& sourcePos_, Node* alignment_, Node* ellipsis_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Alignment() const noexcept { return alignment.get(); }
    inline Node* Ellipsis() const noexcept { return ellipsis.get(); }
    inline const soul::ast::SourcePos& LParenPos() const noexcept { return lpPos; }
    inline const soul::ast::SourcePos& RParenPos() const noexcept { return rpPos; }
private:
    std::unique_ptr<Node> alignment;
    std::unique_ptr<Node> ellipsis;
    soul::ast::SourcePos lpPos;
    soul::ast::SourcePos rpPos;
};

} // namespace otava::ast
