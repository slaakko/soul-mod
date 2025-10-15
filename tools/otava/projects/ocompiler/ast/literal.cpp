// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.ast.literal;

import otava.ast.visitor;
import otava.ast.reader;
import otava.ast.writer;

namespace otava::ast {

LiteralNode::LiteralNode(NodeKind kind_, const soul::ast::SourcePos& sourcePos_) : Node(kind_, sourcePos_), rep()
{
}

LiteralNode::LiteralNode(NodeKind kind_, const soul::ast::SourcePos& sourcePos_, const std::u32string& rep_) : Node(kind_, sourcePos_), rep(rep_)
{
}

std::expected<bool, int> LiteralNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = Node::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(rep);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> LiteralNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = Node::Read(reader);
    if (!rv) return rv;
    std::expected<std::u32string, int> srv = reader.ReadStr();
    if (!srv) return std::unexpected<int>(srv.error());
    rep = *srv;
    return std::expected<bool, int>(true);
}

IntegerLiteralNode::IntegerLiteralNode(const soul::ast::SourcePos& sourcePos_) : LiteralNode(NodeKind::integerLiteralNode, sourcePos_), value(), suffix(), base()
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

std::expected<bool, int> IntegerLiteralNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = LiteralNode::Write(writer);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(value);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(static_cast<std::uint8_t>(suffix));
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(static_cast<std::uint8_t>(base));
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> IntegerLiteralNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = LiteralNode::Read(reader);
    if (!rv) return rv;
    std::expected<std::uint64_t, int> lrv = reader.GetBinaryStreamReader().ReadULong();
    if (!lrv) return std::unexpected<int>(rv.error());
    value = *lrv;
    std::expected<std::uint8_t, int> brv = reader.GetBinaryStreamReader().ReadByte();
    if (!brv) return std::unexpected<int>(brv.error());
    std::uint8_t s = *brv;
    suffix = static_cast<Suffix>(s);
    brv = reader.GetBinaryStreamReader().ReadByte();
    if (!brv) return std::unexpected<int>(brv.error());
    s = *brv;
    base = static_cast<Base>(s);
    return std::expected<bool, int>(true);
}

FloatingLiteralNode::FloatingLiteralNode(const soul::ast::SourcePos& sourcePos_) : LiteralNode(NodeKind::floatingLiteralNode, sourcePos_), value(), suffix(), base()
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

std::expected<bool, int> FloatingLiteralNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = LiteralNode::Write(writer);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(value);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(static_cast<std::uint8_t>(suffix));
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(static_cast<std::uint8_t>(base));
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> FloatingLiteralNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = LiteralNode::Read(reader);
    if (!rv) return rv;
    std::expected<double, int> drv = reader.GetBinaryStreamReader().ReadDouble();
    if (!drv) return std::unexpected<int>(drv.error());
    value = *drv;
    std::expected<std::uint8_t, int> brv = reader.GetBinaryStreamReader().ReadByte();
    if (!brv) return std::unexpected<int>(brv.error());
    std::uint8_t s = *brv;
    suffix = static_cast<Suffix>(s);
    brv = reader.GetBinaryStreamReader().ReadByte();
    if (!brv) return std::unexpected<int>(brv.error());
    s = *brv;
    base = static_cast<Base>(s);
    return std::expected<bool, int>(true);
}

CharacterLiteralNode::CharacterLiteralNode(const soul::ast::SourcePos& sourcePos_) : LiteralNode(NodeKind::characterLiteralNode, sourcePos_), value(), encodingPrefix(), hasMultipleCharacters(false)
{
}

CharacterLiteralNode::CharacterLiteralNode(const soul::ast::SourcePos& sourcePos_, char32_t value_, EncodingPrefix encodingPrefix_, const std::u32string& rep_, bool hasMultipleCharacters_) :
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

std::expected<bool, int> CharacterLiteralNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = LiteralNode::Write(writer);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(value);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(static_cast<std::uint8_t>(encodingPrefix));
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(hasMultipleCharacters);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> CharacterLiteralNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = LiteralNode::Read(reader);
    if (!rv) return rv;
    std::expected<char32_t, int> crv = reader.GetBinaryStreamReader().ReadUChar();
    if (!crv) return std::unexpected<int>(crv.error());
    value = *crv;
    std::expected<std::uint8_t, int> brv = reader.GetBinaryStreamReader().ReadByte();
    if (!brv) return std::unexpected<int>(brv.error());
    std::uint8_t e = *brv;
    encodingPrefix = static_cast<EncodingPrefix>(e);
    std::expected<bool, int> mrv = reader.GetBinaryStreamReader().ReadBool();
    if (!mrv) return mrv;
    hasMultipleCharacters = *mrv;
    return std::expected<bool, int>(true);
}

