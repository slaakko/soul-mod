// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.spg.parsing.util;

import std.core;
import soul.ast.spg;

export namespace soul::spg::parsing::util {

soul::ast::spg::Parser* MakeParserFromStrLiteral(const std::u32string& str);

} // namespace soul::spg
