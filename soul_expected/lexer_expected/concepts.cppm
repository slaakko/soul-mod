// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul_expected.lexer.concepts;

import std;
import soul_expected.lexer.base;

export namespace soul_expected::lexer {

template<typename T>
concept LexicalIterator = requires(T it, std::int64_t pos)
{
    *it;                                        // returns current token id
    ++it;                                       // advances the lexer iterator ('eats' current token)
    it.GetPos();                                // returns current lexer position
    it.SetPos(pos);                             // backtracts to a saved lexer position
};

template<typename Machine, typename Char>
concept FiniteStateMachine = requires(Machine machine, Char chr, LexerBase<Char>&lexer)
{
    machine.NextState(int{}, chr, lexer);  // returns next state id when given current state id, current input char and lexer ref
};

template<typename Stack>
concept RuleStack = requires(Stack stack, int ruleId)
{
    stack.PushRule(ruleId);
    stack.PopRule();
};

} // namespace soul_expected::lexer
