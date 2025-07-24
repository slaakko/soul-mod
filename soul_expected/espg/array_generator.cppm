// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul_expected.spg.array.generator;

import std;
import soul_expected.ast.spg;
import util_expected.code.formatter;

export namespace soul_expected::spg {

std::expected<bool, int> GenerateArrays(soul_expected::ast::spg::ParserFile& parserFile, util::CodeFormatter& formatter, int& sn);

} // namespace soul_expected::spg
