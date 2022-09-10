// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.ast.xml;

import std.core;

export namespace soul::cpp20::ast {

class Node;
void WriteXml(Node* node, const std::string& filePath);

} // namespace soul::cpp20::ast
