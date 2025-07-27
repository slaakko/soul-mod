// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul_expected.rex.context;

import std;
import soul_expected.rex.nfa;
import soul_expected.rex.symbol;

export namespace soul_expected::rex::context {

class Context
{
public:
    Context();
    ~Context();
    soul_expected::rex::nfa::NfaState* MakeNfaState();
    soul_expected::rex::symbol::Symbol* MakeChar(char32_t c);
    soul_expected::rex::symbol::Symbol* MakeRange(char32_t start, char32_t end);
    soul_expected::rex::symbol::Symbol* MakeAny() { return &any; }
    soul_expected::rex::symbol::Symbol* MakeEpsilon() { return &epsilon; }
    soul_expected::rex::symbol::Class* MakeClass();
private:
    std::vector<soul_expected::rex::nfa::NfaState*> nfaStates;
    std::vector<soul_expected::rex::symbol::Symbol*> symbols;
    soul_expected::rex::symbol::Any any;
    soul_expected::rex::symbol::Char epsilon;
    std::map<char32_t, soul_expected::rex::symbol::Symbol*> charSymbols;
    std::map<soul_expected::rex::symbol::Range, soul_expected::rex::symbol::Symbol*> rangeSymbols;
};

} // namespace soul_expected::rex::context
