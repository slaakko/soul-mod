// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.expr.parser;

import std;
import otava.ast;
import otava.symbols.modules;

export namespace otava::parser {

std::unique_ptr<otava::ast::Node> ParseExpression(const std::u32string& expr, otava::symbols::Module* module);

} // otava::parser
