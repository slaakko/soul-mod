
// this file has been automatically generated from 'C:/work/soul-mod/soul/spg/spg_file.parser' using soul parser generator spg version 4.0.0

export module soul.spg.spg.file.parser;

import std.core;
import soul.lexer;
import soul.parser;
import soul.ast.spg;

using namespace soul::ast::spg;

export namespace soul::spg::spg::file::parser {

template<typename Lexer>
struct SpgFileParser
{
    static std::unique_ptr<soul::ast::spg::SpgFile> Parse(Lexer& lexer);
    static soul::parser::Match SpgFile(Lexer& lexer);
    static soul::parser::Match SpgFileDeclaration(Lexer& lexer);
    static soul::parser::Match ParserFileDeclaration(Lexer& lexer);
};

} // namespace soul::spg::spg::file::parser
