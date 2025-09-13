// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.spg.xml.printer;

import std;
import soul.ast.spg;

export namespace soul::spg {

std::expected<bool, int>  PrintXml(soul::ast::spg::SpgFile* spgFile, bool verbose, bool opt);

} // namespace soul::spg
