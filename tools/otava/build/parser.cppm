// =================================
// Copyright (c) 2023 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.build.parser;

import std.core;

export namespace otava::build {

class Project;
class Solution;

std::unique_ptr<Project> ParseProjectFile(const std::string& projectFilePath);
std::unique_ptr<Solution> ParseSolutionFile(const std::string& solutionFilePath);

} // namespace otava::build
