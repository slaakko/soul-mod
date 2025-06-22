
// this file has been automatically generated from 'C:/work/soul-mod/soul/slg/keyword_file.parser' using soul parser generator spg version 5.0.0

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
    static std::unique_ptr<soul::ast::slg::KeywordFile> Parse(LexerT& lexer);
    static soul::parser::Match KeywordFile(LexerT& lexer);
    static soul::parser::Match Imports(LexerT& lexer, soul::ast::slg::KeywordFile* keywordFile);
    static soul::parser::Match Keyword(LexerT& lexer);
};

} // namespace soul::slg::keyword::file::parser
