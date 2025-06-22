// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.alias.type.symbol;

import std;
import otava.ast;
import otava.symbols.type.symbol;

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
    void SetReferredType(TypeSymbol* referredType_) { referredType = referredType_; }
    TypeSymbol* ReferredType() const { return referredType; }
    TypeSymbol* DirectType(Context* context) override;
    std::string SymbolKindStr() const override { return "alias type symbol"; }
    std::string SymbolDocKindStr() const override { return "alias_type"; }
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
    void Accept(Visitor& visitor) override;
    otava::intermediate::Type* IrType(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context) override;
    AliasGroupSymbol* Group() const { return group; }
    void SetGroup(AliasGroupSymbol* group_) { group = group_; }
private:
    TypeSymbol* referredType;
    util::uuid referredTypeId;
    AliasGroupSymbol* group;
};

void ProcessAliasDeclaration(otava::ast::Node* aliasDeclarationNode, Context* context);

struct AliasTypeLess
{
    bool operator()(AliasTypeSymbol* left, AliasTypeSymbol* right) const;
};

void AddTemporaryTypeAlias(otava::ast::Node* aliasDeclarationNode, Context* context);

void RemoveTemporaryAliasTypeSymbols(Context* context);

} // namespace otava::symbols
