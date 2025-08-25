// this file has been automatically generated from 'D:/work/soul-mod/soul_expected/lex_expected/slg.lexer' using soul lexer generator eslg version 5.0.0

module soul_expected.lex.slg;

using namespace soul_expected::cpp::token;
using namespace soul_expected::cpp::op::token;
using namespace soul_expected::punctuation::token;
using namespace soul_expected::tool::token;

namespace soul_expected::lex::slg {

soul_expected::ast::common::TokenCollection* GetTokens()
{
    static soul_expected::ast::common::TokenCollection tokens("soul_expected.lex.slg.tokens");
    if (!tokens.Initialized())
    {
        tokens.SetInitialized();
        tokens.AddToken(new soul_expected::ast::common::Token(AUTO, "AUTO", "'auto'"));
        tokens.AddToken(new soul_expected::ast::common::Token(REGISTER, "REGISTER", "'register'"));
        tokens.AddToken(new soul_expected::ast::common::Token(STATIC, "STATIC", "'static'"));
        tokens.AddToken(new soul_expected::ast::common::Token(EXTERN, "EXTERN", "'extern'"));
        tokens.AddToken(new soul_expected::ast::common::Token(MUTABLE, "MUTABLE", "'mutable'"));
        tokens.AddToken(new soul_expected::ast::common::Token(EXPORT, "EXPORT", "'export'"));
        tokens.AddToken(new soul_expected::ast::common::Token(IMPORT, "IMPORT", "'import'"));
        tokens.AddToken(new soul_expected::ast::common::Token(MODULE, "MODULE", "'module"));
        tokens.AddToken(new soul_expected::ast::common::Token(CHAR, "CHAR", "'char'"));
        tokens.AddToken(new soul_expected::ast::common::Token(CHAR8T, "CHAR8T", "'char8_t'"));
        tokens.AddToken(new soul_expected::ast::common::Token(CHAR16T, "CHAR16T", "'char16_t'"));
        tokens.AddToken(new soul_expected::ast::common::Token(CHAR32T, "CHAR32T", "'char32_t'"));
        tokens.AddToken(new soul_expected::ast::common::Token(WCHART, "WCHART", "'wchar_t'"));
        tokens.AddToken(new soul_expected::ast::common::Token(BOOL, "BOOL", "'bool'"));
        tokens.AddToken(new soul_expected::ast::common::Token(SHORT, "SHORT", "'short'"));
        tokens.AddToken(new soul_expected::ast::common::Token(INT, "INT", "'int'"));
        tokens.AddToken(new soul_expected::ast::common::Token(LONG, "LONG", "'long'"));
        tokens.AddToken(new soul_expected::ast::common::Token(SIGNED, "SIGNED", "'signed'"));
        tokens.AddToken(new soul_expected::ast::common::Token(UNSIGNED, "UNSIGNED", "'unsigned'"));
        tokens.AddToken(new soul_expected::ast::common::Token(FLOAT, "FLOAT", "'float'"));
        tokens.AddToken(new soul_expected::ast::common::Token(DOUBLE, "DOUBLE", "'double'"));
        tokens.AddToken(new soul_expected::ast::common::Token(VOID, "VOID", "'void'"));
        tokens.AddToken(new soul_expected::ast::common::Token(TYPEDEF, "TYPEDEF", "'typedef'"));
        tokens.AddToken(new soul_expected::ast::common::Token(CONST, "CONST", "'const'"));
        tokens.AddToken(new soul_expected::ast::common::Token(VOLATILE, "VOLATILE", "'volatile'"));
        tokens.AddToken(new soul_expected::ast::common::Token(USING, "USING", "'using'"));
        tokens.AddToken(new soul_expected::ast::common::Token(NAMESPACE, "NAMESPACE", "'namespace'"));
        tokens.AddToken(new soul_expected::ast::common::Token(THROW, "THROW", "'throw'"));
        tokens.AddToken(new soul_expected::ast::common::Token(SIZEOF, "SIZEOF", "'sizeof'"));
        tokens.AddToken(new soul_expected::ast::common::Token(OPERATOR, "OPERATOR", "'operator'"));
        tokens.AddToken(new soul_expected::ast::common::Token(DYNAMIC_CAST, "DYNAMIC_CAST", "'dynamic_cast'"));
        tokens.AddToken(new soul_expected::ast::common::Token(STATIC_CAST, "STATIC_CAST", "'static_cast'"));
        tokens.AddToken(new soul_expected::ast::common::Token(REINTERPRET_CAST, "REINTERPRET_CAST", "'reinterpret_cast'"));
        tokens.AddToken(new soul_expected::ast::common::Token(CONST_CAST, "CONST_CAST", "'const_cast'"));
        tokens.AddToken(new soul_expected::ast::common::Token(TYPEID, "TYPEID", "'typeid'"));
        tokens.AddToken(new soul_expected::ast::common::Token(THIS, "THIS", "'this'"));
        tokens.AddToken(new soul_expected::ast::common::Token(NEW, "NEW", "'new'"));
        tokens.AddToken(new soul_expected::ast::common::Token(DELETE, "DELETE", "'delete'"));
        tokens.AddToken(new soul_expected::ast::common::Token(TRUE, "TRUE", "'true'"));
        tokens.AddToken(new soul_expected::ast::common::Token(FALSE, "FALSE", "'false'"));
        tokens.AddToken(new soul_expected::ast::common::Token(NULLPTR, "NULLPTR", "'nullptr'"));
        tokens.AddToken(new soul_expected::ast::common::Token(CASE, "CASE", "'case'"));
        tokens.AddToken(new soul_expected::ast::common::Token(DEFAULT, "DEFAULT", "'default'"));
        tokens.AddToken(new soul_expected::ast::common::Token(IF, "IF", "'if'"));
        tokens.AddToken(new soul_expected::ast::common::Token(ELSE, "ELSE", "'else'"));
        tokens.AddToken(new soul_expected::ast::common::Token(SWITCH, "SWITCH", "'switch'"));
        tokens.AddToken(new soul_expected::ast::common::Token(WHILE, "WHILE", "'while'"));
        tokens.AddToken(new soul_expected::ast::common::Token(DO, "DO", "'do'"));
        tokens.AddToken(new soul_expected::ast::common::Token(FOR, "FOR", "'for'"));
        tokens.AddToken(new soul_expected::ast::common::Token(BREAK, "BREAK", "'break'"));
        tokens.AddToken(new soul_expected::ast::common::Token(CONTINUE, "CONTINUE", "'continue'"));
        tokens.AddToken(new soul_expected::ast::common::Token(RETURN, "RETURN", "'return'"));
        tokens.AddToken(new soul_expected::ast::common::Token(GOTO, "GOTO", "'goto'"));
        tokens.AddToken(new soul_expected::ast::common::Token(TRY, "TRY", "'try'"));
        tokens.AddToken(new soul_expected::ast::common::Token(CATCH, "CATCH", "'catch'"));
        tokens.AddToken(new soul_expected::ast::common::Token(ID, "ID", "identifier"));
        tokens.AddToken(new soul_expected::ast::common::Token(INTEGER_LITERAL, "INTEGER_LITERAL", "integer literal"));
        tokens.AddToken(new soul_expected::ast::common::Token(FLOATING_LITERAL, "FLOATING_LITERAL", "floating literal"));
        tokens.AddToken(new soul_expected::ast::common::Token(CHAR_LITERAL, "CHAR_LITERAL", "character literal"));
        tokens.AddToken(new soul_expected::ast::common::Token(STRING_LITERAL, "STRING_LITERAL", "string literal"));
        tokens.AddToken(new soul_expected::ast::common::Token(DISJUNCTION, "DISJUNCTION", "'||'"));
        tokens.AddToken(new soul_expected::ast::common::Token(AMP_AMP, "AMP_AMP", "'&&'"));
        tokens.AddToken(new soul_expected::ast::common::Token(DOT_STAR, "DOT_STAR", "'.*'"));
        tokens.AddToken(new soul_expected::ast::common::Token(ARROW_STAR, "ARROW_STAR", "'->*'"));
        tokens.AddToken(new soul_expected::ast::common::Token(EQ, "EQ", "'=='"));
        tokens.AddToken(new soul_expected::ast::common::Token(NEQ, "NEQ", "'!='"));
        tokens.AddToken(new soul_expected::ast::common::Token(LEQ, "LEQ", "'<='"));
        tokens.AddToken(new soul_expected::ast::common::Token(GEQ, "GEQ", "'>='"));
        tokens.AddToken(new soul_expected::ast::common::Token(SHIFT_LEFT, "SHIFT_LEFT", "'<<'"));
        tokens.AddToken(new soul_expected::ast::common::Token(SHIFT_RIGHT, "SHIFT_RIGHT", "'>>'"));
        tokens.AddToken(new soul_expected::ast::common::Token(PLUS, "PLUS", "'+'"));
        tokens.AddToken(new soul_expected::ast::common::Token(MINUS, "MINUS", "'-'"));
        tokens.AddToken(new soul_expected::ast::common::Token(STAR, "STAR", "'*'"));
        tokens.AddToken(new soul_expected::ast::common::Token(DIV, "DIV", "'/'"));
        tokens.AddToken(new soul_expected::ast::common::Token(REM, "REM", "'%'"));
        tokens.AddToken(new soul_expected::ast::common::Token(PLUS_PLUS, "PLUS_PLUS", "'++'"));
        tokens.AddToken(new soul_expected::ast::common::Token(MINUS_MINUS, "MINUS_MINUS", "'--'"));
        tokens.AddToken(new soul_expected::ast::common::Token(ELLIPSIS, "ELLIPSIS", "'...'"));
        tokens.AddToken(new soul_expected::ast::common::Token(COLON_COLON, "COLON_COLON", "'::'"));
        tokens.AddToken(new soul_expected::ast::common::Token(ASSIGN, "ASSIGN", "'='"));
        tokens.AddToken(new soul_expected::ast::common::Token(MUL_ASSIGN, "MUL_ASSIGN", "'*='"));
        tokens.AddToken(new soul_expected::ast::common::Token(DIV_ASSIGN, "DIV_ASSIGN", "'/='"));
        tokens.AddToken(new soul_expected::ast::common::Token(REM_ASSIGN, "REM_ASSIGN", "'%='"));
        tokens.AddToken(new soul_expected::ast::common::Token(PLUS_ASSIGN, "PLUS_ASSIGN", "'+='"));
        tokens.AddToken(new soul_expected::ast::common::Token(MINUS_ASSIGN, "MINUS_ASSIGN", "'-='"));
        tokens.AddToken(new soul_expected::ast::common::Token(SHIFT_LEFT_ASSIGN, "SHIFT_LEFT_ASSIGN", "'<<='"));
        tokens.AddToken(new soul_expected::ast::common::Token(SHIFT_RIGHT_ASSIGN, "SHIFT_RIGHT_ASSIGN", "'>>='"));
        tokens.AddToken(new soul_expected::ast::common::Token(AND_ASSIGN, "AND_ASSIGN", "'&='"));
        tokens.AddToken(new soul_expected::ast::common::Token(XOR_ASSIGN, "XOR_ASSIGN", "'^='"));
        tokens.AddToken(new soul_expected::ast::common::Token(OR_ASSIGN, "OR_ASSIGN", "'|='"));
        tokens.AddToken(new soul_expected::ast::common::Token(DOT, "DOT", "'.'"));
        tokens.AddToken(new soul_expected::ast::common::Token(LPAREN, "LPAREN", "'('"));
        tokens.AddToken(new soul_expected::ast::common::Token(RPAREN, "RPAREN", "')'"));
        tokens.AddToken(new soul_expected::ast::common::Token(LBRACE, "LBRACE", "'{'"));
        tokens.AddToken(new soul_expected::ast::common::Token(RBRACE, "RBRACE", "'}'"));
        tokens.AddToken(new soul_expected::ast::common::Token(LBRACKET, "LBRACKET", "'['"));
        tokens.AddToken(new soul_expected::ast::common::Token(RBRACKET, "RBRACKET", "']'"));
        tokens.AddToken(new soul_expected::ast::common::Token(LANGLE, "LANGLE", "'<'"));
        tokens.AddToken(new soul_expected::ast::common::Token(RANGLE, "RANGLE", "'>'"));
        tokens.AddToken(new soul_expected::ast::common::Token(COLON, "COLON", "':'"));
        tokens.AddToken(new soul_expected::ast::common::Token(SEMICOLON, "SEMICOLON", "';'"));
        tokens.AddToken(new soul_expected::ast::common::Token(HASH, "HASH", "'#'"));
        tokens.AddToken(new soul_expected::ast::common::Token(COMMA, "COMMA", "','"));
        tokens.AddToken(new soul_expected::ast::common::Token(ARROW, "ARROW", "'->'"));
        tokens.AddToken(new soul_expected::ast::common::Token(QUEST, "QUEST", "'?'"));
        tokens.AddToken(new soul_expected::ast::common::Token(AMP, "AMP", "'&'"));
        tokens.AddToken(new soul_expected::ast::common::Token(DOLLAR, "DOLLAR", "'$'"));
        tokens.AddToken(new soul_expected::ast::common::Token(EXCLAMATION, "EXCLAMATION", "'!'"));
        tokens.AddToken(new soul_expected::ast::common::Token(TILDE, "TILDE", "'~'"));
        tokens.AddToken(new soul_expected::ast::common::Token(CARET, "CARET", "'^'"));
        tokens.AddToken(new soul_expected::ast::common::Token(PIPE, "PIPE", "'|'"));
        tokens.AddToken(new soul_expected::ast::common::Token(PRODUCES, "PRODUCES", "'::='"));
        tokens.AddToken(new soul_expected::ast::common::Token(BACKSLASH, "BACKSLASH", "'\'"));
        tokens.AddToken(new soul_expected::ast::common::Token(TOKENS, "TOKENS", "'tokens'"));
        tokens.AddToken(new soul_expected::ast::common::Token(KEYWORDS, "KEYWORDS", "'keywords'"));
        tokens.AddToken(new soul_expected::ast::common::Token(EXPRESSIONS, "EXPRESSIONS", "'expressions'"));
        tokens.AddToken(new soul_expected::ast::common::Token(RULES, "RULES", "'rules'"));
        tokens.AddToken(new soul_expected::ast::common::Token(VARIABLES, "VARIABLES", "''variables'"));
        tokens.AddToken(new soul_expected::ast::common::Token(ACTIONS, "ACTIONS", "'actions'"));
        tokens.AddToken(new soul_expected::ast::common::Token(MAIN, "MAIN", "'main'"));
        tokens.AddToken(new soul_expected::ast::common::Token(START, "START", "'start'"));
        tokens.AddToken(new soul_expected::ast::common::Token(EMPTY, "EMPTY", "'empty'"));
        tokens.AddToken(new soul_expected::ast::common::Token(ANY, "ANY", "'any'"));
        tokens.AddToken(new soul_expected::ast::common::Token(VAR, "VAR", "'var'"));
        tokens.AddToken(new soul_expected::ast::common::Token(FILEPATH, "FILEPATH", "file path"));
        tokens.AddToken(new soul_expected::ast::common::Token(PROJECT, "PROJECT", "'project'"));
        tokens.AddToken(new soul_expected::ast::common::Token(CHARACTER, "CHARACTER", "character"));
        tokens.AddToken(new soul_expected::ast::common::Token(ESCAPE, "ESCAPE", "escape"));
    }
    return &tokens;
}

SlgLexer_Variables::SlgLexer_Variables() :
    leftAngleCount(), matchFilePath()
{
}

std::mutex mtx;

std::mutex& MakeLexerMtx() { return mtx; }

template<>
soul_expected::lexer::KeywordMap<char>* GetKeywords<char>()
{
    static const soul_expected::lexer::Keyword<char> keywords[] = {
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
         { "tokens", TOKENS },
         { "keywords", KEYWORDS },
         { "expressions", EXPRESSIONS },
         { "rules", RULES },
         { "variables", VARIABLES },
         { "actions", ACTIONS },
         { "project", PROJECT },
         { nullptr, -1 }
    };
    static soul_expected::lexer::KeywordMap<char> keywordMap(keywords);
    return &keywordMap;
}

template<>
soul_expected::lexer::KeywordMap<char8_t>* GetKeywords<char8_t>()
{
    static const soul_expected::lexer::Keyword<char8_t> keywords[] = {
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
         { u8"tokens", TOKENS },
         { u8"keywords", KEYWORDS },
         { u8"expressions", EXPRESSIONS },
         { u8"rules", RULES },
         { u8"variables", VARIABLES },
         { u8"actions", ACTIONS },
         { u8"project", PROJECT },
         { nullptr, -1 }
    };
    static soul_expected::lexer::KeywordMap<char8_t> keywordMap(keywords);
    return &keywordMap;
}

template<>
soul_expected::lexer::KeywordMap<char16_t>* GetKeywords<char16_t>()
{
    static const soul_expected::lexer::Keyword<char16_t> keywords[] = {
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
         { u"tokens", TOKENS },
         { u"keywords", KEYWORDS },
         { u"expressions", EXPRESSIONS },
         { u"rules", RULES },
         { u"variables", VARIABLES },
         { u"actions", ACTIONS },
         { u"project", PROJECT },
         { nullptr, -1 }
    };
    static soul_expected::lexer::KeywordMap<char16_t> keywordMap(keywords);
    return &keywordMap;
}

template<>
soul_expected::lexer::KeywordMap<char32_t>* GetKeywords<char32_t>()
{
    static const soul_expected::lexer::Keyword<char32_t> keywords[] = {
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
         { U"tokens", TOKENS },
         { U"keywords", KEYWORDS },
         { U"expressions", EXPRESSIONS },
         { U"rules", RULES },
         { U"variables", VARIABLES },
         { U"actions", ACTIONS },
         { U"project", PROJECT },
         { nullptr, -1 }
    };
    static soul_expected::lexer::KeywordMap<char32_t> keywordMap(keywords);
    return &keywordMap;
}

} // namespace soul_expected::lex::slg
