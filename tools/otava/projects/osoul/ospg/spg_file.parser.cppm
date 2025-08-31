
// this file has been automatically generated from 'D:/work/soul-mod/tools/otava/projects/osoul/ospg/spg_file.parser' using soul parser generator ospg version 5.0.0

export module soul.spg.spg.file.parser;

import std;
import soul.lexer;
import soul.parser;
import soul.ast.spg;
import soul.ast.common;

export namespace soul::spg::spg::file::parser {

template<typename LexerT>
struct SpgFileParser
{
    static std::expected<std::unique_ptr<soul::ast::spg::SpgFile>, int> Parse(LexerT& lexer);
    static std::expected<soul::parser::Match, int> SpgFile(LexerT& lexer);
    static std::expected<soul::parser::Match, int> SpgFileDeclaration(LexerT& lexer);
    static std::expected<soul::parser::Match, int> ParserFileDeclaration(LexerT& lexer);
    static std::expected<soul::parser::Match, int> TokenFileDeclaration(LexerT& lexer);
};

} // namespace soul::spg::spg::file::parser
