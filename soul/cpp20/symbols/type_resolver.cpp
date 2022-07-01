// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.symbols.type.resolver;

import soul.cpp20.symbols.context;
import soul.cpp20.symbols.exception;
import soul.cpp20.symbols.derivations;
import soul.cpp20.symbols.fundamental.type.symbol;
import soul.cpp20.symbols.compound.type.symbol;
import soul.cpp20.symbols.symbol.table;
import soul.cpp20.symbols.scope.resolver;
import util.unicode;

namespace soul::cpp20::symbols {

void CheckDuplicateSpecifier(DeclarationFlags flags, DeclarationFlags flag, const std::string& specifierStr, const soul::ast::SourcePos& sourcePos, Context* context)
{
    if ((flags & flag) != DeclarationFlags::none)
    {
        throw Exception("duplicate '" + specifierStr + "'", sourcePos, context);
    }
}

class TypeResolver : public soul::cpp20::ast::DefaultVisitor
{
public:
    TypeResolver(Context* context_);
    TypeSymbol* GetType() const { return type; }
    void ResolveBaseType(soul::cpp20::ast::Node* node);
    void Visit(soul::cpp20::ast::DefiningTypeIdNode& node) override;
    void Visit(soul::cpp20::ast::CharNode& node) override;
    void Visit(soul::cpp20::ast::Char8Node& node) override;
    void Visit(soul::cpp20::ast::Char16Node& node) override;
    void Visit(soul::cpp20::ast::Char32Node& node) override;
    void Visit(soul::cpp20::ast::WCharNode& node) override;
    void Visit(soul::cpp20::ast::BoolNode& node) override;
    void Visit(soul::cpp20::ast::ShortNode& node) override;
    void Visit(soul::cpp20::ast::IntNode& node) override;
    void Visit(soul::cpp20::ast::LongNode& node) override;
    void Visit(soul::cpp20::ast::SignedNode& node) override;
    void Visit(soul::cpp20::ast::UnsignedNode& node) override;
    void Visit(soul::cpp20::ast::FloatNode& node) override;
    void Visit(soul::cpp20::ast::DoubleNode& node) override;
    void Visit(soul::cpp20::ast::VoidNode& node) override;
    void Visit(soul::cpp20::ast::ConstNode& node) override;
    void Visit(soul::cpp20::ast::VolatileNode& node) override;
    void Visit(soul::cpp20::ast::LvalueRefNode& node) override;
    void Visit(soul::cpp20::ast::RvalueRefNode& node) override;
    void Visit(soul::cpp20::ast::PtrNode& node) override;
    void Visit(soul::cpp20::ast::QualifiedIdNode& node) override;
    void Visit(soul::cpp20::ast::IdentifierNode& node) override;
private:
    Context* context;
    TypeSymbol* type;
    TypeSymbol* baseType;
    DeclarationFlags flags;
    int pointerCount;
};

TypeResolver::TypeResolver(Context* context_) : context(context_), type(nullptr), baseType(nullptr), flags(DeclarationFlags::none), pointerCount(0)
{
}

void TypeResolver::ResolveBaseType(soul::cpp20::ast::Node* node)
{
    DeclarationFlags fundamentalTypeFlags = flags & DeclarationFlags::fundamentalTypeFlags;
    if (fundamentalTypeFlags != DeclarationFlags::none)
    {
        if (baseType)
        {
            throw Exception("duplicate type symbol in declaration specifier sequence", node->GetSourcePos(), context);
        }
        baseType = GetFundamentalType(fundamentalTypeFlags, node->GetSourcePos(), context);
    }
}

void TypeResolver::Visit(soul::cpp20::ast::DefiningTypeIdNode& node)
{
    node.DefiningTypeSpecifiers()->Accept(*this);
    ResolveBaseType(&node);
    type = baseType;
    node.AbstractDeclarator()->Accept(*this);
    Derivations derivations;
    if ((flags & DeclarationFlags::constFlag) != DeclarationFlags::none)
    {
        derivations.vec.push_back(Derivation::constDerivation);
    }
    if ((flags & DeclarationFlags::volatileFlag) != DeclarationFlags::none)
    {
        derivations.vec.push_back(Derivation::volatileDerivation);
    }
    if (pointerCount > 0)
    {
        for (int i = 0; i < pointerCount; ++i)
        {
            derivations.vec.push_back(Derivation::pointerDerivation);
        }
    }
    if ((flags & DeclarationFlags::lvalueRefFlag) != DeclarationFlags::none)
    {
        derivations.vec.push_back(Derivation::lvalueRefDerivation);
    }
    else if ((flags & DeclarationFlags::lvalueRefFlag) != DeclarationFlags::none)
    { 
        derivations.vec.push_back(Derivation::rvalueRefDerivation);
    }
    if (!derivations.IsEmpty())
    {
        type = context->GetSymbolTable()->MakeCompoundType(type, derivations);
    }
}

void TypeResolver::Visit(soul::cpp20::ast::CharNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::charFlag, "char", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::charFlag;
}

void TypeResolver::Visit(soul::cpp20::ast::Char8Node& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::char8Flag, "char8_t", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::char8Flag;
}

void TypeResolver::Visit(soul::cpp20::ast::Char16Node& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::char16Flag, "char16_t", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::char16Flag;
}

void TypeResolver::Visit(soul::cpp20::ast::Char32Node& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::char32Flag, "char32_t", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::char32Flag;
}

void TypeResolver::Visit(soul::cpp20::ast::WCharNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::wcharFlag, "wchar_t", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::wcharFlag;
}

void TypeResolver::Visit(soul::cpp20::ast::BoolNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::wcharFlag, "bool", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::boolFlag;
}

void TypeResolver::Visit(soul::cpp20::ast::ShortNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::shortFlag, "short", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::shortFlag;
}

void TypeResolver::Visit(soul::cpp20::ast::IntNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::intFlag, "int", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::intFlag;
}

void TypeResolver::Visit(soul::cpp20::ast::LongNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::longLongFlag, "long long", node.GetSourcePos(), context);
    if ((flags & DeclarationFlags::longFlag) != DeclarationFlags::none)
    {
        flags = (flags | DeclarationFlags::longLongFlag) & ~DeclarationFlags::longFlag;
    }
    else
    {
        flags = flags | DeclarationFlags::longFlag;
    }
}

