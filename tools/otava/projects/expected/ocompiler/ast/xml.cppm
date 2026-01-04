// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.ast.xml;

import std;

export namespace otava::ast {

class Node;
std::expected<bool, int> WriteXml(Node* node, const std::string& filePath);

} // namespace otava::ast
