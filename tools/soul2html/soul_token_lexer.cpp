// this file has been automatically generated from 'C:/work/soul-mod/tools/soul2html/soul_token_lexer.lexer' using soul lexer generator slg version 4.0.0

module soul.token.lexer;

using namespace soul::token;
using namespace soul::cpp::token;

namespace soul::token::lexer {

soul::ast::slg::TokenCollection* GetTokens()
{
    static soul::ast::slg::TokenCollection tokens("soul.token.lexer.tokens");
    if (!tokens.Initialized())
    {
        tokens.SetInitialized();
        tokens.AddToken(new soul::ast::slg::Token(WS, "WS", "white space"));
        tokens.AddToken(new soul::ast::slg::Token(LINE_COMMENT, "LINE_COMMENT", "comment"));
        tokens.AddToken(new soul::ast::slg::Token(ID, "ID", "identifier"));
        tokens.AddToken(new soul::ast::slg::Token(KEYWORD, "KEYWORD", "keyword"));
        tokens.AddToken(new soul::ast::slg::Token(CHAR_LITERAL, "CHAR_LITERAL", "character literal"));
        tokens.AddToken(new soul::ast::slg::Token(STRING_LITERAL, "STRING_LITERAL", "string literal"));
        tokens.AddToken(new soul::ast::slg::Token(NUMBER, "NUMBER", "number"));
        tokens.AddToken(new soul::ast::slg::Token(PUNCT, "PUNCT", "punctuation"));
        tokens.AddToken(new soul::ast::slg::Token(MAIN, "MAIN", "'main'"));
        tokens.AddToken(new soul::ast::slg::Token(START, "START", "'start'"));
        tokens.AddToken(new soul::ast::slg::Token(EMPTY, "EMPTY", "'empty'"));
        tokens.AddToken(new soul::ast::slg::Token(ANY, "ANY", "'any'"));
        tokens.AddToken(new soul::ast::slg::Token(VAR, "VAR", "'var'"));
        tokens.AddToken(new soul::ast::slg::Token(PROJECT, "PROJECT", "'project'"));
        tokens.AddToken(new soul::ast::slg::Token(EXPORT, "EXPORT", "'export'"));
        tokens.AddToken(new soul::ast::slg::Token(MODULE, "MODULE", "'module'"));
        tokens.AddToken(new soul::ast::slg::Token(IMPORT, "IMPORT", "'import'"));
        tokens.AddToken(new soul::ast::slg::Token(IMPLEMENTATION, "IMPLEMENTATION", "'implementation'"));
        tokens.AddToken(new soul::ast::slg::Token(INTERFACE, "INTERFACE", "'interface'"));
        tokens.AddToken(new soul::ast::slg::Token(PARSER, "PARSER", "'parser'"));
        tokens.AddToken(new soul::ast::slg::Token(LEXER, "LEXER", "'lexer'"));
        tokens.AddToken(new soul::ast::slg::Token(TOKENS, "TOKENS", "tokens"));
        tokens.AddToken(new soul::ast::slg::Token(KEYWORDS, "KEYWORDS", "keywords"));
        tokens.AddToken(new soul::ast::slg::Token(EXPRESSIONS, "EXPRESSIONS", "expressions"));
        tokens.AddToken(new soul::ast::slg::Token(RULES, "RULES", "rules"));
        tokens.AddToken(new soul::ast::slg::Token(VARIABLES, "VARIABLES", "variables"));
        tokens.AddToken(new soul::ast::slg::Token(ACTIONS, "ACTIONS", "actions"));
        tokens.AddToken(new soul::ast::slg::Token(AUTO, "AUTO", "'auto'"));
        tokens.AddToken(new soul::ast::slg::Token(REGISTER, "REGISTER", "'register'"));
        tokens.AddToken(new soul::ast::slg::Token(STATIC, "STATIC", "'static'"));
        tokens.AddToken(new soul::ast::slg::Token(EXTERN, "EXTERN", "'extern'"));
        tokens.AddToken(new soul::ast::slg::Token(MUTABLE, "MUTABLE", "'mutable'"));
        tokens.AddToken(new soul::ast::slg::Token(EXPORT, "EXPORT", "'export'"));
        tokens.AddToken(new soul::ast::slg::Token(IMPORT, "IMPORT", "'import'"));
        tokens.AddToken(new soul::ast::slg::Token(MODULE, "MODULE", "'module"));
        tokens.AddToken(new soul::ast::slg::Token(CHAR, "CHAR", "'char'"));
        tokens.AddToken(new soul::ast::slg::Token(CHAR8T, "CHAR8T", "'char8_t'"));
        tokens.AddToken(new soul::ast::slg::Token(CHAR16T, "CHAR16T", "'char16_t'"));
        tokens.AddToken(new soul::ast::slg::Token(CHAR32T, "CHAR32T", "'char32_t'"));
        tokens.AddToken(new soul::ast::slg::Token(WCHART, "WCHART", "'wchar_t'"));
        tokens.AddToken(new soul::ast::slg::Token(BOOL, "BOOL", "'bool'"));
        tokens.AddToken(new soul::ast::slg::Token(SHORT, "SHORT", "'short'"));
        tokens.AddToken(new soul::ast::slg::Token(INT, "INT", "'int'"));
        tokens.AddToken(new soul::ast::slg::Token(LONG, "LONG", "'long'"));
        tokens.AddToken(new soul::ast::slg::Token(SIGNED, "SIGNED", "'signed'"));
        tokens.AddToken(new soul::ast::slg::Token(UNSIGNED, "UNSIGNED", "'unsigned'"));
        tokens.AddToken(new soul::ast::slg::Token(FLOAT, "FLOAT", "'float'"));
        tokens.AddToken(new soul::ast::slg::Token(DOUBLE, "DOUBLE", "'double'"));
        tokens.AddToken(new soul::ast::slg::Token(VOID, "VOID", "'void'"));
        tokens.AddToken(new soul::ast::slg::Token(TYPEDEF, "TYPEDEF", "'typedef'"));
        tokens.AddToken(new soul::ast::slg::Token(CONST, "CONST", "'const'"));
        tokens.AddToken(new soul::ast::slg::Token(VOLATILE, "VOLATILE", "'volatile'"));
        tokens.AddToken(new soul::ast::slg::Token(USING, "USING", "'using'"));
        tokens.AddToken(new soul::ast::slg::Token(NAMESPACE, "NAMESPACE", "'namespace'"));
        tokens.AddToken(new soul::ast::slg::Token(THROW, "THROW", "'throw'"));
        tokens.AddToken(new soul::ast::slg::Token(SIZEOF, "SIZEOF", "'sizeof'"));
        tokens.AddToken(new soul::ast::slg::Token(OPERATOR, "OPERATOR", "'operator'"));
        tokens.AddToken(new soul::ast::slg::Token(DYNAMIC_CAST, "DYNAMIC_CAST", "'dynamic_cast'"));
        tokens.AddToken(new soul::ast::slg::Token(STATIC_CAST, "STATIC_CAST", "'static_cast'"));
        tokens.AddToken(new soul::ast::slg::Token(REINTERPRET_CAST, "REINTERPRET_CAST", "'reinterpret_cast'"));
        tokens.AddToken(new soul::ast::slg::Token(CONST_CAST, "CONST_CAST", "'const_cast'"));
        tokens.AddToken(new soul::ast::slg::Token(TYPEID, "TYPEID", "'typeid'"));
        tokens.AddToken(new soul::ast::slg::Token(THIS, "THIS", "'this'"));
        tokens.AddToken(new soul::ast::slg::Token(NEW, "NEW", "'new'"));
        tokens.AddToken(new soul::ast::slg::Token(DELETE, "DELETE", "'delete'"));
        tokens.AddToken(new soul::ast::slg::Token(TRUE, "TRUE", "'true'"));
        tokens.AddToken(new soul::ast::slg::Token(FALSE, "FALSE", "'false'"));
        tokens.AddToken(new soul::ast::slg::Token(NULLPTR, "NULLPTR", "'nullptr'"));
        tokens.AddToken(new soul::ast::slg::Token(CASE, "CASE", "'case'"));
        tokens.AddToken(new soul::ast::slg::Token(DEFAULT, "DEFAULT", "'default'"));
        tokens.AddToken(new soul::ast::slg::Token(IF, "IF", "'if'"));
        tokens.AddToken(new soul::ast::slg::Token(ELSE, "ELSE", "'else'"));
        tokens.AddToken(new soul::ast::slg::Token(SWITCH, "SWITCH", "'switch'"));
        tokens.AddToken(new soul::ast::slg::Token(WHILE, "WHILE", "'while'"));
        tokens.AddToken(new soul::ast::slg::Token(DO, "DO", "'do'"));
        tokens.AddToken(new soul::ast::slg::Token(FOR, "FOR", "'for'"));
        tokens.AddToken(new soul::ast::slg::Token(BREAK, "BREAK", "'break'"));
        tokens.AddToken(new soul::ast::slg::Token(CONTINUE, "CONTINUE", "'continue'"));
        tokens.AddToken(new soul::ast::slg::Token(RETURN, "RETURN", "'return'"));
        tokens.AddToken(new soul::ast::slg::Token(GOTO, "GOTO", "'goto'"));
        tokens.AddToken(new soul::ast::slg::Token(TRY, "TRY", "'try'"));
        tokens.AddToken(new soul::ast::slg::Token(CATCH, "CATCH", "'catch'"));
        tokens.AddToken(new soul::ast::slg::Token(ID, "ID", "identifier"));
        tokens.AddToken(new soul::ast::slg::Token(INTEGER_LITERAL, "INTEGER_LITERAL", "integer literal"));
        tokens.AddToken(new soul::ast::slg::Token(FLOATING_LITERAL, "FLOATING_LITERAL", "floating literal"));
        tokens.AddToken(new soul::ast::slg::Token(CHAR_LITERAL, "CHAR_LITERAL", "character literal"));
        tokens.AddToken(new soul::ast::slg::Token(STRING_LITERAL, "STRING_LITERAL", "string literal"));
    }
    return &tokens;
}

SoulTokenLexer_Variables::SoulTokenLexer_Variables()
{
}

std::mutex mtx;

std::mutex& MakeLexerMtx() { return mtx; }

template<>
soul::lexer::KeywordMap<char>* GetKeywords<char>()
{
    static const soul::lexer::Keyword<char> keywords[] = {
         { "main", MAIN },
         { "start", START },
         { "empty", EMPTY },
         { "any", ANY },
         { "var", VAR },
         { "project", PROJECT },
         { "export", EXPORT },
         { "module", MODULE },
         { "import", IMPORT },
         { "implementation", IMPLEMENTATION },
         { "interface", INTERFACE },
         { "parser", PARSER },
         { "lexer", LEXER },
         { "tokens", TOKENS },
         { "keywords", KEYWORDS },
         { "expressions", EXPRESSIONS },
         { "rules", RULES },
         { "variables", VARIABLES },
         { "actions", ACTIONS },
         { "auto", AUTO },
         { "register", REGISTER },
         { "static", STATIC },
         { "extern", EXTERN },
         { "mutable", MUTABLE },
         { "char", CHAR },
         { "char8_t", CHAR8T },
         { "char16_t", CHAR16T },
         { "char32_t", CHAR32T },
         { "wchar_t", WCHART },
         { "bool", BOOL },
         { "short", SHORT },
         { "int", INT },
         { "long", LONG },
         { "signed", SIGNED },
         { "unsigned", UNSIGNED },
         { "float", FLOAT },
         { "double", DOUBLE },
         { "void", VOID },
         { "typedef", TYPEDEF },
         { "const", CONST },
         { "volatile", VOLATILE },
         { "using", USING },
         { "namespace", NAMESPACE },
         { "throw", THROW },
         { "sizeof", SIZEOF },
         { "operator", OPERATOR },
         { "dynamic_cast", DYNAMIC_CAST },
         { "static_cast", STATIC_CAST },
         { "reinterpret_cast", REINTERPRET_CAST },
         { "const_cast", CONST_CAST },
         { "typeid", TYPEID },
         { "this", THIS },
         { "new", NEW },
         { "delete", DELETE },
         { "true", TRUE },
         { "false", FALSE },
         { "nullptr", NULLPTR },
         { "case", CASE },
         { "default", DEFAULT },
         { "if", IF },
         { "else", ELSE },
         { "switch", SWITCH },
         { "while", WHILE },
         { "do", DO },
         { "for", FOR },
         { "break", BREAK },
         { "continue", CONTINUE },
         { "return", RETURN },
         { "goto", GOTO },
         { "try", TRY },
         { "catch", CATCH },
         { nullptr, -1 }
    };
    static soul::lexer::KeywordMap<char> keywordMap(keywords);
    return &keywordMap;
}

template<>
soul::lexer::KeywordMap<char8_t>* GetKeywords<char8_t>()
{
    static const soul::lexer::Keyword<char8_t> keywords[] = {
         { u8"main", MAIN },
         { u8"start", START },
         { u8"empty", EMPTY },
         { u8"any", ANY },
         { u8"var", VAR },
         { u8"project", PROJECT },
         { u8"export", EXPORT },
         { u8"module", MODULE },
         { u8"import", IMPORT },
         { u8"implementation", IMPLEMENTATION },
         { u8"interface", INTERFACE },
         { u8"parser", PARSER },
         { u8"lexer", LEXER },
         { u8"tokens", TOKENS },
         { u8"keywords", KEYWORDS },
         { u8"expressions", EXPRESSIONS },
         { u8"rules", RULES },
         { u8"variables", VARIABLES },
         { u8"actions", ACTIONS },
         { u8"auto", AUTO },
         { u8"register", REGISTER },
         { u8"static", STATIC },
         { u8"extern", EXTERN },
         { u8"mutable", MUTABLE },
         { u8"char", CHAR },
         { u8"char8_t", CHAR8T },
         { u8"char16_t", CHAR16T },
         { u8"char32_t", CHAR32T },
         { u8"wchar_t", WCHART },
         { u8"bool", BOOL },
         { u8"short", SHORT },
         { u8"int", INT },
         { u8"long", LONG },
         { u8"signed", SIGNED },
         { u8"unsigned", UNSIGNED },
         { u8"float", FLOAT },
         { u8"double", DOUBLE },
         { u8"void", VOID },
         { u8"typedef", TYPEDEF },
         { u8"const", CONST },
         { u8"volatile", VOLATILE },
         { u8"using", USING },
         { u8"namespace", NAMESPACE },
         { u8"throw", THROW },
         { u8"sizeof", SIZEOF },
         { u8"operator", OPERATOR },
         { u8"dynamic_cast", DYNAMIC_CAST },
         { u8"static_cast", STATIC_CAST },
         { u8"reinterpret_cast", REINTERPRET_CAST },
         { u8"const_cast", CONST_CAST },
         { u8"typeid", TYPEID },
         { u8"this", THIS },
         { u8"new", NEW },
         { u8"delete", DELETE },
         { u8"true", TRUE },
         { u8"false", FALSE },
         { u8"nullptr", NULLPTR },
         { u8"case", CASE },
         { u8"default", DEFAULT },
         { u8"if", IF },
         { u8"else", ELSE },
         { u8"switch", SWITCH },
         { u8"while", WHILE },
         { u8"do", DO },
         { u8"for", FOR },
         { u8"break", BREAK },
         { u8"continue", CONTINUE },
         { u8"return", RETURN },
         { u8"goto", GOTO },
         { u8"try", TRY },
         { u8"catch", CATCH },
         { nullptr, -1 }
    };
    static soul::lexer::KeywordMap<char8_t> keywordMap(keywords);
    return &keywordMap;
}

template<>
soul::lexer::KeywordMap<char16_t>* GetKeywords<char16_t>()
{
    static const soul::lexer::Keyword<char16_t> keywords[] = {
         { u"main", MAIN },
         { u"start", START },
         { u"empty", EMPTY },
         { u"any", ANY },
         { u"var", VAR },
         { u"project", PROJECT },
         { u"export", EXPORT },
         { u"module", MODULE },
         { u"import", IMPORT },
         { u"implementation", IMPLEMENTATION },
         { u"interface", INTERFACE },
         { u"parser", PARSER },
         { u"lexer", LEXER },
         { u"tokens", TOKENS },
         { u"keywords", KEYWORDS },
         { u"expressions", EXPRESSIONS },
         { u"rules", RULES },
         { u"variables", VARIABLES },
         { u"actions", ACTIONS },
         { u"auto", AUTO },
         { u"register", REGISTER },
         { u"static", STATIC },
         { u"extern", EXTERN },
         { u"mutable", MUTABLE },
         { u"char", CHAR },
         { u"char8_t", CHAR8T },
         { u"char16_t", CHAR16T },
         { u"char32_t", CHAR32T },
         { u"wchar_t", WCHART },
         { u"bool", BOOL },
         { u"short", SHORT },
         { u"int", INT },
         { u"long", LONG },
         { u"signed", SIGNED },
         { u"unsigned", UNSIGNED },
         { u"float", FLOAT },
         { u"double", DOUBLE },
         { u"void", VOID },
         { u"typedef", TYPEDEF },
         { u"const", CONST },
         { u"volatile", VOLATILE },
         { u"using", USING },
         { u"namespace", NAMESPACE },
         { u"throw", THROW },
         { u"sizeof", SIZEOF },
         { u"operator", OPERATOR },
         { u"dynamic_cast", DYNAMIC_CAST },
         { u"static_cast", STATIC_CAST },
         { u"reinterpret_cast", REINTERPRET_CAST },
         { u"const_cast", CONST_CAST },
         { u"typeid", TYPEID },
         { u"this", THIS },
         { u"new", NEW },
         { u"delete", DELETE },
         { u"true", TRUE },
         { u"false", FALSE },
         { u"nullptr", NULLPTR },
         { u"case", CASE },
         { u"default", DEFAULT },
         { u"if", IF },
         { u"else", ELSE },
         { u"switch", SWITCH },
         { u"while", WHILE },
         { u"do", DO },
         { u"for", FOR },
         { u"break", BREAK },
         { u"continue", CONTINUE },
         { u"return", RETURN },
         { u"goto", GOTO },
         { u"try", TRY },
         { u"catch", CATCH },
         { nullptr, -1 }
    };
    static soul::lexer::KeywordMap<char16_t> keywordMap(keywords);
    return &keywordMap;
}

template<>
soul::lexer::KeywordMap<char32_t>* GetKeywords<char32_t>()
{
    static const soul::lexer::Keyword<char32_t> keywords[] = {
         { U"main", MAIN },
         { U"start", START },
         { U"empty", EMPTY },
         { U"any", ANY },
         { U"var", VAR },
         { U"project", PROJECT },
         { U"export", EXPORT },
         { U"module", MODULE },
         { U"import", IMPORT },
         { U"implementation", IMPLEMENTATION },
         { U"interface", INTERFACE },
         { U"parser", PARSER },
         { U"lexer", LEXER },
         { U"tokens", TOKENS },
         { U"keywords", KEYWORDS },
         { U"expressions", EXPRESSIONS },
         { U"rules", RULES },
         { U"variables", VARIABLES },
         { U"actions", ACTIONS },
         { U"auto", AUTO },
         { U"register", REGISTER },
         { U"static", STATIC },
         { U"extern", EXTERN },
         { U"mutable", MUTABLE },
         { U"char", CHAR },
         { U"char8_t", CHAR8T },
         { U"char16_t", CHAR16T },
         { U"char32_t", CHAR32T },
         { U"wchar_t", WCHART },
         { U"bool", BOOL },
         { U"short", SHORT },
         { U"int", INT },
         { U"long", LONG },
         { U"signed", SIGNED },
         { U"unsigned", UNSIGNED },
         { U"float", FLOAT },
         { U"double", DOUBLE },
         { U"void", VOID },
         { U"typedef", TYPEDEF },
         { U"const", CONST },
         { U"volatile", VOLATILE },
         { U"using", USING },
         { U"namespace", NAMESPACE },
         { U"throw", THROW },
         { U"sizeof", SIZEOF },
         { U"operator", OPERATOR },
         { U"dynamic_cast", DYNAMIC_CAST },
         { U"static_cast", STATIC_CAST },
         { U"reinterpret_cast", REINTERPRET_CAST },
         { U"const_cast", CONST_CAST },
         { U"typeid", TYPEID },
         { U"this", THIS },
         { U"new", NEW },
         { U"delete", DELETE },
         { U"true", TRUE },
         { U"false", FALSE },
         { U"nullptr", NULLPTR },
         { U"case", CASE },
         { U"default", DEFAULT },
         { U"if", IF },
         { U"else", ELSE },
         { U"switch", SWITCH },
         { U"while", WHILE },
         { U"do", DO },
         { U"for", FOR },
         { U"break", BREAK },
         { U"continue", CONTINUE },
         { U"return", RETURN },
         { U"goto", GOTO },
         { U"try", TRY },
         { U"catch", CATCH },
         { nullptr, -1 }
    };
    static soul::lexer::KeywordMap<char32_t> keywordMap(keywords);
    return &keywordMap;
}

} // namespace soul::token::lexer
