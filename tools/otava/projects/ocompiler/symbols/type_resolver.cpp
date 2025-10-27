// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.type.resolver;

import otava.symbols.context;
import otava.symbols.error;
import otava.symbols.alias.group.symbol;
import otava.symbols.alias.type.symbol;
import otava.symbols.alias.type.templates;
import otava.symbols.classes;
import otava.symbols.class_group.symbol;
import otava.symbols.declaration;
import otava.symbols.declarator;
import otava.symbols.derivations;
import otava.symbols.enums;
import otava.symbols.evaluator;
import otava.symbols.fundamental.type.symbol;
import otava.symbols.compound.type.symbol;
import otava.symbols.symbol.table;
import otava.symbols.scope.resolver;
import otava.symbols.templates;
import otava.symbols.class_templates;
import otava.symbols.inline_functions;
import otava.symbols.value;
import otava.symbols.expression.binder;
import otava.symbols.bound.tree;
import otava.symbols.function.kind;
import otava.symbols.function.symbol;
import otava.symbols.variable.symbol;
import util.unicode;

namespace otava::symbols {

std::expected<bool, int> CheckDuplicateSpecifier(DeclarationFlags flags, DeclarationFlags flag, const std::string& specifierStr, 
    const soul::ast::SourcePos& sourcePos, Context* context)
{
    if ((flags & flag) != DeclarationFlags::none)
    {
        return Error("duplicate '" + specifierStr + "'", sourcePos, context);
    }
    return std::expected<bool, int>(true);
}

class TypeResolver : public otava::ast::DefaultVisitor
{
public:
    TypeResolver(Context* context_, DeclarationFlags flags_, TypeResolverFlags resolverFlags_);
    std::expected<TypeSymbol*, int> GetType();
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
    void Visit(otava::ast::NewTypeIdNode& node) override;
    void Visit(otava::ast::ArrayNewDeclaratorNode& node) override;
private:
    Context* context;
    TypeSymbol* type;
    TypeSymbol* baseType;
    DeclarationFlags flags;
    TypeResolverFlags resolverFlags;
    int pointerCount;
    bool typeResolved;
    bool createTypeSymbol;
    BoundExpressionNode* size;
};

TypeResolver::TypeResolver(Context* context_, DeclarationFlags flags_, TypeResolverFlags resolverFlags_) :
    context(context_),
    type(nullptr),
    baseType(nullptr),
    flags(flags_),
    resolverFlags(resolverFlags_),
    pointerCount(0),
    typeResolved(false),
    createTypeSymbol(false),
    size(nullptr)
{
}

std::expected<TypeSymbol*, int> TypeResolver::GetType()
{
    ResolveType();
    if (!Valid()) return std::unexpected<int>(Error());
    return std::expected<TypeSymbol*, int>(type);
}

void TypeResolver::ResolveBaseType(otava::ast::Node* node)
{
    if (!Valid()) return;
    DeclarationFlags fundamentalTypeFlags = flags & DeclarationFlags::fundamentalTypeFlags;
    if (fundamentalTypeFlags != DeclarationFlags::none)
    {
        if (baseType)
        {
            std::unexpected<int> result = Error("duplicate type symbol in declaration specifier sequence", node->GetSourcePos(), context);
            SetError(result.error());
            return;
        }
        std::expected<TypeSymbol*, int> f = GetFundamentalType(fundamentalTypeFlags, node->GetSourcePos(), context);
        if (!f)
        {
            SetError(f.error());
            return;
        }
        baseType = *f;
    }
}

void TypeResolver::ResolveType()
{
    if (!Valid()) return;
    if (typeResolved) return;
    typeResolved = true;
    Derivations derivations = Derivations::none;
    if ((flags & DeclarationFlags::constFlag) != DeclarationFlags::none)
    {
        derivations = derivations | Derivations::constDerivation;
    }
    if ((flags & DeclarationFlags::volatileFlag) != DeclarationFlags::none)
    {
        derivations = derivations | Derivations::volatileDerivation;
    }
    if (pointerCount > 0)
    {
        derivations = otava::symbols::SetPointerCount(derivations, pointerCount);
    }
    if ((flags & DeclarationFlags::lvalueRefFlag) != DeclarationFlags::none)
    {
        derivations = derivations | Derivations::lvalueRefDerivation;
    }
    else if ((flags & DeclarationFlags::rvalueRefFlag) != DeclarationFlags::none)
    {
        derivations = derivations | Derivations::rvalueRefDerivation;
    }
    if (derivations != Derivations::none && type)
    {
        std::expected<TypeSymbol*, int> rv = context->GetSymbolTable()->MakeCompoundType(type, derivations);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        type = *rv;
    }
}

void TypeResolver::Visit(otava::ast::DefiningTypeIdNode& node)
{
    if (!Valid()) return;
    node.DefiningTypeSpecifiers()->Accept(*this);
    if (!Valid()) return;
    if (!type)
    {
        ResolveBaseType(&node);
        if (!Valid()) return;
        type = baseType;
    }
    node.AbstractDeclarator()->Accept(*this);
    if (!Valid()) return;
    ResolveType();
}

void TypeResolver::Visit(otava::ast::TypeSpecifierSequenceNode& node)
{
    if (!Valid()) return;
    VisitSequenceContent(node);
    if (!Valid()) return;
    if (!type)
    {
        ResolveBaseType(&node);
        if (!Valid()) return;
        type = baseType;
    }
    ResolveType();
}

void TypeResolver::Visit(otava::ast::CharNode& node)
{
    if (!Valid()) return;
    auto rv = CheckDuplicateSpecifier(flags, DeclarationFlags::charFlag, "char", node.GetSourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    flags = flags | DeclarationFlags::charFlag;
}

void TypeResolver::Visit(otava::ast::Char8Node& node)
{
    if (!Valid()) return;
    auto rv = CheckDuplicateSpecifier(flags, DeclarationFlags::char8Flag, "char8_t", node.GetSourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    flags = flags | DeclarationFlags::char8Flag;
}

void TypeResolver::Visit(otava::ast::Char16Node& node)
{
    if (!Valid()) return;
    auto rv = CheckDuplicateSpecifier(flags, DeclarationFlags::char16Flag, "char16_t", node.GetSourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    flags = flags | DeclarationFlags::char16Flag;
}

void TypeResolver::Visit(otava::ast::Char32Node& node)
{
    if (!Valid()) return;
    auto rv = CheckDuplicateSpecifier(flags, DeclarationFlags::char32Flag, "char32_t", node.GetSourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    flags = flags | DeclarationFlags::char32Flag;
}

void TypeResolver::Visit(otava::ast::WCharNode& node)
{
    if (!Valid()) return;
    auto rv = CheckDuplicateSpecifier(flags, DeclarationFlags::wcharFlag, "wchar_t", node.GetSourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    flags = flags | DeclarationFlags::wcharFlag;
}

void TypeResolver::Visit(otava::ast::BoolNode& node)
{
    if (!Valid()) return;
    auto rv = CheckDuplicateSpecifier(flags, DeclarationFlags::wcharFlag, "bool", node.GetSourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    flags = flags | DeclarationFlags::boolFlag;
}

void TypeResolver::Visit(otava::ast::ShortNode& node)
{
    if (!Valid()) return;
    auto rv = CheckDuplicateSpecifier(flags, DeclarationFlags::shortFlag, "short", node.GetSourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    flags = flags | DeclarationFlags::shortFlag;
}

void TypeResolver::Visit(otava::ast::IntNode& node)
{
    if (!Valid()) return;
    auto rv = CheckDuplicateSpecifier(flags, DeclarationFlags::intFlag, "int", node.GetSourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    flags = flags | DeclarationFlags::intFlag;
}

void TypeResolver::Visit(otava::ast::LongNode& node)
{
    if (!Valid()) return;
    auto rv = CheckDuplicateSpecifier(flags, DeclarationFlags::longLongFlag, "long long", node.GetSourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
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
    if (!Valid()) return;
    auto rv = CheckDuplicateSpecifier(flags, DeclarationFlags::signedFlag, "signed", node.GetSourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    flags = flags | DeclarationFlags::signedFlag;
}

void TypeResolver::Visit(otava::ast::UnsignedNode& node)
{
    if (!Valid()) return;
    auto rv = CheckDuplicateSpecifier(flags, DeclarationFlags::unsignedFlag, "unsigned", node.GetSourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    flags = flags | DeclarationFlags::unsignedFlag;
}

void TypeResolver::Visit(otava::ast::FloatNode& node)
{
    if (!Valid()) return;
    auto rv = CheckDuplicateSpecifier(flags, DeclarationFlags::floatFlag, "float", node.GetSourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    flags = flags | DeclarationFlags::floatFlag;
}

void TypeResolver::Visit(otava::ast::DoubleNode& node)
{
    if (!Valid()) return;
    auto rv = CheckDuplicateSpecifier(flags, DeclarationFlags::doubleFlag, "double", node.GetSourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    flags = flags | DeclarationFlags::doubleFlag;
}

void TypeResolver::Visit(otava::ast::VoidNode& node)
{
    if (!Valid()) return;
    auto rv = CheckDuplicateSpecifier(flags, DeclarationFlags::voidFlag, "void", node.GetSourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    flags = flags | DeclarationFlags::voidFlag;
}

void TypeResolver::Visit(otava::ast::ConstNode& node)
{
    if (!Valid()) return;
    auto rv = CheckDuplicateSpecifier(flags, DeclarationFlags::constFlag, "const", node.GetSourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    flags = flags | DeclarationFlags::constFlag;
}

void TypeResolver::Visit(otava::ast::VolatileNode& node)
{
    if (!Valid()) return;
    auto rv = CheckDuplicateSpecifier(flags, DeclarationFlags::volatileFlag, "volatile", node.GetSourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    flags = flags | DeclarationFlags::volatileFlag;
}

void TypeResolver::Visit(otava::ast::LvalueRefNode& node)
{
    if (!Valid()) return;
    auto rv = CheckDuplicateSpecifier(flags, DeclarationFlags::lvalueRefFlag, "&", node.GetSourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    flags = flags | DeclarationFlags::lvalueRefFlag;
}

void TypeResolver::Visit(otava::ast::RvalueRefNode& node)
{
    if (!Valid()) return;
    auto rv = CheckDuplicateSpecifier(flags, DeclarationFlags::rvalueRefFlag, "&&", node.GetSourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    flags = flags | DeclarationFlags::rvalueRefFlag;
}

void TypeResolver::Visit(otava::ast::PtrNode& node)
{
    ++pointerCount;
}

void TypeResolver::Visit(otava::ast::TypenameSpecifierNode& node)
{
    if (!Valid()) return;
    if (context->GetFlag(ContextFlags::processingAliasDeclation))
    {
        context->GetSymbolTable()->PushTopScopeIndex();
        std::expected<bool, int> s = BeginScope(node.NestedNameSpecifier(), context);
        if (!s)
        {
            SetError(s.error());
            return;
        }
        createTypeSymbol = true;
        node.Id()->Accept(*this);
        if (!Valid()) return;
        createTypeSymbol = false;
        s = EndScope(context);
        if (!s)
        {
            SetError(s.error());
            return;
        }
        context->GetSymbolTable()->PopTopScopeIndex();
    }
    else
    {
        if (context->GetFlag(ContextFlags::parsingTemplateDeclaration))
        {
            std::expected<otava::ast::Node*, int> n = node.Clone();
            if (!n)
            {
                SetError(n.error());
                return;
            }
            type = context->GetSymbolTable()->MakeDependentTypeSymbol(*n);
        }
        else
        {
            InstantiationScope instantiationScope(context->GetSymbolTable()->CurrentScope());
            std::vector<std::unique_ptr<BoundTemplateParameterSymbol>> boundTemplateParameters;
            if (context->TemplateParameterMap())
            {
                for (const auto& templateParamType : *context->TemplateParameterMap())
                {
                    TemplateParameterSymbol* templateParameter = templateParamType.first;
                    BoundTemplateParameterSymbol* boundTemplateParameter = new BoundTemplateParameterSymbol(templateParameter->Name());
                    boundTemplateParameter->SetTemplateParameterSymbol(templateParameter);
                    boundTemplateParameter->SetBoundSymbol(templateParamType.second);
                    boundTemplateParameters.push_back(std::unique_ptr<BoundTemplateParameterSymbol>(boundTemplateParameter));
                    instantiationScope.Install(boundTemplateParameter, context);
                }
            }
            context->GetSymbolTable()->PushTopScopeIndex();
            context->GetSymbolTable()->BeginScope(&instantiationScope);
            std::expected<bool, int> rv = BeginScope(node.NestedNameSpecifier(), context);
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
            node.Id()->Accept(*this);
            if (!Valid()) return;
            rv = EndScope(context);
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
            rv = context->GetSymbolTable()->EndScope();
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
            context->GetSymbolTable()->PopTopScopeIndex();
        }
    }
}

void TypeResolver::Visit(otava::ast::DeclTypeSpecifierNode& node)
{
    if (!Valid()) return;
    std::expected<BoundExpressionNode*, int> e = BindExpression(node.Expression(), context);
    if (!e)
    {
        SetError(e.error());
        return;
    }
    std::unique_ptr<BoundExpressionNode> expr(*e);
    std::expected<TypeSymbol*, int> pt = expr->GetType()->PlainType(context);
    if (!pt)
    {
        SetError(pt.error());
        return;
    }
    type = *pt;
}

void TypeResolver::Visit(otava::ast::QualifiedIdNode& node)
{
    if (!Valid()) return;
    context->GetSymbolTable()->PushTopScopeIndex();
    std::expected<bool, int> rv = BeginScope(node.Left(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    node.Right()->Accept(*this);
    if (!Valid()) return;
    rv = EndScope(context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    context->GetSymbolTable()->PopTopScopeIndex();
}

void TypeResolver::Visit(otava::ast::IdentifierNode& node)
{
    if (!Valid()) return;
    std::expected<Symbol*, int> s = context->GetSymbolTable()->Lookup(node.Str(), SymbolGroupKind::typeSymbolGroup, node.GetSourcePos(), context);
    if (!s)
    {
        SetError(s.error());
        return;
    }
    Symbol* symbol = *s;
    if (!symbol && !createTypeSymbol)
    {
        int topScopeIndex = context->GetSymbolTable()->TopScopeIndex();
        context->GetSymbolTable()->SetTopScopeIndex(0);
        s = context->GetSymbolTable()->LookupInScopeStack(node.Str(), SymbolGroupKind::typeSymbolGroup, node.GetSourcePos(), context, LookupFlags::none);
        if (!s)
        {
            SetError(s.error());
            return;
        }
        symbol = *s;
        context->GetSymbolTable()->SetTopScopeIndex(topScopeIndex);
    }
    if (symbol)
    {
        if (symbol->IsTypeSymbol())
        {
            type = static_cast<TypeSymbol*>(symbol);
        }
        else if (symbol->IsAliasGroupSymbol())
        {
            AliasGroupSymbol* aliasGroup = static_cast<AliasGroupSymbol*>(symbol);
            type = context->GetSymbolTable()->MakeAliasGroupTypeSymbol(aliasGroup);
        }
        else if (symbol->IsClassGroupSymbol())
        {
            ClassGroupSymbol* classGroup = static_cast<ClassGroupSymbol*>(symbol);
            type = context->GetSymbolTable()->MakeClassGroupTypeSymbol(classGroup);
        }
        else
        {
            std::expected<std::string, int> name = util::ToUtf8(symbol->Name());
            if (!name)
            {
                SetError(name.error());
                return;
            }
            std::unexpected<int> result = Error("symbol '" + *name + "' is not a type symbol", node.GetSourcePos(), context);
            type = nullptr;
            SetError(result.error());
            return;
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
                std::expected<bool, int> rv = containerSymbol->AddSymbol(nestedTypeSymbol, node.GetSourcePos(), context);
                if (!rv)
                {
                    SetError(rv.error());
                    return;
                }
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
        type = nullptr;
        std::expected<std::string, int> s = util::ToUtf8(node.Str());
        if (!s)
        {
            SetError(s.error());
            return;
        }
        std::unexpected<int> result = Error("symbol '" + *s + "' not found", node.GetSourcePos(), context);
        SetError(result.error());
        return;
    }
}

void TypeResolver::Visit(otava::ast::TemplateIdNode& node)
{
    if (!Valid()) return;
    std::expected<TypeSymbol*, int> t = otava::symbols::ResolveType(node.TemplateName(), DeclarationFlags::none, context, resolverFlags);
    if (!t)
    {
        SetError(t.error());
        return;
    }
    TypeSymbol* typeSymbol = *t;
    if (!typeSymbol)
    {
        type = nullptr;
        return;
    }
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
                std::expected<Value*, int> v = Evaluate(argItem, context);
                if (!v)
                {
                    SetError(v.error());
                    return;
                }
                Value* value = *v;
                templateArgs.push_back(value);
                continue;
            }
        }
        t = otava::symbols::ResolveType(argItem, DeclarationFlags::none, context, resolverFlags);
        if (!t)
        {
            SetError(t.error());
            return;
        }
        TypeSymbol* templateArg = *t;
        if (!templateArg)
        {
            type = nullptr;
            return;
        }
        std::expected<TypeSymbol*, int> dt = templateArg->DirectType(context);
        if (!dt)
        {
            SetError(dt.error());
            return;
        }
        TypeSymbol* directType = *dt;
        std::expected<TypeSymbol*, int> ft = directType->FinalType(node.GetSourcePos(), context);
        if (!ft)
        {
            SetError(ft.error());
            return;
        }
        templateArg = *ft;
        templateArgs.push_back(templateArg);
    }
    if (typeSymbol->IsClassGroupTypeSymbol())
    {
        ClassGroupTypeSymbol* classGroupType = static_cast<ClassGroupTypeSymbol*>(typeSymbol);
        ClassGroupSymbol* classGroup = classGroupType->ClassGroup();
        TemplateMatchInfo matchInfo;
        std::expected<ClassTypeSymbol*, int> m = classGroup->GetBestMatchingClass(templateArgs, matchInfo, context);
        if (!m)
        {
            SetError(m.error());
            return;
        }
        typeSymbol = *m;
        if (!typeSymbol)
        {
            std::expected<std::string, int> group = util::ToUtf8(classGroup->Name());
            if (!group)
            {
                SetError(group.error());
                return;
            }
            std::unexpected<int> result = Error("no matching class found from class group '" + *group + "'", node.GetSourcePos(), context);
            SetError(result.error());
            return;
        }
        else
        {
            if (matchInfo.kind == TemplateMatchKind::explicitSpecialization)
            {
                templateArgs = matchInfo.templateArgs;
            }
        }
    }
    else if (typeSymbol->IsAliasGroupTypeSymbol())
    {
        AliasGroupTypeSymbol* aliasGroupType = static_cast<AliasGroupTypeSymbol*>(typeSymbol);
        AliasGroupSymbol* aliasGroup = aliasGroupType->AliasGroup();
        typeSymbol = aliasGroup->GetBestMatchingAliasType(templateArgs, context);
        if (!typeSymbol)
        {
            std::expected<std::string, int> group = util::ToUtf8(aliasGroup->Name());
            if (!group)
            {
                SetError(group.error());
                return;
            }
            std::unexpected<int> result = Error("no matching alias type found from alias group '" + *group + "'", node.GetSourcePos(), context);
            SetError(result.error());
            return;
        }
    }
    else if (typeSymbol->IsForwardClassDeclarationSymbol())
    {
        std::expected<TypeSymbol*, int> f = ResolveFwdDeclaredType(typeSymbol, node.GetSourcePos(), context);
        if (!f)
        {
            SetError(f.error());
            return;
        }
        typeSymbol = *f;
    }
    if ((resolverFlags & TypeResolverFlags::dontInstantiate) == TypeResolverFlags::none)
    {
        if (typeSymbol->IsAliasTypeSymbol())
        {
            std::expected<TypeSymbol*, int> a = InstantiateAliasTypeSymbol(typeSymbol, templateArgs, &node, context);
            if (!a)
            {
                SetError(a.error());
                return;
            }
            TypeSymbol* specialization = *a;
            type = specialization;
        }
        else if (typeSymbol->IsClassTypeSymbol())
        {
            ClassTypeSymbol* classTemplate = static_cast<ClassTypeSymbol*>(typeSymbol);
            std::expected<ClassTemplateSpecializationSymbol*, int> c = InstantiateClassTemplate(classTemplate, templateArgs, node.GetSourcePos(), context);
            if (!c)
            {
                SetError(c.error());
                return;
            }
            TypeSymbol* specialization = *c;
            type = specialization;
        }
        else if (typeSymbol->IsForwardClassDeclarationSymbol())
        {
            type = typeSymbol;
        }
        else
        {
            std::unexpected<int> result = Error("alias type or class type expected", node.GetSourcePos(), context);
            SetError(result.error());
            return;
        }
    }
    else
    {
        if (typeSymbol->IsClassTypeSymbol())
        {
            ClassTypeSymbol* classTemplate = static_cast<ClassTypeSymbol*>(typeSymbol);
            std::expected<ClassTemplateSpecializationSymbol*, int> sp = context->GetSymbolTable()->MakeClassTemplateSpecialization(classTemplate, templateArgs);
            if (!sp)
            {
                SetError(sp.error());
                return;
            }
            ClassTemplateSpecializationSymbol* specialization = *sp;
            type = specialization;
        }
        else
        {
            std::unexpected<int> result = Error("alias type or class type expected", node.GetSourcePos(), context);
            SetError(result.error());
            return;
        }
    }
}

void TypeResolver::Visit(otava::ast::TypeIdNode& node)
{
    if (!Valid()) return;
    node.TypeSpecifiers()->Accept(*this);
    if (!Valid()) return;
    while (type && type->IsAliasTypeSymbol())
    {
        AliasTypeSymbol* aliasType = static_cast<AliasTypeSymbol*>(type);
        type = aliasType->ReferredType();
    }
    if (!type)
    {
        ResolveBaseType(&node);
        if (!Valid()) return;
        type = baseType;
    }
    DeclarationFlags prevFlags = flags;
    node.Declarator()->Accept(*this);
    if (!Valid()) return;
    typeResolved = false;
    ResolveType();
}

void TypeResolver::Visit(otava::ast::FunctionDeclaratorNode& node)
{
    if (!Valid()) return;
    ResolveType();
    if (!Valid()) return;
    std::expected<Declaration, int> d = ProcessDeclarator(type, &node, &node, flags, FunctionQualifiers::none, context);
    if (!d)
    {
        SetError(d.error());
        return;
    }
    Declaration declaration = std::move(*d);
    type = declaration.type;
}

void TypeResolver::Visit(otava::ast::NewTypeIdNode& node)
{
    if (!Valid()) return;
    node.TypeSpecifierSeq()->Accept(*this);
    if (!Valid()) return;
    TypeSymbol* newType = type;
    if (node.NewDeclarator())
    {
        node.NewDeclarator()->Accept(*this);
        if (!Valid()) return;
    }
}

void TypeResolver::Visit(otava::ast::ArrayNewDeclaratorNode& node)
{
    std::expected<BoundExpressionNode*, int> s = BindExpression(&node, context);
    if (!s)
    {
        SetError(s.error());
        return;
    }
    size = *s;
}

std::expected<TypeSymbol*, int> ResolveType(otava::ast::Node* node, DeclarationFlags flags, Context* context)
{
    return ResolveType(node, flags, context, TypeResolverFlags::none);
}

std::expected<TypeSymbol*, int> ResolveType(otava::ast::Node* node, DeclarationFlags flags, Context* context, TypeResolverFlags resolverFlags)
{
    TypeResolver resolver(context, flags, resolverFlags);
    node->Accept(resolver);
    if (!resolver) return std::unexpected<int>(resolver.Error());
    return resolver.GetType();
}

std::expected<TypeSymbol*, int> ResolveFwdDeclaredType(TypeSymbol* type, const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (type->IsCompoundTypeSymbol())
    {
        CompoundTypeSymbol* compoundTypeSymbol = static_cast<CompoundTypeSymbol*>(type);
        std::expected<TypeSymbol*, int> r = ResolveFwdDeclaredType(compoundTypeSymbol->GetBaseType(), sourcePos, context);
        if (!r) return r;
        std::expected<TypeSymbol*, int> rv = context->GetSymbolTable()->MakeCompoundType(*r, compoundTypeSymbol->GetDerivations());
        if (!rv) return std::unexpected<int>(rv.error());
        TypeSymbol* resolvedType = *rv;
        return std::expected<TypeSymbol*, int>(resolvedType);
    }
    if (type->IsForwardClassDeclarationSymbol())
    {
        ForwardClassDeclarationSymbol* fwdClassDeclarationSymbol = static_cast<ForwardClassDeclarationSymbol*>(type);
        if (fwdClassDeclarationSymbol->GetClassTypeSymbol())
        {
            return std::expected<TypeSymbol*, int>(fwdClassDeclarationSymbol->GetClassTypeSymbol());
        }
        else
        {
            std::expected<Symbol*, int> s = context->GetSymbolTable()->Lookup(fwdClassDeclarationSymbol->Name(), SymbolGroupKind::typeSymbolGroup, sourcePos, context,
                LookupFlags::noFwdDeclarationSymbol);
            if (!s) return std::unexpected<int>(s.error());
            Symbol* type = *s;
            if (type && type->IsClassTypeSymbol())
            {
                fwdClassDeclarationSymbol->SetClassTypeSymbol(static_cast<ClassTypeSymbol*>(type));
                return std::expected<TypeSymbol*, int>(static_cast<TypeSymbol*>(type));
            }
        }
    }
    else if (type->IsForwardEnumDeclarationSymbol())
    {
        ForwardEnumDeclarationSymbol* fwdEnumDeclarationSymbol = static_cast<ForwardEnumDeclarationSymbol*>(type);
        if (fwdEnumDeclarationSymbol->GetEnumeratedTypeSymbol())
        {
            return std::expected<TypeSymbol*, int>(fwdEnumDeclarationSymbol->GetEnumeratedTypeSymbol());
        }
        else
        {
            std::expected<Symbol*, int> s = context->GetSymbolTable()->Lookup(fwdEnumDeclarationSymbol->Name(), SymbolGroupKind::typeSymbolGroup, sourcePos, context,
                LookupFlags::noFwdDeclarationSymbol);
            if (!s) return std::unexpected<int>(s.error());
            Symbol* type = *s;
            if (type && type->IsEnumeratedTypeSymbol())
            {
                fwdEnumDeclarationSymbol->SetEnumeratedTypeSymbol(static_cast<EnumeratedTypeSymbol*>(type));
                return std::expected<TypeSymbol*, int>(static_cast<TypeSymbol*>(type));
            }
        }
    }
    return std::expected<TypeSymbol*, int>(type);
}

} // namespace otava::symbols
