// this file has been automatically generated from 'C:/work/soul-mod/tools/cpp2html/cpp_token_lexer.lexer' using soul lexer generator slg version 4.1.0

module cpp.token.lexer;

using namespace cpp::token;

namespace cpp::token::lexer {

soul::ast::slg::TokenCollection* GetTokens()
{
    static soul::ast::slg::TokenCollection tokens("cpp.token.lexer.tokens");
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
        tokens.AddToken(new soul::ast::slg::Token(IMPORT, "IMPORT", "'import'"));
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
        tokens.AddToken(new soul::ast::slg::Token(MODULE, "MODULE", "'module"));
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
        tokens.AddToken(new soul::ast::slg::Token(FLOATLIT, "FLOATLIT", "floating literal"));
        tokens.AddToken(new soul::ast::slg::Token(INTLIT, "INTLIT", "integer literal"));
        tokens.AddToken(new soul::ast::slg::Token(CHARLIT, "CHARLIT", "character literal"));
        tokens.AddToken(new soul::ast::slg::Token(STRINGLIT, "STRINGLIT", "string literal"));
        tokens.AddToken(new soul::ast::slg::Token(BEGINRAWSTRINGLIT, "BEGINRAWSTRINGLIT", "'begin raw string literal'"));
        tokens.AddToken(new soul::ast::slg::Token(COLONCOLON, "COLONCOLON", "'::'"));
        tokens.AddToken(new soul::ast::slg::Token(COMMA, "COMMA", "','"));
        tokens.AddToken(new soul::ast::slg::Token(ASSIGN, "ASSIGN", "'='"));
        tokens.AddToken(new soul::ast::slg::Token(MULASSIGN, "MULASSIGN", "'*='"));
        tokens.AddToken(new soul::ast::slg::Token(DIVASSIGN, "DIVASSIGN", "'/='"));
        tokens.AddToken(new soul::ast::slg::Token(REMASSIGN, "REMASSIGN", "'%='"));
        tokens.AddToken(new soul::ast::slg::Token(ADDASSIGN, "ADDASSIGN", "'+='"));
        tokens.AddToken(new soul::ast::slg::Token(SUBASSIGN, "SUBASSIGN", "'-='"));
        tokens.AddToken(new soul::ast::slg::Token(SHIFTRIGHTASSIGN, "SHIFTRIGHTASSIGN", "'>>='"));
        tokens.AddToken(new soul::ast::slg::Token(SHIFTLEFTASSIGN, "SHIFTLEFTASSIGN", "'<<='"));
        tokens.AddToken(new soul::ast::slg::Token(ANDASSIGN, "ANDASSIGN", "'&='"));
        tokens.AddToken(new soul::ast::slg::Token(XORASSIGN, "XORASSIGN", "'^='"));
        tokens.AddToken(new soul::ast::slg::Token(ORASSIGN, "ORASSIGN", "'|='"));
        tokens.AddToken(new soul::ast::slg::Token(QUEST, "QUEST", "'?'"));
        tokens.AddToken(new soul::ast::slg::Token(COLON, "COLON", "':'"));
        tokens.AddToken(new soul::ast::slg::Token(OROR, "OROR", "'||'"));
        tokens.AddToken(new soul::ast::slg::Token(AMPAMP, "AMPAMP", "'&&'"));
        tokens.AddToken(new soul::ast::slg::Token(OR, "OR", "'|'"));
        tokens.AddToken(new soul::ast::slg::Token(XOR, "XOR", "'^'"));
        tokens.AddToken(new soul::ast::slg::Token(AMP, "AMP", "'&'"));
        tokens.AddToken(new soul::ast::slg::Token(EQ, "EQ", "'=='"));
        tokens.AddToken(new soul::ast::slg::Token(NEQ, "NEQ", "'!='"));
        tokens.AddToken(new soul::ast::slg::Token(LEQ, "LEQ", "'<='"));
        tokens.AddToken(new soul::ast::slg::Token(GEQ, "GEQ", "'>='"));
        tokens.AddToken(new soul::ast::slg::Token(SPACESHIP, "SPACESHIP", "<=>"));
        tokens.AddToken(new soul::ast::slg::Token(LANGLE, "LANGLE", "'<'"));
        tokens.AddToken(new soul::ast::slg::Token(RANGLE, "RANGLE", "'>'"));
        tokens.AddToken(new soul::ast::slg::Token(SHIFTLEFT, "SHIFTLEFT", "'<<'"));
        tokens.AddToken(new soul::ast::slg::Token(SHIFTRIGHT, "SHIFTRIGHT", "'>>'"));
        tokens.AddToken(new soul::ast::slg::Token(PLUS, "PLUS", "'+'"));
        tokens.AddToken(new soul::ast::slg::Token(MINUS, "MINUS", "'-'"));
        tokens.AddToken(new soul::ast::slg::Token(STAR, "STAR", "'*'"));
        tokens.AddToken(new soul::ast::slg::Token(DIV, "DIV", "'/'"));
        tokens.AddToken(new soul::ast::slg::Token(MOD, "MOD", "'%'"));
        tokens.AddToken(new soul::ast::slg::Token(DOTSTAR, "DOTSTAR", "'.*'"));
        tokens.AddToken(new soul::ast::slg::Token(ARROWSTAR, "ARROWSTAR", "'->*'"));
        tokens.AddToken(new soul::ast::slg::Token(LPAREN, "LPAREN", "'('"));
        tokens.AddToken(new soul::ast::slg::Token(RPAREN, "RPAREN", "')'"));
        tokens.AddToken(new soul::ast::slg::Token(PLUSPLUS, "PLUSPLUS", "'++'"));
        tokens.AddToken(new soul::ast::slg::Token(MINUSMINUS, "MINUSMINUS", "'--'"));
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
        tokens.AddToken(new soul::ast::slg::Token(WS, "WS", "white space"));
        tokens.AddToken(new soul::ast::slg::Token(LINECOMMENT, "LINECOMMENT", "line comment"));
        tokens.AddToken(new soul::ast::slg::Token(BLOCKCOMMENT, "BLOCKCOMMENT", "block comment"));
        tokens.AddToken(new soul::ast::slg::Token(BLOCKCOMMENTLINE, "BLOCKCOMMENTLINE", "block comment line"));
        tokens.AddToken(new soul::ast::slg::Token(KEYWORD, "KEYWORD", "keyword"));
        tokens.AddToken(new soul::ast::slg::Token(ID, "ID", "identifier"));
        tokens.AddToken(new soul::ast::slg::Token(NUMBER, "NUMBER", "number"));
        tokens.AddToken(new soul::ast::slg::Token(PP, "PP", "pp"));
        tokens.AddToken(new soul::ast::slg::Token(OTHER, "OTHER", "other"));
        tokens.AddToken(new soul::ast::slg::Token(__THREAD, "__THREAD", "'__thread'"));
        tokens.AddToken(new soul::ast::slg::Token(__DECLSPEC, "__DECLSPEC", "'__declspec'"));
        tokens.AddToken(new soul::ast::slg::Token(__CDECL, "__CDECL", "'__cdecl'"));
        tokens.AddToken(new soul::ast::slg::Token(__FASTCALL, "__FASTCALL", "'__fastcall'"));
        tokens.AddToken(new soul::ast::slg::Token(__STDCALL, "__STDCALL", "'__stdcall'"));
        tokens.AddToken(new soul::ast::slg::Token(__THISCALL, "__THISCALL", "'__thiscall'"));
        tokens.AddToken(new soul::ast::slg::Token(__VECTORCALL, "__VECTORCALL", "'__vectorcall'"));
        tokens.AddToken(new soul::ast::slg::Token(__INT64, "__INT64", "'__int64'"));
        tokens.AddToken(new soul::ast::slg::Token(__INT32, "__INT32", "'__int32'"));
        tokens.AddToken(new soul::ast::slg::Token(__INT16, "__INT16", "'__int16'"));
        tokens.AddToken(new soul::ast::slg::Token(__INT8, "__INT8", "'__int8'"));
        tokens.AddToken(new soul::ast::slg::Token(__UNALIGNED, "__UNALIGNED", "'__unaligned'"));
        tokens.AddToken(new soul::ast::slg::Token(__INLINE, "__INLINE", "'__inline'"));
        tokens.AddToken(new soul::ast::slg::Token(__NULLPTR, "__NULLPTR", "'__nullptr'"));
        tokens.AddToken(new soul::ast::slg::Token(__PRAGMA, "__PRAGMA", "'__pragma'"));
        tokens.AddToken(new soul::ast::slg::Token(MAX, "MAX", "max"));
    }
    return &tokens;
}

