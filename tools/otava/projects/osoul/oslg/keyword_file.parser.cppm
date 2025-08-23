
// this file has been automatically generated from 'D:/work/soul-mod/tools/otava/projects/osoul/oslg/keyword_file.parser' using soul parser generator oespg version 5.0.0

export module soul.slg.keyword.file.parser;

import std;
import soul.lexer;
import soul.parser;
import soul.ast.slg;

using namespace soul::ast::slg;

export namespace soul::slg::keyword::file::parser {

template<typename LexerT>
struct KeywordFileParser
{
    static std::expected<std::unique_ptr<soul::ast::slg::KeywordFile>, int> Parse(LexerT& lexer);
    static std::expected<soul::parser::Match, int> KeywordFile(LexerT& lexer);
    static std::expected<soul::parser::Match, int> Imports(LexerT& lexer, soul::ast::slg::KeywordFile* keywordFile);
    static std::expected<soul::parser::Match, int> Keyword(LexerT& lexer);
};

} // namespace soul::slg::keyword::file::parser
