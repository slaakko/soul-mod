
// this file has been automatically generated from 'D:/work/soul-mod/soul/spg/spg_file.parser' using soul parser generator spg version 5.0.0

export module soul.spg.spg.file.parser;

import std;
import soul.lexer;
import soul.parser;
import soul.ast.spg;
import soul.ast.slg;

export namespace soul::spg::spg::file::parser {

template<typename LexerT>
struct SpgFileParser
{
    static std::unique_ptr<soul::ast::spg::SpgFile> Parse(LexerT& lexer);
    static soul::parser::Match SpgFile(LexerT& lexer);
    static soul::parser::Match SpgFileDeclaration(LexerT& lexer);
    static soul::parser::Match ParserFileDeclaration(LexerT& lexer);
    static soul::parser::Match TokenFileDeclaration(LexerT& lexer);
};

} // namespace soul::spg::spg::file::parser
