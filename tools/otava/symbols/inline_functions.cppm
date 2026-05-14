// =================================
// Copyright (c) 2026 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.inline_functions;

import std;
import soul.ast.span;
import otava.symbols.symbol;

export namespace otava::symbols {

class FunctionSymbol;

class InlineFunctionRepository
{
public:
    InlineFunctionRepository();
    FunctionSymbol* GetInlineFunction(FunctionSymbol* fn) const noexcept;
    void AddInlineFunction(FunctionSymbol* fn, FunctionSymbol* inlineFn);
private:
    std::map<FunctionSymbol*, FunctionSymbol*> inlineFunctionMap;
};

FunctionSymbol* InstantiateInlineFunction(FunctionSymbol* fn, const soul::ast::FullSpan& fullSpan, Context* context);

} // namespace otava::symbols
