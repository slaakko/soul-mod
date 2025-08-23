
// this file has been automatically generated from 'D:/work/soul-mod/tools/otava/projects/osoul/oslg/lexer_file.parser' using soul parser generator oespg version 5.0.0

export module soul.slg.lexer.file.parser;

import std;
import soul.lexer;
import soul.parser;
import soul.ast.slg;
import soul.ast.cpp;

using namespace soul::ast::slg;
using namespace soul::ast::cpp;

export namespace soul::slg::lexer::file::parser {

template<typename LexerT>
struct LexerFileParser
{
    static std::expected<std::unique_ptr<soul::ast::slg::LexerFile>, int> Parse(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> LexerFile(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> Imports(LexerT& lexer, soul::ast::slg::LexerFile* lexerFile);
    static std::expected<soul::parser::Match, int> LexerContent(LexerT& lexer, soul::ast::cpp::Context* context, soul::ast::slg::Lexer* lxr);
    static std::expected<soul::parser::Match, int> Rules(LexerT& lexer, soul::ast::cpp::Context* context, soul::ast::slg::Lexer* lxr);
    static std::expected<soul::parser::Match, int> Rule(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> Variables(LexerT& lexer, soul::ast::cpp::Context* context, soul::ast::slg::Lexer* lxr);
    static std::expected<soul::parser::Match, int> Variable(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> Actions(LexerT& lexer, soul::ast::cpp::Context* context, soul::ast::slg::Lexer* lxr);
    static std::expected<soul::parser::Match, int> Action(LexerT& lexer, soul::ast::cpp::Context* context);
};

} // namespace soul::slg::lexer::file::parser
