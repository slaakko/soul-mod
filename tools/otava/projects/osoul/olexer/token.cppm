// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.lexer.token;

import std;
import soul.lexer.lexeme;
import soul.lexer.token.parser;

export namespace soul::lexer {

const std::int64_t CONTINUE_TOKEN = -2;
const std::int64_t INVALID_TOKEN = -1;
const std::int64_t END_TOKEN = 0;

template<typename CharT, typename LexerBaseT>
struct Token
{
    using CharType = CharT;

    inline Token(LexerBaseT* lexer_) : match(), lexer(lexer_), id(INVALID_TOKEN), line(1) {}
    inline Token(std::int64_t id_, LexerBaseT* lexer_) : match(), lexer(lexer_), id(id_), line(1) {}
    inline Token(std::int64_t id_, const Lexeme<CharT>& match_, LexerBaseT* lexer_, int line_) : match(match_), lexer(lexer_), id(id_), line(line_) {}
    inline std::basic_string<CharT> ToString() const { return match.ToString(); }
    inline CharT Chr() const { return *match.begin; }
    inline std::expected<std::int8_t, int> ToSByte() const { return ParseSByte(match.begin, match.end, lexer, line); }
    inline std::expected<std::uint8_t, int> ToByte() const { return ParseByte(match.begin, match.end, lexer, line); }
    inline std::expected<std::int16_t, int> ToShort() const { return ParseShort(match.begin, match.end, lexer, line); }
    inline std::expected<std::uint16_t, int> ToUShort() const { return ParseUShort(match.begin, match.end, lexer, line); }
    inline std::expected<std::int32_t, int> ToInt() const { return ParseInt(match.begin, match.end, lexer, line); }
    inline std::expected<std::uint32_t, int> ToUInt() const { return ParseUInt(match.begin, match.end, lexer, line); }
    inline std::expected<std::int64_t, int> ToLong() const { return ParseLong(match.begin, match.end, lexer, line); }
    inline std::expected<std::uint64_t, int> ToULong() const { return ParseULong(match.begin, match.end, lexer, line); }
    inline std::expected<std::uint64_t, int> ToHexULong() const { return ParseHexULong(match.begin, match.end, lexer, line); }
    inline std::expected<std::uint64_t, int> ToOctalULong() const { return ParseOctalULong(match.begin, match.end, lexer, line); }
    inline std::expected<float, int> ToFloat() const { return ParseFloat(match.begin, match.end, lexer, line); }
    inline std::expected<double, int> ToDouble() const { return ParseDouble(match.begin, match.end, lexer, line); }
    inline std::expected<bool, int> ToBool() const { return ParseBool(match.begin, match.end, lexer, line); }
    Lexeme<CharT> match;
    LexerBaseT* lexer;
    std::int64_t id;
    int line;
};

template<typename CharT, typename LexerBaseT>
struct TokenLine
{
    TokenLine() : startState(0), endState(0) {}
    int TokenIndex(int columnNumber) const
    {
        int col = 1;
        int index = 0;
        for (const Token<CharT, LexerBaseT>& token : tokens)
        {
            int len = token.match.end - token.match.begin;
            if (columnNumber >= col && columnNumber < col + len)
            {
                return index;
            }
            col += len;
            ++index;
        }
        return -1;
    }
    std::vector<Token<CharT, LexerBaseT>> tokens;
    int startState;
    int endState;
};

} // namespace soul::lexer