CppTokenLexer_Variables::CppTokenLexer_Variables() :
    inBlockComment()
{
}

std::mutex mtx;

std::mutex& MakeLexerMtx() { return mtx; }

template<>
soul::lexer::KeywordMap<char>* GetKeywords<char>()
{
    static const soul::lexer::Keyword<char> keywords[] = {
         { "alignas", ALIGNAS },
         { "alignof", ALIGNOF },
         { "asm", ASM },
         { "auto", AUTO },
         { "bool", BOOL },
         { "break", BREAK },
         { "case", CASE },
         { "catch", CATCH },
         { "char", CHAR },
         { "char8_t", CHAR8_T },
         { "char16_t", CHAR16_T },
         { "char32_t", CHAR32_T },
         { "class", CLASS },
         { "concept", CONCEPT },
         { "const", CONST },
         { "consteval", CONSTEVAL },
         { "constexpr", CONSTEXPR },
         { "constinit", CONSTINIT },
         { "const_cast", CONST_CAST },
         { "continue", CONTINUE },
         { "co_await", CO_AWAIT },
         { "co_return", CO_RETURN },
         { "co_yield", CO_YIELD },
         { "decltype", DECLTYPE },
         { "default", DEFAULT },
         { "delete", DELETE },
         { "do", DO },
         { "double", DOUBLE },
         { "dynamic_cast", DYNAMIC_CAST },
         { "else", ELSE },
         { "enum", ENUM },
         { "explicit", EXPLICIT },
         { "export", EXPORT },
         { "extern", EXTERN },
         { "false", FALSE },
         { "float", FLOAT },
         { "for", FOR },
         { "friend", FRIEND },
         { "goto", GOTO },
         { "if", IF },
         { "import", IMPORT },
         { "inline", INLINE },
         { "int", INT },
         { "long", LONG },
         { "module", MODULE },
         { "mutable", MUTABLE },
         { "namespace", NAMESPACE },
         { "new", NEW },
         { "noexcept", NOEXCEPT },
         { "nullptr", NULLPTR },
         { "operator", OPERATOR },
         { "private", PRIVATE },
         { "protected", PROTECTED },
         { "public", PUBLIC },
         { "register", REGISTER },
         { "reinterpret_cast", REINTERPRET_CAST },
         { "requires", REQUIRES },
         { "return", RETURN },
         { "short", SHORT },
         { "signed", SIGNED },
         { "sizeof", SIZEOF },
         { "static", STATIC },
         { "static_assert", STATIC_ASSERT },
         { "static_cast", STATIC_CAST },
         { "struct", STRUCT },
         { "switch", SWITCH },
         { "template", TEMPLATE },
         { "this", THIS },
         { "thread_local", THREAD_LOCAL },
         { "throw", THROW },
         { "true", TRUE },
         { "try", TRY },
         { "typedef", TYPEDEF },
         { "typeid", TYPEID },
         { "typename", TYPENAME },
         { "union", UNION },
         { "unsigned", UNSIGNED },
         { "using", USING },
         { "virtual", VIRTUAL },
         { "void", VOID },
         { "volatile", VOLATILE },
         { "wchar_t", WCHAR_T },
         { "while", WHILE },
         { "__thread", __THREAD },
         { "__declspec", __DECLSPEC },
         { "__cdecl", __CDECL },
         { "__fastcall", __FASTCALL },
         { "__stdcall", __STDCALL },
         { "__thiscall", __THISCALL },
         { "__vectorcall", __VECTORCALL },
         { "__int64", __INT64 },
         { "__int32", __INT32 },
         { "__int16", __INT16 },
         { "__int8", __INT8 },
         { "__unaligned", __UNALIGNED },
         { "__inline", __INLINE },
         { "__nullptr", __NULLPTR },
         { "__pragma", __PRAGMA },
         { nullptr, -1 }
    };
    static soul::lexer::KeywordMap<char> keywordMap(keywords);
    return &keywordMap;
}

