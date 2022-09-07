// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.parser.token;

import std.core;
import soul.ast.source.pos;
import soul.cpp20.ast.identifier;
import soul.cpp20.ast.literal;
import soul.lexer.token;
import soul.lexer.base;

export namespace soul::cpp20::parser::token {

using Suffix = soul::cpp20::ast::Suffix;
using EncodingPrefix = soul::cpp20::ast::EncodingPrefix;
using Base = soul::cpp20::ast::Base;

Suffix ParseIntegerSuffix(const char32_t*& p, const char32_t* e);
Suffix ParseFloatingSuffix(const char32_t*& p, const char32_t* e);
EncodingPrefix ParseEncodingPrefix(const char32_t*& p, const char32_t* e);
bool IsHexChar(char32_t c);
uint64_t ParseHexChar(char32_t c);
char32_t ParseEscape(const char32_t*& p, const char32_t* e, bool& valid);
soul::cpp20::ast::IntegerLiteralNode* ParseIntegerLiteral(const soul::ast::SourcePos& sourcePos, const std::string& fileName,
    const soul::lexer::Token<char32_t, soul::lexer::LexerBase<char32_t>>& token);
soul::cpp20::ast::FloatingLiteralNode* ParseFloatingLiteral(const soul::ast::SourcePos& sourcePos, const std::string& fileName,
    const soul::lexer::Token<char32_t, soul::lexer::LexerBase<char32_t>>& token);
soul::cpp20::ast::CharacterLiteralNode* ParseCharacterLiteral(const soul::ast::SourcePos& sourcePos, const std::string& fileName,
    const soul::lexer::Token<char32_t, soul::lexer::LexerBase<char32_t>>& token);
soul::cpp20::ast::RawStringLiteralNode* ParseRawStringLiteral(const soul::ast::SourcePos& sourcePos, soul::lexer::LexerBase<char32_t>& lexer);
soul::cpp20::ast::StringLiteralNode* ParseStringLiteral(const soul::ast::SourcePos& sourcePos, const std::string& fileName,
    const soul::lexer::Token<char32_t, soul::lexer::LexerBase<char32_t>>& token);
soul::cpp20::ast::IdentifierNode* ParseIdentifier(const soul::ast::SourcePos& sourcePos, const std::string& fileName,
    const soul::lexer::Token<char32_t, soul::lexer::LexerBase<char32_t>>& token);

} // namespace soul::cpp20::parser::token
