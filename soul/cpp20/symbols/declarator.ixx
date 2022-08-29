// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.symbols.declarator;

import std.core;
import soul.cpp20.ast;

export namespace soul::cpp20::symbols {

class Scope;
class TypeSymbol;

enum class FunctionKind;
enum class FunctionQualifiers;
enum class DeclarationFlags : int32_t;

enum class DeclaratorKind
{
    simpleDeclarator = 0, functionDeclarator = 1
};

class Value;

class Declarator
{
public:
    Declarator(DeclaratorKind kind_, const std::u32string& name_, soul::cpp20::ast::Node* node_);
    virtual ~Declarator();
    bool IsSimpleDeclarator() const { return kind == DeclaratorKind::simpleDeclarator; }
    bool IsFunctionDeclarator() const { return kind == DeclaratorKind::functionDeclarator;  }
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
    Declaration(DeclarationFlags flags_, TypeSymbol* type_, Declarator* declarator_);
    DeclarationFlags flags;
    TypeSymbol* type;
    std::unique_ptr<Declarator> declarator;
    Value* value;
};

class FunctionDeclarator : public Declarator
{
public:
    FunctionDeclarator(const std::u32string& name_, soul::cpp20::ast::Node* node_, FunctionKind kind_, FunctionQualifiers qualifiers_, Scope* scope_);
    FunctionKind GetFunctionKind() const { return kind; }
    FunctionQualifiers GetFunctionQualifiers() const { return qualifiers; }
    void AddQualifier(FunctionQualifiers qualifier);
    void AddParameterDeclaration(Declaration&& parameterDeclaration);
    const std::vector<Declaration>& ParameterDeclarations() const { return parameterDeclarations; }
    Scope* GetScope() const { return scope; }
private:
    FunctionKind kind;
    FunctionQualifiers qualifiers;
    std::vector<Declaration> parameterDeclarations;
    Scope* scope;
};

class Context;

std::vector<Declaration> ProcessInitDeclaratorList(TypeSymbol* baseType, soul::cpp20::ast::Node* initDeclaratorList, DeclarationFlags flags, Context* context);
std::vector<Declaration> ProcessMemberDeclaratorList(TypeSymbol* baseType, soul::cpp20::ast::Node* memberDeclaratorList, DeclarationFlags flags, Context* context);
Declaration ProcessDeclarator(TypeSymbol* baseType, soul::cpp20::ast::Node* declarator, DeclarationFlags flags, Context* context);

} // namespace soul::cpp20::symbols
