// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.ast.file;

import std.core;
import soul.cpp20.ast.node;

export namespace soul::cpp20::ast {

struct File
{
    File();
    File(const std::string& filePath_, Node* content_);
    void Write(Writer& writer);
    void Read(Reader& reader);
    std::string filePath;
    std::unique_ptr<Node> content;
};

} // namespace soul::cpp20::ast
