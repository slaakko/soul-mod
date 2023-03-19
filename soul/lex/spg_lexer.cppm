// this file has been automatically generated from 'C:/work/soul-mod/soul/lex/spg_lexer.lexer' using soul lexer generator slg version 4.0.0

export module soul.lex.spg;

import std.core;
import soul.lexer;
import soul.ast.slg;
import soul.cpp.token;
import soul.cpp.op.token;
import soul.punctuation.token;
import soul.tool.token;

using namespace soul;
using namespace soul::lexer;
using namespace soul::cpp::token;
using namespace soul::cpp::op::token;
using namespace soul::punctuation::token;
using namespace soul::tool::token;

export namespace soul::lex::spg {

std::mutex& MakeLexerMtx();

template<typename Char>
struct SpgLexer;

template<typename Char>
soul::lexer::Lexer<SpgLexer<Char>, Char> MakeLexer(const Char* start, const Char* end, const std::string& fileName);

soul::ast::slg::TokenCollection* GetTokens();

struct SpgLexer_Variables : public soul::lexer::Variables
{
    SpgLexer_Variables();
    int leftAngleCount;
    bool matchFilePath;
};

template<typename Char>
struct SpgLexer
{
    using Variables = SpgLexer_Variables;

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
                    case 2:
                    case 12:
                    case 13:
                    {
                        return 1;
                    }
                    case 1:
                    {
                        return 2;
                    }
                    case 4:
                    {
                        return 3;
                    }
                    case 5:
                    {
                        return 4;
                    }
                    case 6:
                    {
                        return 5;
                    }
                    case 7:
                    {
                        return 6;
                    }
                    case 8:
                    case 9:
                    case 11:
                    case 15:
                    case 16:
                    case 19:
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
                    {
                        return 7;
                    }
                    case 17:
                    {
                        return 8;
                    }
                    case 18:
                    {
                        return 9;
                    }
                    case 20:
                    {
                        return 10;
                    }
                    case 21:
                    {
                        return 11;
                    }
                    case 22:
                    {
                        return 12;
                    }
                    case 23:
                    {
                        return 13;
                    }
                    case 37:
                    case 38:
                    case 40:
                    {
                        return 14;
                    }
                    case 39:
                    {
                        return 15;
                    }
                    case 41:
                    {
                        return 16;
                    }
                    case 42:
                    {
                        return 17;
                    }
                    case 43:
                    {
                        return 18;
                    }
                    case 44:
                    {
                        return 19;
                    }
                    case 45:
                    {
                        return 20;
                    }
                    case 46:
                    {
                        return 21;
                    }
                    case 47:
                    {
                        return 22;
                    }
                    case 48:
                    {
                        return 23;
                    }
                    case 49:
                    {
                        return 24;
                    }
                    case 50:
                    {
                        return 25;
                    }
                    case 51:
                    {
                        return 26;
                    }
                    case 52:
                    {
                        return 27;
                    }
                    case 53:
                    {
                        return 28;
                    }
                    case 54:
                    {
                        return 29;
                    }
                    case 55:
                    {
                        return 30;
                    }
                    case 56:
                    {
                        return 31;
                    }
                    case 57:
                    {
                        return 32;
                    }
                    case 58:
                    {
                        return 33;
                    }
                    case 59:
                    {
                        return 34;
                    }
                    case 60:
                    {
                        return 35;
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
            case 34:
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
                return -1;
            }
            case 33:
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
                return -1;
            }
            case 32:
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
                return -1;
            }
            case 31:
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
                return -1;
            }
            case 30:
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
                return -1;
            }
            case 29:
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
                return -1;
            }
            case 28:
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
            case 27:
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
            case 26:
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
            case 25:
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
                return -1;
            }
            case 24:
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
                switch (cls)
                {
                    case 42:
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
            case 23:
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
                switch (cls)
                {
                    case 1:
                    {
                        return 37;
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
                    case 43:
                    case 44:
                    case 45:
                    case 46:
                    case 47:
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
                    {
                        return 38;
                    }
                    case 42:
                    {
                        return 39;
                    }
                    case 48:
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
                switch (cls)
                {
                    case 1:
                    {
                        return 37;
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
                    {
                        return 38;
                    }
                    case 42:
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
                switch (cls)
                {
                    case 1:
                    {
                        return 37;
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
                    {
                        return 38;
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
                switch (cls)
                {
                    case 1:
                    {
                        return 37;
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
                    case 1:
                    {
                        return 37;
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
            case 22:
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
                    case 42:
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
            case 21:
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
                switch (cls)
                {
                    case 42:
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
                return -1;
            }
            case 20:
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
                    case 42:
                    {
                        return 44;
                    }
                    case 45:
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
            case 44:
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
            case 19:
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
                switch (cls)
                {
                    case 42:
                    {
                        return 46;
                    }
                    case 44:
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
            case 46:
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
                return -1;
            }
            case 18:
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
            case 17:
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
                switch (cls)
                {
                    case 42:
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
            case 16:
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
                    case 41:
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
                    case 42:
                    {
                        return 50;
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
                return -1;
            }
            case 15:
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
                    case 15:
                    {
                        return 51;
                    }
                    case 16:
                    {
                        return 52;
                    }
                    case 17:
                    {
                        return 53;
                    }
                    case 18:
                    {
                        return 54;
                    }
                    case 21:
                    {
                        return 55;
                    }
                    case 29:
                    {
                        return 56;
                    }
                    case 30:
                    {
                        return 57;
                    }
                    case 37:
                    case 38:
                    {
                        return 58;
                    }
                    case 39:
                    case 40:
                    {
                        return 59;
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
                    case 17:
                    {
                        return 53;
                    }
                    case 18:
                    {
                        return 54;
                    }
                    case 21:
                    {
                        return 55;
                    }
                    case 29:
                    {
                        return 56;
                    }
                    case 30:
                    {
                        return 57;
                    }
                    case 37:
                    case 38:
                    {
                        return 58;
                    }
                    case 39:
                    case 40:
                    {
                        return 59;
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
                    case 21:
                    {
                        return 55;
                    }
                    case 29:
                    {
                        return 56;
                    }
                    case 30:
                    {
                        return 57;
                    }
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    {
                        return 58;
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
                    case 22:
                    {
                        return 60;
                    }
                    case 23:
                    {
                        return 61;
                    }
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    {
                        return 62;
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
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    {
                        return 62;
                    }
                    case 19:
                    {
                        return 63;
                    }
                    case 20:
                    {
                        return 64;
                    }
                    case 31:
                    {
                        return 65;
                    }
                    case 32:
                    {
                        return 66;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 66:
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
            case 65:
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
            case 64:
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
            case 63:
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
            case 61:
            {
                switch (cls)
                {
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    {
                        return 62;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 60:
            {
                switch (cls)
                {
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    {
                        return 62;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 56:
            {
                switch (cls)
                {
                    case 22:
                    {
                        return 60;
                    }
                    case 23:
                    {
                        return 61;
                    }
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    {
                        return 62;
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
                    case 19:
                    {
                        return 63;
                    }
                    case 20:
                    {
                        return 64;
                    }
                    case 31:
                    {
                        return 65;
                    }
                    case 32:
                    {
                        return 66;
                    }
                    case 29:
                    {
                        return 67;
                    }
                    case 30:
                    {
                        return 68;
                    }
                    case 37:
                    case 38:
                    case 39:
                    case 40:
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
                    case 19:
                    {
                        return 63;
                    }
                    case 20:
                    {
                        return 64;
                    }
                    case 31:
                    {
                        return 65;
                    }
                    case 32:
                    {
                        return 66;
                    }
                    case 29:
                    {
                        return 67;
                    }
                    case 30:
                    {
                        return 68;
                    }
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    {
                        return 69;
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
                    case 22:
                    {
                        return 70;
                    }
                    case 23:
                    {
                        return 71;
                    }
                    case 37:
                    case 38:
                    case 39:
                    case 40:
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
                    case 19:
                    {
                        return 63;
                    }
                    case 20:
                    {
                        return 64;
                    }
                    case 31:
                    {
                        return 65;
                    }
                    case 32:
                    {
                        return 66;
                    }
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    {
                        return 72;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 71:
            {
                switch (cls)
                {
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    {
                        return 72;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 70:
            {
                switch (cls)
                {
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    {
                        return 72;
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
                    case 22:
                    {
                        return 70;
                    }
                    case 23:
                    {
                        return 71;
                    }
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    {
                        return 72;
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
                    case 19:
                    {
                        return 73;
                    }
                    case 20:
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
                    case 20:
                    {
                        return 75;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 75:
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
            case 73:
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
                    case 19:
                    {
                        return 76;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 76:
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
            case 53:
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
                    case 19:
                    {
                        return 73;
                    }
                    case 20:
                    {
                        return 74;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 52:
            {
                switch (cls)
                {
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
                    case 17:
                    {
                        return 53;
                    }
                    case 18:
                    {
                        return 54;
                    }
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
                    {
                        return 77;
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
                    {
                        return 77;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 14:
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
                    case 17:
                    {
                        return 53;
                    }
                    case 18:
                    {
                        return 54;
                    }
                    case 21:
                    {
                        return 55;
                    }
                    case 29:
                    {
                        return 56;
                    }
                    case 30:
                    {
                        return 57;
                    }
                    case 37:
                    case 38:
                    case 39:
                    case 40:
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
                    case 17:
                    {
                        return 53;
                    }
                    case 18:
                    {
                        return 54;
                    }
                    case 21:
                    {
                        return 55;
                    }
                    case 29:
                    {
                        return 56;
                    }
                    case 30:
                    {
                        return 57;
                    }
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    {
                        return 78;
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
                switch (cls)
                {
                    case 1:
                    {
                        return 79;
                    }
                    case 23:
                    {
                        return 80;
                    }
                    case 42:
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
                return -1;
            }
            case 80:
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
                return -1;
            }
            case 79:
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
                    case 7:
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
            case 12:
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
                switch (cls)
                {
                    case 22:
                    {
                        return 83;
                    }
                    case 42:
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
            case 83:
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
            case 11:
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
                switch (cls)
                {
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    {
                        return 69;
                    }
                    case 7:
                    {
                        return 85;
                    }
                    case 21:
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
                switch (cls)
                {
                    case 21:
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
                return -1;
            }
            case 85:
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
            case 10:
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
                    case 4:
                    {
                        return 3;
                    }
                    case 5:
                    {
                        return 88;
                    }
                    case 8:
                    case 9:
                    case 10:
                    case 11:
                    case 15:
                    case 16:
                    case 17:
                    case 18:
                    case 19:
                    case 20:
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
                    {
                        return 89;
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
                    case 8:
                    case 9:
                    case 10:
                    case 11:
                    case 15:
                    case 16:
                    case 17:
                    case 18:
                    case 19:
                    case 20:
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
                    {
                        return 89;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 88:
            {
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 90;
                    }
                    case 3:
                    {
                        return 91;
                    }
                    case 5:
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
            case 91:
            {
                switch (cls)
                {
                    case 3:
                    {
                        return 91;
                    }
                    case 0:
                    case 1:
                    case 2:
                    case 4:
                    case 6:
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 23:
                    case 28:
                    case 29:
                    case 30:
                    case 32:
                    case 37:
                    case 38:
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
                    {
                        return 93;
                    }
                    case 5:
                    {
                        return 94;
                    }
                    case 15:
                    {
                        return 95;
                    }
                    case 16:
                    {
                        return 96;
                    }
                    case 17:
                    {
                        return 97;
                    }
                    case 18:
                    {
                        return 98;
                    }
                    case 24:
                    {
                        return 99;
                    }
                    case 25:
                    {
                        return 100;
                    }
                    case 26:
                    {
                        return 101;
                    }
                    case 27:
                    {
                        return 102;
                    }
                    case 31:
                    {
                        return 103;
                    }
                    case 33:
                    {
                        return 104;
                    }
                    case 34:
                    {
                        return 105;
                    }
                    case 35:
                    {
                        return 106;
                    }
                    case 36:
                    {
                        return 107;
                    }
                    case 39:
                    case 40:
                    {
                        return 108;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 108:
            {
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 90;
                    }
                    case 3:
                    {
                        return 91;
                    }
                    case 5:
                    {
                        return 92;
                    }
                    case 39:
                    case 40:
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
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 90;
                    }
                    case 3:
                    {
                        return 91;
                    }
                    case 5:
                    {
                        return 92;
                    }
                    case 39:
                    case 40:
                    {
                        return 109;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 107:
            {
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 90;
                    }
                    case 3:
                    {
                        return 91;
                    }
                    case 5:
                    {
                        return 92;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 106:
            {
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 90;
                    }
                    case 3:
                    {
                        return 91;
                    }
                    case 5:
                    {
                        return 92;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 105:
            {
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 90;
                    }
                    case 3:
                    {
                        return 91;
                    }
                    case 5:
                    {
                        return 92;
                    }
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    {
                        return 110;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 110:
            {
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 90;
                    }
                    case 3:
                    {
                        return 91;
                    }
                    case 5:
                    {
                        return 92;
                    }
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    {
                        return 110;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 104:
            {
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 90;
                    }
                    case 3:
                    {
                        return 91;
                    }
                    case 5:
                    {
                        return 92;
                    }
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    {
                        return 110;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 103:
            {
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 90;
                    }
                    case 3:
                    {
                        return 91;
                    }
                    case 5:
                    {
                        return 92;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 102:
            {
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 90;
                    }
                    case 3:
                    {
                        return 91;
                    }
                    case 5:
                    {
                        return 92;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 101:
            {
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 90;
                    }
                    case 3:
                    {
                        return 91;
                    }
                    case 5:
                    {
                        return 92;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 100:
            {
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 90;
                    }
                    case 3:
                    {
                        return 91;
                    }
                    case 5:
                    {
                        return 92;
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
                    case 1:
                    case 4:
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
                    {
                        return 90;
                    }
                    case 3:
                    {
                        return 91;
                    }
                    case 5:
                    {
                        return 92;
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
                    case 1:
                    case 4:
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
                    {
                        return 90;
                    }
                    case 3:
                    {
                        return 91;
                    }
                    case 5:
                    {
                        return 92;
                    }
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
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 90;
                    }
                    case 3:
                    {
                        return 91;
                    }
                    case 5:
                    {
                        return 92;
                    }
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
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 90;
                    }
                    case 3:
                    {
                        return 91;
                    }
                    case 5:
                    {
                        return 92;
                    }
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
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 90;
                    }
                    case 3:
                    {
                        return 91;
                    }
                    case 5:
                    {
                        return 92;
                    }
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
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 90;
                    }
                    case 3:
                    {
                        return 91;
                    }
                    case 5:
                    {
                        return 92;
                    }
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
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 90;
                    }
                    case 3:
                    {
                        return 91;
                    }
                    case 5:
                    {
                        return 92;
                    }
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
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 90;
                    }
                    case 3:
                    {
                        return 91;
                    }
                    case 5:
                    {
                        return 92;
                    }
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
                    {
                        return 117;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 117:
            {
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 90;
                    }
                    case 3:
                    {
                        return 91;
                    }
                    case 5:
                    {
                        return 92;
                    }
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
                    {
                        return 118;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 118:
            {
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 90;
                    }
                    case 3:
                    {
                        return 91;
                    }
                    case 5:
                    {
                        return 92;
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
                    case 1:
                    case 4:
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
                    {
                        return 90;
                    }
                    case 3:
                    {
                        return 91;
                    }
                    case 5:
                    {
                        return 92;
                    }
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
                    {
                        return 119;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 119:
            {
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 90;
                    }
                    case 3:
                    {
                        return 91;
                    }
                    case 5:
                    {
                        return 92;
                    }
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
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 90;
                    }
                    case 3:
                    {
                        return 91;
                    }
                    case 5:
                    {
                        return 92;
                    }
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
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 90;
                    }
                    case 3:
                    {
                        return 91;
                    }
                    case 5:
                    {
                        return 92;
                    }
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
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 90;
                    }
                    case 3:
                    {
                        return 91;
                    }
                    case 5:
                    {
                        return 92;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 96:
            {
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 90;
                    }
                    case 3:
                    {
                        return 91;
                    }
                    case 5:
                    {
                        return 92;
                    }
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
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 90;
                    }
                    case 3:
                    {
                        return 91;
                    }
                    case 5:
                    {
                        return 92;
                    }
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
                    {
                        return 123;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 95:
            {
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 90;
                    }
                    case 3:
                    {
                        return 91;
                    }
                    case 5:
                    {
                        return 92;
                    }
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
                    {
                        return 123;
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
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 90;
                    }
                    case 3:
                    {
                        return 91;
                    }
                    case 5:
                    {
                        return 92;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 93:
            {
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 90;
                    }
                    case 3:
                    {
                        return 91;
                    }
                    case 5:
                    {
                        return 92;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 90:
            {
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 90;
                    }
                    case 3:
                    {
                        return 91;
                    }
                    case 5:
                    {
                        return 92;
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
                    case 4:
                    {
                        return 3;
                    }
                    case 8:
                    case 9:
                    case 10:
                    case 11:
                    case 15:
                    case 16:
                    case 17:
                    case 18:
                    case 19:
                    case 20:
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
                    {
                        return 89;
                    }
                    case 5:
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
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 125;
                    }
                    case 3:
                    {
                        return 126;
                    }
                    case 5:
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
            case 126:
            {
                switch (cls)
                {
                    case 3:
                    {
                        return 126;
                    }
                    case 0:
                    case 1:
                    case 2:
                    case 4:
                    case 6:
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 23:
                    case 28:
                    case 29:
                    case 30:
                    case 32:
                    case 37:
                    case 38:
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
                    {
                        return 128;
                    }
                    case 5:
                    {
                        return 129;
                    }
                    case 15:
                    {
                        return 130;
                    }
                    case 16:
                    {
                        return 131;
                    }
                    case 17:
                    {
                        return 132;
                    }
                    case 18:
                    {
                        return 133;
                    }
                    case 24:
                    {
                        return 134;
                    }
                    case 25:
                    {
                        return 135;
                    }
                    case 26:
                    {
                        return 136;
                    }
                    case 27:
                    {
                        return 137;
                    }
                    case 31:
                    {
                        return 138;
                    }
                    case 33:
                    {
                        return 139;
                    }
                    case 34:
                    {
                        return 140;
                    }
                    case 35:
                    {
                        return 141;
                    }
                    case 36:
                    {
                        return 142;
                    }
                    case 39:
                    case 40:
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
                    case 1:
                    case 4:
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
                    {
                        return 125;
                    }
                    case 3:
                    {
                        return 126;
                    }
                    case 5:
                    {
                        return 127;
                    }
                    case 39:
                    case 40:
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
                    case 1:
                    case 4:
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
                    {
                        return 125;
                    }
                    case 3:
                    {
                        return 126;
                    }
                    case 5:
                    {
                        return 127;
                    }
                    case 39:
                    case 40:
                    {
                        return 144;
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
                    case 1:
                    case 4:
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
                    {
                        return 125;
                    }
                    case 3:
                    {
                        return 126;
                    }
                    case 5:
                    {
                        return 127;
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
                    case 1:
                    case 4:
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
                    {
                        return 125;
                    }
                    case 3:
                    {
                        return 126;
                    }
                    case 5:
                    {
                        return 127;
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
                    case 1:
                    case 4:
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
                    {
                        return 125;
                    }
                    case 3:
                    {
                        return 126;
                    }
                    case 5:
                    {
                        return 127;
                    }
                    case 37:
                    case 38:
                    case 39:
                    case 40:
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
                    case 1:
                    case 4:
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
                    {
                        return 125;
                    }
                    case 3:
                    {
                        return 126;
                    }
                    case 5:
                    {
                        return 127;
                    }
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    {
                        return 145;
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
                    case 1:
                    case 4:
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
                    {
                        return 125;
                    }
                    case 3:
                    {
                        return 126;
                    }
                    case 5:
                    {
                        return 127;
                    }
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    {
                        return 145;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 138:
            {
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 125;
                    }
                    case 3:
                    {
                        return 126;
                    }
                    case 5:
                    {
                        return 127;
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
                    case 1:
                    case 4:
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
                    {
                        return 125;
                    }
                    case 3:
                    {
                        return 126;
                    }
                    case 5:
                    {
                        return 127;
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
                    case 1:
                    case 4:
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
                    {
                        return 125;
                    }
                    case 3:
                    {
                        return 126;
                    }
                    case 5:
                    {
                        return 127;
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
                    case 1:
                    case 4:
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
                    {
                        return 125;
                    }
                    case 3:
                    {
                        return 126;
                    }
                    case 5:
                    {
                        return 127;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 134:
            {
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 125;
                    }
                    case 3:
                    {
                        return 126;
                    }
                    case 5:
                    {
                        return 127;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 133:
            {
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 125;
                    }
                    case 3:
                    {
                        return 126;
                    }
                    case 5:
                    {
                        return 127;
                    }
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
                    {
                        return 146;
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
                    case 1:
                    case 4:
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
                    {
                        return 125;
                    }
                    case 3:
                    {
                        return 126;
                    }
                    case 5:
                    {
                        return 127;
                    }
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
                    {
                        return 147;
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
                    case 1:
                    case 4:
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
                    {
                        return 125;
                    }
                    case 3:
                    {
                        return 126;
                    }
                    case 5:
                    {
                        return 127;
                    }
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
                    {
                        return 148;
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
                    case 1:
                    case 4:
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
                    {
                        return 125;
                    }
                    case 3:
                    {
                        return 126;
                    }
                    case 5:
                    {
                        return 127;
                    }
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
                    {
                        return 149;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 149:
            {
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 125;
                    }
                    case 3:
                    {
                        return 126;
                    }
                    case 5:
                    {
                        return 127;
                    }
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
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 125;
                    }
                    case 3:
                    {
                        return 126;
                    }
                    case 5:
                    {
                        return 127;
                    }
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
                    {
                        return 151;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 151:
            {
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 125;
                    }
                    case 3:
                    {
                        return 126;
                    }
                    case 5:
                    {
                        return 127;
                    }
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
                    {
                        return 152;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 152:
            {
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 125;
                    }
                    case 3:
                    {
                        return 126;
                    }
                    case 5:
                    {
                        return 127;
                    }
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
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 125;
                    }
                    case 3:
                    {
                        return 126;
                    }
                    case 5:
                    {
                        return 127;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 132:
            {
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 125;
                    }
                    case 3:
                    {
                        return 126;
                    }
                    case 5:
                    {
                        return 127;
                    }
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
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 125;
                    }
                    case 3:
                    {
                        return 126;
                    }
                    case 5:
                    {
                        return 127;
                    }
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
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 125;
                    }
                    case 3:
                    {
                        return 126;
                    }
                    case 5:
                    {
                        return 127;
                    }
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
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 125;
                    }
                    case 3:
                    {
                        return 126;
                    }
                    case 5:
                    {
                        return 127;
                    }
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
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 125;
                    }
                    case 3:
                    {
                        return 126;
                    }
                    case 5:
                    {
                        return 127;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 131:
            {
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 125;
                    }
                    case 3:
                    {
                        return 126;
                    }
                    case 5:
                    {
                        return 127;
                    }
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
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 125;
                    }
                    case 3:
                    {
                        return 126;
                    }
                    case 5:
                    {
                        return 127;
                    }
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
                    {
                        return 158;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 130:
            {
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 125;
                    }
                    case 3:
                    {
                        return 126;
                    }
                    case 5:
                    {
                        return 127;
                    }
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
                    {
                        return 158;
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
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 125;
                    }
                    case 3:
                    {
                        return 126;
                    }
                    case 5:
                    {
                        return 127;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 128:
            {
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 125;
                    }
                    case 3:
                    {
                        return 126;
                    }
                    case 5:
                    {
                        return 127;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 125:
            {
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 125;
                    }
                    case 3:
                    {
                        return 126;
                    }
                    case 5:
                    {
                        return 127;
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
                    case 4:
                    {
                        return 3;
                    }
                    case 8:
                    case 9:
                    case 10:
                    case 11:
                    case 15:
                    case 16:
                    case 17:
                    case 18:
                    case 19:
                    case 20:
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
                    case 39:
                    case 40:
                    {
                        return 89;
                    }
                    case 5:
                    {
                        return 124;
                    }
                    case 38:
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
                    case 4:
                    {
                        return 3;
                    }
                    case 8:
                    case 9:
                    case 10:
                    case 11:
                    case 15:
                    case 16:
                    case 17:
                    case 18:
                    case 19:
                    case 20:
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
                    {
                        return 89;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 7:
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
                    case 8:
                    case 9:
                    case 10:
                    case 11:
                    case 15:
                    case 16:
                    case 17:
                    case 18:
                    case 19:
                    case 20:
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
                    {
                        return 89;
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
                switch (cls)
                {
                    case 42:
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
            case 5:
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
                    case 6:
                    {
                        return 161;
                    }
                    case 7:
                    {
                        return 162;
                    }
                    case 42:
                    {
                        return 163;
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
            case 162:
            {
                switch (cls)
                {
                    case 0:
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
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
                    {
                        return 164;
                    }
                    case 7:
                    {
                        return 165;
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
                    case 7:
                    {
                        return 165;
                    }
                    case 0:
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 5:
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
                    {
                        return 166;
                    }
                    case 6:
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
                    case 3:
                    case 4:
                    case 5:
                    case 8:
                    case 9:
                    case 10:
                    case 11:
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
                    {
                        return 164;
                    }
                    case 7:
                    {
                        return 165;
                    }
                    case 0:
                    case 2:
                    case 12:
                    case 13:
                    {
                        return 168;
                    }
                    case 6:
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
                switch (cls)
                {
                    case 0:
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 5:
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
                    {
                        return 164;
                    }
                    case 6:
                    {
                        return 170;
                    }
                    case 7:
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
                switch (cls)
                {
                    case 7:
                    {
                        return 165;
                    }
                    case 0:
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 5:
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
                    {
                        return 166;
                    }
                    case 6:
                    {
                        return 167;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 170:
            {
                switch (cls)
                {
                    case 0:
                    {
                        return 172;
                    }
                    case 1:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
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
                    {
                        return 173;
                    }
                    case 2:
                    {
                        return 174;
                    }
                    case 7:
                    {
                        return 175;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 175:
            {
                switch (cls)
                {
                    case 7:
                    {
                        return 175;
                    }
                    case 0:
                    {
                        return 176;
                    }
                    case 1:
                    case 3:
                    case 4:
                    case 5:
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
                    {
                        return 177;
                    }
                    case 2:
                    {
                        return 178;
                    }
                    case 6:
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
                    case 3:
                    case 4:
                    case 5:
                    case 8:
                    case 9:
                    case 10:
                    case 11:
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
                    {
                        return 173;
                    }
                    case 7:
                    {
                        return 175;
                    }
                    case 0:
                    {
                        return 180;
                    }
                    case 2:
                    {
                        return 181;
                    }
                    case 6:
                    {
                        return 182;
                    }
                    case 12:
                    case 13:
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
                    case 3:
                    case 4:
                    case 5:
                    case 8:
                    case 9:
                    case 10:
                    case 11:
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
                    {
                        return 173;
                    }
                    case 7:
                    {
                        return 175;
                    }
                    case 0:
                    {
                        return 180;
                    }
                    case 2:
                    {
                        return 181;
                    }
                    case 6:
                    {
                        return 182;
                    }
                    case 12:
                    case 13:
                    {
                        return 183;
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
                    case 6:
                    {
                        return 170;
                    }
                    case 0:
                    {
                        return 172;
                    }
                    case 1:
                    case 3:
                    case 4:
                    case 5:
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
                    {
                        return 173;
                    }
                    case 2:
                    {
                        return 174;
                    }
                    case 7:
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
                switch (cls)
                {
                    case 7:
                    {
                        return 175;
                    }
                    case 0:
                    {
                        return 176;
                    }
                    case 1:
                    case 3:
                    case 4:
                    case 5:
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
                    {
                        return 177;
                    }
                    case 2:
                    {
                        return 178;
                    }
                    case 6:
                    {
                        return 179;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 181:
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
                    case 3:
                    case 4:
                    case 5:
                    case 8:
                    case 9:
                    case 10:
                    case 11:
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
                    {
                        return 164;
                    }
                    case 7:
                    {
                        return 165;
                    }
                    case 2:
                    case 12:
                    case 13:
                    {
                        return 168;
                    }
                    case 6:
                    {
                        return 169;
                    }
                    case 0:
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
                    case 3:
                    case 4:
                    case 5:
                    case 8:
                    case 9:
                    case 10:
                    case 11:
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
                    {
                        return 164;
                    }
                    case 7:
                    {
                        return 165;
                    }
                    case 0:
                    case 2:
                    case 12:
                    case 13:
                    {
                        return 168;
                    }
                    case 6:
                    {
                        return 169;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 180:
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
                    case 3:
                    case 4:
                    case 5:
                    case 8:
                    case 9:
                    case 10:
                    case 11:
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
                    {
                        return 164;
                    }
                    case 7:
                    {
                        return 165;
                    }
                    case 0:
                    case 2:
                    case 12:
                    case 13:
                    {
                        return 168;
                    }
                    case 6:
                    {
                        return 169;
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
                    case 3:
                    case 4:
                    case 5:
                    case 8:
                    case 9:
                    case 10:
                    case 11:
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
                    {
                        return 164;
                    }
                    case 7:
                    {
                        return 165;
                    }
                    case 2:
                    case 12:
                    case 13:
                    {
                        return 168;
                    }
                    case 6:
                    {
                        return 169;
                    }
                    case 0:
                    {
                        return 185;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 177:
            {
                switch (cls)
                {
                    case 0:
                    {
                        return 172;
                    }
                    case 1:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
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
                    {
                        return 173;
                    }
                    case 2:
                    {
                        return 174;
                    }
                    case 7:
                    {
                        return 175;
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
                    case 3:
                    case 4:
                    case 5:
                    case 8:
                    case 9:
                    case 10:
                    case 11:
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
                    {
                        return 164;
                    }
                    case 7:
                    {
                        return 165;
                    }
                    case 0:
                    case 2:
                    case 12:
                    case 13:
                    {
                        return 168;
                    }
                    case 6:
                    {
                        return 169;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 174:
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
                    case 3:
                    case 4:
                    case 5:
                    case 8:
                    case 9:
                    case 10:
                    case 11:
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
                    {
                        return 164;
                    }
                    case 7:
                    {
                        return 165;
                    }
                    case 2:
                    case 12:
                    case 13:
                    {
                        return 168;
                    }
                    case 6:
                    {
                        return 169;
                    }
                    case 0:
                    {
                        return 185;
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
                    case 0:
                    {
                        return 172;
                    }
                    case 1:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
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
                    {
                        return 173;
                    }
                    case 2:
                    {
                        return 174;
                    }
                    case 7:
                    {
                        return 175;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 172:
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
                    case 3:
                    case 4:
                    case 5:
                    case 8:
                    case 9:
                    case 10:
                    case 11:
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
                    {
                        return 164;
                    }
                    case 7:
                    {
                        return 165;
                    }
                    case 0:
                    case 2:
                    case 12:
                    case 13:
                    {
                        return 168;
                    }
                    case 6:
                    {
                        return 169;
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
                    case 3:
                    case 4:
                    case 5:
                    case 8:
                    case 9:
                    case 10:
                    case 11:
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
                    {
                        return 164;
                    }
                    case 7:
                    {
                        return 165;
                    }
                    case 0:
                    case 2:
                    case 12:
                    case 13:
                    {
                        return 168;
                    }
                    case 6:
                    {
                        return 169;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 166:
            {
                switch (cls)
                {
                    case 0:
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
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
                    {
                        return 164;
                    }
                    case 7:
                    {
                        return 165;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 164:
            {
                switch (cls)
                {
                    case 0:
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
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
                    {
                        return 164;
                    }
                    case 7:
                    {
                        return 165;
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
                    case 0:
                    {
                        return 186;
                    }
                    case 1:
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
                    {
                        return 187;
                    }
                    case 2:
                    {
                        return 188;
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
                    case 2:
                    case 12:
                    case 13:
                    {
                        return 1;
                    }
                    case 0:
                    {
                        return 189;
                    }
                    case 6:
                    {
                        return 190;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 190:
            {
                switch (cls)
                {
                    case 6:
                    {
                        return 161;
                    }
                    case 7:
                    {
                        return 162;
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
                    case 2:
                    case 12:
                    case 13:
                    {
                        return 1;
                    }
                    case 6:
                    {
                        return 190;
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
                    case 0:
                    {
                        return 186;
                    }
                    case 1:
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
                    {
                        return 187;
                    }
                    case 2:
                    {
                        return 188;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 186:
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
                    case 2:
                    case 12:
                    case 13:
                    {
                        return 1;
                    }
                    case 6:
                    {
                        return 190;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 4:
            {
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 191;
                    }
                    case 3:
                    {
                        return 192;
                    }
                    case 5:
                    {
                        return 193;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 193:
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
            case 192:
            {
                switch (cls)
                {
                    case 3:
                    {
                        return 192;
                    }
                    case 0:
                    case 1:
                    case 2:
                    case 4:
                    case 6:
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 23:
                    case 28:
                    case 29:
                    case 30:
                    case 32:
                    case 37:
                    case 38:
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
                    {
                        return 194;
                    }
                    case 5:
                    {
                        return 195;
                    }
                    case 15:
                    {
                        return 196;
                    }
                    case 16:
                    {
                        return 197;
                    }
                    case 17:
                    {
                        return 198;
                    }
                    case 18:
                    {
                        return 199;
                    }
                    case 24:
                    {
                        return 200;
                    }
                    case 25:
                    {
                        return 201;
                    }
                    case 26:
                    {
                        return 202;
                    }
                    case 27:
                    {
                        return 203;
                    }
                    case 31:
                    {
                        return 204;
                    }
                    case 33:
                    {
                        return 205;
                    }
                    case 34:
                    {
                        return 206;
                    }
                    case 35:
                    {
                        return 207;
                    }
                    case 36:
                    {
                        return 208;
                    }
                    case 39:
                    case 40:
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
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 191;
                    }
                    case 3:
                    {
                        return 192;
                    }
                    case 5:
                    {
                        return 193;
                    }
                    case 39:
                    case 40:
                    {
                        return 210;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 210:
            {
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 191;
                    }
                    case 3:
                    {
                        return 192;
                    }
                    case 5:
                    {
                        return 193;
                    }
                    case 39:
                    case 40:
                    {
                        return 210;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 208:
            {
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 191;
                    }
                    case 3:
                    {
                        return 192;
                    }
                    case 5:
                    {
                        return 193;
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
                    case 1:
                    case 4:
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
                    {
                        return 191;
                    }
                    case 3:
                    {
                        return 192;
                    }
                    case 5:
                    {
                        return 193;
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
                    case 1:
                    case 4:
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
                    {
                        return 191;
                    }
                    case 3:
                    {
                        return 192;
                    }
                    case 5:
                    {
                        return 193;
                    }
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    {
                        return 211;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 211:
            {
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 191;
                    }
                    case 3:
                    {
                        return 192;
                    }
                    case 5:
                    {
                        return 193;
                    }
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    {
                        return 211;
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
                    case 1:
                    case 4:
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
                    {
                        return 191;
                    }
                    case 3:
                    {
                        return 192;
                    }
                    case 5:
                    {
                        return 193;
                    }
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    {
                        return 211;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 204:
            {
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 191;
                    }
                    case 3:
                    {
                        return 192;
                    }
                    case 5:
                    {
                        return 193;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 203:
            {
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 191;
                    }
                    case 3:
                    {
                        return 192;
                    }
                    case 5:
                    {
                        return 193;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 202:
            {
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 191;
                    }
                    case 3:
                    {
                        return 192;
                    }
                    case 5:
                    {
                        return 193;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 201:
            {
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 191;
                    }
                    case 3:
                    {
                        return 192;
                    }
                    case 5:
                    {
                        return 193;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 200:
            {
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 191;
                    }
                    case 3:
                    {
                        return 192;
                    }
                    case 5:
                    {
                        return 193;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 199:
            {
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 191;
                    }
                    case 3:
                    {
                        return 192;
                    }
                    case 5:
                    {
                        return 193;
                    }
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
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 191;
                    }
                    case 3:
                    {
                        return 192;
                    }
                    case 5:
                    {
                        return 193;
                    }
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
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 191;
                    }
                    case 3:
                    {
                        return 192;
                    }
                    case 5:
                    {
                        return 193;
                    }
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
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 191;
                    }
                    case 3:
                    {
                        return 192;
                    }
                    case 5:
                    {
                        return 193;
                    }
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
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 191;
                    }
                    case 3:
                    {
                        return 192;
                    }
                    case 5:
                    {
                        return 193;
                    }
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
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 191;
                    }
                    case 3:
                    {
                        return 192;
                    }
                    case 5:
                    {
                        return 193;
                    }
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
                    case 1:
                    case 4:
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
                    {
                        return 191;
                    }
                    case 3:
                    {
                        return 192;
                    }
                    case 5:
                    {
                        return 193;
                    }
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
                    case 1:
                    case 4:
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
                    {
                        return 191;
                    }
                    case 3:
                    {
                        return 192;
                    }
                    case 5:
                    {
                        return 193;
                    }
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
                    case 1:
                    case 4:
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
                    {
                        return 191;
                    }
                    case 3:
                    {
                        return 192;
                    }
                    case 5:
                    {
                        return 193;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 198:
            {
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 191;
                    }
                    case 3:
                    {
                        return 192;
                    }
                    case 5:
                    {
                        return 193;
                    }
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
                    {
                        return 220;
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
                    case 1:
                    case 4:
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
                    {
                        return 191;
                    }
                    case 3:
                    {
                        return 192;
                    }
                    case 5:
                    {
                        return 193;
                    }
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
                    {
                        return 221;
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
                    case 1:
                    case 4:
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
                    {
                        return 191;
                    }
                    case 3:
                    {
                        return 192;
                    }
                    case 5:
                    {
                        return 193;
                    }
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
                    {
                        return 222;
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
                    case 1:
                    case 4:
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
                    {
                        return 191;
                    }
                    case 3:
                    {
                        return 192;
                    }
                    case 5:
                    {
                        return 193;
                    }
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
                    case 1:
                    case 4:
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
                    {
                        return 191;
                    }
                    case 3:
                    {
                        return 192;
                    }
                    case 5:
                    {
                        return 193;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 197:
            {
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 191;
                    }
                    case 3:
                    {
                        return 192;
                    }
                    case 5:
                    {
                        return 193;
                    }
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
                    case 1:
                    case 4:
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
                    {
                        return 191;
                    }
                    case 3:
                    {
                        return 192;
                    }
                    case 5:
                    {
                        return 193;
                    }
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
                    {
                        return 224;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 196:
            {
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 191;
                    }
                    case 3:
                    {
                        return 192;
                    }
                    case 5:
                    {
                        return 193;
                    }
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
                    {
                        return 224;
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
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 191;
                    }
                    case 3:
                    {
                        return 192;
                    }
                    case 5:
                    {
                        return 193;
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
                    case 1:
                    case 4:
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
                    {
                        return 191;
                    }
                    case 3:
                    {
                        return 192;
                    }
                    case 5:
                    {
                        return 193;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 191:
            {
                switch (cls)
                {
                    case 1:
                    case 4:
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
                    {
                        return 191;
                    }
                    case 3:
                    {
                        return 192;
                    }
                    case 5:
                    {
                        return 193;
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
                    case 1:
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
                    {
                        return 225;
                    }
                    case 3:
                    {
                        return 226;
                    }
                    case 4:
                    {
                        return 227;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 227:
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
            case 226:
            {
                switch (cls)
                {
                    case 3:
                    {
                        return 226;
                    }
                    case 0:
                    case 1:
                    case 2:
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
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 23:
                    case 28:
                    case 29:
                    case 30:
                    case 32:
                    case 37:
                    case 38:
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
                    {
                        return 228;
                    }
                    case 4:
                    {
                        return 229;
                    }
                    case 15:
                    {
                        return 230;
                    }
                    case 16:
                    {
                        return 231;
                    }
                    case 17:
                    {
                        return 232;
                    }
                    case 18:
                    {
                        return 233;
                    }
                    case 24:
                    {
                        return 234;
                    }
                    case 25:
                    {
                        return 235;
                    }
                    case 26:
                    {
                        return 236;
                    }
                    case 27:
                    {
                        return 237;
                    }
                    case 31:
                    {
                        return 238;
                    }
                    case 33:
                    {
                        return 239;
                    }
                    case 34:
                    {
                        return 240;
                    }
                    case 35:
                    {
                        return 241;
                    }
                    case 36:
                    {
                        return 242;
                    }
                    case 39:
                    case 40:
                    {
                        return 243;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 243:
            {
                switch (cls)
                {
                    case 1:
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
                    {
                        return 225;
                    }
                    case 3:
                    {
                        return 226;
                    }
                    case 4:
                    {
                        return 227;
                    }
                    case 39:
                    case 40:
                    {
                        return 244;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 244:
            {
                switch (cls)
                {
                    case 1:
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
                    {
                        return 225;
                    }
                    case 3:
                    {
                        return 226;
                    }
                    case 4:
                    {
                        return 227;
                    }
                    case 39:
                    case 40:
                    {
                        return 244;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 242:
            {
                switch (cls)
                {
                    case 1:
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
                    {
                        return 225;
                    }
                    case 3:
                    {
                        return 226;
                    }
                    case 4:
                    {
                        return 227;
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
                    case 1:
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
                    {
                        return 225;
                    }
                    case 3:
                    {
                        return 226;
                    }
                    case 4:
                    {
                        return 227;
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
                    case 1:
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
                    {
                        return 225;
                    }
                    case 3:
                    {
                        return 226;
                    }
                    case 4:
                    {
                        return 227;
                    }
                    case 37:
                    case 38:
                    case 39:
                    case 40:
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
                switch (cls)
                {
                    case 1:
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
                    {
                        return 225;
                    }
                    case 3:
                    {
                        return 226;
                    }
                    case 4:
                    {
                        return 227;
                    }
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    {
                        return 245;
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
                    case 1:
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
                    {
                        return 225;
                    }
                    case 3:
                    {
                        return 226;
                    }
                    case 4:
                    {
                        return 227;
                    }
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    {
                        return 245;
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
                    case 1:
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
                    {
                        return 225;
                    }
                    case 3:
                    {
                        return 226;
                    }
                    case 4:
                    {
                        return 227;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 237:
            {
                switch (cls)
                {
                    case 1:
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
                    {
                        return 225;
                    }
                    case 3:
                    {
                        return 226;
                    }
                    case 4:
                    {
                        return 227;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 236:
            {
                switch (cls)
                {
                    case 1:
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
                    {
                        return 225;
                    }
                    case 3:
                    {
                        return 226;
                    }
                    case 4:
                    {
                        return 227;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 235:
            {
                switch (cls)
                {
                    case 1:
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
                    {
                        return 225;
                    }
                    case 3:
                    {
                        return 226;
                    }
                    case 4:
                    {
                        return 227;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 234:
            {
                switch (cls)
                {
                    case 1:
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
                    {
                        return 225;
                    }
                    case 3:
                    {
                        return 226;
                    }
                    case 4:
                    {
                        return 227;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 233:
            {
                switch (cls)
                {
                    case 1:
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
                    {
                        return 225;
                    }
                    case 3:
                    {
                        return 226;
                    }
                    case 4:
                    {
                        return 227;
                    }
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
                switch (cls)
                {
                    case 1:
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
                    {
                        return 225;
                    }
                    case 3:
                    {
                        return 226;
                    }
                    case 4:
                    {
                        return 227;
                    }
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
                switch (cls)
                {
                    case 1:
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
                    {
                        return 225;
                    }
                    case 3:
                    {
                        return 226;
                    }
                    case 4:
                    {
                        return 227;
                    }
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
                switch (cls)
                {
                    case 1:
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
                    {
                        return 225;
                    }
                    case 3:
                    {
                        return 226;
                    }
                    case 4:
                    {
                        return 227;
                    }
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
                switch (cls)
                {
                    case 1:
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
                    {
                        return 225;
                    }
                    case 3:
                    {
                        return 226;
                    }
                    case 4:
                    {
                        return 227;
                    }
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
                switch (cls)
                {
                    case 1:
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
                    {
                        return 225;
                    }
                    case 3:
                    {
                        return 226;
                    }
                    case 4:
                    {
                        return 227;
                    }
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
                    {
                        return 251;
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
                    case 1:
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
                    {
                        return 225;
                    }
                    case 3:
                    {
                        return 226;
                    }
                    case 4:
                    {
                        return 227;
                    }
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
                    case 1:
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
                    {
                        return 225;
                    }
                    case 3:
                    {
                        return 226;
                    }
                    case 4:
                    {
                        return 227;
                    }
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
                switch (cls)
                {
                    case 1:
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
                    {
                        return 225;
                    }
                    case 3:
                    {
                        return 226;
                    }
                    case 4:
                    {
                        return 227;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 232:
            {
                switch (cls)
                {
                    case 1:
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
                    {
                        return 225;
                    }
                    case 3:
                    {
                        return 226;
                    }
                    case 4:
                    {
                        return 227;
                    }
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
                switch (cls)
                {
                    case 1:
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
                    {
                        return 225;
                    }
                    case 3:
                    {
                        return 226;
                    }
                    case 4:
                    {
                        return 227;
                    }
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
                switch (cls)
                {
                    case 1:
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
                    {
                        return 225;
                    }
                    case 3:
                    {
                        return 226;
                    }
                    case 4:
                    {
                        return 227;
                    }
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
                switch (cls)
                {
                    case 1:
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
                    {
                        return 225;
                    }
                    case 3:
                    {
                        return 226;
                    }
                    case 4:
                    {
                        return 227;
                    }
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
                switch (cls)
                {
                    case 1:
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
                    {
                        return 225;
                    }
                    case 3:
                    {
                        return 226;
                    }
                    case 4:
                    {
                        return 227;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 231:
            {
                switch (cls)
                {
                    case 1:
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
                    {
                        return 225;
                    }
                    case 3:
                    {
                        return 226;
                    }
                    case 4:
                    {
                        return 227;
                    }
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
                    {
                        return 258;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 258:
            {
                switch (cls)
                {
                    case 1:
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
                    {
                        return 225;
                    }
                    case 3:
                    {
                        return 226;
                    }
                    case 4:
                    {
                        return 227;
                    }
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
                    {
                        return 258;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 230:
            {
                switch (cls)
                {
                    case 1:
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
                    {
                        return 225;
                    }
                    case 3:
                    {
                        return 226;
                    }
                    case 4:
                    {
                        return 227;
                    }
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
                    {
                        return 258;
                    }
                    default:
                    {
                        return -1;
                    }
                }
            }
            case 229:
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
                switch (cls)
                {
                    case 1:
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
                    {
                        return 225;
                    }
                    case 3:
                    {
                        return 226;
                    }
                    case 4:
                    {
                        return 227;
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
                    case 1:
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
                    {
                        return 225;
                    }
                    case 3:
                    {
                        return 226;
                    }
                    case 4:
                    {
                        return 227;
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
                    case 1:
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
                    {
                        return 225;
                    }
                    case 3:
                    {
                        return 226;
                    }
                    case 4:
                    {
                        return 227;
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
                switch (cls)
                {
                    case 1:
                    {
                        return 259;
                    }
                    case 42:
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
            case 259:
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
                switch (cls)
                {
                    case 42:
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
                    case 2:
                    case 12:
                    case 13:
                    {
                        return 1;
                    }
                    case 6:
                    {
                        return 190;
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
                break;
            }
            case 1:
            {
                lexer.Retract();
                int64_t kw = lexer.GetKeywordToken(lexer.CurrentToken().match);
                if (kw == INVALID_TOKEN) return ID;
                else return kw;
                break;
            }
            case 2:
            {
                lexer.Retract();
                return INTEGER_LITERAL;
                break;
            }
            case 3:
            {
                lexer.Retract();
                return FLOATING_LITERAL;
                break;
            }
            case 4:
            {
                lexer.Retract();
                return CHAR_LITERAL;
                break;
            }
            case 5:
            {
                lexer.Retract();
                return STRING_LITERAL;
                break;
            }
            case 6:
            {
                lexer.Retract();
                return PRODUCES;
                break;
            }
            case 7:
            {
                lexer.Retract();
                return DOLLAR;
                break;
            }
            case 8:
            {
                lexer.Retract();
                return DISJUNCTION;
                break;
            }
            case 9:
            {
                lexer.Retract();
                return AMP_AMP;
                break;
            }
            case 10:
            {
                lexer.Retract();
                return DOT_STAR;
                break;
            }
            case 11:
            {
                lexer.Retract();
                return ARROW_STAR;
                break;
            }
            case 12:
            {
                lexer.Retract();
                return PIPE;
                break;
            }
            case 13:
            {
                lexer.Retract();
                return CARET;
                break;
            }
            case 14:
            {
                lexer.Retract();
                return AMP;
                break;
            }
            case 15:
            {
                lexer.Retract();
                return EQ;
                break;
            }
            case 16:
            {
                lexer.Retract();
                return NEQ;
                break;
            }
            case 17:
            {
                lexer.Retract();
                return LEQ;
                break;
            }
            case 18:
            {
                lexer.Retract();
                return GEQ;
                break;
            }
            case 19:
            {
                lexer.Retract();
                return LANGLE;
                break;
            }
            case 20:
            {
                lexer.Retract();
                return RANGLE;
                break;
            }
            case 21:
            {
                lexer.Retract();
                return SHIFT_LEFT;
                break;
            }
            case 22:
            {
                auto vars = static_cast<Variables*>(lexer.GetVariables());
                if (vars->leftAngleCount > 0) return INVALID_TOKEN;
                lexer.Retract();
                return SHIFT_RIGHT;
                break;
            }
            case 23:
            {
                lexer.Retract();
                return PLUS;
                break;
            }
            case 24:
            {
                lexer.Retract();
                return MINUS;
                break;
            }
            case 25:
            {
                lexer.Retract();
                return STAR;
                break;
            }
            case 26:
            {
                lexer.Retract();
                return DIV;
                break;
            }
            case 27:
            {
                lexer.Retract();
                return REM;
                break;
            }
            case 28:
            {
                lexer.Retract();
                return PLUS_PLUS;
                break;
            }
            case 29:
            {
                lexer.Retract();
                return MINUS_MINUS;
                break;
            }
            case 30:
            {
                lexer.Retract();
                return EXCLAMATION;
                break;
            }
            case 31:
            {
                lexer.Retract();
                return QUEST;
                break;
            }
            case 32:
            {
                lexer.Retract();
                return TILDE;
                break;
            }
            case 33:
            {
                lexer.Retract();
                return DOT;
                break;
            }
            case 34:
            {
                lexer.Retract();
                return ARROW;
                break;
            }
            case 35:
            {
                lexer.Retract();
                return LBRACKET;
                break;
            }
            case 36:
            {
                lexer.Retract();
                return RBRACKET;
                break;
            }
            case 37:
            {
                lexer.Retract();
                return LPAREN;
                break;
            }
            case 38:
            {
                lexer.Retract();
                return RPAREN;
                break;
            }
            case 39:
            {
                lexer.Retract();
                return LBRACE;
                break;
            }
            case 40:
            {
                lexer.Retract();
                return RBRACE;
                break;
            }
            case 41:
            {
                lexer.Retract();
                return ELLIPSIS;
                break;
            }
            case 42:
            {
                lexer.Retract();
                return COLON_COLON;
                break;
            }
            case 43:
            {
                lexer.Retract();
                return COLON;
                break;
            }
            case 44:
            {
                lexer.Retract();
                return SEMICOLON;
                break;
            }
            case 45:
            {
                lexer.Retract();
                return HASH;
                break;
            }
            case 46:
            {
                lexer.Retract();
                return COMMA;
                break;
            }
            case 47:
            {
                lexer.Retract();
                return ASSIGN;
                break;
            }
            case 48:
            {
                lexer.Retract();
                return MUL_ASSIGN;
                break;
            }
            case 49:
            {
                lexer.Retract();
                return DIV_ASSIGN;
                break;
            }
            case 50:
            {
                lexer.Retract();
                return REM_ASSIGN;
                break;
            }
            case 51:
            {
                lexer.Retract();
                return PLUS_ASSIGN;
                break;
            }
            case 52:
            {
                lexer.Retract();
                return MINUS_ASSIGN;
                break;
            }
            case 53:
            {
                lexer.Retract();
                return SHIFT_LEFT_ASSIGN;
                break;
            }
            case 54:
            {
                lexer.Retract();
                return SHIFT_RIGHT_ASSIGN;
                break;
            }
            case 55:
            {
                lexer.Retract();
                return AND_ASSIGN;
                break;
            }
            case 56:
            {
                lexer.Retract();
                return XOR_ASSIGN;
                break;
            }
            case 57:
            {
                lexer.Retract();
                return OR_ASSIGN;
                break;
            }
            case 58:
            {
                auto vars = static_cast<Variables*>(lexer.GetVariables());
                if (!vars->matchFilePath) return INVALID_TOKEN;
                lexer.Retract();
                return FILEPATH;
                break;
            }
        }
        return CONTINUE_TOKEN;
    }
};

template<typename Char>
ClassMap<Char>* GetClassMap()
{
    static ClassMap<Char>* classmap = MakeClassMap<Char>("soul.lex.spg.classmap");
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
soul::lexer::Lexer<SpgLexer<Char>, Char> MakeLexer(const Char* start, const Char* end, const std::string& fileName)
{
    std::lock_guard<std::mutex> lock(MakeLexerMtx());
    auto lexer = soul::lexer::Lexer<SpgLexer<Char>, Char>(start, end, fileName);
    lexer.SetClassMap(GetClassMap<Char>());
    lexer.SetTokenCollection(GetTokens());
    lexer.SetKeywordMap(GetKeywords<Char>());
    return lexer;
}

} // namespace soul::lex::spg
