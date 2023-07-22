
// this file has been automatically generated from 'C:/work/soul-mod/examples/minilang/function.parser' using soul parser generator spg version 5.0.0

export module minilang.parser.function;

import std.core;
import soul.lexer;
import soul.parser;
import minilang.ast;

using namespace minilang::ast;

export namespace minilang::parser::function {

template<typename LexerT>
struct FunctionParser
{
    static soul::parser::Match Function(LexerT& lexer);
    static soul::parser::Match ParameterList(LexerT& lexer, minilang::ast::FunctionNode* function);
    static soul::parser::Match Parameter(LexerT& lexer);
};

} // namespace minilang::parser::function
