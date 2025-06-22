// =================================
// Copyright (c) 2025 Seppo Laakko
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

enum class TypeResolverFlags : std::int32_t
{
    none = 0, dontInstantiate = 1 << 0, dontThrow = 1 << 1
};

constexpr TypeResolverFlags operator|(TypeResolverFlags left, TypeResolverFlags right)
{
    return TypeResolverFlags(std::int32_t(left) | std::int32_t(right));
}

constexpr TypeResolverFlags operator&(TypeResolverFlags left, TypeResolverFlags right)
{
    return TypeResolverFlags(std::int32_t(left) & std::int32_t(right));
}

constexpr TypeResolverFlags operator~(TypeResolverFlags flags)
{
    return TypeResolverFlags(~std::int32_t(flags));
}

TypeSymbol* ResolveType(otava::ast::Node* node, DeclarationFlags flags, Context* context);
TypeSymbol* ResolveType(otava::ast::Node* node, DeclarationFlags flags, Context* context, TypeResolverFlags resolverFlags);
TypeSymbol* ResolveFwdDeclaredType(TypeSymbol* type, const soul::ast::SourcePos& sourcePos, Context* context);

} // namespace otava::symbols
