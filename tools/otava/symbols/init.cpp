// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.init;

import otava.symbols.expression.binder;
import otava.symbols.function.symbol;
import otava.symbols.modules;
import otava.ast.node;

namespace otava::symbols {

void Init()
{
    InitExpressionBinder();
    InitFunction();
    otava::ast::SetNodeDestroyedFunc(otava::symbols::NodeDestroyed);
    otava::ast::MakeNodeFactoryCollection();
}

} // namespace otava::symbols
