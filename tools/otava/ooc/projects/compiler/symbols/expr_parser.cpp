// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.expr.parser;

namespace otava::symbols {

ExprParser exprParser;

void SetExprParser(ExprParser exprParser_) noexcept
{
    exprParser = exprParser_;
}

std::unique_ptr<otava::ast::Node> ParseExpression(const std::u32string& expr, Context* context)
{
    return exprParser(expr, context);
}

} // namespace otava::symbols
