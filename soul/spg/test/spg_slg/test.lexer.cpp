// this file has been automatically generated from 'C:/work/soul-mod/soul/spg/test/test.lexer' using soul lexer generator slg version 4.1.0

module test.lexer;

using namespace test::token;

namespace test::lexer {

soul::ast::slg::TokenCollection* GetTokens()
{
    static soul::ast::slg::TokenCollection tokens("test.lexer.tokens");
    if (!tokens.Initialized())
    {
        tokens.SetInitialized();
        tokens.AddToken(new soul::ast::slg::Token(CLASS, "CLASS", "class"));
        tokens.AddToken(new soul::ast::slg::Token(STRUCT, "STRUCT", "struct"));
        tokens.AddToken(new soul::ast::slg::Token(UNION, "UNION", "union"));
        tokens.AddToken(new soul::ast::slg::Token(ID, "ID", "identifier"));
    }
    return &tokens;
}

TestLexer_Variables::TestLexer_Variables()
{
}

std::mutex mtx;

std::mutex& MakeLexerMtx() { return mtx; }

template<>
soul::lexer::KeywordMap<char>* GetKeywords<char>()
{
    static const soul::lexer::Keyword<char> keywords[] = {
         { "class", CLASS },
         { "struct", STRUCT },
         { "union", UNION },
         { nullptr, -1 }
    };
    static soul::lexer::KeywordMap<char> keywordMap(keywords);
    return &keywordMap;
}

template<>
soul::lexer::KeywordMap<char8_t>* GetKeywords<char8_t>()
{
    static const soul::lexer::Keyword<char8_t> keywords[] = {
         { u8"class", CLASS },
         { u8"struct", STRUCT },
         { u8"union", UNION },
         { nullptr, -1 }
    };
    static soul::lexer::KeywordMap<char8_t> keywordMap(keywords);
    return &keywordMap;
}

template<>
soul::lexer::KeywordMap<char16_t>* GetKeywords<char16_t>()
{
    static const soul::lexer::Keyword<char16_t> keywords[] = {
         { u"class", CLASS },
         { u"struct", STRUCT },
         { u"union", UNION },
         { nullptr, -1 }
    };
    static soul::lexer::KeywordMap<char16_t> keywordMap(keywords);
    return &keywordMap;
}

template<>
soul::lexer::KeywordMap<char32_t>* GetKeywords<char32_t>()
{
    static const soul::lexer::Keyword<char32_t> keywords[] = {
         { U"class", CLASS },
         { U"struct", STRUCT },
         { U"union", UNION },
         { nullptr, -1 }
    };
    static soul::lexer::KeywordMap<char32_t> keywordMap(keywords);
    return &keywordMap;
}

} // namespace test::lexer
