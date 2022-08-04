// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.symbols.declarator;

import soul.cpp20.symbols.context;
import soul.cpp20.symbols.declaration;
import soul.cpp20.symbols.scope.resolver;
import soul.cpp20.symbols.symbol.table;

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

FunctionDeclarator::FunctionDeclarator(const std::u32string& name_, soul::cpp20::ast::Node* node_, Scope* scope_) : 
    Declarator(DeclaratorKind::functionDeclarator, name_, node_), scope(scope_)
{
}

void FunctionDeclarator::AddParameterDeclaration(Declaration&& parameterDeclaration)
{
    parameterDeclarations.push_back(std::move(parameterDeclaration));
}

Declaration::Declaration() : type(nullptr), declarator(nullptr)
{
}

Declaration::Declaration(TypeSymbol* type_, Declarator* declarator_) : type(type_), declarator(declarator_)
{
}

class DeclaratorListProcessor : public soul::cpp20::ast::DefaultVisitor
{
public:
    DeclaratorListProcessor(Context* context_, TypeSymbol* baseType_);
    std::vector<Declaration> GetDeclarations() { return std::move(declarations); }
    void Visit(soul::cpp20::ast::InitDeclaratorListNode& node) override;
    void Visit(soul::cpp20::ast::MemberDeclaratorListNode& node) override;
private:
    Context* context;
    TypeSymbol* baseType;
    std::vector<Declaration> declarations;
};

DeclaratorListProcessor::DeclaratorListProcessor(Context* context_, TypeSymbol* baseType_) : context(context_), baseType(baseType_)
{
}

void DeclaratorListProcessor::Visit(soul::cpp20::ast::InitDeclaratorListNode& node)
{
    int32_t n = node.Items().size();
    for (int32_t i = 0; i < n; ++i)
    {
        soul::cpp20::ast::Node* declarator = node.Items()[i];
        Declaration declaration = ProcessDeclarator(baseType, declarator, context);
        if (declaration.declarator.get())
        {
            declarations.push_back(std::move(declaration));
        }
    }
}

void DeclaratorListProcessor::Visit(soul::cpp20::ast::MemberDeclaratorListNode& node)
{
    int32_t n = node.Items().size();
    for (int32_t i = 0; i < n; ++i)
    {
        soul::cpp20::ast::Node* declarator = node.Items()[i];
        Declaration declaration = ProcessDeclarator(baseType, declarator, context);
        if (declaration.declarator.get())
        {
            declarations.push_back(std::move(declaration));
        }
    }
}

class DeclaratorProcessor : public soul::cpp20::ast::DefaultVisitor
{
public:
    DeclaratorProcessor(Context* context_, TypeSymbol* baseType_);
    Declaration GetDeclaration() { return std::move(declaration); }
    void Visit(soul::cpp20::ast::FunctionDeclaratorNode& node) override;
    void Visit(soul::cpp20::ast::ParameterListNode& node) override;
    void Visit(soul::cpp20::ast::ParameterNode& node) override;
    void Visit(soul::cpp20::ast::DestructorIdNode& node) override;
    void Visit(soul::cpp20::ast::ConversionFunctionIdNode& node) override;
    void Visit(soul::cpp20::ast::OperatorFunctionIdNode& node) override;
    void Visit(soul::cpp20::ast::QualifiedIdNode& node) override;
    void Visit(soul::cpp20::ast::IdentifierNode& node) override;
private:
    Context* context;
    TypeSymbol* baseType;
    Declaration declaration;
    bool isFunctionDeclarator;
    bool isDestructorDeclarator;
    bool skipFunctionDeclarator;
    FunctionDeclarator* functionDeclarator;
    Scope* scope;
};

DeclaratorProcessor::DeclaratorProcessor(Context* context_, TypeSymbol* baseType_) : 
    context(context_), baseType(baseType_), isFunctionDeclarator(false), isDestructorDeclarator(false), skipFunctionDeclarator(false), 
    scope(context->GetSymbolTable()->CurrentScope())
{
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::FunctionDeclaratorNode& node)
{
    isFunctionDeclarator = true;
    node.Child()->Accept(*this);
    isFunctionDeclarator = false;
    if (node.Params())
    {
        node.Params()->Accept(*this);
    }
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::ParameterListNode& node)
{
    int n = node.Items().size();
    for (int i = 0; i < n; ++i)
    {
        node.Items()[i]->Accept(*this);
    }
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::ParameterNode& node)
{
    Declaration declaration = ProcessParameterDeclaration(&node, context);
    if (functionDeclarator)
    {
        functionDeclarator->AddParameterDeclaration(std::move(declaration));
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
    skipFunctionDeclarator = true;
    node.Right()->Accept(*this);
    skipFunctionDeclarator = false;
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::OperatorFunctionIdNode& node)
{
    skipFunctionDeclarator = true;
    node.Right()->Accept(*this);
    skipFunctionDeclarator = false;
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::QualifiedIdNode& node)
{
    scope = ResolveScope(node.Left(), context);
    node.Right()->Accept(*this);
}

void DeclaratorProcessor::Visit(soul::cpp20::ast::IdentifierNode& node)
{
    if (!skipFunctionDeclarator)
    {
        if (isFunctionDeclarator)
        {
            if (isDestructorDeclarator)
            {
                functionDeclarator = new FunctionDeclarator(U"~" + node.Str(), &node, scope);
            }
            else
            {
                functionDeclarator = new FunctionDeclarator(node.Str(), &node, scope);
            }
            declaration = Declaration(baseType, functionDeclarator);
        }
        else
        {
            declaration = Declaration(baseType, new SimpleDeclarator(node.Str(), &node));
        }
    }
}

std::vector<Declaration> ProcessInitDeclaratorList(TypeSymbol* baseType, soul::cpp20::ast::Node* initDeclaratorList, Context* context)
{
    DeclaratorListProcessor processor(context, baseType);
    initDeclaratorList->Accept(processor);
    return processor.GetDeclarations();
}

std::vector<Declaration> ProcessMemberDeclaratorList(TypeSymbol* baseType, soul::cpp20::ast::Node* memberDeclaratorList, Context* context)
{
    DeclaratorListProcessor processor(context, baseType);
    memberDeclaratorList->Accept(processor);
    return processor.GetDeclarations();
}

Declaration ProcessDeclarator(TypeSymbol* baseType, soul::cpp20::ast::Node* declarator, Context* context)
{
    DeclaratorProcessor processor(context, baseType);
    declarator->Accept(processor);
    return processor.GetDeclaration();
}

} // namespace soul::cpp20::symbols
