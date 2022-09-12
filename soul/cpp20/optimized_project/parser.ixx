// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.project.parser;

import std.core;
import soul.cpp20.proj.ast;

export namespace soul::cpp20::project::parser {

std::unique_ptr<soul::cpp20::proj::ast::Project> ParseProjectFile(const std::string& projectFilePath);
std::unique_ptr<soul::cpp20::proj::ast::Solution> ParseSolutionFile(const std::string& solutionFilePath);

} // namespace soul::cpp20::project::parser
