// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.type.resolver;

import otava.symbols.context;
import otava.symbols.exception;
import otava.symbols.classes;
import otava.symbols.declaration;
import otava.symbols.declarator;
import otava.symbols.derivations;
import otava.symbols.enums;
import otava.symbols.evaluator;
import otava.symbols.fundamental.type.symbol;
import otava.symbols.compound.type.symbol;
import otava.symbols.specialization;
import otava.symbols.symbol.table;
import otava.symbols.scope.resolver;
import otava.symbols.templates;
import otava.symbols.value;
import util.unicode;

namespace otava::symbols {

void CheckDuplicateSpecifier(DeclarationFlags flags, DeclarationFlags flag, const std::string& specifierStr, const soul::ast::SourcePos& sourcePos, Context* context)
{
    if ((flags & flag) != DeclarationFlags::none)
    {
        ThrowException("duplicate '" + specifierStr + "'", sourcePos, context);
    }
}

class TypeResolver : public otava::ast::DefaultVisitor
{
public:
    TypeResolver(Context* context_, DeclarationFlags flags_);
    TypeSymbol* GetType();
    void ResolveBaseType(otava::ast::Node* node);
    void ResolveType();
    void Visit(otava::ast::DefiningTypeIdNode& node) override;
    void Visit(otava::ast::TypeSpecifierSequenceNode& node) override;
    void Visit(otava::ast::CharNode& node) override;
    void Visit(otava::ast::Char8Node& node) override;
    void Visit(otava::ast::Char16Node& node) override;
    void Visit(otava::ast::Char32Node& node) override;
    void Visit(otava::ast::WCharNode& node) override;
    void Visit(otava::ast::BoolNode& node) override;
    void Visit(otava::ast::ShortNode& node) override;
    void Visit(otava::ast::IntNode& node) override;
    void Visit(otava::ast::LongNode& node) override;
    void Visit(otava::ast::SignedNode& node) override;
    void Visit(otava::ast::UnsignedNode& node) override;
    void Visit(otava::ast::FloatNode& node) override;
    void Visit(otava::ast::DoubleNode& node) override;
    void Visit(otava::ast::VoidNode& node) override;
    void Visit(otava::ast::ConstNode& node) override;
    void Visit(otava::ast::VolatileNode& node) override;
    void Visit(otava::ast::LvalueRefNode& node) override;
    void Visit(otava::ast::RvalueRefNode& node) override;
    void Visit(otava::ast::PtrNode& node) override;
    void Visit(otava::ast::TypenameSpecifierNode& node) override;
    void Visit(otava::ast::DeclTypeSpecifierNode& node) override;
    void Visit(otava::ast::QualifiedIdNode& node) override;
    void Visit(otava::ast::IdentifierNode& node) override;
    void Visit(otava::ast::TemplateIdNode& node) override;
    void Visit(otava::ast::TypeIdNode& node) override;
    void Visit(otava::ast::FunctionDeclaratorNode& node) override;
private:
    Context* context;
    TypeSymbol* type;
    TypeSymbol* baseType;
    DeclarationFlags flags;
    int pointerCount;
    bool typeResolved;
    bool createTypeSymbol;
};

TypeResolver::TypeResolver(Context* context_, DeclarationFlags flags_) : 
    context(context_), 
    type(nullptr), 
    baseType(nullptr), 
    flags(flags_), 
    pointerCount(0), 
    typeResolved(false), 
    createTypeSymbol(false)
{
}

TypeSymbol* TypeResolver::GetType() 
{
    ResolveType();
    return type;
}

void TypeResolver::ResolveBaseType(otava::ast::Node* node)
{
    DeclarationFlags fundamentalTypeFlags = flags & DeclarationFlags::fundamentalTypeFlags;
    if (fundamentalTypeFlags != DeclarationFlags::none)
    {
        if (baseType)
        {
            ThrowException("duplicate type symbol in declaration specifier sequence", node->GetSourcePos(), context);
        }
        baseType = GetFundamentalType(fundamentalTypeFlags, node->GetSourcePos(), context);
    }
}

void TypeResolver::ResolveType()
{
    if (typeResolved) return;
    typeResolved = true;
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

void TypeResolver::Visit(otava::ast::DefiningTypeIdNode& node)
{
    node.DefiningTypeSpecifiers()->Accept(*this);
    if (!type)
    {
        ResolveBaseType(&node);
        type = baseType;
    }
    node.AbstractDeclarator()->Accept(*this);
    ResolveType();
}

void TypeResolver::Visit(otava::ast::TypeSpecifierSequenceNode& node)
{
    VisitSequenceContent(node);
    if (!type)
    {
        ResolveBaseType(&node);
        type = baseType;
    }
    ResolveType();
}

void TypeResolver::Visit(otava::ast::CharNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::charFlag, "char", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::charFlag;
}

void TypeResolver::Visit(otava::ast::Char8Node& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::char8Flag, "char8_t", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::char8Flag;
}

void TypeResolver::Visit(otava::ast::Char16Node& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::char16Flag, "char16_t", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::char16Flag;
}

void TypeResolver::Visit(otava::ast::Char32Node& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::char32Flag, "char32_t", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::char32Flag;
}

void TypeResolver::Visit(otava::ast::WCharNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::wcharFlag, "wchar_t", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::wcharFlag;
}

void TypeResolver::Visit(otava::ast::BoolNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::wcharFlag, "bool", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::boolFlag;
}

void TypeResolver::Visit(otava::ast::ShortNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::shortFlag, "short", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::shortFlag;
}

void TypeResolver::Visit(otava::ast::IntNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::intFlag, "int", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::intFlag;
}

void TypeResolver::Visit(otava::ast::LongNode& node)
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

void TypeResolver::Visit(otava::ast::SignedNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::signedFlag, "signed", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::signedFlag;
}

void TypeResolver::Visit(otava::ast::UnsignedNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::unsignedFlag, "unsigned", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::unsignedFlag;
}

void TypeResolver::Visit(otava::ast::FloatNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::floatFlag, "float", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::floatFlag;
}

void TypeResolver::Visit(otava::ast::DoubleNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::doubleFlag, "double", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::doubleFlag;
}

void TypeResolver::Visit(otava::ast::VoidNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::voidFlag, "void", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::voidFlag;
}

void TypeResolver::Visit(otava::ast::ConstNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::constFlag, "const", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::constFlag;
}

void TypeResolver::Visit(otava::ast::VolatileNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::volatileFlag, "volatile", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::volatileFlag;
}

void TypeResolver::Visit(otava::ast::LvalueRefNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::lvalueRefFlag, "&", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::lvalueRefFlag;
}

void TypeResolver::Visit(otava::ast::RvalueRefNode& node)
{
    CheckDuplicateSpecifier(flags, DeclarationFlags::rvalueRefFlag, "&&", node.GetSourcePos(), context);
    flags = flags | DeclarationFlags::rvalueRefFlag;
}

void TypeResolver::Visit(otava::ast::PtrNode& node)
{
    ++pointerCount;
}

void TypeResolver::Visit(otava::ast::TypenameSpecifierNode& node)
{
    context->GetSymbolTable()->PushTopScopeIndex();
    BeginScope(node.NestedNameSpecifier(), context);
    createTypeSymbol = true;
    node.Id()->Accept(*this);
    createTypeSymbol = false;
    EndScope(context);
    context->GetSymbolTable()->PopTopScopeIndex();
}

void TypeResolver::Visit(otava::ast::DeclTypeSpecifierNode& node)
{
    // TODO: resolve type of node.Expression();
    type = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::autoType);
}

void TypeResolver::Visit(otava::ast::QualifiedIdNode& node)
{
    context->GetSymbolTable()->PushTopScopeIndex();
    BeginScope(node.Left(), context);
    node.Right()->Accept(*this);
    EndScope(context);
    context->GetSymbolTable()->PopTopScopeIndex();
}

void TypeResolver::Visit(otava::ast::IdentifierNode& node)
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
            ThrowException("symbol '" + util::ToUtf8(symbol->Name()) + "' is not a type symbol", node.GetSourcePos(), context);
        }
    }
    else if (createTypeSymbol)
    {
        Scope* scope = context->GetSymbolTable()->CurrentScope()->SymbolScope();
        ContainerSymbol* containerSymbol = nullptr;
        if (scope->IsContainerScope())
        {
            ContainerScope* containerScope = static_cast<ContainerScope*>(scope);
            std::vector<Symbol*> symbols;
            std::set<Scope*> visited;
            containerScope->Lookup(node.Str(), SymbolGroupKind::typeSymbolGroup, ScopeLookup::thisScope, LookupFlags::none, symbols, visited, context);
            if (!symbols.empty())
            {
                Symbol* symbol = symbols.front();
                if (symbol->IsTypeSymbol())
                {
                    type = static_cast<TypeSymbol*>(symbol);
                }
                else
                {
                    type = context->GetSymbolTable()->GetErrorTypeSymbol();
                }
            }
            else
            {
                containerSymbol = containerScope->GetContainerSymbol();
                NestedTypeSymbol* nestedTypeSymbol = new NestedTypeSymbol(node.Str());
                containerSymbol->AddSymbol(nestedTypeSymbol, node.GetSourcePos(), context);
                type = nestedTypeSymbol;
            }
        }
        else
        {
            type = context->GetSymbolTable()->GetErrorTypeSymbol();
        }
    }
    else
    {
        ThrowException("symbol '" + util::ToUtf8(node.Str()) + "' not found", node.GetSourcePos(), context);
        type = context->GetSymbolTable()->GetErrorTypeSymbol();
    }
}

