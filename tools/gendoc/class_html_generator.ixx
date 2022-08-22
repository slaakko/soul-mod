// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module gendoc.class_html_generator;

import std.core;
import soul.cpp20.symbols.classes;
import soul.cpp20.symbols.modules;

export namespace gendoc {

void GenerateClassHtml(const std::string& modulePath, soul::cpp20::symbols::Module* module, soul::cpp20::symbols::ClassTypeSymbol* classTypeSymbol);

} // namespace gendoc
