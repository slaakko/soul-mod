
// this file has been automatically generated from 'C:/work/soul-mod/examples/minilang/function.parser' using soul parser generator spg version 4.1.0

export module minilang.parser.function;

import std.core;
import soul.lexer;
import soul.parser;
import minilang.ast;

using namespace minilang::ast;

export namespace minilang::parser::function {

template<typename Lexer>
struct FunctionParser
{
    static soul::parser::Match Function(Lexer& lexer);
    static soul::parser::Match ParameterList(Lexer& lexer, minilang::ast::FunctionNode* function);
    static soul::parser::Match Parameter(Lexer& lexer);
};

} // namespace minilang::parser::function
