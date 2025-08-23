
// this file has been automatically generated from 'D:/work/soul-mod/tools/otava/projects/osoul/oslg/token_file.parser' using soul parser generator oespg version 5.0.0

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
    static std::expected<std::unique_ptr<soul::ast::slg::TokenFile>, int> Parse(LexerT& lexer);
    static std::expected<soul::parser::Match, int> TokenFile(LexerT& lexer);
    static std::expected<soul::parser::Match, int> Token(LexerT& lexer);
};

} // namespace soul::slg::token::file::parser
