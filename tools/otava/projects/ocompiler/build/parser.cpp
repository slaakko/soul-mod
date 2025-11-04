// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.build.parser;

import otava.project_lexer;
import otava.project_parser;
import otava.project_spg.rules;
import otava.solution_lexer;
import otava.solution_parser;
import otava.solution_spg.rules;
import otava.symbols.namespaces;
import otava.symbols.compound.type.symbol;
import otava.symbols.conversion.table;
import util.path;
import util.file.stream;
import util.unicode;

namespace otava::build {

std::expected<std::unique_ptr<Project>, int> ParseProjectFile(const std::string& projectFilePath)
{
    auto fp = util::GetFullPath(projectFilePath);
    if (!fp) return std::unexpected<int>(fp.error());
    std::string filePath = std::move(*fp);
    auto f = util::ReadFile(filePath);
    if (!f) return std::unexpected<int>(f.error());
    std::string content = std::move(*f);
    auto u = util::ToUtf32(content);
    if (!u) return std::unexpected<int>(u.error());
    std::u32string ucontent = std::move(*u);
    auto lxr = otava::project_lexer::MakeLexer(ucontent.c_str(), ucontent.c_str() + ucontent.length(), filePath);
    if (!lxr) return std::unexpected<int>(lxr.error());
    auto& lexer = *lxr;
    lexer.SetRuleNameMapPtr(otava::project_spg::rules::GetRuleNameMapPtr());
    using LexerType = decltype(lexer);
    return otava::project_parser::ProjectParser<LexerType>::Parse(lexer);
}

std::expected<std::unique_ptr<Solution>, int> ParseSolutionFile(const std::string& solutionFilePath)
{
    auto fp = util::GetFullPath(solutionFilePath);
    if (!fp) return std::unexpected<int>(fp.error());
    std::string filePath = std::move(*fp);
    auto f = util::ReadFile(filePath);
    if (!f) return std::unexpected<int>(f.error());
    std::string content = std::move(*f);
    auto u = util::ToUtf32(content);
    if (!u) return std::unexpected<int>(u.error());
    std::u32string ucontent = std::move(*u);
    auto lxr = otava::solution_lexer::MakeLexer(ucontent.c_str(), ucontent.c_str() + ucontent.length(), filePath);
    if (!lxr) return std::unexpected<int>(lxr.error());
    auto& lexer = *lxr;
    lexer.SetRuleNameMapPtr(otava::solution_spg::rules::GetRuleNameMapPtr());
    using LexerType = decltype(lexer);
    return otava::solution_parser::SolutionParser<LexerType>::Parse(lexer);
}

} // namespace otava::build