void TypeResolver::Visit(soul::cpp20::ast::SignedNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::signedFlag, "signed", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::signedFlag;
}

void TypeResolver::Visit(soul::cpp20::ast::UnsignedNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::unsignedFlag, "unsigned", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::unsignedFlag;
}

void TypeResolver::Visit(soul::cpp20::ast::FloatNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::floatFlag, "float", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::floatFlag;
}

void TypeResolver::Visit(soul::cpp20::ast::DoubleNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::doubleFlag, "double", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::doubleFlag;
}

void TypeResolver::Visit(soul::cpp20::ast::VoidNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::voidFlag, "void", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::voidFlag;
}

void TypeResolver::Visit(soul::cpp20::ast::ConstNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::constFlag, "const", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::constFlag;
}

void TypeResolver::Visit(soul::cpp20::ast::VolatileNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::volatileFlag, "volatile", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::volatileFlag;
}

void TypeResolver::Visit(soul::cpp20::ast::LvalueRefNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::lvalueRefFlag, "&", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::lvalueRefFlag;
}

void TypeResolver::Visit(soul::cpp20::ast::RvalueRefNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::rvalueRefFlag, "&&", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::rvalueRefFlag;
}

void TypeResolver::Visit(soul::cpp20::ast::PtrNode& node)
{
    ++pointerCount;
}

void TypeResolver::Visit(soul::cpp20::ast::QualifiedIdNode& node)
{
    BeginScope(node.Left(), context);
    Symbol* symbol = context->GetSymbolTable()->Lookup(node.Right()->Str(), SymbolGroupKind::typeSymbolGroup, node.GetSourcePos(), context);
    EndScope(context);
    if (symbol)
    {
        if (symbol->IsTypeSymbol())
        {
            type = static_cast<TypeSymbol*>(symbol);
        }
        else
        {
            throw Exception("symbol '" + util::ToUtf8(symbol->Name()) + "' is not a type symbol", node.GetSourcePos(), context);
        }
    }
    else
    {
        throw Exception("symbol '" + util::ToUtf8(node.Right()->Str()) + "' not found", node.GetSourcePos(), context);
    }
}

void TypeResolver::Visit(soul::cpp20::ast::IdentifierNode& node)
{
    Symbol* symbol = context->GetSymbolTable()->Lookup(node.Str(), SymbolGroupKind::typeSymbolGroup, node.GetSourcePos(), context);
    if (symbol)
    {
        if (symbol->IsTypeSymbol())
        {
            type = static_cast<TypeSymbol*>(symbol);
        }
        else
        {
            throw Exception("symbol '" + util::ToUtf8(symbol->Name()) + "' is not a type symbol", node.GetSourcePos(), context);
        }
    }
    else
    {
        throw Exception("symbol '" + util::ToUtf8(node.Str()) + "' not found", node.GetSourcePos(), context);
    }
}

TypeSymbol* ResolveType(soul::cpp20::ast::Node* node, Context* context)
{
    TypeResolver resolver(context);
    node->Accept(resolver);
    return resolver.GetType();
}

} // namespace soul::cpp20::symbols
