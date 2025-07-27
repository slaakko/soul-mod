// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul_expected.rex.algorithm;

import std;
import soul_expected.rex.nfa;

export namespace soul_expected::rex::algorithm {

std::vector<soul_expected::rex::nfa::NfaState*> EpsilonClosure(const std::vector<soul_expected::rex::nfa::NfaState*>& states);
std::vector<soul_expected::rex::nfa::NfaState*> EpsilonClosure(soul_expected::rex::nfa::NfaState* state);
std::vector<soul_expected::rex::nfa::NfaState*> Move(const std::vector<soul_expected::rex::nfa::NfaState*>& states, char32_t c);
bool Match(soul_expected::rex::nfa::Nfa& nfa, const std::u32string& s);

} // namespace soul_expected::rex::algorithm
