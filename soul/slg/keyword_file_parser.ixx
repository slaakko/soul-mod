
// this file has been automatically generated from 'C:/work/soul-mod/soul/slg/keyword_file_parser.parser' using soul parser generator spg version 4.0.0

export module soul.slg.keyword.file.parser;

import std.core;
import soul.lexer;
import soul.parser;
import soul.ast.slg;

using namespace soul::ast::slg;

export namespace soul::slg::keyword::file::parser {

template<typename Lexer>
struct KeywordFileParser
{
    static std::unique_ptr<soul::ast::slg::KeywordFile> Parse(Lexer& lexer);
    static soul::parser::Match KeywordFile(Lexer& lexer);
    static soul::parser::Match Imports(Lexer& lexer, soul::ast::slg::KeywordFile* keywordFile);
    static soul::parser::Match Keyword(Lexer& lexer);
};

} // namespace soul::slg::keyword::file::parser
