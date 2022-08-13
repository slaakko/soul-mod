// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module gendoc.module_html_generator;

import std.core;
import soul.cpp20.symbols.modules;

export namespace gendoc {

void GenerateModuleHtml(const std::string& rootDir, soul::cpp20::symbols::Module* module);

} // namespace gendoc::module_html_generator
