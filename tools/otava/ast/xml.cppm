// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.ast.xml;

import std.core;

export namespace otava::ast {

class Node;
void WriteXml(Node* node, const std::string& filePath);

} // namespace otava::ast
