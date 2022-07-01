// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.symbols.declarator;

import std.core;
import soul.cpp20.ast;

export namespace soul::cpp20::symbols {

class TypeSymbol;

enum class DeclaratorKind
{
    simpleDeclarator = 0, functionDeclarator = 1
};

class Declarator
{
public:
    Declarator(DeclaratorKind kind_, const std::u32string& name_, soul::cpp20::ast::Node* node_);
    virtual ~Declarator();
    DeclaratorKind Kind() const { return kind; }
    const std::u32string& Name() const { return name; }
    soul::cpp20::ast::Node* Node() const { return node; }
private:
    DeclaratorKind kind;
    std::u32string name;
    soul::cpp20::ast::Node* node;
};

class SimpleDeclarator : public Declarator
{
public:
    SimpleDeclarator(const std::u32string& name_, soul::cpp20::ast::Node* node_);
};

struct Declaration
{
    Declaration();
    Declaration(TypeSymbol* type_, Declarator* declarator_);
    TypeSymbol* type;
    std::unique_ptr<Declarator> declarator;
};

class FunctionDeclarator : public Declarator
{
public:
    FunctionDeclarator(const std::u32string& name_, soul::cpp20::ast::Node* node_);
    void AddParameterDeclaration(Declaration&& parameterDeclaration);
    const std::vector<Declaration>& ParameterDeclarations() const { return parameterDeclarations; }
private:
    std::vector<Declaration> parameterDeclarations;
};

class Context;

std::vector<Declaration> ProcessInitDeclaratorList(TypeSymbol* baseType, soul::cpp20::ast::Node* initDeclaratorList, Context* context);
Declaration ProcessDeclarator(TypeSymbol* baseType, soul::cpp20::ast::Node* declarator, Context* context);

} // namespace soul::cpp20::symbols
