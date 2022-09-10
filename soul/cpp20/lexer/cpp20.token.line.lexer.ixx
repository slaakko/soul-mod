// this file has been automatically generated from 'C:/work/soul-mod/soul/cpp20/lexer/cpp20.token.line.lexer' using soul lexer generator slg version 4.1.0

export module soul.cpp20.token.line.lexer;

import std.core;
import soul.lexer;
import soul.ast.slg;
import soul.cpp20.token;

using namespace soul;
using namespace soul::lexer;
using namespace soul::cpp20::token;

export namespace soul::cpp20::token::line::lexer {

std::mutex& MakeLexerMtx();

template<typename Char>
struct Cpp20TokenLineLexer;

template<typename Char>
soul::lexer::Lexer<Cpp20TokenLineLexer<Char>, Char> MakeLexer(const Char* start, const Char* end, const std::string& fileName);

soul::ast::slg::TokenCollection* GetTokens();

struct Cpp20TokenLineLexer_Variables : public soul::lexer::Variables
{
    Cpp20TokenLineLexer_Variables();
    int langleCount;
};

template<typename Char>
struct Cpp20TokenLineLexer
{
    using Variables = Cpp20TokenLineLexer_Variables;

    static int32_t NextState(int32_t state, Char chr, soul::lexer::LexerBase<Char>& lexer)
    {
        ClassMap<Char>* classmap = lexer.GetClassMap();
        int32_t cls = classmap->GetClass(chr);
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
                    case 2:
                    {
                        return 3;
                    }
                    case 3:
                    case 4:
                    case 6:
                    case 13:
                    case 14:
                    case 15:
                    case 16:
                    case 22:
                    case 23:
                    case 24:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 40:
                    case 42:
                    case 43:
                    case 44:
                    {
                        return 4;
                    }
                    case 7:
                    case 8:
                    {
                        return 5;
                    }
                    case 9:
                    {
                        return 6;
                    }
                    case 11:
                    {
                        return 7;
                    }
                    case 12:
                    {
                        return 8;
                    }
                    case 17:
                    {
                        return 9;
                    }
                    case 18:
                    {
                        return 10;
                    }
                    case 19:
                    {
                        return 11;
                    }
                    case 20:
                    {
                        return 12;
                    }
                    case 21:
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
                    case 39:
                    case 41:
                    case 46:
                    case 47:
                    {
                        return 20;
                    }
                    case 45:
                    {
                        return 21;
                    }
                    case 48:
                    {
                        return 22;
                    }
                    case 49:
                    {
                        return 23;
                    }
                    case 50:
                    {
                        return 24;
                    }
                    case 51:
                    {
                        return 25;
                    }
                    case 52:
                    {
                        return 26;
                    }
                    case 53:
                    {
                        return 27;
                    }
                    case 54:
                    {
                        return 28;
                    }
                    case 55:
                    {
                        return 29;
                    }
                    case 56:
                    {
                        return 30;
                    }
                    case 57:
                    {
                        return 31;
                    }
                    case 58:
                    {
                        return 32;
                    }
                    case 59:
                    {
                        return 33;
                    }
                    case 60:
                    {
                        return 34;
                    }
                    case 61:
                    {
                        return 35;
                    }
                    case 62:
                    {
                        return 36;
                    }
                    case 63:
                    {
                        return 37;
                    }
                    case 64:
                    {
                        return 38;
                    }
                    case 65:
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
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(61, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 38:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(60, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 37:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(58, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 36:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(55, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(54, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 34:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(53, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 33:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(49, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 32:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(48, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 31:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(52, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 50:
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
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(33, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 30:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(29, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 50:
                    {
                        return 41;
                    }
                    case 56:
                    {
                        return 42;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 42:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(27, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 41:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(24, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 29:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(30, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 50:
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
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(23, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 28:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(31, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 50:
                    {
                        return 44;
                    }
                    case 54:
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
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(28, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 44:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(22, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 27:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(37, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 50:
                    {
                        return 46;
                    }
                    case 53:
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
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(39, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 50:
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
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(21, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 46:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(34, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 52:
                    {
                        return 49;
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
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(36, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 26:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(38, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 50:
                    {
                        return 50;
                    }
                    case 52:
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
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(40, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 50:
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
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(20, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 50:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(35, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 25:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(45, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 50:
                    {
                        return 53;
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
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(17, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 24:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(14, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 50:
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
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(32, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(13, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(26, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 48:
                    {
                        return 55;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 55:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(12, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 56;
                    }
                    case 13:
                    {
                        return 57;
                    }
                    case 14:
                    {
                        return 58;
                    }
                    case 15:
                    case 16:
                    {
                        return 59;
                    }
                    case 17:
                    case 18:
                    {
                        return 60;
                    }
                    case 19:
                    {
                        return 61;
                    }
                    case 24:
                    {
                        return 62;
                    }
                    case 25:
                    {
                        return 63;
                    }
                    case 29:
                    {
                        return 64;
                    }
                    case 36:
                    {
                        return 65;
                    }
                    case 37:
                    case 38:
                    {
                        return 66;
                    }
                    case 39:
                    case 41:
                    {
                        return 67;
                    }
                    case 42:
                    {
                        return 68;
                    }
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 69;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 69:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 16:
                    {
                        return 59;
                    }
                    case 17:
                    case 18:
                    {
                        return 60;
                    }
                    case 19:
                    {
                        return 61;
                    }
                    case 24:
                    {
                        return 62;
                    }
                    case 25:
                    {
                        return 63;
                    }
                    case 29:
                    {
                        return 64;
                    }
                    case 37:
                    case 38:
                    {
                        return 66;
                    }
                    case 39:
                    case 41:
                    {
                        return 67;
                    }
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 69;
                    }
                    case 2:
                    {
                        return 70;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 70:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 16:
                    {
                        return 59;
                    }
                    case 17:
                    case 18:
                    {
                        return 60;
                    }
                    case 19:
                    {
                        return 61;
                    }
                    case 24:
                    {
                        return 62;
                    }
                    case 25:
                    {
                        return 63;
                    }
                    case 29:
                    {
                        return 64;
                    }
                    case 37:
                    case 38:
                    {
                        return 66;
                    }
                    case 39:
                    case 41:
                    {
                        return 67;
                    }
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 69;
                    }
                    case 2:
                    {
                        return 71;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 71:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 16:
                    {
                        return 59;
                    }
                    case 17:
                    case 18:
                    {
                        return 60;
                    }
                    case 19:
                    {
                        return 61;
                    }
                    case 24:
                    {
                        return 62;
                    }
                    case 25:
                    {
                        return 63;
                    }
                    case 29:
                    {
                        return 64;
                    }
                    case 37:
                    case 38:
                    {
                        return 66;
                    }
                    case 39:
                    case 41:
                    {
                        return 67;
                    }
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 69;
                    }
                    case 2:
                    {
                        return 72;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 72:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 16:
                    {
                        return 59;
                    }
                    case 17:
                    case 18:
                    {
                        return 60;
                    }
                    case 24:
                    {
                        return 62;
                    }
                    case 25:
                    {
                        return 63;
                    }
                    case 29:
                    {
                        return 64;
                    }
                    case 39:
                    case 41:
                    {
                        return 67;
                    }
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 69;
                    }
                    case 2:
                    {
                        return 73;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 73:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 18:
                    {
                        return 60;
                    }
                    case 24:
                    {
                        return 62;
                    }
                    case 25:
                    {
                        return 63;
                    }
                    case 2:
                    {
                        return 74;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 74:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 18:
                    {
                        return 60;
                    }
                    case 2:
                    {
                        return 75;
                    }
                    case 24:
                    {
                        return 76;
                    }
                    case 25:
                    {
                        return 77;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 77:
            {
                switch (cls)
                {
                    case 25:
                    {
                        return 78;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 78:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 79;
                    }
                    case 17:
                    case 18:
                    {
                        return 80;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 80:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 81;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 81:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 82;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 82:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 83;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 83:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 84;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 84:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 85;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 85:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 79:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    case 17:
                    case 18:
                    {
                        return 80;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 76:
            {
                switch (cls)
                {
                    case 24:
                    {
                        return 86;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 86:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 79;
                    }
                    case 17:
                    case 18:
                    {
                        return 80;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 75:
            {
                switch (cls)
                {
                    case 17:
                    case 18:
                    {
                        return 60;
                    }
                    case 24:
                    {
                        return 76;
                    }
                    case 25:
                    {
                        return 77;
                    }
                    case 2:
                    {
                        return 87;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 87:
            {
                switch (cls)
                {
                    case 17:
                    case 18:
                    {
                        return 88;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 88:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 89;
                    }
                    case 24:
                    {
                        return 90;
                    }
                    case 25:
                    {
                        return 91;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 91:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 92;
                    }
                    case 25:
                    {
                        return 93;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 93:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 94;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 94:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 92;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 92:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 95;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 95:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 81;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 90:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 92;
                    }
                    case 24:
                    {
                        return 96;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 96:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 94;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 89:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 92;
                    }
                    case 24:
                    {
                        return 97;
                    }
                    case 25:
                    {
                        return 98;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 98:
            {
                switch (cls)
                {
                    case 25:
                    {
                        return 93;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 97:
            {
                switch (cls)
                {
                    case 24:
                    {
                        return 96;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 68:
            {
                switch (cls)
                {
                    case 2:
                    {
                        return 99;
                    }
                    case 29:
                    {
                        return 100;
                    }
                    case 45:
                    {
                        return 101;
                    }
                    case 47:
                    {
                        return 102;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 102:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 29:
                    {
                        return 100;
                    }
                    case 45:
                    {
                        return 101;
                    }
                    case 47:
                    {
                        return 102;
                    }
                    case 2:
                    {
                        return 103;
                    }
                    case 15:
                    case 16:
                    {
                        return 104;
                    }
                    case 17:
                    case 18:
                    {
                        return 105;
                    }
                    case 24:
                    {
                        return 106;
                    }
                    case 25:
                    {
                        return 107;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 107:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    case 17:
                    case 18:
                    {
                        return 108;
                    }
                    case 25:
                    {
                        return 109;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 109:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 110;
                    }
                    case 17:
                    case 18:
                    {
                        return 111;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 111:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 112;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 112:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 113;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 113:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 114;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 114:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 115;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 115:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 84;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 110:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    case 17:
                    case 18:
                    {
                        return 111;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 108:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 113;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 106:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    case 17:
                    case 18:
                    {
                        return 108;
                    }
                    case 24:
                    {
                        return 116;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 116:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 110;
                    }
                    case 17:
                    case 18:
                    {
                        return 111;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 105:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 117;
                    }
                    case 15:
                    case 16:
                    {
                        return 118;
                    }
                    case 24:
                    {
                        return 119;
                    }
                    case 25:
                    {
                        return 120;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 120:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 121;
                    }
                    case 25:
                    {
                        return 122;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 122:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 123;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 123:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 121;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 121:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 124;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 124:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 112;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 119:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 121;
                    }
                    case 24:
                    {
                        return 125;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 125:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 123;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 118:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 124;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 117:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 121;
                    }
                    case 24:
                    {
                        return 126;
                    }
                    case 25:
                    {
                        return 127;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 127:
            {
                switch (cls)
                {
                    case 25:
                    {
                        return 122;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 126:
            {
                switch (cls)
                {
                    case 24:
                    {
                        return 125;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 104:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    case 17:
                    case 18:
                    {
                        return 128;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 128:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 114;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 103:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 29:
                    {
                        return 100;
                    }
                    case 45:
                    {
                        return 101;
                    }
                    case 47:
                    {
                        return 102;
                    }
                    case 15:
                    case 16:
                    {
                        return 104;
                    }
                    case 17:
                    case 18:
                    {
                        return 105;
                    }
                    case 24:
                    {
                        return 106;
                    }
                    case 25:
                    {
                        return 107;
                    }
                    case 2:
                    {
                        return 129;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 129:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 29:
                    {
                        return 100;
                    }
                    case 45:
                    {
                        return 101;
                    }
                    case 47:
                    {
                        return 102;
                    }
                    case 15:
                    case 16:
                    {
                        return 104;
                    }
                    case 17:
                    case 18:
                    {
                        return 105;
                    }
                    case 24:
                    {
                        return 106;
                    }
                    case 25:
                    {
                        return 107;
                    }
                    case 2:
                    {
                        return 130;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 130:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 29:
                    {
                        return 100;
                    }
                    case 45:
                    {
                        return 101;
                    }
                    case 47:
                    {
                        return 102;
                    }
                    case 15:
                    case 16:
                    {
                        return 104;
                    }
                    case 17:
                    case 18:
                    {
                        return 105;
                    }
                    case 24:
                    {
                        return 106;
                    }
                    case 25:
                    {
                        return 107;
                    }
                    case 2:
                    {
                        return 131;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 131:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 29:
                    {
                        return 100;
                    }
                    case 45:
                    {
                        return 101;
                    }
                    case 47:
                    {
                        return 102;
                    }
                    case 15:
                    case 16:
                    {
                        return 104;
                    }
                    case 17:
                    case 18:
                    {
                        return 105;
                    }
                    case 24:
                    {
                        return 106;
                    }
                    case 25:
                    {
                        return 107;
                    }
                    case 2:
                    {
                        return 132;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 132:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 45:
                    {
                        return 101;
                    }
                    case 47:
                    {
                        return 102;
                    }
                    case 17:
                    case 18:
                    {
                        return 105;
                    }
                    case 24:
                    {
                        return 106;
                    }
                    case 25:
                    {
                        return 107;
                    }
                    case 2:
                    {
                        return 133;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 133:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 18:
                    {
                        return 105;
                    }
                    case 2:
                    {
                        return 134;
                    }
                    case 24:
                    {
                        return 135;
                    }
                    case 25:
                    {
                        return 136;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 136:
            {
                switch (cls)
                {
                    case 25:
                    {
                        return 109;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 135:
            {
                switch (cls)
                {
                    case 24:
                    {
                        return 116;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 134:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 18:
                    {
                        return 105;
                    }
                    case 24:
                    {
                        return 135;
                    }
                    case 25:
                    {
                        return 136;
                    }
                    case 2:
                    {
                        return 137;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 137:
            {
                switch (cls)
                {
                    case 17:
                    case 18:
                    {
                        return 138;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 138:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 117;
                    }
                    case 24:
                    {
                        return 119;
                    }
                    case 25:
                    {
                        return 120;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 101:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 29:
                    {
                        return 100;
                    }
                    case 45:
                    {
                        return 101;
                    }
                    case 47:
                    {
                        return 102;
                    }
                    case 2:
                    {
                        return 103;
                    }
                    case 15:
                    case 16:
                    {
                        return 104;
                    }
                    case 17:
                    case 18:
                    {
                        return 105;
                    }
                    case 24:
                    {
                        return 106;
                    }
                    case 25:
                    {
                        return 107;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 100:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 29:
                    {
                        return 100;
                    }
                    case 45:
                    {
                        return 101;
                    }
                    case 47:
                    {
                        return 102;
                    }
                    case 15:
                    case 16:
                    {
                        return 104;
                    }
                    case 17:
                    case 18:
                    {
                        return 105;
                    }
                    case 24:
                    {
                        return 106;
                    }
                    case 25:
                    {
                        return 107;
                    }
                    case 2:
                    {
                        return 129;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 99:
            {
                switch (cls)
                {
                    case 29:
                    {
                        return 100;
                    }
                    case 45:
                    {
                        return 101;
                    }
                    case 47:
                    {
                        return 102;
                    }
                    case 2:
                    {
                        return 139;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 139:
            {
                switch (cls)
                {
                    case 29:
                    {
                        return 100;
                    }
                    case 45:
                    {
                        return 101;
                    }
                    case 47:
                    {
                        return 102;
                    }
                    case 2:
                    {
                        return 140;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 140:
            {
                switch (cls)
                {
                    case 29:
                    {
                        return 100;
                    }
                    case 45:
                    {
                        return 101;
                    }
                    case 47:
                    {
                        return 102;
                    }
                    case 2:
                    {
                        return 141;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 141:
            {
                switch (cls)
                {
                    case 45:
                    {
                        return 101;
                    }
                    case 47:
                    {
                        return 102;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 67:
            {
                switch (cls)
                {
                    case 19:
                    {
                        return 61;
                    }
                    case 37:
                    case 38:
                    {
                        return 66;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 67;
                    }
                    case 2:
                    {
                        return 142;
                    }
                    case 29:
                    {
                        return 143;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 143:
            {
                switch (cls)
                {
                    case 19:
                    {
                        return 61;
                    }
                    case 37:
                    case 38:
                    {
                        return 66;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 67;
                    }
                    case 2:
                    {
                        return 142;
                    }
                    case 29:
                    {
                        return 143;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 142:
            {
                switch (cls)
                {
                    case 19:
                    {
                        return 61;
                    }
                    case 37:
                    case 38:
                    {
                        return 66;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 67;
                    }
                    case 29:
                    {
                        return 143;
                    }
                    case 2:
                    {
                        return 144;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 144:
            {
                switch (cls)
                {
                    case 19:
                    {
                        return 61;
                    }
                    case 37:
                    case 38:
                    {
                        return 66;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 67;
                    }
                    case 29:
                    {
                        return 143;
                    }
                    case 2:
                    {
                        return 145;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 145:
            {
                switch (cls)
                {
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 67;
                    }
                    case 29:
                    {
                        return 143;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 66:
            {
                switch (cls)
                {
                    case 2:
                    {
                        return 146;
                    }
                    case 20:
                    {
                        return 147;
                    }
                    case 21:
                    {
                        return 148;
                    }
                    case 29:
                    {
                        return 149;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 150;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 150:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 29:
                    {
                        return 149;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 150;
                    }
                    case 2:
                    {
                        return 151;
                    }
                    case 24:
                    case 25:
                    {
                        return 152;
                    }
                    case 40:
                    case 43:
                    {
                        return 153;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 153:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 154;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 154:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 155;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 155:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 152:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 154;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 151:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 29:
                    {
                        return 149;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 150;
                    }
                    case 24:
                    case 25:
                    {
                        return 152;
                    }
                    case 40:
                    case 43:
                    {
                        return 153;
                    }
                    case 2:
                    {
                        return 156;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 156:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 29:
                    {
                        return 149;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 150;
                    }
                    case 24:
                    case 25:
                    {
                        return 152;
                    }
                    case 40:
                    case 43:
                    {
                        return 153;
                    }
                    case 2:
                    {
                        return 157;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 157:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 29:
                    {
                        return 149;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 150;
                    }
                    case 24:
                    case 25:
                    {
                        return 152;
                    }
                    case 40:
                    case 43:
                    {
                        return 153;
                    }
                    case 2:
                    {
                        return 158;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 158:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 24:
                    case 25:
                    {
                        return 152;
                    }
                    case 40:
                    case 43:
                    {
                        return 153;
                    }
                    case 2:
                    {
                        return 155;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 149:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 29:
                    {
                        return 149;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 150;
                    }
                    case 2:
                    {
                        return 151;
                    }
                    case 24:
                    case 25:
                    {
                        return 152;
                    }
                    case 40:
                    case 43:
                    {
                        return 153;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 148:
            {
                switch (cls)
                {
                    case 29:
                    {
                        return 149;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 150;
                    }
                    case 2:
                    {
                        return 159;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 159:
            {
                switch (cls)
                {
                    case 29:
                    {
                        return 149;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 150;
                    }
                    case 2:
                    {
                        return 160;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 160:
            {
                switch (cls)
                {
                    case 29:
                    {
                        return 149;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 150;
                    }
                    case 2:
                    {
                        return 161;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 161:
            {
                switch (cls)
                {
                    case 29:
                    {
                        return 149;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 150;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 147:
            {
                switch (cls)
                {
                    case 29:
                    {
                        return 149;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 150;
                    }
                    case 2:
                    {
                        return 159;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 146:
            {
                switch (cls)
                {
                    case 20:
                    {
                        return 147;
                    }
                    case 21:
                    {
                        return 148;
                    }
                    case 29:
                    {
                        return 149;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 150;
                    }
                    case 2:
                    {
                        return 160;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 65:
            {
                switch (cls)
                {
                    case 2:
                    {
                        return 99;
                    }
                    case 29:
                    {
                        return 100;
                    }
                    case 45:
                    {
                        return 101;
                    }
                    case 47:
                    {
                        return 102;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 64:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 16:
                    {
                        return 59;
                    }
                    case 17:
                    case 18:
                    {
                        return 60;
                    }
                    case 19:
                    {
                        return 61;
                    }
                    case 24:
                    {
                        return 62;
                    }
                    case 25:
                    {
                        return 63;
                    }
                    case 29:
                    {
                        return 64;
                    }
                    case 37:
                    case 38:
                    {
                        return 66;
                    }
                    case 39:
                    case 41:
                    {
                        return 67;
                    }
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 69;
                    }
                    case 2:
                    {
                        return 70;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 63:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    {
                        return 78;
                    }
                    case 2:
                    case 17:
                    case 18:
                    {
                        return 162;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 162:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 82;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 62:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 24:
                    {
                        return 86;
                    }
                    case 2:
                    case 17:
                    case 18:
                    {
                        return 162;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 61:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 24:
                    case 25:
                    {
                        return 152;
                    }
                    case 40:
                    case 43:
                    {
                        return 153;
                    }
                    case 2:
                    {
                        return 163;
                    }
                    case 29:
                    {
                        return 164;
                    }
                    case 37:
                    case 38:
                    {
                        return 165;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 166;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 166:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 24:
                    case 25:
                    {
                        return 152;
                    }
                    case 40:
                    case 43:
                    {
                        return 153;
                    }
                    case 29:
                    {
                        return 164;
                    }
                    case 37:
                    case 38:
                    {
                        return 165;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 166;
                    }
                    case 2:
                    {
                        return 167;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 167:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 24:
                    case 25:
                    {
                        return 152;
                    }
                    case 40:
                    case 43:
                    {
                        return 153;
                    }
                    case 29:
                    {
                        return 164;
                    }
                    case 37:
                    case 38:
                    {
                        return 165;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 166;
                    }
                    case 2:
                    {
                        return 168;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 168:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 24:
                    case 25:
                    {
                        return 152;
                    }
                    case 40:
                    case 43:
                    {
                        return 153;
                    }
                    case 29:
                    {
                        return 164;
                    }
                    case 37:
                    case 38:
                    {
                        return 165;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 166;
                    }
                    case 2:
                    {
                        return 169;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 169:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 24:
                    case 25:
                    {
                        return 152;
                    }
                    case 40:
                    case 43:
                    {
                        return 153;
                    }
                    case 29:
                    {
                        return 164;
                    }
                    case 37:
                    case 38:
                    {
                        return 165;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 166;
                    }
                    case 2:
                    {
                        return 170;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 170:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 24:
                    case 25:
                    {
                        return 152;
                    }
                    case 40:
                    case 43:
                    {
                        return 153;
                    }
                    case 2:
                    {
                        return 171;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 171:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 24:
                    case 25:
                    {
                        return 152;
                    }
                    case 40:
                    case 43:
                    {
                        return 153;
                    }
                    case 2:
                    {
                        return 158;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 165:
            {
                switch (cls)
                {
                    case 2:
                    {
                        return 172;
                    }
                    case 20:
                    {
                        return 173;
                    }
                    case 21:
                    {
                        return 174;
                    }
                    case 29:
                    {
                        return 175;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 176;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 176:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 24:
                    case 25:
                    {
                        return 152;
                    }
                    case 40:
                    case 43:
                    {
                        return 153;
                    }
                    case 29:
                    {
                        return 175;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 176;
                    }
                    case 2:
                    {
                        return 177;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 177:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 24:
                    case 25:
                    {
                        return 152;
                    }
                    case 40:
                    case 43:
                    {
                        return 153;
                    }
                    case 29:
                    {
                        return 175;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 176;
                    }
                    case 2:
                    {
                        return 178;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 178:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 24:
                    case 25:
                    {
                        return 152;
                    }
                    case 40:
                    case 43:
                    {
                        return 153;
                    }
                    case 29:
                    {
                        return 175;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 176;
                    }
                    case 2:
                    {
                        return 179;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 179:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 24:
                    case 25:
                    {
                        return 152;
                    }
                    case 40:
                    case 43:
                    {
                        return 153;
                    }
                    case 2:
                    {
                        return 158;
                    }
                    case 29:
                    {
                        return 175;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 176;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 175:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 24:
                    case 25:
                    {
                        return 152;
                    }
                    case 40:
                    case 43:
                    {
                        return 153;
                    }
                    case 29:
                    {
                        return 175;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 176;
                    }
                    case 2:
                    {
                        return 177;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 174:
            {
                switch (cls)
                {
                    case 29:
                    {
                        return 175;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 176;
                    }
                    case 2:
                    {
                        return 180;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 180:
            {
                switch (cls)
                {
                    case 29:
                    {
                        return 175;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 176;
                    }
                    case 2:
                    {
                        return 181;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 181:
            {
                switch (cls)
                {
                    case 29:
                    {
                        return 175;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 176;
                    }
                    case 2:
                    {
                        return 182;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 182:
            {
                switch (cls)
                {
                    case 29:
                    {
                        return 175;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 176;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 173:
            {
                switch (cls)
                {
                    case 29:
                    {
                        return 175;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 176;
                    }
                    case 2:
                    {
                        return 180;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 172:
            {
                switch (cls)
                {
                    case 20:
                    {
                        return 173;
                    }
                    case 21:
                    {
                        return 174;
                    }
                    case 29:
                    {
                        return 175;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 176;
                    }
                    case 2:
                    {
                        return 181;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 164:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 24:
                    case 25:
                    {
                        return 152;
                    }
                    case 40:
                    case 43:
                    {
                        return 153;
                    }
                    case 29:
                    {
                        return 164;
                    }
                    case 37:
                    case 38:
                    {
                        return 165;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 166;
                    }
                    case 2:
                    {
                        return 167;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 163:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 24:
                    case 25:
                    {
                        return 152;
                    }
                    case 40:
                    case 43:
                    {
                        return 153;
                    }
                    case 29:
                    {
                        return 164;
                    }
                    case 37:
                    case 38:
                    {
                        return 165;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 166;
                    }
                    case 2:
                    {
                        return 183;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 183:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 24:
                    case 25:
                    {
                        return 152;
                    }
                    case 40:
                    case 43:
                    {
                        return 153;
                    }
                    case 29:
                    {
                        return 164;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 166;
                    }
                    case 2:
                    {
                        return 171;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 60:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 89;
                    }
                    case 24:
                    {
                        return 90;
                    }
                    case 25:
                    {
                        return 91;
                    }
                    case 15:
                    case 16:
                    {
                        return 184;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 184:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 95;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 59:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    case 17:
                    case 18:
                    {
                        return 185;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 185:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 83;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 58:
            {
                switch (cls)
                {
                    case 2:
                    {
                        return 186;
                    }
                    case 19:
                    {
                        return 187;
                    }
                    case 29:
                    {
                        return 188;
                    }
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 189;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 189:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 29:
                    {
                        return 188;
                    }
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 189;
                    }
                    case 2:
                    {
                        return 190;
                    }
                    case 15:
                    case 16:
                    {
                        return 191;
                    }
                    case 17:
                    case 18:
                    {
                        return 192;
                    }
                    case 19:
                    {
                        return 193;
                    }
                    case 22:
                    case 23:
                    {
                        return 194;
                    }
                    case 24:
                    {
                        return 195;
                    }
                    case 25:
                    {
                        return 196;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 196:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    case 17:
                    case 18:
                    {
                        return 197;
                    }
                    case 25:
                    {
                        return 198;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 198:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 199;
                    }
                    case 17:
                    case 18:
                    {
                        return 200;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 200:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 201;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 201:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 202;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 202:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 203;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 203:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 115;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 199:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    case 17:
                    case 18:
                    {
                        return 200;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 197:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 202;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 195:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    case 17:
                    case 18:
                    {
                        return 197;
                    }
                    case 24:
                    {
                        return 204;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 204:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 199;
                    }
                    case 17:
                    case 18:
                    {
                        return 200;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 194:
            {
                switch (cls)
                {
                    case 2:
                    {
                        return 205;
                    }
                    case 20:
                    {
                        return 206;
                    }
                    case 21:
                    {
                        return 207;
                    }
                    case 29:
                    {
                        return 208;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 209;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 209:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 29:
                    {
                        return 208;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 209;
                    }
                    case 2:
                    {
                        return 210;
                    }
                    case 24:
                    case 25:
                    {
                        return 211;
                    }
                    case 40:
                    case 43:
                    {
                        return 212;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 212:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 213;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 213:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 214;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 214:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 155;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 211:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 213;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 210:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 29:
                    {
                        return 208;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 209;
                    }
                    case 24:
                    case 25:
                    {
                        return 211;
                    }
                    case 40:
                    case 43:
                    {
                        return 212;
                    }
                    case 2:
                    {
                        return 215;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 215:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 29:
                    {
                        return 208;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 209;
                    }
                    case 24:
                    case 25:
                    {
                        return 211;
                    }
                    case 40:
                    case 43:
                    {
                        return 212;
                    }
                    case 2:
                    {
                        return 216;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 216:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 29:
                    {
                        return 208;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 209;
                    }
                    case 24:
                    case 25:
                    {
                        return 211;
                    }
                    case 40:
                    case 43:
                    {
                        return 212;
                    }
                    case 2:
                    {
                        return 214;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 208:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 29:
                    {
                        return 208;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 209;
                    }
                    case 2:
                    {
                        return 210;
                    }
                    case 24:
                    case 25:
                    {
                        return 211;
                    }
                    case 40:
                    case 43:
                    {
                        return 212;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 207:
            {
                switch (cls)
                {
                    case 29:
                    {
                        return 208;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 209;
                    }
                    case 2:
                    {
                        return 217;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 217:
            {
                switch (cls)
                {
                    case 29:
                    {
                        return 208;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 209;
                    }
                    case 2:
                    {
                        return 218;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 218:
            {
                switch (cls)
                {
                    case 29:
                    {
                        return 208;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 209;
                    }
                    case 2:
                    {
                        return 219;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 219:
            {
                switch (cls)
                {
                    case 29:
                    {
                        return 208;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 209;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 206:
            {
                switch (cls)
                {
                    case 29:
                    {
                        return 208;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 209;
                    }
                    case 2:
                    {
                        return 217;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 205:
            {
                switch (cls)
                {
                    case 20:
                    {
                        return 206;
                    }
                    case 21:
                    {
                        return 207;
                    }
                    case 29:
                    {
                        return 208;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 209;
                    }
                    case 2:
                    {
                        return 218;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 193:
            {
                switch (cls)
                {
                    case 2:
                    {
                        return 220;
                    }
                    case 22:
                    case 23:
                    {
                        return 221;
                    }
                    case 29:
                    {
                        return 222;
                    }
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 223;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 223:
            {
                switch (cls)
                {
                    case 22:
                    case 23:
                    {
                        return 221;
                    }
                    case 29:
                    {
                        return 222;
                    }
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 223;
                    }
                    case 2:
                    {
                        return 224;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 224:
            {
                switch (cls)
                {
                    case 22:
                    case 23:
                    {
                        return 221;
                    }
                    case 29:
                    {
                        return 222;
                    }
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 223;
                    }
                    case 2:
                    {
                        return 225;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 225:
            {
                switch (cls)
                {
                    case 22:
                    case 23:
                    {
                        return 221;
                    }
                    case 29:
                    {
                        return 222;
                    }
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 223;
                    }
                    case 2:
                    {
                        return 226;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 226:
            {
                switch (cls)
                {
                    case 22:
                    case 23:
                    {
                        return 221;
                    }
                    case 29:
                    {
                        return 222;
                    }
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 223;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 222:
            {
                switch (cls)
                {
                    case 22:
                    case 23:
                    {
                        return 221;
                    }
                    case 29:
                    {
                        return 222;
                    }
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 223;
                    }
                    case 2:
                    {
                        return 224;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 221:
            {
                switch (cls)
                {
                    case 2:
                    {
                        return 227;
                    }
                    case 20:
                    {
                        return 228;
                    }
                    case 21:
                    {
                        return 229;
                    }
                    case 29:
                    {
                        return 230;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 231;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 231:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 29:
                    {
                        return 230;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 231;
                    }
                    case 2:
                    {
                        return 232;
                    }
                    case 24:
                    case 25:
                    {
                        return 233;
                    }
                    case 40:
                    case 43:
                    {
                        return 234;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 234:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 235;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 235:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 214;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 233:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 235;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 232:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 29:
                    {
                        return 230;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 231;
                    }
                    case 24:
                    case 25:
                    {
                        return 233;
                    }
                    case 40:
                    case 43:
                    {
                        return 234;
                    }
                    case 2:
                    {
                        return 236;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 236:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 29:
                    {
                        return 230;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 231;
                    }
                    case 24:
                    case 25:
                    {
                        return 233;
                    }
                    case 40:
                    case 43:
                    {
                        return 234;
                    }
                    case 2:
                    {
                        return 237;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 237:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 214;
                    }
                    case 29:
                    {
                        return 230;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 231;
                    }
                    case 24:
                    case 25:
                    {
                        return 233;
                    }
                    case 40:
                    case 43:
                    {
                        return 234;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 230:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 29:
                    {
                        return 230;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 231;
                    }
                    case 2:
                    {
                        return 232;
                    }
                    case 24:
                    case 25:
                    {
                        return 233;
                    }
                    case 40:
                    case 43:
                    {
                        return 234;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 229:
            {
                switch (cls)
                {
                    case 29:
                    {
                        return 230;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 231;
                    }
                    case 2:
                    {
                        return 238;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 238:
            {
                switch (cls)
                {
                    case 29:
                    {
                        return 230;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 231;
                    }
                    case 2:
                    {
                        return 239;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 239:
            {
                switch (cls)
                {
                    case 29:
                    {
                        return 230;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 231;
                    }
                    case 2:
                    {
                        return 240;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 240:
            {
                switch (cls)
                {
                    case 29:
                    {
                        return 230;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 231;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 228:
            {
                switch (cls)
                {
                    case 29:
                    {
                        return 230;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 231;
                    }
                    case 2:
                    {
                        return 238;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 227:
            {
                switch (cls)
                {
                    case 20:
                    {
                        return 228;
                    }
                    case 21:
                    {
                        return 229;
                    }
                    case 29:
                    {
                        return 230;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 231;
                    }
                    case 2:
                    {
                        return 239;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 220:
            {
                switch (cls)
                {
                    case 22:
                    case 23:
                    {
                        return 221;
                    }
                    case 29:
                    {
                        return 222;
                    }
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 223;
                    }
                    case 2:
                    {
                        return 241;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 241:
            {
                switch (cls)
                {
                    case 29:
                    {
                        return 222;
                    }
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 223;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 192:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 242;
                    }
                    case 15:
                    case 16:
                    {
                        return 243;
                    }
                    case 24:
                    {
                        return 244;
                    }
                    case 25:
                    {
                        return 245;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 245:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 246;
                    }
                    case 25:
                    {
                        return 247;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 247:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 248;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 248:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 246;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 246:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 249;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 249:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 201;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 244:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 246;
                    }
                    case 24:
                    {
                        return 250;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 250:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 248;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 243:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 249;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 242:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 246;
                    }
                    case 24:
                    {
                        return 251;
                    }
                    case 25:
                    {
                        return 252;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 252:
            {
                switch (cls)
                {
                    case 25:
                    {
                        return 247;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 251:
            {
                switch (cls)
                {
                    case 24:
                    {
                        return 250;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 191:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    case 17:
                    case 18:
                    {
                        return 253;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 253:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 203;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 190:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 29:
                    {
                        return 188;
                    }
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 189;
                    }
                    case 15:
                    case 16:
                    {
                        return 191;
                    }
                    case 17:
                    case 18:
                    {
                        return 192;
                    }
                    case 19:
                    {
                        return 193;
                    }
                    case 22:
                    case 23:
                    {
                        return 194;
                    }
                    case 24:
                    {
                        return 195;
                    }
                    case 25:
                    {
                        return 196;
                    }
                    case 2:
                    {
                        return 254;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 254:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 29:
                    {
                        return 188;
                    }
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 189;
                    }
                    case 15:
                    case 16:
                    {
                        return 191;
                    }
                    case 17:
                    case 18:
                    {
                        return 192;
                    }
                    case 19:
                    {
                        return 193;
                    }
                    case 22:
                    case 23:
                    {
                        return 194;
                    }
                    case 24:
                    {
                        return 195;
                    }
                    case 25:
                    {
                        return 196;
                    }
                    case 2:
                    {
                        return 255;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 255:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 29:
                    {
                        return 188;
                    }
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 189;
                    }
                    case 15:
                    case 16:
                    {
                        return 191;
                    }
                    case 17:
                    case 18:
                    {
                        return 192;
                    }
                    case 24:
                    {
                        return 195;
                    }
                    case 25:
                    {
                        return 196;
                    }
                    case 2:
                    {
                        return 256;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 256:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 18:
                    {
                        return 192;
                    }
                    case 24:
                    {
                        return 195;
                    }
                    case 25:
                    {
                        return 196;
                    }
                    case 2:
                    {
                        return 257;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 257:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 18:
                    {
                        return 192;
                    }
                    case 2:
                    {
                        return 258;
                    }
                    case 24:
                    {
                        return 259;
                    }
                    case 25:
                    {
                        return 260;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 260:
            {
                switch (cls)
                {
                    case 25:
                    {
                        return 198;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 259:
            {
                switch (cls)
                {
                    case 24:
                    {
                        return 204;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 258:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 18:
                    {
                        return 192;
                    }
                    case 24:
                    {
                        return 259;
                    }
                    case 25:
                    {
                        return 260;
                    }
                    case 2:
                    {
                        return 261;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 261:
            {
                switch (cls)
                {
                    case 17:
                    case 18:
                    {
                        return 262;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 262:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 242;
                    }
                    case 24:
                    {
                        return 244;
                    }
                    case 25:
                    {
                        return 245;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 188:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 29:
                    {
                        return 188;
                    }
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 189;
                    }
                    case 2:
                    {
                        return 190;
                    }
                    case 15:
                    case 16:
                    {
                        return 191;
                    }
                    case 17:
                    case 18:
                    {
                        return 192;
                    }
                    case 19:
                    {
                        return 193;
                    }
                    case 22:
                    case 23:
                    {
                        return 194;
                    }
                    case 24:
                    {
                        return 195;
                    }
                    case 25:
                    {
                        return 196;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 187:
            {
                switch (cls)
                {
                    case 29:
                    {
                        return 222;
                    }
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 223;
                    }
                    case 2:
                    {
                        return 263;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 263:
            {
                switch (cls)
                {
                    case 29:
                    {
                        return 222;
                    }
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 223;
                    }
                    case 2:
                    {
                        return 241;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 186:
            {
                switch (cls)
                {
                    case 19:
                    {
                        return 187;
                    }
                    case 29:
                    {
                        return 188;
                    }
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 189;
                    }
                    case 2:
                    {
                        return 264;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 264:
            {
                switch (cls)
                {
                    case 19:
                    {
                        return 187;
                    }
                    case 29:
                    {
                        return 188;
                    }
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 189;
                    }
                    case 2:
                    {
                        return 265;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 265:
            {
                switch (cls)
                {
                    case 19:
                    {
                        return 187;
                    }
                    case 29:
                    {
                        return 188;
                    }
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 189;
                    }
                    case 2:
                    {
                        return 266;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 266:
            {
                switch (cls)
                {
                    case 29:
                    {
                        return 267;
                    }
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 268;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 268:
            {
                switch (cls)
                {
                    case 19:
                    {
                        return 193;
                    }
                    case 29:
                    {
                        return 267;
                    }
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 268;
                    }
                    case 2:
                    {
                        return 269;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 269:
            {
                switch (cls)
                {
                    case 19:
                    {
                        return 193;
                    }
                    case 29:
                    {
                        return 267;
                    }
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 268;
                    }
                    case 2:
                    {
                        return 270;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 270:
            {
                switch (cls)
                {
                    case 19:
                    {
                        return 193;
                    }
                    case 2:
                    {
                        return 266;
                    }
                    case 29:
                    {
                        return 267;
                    }
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 268;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 267:
            {
                switch (cls)
                {
                    case 19:
                    {
                        return 193;
                    }
                    case 29:
                    {
                        return 267;
                    }
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 268;
                    }
                    case 2:
                    {
                        return 269;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 57:
            {
                switch (cls)
                {
                    case 2:
                    {
                        return 186;
                    }
                    case 19:
                    {
                        return 187;
                    }
                    case 29:
                    {
                        return 188;
                    }
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 189;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 56:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 16:
                    {
                        return 59;
                    }
                    case 17:
                    case 18:
                    {
                        return 60;
                    }
                    case 19:
                    {
                        return 61;
                    }
                    case 24:
                    {
                        return 62;
                    }
                    case 25:
                    {
                        return 63;
                    }
                    case 29:
                    {
                        return 64;
                    }
                    case 37:
                    case 38:
                    {
                        return 66;
                    }
                    case 39:
                    case 41:
                    {
                        return 67;
                    }
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 69;
                    }
                    case 2:
                    {
                        return 271;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 271:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 16:
                    {
                        return 59;
                    }
                    case 17:
                    case 18:
                    {
                        return 60;
                    }
                    case 19:
                    {
                        return 61;
                    }
                    case 24:
                    {
                        return 62;
                    }
                    case 25:
                    {
                        return 63;
                    }
                    case 29:
                    {
                        return 64;
                    }
                    case 37:
                    case 38:
                    {
                        return 66;
                    }
                    case 39:
                    case 41:
                    {
                        return 67;
                    }
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 69;
                    }
                    case 2:
                    {
                        return 272;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 272:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 18:
                    {
                        return 60;
                    }
                    case 24:
                    {
                        return 62;
                    }
                    case 25:
                    {
                        return 63;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 67;
                    }
                    case 2:
                    {
                        return 74;
                    }
                    case 29:
                    {
                        return 143;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 20:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                        return 61;
                    }
                    case 37:
                    case 38:
                    {
                        return 66;
                    }
                    case 2:
                    {
                        return 273;
                    }
                    case 15:
                    case 16:
                    {
                        return 274;
                    }
                    case 17:
                    case 18:
                    {
                        return 275;
                    }
                    case 24:
                    {
                        return 276;
                    }
                    case 25:
                    {
                        return 277;
                    }
                    case 29:
                    {
                        return 278;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 279;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 279:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                        return 61;
                    }
                    case 37:
                    case 38:
                    {
                        return 66;
                    }
                    case 15:
                    case 16:
                    {
                        return 274;
                    }
                    case 17:
                    case 18:
                    {
                        return 275;
                    }
                    case 24:
                    {
                        return 276;
                    }
                    case 25:
                    {
                        return 277;
                    }
                    case 29:
                    {
                        return 278;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 279;
                    }
                    case 2:
                    {
                        return 280;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 280:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                        return 61;
                    }
                    case 37:
                    case 38:
                    {
                        return 66;
                    }
                    case 15:
                    case 16:
                    {
                        return 274;
                    }
                    case 17:
                    case 18:
                    {
                        return 275;
                    }
                    case 24:
                    {
                        return 276;
                    }
                    case 25:
                    {
                        return 277;
                    }
                    case 29:
                    {
                        return 278;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 279;
                    }
                    case 2:
                    {
                        return 281;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 281:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                        return 61;
                    }
                    case 37:
                    case 38:
                    {
                        return 66;
                    }
                    case 15:
                    case 16:
                    {
                        return 274;
                    }
                    case 17:
                    case 18:
                    {
                        return 275;
                    }
                    case 24:
                    {
                        return 276;
                    }
                    case 25:
                    {
                        return 277;
                    }
                    case 29:
                    {
                        return 278;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 279;
                    }
                    case 2:
                    {
                        return 282;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 282:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 16:
                    {
                        return 274;
                    }
                    case 17:
                    case 18:
                    {
                        return 275;
                    }
                    case 24:
                    {
                        return 276;
                    }
                    case 25:
                    {
                        return 277;
                    }
                    case 29:
                    {
                        return 278;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 279;
                    }
                    case 2:
                    {
                        return 283;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 283:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 18:
                    {
                        return 275;
                    }
                    case 24:
                    {
                        return 276;
                    }
                    case 25:
                    {
                        return 277;
                    }
                    case 2:
                    {
                        return 284;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 284:
            {
                switch (cls)
                {
                    case 17:
                    case 18:
                    {
                        return 275;
                    }
                    case 2:
                    {
                        return 285;
                    }
                    case 24:
                    {
                        return 286;
                    }
                    case 25:
                    {
                        return 287;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 287:
            {
                switch (cls)
                {
                    case 25:
                    {
                        return 288;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 288:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 289;
                    }
                    case 17:
                    case 18:
                    {
                        return 290;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 290:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 291;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 291:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 292;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 292:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 293;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 293:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 85;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 289:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    case 17:
                    case 18:
                    {
                        return 290;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 286:
            {
                switch (cls)
                {
                    case 24:
                    {
                        return 294;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 294:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 289;
                    }
                    case 17:
                    case 18:
                    {
                        return 290;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 285:
            {
                switch (cls)
                {
                    case 17:
                    case 18:
                    {
                        return 275;
                    }
                    case 24:
                    {
                        return 286;
                    }
                    case 25:
                    {
                        return 287;
                    }
                    case 2:
                    {
                        return 295;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 295:
            {
                switch (cls)
                {
                    case 17:
                    case 18:
                    {
                        return 296;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 296:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 297;
                    }
                    case 24:
                    {
                        return 298;
                    }
                    case 25:
                    {
                        return 299;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 299:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 300;
                    }
                    case 25:
                    {
                        return 301;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 301:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 302;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 302:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 300;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 300:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 303;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 303:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 291;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 298:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 300;
                    }
                    case 24:
                    {
                        return 304;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 304:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 302;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 297:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 300;
                    }
                    case 24:
                    {
                        return 305;
                    }
                    case 25:
                    {
                        return 306;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 306:
            {
                switch (cls)
                {
                    case 25:
                    {
                        return 301;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 305:
            {
                switch (cls)
                {
                    case 24:
                    {
                        return 304;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 278:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                        return 61;
                    }
                    case 37:
                    case 38:
                    {
                        return 66;
                    }
                    case 15:
                    case 16:
                    {
                        return 274;
                    }
                    case 17:
                    case 18:
                    {
                        return 275;
                    }
                    case 24:
                    {
                        return 276;
                    }
                    case 25:
                    {
                        return 277;
                    }
                    case 29:
                    {
                        return 278;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 279;
                    }
                    case 2:
                    {
                        return 280;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 277:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    {
                        return 288;
                    }
                    case 2:
                    case 17:
                    case 18:
                    {
                        return 307;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 307:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 292;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 276:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 24:
                    {
                        return 294;
                    }
                    case 2:
                    case 17:
                    case 18:
                    {
                        return 307;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 275:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 297;
                    }
                    case 24:
                    {
                        return 298;
                    }
                    case 25:
                    {
                        return 299;
                    }
                    case 15:
                    case 16:
                    {
                        return 308;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 308:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 303;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 274:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    case 17:
                    case 18:
                    {
                        return 309;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 309:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 293;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 273:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                        return 61;
                    }
                    case 37:
                    case 38:
                    {
                        return 66;
                    }
                    case 15:
                    case 16:
                    {
                        return 274;
                    }
                    case 17:
                    case 18:
                    {
                        return 275;
                    }
                    case 24:
                    {
                        return 276;
                    }
                    case 25:
                    {
                        return 277;
                    }
                    case 29:
                    {
                        return 278;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 279;
                    }
                    case 2:
                    {
                        return 310;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 310:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                        return 61;
                    }
                    case 37:
                    case 38:
                    {
                        return 66;
                    }
                    case 15:
                    case 16:
                    {
                        return 274;
                    }
                    case 17:
                    case 18:
                    {
                        return 275;
                    }
                    case 24:
                    {
                        return 276;
                    }
                    case 25:
                    {
                        return 277;
                    }
                    case 29:
                    {
                        return 278;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 279;
                    }
                    case 2:
                    {
                        return 311;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 311:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 67;
                    }
                    case 29:
                    {
                        return 143;
                    }
                    case 17:
                    case 18:
                    {
                        return 275;
                    }
                    case 24:
                    {
                        return 276;
                    }
                    case 25:
                    {
                        return 277;
                    }
                    case 2:
                    {
                        return 284;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 19:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(25, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                switch (cls)
                {
                    case 2:
                    {
                        return 312;
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
                    case 20:
                    case 21:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 28:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 40:
                    case 42:
                    case 43:
                    case 44:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 313;
                    }
                    case 19:
                    {
                        return 314;
                    }
                    case 27:
                    {
                        return 315;
                    }
                    case 29:
                    {
                        return 316;
                    }
                    case 37:
                    case 38:
                    {
                        return 317;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 318;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 318:
            {
                switch (cls)
                {
                    case 2:
                    {
                        return 312;
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
                    case 20:
                    case 21:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 28:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 40:
                    case 42:
                    case 43:
                    case 44:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 313;
                    }
                    case 19:
                    {
                        return 314;
                    }
                    case 27:
                    {
                        return 315;
                    }
                    case 29:
                    {
                        return 316;
                    }
                    case 37:
                    case 38:
                    {
                        return 317;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 318;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 317:
            {
                switch (cls)
                {
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
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 28:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 40:
                    case 42:
                    case 43:
                    case 44:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 313;
                    }
                    case 27:
                    {
                        return 315;
                    }
                    case 2:
                    {
                        return 319;
                    }
                    case 20:
                    {
                        return 320;
                    }
                    case 21:
                    {
                        return 321;
                    }
                    case 29:
                    {
                        return 322;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 323;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 323:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 26:
                    case 28:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 42:
                    case 44:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 313;
                    }
                    case 27:
                    {
                        return 315;
                    }
                    case 29:
                    {
                        return 322;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 323;
                    }
                    case 2:
                    {
                        return 324;
                    }
                    case 24:
                    case 25:
                    {
                        return 325;
                    }
                    case 40:
                    case 43:
                    {
                        return 326;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 326:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 28:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 313;
                    }
                    case 27:
                    {
                        return 315;
                    }
                    case 2:
                    {
                        return 327;
                    }
                    case 29:
                    {
                        return 328;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 328:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(9, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 327:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 28:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 313;
                    }
                    case 27:
                    {
                        return 315;
                    }
                    case 29:
                    {
                        return 328;
                    }
                    case 2:
                    {
                        return 329;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 329:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
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
                    case 28:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 313;
                    }
                    case 27:
                    {
                        return 315;
                    }
                    case 29:
                    {
                        return 328;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 325:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 28:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 313;
                    }
                    case 27:
                    {
                        return 315;
                    }
                    case 2:
                    {
                        return 327;
                    }
                    case 29:
                    {
                        return 328;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 324:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 26:
                    case 28:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 42:
                    case 44:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 313;
                    }
                    case 27:
                    {
                        return 315;
                    }
                    case 29:
                    {
                        return 322;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 323;
                    }
                    case 24:
                    case 25:
                    {
                        return 325;
                    }
                    case 40:
                    case 43:
                    {
                        return 326;
                    }
                    case 2:
                    {
                        return 330;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 330:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 26:
                    case 28:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 42:
                    case 44:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 313;
                    }
                    case 27:
                    {
                        return 315;
                    }
                    case 29:
                    {
                        return 322;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 323;
                    }
                    case 24:
                    case 25:
                    {
                        return 325;
                    }
                    case 40:
                    case 43:
                    {
                        return 326;
                    }
                    case 2:
                    {
                        return 331;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 331:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 26:
                    case 28:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 42:
                    case 44:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 313;
                    }
                    case 27:
                    {
                        return 315;
                    }
                    case 29:
                    {
                        return 322;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 323;
                    }
                    case 24:
                    case 25:
                    {
                        return 325;
                    }
                    case 40:
                    case 43:
                    {
                        return 326;
                    }
                    case 2:
                    {
                        return 332;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 332:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 26:
                    case 28:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 41:
                    case 42:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 313;
                    }
                    case 27:
                    {
                        return 315;
                    }
                    case 24:
                    case 25:
                    {
                        return 325;
                    }
                    case 40:
                    case 43:
                    {
                        return 326;
                    }
                    case 29:
                    {
                        return 328;
                    }
                    case 2:
                    {
                        return 329;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 322:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 29:
                    {
                        return 149;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 150;
                    }
                    case 2:
                    {
                        return 151;
                    }
                    case 24:
                    case 25:
                    {
                        return 152;
                    }
                    case 40:
                    case 43:
                    {
                        return 153;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 321:
            {
                switch (cls)
                {
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
                    case 28:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 40:
                    case 42:
                    case 43:
                    case 44:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 313;
                    }
                    case 27:
                    {
                        return 315;
                    }
                    case 29:
                    {
                        return 322;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 323;
                    }
                    case 2:
                    {
                        return 333;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 333:
            {
                switch (cls)
                {
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
                    case 28:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 40:
                    case 42:
                    case 43:
                    case 44:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 313;
                    }
                    case 27:
                    {
                        return 315;
                    }
                    case 29:
                    {
                        return 322;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 323;
                    }
                    case 2:
                    {
                        return 334;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 334:
            {
                switch (cls)
                {
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
                    case 28:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 40:
                    case 42:
                    case 43:
                    case 44:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 313;
                    }
                    case 27:
                    {
                        return 315;
                    }
                    case 29:
                    {
                        return 322;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 323;
                    }
                    case 2:
                    {
                        return 335;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 335:
            {
                switch (cls)
                {
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
                    case 28:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 40:
                    case 42:
                    case 43:
                    case 44:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 313;
                    }
                    case 27:
                    {
                        return 315;
                    }
                    case 29:
                    {
                        return 322;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 323;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 320:
            {
                switch (cls)
                {
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
                    case 28:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 40:
                    case 42:
                    case 43:
                    case 44:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 313;
                    }
                    case 27:
                    {
                        return 315;
                    }
                    case 29:
                    {
                        return 322;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 323;
                    }
                    case 2:
                    {
                        return 333;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 319:
            {
                switch (cls)
                {
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
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 28:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 40:
                    case 42:
                    case 43:
                    case 44:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 313;
                    }
                    case 27:
                    {
                        return 315;
                    }
                    case 20:
                    {
                        return 320;
                    }
                    case 21:
                    {
                        return 321;
                    }
                    case 29:
                    {
                        return 322;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 323;
                    }
                    case 2:
                    {
                        return 334;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 316:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(9, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                        return 61;
                    }
                    case 37:
                    case 38:
                    {
                        return 66;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 67;
                    }
                    case 2:
                    {
                        return 142;
                    }
                    case 29:
                    {
                        return 143;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 315:
            {
                switch (cls)
                {
                    case 13:
                    {
                        return 336;
                    }
                    case 17:
                    {
                        return 337;
                    }
                    case 18:
                    {
                        return 338;
                    }
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 42:
                    case 43:
                    case 44:
                    {
                        return 339;
                    }
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 340;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 340:
            {
                switch (cls)
                {
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
                    case 28:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 313;
                    }
                    case 27:
                    {
                        return 315;
                    }
                    case 29:
                    {
                        return 328;
                    }
                    case 2:
                    {
                        return 341;
                    }
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 342;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 342:
            {
                switch (cls)
                {
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
                    case 28:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 313;
                    }
                    case 27:
                    {
                        return 315;
                    }
                    case 29:
                    {
                        return 328;
                    }
                    case 2:
                    {
                        return 341;
                    }
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 343;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 343:
            {
                switch (cls)
                {
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
                    case 28:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 313;
                    }
                    case 27:
                    {
                        return 315;
                    }
                    case 29:
                    {
                        return 328;
                    }
                    case 2:
                    {
                        return 344;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 344:
            {
                switch (cls)
                {
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
                    case 28:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 313;
                    }
                    case 27:
                    {
                        return 315;
                    }
                    case 29:
                    {
                        return 328;
                    }
                    case 2:
                    {
                        return 345;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 345:
            {
                switch (cls)
                {
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
                    case 28:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 313;
                    }
                    case 27:
                    {
                        return 315;
                    }
                    case 29:
                    {
                        return 328;
                    }
                    case 2:
                    {
                        return 346;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 346:
            {
                switch (cls)
                {
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
                    case 28:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 313;
                    }
                    case 27:
                    {
                        return 315;
                    }
                    case 29:
                    {
                        return 328;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 341:
            {
                switch (cls)
                {
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
                    case 28:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 313;
                    }
                    case 27:
                    {
                        return 315;
                    }
                    case 29:
                    {
                        return 328;
                    }
                    case 2:
                    {
                        return 344;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 339:
            {
                switch (cls)
                {
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
                    case 28:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 313;
                    }
                    case 27:
                    {
                        return 315;
                    }
                    case 29:
                    {
                        return 328;
                    }
                    case 2:
                    {
                        return 345;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 338:
            {
                switch (cls)
                {
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 347;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 347:
            {
                switch (cls)
                {
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 348;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 348:
            {
                switch (cls)
                {
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 349;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 349:
            {
                switch (cls)
                {
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 350;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 350:
            {
                switch (cls)
                {
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 351;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 351:
            {
                switch (cls)
                {
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 352;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 352:
            {
                switch (cls)
                {
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 353;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 353:
            {
                switch (cls)
                {
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 354;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 354:
            {
                switch (cls)
                {
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
                    case 28:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 313;
                    }
                    case 27:
                    {
                        return 315;
                    }
                    case 29:
                    {
                        return 328;
                    }
                    case 2:
                    {
                        return 355;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 355:
            {
                switch (cls)
                {
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
                    case 28:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 313;
                    }
                    case 27:
                    {
                        return 315;
                    }
                    case 29:
                    {
                        return 328;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 337:
            {
                switch (cls)
                {
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 356;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 356:
            {
                switch (cls)
                {
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 357;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 357:
            {
                switch (cls)
                {
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 358;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 358:
            {
                switch (cls)
                {
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 359;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 359:
            {
                switch (cls)
                {
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
                    case 28:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 313;
                    }
                    case 27:
                    {
                        return 315;
                    }
                    case 29:
                    {
                        return 328;
                    }
                    case 2:
                    {
                        return 355;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 336:
            {
                switch (cls)
                {
                    case 2:
                    {
                        return 360;
                    }
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 361;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 361:
            {
                switch (cls)
                {
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
                    case 28:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 313;
                    }
                    case 27:
                    {
                        return 315;
                    }
                    case 29:
                    {
                        return 328;
                    }
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 361;
                    }
                    case 2:
                    {
                        return 362;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 362:
            {
                switch (cls)
                {
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
                    case 28:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 313;
                    }
                    case 27:
                    {
                        return 315;
                    }
                    case 29:
                    {
                        return 328;
                    }
                    case 2:
                    {
                        return 346;
                    }
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 361;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 360:
            {
                switch (cls)
                {
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 361;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 314:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 26:
                    case 28:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 42:
                    case 44:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 313;
                    }
                    case 27:
                    {
                        return 315;
                    }
                    case 24:
                    case 25:
                    {
                        return 325;
                    }
                    case 40:
                    case 43:
                    {
                        return 326;
                    }
                    case 2:
                    {
                        return 363;
                    }
                    case 29:
                    {
                        return 364;
                    }
                    case 37:
                    case 38:
                    {
                        return 365;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 366;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 366:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 26:
                    case 28:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 42:
                    case 44:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 313;
                    }
                    case 27:
                    {
                        return 315;
                    }
                    case 24:
                    case 25:
                    {
                        return 325;
                    }
                    case 40:
                    case 43:
                    {
                        return 326;
                    }
                    case 29:
                    {
                        return 364;
                    }
                    case 37:
                    case 38:
                    {
                        return 365;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 366;
                    }
                    case 2:
                    {
                        return 367;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 367:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 26:
                    case 28:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 42:
                    case 44:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 313;
                    }
                    case 27:
                    {
                        return 315;
                    }
                    case 24:
                    case 25:
                    {
                        return 325;
                    }
                    case 40:
                    case 43:
                    {
                        return 326;
                    }
                    case 29:
                    {
                        return 364;
                    }
                    case 37:
                    case 38:
                    {
                        return 365;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 366;
                    }
                    case 2:
                    {
                        return 368;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 368:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 26:
                    case 28:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 42:
                    case 44:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 313;
                    }
                    case 27:
                    {
                        return 315;
                    }
                    case 24:
                    case 25:
                    {
                        return 325;
                    }
                    case 40:
                    case 43:
                    {
                        return 326;
                    }
                    case 29:
                    {
                        return 364;
                    }
                    case 37:
                    case 38:
                    {
                        return 365;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 366;
                    }
                    case 2:
                    {
                        return 369;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 369:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 26:
                    case 28:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 42:
                    case 44:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 313;
                    }
                    case 27:
                    {
                        return 315;
                    }
                    case 24:
                    case 25:
                    {
                        return 325;
                    }
                    case 40:
                    case 43:
                    {
                        return 326;
                    }
                    case 29:
                    {
                        return 364;
                    }
                    case 37:
                    case 38:
                    {
                        return 365;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 366;
                    }
                    case 2:
                    {
                        return 370;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 370:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 26:
                    case 28:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 41:
                    case 42:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 313;
                    }
                    case 27:
                    {
                        return 315;
                    }
                    case 24:
                    case 25:
                    {
                        return 325;
                    }
                    case 40:
                    case 43:
                    {
                        return 326;
                    }
                    case 29:
                    {
                        return 328;
                    }
                    case 2:
                    {
                        return 371;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 371:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 26:
                    case 28:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 41:
                    case 42:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 313;
                    }
                    case 27:
                    {
                        return 315;
                    }
                    case 24:
                    case 25:
                    {
                        return 325;
                    }
                    case 40:
                    case 43:
                    {
                        return 326;
                    }
                    case 29:
                    {
                        return 328;
                    }
                    case 2:
                    {
                        return 332;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 365:
            {
                switch (cls)
                {
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
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 28:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 40:
                    case 42:
                    case 43:
                    case 44:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 313;
                    }
                    case 27:
                    {
                        return 315;
                    }
                    case 2:
                    {
                        return 372;
                    }
                    case 20:
                    {
                        return 373;
                    }
                    case 21:
                    {
                        return 374;
                    }
                    case 29:
                    {
                        return 375;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 376;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 376:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 26:
                    case 28:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 42:
                    case 44:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 313;
                    }
                    case 27:
                    {
                        return 315;
                    }
                    case 24:
                    case 25:
                    {
                        return 325;
                    }
                    case 40:
                    case 43:
                    {
                        return 326;
                    }
                    case 29:
                    {
                        return 375;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 376;
                    }
                    case 2:
                    {
                        return 377;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 377:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 26:
                    case 28:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 42:
                    case 44:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 313;
                    }
                    case 27:
                    {
                        return 315;
                    }
                    case 24:
                    case 25:
                    {
                        return 325;
                    }
                    case 40:
                    case 43:
                    {
                        return 326;
                    }
                    case 29:
                    {
                        return 375;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 376;
                    }
                    case 2:
                    {
                        return 378;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 378:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 26:
                    case 28:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 42:
                    case 44:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 313;
                    }
                    case 27:
                    {
                        return 315;
                    }
                    case 24:
                    case 25:
                    {
                        return 325;
                    }
                    case 40:
                    case 43:
                    {
                        return 326;
                    }
                    case 29:
                    {
                        return 375;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 376;
                    }
                    case 2:
                    {
                        return 379;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 379:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 26:
                    case 28:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 42:
                    case 44:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 313;
                    }
                    case 27:
                    {
                        return 315;
                    }
                    case 24:
                    case 25:
                    {
                        return 325;
                    }
                    case 40:
                    case 43:
                    {
                        return 326;
                    }
                    case 2:
                    {
                        return 332;
                    }
                    case 29:
                    {
                        return 375;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 376;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 375:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 24:
                    case 25:
                    {
                        return 152;
                    }
                    case 40:
                    case 43:
                    {
                        return 153;
                    }
                    case 29:
                    {
                        return 175;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 176;
                    }
                    case 2:
                    {
                        return 177;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 374:
            {
                switch (cls)
                {
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
                    case 28:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 40:
                    case 42:
                    case 43:
                    case 44:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 313;
                    }
                    case 27:
                    {
                        return 315;
                    }
                    case 29:
                    {
                        return 375;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 376;
                    }
                    case 2:
                    {
                        return 380;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 380:
            {
                switch (cls)
                {
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
                    case 28:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 40:
                    case 42:
                    case 43:
                    case 44:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 313;
                    }
                    case 27:
                    {
                        return 315;
                    }
                    case 29:
                    {
                        return 375;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 376;
                    }
                    case 2:
                    {
                        return 381;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 381:
            {
                switch (cls)
                {
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
                    case 28:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 40:
                    case 42:
                    case 43:
                    case 44:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 313;
                    }
                    case 27:
                    {
                        return 315;
                    }
                    case 29:
                    {
                        return 375;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 376;
                    }
                    case 2:
                    {
                        return 382;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 382:
            {
                switch (cls)
                {
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
                    case 28:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 40:
                    case 42:
                    case 43:
                    case 44:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 313;
                    }
                    case 27:
                    {
                        return 315;
                    }
                    case 29:
                    {
                        return 375;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 376;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 373:
            {
                switch (cls)
                {
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
                    case 28:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 40:
                    case 42:
                    case 43:
                    case 44:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 313;
                    }
                    case 27:
                    {
                        return 315;
                    }
                    case 29:
                    {
                        return 375;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 376;
                    }
                    case 2:
                    {
                        return 380;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 372:
            {
                switch (cls)
                {
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
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 28:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 40:
                    case 42:
                    case 43:
                    case 44:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 313;
                    }
                    case 27:
                    {
                        return 315;
                    }
                    case 20:
                    {
                        return 373;
                    }
                    case 21:
                    {
                        return 374;
                    }
                    case 29:
                    {
                        return 375;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 376;
                    }
                    case 2:
                    {
                        return 381;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 364:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 24:
                    case 25:
                    {
                        return 152;
                    }
                    case 40:
                    case 43:
                    {
                        return 153;
                    }
                    case 29:
                    {
                        return 164;
                    }
                    case 37:
                    case 38:
                    {
                        return 165;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 166;
                    }
                    case 2:
                    {
                        return 167;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 363:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 26:
                    case 28:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 42:
                    case 44:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 313;
                    }
                    case 27:
                    {
                        return 315;
                    }
                    case 24:
                    case 25:
                    {
                        return 325;
                    }
                    case 40:
                    case 43:
                    {
                        return 326;
                    }
                    case 29:
                    {
                        return 364;
                    }
                    case 37:
                    case 38:
                    {
                        return 365;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 366;
                    }
                    case 2:
                    {
                        return 383;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 383:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(8, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 26:
                    case 28:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 42:
                    case 44:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 313;
                    }
                    case 27:
                    {
                        return 315;
                    }
                    case 24:
                    case 25:
                    {
                        return 325;
                    }
                    case 40:
                    case 43:
                    {
                        return 326;
                    }
                    case 29:
                    {
                        return 364;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 366;
                    }
                    case 2:
                    {
                        return 371;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 313:
            {
                switch (cls)
                {
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
                    case 28:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 313;
                    }
                    case 27:
                    {
                        return 315;
                    }
                    case 29:
                    {
                        return 328;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 312:
            {
                switch (cls)
                {
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
                    case 20:
                    case 21:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 28:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 40:
                    case 42:
                    case 43:
                    case 44:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 313;
                    }
                    case 19:
                    {
                        return 314;
                    }
                    case 27:
                    {
                        return 315;
                    }
                    case 29:
                    {
                        return 316;
                    }
                    case 37:
                    case 38:
                    {
                        return 317;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 318;
                    }
                    case 2:
                    {
                        return 384;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 384:
            {
                switch (cls)
                {
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
                    case 20:
                    case 21:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 28:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 40:
                    case 42:
                    case 43:
                    case 44:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 313;
                    }
                    case 19:
                    {
                        return 314;
                    }
                    case 27:
                    {
                        return 315;
                    }
                    case 29:
                    {
                        return 316;
                    }
                    case 37:
                    case 38:
                    {
                        return 317;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 318;
                    }
                    case 2:
                    {
                        return 385;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 385:
            {
                switch (cls)
                {
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
                    case 28:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 40:
                    case 42:
                    case 43:
                    case 44:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 313;
                    }
                    case 27:
                    {
                        return 315;
                    }
                    case 29:
                    {
                        return 316;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 318;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 17:
            {
                switch (cls)
                {
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
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 386;
                    }
                    case 27:
                    {
                        return 387;
                    }
                    case 28:
                    {
                        return 388;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 388:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(11, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 387:
            {
                switch (cls)
                {
                    case 13:
                    {
                        return 389;
                    }
                    case 17:
                    {
                        return 390;
                    }
                    case 18:
                    {
                        return 391;
                    }
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 42:
                    case 43:
                    case 44:
                    {
                        return 392;
                    }
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 393;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 393:
            {
                switch (cls)
                {
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
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 386;
                    }
                    case 27:
                    {
                        return 387;
                    }
                    case 28:
                    {
                        return 388;
                    }
                    case 2:
                    {
                        return 394;
                    }
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 395;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 395:
            {
                switch (cls)
                {
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
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 386;
                    }
                    case 27:
                    {
                        return 387;
                    }
                    case 28:
                    {
                        return 388;
                    }
                    case 2:
                    {
                        return 394;
                    }
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 396;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 396:
            {
                switch (cls)
                {
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
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 386;
                    }
                    case 27:
                    {
                        return 387;
                    }
                    case 28:
                    {
                        return 388;
                    }
                    case 2:
                    {
                        return 397;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 397:
            {
                switch (cls)
                {
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
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 386;
                    }
                    case 27:
                    {
                        return 387;
                    }
                    case 28:
                    {
                        return 388;
                    }
                    case 2:
                    {
                        return 398;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 398:
            {
                switch (cls)
                {
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
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 386;
                    }
                    case 27:
                    {
                        return 387;
                    }
                    case 28:
                    {
                        return 388;
                    }
                    case 2:
                    {
                        return 399;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 399:
            {
                switch (cls)
                {
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
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 386;
                    }
                    case 27:
                    {
                        return 387;
                    }
                    case 28:
                    {
                        return 388;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 394:
            {
                switch (cls)
                {
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
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 386;
                    }
                    case 27:
                    {
                        return 387;
                    }
                    case 28:
                    {
                        return 388;
                    }
                    case 2:
                    {
                        return 397;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 392:
            {
                switch (cls)
                {
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
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 386;
                    }
                    case 27:
                    {
                        return 387;
                    }
                    case 28:
                    {
                        return 388;
                    }
                    case 2:
                    {
                        return 398;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 391:
            {
                switch (cls)
                {
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 400;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 400:
            {
                switch (cls)
                {
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 401;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 401:
            {
                switch (cls)
                {
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 402;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 402:
            {
                switch (cls)
                {
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 403;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 403:
            {
                switch (cls)
                {
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 404;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 404:
            {
                switch (cls)
                {
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 405;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 405:
            {
                switch (cls)
                {
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 406;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 406:
            {
                switch (cls)
                {
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 407;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 407:
            {
                switch (cls)
                {
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
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 386;
                    }
                    case 27:
                    {
                        return 387;
                    }
                    case 28:
                    {
                        return 388;
                    }
                    case 2:
                    {
                        return 408;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 408:
            {
                switch (cls)
                {
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
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 386;
                    }
                    case 27:
                    {
                        return 387;
                    }
                    case 28:
                    {
                        return 388;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 390:
            {
                switch (cls)
                {
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 409;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 409:
            {
                switch (cls)
                {
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 410;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 410:
            {
                switch (cls)
                {
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 411;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 411:
            {
                switch (cls)
                {
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 412;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 412:
            {
                switch (cls)
                {
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
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 386;
                    }
                    case 27:
                    {
                        return 387;
                    }
                    case 28:
                    {
                        return 388;
                    }
                    case 2:
                    {
                        return 408;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 389:
            {
                switch (cls)
                {
                    case 2:
                    {
                        return 413;
                    }
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 414;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 414:
            {
                switch (cls)
                {
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
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 386;
                    }
                    case 27:
                    {
                        return 387;
                    }
                    case 28:
                    {
                        return 388;
                    }
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 414;
                    }
                    case 2:
                    {
                        return 415;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 415:
            {
                switch (cls)
                {
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
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 386;
                    }
                    case 27:
                    {
                        return 387;
                    }
                    case 28:
                    {
                        return 388;
                    }
                    case 2:
                    {
                        return 399;
                    }
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 414;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 413:
            {
                switch (cls)
                {
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 414;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 386:
            {
                switch (cls)
                {
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
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 386;
                    }
                    case 27:
                    {
                        return 387;
                    }
                    case 28:
                    {
                        return 388;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 16:
            {
                switch (cls)
                {
                    case 17:
                    {
                        return 416;
                    }
                    case 18:
                    {
                        return 417;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 417:
            {
                switch (cls)
                {
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 418;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 418:
            {
                switch (cls)
                {
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 419;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 419:
            {
                switch (cls)
                {
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 420;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 420:
            {
                switch (cls)
                {
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 421;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 421:
            {
                switch (cls)
                {
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 422;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 422:
            {
                switch (cls)
                {
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 423;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 423:
            {
                switch (cls)
                {
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 424;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 424:
            {
                switch (cls)
                {
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 425;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 425:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(6, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 426;
                    }
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 13:
                    case 14:
                    case 15:
                    case 16:
                    case 17:
                    case 18:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 427;
                    }
                    case 27:
                    {
                        return 428;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 428:
            {
                switch (cls)
                {
                    case 17:
                    {
                        return 429;
                    }
                    case 18:
                    {
                        return 430;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 430:
            {
                switch (cls)
                {
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 431;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 431:
            {
                switch (cls)
                {
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 432;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 432:
            {
                switch (cls)
                {
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 433;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 433:
            {
                switch (cls)
                {
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 434;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 434:
            {
                switch (cls)
                {
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 435;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 435:
            {
                switch (cls)
                {
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 436;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 436:
            {
                switch (cls)
                {
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 437;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 437:
            {
                switch (cls)
                {
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 438;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 438:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(6, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 6:
                    case 13:
                    case 14:
                    case 15:
                    case 16:
                    case 17:
                    case 18:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 427;
                    }
                    case 27:
                    {
                        return 428;
                    }
                    case 2:
                    {
                        return 439;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 439:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(6, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 6:
                    case 13:
                    case 14:
                    case 15:
                    case 16:
                    case 17:
                    case 18:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 427;
                    }
                    case 27:
                    {
                        return 428;
                    }
                    case 2:
                    {
                        return 440;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 440:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(6, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 6:
                    case 13:
                    case 14:
                    case 15:
                    case 16:
                    case 17:
                    case 18:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 427;
                    }
                    case 27:
                    {
                        return 428;
                    }
                    case 2:
                    {
                        return 441;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 441:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(6, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 6:
                    case 13:
                    case 14:
                    case 15:
                    case 16:
                    case 17:
                    case 18:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 427;
                    }
                    case 27:
                    {
                        return 428;
                    }
                    case 2:
                    {
                        return 442;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 442:
            {
                switch (cls)
                {
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 13:
                    case 14:
                    case 15:
                    case 16:
                    case 17:
                    case 18:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 427;
                    }
                    case 27:
                    {
                        return 428;
                    }
                    case 2:
                    {
                        return 443;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 443:
            {
                switch (cls)
                {
                    case 27:
                    {
                        return 428;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 429:
            {
                switch (cls)
                {
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 444;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 444:
            {
                switch (cls)
                {
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 445;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 445:
            {
                switch (cls)
                {
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 446;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 446:
            {
                switch (cls)
                {
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 447;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 447:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(6, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 6:
                    case 13:
                    case 14:
                    case 15:
                    case 16:
                    case 17:
                    case 18:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 427;
                    }
                    case 27:
                    {
                        return 428;
                    }
                    case 2:
                    {
                        return 439;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 427:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(6, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 6:
                    case 13:
                    case 14:
                    case 15:
                    case 16:
                    case 17:
                    case 18:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 427;
                    }
                    case 27:
                    {
                        return 428;
                    }
                    case 2:
                    {
                        return 440;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 426:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(6, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 6:
                    case 13:
                    case 14:
                    case 15:
                    case 16:
                    case 17:
                    case 18:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 427;
                    }
                    case 27:
                    {
                        return 428;
                    }
                    case 2:
                    {
                        return 448;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 448:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(6, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 6:
                    case 13:
                    case 14:
                    case 15:
                    case 16:
                    case 17:
                    case 18:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 427;
                    }
                    case 27:
                    {
                        return 428;
                    }
                    case 2:
                    {
                        return 441;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 416:
            {
                switch (cls)
                {
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 449;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 449:
            {
                switch (cls)
                {
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 450;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 450:
            {
                switch (cls)
                {
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 451;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 451:
            {
                switch (cls)
                {
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 452;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 452:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(6, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 426;
                    }
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 13:
                    case 14:
                    case 15:
                    case 16:
                    case 17:
                    case 18:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 427;
                    }
                    case 27:
                    {
                        return 428;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 15:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(6, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 6:
                    case 13:
                    case 14:
                    case 15:
                    case 16:
                    case 17:
                    case 18:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 427;
                    }
                    case 27:
                    {
                        return 428;
                    }
                    case 2:
                    {
                        return 448;
                    }
                    case 28:
                    {
                        return 453;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 453:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(10, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(6, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 28:
                    {
                        return 17;
                    }
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 13:
                    case 14:
                    case 15:
                    case 16:
                    case 17:
                    case 18:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 427;
                    }
                    case 27:
                    {
                        return 428;
                    }
                    case 2:
                    {
                        return 454;
                    }
                    case 26:
                    {
                        return 455;
                    }
                    case 29:
                    {
                        return 456;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 456:
            {
                switch (cls)
                {
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
                    case 28:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 313;
                    }
                    case 27:
                    {
                        return 315;
                    }
                    case 29:
                    {
                        return 328;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 455:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(6, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 6:
                    case 13:
                    case 14:
                    case 15:
                    case 16:
                    case 17:
                    case 18:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 427;
                    }
                    case 27:
                    {
                        return 428;
                    }
                    case 2:
                    {
                        return 440;
                    }
                    case 28:
                    {
                        return 453;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 454:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(6, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 28:
                    {
                        return 17;
                    }
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 13:
                    case 14:
                    case 15:
                    case 16:
                    case 17:
                    case 18:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 427;
                    }
                    case 27:
                    {
                        return 428;
                    }
                    case 2:
                    {
                        return 441;
                    }
                    case 26:
                    {
                        return 455;
                    }
                    case 29:
                    {
                        return 456;
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
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(42, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 21:
                    {
                        return 457;
                    }
                    case 50:
                    {
                        return 458;
                    }
                    case 52:
                    {
                        return 459;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 459:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(57, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 12:
                    {
                        return 460;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 460:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(47, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 458:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(19, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 457:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(51, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(41, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 20:
                    {
                        return 461;
                    }
                    case 50:
                    {
                        return 462;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 462:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(18, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 461:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(50, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(56, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 29:
                    {
                        return 164;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 166;
                    }
                    case 2:
                    {
                        return 463;
                    }
                    case 12:
                    {
                        return 464;
                    }
                    case 19:
                    {
                        return 465;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 465:
            {
                switch (cls)
                {
                    case 19:
                    {
                        return 466;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 466:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(59, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 464:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(46, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 463:
            {
                switch (cls)
                {
                    case 29:
                    {
                        return 164;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 166;
                    }
                    case 2:
                    {
                        return 467;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 467:
            {
                switch (cls)
                {
                    case 29:
                    {
                        return 164;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 166;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 10:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(6, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 28:
                    {
                        return 17;
                    }
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 13:
                    case 14:
                    case 15:
                    case 16:
                    case 17:
                    case 18:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 427;
                    }
                    case 27:
                    {
                        return 428;
                    }
                    case 26:
                    {
                        return 455;
                    }
                    case 29:
                    {
                        return 456;
                    }
                    case 2:
                    {
                        return 468;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 468:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(6, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 28:
                    {
                        return 17;
                    }
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 13:
                    case 14:
                    case 15:
                    case 16:
                    case 17:
                    case 18:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 427;
                    }
                    case 27:
                    {
                        return 428;
                    }
                    case 26:
                    {
                        return 455;
                    }
                    case 29:
                    {
                        return 456;
                    }
                    case 2:
                    {
                        return 469;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 469:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(6, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 28:
                    {
                        return 17;
                    }
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 13:
                    case 14:
                    case 15:
                    case 16:
                    case 17:
                    case 18:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 427;
                    }
                    case 27:
                    {
                        return 428;
                    }
                    case 2:
                    {
                        return 442;
                    }
                    case 26:
                    {
                        return 455;
                    }
                    case 29:
                    {
                        return 456;
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
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(6, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 28:
                    {
                        return 17;
                    }
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 13:
                    case 14:
                    case 15:
                    case 16:
                    case 17:
                    case 18:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 427;
                    }
                    case 27:
                    {
                        return 428;
                    }
                    case 26:
                    {
                        return 455;
                    }
                    case 29:
                    {
                        return 456;
                    }
                    case 2:
                    {
                        return 470;
                    }
                    case 41:
                    {
                        return 471;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 471:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(6, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 28:
                    {
                        return 17;
                    }
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 13:
                    case 14:
                    case 15:
                    case 16:
                    case 17:
                    case 18:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 427;
                    }
                    case 27:
                    {
                        return 428;
                    }
                    case 26:
                    {
                        return 455;
                    }
                    case 29:
                    {
                        return 456;
                    }
                    case 2:
                    {
                        return 472;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 472:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(6, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 28:
                    {
                        return 17;
                    }
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 13:
                    case 14:
                    case 15:
                    case 16:
                    case 17:
                    case 18:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 427;
                    }
                    case 27:
                    {
                        return 428;
                    }
                    case 26:
                    {
                        return 455;
                    }
                    case 29:
                    {
                        return 456;
                    }
                    case 2:
                    {
                        return 473;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 473:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(6, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 28:
                    {
                        return 17;
                    }
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 13:
                    case 14:
                    case 15:
                    case 16:
                    case 17:
                    case 18:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 427;
                    }
                    case 27:
                    {
                        return 428;
                    }
                    case 26:
                    {
                        return 455;
                    }
                    case 29:
                    {
                        return 456;
                    }
                    case 2:
                    {
                        return 474;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 474:
            {
                switch (cls)
                {
                    case 28:
                    {
                        return 17;
                    }
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 13:
                    case 14:
                    case 15:
                    case 16:
                    case 17:
                    case 18:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 427;
                    }
                    case 27:
                    {
                        return 428;
                    }
                    case 2:
                    {
                        return 443;
                    }
                    case 26:
                    {
                        return 455;
                    }
                    case 29:
                    {
                        return 456;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 470:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(6, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 28:
                    {
                        return 17;
                    }
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 13:
                    case 14:
                    case 15:
                    case 16:
                    case 17:
                    case 18:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 427;
                    }
                    case 27:
                    {
                        return 428;
                    }
                    case 26:
                    {
                        return 455;
                    }
                    case 29:
                    {
                        return 456;
                    }
                    case 2:
                    {
                        return 473;
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
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(43, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 11:
                    {
                        return 475;
                    }
                    case 50:
                    {
                        return 476;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 476:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(15, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 475:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(5, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(44, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 11:
                    {
                        return 477;
                    }
                    case 12:
                    {
                        return 478;
                    }
                    case 50:
                    {
                        return 479;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 479:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(16, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 478:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(4, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 477:
            {
                switch (cls)
                {
                    case 0:
                    {
                        return 480;
                    }
                    case 1:
                    {
                        return 481;
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
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 482;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 482:
            {
                switch (cls)
                {
                    case 0:
                    {
                        return 480;
                    }
                    case 1:
                    {
                        return 481;
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
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 482;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 481:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    {
                        return 483;
                    }
                    case 2:
                    {
                        return 484;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 484:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 483:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 485;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 485:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 484;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 480:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(3, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 485;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 6:
            {
                switch (cls)
                {
                    case 0:
                    {
                        return 486;
                    }
                    case 1:
                    {
                        return 487;
                    }
                    case 2:
                    {
                        return 488;
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
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 489;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 489:
            {
                switch (cls)
                {
                    case 0:
                    {
                        return 486;
                    }
                    case 1:
                    {
                        return 487;
                    }
                    case 2:
                    {
                        return 488;
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
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 489;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 488:
            {
                switch (cls)
                {
                    case 0:
                    {
                        return 486;
                    }
                    case 1:
                    {
                        return 487;
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
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    case 56:
                    case 57:
                    case 58:
                    case 59:
                    case 60:
                    case 61:
                    case 62:
                    case 63:
                    case 64:
                    case 65:
                    {
                        return 489;
                    }
                    case 2:
                    {
                        return 490;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 490:
            {
                switch (cls)
                {
                    case 0:
                    {
                        return 486;
                    }
                    case 1:
                    {
                        return 487;
                    }
                    case 2:
                    {
                        return 491;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 491:
            {
                switch (cls)
                {
                    case 0:
                    {
                        return 486;
                    }
                    case 1:
                    {
                        return 492;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 492:
            {
                switch (cls)
                {
                    case 0:
                    {
                        return 493;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 493:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 494;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 494:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 495;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 495:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 487:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    {
                        return 493;
                    }
                    case 2:
                    {
                        return 495;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 486:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(2, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 494;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 5:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(0, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 7:
                    case 8:
                    {
                        return 5;
                    }
                    case 9:
                    {
                        return 6;
                    }
                    case 0:
                    case 1:
                    {
                        return 496;
                    }
                    case 2:
                    {
                        return 497;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 497:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(0, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 7:
                    case 8:
                    {
                        return 5;
                    }
                    case 9:
                    {
                        return 6;
                    }
                    case 0:
                    case 1:
                    {
                        return 496;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 496:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(0, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                        return 496;
                    }
                    case 2:
                    {
                        return 498;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 498:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(0, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                        return 496;
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
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(6, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 6:
                    case 13:
                    case 14:
                    case 15:
                    case 16:
                    case 17:
                    case 18:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 427;
                    }
                    case 27:
                    {
                        return 428;
                    }
                    case 2:
                    {
                        return 448;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 3:
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
                    case 3:
                    case 4:
                    case 6:
                    case 13:
                    case 14:
                    case 15:
                    case 16:
                    case 22:
                    case 23:
                    case 24:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 40:
                    case 42:
                    case 43:
                    case 44:
                    {
                        return 4;
                    }
                    case 7:
                    case 8:
                    {
                        return 5;
                    }
                    case 9:
                    {
                        return 6;
                    }
                    case 11:
                    {
                        return 7;
                    }
                    case 12:
                    {
                        return 8;
                    }
                    case 17:
                    {
                        return 9;
                    }
                    case 18:
                    {
                        return 10;
                    }
                    case 19:
                    {
                        return 11;
                    }
                    case 20:
                    {
                        return 12;
                    }
                    case 21:
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
                    case 39:
                    case 41:
                    case 46:
                    case 47:
                    {
                        return 20;
                    }
                    case 45:
                    {
                        return 21;
                    }
                    case 48:
                    {
                        return 22;
                    }
                    case 49:
                    {
                        return 23;
                    }
                    case 50:
                    {
                        return 24;
                    }
                    case 51:
                    {
                        return 25;
                    }
                    case 52:
                    {
                        return 26;
                    }
                    case 53:
                    {
                        return 27;
                    }
                    case 54:
                    {
                        return 28;
                    }
                    case 55:
                    {
                        return 29;
                    }
                    case 56:
                    {
                        return 30;
                    }
                    case 57:
                    {
                        return 31;
                    }
                    case 58:
                    {
                        return 32;
                    }
                    case 59:
                    {
                        return 33;
                    }
                    case 60:
                    {
                        return 34;
                    }
                    case 61:
                    {
                        return 35;
                    }
                    case 62:
                    {
                        return 36;
                    }
                    case 63:
                    {
                        return 37;
                    }
                    case 64:
                    {
                        return 38;
                    }
                    case 65:
                    {
                        return 39;
                    }
                    case 2:
                    {
                        return 499;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 499:
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
                    case 3:
                    case 4:
                    case 6:
                    case 13:
                    case 14:
                    case 15:
                    case 16:
                    case 22:
                    case 23:
                    case 24:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 40:
                    case 42:
                    case 43:
                    case 44:
                    {
                        return 4;
                    }
                    case 7:
                    case 8:
                    {
                        return 5;
                    }
                    case 9:
                    {
                        return 6;
                    }
                    case 17:
                    {
                        return 9;
                    }
                    case 18:
                    {
                        return 10;
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
                    case 39:
                    case 41:
                    case 46:
                    case 47:
                    {
                        return 20;
                    }
                    case 45:
                    {
                        return 21;
                    }
                    case 2:
                    {
                        return 500;
                    }
                    case 19:
                    {
                        return 501;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 501:
            {
                switch (cls)
                {
                    case 29:
                    {
                        return 164;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 166;
                    }
                    case 2:
                    {
                        return 463;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 500:
            {
                switch (cls)
                {
                    case 27:
                    {
                        return 16;
                    }
                    case 45:
                    {
                        return 21;
                    }
                    case 39:
                    case 41:
                    case 46:
                    case 47:
                    {
                        return 67;
                    }
                    case 29:
                    {
                        return 143;
                    }
                    case 19:
                    {
                        return 501;
                    }
                    case 0:
                    {
                        return 502;
                    }
                    case 1:
                    {
                        return 503;
                    }
                    case 2:
                    {
                        return 504;
                    }
                    case 17:
                    {
                        return 505;
                    }
                    case 18:
                    {
                        return 506;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 506:
            {
                switch (cls)
                {
                    case 28:
                    {
                        return 17;
                    }
                    case 29:
                    {
                        return 456;
                    }
                    case 2:
                    {
                        return 507;
                    }
                    case 26:
                    {
                        return 508;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 508:
            {
                switch (cls)
                {
                    case 28:
                    {
                        return 453;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 507:
            {
                switch (cls)
                {
                    case 28:
                    {
                        return 17;
                    }
                    case 29:
                    {
                        return 456;
                    }
                    case 26:
                    {
                        return 508;
                    }
                    case 2:
                    {
                        return 509;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 509:
            {
                switch (cls)
                {
                    case 28:
                    {
                        return 17;
                    }
                    case 29:
                    {
                        return 456;
                    }
                    case 26:
                    {
                        return 508;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 505:
            {
                switch (cls)
                {
                    case 28:
                    {
                        return 17;
                    }
                    case 29:
                    {
                        return 456;
                    }
                    case 26:
                    {
                        return 508;
                    }
                    case 2:
                    {
                        return 510;
                    }
                    case 41:
                    {
                        return 511;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 511:
            {
                switch (cls)
                {
                    case 28:
                    {
                        return 17;
                    }
                    case 29:
                    {
                        return 456;
                    }
                    case 26:
                    {
                        return 508;
                    }
                    case 2:
                    {
                        return 510;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 510:
            {
                switch (cls)
                {
                    case 28:
                    {
                        return 17;
                    }
                    case 29:
                    {
                        return 456;
                    }
                    case 2:
                    {
                        return 507;
                    }
                    case 26:
                    {
                        return 508;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 504:
            {
                switch (cls)
                {
                    case 39:
                    case 41:
                    case 46:
                    case 47:
                    {
                        return 67;
                    }
                    case 29:
                    {
                        return 143;
                    }
                    case 19:
                    {
                        return 501;
                    }
                    case 17:
                    {
                        return 505;
                    }
                    case 2:
                    {
                        return 512;
                    }
                    case 45:
                    {
                        return 513;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 513:
            {
                switch (cls)
                {
                    case 13:
                    {
                        return 57;
                    }
                    case 14:
                    {
                        return 58;
                    }
                    case 19:
                    {
                        return 61;
                    }
                    case 36:
                    {
                        return 65;
                    }
                    case 37:
                    case 38:
                    {
                        return 66;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 67;
                    }
                    case 42:
                    {
                        return 68;
                    }
                    case 2:
                    {
                        return 142;
                    }
                    case 29:
                    {
                        return 143;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 512:
            {
                switch (cls)
                {
                    case 39:
                    case 41:
                    case 46:
                    case 47:
                    {
                        return 67;
                    }
                    case 29:
                    {
                        return 143;
                    }
                    case 19:
                    {
                        return 501;
                    }
                    case 2:
                    {
                        return 514;
                    }
                    case 45:
                    {
                        return 515;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 515:
            {
                switch (cls)
                {
                    case 19:
                    {
                        return 61;
                    }
                    case 36:
                    {
                        return 65;
                    }
                    case 37:
                    case 38:
                    {
                        return 66;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 67;
                    }
                    case 42:
                    {
                        return 68;
                    }
                    case 2:
                    {
                        return 142;
                    }
                    case 29:
                    {
                        return 143;
                    }
                    case 13:
                    {
                        return 516;
                    }
                    case 14:
                    {
                        return 517;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 517:
            {
                switch (cls)
                {
                    case 2:
                    {
                        return 518;
                    }
                    case 29:
                    {
                        return 519;
                    }
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 520;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 520:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 16:
                    {
                        return 191;
                    }
                    case 17:
                    case 18:
                    {
                        return 192;
                    }
                    case 24:
                    {
                        return 195;
                    }
                    case 25:
                    {
                        return 196;
                    }
                    case 29:
                    {
                        return 519;
                    }
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 520;
                    }
                    case 2:
                    {
                        return 521;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 521:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 16:
                    {
                        return 191;
                    }
                    case 17:
                    case 18:
                    {
                        return 192;
                    }
                    case 24:
                    {
                        return 195;
                    }
                    case 25:
                    {
                        return 196;
                    }
                    case 29:
                    {
                        return 519;
                    }
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 520;
                    }
                    case 2:
                    {
                        return 522;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 522:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 16:
                    {
                        return 191;
                    }
                    case 17:
                    case 18:
                    {
                        return 192;
                    }
                    case 24:
                    {
                        return 195;
                    }
                    case 25:
                    {
                        return 196;
                    }
                    case 29:
                    {
                        return 519;
                    }
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 520;
                    }
                    case 2:
                    {
                        return 523;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 523:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 16:
                    {
                        return 191;
                    }
                    case 17:
                    case 18:
                    {
                        return 192;
                    }
                    case 24:
                    {
                        return 195;
                    }
                    case 25:
                    {
                        return 196;
                    }
                    case 2:
                    {
                        return 256;
                    }
                    case 29:
                    {
                        return 519;
                    }
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 520;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 519:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(7, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                    case 16:
                    {
                        return 191;
                    }
                    case 17:
                    case 18:
                    {
                        return 192;
                    }
                    case 24:
                    {
                        return 195;
                    }
                    case 25:
                    {
                        return 196;
                    }
                    case 29:
                    {
                        return 519;
                    }
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 520;
                    }
                    case 2:
                    {
                        return 521;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 518:
            {
                switch (cls)
                {
                    case 29:
                    {
                        return 519;
                    }
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 520;
                    }
                    case 2:
                    {
                        return 524;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 524:
            {
                switch (cls)
                {
                    case 29:
                    {
                        return 519;
                    }
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 520;
                    }
                    case 2:
                    {
                        return 525;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 525:
            {
                switch (cls)
                {
                    case 29:
                    {
                        return 519;
                    }
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 520;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 516:
            {
                switch (cls)
                {
                    case 2:
                    {
                        return 518;
                    }
                    case 29:
                    {
                        return 519;
                    }
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 520;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 514:
            {
                switch (cls)
                {
                    case 29:
                    {
                        return 526;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 527;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 527:
            {
                switch (cls)
                {
                    case 19:
                    {
                        return 61;
                    }
                    case 29:
                    {
                        return 526;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 527;
                    }
                    case 2:
                    {
                        return 528;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 528:
            {
                switch (cls)
                {
                    case 19:
                    {
                        return 61;
                    }
                    case 29:
                    {
                        return 526;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 527;
                    }
                    case 2:
                    {
                        return 529;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 529:
            {
                switch (cls)
                {
                    case 19:
                    {
                        return 61;
                    }
                    case 2:
                    {
                        return 514;
                    }
                    case 29:
                    {
                        return 526;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 527;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 526:
            {
                switch (cls)
                {
                    case 19:
                    {
                        return 61;
                    }
                    case 29:
                    {
                        return 526;
                    }
                    case 39:
                    case 41:
                    case 45:
                    case 46:
                    case 47:
                    {
                        return 527;
                    }
                    case 2:
                    {
                        return 528;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 503:
            {
                switch (cls)
                {
                    case 0:
                    {
                        return 530;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 530:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(1, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 531;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 531:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(1, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 532;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 532:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(1, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                return -1;
            }
            case 502:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(1, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
                {
                    token.id = tokenId;
                }
                else
                {
                    token.match = prevMatch;
                }
                switch (cls)
                {
                    case 2:
                    {
                        return 531;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 2:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(0, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                        return 496;
                    }
                    case 0:
                    {
                        return 533;
                    }
                    case 2:
                    {
                        return 534;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 534:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(0, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                        return 496;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 533:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(0, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                        return 496;
                    }
                    case 2:
                    {
                        return 535;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 535:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(0, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                        return 496;
                    }
                    case 2:
                    {
                        return 532;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 1:
            {
                auto& token = lexer.CurrentToken();
                Lexeme prevMatch = token.match;
                token.match = lexer.CurrentLexeme();
                int64_t tokenId = GetTokenId(0, lexer);
                if (tokenId == CONTINUE_TOKEN)
                {
                    token.id = CONTINUE_TOKEN;
                    return -1;
                }
                else if (tokenId != INVALID_TOKEN)
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
                        return 496;
                    }
                    case 2:
                    {
                        return 535;
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

    static int64_t GetTokenId(int32_t ruleIndex, soul::lexer::LexerBase<Char>& lexer)
    {
        switch (ruleIndex)
        {
            case 0:
            {
                lexer.Retract();
                return WS;
                break;
            }
            case 1:
            {
                lexer.Retract();
                return NEWLINE;
                break;
            }
            case 2:
            {
                lexer.Retract();
                return PP_LINE;
                break;
            }
            case 3:
            {
                lexer.Retract();
                return LINE_COMMENT;
                break;
            }
            case 4:
            {
                lexer.Retract();
                return BLOCK_COMMENT_START;
                break;
            }
            case 5:
            {
                lexer.Retract();
                return BLOCK_COMMENT_END;
                break;
            }
            case 6:
            {
                lexer.Retract();
                int64_t kw = lexer.GetKeywordToken(lexer.CurrentToken().match);
                if (kw == INVALID_TOKEN) return ID;
                else return KEYWORD;
                break;
            }
            case 7:
            {
                lexer.Retract();
                return INTEGER_LITERAL;
                break;
            }
            case 8:
            {
                lexer.Retract();
                return FLOATING_LITERAL;
                break;
            }
            case 9:
            {
                lexer.Retract();
                return CHARACTER_LITERAL;
                break;
            }
            case 10:
            {
                lexer.Retract();
                return BEGIN_RAW_STRING_LITERAL;
                break;
            }
            case 11:
            {
                lexer.Retract();
                return STRING_LITERAL;
                break;
            }
            case 12:
            {
                lexer.Retract();
                return OTHER;
                break;
            }
            case 13:
            {
                lexer.Retract();
                return OTHER;
                break;
            }
            case 14:
            {
                lexer.Retract();
                return OTHER;
                break;
            }
            case 15:
            {
                lexer.Retract();
                return OTHER;
                break;
            }
            case 16:
            {
                lexer.Retract();
                return OTHER;
                break;
            }
            case 17:
            {
                lexer.Retract();
                return OTHER;
                break;
            }
            case 18:
            {
                lexer.Retract();
                return OTHER;
                break;
            }
            case 19:
            {
                lexer.Retract();
                return OTHER;
                break;
            }
            case 20:
            {
                lexer.Retract();
                return OTHER;
                break;
            }
            case 21:
            {
                lexer.Retract();
                return OTHER;
                break;
            }
            case 22:
            {
                lexer.Retract();
                return OTHER;
                break;
            }
            case 23:
            {
                lexer.Retract();
                return OTHER;
                break;
            }
            case 24:
            {
                lexer.Retract();
                return OTHER;
                break;
            }
            case 25:
            {
                lexer.Retract();
                return OTHER;
                break;
            }
            case 26:
            {
                lexer.Retract();
                return OTHER;
                break;
            }
            case 27:
            {
                lexer.Retract();
                return OTHER;
                break;
            }
            case 28:
            {
                lexer.Retract();
                return OTHER;
                break;
            }
            case 29:
            {
                lexer.Retract();
                return OTHER;
                break;
            }
            case 30:
            {
                lexer.Retract();
                return OTHER;
                break;
            }
            case 31:
            {
                lexer.Retract();
                return OTHER;
                break;
            }
            case 32:
            {
                lexer.Retract();
                return OTHER;
                break;
            }
            case 33:
            {
                lexer.Retract();
                return OTHER;
                break;
            }
            case 34:
            {
                lexer.Retract();
                return OTHER;
                break;
            }
            case 35:
            {
                lexer.Retract();
                return OTHER;
                break;
            }
            case 36:
            {
                lexer.Retract();
                return OTHER;
                break;
            }
            case 37:
            {
                lexer.Retract();
                return OTHER;
                break;
            }
            case 38:
            {
                lexer.Retract();
                return OTHER;
                break;
            }
            case 39:
            {
                lexer.Retract();
                return OTHER;
                break;
            }
            case 40:
            {
                auto vars = static_cast<Variables*>(lexer.GetVariables());
                if (vars->langleCount > 0) return INVALID_TOKEN;
                lexer.Retract();
                return OTHER;
                break;
            }
            case 41:
            {
                lexer.Retract();
                return OTHER;
                break;
            }
            case 42:
            {
                lexer.Retract();
                return OTHER;
                break;
            }
            case 43:
            {
                lexer.Retract();
                return OTHER;
                break;
            }
            case 44:
            {
                lexer.Retract();
                return OTHER;
                break;
            }
            case 45:
            {
                lexer.Retract();
                return OTHER;
                break;
            }
            case 46:
            {
                lexer.Retract();
                return OTHER;
                break;
            }
            case 47:
            {
                lexer.Retract();
                return OTHER;
                break;
            }
            case 48:
            {
                lexer.Retract();
                return OTHER;
                break;
            }
            case 49:
            {
                lexer.Retract();
                return OTHER;
                break;
            }
            case 50:
            {
                lexer.Retract();
                return OTHER;
                break;
            }
            case 51:
            {
                lexer.Retract();
                return OTHER;
                break;
            }
            case 52:
            {
                lexer.Retract();
                return OTHER;
                break;
            }
            case 53:
            {
                lexer.Retract();
                return OTHER;
                break;
            }
            case 54:
            {
                lexer.Retract();
                return OTHER;
                break;
            }
            case 55:
            {
                lexer.Retract();
                return OTHER;
                break;
            }
            case 56:
            {
                lexer.Retract();
                return OTHER;
                break;
            }
            case 57:
            {
                lexer.Retract();
                return OTHER;
                break;
            }
            case 58:
            {
                lexer.Retract();
                return OTHER;
                break;
            }
            case 59:
            {
                lexer.Retract();
                return OTHER;
                break;
            }
            case 60:
            {
                lexer.Retract();
                return OTHER;
                break;
            }
            case 61:
            {
                lexer.Retract();
                return OTHER;
                break;
            }
        }
        return CONTINUE_TOKEN;
    }
};

template<typename Char>
ClassMap<Char>* GetClassMap()
{
    static ClassMap<Char>* classmap = MakeClassMap<Char>("soul.cpp20.token.line.lexer.classmap");
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
soul::lexer::Lexer<Cpp20TokenLineLexer<Char>, Char> MakeLexer(const Char* start, const Char* end, const std::string& fileName)
{
    std::lock_guard<std::mutex> lock(MakeLexerMtx());
    auto lexer = soul::lexer::Lexer<Cpp20TokenLineLexer<Char>, Char>(start, end, fileName);
    lexer.SetClassMap(GetClassMap<Char>());
    lexer.SetTokenCollection(GetTokens());
    lexer.SetKeywordMap(GetKeywords<Char>());
    return lexer;
}

} // namespace soul::cpp20::token::line::lexer
