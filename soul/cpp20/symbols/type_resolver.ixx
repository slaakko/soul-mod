// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.symbols.type.resolver;

import std.core;
import soul.cpp20.ast;
import soul.cpp20.symbols.declaration;
import soul.ast.source.pos;

export namespace soul::cpp20::symbols {

class Context;
class TypeSymbol;

void CheckDuplicateSpecifier(DeclarationFlags flags, DeclarationFlags flag, const std::string& specifierStr, const soul::ast::SourcePos& sourcePos, Context* context);

TypeSymbol* ResolveType(soul::cpp20::ast::Node* node, DeclarationFlags flags, Context* context);
TypeSymbol* ResolveFwdDeclaredType(TypeSymbol* type, const soul::ast::SourcePos& sourcePos, Context* context);

} // namespace soul::cpp20::symbols
