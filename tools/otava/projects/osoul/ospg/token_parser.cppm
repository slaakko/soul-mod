// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.spg.token.parser;

import util;
import std;
import soul.lexer.token;
import soul.lexer.base;
import soul.ast.spg;
import soul.ast.source.pos;
import soul.common.token.parser;

export namespace soul::spg::token::parser {

    template<typename CharT>
    std::expected<soul::ast::spg::Parser*, int> ParseStringLiteralOrCharSet(const std::string& fileName,
        const soul::lexer::Token<CharT, soul::lexer::LexerBase<CharT>>* token, const soul::ast::SourcePos& sourcePos)
    {
        std::u32string stringLiteral;
        std::unique_ptr<soul::ast::spg::CharSet> set;
        const CharT* p = token->match.begin;
        const CharT* e = token->match.end;
        if (p != e && *p == '"')
        {
            ++p;
            if (p != e && *p == '[')
            {
                set.reset(new soul::ast::spg::CharSet());
                ++p;
                if (p != e && *p == '^')
                {
                    set->SetInverse();
                    ++p;
                }
                while (p != e && *p != ']')
                {
                    char32_t first = *p;
                    char32_t last = first;
                    if (*p == '\\')
                    {
                        ++p;
                        auto rv = util::ParseEscape(p, e, token->ToString());
                        if (!rv)
                        {
                            int error = util::AllocateError(util::GetErrorMessage(rv.error()) + "\n(file=" + fileName + ", line=" + std::to_string(token->line) + ")");
                            return std::unexpected<int>(error);
                        }
                        first = *rv;
                        last = first;
                    }
                    else
                    {
                        ++p;
                    }
                    if (p != e && *p != ']')
                    {
                        if (*p == '-')
                        {
                            ++p;
                            if (p != e && *p != ']')
                            {
                                last = *p;
                                if (*p == '\\')
                                {
                                    ++p;
                                    auto rv = util::ParseEscape(p, e, token->ToString());
                                    if (!rv)
                                    {
                                        int error = util::AllocateError(util::GetErrorMessage(rv.error()) + "\n(file=" + fileName + ", line=" + std::to_string(token->line) + ")");
                                        return std::unexpected<int>(error);
                                    }
                                    last = *rv;
                                }
                                else
                                {
                                    ++p;
                                }
                            }
                            else
                            {
                                soul::ast::spg::Range range;
                                range.first = first;
                                range.last = first;
                                set->AddRange(range);
                                first = '-';
                                last = '-';
                            }
                        }
                    }
                    soul::ast::spg::Range range;
                    range.first = first;
                    range.last = last;
                    set->AddRange(range);
                }
                if (p != e && *p == ']')
                {
                    ++p;
                }
                if (p != e && *p == '"')
                {
                    ++p;
                }
                if (p != e)
                {
                    auto u = util::ToUtf8(token->match.ToString());
                    if (!u) return std::unexpected<int>(u.error());
                    return std::unexpected<int>(util::AllocateError("invalid character set literal at " + fileName + ":" + std::to_string(token->line) + ": " + *u));
                }
                return std::expected<soul::ast::spg::Parser*, int>(static_cast<soul::ast::spg::Parser*>(new soul::ast::spg::CharSetParser(sourcePos, set.release())));
            }
            else
            {
                while (p != e && *p != '\r' && *p != '\n' && *p != '"')
                {
                    if (*p == '\\')
                    {
                        ++p;
                        auto rv = util::ParseEscape(p, e, token->ToString());
                        if (!rv)
                        {
                            int error = util::AllocateError(util::GetErrorMessage(rv.error()) + "\n(file=" + fileName + ", line=" + std::to_string(token->line) + ")");
                            return std::unexpected<int>(error);
                        }
                        stringLiteral.append(1, *rv);
                    }
                    else
                    {
                        stringLiteral.append(1, *p);
                        ++p;
                    }
                }
                if (p != e && *p == '"')
                {
                    ++p;
                }
                if (p != e)
                {
                    auto u = util::ToUtf8(token->match.ToString());
                    if (!u) return std::unexpected<int>(u.error());
                    return std::unexpected<int>(util::AllocateError("invalid string literal at " + fileName + ":" + std::to_string(token->line) + ": " + *u));
                }
            }
        }
        else
        {
            auto u = util::ToUtf8(token->match.ToString());
            if (!u) return std::unexpected<int>(u.error());
            return std::unexpected<int>(util::AllocateError("invalid string literal at " + fileName + ":" + std::to_string(token->line) + ": " + *u));
        }
        return std::expected<soul::ast::spg::Parser*, int>(static_cast<soul::ast::spg::Parser*>(new soul::ast::spg::StringParser(sourcePos, stringLiteral)));
    }

} // namespace soul::spg::token::parser
