
// this file has been automatically generated from 'D:/work/soul-mod/tools/otava/projects/ocompiler/parser/lambda.parser' using soul parser generator ospg version 5.0.0

export module otava.parser.lambda;

import std;
import soul.lexer;
import soul.parser;
import otava.symbols.context;
import otava.ast;

export namespace otava::parser::lambda {

template<typename LexerT>
struct LambdaParser
{
    static std::expected<soul::parser::Match, int> LambdaExpression(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> LambdaIntroducer(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> LambdaCapture(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> CaptureDefault(LexerT& lexer);
    static std::expected<soul::parser::Match, int> CaptureList(LexerT& lexer, otava::symbols::Context* context, otava::ast::Node* container);
    static std::expected<soul::parser::Match, int> Capture(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> InitCapture(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> SimpleCapture(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> LambdaDeclarator(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> LambdaSpecifiers(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> LambdaTemplateParams(LexerT& lexer, otava::symbols::Context* context);
};

} // namespace otava::parser::lambda
