// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.lexer.cls;

import std;
import util;
import soul.ast.source.pos;
import soul.ast.slg;
import soul.ast.common;
import soul.lexer.token.parser;
import soul.lexer.base;
import soul.lexer.parsing.log;
import soul.lexer.token;
import soul.lexer.keyword;
import soul.ast.lexer.pos.pair;
import soul.ast.span;

export namespace soul::lexer {

enum class LexerFlags : std::int32_t
{
    none = 0, synchronize = 1 << 0, synchronized = 1 << 1, synchronizedAtLeastOnce = 1 << 2, cursorSeen = 1 << 3, recordedParse = 1 << 4, farthestError = 1 << 5
};

constexpr LexerFlags operator|(LexerFlags left, LexerFlags right)
{
    return static_cast<LexerFlags>(static_cast<std::int32_t>(left) | static_cast<std::int32_t>(right));
}

constexpr LexerFlags operator&(LexerFlags left, LexerFlags right)
{
    return static_cast<LexerFlags>(static_cast<std::int32_t>(left) & static_cast<std::int32_t>(right));
}

constexpr LexerFlags operator~(LexerFlags flag)
{
    return static_cast<LexerFlags>(~static_cast<std::int32_t>(flag));
}

bool parsing_error_thrown = false;

template<class CharT, class LexerBaseT>
struct LexerState
{
    LexerState(LexerBaseT* lexer) : token(lexer), line(0), lexeme(), pos(), tokens(), flags(), recordedPosPair(), farthestPos(), currentPos()
    {
    }
    soul::lexer::Token<CharT, LexerBaseT> token;
    int line;
    Lexeme<CharT> lexeme;
    const CharT* pos;
    std::vector<soul::lexer::Token<CharT, LexerBaseT>> tokens;
    LexerFlags flags;
    soul::ast::lexer::pos::pair::LexerPosPair recordedPosPair;
    std::int64_t farthestPos;
    std::vector<std::int64_t> ruleContext;
    std::vector<std::int64_t> farthestRuleContext;
    std::int64_t currentPos;
};

template<typename Stack>
struct RuleGuard
{
    RuleGuard(Stack& stack_, std::int64_t ruleId) : stack(stack_)
    {
        stack.PushRule(ruleId);
    }
    ~RuleGuard()
    {
        stack.PopRule();
    }
    Stack& stack;
};

template<typename CharT>
const CharT* LineStart(const CharT* start, const CharT* p)
{
    while (p != start && *p != '\n' && *p != '\r')
    {
        --p;
    }
    if (p != start)
    {
        ++p;
    }
    return p;
}

template<typename CharT>
const CharT* LineEnd(const CharT* end, const CharT* p)
{
    while (p != end && *p != '\n' && *p != '\r')
    {
        ++p;
    }
    return p;
}

template<typename Machine, typename CharT>
class Lexer : public LexerBase<CharT>
{
public:
    using LexerType = Lexer<Machine, CharT>;
    using CharType = CharT;
    using TokenType = soul::lexer::Token<CharT, LexerBase<CharT>>;
    using TokenLineType = soul::lexer::TokenLine<CharT, LexerBase<CharT>>;
    using VariableClassType = Machine::Variables;
    using PPHook = void (*)(LexerType* lexer, TokenType* token);

    Lexer() :
        LexerBase<CharT>(), 
        flags(LexerFlags::none),
        file(-1),
        line(1),
        current(tokens.end()),
        token(this),
        separatorChar('\0'),
        start(),
        end(),
        pos(),
        fileName(),
        countLines(true),
        classMap(nullptr),
        tokenCollection(nullptr),
        keywordMap(nullptr),
        ruleNameMapPtr(nullptr),
        farthestPos(GetPos()),
        log(nullptr),
        vars(),
        state(this),
        ppHook(nullptr),
        skip(false),
        commentTokenId(-1)
    {
    }

