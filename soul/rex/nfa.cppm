// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.rex.nfa;

import std;
import soul.rex.symbol;

export namespace soul::rex::context {

class Context;

} //  namespace soul::rex::context

export namespace soul::rex::nfa {

class NfaState;

class NfaEdge
{
public:
    NfaEdge(soul::rex::symbol::Symbol* symbol_, NfaState* next_);
    inline soul::rex::symbol::Symbol* GetSymbol() const { return symbol; }
    inline NfaState* Next() const { return next; }
private:
    soul::rex::symbol::Symbol* symbol;
    NfaState* next;
};

class NfaState
{
public:
    NfaState();
    inline bool Accept() const { return accept; }
    inline void SetAccept(bool accept_) { accept = accept_; }
    inline const std::vector<NfaEdge>& Edges() const { return edges; }
    void SetEdges(const std::vector<NfaEdge>& edges_);
    void AddEdge(const NfaEdge& edge);
    std::vector<NfaState*> Next(char32_t c) const;
private:
    bool accept;
    std::vector<NfaEdge> edges;
};

class Nfa
{
public:
    Nfa();
    Nfa(NfaState* start_, NfaState* end_);
    inline NfaState* Start() const { return start; }
    inline void SetStart(NfaState* start_) { start = start_; }
    inline NfaState* End() const { return end; }
    inline void SetEnd(NfaState* end_) { end = end_; }
private:
    NfaState* start;
    NfaState* end;
};

Nfa MakeNfa(soul::rex::context::Context& context, soul::rex::symbol::Symbol* symbol);
Nfa Cat(const Nfa& left, const Nfa& right);
Nfa Alt(soul::rex::context::Context& context, const Nfa& left, const Nfa& right);
Nfa Kleene(soul::rex::context::Context& context, const Nfa& nfa);
Nfa Pos(soul::rex::context::Context& context, const Nfa& nfa);
Nfa Opt(soul::rex::context::Context& context, const Nfa& nfa);

} // namespace soul::rex::nfa
