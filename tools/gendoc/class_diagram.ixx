// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module gendoc.class_diagram;

import std.core;
import soul.cpp20.symbols.classes;

export namespace gendoc {

bool GenerateClassDiagramFile(const std::string& modulePath, soul::cpp20::symbols::ClassTypeSymbol* cls, std::string& diagramFileName);

} // namespace gendoc
