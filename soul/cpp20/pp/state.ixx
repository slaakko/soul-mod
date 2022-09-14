// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.pp.state;

import std.core;
import soul.cpp20.lexer;
import soul.lexer;

export namespace soul::cpp20::pp::state {

using Lexer = soul::lexer::Lexer<soul::cpp20::lexer::Cpp20Lexer<char32_t>, char32_t>;

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
    void If(bool value);
    void Elif(bool value);
    void Ifdef(const std::string& symbol);
    void Ifndef(const std::string& symbol);
    void Else();
    void  Endif();
    void Define(const std::string& symbol, int64_t value);
    void Undef(const std::string& symbol);
    bool Defined(const std::string& symbol) const;
    void Include();
    int64_t GetSymbolValue(const std::string& symbol) const;
private:
    void PushSection();
    void PopSection();
    void SkipSection();
    Lexer* lexer;
    std::map<std::string, int64_t> symbolMap;
    std::unique_ptr<Section> currentSection;
    std::stack<std::unique_ptr<Section>> sectionStack;
};

class LexerStateMap
{
public:
    State* GetState(Lexer* lexer);
    static LexerStateMap& Instance();
private:
    std::mutex mtx;
    std::map<Lexer*, State*> stateMap;
    std::vector<std::unique_ptr<State>> states;
};

} // namespace soul::cpp20::pp::state
