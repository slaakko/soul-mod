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

template<typename Char>
struct TrivialLexer;

template<typename Char>
soul_expected::lexer::Lexer<TrivialLexer<Char>, Char> MakeLexer(const Char* start, const Char* end, const std::string& fileName);

template<typename Char>
struct TrivialLexer
{
    using Variables = TrivialLexer_Variables;

    static std::int32_t NextState(std::int32_t state, Char chr, soul_expected::lexer::LexerBase<Char>& lexer)
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

template<typename Char>
soul_expected::lexer::Lexer<TrivialLexer<Char>, Char> MakeLexer(const Char* start, const Char* end, const std::string& fileName)
{
    auto lexer = soul_expected::lexer::Lexer<TrivialLexer<Char>, Char>(start, end, fileName);
    return lexer;
}

} // namespace soul_expected::lexer::trivial
