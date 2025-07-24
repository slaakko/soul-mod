// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul_expected.ast.re;

import std;
import util_expected;
import soul_expected.ast.slg;

export namespace soul_expected::ast::re {

class Visitor;
class LexerContext;
using util::CodeFormatter;

const char32_t eps = '\0';

class Class;

enum class SymbolKind
{
    charSymbol, anySymbol, rangeSymbol, classSymbol
};

class Symbol
{
public:
    Symbol(SymbolKind kind_);
    virtual ~Symbol();
    SymbolKind Kind() const { return kind; }
    virtual bool Match(char32_t c) = 0;
    virtual void Accept(Visitor& visitor) = 0;
    virtual std::expected<bool, int> Print(CodeFormatter& formatter) = 0;
    void SetName(const std::string& name_);
    const std::string& Name() const { return name; }
    bool Contained() const { return contained; }
    void SetContained() { if (!dontSetContained) contained = true; }
    void DontSetContained() { dontSetContained = true; }
private:
    SymbolKind kind;
    std::string name;
    bool contained;
    bool dontSetContained;
};

class CharSymbol : public Symbol
{
public:
    CharSymbol(char32_t chr_);
    bool Match(char32_t c) override;
    void Accept(Visitor& visitor) override;
    std::expected<bool, int> Print(CodeFormatter& formatter) override;
    char32_t Chr() const { return chr; }
    int Error() const { return error; }
    bool Valid() const { return error == 0; }
    explicit operator bool() const { return Valid(); }
private:
    char32_t chr;
    int error;
};

class Any : public Symbol
{
public:
    Any();
    bool Match(char32_t c) override;
    void Accept(Visitor& visitor) override;
    std::expected<bool, int> Print(CodeFormatter& formatter) override;
};

class Range : public Symbol
{
public:
    Range();
    Range(char32_t start_, char32_t end_);
    bool Match(char32_t c) override;
    void Accept(Visitor& visitor) override;
    std::expected<bool, int> Print(CodeFormatter& formatter) override;
    bool IsEmpty() const { return start > end; }
    char32_t Start() const { return start; }
    char32_t End() const { return end; }
    int Error() const { return error; }
    bool Valid() const { return error == 0; }
    explicit operator bool() const { return Valid(); }
private:
    char32_t start;
    char32_t end;
    int error;
};

inline bool operator==(const Range& left, const Range& right)
{
    return left.Start() == right.Start() && left.End() == right.End();
}

inline bool operator<(const Range& left, const Range& right)
{
    if (left.Start() < right.Start()) return true;
    if (left.Start() > right.Start()) return false;
    return left.End() < right.End();
}

bool Intersect(const Range& left, const Range& right);

Range operator&(const Range& left, const Range& right);

std::vector<Range> operator-(const Range& left, const Range& right);

std::vector<Range> operator~(const Range& that);

class Class : public Symbol
{
public:
    Class(int index_);
    bool Match(char32_t c) override;
    void Accept(Visitor& visitor) override;
    std::expected<bool, int> Print(CodeFormatter& formatter) override;
    bool Inverse() const { return inverse; }
    void SetInverse() { inverse = true; }
    const std::vector<Symbol*>& Symbols() const { return symbols; }
    void AddSymbol(Symbol* symbol);
    void AddChar(char32_t c);
    int Index() const { return index; }
    void SetIndex(int index_);
    const std::vector<char32_t>& Chars() const { return chars; }
    std::expected<Class*, int> MakeCanonical(LexerContext& lexerContext);
    void MakeMinimal(LexerContext& lexerContext);
    void MakeInverse(LexerContext& lexerContext);
    Class* Clone();
    bool IsEmpty() const { return symbols.empty(); }
    const std::list<Range>& Ranges() const { return ranges; }
    std::list<Range>& Ranges() { return ranges; }
private:
    int index;
    bool inverse;
    std::vector<Symbol*> symbols;
    std::vector<char32_t> chars;
    std::list<Range> ranges;
};

bool operator==(const Class& left, const Class& right);

bool Intersect(const Class& left, const Class& right);

std::expected<Class*, int> MakeIntertersection(const Class& left, const Class& right, LexerContext& lexerContext);

std::expected<Class*, int> MakeDifference(const Class& left, const Class& right, LexerContext& lexerContext);

class NfaState;

class NfaEdge
{
public:
    NfaEdge(Symbol* symbol_, NfaState* next_);
    Symbol* GetSymbol() const { return symbol; }
    NfaState* Next() const { return next; }
    std::expected<bool, int> Print(CodeFormatter& formatter);
private:
    Symbol* symbol;
    NfaState* next;
};

class NfaState
{
public:
    NfaState(int id_, int ruleIndex_);
    int Id() const { return id; }
    int RuleIndex() const { return ruleIndex; }
    void SetRuleIndex(int ruleIndex_) { ruleIndex = ruleIndex_; }
    bool Accept() const { return accept; }
    void SetAccept(bool accept_) { accept = accept_; }
    const std::vector<NfaEdge>& Edges() const { return edges; }
    void SetEdges(const std::vector<NfaEdge>& edges_);
    void AddEdge(const NfaEdge& edge);
    void AddPrev(NfaState* prev_);
    std::vector<NfaState*> Next(char32_t c) const;
    std::expected<bool, int> Print(CodeFormatter& formatter);
private:
    int id;
    int ruleIndex;
    bool accept;
    std::vector<NfaEdge> edges;
    std::set<NfaState*> prev;
};

class Nfa
{
public:
    Nfa();
    Nfa(NfaState* start_, NfaState* end_);
    NfaState* Start() const { return start; }
    void SetStart(NfaState* start_) { start = start_; }
    NfaState* End() const { return end; }
    void SetEnd(NfaState* end_) { end = end_; }
private:
    NfaState* start;
    NfaState* end;
};

Nfa MakeNfa(LexerContext& lexerContext, Symbol* symbol);
Nfa Cat(const Nfa& left, const Nfa& right);
Nfa Alt(LexerContext& lexerContext, const Nfa& left, const Nfa& right);
Nfa Kleene(LexerContext& lexerContext, const Nfa& nfa);
Nfa Pos(LexerContext& lexerContext, const Nfa& nfa);
Nfa Opt(LexerContext& lexerContext, const Nfa& nfa);

class DfaState
{
public:
    DfaState(int id_, const std::vector<int>& nfaStateIds_);
    int Id() const { return id; }
    bool IsMarked() const { return marked; }
    void Mark() { marked = true; }
    bool Accept() const { return accept; }
    void SetAccept(bool accept_) { accept = accept_; }
    int RuleIndex() const { return ruleIndex; }
    void SetRuleIndex(int index) { ruleIndex = index; }
    const std::vector<int>& NfaStateIds() const { return nfaStateIds; }
    void AddNext(DfaState* next);
    DfaState* Next(int i) const;
    std::expected<bool, int> Print(LexerContext& context, CodeFormatter& formatter);
private:
    int id;
    std::vector<int> nfaStateIds;
    std::vector<DfaState*> next;
    bool marked;
    bool accept;
    int ruleIndex;
};

class Dfa
{
public:
    void AddState(DfaState* state);
    const std::vector<DfaState*>& States() const { return states; }
    std::expected<bool, int> Finalize(LexerContext& lexerContext);
    std::expected<bool, int>  Print(LexerContext& lexerContext, CodeFormatter& formatter);
private:
    std::vector<DfaState*> states;
};

std::expected<std::vector<int>, int> EpsilonClosure(LexerContext& lexerContext, const std::vector<int>& stateIds);
std::expected<std::vector<int>, int> EpsilonClosure(LexerContext& lexerContext, int nfaStateId);
std::expected<std::vector<int>, int> Move(LexerContext& lexerContext, const std::vector<int>& stateIds, char32_t c);
std::expected<Dfa, int> Compile(LexerContext& lexerContext, Nfa& nfa);

class ExprParser
{
public:
    virtual ~ExprParser();
    virtual std::expected<Nfa, int> Parse(const std::string& expression, LexerContext* lexerContext, const std::string& fileName, int line) = 0;
};

class LexerContext
{
public:
    LexerContext();
    ~LexerContext();
    const std::string& FileName() const { return fileName; }
    void SetFileName(const std::string& fileName_);
    const std::string& Base() const { return base; }
    void SetBase(const std::string& base_);
    NfaState* MakeNfaState();
    std::expected<NfaState*, int> GetNfaState(int id) const;
    const std::vector<NfaState*>& NfaStates() const { return nfaStates; }
    DfaState* MakeDfaState(const std::vector<int>& nfaStates);
    std::expected<Symbol*, int> MakeChar(char32_t c);
    Symbol* MakeAny() { return &any; }
    Symbol* MakeEpsilon() { return &epsilon; }
    std::expected<Symbol*, int> MakeRange(char32_t start, char32_t end);
    Class* MakeAsciiIdStart() { return asciiIdStart; }
    Class* MakeAsciiIdCont() { return asciiIdCont; }
    Class* MakeUnicodeIdStart() { return unicodeIdStart; }
    Class* MakeUnicodeIdCont() { return unicodeIdCont; }
    void AddToSymbols(Symbol* symbol);
    const std::vector<soul_expected::ast::re::Symbol*>& Symbols() const { return symbols; }
    Class* MakeClass();
    void AddCanonicalClass(Class* cls);
    const std::vector<Class*>& CanonicalClasses() const { return canonicalClasses; }
    void AddToPartition(Class* cls);
    const std::vector<Class*>& Partition() const { return partition; }
    void SetCurrentExpression(soul_expected::ast::slg::Expression* currentExpression_) { currentExpression = currentExpression_; }
    void SetExprParser(ExprParser* exprParser_) { exprParser = exprParser_; }
    ExprParser* GetExprParser() const { return exprParser; }
    std::expected<Nfa, int> MakeExpr(const std::string& id);
    soul_expected::ast::slg::Tokens* GetTokens() const { return tokens; }
    void SetTokens(soul_expected::ast::slg::Tokens* tokens_) { tokens = tokens_; }
    soul_expected::ast::slg::Keywords* GetKeywords() const { return keywords; }
    void SetKeywords(soul_expected::ast::slg::Keywords* keywords_) { keywords = keywords_; }
    soul_expected::ast::slg::Expressions* GetExpressions() const { return expressions; }
    void SetExpressions(soul_expected::ast::slg::Expressions* expressions_) { expressions = expressions_; }
    soul_expected::ast::slg::Lexer* GetLexer() const { return lexer; }
    void SetLexer(soul_expected::ast::slg::Lexer* lexer_) { lexer = lexer_; }
    int AddNfa(Nfa* nfa);
    std::expected<Nfa*, int> GetNfa(int index) const;
    int MasterNfaIndex() const { return masterNfaIndex; }
    void SetMasterNfaIndex(int masterNfaIndex_) { masterNfaIndex = masterNfaIndex_; }
    void SetDfa(Dfa&& dfa_);
    const Dfa& GetDfa() const { return dfa; }
    Dfa& GetDfa() { return dfa; }
    int Error() const { return error; }
    bool Valid() const { return error == 0; }
    explicit operator bool() const { return Valid(); }
    bool Verbose() const { return verbose; }
    void SetVerbose() { verbose = true; }
    bool Debug() const { return debug; }
    void SetDebug() { debug = true; }
private:
    std::string fileName;
    int nextNfaStateId;
    int nextDfaStateId;
    int ruleIndex;
    int classIndex;
    std::vector<NfaState*> nfaStates;
    std::map<int, NfaState*> nfaStateMap;
    std::vector<DfaState*> dfaStates;
    std::vector<Symbol*> symbols;
    std::vector<Class*> canonicalClasses;
    std::vector<Class*> partition;
    std::map<char32_t, Symbol*> charSymbols;
    std::map<Range, Symbol*> rangeSymbols;
    Any any;
    CharSymbol epsilon;
    Class* asciiIdStart;
    Class* asciiIdCont;
    Class* unicodeIdStart;
    Class* unicodeIdCont;
    soul_expected::ast::slg::Tokens* tokens;
    soul_expected::ast::slg::Keywords* keywords;
    soul_expected::ast::slg::Expressions* expressions;
    soul_expected::ast::slg::Lexer* lexer;
    soul_expected::ast::slg::Expression* currentExpression;
    ExprParser* exprParser;
    std::vector<std::unique_ptr<Nfa>> nfas;
    std::map<int, Nfa*> nfaMap;
    int masterNfaIndex;
    Dfa dfa;
    int error;
    std::string base;
    bool verbose;
    bool debug;
};

class Visitor
{
public:
    virtual void Visit(CharSymbol& c) {}
    virtual void Visit(Any& a) {}
    virtual void Visit(Range& r) {}
    virtual void Visit(Class& c) {}
};

} // namespace soul::ast::re
