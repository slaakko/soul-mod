
// this file has been automatically generated from 'C:/work/soul-mod/soul/slg/slg_file.parser' using soul parser generator spg version 4.1.0

export module soul.slg.slg.file.parser;

import std.core;
import soul.lexer;
import soul.parser;
import soul.ast.slg;

using namespace soul::ast::slg;

export namespace soul::slg::slg::file::parser {

template<typename LexerT>
struct SlgFileParser
{
    static std::unique_ptr<soul::ast::slg::SlgFile> Parse(LexerT& lexer);
    static soul::parser::Match SlgFile(LexerT& lexer);
    static soul::parser::Match SlgFileDeclaration(LexerT& lexer);
    static soul::parser::Match TokenFileDeclaration(LexerT& lexer);
    static soul::parser::Match KeywordFileDeclaration(LexerT& lexer);
    static soul::parser::Match ExpressionFileDeclaration(LexerT& lexer);
    static soul::parser::Match LexerFileDeclaration(LexerT& lexer);
};

} // namespace soul::slg::slg::file::parser
