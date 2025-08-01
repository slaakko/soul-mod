
// this file has been automatically generated from 'D:/work/soul-mod/soul/slg/token_file.parser' using soul parser generator spg version 5.0.0

export module soul.slg.token.file.parser;

import std;
import soul.lexer;
import soul.parser;
import soul.ast.slg;

using namespace soul::ast::slg;

export namespace soul::slg::token::file::parser {

template<typename LexerT>
struct TokenFileParser
{
    static std::unique_ptr<soul::ast::slg::TokenFile> Parse(LexerT& lexer);
    static soul::parser::Match TokenFile(LexerT& lexer);
    static soul::parser::Match Token(LexerT& lexer);
};

} // namespace soul::slg::token::file::parser
