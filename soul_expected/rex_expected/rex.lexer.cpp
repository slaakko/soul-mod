// this file has been automatically generated from 'D:/work/soul-mod/soul_expected/rex_expected/rex.lexer' using soul lexer generator eslg version 5.0.0

module soul_expected.rex.lexer;

using namespace soul_expected::rex::token;

namespace soul_expected::rex::lexer {

soul_expected::ast::slg::TokenCollection* GetTokens()
{
    static soul_expected::ast::slg::TokenCollection tokens("soul_expected.rex.lexer.tokens");
    if (!tokens.Initialized())
    {
        tokens.SetInitialized();
        tokens.AddToken(new soul_expected::ast::slg::Token(LPAREN, "LPAREN", "'('"));
        tokens.AddToken(new soul_expected::ast::slg::Token(RPAREN, "RPAREN", "')'"));
        tokens.AddToken(new soul_expected::ast::slg::Token(LBRACKET, "LBRACKET", "'['"));
        tokens.AddToken(new soul_expected::ast::slg::Token(RBRACKET, "RBRACKET", "']'"));
        tokens.AddToken(new soul_expected::ast::slg::Token(ALT, "ALT", "'|'"));
        tokens.AddToken(new soul_expected::ast::slg::Token(STAR, "STAR", "'*'"));
        tokens.AddToken(new soul_expected::ast::slg::Token(PLUS, "PLUS", "'+'"));
        tokens.AddToken(new soul_expected::ast::slg::Token(QUEST, "QUEST", "'?'"));
        tokens.AddToken(new soul_expected::ast::slg::Token(DOT, "DOT", "'.'"));
        tokens.AddToken(new soul_expected::ast::slg::Token(ESCAPE, "ESCAPE", "escape"));
        tokens.AddToken(new soul_expected::ast::slg::Token(INVERSE, "INVERSE", "'^'"));
        tokens.AddToken(new soul_expected::ast::slg::Token(MINUS, "MINUS", "'-'"));
        tokens.AddToken(new soul_expected::ast::slg::Token(CHAR, "CHAR", "character"));
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
