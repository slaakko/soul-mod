// this file has been automatically generated from 'D:/work/soul-mod/soul_expected/lex_expected/spg.lexer' using soul lexer generator eslg version 5.0.0

module soul_expected.lex.spg;


namespace soul_expected::lex::spg {

soul_expected::ast::common::TokenCollection* GetTokens()
{
    static soul_expected::ast::common::TokenCollection tokens("soul_expected.lex.spg.tokens");
    if (!tokens.Initialized())
    {
        tokens.SetInitialized();
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::token::AUTO, "AUTO", "'auto'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::token::REGISTER, "REGISTER", "'register'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::token::STATIC, "STATIC", "'static'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::token::EXTERN, "EXTERN", "'extern'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::token::MUTABLE, "MUTABLE", "'mutable'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::token::EXPORT, "EXPORT", "'export'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::token::IMPORT, "IMPORT", "'import'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::token::MODULE, "MODULE", "'module"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::token::CHAR, "CHAR", "'char'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::token::CHAR8T, "CHAR8T", "'char8_t'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::token::CHAR16T, "CHAR16T", "'char16_t'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::token::CHAR32T, "CHAR32T", "'char32_t'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::token::WCHART, "WCHART", "'wchar_t'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::token::BOOL, "BOOL", "'bool'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::token::SHORT, "SHORT", "'short'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::token::INT, "INT", "'int'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::token::LONG, "LONG", "'long'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::token::SIGNED, "SIGNED", "'signed'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::token::UNSIGNED, "UNSIGNED", "'unsigned'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::token::FLOAT, "FLOAT", "'float'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::token::DOUBLE, "DOUBLE", "'double'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::token::VOID, "VOID", "'void'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::token::TYPEDEF, "TYPEDEF", "'typedef'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::token::CONST, "CONST", "'const'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::token::VOLATILE, "VOLATILE", "'volatile'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::token::USING, "USING", "'using'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::token::NAMESPACE, "NAMESPACE", "'namespace'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::token::THROW, "THROW", "'throw'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::token::SIZEOF, "SIZEOF", "'sizeof'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::token::OPERATOR, "OPERATOR", "'operator'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::token::DYNAMIC_CAST, "DYNAMIC_CAST", "'dynamic_cast'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::token::STATIC_CAST, "STATIC_CAST", "'static_cast'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::token::REINTERPRET_CAST, "REINTERPRET_CAST", "'reinterpret_cast'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::token::CONST_CAST, "CONST_CAST", "'const_cast'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::token::TYPEID, "TYPEID", "'typeid'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::token::THIS, "THIS", "'this'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::token::NEW, "NEW", "'new'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::token::DELETE, "DELETE", "'delete'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::token::TRUE, "TRUE", "'true'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::token::FALSE, "FALSE", "'false'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::token::NULLPTR, "NULLPTR", "'nullptr'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::token::CASE, "CASE", "'case'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::token::DEFAULT, "DEFAULT", "'default'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::token::IF, "IF", "'if'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::token::ELSE, "ELSE", "'else'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::token::SWITCH, "SWITCH", "'switch'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::token::WHILE, "WHILE", "'while'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::token::DO, "DO", "'do'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::token::FOR, "FOR", "'for'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::token::BREAK, "BREAK", "'break'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::token::CONTINUE, "CONTINUE", "'continue'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::token::RETURN, "RETURN", "'return'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::token::GOTO, "GOTO", "'goto'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::token::TRY, "TRY", "'try'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::token::CATCH, "CATCH", "'catch'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::token::ID, "ID", "identifier"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::token::INTEGER_LITERAL, "INTEGER_LITERAL", "integer literal"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::token::FLOATING_LITERAL, "FLOATING_LITERAL", "floating literal"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::token::CHAR_LITERAL, "CHAR_LITERAL", "character literal"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::token::STRING_LITERAL, "STRING_LITERAL", "string literal"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::op::token::DISJUNCTION, "DISJUNCTION", "'||'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::op::token::AMP_AMP, "AMP_AMP", "'&&'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::op::token::DOT_STAR, "DOT_STAR", "'.*'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::op::token::ARROW_STAR, "ARROW_STAR", "'->*'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::op::token::EQ, "EQ", "'=='"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::op::token::NEQ, "NEQ", "'!='"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::op::token::LEQ, "LEQ", "'<='"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::op::token::GEQ, "GEQ", "'>='"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::op::token::SHIFT_LEFT, "SHIFT_LEFT", "'<<'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::op::token::SHIFT_RIGHT, "SHIFT_RIGHT", "'>>'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::op::token::PLUS, "PLUS", "'+'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::op::token::MINUS, "MINUS", "'-'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::op::token::STAR, "STAR", "'*'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::op::token::DIV, "DIV", "'/'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::op::token::REM, "REM", "'%'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::op::token::PLUS_PLUS, "PLUS_PLUS", "'++'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::op::token::MINUS_MINUS, "MINUS_MINUS", "'--'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::op::token::ELLIPSIS, "ELLIPSIS", "'...'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::op::token::COLON_COLON, "COLON_COLON", "'::'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::op::token::ASSIGN, "ASSIGN", "'='"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::op::token::MUL_ASSIGN, "MUL_ASSIGN", "'*='"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::op::token::DIV_ASSIGN, "DIV_ASSIGN", "'/='"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::op::token::REM_ASSIGN, "REM_ASSIGN", "'%='"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::op::token::PLUS_ASSIGN, "PLUS_ASSIGN", "'+='"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::op::token::MINUS_ASSIGN, "MINUS_ASSIGN", "'-='"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::op::token::SHIFT_LEFT_ASSIGN, "SHIFT_LEFT_ASSIGN", "'<<='"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::op::token::SHIFT_RIGHT_ASSIGN, "SHIFT_RIGHT_ASSIGN", "'>>='"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::op::token::AND_ASSIGN, "AND_ASSIGN", "'&='"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::op::token::XOR_ASSIGN, "XOR_ASSIGN", "'^='"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::cpp::op::token::OR_ASSIGN, "OR_ASSIGN", "'|='"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::punctuation::token::DOT, "DOT", "'.'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::punctuation::token::LPAREN, "LPAREN", "'('"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::punctuation::token::RPAREN, "RPAREN", "')'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::punctuation::token::LBRACE, "LBRACE", "'{'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::punctuation::token::RBRACE, "RBRACE", "'}'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::punctuation::token::LBRACKET, "LBRACKET", "'['"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::punctuation::token::RBRACKET, "RBRACKET", "']'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::punctuation::token::LANGLE, "LANGLE", "'<'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::punctuation::token::RANGLE, "RANGLE", "'>'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::punctuation::token::COLON, "COLON", "':'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::punctuation::token::SEMICOLON, "SEMICOLON", "';'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::punctuation::token::HASH, "HASH", "'#'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::punctuation::token::COMMA, "COMMA", "','"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::punctuation::token::ARROW, "ARROW", "'->'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::punctuation::token::QUEST, "QUEST", "'?'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::punctuation::token::AMP, "AMP", "'&'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::punctuation::token::DOLLAR, "DOLLAR", "'$'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::punctuation::token::EXCLAMATION, "EXCLAMATION", "'!'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::punctuation::token::TILDE, "TILDE", "'~'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::punctuation::token::CARET, "CARET", "'^'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::punctuation::token::PIPE, "PIPE", "'|'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::punctuation::token::PRODUCES, "PRODUCES", "'::='"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::punctuation::token::BACKSLASH, "BACKSLASH", "'\'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::tool::token::TOKENS, "TOKENS", "'tokens'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::tool::token::KEYWORDS, "KEYWORDS", "'keywords'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::tool::token::EXPRESSIONS, "EXPRESSIONS", "'expressions'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::tool::token::RULES, "RULES", "'rules'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::tool::token::VARIABLES, "VARIABLES", "''variables'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::tool::token::ACTIONS, "ACTIONS", "'actions'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::tool::token::MAIN, "MAIN", "'main'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::tool::token::START, "START", "'start'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::tool::token::EMPTY, "EMPTY", "'empty'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::tool::token::ANY, "ANY", "'any'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::tool::token::VAR, "VAR", "'var'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::tool::token::FILEPATH, "FILEPATH", "file path"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::tool::token::PROJECT, "PROJECT", "'project'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::tool::token::CHARACTER, "CHARACTER", "character"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::tool::token::ESCAPE, "ESCAPE", "escape"));
    }
    return &tokens;
}

SpgLexer_Variables::SpgLexer_Variables() :
    leftAngleCount(), matchFilePath()
{
}

std::mutex mtx;

std::mutex& MakeLexerMtx() { return mtx; }

template<>
soul_expected::lexer::KeywordMap<char>* GetKeywords<char>()
{
    static const soul_expected::lexer::Keyword<char> keywords[] = {
         { "auto", soul_expected::cpp::token::AUTO },
         { "register", soul_expected::cpp::token::REGISTER },
         { "static", soul_expected::cpp::token::STATIC },
         { "extern", soul_expected::cpp::token::EXTERN },
         { "mutable", soul_expected::cpp::token::MUTABLE },
         { "char", soul_expected::cpp::token::CHAR },
         { "char8_t", soul_expected::cpp::token::CHAR8T },
         { "char16_t", soul_expected::cpp::token::CHAR16T },
         { "char32_t", soul_expected::cpp::token::CHAR32T },
         { "wchar_t", soul_expected::cpp::token::WCHART },
         { "bool", soul_expected::cpp::token::BOOL },
         { "short", soul_expected::cpp::token::SHORT },
         { "int", soul_expected::cpp::token::INT },
         { "long", soul_expected::cpp::token::LONG },
         { "signed", soul_expected::cpp::token::SIGNED },
         { "unsigned", soul_expected::cpp::token::UNSIGNED },
         { "float", soul_expected::cpp::token::FLOAT },
         { "double", soul_expected::cpp::token::DOUBLE },
         { "void", soul_expected::cpp::token::VOID },
         { "typedef", soul_expected::cpp::token::TYPEDEF },
         { "const", soul_expected::cpp::token::CONST },
         { "volatile", soul_expected::cpp::token::VOLATILE },
         { "using", soul_expected::cpp::token::USING },
         { "namespace", soul_expected::cpp::token::NAMESPACE },
         { "throw", soul_expected::cpp::token::THROW },
         { "sizeof", soul_expected::cpp::token::SIZEOF },
         { "operator", soul_expected::cpp::token::OPERATOR },
         { "dynamic_cast", soul_expected::cpp::token::DYNAMIC_CAST },
         { "static_cast", soul_expected::cpp::token::STATIC_CAST },
         { "reinterpret_cast", soul_expected::cpp::token::REINTERPRET_CAST },
         { "const_cast", soul_expected::cpp::token::CONST_CAST },
         { "typeid", soul_expected::cpp::token::TYPEID },
         { "this", soul_expected::cpp::token::THIS },
         { "new", soul_expected::cpp::token::NEW },
         { "delete", soul_expected::cpp::token::DELETE },
         { "true", soul_expected::cpp::token::TRUE },
         { "false", soul_expected::cpp::token::FALSE },
         { "nullptr", soul_expected::cpp::token::NULLPTR },
         { "case", soul_expected::cpp::token::CASE },
         { "default", soul_expected::cpp::token::DEFAULT },
         { "if", soul_expected::cpp::token::IF },
         { "else", soul_expected::cpp::token::ELSE },
         { "switch", soul_expected::cpp::token::SWITCH },
         { "while", soul_expected::cpp::token::WHILE },
         { "do", soul_expected::cpp::token::DO },
         { "for", soul_expected::cpp::token::FOR },
         { "break", soul_expected::cpp::token::BREAK },
         { "continue", soul_expected::cpp::token::CONTINUE },
         { "return", soul_expected::cpp::token::RETURN },
         { "goto", soul_expected::cpp::token::GOTO },
         { "try", soul_expected::cpp::token::TRY },
         { "catch", soul_expected::cpp::token::CATCH },
         { "main", soul_expected::tool::token::MAIN },
         { "start", soul_expected::tool::token::START },
         { "empty", soul_expected::tool::token::EMPTY },
         { "any", soul_expected::tool::token::ANY },
         { "var", soul_expected::tool::token::VAR },
         { "project", soul_expected::tool::token::PROJECT },
         { "tokens", soul_expected::tool::token::TOKENS },
         { nullptr, -1 }
    };
    static soul_expected::lexer::KeywordMap<char> keywordMap(keywords);
    return &keywordMap;
}

template<>
soul_expected::lexer::KeywordMap<char8_t>* GetKeywords<char8_t>()
{
    static const soul_expected::lexer::Keyword<char8_t> keywords[] = {
         { u8"auto", soul_expected::cpp::token::AUTO },
         { u8"register", soul_expected::cpp::token::REGISTER },
         { u8"static", soul_expected::cpp::token::STATIC },
         { u8"extern", soul_expected::cpp::token::EXTERN },
         { u8"mutable", soul_expected::cpp::token::MUTABLE },
         { u8"char", soul_expected::cpp::token::CHAR },
         { u8"char8_t", soul_expected::cpp::token::CHAR8T },
         { u8"char16_t", soul_expected::cpp::token::CHAR16T },
         { u8"char32_t", soul_expected::cpp::token::CHAR32T },
         { u8"wchar_t", soul_expected::cpp::token::WCHART },
         { u8"bool", soul_expected::cpp::token::BOOL },
         { u8"short", soul_expected::cpp::token::SHORT },
         { u8"int", soul_expected::cpp::token::INT },
         { u8"long", soul_expected::cpp::token::LONG },
         { u8"signed", soul_expected::cpp::token::SIGNED },
         { u8"unsigned", soul_expected::cpp::token::UNSIGNED },
         { u8"float", soul_expected::cpp::token::FLOAT },
         { u8"double", soul_expected::cpp::token::DOUBLE },
         { u8"void", soul_expected::cpp::token::VOID },
         { u8"typedef", soul_expected::cpp::token::TYPEDEF },
         { u8"const", soul_expected::cpp::token::CONST },
         { u8"volatile", soul_expected::cpp::token::VOLATILE },
         { u8"using", soul_expected::cpp::token::USING },
         { u8"namespace", soul_expected::cpp::token::NAMESPACE },
         { u8"throw", soul_expected::cpp::token::THROW },
         { u8"sizeof", soul_expected::cpp::token::SIZEOF },
         { u8"operator", soul_expected::cpp::token::OPERATOR },
         { u8"dynamic_cast", soul_expected::cpp::token::DYNAMIC_CAST },
         { u8"static_cast", soul_expected::cpp::token::STATIC_CAST },
         { u8"reinterpret_cast", soul_expected::cpp::token::REINTERPRET_CAST },
         { u8"const_cast", soul_expected::cpp::token::CONST_CAST },
         { u8"typeid", soul_expected::cpp::token::TYPEID },
         { u8"this", soul_expected::cpp::token::THIS },
         { u8"new", soul_expected::cpp::token::NEW },
         { u8"delete", soul_expected::cpp::token::DELETE },
         { u8"true", soul_expected::cpp::token::TRUE },
         { u8"false", soul_expected::cpp::token::FALSE },
         { u8"nullptr", soul_expected::cpp::token::NULLPTR },
         { u8"case", soul_expected::cpp::token::CASE },
         { u8"default", soul_expected::cpp::token::DEFAULT },
         { u8"if", soul_expected::cpp::token::IF },
         { u8"else", soul_expected::cpp::token::ELSE },
         { u8"switch", soul_expected::cpp::token::SWITCH },
         { u8"while", soul_expected::cpp::token::WHILE },
         { u8"do", soul_expected::cpp::token::DO },
         { u8"for", soul_expected::cpp::token::FOR },
         { u8"break", soul_expected::cpp::token::BREAK },
         { u8"continue", soul_expected::cpp::token::CONTINUE },
         { u8"return", soul_expected::cpp::token::RETURN },
         { u8"goto", soul_expected::cpp::token::GOTO },
         { u8"try", soul_expected::cpp::token::TRY },
         { u8"catch", soul_expected::cpp::token::CATCH },
         { u8"main", soul_expected::tool::token::MAIN },
         { u8"start", soul_expected::tool::token::START },
         { u8"empty", soul_expected::tool::token::EMPTY },
         { u8"any", soul_expected::tool::token::ANY },
         { u8"var", soul_expected::tool::token::VAR },
         { u8"project", soul_expected::tool::token::PROJECT },
         { u8"tokens", soul_expected::tool::token::TOKENS },
         { nullptr, -1 }
    };
    static soul_expected::lexer::KeywordMap<char8_t> keywordMap(keywords);
    return &keywordMap;
}

template<>
soul_expected::lexer::KeywordMap<char16_t>* GetKeywords<char16_t>()
{
    static const soul_expected::lexer::Keyword<char16_t> keywords[] = {
         { u"auto", soul_expected::cpp::token::AUTO },
         { u"register", soul_expected::cpp::token::REGISTER },
         { u"static", soul_expected::cpp::token::STATIC },
         { u"extern", soul_expected::cpp::token::EXTERN },
         { u"mutable", soul_expected::cpp::token::MUTABLE },
         { u"char", soul_expected::cpp::token::CHAR },
         { u"char8_t", soul_expected::cpp::token::CHAR8T },
         { u"char16_t", soul_expected::cpp::token::CHAR16T },
         { u"char32_t", soul_expected::cpp::token::CHAR32T },
         { u"wchar_t", soul_expected::cpp::token::WCHART },
         { u"bool", soul_expected::cpp::token::BOOL },
         { u"short", soul_expected::cpp::token::SHORT },
         { u"int", soul_expected::cpp::token::INT },
         { u"long", soul_expected::cpp::token::LONG },
         { u"signed", soul_expected::cpp::token::SIGNED },
         { u"unsigned", soul_expected::cpp::token::UNSIGNED },
         { u"float", soul_expected::cpp::token::FLOAT },
         { u"double", soul_expected::cpp::token::DOUBLE },
         { u"void", soul_expected::cpp::token::VOID },
         { u"typedef", soul_expected::cpp::token::TYPEDEF },
         { u"const", soul_expected::cpp::token::CONST },
         { u"volatile", soul_expected::cpp::token::VOLATILE },
         { u"using", soul_expected::cpp::token::USING },
         { u"namespace", soul_expected::cpp::token::NAMESPACE },
         { u"throw", soul_expected::cpp::token::THROW },
         { u"sizeof", soul_expected::cpp::token::SIZEOF },
         { u"operator", soul_expected::cpp::token::OPERATOR },
         { u"dynamic_cast", soul_expected::cpp::token::DYNAMIC_CAST },
         { u"static_cast", soul_expected::cpp::token::STATIC_CAST },
         { u"reinterpret_cast", soul_expected::cpp::token::REINTERPRET_CAST },
         { u"const_cast", soul_expected::cpp::token::CONST_CAST },
         { u"typeid", soul_expected::cpp::token::TYPEID },
         { u"this", soul_expected::cpp::token::THIS },
         { u"new", soul_expected::cpp::token::NEW },
         { u"delete", soul_expected::cpp::token::DELETE },
         { u"true", soul_expected::cpp::token::TRUE },
         { u"false", soul_expected::cpp::token::FALSE },
         { u"nullptr", soul_expected::cpp::token::NULLPTR },
         { u"case", soul_expected::cpp::token::CASE },
         { u"default", soul_expected::cpp::token::DEFAULT },
         { u"if", soul_expected::cpp::token::IF },
         { u"else", soul_expected::cpp::token::ELSE },
         { u"switch", soul_expected::cpp::token::SWITCH },
         { u"while", soul_expected::cpp::token::WHILE },
         { u"do", soul_expected::cpp::token::DO },
         { u"for", soul_expected::cpp::token::FOR },
         { u"break", soul_expected::cpp::token::BREAK },
         { u"continue", soul_expected::cpp::token::CONTINUE },
         { u"return", soul_expected::cpp::token::RETURN },
         { u"goto", soul_expected::cpp::token::GOTO },
         { u"try", soul_expected::cpp::token::TRY },
         { u"catch", soul_expected::cpp::token::CATCH },
         { u"main", soul_expected::tool::token::MAIN },
         { u"start", soul_expected::tool::token::START },
         { u"empty", soul_expected::tool::token::EMPTY },
         { u"any", soul_expected::tool::token::ANY },
         { u"var", soul_expected::tool::token::VAR },
         { u"project", soul_expected::tool::token::PROJECT },
         { u"tokens", soul_expected::tool::token::TOKENS },
         { nullptr, -1 }
    };
    static soul_expected::lexer::KeywordMap<char16_t> keywordMap(keywords);
    return &keywordMap;
}

template<>
soul_expected::lexer::KeywordMap<char32_t>* GetKeywords<char32_t>()
{
    static const soul_expected::lexer::Keyword<char32_t> keywords[] = {
         { U"auto", soul_expected::cpp::token::AUTO },
         { U"register", soul_expected::cpp::token::REGISTER },
         { U"static", soul_expected::cpp::token::STATIC },
         { U"extern", soul_expected::cpp::token::EXTERN },
         { U"mutable", soul_expected::cpp::token::MUTABLE },
         { U"char", soul_expected::cpp::token::CHAR },
         { U"char8_t", soul_expected::cpp::token::CHAR8T },
         { U"char16_t", soul_expected::cpp::token::CHAR16T },
         { U"char32_t", soul_expected::cpp::token::CHAR32T },
         { U"wchar_t", soul_expected::cpp::token::WCHART },
         { U"bool", soul_expected::cpp::token::BOOL },
         { U"short", soul_expected::cpp::token::SHORT },
         { U"int", soul_expected::cpp::token::INT },
         { U"long", soul_expected::cpp::token::LONG },
         { U"signed", soul_expected::cpp::token::SIGNED },
         { U"unsigned", soul_expected::cpp::token::UNSIGNED },
         { U"float", soul_expected::cpp::token::FLOAT },
         { U"double", soul_expected::cpp::token::DOUBLE },
         { U"void", soul_expected::cpp::token::VOID },
         { U"typedef", soul_expected::cpp::token::TYPEDEF },
         { U"const", soul_expected::cpp::token::CONST },
         { U"volatile", soul_expected::cpp::token::VOLATILE },
         { U"using", soul_expected::cpp::token::USING },
         { U"namespace", soul_expected::cpp::token::NAMESPACE },
         { U"throw", soul_expected::cpp::token::THROW },
         { U"sizeof", soul_expected::cpp::token::SIZEOF },
         { U"operator", soul_expected::cpp::token::OPERATOR },
         { U"dynamic_cast", soul_expected::cpp::token::DYNAMIC_CAST },
         { U"static_cast", soul_expected::cpp::token::STATIC_CAST },
         { U"reinterpret_cast", soul_expected::cpp::token::REINTERPRET_CAST },
         { U"const_cast", soul_expected::cpp::token::CONST_CAST },
         { U"typeid", soul_expected::cpp::token::TYPEID },
         { U"this", soul_expected::cpp::token::THIS },
         { U"new", soul_expected::cpp::token::NEW },
         { U"delete", soul_expected::cpp::token::DELETE },
         { U"true", soul_expected::cpp::token::TRUE },
         { U"false", soul_expected::cpp::token::FALSE },
         { U"nullptr", soul_expected::cpp::token::NULLPTR },
         { U"case", soul_expected::cpp::token::CASE },
         { U"default", soul_expected::cpp::token::DEFAULT },
         { U"if", soul_expected::cpp::token::IF },
         { U"else", soul_expected::cpp::token::ELSE },
         { U"switch", soul_expected::cpp::token::SWITCH },
         { U"while", soul_expected::cpp::token::WHILE },
         { U"do", soul_expected::cpp::token::DO },
         { U"for", soul_expected::cpp::token::FOR },
         { U"break", soul_expected::cpp::token::BREAK },
         { U"continue", soul_expected::cpp::token::CONTINUE },
         { U"return", soul_expected::cpp::token::RETURN },
         { U"goto", soul_expected::cpp::token::GOTO },
         { U"try", soul_expected::cpp::token::TRY },
         { U"catch", soul_expected::cpp::token::CATCH },
         { U"main", soul_expected::tool::token::MAIN },
         { U"start", soul_expected::tool::token::START },
         { U"empty", soul_expected::tool::token::EMPTY },
         { U"any", soul_expected::tool::token::ANY },
         { U"var", soul_expected::tool::token::VAR },
         { U"project", soul_expected::tool::token::PROJECT },
         { U"tokens", soul_expected::tool::token::TOKENS },
         { nullptr, -1 }
    };
    static soul_expected::lexer::KeywordMap<char32_t> keywordMap(keywords);
    return &keywordMap;
}

} // namespace soul_expected::lex::spg
