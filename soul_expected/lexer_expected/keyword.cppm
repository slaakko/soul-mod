// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul_expected.lexer.keyword;

import std;
import soul_expected.lexer.token;
import soul_expected.lexer.lexeme;

export namespace soul_expected::lexer {

template<typename Char>
constexpr const Char* StrEnd(const Char* s)
{
    while (*s)
    {
        ++s;
    }
    return s;
}

template<typename Char>
struct Keyword
{
    inline Keyword() : str(nullptr), tokenID(INVALID_TOKEN) {}
    inline Keyword(const Char* str_, std::int64_t tokenID_) : str(str_), tokenID(tokenID_) {}
    const Char* str;
    std::int64_t tokenID;
};

template<typename Char>
class KeywordMap
{
public:
    constexpr KeywordMap(const soul_expected::lexer::Keyword<Char>* keywords_) : keywords(keywords_)
    {
        const soul_expected::lexer::Keyword<Char>* kw = keywords;
        while (kw->str)
        {
            Lexeme<Char> lexeme(kw->str, StrEnd(kw->str));
            keywordMap[lexeme] = kw->tokenID;
            ++kw;
        }
    }
    std::int64_t GetKeywordToken(const Lexeme<Char>& lexeme) const
    {
        auto it = keywordMap.find(lexeme);
        if (it != keywordMap.cend())
        {
            return it->second;
        }
        else
        {
            return INVALID_TOKEN;
        }
    }
private:
    const soul_expected::lexer::Keyword<Char>* keywords;
    std::map<Lexeme<Char>, std::int64_t, LexemeCompare<Char>> keywordMap;
};

} // namespace soul_expected::lexer
