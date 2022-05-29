
// this file has been automatically generated from 'C:/work/soul-mod/soul/common/common_parser.parser' using soul parser generator spg version 4.0.0

export module soul.common.common.parser;

import std.core;
import soul.lexer;
import soul.parser;
import soul.ast.common;

using namespace soul::ast::common;

export namespace soul::common::common::parser {

template<typename Lexer>
struct CommonParser
{
    static soul::parser::Match QualifiedId(Lexer& lexer);
    static soul::parser::Match ExportModule(Lexer& lexer);
    static soul::parser::Match Import(Lexer& lexer);
    static soul::parser::Match ImportPrefix(Lexer& lexer);
    static soul::parser::Match ExprString(Lexer& lexer);
    static soul::parser::Match FilePath(Lexer& lexer);
    static soul::parser::Match ExportKeyword(Lexer& lexer);
    static soul::parser::Match ModuleKeyword(Lexer& lexer);
    static soul::parser::Match ImportKeyword(Lexer& lexer);
    static soul::parser::Match ImplementationPrefix(Lexer& lexer);
    static soul::parser::Match InterfacePrefix(Lexer& lexer);
    static soul::parser::Match ImplementationKeyword(Lexer& lexer);
    static soul::parser::Match InterfaceKeyword(Lexer& lexer);
    static soul::parser::Match ParserKeyword(Lexer& lexer);
    static soul::parser::Match LexerKeyword(Lexer& lexer);
};

} // namespace soul::common::common::parser
