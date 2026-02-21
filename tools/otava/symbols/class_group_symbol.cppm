// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.class_group.symbol;

import std;
import otava.symbols.type.symbol;
import otava.symbols.symbol;
import otava.symbols.template_param_compare;

export namespace otava::symbols {

class ClassTypeSymbol;
class ForwardClassDeclarationSymbol;

enum class TemplateMatchKind
{
    straight, partialSpecialization, explicitSpecialization
};

struct TemplateMatchInfo
{
    inline TemplateMatchInfo() noexcept : kind(TemplateMatchKind::straight), matchValue(0) {}
    inline TemplateMatchInfo(TemplateMatchKind kind_, int matchValue_) noexcept : kind(kind_), matchValue(matchValue_) {}
    TemplateMatchKind kind;
    int matchValue;
    std::map<TemplateParameterSymbol*, TypeSymbol*, TemplateParamLess> templateParameterMap;
    std::vector<Symbol*> templateArgs;
};

class ClassGroupSymbol : public Symbol
{
public:
    ClassGroupSymbol(const std::u32string& name_);
    std::string SymbolKindStr() const override { return "class group symbol"; }
    std::string SymbolDocKindStr() const override { return "class_group"; }
    bool IsValidDeclarationScope(ScopeKind scopeKind) const noexcept override;
    Symbol* GetSingleSymbol() noexcept override;
    void AddClass(ClassTypeSymbol* classTypeSymbol);
    ClassTypeSymbol* GetClass(int arity) const noexcept;
    inline const std::vector<ClassTypeSymbol*>& Classes() const noexcept { return classes; }
    void AddForwardDeclaration(ForwardClassDeclarationSymbol* forwardDeclaration);
    ForwardClassDeclarationSymbol* GetForwardDeclaration(int arity) const noexcept;
    inline const std::vector<ForwardClassDeclarationSymbol*>& ForwardDeclarations() const noexcept { return forwardDeclarations; }
    ClassTypeSymbol* GetBestMatchingClass(const std::vector<Symbol*>& templateArgs, TemplateMatchInfo& matchInfo, Context* context) const noexcept;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable, Context* context) override;
    void Accept(Visitor& visitor) override;
    void Merge(ClassGroupSymbol* that);
private:
    std::vector<ClassTypeSymbol*> classes;
    std::vector<ForwardClassDeclarationSymbol*> forwardDeclarations;
    std::vector<util::uuid> classIds;
};

} // namespace otava::symbols
