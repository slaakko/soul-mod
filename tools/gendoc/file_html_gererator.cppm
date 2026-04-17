// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module gendoc.file_html_generator;

import std;
import otava.symbols;

export namespace gendoc {

void GenerateFileHtml(otava::symbols::Module* module, const std::string& moduleDir);

} // namespace gendoc
