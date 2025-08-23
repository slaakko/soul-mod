// this file has been automatically generated from 'C:/work/soul-mod/examples/minilang/minilang.lexer' using soul lexer generator slg version 5.0.0

module minilang.lexer;

using namespace minilang::token;

namespace minilang::lexer {

soul::ast::common::TokenCollection* GetTokens()
{
    static soul::ast::common::TokenCollection tokens("minilang.lexer.tokens");
    if (!tokens.Initialized())
    {
        tokens.SetInitialized();
        tokens.AddToken(new soul::ast::common::Token(IF, "IF", "'if'"));
        tokens.AddToken(new soul::ast::common::Token(ELSE, "ELSE", "'else'"));
        tokens.AddToken(new soul::ast::common::Token(WHILE, "WHILE", "'while'"));
        tokens.AddToken(new soul::ast::common::Token(RETURN, "RETURN", "'return'"));
        tokens.AddToken(new soul::ast::common::Token(INT, "INT", "'int'"));
        tokens.AddToken(new soul::ast::common::Token(BOOL, "BOOL", "'bool'"));
        tokens.AddToken(new soul::ast::common::Token(VOID, "VOID", "'void'"));
        tokens.AddToken(new soul::ast::common::Token(ID, "ID", "identifier"));
        tokens.AddToken(new soul::ast::common::Token(INTEGER_LITERAL, "INTEGER_LITERAL", "integer literal"));
        tokens.AddToken(new soul::ast::common::Token(TRUE, "TRUE", "'true'"));
        tokens.AddToken(new soul::ast::common::Token(FALSE, "FALSE", "'false'"));
        tokens.AddToken(new soul::ast::common::Token(SEMICOLON, "SEMICOLON", "';'"));
        tokens.AddToken(new soul::ast::common::Token(LPAREN, "LPAREN", "'('"));
        tokens.AddToken(new soul::ast::common::Token(RPAREN, "RPAREN", "')'"));
        tokens.AddToken(new soul::ast::common::Token(LBRACE, "LBRACE", "'{'"));
        tokens.AddToken(new soul::ast::common::Token(RBRACE, "RBRACE", "'}'"));
        tokens.AddToken(new soul::ast::common::Token(PLUS, "PLUS", "'+'"));
        tokens.AddToken(new soul::ast::common::Token(MINUS, "MINUS", "'-'"));
        tokens.AddToken(new soul::ast::common::Token(MUL, "MUL", "'*'"));
        tokens.AddToken(new soul::ast::common::Token(DIV, "DIV", "'/'"));
        tokens.AddToken(new soul::ast::common::Token(MOD, "MOD", "'%''"));
        tokens.AddToken(new soul::ast::common::Token(NOT, "NOT", "'!'"));
        tokens.AddToken(new soul::ast::common::Token(EQ, "EQ", "'=='"));
        tokens.AddToken(new soul::ast::common::Token(NEQ, "NEQ", "'!='"));
        tokens.AddToken(new soul::ast::common::Token(LEQ, "LEQ", "'<='"));
        tokens.AddToken(new soul::ast::common::Token(GEQ, "GEQ", "'>='"));
        tokens.AddToken(new soul::ast::common::Token(LESS, "LESS", "'<'"));
        tokens.AddToken(new soul::ast::common::Token(GREATER, "GREATER", "'>'"));
        tokens.AddToken(new soul::ast::common::Token(ASSIGN, "ASSIGN", "'='"));
        tokens.AddToken(new soul::ast::common::Token(COMMA, "COMMA", "','"));
    }
    return &tokens;
}

MinilangLexer_Variables::MinilangLexer_Variables()
{
}

std::mutex mtx;

std::mutex& MakeLexerMtx() { return mtx; }

template<>
soul::lexer::KeywordMap<char>* GetKeywords<char>()
{
    static const soul::lexer::Keyword<char> keywords[] = {
         { "if", IF },
         { "else", ELSE },
         { "while", WHILE },
         { "return", RETURN },
         { "int", INT },
         { "bool", BOOL },
         { "void", VOID },
         { "true", TRUE },
         { "false", FALSE },
         { nullptr, -1 }
    };
    static soul::lexer::KeywordMap<char> keywordMap(keywords);
    return &keywordMap;
}

template<>
soul::lexer::KeywordMap<char8_t>* GetKeywords<char8_t>()
{
    static const soul::lexer::Keyword<char8_t> keywords[] = {
         { u8"if", IF },
         { u8"else", ELSE },
         { u8"while", WHILE },
         { u8"return", RETURN },
         { u8"int", INT },
         { u8"bool", BOOL },
         { u8"void", VOID },
         { u8"true", TRUE },
         { u8"false", FALSE },
         { nullptr, -1 }
    };
    static soul::lexer::KeywordMap<char8_t> keywordMap(keywords);
    return &keywordMap;
}

template<>
soul::lexer::KeywordMap<char16_t>* GetKeywords<char16_t>()
{
    static const soul::lexer::Keyword<char16_t> keywords[] = {
         { u"if", IF },
         { u"else", ELSE },
         { u"while", WHILE },
         { u"return", RETURN },
         { u"int", INT },
         { u"bool", BOOL },
         { u"void", VOID },
         { u"true", TRUE },
         { u"false", FALSE },
         { nullptr, -1 }
    };
    static soul::lexer::KeywordMap<char16_t> keywordMap(keywords);
    return &keywordMap;
}

template<>
soul::lexer::KeywordMap<char32_t>* GetKeywords<char32_t>()
{
    static const soul::lexer::Keyword<char32_t> keywords[] = {
         { U"if", IF },
         { U"else", ELSE },
         { U"while", WHILE },
         { U"return", RETURN },
         { U"int", INT },
         { U"bool", BOOL },
         { U"void", VOID },
         { U"true", TRUE },
         { U"false", FALSE },
         { nullptr, -1 }
    };
    static soul::lexer::KeywordMap<char32_t> keywordMap(keywords);
    return &keywordMap;
}

} // namespace minilang::lexer
