
// this file has been automatically generated from 'C:/work/soul-mod/examples/minilang/function_parser.parser' using soul parser generator spg version 4.0.0

export module minilang.parser.function;

import std.core;
import soul.lexer;
import soul.parser;
import minilang.tree;

using namespace minilang::tree;

export namespace minilang::parser::function {

template<typename Lexer>
struct FunctionParser
{
    static soul::parser::Match Function(Lexer& lexer);
    static soul::parser::Match ParameterList(Lexer& lexer, minilang::tree::FunctionNode* function);
    static soul::parser::Match Parameter(Lexer& lexer);
};

} // namespace minilang::parser::function
