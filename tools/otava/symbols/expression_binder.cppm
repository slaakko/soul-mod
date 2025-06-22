// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.expression.binder;

import std;
import otava.ast.node;
import otava.symbols.symbol;
import soul.ast.source.pos;

export namespace otava::symbols {

class BoundExpressionNode;
class Context;
class Scope;
class StatementBinder;
    
otava::ast::Node* MakeTypeNameNodes(const soul::ast::SourcePos& sourcePos, const std::u32string& fullTypeName);

BoundExpressionNode* BindExpression(otava::ast::Node* node, Context* context);
BoundExpressionNode* BindExpression(otava::ast::Node* node, Context* context, bool booleanChild);
BoundExpressionNode* BindExpression(otava::ast::Node* node, Context* context, SymbolGroupKind symbolGroups, Scope*& scope);
void InitExpressionBinder();

} // namespace otava::symbols
