// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module gendoc.project_html_generator;

import std;
import otava.symbols;

export namespace gendoc {

class Project;

void GenerateProjectHtml(Project* project, const std::string& rootDir, std::vector<otava::symbols::Module*>& modules);

} // namespace gendoc
