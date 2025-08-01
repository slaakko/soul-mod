// this file has been automatically generated from 'D:/work/soul-mod/tools/otava/build/solution.lexer' using soul lexer generator slg version 5.0.0

module otava.solution_lexer;

using namespace otava::solution_token;

namespace otava::solution_lexer {

soul::ast::slg::TokenCollection* GetTokens()
{
    static soul::ast::slg::TokenCollection tokens("otava.solution_lexer.tokens");
    if (!tokens.Initialized())
    {
        tokens.SetInitialized();
        tokens.AddToken(new soul::ast::slg::Token(SOLUTION, "SOLUTION", "'solution'"));
        tokens.AddToken(new soul::ast::slg::Token(ID, "ID", "identifier"));
        tokens.AddToken(new soul::ast::slg::Token(DOT, "DOT", "'.'"));
        tokens.AddToken(new soul::ast::slg::Token(SEMICOLON, "SEMICOLON", "';'"));
        tokens.AddToken(new soul::ast::slg::Token(PROJECT, "PROJECT", "'project'"));
        tokens.AddToken(new soul::ast::slg::Token(FILEPATH, "FILEPATH", "file path"));
    }
    return &tokens;
}

SolutionLexer_Variables::SolutionLexer_Variables()
{
}

std::mutex mtx;

std::mutex& MakeLexerMtx() { return mtx; }

template<>
soul::lexer::KeywordMap<char>* GetKeywords<char>()
{
    static const soul::lexer::Keyword<char> keywords[] = {
         { "solution", SOLUTION },
         { "project", PROJECT },
         { nullptr, -1 }
    };
    static soul::lexer::KeywordMap<char> keywordMap(keywords);
    return &keywordMap;
}

template<>
soul::lexer::KeywordMap<char8_t>* GetKeywords<char8_t>()
{
    static const soul::lexer::Keyword<char8_t> keywords[] = {
         { u8"solution", SOLUTION },
         { u8"project", PROJECT },
         { nullptr, -1 }
    };
    static soul::lexer::KeywordMap<char8_t> keywordMap(keywords);
    return &keywordMap;
}

template<>
soul::lexer::KeywordMap<char16_t>* GetKeywords<char16_t>()
{
    static const soul::lexer::Keyword<char16_t> keywords[] = {
         { u"solution", SOLUTION },
         { u"project", PROJECT },
         { nullptr, -1 }
    };
    static soul::lexer::KeywordMap<char16_t> keywordMap(keywords);
    return &keywordMap;
}

template<>
soul::lexer::KeywordMap<char32_t>* GetKeywords<char32_t>()
{
    static const soul::lexer::Keyword<char32_t> keywords[] = {
         { U"solution", SOLUTION },
         { U"project", PROJECT },
         { nullptr, -1 }
    };
    static soul::lexer::KeywordMap<char32_t> keywordMap(keywords);
    return &keywordMap;
}

} // namespace otava::solution_lexer
