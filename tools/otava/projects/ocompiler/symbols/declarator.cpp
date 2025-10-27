// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.declarator;

import otava.ast.visitor;
import otava.symbols.array.type.symbol;
import otava.symbols.classes;
import otava.symbols.context;
import otava.symbols.declaration;
import otava.symbols.evaluator;
import otava.symbols.expression.binder;
import otava.symbols.function.kind;
import otava.symbols.function.symbol;
import otava.symbols.function.type.symbol;
import otava.symbols.scope;
import otava.symbols.scope.resolver;
import otava.symbols.symbol;
import otava.symbols.symbol.table;
import otava.symbols.type.resolver;
import otava.symbols.type.symbol;
import otava.symbols.value;
import otava.symbols.error;
import otava.symbols.modules;
import util.unicode;

namespace otava::symbols {

Declarator::Declarator(DeclaratorKind kind_, const std::u32string& name_, otava::ast::Node* node_) : kind(kind_), name(name_), node(node_)
{
}

Declarator::~Declarator()
{
}

SimpleDeclarator::SimpleDeclarator(const std::u32string& name_, otava::ast::Node* node_) : Declarator(DeclaratorKind::simpleDeclarator, name_, node_)
{
}

FunctionDeclarator::FunctionDeclarator(const std::u32string& name_, otava::ast::Node* node_, FunctionKind kind_, FunctionQualifiers qualifiers_, Scope* scope_) :
    Declarator(DeclaratorKind::functionDeclarator, name_, node_), scope(scope_), kind(kind_), qualifiers(qualifiers_)
{
}

void FunctionDeclarator::AddParameterDeclaration(Declaration&& parameterDeclaration)
{
    parameterDeclarations.push_back(std::move(parameterDeclaration));
}

void FunctionDeclarator::AddQualifier(FunctionQualifiers qualifier)
{
    qualifiers = qualifiers | qualifier;
}

void FunctionDeclarator::SetTemplateArgs(const std::vector<TypeSymbol*>& templateArgs_)
{
    templateArgs = templateArgs_;
}

ArrayDeclarator::ArrayDeclarator(const std::u32string& name_, otava::ast::Node* node_, std::int64_t size_) : 
    Declarator(DeclaratorKind::arrayDeclarator, name_, node_), size(size_)
{
}

Declaration::Declaration() : flags(DeclarationFlags::none), type(nullptr), declarator(nullptr), value(nullptr), initializer(nullptr), variable(nullptr)
{
}

Declaration::Declaration(DeclarationFlags flags_, TypeSymbol* type_, Declarator* declarator_) :
    flags(flags_), type(type_), declarator(declarator_), value(nullptr), initializer(nullptr), variable(nullptr)
{
}

class DeclaratorListProcessor : public otava::ast::DefaultVisitor
{
public:
    DeclaratorListProcessor(Context* context_, TypeSymbol* baseType_, DeclarationFlags flags_, otava::ast::Node* declarationNode_);
    std::unique_ptr<DeclarationList> GetDeclarations() { return std::move(declarationList); }
    void Visit(otava::ast::InitDeclaratorListNode& node) override;
    void Visit(otava::ast::MemberDeclaratorListNode& node) override;
private:
    Context* context;
    TypeSymbol* baseType;
    DeclarationFlags flags;
    std::unique_ptr<DeclarationList> declarationList;
    otava::ast::Node* declarationNode;
};

DeclaratorListProcessor::DeclaratorListProcessor(Context* context_, TypeSymbol* baseType_, DeclarationFlags flags_, otava::ast::Node* declarationNode_) :
    context(context_), baseType(baseType_), flags(flags_), declarationList(new DeclarationList()), declarationNode(declarationNode_)
{
}

void DeclaratorListProcessor::Visit(otava::ast::InitDeclaratorListNode& node)
{
    if (!Valid()) return;
    std::int32_t n = node.Items().size();
    for (std::int32_t i = 0; i < n; ++i)
    {
        otava::ast::Node* declarator = node.Items()[i];
        std::expected<Declaration, int> rv = ProcessDeclarator(baseType, declarator, declarationNode, flags, FunctionQualifiers::none, context);
        if (!rv)
        {
            SetError(rv.error());
        }
        Declaration declaration = std::move(*rv);
        if (declaration.declarator.get())
        {
            declarationList->declarations.push_back(std::move(declaration));
        }
    }
}

void DeclaratorListProcessor::Visit(otava::ast::MemberDeclaratorListNode& node)
{
    if (!Valid()) return;
    std::int32_t n = node.Items().size();
    for (std::int32_t i = 0; i < n; ++i)
    {
        otava::ast::Node* declarator = node.Items()[i];
        std::expected<Declaration, int> rv = ProcessDeclarator(baseType, declarator, declarationNode, flags, FunctionQualifiers::none, context);
        if (!rv)
        {
            SetError(rv.error());
        }
        Declaration declaration = std::move(*rv);
        if (declaration.declarator.get())
        {
            declarationList->declarations.push_back(std::move(declaration));
        }
    }
}

class DeclaratorProcessor : public otava::ast::DefaultVisitor
{
public:
    DeclaratorProcessor(Context* context_, DeclarationFlags flags_, TypeSymbol* baseType_, FunctionQualifiers qualifiers_, otava::ast::Node* declarationNode_);
    void SetProcessTrailingQualifiers(bool processTrailingQualifiers_) { processTrailingQualifiers = processTrailingQualifiers_; }
    Declaration GetDeclaration() { return std::move(declaration); }
    void Visit(otava::ast::FunctionDeclaratorNode& node) override;
    void Visit(otava::ast::ParenthesizedDeclaratorNode& node);
    void Visit(otava::ast::TrailingQualifiersNode& node) override;
    void Visit(otava::ast::InitDeclaratorNode& node) override;
    void Visit(otava::ast::ParameterListNode& node) override;
    void Visit(otava::ast::ParameterNode& node) override;
    void Visit(otava::ast::DestructorIdNode& node) override;
    void Visit(otava::ast::ConversionFunctionIdNode& node) override;
    void Visit(otava::ast::ConversionTypeIdNode& node) override;
    void Visit(otava::ast::OperatorFunctionIdNode& node) override;
    void Visit(otava::ast::QualifiedIdNode& node) override;
    void Visit(otava::ast::IdentifierNode& node) override;
    void Visit(otava::ast::TemplateIdNode& node) override;
    void Visit(otava::ast::AbstractDeclaratorNode& node) override;
    void Visit(otava::ast::ArrayDeclaratorNode& node) override;
    void Visit(otava::ast::ConstNode& node) override;
    void Visit(otava::ast::VolatileNode& node) override;
    void Visit(otava::ast::FinalNode& node) override;
    void Visit(otava::ast::OverrideNode& node) override;
    void Visit(otava::ast::PureSpecifierNode& node) override;
    void Visit(otava::ast::LvalueRefNode& node) override;
    void Visit(otava::ast::RvalueRefNode& node) override;
    void Visit(otava::ast::PtrNode& node) override;
    void Visit(otava::ast::NewArrayOpNode& node) override;
    void Visit(otava::ast::NewOpNode& node) override;
    void Visit(otava::ast::DeleteArrayOpNode& node) override;
    void Visit(otava::ast::DeleteOpNode& node) override;
    void Visit(otava::ast::CoAwaitOpNode& node) override;
    void Visit(otava::ast::InvokeOpNode& node) override;
    void Visit(otava::ast::SubscriptOpNode& node) override;
    void Visit(otava::ast::ArrowNode& node) override;
    void Visit(otava::ast::ArrowStarNode& node) override;
    void Visit(otava::ast::ComplementNode& node) override;
    void Visit(otava::ast::NotNode& node) override;
    void Visit(otava::ast::PlusNode& node) override;
    void Visit(otava::ast::MinusNode& node) override;
    void Visit(otava::ast::MulNode& node) override;
    void Visit(otava::ast::DivNode& node) override;
    void Visit(otava::ast::ModNode& node) override;
    void Visit(otava::ast::ExclusiveOrNode& node) override;
    void Visit(otava::ast::AndNode& node) override;
    void Visit(otava::ast::InclusiveOrNode& node) override;
    void Visit(otava::ast::AssignNode& node) override;
    void Visit(otava::ast::PlusAssignNode& node) override;
    void Visit(otava::ast::MinusAssignNode& node) override;
    void Visit(otava::ast::MulAssignNode& node) override;
    void Visit(otava::ast::DivAssignNode& node) override;
    void Visit(otava::ast::ModAssignNode& node) override;
    void Visit(otava::ast::XorAssignNode& node) override;
    void Visit(otava::ast::AndAssignNode& node) override;
    void Visit(otava::ast::OrAssignNode& node) override;
    void Visit(otava::ast::ShiftLeftAssignNode& node) override;
    void Visit(otava::ast::ShiftRightAssignNode& node) override;
    void Visit(otava::ast::EqualNode& node) override;
    void Visit(otava::ast::NotEqualNode& node) override;
    void Visit(otava::ast::LessOrEqualNode& node) override;
    void Visit(otava::ast::GreaterOrEqualNode& node) override;
    void Visit(otava::ast::CompareNode& node) override;
    void Visit(otava::ast::LessNode& node) override;
    void Visit(otava::ast::GreaterNode& node) override;
    void Visit(otava::ast::ConjunctionNode& node) override;
    void Visit(otava::ast::DisjunctionNode& node) override;
    void Visit(otava::ast::ShiftLeftNode& node) override;
    void Visit(otava::ast::ShiftRightNode& node) override;
    void Visit(otava::ast::PrefixIncNode& node) override;
    void Visit(otava::ast::PrefixDecNode& node) override;
    void Visit(otava::ast::CommaNode& node) override;
private:
    Context* context;
    DeclarationFlags flags;
    TypeSymbol* baseType;
    FunctionTypeSymbol* functionTypeSymbol;
    Declaration declaration;
    bool isFunctionDeclarator;
    bool isDestructorDeclarator;
    bool skipIdFunctionDeclarator;
    bool operatorFunctionId;
    bool trailingQualifiers;
    bool processTrailingQualifiers;
    bool processArrayId;
    FunctionQualifiers qualifiers;
    FunctionDeclarator* functionDeclarator;
    Scope* scope;
    std::u32string arrayName;
    otava::ast::Node* declarationNode;
};

DeclaratorProcessor::DeclaratorProcessor(Context* context_, DeclarationFlags flags_, TypeSymbol* baseType_, FunctionQualifiers qualifiers_, otava::ast::Node* declarationNode_) :
    context(context_),
    flags(flags_),
    baseType(baseType_),
    functionTypeSymbol(nullptr),
    isFunctionDeclarator(false),
    isDestructorDeclarator(false),
    skipIdFunctionDeclarator(false),
    operatorFunctionId(false),
    trailingQualifiers(false),
    processTrailingQualifiers(false),
    processArrayId(false),
    scope(context->GetSymbolTable()->CurrentScope()),
    functionDeclarator(),
    qualifiers(qualifiers_),
    declarationNode(declarationNode_)
{
}

void DeclaratorProcessor::Visit(otava::ast::FunctionDeclaratorNode& node)
{
    if (!Valid()) return;
    processTrailingQualifiers = true;
    node.Params()->Accept(*this);
    if (!Valid()) return;
    processTrailingQualifiers = false;
    isFunctionDeclarator = true;
    node.Child()->Accept(*this);
    if (!Valid()) return;
    if (node.Params())
    {
        node.Params()->Accept(*this);
        if (!Valid()) return;
    }
    isFunctionDeclarator = false;
    if (functionTypeSymbol)
    {
        functionTypeSymbol->MakeName();
        if (context->GetSymbolTable()->AddToRecomputeNameSet())
        {
            context->GetSymbolTable()->RecomputeNames();
            context->GetSymbolTable()->SetAddToRecomputeNameSet(false);
        }
        std::expected<bool, int> rv = context->GetSymbolTable()->CurrentScope()->SymbolScope()->AddSymbol(functionTypeSymbol, node.GetSourcePos(), context);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
    }
}

void DeclaratorProcessor::Visit(otava::ast::ParenthesizedDeclaratorNode& node)
{
    if (!Valid()) return;
    if (isFunctionDeclarator)
    {
        isFunctionDeclarator = false;
        functionTypeSymbol = new FunctionTypeSymbol();
        functionTypeSymbol->SetReturnType(baseType);
        baseType = functionTypeSymbol;
        context->GetSymbolTable()->SetAddToRecomputeNameSet(true);
    }
    auto rv = ProcessDeclarator(baseType, node.Declarator(), declarationNode, flags, FunctionQualifiers::none, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    declaration = std::move(*rv);
}

void DeclaratorProcessor::Visit(otava::ast::TrailingQualifiersNode& node)
{
    if (!Valid()) return;
    if (!processTrailingQualifiers)
    {
        node.Subject()->Accept(*this);
        if (!Valid()) return;
        return;
    }
    trailingQualifiers = true;
    VisitSequence(node);
    trailingQualifiers = false;
}

void DeclaratorProcessor::Visit(otava::ast::InitDeclaratorNode& node)
{
    if (!Valid()) return;
    node.Left()->Accept(*this);
    if (node.Right())
    {
        context->SetDeclaredInitializerType(declaration.type);
        auto rv = Evaluate(node.Right(), context);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        Value* value = *rv;
        declaration.value = value;
        declaration.initializer = node.Right();
    }
}

void DeclaratorProcessor::Visit(otava::ast::ParameterListNode& node)
{
    if (!Valid()) return;
    if (processTrailingQualifiers) return;
    int n = node.Items().size();
    for (int i = 0; i < n; ++i)
    {
        otava::ast::Node* item = node.Items()[i];
        item->Accept(*this);
        if (!Valid()) return;
    }
}

void DeclaratorProcessor::Visit(otava::ast::ParameterNode& node)
{
    if (!Valid()) return;
    std::expected<Declaration, int> rv = ProcessParameterDeclaration(&node, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    Declaration declaration = std::move(*rv);
    if (functionDeclarator)
    {
        functionDeclarator->AddParameterDeclaration(std::move(declaration));
    }
    if (functionTypeSymbol)
    {
        functionTypeSymbol->AddParameterType(declaration.type);
    }
}

void DeclaratorProcessor::Visit(otava::ast::ConstNode& node)
{
    if (!Valid()) return;
    if (!trailingQualifiers) return;
    qualifiers = qualifiers | FunctionQualifiers::isConst;
}

void DeclaratorProcessor::Visit(otava::ast::VolatileNode& node)
{
    if (!Valid()) return;
    if (!trailingQualifiers) return;
    qualifiers = qualifiers | FunctionQualifiers::isVolatile;
}

void DeclaratorProcessor::Visit(otava::ast::FinalNode& node)
{
    if (!Valid()) return;
    if (!trailingQualifiers) return;
    qualifiers = qualifiers | FunctionQualifiers::isFinal;
}

void DeclaratorProcessor::Visit(otava::ast::PureSpecifierNode& node)
{
    if (!Valid()) return;
    if (!trailingQualifiers) return;
    qualifiers = qualifiers | FunctionQualifiers::isPure;
}

void DeclaratorProcessor::Visit(otava::ast::OverrideNode& node)
{
    if (!Valid()) return;
    if (!trailingQualifiers) return;
    qualifiers = qualifiers | FunctionQualifiers::isOverride;
}

void DeclaratorProcessor::Visit(otava::ast::LvalueRefNode& node)
{
    if (!Valid()) return;
    Derivations derivations = Derivations::lvalueRefDerivation;
    if (baseType)
    {
        std::expected<TypeSymbol*, int> c = context->GetSymbolTable()->MakeCompoundType(baseType, derivations);
        if (!c)
        {
            SetError(c.error());
            return;
        }
        baseType = *c;
    }
}

void DeclaratorProcessor::Visit(otava::ast::RvalueRefNode& node)
{
    if (!Valid()) return;
    Derivations derivations = Derivations::none;
    if (!baseType || !baseType->IsLValueRefType())
    {
        derivations = derivations | Derivations::rvalueRefDerivation;
    }
    if (baseType)
    {
        std::expected<TypeSymbol*, int> c = context->GetSymbolTable()->MakeCompoundType(baseType, derivations);
        if (!c)
        {
            SetError(c.error());
            return;
        }
        baseType = *c;
    }
}

void DeclaratorProcessor::Visit(otava::ast::PtrNode& node)
{
    if (!Valid()) return;
    Derivations derivations = Derivations::none;
    derivations = otava::symbols::SetPointerCount(derivations, 1);
    if (baseType)
    {
        std::expected<TypeSymbol*, int> c = context->GetSymbolTable()->MakeCompoundType(baseType, derivations);
        if (!c)
        {
            SetError(c.error());
            return;
        }
        baseType = *c;
    }
}

void DeclaratorProcessor::Visit(otava::ast::DestructorIdNode& node)
{
    if (!Valid()) return;
    isDestructorDeclarator = true;
    node.Child()->Accept(*this);
    if (!Valid()) return;
    isDestructorDeclarator = false;
}

void DeclaratorProcessor::Visit(otava::ast::ConversionFunctionIdNode& node)
{
    if (!Valid()) return;
    node.Right()->Accept(*this);
    if (!Valid()) return;
    auto irName = baseType->IrName(context);
    if (!irName)
    {
        SetError(irName.error());
        return;
    }
    auto ustr = util::ToUtf32(*irName);
    if (!ustr)
    {
        SetError(ustr.error());
        return;
    }
    functionDeclarator = new FunctionDeclarator(U"operator_" + *ustr, &node, FunctionKind::conversionMemFn, qualifiers, scope);
    declaration = Declaration(flags, baseType, functionDeclarator);
}

void DeclaratorProcessor::Visit(otava::ast::ConversionTypeIdNode& node)
{
    if (!Valid()) return;
    auto rv = ResolveType(node.TypeSpecifierSeq(), DeclarationFlags::none, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    baseType = *rv;
    if (node.ConversionDeclarator())
    {
        node.ConversionDeclarator()->Accept(*this);
        if (!Valid()) return;
    }
}

void DeclaratorProcessor::Visit(otava::ast::OperatorFunctionIdNode& node)
{
    if (!Valid()) return;
    operatorFunctionId = true;
    skipIdFunctionDeclarator = true;
    node.Right()->Accept(*this);
    if (!Valid()) return;
    skipIdFunctionDeclarator = false;
    operatorFunctionId = false;
    if (functionDeclarator)
    {
        declaration = Declaration(flags, baseType, functionDeclarator);
    }
}

void DeclaratorProcessor::Visit(otava::ast::NewArrayOpNode& node)
{
    if (!Valid()) return;
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator new[]", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(otava::ast::NewOpNode& node)
{
    if (!Valid()) return;
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator new", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(otava::ast::DeleteArrayOpNode& node)
{
    if (!Valid()) return;
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator delete[]", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(otava::ast::DeleteOpNode& node)
{
    if (!Valid()) return;
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator delete", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(otava::ast::CoAwaitOpNode& node)
{
    if (!Valid()) return;
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator co_await", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(otava::ast::InvokeOpNode& node)
{
    if (!Valid()) return;
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator()", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(otava::ast::SubscriptOpNode& node)
{
    if (!Valid()) return;
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator[]", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(otava::ast::ArrowNode& node)
{
    if (!Valid()) return;
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator->", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(otava::ast::ArrowStarNode& node)
{
    if (!Valid()) return;
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator->*", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(otava::ast::ComplementNode& node)
{
    if (!Valid()) return;
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator~", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(otava::ast::NotNode& node)
{
    if (!Valid()) return;
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator!", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(otava::ast::PlusNode& node)
{
    if (!Valid()) return;
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator+", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(otava::ast::MinusNode& node)
{
    if (!Valid()) return;
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator-", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(otava::ast::MulNode& node)
{
    if (!Valid()) return;
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator*", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(otava::ast::DivNode& node)
{
    if (!Valid()) return;
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator/", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(otava::ast::ModNode& node)
{
    if (!Valid()) return;
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator%", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(otava::ast::ExclusiveOrNode& node)
{
    if (!Valid()) return;
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator^", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(otava::ast::AndNode& node)
{
    if (!Valid()) return;
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator&", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(otava::ast::InclusiveOrNode& node)
{
    if (!Valid()) return;
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator|", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(otava::ast::AssignNode& node)
{
    if (!Valid()) return;
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator=", &node, FunctionKind::special, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(otava::ast::PlusAssignNode& node)
{
    if (!Valid()) return;
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator+=", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(otava::ast::MinusAssignNode& node)
{
    if (!Valid()) return;
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator-=", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(otava::ast::MulAssignNode& node)
{
    if (!Valid()) return;
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator*=", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(otava::ast::DivAssignNode& node)
{
    if (!Valid()) return;
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator/=", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(otava::ast::ModAssignNode& node)
{
    if (!Valid()) return;
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator%=", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(otava::ast::XorAssignNode& node)
{
    if (!Valid()) return;
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator^=", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(otava::ast::AndAssignNode& node)
{
    if (!Valid()) return;
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator&=", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(otava::ast::OrAssignNode& node)
{
    if (!Valid()) return;
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator|=", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(otava::ast::ShiftLeftAssignNode& node)
{
    if (!Valid()) return;
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator<<=", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(otava::ast::ShiftRightAssignNode& node)
{
    if (!Valid()) return;
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator>>=", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(otava::ast::EqualNode& node)
{
    if (!Valid()) return;
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator==", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(otava::ast::NotEqualNode& node)
{
    if (!Valid()) return;
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator!=", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(otava::ast::LessOrEqualNode& node)
{
    if (!Valid()) return;
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator<=", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(otava::ast::GreaterOrEqualNode& node)
{
    if (!Valid()) return;
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator>=", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(otava::ast::CompareNode& node)
{
    if (!Valid()) return;
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator<=>", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(otava::ast::LessNode& node)
{
    if (!Valid()) return;
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator<", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(otava::ast::GreaterNode& node)
{
    if (!Valid()) return;
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator>", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(otava::ast::ConjunctionNode& node)
{
    if (!Valid()) return;
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator&&", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(otava::ast::DisjunctionNode& node)
{
    if (!Valid()) return;
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator||", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(otava::ast::ShiftLeftNode& node)
{
    if (!Valid()) return;
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator<<", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(otava::ast::ShiftRightNode& node)
{
    if (!Valid()) return;
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator>>", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(otava::ast::PrefixIncNode& node)
{
    if (!Valid()) return;
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator++", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(otava::ast::PrefixDecNode& node)
{
    if (!Valid()) return;
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator--", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(otava::ast::CommaNode& node)
{
    if (!Valid()) return;
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator,", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(otava::ast::QualifiedIdNode& node)
{
    if (!Valid()) return;
    if (processTrailingQualifiers) return;
    auto srv = ResolveScope(node.Left(), context);
    if (!srv)
    {
        SetError(srv.error());
        return;
    }
    scope = *srv;
    node.Right()->Accept(*this);
    if (!Valid()) return;
}

void DeclaratorProcessor::Visit(otava::ast::IdentifierNode& node)
{
    if (!Valid()) return;
    if (processTrailingQualifiers) return;
    if (processArrayId)
    {
        arrayName = node.Str();
    }
    else
    {
        if (!skipIdFunctionDeclarator)
        {
            if (isFunctionDeclarator)
            {
                if (isDestructorDeclarator)
                {
                    functionDeclarator = new FunctionDeclarator(U"~" + node.Str(), declarationNode, FunctionKind::destructor, qualifiers, scope);
                }
                else
                {
                    FunctionKind kind = FunctionKind::function;
                    Scope* classScope = context->GetSymbolTable()->CurrentScope()->GetClassScope();
                    if (classScope)
                    {
                        Symbol* symbol = classScope->GetSymbol();
                        if (symbol->IsClassTypeSymbol())
                        {
                            ClassTypeSymbol* classTypeSymbol = static_cast<ClassTypeSymbol*>(symbol);
                            if (node.Str() == classTypeSymbol->Name())
                            {
                                kind = FunctionKind::constructor;
                            }
                        }
                    }
                    functionDeclarator = new FunctionDeclarator(node.Str(), declarationNode, kind, qualifiers, scope);
                }
                declaration = Declaration(flags, baseType, functionDeclarator);
            }
            else
            {
                declaration = Declaration(flags, baseType, new SimpleDeclarator(node.Str(), &node));
            }
        }
    }
}

void DeclaratorProcessor::Visit(otava::ast::TemplateIdNode& node)
{
    if (!Valid()) return;
    node.TemplateName()->Accept(*this);
    if (!Valid()) return;
    std::vector<TypeSymbol*> templateArgs;
    for (otava::ast::Node* item : node.Items())
    {
        std::expected<TypeSymbol*, int> rv = ResolveType(item, DeclarationFlags::none, context);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        TypeSymbol* type = *rv;
        templateArgs.push_back(type);
    }
    if (functionDeclarator)
    {
        functionDeclarator->SetTemplateArgs(templateArgs);
    }
}

void DeclaratorProcessor::Visit(otava::ast::AbstractDeclaratorNode& node)
{
    if (!Valid()) return;
    declaration = Declaration(flags, baseType, new SimpleDeclarator(std::u32string(), &node));
}

void DeclaratorProcessor::Visit(otava::ast::ArrayDeclaratorNode& node)
{
    if (!Valid()) return;
    processArrayId = true;
    node.Child()->Accept(*this);
    if (!Valid()) return;
    processArrayId = false;
    std::int64_t size = -1;
    if (node.Dimension())
    {
        auto rv = Evaluate(node.Dimension(), context);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        Value* sizeValue = *rv;
        if (sizeValue->IsIntegerValue())
        {
            IntegerValue* integerValue = static_cast<IntegerValue*>(sizeValue);
            size = integerValue->GetValue();
        }
        else
        {
            std::unexpected<int> result = Error("integer value expected", node.GetSourcePos(), context);
            SetError(result.error());
            return;
        }
    }
    ArrayTypeSymbol* arrayType = context->GetSymbolTable()->MakeArrayType(baseType, size);
    std::expected<bool, int> rv = arrayType->Bind(node.GetSourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    declaration = Declaration(flags, arrayType, new ArrayDeclarator(arrayName, &node, size));
}

std::expected<std::unique_ptr<DeclarationList>, int> ProcessInitDeclaratorList(TypeSymbol* baseType, otava::ast::Node* declarationNode, 
    otava::ast::Node* initDeclaratorList, DeclarationFlags flags, Context* context)
{
    DeclaratorListProcessor processor(context, baseType, flags, declarationNode);
    initDeclaratorList->Accept(processor);
    if (!processor) return std::unexpected<int>(processor.Error());
    return std::expected<std::unique_ptr<DeclarationList>, int>(std::move(processor.GetDeclarations()));
}

std::expected<std::unique_ptr<DeclarationList>, int> ProcessMemberDeclaratorList(TypeSymbol* baseType, otava::ast::Node* declarationNode, 
    otava::ast::Node* memberDeclaratorList, DeclarationFlags flags, Context* context)
{
    DeclaratorListProcessor processor(context, baseType, flags, declarationNode);
    memberDeclaratorList->Accept(processor);
    if (!processor) return std::unexpected<int>(processor.Error());
    return std::expected<std::unique_ptr<DeclarationList>, int>(std::move(processor.GetDeclarations()));
}

std::expected<Declaration, int> ProcessDeclarator(TypeSymbol* baseType, otava::ast::Node* declarator, otava::ast::Node* declarationNode, DeclarationFlags flags, 
    FunctionQualifiers qualifiers, Context* context)
{
    DeclaratorProcessor processor(context, flags, baseType, qualifiers, declarationNode);
    if (declarator->Kind() == otava::ast::NodeKind::trailingQualifiersNode)
    {
        processor.SetProcessTrailingQualifiers(true);
        declarator->Accept(processor);
        if (!processor) return std::unexpected<int>(processor.Error());
        processor.SetProcessTrailingQualifiers(false);
    }
    declarator->Accept(processor);
    if (!processor) return std::unexpected<int>(processor.Error());
    return std::expected<Declaration, int>(processor.GetDeclaration());
}

} // namespace otava::symbols
