// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.expression.binder;

import std;
import otava.ast.node;
import otava.symbols.scope;
import otava.symbols.symbol;
import soul.ast.source.pos;

export namespace otava::symbols {

class BoundExpressionNode;
class Context;
class Scope;
class StatementBinder;

std::expected<otava::ast::Node*, int> MakeTypeNameNodes(const soul::ast::SourcePos& sourcePos, const std::u32string& fullTypeName);

std::expected<BoundExpressionNode*, int> BindExpression(otava::ast::Node* node, Context* context);
std::expected<BoundExpressionNode*, int> BindExpression(otava::ast::Node* node, Context* context, bool booleanChild);
std::expected<BoundExpressionNode*, int> BindExpression(otava::ast::Node* node, Context* context, SymbolGroupKind symbolGroups, Scope*& scope);
void InitExpressionBinder();

} // namespace otava::symbols
