// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.pp.state;

import std;
import otava.lexer;
import soul.lexer;

export namespace otava::pp::state {

using Lexer = soul::lexer::Lexer<otava::lexer::OtavaLexer<char32_t>, char32_t>;

class Section
{
public:
    Section(Section* parent_);
    Section* Parent() const { return parent; }
    bool Skip() const { return skip; }
    void SetSkip(bool skip_) { skip = skip_; }
    bool Processed() const { return processed; }
    void SetProcessed(bool processed_) { processed = processed_; }
private:
    Section* parent;
    bool skip;
    bool processed;
};

class State
{
public:
    State(Lexer* lexer_);
    std::expected<bool, int> If(bool value);
    std::expected<bool, int> Elif(bool value);
    std::expected<bool, int> Ifdef(const std::string& symbol);
    std::expected<bool, int> Ifndef(const std::string& symbol);
    std::expected<bool, int> Else();
    std::expected<bool, int> Endif();
    void Define(const std::string& symbol, std::int64_t value);
    std::expected<bool, int> Undef(const std::string& symbol);
    bool Defined(const std::string& symbol) const;
    void Include();
    std::int64_t GetSymbolValue(const std::string& symbol) const;
private:
    void PushSection();
    std::expected<bool, int> PopSection();
    std::expected<bool, int> SkipSection();
    Lexer* lxr;
    std::map<std::string, std::int64_t> symbolMap;
    std::unique_ptr<Section> currentSection;
    std::stack<std::unique_ptr<Section>> sectionStack;
};

class LexerStateMap
{
public:
    State* GetState(Lexer* lxr);
    static LexerStateMap& Instance();
private:
    std::mutex mtx;
    std::map<Lexer*, State*> stateMap;
    std::vector<std::unique_ptr<State>> states;
};

inline std::int64_t Less(std::int64_t left, std::int64_t right)
{
    if (left < right) return 1; else return 0;
}

inline std::int64_t Greater(std::int64_t left, std::int64_t right)
{
    if (left > right) return 1; else return 0;
}

} // namespace otava::pp::state
