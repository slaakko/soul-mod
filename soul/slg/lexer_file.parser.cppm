
// this file has been automatically generated from 'C:/work/soul-mod/soul/slg/lexer_file.parser' using soul parser generator spg version 4.1.0

export module soul.slg.lexer.file.parser;

import std.core;
import soul.lexer;
import soul.parser;
import soul.ast.slg;

using namespace soul::ast::slg;

export namespace soul::slg::lexer::file::parser {

template<typename Lexer>
struct LexerFileParser
{
    static std::unique_ptr<soul::ast::slg::LexerFile> Parse(Lexer& lexer);
    static soul::parser::Match LexerFile(Lexer& lexer);
    static soul::parser::Match Imports(Lexer& lexer, soul::ast::slg::LexerFile* lexerFile);
    static soul::parser::Match LexerContent(Lexer& lexer, soul::ast::slg::Lexer* lxr);
    static soul::parser::Match Rules(Lexer& lexer, soul::ast::slg::Lexer* lxr);
    static soul::parser::Match Rule(Lexer& lexer);
    static soul::parser::Match Variables(Lexer& lexer, soul::ast::slg::Lexer* lxr);
    static soul::parser::Match Variable(Lexer& lexer);
    static soul::parser::Match Actions(Lexer& lexer, soul::ast::slg::Lexer* lxr);
    static soul::parser::Match Action(Lexer& lexer);
};

} // namespace soul::slg::lexer::file::parser
