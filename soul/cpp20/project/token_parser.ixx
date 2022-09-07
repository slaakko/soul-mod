// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.proj.parser.token;

import std.core;
import soul.lexer.base;
import soul.lexer.token;
import util.unicode;
import soul.cpp20.ast.error;

export namespace soul::cpp20::proj::parser::token {

template<typename Char>
std::string ParseFilePath(const std::string& fileName, const soul::lexer::Token<Char, soul::lexer::LexerBase<Char>>& token)
{
    std::u32string strValue;
    const Char* p = token.match.begin;
    const Char* e = token.match.end;
    if (p != e && *p == '<')
    {
        ++p;
    }
    while (p != e && *p != '>')
    {
        strValue.append(1, *p);
        ++p;
    }
    if (p != e && *p == '>')
    {
        ++p;
    }
    if (p != e)
    {
        soul::cpp20::ast::SetExceptionThrown();
        throw std::runtime_error("invalid file path at " + fileName + ":" + std::to_string(token.line) + " : '" + util::ToUtf8(token.match.ToString()) + "'");
    }
    return util::ToUtf8(strValue);
}

} // namespace soul::cpp20::proj::parser::token