StringLiteralNode::StringLiteralNode(const soul::ast::SourcePos& sourcePos_) : LiteralNode(NodeKind::stringLiteralNode, sourcePos_), value(), encodingPrefix()
{
}

StringLiteralNode::StringLiteralNode(NodeKind kind_, const soul::ast::SourcePos& sourcePos_) : LiteralNode(kind_, sourcePos_), value(), encodingPrefix()
{
}

StringLiteralNode::StringLiteralNode(const soul::ast::SourcePos& sourcePos_, const std::u32string& value_, EncodingPrefix encodingPrefix_, const std::u32string& rep_) :
    LiteralNode(NodeKind::stringLiteralNode, sourcePos_, rep_), value(value_), encodingPrefix(encodingPrefix_)
{
}

StringLiteralNode::StringLiteralNode(NodeKind kind_, const soul::ast::SourcePos& sourcePos_, const std::u32string& value_, EncodingPrefix encodingPrefix_, const std::u32string& rep_) :
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

std::expected<bool, int> StringLiteralNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = LiteralNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(value);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(static_cast<std::uint8_t>(encodingPrefix));
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> StringLiteralNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = LiteralNode::Read(reader);
    if (!rv) return rv;
    std::expected<std::u32string, int> srv = reader.ReadStr();
    if (!srv) return std::unexpected<int>(srv.error());
    value = *srv;
    std::expected<std::uint8_t, int> brv = reader.GetBinaryStreamReader().ReadByte();
    if (!brv) return std::unexpected<int>(brv.error());
    std::uint8_t b = *brv;
    encodingPrefix = static_cast<EncodingPrefix>(b);
    return std::expected<bool, int>(true);
}

RawStringLiteralNode::RawStringLiteralNode(const soul::ast::SourcePos& sourcePos_) : StringLiteralNode(NodeKind::rawStringLiteralNode, sourcePos_)
{
}

RawStringLiteralNode::RawStringLiteralNode(const soul::ast::SourcePos& sourcePos_, const std::u32string& value_, EncodingPrefix encodingPrefix_,
    const std::u32string& delimSequence_, const std::u32string& rep_) :
    StringLiteralNode(NodeKind::rawStringLiteralNode, sourcePos_, value_, encodingPrefix_, rep_), delimSequence(delimSequence_)
{
}

Node* RawStringLiteralNode::Clone() const
{
    RawStringLiteralNode* clone = new RawStringLiteralNode(GetSourcePos(), Value(), EncodingPrefix(), delimSequence, Rep());
    return clone;
}

void RawStringLiteralNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> RawStringLiteralNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = StringLiteralNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(delimSequence);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> RawStringLiteralNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = StringLiteralNode::Read(reader);
    if (!rv) return rv;
    std::expected<std::u32string, int> srv = reader.ReadStr();
    if (!srv) return std::unexpected<int>(srv.error());
    delimSequence = *srv;
    return std::expected<bool, int>(true);
}

BooleanLiteralNode::BooleanLiteralNode(const soul::ast::SourcePos& sourcePos_) : LiteralNode(NodeKind::booleanLiteralNode, sourcePos_), value()
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

std::expected<bool, int> BooleanLiteralNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = LiteralNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(value);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> BooleanLiteralNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = LiteralNode::Read(reader);
    if (!rv) return rv;
    std::expected<bool, int> brv = reader.ReadBool();
    if (!brv) return brv;
    value = *brv;
    return std::expected<bool, int>(true);
}

NullPtrLiteralNode::NullPtrLiteralNode(const soul::ast::SourcePos& sourcePos_) : LiteralNode(NodeKind::nullPtrLiteralNode, sourcePos_)
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

UserDefinedLiteraNode::UserDefinedLiteraNode(const soul::ast::SourcePos& sourcePos_) : BinaryNode(NodeKind::userDefinedLiteralNode, sourcePos_, nullptr, nullptr)
{
}

UserDefinedLiteraNode::UserDefinedLiteraNode(const soul::ast::SourcePos& sourcePos_, Node* literalNode_, Node* udSuffix_) :
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

LiteralOperatorIdNode::LiteralOperatorIdNode(const soul::ast::SourcePos& sourcePos_) : UnaryNode(NodeKind::literalOperatorIdNode, sourcePos_, nullptr)
{
}

LiteralOperatorIdNode::LiteralOperatorIdNode(const soul::ast::SourcePos& sourcePos_, Node* id_, const soul::ast::SourcePos& stringLitPos_) :
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

std::expected<bool, int> LiteralOperatorIdNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = UnaryNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(stringLitPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> LiteralOperatorIdNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = UnaryNode::Read(reader);
    if (!rv) return rv;
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    stringLitPos = *posRv;
    return std::expected<bool, int>(true);
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

EncodingPrefix CommonEncodingPrefix(otava::ast::EncodingPrefix leftEncodingPrefix, otava::ast::EncodingPrefix rightEncodingPrefix)
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
