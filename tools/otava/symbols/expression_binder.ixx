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
class StatementBinder;
    
BoundExpressionNode* BindExpression(otava::ast::Node* node, Context* context, StatementBinder* statementBinder);
BoundExpressionNode* BindExpression(otava::ast::Node* node, Context* context, SymbolGroupKind symbolGroups, Scope*& scope, StatementBinder* statementBinder);
void InitExpressionBinder();

} // namespace otava::symbols
