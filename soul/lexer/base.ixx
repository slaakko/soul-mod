// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.lexer.base;

import soul.lexer.lexeme;
import soul.lexer.token;
import soul.lexer.keyword;

export namespace soul {

template<typename Char>
class LexerBase
{
public:
    using Self = LexerBase<Char>;
    virtual void Retract() = 0;
    virtual int64_t GetKeywordToken(const Lexeme<Char>& lexeme) const = 0;
    virtual const Token<Char, Self>& CurrentToken() const = 0;
    virtual const Token<Char, Self>& GetToken(int64_t pos) const = 0;
    virtual const std::string& FileName() const = 0;
    virtual int Line() const = 0;
    virtual void SetKeywordMap(KeywordMap<Char>* keywordMap) = 0;
};

} // namespace soul
