
// this file has been automatically generated from 'D:/work/soul-mod/soul_expected/eslg/keyword_file.parser' using soul parser generator espg version 5.0.0

export module soul_expected.slg.keyword.file.parser;

import std;
import soul_expected.lexer;
import soul_expected.parser;
import soul_expected.ast.slg;

export namespace soul_expected::slg::keyword::file::parser {

template<typename LexerT>
struct KeywordFileParser
{
    static std::expected<std::unique_ptr<soul_expected::ast::slg::KeywordFile>, int> Parse(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> KeywordFile(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> Imports(LexerT& lexer, soul_expected::ast::slg::KeywordFile* keywordFile);
    static std::expected<soul_expected::parser::Match, int> Keyword(LexerT& lexer);
};

} // namespace soul_expected::slg::keyword::file::parser
