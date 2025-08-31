// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.lexer.base;

import std;
import soul.lexer.lexeme;
import soul.lexer.token;
import soul.lexer.keyword;
import soul.lexer.classmap;
import soul.lexer.variables;
import soul.ast.slg;
import soul.ast.common;
import soul.ast.lexer.pos.pair;
import soul.ast.span;

export namespace soul::lexer {

template<typename CharT>
class LexerBase
{
public:
    using Self = LexerBase<CharT>;
    using TokenType = soul::lexer::Token<CharT, Self>;
    virtual ~LexerBase() {}
    virtual void Retract() = 0;
    virtual std::int64_t GetKeywordToken(const Lexeme<CharT>& lexeme) const = 0;
    virtual void EraseTail() = 0;
    virtual TokenType& CurrentToken() = 0;
    virtual const Lexeme<CharT>& CurrentLexeme() const = 0;
    virtual Lexeme<CharT>& CurrentLexeme() = 0;
    virtual std::expected<soul::ast::Span, int> GetSpan() const = 0;
    virtual std::expected<soul::ast::Span, int> GetSpan(std::int64_t pos) const = 0;
    virtual std::expected<const TokenType*, int> GetToken(std::int64_t pos) const = 0;
    virtual std::expected<std::basic_string<CharT>, int> TokenToString(std::int64_t pos) const = 0;
    virtual std::expected<std::string, int> TokenToUtf8(std::int64_t pos) const = 0;
    virtual std::expected<std::int8_t, int> TokenToSByte(std::int64_t pos) const = 0;
    virtual std::expected<std::uint8_t, int> TokenToByte(std::int64_t pos) const = 0;
    virtual std::expected<std::int16_t, int> TokenToShort(std::int64_t pos) const = 0;
    virtual std::expected<std::uint16_t, int> TokenToUShort(std::int64_t pos) const = 0;
    virtual std::expected<std::int32_t, int> TokenToInt(std::int64_t pos) const = 0;
    virtual std::expected<std::uint32_t, int> TokenToUInt(std::int64_t pos) const = 0;
    virtual std::expected<std::int64_t, int> TokenToLong(std::int64_t pos) const = 0;
    virtual std::expected<std::uint64_t, int> TokenToULong(std::int64_t pos) const = 0;
    virtual std::expected<float, int> TokenToFloat(std::int64_t pos) const = 0;
    virtual std::expected<double, int> TokenToDouble(std::int64_t pos) const = 0;
    virtual std::expected<CharT, int> TokenToCharLiteral(std::int64_t pos) const = 0;
    virtual std::expected<std::basic_string<CharT>, int> TokenToStringLiteral(std::int64_t pos) const = 0;
    virtual const std::string& FileName() const = 0;
    virtual int File() const = 0;
    virtual int Line() const = 0;
    virtual void SetLine(std::int32_t line_) = 0;
    virtual soul::lexer::ClassMap<CharT>* GetClassMap() const = 0;
    virtual void SetClassMap(soul::lexer::ClassMap<CharT>* classMap) = 0;
    virtual Variables* GetVariables() const = 0;
    virtual std::vector<int> GetLineStartIndeces() const = 0;
    virtual soul::ast::common::TokenCollection* GetTokenCollection() const = 0;
    virtual void SetTokenCollection(soul::ast::common::TokenCollection* tokenCollection_) = 0;
    virtual KeywordMap<CharT>* GetKeywordMap() const = 0;
    virtual void SetKeywordMap(KeywordMap<CharT>* keywordMap_) = 0;
    virtual std::map<std::int64_t, std::string>* GetRuleNameMapPtr() const = 0;
    virtual void SetRuleNameMapPtr(std::map<std::int64_t, std::string>* ruleNameMapPtr) = 0;
    virtual std::expected<std::string, int> ErrorLines(std::int64_t pos) const = 0;
    virtual std::int64_t GetPos() const = 0;
    virtual const CharT* End() const = 0;
    virtual void SetPos(const CharT* p) = 0;
    virtual void SetCurrentMatchEnd(const CharT* end) = 0;
    virtual std::expected<bool, int> Increment() = 0;
    virtual void MoveToEnd() = 0;
    virtual void BeginRecordedParse(const soul::ast::lexer::pos::pair::LexerPosPair& lexerPosPair) = 0;
    virtual void EndRecordedParse() = 0;
    virtual void PreprocessCurrentToken() = 0;
    virtual void Skip(bool skip_) = 0;
    virtual bool Skipping() const = 0;
};

} // namespace soul::lexer
