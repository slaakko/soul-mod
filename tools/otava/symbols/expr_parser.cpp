// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.expr.parser;

namespace otava::symbols {

ExprParser exprParser;

void SetExprParser(ExprParser exprParser_)
{
    exprParser = exprParser_;
}

std::unique_ptr<otava::ast::Node> ParseExpression(const std::u32string& expr, otava::symbols::Module* module)
{
    return exprParser(expr, module);
}

} // namespace otava::symbols
