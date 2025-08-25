// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul_expected.lexer.test;

import std;
import util_expected;
import soul_expected.lexer.base;
import soul_expected.lexer.token;
import soul_expected.ast.slg;
import soul_expected.ast.common;

export namespace soul::lexer {

template<typename Lexer>
std::expected<bool, int> TestLexer(Lexer& lexer, util::CodeFormatter& formatter)
{
    bool succeeded = false;
    soul_expected::ast::common::TokenCollection* tokens = lexer.GetTokenCollection();
    ++lexer;
    while (*lexer != soul_expected::lexer::END_TOKEN && *lexer != soul_expected::lexer::INVALID_TOKEN)
    {
        auto token = lexer.CurrentToken();
        auto tokenInfo = tokens->GetToken(token.id);
        if (tokenInfo)
        {
            std::expected<bool, int> rv = formatter.WriteLine(tokenInfo->Name() + "[" + util::ToUtf8(token.ToString()) + "]");
            if (!rv) return std::unexpected<int>(rv.error());
        }
        else
        {
            std::expected<bool, int> rv = formatter.WriteLine("<unknown token>");
            if (!rv) return std::unexpected<int>(rv.error());
        }
        ++lexer;
    }
    if (*lexer == soul_expected::lexer::END_TOKEN)
    {
        std::expected<bool, int> rv = formatter.WriteLine("success");
        if (!rv) return std::unexpected<int>(rv.error());
        succeeded = true;
    }
    else
    {
        std::expected<bool, int> rv = formatter.WriteLine("failure");
        if (!rv) return std::unexpected<int>(rv.error());
    }
    return std::expected<bool, int>(succeeded);
}

} // namespace soul::lexer
