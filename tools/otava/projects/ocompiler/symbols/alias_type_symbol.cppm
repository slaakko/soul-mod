// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.alias.type.symbol;

import std;
import otava.ast;
import otava.symbols.type.symbol;
import otava.symbols.templates;
import otava.symbols.emitter;

export namespace otava::symbols {

class AliasGroupSymbol;

class AliasTypeSymbol : public TypeSymbol
{
public:
    AliasTypeSymbol(const std::u32string& name_);
    AliasTypeSymbol(const std::u32string& name_, SymbolKind kind_);
    AliasTypeSymbol(const std::u32string& name_, TypeSymbol* referredType_);
    TemplateDeclarationSymbol* ParentTemplateDeclaration();
    int Arity();
    inline void SetReferredType(TypeSymbol* referredType_) { referredType = referredType_; }
    TypeSymbol* ReferredType() const { return referredType; }
    std::expected<TypeSymbol*, int> DirectType(Context* context) override;
    std::string SymbolKindStr() const override { return "alias type symbol"; }
    std::string SymbolDocKindStr() const override { return "alias_type"; }
    std::expected<bool, int> Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    std::expected<bool, int> Resolve(SymbolTable& symbolTable, Context* context) override;
    void Accept(Visitor& visitor) override;
    bool IsExportSymbol(Context* context) const override;
    bool IsExportMapSymbol(Context* context) const override;
    std::expected<otava::intermediate::Type*, int> IrType(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context) override;
    inline AliasGroupSymbol* Group() const { return group; }
    inline void SetGroup(AliasGroupSymbol* group_) { group = group_; }
    std::expected<soul::xml::Element*, int> ToXml() const override;
private:
    TypeSymbol* referredType;
    util::uuid referredTypeId;
    AliasGroupSymbol* group;
};

std::expected<bool, int> ProcessAliasDeclaration(otava::ast::Node* aliasDeclarationNode, Context* context);

struct AliasTypeLess
{
    bool operator()(AliasTypeSymbol* left, AliasTypeSymbol* right) const;
};

std::expected<bool, int> AddTemporaryTypeAlias(otava::ast::Node* aliasDeclarationNode, Context* context);

std::expected<bool, int> RemoveTemporaryAliasTypeSymbols(Context* context);

} // namespace otava::symbols
