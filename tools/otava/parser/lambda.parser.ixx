
// this file has been automatically generated from 'C:/work/soul-mod/tools/otava/parser/lambda.parser' using soul parser generator spg version 4.1.0

export module otava.parser.lambda;

import std.core;
import soul.lexer;
import soul.parser;
import otava.symbols.context;

using namespace otava::symbols::context;

export namespace otava::parser::lambda {

template<typename Lexer>
struct LambdaParser
{
    static soul::parser::Match LambdaExpression(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match LambdaIntroducer(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match LambdaCapture(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match CaptureDefault(Lexer& lexer);
    static soul::parser::Match CaptureList(Lexer& lexer, otava::symbols::Context* context, otava::ast::Node* container);
    static soul::parser::Match Capture(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match InitCapture(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match SimpleCapture(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match LambdaDeclarator(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match LambdaSpecifiers(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match LambdaTemplateParams(Lexer& lexer, otava::symbols::Context* context);
};

} // namespace otava::parser::lambda
