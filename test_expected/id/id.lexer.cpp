// this file has been automatically generated from 'D:/work/soul-mod/test_expected/id/id.lexer' using soul lexer generator eslg version 5.0.0

module id;

using namespace id::token;

namespace id {

soul_expected::ast::slg::TokenCollection* GetTokens()
{
    static soul_expected::ast::slg::TokenCollection tokens("id.tokens");
    if (!tokens.Initialized())
    {
        tokens.SetInitialized();
        tokens.AddToken(new soul_expected::ast::slg::Token(ID, "ID", "'id'"));
    }
    return &tokens;
}

IdLexer_Variables::IdLexer_Variables()
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

} // namespace id
