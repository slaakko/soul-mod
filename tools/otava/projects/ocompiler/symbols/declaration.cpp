// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.declaration;

import otava.symbols.context;
import otava.symbols.declarator;
import otava.symbols.evaluator;
import otava.symbols.error;
import otava.symbols.function.kind;
import otava.symbols.function.symbol;
import otava.symbols.function.group.symbol;
import otava.symbols.fundamental.type.symbol;
import otava.symbols.type.resolver;
import otava.symbols.symbol.table;
import otava.symbols.reader;
import otava.symbols.writer;
import otava.symbols.bound.tree;
import otava.symbols.symbol;
import otava.symbols.statement.binder;
import otava.symbols.classes;
import otava.symbols.alias.type.symbol;
import otava.symbols.templates;
import otava.symbols.variable.symbol;
import otava.symbols.class_templates;
import otava.symbols.inline_functions;
import otava.symbols.array.type.symbol;
import otava.symbols.overload.resolution;
import otava.symbols.modules;
import otava.symbols.conversion.table;
import otava.symbols.expression.binder;
import otava.symbols.type_compare;
import otava.symbols.type.symbol;
import otava.symbols.value;
import otava.symbols.function.templates;
import otava.symbols.inline_functions;
import otava.symbols.argument.conversion.table;
import otava.symbols.operation.repository;
import otava.ast.attribute;
import otava.ast.visitor;
import util;

namespace otava::symbols {

struct ArraySizeComputer : public otava::ast::DefaultVisitor
{
    ArraySizeComputer();
    void Visit(otava::ast::InitDeclaratorNode& node);
    void Visit(otava::ast::AssignmentInitNode& node);
    void Visit(otava::ast::BracedInitListNode& node);
    std::int64_t size;
};

ArraySizeComputer::ArraySizeComputer() : size(-1)
{
}

void ArraySizeComputer::Visit(otava::ast::InitDeclaratorNode& node)
{
    node.Right()->Accept(*this);
}

void ArraySizeComputer::Visit(otava::ast::AssignmentInitNode& node)
{
    node.Child()->Accept(*this);
}

void ArraySizeComputer::Visit(otava::ast::BracedInitListNode& node)
{
    std::int64_t count = 0;
    for (otava::ast::Node* item : node.Items())
    {
        if (item->IsLBraceNode() || item->IsRBraceNode()) continue;
        ++count;
    }
    size = count;
}

std::int64_t GetSizeFromInitializer(otava::ast::Node* node)
{
    if (node->Parent())
    {
        ArraySizeComputer visitor;
        node->Parent()->Accept(visitor);
        return visitor.size;
    }
    return -1;
}

class NoReturnAttributeMatcher : public otava::ast::DefaultVisitor
{
public:
    NoReturnAttributeMatcher();
    void Visit(otava::ast::AttributeNode& node);
    void Visit(otava::ast::IdentifierNode& node);
    inline bool GetValue() const { return value; }
private:
    bool matchId;
    bool value;
};

NoReturnAttributeMatcher::NoReturnAttributeMatcher() : matchId(false), value(false)
{
}

void NoReturnAttributeMatcher::Visit(otava::ast::AttributeNode& node)
{
    matchId = true;
    node.AttributeToken()->Accept(*this);
    matchId = false;
}

void NoReturnAttributeMatcher::Visit(otava::ast::IdentifierNode& node)
{
    if (!matchId) return;
    if (node.Str() == U"noreturn")
    {
        value = true;
    }
}

bool HasNoReturnAttribute(otava::ast::Node* attributes)
{
    if (!attributes) return false;
    NoReturnAttributeMatcher noReturnAttributeMatcher;
    attributes->Accept(noReturnAttributeMatcher);
    return noReturnAttributeMatcher.GetValue();
}

std::string DeclarationFlagStr(DeclarationFlags flags)
{
    std::string str;
    if ((flags & DeclarationFlags::typedefFlag) != DeclarationFlags::none)
    {
        if (!str.empty())
        {
            str.append(1, ' ');
        }
        str.append("typedef");
    }
    if ((flags & DeclarationFlags::staticFlag) != DeclarationFlags::none)
    {
        if (!str.empty())
        {
            str.append(1, ' ');
        }
        str.append("static");
    }
    if ((flags & DeclarationFlags::threadLocalFlag) != DeclarationFlags::none)
    {
        if (!str.empty())
        {
            str.append(1, ' ');
        }
        str.append("thread_local");
    }
    if ((flags & DeclarationFlags::externFlag) != DeclarationFlags::none)
    {
        if (!str.empty())
        {
            str.append(1, ' ');
        }
        str.append("extern");
    }
    if ((flags & DeclarationFlags::mutableFlag) != DeclarationFlags::none)
    {
        if (!str.empty())
        {
            str.append(1, ' ');
        }
        str.append("mutable");
    }
    if ((flags & DeclarationFlags::virtualFlag) != DeclarationFlags::none)
    {
        if (!str.empty())
        {
            str.append(1, ' ');
        }
        str.append("virtual");
    }
    if ((flags & DeclarationFlags::explicitFlag) != DeclarationFlags::none)
    {
        if (!str.empty())
        {
            str.append(1, ' ');
        }
        str.append("explicit");
    }
    if ((flags & DeclarationFlags::inlineFlag) != DeclarationFlags::none)
    {
        if (!str.empty())
        {
            str.append(1, ' ');
        }
        str.append("inline");
    }
    if ((flags & DeclarationFlags::friendFlag) != DeclarationFlags::none)
    {
        if (!str.empty())
        {
            str.append(1, ' ');
        }
        str.append("friend");
    }
    if ((flags & DeclarationFlags::constExprFlag) != DeclarationFlags::none)
    {
        if (!str.empty())
        {
            str.append(1, ' ');
        }
        str.append("constexpr");
    }
    if ((flags & DeclarationFlags::constEvalFlag) != DeclarationFlags::none)
    {
        if (!str.empty())
        {
            str.append(1, ' ');
        }
        str.append("consteval");
    }
    if ((flags & DeclarationFlags::constInitFlag) != DeclarationFlags::none)
    {
        if (!str.empty())
        {
            str.append(1, ' ');
        }
        str.append("constinit");
    }
    return str;
}

class FunctionQualifierExtractor : public otava::ast::DefaultVisitor
{
public:
    FunctionQualifierExtractor();
    inline FunctionQualifiers Qualifiers() const { return qualifiers; }
    void Visit(otava::ast::VirtSpecifierSequenceNode& node) override;
    void Visit(otava::ast::OverrideNode& node) override;
    void Visit(otava::ast::FinalNode& node) override;
private:
    FunctionQualifiers qualifiers;
};

FunctionQualifierExtractor::FunctionQualifierExtractor() : qualifiers(FunctionQualifiers::none)
{
}

void FunctionQualifierExtractor::Visit(otava::ast::VirtSpecifierSequenceNode& node)
{
    for (const auto& specifierNode : node.Nodes())
    {
        specifierNode->Accept(*this);
    }
}

void FunctionQualifierExtractor::Visit(otava::ast::OverrideNode& node)
{
    qualifiers = qualifiers | FunctionQualifiers::isOverride;
}

void FunctionQualifierExtractor::Visit(otava::ast::FinalNode& node)
{
    qualifiers = qualifiers | FunctionQualifiers::isFinal;
}

FunctionQualifiers GetQualifiers(otava::ast::Node* specifierNode)
{
    FunctionQualifierExtractor extractor;
    if (specifierNode)
    {
        specifierNode->Accept(extractor);
    }
    return extractor.Qualifiers();
}

class DeclarationProcessor : public otava::ast::DefaultVisitor
{
public:
    DeclarationProcessor(Context* context_);
    inline std::unique_ptr<DeclarationList> GetDeclarations();
    inline TypeSymbol* GetType() const { return type; }
    void BeginProcessFunctionDefinition(otava::ast::Node* declSpecifierSeq, otava::ast::Node* declarator, otava::ast::Node* specifierNode);
    void Visit(otava::ast::SimpleDeclarationNode& node) override;
    void Visit(otava::ast::MemberDeclarationNode& node) override;
    void Visit(otava::ast::NoDeclSpecFunctionDeclarationNode& node) override;
    void Visit(otava::ast::FunctionDefinitionNode& node) override;
    void Visit(otava::ast::ParameterNode& node) override;
    void Visit(otava::ast::ExceptionDeclarationNode& node) override;
    void Visit(otava::ast::ClassSpecifierNode& node) override;
    void Visit(otava::ast::EnumSpecifierNode& node) override;
    void Visit(otava::ast::ElaboratedTypeSpecifierNode & override);
    std::expected<TypeSymbol*, int> ResolveBaseType(otava::ast::Node* node);
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
    void Visit(otava::ast::PlaceholderTypeSpecifierNode& node) override;

