// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.stmt.parser;

import otava.lexer;
import otava.parser.statement;
import otava.symbols;

namespace otava::parser {

std::unique_ptr<otava::ast::Node> ParseStatement(const std::u32string& stmt, otava::symbols::Context* context)
{
    auto lexer = otava::lexer::MakeLexer(stmt.c_str(), stmt.c_str() + stmt.length(), "<stmt>");
    using LexerType = decltype(lexer);
    otava::symbols::Lexer* prevLexer = context->GetLexer();
    context->SetLexer(&lexer);
    std::unique_ptr<otava::ast::Node> node = otava::parser::statement::StatementParser<LexerType>::Parse(lexer, context);
    context->SetLexer(prevLexer);
    return node;
}

} // otava::parser
