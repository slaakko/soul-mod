// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.symbols.declarator;

import soul.cpp20.ast.visitor;
import soul.cpp20.symbols.classes;
import soul.cpp20.symbols.context;
import soul.cpp20.symbols.declaration;
import soul.cpp20.symbols.evaluator;
import soul.cpp20.symbols.expression.binder;
import soul.cpp20.symbols.function.symbol;
import soul.cpp20.symbols.scope;
import soul.cpp20.symbols.scope.resolver;
import soul.cpp20.symbols.symbol;
import soul.cpp20.symbols.symbol.table;
import soul.cpp20.symbols.value;

namespace soul::cpp20::symbols {

Declarator::Declarator(DeclaratorKind kind_, const std::u32string& name_, soul::cpp20::ast::Node* node_) : kind(kind_), name(name_), node(node_)
{
}
    
Declarator::~Declarator()
{
}

SimpleDeclarator::SimpleDeclarator(const std::u32string& name_, soul::cpp20::ast::Node* node_) : Declarator(DeclaratorKind::simpleDeclarator, name_, node_)
{
}

FunctionDeclarator::FunctionDeclarator(const std::u32string& name_, soul::cpp20::ast::Node* node_, FunctionKind kind_, FunctionQualifiers qualifiers_, Scope* scope_) :
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

Declaration::Declaration() : flags(DeclarationFlags::none), type(nullptr), declarator(nullptr), value(nullptr), initializer(nullptr), variable(nullptr)
{
}

Declaration::Declaration(DeclarationFlags flags_, TypeSymbol* type_, Declarator* declarator_) : 
    flags(flags_), type(type_), declarator(declarator_), value(nullptr), initializer(nullptr), variable(nullptr)
{
}

class DeclaratorListProcessor : public soul::cpp20::ast::DefaultVisitor
{
public:
    DeclaratorListProcessor(Context* context_, TypeSymbol* baseType_, DeclarationFlags flags_);
    std::unique_ptr<DeclarationList> GetDeclarations() { return std::move(declarationList); }
    void Visit(soul::cpp20::ast::InitDeclaratorListNode& node) override;
    void Visit(soul::cpp20::ast::MemberDeclaratorListNode& node) override;
private:
    Context* context;
    TypeSymbol* baseType;
    DeclarationFlags flags;
    std::unique_ptr<DeclarationList> declarationList;
};

DeclaratorListProcessor::DeclaratorListProcessor(Context* context_, TypeSymbol* baseType_, DeclarationFlags flags_) : 
    context(context_), baseType(baseType_), flags(flags_), declarationList(new DeclarationList())
{
}

void DeclaratorListProcessor::Visit(soul::cpp20::ast::InitDeclaratorListNode& node)
{
    int32_t n = node.Items().size();
    for (int32_t i = 0; i < n; ++i)
    {
        soul::cpp20::ast::Node* declarator = node.Items()[i];
        Declaration declaration = ProcessDeclarator(baseType, declarator, flags, context);
        if (declaration.declarator.get())
        {
            declarationList->declarations.push_back(std::move(declaration));
        }
    }
}

void DeclaratorListProcessor::Visit(soul::cpp20::ast::MemberDeclaratorListNode& node)
{
    int32_t n = node.Items().size();
    for (int32_t i = 0; i < n; ++i)
    {
        soul::cpp20::ast::Node* declarator = node.Items()[i];
        Declaration declaration = ProcessDeclarator(baseType, declarator, flags, context);
        if (declaration.declarator.get())
        {
            declarationList->declarations.push_back(std::move(declaration));
        }
    }
}

class DeclaratorProcessor : public soul::cpp20::ast::DefaultVisitor
{
public:
    DeclaratorProcessor(Context* context_, DeclarationFlags flags_, TypeSymbol* baseType_);
    void SetProcessTrailingQualifiers(bool processTrailingQualifiers_) { processTrailingQualifiers = processTrailingQualifiers_; }
    Declaration GetDeclaration() { return std::move(declaration); }
    void Visit(soul::cpp20::ast::FunctionDeclaratorNode& node) override;
    void Visit(soul::cpp20::ast::ParenthesizedDeclaratorNode& node);
    void Visit(soul::cpp20::ast::TrailingQualifiersNode& node) override;
    void Visit(soul::cpp20::ast::InitDeclaratorNode& node) override;
    void Visit(soul::cpp20::ast::ParameterListNode& node) override;
    void Visit(soul::cpp20::ast::ParameterNode& node) override;
    void Visit(soul::cpp20::ast::DestructorIdNode& node) override;
    void Visit(soul::cpp20::ast::ConversionFunctionIdNode& node) override;
    void Visit(soul::cpp20::ast::OperatorFunctionIdNode& node) override;
    void Visit(soul::cpp20::ast::QualifiedIdNode& node) override;
    void Visit(soul::cpp20::ast::IdentifierNode& node) override;
    void Visit(soul::cpp20::ast::AbstractDeclaratorNode& node) override;
    void Visit(soul::cpp20::ast::ConstNode& node) override;
    void Visit(soul::cpp20::ast::VolatileNode& node) override;
    void Visit(soul::cpp20::ast::FinalNode& node) override;
    void Visit(soul::cpp20::ast::OverrideNode& node) override;
    void Visit(soul::cpp20::ast::LvalueRefNode& node) override;
    void Visit(soul::cpp20::ast::RvalueRefNode& node) override;
    void Visit(soul::cpp20::ast::PtrNode& node) override;
    void Visit(soul::cpp20::ast::NewArrayOpNode& node) override;
    void Visit(soul::cpp20::ast::NewOpNode& node) override;
    void Visit(soul::cpp20::ast::DeleteArrayOpNode& node) override;
    void Visit(soul::cpp20::ast::DeleteOpNode& node) override;
    void Visit(soul::cpp20::ast::CoAwaitOpNode& node) override;
    void Visit(soul::cpp20::ast::InvokeOpNode& node) override;
    void Visit(soul::cpp20::ast::SubscriptOpNode& node) override;
    void Visit(soul::cpp20::ast::ArrowNode& node) override;
    void Visit(soul::cpp20::ast::ArrowStarNode& node) override;
    void Visit(soul::cpp20::ast::ComplementNode& node) override;
    void Visit(soul::cpp20::ast::NotNode& node) override;
    void Visit(soul::cpp20::ast::PlusNode& node) override;
    void Visit(soul::cpp20::ast::MinusNode& node) override;
    void Visit(soul::cpp20::ast::MulNode& node) override;
    void Visit(soul::cpp20::ast::DivNode& node) override;
    void Visit(soul::cpp20::ast::ModNode& node) override;
    void Visit(soul::cpp20::ast::ExclusiveOrNode& node) override;
    void Visit(soul::cpp20::ast::AndNode& node) override;
    void Visit(soul::cpp20::ast::InclusiveOrNode& node) override;
    void Visit(soul::cpp20::ast::AssignNode& node) override;
    void Visit(soul::cpp20::ast::PlusAssignNode& node) override;
    void Visit(soul::cpp20::ast::MinusAssignNode& node) override;
    void Visit(soul::cpp20::ast::MulAssignNode& node) override;
    void Visit(soul::cpp20::ast::DivAssignNode& node) override;
    void Visit(soul::cpp20::ast::ModAssignNode& node) override;
    void Visit(soul::cpp20::ast::XorAssignNode& node) override;
    void Visit(soul::cpp20::ast::AndAssignNode& node) override;
    void Visit(soul::cpp20::ast::OrAssignNode& node) override;
    void Visit(soul::cpp20::ast::ShiftLeftAssignNode& node) override;
    void Visit(soul::cpp20::ast::ShiftRightAssignNode& node) override;
    void Visit(soul::cpp20::ast::EqualNode& node) override;
    void Visit(soul::cpp20::ast::NotEqualNode& node) override;
    void Visit(soul::cpp20::ast::LessOrEqualNode& node) override;
    void Visit(soul::cpp20::ast::GreaterOrEqualNode& node) override;
    void Visit(soul::cpp20::ast::CompareNode& node) override;
    void Visit(soul::cpp20::ast::LessNode& node) override;
    void Visit(soul::cpp20::ast::GreaterNode& node) override;
    void Visit(soul::cpp20::ast::ConjunctionNode& node) override;
    void Visit(soul::cpp20::ast::DisjunctionNode& node) override;
    void Visit(soul::cpp20::ast::ShiftLeftNode& node) override;
    void Visit(soul::cpp20::ast::ShiftRightNode& node) override;
    void Visit(soul::cpp20::ast::PrefixIncNode& node) override;
    void Visit(soul::cpp20::ast::PrefixDecNode& node) override;
    void Visit(soul::cpp20::ast::CommaNode& node) override;
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
    FunctionQualifiers qualifiers;
    FunctionDeclarator* functionDeclarator;
    Scope* scope;
};

DeclaratorProcessor::DeclaratorProcessor(Context* context_, DeclarationFlags flags_, TypeSymbol* baseType_) :
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
    scope(context->GetSymbolTable()->CurrentScope())
{
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::FunctionDeclaratorNode& node)
{
    processTrailingQualifiers = true;
    node.Params()->Accept(*this);
    processTrailingQualifiers = false;
    isFunctionDeclarator = true;
    node.Child()->Accept(*this);
    if (node.Params())
    {
        node.Params()->Accept(*this);
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
        context->GetSymbolTable()->CurrentScope()->SymbolScope()->AddSymbol(functionTypeSymbol, node.GetSourcePos(), context);
    }
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::ParenthesizedDeclaratorNode& node)
{
    if (isFunctionDeclarator)
    {
        isFunctionDeclarator = false;
        functionTypeSymbol = new FunctionTypeSymbol();
        functionTypeSymbol->SetReturnType(baseType);
        baseType = functionTypeSymbol;
        context->GetSymbolTable()->SetAddToRecomputeNameSet(true);
    }
    declaration = ProcessDeclarator(baseType, node.Declarator(), flags, context);
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::TrailingQualifiersNode& node)
{
    if (!processTrailingQualifiers)
    {
        node.Subject()->Accept(*this);
        return;
    }
    trailingQualifiers = true;
    VisitSequence(node);
    trailingQualifiers = false;
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::InitDeclaratorNode& node)
{
    node.Left()->Accept(*this);
    if (node.Right())
    {
        Value* value = Evaluate(node.Right(), context);
        declaration.value = value;
        declaration.initializer = node.Right();
    }
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::ParameterListNode& node)
{
    if (processTrailingQualifiers) return;
    int n = node.Items().size();
    for (int i = 0; i < n; ++i)
    {
        soul::cpp20::ast::Node* item = node.Items()[i];
        item->Accept(*this);
    }
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::ParameterNode& node)
{
    Declaration declaration = ProcessParameterDeclaration(&node, context);
    if (functionDeclarator)
    {
        functionDeclarator->AddParameterDeclaration(std::move(declaration));
    }
    if (functionTypeSymbol)
    {
        functionTypeSymbol->AddParameterType(declaration.type);
    }
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::ConstNode& node)
{
    if (!trailingQualifiers) return;
    qualifiers = qualifiers | FunctionQualifiers::isConst;
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::VolatileNode& node)
{
    if (!trailingQualifiers) return;
    qualifiers = qualifiers | FunctionQualifiers::isVolatile;
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::FinalNode& node)
{
    if (!trailingQualifiers) return;
    qualifiers = qualifiers | FunctionQualifiers::isFinal;
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::OverrideNode& node)
{
    if (!trailingQualifiers) return;
    qualifiers = qualifiers | FunctionQualifiers::isOverride;
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::LvalueRefNode& node)
{
    Derivations derivations;
    derivations.vec.push_back(Derivation::lvalueRefDerivation);
    if (baseType)
    {
        baseType = context->GetSymbolTable()->MakeCompoundType(baseType, derivations);
    }
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::RvalueRefNode& node)
{
    Derivations derivations;
    derivations.vec.push_back(Derivation::rvalueRefDerivation);
    if (baseType)
    {
        baseType = context->GetSymbolTable()->MakeCompoundType(baseType, derivations);
    }
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::PtrNode& node)
{
    Derivations derivations;
    derivations.vec.push_back(Derivation::pointerDerivation);
    if (baseType)
    {
        baseType = context->GetSymbolTable()->MakeCompoundType(baseType, derivations);
    }
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::DestructorIdNode& node)
{
    isDestructorDeclarator = true;
    node.Child()->Accept(*this);
    isDestructorDeclarator = false;
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::ConversionFunctionIdNode& node)
{
    skipIdFunctionDeclarator = true;
    node.Right()->Accept(*this);
    skipIdFunctionDeclarator = false;
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::OperatorFunctionIdNode& node)
{
    operatorFunctionId = true;
    skipIdFunctionDeclarator = true;
    node.Right()->Accept(*this);
    skipIdFunctionDeclarator = false;
    operatorFunctionId = false;
    if (functionDeclarator)
    {
        declaration = Declaration(flags, baseType, functionDeclarator);
    }
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::NewArrayOpNode& node)
{
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator new[]", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::NewOpNode& node)
{
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator new", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::DeleteArrayOpNode& node)
{
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator delete[]", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::DeleteOpNode& node)
{
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator delete", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::CoAwaitOpNode& node)
{
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator co_await", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::InvokeOpNode& node)
{
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator()", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::SubscriptOpNode& node)
{
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator[]", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::ArrowNode& node)
{
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator->", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::ArrowStarNode& node)
{
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator->*", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::ComplementNode& node)
{
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator~", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::NotNode& node)
{
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator!", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::PlusNode& node)
{
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator+", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::MinusNode& node)
{
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator-", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::MulNode& node)
{
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator*", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::DivNode& node)
{
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator/", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::ModNode& node)
{
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator%", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::ExclusiveOrNode& node)
{
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator^", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::AndNode& node)
{
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator&", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::InclusiveOrNode& node)
{
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator|", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::AssignNode& node)
{
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator=", &node, FunctionKind::special, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::PlusAssignNode& node)
{
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator+=", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::MinusAssignNode& node)
{
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator-=", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::MulAssignNode& node)
{
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator*=", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::DivAssignNode& node)
{
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator/=", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::ModAssignNode& node)
{
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator%=", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::XorAssignNode& node)
{
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator^=", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::AndAssignNode& node)
{
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator&=", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::OrAssignNode& node)
{
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator|=", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::ShiftLeftAssignNode& node)
{
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator<<=", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::ShiftRightAssignNode& node)
{
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator>>=", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::EqualNode& node)
{
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator==", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::NotEqualNode& node)
{
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator!=", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::LessOrEqualNode& node)
{
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator<=", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::GreaterOrEqualNode& node)
{
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator>=", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::CompareNode& node)
{
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator<=>", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::LessNode& node)
{
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator<", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::GreaterNode& node)
{
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator>", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::ConjunctionNode& node)
{
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator&&", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::DisjunctionNode& node)
{
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator||", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::ShiftLeftNode& node)
{
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator<<", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::ShiftRightNode& node)
{
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator>>", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::PrefixIncNode& node)
{
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator++", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::PrefixDecNode& node)
{
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator--", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::CommaNode& node) 
{
    if (operatorFunctionId)
    {
        functionDeclarator = new FunctionDeclarator(U"operator,", &node, FunctionKind::function, qualifiers, scope);
    }
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::QualifiedIdNode& node)
{
    if (processTrailingQualifiers) return;
    scope = ResolveScope(node.Left(), context);
    node.Right()->Accept(*this);
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::IdentifierNode& node)
{
    if (processTrailingQualifiers) return;
    if (!skipIdFunctionDeclarator)
    {
        if (isFunctionDeclarator)
        {
            if (isDestructorDeclarator)
            {
                functionDeclarator = new FunctionDeclarator(U"~" + node.Str(), &node, FunctionKind::destructor, qualifiers, scope);
            }
            else
            {
                FunctionKind kind = FunctionKind::function;
                if (context->GetSymbolTable()->CurrentScope()->SymbolScope()->IsClassScope())
                {
                    Symbol* symbol = context->GetSymbolTable()->CurrentScope()->SymbolScope()->GetSymbol();
                    if (symbol->IsClassTypeSymbol())
                    {
                        ClassTypeSymbol* classTypeSymbol = static_cast<ClassTypeSymbol*>(symbol);
                        if (node.Str() == classTypeSymbol->Name())
                        {
                            kind = FunctionKind::constructor;
                        }
                    }
                }
                functionDeclarator = new FunctionDeclarator(node.Str(), &node, kind, qualifiers, scope);
            }
            declaration = Declaration(flags, baseType, functionDeclarator);
        }
        else
        {
            declaration = Declaration(flags, baseType, new SimpleDeclarator(node.Str(), &node));
        }
    }
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::AbstractDeclaratorNode& node)
{
    declaration = Declaration(flags, baseType, new SimpleDeclarator(std::u32string(), &node));
}

std::unique_ptr<DeclarationList> ProcessInitDeclaratorList(TypeSymbol* baseType, soul::cpp20::ast::Node* initDeclaratorList, DeclarationFlags flags, Context* context)
{
    DeclaratorListProcessor processor(context, baseType, flags);
    initDeclaratorList->Accept(processor);
    return processor.GetDeclarations();
}

std::unique_ptr<DeclarationList> ProcessMemberDeclaratorList(TypeSymbol* baseType, soul::cpp20::ast::Node* memberDeclaratorList, DeclarationFlags flags, Context* context)
{
    DeclaratorListProcessor processor(context, baseType, flags);
    memberDeclaratorList->Accept(processor);
    return processor.GetDeclarations();
}

Declaration ProcessDeclarator(TypeSymbol* baseType, soul::cpp20::ast::Node* declarator, DeclarationFlags flags, Context* context)
{
    DeclaratorProcessor processor(context, flags, baseType);
    if (declarator->Kind() == soul::cpp20::ast::NodeKind::trailingQualifiersNode)
    {
        processor.SetProcessTrailingQualifiers(true);
        declarator->Accept(processor);
        processor.SetProcessTrailingQualifiers(false);
    }
    declarator->Accept(processor);
    return processor.GetDeclaration();
}

} // namespace soul::cpp20::symbols
