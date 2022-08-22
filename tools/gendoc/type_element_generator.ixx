// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module gendoc.type_element_generator;

import std.core;
import soul.xml.element;
import soul.cpp20.symbols.modules;
import soul.cpp20.symbols.namespaces;
import soul.cpp20.symbols.value;

export namespace gendoc {

std::string MakeNsText(soul::cpp20::symbols::NamespaceSymbol* ns);
void AddValue(soul::xml::Element* containerElement, soul::cpp20::symbols::Value* value, soul::cpp20::symbols::Module* module, soul::cpp20::symbols::Symbol* containerSymbol);
soul::xml::Element* GenerateTypeXmlElement(soul::cpp20::symbols::Module* module, soul::cpp20::symbols::Symbol* containerSymbol, soul::cpp20::symbols::Symbol* symbol);

} // namespace gendoc