    void Visit(otava::ast::FriendNode& node) override;
    void Visit(otava::ast::TypedefNode& node) override;
    void Visit(otava::ast::ConstExprNode& node) override;
    void Visit(otava::ast::ConstEvalNode& node) override;
    void Visit(otava::ast::ConstInitNode& node) override;
    void Visit(otava::ast::InlineNode& node) override;
    void Visit(otava::ast::StaticNode& node) override;
    void Visit(otava::ast::ThreadLocalNode& node) override;
    void Visit(otava::ast::ExternNode& node) override;
    void Visit(otava::ast::VirtualNode& node) override;
    void Visit(otava::ast::ExplicitNode& node) override;

    void Visit(otava::ast::QualifiedIdNode& node) override;
    void Visit(otava::ast::IdentifierNode& node) override;
    void Visit(otava::ast::TemplateIdNode& node) override;

    void Visit(otava::ast::TypenameSpecifierNode& node) override;
private:
    Context* context;
    DeclarationFlags flags;
    bool isClassSpecifier;
    TypeSymbol* type;
    std::unique_ptr<DeclarationList> declarationList;
};

DeclarationProcessor::DeclarationProcessor(Context* context_) :
    context(context_), flags(DeclarationFlags::none), isClassSpecifier(false), type(nullptr), declarationList(new DeclarationList())
{
}

std::unique_ptr<DeclarationList> DeclarationProcessor::GetDeclarations()
{
    return std::move(declarationList);
}

void DeclarationProcessor::BeginProcessFunctionDefinition(otava::ast::Node* declSpecifierSeq, otava::ast::Node* declarator, otava::ast::Node* specifierNode)
{
    if (!Valid()) return;
    if (declSpecifierSeq)
    {
        declSpecifierSeq->Accept(*this);
    }
    std::expected<TypeSymbol*, int> brv = ResolveBaseType(declSpecifierSeq);
    if (!brv)
    {
        SetError(brv.error());
        return;
    }
    TypeSymbol* baseType = *brv;
    FunctionQualifiers qualifiers = GetQualifiers(specifierNode);
    std::expected<Declaration, int> rv = ProcessDeclarator(baseType, declarator, nullptr, flags, qualifiers, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    Declaration declaration = std::move(*rv);
    declarationList->declarations.push_back(std::move(declaration));
}

std::expected<TypeSymbol*, int> DeclarationProcessor::ResolveBaseType(otava::ast::Node* node)
{
    if (!Valid()) return std::unexpected<int>(Error());
    TypeSymbol* baseType = nullptr;
    DeclarationFlags fundamentalTypeFlags = flags & DeclarationFlags::fundamentalTypeFlags;
    if (fundamentalTypeFlags != DeclarationFlags::none)
    {
        std::expected<TypeSymbol*, int> rv = GetFundamentalType(fundamentalTypeFlags, node->GetSourcePos(), context);
        if (!rv) return rv;
        baseType = *rv;
    }
    else
    {
        while (type && type->IsAliasTypeSymbol())
        {
            AliasTypeSymbol* aliasType = static_cast<AliasTypeSymbol*>(type);
            type = aliasType->ReferredType();
        }
        baseType = type;
    }
    if (baseType)
    {
        Derivations derivations = Derivations::none;
        if ((flags & DeclarationFlags::constFlag) != DeclarationFlags::none)
        {
            derivations = derivations | Derivations::constDerivation;
        }
        if ((flags & DeclarationFlags::volatileFlag) != DeclarationFlags::none)
        {
            derivations = derivations | Derivations::volatileDerivation;
        }
        if (derivations != Derivations::none)
        {
            std::expected<TypeSymbol*, int> c = context->GetSymbolTable()->MakeCompoundType(baseType, derivations);
            if (!c) return c;
            baseType = *c;
        }
    }
    return std::expected<TypeSymbol*, int>(baseType);
}

void DeclarationProcessor::Visit(otava::ast::SimpleDeclarationNode& node)
{
    if (!Valid()) return;
    node.DeclarationSpecifiers()->Accept(*this);
    if (!Valid()) return;
    if (node.InitDeclaratorList())
    {
        std::expected<TypeSymbol*, int> rv = ResolveBaseType(&node);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        TypeSymbol* baseType = *rv;
        std::expected<std::unique_ptr<DeclarationList>, int> irv = ProcessInitDeclaratorList(baseType, &node, node.InitDeclaratorList(), flags, context);
        if (!irv)
        {
            SetError(irv.error());
            return;
        }
        declarationList = std::move(*irv);
    }
}

void DeclarationProcessor::Visit(otava::ast::MemberDeclarationNode& node)
{
    if (!Valid()) return;
    if (node.DeclSpecifiers())
    {
        node.DeclSpecifiers()->Accept(*this);
        if (!Valid()) return;
    }
    if (node.MemberDeclarators())
    {
        std::expected<TypeSymbol*, int> rv = ResolveBaseType(&node);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        TypeSymbol* baseType = *rv;
        std::expected<std::unique_ptr<DeclarationList>, int> mrv = ProcessMemberDeclaratorList(baseType, &node, node.MemberDeclarators(), flags, context);
        if (!mrv)
        {
            SetError(mrv.error());
            return;
        }
        declarationList = std::move(*mrv);
    }
}

void DeclarationProcessor::Visit(otava::ast::NoDeclSpecFunctionDeclarationNode& node)
{
    if (!Valid()) return;
    std::expected<Declaration, int> rv = ProcessDeclarator(nullptr, &node, &node, flags, FunctionQualifiers::none, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    Declaration declaration = std::move(*rv);
    declarationList->declarations.push_back(std::move(declaration));
}

void DeclarationProcessor::Visit(otava::ast::FunctionDefinitionNode& node)
{
    if (!Valid()) return;
    if (node.DeclSpecifiers())
    {
        node.DeclSpecifiers()->Accept(*this);
        if (!Valid()) return;
    }
    std::expected<TypeSymbol*, int> rv = ResolveBaseType(&node);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    TypeSymbol* baseType = *rv;
    if (!baseType)
    {
        return;
    }
    while (baseType->IsAliasTypeSymbol())
    {
        AliasTypeSymbol* aliasType = static_cast<AliasTypeSymbol*>(baseType);
        baseType = aliasType->ReferredType();
    }
    FunctionQualifiers qualifiers = GetQualifiers(node.Specifiers());
    std::expected<Declaration, int> drv = ProcessDeclarator(baseType, node.Declarator(), &node, flags, qualifiers, context);
    if (!drv)
    {
        SetError(drv.error());
        return;
    }
    Declaration declaration = std::move(*drv);
    if (node.FunctionBody() && node.FunctionBody()->Kind() == otava::ast::NodeKind::defaultedOrDeletedFunctionNode)
    {
        if (declaration.declarator->IsFunctionDeclarator())
        {
            FunctionDeclarator* functionDeclarator = static_cast<FunctionDeclarator*>(declaration.declarator.get());
            otava::ast::DefaultedOrDeletedFunctionNode* ddNode = static_cast<otava::ast::DefaultedOrDeletedFunctionNode*>(node.FunctionBody());
            switch (ddNode->DefaultOrDelete()->Kind())
            {
                case otava::ast::NodeKind::defaultNode:
                {
                    functionDeclarator->AddQualifier(FunctionQualifiers::isDefault);
                    break;
                }
                case otava::ast::NodeKind::deleteNode:
                {
                    functionDeclarator->AddQualifier(FunctionQualifiers::isDeleted);
                    break;
                }
            }
        }
    }
    declarationList->declarations.push_back(std::move(declaration));
}

void DeclarationProcessor::Visit(otava::ast::ParameterNode& node)
{
    if (!Valid()) return;
    node.DeclSpecifiers()->Accept(*this);
    if (!Valid()) return;
    std::expected<TypeSymbol*, int> rv = ResolveBaseType(&node);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    TypeSymbol* baseType = *rv;
    std::expected<Declaration, int> drv = ProcessDeclarator(baseType, node.Declarator(), &node, flags, FunctionQualifiers::none, context);
    if (!drv)
    {
        SetError(drv.error());
        return;
    }
    Declaration declaration = std::move(*drv);
    if (node.Initializer())
    {
        std::expected<Value*, int> rv = Evaluate(node.Initializer(), context);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        declaration.value = *rv;
        declaration.initializer = node.Initializer();
    }
    declarationList->declarations.push_back(std::move(declaration));
}

void DeclarationProcessor::Visit(otava::ast::ExceptionDeclarationNode& node)
{
    if (!Valid()) return;
    if (node.Ellipsis())
    {
        Declaration emptyDeclaration;
        declarationList->declarations.push_back(std::move(emptyDeclaration));
    }
    else
    {
        node.TypeSpecifiers()->Accept(*this);
        if (!Valid()) return;
        std::expected<TypeSymbol*, int> rv = ResolveBaseType(&node);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        TypeSymbol* baseType = *rv;
        std::expected<Declaration, int> drv = ProcessDeclarator(baseType, node.Declarator(), &node, flags, FunctionQualifiers::none, context);
        if (!drv)
        {
            SetError(drv.error());
            return;
        }
        Declaration declaration = std::move(*drv);
        declarationList->declarations.push_back(std::move(declaration));
    }
}

void DeclarationProcessor::Visit(otava::ast::ClassSpecifierNode& node)
{
}

void DeclarationProcessor::Visit(otava::ast::EnumSpecifierNode& node)
{
}

void DeclarationProcessor::Visit(otava::ast::ElaboratedTypeSpecifierNode& node)
{
    if (!Valid()) return;
    std::expected<TypeSymbol*, int> rv = ResolveType(node.Id(), DeclarationFlags::none, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    type = *rv;
}

void DeclarationProcessor::Visit(otava::ast::CharNode& node)
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

void DeclarationProcessor::Visit(otava::ast::Char8Node& node)
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

void DeclarationProcessor::Visit(otava::ast::Char16Node& node)
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

void DeclarationProcessor::Visit(otava::ast::Char32Node& node)
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

void DeclarationProcessor::Visit(otava::ast::WCharNode& node)
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

void DeclarationProcessor::Visit(otava::ast::BoolNode& node)
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

void DeclarationProcessor::Visit(otava::ast::ShortNode& node)
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

void DeclarationProcessor::Visit(otava::ast::IntNode& node)
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

void DeclarationProcessor::Visit(otava::ast::LongNode& node)
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

void DeclarationProcessor::Visit(otava::ast::SignedNode& node)
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

void DeclarationProcessor::Visit(otava::ast::UnsignedNode& node)
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

void DeclarationProcessor::Visit(otava::ast::FloatNode& node)
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

void DeclarationProcessor::Visit(otava::ast::DoubleNode& node)
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

void DeclarationProcessor::Visit(otava::ast::VoidNode& node)
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

void DeclarationProcessor::Visit(otava::ast::ConstNode& node)
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

void DeclarationProcessor::Visit(otava::ast::VolatileNode& node)
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

void DeclarationProcessor::Visit(otava::ast::PlaceholderTypeSpecifierNode& node)
{
    if (!Valid()) return;
    auto rv = CheckDuplicateSpecifier(flags, DeclarationFlags::autoFlag, "auto", node.GetSourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    flags = flags | DeclarationFlags::autoFlag;
}

void DeclarationProcessor::Visit(otava::ast::FriendNode& node)
{
    if (!Valid()) return;
    auto rv = CheckDuplicateSpecifier(flags, DeclarationFlags::friendFlag, "friend", node.GetSourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    flags = flags | DeclarationFlags::friendFlag;
}

void DeclarationProcessor::Visit(otava::ast::TypedefNode& node)
{
    if (!Valid()) return;
    auto rv = CheckDuplicateSpecifier(flags, DeclarationFlags::typedefFlag, "typedef", node.GetSourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    flags = flags | DeclarationFlags::typedefFlag;
}

void DeclarationProcessor::Visit(otava::ast::ConstExprNode& node)
{
    if (!Valid()) return;
    auto rv = CheckDuplicateSpecifier(flags, DeclarationFlags::constExprFlag, "constexpr", node.GetSourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    flags = flags | DeclarationFlags::constExprFlag;
}

void DeclarationProcessor::Visit(otava::ast::ConstEvalNode& node)
{
    if (!Valid()) return;
    auto rv = CheckDuplicateSpecifier(flags, DeclarationFlags::constEvalFlag, "consteval", node.GetSourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    flags = flags | DeclarationFlags::constEvalFlag;
}

void DeclarationProcessor::Visit(otava::ast::ConstInitNode& node)
{
    if (!Valid()) return;
    auto rv = CheckDuplicateSpecifier(flags, DeclarationFlags::constInitFlag, "constinit", node.GetSourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    flags = flags | DeclarationFlags::constInitFlag;
}

void DeclarationProcessor::Visit(otava::ast::InlineNode& node)
{
    if (!Valid()) return;
    auto rv = CheckDuplicateSpecifier(flags, DeclarationFlags::inlineFlag, "inline", node.GetSourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    flags = flags | DeclarationFlags::inlineFlag;
}

void DeclarationProcessor::Visit(otava::ast::StaticNode& node)
{
    if (!Valid()) return;
    auto rv = CheckDuplicateSpecifier(flags, DeclarationFlags::staticFlag, "static", node.GetSourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    flags = flags | DeclarationFlags::staticFlag;
}

void DeclarationProcessor::Visit(otava::ast::ThreadLocalNode& node)
{
    if (!Valid()) return;
    auto rv = CheckDuplicateSpecifier(flags, DeclarationFlags::threadLocalFlag, "thread_local", node.GetSourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    flags = flags | DeclarationFlags::threadLocalFlag;
}

void DeclarationProcessor::Visit(otava::ast::ExternNode& node)
{
    if (!Valid()) return;
    auto rv = CheckDuplicateSpecifier(flags, DeclarationFlags::externFlag, "extern", node.GetSourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    flags = flags | DeclarationFlags::externFlag;
}

void DeclarationProcessor::Visit(otava::ast::VirtualNode& node)
{
    if (!Valid()) return;
    auto rv = CheckDuplicateSpecifier(flags, DeclarationFlags::externFlag, "virtual", node.GetSourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    flags = flags | DeclarationFlags::virtualFlag;
}

void DeclarationProcessor::Visit(otava::ast::ExplicitNode& node)
{
    if (!Valid()) return;
    auto rv = CheckDuplicateSpecifier(flags, DeclarationFlags::explicitFlag, "explicit", node.GetSourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    flags = flags | DeclarationFlags::explicitFlag;
}

void DeclarationProcessor::Visit(otava::ast::QualifiedIdNode& node)
{
    if (!Valid()) return;
    std::expected<TypeSymbol*, int> rv = ResolveType(&node, flags, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    type = *rv;
}

void DeclarationProcessor::Visit(otava::ast::IdentifierNode& node)
{
    if (!Valid()) return;
    std::expected<TypeSymbol*, int> rv = ResolveType(&node, flags, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    type = *rv;
}

void DeclarationProcessor::Visit(otava::ast::TemplateIdNode& node)
{
    if (!Valid()) return;
    std::expected<TypeSymbol*, int> rv = ResolveType(&node, flags, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    type = *rv;
}

void DeclarationProcessor::Visit(otava::ast::TypenameSpecifierNode& node)
{
    if (!Valid()) return;
    std::expected<TypeSymbol*, int> rv = ResolveType(&node, flags, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    type = *rv;
}

std::expected<VariableSymbol*, int> ProcessSimpleDeclarator(SimpleDeclarator* simpleDeclarator, TypeSymbol* type, Value* value, DeclarationFlags flags, Context* context)
{
    std::expected<VariableSymbol*, int> v = context->GetSymbolTable()->AddVariable(
        simpleDeclarator->Name(), simpleDeclarator->Node(), type, nullptr, value, flags, context);
    if (!v) return std::unexpected<int>(v.error());
    VariableSymbol* variable = *v;
    return std::expected<VariableSymbol*, int>(variable);
}

std::expected<VariableSymbol*, int> ProcessArrayDeclarator(ArrayDeclarator* arrayDeclarator, TypeSymbol* elementType, DeclarationFlags flags, Context* context)
{
    if (arrayDeclarator->Size() == -1)
    {
        otava::ast::Node* node = arrayDeclarator->Node();
        arrayDeclarator->SetSize(GetSizeFromInitializer(node));
    }
    ArrayTypeSymbol* arrayTypeSymbol = context->GetSymbolTable()->MakeArrayType(elementType, arrayDeclarator->Size());
    std::expected<bool, int> rv = arrayTypeSymbol->Bind(arrayDeclarator->Node()->GetSourcePos(), context);
    if (!rv) return std::unexpected<int>(rv.error());
    std::expected<VariableSymbol*, int> v = context->GetSymbolTable()->AddVariable(
        arrayDeclarator->Name(), arrayDeclarator->Node(), arrayTypeSymbol, nullptr, nullptr, flags, context);
    if (!v) return v;
    VariableSymbol* variable = *v;
    return std::expected<VariableSymbol*, int>(variable);
}

std::expected<bool, int> ProcessFunctionDeclarator(FunctionDeclarator* functionDeclarator, TypeSymbol* type, DeclarationFlags flags, otava::ast::Node* functionNode, 
    Context* context)
{
    std::expected<FunctionSymbol*, int> f = context->GetSymbolTable()->AddFunction(
        functionDeclarator->Name(),
        functionDeclarator->TemplateArgs(),
        functionDeclarator->Node(),
        functionDeclarator->GetFunctionKind(),
        functionDeclarator->GetFunctionQualifiers(),
        flags,
        context);
    if (!f) return std::unexpected<int>(f.error());
    FunctionSymbol* functionSymbol = *f;
    context->SetSpecialization(functionSymbol, functionNode);
    std::expected<TypeSymbol*, int> m = MapType(functionSymbol, type, context);
    if (!m) return std::unexpected<int>(m.error());
    TypeSymbol* returnType = *m;
    std::expected<bool, int> rv = functionSymbol->SetReturnType(returnType, context);
    if (!rv) return rv;
    for (const auto& parameterDeclaration : functionDeclarator->ParameterDeclarations())
    {
        soul::ast::SourcePos sourcePos;
        std::u32string name;
        otava::ast::Node* node = nullptr;
        if (parameterDeclaration.declarator)
        {
            name = parameterDeclaration.declarator->Name();
            node = parameterDeclaration.declarator->Node();
            sourcePos = parameterDeclaration.declarator->Node()->GetSourcePos();
        }
        std::expected<TypeSymbol*, int> m = MapType(functionSymbol, parameterDeclaration.type, context);
        if (!m) return std::unexpected<int>(m.error());
        TypeSymbol* parameterType = *m;
        ParameterSymbol* parameter = context->GetSymbolTable()->CreateParameter(name, node, parameterType, context);
        if (parameterDeclaration.initializer)
        {
            parameter->SetDefaultValue(parameterDeclaration.initializer);
        }
        std::expected<bool, int> rv = functionSymbol->AddParameter(parameter, sourcePos, context);
        if (!rv) return rv;
    }
    ClassTypeSymbol* classType = functionSymbol->ParentClassType();
    if (classType)
    {
        std::int32_t functionIndex = 0;
        std::expected<SpecialFunctionKind, int> s = functionSymbol->GetSpecialFunctionKind(context);
        if (!s) return std::unexpected<int>(s.error());
        SpecialFunctionKind specialFunctionKind = *s;
        if (specialFunctionKind != SpecialFunctionKind::none)
        {
            functionIndex = GetSpecialFunctionIndex(specialFunctionKind);
            if (specialFunctionKind == SpecialFunctionKind::dtor)
            {
                classType->SetHasUserDefinedDestructor();
            }
        }
        else
        {
            functionIndex = classType->NextFunctionIndex();
        }
        functionSymbol->SetIndex(functionIndex);
        classType->MapFunction(functionSymbol);
        context->GetSymbolTable()->MapFunction(functionSymbol);
    }
    if (functionSymbol->IsExplicitSpecializationDeclaration())
    {
        std::map<TemplateParameterSymbol*, TypeSymbol*, TemplateParamLess> templateParameterMap;
        std::expected<FunctionSymbol*, int> rv = InstantiateFunctionTemplate(functionSymbol, templateParameterMap, functionDeclarator->Node()->GetSourcePos(), context);
        if (!rv) return std::unexpected<int>(rv.error());
    }
    rv = AddConvertingConstructorToConversionTable(functionSymbol, functionDeclarator->Node()->GetSourcePos(), context);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ProcessSimpleDeclaration(otava::ast::Node* node, otava::ast::Node* functionNode, Context* context)
{
    if (context->GetFlag(ContextFlags::linkageDeclaration)) return std::expected<bool, int>(false);
    DeclarationProcessor processor(context);
    node->Accept(processor);
    if (!processor) return std::unexpected<int>(processor.Error());
    std::unique_ptr<DeclarationList> declarationList = processor.GetDeclarations();
    for (auto& declaration : declarationList->declarations)
    {
        Declarator* declarator = declaration.declarator.get();
        switch (declarator->Kind())
        {
            case DeclaratorKind::simpleDeclarator:
            {
                SimpleDeclarator* simpleDeclarator = static_cast<SimpleDeclarator*>(declarator);
                if (!simpleDeclarator->Name().empty())
                {
                    std::expected<VariableSymbol*, int> v = ProcessSimpleDeclarator(simpleDeclarator, declaration.type, declaration.value, declaration.flags, context);
                    if (!v) return std::unexpected<int>(v.error());
                    VariableSymbol* variable = *v;
                    if (variable->IsGlobalVariable())
                    {
                        std::unique_ptr<BoundExpressionNode> variableInitializer(nullptr);
                        if (declaration.initializer)
                        {
                            std::expected<BoundExpressionNode*, int> rv = BindExpression(declaration.initializer, context);
                            if (!rv)
                            {
                                return std::unexpected<int>(rv.error());
                            }
                            variableInitializer.reset(*rv);
                        }
                        if (!variable->IsExtern())
                        {
                            std::expected<bool, int> rv = context->GetBoundCompileUnit()->AddBoundNode(std::unique_ptr<BoundNode>(
                                new BoundGlobalVariableDefinitionNode(variable, node->GetSourcePos())), context);
                            if (!rv) return rv;
                            rv = GenerateDynamicInitialization(variable, variableInitializer.get(), node->GetSourcePos(), context);
                            if (!rv) return rv;
                        }
                    }
                    declaration.variable = variable;
                }
                break;
            }
            case DeclaratorKind::functionDeclarator:
            {
                FunctionDeclarator* functionDeclarator = static_cast<FunctionDeclarator*>(declarator);
                std::expected<bool, int> rv = ProcessFunctionDeclarator(functionDeclarator, declaration.type, declaration.flags, functionNode, context);
                if (!rv) return rv;
                break;
            }
            case DeclaratorKind::arrayDeclarator:
            {
                ArrayDeclarator* arrayDeclarator = static_cast<ArrayDeclarator*>(declarator);
                ArrayTypeSymbol* arrayType = static_cast<ArrayTypeSymbol*>(declaration.type);
                std::expected<VariableSymbol*, int> rv = ProcessArrayDeclarator(arrayDeclarator, arrayType->ElementType(), declaration.flags, context);
                if (!rv) return std::unexpected<int>(rv.error());
                VariableSymbol* variable = *rv;
                if (declaration.value)
                {
                    variable->SetValue(declaration.value);
                    variable->SetDeclaredType(declaration.value->GetType());
                }
                if (variable->IsGlobalVariable())
                {
                    std::expected<bool, int> rv = context->GetBoundCompileUnit()->AddBoundNode(
                        std::unique_ptr<BoundNode>(new BoundGlobalVariableDefinitionNode(variable, node->GetSourcePos())), context);
                    if (!rv) return rv;
                }
                declaration.variable = variable;
                break;
            }
        }
    }
    if (context->GetFlag(ContextFlags::saveDeclarations))
    {
        context->SetDeclarationList(node, declarationList.release());
    }
    return std::expected<bool, int>(true);
}

std::expected<Declaration, int> ProcessParameterDeclaration(otava::ast::Node* node, Context* context)
{
    DeclarationProcessor processor(context);
    node->Accept(processor);
    if (!processor) return std::unexpected<int>(processor.Error());
    std::unique_ptr<DeclarationList> declarationList = processor.GetDeclarations();
    if (declarationList->declarations.size() == 1)
    {
        return std::expected<Declaration, int>(std::move(declarationList->declarations.front()));
    }
    else
    {
        return Error("otava.symbols.declaration: single declaration expected", node->GetSourcePos(), context);
    }
}

std::expected<Declaration, int> ProcessExceptionDeclaration(otava::ast::Node* node, Context* context)
{
    DeclarationProcessor processor(context);
    node->Accept(processor);
    if (!processor) return std::unexpected<int>(processor.Error());
    std::unique_ptr<DeclarationList> declarationList = processor.GetDeclarations();
    if (declarationList->declarations.size() == 1)
    {
        return std::expected<Declaration, int>(std::move(declarationList->declarations.front()));
    }
    else
    {
        return Error("otava.symbols.declaration: single declaration expected", node->GetSourcePos(), context);
    }
}

std::expected<bool, int> ProcessMemberDeclaration(otava::ast::Node* node, otava::ast::Node* functionNode, Context* context)
{
    return ProcessSimpleDeclaration(node, functionNode, context);
}

std::expected<Declaration, int> ProcessFunctionDeclaration(otava::ast::Node* node, Context* context)
{
    DeclarationProcessor processor(context);
    node->Accept(processor);
    if (!processor) return std::unexpected<int>(processor.Error());
    std::unique_ptr<DeclarationList> declarationList = processor.GetDeclarations();
    if (declarationList->declarations.size() == 1)
    {
        return std::expected<Declaration, int>(std::move(declarationList->declarations.front()));
    }
    else
    {
        return Error("otava.symbols.declaration: single declaration expected", node->GetSourcePos(), context);
    }
}

bool IsTokenSwitchDeclarator(otava::ast::Node* declarator)
{
    if (declarator->IsFunctionDeclaratorNode())
    {
        otava::ast::FunctionDeclaratorNode* fnd = static_cast<otava::ast::FunctionDeclaratorNode*>(declarator);
        if (fnd->Child()->Str() == U"IsTokenSwitch")
        {
            return true;
        }
    }
    return false;
}

std::expected<int, int> BeginFunctionDefinition(otava::ast::Node* declSpecifierSequence, otava::ast::Node* declarator, otava::ast::Node* functionNode, 
    otava::ast::Node* specifierNode, bool& get, Context* context)
{
    get = false;
    int scopes = 0;
    if (!context->GetFlag(ContextFlags::instantiateFunctionTemplate) &&
        !context->GetFlag(ContextFlags::instantiateMemFnOfClassTemplate) &&
        !context->GetFlag(ContextFlags::instantiateInlineFunction))
    {
        std::expected<bool, int> rv = context->GetSymbolTable()->CurrentScope()->PopParentScope();
        if (!rv) return std::unexpected<int>(rv.error());
    }
    DeclarationProcessor processor(context);
    processor.BeginProcessFunctionDefinition(declSpecifierSequence, declarator, specifierNode);
    if (!processor) return std::unexpected<int>(processor.Error());
    std::unique_ptr<DeclarationList> declarationList = processor.GetDeclarations();
    if (declarationList->declarations.size() == 1)
    {
        Declaration declaration = std::move(declarationList->declarations.front());
        if (declaration.declarator->Kind() == DeclaratorKind::functionDeclarator)
        {
            FunctionDeclarator* functionDeclarator = static_cast<FunctionDeclarator*>(declaration.declarator.get());
            FunctionQualifiers qualifiers = functionDeclarator->GetFunctionQualifiers();
            FunctionKind kind = functionDeclarator->GetFunctionKind();
            std::vector<TypeSymbol*> parameterTypes;
            for (const auto& parameterDeclaration : functionDeclarator->ParameterDeclarations())
            {
                parameterTypes.push_back(parameterDeclaration.type);
            }
            std::expected<FunctionDefinitionSymbol*, int> f = context->GetSymbolTable()->AddOrGetFunctionDefinition(functionDeclarator->GetScope(), 
                functionDeclarator->Name(), functionDeclarator->TemplateArgs(), parameterTypes, qualifiers, kind, declaration.flags, declarator, 
                functionNode, get, context);
            if (!f) return std::unexpected<int>(f.error());
            FunctionDefinitionSymbol* definition = *f;
            TypeSymbol* fnDeclarationReturnType = nullptr;
            FunctionSymbol* fnDeclaration = definition->Declaration();
            if (fnDeclaration)
            {
                if (fnDeclaration->IsInline())
                {
                    definition->SetInline();
                }
                fnDeclarationReturnType = fnDeclaration->ReturnType();
            }
            if (context->GetFlag(ContextFlags::instantiateFunctionTemplate) ||
                context->GetFlag(ContextFlags::instantiateMemFnOfClassTemplate) ||
                context->GetFlag(ContextFlags::instantiateInlineFunction) ||
                context->GetFlag(ContextFlags::generateMainWrapper))
            {
                context->SetSpecialization(definition, functionNode);
            }
            if (get)
            {
                return std::expected<int, int>(0);
            }
            int parameterIndex = 0;
            for (const auto& parameterDeclaration : functionDeclarator->ParameterDeclarations())
            {
                soul::ast::SourcePos sourcePos;
                std::u32string name;
                otava::ast::Node* node = nullptr;
                if (parameterDeclaration.declarator)
                {
                    name = parameterDeclaration.declarator->Name();
                    node = parameterDeclaration.declarator->Node();
                    sourcePos = parameterDeclaration.declarator->Node()->GetSourcePos();
                }
                std::expected<TypeSymbol*, int> m = MapType(definition, parameterDeclaration.type, context);
                if (!m) return std::unexpected<int>(m.error());
                TypeSymbol* parameterType = *m;
                ParameterSymbol* parameter = context->GetSymbolTable()->CreateParameter(name, node, parameterType, context);
                if (parameterDeclaration.initializer)
                {
                    parameter->SetDefaultValue(parameterDeclaration.initializer);
                }
                FunctionSymbol* declaration = definition->Declaration();
                if (declaration)
                {
                    if (parameterIndex >= 0 && parameterIndex < declaration->Parameters().size())
                    {
                        ParameterSymbol* declarationParam = declaration->Parameters()[parameterIndex];
                        if (declarationParam->DefaultValue() && !parameter->DefaultValue())
                        {
                            parameter->SetDefaultValue(declarationParam->DefaultValue());
                        }
                    }
                }
                std::expected<bool, int> rv = definition->AddParameter(parameter, sourcePos, context);
                if (!rv) return std::unexpected<int>(rv.error());
                ++parameterIndex;
            }
            definition->AddDefinitionToGroup(context);
            std::expected<TypeSymbol*, int> m = MapType(definition, declaration.type, context);
            if (!m) return std::unexpected<int>(m.error());
            TypeSymbol* returnType = *m;
            std::expected<bool, int> rv = definition->SetReturnType(returnType, context);
            if (!rv) return std::unexpected<int>(rv.error());
            if (fnDeclarationReturnType && returnType && !TypesEqual(fnDeclarationReturnType, returnType, context))
            {
                std::set<const Symbol*> visited;
                bool isTemplateParameterInstantiation = fnDeclaration->IsTemplateParameterInstantiation(context, visited) ||
                    fnDeclarationReturnType->IsTemplateParameterInstantiation(context, visited) ||
                    definition->IsTemplateParameterInstantiation(context, visited) ||
                    returnType->IsTemplateParameterInstantiation(context, visited);
                if (!isTemplateParameterInstantiation)
                {
                    std::expected<std::u32string, int> fname = definition->FullName();
                    if (!fname) return std::unexpected<int>(fname.error());
                    std::expected<std::string, int> sfname = util::ToUtf8(*fname);
                    if (!sfname) return std::unexpected<int>(sfname.error());
                    return Error("the return type of function '" + *sfname + "' definition differs from the return type of function declaration",
                        definition->GetSourcePos(), fnDeclaration->GetSourcePos(), context);
                }
            }
            rv = context->GetSymbolTable()->BeginScopeGeneric(definition->GetScope(), context);
            if (!rv) return std::unexpected<int>(rv.error());
            if (!context->GetFlag(ContextFlags::instantiateFunctionTemplate) &&
                !context->GetFlag(ContextFlags::instantiateMemFnOfClassTemplate) &&
                !context->GetFlag(ContextFlags::instantiateInlineFunction))
            {
                rv = definition->GetScope()->AddParentScope(functionDeclarator->GetScope());
                if (!rv) return std::unexpected<int>(rv.error());
            }
            ++scopes;
            BoundFunctionNode* boundFunctionNode = new BoundFunctionNode(definition, declarator->GetSourcePos());
            context->PushBoundFunction(boundFunctionNode);
        }
    }
    else
    {
        return Error("otava.symbols.declaration: single declaration expected", declarator->GetSourcePos(), context);
    }
    return std::expected<int, int>(scopes);
}

std::expected<bool, int> EndFunctionDefinition(otava::ast::Node* node, int scopes, Context* context)
{
    if (node->IsFunctionDefinitionNode())
    {
        otava::ast::FunctionDefinitionNode* functionDefinitionNode = static_cast<otava::ast::FunctionDefinitionNode*>(node);
        FunctionDefinitionSymbol* functionDefinitionSymbol = nullptr;
        Symbol* symbol = context->GetSymbolTable()->CurrentScope()->SymbolScope()->GetSymbol();
        if (symbol && symbol->IsFunctionDefinitionSymbol())
        {
            functionDefinitionSymbol = static_cast<FunctionDefinitionSymbol*>(symbol);
            if (HasNoReturnAttribute(functionDefinitionNode->Attributes()))
            {
                functionDefinitionSymbol->SetFunctionQualifiers(functionDefinitionSymbol->Qualifiers() | FunctionQualifiers::noreturn);
            }
            context->GetSymbolTable()->MapNode(functionDefinitionNode, functionDefinitionSymbol);
            ClassTypeSymbol* classType = functionDefinitionSymbol->ParentClassType();
            if (classType)
            {
                if (classType->IsClassTemplateSpecializationSymbol())
                {
                    std::set<const Symbol*> visited;
                    if (classType->IsTemplateParameterInstantiation(context, visited))
                    {
                        ClassTemplateSpecializationSymbol* specialiazation = static_cast<ClassTemplateSpecializationSymbol*>(classType);
                        classType = specialiazation->ClassTemplate();
                    }
                }
                std::int32_t functionIndex = 0;
                std::expected<SpecialFunctionKind, int> s = functionDefinitionSymbol->GetSpecialFunctionKind(context);
                if (!s) return std::unexpected<int>(s.error());
                SpecialFunctionKind specialFunctionKind = *s;
                if (specialFunctionKind != SpecialFunctionKind::none)
                {
                    functionIndex = GetSpecialFunctionIndex(specialFunctionKind);
                }
                else
                {
                    functionIndex = classType->NextFunctionIndex();
                }
                functionDefinitionSymbol->SetIndex(functionIndex);
                functionDefinitionNode->SetIndex(functionIndex);
                if (!classType->GetFunctionByIndex(functionIndex))
                {
                    classType->MapFunction(functionDefinitionSymbol);
                }
                if (context->MemFunDefSymbolIndex() != -1 && functionDefinitionSymbol->DefIndex() == -1)
                {
                    functionDefinitionSymbol->SetDefIndex(context->MemFunDefSymbolIndex());
                    context->SetMemFunDefSymbolIndex(-1);
                }
                classType->SetMemFnDefSymbol(functionDefinitionSymbol);
                context->GetSymbolTable()->MapFunctionDefinition(functionDefinitionSymbol);
            }
        }
        for (int i = 0; i < scopes; ++i)
        {
            std::expected<bool, int> rv = context->GetSymbolTable()->EndScopeGeneric(context);
            if (!rv) return rv;
        }
        if (!context->GetFlag(ContextFlags::dontBind) && functionDefinitionSymbol)
        {
            std::expected<FunctionDefinitionSymbol*, int> rv = BindFunction(functionDefinitionNode, functionDefinitionSymbol, context);
            if (!rv) return std::unexpected<int>(rv.error());
            functionDefinitionSymbol = *rv;
        }
        if (functionDefinitionSymbol && functionDefinitionSymbol->IsTemplate())
        {
            std::expected<bool, int> rv = InstantiateEnqueuedRequests(functionDefinitionSymbol, node->GetSourcePos(), context);
            if (!rv) return rv;
        }
        if (functionDefinitionSymbol && functionDefinitionSymbol->IsExplicitSpecializationDefinitionSymbol())
        {
            std::map<TemplateParameterSymbol*, TypeSymbol*, TemplateParamLess> templateParameterMap;
            std::expected<FunctionSymbol*, int> rv = InstantiateFunctionTemplate(functionDefinitionSymbol, templateParameterMap, node->GetSourcePos(), context);
            if (!rv) return std::unexpected<int>(rv.error());
        }
    }
    if (context->GetBoundFunction())
    {
        if (context->GetBoundFunction()->GetFunctionDefinitionSymbol()->IsBound())
        {
            std::expected<bool, int> rv = context->GetBoundCompileUnit()->AddBoundNode(std::unique_ptr<BoundNode>(context->ReleaseBoundFunction()), context);
            if (!rv) return rv;
        }
        context->PopBoundFunction();
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ProcessMemberFunctionDefinition(otava::ast::Node* node, Context* context)
{
    return ProcessSimpleDeclaration(node, nullptr, context);
}

std::expected<bool, int> Write(Writer& writer, DeclarationFlags flags)
{
    return writer.GetBinaryStreamWriter().Write(static_cast<std::int32_t>(flags));
}

std::expected<bool, int> Read(Reader& reader, DeclarationFlags& flags)
{
    std::expected<std::int32_t, int> rv = reader.GetBinaryStreamReader().ReadInt();
    if (!rv) return std::unexpected<int>(rv.error());
    std::int32_t f = *rv;
    flags = static_cast<DeclarationFlags>(f);
    return std::expected<bool, int>(true);
}

std::unexpected<int> ReturnDeclarationParsingError(const soul::ast::SourcePos& sourcePos, Context* context)
{
    return Error("declaration parsing error", sourcePos, context);
}

class LinkageProcessor : public otava::ast::DefaultVisitor
{
public:
    LinkageProcessor(Context* context_);
    void Visit(otava::ast::LinkageSpecificationNode& node) override;
    void Visit(otava::ast::StringLiteralNode& node) override;
    void Visit(otava::ast::SimpleDeclarationNode& node) override;
private:
    Context* context;
    Linkage linkage;
};

LinkageProcessor::LinkageProcessor(Context* context_) : context(context_), linkage(Linkage::cpp_linkage)
{
}

void LinkageProcessor::Visit(otava::ast::LinkageSpecificationNode& node)
{
    if (!Valid()) return;
    node.Linkage()->Accept(*this);
    if (!Valid()) return;
    context->GetSymbolTable()->PushLinkage(linkage);
    node.Declarations()->Accept(*this);
    if (!Valid()) return;
    context->GetSymbolTable()->PopLinkage();
}

void LinkageProcessor::Visit(otava::ast::StringLiteralNode& node)
{
    if (!Valid()) return;
    if (node.Value() == U"C")
    {
        linkage = Linkage::c_linkage;
    }
    else if (node.Value() == U"C++")
    {
        linkage = Linkage::cpp_linkage;
    }
    else
    {
        std::unexpected<int> result = Error("unknown linkage", node.GetSourcePos(), context);
        SetError(result.error());
        return;
    }
}

void LinkageProcessor::Visit(otava::ast::SimpleDeclarationNode& node)
{
    if (!Valid()) return;
    auto rv = ProcessSimpleDeclaration(&node, nullptr, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

std::expected<bool, int> ProcessLinkageSpecification(otava::ast::Node* node, Context* context)
{
    LinkageProcessor linkageProcessor(context);
    node->Accept(linkageProcessor);
    if (!linkageProcessor) return std::unexpected<int>(linkageProcessor.Error());
    return std::expected<bool, int>(true);
}

std::expected<TypeSymbol*, int> ProcessExplicitInstantiationDeclaration(otava::ast::Node* node, Context* context)
{
    DeclarationProcessor processor(context);
    node->Accept(processor);
    if (!processor) return std::unexpected<int>(processor.Error());
    return std::expected<TypeSymbol*, int>(processor.GetType());
}

std::expected<TypeSymbol*, int> MapType(FunctionSymbol* functionSymbol, TypeSymbol* type, Context* context)
{
    if (type)
    {
        ClassTypeSymbol* parentClassType = functionSymbol->ParentClassType();
        if (parentClassType && parentClassType->IsClassTemplateSpecializationSymbol())
        {
            ClassTemplateSpecializationSymbol* specialization = static_cast<ClassTemplateSpecializationSymbol*>(parentClassType);
            if (type->GetBaseType()->IsClassTypeSymbol())
            {
                if (TypesEqual(type->GetBaseType(), specialization->ClassTemplate(), context))
                {
                    std::expected<TypeSymbol*, int> c = context->GetSymbolTable()->MakeCompoundType(specialization, type->GetDerivations());
                    if (!c) return c;
                    type = *c;
                }
            }
        }
    }
    return std::expected<TypeSymbol*, int>(type);
}

std::expected<bool, int> GenerateDynamicInitialization(VariableSymbol* variable, BoundExpressionNode* initializer, const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (!variable->GetType()->IsClassTypeSymbol()) return std::expected<bool, int>(false);
    if (context->GetFlag(ContextFlags::noDynamicInit)) return std::expected<bool, int>(false);
    bool prevInternallyMapped = context->GetModule()->GetNodeIdFactory()->IsInternallyMapped();
    context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(true);
    BoundVariableNode* boundGlobalVariable = new BoundVariableNode(variable, sourcePos);
    std::vector<std::unique_ptr<BoundExpressionNode>> args;
    std::expected<TypeSymbol*, int> pt = variable->GetType()->AddPointer(context);
    if (!pt) return std::unexpected<int>(pt.error());
    args.push_back(std::unique_ptr<BoundExpressionNode>(new BoundAddressOfNode(boundGlobalVariable, sourcePos, *pt)));
    if (initializer)
    {
        if (initializer->IsBoundExpressionListNode())
        {
            BoundExpressionListNode* expressionList = static_cast<BoundExpressionListNode*>(initializer);
            int n = expressionList->Count();
            for (int i = 0; i < n; ++i)
            {
                args.push_back(std::unique_ptr<BoundExpressionNode>(expressionList->ReleaseExpr(i)));
            }
        }
        else
        {
            args.push_back(std::unique_ptr<BoundExpressionNode>(initializer->Clone()));
        }
    }
    std::vector<TypeSymbol*> templateArgs;
    std::expected<std::unique_ptr<BoundFunctionCallNode>, int> rv = ResolveOverload(context->GetSymbolTable()->CurrentScope(), U"@constructor", templateArgs, args, 
        sourcePos, context);
    if (!rv) return std::unexpected<int>(rv.error());
    std::unique_ptr<BoundFunctionCallNode> constructorCall = std::move(*rv);
    if (constructorCall)
    {
        auto arv = MakeAtExitForVariable(variable, sourcePos, context);
        if (!arv) return std::unexpected<int>(arv.error());
        std::unique_ptr<BoundFunctionCallNode> atExitCall = std::move(*arv);
        auto rv = context->GetBoundCompileUnit()->AddDynamicInitialization(constructorCall.release(), atExitCall.release(), sourcePos, context);
        if (!rv) return rv;
    }
    context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(prevInternallyMapped);
    return std::expected<bool, int>(true);
}

std::expected<std::unique_ptr<BoundFunctionCallNode>, int> MakeAtExitForVariable(VariableSymbol* variable, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::vector<std::unique_ptr<BoundExpressionNode>> dtorArgs;
    BoundVariableNode* boundGlobalVariable = new BoundVariableNode(variable, sourcePos);
    std::expected<TypeSymbol*, int> pt = variable->GetType()->AddPointer(context);
    if (!pt) return std::unexpected<int>(pt.error());
    dtorArgs.push_back(std::unique_ptr<BoundExpressionNode>(new BoundAddressOfNode(boundGlobalVariable, sourcePos, *pt)));
    std::vector<TypeSymbol*> templateArgs;
    auto rv = ResolveOverload(context->GetSymbolTable()->CurrentScope(), U"@destructor", templateArgs, dtorArgs, sourcePos, context);
    if (!rv) return std::unexpected<int>(rv.error());
    std::unique_ptr<BoundFunctionCallNode> destructorCall = std::move(*rv);
    std::unique_ptr<BoundFunctionCallNode> atExitCall;
    if (destructorCall.get() && !destructorCall->GetFunctionSymbol()->IsTrivialDestructor())
    {
        std::expected<TypeSymbol*, int> pt = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::voidType)->AddPointer(context);
        if (!pt) return std::unexpected<int>(pt.error());
        TypeSymbol* voidPtrType = *pt;
        std::vector<std::unique_ptr<BoundExpressionNode>> atExitArgs;
        atExitArgs.push_back(std::unique_ptr<BoundExpressionNode>(new BoundFunctionValueNode(destructorCall->GetFunctionSymbol(), sourcePos, voidPtrType)));
        BoundVariableNode* boundGlobalVariable = new BoundVariableNode(variable, sourcePos);
        pt = boundGlobalVariable->GetType()->AddPointer(context);
        if (!pt) return std::unexpected<int>(pt.error());
        atExitArgs.push_back(std::unique_ptr<BoundExpressionNode>(new BoundVariableAsVoidPtrNode(new BoundAddressOfNode(
            boundGlobalVariable, sourcePos, *pt), sourcePos, voidPtrType)));
        std::expected<Scope*, int> nrv = context->GetSymbolTable()->GetNamespaceScope(U"std", sourcePos, context);
        if (!nrv) return std::unexpected<int>(nrv.error());
        Scope* stdScope = *nrv;
        std::vector<TypeSymbol*> templateArgs;
        rv = ResolveOverload(stdScope, U"at_exit", templateArgs, atExitArgs, sourcePos, context);
        if (!rv) return std::unexpected<int>(rv.error());
        atExitCall = std::move(*rv);
    }
    return std::expected<std::unique_ptr<BoundFunctionCallNode>, int>(std::move(atExitCall));
}

std::expected<bool, int> AddConvertingConstructorToConversionTable(FunctionSymbol* functionSymbol, const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (!functionSymbol->IsExplicit() && functionSymbol->GetFunctionKind() == FunctionKind::constructor && functionSymbol->MemFunArity(context) == 2)
    {
        std::expected<TypeSymbol*, int> rv = functionSymbol->MemFunParameters(context)[0]->GetType()->RemovePointer(context);
        if (!functionSymbol->Valid()) return std::unexpected<int>(functionSymbol->GetError());
        if (!rv) return std::unexpected<int>(rv.error());
        TypeSymbol* type = *rv;
        rv = type->DirectType(context);
        if (!rv) return std::unexpected<int>(rv.error());
        TypeSymbol* dt = *rv;
        rv = dt->FinalType(sourcePos, context);
        if (!rv) return std::unexpected<int>(rv.error());
        TypeSymbol* conversionParamType = *rv;
        rv = functionSymbol->MemFunParameters(context)[1]->GetType()->PlainType(context);
        if (!rv) return std::unexpected<int>(rv.error());
        if (!functionSymbol->Valid()) return std::unexpected<int>(functionSymbol->GetError());
        TypeSymbol* plainType = *rv;
        rv = plainType->DirectType(context);
        if (!rv) return std::unexpected<int>(rv.error());
        TypeSymbol* directType = *rv;
        if (!rv) return std::unexpected<int>(rv.error());
        rv = directType->FinalType(sourcePos, context);
        if (!rv) return std::unexpected<int>(rv.error());
        TypeSymbol* conversionArgType = *rv;
        if (!TypesEqual(conversionParamType, conversionArgType, context))
        {
            std::expected<FunctionSymbol*, int> rv = context->GetSymbolTable()->GetConversionTable().GetConversion(conversionParamType, conversionArgType, context);
            if (!rv) return std::unexpected<int>(rv.error());
            FunctionSymbol* conversion = *rv;
            if (!conversion)
            {
                functionSymbol->SetConversion();
                functionSymbol->SetConversionParamType(conversionParamType);
                functionSymbol->SetConversionArgType(conversionArgType);
                functionSymbol->SetConversionDistance(10);
                std::expected<bool, int> arv = context->GetSymbolTable()->GetConversionTable().AddConversion(functionSymbol);
                if (!arv) return arv;
            }
        }
    }
    return std::expected<bool, int>(true);
}

} // namespace otava::symbols
