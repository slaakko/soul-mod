// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.project.init;

import std.core;
import soul.cpp20.symbols.modules;
import soul.cpp20.symbols.symbol.table;
import soul.cpp20.symbols.value;
import soul.cpp20.ast.node;

export namespace soul::cpp20::project::init {

struct Init
{
    Init();
    void SetSymbols(soul::cpp20::symbols::Symbols* symbols_) { symbols = symbols_; }
    void SetNodeIdFactory(soul::cpp20::ast::NodeIdFactory* nodeIdFactory_) { nodeIdFactory = nodeIdFactory_; }
    void SetEvaluationContext(soul::cpp20::symbols::EvaluationContext* evaluationContext_) { evaluationContext = evaluationContext_; }
    soul::cpp20::symbols::ModuleMapper moduleMapper;
    soul::cpp20::symbols::Symbols* symbols;
    soul::cpp20::ast::NodeIdFactory* nodeIdFactory;
    soul::cpp20::symbols::EvaluationContext* evaluationContext;
};

} // namespace soul::cpp20::project::init
