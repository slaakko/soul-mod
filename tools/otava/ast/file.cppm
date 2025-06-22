// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.ast.file;

import std.core;
import otava.ast.node;

export namespace otava::ast {

struct File
{
    File();
    File(const std::string& filePath_, Node* content_);
    void Write(Writer& writer);
    void Read(Reader& reader);
    std::string filePath;
    std::unique_ptr<Node> content;
};

} // namespace otava::ast
