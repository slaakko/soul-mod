// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.ast.output;

import std.core;
import otava.ast.node;

export namespace otava::ast {

void PrintSource(Node& node, std::ostream& stream);
void PrintXml(Node& node, std::ostream& stream);

} // namespace otava::ast
