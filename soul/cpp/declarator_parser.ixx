
// this file has been automatically generated from 'C:/work/soul-mod/soul/cpp/declarator_parser.parser' using soul parser generator spg version 4.0.0

export module soul.cpp.declarator.parser;

import std.core;
import soul.lexer;
import soul.parser;
import soul.ast.cpp;

using namespace soul::ast::cpp;

export namespace soul::cpp::declarator::parser {

template<typename Lexer>
struct DeclaratorParser
{
    static soul::parser::Match InitDeclaratorList(Lexer& lexer);
    static soul::parser::Match InitDeclarator(Lexer& lexer);
    static soul::parser::Match Declarator(Lexer& lexer);
    static soul::parser::Match DirectDeclarator(Lexer& lexer);
    static soul::parser::Match DeclaratorId(Lexer& lexer);
    static soul::parser::Match TypeId(Lexer& lexer);
    static soul::parser::Match Type(Lexer& lexer);
    static soul::parser::Match TypeSpecifierSeq(Lexer& lexer, soul::ast::cpp::TypeIdNode* typeId);
    static soul::parser::Match AbstractDeclarator(Lexer& lexer);
    static soul::parser::Match DirectAbstractDeclarator(Lexer& lexer);
    static soul::parser::Match PtrOperator(Lexer& lexer);
    static soul::parser::Match CVQualifierSeq(Lexer& lexer);
    static soul::parser::Match Initializer(Lexer& lexer);
    static soul::parser::Match InitializerClause(Lexer& lexer);
    static soul::parser::Match InitializerList(Lexer& lexer, soul::ast::cpp::AssignInitNode* init);
};

} // namespace soul::cpp::declarator::parser
