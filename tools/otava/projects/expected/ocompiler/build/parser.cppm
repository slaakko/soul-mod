// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.build.parser;

import std;
import otava.build_project;
import otava.build_solution;

export namespace otava::build {

std::expected<std::unique_ptr<Project>, int> ParseProjectFile(const std::string& projectFilePath);
std::expected<std::unique_ptr<Solution>, int> ParseSolutionFile(const std::string& solutionFilePath);

} // namespace otava::build
