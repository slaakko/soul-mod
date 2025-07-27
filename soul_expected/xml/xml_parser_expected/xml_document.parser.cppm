
// this file has been automatically generated from 'D:/work/soul-mod/soul_expected/xml/xml_parser_expected/xml_document.parser' using soul parser generator espg version 5.0.0

export module soul_expected.xml.document.parser;

import std;
import soul_expected.lexer;
import soul_expected.parser;
import soul_expected.xml.processor;
import soul_expected.lexer.trivial;

using namespace soul_expected::xml::processor;
using namespace soul_expected::lexer::trivial;

export namespace soul_expected::xml::document::parser {

template<typename LexerT>
struct XmlParser
{
    static std::expected<bool, int> Parse(LexerT& lexer, soul_expected::xml::processor::XmlProcessor* processor);
    static std::expected<soul_expected::parser::Match, int> Document(LexerT& lexer, soul_expected::xml::processor::XmlProcessor* processor);
    static std::expected<soul_expected::parser::Match, int> Prolog(LexerT& lexer, soul_expected::xml::processor::XmlProcessor* processor);
    static std::expected<soul_expected::parser::Match, int> XmlDecl(LexerT& lexer, soul_expected::xml::processor::XmlProcessor* processor);
    static std::expected<soul_expected::parser::Match, int> VersionInfo(LexerT& lexer, soul_expected::xml::processor::XmlProcessor* processor);
    static std::expected<soul_expected::parser::Match, int> S(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> Eq(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> VersionNumber(LexerT& lexer, soul_expected::xml::processor::XmlProcessor* processor);
    static std::expected<soul_expected::parser::Match, int> VersionNumDQ(LexerT& lexer, soul_expected::xml::processor::XmlProcessor* processor);
    static std::expected<soul_expected::parser::Match, int> VersionNumSQ(LexerT& lexer, soul_expected::xml::processor::XmlProcessor* processor);
    static std::expected<soul_expected::parser::Match, int> VersionNum(LexerT& lexer, soul_expected::xml::processor::XmlProcessor* processor);
    static std::expected<soul_expected::parser::Match, int> EncodingDecl(LexerT& lexer, soul_expected::xml::processor::XmlProcessor* processor);
    static std::expected<soul_expected::parser::Match, int> EncodingName(LexerT& lexer, soul_expected::xml::processor::XmlProcessor* processor);
    static std::expected<soul_expected::parser::Match, int> EncNameDQ(LexerT& lexer, soul_expected::xml::processor::XmlProcessor* processor);
    static std::expected<soul_expected::parser::Match, int> EncNameSQ(LexerT& lexer, soul_expected::xml::processor::XmlProcessor* processor);
    static std::expected<soul_expected::parser::Match, int> EncName(LexerT& lexer, soul_expected::xml::processor::XmlProcessor* processor);
    static std::expected<soul_expected::parser::Match, int> StandaloneDecl(LexerT& lexer, soul_expected::xml::processor::XmlProcessor* processor);
    static std::expected<soul_expected::parser::Match, int> YesNo(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> Misc(LexerT& lexer, soul_expected::xml::processor::XmlProcessor* processor);
    static std::expected<soul_expected::parser::Match, int> Comment(LexerT& lexer, soul_expected::xml::processor::XmlProcessor* processor);
    static std::expected<soul_expected::parser::Match, int> Char(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> PI(LexerT& lexer, soul_expected::xml::processor::XmlProcessor* processor);
    static std::expected<soul_expected::parser::Match, int> PITarget(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> Name(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> NameStartChar(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> NameChar(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> Xml(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> Element(LexerT& lexer, soul_expected::xml::processor::XmlProcessor* processor);
    static std::expected<soul_expected::parser::Match, int> Attribute(LexerT& lexer, soul_expected::xml::processor::XmlProcessor* processor);
    static std::expected<soul_expected::parser::Match, int> AttValue(LexerT& lexer, soul_expected::xml::processor::XmlProcessor* processor);
    static std::expected<soul_expected::parser::Match, int> AttValueDQ(LexerT& lexer, soul_expected::xml::processor::XmlProcessor* processor);
    static std::expected<soul_expected::parser::Match, int> AttValueSQ(LexerT& lexer, soul_expected::xml::processor::XmlProcessor* processor);
    static std::expected<soul_expected::parser::Match, int> Reference(LexerT& lexer, soul_expected::xml::processor::XmlProcessor* processor);
    static std::expected<soul_expected::parser::Match, int> CharRef(LexerT& lexer, soul_expected::xml::processor::XmlProcessor* processor);
    static std::expected<soul_expected::parser::Match, int> DecCodePoint(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> HexCodePoint(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> EntityRef(LexerT& lexer, soul_expected::xml::processor::XmlProcessor* processor);
    static std::expected<soul_expected::parser::Match, int> Content(LexerT& lexer, soul_expected::xml::processor::XmlProcessor* processor);
    static std::expected<soul_expected::parser::Match, int> CharData(LexerT& lexer, soul_expected::xml::processor::XmlProcessor* processor);
    static std::expected<soul_expected::parser::Match, int> CharDataChar(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> CDSect(LexerT& lexer, soul_expected::xml::processor::XmlProcessor* processor);
    static std::expected<soul_expected::parser::Match, int> ETag(LexerT& lexer, soul_expected::xml::processor::XmlProcessor* processor);
    static std::expected<soul_expected::parser::Match, int> DocTypeDecl(LexerT& lexer, soul_expected::xml::processor::XmlProcessor* processor);
    static std::expected<soul_expected::parser::Match, int> ExternalID(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> SystemLiteral(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> PubidLiteral(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> PubidChar(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> IntSubset(LexerT& lexer, soul_expected::xml::processor::XmlProcessor* processor);
    static std::expected<soul_expected::parser::Match, int> MarkupDecl(LexerT& lexer, soul_expected::xml::processor::XmlProcessor* processor);
    static std::expected<soul_expected::parser::Match, int> ElementDecl(LexerT& lexer, soul_expected::xml::processor::XmlProcessor* processor);
    static std::expected<soul_expected::parser::Match, int> ContentSpec(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> Mixed(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> Choice(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> CP(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> Seq(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> Children(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> AttlistDecl(LexerT& lexer, soul_expected::xml::processor::XmlProcessor* processor);
    static std::expected<soul_expected::parser::Match, int> AttDef(LexerT& lexer, soul_expected::xml::processor::XmlProcessor* processor);
    static std::expected<soul_expected::parser::Match, int> AttType(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> StringType(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> TokenizedType(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> EnumeratedType(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> NotationType(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> Enumeration(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> Nmtoken(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> DefaultDecl(LexerT& lexer, soul_expected::xml::processor::XmlProcessor* processor);
    static std::expected<soul_expected::parser::Match, int> EntityDecl(LexerT& lexer, soul_expected::xml::processor::XmlProcessor* processor);
    static std::expected<soul_expected::parser::Match, int> GEDecl(LexerT& lexer, soul_expected::xml::processor::XmlProcessor* processor);
    static std::expected<soul_expected::parser::Match, int> EntityDef(LexerT& lexer, soul_expected::xml::processor::XmlProcessor* processor);
    static std::expected<soul_expected::parser::Match, int> EntityValue(LexerT& lexer, soul_expected::xml::processor::XmlProcessor* processor);
    static std::expected<soul_expected::parser::Match, int> PEReference(LexerT& lexer, soul_expected::xml::processor::XmlProcessor* processor);
    static std::expected<soul_expected::parser::Match, int> PEDecl(LexerT& lexer, soul_expected::xml::processor::XmlProcessor* processor);
    static std::expected<soul_expected::parser::Match, int> PEDef(LexerT& lexer, soul_expected::xml::processor::XmlProcessor* processor);
    static std::expected<soul_expected::parser::Match, int> NDataDecl(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> NotationDecl(LexerT& lexer, soul_expected::xml::processor::XmlProcessor* processor);
    static std::expected<soul_expected::parser::Match, int> DeclSep(LexerT& lexer, soul_expected::xml::processor::XmlProcessor* processor);
    static std::expected<soul_expected::parser::Match, int> PublicID(LexerT& lexer);
};

} // namespace soul_expected::xml::document::parser
