// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul_expected.lexer.trivial;

import std;
import soul_expected.lexer.cls;
import soul_expected.lexer.variables;

export namespace soul_expected::lexer::trivial {

struct TrivialLexer_Variables : public soul_expected::lexer::Variables
{
};

template<typename CharT>
struct TrivialLexer;

template<typename CharT>
soul_expected::lexer::Lexer<TrivialLexer<CharT>, CharT> MakeLexer(const CharT* start, const CharT* end, const std::string& fileName);

template<typename CharT>
struct TrivialLexer
{
    using Variables = TrivialLexer_Variables;

    TrivialLexer(const CharT* start_, const CharT* end_, const std::string& fileName_) : soul_expected::lexer::Lexer(start_, end_, fileName_)
    {
    }
    static std::int32_t NextState(std::int32_t state, CharT chr, soul_expected::lexer::LexerBase<CharT>& lexer)
    {
        auto& token = lexer.CurrentToken();
        token.match = lexer.CurrentLexeme();
        token.id = static_cast<std::int64_t>(chr);
        if (chr == '\n')
        {
            lexer.SetLine(lexer.Line() + 1);
        }
        return -1;
    }
};

template<typename CharT>
soul_expected::lexer::Lexer<TrivialLexer<CharT>, CharT> MakeLexer(const CharT* start, const CharT* end, const std::string& fileName)
{
    auto lexer = soul_expected::lexer::Lexer<TrivialLexer<CharT>, CharT>(start, end, fileName);
    return lexer;
}

} // namespace soul_expected::lexer::trivial
