// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul_expected.rex.match;

import std;
import soul_expected.rex.nfa;
import soul_expected.rex.context;
import util_expected;

export namespace soul_expected::rex {

std::expected<bool, int> FilePatternMatch(const std::u32string& filePath, const std::u32string& filePattern);

std::expected<bool, int> FilePatternMatch(const std::string& filePath, const std::string& filePattern);

std::expected<bool, int> PatternMatch(const std::u32string& str, const std::u32string& regularExpressionPattern);

std::expected<bool, int> PatternMatch(const std::string& str, const std::string& regularExpressionPattern);

bool PatternMatch(const std::u32string& str, soul_expected::rex::nfa::Nfa& nfa);

std::expected<bool, int> PatternMatch(const std::string& str, soul_expected::rex::nfa::Nfa& nfa);

std::expected<soul_expected::rex::nfa::Nfa, int> CompileRegularExpressionPattern(soul_expected::rex::context::Context& context, const std::u32string& regularExpressionPattern);

std::expected<soul_expected::rex::nfa::Nfa, int> CompileRegularExpressionPattern(soul_expected::rex::context::Context& context, const std::string& regularExpressionPattern);

std::expected<soul_expected::rex::nfa::Nfa, int> CompileFilePattern(soul_expected::rex::context::Context& context, const std::u32string& filePattern);

std::expected<soul_expected::rex::nfa::Nfa, int> CompileFilePattern(soul_expected::rex::context::Context& context, const std::string& filePattern);

std::expected<bool, int> FilePatternMatch(const std::string& lexerModuleFileName, const std::u32string& filePath, const std::u32string& filePattern);

std::expected<bool, int> FilePatternMatch(const std::string& lexerModuleFileName, const std::string& filePath, const std::string& filePattern);

std::expected<bool, int> PatternMatch(const std::string& lexerModuleFileName, const std::u32string& str, const std::u32string& regularExpressionPattern);

std::expected<bool, int> PatternMatch(const std::string& lexerModuleFileName, const std::string& str, const std::string& regularExpressionPattern);

std::expected<soul_expected::rex::nfa::Nfa, int> CompileRegularExpressionPattern(const std::string& lexerModuleFileName, util::ResourceFlags resourceFlags,
    soul_expected::rex::context::Context& context, const std::u32string& regularExpressionPattern);

std::expected<soul_expected::rex::nfa::Nfa, int> CompileRegularExpressionPattern(const std::string& lexerModuleFileName, soul_expected::rex::context::Context& context, const std::u32string& regularExpressionPattern);

std::expected<soul_expected::rex::nfa::Nfa, int> CompileRegularExpressionPattern(const std::string& lexerModuleFileName, soul_expected::rex::context::Context& context, const std::string& regularExpressionPattern);

std::expected<soul_expected::rex::nfa::Nfa, int> CompileFilePattern(const std::string& lexerModuleFileName, soul_expected::rex::context::Context& context, const std::u32string& filePattern);

std::expected<soul_expected::rex::nfa::Nfa, int> CompileFilePattern(const std::string& lexerModuleFileName, soul_expected::rex::context::Context& context, const std::string& filePattern);

} // namespace soul_expected::rex