// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.function_return_path_checker;

import otava.ast;
import std;

export namespace otava::symbols {

class Context;

void CheckFunctionReturnPaths(otava::ast::Node* node, Context* context);
bool TerminatesCaseOrDefault(otava::ast::Node* statementNode);

} // namespace otava::symbols
