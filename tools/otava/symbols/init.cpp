// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.init;

import otava.symbols.expression.binder;
import otava.symbols.modules;
import otava.ast.node;

namespace otava::symbols {

void Init()
{
    InitExpressionBinder();
    otava::ast::SetNodeDestroyedFunc(otava::symbols::NodeDestroyed);
    otava::ast::MakeNodeFactoryCollection();
}

} // namespace otava::symbols
