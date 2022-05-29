
// this file has been automatically generated from 'C:/work/soul-mod/soul/spg/parser_file_parser.parser' using soul parser generator spg version 4.0.0

export module soul.spg.parser.file.parser;

import std.core;
import soul.lexer;
import soul.parser;
import soul.ast.spg;

using namespace soul::ast::spg;

export namespace soul::spg::parser::file::parser {

template<typename Lexer>
struct ParserFileParser
{
    static std::unique_ptr<soul::ast::spg::ParserFile> Parse(Lexer& lexer);
    static soul::parser::Match ParserFile(Lexer& lexer);
    static soul::parser::Match Parser(Lexer& lexer);
    static soul::parser::Match ParserStatement(Lexer& lexer, soul::ast::spg::GrammarParser* parser);
    static soul::parser::Match LexerStatement(Lexer& lexer, soul::ast::spg::GrammarParser* parser);
    static soul::parser::Match MainStatement(Lexer& lexer, soul::ast::spg::GrammarParser* parser);
    static soul::parser::Match UsingStatement(Lexer& lexer, soul::ast::spg::GrammarParser* parser);
    static soul::parser::Match RuleStatement(Lexer& lexer, soul::ast::spg::GrammarParser* parser);
    static soul::parser::Match ParametersAndVariables(Lexer& lexer, soul::ast::spg::RuleParser* rule);
    static soul::parser::Match ParamOrVariable(Lexer& lexer);
    static soul::parser::Match ReturnType(Lexer& lexer);
    static soul::parser::Match RuleBody(Lexer& lexer);
    static soul::parser::Match Alternative(Lexer& lexer);
    static soul::parser::Match Sequence(Lexer& lexer);
    static soul::parser::Match Difference(Lexer& lexer);
    static soul::parser::Match List(Lexer& lexer);
    static soul::parser::Match Prefix(Lexer& lexer);
    static soul::parser::Match Postfix(Lexer& lexer);
    static soul::parser::Match Primary(Lexer& lexer);
    static soul::parser::Match RuleCall(Lexer& lexer);
    static soul::parser::Match Nonterminal(Lexer& lexer);
    static soul::parser::Match Primitive(Lexer& lexer);
    static soul::parser::Match Grouping(Lexer& lexer);
};

} // namespace soul::spg::parser::file::parser
