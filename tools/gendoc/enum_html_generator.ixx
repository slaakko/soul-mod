// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module gendoc.enum_html_generator;

import std.core;
import soul.cpp20.symbols.enums;
import soul.cpp20.symbols.modules;

export namespace gendoc {

void GenerateEnumHtml(const std::string& modulePath, soul::cpp20::symbols::Module* module, soul::cpp20::symbols::EnumeratedTypeSymbol* enumTypeSymbol);

} // namespace gendoc
