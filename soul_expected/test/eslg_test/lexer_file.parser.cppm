
// this file has been automatically generated from 'D:/work/soul-mod/soul_expected/test/eslg_test/lexer_file.parser' using soul parser generator espg version 5.0.0

export module soul_expected.slg.lexer.file.parser;

import std;
import soul_expected.lexer;
import soul_expected.parser;
import soul_expected.ast.slg;
import soul_expected.ast.cpp;

using namespace soul_expected::ast::slg;
using namespace soul_expected::ast::cpp;

export namespace soul_expected::slg::lexer::file::parser {

template<typename LexerT>
struct LexerFileParser
{
    static std::expected<std::unique_ptr<soul_expected::ast::slg::LexerFile>, int> Parse(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> LexerFile(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> Imports(LexerT& lexer, soul_expected::ast::slg::LexerFile* lexerFile);
    static std::expected<soul_expected::parser::Match, int> LexerContent(LexerT& lexer, soul_expected::ast::cpp::Context* context, soul_expected::ast::slg::Lexer* lxr);
    static std::expected<soul_expected::parser::Match, int> Rules(LexerT& lexer, soul_expected::ast::cpp::Context* context, soul_expected::ast::slg::Lexer* lxr);
    static std::expected<soul_expected::parser::Match, int> Rule(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> Variables(LexerT& lexer, soul_expected::ast::cpp::Context* context, soul_expected::ast::slg::Lexer* lxr);
    static std::expected<soul_expected::parser::Match, int> Variable(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> Actions(LexerT& lexer, soul_expected::ast::cpp::Context* context, soul_expected::ast::slg::Lexer* lxr);
    static std::expected<soul_expected::parser::Match, int> Action(LexerT& lexer, soul_expected::ast::cpp::Context* context);
};

} // namespace soul_expected::slg::lexer::file::parser
