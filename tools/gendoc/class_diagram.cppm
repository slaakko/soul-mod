// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module gendoc.class_diagram;

import std;
import otava.symbols;

export namespace gendoc {

bool GenerateClassDiagramFile(const std::string& modulePath, otava::symbols::ClassTypeSymbol* cls, std::string& diagramFileName);

} // namespace gendoc
