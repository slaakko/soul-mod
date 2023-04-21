// =================================
// Copyright (c) 2023 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.intermediate.error;

import std.core;
import soul.ast.source.pos;

export namespace otava::intermediate {

class Context;
using SourcePos = soul::ast::SourcePos;

bool ExceptionThrown();
void Error(const std::string& message, const SourcePos& sourcePos, Context* context);
void Error(const std::string& message, const SourcePos& sourcePos, Context* context, const SourcePos& refSourcePos);
void Warning(const std::string& message, const SourcePos& sourcePos, Context* context, const SourcePos& refSourcePos);

} // otava::intermediate
