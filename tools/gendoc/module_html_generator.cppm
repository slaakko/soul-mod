// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module gendoc.module_html_generator;

import std;
import otava.symbols;

export namespace gendoc {

class Project;

void GenerateModuleHtml(Project* project, const std::string& rootDir, otava::symbols::Module* module, otava::symbols::ModuleMapper& moduleMapper, Project* nsProject);

} // namespace gendoc
