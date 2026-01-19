// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.spg.array.generator;

import std;
import soul.ast.spg;
import util.code.formatter;

export namespace soul::spg {

std::expected<bool, int> GenerateArrays(soul::ast::spg::ParserFile& parserFile, util::CodeFormatter& formatter, int& sn);

} // namespace soul::spg
