// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul_expected.rex.algorithm;

import soul_expected.rex.symbol;

namespace soul_expected::rex::algorithm {

std::vector<soul_expected::rex::nfa::NfaState*> EpsilonClosure(const std::vector<soul_expected::rex::nfa::NfaState*>& states)
{
    std::vector<soul_expected::rex::nfa::NfaState*> stack;
    for (soul_expected::rex::nfa::NfaState* state : states)
    {
        stack.push_back(state);
    }
    std::vector<soul_expected::rex::nfa::NfaState*> epsilonClosure = states;
    while (!stack.empty())
    {
        soul_expected::rex::nfa::NfaState* s = stack.back();
        stack.pop_back();
        std::vector<soul_expected::rex::nfa::NfaState*> u = s->Next(soul_expected::rex::symbol::eps);
        for (soul_expected::rex::nfa::NfaState* v : u)
        {
            if (std::find(epsilonClosure.cbegin(), epsilonClosure.cend(), v) == epsilonClosure.cend())
            {
                epsilonClosure.push_back(v);
                stack.push_back(v);
            }
        }
    }
    return epsilonClosure;
}

std::vector<soul_expected::rex::nfa::NfaState*> EpsilonClosure(soul_expected::rex::nfa::NfaState* state)
{
    std::vector<soul_expected::rex::nfa::NfaState*> states(1, state);
    return EpsilonClosure(states);
}

std::vector<soul_expected::rex::nfa::NfaState*> Move(const std::vector<soul_expected::rex::nfa::NfaState*>& states, char32_t c)
{
    std::vector<soul_expected::rex::nfa::NfaState*> next;
    for (soul_expected::rex::nfa::NfaState* state : states)
    {
        std::vector<soul_expected::rex::nfa::NfaState*> n = state->Next(c);
        for (soul_expected::rex::nfa::NfaState* s : n)
        {
            if (std::find(next.cbegin(), next.cend(), s) == next.cend())
            {
                next.push_back(s);
            }
        }
    }
    return next;
}

bool Match(soul_expected::rex::nfa::Nfa& nfa, const std::u32string& s)
{
    std::vector<soul_expected::rex::nfa::NfaState*> states = EpsilonClosure(nfa.Start());
    for (char32_t c : s)
    {
        states = EpsilonClosure(Move(states, c));
    }
    for (soul_expected::rex::nfa::NfaState* state : states)
    {
        if (state->Accept()) return true;
    }
    return false;
}

} // namespace soul_expected::rex::algorithm
