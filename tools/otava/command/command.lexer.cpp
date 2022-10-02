// this file has been automatically generated from 'C:/work/soul-mod/tools/otava/command/command.lexer' using soul lexer generator slg version 4.1.0

module otava.command.lexer;

using namespace otava::command::token;

namespace otava::command::lexer {

soul::ast::slg::TokenCollection* GetTokens()
{
    static soul::ast::slg::TokenCollection tokens("otava.command.lexer.tokens");
    if (!tokens.Initialized())
    {
        tokens.SetInitialized();
        tokens.AddToken(new soul::ast::slg::Token(BUILD, "BUILD", "'build'"));
        tokens.AddToken(new soul::ast::slg::Token(DUMP, "DUMP", "'dump'"));
        tokens.AddToken(new soul::ast::slg::Token(ASSEMBLE, "ASSEMBLE", "'assemble'"));
        tokens.AddToken(new soul::ast::slg::Token(IC, "IC", "'ic'"));
        tokens.AddToken(new soul::ast::slg::Token(FILEPATH, "FILEPATH", "file path"));
        tokens.AddToken(new soul::ast::slg::Token(ID, "ID", "identifier"));
        tokens.AddToken(new soul::ast::slg::Token(DOT, "DOT", "'.'"));
        tokens.AddToken(new soul::ast::slg::Token(SEMICOLON, "SEMICOLON", "';'"));
    }
    return &tokens;
}

CommandLexer_Variables::CommandLexer_Variables()
{
}

std::mutex mtx;

std::mutex& MakeLexerMtx() { return mtx; }

template<>
soul::lexer::KeywordMap<char>* GetKeywords<char>()
{
    static const soul::lexer::Keyword<char> keywords[] = {
         { "build", BUILD },
         { "dump", DUMP },
         { "assemble", ASSEMBLE },
         { "ic", IC },
         { nullptr, -1 }
    };
    static soul::lexer::KeywordMap<char> keywordMap(keywords);
    return &keywordMap;
}

template<>
soul::lexer::KeywordMap<char8_t>* GetKeywords<char8_t>()
{
    static const soul::lexer::Keyword<char8_t> keywords[] = {
         { u8"build", BUILD },
         { u8"dump", DUMP },
         { u8"assemble", ASSEMBLE },
         { u8"ic", IC },
         { nullptr, -1 }
    };
    static soul::lexer::KeywordMap<char8_t> keywordMap(keywords);
    return &keywordMap;
}

template<>
soul::lexer::KeywordMap<char16_t>* GetKeywords<char16_t>()
{
    static const soul::lexer::Keyword<char16_t> keywords[] = {
         { u"build", BUILD },
         { u"dump", DUMP },
         { u"assemble", ASSEMBLE },
         { u"ic", IC },
         { nullptr, -1 }
    };
    static soul::lexer::KeywordMap<char16_t> keywordMap(keywords);
    return &keywordMap;
}

template<>
soul::lexer::KeywordMap<char32_t>* GetKeywords<char32_t>()
{
    static const soul::lexer::Keyword<char32_t> keywords[] = {
         { U"build", BUILD },
         { U"dump", DUMP },
         { U"assemble", ASSEMBLE },
         { U"ic", IC },
         { nullptr, -1 }
    };
    static soul::lexer::KeywordMap<char32_t> keywordMap(keywords);
    return &keywordMap;
}

} // namespace otava::command::lexer
