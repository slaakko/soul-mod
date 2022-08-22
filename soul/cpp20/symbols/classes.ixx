// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.symbols.classes;

import soul.cpp20.symbols.type.symbol;
import soul.cpp20.ast.node;

export namespace soul::cpp20::symbols {

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
    virtual int Arity() const { return 0; }
    ClassKind GetClassKind() const { return classKind; }
    void SetClassKind(ClassKind classKind_) { classKind = classKind_; }
    std::string SymbolKindStr() const override { return "class type symbol"; }
    std::string SymbolDocKindStr() const override { return "class"; }
    bool IsValidDeclarationScope(ScopeKind scopeKind) const override;
    TemplateDeclarationSymbol* ParentTemplateDeclaration();
    const std::vector<Symbol*>& BaseClasses() const { return baseClasses; }
    void AddBaseClass(Symbol* baseClass, const soul::ast::SourcePos& sourcePos, Context* context);
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
private:
    std::vector<Symbol*> baseClasses;
    std::vector<util::uuid> baseClassIds;
    ClassKind classKind;
};

void BeginClass(soul::cpp20::ast::Node* node, soul::cpp20::symbols::Context* context);
void EndClass(soul::cpp20::symbols::Context* context);

struct ClassLess
{
    bool operator()(ClassTypeSymbol* left, ClassTypeSymbol* right) const;
};

} // namespace soul::cpp20::symbols
