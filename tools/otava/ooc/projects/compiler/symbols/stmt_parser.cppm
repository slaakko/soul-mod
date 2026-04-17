// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.stmt.parser;

import std;
import otava.ast;
import otava.symbols.context;

export namespace otava::symbols {

using StmtParser = std::unique_ptr<otava::ast::Node>(*)(const std::u32string&, otava::symbols::Context*);

void SetStmtParser(StmtParser stmtParser_) noexcept;

std::unique_ptr<otava::ast::Node> ParseStatement(const std::u32string& stmt, otava::symbols::Context* context);

} // namespace otava::symbols
