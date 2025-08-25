// this file has been automatically generated from 'D:/work/soul-mod/soul_expected/rex_expected/rex.lexer' using soul lexer generator eslg version 5.0.0

module soul_expected.rex.lexer;

using namespace soul_expected::rex::token;

namespace soul_expected::rex::lexer {

soul_expected::ast::common::TokenCollection* GetTokens()
{
    static soul_expected::ast::common::TokenCollection tokens("soul_expected.rex.lexer.tokens");
    if (!tokens.Initialized())
    {
        tokens.SetInitialized();
        tokens.AddToken(new soul_expected::ast::common::Token(LPAREN, "LPAREN", "'('"));
        tokens.AddToken(new soul_expected::ast::common::Token(RPAREN, "RPAREN", "')'"));
        tokens.AddToken(new soul_expected::ast::common::Token(LBRACKET, "LBRACKET", "'['"));
        tokens.AddToken(new soul_expected::ast::common::Token(RBRACKET, "RBRACKET", "']'"));
        tokens.AddToken(new soul_expected::ast::common::Token(ALT, "ALT", "'|'"));
        tokens.AddToken(new soul_expected::ast::common::Token(STAR, "STAR", "'*'"));
        tokens.AddToken(new soul_expected::ast::common::Token(PLUS, "PLUS", "'+'"));
        tokens.AddToken(new soul_expected::ast::common::Token(QUEST, "QUEST", "'?'"));
        tokens.AddToken(new soul_expected::ast::common::Token(DOT, "DOT", "'.'"));
        tokens.AddToken(new soul_expected::ast::common::Token(ESCAPE, "ESCAPE", "escape"));
        tokens.AddToken(new soul_expected::ast::common::Token(INVERSE, "INVERSE", "'^'"));
        tokens.AddToken(new soul_expected::ast::common::Token(MINUS, "MINUS", "'-'"));
        tokens.AddToken(new soul_expected::ast::common::Token(CHAR, "CHAR", "character"));
    }
    return &tokens;
}

RexLexer_Variables::RexLexer_Variables()
{
}

std::mutex mtx;

std::mutex& MakeLexerMtx() { return mtx; }

template<>
soul_expected::lexer::KeywordMap<char>* GetKeywords<char>()
{
    static const soul_expected::lexer::Keyword<char> keywords[] = {
         { nullptr, -1 }
    };
    static soul_expected::lexer::KeywordMap<char> keywordMap(keywords);
    return &keywordMap;
}

template<>
soul_expected::lexer::KeywordMap<char8_t>* GetKeywords<char8_t>()
{
    static const soul_expected::lexer::Keyword<char8_t> keywords[] = {
         { nullptr, -1 }
    };
    static soul_expected::lexer::KeywordMap<char8_t> keywordMap(keywords);
    return &keywordMap;
}

template<>
soul_expected::lexer::KeywordMap<char16_t>* GetKeywords<char16_t>()
{
    static const soul_expected::lexer::Keyword<char16_t> keywords[] = {
         { nullptr, -1 }
    };
    static soul_expected::lexer::KeywordMap<char16_t> keywordMap(keywords);
    return &keywordMap;
}

template<>
soul_expected::lexer::KeywordMap<char32_t>* GetKeywords<char32_t>()
{
    static const soul_expected::lexer::Keyword<char32_t> keywords[] = {
         { nullptr, -1 }
    };
    static soul_expected::lexer::KeywordMap<char32_t> keywordMap(keywords);
    return &keywordMap;
}

} // namespace soul_expected::rex::lexer
