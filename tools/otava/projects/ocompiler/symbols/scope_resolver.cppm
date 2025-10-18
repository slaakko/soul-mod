// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.scope.resolver;

import std;
import otava.ast;

export namespace otava::symbols {

class Scope;
class Context;

std::expected<Scope*, int> ResolveScope(otava::ast::Node* nnsNode, Context* context);

void BeginScope(otava::ast::Node* nnsNode, Context* context);
void EndScope(Context* context);
void AddParentScope(otava::ast::Node* node, Context* context);

} // namespace otava::symbols
