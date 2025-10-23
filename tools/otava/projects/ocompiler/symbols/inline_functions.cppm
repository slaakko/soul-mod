// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.inline_functions;

import std;
import soul.ast.source.pos;
import otava.symbols.symbol;

export namespace otava::symbols {

class FunctionSymbol;

class InlineFunctionRepository
{
public:
    InlineFunctionRepository();
    FunctionSymbol* GetInlineFunction(FunctionSymbol* fn) const;
    void AddInlineFunction(FunctionSymbol* fn, FunctionSymbol* inlineFn);
private:
    std::map<FunctionSymbol*, FunctionSymbol*> inlineFunctionMap;
};

std::expected<FunctionSymbol*, int> InstantiateInlineFunction(FunctionSymbol* fn, const soul::ast::SourcePos& sourcePos, Context* context);

} // namespace otava::symbols
