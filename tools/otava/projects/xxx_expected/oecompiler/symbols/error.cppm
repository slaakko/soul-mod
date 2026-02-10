// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.error;

import std;
import soul.ast.source.pos;

export namespace otava::symbols {

class Context;

std::unexpected<int> Error(const std::string& message, const soul::ast::SourcePos& sourcePos, Context* context);
std::unexpected<int> Error(const std::string& message, const soul::ast::SourcePos& sourcePos, const soul::ast::SourcePos& refSourcePos, Context* context);
std::unexpected<int> Warning(const std::string& message, const soul::ast::SourcePos& sourcePos, Context* context);
std::unexpected<int> Warning(const std::string& message, const soul::ast::SourcePos& sourcePos, const soul::ast::SourcePos& refSourcePos, Context* context);

} // namespace otava::symbols
