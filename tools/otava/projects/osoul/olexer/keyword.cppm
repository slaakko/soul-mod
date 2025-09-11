// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.lexer.keyword;

import std;
import soul.lexer.token;
import soul.lexer.lexeme;

export namespace soul::lexer {

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
    std::string ToAscii() const
    {
        std::string asciiStr;
        const Char* i = str;
        while (*i)
        {
            Char c = *i;
            int a = static_cast<int>(c);
            if (a >= 32 && a < 127)
            {
                char ca = static_cast<char>(a);
                asciiStr.append(1, ca);
            }
            ++i;
        }
        return asciiStr;
    }
    const Char* str;
    std::int64_t tokenID;
};

template<typename Char>
class KeywordMap
{
public:
    constexpr KeywordMap(const soul::lexer::Keyword<Char>* keywords_) : keywords(keywords_)
    {
        const soul::lexer::Keyword<Char>* kw = keywords;
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
    void Print()
    {
        for (const auto& p : keywordMap)
        {
            std::cout << p.first->ToAscii() << " : " << p.second << "\n";
        }
    }
private:
    const soul::lexer::Keyword<Char>* keywords;
    std::map<Lexeme<Char>, std::int64_t, LexemeCompare<Char>> keywordMap;
};

} // namespace soul::lexer
