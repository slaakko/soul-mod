// this file has been automatically generated from 'D:/work/soul-mod/examples/calculator/calculator.lexer' using soul lexer generator slg version 5.0.0

module calculator.lexer;


namespace calculator::lexer {

soul::ast::common::TokenCollection* GetTokens(calculator::lexer::Tag tag)
{
    static soul::ast::common::TokenCollection tokens("calculator.lexer.tokens");
    if (!tokens.Initialized())
    {
        tokens.SetInitialized();
        tokens.AddToken(new soul::ast::common::Token(calculator::token::NUMBER, "NUMBER", "number"));
        tokens.AddToken(new soul::ast::common::Token(calculator::token::VARIABLE, "VARIABLE", "variable"));
        tokens.AddToken(new soul::ast::common::Token(calculator::token::PI, "PI", "'pi'"));
        tokens.AddToken(new soul::ast::common::Token(calculator::token::PLUS, "PLUS", "+"));
        tokens.AddToken(new soul::ast::common::Token(calculator::token::MINUS, "MINUS", "-"));
        tokens.AddToken(new soul::ast::common::Token(calculator::token::TIMES, "TIMES", "*"));
        tokens.AddToken(new soul::ast::common::Token(calculator::token::DIVIDES, "DIVIDES", "/"));
        tokens.AddToken(new soul::ast::common::Token(calculator::token::ASSIGN, "ASSIGN", "="));
        tokens.AddToken(new soul::ast::common::Token(calculator::token::LPAREN, "LPAREN", "("));
        tokens.AddToken(new soul::ast::common::Token(calculator::token::RPAREN, "RPAREN", ")"));
    }
    return &tokens;
}

CalculatorLexer_Variables::CalculatorLexer_Variables()
{
}

std::mutex mtx;

std::mutex& MakeLexerMtx() { return mtx; }

template<>
soul::lexer::KeywordMap<char>* GetKeywords<char>(calculator::lexer::Tag tag)
{
    static const soul::lexer::Keyword<char> keywords[] = {
         { "pi", calculator::token::PI },
         { nullptr, -1 }
    };
    static soul::lexer::KeywordMap<char> keywordMap(keywords);
    return &keywordMap;
}

template<>
soul::lexer::KeywordMap<char8_t>* GetKeywords<char8_t>(calculator::lexer::Tag tag)
{
    static const soul::lexer::Keyword<char8_t> keywords[] = {
         { u8"pi", calculator::token::PI },
         { nullptr, -1 }
    };
    static soul::lexer::KeywordMap<char8_t> keywordMap(keywords);
    return &keywordMap;
}

template<>
soul::lexer::KeywordMap<char16_t>* GetKeywords<char16_t>(calculator::lexer::Tag tag)
{
    static const soul::lexer::Keyword<char16_t> keywords[] = {
         { u"pi", calculator::token::PI },
         { nullptr, -1 }
    };
    static soul::lexer::KeywordMap<char16_t> keywordMap(keywords);
    return &keywordMap;
}

template<>
soul::lexer::KeywordMap<char32_t>* GetKeywords<char32_t>(calculator::lexer::Tag tag)
{
    static const soul::lexer::Keyword<char32_t> keywords[] = {
         { U"pi", calculator::token::PI },
         { nullptr, -1 }
    };
    static soul::lexer::KeywordMap<char32_t> keywordMap(keywords);
    return &keywordMap;
}

} // namespace calculator::lexer
