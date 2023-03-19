
// this file has been automatically generated from 'C:/work/soul-mod/tools/otava/parser/function.parser' using soul parser generator spg version 4.1.0

export module otava.parser.function;

import std.core;
import soul.lexer;
import soul.parser;
import otava.symbols.context;
import otava.ast;

using namespace otava::symbols::context;
using namespace otava::ast;

export namespace otava::parser::function {

template<typename Lexer>
struct FunctionParser
{
    static soul::parser::Match FunctionDefinition(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match NoDeclSpecFunctionDefinition(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match FunctionBody(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match Default(Lexer& lexer);
    static soul::parser::Match Delete(Lexer& lexer);
    static soul::parser::Match ParameterDeclarationClause(Lexer& lexer, otava::symbols::Context* context, otava::ast::Node* container);
    static soul::parser::Match ParameterDeclarationList(Lexer& lexer, otava::symbols::Context* context, otava::ast::Node* container);
    static soul::parser::Match ParameterDeclaration(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match OperatorFunctionId(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match ConversionFunctionId(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match DestructorId(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match ConversionTypeId(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match ConversionDeclarator(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match OperatorKw(Lexer& lexer);
    static soul::parser::Match Operator(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match Noexcept(Lexer& lexer);
    static soul::parser::Match FunctionTryBlock(Lexer& lexer, otava::symbols::Context* context);
};

} // namespace otava::parser::function