template<>
soul::lexer::KeywordMap<char8_t>* GetKeywords<char8_t>()
{
    static const soul::lexer::Keyword<char8_t> keywords[] = {
         { u8"alignas", ALIGNAS },
         { u8"alignof", ALIGNOF },
         { u8"asm", ASM },
         { u8"auto", AUTO },
         { u8"bool", BOOL },
         { u8"break", BREAK },
         { u8"case", CASE },
         { u8"catch", CATCH },
         { u8"char", CHAR },
         { u8"char8_t", CHAR8_T },
         { u8"char16_t", CHAR16_T },
         { u8"char32_t", CHAR32_T },
         { u8"class", CLASS },
         { u8"concept", CONCEPT },
         { u8"const", CONST },
         { u8"consteval", CONSTEVAL },
         { u8"constexpr", CONSTEXPR },
         { u8"constinit", CONSTINIT },
         { u8"const_cast", CONST_CAST },
         { u8"continue", CONTINUE },
         { u8"co_await", CO_AWAIT },
         { u8"co_return", CO_RETURN },
         { u8"co_yield", CO_YIELD },
         { u8"decltype", DECLTYPE },
         { u8"default", DEFAULT },
         { u8"delete", DELETE },
         { u8"do", DO },
         { u8"double", DOUBLE },
         { u8"dynamic_cast", DYNAMIC_CAST },
         { u8"else", ELSE },
         { u8"enum", ENUM },
         { u8"explicit", EXPLICIT },
         { u8"export", EXPORT },
         { u8"extern", EXTERN },
         { u8"false", FALSE },
         { u8"float", FLOAT },
         { u8"for", FOR },
         { u8"friend", FRIEND },
         { u8"goto", GOTO },
         { u8"if", IF },
         { u8"import", IMPORT },
         { u8"inline", INLINE },
         { u8"int", INT },
         { u8"long", LONG },
         { u8"module", MODULE },
         { u8"mutable", MUTABLE },
         { u8"namespace", NAMESPACE },
         { u8"new", NEW },
         { u8"noexcept", NOEXCEPT },
         { u8"nullptr", NULLPTR },
         { u8"operator", OPERATOR },
         { u8"private", PRIVATE },
         { u8"protected", PROTECTED },
         { u8"public", PUBLIC },
         { u8"register", REGISTER },
         { u8"reinterpret_cast", REINTERPRET_CAST },
         { u8"requires", REQUIRES },
         { u8"return", RETURN },
         { u8"short", SHORT },
         { u8"signed", SIGNED },
         { u8"sizeof", SIZEOF },
         { u8"static", STATIC },
         { u8"static_assert", STATIC_ASSERT },
         { u8"static_cast", STATIC_CAST },
         { u8"struct", STRUCT },
         { u8"switch", SWITCH },
         { u8"template", TEMPLATE },
         { u8"this", THIS },
         { u8"thread_local", THREAD_LOCAL },
         { u8"throw", THROW },
         { u8"true", TRUE },
         { u8"try", TRY },
         { u8"typedef", TYPEDEF },
         { u8"typeid", TYPEID },
         { u8"typename", TYPENAME },
         { u8"union", UNION },
         { u8"unsigned", UNSIGNED },
         { u8"using", USING },
         { u8"virtual", VIRTUAL },
         { u8"void", VOID },
         { u8"volatile", VOLATILE },
         { u8"wchar_t", WCHAR_T },
         { u8"while", WHILE },
         { u8"__thread", __THREAD },
         { u8"__declspec", __DECLSPEC },
         { u8"__cdecl", __CDECL },
         { u8"__fastcall", __FASTCALL },
         { u8"__stdcall", __STDCALL },
         { u8"__thiscall", __THISCALL },
         { u8"__vectorcall", __VECTORCALL },
         { u8"__int64", __INT64 },
         { u8"__int32", __INT32 },
         { u8"__int16", __INT16 },
         { u8"__int8", __INT8 },
         { u8"__unaligned", __UNALIGNED },
         { u8"__inline", __INLINE },
         { u8"__nullptr", __NULLPTR },
         { u8"__pragma", __PRAGMA },
         { nullptr, -1 }
    };
    static soul::lexer::KeywordMap<char8_t> keywordMap(keywords);
    return &keywordMap;
}

