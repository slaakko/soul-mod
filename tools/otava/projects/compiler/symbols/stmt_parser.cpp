// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.stmt.parser;

namespace otava::symbols {

StmtParser stmtParser;

void SetStmtParser(StmtParser stmtParser_) noexcept
{
    stmtParser = stmtParser_;
}

std::unique_ptr<otava::ast::Node> ParseStatement(const std::u32string& stmt, otava::symbols::Context* context)
{
    return stmtParser(stmt, context);
}

} // namespace otava::symbols
