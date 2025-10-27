// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.using_declaration;

import std;
import otava.ast;

export namespace otava::symbols {

class Context;

std::expected<bool, int> AddUsingDeclaration(otava::ast::Node* node, Context* context);

} // namespace otava::symbols