template<>
soul::lexer::KeywordMap<char16_t>* GetKeywords<char16_t>()
{
    static const soul::lexer::Keyword<char16_t> keywords[] = {
         { u"alignas", ALIGNAS },
         { u"alignof", ALIGNOF },
         { u"asm", ASM },
         { u"auto", AUTO },
         { u"bool", BOOL },
         { u"break", BREAK },
         { u"case", CASE },
         { u"catch", CATCH },
         { u"char", CHAR },
         { u"char8_t", CHAR8_T },
         { u"char16_t", CHAR16_T },
         { u"char32_t", CHAR32_T },
         { u"class", CLASS },
         { u"concept", CONCEPT },
         { u"const", CONST },
         { u"consteval", CONSTEVAL },
         { u"constexpr", CONSTEXPR },
         { u"constinit", CONSTINIT },
         { u"const_cast", CONST_CAST },
         { u"continue", CONTINUE },
         { u"co_await", CO_AWAIT },
         { u"co_return", CO_RETURN },
         { u"co_yield", CO_YIELD },
         { u"decltype", DECLTYPE },
         { u"default", DEFAULT },
         { u"delete", DELETE },
         { u"do", DO },
         { u"double", DOUBLE },
         { u"dynamic_cast", DYNAMIC_CAST },
         { u"else", ELSE },
         { u"enum", ENUM },
         { u"explicit", EXPLICIT },
         { u"export", EXPORT },
         { u"extern", EXTERN },
         { u"false", FALSE },
         { u"float", FLOAT },
         { u"for", FOR },
         { u"friend", FRIEND },
         { u"goto", GOTO },
         { u"if", IF },
         { u"import", IMPORT },
         { u"inline", INLINE },
         { u"int", INT },
         { u"long", LONG },
         { u"module", MODULE },
         { u"mutable", MUTABLE },
         { u"namespace", NAMESPACE },
         { u"new", NEW },
         { u"noexcept", NOEXCEPT },
         { u"nullptr", NULLPTR },
         { u"operator", OPERATOR },
         { u"private", PRIVATE },
         { u"protected", PROTECTED },
         { u"public", PUBLIC },
         { u"register", REGISTER },
         { u"reinterpret_cast", REINTERPRET_CAST },
         { u"requires", REQUIRES },
         { u"return", RETURN },
         { u"short", SHORT },
         { u"signed", SIGNED },
         { u"sizeof", SIZEOF },
         { u"static", STATIC },
         { u"static_assert", STATIC_ASSERT },
         { u"static_cast", STATIC_CAST },
         { u"struct", STRUCT },
         { u"switch", SWITCH },
         { u"template", TEMPLATE },
         { u"this", THIS },
         { u"thread_local", THREAD_LOCAL },
         { u"throw", THROW },
         { u"true", TRUE },
         { u"try", TRY },
         { u"typedef", TYPEDEF },
         { u"typeid", TYPEID },
         { u"typename", TYPENAME },
         { u"union", UNION },
         { u"unsigned", UNSIGNED },
         { u"using", USING },
         { u"virtual", VIRTUAL },
         { u"void", VOID },
         { u"volatile", VOLATILE },
         { u"wchar_t", WCHAR_T },
         { u"while", WHILE },
         { u"__thread", __THREAD },
         { u"__declspec", __DECLSPEC },
         { u"__cdecl", __CDECL },
         { u"__fastcall", __FASTCALL },
         { u"__stdcall", __STDCALL },
         { u"__thiscall", __THISCALL },
         { u"__vectorcall", __VECTORCALL },
         { u"__int64", __INT64 },
         { u"__int32", __INT32 },
         { u"__int16", __INT16 },
         { u"__int8", __INT8 },
         { u"__unaligned", __UNALIGNED },
         { u"__inline", __INLINE },
         { u"__nullptr", __NULLPTR },
         { u"__pragma", __PRAGMA },
         { nullptr, -1 }
    };
    static soul::lexer::KeywordMap<char16_t> keywordMap(keywords);
    return &keywordMap;
}

