// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.statement.binder;

import std.core;
import otava.ast.node;

export namespace otava::symbols {

class BoundStatementNode;
class Context;
class FunctionDefinitionSymbol;

void BindFunction(otava::ast::Node* functionDefinitionNode, FunctionDefinitionSymbol* functionDefinitionSymbol, Context* context);
BoundStatementNode* BindStatement(otava::ast::Node* statementNode, Context* context);

} // namespace otava::symbols
