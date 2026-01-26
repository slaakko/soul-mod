// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.expr.parser;

import std;
import otava.ast;
import otava.symbols.modules;

export namespace otava::symbols {

class Context;

using ExprParser = std::unique_ptr<otava::ast::Node>(*)(const std::u32string&, Context* context);

void SetExprParser(ExprParser exprParser_);

std::unique_ptr<otava::ast::Node> ParseExpression(const std::u32string& expr, Context* context);

} // namespace otava::symbols