template<>
soul::lexer::KeywordMap<char32_t>* GetKeywords<char32_t>()
{
    static const soul::lexer::Keyword<char32_t> keywords[] = {
         { U"alignas", ALIGNAS },
         { U"alignof", ALIGNOF },
         { U"asm", ASM },
         { U"auto", AUTO },
         { U"bool", BOOL },
         { U"break", BREAK },
         { U"case", CASE },
         { U"catch", CATCH },
         { U"char", CHAR },
         { U"char8_t", CHAR8_T },
         { U"char16_t", CHAR16_T },
         { U"char32_t", CHAR32_T },
         { U"class", CLASS },
         { U"concept", CONCEPT },
         { U"const", CONST },
         { U"consteval", CONSTEVAL },
         { U"constexpr", CONSTEXPR },
         { U"constinit", CONSTINIT },
         { U"const_cast", CONST_CAST },
         { U"continue", CONTINUE },
         { U"co_await", CO_AWAIT },
         { U"co_return", CO_RETURN },
         { U"co_yield", CO_YIELD },
         { U"decltype", DECLTYPE },
         { U"default", DEFAULT },
         { U"delete", DELETE },
         { U"do", DO },
         { U"double", DOUBLE },
         { U"dynamic_cast", DYNAMIC_CAST },
         { U"else", ELSE },
         { U"enum", ENUM },
         { U"explicit", EXPLICIT },
         { U"export", EXPORT },
         { U"extern", EXTERN },
         { U"false", FALSE },
         { U"float", FLOAT },
         { U"for", FOR },
         { U"friend", FRIEND },
         { U"goto", GOTO },
         { U"if", IF },
         { U"import", IMPORT },
         { U"inline", INLINE },
         { U"int", INT },
         { U"long", LONG },
         { U"module", MODULE },
         { U"mutable", MUTABLE },
         { U"namespace", NAMESPACE },
         { U"new", NEW },
         { U"noexcept", NOEXCEPT },
         { U"nullptr", NULLPTR },
         { U"operator", OPERATOR },
         { U"private", PRIVATE },
         { U"protected", PROTECTED },
         { U"public", PUBLIC },
         { U"register", REGISTER },
         { U"reinterpret_cast", REINTERPRET_CAST },
         { U"requires", REQUIRES },
         { U"return", RETURN },
         { U"short", SHORT },
         { U"signed", SIGNED },
         { U"sizeof", SIZEOF },
         { U"static", STATIC },
         { U"static_assert", STATIC_ASSERT },
         { U"static_cast", STATIC_CAST },
         { U"struct", STRUCT },
         { U"switch", SWITCH },
         { U"template", TEMPLATE },
         { U"this", THIS },
         { U"thread_local", THREAD_LOCAL },
         { U"throw", THROW },
         { U"true", TRUE },
         { U"try", TRY },
         { U"typedef", TYPEDEF },
         { U"typeid", TYPEID },
         { U"typename", TYPENAME },
         { U"union", UNION },
         { U"unsigned", UNSIGNED },
         { U"using", USING },
         { U"virtual", VIRTUAL },
         { U"void", VOID },
         { U"volatile", VOLATILE },
         { U"wchar_t", WCHAR_T },
         { U"while", WHILE },
         { U"__thread", __THREAD },
         { U"__declspec", __DECLSPEC },
         { U"__cdecl", __CDECL },
         { U"__fastcall", __FASTCALL },
         { U"__stdcall", __STDCALL },
         { U"__thiscall", __THISCALL },
         { U"__vectorcall", __VECTORCALL },
         { U"__int64", __INT64 },
         { U"__int32", __INT32 },
         { U"__int16", __INT16 },
         { U"__int8", __INT8 },
         { U"__unaligned", __UNALIGNED },
         { U"__inline", __INLINE },
         { U"__nullptr", __NULLPTR },
         { U"__pragma", __PRAGMA },
         { nullptr, -1 }
    };
    static soul::lexer::KeywordMap<char32_t> keywordMap(keywords);
    return &keywordMap;
}

} // namespace cpp::token::lexer
