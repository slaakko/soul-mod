// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.error;

import std;
import otava.symbols.context;
import soul.ast.source.pos;

export namespace otava::symbols {

std::unexpected<int> Error(const std::string& message, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context);
std::unexpected<int> Error(const std::string& message, const soul::ast::SourcePos& sourcePos, const soul::ast::SourcePos& refSourcePos, otava::symbols::Context* context);

} // namespace otava::symbols
