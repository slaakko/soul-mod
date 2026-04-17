// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module gendoc.type_element_generator;

import std;
import soul.xml.element;
import otava.symbols;

export namespace gendoc {

std::string MakeNsText(otava::symbols::NamespaceSymbol* ns);
void AddValue(soul::xml::Element* containerElement, otava::symbols::Value* value, otava::symbols::Module* module, otava::symbols::Symbol* containerSymbol);
soul::xml::Element* GenerateTypeXmlElement(otava::symbols::Module* module, otava::symbols::Symbol* containerSymbol, otava::symbols::Symbol* symbol);

} // namespace gendoc
