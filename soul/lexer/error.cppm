// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.lexer.error;

import std;
import soul.ast.source.pos;
import soul.lexer.file.map;

export namespace soul::lexer {

class ParsingException : public std::runtime_error
{
public:
    ParsingException(const std::string& message_, const std::string& fileName_, const soul::ast::SourcePos& sourcePos_);
    inline const std::string& Project() const { return project; }
    void SetProject(const std::string& project_);
    inline const std::string& Message() const { return message; }
    inline const std::string& FileName() const { return fileName; }
    inline const soul::ast::SourcePos& GetSourcePos() const { return sourcePos; }
private:
    std::string project;
    std::string message;
    std::string fileName;
    soul::ast::SourcePos sourcePos;
};

std::string MakeMessage(const std::string& msgClass, const std::string& msg, const soul::ast::SourcePos& sourcePos, FileMap& fileMap);

} // namespace soul::lexer
