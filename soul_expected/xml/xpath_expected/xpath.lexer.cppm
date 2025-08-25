// this file has been automatically generated from 'D:/work/soul-mod/soul_expected/xml/xpath_expected/xpath.lexer' using soul lexer generator eslg version 5.0.0

export module soul_expected.xml.xpath.lexer;

import std;
import soul_expected.lexer;
import soul_expected.ast.slg;
import soul_expected.ast.common;
import util_expected;
import soul_expected.xml.xpath.token;

export namespace soul_expected::xml::xpath::lexer {

std::mutex& MakeLexerMtx();

template<typename CharT>
struct XPathLexer;

template<typename CharT>
std::expected<soul_expected::lexer::Lexer<XPathLexer<CharT>, CharT>, int> MakeLexer(const CharT* start, const CharT* end, const std::string& fileName);

template<typename CharT>
std::expected<soul_expected::lexer::Lexer<XPathLexer<CharT>, CharT>, int> MakeLexer(const std::string& moduleFileName, util::ResourceFlags resourceFlags, const CharT* start, const CharT* end, const std::string& fileName);

soul_expected::ast::common::TokenCollection* GetTokens();

struct XPathLexer_Variables : public soul_expected::lexer::Variables
{
    XPathLexer_Variables();
};

template<typename CharT>
struct XPathLexer
{
    using Variables = XPathLexer_Variables;

