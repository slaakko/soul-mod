// this file has been automatically generated from 'C:/work/soul-mod/soul/json/json.lexer' using soul lexer generator slg version 5.0.0

module soul.json.lexer;

using namespace soul::json::token;

namespace soul::json::lexer {

soul::ast::common::TokenCollection* GetTokens()
{
    static soul::ast::common::TokenCollection tokens("soul.json.lexer.tokens");
    if (!tokens.Initialized())
    {
        tokens.SetInitialized();
        tokens.AddToken(new soul::ast::common::Token(STRING, "STRING", "'string'"));
        tokens.AddToken(new soul::ast::common::Token(NUMBER, "NUMBER", "'number'"));
        tokens.AddToken(new soul::ast::common::Token(LBRACKET, "LBRACKET", "'['"));
        tokens.AddToken(new soul::ast::common::Token(RBRACKET, "RBRACKET", "']"));
        tokens.AddToken(new soul::ast::common::Token(LBRACE, "LBRACE", "{'"));
        tokens.AddToken(new soul::ast::common::Token(RBRACE, "RBRACE", "'}'"));
        tokens.AddToken(new soul::ast::common::Token(COMMA, "COMMA", "','"));
        tokens.AddToken(new soul::ast::common::Token(COLON, "COLON", "':'"));
        tokens.AddToken(new soul::ast::common::Token(TRUE, "TRUE", "'true'"));
        tokens.AddToken(new soul::ast::common::Token(FALSE, "FALSE", "'false'"));
        tokens.AddToken(new soul::ast::common::Token(NULL, "NULL", "'null'"));
    }
    return &tokens;
}

JsonLexer_Variables::JsonLexer_Variables()
{
}

std::mutex mtx;

std::mutex& MakeLexerMtx() { return mtx; }

template<>
soul::lexer::KeywordMap<char>* GetKeywords<char>()
{
    static const soul::lexer::Keyword<char> keywords[] = {
         { nullptr, -1 }
    };
    static soul::lexer::KeywordMap<char> keywordMap(keywords);
    return &keywordMap;
}

template<>
soul::lexer::KeywordMap<char8_t>* GetKeywords<char8_t>()
{
    static const soul::lexer::Keyword<char8_t> keywords[] = {
         { nullptr, -1 }
    };
    static soul::lexer::KeywordMap<char8_t> keywordMap(keywords);
    return &keywordMap;
}

template<>
soul::lexer::KeywordMap<char16_t>* GetKeywords<char16_t>()
{
    static const soul::lexer::Keyword<char16_t> keywords[] = {
         { nullptr, -1 }
    };
    static soul::lexer::KeywordMap<char16_t> keywordMap(keywords);
    return &keywordMap;
}

template<>
soul::lexer::KeywordMap<char32_t>* GetKeywords<char32_t>()
{
    static const soul::lexer::Keyword<char32_t> keywords[] = {
         { nullptr, -1 }
    };
    static soul::lexer::KeywordMap<char32_t> keywordMap(keywords);
    return &keywordMap;
}

} // namespace soul::json::lexer
