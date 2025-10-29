
// this file has been automatically generated from 'D:/work/soul-mod/tools/otava/projects/ocompiler/parser/function.parser' using soul parser generator ospg version 5.0.0

export module otava.parser.function;

import std;
import soul.lexer;
import soul.parser;
import otava.symbols.context;
import otava.ast;

export namespace otava::parser::function {

template<typename LexerT>
struct FunctionParser
{
    static std::expected<soul::parser::Match, int> FunctionDefinition(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> NoDeclSpecFunctionDefinition(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> FunctionBody(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> Default(LexerT& lexer);
    static std::expected<soul::parser::Match, int> Delete(LexerT& lexer);
    static std::expected<soul::parser::Match, int> ParameterDeclarationClause(LexerT& lexer, otava::symbols::Context* context, otava::ast::Node* container);
    static std::expected<soul::parser::Match, int> ParameterDeclarationList(LexerT& lexer, otava::symbols::Context* context, otava::ast::Node* container);
    static std::expected<soul::parser::Match, int> ParameterDeclaration(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> OperatorFunctionId(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> ConversionFunctionId(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> DestructorId(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> ConversionTypeId(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> ConversionDeclarator(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> OperatorKw(LexerT& lexer);
    static std::expected<soul::parser::Match, int> Operator(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> Noexcept(LexerT& lexer);
};

} // namespace otava::parser::function
