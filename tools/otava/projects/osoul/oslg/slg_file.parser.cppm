
// this file has been automatically generated from 'D:/work/soul-mod/tools/otava/projects/osoul/oslg/slg_file.parser' using soul parser generator oespg version 5.0.0

export module soul.slg.slg.file.parser;

import std;
import soul.lexer;
import soul.parser;
import soul.ast.slg;

using namespace soul::ast::slg;

export namespace soul::slg::slg::file::parser {

template<typename LexerT>
struct SlgFileParser
{
    static std::expected<std::unique_ptr<soul::ast::slg::SlgFile>, int> Parse(LexerT& lexer);
    static std::expected<soul::parser::Match, int> SlgFile(LexerT& lexer);
    static std::expected<soul::parser::Match, int> SlgFileDeclaration(LexerT& lexer);
    static std::expected<soul::parser::Match, int> TokenFileDeclaration(LexerT& lexer);
    static std::expected<soul::parser::Match, int> KeywordFileDeclaration(LexerT& lexer);
    static std::expected<soul::parser::Match, int> ExpressionFileDeclaration(LexerT& lexer);
    static std::expected<soul::parser::Match, int> LexerFileDeclaration(LexerT& lexer);
};

} // namespace soul::slg::slg::file::parser
