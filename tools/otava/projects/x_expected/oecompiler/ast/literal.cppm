// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.ast.literal;

import std;
import otava.ast.node;

export namespace otava::ast {

enum class Suffix : std::uint8_t
{
    none = 0,
    u = 1 << 0,
    l = 1 << 1,
    ll = 1 << 2,
    z = 1 << 3,
    f = 1 << 4
};

inline Suffix operator|(Suffix left, Suffix right)
{
    return Suffix(std::uint8_t(left) | std::uint8_t(right));
}

inline Suffix operator&(Suffix left, Suffix right)
{
    return Suffix(std::uint8_t(left) & std::uint8_t(right));
}

inline Suffix operator~(Suffix suffix)
{
    return Suffix(~std::uint8_t(suffix));
}

enum class Base : std::uint8_t
{
    binary, octal, decimal, hexadecimal
};

enum class EncodingPrefix : std::uint8_t
{
    none, u8, u, U, L
};

class LiteralNode : public Node
{
public:
    LiteralNode(NodeKind kind_, const soul::ast::SourcePos& sourcePos_);
    LiteralNode(NodeKind kind_, const soul::ast::SourcePos& sourcePos_, const std::u32string& rep_);
    std::expected<bool, int> Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    inline const std::u32string& Rep() const { return rep; }
private:
    std::u32string rep;
};

class IntegerLiteralNode : public LiteralNode
{
public:
    IntegerLiteralNode(const soul::ast::SourcePos& sourcePos_);
    IntegerLiteralNode(const soul::ast::SourcePos& sourcePos_, std::uint64_t value_, Suffix suffix_, Base base_, const std::u32string& rep_);
    std::expected<Node*, int> Clone() const override;
    void Accept(Visitor& visitor) override;
    std::expected<bool, int> Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    inline std::uint64_t Value() const { return value; }
    inline Suffix GetSuffix() const { return suffix; }
    inline Base GetBase() const { return base; }
private:
    std::uint64_t value;
    Suffix suffix;
    Base base;
};

class FloatingLiteralNode : public LiteralNode
{
public:
    FloatingLiteralNode(const soul::ast::SourcePos& sourcePos_);
    FloatingLiteralNode(const soul::ast::SourcePos& sourcePos_, double value_, Suffix suffix_, Base base_, const std::u32string& rep_);
    std::expected<Node*, int> Clone() const override;
    void Accept(Visitor& visitor) override;
    std::expected<bool, int> Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    inline double Value() const { return value; }
    inline Suffix GetSuffix() const { return suffix; }
    inline Base GetBase() const { return base; }
private:
    double value;
    Suffix suffix;
    Base base;
};

class CharacterLiteralNode : public LiteralNode
{
public:
    CharacterLiteralNode(const soul::ast::SourcePos& sourcePos_);
    CharacterLiteralNode(const soul::ast::SourcePos& sourcePos_, char32_t value_, EncodingPrefix encodingPrefix_, const std::u32string& rep_, bool hasMultipleCharacters_);
    std::expected<Node*, int> Clone() const override;
    void Accept(Visitor& visitor) override;
    std::expected<bool, int> Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    inline char32_t Value() const { return value; }
    inline EncodingPrefix GetEncodingPrefix() const { return encodingPrefix; }
    inline bool HasMultipleCharacters() const { return hasMultipleCharacters; }
private:
    char32_t value;
    EncodingPrefix encodingPrefix;
    bool hasMultipleCharacters;
};

class StringLiteralNode : public LiteralNode
{
public:
    StringLiteralNode(const soul::ast::SourcePos& sourcePos_);
    StringLiteralNode(NodeKind kind_, const soul::ast::SourcePos& sourcePos_);
    StringLiteralNode(const soul::ast::SourcePos& sourcePos_, const std::u32string& value_, EncodingPrefix encodingPrefix_, const std::u32string& rep_);
    StringLiteralNode(NodeKind kind_, const soul::ast::SourcePos& sourcePos_, const std::u32string& value_, EncodingPrefix encodingPrefix_, const std::u32string& rep_);
    std::expected<Node*, int> Clone() const override;
    void Accept(Visitor& visitor) override;
    std::expected<bool, int> Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    inline const std::u32string& Value() const { return value; }
    inline EncodingPrefix GetEncodingPrefix() const { return encodingPrefix; }
private:
    std::u32string value;
    EncodingPrefix encodingPrefix;
};

class RawStringLiteralNode : public StringLiteralNode
{
public:
    RawStringLiteralNode(const soul::ast::SourcePos& sourcePos_);
    RawStringLiteralNode(const soul::ast::SourcePos& sourcePos_, const std::u32string& value_, EncodingPrefix encodingPrefix_, const std::u32string& delimSequence_, const std::u32string& rep_);
    std::expected<Node*, int> Clone() const override;
    void Accept(Visitor& visitor) override;
    std::expected<bool, int> Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    inline const std::u32string& DelimSequence() const { return delimSequence; }
private:
    std::u32string delimSequence;
};

class BooleanLiteralNode : public LiteralNode
{
public:
    BooleanLiteralNode(const soul::ast::SourcePos& sourcePos_);
    BooleanLiteralNode(const soul::ast::SourcePos& sourcePos_, bool value_, const std::u32string& rep_);
    std::expected<Node*, int> Clone() const override;
    void Accept(Visitor& visitor) override;
    std::expected<bool, int> Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    inline bool Value() const { return value; }
private:
    bool value;
};

class NullPtrLiteralNode : public LiteralNode
{
public:
    NullPtrLiteralNode(const soul::ast::SourcePos& sourcePos_);
    NullPtrLiteralNode(const soul::ast::SourcePos& sourcePos_, const std::u32string& rep_);
    std::expected<Node*, int> Clone() const override;
    void Accept(Visitor& visitor) override;
};

class UserDefinedLiteraNode : public BinaryNode
{
public:
    UserDefinedLiteraNode(const soul::ast::SourcePos& sourcePos_);
    UserDefinedLiteraNode(const soul::ast::SourcePos& sourcePos_, Node* literalNode_, Node* udSuffix_);
    std::expected<Node*, int> Clone() const override;
    void Accept(Visitor& visitor) override;
};

class LiteralOperatorIdNode : public UnaryNode
{
public:
    LiteralOperatorIdNode(const soul::ast::SourcePos& sourcePos_);
    LiteralOperatorIdNode(const soul::ast::SourcePos& sourcePos_, Node* id_, const soul::ast::SourcePos& stringLitPos_);
    std::expected<Node*, int> Clone() const override;
    void Accept(Visitor& visitor) override;
    std::expected<bool, int> Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    inline const soul::ast::SourcePos& StringLitPos() const { return stringLitPos; }
private:
    soul::ast::SourcePos stringLitPos;
};

std::u32string EncodingPrefixStr(EncodingPrefix encodingPrefix);
EncodingPrefix CommonEncodingPrefix(otava::ast::EncodingPrefix leftEncodingPrefix, otava::ast::EncodingPrefix rightEncodingPrefix);

} // namespace otava::ast
