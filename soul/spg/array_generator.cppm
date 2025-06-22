// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.spg.array.generator;

import std.core;
import soul.ast.spg;
import util.code.formatter;

export namespace soul::spg {

void GenerateArrays(soul::ast::spg::ParserFile& parserFile, util::CodeFormatter& formatter, int& sn);

} // namespace soul::spg
