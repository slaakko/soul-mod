// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul_expected.spg.file.parsers;

import std;
import soul_expected.lexer.file.map;
import soul_expected.ast.spg;
import soul_expected.ast.slg;
import soul_expected.ast.source.pos;

export namespace soul_expected::spg {

std::expected<std::unique_ptr<soul_expected::ast::spg::SpgFile>, int> ParseSpgFile(const std::string& spgFilePath, soul_expected::lexer::FileMap& fileMap, bool verbose);
std::expected<std::unique_ptr<soul_expected::ast::spg::ParserFile>, int> ParseParserFile(const std::string& parserFilePath, const soul_expected::ast::SourcePos& sourcePos,
    soul_expected::lexer::FileMap& fileMap, bool verbose, bool external);
std::expected<std::unique_ptr<soul_expected::ast::slg::TokenFile>, int> ParseTokenFile(const std::string& tokenFilePath, bool external);

} // namespace soul_expected::spg
