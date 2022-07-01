// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.symbols.declarator;

import soul.cpp20.symbols.declaration;

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

FunctionDeclarator::FunctionDeclarator(const std::u32string& name_, soul::cpp20::ast::Node* node_) : Declarator(DeclaratorKind::functionDeclarator, name_, node_)
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

class InitDeclaratorListProcessor : public soul::cpp20::ast::DefaultVisitor
{
public:
    InitDeclaratorListProcessor(Context* context_, TypeSymbol* baseType_);
    std::vector<Declaration> GetDeclarations() { return std::move(declarations); }
    void Visit(soul::cpp20::ast::InitDeclaratorListNode& node) override;
private:
    Context* context;
    TypeSymbol* baseType;
    std::vector<Declaration> declarations;
};

InitDeclaratorListProcessor::InitDeclaratorListProcessor(Context* context_, TypeSymbol* baseType_) : context(context_), baseType(baseType_)
{
}

void InitDeclaratorListProcessor::Visit(soul::cpp20::ast::InitDeclaratorListNode& node)
{
    int32_t n = node.Items().size();
    for (int32_t i = 0; i < n; ++i)
    {
        soul::cpp20::ast::Node* declarator = node.Items()[i];
        Declaration declaration = ProcessDeclarator(baseType, declarator, context);
        declarations.push_back(std::move(declaration));
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
    void Visit(soul::cpp20::ast::IdentifierNode& node) override;
private:
    Context* context;
    TypeSymbol* baseType;
    Declaration declaration;
    bool isFunctionDeclarator;
    FunctionDeclarator* functionDeclarator;
};

DeclaratorProcessor::DeclaratorProcessor(Context* context_, TypeSymbol* baseType_) : context(context_), baseType(baseType_), isFunctionDeclarator(false)
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
    int n = node.Nodes().Count();
    for (int i = 0; i < n; ++i)
    {
        node.Nodes()[i]->Accept(*this);
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

void DeclaratorProcessor::Visit(soul::cpp20::ast::IdentifierNode& node)
{
    if (isFunctionDeclarator)
    {
        functionDeclarator = new FunctionDeclarator(node.Str(), &node);
        declaration = Declaration(baseType, functionDeclarator);
    }
    else
    {
        declaration = Declaration(baseType, new SimpleDeclarator(node.Str(), &node));
    }
}

std::vector<Declaration> ProcessInitDeclaratorList(TypeSymbol* baseType, soul::cpp20::ast::Node* initDeclaratorList, Context* context)
{
    InitDeclaratorListProcessor processor(context, baseType);
    initDeclaratorList->Accept(processor);
    return processor.GetDeclarations();
}

Declaration ProcessDeclarator(TypeSymbol* baseType, soul::cpp20::ast::Node* declarator, Context* context)
{
    DeclaratorProcessor processor(context, baseType);
    declarator->Accept(processor);
    return processor.GetDeclaration();
}

} // namespace soul::cpp20::symbols
