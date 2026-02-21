// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.ast.literal;

import otava.ast.visitor;
import otava.ast.reader;
import otava.ast.writer;

namespace otava::ast {

LiteralNode::LiteralNode(NodeKind kind_, const soul::ast::SourcePos& sourcePos_) noexcept : Node(kind_, sourcePos_), rep()
{
}

LiteralNode::LiteralNode(NodeKind kind_, const soul::ast::SourcePos& sourcePos_, const std::u32string& rep_) : Node(kind_, sourcePos_), rep(rep_)
{
}

void LiteralNode::Write(Writer& writer)
{
    Node::Write(writer);
    writer.Write(rep);
}

void LiteralNode::Read(Reader& reader)
{
    Node::Read(reader);
    rep = reader.ReadStr();
}

IntegerLiteralNode::IntegerLiteralNode(const soul::ast::SourcePos& sourcePos_) noexcept : LiteralNode(NodeKind::integerLiteralNode, sourcePos_), value(), suffix(), base()
{
}

IntegerLiteralNode::IntegerLiteralNode(const soul::ast::SourcePos& sourcePos_, std::uint64_t value_, Suffix suffix_, Base base_, const std::u32string& rep_) :
    LiteralNode(NodeKind::integerLiteralNode, sourcePos_, rep_), value(value_), suffix(suffix_), base(base_)
{
}

Node* IntegerLiteralNode::Clone() const
{
    IntegerLiteralNode* clone = new IntegerLiteralNode(GetSourcePos(), value, suffix, base, Rep());
    return clone;
}

void IntegerLiteralNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void IntegerLiteralNode::Write(Writer& writer)
{
    LiteralNode::Write(writer);
    writer.GetBinaryStreamWriter().Write(value);
    writer.GetBinaryStreamWriter().Write(static_cast<std::uint8_t>(suffix));
    writer.GetBinaryStreamWriter().Write(static_cast<std::uint8_t>(base));
}

void IntegerLiteralNode::Read(Reader& reader)
{
    LiteralNode::Read(reader);
    value = reader.GetBinaryStreamReader().ReadULong();
    suffix = static_cast<Suffix>(reader.GetBinaryStreamReader().ReadByte());
    base = static_cast<Base>(reader.GetBinaryStreamReader().ReadByte());
}

FloatingLiteralNode::FloatingLiteralNode(const soul::ast::SourcePos& sourcePos_) noexcept : 
    LiteralNode(NodeKind::floatingLiteralNode, sourcePos_), value(), suffix(), base()
{
}

FloatingLiteralNode::FloatingLiteralNode(const soul::ast::SourcePos& sourcePos_, double value_, Suffix suffix_, Base base_, const std::u32string& rep_) :
    LiteralNode(NodeKind::floatingLiteralNode, sourcePos_, rep_), value(value_), suffix(suffix_), base(base_)
{
}

Node* FloatingLiteralNode::Clone() const
{
    FloatingLiteralNode* clone = new FloatingLiteralNode(GetSourcePos(), value, suffix, base, Rep());
    return clone;
}

void FloatingLiteralNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void FloatingLiteralNode::Write(Writer& writer)
{
    LiteralNode::Write(writer);
    writer.GetBinaryStreamWriter().Write(value);
    writer.GetBinaryStreamWriter().Write(static_cast<std::uint8_t>(suffix));
    writer.GetBinaryStreamWriter().Write(static_cast<std::uint8_t>(base));
}

void FloatingLiteralNode::Read(Reader& reader)
{
    LiteralNode::Read(reader);
    value = reader.GetBinaryStreamReader().ReadDouble();
    suffix = static_cast<Suffix>(reader.GetBinaryStreamReader().ReadByte());
    base = static_cast<Base>(reader.GetBinaryStreamReader().ReadByte());
}

CharacterLiteralNode::CharacterLiteralNode(const soul::ast::SourcePos& sourcePos_) noexcept : 
    LiteralNode(NodeKind::characterLiteralNode, sourcePos_), value(), encodingPrefix(), hasMultipleCharacters(false)
{
}

CharacterLiteralNode::CharacterLiteralNode(const soul::ast::SourcePos& sourcePos_, char32_t value_, EncodingPrefix encodingPrefix_, 
    const std::u32string& rep_, bool hasMultipleCharacters_) :
    LiteralNode(NodeKind::characterLiteralNode, sourcePos_, rep_), value(value_), encodingPrefix(encodingPrefix_), hasMultipleCharacters(hasMultipleCharacters_)
{
}

Node* CharacterLiteralNode::Clone() const
{
    CharacterLiteralNode* clone = new CharacterLiteralNode(GetSourcePos(), value, encodingPrefix, Rep(), hasMultipleCharacters);
    return clone;
}

void CharacterLiteralNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void CharacterLiteralNode::Write(Writer& writer)
{
    LiteralNode::Write(writer);
    writer.GetBinaryStreamWriter().Write(value);
    writer.GetBinaryStreamWriter().Write(static_cast<std::uint8_t>(encodingPrefix));
    writer.GetBinaryStreamWriter().Write(hasMultipleCharacters);
}

void CharacterLiteralNode::Read(Reader& reader)
{
    LiteralNode::Read(reader);
    value = reader.GetBinaryStreamReader().ReadUChar();
    encodingPrefix = static_cast<EncodingPrefix>(reader.GetBinaryStreamReader().ReadByte());
    hasMultipleCharacters = reader.GetBinaryStreamReader().ReadBool();
}

StringLiteralNode::StringLiteralNode(const soul::ast::SourcePos& sourcePos_) noexcept : 
    LiteralNode(NodeKind::stringLiteralNode, sourcePos_), value(), encodingPrefix()
{
}

StringLiteralNode::StringLiteralNode(NodeKind kind_, const soul::ast::SourcePos& sourcePos_) : LiteralNode(kind_, sourcePos_), value(), encodingPrefix()
{
}

StringLiteralNode::StringLiteralNode(const soul::ast::SourcePos& sourcePos_, const std::u32string& value_, EncodingPrefix encodingPrefix_, const std::u32string& rep_) :
    LiteralNode(NodeKind::stringLiteralNode, sourcePos_, rep_), value(value_), encodingPrefix(encodingPrefix_)
{
}

StringLiteralNode::StringLiteralNode(NodeKind kind_, const soul::ast::SourcePos& sourcePos_, const std::u32string& value_, EncodingPrefix encodingPrefix_, 
    const std::u32string& rep_) :
    LiteralNode(kind_, sourcePos_, rep_), value(value_), encodingPrefix(encodingPrefix_)
{
}

Node* StringLiteralNode::Clone() const
{
    StringLiteralNode* clone = new StringLiteralNode(GetSourcePos(), value, encodingPrefix, Rep());
    return clone;
}

void StringLiteralNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void StringLiteralNode::Write(Writer& writer)
{
    LiteralNode::Write(writer);
    writer.Write(value);
    writer.GetBinaryStreamWriter().Write(static_cast<std::uint8_t>(encodingPrefix));
}

void StringLiteralNode::Read(Reader& reader)
{
    LiteralNode::Read(reader);
    value = reader.ReadStr();
    encodingPrefix = static_cast<EncodingPrefix>(reader.GetBinaryStreamReader().ReadByte());
}

RawStringLiteralNode::RawStringLiteralNode(const soul::ast::SourcePos& sourcePos_) noexcept : StringLiteralNode(NodeKind::rawStringLiteralNode, sourcePos_)
{
}

RawStringLiteralNode::RawStringLiteralNode(const soul::ast::SourcePos& sourcePos_, const std::u32string& value_, EncodingPrefix encodingPrefix_, 
    const std::u32string& delimSequence_, const std::u32string& rep_) :
    StringLiteralNode(NodeKind::rawStringLiteralNode, sourcePos_, value_, encodingPrefix_, rep_), delimSequence(delimSequence_)
{
}

Node* RawStringLiteralNode::Clone() const
{
    RawStringLiteralNode* clone = new RawStringLiteralNode(GetSourcePos(), GetValue(), EncodingPrefix(), delimSequence, Rep());
    return clone;
}

void RawStringLiteralNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void RawStringLiteralNode::Write(Writer& writer)
{
    StringLiteralNode::Write(writer);
    writer.Write(delimSequence);
}

void RawStringLiteralNode::Read(Reader& reader)
{
    StringLiteralNode::Read(reader);
    delimSequence = reader.ReadStr();
}

BooleanLiteralNode::BooleanLiteralNode(const soul::ast::SourcePos& sourcePos_) noexcept : LiteralNode(NodeKind::booleanLiteralNode, sourcePos_), value()
{
}

BooleanLiteralNode::BooleanLiteralNode(const soul::ast::SourcePos& sourcePos_, bool value_, const std::u32string& rep_) :
    LiteralNode(NodeKind::booleanLiteralNode, sourcePos_, rep_), value(value_)
{
}

Node* BooleanLiteralNode::Clone() const
{
    BooleanLiteralNode* clone = new BooleanLiteralNode(GetSourcePos(), value, Rep());
    return clone;
}

void BooleanLiteralNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void BooleanLiteralNode::Write(Writer& writer)
{
    LiteralNode::Write(writer);
    writer.Write(value);
}

void BooleanLiteralNode::Read(Reader& reader)
{
    LiteralNode::Read(reader);
    value = reader.ReadBool();
}

NullPtrLiteralNode::NullPtrLiteralNode(const soul::ast::SourcePos& sourcePos_) noexcept : LiteralNode(NodeKind::nullPtrLiteralNode, sourcePos_)
{
}

NullPtrLiteralNode::NullPtrLiteralNode(const soul::ast::SourcePos& sourcePos_, const std::u32string& rep_) :
    LiteralNode(NodeKind::nullPtrLiteralNode, sourcePos_, rep_)
{
}

Node* NullPtrLiteralNode::Clone() const
{
    NullPtrLiteralNode* clone = new NullPtrLiteralNode(GetSourcePos(), Rep());
    return clone;
}

void NullPtrLiteralNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

UserDefinedLiteraNode::UserDefinedLiteraNode(const soul::ast::SourcePos& sourcePos_) noexcept : 
    BinaryNode(NodeKind::userDefinedLiteralNode, sourcePos_, nullptr, nullptr)
{
}

UserDefinedLiteraNode::UserDefinedLiteraNode(const soul::ast::SourcePos& sourcePos_, Node* literalNode_, Node* udSuffix_) noexcept :
    BinaryNode(NodeKind::userDefinedLiteralNode, sourcePos_, literalNode_, udSuffix_)
{
}

Node* UserDefinedLiteraNode::Clone() const
{
    UserDefinedLiteraNode* clone = new UserDefinedLiteraNode(GetSourcePos(), Left()->Clone(), Right()->Clone());
    return clone;
}

void UserDefinedLiteraNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

LiteralOperatorIdNode::LiteralOperatorIdNode(const soul::ast::SourcePos& sourcePos_) noexcept : UnaryNode(NodeKind::literalOperatorIdNode, sourcePos_, nullptr)
{
}

LiteralOperatorIdNode::LiteralOperatorIdNode(const soul::ast::SourcePos& sourcePos_, Node* id_, const soul::ast::SourcePos& stringLitPos_) noexcept :
    UnaryNode(NodeKind::literalOperatorIdNode, sourcePos_, id_), stringLitPos(stringLitPos_)
{
}

Node* LiteralOperatorIdNode::Clone() const
{
    LiteralOperatorIdNode* clone = new LiteralOperatorIdNode(GetSourcePos(), Child()->Clone(), stringLitPos);
    return clone;
}

void LiteralOperatorIdNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void LiteralOperatorIdNode::Write(Writer& writer)
{
    UnaryNode::Write(writer);
    writer.Write(stringLitPos);
}

void LiteralOperatorIdNode::Read(Reader& reader)
{
    UnaryNode::Read(reader);
    stringLitPos = reader.ReadSourcePos();
}

std::u32string EncodingPrefixStr(EncodingPrefix encodingPrefix)
{
    switch (encodingPrefix)
    {
        case EncodingPrefix::none: return std::u32string();
        case EncodingPrefix::u8: return std::u32string(U"u8");
        case EncodingPrefix::u: return std::u32string(U"u");
        case EncodingPrefix::U: return std::u32string(U"U");
        case EncodingPrefix::L: return std::u32string(U"L");
    }
    return std::u32string();
}

EncodingPrefix CommonEncodingPrefix(otava::ast::EncodingPrefix leftEncodingPrefix, otava::ast::EncodingPrefix rightEncodingPrefix) noexcept
{
    switch (leftEncodingPrefix)
    {
        case EncodingPrefix::none:
        {
            switch (rightEncodingPrefix)
            {
                case EncodingPrefix::none:
                {
                    return EncodingPrefix::none;
                }
                default:
                {
                    return rightEncodingPrefix;
                }
            }
            break;
        }
        default:
        {
            switch (rightEncodingPrefix)
            {
                case EncodingPrefix::none:
                {
                    return leftEncodingPrefix;
                }
                default:
                {
                    return EncodingPrefix::u8;
                }
            }
            break;
        }
    }
    return EncodingPrefix::u8;
}

} // namespace otava::ast
