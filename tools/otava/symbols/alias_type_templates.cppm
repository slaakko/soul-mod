// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.alias.type.templates;

import otava.symbols.alias.type.symbol;
import std;
import otava.ast.templates;

export namespace otava::symbols {

class AliasTypeTemplateSpecializationSymbol : public AliasTypeSymbol
{
public:
    AliasTypeTemplateSpecializationSymbol(const std::u32string& name_);
    inline bool Instantiated() const { return instantiated; }
    inline void SetInstantiated() { instantiated = true; }
    std::string SymbolKindStr() const override { return "alias type specialization symbol"; }
    std::string SymbolDocKindStr() const override { return "alias_type_specialization"; }
    inline TypeSymbol* AliasTypeTemplate() const { return aliasTypeTemplate; }
    void SetAliasTypeTemplate(TypeSymbol* aliasTypeTemplate_);
    inline const std::vector<Symbol*>& TemplateArguments() const { return templateArguments; }
    void AddTemplateArgument(Symbol* templateArgument);
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
    void Accept(Visitor& visitor) override;
private:
    TypeSymbol* aliasTypeTemplate;
    std::vector<Symbol*> templateArguments;
    std::vector<util::uuid> ids;
    bool instantiated;
};

TypeSymbol* InstantiateAliasTypeSymbol(TypeSymbol* aliasTypeSymbol, const std::vector<Symbol*>& templateArgs, otava::ast::TemplateIdNode* node, Context* context);

} // namespace otava::symbols
