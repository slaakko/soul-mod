// this file has been automatically generated from 'D:/work/soul-mod/tools/otava/projects/ocompiler/build/project.lexer' using soul lexer generator oslg version 5.0.0

module otava.project_lexer;


namespace otava::project_lexer {

soul::ast::common::TokenCollection* GetTokens()
{
    static soul::ast::common::TokenCollection tokens("otava.project_lexer.tokens");
    if (!tokens.Initialized())
    {
        tokens.SetInitialized();
        tokens.AddToken(new soul::ast::common::Token(otava::project_token::PROJECT, "PROJECT", "'project'"));
        tokens.AddToken(new soul::ast::common::Token(otava::project_token::ID, "ID", "identifier"));
        tokens.AddToken(new soul::ast::common::Token(otava::project_token::DOT, "DOT", "'.'"));
        tokens.AddToken(new soul::ast::common::Token(otava::project_token::SEMICOLON, "SEMICOLON", "';'"));
        tokens.AddToken(new soul::ast::common::Token(otava::project_token::ASSIGN, "ASSIGN", "'='"));
        tokens.AddToken(new soul::ast::common::Token(otava::project_token::INTERFACE, "INTERFACE", "'interface'"));
        tokens.AddToken(new soul::ast::common::Token(otava::project_token::SOURCE, "SOURCE", "'source'"));
        tokens.AddToken(new soul::ast::common::Token(otava::project_token::RESOURCE, "RESOURCE", "'resource'"));
        tokens.AddToken(new soul::ast::common::Token(otava::project_token::FILEPATH, "FILEPATH", "file path"));
        tokens.AddToken(new soul::ast::common::Token(otava::project_token::REFERENCE, "REFERENCE", "'reference'"));
        tokens.AddToken(new soul::ast::common::Token(otava::project_token::DEFINE, "DEFINE", "'define'"));
        tokens.AddToken(new soul::ast::common::Token(otava::project_token::VALUE, "VALUE", "value"));
        tokens.AddToken(new soul::ast::common::Token(otava::project_token::TARGET, "TARGET", "'target'"));
        tokens.AddToken(new soul::ast::common::Token(otava::project_token::PROGRAM, "PROGRAM", "'program'"));
        tokens.AddToken(new soul::ast::common::Token(otava::project_token::LIBRARY, "LIBRARY", "'library"));
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
         { "project", otava::project_token::PROJECT },
         { "interface", otava::project_token::INTERFACE },
         { "source", otava::project_token::SOURCE },
         { "reference", otava::project_token::REFERENCE },
         { "resource", otava::project_token::RESOURCE },
         { "define", otava::project_token::DEFINE },
         { "target", otava::project_token::TARGET },
         { "program", otava::project_token::PROGRAM },
         { "library", otava::project_token::LIBRARY },
         { nullptr, -1 }
    };
    static soul::lexer::KeywordMap<char> keywordMap(keywords);
    return &keywordMap;
}

template<>
soul::lexer::KeywordMap<char8_t>* GetKeywords<char8_t>()
{
    static const soul::lexer::Keyword<char8_t> keywords[] = {
         { u8"project", otava::project_token::PROJECT },
         { u8"interface", otava::project_token::INTERFACE },
         { u8"source", otava::project_token::SOURCE },
         { u8"reference", otava::project_token::REFERENCE },
         { u8"resource", otava::project_token::RESOURCE },
         { u8"define", otava::project_token::DEFINE },
         { u8"target", otava::project_token::TARGET },
         { u8"program", otava::project_token::PROGRAM },
         { u8"library", otava::project_token::LIBRARY },
         { nullptr, -1 }
    };
    static soul::lexer::KeywordMap<char8_t> keywordMap(keywords);
    return &keywordMap;
}

template<>
soul::lexer::KeywordMap<char16_t>* GetKeywords<char16_t>()
{
    static const soul::lexer::Keyword<char16_t> keywords[] = {
         { u"project", otava::project_token::PROJECT },
         { u"interface", otava::project_token::INTERFACE },
         { u"source", otava::project_token::SOURCE },
         { u"reference", otava::project_token::REFERENCE },
         { u"resource", otava::project_token::RESOURCE },
         { u"define", otava::project_token::DEFINE },
         { u"target", otava::project_token::TARGET },
         { u"program", otava::project_token::PROGRAM },
         { u"library", otava::project_token::LIBRARY },
         { nullptr, -1 }
    };
    static soul::lexer::KeywordMap<char16_t> keywordMap(keywords);
    return &keywordMap;
}

template<>
soul::lexer::KeywordMap<char32_t>* GetKeywords<char32_t>()
{
    static const soul::lexer::Keyword<char32_t> keywords[] = {
         { U"project", otava::project_token::PROJECT },
         { U"interface", otava::project_token::INTERFACE },
         { U"source", otava::project_token::SOURCE },
         { U"reference", otava::project_token::REFERENCE },
         { U"resource", otava::project_token::RESOURCE },
         { U"define", otava::project_token::DEFINE },
         { U"target", otava::project_token::TARGET },
         { U"program", otava::project_token::PROGRAM },
         { U"library", otava::project_token::LIBRARY },
         { nullptr, -1 }
    };
    static soul::lexer::KeywordMap<char32_t> keywordMap(keywords);
    return &keywordMap;
}

} // namespace otava::project_lexer
