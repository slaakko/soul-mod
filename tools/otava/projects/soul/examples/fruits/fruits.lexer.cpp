// this file has been automatically generated from 'D:/work/soul-mod/tools/otava/projects/soul/examples/fruits/fruits.lexer' using soul lexer generator oslg version 5.0.0

module fruits.lexer;


namespace fruits::lexer {

soul::ast::common::TokenCollection* GetTokens()
{
    static soul::ast::common::TokenCollection tokens("fruits.lexer.tokens");
    if (!tokens.Initialized())
    {
        tokens.SetInitialized();
        tokens.AddToken(new soul::ast::common::Token(fruits::token::APPLE, "APPLE", "'apple'"));
        tokens.AddToken(new soul::ast::common::Token(fruits::token::ORANGE, "ORANGE", "'orange'"));
        tokens.AddToken(new soul::ast::common::Token(fruits::token::BANANA, "BANANA", "'banana'"));
        tokens.AddToken(new soul::ast::common::Token(fruits::token::COMMA, "COMMA", ","));
        tokens.AddToken(new soul::ast::common::Token(fruits::token::LPAREN, "LPAREN", "("));
        tokens.AddToken(new soul::ast::common::Token(fruits::token::RPAREN, "RPAREN", ")"));
        tokens.AddToken(new soul::ast::common::Token(fruits::token::ID, "ID", "identifier"));
    }
    return &tokens;
}

FruitLexer_Variables::FruitLexer_Variables()
{
}

std::mutex mtx;

std::mutex& MakeLexerMtx() { return mtx; }

template<>
soul::lexer::KeywordMap<char>* GetKeywords<char>()
{
    static const soul::lexer::Keyword<char> keywords[] = {
         { "apple", fruits::token::APPLE },
         { "orange", fruits::token::ORANGE },
         { "banana", fruits::token::BANANA },
         { nullptr, -1 }
    };
    static soul::lexer::KeywordMap<char> keywordMap(keywords);
    return &keywordMap;
}

template<>
soul::lexer::KeywordMap<char8_t>* GetKeywords<char8_t>()
{
    static const soul::lexer::Keyword<char8_t> keywords[] = {
         { u8"apple", fruits::token::APPLE },
         { u8"orange", fruits::token::ORANGE },
         { u8"banana", fruits::token::BANANA },
         { nullptr, -1 }
    };
    static soul::lexer::KeywordMap<char8_t> keywordMap(keywords);
    return &keywordMap;
}

template<>
soul::lexer::KeywordMap<char16_t>* GetKeywords<char16_t>()
{
    static const soul::lexer::Keyword<char16_t> keywords[] = {
         { u"apple", fruits::token::APPLE },
         { u"orange", fruits::token::ORANGE },
         { u"banana", fruits::token::BANANA },
         { nullptr, -1 }
    };
    static soul::lexer::KeywordMap<char16_t> keywordMap(keywords);
    return &keywordMap;
}

template<>
soul::lexer::KeywordMap<char32_t>* GetKeywords<char32_t>()
{
    static const soul::lexer::Keyword<char32_t> keywords[] = {
         { U"apple", fruits::token::APPLE },
         { U"orange", fruits::token::ORANGE },
         { U"banana", fruits::token::BANANA },
         { nullptr, -1 }
    };
    static soul::lexer::KeywordMap<char32_t> keywordMap(keywords);
    return &keywordMap;
}

} // namespace fruits::lexer
