
// this file has been automatically generated from 'D:/work/soul-mod/tools/otava/projects/osoul/ospg/parser_file.parser' using soul parser generator ospg version 5.0.0

export module soul.spg.parser.file.parser;

import std;
import soul.lexer;
import soul.parser;
import soul.ast.spg;
import soul.ast.cpp;

export namespace soul::spg::parser::file::parser {

template<typename LexerT>
struct ParserFileParser
{
    static std::expected<std::unique_ptr<soul::ast::spg::ParserFile>, int> Parse(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> ParserFile(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> Parser(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> ParserStatement(LexerT& lexer, soul::ast::cpp::Context* context, soul::ast::spg::GrammarParser* parser);
    static std::expected<soul::parser::Match, int> LexerStatement(LexerT& lexer, soul::ast::cpp::Context* context, soul::ast::spg::GrammarParser* parser);
    static std::expected<soul::parser::Match, int> MainStatement(LexerT& lexer, soul::ast::spg::GrammarParser* parser);
    static std::expected<soul::parser::Match, int> UsingStatement(LexerT& lexer, soul::ast::spg::GrammarParser* parser);
    static std::expected<soul::parser::Match, int> RuleStatement(LexerT& lexer, soul::ast::cpp::Context* context, soul::ast::spg::GrammarParser* parser);
    static std::expected<soul::parser::Match, int> ParametersAndVariables(LexerT& lexer, soul::ast::cpp::Context* context, soul::ast::spg::RuleParser* rule);
    static std::expected<soul::parser::Match, int> ParamOrVariable(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> ReturnType(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> RuleBody(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> Choice(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> Sequence(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> Difference(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> List(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> Prefix(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> Postfix(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> Primary(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> RuleCall(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> Nonterminal(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> Primitive(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> Grouping(LexerT& lexer, soul::ast::cpp::Context* context);
};

} // namespace soul::spg::parser::file::parser
