// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.class_group.symbol;

import std.core;
import otava.symbols.type.symbol;

export namespace otava::symbols {

class ClassTypeSymbol;
class ForwardClassDeclarationSymbol;

enum class TemplateMatchKind
{
    straight, partialSpecialization, explicitSpecialization
};

struct TemplateMatchInfo
{
    TemplateMatchInfo() : kind(TemplateMatchKind::straight), matchValue(0) {}
    TemplateMatchInfo(TemplateMatchKind kind_, int matchValue_) : kind(kind_), matchValue(matchValue_) {}
    TemplateMatchKind kind;
    int matchValue;
    std::map<TemplateParameterSymbol*, TypeSymbol*, TemplateParamLess> templateParameterMap;
    std::vector<Symbol*> templateArgs;
};

class ClassGroupSymbol : public TypeSymbol
{
public:
    ClassGroupSymbol(const std::u32string& name_);
    std::string SymbolKindStr() const override { return "class group symbol"; }
    std::string SymbolDocKindStr() const override { return "class_group"; }
    bool IsValidDeclarationScope(ScopeKind scopeKind) const override;
    Symbol* GetSingleSymbol() override;
    void AddClass(ClassTypeSymbol* classTypeSymbol);
    ClassTypeSymbol* GetClass(int arity) const;
    const std::vector<ClassTypeSymbol*>& Classes() const { return classes; }
    void AddForwardDeclaration(ForwardClassDeclarationSymbol* forwardDeclaration);
    ForwardClassDeclarationSymbol* GetForwardDeclaration(int arity) const;
    const std::vector<ForwardClassDeclarationSymbol*>& ForwardDeclarations() const { return forwardDeclarations; }
    ClassTypeSymbol* GetBestMatchingClass(const std::vector<Symbol*>& templateArgs, TemplateMatchInfo& matchInfo, Context* context) const;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
    void Accept(Visitor& visitor) override;
    void Merge(ClassGroupSymbol* that);
private:
    std::vector<ClassTypeSymbol*> classes;
    std::vector<ForwardClassDeclarationSymbol*> forwardDeclarations;
    std::vector<util::uuid> classIds;
};

} // namespace otava::symbols
