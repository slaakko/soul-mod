// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.symbols.classes;

import std.core;
import soul.cpp20.symbols.scope;
import soul.cpp20.symbols.type.symbol;
import soul.cpp20.ast.node;
import soul.cpp20.ast.statement;

export namespace soul::cpp20::symbols {

class Context;

using RecordedParseFn = void (*)(soul::cpp20::ast::CompoundStatementNode* compoundStatementNode, Context* context);

void SetRecordedParseFn(RecordedParseFn fn);

class TemplateDeclarationSymbol;
class TemplateParameterSymbol;

enum class ClassKind
{
    class_, struct_, union_
};

class ClassTypeSymbol : public TypeSymbol
{
public:
    ClassTypeSymbol(const std::u32string& name_);
    int Arity();
    ClassKind GetClassKind() const { return classKind; }
    void SetClassKind(ClassKind classKind_) { classKind = classKind_; }
    std::string SymbolKindStr() const override { return "class type symbol"; }
    std::string SymbolDocKindStr() const override { return "class"; }
    bool IsValidDeclarationScope(ScopeKind scopeKind) const override;
    TemplateDeclarationSymbol* ParentTemplateDeclaration();
    const std::vector<TypeSymbol*>& BaseClasses() const { return baseClasses; }
    void AddBaseClass(TypeSymbol* baseClass, const soul::ast::SourcePos& sourcePos, Context* context);
    const std::vector<TypeSymbol*>& DerivedClasses() const { return derivedClasses; }
    void AddDerivedClass(TypeSymbol* derivedClass);
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
    int Level() const { return level; }
    void SetLevel(int level_) { level = level_; }
private:
    std::vector<TypeSymbol*> baseClasses;
    std::vector<util::uuid> baseClassIds;
    ClassKind classKind;
    std::vector<TypeSymbol*> derivedClasses;
    int level;
};

class ForwardClassDeclarationSymbol : public TypeSymbol
{
public:
    ForwardClassDeclarationSymbol(const std::u32string& name_);
    int Arity();
    ClassKind GetClassKind() const { return classKind; }
    void SetClassKind(ClassKind classKind_) { classKind = classKind_; }
    void SetClassTypeSymbol(ClassTypeSymbol* classTypeSymbol_) { classTypeSymbol = classTypeSymbol_; }
    ClassTypeSymbol* GetClassTypeSymbol() const { return classTypeSymbol; }
    std::string SymbolKindStr() const override { return "forward class declaration symbol"; }
    std::string SymbolDocKindStr() const override { return "forward_class"; }
    bool IsValidDeclarationScope(ScopeKind scopeKind) const override;
    TemplateDeclarationSymbol* ParentTemplateDeclaration();
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
private:
    ClassKind classKind;
    ClassTypeSymbol* classTypeSymbol;
    util::uuid classTypeSymbolId;
};

void BeginClass(soul::cpp20::ast::Node* node, soul::cpp20::symbols::Context* context);
void EndClass(soul::cpp20::ast::Node* node, soul::cpp20::symbols::Context* context);
void AddForwardClassDeclaration(soul::cpp20::ast::Node* node, soul::cpp20::symbols::Context* context);
void SetCurrentAccess(soul::cpp20::ast::Node* node, soul::cpp20::symbols::Context* context);
void GetClassAttributes(soul::cpp20::ast::Node* node, std::u32string& name, soul::cpp20::symbols::ClassKind& kind);
void ParseInlineMemberFunctions(soul::cpp20::ast::Node* classSpecifierNode, ClassTypeSymbol* classTypeSymbol, soul::cpp20::symbols::Context* context);
void ThrowMemberDeclarationExpected(const soul::ast::SourcePos& sourcePos, soul::cpp20::symbols::Context* context);
void ThrowStatementExpected(const soul::ast::SourcePos& sourcePos, soul::cpp20::symbols::Context* context);

struct ClassLess
{
    bool operator()(ClassTypeSymbol* left, ClassTypeSymbol* right) const;
};

} // namespace soul::cpp20::symbols
