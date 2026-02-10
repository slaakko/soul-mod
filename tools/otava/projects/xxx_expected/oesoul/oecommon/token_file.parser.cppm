
// this file has been automatically generated from 'D:/work/soul-mod/tools/otava/projects/osoul/ocommon/token_file.parser' using soul parser generator ospg version 5.0.0

export module soul.common.token.file.parser;

import std;
import soul.lexer;
import soul.parser;
import soul.ast.slg;
import soul.ast.common;

export namespace soul::common::token::file::parser {

template<typename LexerT>
struct TokenFileParser
{
    static std::expected<std::unique_ptr<soul::ast::common::TokenFile>, int> Parse(LexerT& lexer);
    static std::expected<soul::parser::Match, int> TokenFile(LexerT& lexer);
    static std::expected<soul::parser::Match, int> Token(LexerT& lexer);
};

} // namespace soul::common::token::file::parser
