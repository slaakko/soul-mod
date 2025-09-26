// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.lexer.trivial;

import std;
import soul.lexer.cls;
import soul.lexer.variables;

export namespace soul::lexer::trivial {

struct TrivialLexer_Variables : public soul::lexer::Variables
{
};

template<typename CharT>
struct TrivialLexer;

template<typename CharT>
soul::lexer::Lexer<TrivialLexer<CharT>, CharT> MakeLexer(const CharT* start, const CharT* end, const std::string& fileName);

template<typename CharT>
struct TrivialLexer
{
    using Variables = TrivialLexer_Variables;

    TrivialLexer(const CharT* start_, const CharT* end_, const std::string& fileName_) : soul::lexer::Lexer(start_, end_, fileName_)
    {
    }
    static std::int32_t NextState(std::int32_t state, CharT chr, soul::lexer::LexerBase<CharT>& lxr)
    {
        auto& token = lxr.CurrentToken();
        token.match = lxr.CurrentLexeme();
        token.id = static_cast<std::int64_t>(chr);
        if (chr == '\n')
        {
            lxr.SetLine(lxr.Line() + 1);
        }
        return -1;
    }
};

template<typename CharT>
soul::lexer::Lexer<TrivialLexer<CharT>, CharT> MakeLexer(const CharT* start, const CharT* end, const std::string& fileName)
{
    auto lxr = soul::lexer::Lexer<TrivialLexer<CharT>, CharT>(start, end, fileName);
    return lxr;
}

} // namespace soul::lexer::trivial
