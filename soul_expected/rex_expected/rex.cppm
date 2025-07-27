// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul_expected.rex;

export import soul_expected.rex.token;
export import soul_expected.rex.context;
export import soul_expected.rex.nfa;
export import soul_expected.rex.lexer;
export import soul_expected.rex.parser;
export import soul_expected.rex.symbol;
export import soul_expected.rex.algorithm;
export import soul_expected.rex.match;

export namespace soul_expected::rex {

using Context = soul_expected::rex::context::Context;
using Nfa = soul_expected::rex::nfa::Nfa;

} // namespace soul_expected::rex
