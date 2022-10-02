// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.symbols.statement.binder;

import std.core;
import soul.cpp20.ast.node;

export namespace soul::cpp20::symbols {

class BoundStatementNode;
class Context;
class FunctionDefinitionSymbol;

void BindFunction(soul::cpp20::ast::Node* functionDefinitionNode, FunctionDefinitionSymbol* functionDefinitionSymbol, Context* context);
BoundStatementNode* BindStatement(soul::cpp20::ast::Node* statementNode, Context* context);

} // namespace soul::cpp20::symbols
