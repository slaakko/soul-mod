
// this file has been automatically generated from 'C:/work/soul-mod/soul/cpp20/optimized_parser/function.parser' using soul parser generator spg version 4.1.0

export module soul.cpp20.parser.function;

import std.core;
import soul.lexer;
import soul.parser;
import soul.cpp20.symbols.context;
import soul.cpp20.ast;

using namespace soul::cpp20::symbols::context;
using namespace soul::cpp20::ast;

export namespace soul::cpp20::parser::function {

template<typename Lexer>
struct FunctionParser
{
    static soul::parser::Match FunctionDefinition(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match NoDeclSpecFunctionDefinition(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match FunctionBody(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match Default(Lexer& lexer);
    static soul::parser::Match Delete(Lexer& lexer);
    static soul::parser::Match ParameterDeclarationClause(Lexer& lexer, soul::cpp20::symbols::Context* context, soul::cpp20::ast::Node* container);
    static soul::parser::Match ParameterDeclarationList(Lexer& lexer, soul::cpp20::symbols::Context* context, soul::cpp20::ast::Node* container);
    static soul::parser::Match ParameterDeclaration(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match OperatorFunctionId(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match ConversionFunctionId(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match DestructorId(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match ConversionTypeId(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match ConversionDeclarator(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match OperatorKw(Lexer& lexer);
    static soul::parser::Match Operator(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match Noexcept(Lexer& lexer);
    static soul::parser::Match FunctionTryBlock(Lexer& lexer, soul::cpp20::symbols::Context* context);
};

} // namespace soul::cpp20::parser::function