void TypeResolver::Visit(otava::ast::TemplateIdNode& node)
{
    TypeSymbol* typeSymbol = otava::symbols::ResolveType(node.TemplateName(), DeclarationFlags::none, context);
    TemplateDeclarationSymbol* templateDeclaration = nullptr;
    if (typeSymbol->IsClassTypeSymbol())
    {
        ClassTypeSymbol* classTemplate = static_cast<ClassTypeSymbol*>(typeSymbol);
        templateDeclaration = classTemplate->ParentTemplateDeclaration();
    }
    std::vector<Symbol*> templateArgs;
    int n = node.Items().size();
    for (int i = 0; i < n; ++i)
    {
        otava::ast::Node* argItem = node.Items()[i];
        TemplateParameterSymbol* templateParameter = nullptr;
        if (templateDeclaration && i < templateDeclaration->Arity())
        {
            templateParameter = templateDeclaration->TemplateParameters()[i];
            ParameterSymbol* parameter = templateParameter->GetParameterSymbol();
            if (parameter)
            {
                Value* value = Evaluate(argItem, context);
                templateArgs.push_back(value);
                continue;
            }
        }
        TypeSymbol* templateArg = otava::symbols::ResolveType(argItem, DeclarationFlags::none, context);
        templateArgs.push_back(templateArg);
    }
    TypeSymbol* specialization = Instantiate(typeSymbol, templateArgs, &node, context);
    type = specialization;
}

