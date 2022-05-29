
// this file has been automatically generated from 'C:/work/soul-mod/soul/slg/token_file_parser.parser' using soul parser generator spg version 4.0.0

export module soul.slg.token.file.parser;

import std.core;
import soul.lexer;
import soul.parser;
import soul.ast.slg;

using namespace soul::ast::slg;

export namespace soul::slg::token::file::parser {

template<typename Lexer>
struct TokenFileParser
{
    static std::unique_ptr<soul::ast::slg::TokenFile> Parse(Lexer& lexer);
    static soul::parser::Match TokenFile(Lexer& lexer);
    static soul::parser::Match Token(Lexer& lexer);
};

} // namespace soul::slg::token::file::parser
