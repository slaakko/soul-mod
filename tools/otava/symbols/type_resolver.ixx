// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.type.resolver;

import std.core;
import otava.ast;
import otava.symbols.declaration;
import soul.ast.source.pos;

export namespace otava::symbols {

class Context;
class TypeSymbol;

void CheckDuplicateSpecifier(DeclarationFlags flags, DeclarationFlags flag, const std::string& specifierStr, const soul::ast::SourcePos& sourcePos, Context* context);

TypeSymbol* ResolveType(otava::ast::Node* node, DeclarationFlags flags, Context* context);
TypeSymbol* ResolveFwdDeclaredType(TypeSymbol* type, const soul::ast::SourcePos& sourcePos, Context* context);

} // namespace otava::symbols
