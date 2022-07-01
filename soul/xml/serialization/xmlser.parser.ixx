
// this file has been automatically generated from 'C:/work/soul-mod/soul/xml/serialization/xmlser.parser' using soul parser generator spg version 4.0.0

export module soul.xml.serialization.parser;

import std.core;
import soul.lexer;
import soul.parser;
import soul.xml.serialization.ast;

using namespace soul::xml::serialization::ast;

export namespace soul::xml::serialization::parser {

template<typename Lexer>
struct XmlSerParser
{
    static std::unique_ptr<soul::xml::serialization::ast::SourceFileNode> Parse(Lexer& lexer);
    static soul::parser::Match SourceFile(Lexer& lexer);
    static soul::parser::Match NamespaceContent(Lexer& lexer, soul::xml::serialization::ast::NamespaceNode* ns);
    static soul::parser::Match Declaration(Lexer& lexer);
    static soul::parser::Match ForwardClassDeclaration(Lexer& lexer);
    static soul::parser::Match UsingAliasDeclaration(Lexer& lexer);
    static soul::parser::Match Definition(Lexer& lexer);
    static soul::parser::Match Class(Lexer& lexer);
    static soul::parser::Match Inheritance(Lexer& lexer, soul::xml::serialization::ast::ClassNode* cls);
    static soul::parser::Match ClassContent(Lexer& lexer, soul::xml::serialization::ast::ClassNode* cls);
    static soul::parser::Match MemberVariable(Lexer& lexer);
    static soul::parser::Match Type(Lexer& lexer);
    static soul::parser::Match ScalarType(Lexer& lexer);
    static soul::parser::Match ClassType(Lexer& lexer);
    static soul::parser::Match CppBlock(Lexer& lexer, bool implementation);
    static soul::parser::Match Enum(Lexer& lexer);
    static soul::parser::Match EnumContent(Lexer& lexer, soul::xml::serialization::ast::EnumTypeNode* enm);
    static soul::parser::Match EnumConstant(Lexer& lexer);
    static soul::parser::Match Namespace(Lexer& lexer);
    static soul::parser::Match QualifiedId(Lexer& lexer);
    static soul::parser::Match QualifiedCppId(Lexer& lexer);
    static soul::parser::Match ExportModule(Lexer& lexer);
    static soul::parser::Match Import(Lexer& lexer);
    static soul::parser::Match ImportPrefix(Lexer& lexer);
    static soul::parser::Match ExportKeyword(Lexer& lexer);
    static soul::parser::Match ModuleKeyword(Lexer& lexer);
    static soul::parser::Match ImportKeyword(Lexer& lexer);
    static soul::parser::Match ImplementationPrefix(Lexer& lexer);
    static soul::parser::Match InterfacePrefix(Lexer& lexer);
    static soul::parser::Match ImplementationKeyword(Lexer& lexer);
    static soul::parser::Match InterfaceKeyword(Lexer& lexer);
};

} // namespace soul::xml::serialization::parser
