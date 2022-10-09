// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.expression.binder;

import std.core;
import otava.ast.node;
import otava.symbols.symbol;

export namespace otava::symbols {

class BoundExpressionNode;
class Context;
class Scope;
    
enum class SymbolGroupKind : int32_t;

BoundExpressionNode* BindExpression(otava::ast::Node* node, Context* context);
BoundExpressionNode* BindExpression(otava::ast::Node* node, Context* context, SymbolGroupKind symbolGroups, Scope*& scope);
void InitExpressionBinder();

} // namespace otava::symbols