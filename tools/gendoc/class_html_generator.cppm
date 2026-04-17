// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module gendoc.class_html_generator;

import std;
import otava.symbols;

export namespace gendoc {

void GenerateClassHtml(const std::string& modulePath, otava::symbols::Module* module, otava::symbols::ClassTypeSymbol* classTypeSymbol);

} // namespace gendoc
