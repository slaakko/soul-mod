
// this file has been automatically generated from 'D:/work/soul-mod/soul_expected/espg/parser_file.parser' using soul parser generator espg version 5.0.0

export module soul_expected.spg.parser.file.parser;

import std;
import soul_expected.lexer;
import soul_expected.parser;
import soul_expected.ast.spg;
import soul_expected.ast.cpp;

export namespace soul_expected::spg::parser::file::parser {

template<typename LexerT>
struct ParserFileParser
{
    static std::expected<std::unique_ptr<soul_expected::ast::spg::ParserFile>, int> Parse(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> ParserFile(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> Parser(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> ParserStatement(LexerT& lexer, soul_expected::ast::cpp::Context* context, soul_expected::ast::spg::GrammarParser* parser);
    static std::expected<soul_expected::parser::Match, int> LexerStatement(LexerT& lexer, soul_expected::ast::cpp::Context* context, soul_expected::ast::spg::GrammarParser* parser);
    static std::expected<soul_expected::parser::Match, int> MainStatement(LexerT& lexer, soul_expected::ast::spg::GrammarParser* parser);
    static std::expected<soul_expected::parser::Match, int> UsingStatement(LexerT& lexer, soul_expected::ast::spg::GrammarParser* parser);
    static std::expected<soul_expected::parser::Match, int> RuleStatement(LexerT& lexer, soul_expected::ast::cpp::Context* context, soul_expected::ast::spg::GrammarParser* parser);
    static std::expected<soul_expected::parser::Match, int> ParametersAndVariables(LexerT& lexer, soul_expected::ast::cpp::Context* context, soul_expected::ast::spg::RuleParser* rule);
    static std::expected<soul_expected::parser::Match, int> ParamOrVariable(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> ReturnType(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> RuleBody(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> Choice(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> Sequence(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> Difference(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> List(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> Prefix(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> Postfix(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> Primary(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> RuleCall(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> Nonterminal(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> Primitive(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> Grouping(LexerT& lexer, soul_expected::ast::cpp::Context* context);
};

} // namespace soul_expected::spg::parser::file::parser
