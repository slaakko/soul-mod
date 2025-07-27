// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul_expected.rex.match;

import util_expected;
import soul_expected.rex.lexer;
import soul_expected.rex.parser;
import soul_expected.rex.algorithm;
import soul_expected.rex.spg.rules;

namespace soul_expected::rex {

std::u32string MakeRegularExpressionPatternFromFilePattern(const std::u32string& filePattern)
{
    std::u32string pattern;
    for (char32_t c : filePattern)
    {
        switch (c)
        {
            case '.': pattern.append(U"\\."); break;
            case '*': pattern.append(U".*"); break;
            case '?': pattern.append(U"."); break;
            default: pattern.append(1, c); break;
        }
    }
    return pattern;
}

std::expected<bool, int> FilePatternMatch(const std::u32string& filePath, const std::u32string& filePattern)
{
    return PatternMatch(filePath, MakeRegularExpressionPatternFromFilePattern(filePattern));
}

std::expected<bool, int> FilePatternMatch(const std::string& filePath, const std::string& filePattern)
{
    auto uf = util::ToUtf32(filePath);
    if (!uf) return std::unexpected<int>(uf.error());
    auto up = util::ToUtf32(filePattern);
    if (!up) return std::unexpected<int>(up.error());
    return FilePatternMatch(*uf, *up);
}

std::expected<bool, int> PatternMatch(const std::u32string& str, const std::u32string& regularExpressionPattern)
{
    soul_expected::rex::context::Context context;
    auto p = CompileRegularExpressionPattern(context, regularExpressionPattern);
    if (!p) return std::unexpected<int>(p.error());
    soul_expected::rex::nfa::Nfa nfa = *p;
    return PatternMatch(str, nfa);
}

std::expected<bool, int>  PatternMatch(const std::string& str, const std::string& regularExpressionPattern)
{
    auto s = util::ToUtf32(str);
    if (!s) return std::unexpected<int>(s.error());
    auto p = util::ToUtf32(regularExpressionPattern);
    if (!p) return std::unexpected<int>(p.error());
    return PatternMatch(*s, *p);
}

std::expected<bool, int>  PatternMatch(const std::string& str, soul_expected::rex::nfa::Nfa& nfa)
{
    auto u = util::ToUtf32(str);
    if (!u) return std::unexpected<int>(u.error());
    return PatternMatch(*u, nfa);
}

std::expected<soul_expected::rex::nfa::Nfa, int> CompileRegularExpressionPattern(soul_expected::rex::context::Context& context, const std::u32string& regularExpressionPattern)
{
    auto lx = soul_expected::rex::lexer::MakeLexer(regularExpressionPattern.c_str(), regularExpressionPattern.c_str() + regularExpressionPattern.length(), "");
    if (!lx) return std::unexpected<int>(lx.error());
    auto lexer = std::move(*lx);
    using LexerType = decltype(lexer);
    lexer.SetRuleNameMapPtr(soul_expected::rex::spg::rules::GetRuleNameMapPtr());
    return soul_expected::rex::parser::RexParser<LexerType>::Parse(lexer, &context);
}

std::expected<soul_expected::rex::nfa::Nfa, int> CompileRegularExpressionPattern(soul_expected::rex::context::Context& context, const std::string& regularExpressionPattern)
{
    auto p = util::ToUtf32(regularExpressionPattern);
    if (!p) return std::unexpected<int>(p.error());
    return CompileRegularExpressionPattern(context, *p);
}

std::expected<soul_expected::rex::nfa::Nfa, int> CompileFilePattern(soul_expected::rex::context::Context& context, const std::u32string& filePattern)
{
    return CompileRegularExpressionPattern(context, MakeRegularExpressionPatternFromFilePattern(filePattern));
}

bool PatternMatch(const std::u32string& str, soul_expected::rex::nfa::Nfa& nfa)
{
    return soul_expected::rex::algorithm::Match(nfa, str);
}

std::expected<soul_expected::rex::nfa::Nfa, int> CompileFilePattern(soul_expected::rex::context::Context& context, const std::string& filePattern)
{
    auto p = util::ToUtf32(filePattern);
    if (!p) return std::unexpected<int>(p.error());
    return CompileFilePattern(context, *p);
}

std::expected<bool, int> FilePatternMatch(const std::string& lexerModuleFileName, const std::u32string& filePath, const std::u32string& filePattern)
{
    return PatternMatch(lexerModuleFileName, filePath, MakeRegularExpressionPatternFromFilePattern(filePattern));
}

std::expected<bool, int> FilePatternMatch(const std::string& lexerModuleFileName, const std::string& filePath, const std::string& filePattern)
{
    auto u = util::ToUtf32(filePath);
    if (!u) return std::unexpected<int>(u.error());
    auto p = util::ToUtf32(filePattern);
    if (!p) return std::unexpected<int>(p.error());
    return FilePatternMatch(lexerModuleFileName, *u, *p);
}

std::expected<bool, int> PatternMatch(const std::string& lexerModuleFileName, const std::u32string& str, const std::u32string& regularExpressionPattern)
{
    soul_expected::rex::context::Context context;
    auto p = CompileRegularExpressionPattern(lexerModuleFileName, context, regularExpressionPattern);
    if (!p) return std::unexpected<int>(p.error());
    soul_expected::rex::nfa::Nfa nfa = *p;
    return PatternMatch(str, nfa);
}

std::expected<bool, int> PatternMatch(const std::string& lexerModuleFileName, const std::string& str, const std::string& regularExpressionPattern)
{
    auto s = util::ToUtf32(str);
    if (!s) return std::unexpected<int>(s.error());
    auto p = util::ToUtf32(regularExpressionPattern);
    if (!p) return std::unexpected<int>(p.error());
    return PatternMatch(lexerModuleFileName, *s, *p);
}

std::expected<soul_expected::rex::nfa::Nfa, int> CompileRegularExpressionPattern(const std::string& lexerModuleFileName, util::ResourceFlags resourceFlags,
    soul_expected::rex::context::Context& context, const std::u32string& regularExpressionPattern)
{
    auto lx = soul_expected::rex::lexer::MakeLexer(lexerModuleFileName, resourceFlags,
        regularExpressionPattern.c_str(), regularExpressionPattern.c_str() + regularExpressionPattern.length(), "");
    if (!lx) return std::unexpected<int>(lx.error());
    auto lexer = std::move(*lx);
    using LexerType = decltype(lexer);
    lexer.SetRuleNameMapPtr(soul_expected::rex::spg::rules::GetRuleNameMapPtr());
    return soul_expected::rex::parser::RexParser<LexerType>::Parse(lexer, &context);
}

std::expected<soul_expected::rex::nfa::Nfa, int> CompileRegularExpressionPattern(const std::string& lexerModuleFileName, soul_expected::rex::context::Context& context, const std::u32string& regularExpressionPattern)
{
    return CompileRegularExpressionPattern(lexerModuleFileName, util::ResourceFlags::none, context, regularExpressionPattern);
}

std::expected<soul_expected::rex::nfa::Nfa, int> CompileRegularExpressionPattern(const std::string& lexerModuleFileName, soul_expected::rex::context::Context& context, const std::string& regularExpressionPattern)
{
    auto p = util::ToUtf32(regularExpressionPattern);
    if (!p) return std::unexpected<int>(p.error());
    return CompileRegularExpressionPattern(lexerModuleFileName, context, *p);
}

std::expected<soul_expected::rex::nfa::Nfa, int> CompileFilePattern(const std::string& lexerModuleFileName, soul_expected::rex::context::Context& context, const std::u32string& filePattern)
{
    return CompileRegularExpressionPattern(lexerModuleFileName, context, MakeRegularExpressionPatternFromFilePattern(filePattern));
}

std::expected<soul_expected::rex::nfa::Nfa, int> CompileFilePattern(const std::string& lexerModuleFileName, soul_expected::rex::context::Context& context, const std::string& filePattern)
{
    auto p = util::ToUtf32(filePattern);
    if (!p) return std::unexpected<int>(p.error());
    return CompileFilePattern(lexerModuleFileName, context, *p);
}

} // namespace soul_expected::rex
