// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module gendoc.file_html_generator;

import std.core;
import soul.cpp20.symbols.modules;

export namespace gendoc {

void GenerateFileHtml(soul::cpp20::symbols::Module* module, const std::string& moduleDir);

} // namespace gendoc
