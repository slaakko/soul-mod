// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.ast.output;

import std.core;
import soul.cpp20.ast.node;

export namespace soul::cpp20::ast {

void PrintSource(Node& node, std::ostream& stream);
void PrintXml(Node& node, std::ostream& stream);

} // namespace soul::cpp20::ast
