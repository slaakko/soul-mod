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
    inline TemplateMatchInfo() : kind(TemplateMatchKind::straight), matchValue(0) {}
    inline TemplateMatchInfo(TemplateMatchKind kind_, int matchValue_) : kind(kind_), matchValue(matchValue_) {}
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
    bool IsValidDeclarationScope(ScopeKind scopeKind) const override;
    Symbol* GetSingleSymbol() override;
    void AddClass(ClassTypeSymbol* classTypeSymbol);
    ClassTypeSymbol* GetClass(int arity) const;
    inline const std::vector<ClassTypeSymbol*>& Classes() const { return classes; }
    void AddForwardDeclaration(ForwardClassDeclarationSymbol* forwardDeclaration);
    ForwardClassDeclarationSymbol* GetForwardDeclaration(int arity) const;
    inline const std::vector<ForwardClassDeclarationSymbol*>& ForwardDeclarations() const { return forwardDeclarations; }
    std::expected<ClassTypeSymbol*, int> GetBestMatchingClass(const std::vector<Symbol*>& templateArgs, TemplateMatchInfo& matchInfo, Context* context) const;
    std::expected<bool, int> Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    std::expected<bool, int> Resolve(SymbolTable& symbolTable, Context* context) override;
    void Accept(Visitor& visitor) override;
    void Merge(ClassGroupSymbol* that);
private:
    std::vector<ClassTypeSymbol*> classes;
    std::vector<ForwardClassDeclarationSymbol*> forwardDeclarations;
    std::vector<util::uuid> classIds;
};

} // namespace otava::symbols
