// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.spg.file.parsers;

import std.core;
import soul.lexer.file.map;
import soul.ast.spg;
import soul.ast.source.pos;

export namespace soul::spg {

std::unique_ptr<soul::ast::spg::SpgFile> ParseSpgFile(const std::string& spgFilePath, soul::lexer::FileMap& fileMap, bool verbose);
std::unique_ptr<soul::ast::spg::ParserFile> ParseParserFile(const std::string& parserFilePath, const soul::ast::SourcePos& sourcePos, 
    soul::lexer::FileMap& fileMap, bool verbose, bool external);

} // namespace soul::spg