    static std::int32_t NextState(std::int32_t state, CharT chr, soul_expected::lexer::LexerBase<CharT>& lexer)
    {
        soul_expected::lexer::ClassMap<CharT>* classmap = lexer.GetClassMap();
        std::int32_t cls = classmap->GetClass(chr);
        switch (state)
        {
            case 0:
            {
                switch (cls)
                {
                    case 0:
                    {
                        return 1;
                    }
                    case 1:
                    {
                        return 2;
                    }
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    {
                        return 3;
                    }
                    case 8:
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                    {
                        return 4;
                    }
                    case 14:
                    {
                        return 5;
                    }
                    case 15:
                    {
                        return 6;
                    }
                    case 17:
                    {
                        return 7;
                    }
                    case 19:
                    {
                        return 8;
                    }
                    case 20:
                    {
                        return 9;
                    }
                    case 21:
                    {
                        return 10;
                    }
                    case 22:
                    {
                        return 11;
                    }
                    case 23:
                    {
                        return 12;
                    }
                    case 24:
                    {
                        return 13;
                    }
                    case 25:
                    {
                        return 14;
                    }
                    case 26:
                    {
                        return 15;
                    }
                    case 27:
                    {
                        return 16;
                    }
                    case 28:
                    {
                        return 17;
                    }
                    case 29:
                    {
                        return 18;
                    }
                    case 30:
                    {
                        return 19;
                    }
                    case 31:
                    {
                        return 20;
                    }
                    case 32:
                    {
                        return 21;
                    }
                    case 33:
                    {
                        return 22;
                    }
                    case 34:
                    {
                        return 23;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 23:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(27, lexer);
                if (tokenId == soul_expected::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul_expected::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul_expected::lexer::INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 22:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(26, lexer);
                if (tokenId == soul_expected::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul_expected::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul_expected::lexer::INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 21:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(25, lexer);
                if (tokenId == soul_expected::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul_expected::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul_expected::lexer::INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 20:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(24, lexer);
                if (tokenId == soul_expected::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul_expected::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul_expected::lexer::INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 19:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(23, lexer);
                if (tokenId == soul_expected::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul_expected::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul_expected::lexer::INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 18:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(22, lexer);
                if (tokenId == soul_expected::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul_expected::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul_expected::lexer::INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 17:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(21, lexer);
                if (tokenId == soul_expected::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul_expected::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul_expected::lexer::INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 16:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(20, lexer);
                if (tokenId == soul_expected::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul_expected::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul_expected::lexer::INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 27:
                    {
                        return 24;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 24:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(19, lexer);
                if (tokenId == soul_expected::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul_expected::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul_expected::lexer::INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 15:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(16, lexer);
                if (tokenId == soul_expected::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul_expected::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul_expected::lexer::INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 26:
                    {
                        return 25;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 25:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(15, lexer);
                if (tokenId == soul_expected::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul_expected::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul_expected::lexer::INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 14:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(14, lexer);
                if (tokenId == soul_expected::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul_expected::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul_expected::lexer::INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 13:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(13, lexer);
                if (tokenId == soul_expected::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul_expected::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul_expected::lexer::INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 12:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(11, lexer);
                if (tokenId == soul_expected::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul_expected::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul_expected::lexer::INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 11:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(10, lexer);
                if (tokenId == soul_expected::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul_expected::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul_expected::lexer::INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 19:
                    {
                        return 26;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 26:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == soul_expected::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul_expected::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul_expected::lexer::INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 10:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(9, lexer);
                if (tokenId == soul_expected::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul_expected::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul_expected::lexer::INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 19:
                    {
                        return 27;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 27:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == soul_expected::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul_expected::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul_expected::lexer::INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 9:
            {
                switch (cls)
                {
                    case 19:
                    {
                        return 28;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 28:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(6, lexer);
                if (tokenId == soul_expected::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul_expected::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul_expected::lexer::INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 8:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(5, lexer);
                if (tokenId == soul_expected::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul_expected::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul_expected::lexer::INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 7:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == soul_expected::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul_expected::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul_expected::lexer::INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 17:
                    {
                        return 7;
                    }
                    case 15:
                    {
                        return 29;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 29:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == soul_expected::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul_expected::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul_expected::lexer::INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 17:
                    {
                        return 30;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 30:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == soul_expected::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul_expected::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul_expected::lexer::INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 17:
                    {
                        return 30;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 6:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(18, lexer);
                if (tokenId == soul_expected::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul_expected::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul_expected::lexer::INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 15:
                    {
                        return 31;
                    }
                    case 17:
                    {
                        return 32;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 32:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == soul_expected::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul_expected::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul_expected::lexer::INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 17:
                    {
                        return 32;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 31:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(17, lexer);
                if (tokenId == soul_expected::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul_expected::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul_expected::lexer::INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 5:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(12, lexer);
                if (tokenId == soul_expected::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul_expected::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul_expected::lexer::INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 4:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(1, lexer);
                if (tokenId == soul_expected::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul_expected::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul_expected::lexer::INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 8:
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                    {
                        return 33;
                    }
                    case 13:
                    case 14:
                    case 15:
                    case 16:
                    case 17:
                    {
                        return 34;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 34:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(1, lexer);
                if (tokenId == soul_expected::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul_expected::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul_expected::lexer::INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 8:
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                    {
                        return 33;
                    }
                    case 13:
                    case 14:
                    case 15:
                    case 16:
                    case 17:
                    {
                        return 34;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 33:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(1, lexer);
                if (tokenId == soul_expected::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul_expected::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul_expected::lexer::INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 8:
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                    {
                        return 33;
                    }
                    case 13:
                    case 14:
                    case 15:
                    case 16:
                    case 17:
                    {
                        return 34;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 3:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(0, lexer);
                if (tokenId == soul_expected::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul_expected::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul_expected::lexer::INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    {
                        return 3;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 2:
            {
                switch (cls)
                {
                    case 0:
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 15:
                    case 16:
                    case 17:
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    {
                        return 35;
                    }
                    case 1:
                    {
                        return 36;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 36:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == soul_expected::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul_expected::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul_expected::lexer::INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 35:
            {
                switch (cls)
                {
                    case 0:
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 15:
                    case 16:
                    case 17:
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    {
                        return 35;
                    }
                    case 1:
                    {
                        return 36;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 1:
            {
                switch (cls)
                {
                    case 0:
                    {
                        return 37;
                    }
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 15:
                    case 16:
                    case 17:
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    {
                        return 38;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 38:
            {
                switch (cls)
                {
                    case 0:
                    {
                        return 37;
                    }
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 15:
                    case 16:
                    case 17:
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    {
                        return 38;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 37:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(4, lexer);
                if (tokenId == soul_expected::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul_expected::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul_expected::lexer::INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
        }
        return -1;
    }

    static std::int64_t GetTokenId(std::int32_t ruleIndex, soul_expected::lexer::LexerBase<CharT>& lexer)
    {
        switch (ruleIndex)
        {
            case 0:
            {
                lexer.Retract();
                break;
            }
            case 1:
            {
                lexer.Retract();
                return soul_expected::xml::xpath::token::NAME;
                break;
            }
            case 2:
            {
                lexer.Retract();
                return soul_expected::xml::xpath::token::NUMBER;
                break;
            }
            case 3:
            {
                lexer.Retract();
                return soul_expected::xml::xpath::token::DQ_STRING;
                break;
            }
            case 4:
            {
                lexer.Retract();
                return soul_expected::xml::xpath::token::SQ_STRING;
                break;
            }
            case 5:
            {
                lexer.Retract();
                return soul_expected::xml::xpath::token::EQ;
                break;
            }
            case 6:
            {
                lexer.Retract();
                return soul_expected::xml::xpath::token::NEQ;
                break;
            }
            case 7:
            {
                lexer.Retract();
                return soul_expected::xml::xpath::token::LEQ;
                break;
            }
            case 8:
            {
                lexer.Retract();
                return soul_expected::xml::xpath::token::GEQ;
                break;
            }
            case 9:
            {
                lexer.Retract();
                return soul_expected::xml::xpath::token::LESS;
                break;
            }
            case 10:
            {
                lexer.Retract();
                return soul_expected::xml::xpath::token::GREATER;
                break;
            }
            case 11:
            {
                lexer.Retract();
                return soul_expected::xml::xpath::token::PLUS;
                break;
            }
            case 12:
            {
                lexer.Retract();
                return soul_expected::xml::xpath::token::MINUS;
                break;
            }
            case 13:
            {
                lexer.Retract();
                return soul_expected::xml::xpath::token::STAR;
                break;
            }
            case 14:
            {
                lexer.Retract();
                return soul_expected::xml::xpath::token::UNION;
                break;
            }
            case 15:
            {
                lexer.Retract();
                return soul_expected::xml::xpath::token::SLASH_SLASH;
                break;
            }
            case 16:
            {
                lexer.Retract();
                return soul_expected::xml::xpath::token::SLASH;
                break;
            }
            case 17:
            {
                lexer.Retract();
                return soul_expected::xml::xpath::token::DOT_DOT;
                break;
            }
            case 18:
            {
                lexer.Retract();
                return soul_expected::xml::xpath::token::DOT;
                break;
            }
            case 19:
            {
                lexer.Retract();
                return soul_expected::xml::xpath::token::COLON_COLON;
                break;
            }
            case 20:
            {
                lexer.Retract();
                return soul_expected::xml::xpath::token::COLON;
                break;
            }
            case 21:
            {
                lexer.Retract();
                return soul_expected::xml::xpath::token::DOLLAR;
                break;
            }
            case 22:
            {
                lexer.Retract();
                return soul_expected::xml::xpath::token::COMMA;
                break;
            }
            case 23:
            {
                lexer.Retract();
                return soul_expected::xml::xpath::token::AT;
                break;
            }
            case 24:
            {
                lexer.Retract();
                return soul_expected::xml::xpath::token::LBRACKET;
                break;
            }
            case 25:
            {
                lexer.Retract();
                return soul_expected::xml::xpath::token::RBRACKET;
                break;
            }
            case 26:
            {
                lexer.Retract();
                return soul_expected::xml::xpath::token::LPAREN;
                break;
            }
            case 27:
            {
                lexer.Retract();
                return soul_expected::xml::xpath::token::RPAREN;
                break;
            }
        }
        return soul_expected::lexer::CONTINUE_TOKEN;
    }
};

template<typename CharT>
std::expected<soul_expected::lexer::ClassMap<CharT>*, int> GetClassMap()
{
    static soul_expected::lexer::ClassMap<CharT>* classmap;
    if (!classmap)
    {
        std::expected<soul_expected::lexer::ClassMap<CharT>*, int> rv = soul_expected::lexer::MakeClassMap<CharT>("soul_expected.xml.xpath.lexer.classmap");
        if (!rv) return std::unexpected<int>(rv.error());
        classmap = *rv;
    }
    return classmap;
}

template<typename CharT>
std::expected<soul_expected::lexer::ClassMap<CharT>*, int> GetClassMap(const std::string & moduleFileName, util::ResourceFlags resourceFlags)
{
    static soul_expected::lexer::ClassMap<CharT>* classmap;
    if (!classmap)
    {
        std::expected<soul_expected::lexer::ClassMap<CharT>*, int> rv = soul_expected::lexer::MakeClassMap<CharT>(moduleFileName, "soul_expected.xml.xpath.lexer.classmap", resourceFlags);
        if (!rv) return std::unexpected<int>(rv.error());
        classmap = *rv;
    }
    return classmap;
}

template<typename CharT>
soul_expected::lexer::KeywordMap<CharT>* GetKeywords();

template<>
soul_expected::lexer::KeywordMap<char>* GetKeywords<char>();

template<>
soul_expected::lexer::KeywordMap<char8_t>* GetKeywords<char8_t>();

template<>
soul_expected::lexer::KeywordMap<char16_t>* GetKeywords<char16_t>();

template<>
soul_expected::lexer::KeywordMap<char32_t>* GetKeywords<char32_t>();

template<typename CharT>
std::expected<soul_expected::lexer::Lexer<XPathLexer<CharT>, CharT>, int> MakeLexer(const CharT* start, const CharT* end, const std::string& fileName)
{
    std::lock_guard<std::mutex> lock(MakeLexerMtx());
    auto lexer = soul_expected::lexer::Lexer<XPathLexer<CharT>, CharT>(start, end, fileName);
    std::expected<soul_expected::lexer::ClassMap<CharT>*, int> rv = GetClassMap<CharT>();
    if (!rv) return std::unexpected<int>(rv.error());
    lexer.SetClassMap(*rv);
    lexer.SetTokenCollection(GetTokens());
    lexer.SetKeywordMap(GetKeywords<CharT>());
    return lexer;
}

template<typename CharT>
std::expected<soul_expected::lexer::Lexer<XPathLexer<CharT>, CharT>, int> MakeLexer(const std::string& moduleFileName, util::ResourceFlags resourceFlags, const CharT* start, const CharT* end, const std::string& fileName)
{
    std::lock_guard<std::mutex> lock(MakeLexerMtx());
    auto lexer = soul_expected::lexer::Lexer<XPathLexer<CharT>, CharT>(start, end, fileName);
    std::expected<soul_expected::lexer::ClassMap<CharT>*, int> rv = GetClassMap<CharT>(moduleFileName, resourceFlags);
    if (!rv) return std::unexpected<int>(rv.error());
    lexer.SetClassMap(*rv);
    lexer.SetTokenCollection(GetTokens());
    lexer.SetKeywordMap(GetKeywords<CharT>());
    return lexer;
}

} // namespace soul_expected::xml::xpath::lexer
