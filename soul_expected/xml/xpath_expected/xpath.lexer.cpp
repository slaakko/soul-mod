// this file has been automatically generated from 'D:/work/soul-mod/soul_expected/xml/xpath_expected/xpath.lexer' using soul lexer generator eslg version 5.0.0

module soul_expected.xml.xpath.lexer;


namespace soul_expected::xml::xpath::lexer {

soul_expected::ast::common::TokenCollection* GetTokens()
{
    static soul_expected::ast::common::TokenCollection tokens("soul_expected.xml.xpath.lexer.tokens");
    if (!tokens.Initialized())
    {
        tokens.SetInitialized();
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::xml::xpath::token::OR, "OR", "'or'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::xml::xpath::token::AND, "AND", "'and'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::xml::xpath::token::EQ, "EQ", "'='"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::xml::xpath::token::NEQ, "NEQ", "'!='"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::xml::xpath::token::LEQ, "LEQ", "'<='"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::xml::xpath::token::GEQ, "GEQ", "'>='"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::xml::xpath::token::LESS, "LESS", "'<'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::xml::xpath::token::GREATER, "GREATER", "'>'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::xml::xpath::token::PLUS, "PLUS", "'+'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::xml::xpath::token::MINUS, "MINUS", "'-'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::xml::xpath::token::STAR, "STAR", "'*'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::xml::xpath::token::DIV, "DIV", "'div'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::xml::xpath::token::MOD, "MOD", "'mod'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::xml::xpath::token::UNION, "UNION", "'|'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::xml::xpath::token::SLASH_SLASH, "SLASH_SLASH", "'//'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::xml::xpath::token::SLASH, "SLASH", "'/'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::xml::xpath::token::DOT_DOT, "DOT_DOT", "'..'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::xml::xpath::token::DOT, "DOT", "'.'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::xml::xpath::token::COLON_COLON, "COLON_COLON", "'::'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::xml::xpath::token::COLON, "COLON", "':'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::xml::xpath::token::DOLLAR, "DOLLAR", "'$'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::xml::xpath::token::COMMA, "COMMA", "','"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::xml::xpath::token::ANCESTOR, "ANCESTOR", "'ancestor'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::xml::xpath::token::ANCESTOR_OR_SELF, "ANCESTOR_OR_SELF", "'ancestor-or-self'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::xml::xpath::token::ATTRIBUTE, "ATTRIBUTE", "'attribte'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::xml::xpath::token::CHILD, "CHILD", "'child'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::xml::xpath::token::DESCENDANT, "DESCENDANT", "'descendant"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::xml::xpath::token::DESCENDANT_OR_SELF, "DESCENDANT_OR_SELF", "'descendant-or-self'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::xml::xpath::token::FOLLOWING, "FOLLOWING", "'following'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::xml::xpath::token::FOLLOWING_SIBLING, "FOLLOWING_SIBLING", "'following-sibling'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::xml::xpath::token::NAMESPACE, "NAMESPACE", "'namespace'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::xml::xpath::token::PARENT, "PARENT", "'parent'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::xml::xpath::token::PRECEDING, "PRECEDING", "'preceding'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::xml::xpath::token::PRECEDING_SIBLING, "PRECEDING_SIBLING", "'preceding-siblibg'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::xml::xpath::token::SELF, "SELF", "'self'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::xml::xpath::token::AT, "AT", "'@'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::xml::xpath::token::LBRACKET, "LBRACKET", "'['"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::xml::xpath::token::RBRACKET, "RBRACKET", "']'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::xml::xpath::token::LPAREN, "LPAREN", "'('"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::xml::xpath::token::RPAREN, "RPAREN", "')'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::xml::xpath::token::PROCESSING_INSTRUCTION, "PROCESSING_INSTRUCTION", "'processing-instructioon'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::xml::xpath::token::COMMENT, "COMMENT", "'comment'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::xml::xpath::token::TEXT, "TEXT", "'text'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::xml::xpath::token::NODE, "NODE", "'node'"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::xml::xpath::token::DQ_STRING, "DQ_STRING", "string"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::xml::xpath::token::SQ_STRING, "SQ_STRING", "string"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::xml::xpath::token::NUMBER, "NUMBER", "number"));
        tokens.AddToken(new soul_expected::ast::common::Token(soul_expected::xml::xpath::token::NAME, "NAME", "name"));
    }
    return &tokens;
}

XPathLexer_Variables::XPathLexer_Variables()
{
}

std::mutex mtx;

std::mutex& MakeLexerMtx() { return mtx; }

template<>
soul_expected::lexer::KeywordMap<char>* GetKeywords<char>()
{
    static const soul_expected::lexer::Keyword<char> keywords[] = {
         { "or", soul_expected::xml::xpath::token::OR },
         { "and", soul_expected::xml::xpath::token::AND },
         { "div", soul_expected::xml::xpath::token::DIV },
         { "mod", soul_expected::xml::xpath::token::MOD },
         { "ancestor", soul_expected::xml::xpath::token::ANCESTOR },
         { "ancestor-or-self", soul_expected::xml::xpath::token::ANCESTOR_OR_SELF },
         { "attribute", soul_expected::xml::xpath::token::ATTRIBUTE },
         { "child", soul_expected::xml::xpath::token::CHILD },
         { "descendant", soul_expected::xml::xpath::token::DESCENDANT },
         { "descendant-or-self", soul_expected::xml::xpath::token::DESCENDANT_OR_SELF },
         { "following", soul_expected::xml::xpath::token::FOLLOWING },
         { "following-sibling", soul_expected::xml::xpath::token::FOLLOWING_SIBLING },
         { "namespace", soul_expected::xml::xpath::token::NAMESPACE },
         { "parent", soul_expected::xml::xpath::token::PARENT },
         { "preceding", soul_expected::xml::xpath::token::PRECEDING },
         { "preceding-sibling", soul_expected::xml::xpath::token::PRECEDING_SIBLING },
         { "self", soul_expected::xml::xpath::token::SELF },
         { "processing-instruction", soul_expected::xml::xpath::token::PROCESSING_INSTRUCTION },
         { "comment", soul_expected::xml::xpath::token::COMMENT },
         { "text", soul_expected::xml::xpath::token::TEXT },
         { "node", soul_expected::xml::xpath::token::NODE },
         { nullptr, -1 }
    };
    static soul_expected::lexer::KeywordMap<char> keywordMap(keywords);
    return &keywordMap;
}

template<>
soul_expected::lexer::KeywordMap<char8_t>* GetKeywords<char8_t>()
{
    static const soul_expected::lexer::Keyword<char8_t> keywords[] = {
         { u8"or", soul_expected::xml::xpath::token::OR },
         { u8"and", soul_expected::xml::xpath::token::AND },
         { u8"div", soul_expected::xml::xpath::token::DIV },
         { u8"mod", soul_expected::xml::xpath::token::MOD },
         { u8"ancestor", soul_expected::xml::xpath::token::ANCESTOR },
         { u8"ancestor-or-self", soul_expected::xml::xpath::token::ANCESTOR_OR_SELF },
         { u8"attribute", soul_expected::xml::xpath::token::ATTRIBUTE },
         { u8"child", soul_expected::xml::xpath::token::CHILD },
         { u8"descendant", soul_expected::xml::xpath::token::DESCENDANT },
         { u8"descendant-or-self", soul_expected::xml::xpath::token::DESCENDANT_OR_SELF },
         { u8"following", soul_expected::xml::xpath::token::FOLLOWING },
         { u8"following-sibling", soul_expected::xml::xpath::token::FOLLOWING_SIBLING },
         { u8"namespace", soul_expected::xml::xpath::token::NAMESPACE },
         { u8"parent", soul_expected::xml::xpath::token::PARENT },
         { u8"preceding", soul_expected::xml::xpath::token::PRECEDING },
         { u8"preceding-sibling", soul_expected::xml::xpath::token::PRECEDING_SIBLING },
         { u8"self", soul_expected::xml::xpath::token::SELF },
         { u8"processing-instruction", soul_expected::xml::xpath::token::PROCESSING_INSTRUCTION },
         { u8"comment", soul_expected::xml::xpath::token::COMMENT },
         { u8"text", soul_expected::xml::xpath::token::TEXT },
         { u8"node", soul_expected::xml::xpath::token::NODE },
         { nullptr, -1 }
    };
    static soul_expected::lexer::KeywordMap<char8_t> keywordMap(keywords);
    return &keywordMap;
}

template<>
soul_expected::lexer::KeywordMap<char16_t>* GetKeywords<char16_t>()
{
    static const soul_expected::lexer::Keyword<char16_t> keywords[] = {
         { u"or", soul_expected::xml::xpath::token::OR },
         { u"and", soul_expected::xml::xpath::token::AND },
         { u"div", soul_expected::xml::xpath::token::DIV },
         { u"mod", soul_expected::xml::xpath::token::MOD },
         { u"ancestor", soul_expected::xml::xpath::token::ANCESTOR },
         { u"ancestor-or-self", soul_expected::xml::xpath::token::ANCESTOR_OR_SELF },
         { u"attribute", soul_expected::xml::xpath::token::ATTRIBUTE },
         { u"child", soul_expected::xml::xpath::token::CHILD },
         { u"descendant", soul_expected::xml::xpath::token::DESCENDANT },
         { u"descendant-or-self", soul_expected::xml::xpath::token::DESCENDANT_OR_SELF },
         { u"following", soul_expected::xml::xpath::token::FOLLOWING },
         { u"following-sibling", soul_expected::xml::xpath::token::FOLLOWING_SIBLING },
         { u"namespace", soul_expected::xml::xpath::token::NAMESPACE },
         { u"parent", soul_expected::xml::xpath::token::PARENT },
         { u"preceding", soul_expected::xml::xpath::token::PRECEDING },
         { u"preceding-sibling", soul_expected::xml::xpath::token::PRECEDING_SIBLING },
         { u"self", soul_expected::xml::xpath::token::SELF },
         { u"processing-instruction", soul_expected::xml::xpath::token::PROCESSING_INSTRUCTION },
         { u"comment", soul_expected::xml::xpath::token::COMMENT },
         { u"text", soul_expected::xml::xpath::token::TEXT },
         { u"node", soul_expected::xml::xpath::token::NODE },
         { nullptr, -1 }
    };
    static soul_expected::lexer::KeywordMap<char16_t> keywordMap(keywords);
    return &keywordMap;
}

template<>
soul_expected::lexer::KeywordMap<char32_t>* GetKeywords<char32_t>()
{
    static const soul_expected::lexer::Keyword<char32_t> keywords[] = {
         { U"or", soul_expected::xml::xpath::token::OR },
         { U"and", soul_expected::xml::xpath::token::AND },
         { U"div", soul_expected::xml::xpath::token::DIV },
         { U"mod", soul_expected::xml::xpath::token::MOD },
         { U"ancestor", soul_expected::xml::xpath::token::ANCESTOR },
         { U"ancestor-or-self", soul_expected::xml::xpath::token::ANCESTOR_OR_SELF },
         { U"attribute", soul_expected::xml::xpath::token::ATTRIBUTE },
         { U"child", soul_expected::xml::xpath::token::CHILD },
         { U"descendant", soul_expected::xml::xpath::token::DESCENDANT },
         { U"descendant-or-self", soul_expected::xml::xpath::token::DESCENDANT_OR_SELF },
         { U"following", soul_expected::xml::xpath::token::FOLLOWING },
         { U"following-sibling", soul_expected::xml::xpath::token::FOLLOWING_SIBLING },
         { U"namespace", soul_expected::xml::xpath::token::NAMESPACE },
         { U"parent", soul_expected::xml::xpath::token::PARENT },
         { U"preceding", soul_expected::xml::xpath::token::PRECEDING },
         { U"preceding-sibling", soul_expected::xml::xpath::token::PRECEDING_SIBLING },
         { U"self", soul_expected::xml::xpath::token::SELF },
         { U"processing-instruction", soul_expected::xml::xpath::token::PROCESSING_INSTRUCTION },
         { U"comment", soul_expected::xml::xpath::token::COMMENT },
         { U"text", soul_expected::xml::xpath::token::TEXT },
         { U"node", soul_expected::xml::xpath::token::NODE },
         { nullptr, -1 }
    };
    static soul_expected::lexer::KeywordMap<char32_t> keywordMap(keywords);
    return &keywordMap;
}

} // namespace soul_expected::xml::xpath::lexer
