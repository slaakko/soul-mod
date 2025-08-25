
// this file has been automatically generated from 'D:/work/soul-mod/soul_expected/espg/spg_file.parser' using soul parser generator espg version 5.0.0

export module soul_expected.spg.spg.file.parser;

import std;
import soul_expected.lexer;
import soul_expected.parser;
import soul_expected.ast.spg;
import soul_expected.ast.common;

export namespace soul_expected::spg::spg::file::parser {

template<typename LexerT>
struct SpgFileParser
{
    static std::expected<std::unique_ptr<soul_expected::ast::spg::SpgFile>, int> Parse(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> SpgFile(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> SpgFileDeclaration(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> ParserFileDeclaration(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> TokenFileDeclaration(LexerT& lexer);
};

} // namespace soul_expected::spg::spg::file::parser
