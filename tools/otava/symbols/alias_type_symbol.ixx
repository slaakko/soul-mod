// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.alias.type.symbol;

import std.core;
import otava.ast;
import otava.symbols.type.symbol;

export namespace otava::symbols {

class AliasTypeSymbol : public TypeSymbol
{
public:
    AliasTypeSymbol(const std::u32string& name_);
    AliasTypeSymbol(const std::u32string& name_, TypeSymbol* referredType_);
    virtual int Arity() const { return 0;  }
    TypeSymbol* ReferredType() const { return referredType; }
    std::string SymbolKindStr() const override { return "alias type symbol"; }
    std::string SymbolDocKindStr() const override { return "alias_type"; }
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
    void Accept(Visitor& visitor) override;
private:
    TypeSymbol* referredType;
    util::uuid referredTypeId;
};

class Context;

void ProcessAliasDeclaration(otava::ast::Node* aliasDeclarationNode, Context* context);

struct AliasTypeLess
{
    bool operator()(AliasTypeSymbol* left, AliasTypeSymbol* right) const;
};

} // namespace otava::symbols
