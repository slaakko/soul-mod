// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.lexer.error;

import std;
import soul.ast.source.pos;
import soul.lexer.file.map;

export namespace soul::lexer {

std::expected<std::string, int> MakeMessage(const std::string& msgClass, const std::string& msg, const soul::ast::SourcePos& sourcePos, FileMap& fileMap);

} // namespace soul::lexer