void TypeResolver::Visit(otava::ast::TypeIdNode& node)
{
    node.TypeSpecifiers()->Accept(*this);
    if (!type)
    {
        ResolveBaseType(&node);
        type = baseType;
    }
    node.Declarator()->Accept(*this);
}

void TypeResolver::Visit(otava::ast::FunctionDeclaratorNode& node)
{
    ResolveType();
    Declaration declaration = ProcessDeclarator(type, &node, flags, context);
    type = declaration.type;
}

TypeSymbol* ResolveType(otava::ast::Node* node, DeclarationFlags flags, Context* context)
{
    TypeResolver resolver(context, flags);
    node->Accept(resolver);
    return resolver.GetType();
}

TypeSymbol* ResolveFwdDeclaredType(TypeSymbol* type, const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (type->IsForwardClassDeclarationSymbol())
    {
        if (type->IsForwardClassDeclarationSymbol())
        {
            ForwardClassDeclarationSymbol* fwdClassDeclarationSymbol = static_cast<ForwardClassDeclarationSymbol*>(type);
            if (fwdClassDeclarationSymbol->GetClassTypeSymbol())
            {
                return fwdClassDeclarationSymbol->GetClassTypeSymbol();
            }
            else
            {
                Symbol* type = context->GetSymbolTable()->Lookup(fwdClassDeclarationSymbol->Name(), SymbolGroupKind::typeSymbolGroup, sourcePos, context, 
                    LookupFlags::noFwdDeclarationSymbol);
                if (type && type->IsClassTypeSymbol())
                {
                    fwdClassDeclarationSymbol->SetClassTypeSymbol(static_cast<ClassTypeSymbol*>(type));
                    return static_cast<TypeSymbol*>(type);
                }
            }
        }
        else if (type->IsForwardEnumDeclarationSymbol())
        {
            ForwardEnumDeclarationSymbol* fwdEnumDeclarationSymbol = static_cast<ForwardEnumDeclarationSymbol*>(type);
            if (fwdEnumDeclarationSymbol->GetEnumeratedTypeSymbol())
            {
                return fwdEnumDeclarationSymbol->GetEnumeratedTypeSymbol();
            }
            else
            {
                Symbol* type = context->GetSymbolTable()->Lookup(fwdEnumDeclarationSymbol->Name(), SymbolGroupKind::typeSymbolGroup, sourcePos, context,
                    LookupFlags::noFwdDeclarationSymbol);
                if (type && type->IsEnumeratedTypeSymbol())
                {
                    fwdEnumDeclarationSymbol->SetEnumeratedTypeSymbol(static_cast<EnumeratedTypeSymbol*>(type));
                    return static_cast<TypeSymbol*>(type);
                }
            }
        }
    }
    return type;
}

} // namespace otava::symbols