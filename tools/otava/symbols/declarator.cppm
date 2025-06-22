// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.declarator;

import std.core;
import otava.ast;
import otava.symbols.bound.tree;

export namespace otava::symbols {

enum class FunctionKind;
enum class FunctionQualifiers;
enum class DeclarationFlags : std::int32_t;

enum class DeclaratorKind
{
    simpleDeclarator = 0, functionDeclarator = 1, arrayDeclarator = 2
};

class Value;

class Declarator
{
public:
    Declarator(DeclaratorKind kind_, const std::u32string& name_, otava::ast::Node* node_);
    virtual ~Declarator();
    bool IsSimpleDeclarator() const { return kind == DeclaratorKind::simpleDeclarator; }
    bool IsFunctionDeclarator() const { return kind == DeclaratorKind::functionDeclarator;  }
    bool IsArrayDeclarator() const { return kind == DeclaratorKind::arrayDeclarator; }
    DeclaratorKind Kind() const { return kind; }
    const std::u32string& Name() const { return name; }
    otava::ast::Node* Node() const { return node; }
private:
    DeclaratorKind kind;
    std::u32string name;
    otava::ast::Node* node;
};

class SimpleDeclarator : public Declarator
{
public:
    SimpleDeclarator(const std::u32string& name_, otava::ast::Node* node_);
};

struct Declaration
{
    Declaration();
    Declaration(DeclarationFlags flags_, TypeSymbol* type_, Declarator* declarator_);
    DeclarationFlags flags;
    TypeSymbol* type;
    std::unique_ptr<Declarator> declarator;
    Value* value;
    otava::ast::Node* initializer;
    VariableSymbol* variable;
};

struct DeclarationList
{
    std::vector<Declaration> declarations;
};

class FunctionDeclarator : public Declarator
{
public:
    FunctionDeclarator(const std::u32string& name_, otava::ast::Node* node_, FunctionKind kind_, FunctionQualifiers qualifiers_, Scope* scope_);
    FunctionKind GetFunctionKind() const { return kind; }
    FunctionQualifiers GetFunctionQualifiers() const { return qualifiers; }
    void AddQualifier(FunctionQualifiers qualifier);
    void AddParameterDeclaration(Declaration&& parameterDeclaration);
    const std::vector<Declaration>& ParameterDeclarations() const { return parameterDeclarations; }
    Scope* GetScope() const { return scope; }
    void SetTemplateArgs(const std::vector<TypeSymbol*>& templateArgs_);
    const std::vector<TypeSymbol*>& TemplateArgs() const { return templateArgs; }
private:
    FunctionKind kind;
    FunctionQualifiers qualifiers;
    std::vector<Declaration> parameterDeclarations;
    std::vector<TypeSymbol*> templateArgs;
    Scope* scope;
};

class ArrayDeclarator : public Declarator
{
public:
    ArrayDeclarator(const std::u32string& name_, otava::ast::Node* node_, std::int64_t size_);
    std::int64_t Size() const { return size; }
private:
    std::int64_t size;
};

class Context;

std::unique_ptr<DeclarationList> ProcessInitDeclaratorList(TypeSymbol* baseType, otava::ast::Node* declarationNode, otava::ast::Node* initDeclaratorList, 
    DeclarationFlags flags, Context* context);
std::unique_ptr<DeclarationList> ProcessMemberDeclaratorList(TypeSymbol* baseType, otava::ast::Node* declarationNode, otava::ast::Node* memberDeclaratorList, DeclarationFlags flags, Context* context);
Declaration ProcessDeclarator(TypeSymbol* baseType, otava::ast::Node* declarator, otava::ast::Node* declarationNode, DeclarationFlags flags, FunctionQualifiers qualifiers, 
    Context* context);

} // namespace otava::symbols
