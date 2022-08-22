// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module gendoc.module_html_generator;

import std.core;
import soul.cpp20.symbols.modules;

export namespace gendoc {

class Project;

void GenerateModuleHtml(const std::string& rootDir, soul::cpp20::symbols::Module* module, Project* nsProject);

} // namespace gendoc
