// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.symbols.evaluator;

import std.core;
import soul.cpp20.ast.node;
import soul.cpp20.ast.literal;
import soul.ast.source.pos;

export namespace soul::cpp20::symbols {

class Value;
class Context;
class TypeSymbol;

TypeSymbol* GetIntegerType(soul::cpp20::ast::Suffix suffix, const soul::ast::SourcePos& sourcePos, Context* context);
TypeSymbol* GetFloatingPointType(soul::cpp20::ast::Suffix suffix, const soul::ast::SourcePos& sourcePos, Context* context);
TypeSymbol* GetStringType(soul::cpp20::ast::EncodingPrefix encodingPrefix, const soul::ast::SourcePos& sourcePos, Context* context);
TypeSymbol* GetCharacterType(soul::cpp20::ast::EncodingPrefix encodingPrefix, const soul::ast::SourcePos& sourcePos, Context* context);
Value* Evaluate(soul::cpp20::ast::Node* node, Context* context);

} // namespace soul::cpp20::symbols
