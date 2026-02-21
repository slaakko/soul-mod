// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.expr.parser;

import otava.lexer;
import otava.parser.expression;
import otava.symbols;

namespace otava::parser {

std::unique_ptr<otava::ast::Node> ParseExpression(const std::u32string& expr, otava::symbols::Context* context)
{
    auto lexer = otava::lexer::MakeLexer(expr.c_str(), expr.c_str() + expr.length(), "<expr>");
    using LexerType = decltype(lexer);
    otava::symbols::Lexer* prevLexer = context->GetLexer();
    context->SetLexer(&lexer);
    std::unique_ptr<otava::ast::Node> node = otava::parser::expression::ExpressionParser<LexerType>::Parse(lexer, context);
    context->SetLexer(prevLexer);
    return node;
}

} // otava::parser
