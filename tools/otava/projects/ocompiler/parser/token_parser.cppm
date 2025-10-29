// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.token.parser;

import std;
import soul.ast.source.pos;
import otava.ast.identifier;
import otava.ast.literal;
import soul.lexer.token;
import soul.lexer.base;

export namespace otava::token::parser {

using Suffix = otava::ast::Suffix;
using EncodingPrefix = otava::ast::EncodingPrefix;
using Base = otava::ast::Base;

Suffix ParseIntegerSuffix(const char32_t*& p, const char32_t* e);
Suffix ParseFloatingSuffix(const char32_t*& p, const char32_t* e);
EncodingPrefix ParseEncodingPrefix(const char32_t*& p, const char32_t* e);
bool IsHexChar(char32_t c);
std::uint64_t ParseHexChar(char32_t c);
char32_t ParseEscape(const char32_t*& p, const char32_t* e, bool& valid);
std::expected<otava::ast::IntegerLiteralNode*, int> ParseIntegerLiteral(const soul::ast::SourcePos& sourcePos, const std::string& fileName,
    const soul::lexer::Token<char32_t, soul::lexer::LexerBase<char32_t>>& token);
std::expected<otava::ast::FloatingLiteralNode*, int> ParseFloatingLiteral(const soul::ast::SourcePos& sourcePos, const std::string& fileName,
    const soul::lexer::Token<char32_t, soul::lexer::LexerBase<char32_t>>& token);
std::expected<otava::ast::CharacterLiteralNode*, int> ParseCharacterLiteral(const soul::ast::SourcePos& sourcePos, const std::string& fileName,
    const soul::lexer::Token<char32_t, soul::lexer::LexerBase<char32_t>>& token);
std::expected<otava::ast::RawStringLiteralNode*, int> ParseRawStringLiteral(const soul::ast::SourcePos& sourcePos, soul::lexer::LexerBase<char32_t>& lexer);
std::expected<otava::ast::StringLiteralNode*, int> ParseStringLiteral(const soul::ast::SourcePos& sourcePos, const std::string& fileName,
    const soul::lexer::Token<char32_t, soul::lexer::LexerBase<char32_t>>& token);
std::expected<otava::ast::IdentifierNode*, int> ParseIdentifier(const soul::ast::SourcePos& sourcePos, const std::string& fileName,
    const soul::lexer::Token<char32_t, soul::lexer::LexerBase<char32_t>>& token);

} // namespace otava::token::parser
