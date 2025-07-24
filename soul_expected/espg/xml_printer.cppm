// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul_expected.spg.xml.printer;

import std;
import soul_expected.ast.spg;

export namespace soul_expected::spg {

std::expected<bool, int>  PrintXml(soul_expected::ast::spg::SpgFile* spgFile, bool verbose, bool opt);

} // namespace soul::spg
