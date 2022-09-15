// this file has been automatically generated from 'C:/work/soul-mod/soul/lex/re_lexer.lexer' using soul lexer generator slg version 4.1.0

module soul.lex.re;

using namespace soul::cpp::token;
using namespace soul::cpp::op::token;
using namespace soul::punctuation::token;
using namespace soul::tool::token;

namespace soul::lex::re {

soul::ast::slg::TokenCollection* GetTokens()
{
    static soul::ast::slg::TokenCollection tokens("soul.lex.re.tokens");
    if (!tokens.Initialized())
    {
        tokens.SetInitialized();
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
        tokens.AddToken(new soul::ast::slg::Token(DISJUNCTION, "DISJUNCTION", "'||'"));
        tokens.AddToken(new soul::ast::slg::Token(AMP_AMP, "AMP_AMP", "'&&'"));
        tokens.AddToken(new soul::ast::slg::Token(DOT_STAR, "DOT_STAR", "'.*'"));
        tokens.AddToken(new soul::ast::slg::Token(ARROW_STAR, "ARROW_STAR", "'->*'"));
        tokens.AddToken(new soul::ast::slg::Token(EQ, "EQ", "'=='"));
        tokens.AddToken(new soul::ast::slg::Token(NEQ, "NEQ", "'!='"));
        tokens.AddToken(new soul::ast::slg::Token(LEQ, "LEQ", "'<='"));
        tokens.AddToken(new soul::ast::slg::Token(GEQ, "GEQ", "'>='"));
        tokens.AddToken(new soul::ast::slg::Token(SHIFT_LEFT, "SHIFT_LEFT", "'<<'"));
        tokens.AddToken(new soul::ast::slg::Token(SHIFT_RIGHT, "SHIFT_RIGHT", "'>>'"));
        tokens.AddToken(new soul::ast::slg::Token(PLUS, "PLUS", "'+'"));
        tokens.AddToken(new soul::ast::slg::Token(MINUS, "MINUS", "'-'"));
        tokens.AddToken(new soul::ast::slg::Token(STAR, "STAR", "'*'"));
        tokens.AddToken(new soul::ast::slg::Token(DIV, "DIV", "'/'"));
        tokens.AddToken(new soul::ast::slg::Token(REM, "REM", "'%'"));
        tokens.AddToken(new soul::ast::slg::Token(PLUS_PLUS, "PLUS_PLUS", "'++'"));
        tokens.AddToken(new soul::ast::slg::Token(MINUS_MINUS, "MINUS_MINUS", "'--'"));
        tokens.AddToken(new soul::ast::slg::Token(ELLIPSIS, "ELLIPSIS", "'...'"));
        tokens.AddToken(new soul::ast::slg::Token(COLON_COLON, "COLON_COLON", "'::'"));
        tokens.AddToken(new soul::ast::slg::Token(ASSIGN, "ASSIGN", "'='"));
        tokens.AddToken(new soul::ast::slg::Token(MUL_ASSIGN, "MUL_ASSIGN", "'*='"));
        tokens.AddToken(new soul::ast::slg::Token(DIV_ASSIGN, "DIV_ASSIGN", "'/='"));
        tokens.AddToken(new soul::ast::slg::Token(REM_ASSIGN, "REM_ASSIGN", "'%='"));
        tokens.AddToken(new soul::ast::slg::Token(PLUS_ASSIGN, "PLUS_ASSIGN", "'+='"));
        tokens.AddToken(new soul::ast::slg::Token(MINUS_ASSIGN, "MINUS_ASSIGN", "'-='"));
        tokens.AddToken(new soul::ast::slg::Token(SHIFT_LEFT_ASSIGN, "SHIFT_LEFT_ASSIGN", "'<<='"));
        tokens.AddToken(new soul::ast::slg::Token(SHIFT_RIGHT_ASSIGN, "SHIFT_RIGHT_ASSIGN", "'>>='"));
        tokens.AddToken(new soul::ast::slg::Token(AND_ASSIGN, "AND_ASSIGN", "'&='"));
        tokens.AddToken(new soul::ast::slg::Token(XOR_ASSIGN, "XOR_ASSIGN", "'^='"));
        tokens.AddToken(new soul::ast::slg::Token(OR_ASSIGN, "OR_ASSIGN", "'|='"));
        tokens.AddToken(new soul::ast::slg::Token(DOT, "DOT", "'.'"));
        tokens.AddToken(new soul::ast::slg::Token(LPAREN, "LPAREN", "'('"));
        tokens.AddToken(new soul::ast::slg::Token(RPAREN, "RPAREN", "')'"));
        tokens.AddToken(new soul::ast::slg::Token(LBRACE, "LBRACE", "'{'"));
        tokens.AddToken(new soul::ast::slg::Token(RBRACE, "RBRACE", "'}'"));
        tokens.AddToken(new soul::ast::slg::Token(LBRACKET, "LBRACKET", "'['"));
        tokens.AddToken(new soul::ast::slg::Token(RBRACKET, "RBRACKET", "']'"));
        tokens.AddToken(new soul::ast::slg::Token(LANGLE, "LANGLE", "'<'"));
        tokens.AddToken(new soul::ast::slg::Token(RANGLE, "RANGLE", "'>'"));
        tokens.AddToken(new soul::ast::slg::Token(COLON, "COLON", "':'"));
        tokens.AddToken(new soul::ast::slg::Token(SEMICOLON, "SEMICOLON", "';'"));
        tokens.AddToken(new soul::ast::slg::Token(HASH, "HASH", "'#'"));
        tokens.AddToken(new soul::ast::slg::Token(COMMA, "COMMA", "','"));
        tokens.AddToken(new soul::ast::slg::Token(ARROW, "ARROW", "'->'"));
        tokens.AddToken(new soul::ast::slg::Token(QUEST, "QUEST", "'?'"));
        tokens.AddToken(new soul::ast::slg::Token(AMP, "AMP", "'&'"));
        tokens.AddToken(new soul::ast::slg::Token(DOLLAR, "DOLLAR", "'$'"));
        tokens.AddToken(new soul::ast::slg::Token(EXCLAMATION, "EXCLAMATION", "'!'"));
        tokens.AddToken(new soul::ast::slg::Token(TILDE, "TILDE", "'~'"));
        tokens.AddToken(new soul::ast::slg::Token(CARET, "CARET", "'^'"));
        tokens.AddToken(new soul::ast::slg::Token(PIPE, "PIPE", "'|'"));
        tokens.AddToken(new soul::ast::slg::Token(PRODUCES, "PRODUCES", "'::='"));
        tokens.AddToken(new soul::ast::slg::Token(BACKSLASH, "BACKSLASH", "'\'"));
        tokens.AddToken(new soul::ast::slg::Token(TOKENS, "TOKENS", "'tokens'"));
        tokens.AddToken(new soul::ast::slg::Token(KEYWORDS, "KEYWORDS", "'keywords'"));
        tokens.AddToken(new soul::ast::slg::Token(EXPRESSIONS, "EXPRESSIONS", "'expressions'"));
        tokens.AddToken(new soul::ast::slg::Token(RULES, "RULES", "'rules'"));
        tokens.AddToken(new soul::ast::slg::Token(VARIABLES, "VARIABLES", "''variables'"));
        tokens.AddToken(new soul::ast::slg::Token(ACTIONS, "ACTIONS", "'actions'"));
        tokens.AddToken(new soul::ast::slg::Token(MAIN, "MAIN", "'main'"));
        tokens.AddToken(new soul::ast::slg::Token(START, "START", "'start'"));
        tokens.AddToken(new soul::ast::slg::Token(EMPTY, "EMPTY", "'empty'"));
        tokens.AddToken(new soul::ast::slg::Token(ANY, "ANY", "'any'"));
        tokens.AddToken(new soul::ast::slg::Token(VAR, "VAR", "'var'"));
        tokens.AddToken(new soul::ast::slg::Token(FILEPATH, "FILEPATH", "file path"));
        tokens.AddToken(new soul::ast::slg::Token(PROJECT, "PROJECT", "'project'"));
        tokens.AddToken(new soul::ast::slg::Token(CHARACTER, "CHARACTER", "character"));
        tokens.AddToken(new soul::ast::slg::Token(ESCAPE, "ESCAPE", "escape"));
    }
    return &tokens;
}

RegExLexer_Variables::RegExLexer_Variables()
{
}

std::mutex mtx;

std::mutex& MakeLexerMtx() { return mtx; }

template<>
soul::lexer::KeywordMap<char>* GetKeywords<char>()
{
    static const soul::lexer::Keyword<char> keywords[] = {
         { nullptr, -1 }
    };
    static soul::lexer::KeywordMap<char> keywordMap(keywords);
    return &keywordMap;
}

template<>
soul::lexer::KeywordMap<char8_t>* GetKeywords<char8_t>()
{
    static const soul::lexer::Keyword<char8_t> keywords[] = {
         { nullptr, -1 }
    };
    static soul::lexer::KeywordMap<char8_t> keywordMap(keywords);
    return &keywordMap;
}

template<>
soul::lexer::KeywordMap<char16_t>* GetKeywords<char16_t>()
{
    static const soul::lexer::Keyword<char16_t> keywords[] = {
         { nullptr, -1 }
    };
    static soul::lexer::KeywordMap<char16_t> keywordMap(keywords);
    return &keywordMap;
}

template<>
soul::lexer::KeywordMap<char32_t>* GetKeywords<char32_t>()
{
    static const soul::lexer::Keyword<char32_t> keywords[] = {
         { nullptr, -1 }
    };
    static soul::lexer::KeywordMap<char32_t> keywordMap(keywords);
    return &keywordMap;
}

} // namespace soul::lex::re
