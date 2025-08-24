// this file has been automatically generated from 'D:/work/soul-mod/soul/rex/rex.lexer' using soul lexer generator slg version 5.0.0

module soul.rex.lexer;

using namespace soul::rex::token;

namespace soul::rex::lexer {

soul::ast::common::TokenCollection* GetTokens()
{
    static soul::ast::common::TokenCollection tokens("soul.rex.lexer.tokens");
    if (!tokens.Initialized())
    {
        tokens.SetInitialized();
        tokens.AddToken(new soul::ast::common::Token(LPAREN, "LPAREN", "'('"));
        tokens.AddToken(new soul::ast::common::Token(RPAREN, "RPAREN", "')'"));
        tokens.AddToken(new soul::ast::common::Token(LBRACKET, "LBRACKET", "'['"));
        tokens.AddToken(new soul::ast::common::Token(RBRACKET, "RBRACKET", "']'"));
        tokens.AddToken(new soul::ast::common::Token(ALT, "ALT", "'|'"));
        tokens.AddToken(new soul::ast::common::Token(STAR, "STAR", "'*'"));
        tokens.AddToken(new soul::ast::common::Token(PLUS, "PLUS", "'+'"));
        tokens.AddToken(new soul::ast::common::Token(QUEST, "QUEST", "'?'"));
        tokens.AddToken(new soul::ast::common::Token(DOT, "DOT", "'.'"));
        tokens.AddToken(new soul::ast::common::Token(ESCAPE, "ESCAPE", "escape"));
        tokens.AddToken(new soul::ast::common::Token(INVERSE, "INVERSE", "'^'"));
        tokens.AddToken(new soul::ast::common::Token(MINUS, "MINUS", "'-'"));
        tokens.AddToken(new soul::ast::common::Token(CHAR, "CHAR", "character"));
    }
    return &tokens;
}

RexLexer_Variables::RexLexer_Variables()
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

} // namespace soul::rex::lexer
