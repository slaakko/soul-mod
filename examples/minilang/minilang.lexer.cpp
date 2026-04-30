// this file has been automatically generated from 'D:/work/soul-mod/examples/minilang/minilang.lexer' using soul lexer generator slg version 5.0.0

module minilang.lexer;


namespace minilang::lexer {

soul::ast::common::TokenCollection* GetTokens(minilang::lexer::Tag tag)
{
    static soul::ast::common::TokenCollection tokens("minilang.lexer.tokens");
    if (!tokens.Initialized())
    {
        tokens.SetInitialized();
        tokens.AddToken(new soul::ast::common::Token(minilang::token::IF, "IF", "'if'"));
        tokens.AddToken(new soul::ast::common::Token(minilang::token::ELSE, "ELSE", "'else'"));
        tokens.AddToken(new soul::ast::common::Token(minilang::token::WHILE, "WHILE", "'while'"));
        tokens.AddToken(new soul::ast::common::Token(minilang::token::RETURN, "RETURN", "'return'"));
        tokens.AddToken(new soul::ast::common::Token(minilang::token::INT, "INT", "'int'"));
        tokens.AddToken(new soul::ast::common::Token(minilang::token::BOOL, "BOOL", "'bool'"));
        tokens.AddToken(new soul::ast::common::Token(minilang::token::VOID, "VOID", "'void'"));
        tokens.AddToken(new soul::ast::common::Token(minilang::token::ID, "ID", "identifier"));
        tokens.AddToken(new soul::ast::common::Token(minilang::token::INTEGER_LITERAL, "INTEGER_LITERAL", "integer literal"));
        tokens.AddToken(new soul::ast::common::Token(minilang::token::TRUE, "TRUE", "'true'"));
        tokens.AddToken(new soul::ast::common::Token(minilang::token::FALSE, "FALSE", "'false'"));
        tokens.AddToken(new soul::ast::common::Token(minilang::token::SEMICOLON, "SEMICOLON", "';'"));
        tokens.AddToken(new soul::ast::common::Token(minilang::token::LPAREN, "LPAREN", "'('"));
        tokens.AddToken(new soul::ast::common::Token(minilang::token::RPAREN, "RPAREN", "')'"));
        tokens.AddToken(new soul::ast::common::Token(minilang::token::LBRACE, "LBRACE", "'{'"));
        tokens.AddToken(new soul::ast::common::Token(minilang::token::RBRACE, "RBRACE", "'}'"));
        tokens.AddToken(new soul::ast::common::Token(minilang::token::PLUS, "PLUS", "'+'"));
        tokens.AddToken(new soul::ast::common::Token(minilang::token::MINUS, "MINUS", "'-'"));
        tokens.AddToken(new soul::ast::common::Token(minilang::token::MUL, "MUL", "'*'"));
        tokens.AddToken(new soul::ast::common::Token(minilang::token::DIV, "DIV", "'/'"));
        tokens.AddToken(new soul::ast::common::Token(minilang::token::MOD, "MOD", "'%''"));
        tokens.AddToken(new soul::ast::common::Token(minilang::token::NOT, "NOT", "'!'"));
        tokens.AddToken(new soul::ast::common::Token(minilang::token::EQ, "EQ", "'=='"));
        tokens.AddToken(new soul::ast::common::Token(minilang::token::NEQ, "NEQ", "'!='"));
        tokens.AddToken(new soul::ast::common::Token(minilang::token::LEQ, "LEQ", "'<='"));
        tokens.AddToken(new soul::ast::common::Token(minilang::token::GEQ, "GEQ", "'>='"));
        tokens.AddToken(new soul::ast::common::Token(minilang::token::LESS, "LESS", "'<'"));
        tokens.AddToken(new soul::ast::common::Token(minilang::token::GREATER, "GREATER", "'>'"));
        tokens.AddToken(new soul::ast::common::Token(minilang::token::ASSIGN, "ASSIGN", "'='"));
        tokens.AddToken(new soul::ast::common::Token(minilang::token::COMMA, "COMMA", "','"));
    }
    return &tokens;
}

MinilangLexer_Variables::MinilangLexer_Variables()
{
}

std::mutex mtx;

std::mutex& MakeLexerMtx() { return mtx; }

template<>
soul::lexer::KeywordMap<char>* GetKeywords<char>(minilang::lexer::Tag tag)
{
    static const soul::lexer::Keyword<char> keywords[] = {
         { "if", minilang::token::IF },
         { "else", minilang::token::ELSE },
         { "while", minilang::token::WHILE },
         { "return", minilang::token::RETURN },
         { "int", minilang::token::INT },
         { "bool", minilang::token::BOOL },
         { "void", minilang::token::VOID },
         { "true", minilang::token::TRUE },
         { "false", minilang::token::FALSE },
         { nullptr, -1 }
    };
    static soul::lexer::KeywordMap<char> keywordMap(keywords);
    return &keywordMap;
}

template<>
soul::lexer::KeywordMap<char8_t>* GetKeywords<char8_t>(minilang::lexer::Tag tag)
{
    static const soul::lexer::Keyword<char8_t> keywords[] = {
         { u8"if", minilang::token::IF },
         { u8"else", minilang::token::ELSE },
         { u8"while", minilang::token::WHILE },
         { u8"return", minilang::token::RETURN },
         { u8"int", minilang::token::INT },
         { u8"bool", minilang::token::BOOL },
         { u8"void", minilang::token::VOID },
         { u8"true", minilang::token::TRUE },
         { u8"false", minilang::token::FALSE },
         { nullptr, -1 }
    };
    static soul::lexer::KeywordMap<char8_t> keywordMap(keywords);
    return &keywordMap;
}

template<>
soul::lexer::KeywordMap<char16_t>* GetKeywords<char16_t>(minilang::lexer::Tag tag)
{
    static const soul::lexer::Keyword<char16_t> keywords[] = {
         { u"if", minilang::token::IF },
         { u"else", minilang::token::ELSE },
         { u"while", minilang::token::WHILE },
         { u"return", minilang::token::RETURN },
         { u"int", minilang::token::INT },
         { u"bool", minilang::token::BOOL },
         { u"void", minilang::token::VOID },
         { u"true", minilang::token::TRUE },
         { u"false", minilang::token::FALSE },
         { nullptr, -1 }
    };
    static soul::lexer::KeywordMap<char16_t> keywordMap(keywords);
    return &keywordMap;
}

template<>
soul::lexer::KeywordMap<char32_t>* GetKeywords<char32_t>(minilang::lexer::Tag tag)
{
    static const soul::lexer::Keyword<char32_t> keywords[] = {
         { U"if", minilang::token::IF },
         { U"else", minilang::token::ELSE },
         { U"while", minilang::token::WHILE },
         { U"return", minilang::token::RETURN },
         { U"int", minilang::token::INT },
         { U"bool", minilang::token::BOOL },
         { U"void", minilang::token::VOID },
         { U"true", minilang::token::TRUE },
         { U"false", minilang::token::FALSE },
         { nullptr, -1 }
    };
    static soul::lexer::KeywordMap<char32_t> keywordMap(keywords);
    return &keywordMap;
}

} // namespace minilang::lexer
