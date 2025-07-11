// this file has been automatically generated from 'D:/work/soul-mod/tools/otava/build/project.lexer' using soul lexer generator slg version 5.0.0

module otava.project_lexer;

using namespace otava::project_token;

namespace otava::project_lexer {

soul::ast::slg::TokenCollection* GetTokens()
{
    static soul::ast::slg::TokenCollection tokens("otava.project_lexer.tokens");
    if (!tokens.Initialized())
    {
        tokens.SetInitialized();
        tokens.AddToken(new soul::ast::slg::Token(PROJECT, "PROJECT", "'project'"));
        tokens.AddToken(new soul::ast::slg::Token(ID, "ID", "identifier"));
        tokens.AddToken(new soul::ast::slg::Token(DOT, "DOT", "'.'"));
        tokens.AddToken(new soul::ast::slg::Token(SEMICOLON, "SEMICOLON", "';'"));
        tokens.AddToken(new soul::ast::slg::Token(ASSIGN, "ASSIGN", "'='"));
        tokens.AddToken(new soul::ast::slg::Token(INTERFACE, "INTERFACE", "'interface'"));
        tokens.AddToken(new soul::ast::slg::Token(SOURCE, "SOURCE", "'source'"));
        tokens.AddToken(new soul::ast::slg::Token(RESOURCE, "RESOURCE", "'resource'"));
        tokens.AddToken(new soul::ast::slg::Token(FILEPATH, "FILEPATH", "file path"));
        tokens.AddToken(new soul::ast::slg::Token(REFERENCE, "REFERENCE", "'reference'"));
        tokens.AddToken(new soul::ast::slg::Token(DEFINE, "DEFINE", "'define'"));
        tokens.AddToken(new soul::ast::slg::Token(VALUE, "VALUE", "value"));
        tokens.AddToken(new soul::ast::slg::Token(TARGET, "TARGET", "'target'"));
        tokens.AddToken(new soul::ast::slg::Token(PROGRAM, "PROGRAM", "'program'"));
        tokens.AddToken(new soul::ast::slg::Token(LIBRARY, "LIBRARY", "'library"));
    }
    return &tokens;
}

ProjectLexer_Variables::ProjectLexer_Variables()
{
}

std::mutex mtx;

std::mutex& MakeLexerMtx() { return mtx; }

template<>
soul::lexer::KeywordMap<char>* GetKeywords<char>()
{
    static const soul::lexer::Keyword<char> keywords[] = {
         { "project", PROJECT },
         { "interface", INTERFACE },
         { "source", SOURCE },
         { "reference", REFERENCE },
         { "resource", RESOURCE },
         { "define", DEFINE },
         { "target", TARGET },
         { "program", PROGRAM },
         { "library", LIBRARY },
         { nullptr, -1 }
    };
    static soul::lexer::KeywordMap<char> keywordMap(keywords);
    return &keywordMap;
}

template<>
soul::lexer::KeywordMap<char8_t>* GetKeywords<char8_t>()
{
    static const soul::lexer::Keyword<char8_t> keywords[] = {
         { u8"project", PROJECT },
         { u8"interface", INTERFACE },
         { u8"source", SOURCE },
         { u8"reference", REFERENCE },
         { u8"resource", RESOURCE },
         { u8"define", DEFINE },
         { u8"target", TARGET },
         { u8"program", PROGRAM },
         { u8"library", LIBRARY },
         { nullptr, -1 }
    };
    static soul::lexer::KeywordMap<char8_t> keywordMap(keywords);
    return &keywordMap;
}

template<>
soul::lexer::KeywordMap<char16_t>* GetKeywords<char16_t>()
{
    static const soul::lexer::Keyword<char16_t> keywords[] = {
         { u"project", PROJECT },
         { u"interface", INTERFACE },
         { u"source", SOURCE },
         { u"reference", REFERENCE },
         { u"resource", RESOURCE },
         { u"define", DEFINE },
         { u"target", TARGET },
         { u"program", PROGRAM },
         { u"library", LIBRARY },
         { nullptr, -1 }
    };
    static soul::lexer::KeywordMap<char16_t> keywordMap(keywords);
    return &keywordMap;
}

template<>
soul::lexer::KeywordMap<char32_t>* GetKeywords<char32_t>()
{
    static const soul::lexer::Keyword<char32_t> keywords[] = {
         { U"project", PROJECT },
         { U"interface", INTERFACE },
         { U"source", SOURCE },
         { U"reference", REFERENCE },
         { U"resource", RESOURCE },
         { U"define", DEFINE },
         { U"target", TARGET },
         { U"program", PROGRAM },
         { U"library", LIBRARY },
         { nullptr, -1 }
    };
    static soul::lexer::KeywordMap<char32_t> keywordMap(keywords);
    return &keywordMap;
}

} // namespace otava::project_lexer
