
// this file has been automatically generated from 'C:/work/soul-mod/soul/cpp20/parser/lambda.parser' using soul parser generator spg version 4.1.0

export module soul.cpp20.parser.lambda;

import std.core;
import soul.lexer;
import soul.parser;
import soul.cpp20.symbols.context;

using namespace soul::cpp20::symbols::context;

export namespace soul::cpp20::parser::lambda {

template<typename Lexer>
struct LambdaParser
{
    static soul::parser::Match LambdaExpression(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match LambdaIntroducer(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match LambdaCapture(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match CaptureDefault(Lexer& lexer);
    static soul::parser::Match CaptureList(Lexer& lexer, soul::cpp20::symbols::Context* context, soul::cpp20::ast::Node* container);
    static soul::parser::Match Capture(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match InitCapture(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match SimpleCapture(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match LambdaDeclarator(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match LambdaSpecifiers(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match LambdaTemplateParams(Lexer& lexer, soul::cpp20::symbols::Context* context);
};

} // namespace soul::cpp20::parser::lambda
