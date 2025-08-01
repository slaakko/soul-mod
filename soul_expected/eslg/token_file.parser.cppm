
// this file has been automatically generated from 'D:/work/soul-mod/soul_expected/eslg/token_file.parser' using soul parser generator espg version 5.0.0

export module soul_expected.slg.token.file.parser;

import std;
import soul_expected.lexer;
import soul_expected.parser;
import soul_expected.ast.slg;

using namespace soul_expected::ast::slg;

export namespace soul_expected::slg::token::file::parser {

template<typename LexerT>
struct TokenFileParser
{
    static std::expected<std::unique_ptr<soul_expected::ast::slg::TokenFile>, int> Parse(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> TokenFile(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> Token(LexerT& lexer);
};

} // namespace soul_expected::slg::token::file::parser
