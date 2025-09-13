// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.spg.file.parsers;

import std;
import soul.lexer.file.map;
import soul.ast.spg;
import soul.ast.common;
import soul.ast.source.pos;

export namespace soul::spg {

std::expected<std::unique_ptr<soul::ast::spg::SpgFile>, int> ParseSpgFile(const std::string& spgFilePath, soul::lexer::FileMap& fileMap, bool verbose);
std::expected<std::unique_ptr<soul::ast::spg::ParserFile>, int> ParseParserFile(const std::string& parserFilePath, const soul::ast::SourcePos& sourcePos,
    soul::lexer::FileMap& fileMap, bool verbose, bool external);
std::expected<std::unique_ptr<soul::ast::common::TokenFile>, int> ParseTokenFile(const std::string& tokenFilePath, const soul::ast::SourcePos& sourcePos,
    bool verbose, bool external, soul::lexer::FileMap& fileMap);

} // namespace soul::spg
