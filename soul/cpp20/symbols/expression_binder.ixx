// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.symbols.expression.binder;

import soul.cpp20.ast.node;
import soul.cpp20.symbols.symbol;

export namespace soul::cpp20::symbols {

class BoundExpressionNode;
class Context;
class Scope;
    
BoundExpressionNode* BindExpression(soul::cpp20::ast::Node* node, Context* context);
BoundExpressionNode* BindExpression(soul::cpp20::ast::Node* node, Context* context, SymbolGroupKind symbolGroups, Scope*& scope);

} // namespace soul::cpp20::symbols
