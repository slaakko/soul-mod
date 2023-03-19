// this file has been automatically generated from 'C:/work/soul-mod/tools/otava/pp/pp.lexer' using soul lexer generator slg version 4.1.0

module otava.pp.lexer;

using namespace otava::token;

namespace otava::pp::lexer {

soul::ast::slg::TokenCollection* GetTokens()
{
    static soul::ast::slg::TokenCollection tokens("otava.pp.lexer.tokens");
    if (!tokens.Initialized())
    {
        tokens.SetInitialized();
        tokens.AddToken(new soul::ast::slg::Token(ALIGNAS, "ALIGNAS", "'alignas'"));
        tokens.AddToken(new soul::ast::slg::Token(ALIGNOF, "ALIGNOF", "'alignof'"));
        tokens.AddToken(new soul::ast::slg::Token(ASM, "ASM", "'asm'"));
        tokens.AddToken(new soul::ast::slg::Token(AUTO, "AUTO", "'auto'"));
        tokens.AddToken(new soul::ast::slg::Token(BOOL, "BOOL", "'bool'"));
        tokens.AddToken(new soul::ast::slg::Token(BREAK, "BREAK", "'break'"));
        tokens.AddToken(new soul::ast::slg::Token(CASE, "CASE", "'case'"));
        tokens.AddToken(new soul::ast::slg::Token(CATCH, "CATCH", "'catch'"));
        tokens.AddToken(new soul::ast::slg::Token(CHAR, "CHAR", "'char'"));
        tokens.AddToken(new soul::ast::slg::Token(CHAR8_T, "CHAR8_T", "'char8_t'"));
        tokens.AddToken(new soul::ast::slg::Token(CHAR16_T, "CHAR16_T", "'char16_t'"));
        tokens.AddToken(new soul::ast::slg::Token(CHAR32_T, "CHAR32_T", "'char32_t'"));
        tokens.AddToken(new soul::ast::slg::Token(CLASS, "CLASS", "'class'"));
        tokens.AddToken(new soul::ast::slg::Token(CONCEPT, "CONCEPT", "'concept'"));
        tokens.AddToken(new soul::ast::slg::Token(CONST, "CONST", "'const'"));
        tokens.AddToken(new soul::ast::slg::Token(CONSTEVAL, "CONSTEVAL", "'consteval'"));
        tokens.AddToken(new soul::ast::slg::Token(CONSTEXPR, "CONSTEXPR", "'constexpr'"));
        tokens.AddToken(new soul::ast::slg::Token(CONSTINIT, "CONSTINIT", "'constinit'"));
        tokens.AddToken(new soul::ast::slg::Token(CONST_CAST, "CONST_CAST", "'const_cast'"));
        tokens.AddToken(new soul::ast::slg::Token(CONTINUE, "CONTINUE", "'continue'"));
        tokens.AddToken(new soul::ast::slg::Token(CO_AWAIT, "CO_AWAIT", "'co_await'"));
        tokens.AddToken(new soul::ast::slg::Token(CO_RETURN, "CO_RETURN", "'co_return'"));
        tokens.AddToken(new soul::ast::slg::Token(CO_YIELD, "CO_YIELD", "'co_yield'"));
        tokens.AddToken(new soul::ast::slg::Token(DECLTYPE, "DECLTYPE", "'decltype'"));
        tokens.AddToken(new soul::ast::slg::Token(DEFAULT, "DEFAULT", "'default'"));
        tokens.AddToken(new soul::ast::slg::Token(DELETE, "DELETE", "'delete'"));
        tokens.AddToken(new soul::ast::slg::Token(DO, "DO", "'do'"));
        tokens.AddToken(new soul::ast::slg::Token(DOUBLE, "DOUBLE", "'double'"));
        tokens.AddToken(new soul::ast::slg::Token(DYNAMIC_CAST, "DYNAMIC_CAST", "'dynamic_cast'"));
        tokens.AddToken(new soul::ast::slg::Token(ELSE, "ELSE", "'else'"));
        tokens.AddToken(new soul::ast::slg::Token(ENUM, "ENUM", "'enum'"));
        tokens.AddToken(new soul::ast::slg::Token(EXPLICIT, "EXPLICIT", "'explicit'"));
        tokens.AddToken(new soul::ast::slg::Token(EXPORT, "EXPORT", "'export'"));
        tokens.AddToken(new soul::ast::slg::Token(EXTERN, "EXTERN", "'extern'"));
        tokens.AddToken(new soul::ast::slg::Token(FALSE, "FALSE", "'false'"));
        tokens.AddToken(new soul::ast::slg::Token(FLOAT, "FLOAT", "'float'"));
        tokens.AddToken(new soul::ast::slg::Token(FOR, "FOR", "'for'"));
        tokens.AddToken(new soul::ast::slg::Token(FRIEND, "FRIEND", "'friend'"));
        tokens.AddToken(new soul::ast::slg::Token(GOTO, "GOTO", "'goto'"));
        tokens.AddToken(new soul::ast::slg::Token(IF, "IF", "'if'"));
        tokens.AddToken(new soul::ast::slg::Token(INLINE, "INLINE", "'inline'"));
        tokens.AddToken(new soul::ast::slg::Token(INT, "INT", "'int'"));
        tokens.AddToken(new soul::ast::slg::Token(LONG, "LONG", "'long'"));
        tokens.AddToken(new soul::ast::slg::Token(MUTABLE, "MUTABLE", "'mutable'"));
        tokens.AddToken(new soul::ast::slg::Token(NAMESPACE, "NAMESPACE", "'namespace'"));
        tokens.AddToken(new soul::ast::slg::Token(NEW, "NEW", "'new'"));
        tokens.AddToken(new soul::ast::slg::Token(NOEXCEPT, "NOEXCEPT", "'noexcept'"));
        tokens.AddToken(new soul::ast::slg::Token(NULLPTR, "NULLPTR", "'nullptr'"));
        tokens.AddToken(new soul::ast::slg::Token(OPERATOR, "OPERATOR", "'operator'"));
        tokens.AddToken(new soul::ast::slg::Token(PRIVATE, "PRIVATE", "'private'"));
        tokens.AddToken(new soul::ast::slg::Token(PROTECTED, "PROTECTED", "'protected'"));
        tokens.AddToken(new soul::ast::slg::Token(PUBLIC, "PUBLIC", "'public'"));
        tokens.AddToken(new soul::ast::slg::Token(REGISTER, "REGISTER", "'register'"));
        tokens.AddToken(new soul::ast::slg::Token(REINTERPRET_CAST, "REINTERPRET_CAST", "'reinterpret_cast'"));
        tokens.AddToken(new soul::ast::slg::Token(REQUIRES, "REQUIRES", "'requires'"));
        tokens.AddToken(new soul::ast::slg::Token(RETURN, "RETURN", "'return'"));
        tokens.AddToken(new soul::ast::slg::Token(SHORT, "SHORT", "'short'"));
        tokens.AddToken(new soul::ast::slg::Token(SIGNED, "SIGNED", "'signed'"));
        tokens.AddToken(new soul::ast::slg::Token(SIZEOF, "SIZEOF", "'sizeof'"));
        tokens.AddToken(new soul::ast::slg::Token(STATIC, "STATIC", "'static'"));
        tokens.AddToken(new soul::ast::slg::Token(STATIC_ASSERT, "STATIC_ASSERT", "'static_assert'"));
        tokens.AddToken(new soul::ast::slg::Token(STATIC_CAST, "STATIC_CAST", "'static_cast'"));
        tokens.AddToken(new soul::ast::slg::Token(STRUCT, "STRUCT", "'struct'"));
        tokens.AddToken(new soul::ast::slg::Token(SWITCH, "SWITCH", "'switch'"));
        tokens.AddToken(new soul::ast::slg::Token(TEMPLATE, "TEMPLATE", "'template'"));
        tokens.AddToken(new soul::ast::slg::Token(THIS, "THIS", "'this'"));
        tokens.AddToken(new soul::ast::slg::Token(THREAD_LOCAL, "THREAD_LOCAL", "'thread_local'"));
        tokens.AddToken(new soul::ast::slg::Token(THROW, "THROW", "'throw'"));
        tokens.AddToken(new soul::ast::slg::Token(TRUE, "TRUE", "'true'"));
        tokens.AddToken(new soul::ast::slg::Token(TRY, "TRY", "'try'"));
        tokens.AddToken(new soul::ast::slg::Token(TYPEDEF, "TYPEDEF", "'typedef'"));
        tokens.AddToken(new soul::ast::slg::Token(TYPEID, "TYPEID", "'typeid'"));
        tokens.AddToken(new soul::ast::slg::Token(TYPENAME, "TYPENAME", "'typename'"));
        tokens.AddToken(new soul::ast::slg::Token(UNION, "UNION", "'union'"));
        tokens.AddToken(new soul::ast::slg::Token(UNSIGNED, "UNSIGNED", "'unsigned'"));
        tokens.AddToken(new soul::ast::slg::Token(USING, "USING", "'using'"));
        tokens.AddToken(new soul::ast::slg::Token(VIRTUAL, "VIRTUAL", "'virtual'"));
        tokens.AddToken(new soul::ast::slg::Token(VOID, "VOID", "'void'"));
        tokens.AddToken(new soul::ast::slg::Token(VOLATILE, "VOLATILE", "'volatile'"));
        tokens.AddToken(new soul::ast::slg::Token(WCHAR_T, "WCHAR_T", "'wchar_t'"));
        tokens.AddToken(new soul::ast::slg::Token(WHILE, "WHILE", "'while'"));
        tokens.AddToken(new soul::ast::slg::Token(FLOATING_LITERAL, "FLOATING_LITERAL", "floating literal"));
        tokens.AddToken(new soul::ast::slg::Token(INTEGER_LITERAL, "INTEGER_LITERAL", "integer literal"));
        tokens.AddToken(new soul::ast::slg::Token(CHARACTER_LITERAL, "CHARACTER_LITERAL", "character literal"));
        tokens.AddToken(new soul::ast::slg::Token(STRING_LITERAL, "STRING_LITERAL", "string literal"));
        tokens.AddToken(new soul::ast::slg::Token(BEGIN_RAW_STRING_LITERAL, "BEGIN_RAW_STRING_LITERAL", "'begin raw string literal'"));
        tokens.AddToken(new soul::ast::slg::Token(ID, "ID", "identifier"));
        tokens.AddToken(new soul::ast::slg::Token(COLON_COLON, "COLON_COLON", "'::'"));
        tokens.AddToken(new soul::ast::slg::Token(COMMA, "COMMA", "','"));
        tokens.AddToken(new soul::ast::slg::Token(ASSIGN, "ASSIGN", "'='"));
        tokens.AddToken(new soul::ast::slg::Token(MUL_ASSIGN, "MUL_ASSIGN", "'*='"));
        tokens.AddToken(new soul::ast::slg::Token(DIV_ASSIGN, "DIV_ASSIGN", "'/='"));
        tokens.AddToken(new soul::ast::slg::Token(REM_ASSIGN, "REM_ASSIGN", "'%='"));
        tokens.AddToken(new soul::ast::slg::Token(ADD_ASSIGN, "ADD_ASSIGN", "'+='"));
        tokens.AddToken(new soul::ast::slg::Token(SUB_ASSIGN, "SUB_ASSIGN", "'-='"));
        tokens.AddToken(new soul::ast::slg::Token(SHIFT_RIGHT_ASSIGN, "SHIFT_RIGHT_ASSIGN", "'>>='"));
        tokens.AddToken(new soul::ast::slg::Token(SHIFT_LEFT_ASSIGN, "SHIFT_LEFT_ASSIGN", "'<<='"));
        tokens.AddToken(new soul::ast::slg::Token(AND_ASSIGN, "AND_ASSIGN", "'&='"));
        tokens.AddToken(new soul::ast::slg::Token(XOR_ASSIGN, "XOR_ASSIGN", "'^='"));
        tokens.AddToken(new soul::ast::slg::Token(OR_ASSIGN, "OR_ASSIGN", "'|='"));
        tokens.AddToken(new soul::ast::slg::Token(QUEST, "QUEST", "'?'"));
        tokens.AddToken(new soul::ast::slg::Token(COLON, "COLON", "':'"));
        tokens.AddToken(new soul::ast::slg::Token(OR_OR, "OR_OR", "'||'"));
        tokens.AddToken(new soul::ast::slg::Token(AMP_AMP, "AMP_AMP", "'&&'"));
        tokens.AddToken(new soul::ast::slg::Token(OR, "OR", "'|'"));
        tokens.AddToken(new soul::ast::slg::Token(XOR, "XOR", "'^'"));
        tokens.AddToken(new soul::ast::slg::Token(AMP, "AMP", "'&'"));
        tokens.AddToken(new soul::ast::slg::Token(EQ, "EQ", "'=='"));
        tokens.AddToken(new soul::ast::slg::Token(NEQ, "NEQ", "'!='"));
        tokens.AddToken(new soul::ast::slg::Token(LEQ, "LEQ", "'<='"));
        tokens.AddToken(new soul::ast::slg::Token(GEQ, "GEQ", "'>='"));
        tokens.AddToken(new soul::ast::slg::Token(SPACE_SHIP, "SPACE_SHIP", "<=>"));
        tokens.AddToken(new soul::ast::slg::Token(LANGLE, "LANGLE", "'<'"));
        tokens.AddToken(new soul::ast::slg::Token(RANGLE, "RANGLE", "'>'"));
        tokens.AddToken(new soul::ast::slg::Token(SHIFT_LEFT, "SHIFT_LEFT", "'<<'"));
        tokens.AddToken(new soul::ast::slg::Token(SHIFT_RIGHT, "SHIFT_RIGHT", "'>>'"));
        tokens.AddToken(new soul::ast::slg::Token(PLUS, "PLUS", "'+'"));
        tokens.AddToken(new soul::ast::slg::Token(MINUS, "MINUS", "'-'"));
        tokens.AddToken(new soul::ast::slg::Token(STAR, "STAR", "'*'"));
        tokens.AddToken(new soul::ast::slg::Token(DIV, "DIV", "'/'"));
        tokens.AddToken(new soul::ast::slg::Token(MOD, "MOD", "'%'"));
        tokens.AddToken(new soul::ast::slg::Token(DOT_STAR, "DOT_STAR", "'.*'"));
        tokens.AddToken(new soul::ast::slg::Token(ARROW_STAR, "ARROW_STAR", "'->*'"));
        tokens.AddToken(new soul::ast::slg::Token(LPAREN, "LPAREN", "'('"));
        tokens.AddToken(new soul::ast::slg::Token(RPAREN, "RPAREN", "')'"));
        tokens.AddToken(new soul::ast::slg::Token(PLUS_PLUS, "PLUS_PLUS", "'++'"));
        tokens.AddToken(new soul::ast::slg::Token(MINUS_MINUS, "MINUS_MINUS", "'--'"));
        tokens.AddToken(new soul::ast::slg::Token(EXCLAMATION, "EXCLAMATION", "'!'"));
        tokens.AddToken(new soul::ast::slg::Token(TILDE, "TILDE", "'~'"));
        tokens.AddToken(new soul::ast::slg::Token(LBRACKET, "LBRACKET", "'['"));
        tokens.AddToken(new soul::ast::slg::Token(RBRACKET, "RBRACKET", "']'"));
        tokens.AddToken(new soul::ast::slg::Token(LBRACE, "LBRACE", "'{'"));
        tokens.AddToken(new soul::ast::slg::Token(RBRACE, "RBRACE", "'}'"));
        tokens.AddToken(new soul::ast::slg::Token(DOT, "DOT", "'.'"));
        tokens.AddToken(new soul::ast::slg::Token(ARROW, "ARROW", "'->'"));
        tokens.AddToken(new soul::ast::slg::Token(SEMICOLON, "SEMICOLON", "';'"));
        tokens.AddToken(new soul::ast::slg::Token(ELLIPSIS, "ELLIPSIS", "'...'"));
        tokens.AddToken(new soul::ast::slg::Token(ANGLE_HEADER_NAME, "ANGLE_HEADER_NAME", "'angle header name'"));
        tokens.AddToken(new soul::ast::slg::Token(QUOTE_HEADER_NAME, "QUOTE_HEADER_NAME", "'quote header name'"));
        tokens.AddToken(new soul::ast::slg::Token(KEYWORD, "KEYWORD", "keyword"));
        tokens.AddToken(new soul::ast::slg::Token(WS, "WS", "white space"));
        tokens.AddToken(new soul::ast::slg::Token(NEWLINE, "NEWLINE", "new line"));
        tokens.AddToken(new soul::ast::slg::Token(LINE_COMMENT, "LINE_COMMENT", "line comment"));
        tokens.AddToken(new soul::ast::slg::Token(BLOCK_COMMENT_START, "BLOCK_COMMENT_START", "block comment start"));
        tokens.AddToken(new soul::ast::slg::Token(BLOCK_COMMENT_END, "BLOCK_COMMENT_END", "block comment end"));
        tokens.AddToken(new soul::ast::slg::Token(OTHER, "OTHER", "other"));
        tokens.AddToken(new soul::ast::slg::Token(PP_LINE, "PP_LINE", "preprocessing line"));
        tokens.AddToken(new soul::ast::slg::Token(HASH, "HASH", "'#'"));
        tokens.AddToken(new soul::ast::slg::Token(DEFINE, "DEFINE", "'define'"));
        tokens.AddToken(new soul::ast::slg::Token(INCLUDE, "INCLUDE", "'include'"));
        tokens.AddToken(new soul::ast::slg::Token(IFDEF, "IFDEF", "'ifdef'"));
        tokens.AddToken(new soul::ast::slg::Token(IFNDEF, "IFNDEF", "'ifndef'"));
        tokens.AddToken(new soul::ast::slg::Token(ELIF, "ELIF", "'elif'"));
        tokens.AddToken(new soul::ast::slg::Token(ENDIF, "ENDIF", "'endif'"));
        tokens.AddToken(new soul::ast::slg::Token(UNDEF, "UNDEF", "'undef'"));
        tokens.AddToken(new soul::ast::slg::Token(DEFINED, "DEFINED", "'defined'"));
        tokens.AddToken(new soul::ast::slg::Token(PRAGMA, "PRAGMA", "'pragma'"));
        tokens.AddToken(new soul::ast::slg::Token(MAX, "MAX", "max"));
    }
    return &tokens;
}

PPLexer_Variables::PPLexer_Variables()
{
}

std::mutex mtx;

std::mutex& MakeLexerMtx() { return mtx; }

template<>
soul::lexer::KeywordMap<char>* GetKeywords<char>()
{
    static const soul::lexer::Keyword<char> keywords[] = {
         { "include", INCLUDE },
         { "if", IF },
         { "elif", ELIF },
         { "else", ELSE },
         { "ifdef", IFDEF },
         { "ifndef", IFNDEF },
         { "endif", ENDIF },
         { "undef", UNDEF },
         { "defined", DEFINED },
         { "pragma", PRAGMA },
         { nullptr, -1 }
    };
    static soul::lexer::KeywordMap<char> keywordMap(keywords);
    return &keywordMap;
}

template<>
soul::lexer::KeywordMap<char8_t>* GetKeywords<char8_t>()
{
    static const soul::lexer::Keyword<char8_t> keywords[] = {
         { u8"include", INCLUDE },
         { u8"if", IF },
         { u8"elif", ELIF },
         { u8"else", ELSE },
         { u8"ifdef", IFDEF },
         { u8"ifndef", IFNDEF },
         { u8"endif", ENDIF },
         { u8"undef", UNDEF },
         { u8"defined", DEFINED },
         { u8"pragma", PRAGMA },
         { nullptr, -1 }
    };
    static soul::lexer::KeywordMap<char8_t> keywordMap(keywords);
    return &keywordMap;
}

template<>
soul::lexer::KeywordMap<char16_t>* GetKeywords<char16_t>()
{
    static const soul::lexer::Keyword<char16_t> keywords[] = {
         { u"include", INCLUDE },
         { u"if", IF },
         { u"elif", ELIF },
         { u"else", ELSE },
         { u"ifdef", IFDEF },
         { u"ifndef", IFNDEF },
         { u"endif", ENDIF },
         { u"undef", UNDEF },
         { u"defined", DEFINED },
         { u"pragma", PRAGMA },
         { nullptr, -1 }
    };
    static soul::lexer::KeywordMap<char16_t> keywordMap(keywords);
    return &keywordMap;
}

template<>
soul::lexer::KeywordMap<char32_t>* GetKeywords<char32_t>()
{
    static const soul::lexer::Keyword<char32_t> keywords[] = {
         { U"include", INCLUDE },
         { U"if", IF },
         { U"elif", ELIF },
         { U"else", ELSE },
         { U"ifdef", IFDEF },
         { U"ifndef", IFNDEF },
         { U"endif", ENDIF },
         { U"undef", UNDEF },
         { U"defined", DEFINED },
         { U"pragma", PRAGMA },
         { nullptr, -1 }
    };
    static soul::lexer::KeywordMap<char32_t> keywordMap(keywords);
    return &keywordMap;
}

} // namespace otava::pp::lexer
