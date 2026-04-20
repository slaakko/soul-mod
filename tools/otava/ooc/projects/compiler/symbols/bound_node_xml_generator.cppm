// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.bound.node.xml.generator;

import std;
import soul.xml.dom;
import otava.symbols.bound.tree;

export namespace otava::symbols {

std::unique_ptr<soul::xml::Element> ToXml(BoundFunctionNode* fn);
std::unique_ptr<soul::xml::Element> ToXml(BoundCompileUnitNode* cu);

void PrintXml(BoundFunctionNode* fn, std::ostream* s);
void PrintXml(BoundCompileUnitNode* cu, std::ostream* s);

} // namespace otava::symbols