    Lexer(const CharT* start_, const CharT* end_, const std::string& fileName_) :
        LexerBase<CharT>(),
        flags(LexerFlags::none),
        file(-1),
        line(1),
        current(tokens.end()),
        token(this),
        separatorChar('\0'),
        start(start_),
        end(end_),
        pos(start),
        fileName(fileName_),
        countLines(true),
        classMap(nullptr),
        tokenCollection(nullptr),
        keywordMap(nullptr),
        ruleNameMapPtr(nullptr),
        farthestPos(GetPos()),
        log(nullptr),
        vars(),
        state(this),
        ppHook(nullptr),
        skip(false),
        commentTokenId(-1)
    {
        ComputeLineStarts();
    }
    inline std::int64_t operator*() const
    {
        return current->id;
    }
    std::expected<bool, int> operator++()
    {
        if (GetFlag(LexerFlags::recordedParse))
        {
            // precondition: !tokens.empty() && tokens.back().id == END_TOKEN
            std::int64_t currentPos = GetPos();
            if (currentPos == recordedPosPair.end)
            {
                current = tokens.end() - 1; // set current to last token whose id is END_TOKEN
                auto token = tokens.back();
                pos = token.match.end;
            }
            else
            {
                ++current;
            }
            line = current->line;
        }
        else
        {
            if (current != tokens.end())
            {
                ++current;
            }
            if (current == tokens.end())
            {
                std::expected<bool, int> next = NextToken();
                if (!next) return next;
            }
            else
            {
                line = current->line;
            }
            std::int64_t p = GetPos();
            if (p > farthestPos)
            {
                farthestPos = p;
                farthestRuleContext = ruleContext;
            }
        }
        return std::expected<bool, int>(true);
    }
    std::int64_t GetPos() const override
    {
        std::int32_t p = static_cast<std::int32_t>(current - tokens.begin());
        return (static_cast<std::int64_t>(line) << 32) | static_cast<std::int64_t>(p);
    }
    void SetPos(std::int64_t pos)
    {
        current = tokens.begin() + static_cast<std::int32_t>(pos);
        line = static_cast<std::int32_t>(pos >> 32);
    }
    std::expected<soul::ast::Span, int> GetSpan() const override
    {
        return GetSpan(GetPos());
    }
    std::expected<soul::ast::Span, int> GetSpan(std::int64_t pos) const override
    {
        auto rv = GetToken(pos);
        if (!rv) return std::unexpected<int>(rv.error());
        const TokenType* token = *rv;
        return soul::ast::Span(static_cast<int>(token->match.begin - start), token->match.Length());
    }
    std::expected<const TokenType*, int> GetToken(std::int64_t pos) const override
    {
        std::int32_t tokenIndex = static_cast<std::int32_t>(pos);
        if (tokenIndex >= 0 && tokenIndex < tokens.size())
        {
            const TokenType* token = &tokens[tokenIndex];
            return std::expected<const TokenType*, int>(token);
        }
        else
        {
            return std::unexpected<int>(util::AllocateError("invalid token index"));
        }
    }
    std::expected<std::basic_string<CharT>, int> TokenToString(std::int64_t pos) const override
    {
        auto rv = GetToken(pos);
        if (!rv) return std::unexpected<int>(rv.error());
        const TokenType* token = *rv;
        return std::expected<std::basic_string<CharT>, int>(token->ToString());
    }
    std::expected<std::string, int> TokenToUtf8(std::int64_t pos) const override
    {
        auto rv = GetToken(pos);
        if (!rv) return std::unexpected<int>(rv.error());
        const TokenType* token = *rv;
        return util::ToUtf8(token->ToString());
    }
    std::expected<std::int8_t, int> TokenToSByte(std::int64_t pos) const override
    {
        auto rv = GetToken(pos);
        if (!rv) return std::unexpected<int>(rv.error());
        const TokenType* token = *rv;
        std::expected<std::int8_t, int> u = util::ParseSByte(token->ToString());
        if (!u) return std::unexpected<int>(util::AllocateError(util::GetErrorMessage(u.error()) + "\n(file='" + fileName + "', line=" + std::to_string(line) + ")"));
        return u;
    }
    std::expected<std::uint8_t, int> TokenToByte(std::int64_t pos) const override
    {
        auto rv = GetToken(pos);
        if (!rv) return std::unexpected<int>(rv.error());
        const TokenType* token = *rv;
        std::expected<std::uint8_t, int> u = util::ParseByte(token->ToString());
        if (!u) return std::unexpected<int>(util::AllocateError(util::GetErrorMessage(u.error()) + "\n(file='" + fileName + "', line=" + std::to_string(line) + ")"));
        return u;
    }
    std::expected<std::int16_t, int> TokenToShort(std::int64_t pos) const override
    {
        auto rv = GetToken(pos);
        if (!rv) return std::unexpected<int>(rv.error());
        const TokenType* token = *rv;
        std::expected<std::int16_t, int> u = util::ParseShort(token->ToString());
        if (!u) return std::unexpected<int>(util::AllocateError(util::GetErrorMessage(u.error()) + "\n(file='" + fileName + "', line=" + std::to_string(line) + ")"));
        return u;
    }
    std::expected<std::uint16_t, int> TokenToUShort(std::int64_t pos) const override
    {
        auto rv = GetToken(pos);
        if (!rv) return std::unexpected<int>(rv.error());
        const TokenType* token = *rv;
        std::expected<std::uint16_t, int> u = util::ParseUShort(token->ToString());
        if (!u) return std::unexpected<int>(util::AllocateError(util::GetErrorMessage(u.error()) + "\n(file='" + fileName + "', line=" + std::to_string(line) + ")"));
        return u;
    }
    std::expected<std::int32_t, int> TokenToInt(std::int64_t pos) const override
    {
        auto rv = GetToken(pos);
        if (!rv) return std::unexpected<int>(rv.error());
        const TokenType* token = *rv;
        std::expected<std::int32_t, int> u = util::ParseInt(token->ToString());
        if (!u) return std::unexpected<int>(util::AllocateError(util::GetErrorMessage(u.error()) + "\n(file='" + fileName + "', line=" + std::to_string(line) + ")"));
        return u;
    }
    std::expected<std::uint32_t, int> TokenToUInt(std::int64_t pos) const override
    {
        auto rv = GetToken(pos);
        if (!rv) return std::unexpected<int>(rv.error());
        const TokenType* token = *rv;
        std::expected<std::uint32_t, int> u = util::ParseUInt(token->ToString());
        if (!u) return std::unexpected<int>(util::AllocateError(util::GetErrorMessage(u.error()) + "\n(file='" + fileName + "', line=" + std::to_string(line) + ")"));
        return u;
    }
    std::expected<std::int64_t, int> TokenToLong(std::int64_t pos) const override
    {
        auto rv = GetToken(pos);
        if (!rv) return std::unexpected<int>(rv.error());
        const TokenType* token = *rv;
        std::expected<std::int64_t, int> u = util::ParseLong(token->ToString());
        if (!u) return std::unexpected<int>(util::AllocateError(util::GetErrorMessage(u.error()) + "\n(file='" + fileName + "', line=" + std::to_string(line) + ")"));
        return u;
    }
    std::expected<std::uint64_t, int> TokenToULong(std::int64_t pos) const override
    {
        auto rv = GetToken(pos);
        if (!rv) return std::unexpected<int>(rv.error());
        const TokenType* token = *rv;
        std::expected<std::uint64_t, int> u = util::ParseULong(token->ToString());
        if (!u) return std::unexpected<int>(util::AllocateError(util::GetErrorMessage(u.error()) + "\n(file='" + fileName + "', line=" + std::to_string(line) + ")"));
        return u;
    }
    std::expected<float, int> TokenToFloat(std::int64_t pos) const override
    {
        auto rv = GetToken(pos);
        if (!rv) return std::unexpected<int>(rv.error());
        const TokenType* token = *rv;
        std::expected<float, int> u = util::ParseFloat(token->ToString());
        if (!u) return std::unexpected<int>(util::AllocateError(util::GetErrorMessage(u.error()) + "\n(file='" + fileName + "', line=" + std::to_string(line) + ")"));
        return u;
    }
    std::expected<double, int> TokenToDouble(std::int64_t pos) const override
    {
        auto rv = GetToken(pos);
        if (!rv) return std::unexpected<int>(rv.error());
        const TokenType* token = *rv;
        std::expected<double, int> u = util::ParseDouble(token->ToString());
        if (!u) return std::unexpected<int>(util::AllocateError(util::GetErrorMessage(u.error()) + "\n(file='" + fileName + "', line=" + std::to_string(line) + ")"));
        return u;
    }
    std::expected<CharT, int> TokenToCharLiteral(std::int64_t pos) const override
    {
        auto rv = GetToken(pos);
        if (!rv) return std::unexpected<int>(rv.error());
        const TokenType* token = *rv;
        std::expected<CharT, int> u = util::ParseCharLiteral(token->ToString());
        if (!u) return std::unexpected<int>(util::AllocateError(util::GetErrorMessage(u.error()) + "\n(file='" + fileName + "', line=" + std::to_string(line) + ")"));
        return u;
    }
    std::expected<std::basic_string<CharT>, int> TokenToStringLiteral(std::int64_t pos) const override
    {
        auto rv = GetToken(pos);
        if (!rv) return std::unexpected<int>(rv.error());
        const TokenType* token = *rv;
        std::expected<std::basic_string<CharT>, int> u = util::ParseStringLiteral(token->ToString());
        if (!u) return std::unexpected<int>(util::AllocateError(util::GetErrorMessage(u.error()) + "\n(file='" + fileName + "', line=" + std::to_string(line) + ")"));
        return u;
    }
    const std::string& FileName() const override
    {
        return fileName;
    }
    int File() const override
    {
        return file;
    }
    void SetFile(int file_)
    {
        file = file_;
    }
    int Line() const override
    {
        return line;
    }
    void SetLine(std::int32_t line_) override
    {
        line = line_;
    }
    soul::lexer::ClassMap<CharT>* GetClassMap() const override
    {
        return classMap;
    }
    void SetClassMap(soul::lexer::ClassMap<CharT>* classMap_) override
    {
        classMap = classMap_;
    }
    soul::ast::common::TokenCollection* GetTokenCollection() const override
    {
        return tokenCollection;
    }
    void SetTokenCollection(soul::ast::common::TokenCollection* tokenCollection_) override
    {
        tokenCollection = tokenCollection_;
    }
    KeywordMap<CharT>* GetKeywordMap() const override
    {
        return keywordMap;
    }
    void SetKeywordMap(KeywordMap<CharT>* keywordMap_) override
    {
        keywordMap = keywordMap_;
    }
    std::map<std::int64_t, std::string>* GetRuleNameMapPtr() const override
    {
        return ruleNameMapPtr;
    }
    void SetRuleNameMapPtr(std::map<std::int64_t, std::string>* ruleNameMapPtr_) override
    {
        ruleNameMapPtr = ruleNameMapPtr_;
    }
    inline LexerFlags Flags() const { return flags; }
    inline bool GetFlag(LexerFlags flag) const { return (flags & flag) != LexerFlags::none; }
    inline void SetFlag(LexerFlags flag) { flags = flags | flag; }
    inline void ResetFlag(LexerFlags flag) { flags = flags & ~flag; }
    inline void PushRule(std::int64_t ruleId)
    {
        ruleContext.push_back(ruleId);
    }
    inline void PopRule()
    {
        ruleContext.pop_back();
    }
    std::int64_t GetKeywordToken(const Lexeme<CharT>& lexeme) const override
    {
        if (keywordMap)
        {
            return keywordMap->GetKeywordToken(lexeme);
        }
        else
        {
            return soul::lexer::INVALID_TOKEN;
        }
    }
    void Retract() override
    {
        token.match.end = pos;
    }
    soul::lexer::Token<CharT, LexerBase<CharT>>& CurrentToken() override
    {
        return token;
    }
    void EraseTail() override
    {
        tokens.erase(current + 1, tokens.end());
    }
    const Lexeme<CharT>& CurrentLexeme() const override
    {
        return lexeme;
    }
    Lexeme<CharT>& CurrentLexeme() override
    {
        return lexeme;
    }
    std::string GetTokenName(std::int64_t tokenID) const
    {
        soul::ast::common::TokenCollection* tokenCollection = GetTokenCollection();
        auto token = tokenCollection->GetToken(tokenID);
        if (token)
        {
            return token->Name();
        }
        else
        {
            return "<unknown token>";
        }
    }
    std::string GetTokenInfo(std::int64_t tokenID) const
    {
        soul::ast::common::TokenCollection* tokenCollection = GetTokenCollection();
        auto token = tokenCollection->GetToken(tokenID);
        if (token)
        {
            return token->Info();
        }
        else
        {
            return "<unknown token>";
        }
    }
    inline int GetLine(std::int64_t pos) const
    {
        return pos >> 32;
    }
    std::expected<soul::ast::SourcePos, int> GetSourcePos(std::int64_t pos) const
    {
        const CharT* s = start;
        int line = GetLine(pos);
        if (line < lineStarts.size())
        {
            s = lineStarts[line];
        }
        auto rv = GetToken(pos);
        if (!rv) return std::unexpected<int>(rv.error());
        const TokenType* token = *rv;
        int col = static_cast<int>(token->match.begin - s + 1);
        return soul::ast::SourcePos(pos, file, line, col);
    }
    std::expected<std::string, int> ErrorLines(std::int64_t pos) const override
    {
        auto rv = GetToken(pos);
        if (!rv) return std::unexpected<int>(rv.error());
        const TokenType* token = *rv;
        std::basic_string<CharT> lines;
        const CharT* lineStart = LineStart(start, token->match.begin);
        const CharT* lineEnd = LineEnd(end, token->match.end);
        if (token->match.begin > lineStart)
        {
            lines.append(std::basic_string<CharT>(lineStart, token->match.begin));
        }
        lines.append(token->match.ToString());
        if (lineEnd > token->match.end)
        {
            lines.append(std::basic_string<CharT>(token->match.end, lineEnd));
        }
        lines.append(1, '\n');
        if (token->match.begin > lineStart)
        {
            lines.append(token->match.begin - lineStart, ' ');
        }
        lines.append(std::max(static_cast<std::int64_t>(1), token->match.end - token->match.begin), '^');
        if (lineEnd > token->match.end)
        {
            lines.append(lineEnd - token->match.end, ' ');
        }
        return util::ToUtf8(lines);
    }
    std::unexpected<int> ExpectationFailure(std::int64_t pos, const std::string& name)
    {
        std::expected<soul::ast::SourcePos, int> srv = GetSourcePos(pos);
        if (!srv) return std::unexpected<int>(srv.error());
        soul::ast::SourcePos sourcePos = *srv;
        std::string parserStateStr = GetParserStateStr();
        std::expected<std::string, int> rv = ErrorLines(pos);
        if (!rv) return std::unexpected<int>(rv.error());
        std::string errorMessage = "parsing error at '" + fileName + ":" + std::to_string(sourcePos.line) + "': " + name + " expected:\n" + *rv + parserStateStr;
        return std::unexpected<int>(util::AllocateError(errorMessage));
    }
    std::string GetParserStateStr() const
    {
        std::string parserStateStr;
        int n = static_cast<int>(farthestRuleContext.size());
        if (ruleNameMapPtr && n > 0)
        {
            parserStateStr.append("\nParser state:\n");
            for (int i = 0; i < n; ++i)
            {
                std::int64_t ruleId = farthestRuleContext[i];
                auto it = (*ruleNameMapPtr).find(ruleId);
                if (it != (*ruleNameMapPtr).cend())
                {
                    std::string ruleName = it->second;
                    parserStateStr.append(ruleName.append("\n"));
                }
            }
        }
        return parserStateStr;
    }
    std::expected<std::string, int> GetError(std::int64_t pos) const
    {
        std::string parserStateStr = GetParserStateStr();
        auto el = ErrorLines(pos);
        if (!el) return el;
        return "parsing error at '" + fileName + ":" + std::to_string(GetLine(pos)) + "':\n" + *el + parserStateStr;
    }
    std::unexpected<int> FarthestError()
    {
        std::cout.flush();
        parsing_error_thrown = true;
        auto err = GetError(farthestPos);
        if (!err) return std::unexpected<int>(err.error());
        return std::unexpected<int>(util::AllocateError(*err));
    }
    inline void SetLog(ParsingLog* log_)
    {
        log = log_;
    }
    inline ParsingLog* Log() const
    {
        return log;
    }
    std::expected<std::string, int> RestOfLine(int maxLineLength) const
    {
        std::expected<std::string, int> rv = util::ToUtf8(current->match.ToString());
        if (!rv) return rv;
        std::string restOfLine = *rv;
        rv = ToString(current->match.end, pos);
        if (!rv) return rv;
        restOfLine.append(*rv);
        rv = ToString(pos, LineEnd(end, pos));
        if (!rv) return rv;
        restOfLine.append(*rv);
        if (maxLineLength != 0)
        {
            restOfLine = restOfLine.substr(0, maxLineLength);
        }
        return std::expected<std::string, int>(restOfLine);
    }
    std::vector<int> GetLineStartIndeces() const override
    {
        std::vector<int> lineStartIndeces;
        for (int i = 0; i < lineStarts.size(); ++i)
        {
            lineStartIndeces.push_back(static_cast<int>(lineStarts[i] - start));
        }
        return lineStartIndeces;
    }
    soul::lexer::Variables* GetVariables() const override
    {
        return const_cast<soul::lexer::Variables*>(static_cast<const soul::lexer::Variables*>(&vars));
    }
    inline const CharT* Start() const
    {
        return start;
    }
    inline const CharT* Pos() const
    {
        return pos;
    }
    void SetPos(const CharT* pos_) override
    {
        pos = pos_;
    }
    const CharT* End() const override
    {
        return end;
    }
    inline const std::vector<soul::lexer::Token<CharT, LexerBase<CharT>>>& Tokens() const
    {
        return tokens;
    }
    inline std::vector<soul::lexer::Token<CharT, LexerBase<CharT>>> ReleaseTokens()
    {
        return std::move(tokens);
    }
    void SetCurrentMatchEnd(const CharT* end) override
    {
        current->match.end = end;
    }
    std::expected<bool, int> Increment() override
    {
        return ++*this;
    }
    void MoveToEnd() override
    {
        TokenType endToken(END_TOKEN, this);
        endToken.match.begin = end;
        endToken.match.end = end;
        tokens.push_back(endToken);
        current = tokens.end() - 1;
    }
    void BeginRecordedParse(const soul::ast::lexer::pos::pair::LexerPosPair& lexerPosPair) override
    {
        PushState();
        if (tokens.empty() || tokens.back().id != END_TOKEN)
        {
            TokenType endToken(END_TOKEN, this);
            endToken.match.begin = end;
            endToken.match.end = end;
            tokens.push_back(endToken);
        }
        recordedPosPair = lexerPosPair;
        SetPos(recordedPosPair.start);
        SetFlag(LexerFlags::recordedParse);
    }
    void EndRecordedParse() override
    {
        PopState();
    }
    inline void SetPPHook(PPHook ppHook_)
    {
        ppHook = ppHook_;
    }
    void PreprocessCurrentToken() override
    {
        if (ppHook)
        {
            ppHook(this, &token);
        }
    }
    inline void PushState()
    {
        stateStack.push(GetState());
    }
    inline void PopState()
    {
        SetState(stateStack.top());
        stateStack.pop();
    }
    LexerState<CharT, LexerBase<CharT>> GetState()
    {
        LexerState<CharT, LexerBase<CharT>> state(this);
        state.token = token;
        state.line = line;
        state.lexeme = lexeme;
        state.pos = pos;
        state.tokens = tokens;
        state.flags = flags;
        state.recordedPosPair = recordedPosPair;
        state.farthestPos = farthestPos;
        state.ruleContext = ruleContext;
        state.farthestRuleContext = farthestRuleContext;
        state.currentPos = GetPos();
        return state;
    }
    void SetState(const LexerState<CharT, LexerBase<CharT>>& state)
    {
        token = state.token;
        line = state.line;
        lexeme = state.lexeme;
        pos = state.pos;
        tokens = state.tokens;
        flags = state.flags;
        recordedPosPair = state.recordedPosPair;
        farthestPos = state.farthestPos;
        ruleContext = state.ruleContext;
        farthestRuleContext = state.farthestRuleContext;
        SetPos(state.currentPos);
    }
    inline void Skip(bool skip_)
    {
        skip = skip_;
        current = tokens.end();
    }
    inline bool Skipping() const
    {
        return skip;
    }
    inline void SetCommentTokenId(std::int64_t commentTokenId_)
    {
        commentTokenId = commentTokenId_;
    }
    inline void SetBlockCommentStates(const std::set<int>& blockCommentStates_)
    {
        blockCommentStates = blockCommentStates_;
    }
    inline const std::set<int>& BlockCommentStates() const
    {
        return blockCommentStates;
    }
    TokenLineType TokenizeLine(const std::basic_string<CharT>& line, int lineNumber, int startState)
    {
        TokenLineType tokenLine;
        pos = line.c_str();
        end = line.c_str() + line.length();
        tokenLine.startState = startState;
        lexeme.begin = pos;
        lexeme.end = end;
        token.match = lexeme;
        token.id = soul::lexer::INVALID_TOKEN;
        token.line = lineNumber;
        int state = startState;
        int prevState = 0;
        int prevPrevState = 0;
        bool cont = false;
        while (pos != end)
        {
            CharT c = *pos;
            if (state == 0)
            {
                lexeme.begin = pos;
                token.id = soul::lexer::INVALID_TOKEN;
                token.line = lineNumber;
            }
            lexeme.end = pos + 1;
            prevPrevState = prevState;
            prevState = state;
            state = Machine::NextState(state, c, *static_cast<LexerBase<CharT>*>(this));
            if (state == -1)
            {
                if (prevState == 0)
                {
                    break;
                }
                state = 0;
                pos = token.match.end;
                tokenLine.tokens.push_back(token);
                if (pos + 1 < end && *pos == '\"' && *(pos + 1) == '\\' && prevPrevState == 13 && prevState == 71)
                {
                    TokenType tok(this);
                    tok.match.begin = pos;
                    tok.match.end = pos + 2;
                    tokenLine.tokens.push_back(tok);
                    pos += 2;
                }
                lexeme.begin = lexeme.end;
            }
            else
            {
                ++pos;
            }
        }
        if (state != 0 && state != -1)
        {
            state = Machine::NextState(state, '\r', *static_cast<LexerBase<CharT>*>(this));
        }
        if (state != 0 && state != -1)
        {
            state = Machine::NextState(state, '\n', *static_cast<LexerBase<CharT>*>(this));
        }
        if (state != 0 && state != -1)
        {
            if (blockCommentStates.find(state) != blockCommentStates.cend())
            {
                token.id = commentTokenId;
                token.match.end = end;
                tokenLine.tokens.push_back(token);
                tokenLine.endState = state;
                return tokenLine;
            }
        }
        if (lexeme.begin != lexeme.end)
        {
            token.match = lexeme;
            tokenLine.tokens.push_back(token);
        }
        if (state == -1)
        {
            state = 0;
        }
        tokenLine.endState = state;
        return tokenLine;
    }
private:
    std::expected<bool, int> NextToken()
    {
        int state = 0;
        while (true)
        {
            CharT c = separatorChar;
            if (pos != end)
            {
                c = *pos;
            }
            else if (c == '\0')
            {
                break;
            }
            if (state == 0)
            {
                lexeme.begin = pos;
                token.id = soul::lexer::INVALID_TOKEN;
                token.line = line;
            }
            if (pos == end)
            {
                lexeme.end = end;
            }
            else
            {
                lexeme.end = pos + 1;
            }
            state = Machine::NextState(state, c, *static_cast<LexerBase<CharT>*>(this));
            if (state == -1)
            {
                if (token.id == soul::lexer::CONTINUE_TOKEN)
                {
                    if (pos == end)
                    {
                        break;
                    }
                    else
                    {
                        pos = token.match.end;
                    }
                    state = 0;
                    continue;
                }
                else if (token.id == soul::lexer::INVALID_TOKEN)
                {
                    if (pos == end)
                    {
                        break;
                    }
                    else
                    {
                        auto u = util::ToUtf8(std::u32string(1, c));
                        if (!u) return std::unexpected<int>(u.error());
                        return std::unexpected<int>(util::AllocateError(
                            "soul::lexer::Lexer::NextToken(): error: invalid character '" + *u + "' in file '" + fileName + "' at line " + std::to_string(line)));
                    }
                }
                else
                {
                    if (!skip)
                    {
                        tokens.push_back(token);
                        current = tokens.end() - 1;
                        pos = token.match.end;
                        return std::expected<bool, int>(true);
                    }
                    else
                    {
                        pos = token.match.end;
                        return std::expected<bool, int>(true);
                    }
                }
            }
            if (c == '\n' && countLines)
            {
                ++line;
            }
            ++pos;
        }
        token.id = soul::lexer::INVALID_TOKEN;
        state = Machine::NextState(state, '\0', *static_cast<LexerBase<CharT>*>(this));
        std::int64_t p = -1;
        if (token.id != soul::lexer::INVALID_TOKEN && token.id != soul::lexer::CONTINUE_TOKEN)
        {
            tokens.push_back(token);
            current = tokens.end() - 1;
            p = GetPos();
        }
        TokenType endToken(soul::lexer::END_TOKEN, this);
        endToken.match.begin = end;
        endToken.match.end = end;
        tokens.push_back(endToken);
        if (p == -1)
        {
            current = tokens.end() - 1;
            p = GetPos();
        }
        SetPos(p);
        return std::expected<bool, int>(true);
    }
    void ComputeLineStarts()
    {
        lineStarts.push_back(pos);
        const CharT* p = pos;
        bool startOfLine = true;
        while (p != end)
        {
            if (startOfLine)
            {
                lineStarts.push_back(p);
            }
            startOfLine = *p == '\n';
            ++p;
        }
        lineStarts.push_back(end);
    }
    LexerFlags flags;
    soul::ast::lexer::pos::pair::LexerPosPair recordedPosPair;
    CharT separatorChar;
    std::vector<soul::lexer::Token<CharT, LexerBase<CharT>>> tokens;
    std::vector<soul::lexer::Token<CharT, LexerBase<CharT>>>::iterator current;
    soul::lexer::Token<CharT, LexerBase<CharT>> token;
    Lexeme<CharT> lexeme;
    std::int32_t file;
    std::int32_t line;
    const CharT* start;
    const CharT* end;
    const CharT* pos;
    std::string fileName;
    bool countLines;
    soul::lexer::ClassMap<CharT>* classMap;
    soul::ast::common::TokenCollection* tokenCollection;
    KeywordMap<CharT>* keywordMap;
    std::int64_t farthestPos;
    std::vector<std::int64_t> ruleContext;
    std::vector<std::int64_t> farthestRuleContext;
    std::vector<const CharT*> lineStarts;
    std::map<std::int64_t, std::string>* ruleNameMapPtr;
    ParsingLog* log;
    Machine::Variables vars;
    LexerState<CharT, LexerBase<CharT>> state;
    std::stack<LexerState<CharT, LexerBase<CharT>>> stateStack;
    PPHook ppHook;
    bool skip;
    std::int64_t commentTokenId;
    std::set<int> blockCommentStates;
};

inline std::string GetEndTokenInfo()
{
    return "end-of-file";
}

template<typename Lexer>
void WriteBeginRuleToLog(Lexer& lexer, const std::string& ruleName)
{
    lexer.Log()->WriteBeginRule(ruleName);
    lexer.Log()->IncIndent();
    lexer.Log()->WriteTry(lexer.RestOfLine(lexer.Log()->MaxLineLength()));
    lexer.Log()->IncIndent();
}

template<typename Lexer>
void WriteSuccessToLog(Lexer& lexer, std::int64_t matchPos, const std::string& ruleName)
{
    lexer.Log()->DecIndent();
    lexer.Log()->WriteSuccess(util::ToUtf8(lexer.GetToken(matchPos).ToString()));
    lexer.Log()->DecIndent();
    lexer.Log()->WriteEndRule(ruleName);
}

template<typename Lexer>
void WriteFailureToLog(Lexer& lexer, const std::string& ruleName)
{
    lexer.Log()->DecIndent();
    lexer.Log()->WriteFail();
    lexer.Log()->DecIndent();
    lexer.Log()->WriteEndRule(ruleName);
}

} // namespace soul::lexer
