// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.ast.output;

import std;
import otava.ast.node;

export namespace otava::ast {

void PrintSource(Node& node, std::ostream& stream);
std::expected<bool, int> PrintXml(Node& node, std::ostream& stream);

} // namespace otava::ast
