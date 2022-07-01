// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.symbols.alias.type.symbol;

import std.core;
import soul.cpp20.ast;
import soul.cpp20.symbols.type.symbol;

export namespace soul::cpp20::symbols {

class AliasTypeSymbol : public TypeSymbol
{
public:
    AliasTypeSymbol(const std::u32string& name_, TypeSymbol* referredType_);
    virtual int Arity() const { return 0;  }
    TypeSymbol* ReferredType() const { return referredType; }
    std::string SymbolKindStr() const override { return "alias type symbol"; }
private:
    TypeSymbol* referredType;
};

class Context;

void ProcessAliasDeclaration(soul::cpp20::ast::Node* aliasDeclarationNode, Context* context);

} // namespace soul::cpp20::symbols
