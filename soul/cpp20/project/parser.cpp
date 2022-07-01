// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.project.parser;

import util;
import soul.cpp20.proj.lexer;
import soul.cpp20.proj.spg.rules;
import soul.cpp20.proj.parser;
import soul.cpp20.symbols;

namespace soul::cpp20::project::parser {

std::unique_ptr<soul::cpp20::proj::ast::Project> ParseProjectFile(const std::string& projectFilePath)
{
    std::string filePath = util::GetFullPath(projectFilePath);
    std::string content = util::ReadFile(filePath);
    std::u32string ucontent = util::ToUtf32(content);
    auto lexer = soul::cpp20::proj::lexer::MakeLexer(ucontent.c_str(), ucontent.c_str() + ucontent.length(), filePath);
    lexer.SetRuleNameMapPtr(soul::cpp20::proj::spg::rules::GetRuleNameMapPtr());
    return soul::cpp20::proj::parser::ProjectParser<decltype(lexer)>::Parse(lexer);
}

} // namespace soul::cpp20::project::parser
