
// this file has been automatically generated from 'C:/work/soul-mod/soul/slg/slg_file_parser.parser' using soul parser generator spg version 4.0.0

export module soul.slg.slg.file.par;

import std.core;
import soul.lexer;
import soul.parser;
import soul.ast.slg;

using namespace soul::ast::slg;

export namespace soul::slg::slg::file::par {

template<typename Lexer>
struct SlgFileParser
{
    static std::unique_ptr<soul::ast::slg::SlgFile> Parse(Lexer& lexer);
    static soul::parser::Match SlgFile(Lexer& lexer);
    static soul::parser::Match SlgFileDeclaration(Lexer& lexer);
    static soul::parser::Match TokenFileDeclaration(Lexer& lexer);
    static soul::parser::Match KeywordFileDeclaration(Lexer& lexer);
    static soul::parser::Match ExpressionFileDeclaration(Lexer& lexer);
    static soul::parser::Match LexerFileDeclaration(Lexer& lexer);
};

} // namespace soul::slg::slg::file::par
