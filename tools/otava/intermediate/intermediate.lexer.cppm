// this file has been automatically generated from 'D:/work/soul-mod/tools/otava/intermediate/intermediate.lexer' using soul lexer generator slg version 5.0.0

export module otava.intermediate.lexer;

import std;
import soul.lexer;
import soul.ast.slg;
import util;
import otava.intermediate.token;

using namespace soul;
using namespace soul::lexer;
using namespace otava::intermediate::token;

export namespace otava::intermediate::lexer {

std::mutex& MakeLexerMtx();

template<typename Char>
struct IntermediateLexer;

template<typename Char>
soul::lexer::Lexer<IntermediateLexer<Char>, Char> MakeLexer(const Char* start, const Char* end, const std::string& fileName);

template<typename Char>
soul::lexer::Lexer<IntermediateLexer<Char>, Char> MakeLexer(const std::string& moduleFileName, util::ResourceFlags resourceFlags, const Char* start, const Char* end, const std::string& fileName);

soul::ast::slg::TokenCollection* GetTokens();

struct IntermediateLexer_Variables : public soul::lexer::Variables
{
    IntermediateLexer_Variables();
};

template<typename Char>
struct IntermediateLexer
{
    using Variables = IntermediateLexer_Variables;

    static std::int32_t NextState(std::int32_t state, Char chr, soul::lexer::LexerBase<Char>& lexer)
    {
        soul::lexer::ClassMap<Char>* classmap = lexer.GetClassMap();
        std::int32_t cls = classmap->GetClass(chr);
        switch (state)
        {
            case 0:
            {
                switch (cls)
                {
                    case 0:
                    case 1:
                    case 7:
                    case 8:
                    {
                        return 1;
                    }
                    case 2:
                    {
                        return 2;
                    }
                    case 3:
                    case 4:
                    case 11:
                    case 12:
                    case 13:
                    case 18:
                    {
                        return 3;
                    }
                    case 6:
                    {
                        return 4;
                    }
                    case 9:
                    {
                        return 5;
                    }
                    case 14:
                    {
                        return 6;
                    }
                    case 15:
                    {
                        return 7;
                    }
                    case 16:
                    {
                        return 8;
                    }
                    case 17:
                    {
                        return 9;
                    }
                    case 19:
                    {
                        return 10;
                    }
                    case 20:
                    case 21:
                    {
                        return 11;
                    }
                    case 22:
                    case 24:
                    case 25:
                    case 26:
                    {
                        return 12;
                    }
                    case 23:
                    {
                        return 13;
                    }
                    case 27:
                    {
                        return 14;
                    }
                    case 28:
                    {
                        return 15;
                    }
                    case 29:
                    {
                        return 16;
                    }
                    case 30:
                    {
                        return 17;
                    }
                    case 31:
                    {
                        return 18;
                    }
                    case 32:
                    {
                        return 19;
                    }
                    case 33:
                    {
                        return 20;
                    }
                    case 34:
                    {
                        return 21;
                    }
                    case 35:
                    {
                        return 22;
                    }
                    case 36:
                    {
                        return 23;
                    }
                    case 37:
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
                std::int64_t tokenId = GetTokenId(20, lexer);
                if (tokenId == soul::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul::lexer::INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 23:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(17, lexer);
                if (tokenId == soul::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul::lexer::INVALID_TOKEN)
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
                std::int64_t tokenId = GetTokenId(16, lexer);
                if (tokenId == soul::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul::lexer::INVALID_TOKEN)
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
                std::int64_t tokenId = GetTokenId(15, lexer);
                if (tokenId == soul::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul::lexer::INVALID_TOKEN)
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
                std::int64_t tokenId = GetTokenId(14, lexer);
                if (tokenId == soul::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul::lexer::INVALID_TOKEN)
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
                std::int64_t tokenId = GetTokenId(13, lexer);
                if (tokenId == soul::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul::lexer::INVALID_TOKEN)
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
                std::int64_t tokenId = GetTokenId(12, lexer);
                if (tokenId == soul::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul::lexer::INVALID_TOKEN)
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
                std::int64_t tokenId = GetTokenId(11, lexer);
                if (tokenId == soul::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul::lexer::INVALID_TOKEN)
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
                std::int64_t tokenId = GetTokenId(10, lexer);
                if (tokenId == soul::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul::lexer::INVALID_TOKEN)
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
                std::int64_t tokenId = GetTokenId(9, lexer);
                if (tokenId == soul::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul::lexer::INVALID_TOKEN)
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
                std::int64_t tokenId = GetTokenId(5, lexer);
                if (tokenId == soul::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul::lexer::INVALID_TOKEN)
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
                        return 14;
                    }
                    case 19:
                    {
                        return 25;
                    }
                    case 22:
                    case 23:
                    case 24:
                    {
                        return 26;
                    }
                    case 25:
                    case 26:
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
                std::int64_t tokenId = GetTokenId(6, lexer);
                if (tokenId == soul::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul::lexer::INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    {
                        return 26;
                    }
                    case 20:
                    case 21:
                    {
                        return 28;
                    }
                    case 27:
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
                std::int64_t tokenId = GetTokenId(5, lexer);
                if (tokenId == soul::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul::lexer::INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    {
                        return 26;
                    }
                    case 27:
                    {
                        return 29;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 28:
            {
                switch (cls)
                {
                    case 27:
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
                std::int64_t tokenId = GetTokenId(5, lexer);
                if (tokenId == soul::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul::lexer::INVALID_TOKEN)
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
                        return 30;
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
                std::int64_t tokenId = GetTokenId(6, lexer);
                if (tokenId == soul::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul::lexer::INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
                    {
                        return 26;
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
                std::int64_t tokenId = GetTokenId(5, lexer);
                if (tokenId == soul::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul::lexer::INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 25:
                    case 26:
                    {
                        return 31;
                    }
                    case 27:
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
                std::int64_t tokenId = GetTokenId(5, lexer);
                if (tokenId == soul::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul::lexer::INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 25:
                    case 26:
                    {
                        return 31;
                    }
                    case 27:
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
                switch (cls)
                {
                    case 20:
                    case 21:
                    {
                        return 28;
                    }
                    case 27:
                    {
                        return 30;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 13:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == soul::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul::lexer::INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 3:
                    case 4:
                    case 5:
                    case 12:
                    case 13:
                    case 18:
                    {
                        return 33;
                    }
                    case 6:
                    {
                        return 34;
                    }
                    case 11:
                    {
                        return 35;
                    }
                    case 16:
                    {
                        return 36;
                    }
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
                    {
                        return 37;
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
                std::int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == soul::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul::lexer::INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 3:
                    case 4:
                    case 5:
                    case 11:
                    case 12:
                    case 13:
                    case 18:
                    {
                        return 33;
                    }
                    case 6:
                    {
                        return 34;
                    }
                    case 16:
                    {
                        return 36;
                    }
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
                    {
                        return 37;
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
                std::int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == soul::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul::lexer::INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 3:
                    case 4:
                    case 5:
                    case 11:
                    case 12:
                    case 13:
                    case 18:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
                    {
                        return 33;
                    }
                    case 6:
                    {
                        return 34;
                    }
                    case 16:
                    {
                        return 36;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 35:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == soul::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul::lexer::INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 3:
                    case 4:
                    case 5:
                    case 11:
                    case 13:
                    case 18:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
                    {
                        return 33;
                    }
                    case 6:
                    {
                        return 34;
                    }
                    case 16:
                    {
                        return 36;
                    }
                    case 12:
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
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == soul::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul::lexer::INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 3:
                    case 4:
                    case 5:
                    case 11:
                    case 12:
                    case 18:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
                    {
                        return 33;
                    }
                    case 6:
                    {
                        return 34;
                    }
                    case 16:
                    {
                        return 36;
                    }
                    case 13:
                    {
                        return 39;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 39:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == soul::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul::lexer::INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 3:
                    case 4:
                    case 5:
                    case 11:
                    case 12:
                    case 13:
                    case 18:
                    case 22:
                    case 23:
                    case 25:
                    case 26:
                    case 27:
                    {
                        return 33;
                    }
                    case 6:
                    {
                        return 34;
                    }
                    case 16:
                    {
                        return 36;
                    }
                    case 24:
                    {
                        return 40;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 40:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == soul::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul::lexer::INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 3:
                    case 4:
                    case 5:
                    case 11:
                    case 12:
                    case 13:
                    case 18:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
                    {
                        return 33;
                    }
                    case 6:
                    {
                        return 34;
                    }
                    case 16:
                    {
                        return 36;
                    }
                    case 14:
                    {
                        return 41;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 41:
            {
                switch (cls)
                {
                    case 20:
                    {
                        return 42;
                    }
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
                    {
                        return 43;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 43:
            {
                switch (cls)
                {
                    case 20:
                    {
                        return 42;
                    }
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
                    {
                        return 43;
                    }
                    case 15:
                    {
                        return 44;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 44:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(1, lexer);
                if (tokenId == soul::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul::lexer::INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 42:
            {
                switch (cls)
                {
                    case 20:
                    {
                        return 42;
                    }
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
                    {
                        return 43;
                    }
                    case 15:
                    {
                        return 44;
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
                std::int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == soul::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul::lexer::INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 3:
                    case 4:
                    case 5:
                    case 11:
                    case 12:
                    case 13:
                    case 18:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
                    {
                        return 33;
                    }
                    case 6:
                    {
                        return 34;
                    }
                    case 16:
                    {
                        return 36;
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
                std::int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == soul::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul::lexer::INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 3:
                    case 4:
                    case 5:
                    case 11:
                    case 12:
                    case 13:
                    case 18:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
                    {
                        return 33;
                    }
                    case 6:
                    {
                        return 34;
                    }
                    case 16:
                    {
                        return 36;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 12:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == soul::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul::lexer::INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 3:
                    case 4:
                    case 5:
                    case 11:
                    case 12:
                    case 13:
                    case 18:
                    {
                        return 33;
                    }
                    case 6:
                    {
                        return 34;
                    }
                    case 16:
                    {
                        return 36;
                    }
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
                    {
                        return 37;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 11:
            {
                switch (cls)
                {
                    case 19:
                    {
                        return 10;
                    }
                    case 27:
                    {
                        return 45;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 45:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(5, lexer);
                if (tokenId == soul::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul::lexer::INVALID_TOKEN)
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
                        return 25;
                    }
                    case 25:
                    case 26:
                    {
                        return 31;
                    }
                    case 27:
                    {
                        return 45;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 10:
            {
                switch (cls)
                {
                    case 27:
                    {
                        return 32;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 9:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(19, lexer);
                if (tokenId == soul::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul::lexer::INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 18:
                    {
                        return 46;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 46:
            {
                switch (cls)
                {
                    case 27:
                    {
                        return 47;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 47:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == soul::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul::lexer::INVALID_TOKEN)
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
                        return 47;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 8:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(18, lexer);
                if (tokenId == soul::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul::lexer::INVALID_TOKEN)
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
                std::int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == soul::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul::lexer::INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 6:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == soul::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul::lexer::INVALID_TOKEN)
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
                switch (cls)
                {
                    case 9:
                    {
                        return 48;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 48:
            {
                switch (cls)
                {
                    case 0:
                    {
                        return 49;
                    }
                    case 1:
                    {
                        return 50;
                    }
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
                    case 35:
                    case 36:
                    case 37:
                    {
                        return 51;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 51:
            {
                switch (cls)
                {
                    case 0:
                    {
                        return 49;
                    }
                    case 1:
                    {
                        return 50;
                    }
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
                    case 35:
                    case 36:
                    case 37:
                    {
                        return 51;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 50:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(0, lexer);
                if (tokenId == soul::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul::lexer::INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 1:
                    case 7:
                    case 8:
                    {
                        return 1;
                    }
                    case 9:
                    {
                        return 5;
                    }
                    case 0:
                    {
                        return 52;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 52:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(0, lexer);
                if (tokenId == soul::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul::lexer::INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 0:
                    case 1:
                    case 7:
                    case 8:
                    {
                        return 1;
                    }
                    case 9:
                    {
                        return 5;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 49:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(0, lexer);
                if (tokenId == soul::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul::lexer::INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 0:
                    case 1:
                    case 7:
                    case 8:
                    {
                        return 1;
                    }
                    case 9:
                    {
                        return 5;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 4:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == soul::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul::lexer::INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 3:
                    case 4:
                    case 5:
                    case 11:
                    case 12:
                    case 13:
                    case 18:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
                    {
                        return 33;
                    }
                    case 6:
                    {
                        return 34;
                    }
                    case 16:
                    {
                        return 36;
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
                std::int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == soul::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul::lexer::INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 3:
                    case 4:
                    case 5:
                    case 11:
                    case 12:
                    case 13:
                    case 18:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
                    {
                        return 33;
                    }
                    case 6:
                    {
                        return 34;
                    }
                    case 16:
                    {
                        return 36;
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
                    case 2:
                    {
                        return 53;
                    }
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
                    case 35:
                    case 36:
                    case 37:
                    {
                        return 54;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 54:
            {
                switch (cls)
                {
                    case 2:
                    {
                        return 53;
                    }
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
                    case 35:
                    case 36:
                    case 37:
                    {
                        return 54;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 53:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(4, lexer);
                if (tokenId == soul::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul::lexer::INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 1:
            {
                auto& token = lexer.CurrentToken();
                auto prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                std::int64_t tokenId = GetTokenId(0, lexer);
                if (tokenId == soul::lexer::CONTINUE_TOKEN)
                {
                    token.id = soul::lexer::CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != soul::lexer::INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 0:
                    case 1:
                    case 7:
                    case 8:
                    {
                        return 1;
                    }
                    case 9:
                    {
                        return 5;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
        }
        return -1;
    }

    static std::int64_t GetTokenId(std::int32_t ruleIndex, soul::lexer::LexerBase<Char>& lexer)
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
                return CLSID;
                break;
            }
            case 2:
            {
                lexer.Retract();
                auto &token = lexer.CurrentToken();
                std::int64_t kw = lexer.GetKeywordToken(token.match);
                if (kw == INVALID_TOKEN) return ID;
                else return kw;
                break;
            }
            case 3:
            {
                lexer.Retract();
                return TYPEID;
                break;
            }
            case 4:
            {
                lexer.Retract();
                return STRING;
                break;
            }
            case 5:
            {
                lexer.Retract();
                return NUMBER;
                break;
            }
            case 6:
            {
                lexer.Retract();
                return HEXNUM;
                break;
            }
            case 7:
            {
                lexer.Retract();
                return LPAREN;
                break;
            }
            case 8:
            {
                lexer.Retract();
                return RPAREN;
                break;
            }
            case 9:
            {
                lexer.Retract();
                return COMMA;
                break;
            }
            case 10:
            {
                lexer.Retract();
                return LBRACE;
                break;
            }
            case 11:
            {
                lexer.Retract();
                return RBRACE;
                break;
            }
            case 12:
            {
                lexer.Retract();
                return AST;
                break;
            }
            case 13:
            {
                lexer.Retract();
                return COLON;
                break;
            }
            case 14:
            {
                lexer.Retract();
                return SEMICOLON;
                break;
            }
            case 15:
            {
                lexer.Retract();
                return LBRACKET;
                break;
            }
            case 16:
            {
                lexer.Retract();
                return RBRACKET;
                break;
            }
            case 17:
            {
                lexer.Retract();
                return ASSIGN;
                break;
            }
            case 18:
            {
                lexer.Retract();
                return AT;
                break;
            }
            case 19:
            {
                lexer.Retract();
                return DOLLAR;
                break;
            }
            case 20:
            {
                lexer.Retract();
                return EXCLAMATION;
                break;
            }
        }
        return soul::lexer::CONTINUE_TOKEN;
    }
};

template<typename Char>
soul::lexer::ClassMap<Char>* GetClassMap()
{
    static soul::lexer::ClassMap<Char>* classmap = soul::lexer::MakeClassMap<Char>("otava.intermediate.lexer.classmap");
    return classmap;
}

template<typename Char>
soul::lexer::ClassMap<Char>* GetClassMap(const std::string& moduleFileName, util::ResourceFlags resourceFlags)
{
    static soul::lexer::ClassMap<Char>* classmap = soul::lexer::MakeClassMap<Char>(moduleFileName, "otava.intermediate.lexer.classmap", resourceFlags);
    return classmap;
}

template<typename Char>
soul::lexer::KeywordMap<Char>* GetKeywords();

template<>
soul::lexer::KeywordMap<char>* GetKeywords<char>();

template<>
soul::lexer::KeywordMap<char8_t>* GetKeywords<char8_t>();

template<>
soul::lexer::KeywordMap<char16_t>* GetKeywords<char16_t>();

template<>
soul::lexer::KeywordMap<char32_t>* GetKeywords<char32_t>();

template<typename Char>
soul::lexer::Lexer<IntermediateLexer<Char>, Char> MakeLexer(const Char* start, const Char* end, const std::string& fileName)
{
    std::lock_guard<std::mutex> lock(MakeLexerMtx());
    auto lexer = soul::lexer::Lexer<IntermediateLexer<Char>, Char>(start, end, fileName);
    lexer.SetClassMap(GetClassMap<Char>());
    lexer.SetTokenCollection(GetTokens());
    lexer.SetKeywordMap(GetKeywords<Char>());
    return lexer;
}

template<typename Char>
soul::lexer::Lexer<IntermediateLexer<Char>, Char> MakeLexer(const std::string& moduleFileName, util::ResourceFlags resourceFlags, const Char* start, const Char* end, const std::string& fileName)
{
    std::lock_guard<std::mutex> lock(MakeLexerMtx());
    auto lexer = soul::lexer::Lexer<IntermediateLexer<Char>, Char>(start, end, fileName);
    lexer.SetClassMap(GetClassMap<Char>(moduleFileName, resourceFlags));
    lexer.SetTokenCollection(GetTokens());
    lexer.SetKeywordMap(GetKeywords<Char>());
    return lexer;
}

} // namespace otava::intermediate::lexer
