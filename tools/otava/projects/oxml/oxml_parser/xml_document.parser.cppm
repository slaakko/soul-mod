
// this file has been automatically generated from 'D:/work/soul-mod/tools/otava/projects/oxml/oxml_parser/xml_document.parser' using soul parser generator ospg version 5.0.0

export module soul.xml.document.parser;

import std;
import soul.lexer;
import soul.parser;
import soul.xml.processor;
import soul.lexer;

export namespace soul::xml::document::parser {

template<typename LexerT>
struct XmlParser
{
    static std::expected<bool, int> Parse(LexerT& lexer, soul::xml::processor::XmlProcessor* processor);
    static std::expected<soul::parser::Match, int> Document(LexerT& lexer, soul::xml::processor::XmlProcessor* processor);
    static std::expected<soul::parser::Match, int> Prolog(LexerT& lexer, soul::xml::processor::XmlProcessor* processor);
    static std::expected<soul::parser::Match, int> XmlDecl(LexerT& lexer, soul::xml::processor::XmlProcessor* processor);
    static std::expected<soul::parser::Match, int> VersionInfo(LexerT& lexer, soul::xml::processor::XmlProcessor* processor);
    static std::expected<soul::parser::Match, int> S(LexerT& lexer);
    static std::expected<soul::parser::Match, int> Eq(LexerT& lexer);
    static std::expected<soul::parser::Match, int> VersionNumber(LexerT& lexer, soul::xml::processor::XmlProcessor* processor);
    static std::expected<soul::parser::Match, int> VersionNumDQ(LexerT& lexer, soul::xml::processor::XmlProcessor* processor);
    static std::expected<soul::parser::Match, int> VersionNumSQ(LexerT& lexer, soul::xml::processor::XmlProcessor* processor);
    static std::expected<soul::parser::Match, int> VersionNum(LexerT& lexer, soul::xml::processor::XmlProcessor* processor);
    static std::expected<soul::parser::Match, int> EncodingDecl(LexerT& lexer, soul::xml::processor::XmlProcessor* processor);
    static std::expected<soul::parser::Match, int> EncodingName(LexerT& lexer, soul::xml::processor::XmlProcessor* processor);
    static std::expected<soul::parser::Match, int> EncNameDQ(LexerT& lexer, soul::xml::processor::XmlProcessor* processor);
    static std::expected<soul::parser::Match, int> EncNameSQ(LexerT& lexer, soul::xml::processor::XmlProcessor* processor);
    static std::expected<soul::parser::Match, int> EncName(LexerT& lexer, soul::xml::processor::XmlProcessor* processor);
    static std::expected<soul::parser::Match, int> StandaloneDecl(LexerT& lexer, soul::xml::processor::XmlProcessor* processor);
    static std::expected<soul::parser::Match, int> YesNo(LexerT& lexer);
    static std::expected<soul::parser::Match, int> Misc(LexerT& lexer, soul::xml::processor::XmlProcessor* processor);
    static std::expected<soul::parser::Match, int> Comment(LexerT& lexer, soul::xml::processor::XmlProcessor* processor);
    static std::expected<soul::parser::Match, int> Char(LexerT& lexer);
    static std::expected<soul::parser::Match, int> PI(LexerT& lexer, soul::xml::processor::XmlProcessor* processor);
    static std::expected<soul::parser::Match, int> PITarget(LexerT& lexer);
    static std::expected<soul::parser::Match, int> Name(LexerT& lexer);
    static std::expected<soul::parser::Match, int> NameStartChar(LexerT& lexer);
    static std::expected<soul::parser::Match, int> NameChar(LexerT& lexer);
    static std::expected<soul::parser::Match, int> Xml(LexerT& lexer);
    static std::expected<soul::parser::Match, int> Element(LexerT& lexer, soul::xml::processor::XmlProcessor* processor);
    static std::expected<soul::parser::Match, int> Attribute(LexerT& lexer, soul::xml::processor::XmlProcessor* processor);
    static std::expected<soul::parser::Match, int> AttValue(LexerT& lexer, soul::xml::processor::XmlProcessor* processor);
    static std::expected<soul::parser::Match, int> AttValueDQ(LexerT& lexer, soul::xml::processor::XmlProcessor* processor);
    static std::expected<soul::parser::Match, int> AttValueSQ(LexerT& lexer, soul::xml::processor::XmlProcessor* processor);
    static std::expected<soul::parser::Match, int> Reference(LexerT& lexer, soul::xml::processor::XmlProcessor* processor);
    static std::expected<soul::parser::Match, int> CharRef(LexerT& lexer, soul::xml::processor::XmlProcessor* processor);
    static std::expected<soul::parser::Match, int> DecCodePoint(LexerT& lexer);
    static std::expected<soul::parser::Match, int> HexCodePoint(LexerT& lexer);
    static std::expected<soul::parser::Match, int> EntityRef(LexerT& lexer, soul::xml::processor::XmlProcessor* processor);
    static std::expected<soul::parser::Match, int> Content(LexerT& lexer, soul::xml::processor::XmlProcessor* processor);
    static std::expected<soul::parser::Match, int> CharData(LexerT& lexer, soul::xml::processor::XmlProcessor* processor);
    static std::expected<soul::parser::Match, int> CharDataChar(LexerT& lexer);
    static std::expected<soul::parser::Match, int> CDSect(LexerT& lexer, soul::xml::processor::XmlProcessor* processor);
    static std::expected<soul::parser::Match, int> ETag(LexerT& lexer, soul::xml::processor::XmlProcessor* processor);
    static std::expected<soul::parser::Match, int> DocTypeDecl(LexerT& lexer, soul::xml::processor::XmlProcessor* processor);
    static std::expected<soul::parser::Match, int> ExternalID(LexerT& lexer);
    static std::expected<soul::parser::Match, int> SystemLiteral(LexerT& lexer);
    static std::expected<soul::parser::Match, int> PubidLiteral(LexerT& lexer);
    static std::expected<soul::parser::Match, int> PubidChar(LexerT& lexer);
    static std::expected<soul::parser::Match, int> IntSubset(LexerT& lexer, soul::xml::processor::XmlProcessor* processor);
    static std::expected<soul::parser::Match, int> MarkupDecl(LexerT& lexer, soul::xml::processor::XmlProcessor* processor);
    static std::expected<soul::parser::Match, int> ElementDecl(LexerT& lexer, soul::xml::processor::XmlProcessor* processor);
    static std::expected<soul::parser::Match, int> ContentSpec(LexerT& lexer);
    static std::expected<soul::parser::Match, int> Mixed(LexerT& lexer);
    static std::expected<soul::parser::Match, int> Choice(LexerT& lexer);
    static std::expected<soul::parser::Match, int> CP(LexerT& lexer);
    static std::expected<soul::parser::Match, int> Seq(LexerT& lexer);
    static std::expected<soul::parser::Match, int> Children(LexerT& lexer);
    static std::expected<soul::parser::Match, int> AttlistDecl(LexerT& lexer, soul::xml::processor::XmlProcessor* processor);
    static std::expected<soul::parser::Match, int> AttDef(LexerT& lexer, soul::xml::processor::XmlProcessor* processor);
    static std::expected<soul::parser::Match, int> AttType(LexerT& lexer);
    static std::expected<soul::parser::Match, int> StringType(LexerT& lexer);
    static std::expected<soul::parser::Match, int> TokenizedType(LexerT& lexer);
    static std::expected<soul::parser::Match, int> EnumeratedType(LexerT& lexer);
    static std::expected<soul::parser::Match, int> NotationType(LexerT& lexer);
    static std::expected<soul::parser::Match, int> Enumeration(LexerT& lexer);
    static std::expected<soul::parser::Match, int> Nmtoken(LexerT& lexer);
    static std::expected<soul::parser::Match, int> DefaultDecl(LexerT& lexer, soul::xml::processor::XmlProcessor* processor);
    static std::expected<soul::parser::Match, int> EntityDecl(LexerT& lexer, soul::xml::processor::XmlProcessor* processor);
    static std::expected<soul::parser::Match, int> GEDecl(LexerT& lexer, soul::xml::processor::XmlProcessor* processor);
    static std::expected<soul::parser::Match, int> EntityDef(LexerT& lexer, soul::xml::processor::XmlProcessor* processor);
    static std::expected<soul::parser::Match, int> EntityValue(LexerT& lexer, soul::xml::processor::XmlProcessor* processor);
    static std::expected<soul::parser::Match, int> PEReference(LexerT& lexer, soul::xml::processor::XmlProcessor* processor);
    static std::expected<soul::parser::Match, int> PEDecl(LexerT& lexer, soul::xml::processor::XmlProcessor* processor);
    static std::expected<soul::parser::Match, int> PEDef(LexerT& lexer, soul::xml::processor::XmlProcessor* processor);
    static std::expected<soul::parser::Match, int> NDataDecl(LexerT& lexer);
    static std::expected<soul::parser::Match, int> NotationDecl(LexerT& lexer, soul::xml::processor::XmlProcessor* processor);
    static std::expected<soul::parser::Match, int> DeclSep(LexerT& lexer, soul::xml::processor::XmlProcessor* processor);
    static std::expected<soul::parser::Match, int> PublicID(LexerT& lexer);
};

} // namespace soul::xml::document::parser
