// this file has been automatically generated from 'D:/work/soul-mod/soul_expected/lex_expected/re.lexer' using soul lexer generator eslg version 5.0.0

module soul_expected.lex.re;


namespace soul_expected::lex::re {

soul_expected::ast::common::TokenCollection* GetTokens()
{
    static soul_expected::ast::common::TokenCollection tokens("soul_expected.lex.re.tokens");
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

RegExLexer_Variables::RegExLexer_Variables()
{
}

std::mutex mtx;

std::mutex& MakeLexerMtx() { return mtx; }

template<>
soul_expected::lexer::KeywordMap<char>* GetKeywords<char>()
{
    static const soul_expected::lexer::Keyword<char> keywords[] = {
         { nullptr, -1 }
    };
    static soul_expected::lexer::KeywordMap<char> keywordMap(keywords);
    return &keywordMap;
}

template<>
soul_expected::lexer::KeywordMap<char8_t>* GetKeywords<char8_t>()
{
    static const soul_expected::lexer::Keyword<char8_t> keywords[] = {
         { nullptr, -1 }
    };
    static soul_expected::lexer::KeywordMap<char8_t> keywordMap(keywords);
    return &keywordMap;
}

template<>
soul_expected::lexer::KeywordMap<char16_t>* GetKeywords<char16_t>()
{
    static const soul_expected::lexer::Keyword<char16_t> keywords[] = {
         { nullptr, -1 }
    };
    static soul_expected::lexer::KeywordMap<char16_t> keywordMap(keywords);
    return &keywordMap;
}

template<>
soul_expected::lexer::KeywordMap<char32_t>* GetKeywords<char32_t>()
{
    static const soul_expected::lexer::Keyword<char32_t> keywords[] = {
         { nullptr, -1 }
    };
    static soul_expected::lexer::KeywordMap<char32_t> keywordMap(keywords);
    return &keywordMap;
}

} // namespace soul_expected::lex::re
