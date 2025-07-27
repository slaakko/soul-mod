// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul_expected.rex.context;

namespace soul_expected::rex::context {

Context::Context() : any(), epsilon(soul_expected::rex::symbol::eps)
{
}

Context::~Context()
{
    for (soul_expected::rex::nfa::NfaState* state : nfaStates)
    {
        delete state;
    }
    for (soul_expected::rex::symbol::Symbol* symbol : symbols)
    {
        delete symbol;
    }
}

soul_expected::rex::nfa::NfaState* Context::MakeNfaState()
{
    soul_expected::rex::nfa::NfaState* state = new soul_expected::rex::nfa::NfaState();
    nfaStates.push_back(state);
    return state;
}

soul_expected::rex::symbol::Symbol* Context::MakeChar(char32_t c)
{
    std::map<char32_t, soul_expected::rex::symbol::Symbol*>::iterator it = charSymbols.find(c);
    if (it != charSymbols.end())
    {
        return it->second;
    }
    else
    {
        soul_expected::rex::symbol::Symbol* symbol = new soul_expected::rex::symbol::Char(c);
        symbols.push_back(symbol);
        charSymbols[c] = symbol;
        return symbol;
    }
}

soul_expected::rex::symbol::Symbol* Context::MakeRange(char32_t start, char32_t end)
{
    soul_expected::rex::symbol::Range range(start, end);
    std::map<soul_expected::rex::symbol::Range, soul_expected::rex::symbol::Symbol*>::iterator it = rangeSymbols.find(range);
    if (it != rangeSymbols.end())
    {
        return it->second;
    }
    else
    {
        soul_expected::rex::symbol::Symbol* symbol = new soul_expected::rex::symbol::Range(start, end);
        symbols.push_back(symbol);
        rangeSymbols[range] = symbol;
        return symbol;
    }
}

soul_expected::rex::symbol::Class* Context::MakeClass()
{
    soul_expected::rex::symbol::Class* cls = new soul_expected::rex::symbol::Class();
    symbols.push_back(cls);
    return cls;
}

} // namespace soul_expected::rex::context
