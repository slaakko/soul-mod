// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.stmt.parser;

import std;
import otava.ast;
import otava.symbols.context;

export namespace otava::parser {

std::unique_ptr<otava::ast::Node> ParseStatement(const std::u32string& stmt, otava::symbols::Context* context);

} // otava::parser
