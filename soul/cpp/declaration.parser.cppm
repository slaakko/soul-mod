
// this file has been automatically generated from 'C:/work/soul-mod/soul/cpp/declaration.parser' using soul parser generator spg version 4.1.0

export module soul.cpp.declaration.parser;

import std.core;
import soul.lexer;
import soul.parser;
import soul.ast.cpp;

using namespace soul::ast::cpp;

export namespace soul::cpp::declaration::parser {

template<typename Lexer>
struct DeclarationParser
{
    static soul::parser::Match BlockDeclaration(Lexer& lexer);
    static soul::parser::Match SimpleDeclaration(Lexer& lexer);
    static soul::parser::Match DeclSpecifierSeq(Lexer& lexer, soul::ast::cpp::SimpleDeclarationNode* declaration);
    static soul::parser::Match DeclSpecifier(Lexer& lexer);
    static soul::parser::Match StorageClassSpecifier(Lexer& lexer);
    static soul::parser::Match TypeSpecifier(Lexer& lexer);
    static soul::parser::Match SimpleTypeSpecifier(Lexer& lexer);
    static soul::parser::Match TypeName(Lexer& lexer);
    static soul::parser::Match TemplateArgumentList(Lexer& lexer, soul::ast::cpp::TypeNameNode* typeName);
    static soul::parser::Match TemplateArgument(Lexer& lexer);
    static soul::parser::Match Typedef(Lexer& lexer);
    static soul::parser::Match CVQualifier(Lexer& lexer);
    static soul::parser::Match NamespaceAliasDefinition(Lexer& lexer);
    static soul::parser::Match UsingDeclaration(Lexer& lexer);
    static soul::parser::Match UsingDirective(Lexer& lexer);
};

} // namespace soul::cpp::declaration::parser
