// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module gendoc.namespace_html_generator;

import gendoc.namespace_symbols;
import std.core;
import soul.cpp20.symbols.modules;

export namespace gendoc {

void GenerateNamespaceHtml(const std::string& rootDir, const std::string& nsDocName, NamespaceSymbols* symbols);

} // namespace gendoc
