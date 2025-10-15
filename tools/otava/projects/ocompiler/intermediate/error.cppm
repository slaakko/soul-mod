// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.intermediate.error;

import soul.ast.span;
import std;

export namespace otava::intermediate {

class Context;

std::unexpected<int> Error(const std::string& message, const soul::ast::Span& span, Context* context);
std::unexpected<int> Error(const std::string& message, const soul::ast::Span& span, Context* context, const soul::ast::Span& refSpan);
void Warning(const std::string& message, const soul::ast::Span& span, Context* context);

} // otava::intermediate
