// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.pp.state;

import otava.token;
import otava.ast;
import util.text.util;
import util.unicode;

namespace otava::pp::state {

Section::Section(Section* parent_) : parent(parent_), skip(false), processed(false)
{
}

State::State(Lexer* lexer_) : lxr(lexer_)
{
    currentSection.reset(new Section(nullptr));
    Define("OTAVA", 1);
}

std::expected<bool, int> State::If(bool value)
{
    PushSection();
    bool skip = false;
    currentSection->SetProcessed(false);
    if (currentSection->Parent()->Skip())
    {
        skip = true;
    }
    else 
    {
        skip = !value;
        if (!skip)
        {
            currentSection->SetProcessed(true);
        }
    }
    currentSection->SetSkip(skip);
    if (skip)
    {
        auto rv = SkipSection();
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> State::Elif(bool value)
{
    bool skip = false;
    if (!currentSection->Parent()->Skip() && !currentSection->Processed())
    {
        skip = !value;
        if (!skip)
        {
            currentSection->SetProcessed(true);
        }
    }
    else
    {
        skip = true;
    }
    currentSection->SetSkip(skip);
    if (skip)
    {
        auto rv = SkipSection();
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> State::Ifdef(const std::string& symbol)
{
    PushSection();
    bool skip = false;
    currentSection->SetProcessed(false);
    if (currentSection->Parent()->Skip())
    {
        skip = true;
    }
    else
    {
        skip = !Defined(symbol);
        if (!skip)
        {
            currentSection->SetProcessed(true);
        }
    }
    currentSection->SetSkip(skip);
    if (skip)
    {
        auto rv = SkipSection();
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> State::Ifndef(const std::string& symbol)
{
    PushSection();
    bool skip = false;
    currentSection->SetProcessed(false);
    if (currentSection->Parent()->Skip())
    {
        skip = true;
    }
    else
    {
        skip = Defined(symbol);
        if (!skip)
        {
            currentSection->SetProcessed(true);
        }
    }
    currentSection->SetSkip(skip);
    if (skip)
    {
        auto rv = SkipSection();
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> State::Else()
{
    bool skip = false;
    if (!currentSection->Parent()->Skip() && !currentSection->Processed())
    {
        skip = false;
        currentSection->SetProcessed(true);
    }
    else
    {
        skip = true;
    }
    currentSection->SetSkip(skip);
    if (skip)
    {
        auto rv = SkipSection();
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> State::Endif()
{
    std::expected<bool, int> rv = PopSection();
    if (!rv) return rv;
    if (currentSection->Skip())
    {
        auto rv = SkipSection();
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

void State::Include()
{
    if (!currentSection->Skip())
    {
        std::cout << "warning: include directive '" << "' skipped" << std::endl;
    }
}

void State::Define(const std::string& symbol, std::int64_t value)
{
    if (!currentSection->Skip())
    {
        symbolMap[symbol] = value;
    }
}

std::expected<bool, int> State::Undef(const std::string& symbol)
{
    if (currentSection->Skip())
    {
        auto rv = SkipSection();
        if (!rv) return rv;
    }
    else
    {
        symbolMap.erase(symbol);
    }
    return std::expected<bool, int>(true);
}

bool State::Defined(const std::string& symbol) const
{
    auto it = symbolMap.find(symbol);
    if (it != symbolMap.cend())
    {
        return true;
    }
    else
    {
        return false;
    }
}

std::int64_t State::GetSymbolValue(const std::string& symbol) const
{
    auto it = symbolMap.find(symbol);
    if (it != symbolMap.cend())
    {
        return it->second;
    }
    else
    {
        return 0;
    }
}

void State::PushSection()
{
    sectionStack.push(std::move(currentSection));
    currentSection.reset(new Section(sectionStack.top().get()));
}

std::expected<bool, int> State::PopSection()
{
    if (sectionStack.empty())
    {
        return std::unexpected<int>(util::AllocateError("otava.pp.state: error: section stack is empty"));
    }
    currentSection = std::move(sectionStack.top());
    sectionStack.pop();
    return std::expected<bool, int>(true);
}

std::expected<bool, int> State::SkipSection()
{
    lxr->Skip(true);
    auto rv = lxr->Increment();
    if (!rv) return rv;
    while (lxr->CurrentToken().id != soul::lexer::END_TOKEN && lxr->CurrentToken().id != otava::token::PP_LINE)
    {
        rv = lxr->Increment();
        if (!rv) return rv;
    }
    lxr->Skip(false);
    if (lxr->CurrentToken().id == otava::token::PP_LINE)
    {
        lxr->PreprocessCurrentToken();
    }
    return std::expected<bool, int>(true);
}

State* LexerStateMap::GetState(Lexer* lxr)
{
    std::lock_guard<std::mutex> lock(mtx);
    auto it = stateMap.find(lxr);
    if (it != stateMap.cend())
    {
        return it->second;
    }
    else
    {
        State* state = new State(lxr);
        stateMap[lxr] = state;
        states.push_back(std::unique_ptr<State>(state));
        return state;
    }
}

LexerStateMap& LexerStateMap::Instance()
{
    static LexerStateMap instance;
    return instance;
}

} // namespace otava::pp::state
