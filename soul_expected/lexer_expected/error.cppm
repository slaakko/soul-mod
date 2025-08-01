// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul_expected.lexer.error;

import std;
import soul_expected.ast.source.pos;
import soul_expected.lexer.file.map;

export namespace soul_expected::lexer {

class ParsingException : public std::runtime_error
{
public:
    ParsingException(const std::string& message_, const std::string& fileName_, const soul_expected::ast::SourcePos& sourcePos_);
    inline const std::string& Project() const { return project; }
    void SetProject(const std::string& project_);
    inline const std::string& Message() const { return message; }
    inline const std::string& FileName() const { return fileName; }
    inline const soul_expected::ast::SourcePos& GetSourcePos() const { return sourcePos; }
private:
    std::string project;
    std::string message;
    std::string fileName;
    soul_expected::ast::SourcePos sourcePos;
};

std::expected<std::string, int> MakeMessage(const std::string& msgClass, const std::string& msg, const soul_expected::ast::SourcePos& sourcePos, FileMap& fileMap);

} // namespace soul_expected::lexer
