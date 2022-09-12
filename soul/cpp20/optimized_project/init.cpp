// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.project.init;

import soul.cpp20.ast;
import soul.cpp20.symbols.namespaces;
import soul.cpp20.symbols.compound.type.symbol;
import soul.cpp20.parser.recorded.parse;

namespace soul::cpp20::project::init {

Init::Init() : moduleMapper(), symbols(nullptr), nodeIdFactory(nullptr)
{
    soul::cpp20::ast::SetNodeDestroyedFunc(soul::cpp20::symbols::NodeDestroyed);
    soul::cpp20::ast::MakeNodeFactoryCollection();
    soul::cpp20::parser::recorded::parse::Init();
}

} // namespace soul::cpp20::project::init

