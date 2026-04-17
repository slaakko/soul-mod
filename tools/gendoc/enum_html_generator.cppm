// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module gendoc.enum_html_generator;

import std;
import otava.symbols;

export namespace gendoc {

void GenerateEnumHtml(const std::string& modulePath, otava::symbols::Module* module, otava::symbols::EnumeratedTypeSymbol* enumTypeSymbol);

} // namespace gendoc
