
// this file has been automatically generated from 'D:/work/soul-mod/soul_expected/test/eslg_test/slg_file.parser' using soul parser generator espg version 5.0.0

export module soul_expected.slg.slg.file.parser;

import std;
import soul_expected.lexer;
import soul_expected.parser;
import soul_expected.ast.slg;

using namespace soul_expected::ast::slg;

export namespace soul_expected::slg::slg::file::parser {

template<typename LexerT>
struct SlgFileParser
{
    static std::expected<std::unique_ptr<soul_expected::ast::slg::SlgFile>, int> Parse(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> SlgFile(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> SlgFileDeclaration(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> TokenFileDeclaration(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> KeywordFileDeclaration(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> ExpressionFileDeclaration(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> LexerFileDeclaration(LexerT& lexer);
};

} // namespace soul_expected::slg::slg::file::parser
