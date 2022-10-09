// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.classes;

import std.core;
import otava.symbols.scope;
import otava.symbols.type.symbol;
import otava.ast.node;
import otava.ast.statement;

export namespace otava::symbols {

class Context;

using RecordedParseFn = void (*)(otava::ast::CompoundStatementNode* compoundStatementNode, Context* context);

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
    const std::vector<VariableSymbol*>& MemberVariables() const { return memberVariables; }
    void AddSymbol(Symbol* symbol, const soul::ast::SourcePos& sourcePos, Context* context) override;
    otava::intermediate::Type* IrType(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context) override;
private:
    std::vector<TypeSymbol*> baseClasses;
    std::vector<util::uuid> baseClassIds;
    ClassKind classKind;
    std::vector<TypeSymbol*> derivedClasses;
    int level;
    std::vector<VariableSymbol*> memberVariables;
    std::vector<FunctionSymbol*> memberFunctions;
    void* irType;
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

void BeginClass(otava::ast::Node* node, otava::symbols::Context* context);
void EndClass(otava::ast::Node* node, otava::symbols::Context* context);
void AddForwardClassDeclaration(otava::ast::Node* node, otava::symbols::Context* context);
void SetCurrentAccess(otava::ast::Node* node, otava::symbols::Context* context);
void GetClassAttributes(otava::ast::Node* node, std::u32string& name, otava::symbols::ClassKind& kind);
void ParseInlineMemberFunctions(otava::ast::Node* classSpecifierNode, ClassTypeSymbol* classTypeSymbol, otava::symbols::Context* context);
void ThrowMemberDeclarationParsingError(const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context);
void ThrowStatementParsingError(const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context);

struct ClassLess
{
    bool operator()(ClassTypeSymbol* left, ClassTypeSymbol* right) const;
};

} // namespace otava::symbols
