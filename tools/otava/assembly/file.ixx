// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.assembly.file;

import std.core;
import util.code.formatter;

export namespace otava::assembly {

class FunctionDeclaration;

class DeclarationSection
{
public:
    void AddFunctionDeclaration(FunctionDeclaration* declaration);
    void Write(util::CodeFormatter& formatter);
private:
    std::vector<std::unique_ptr<FunctionDeclaration>> declarations;
};

class Function;

class CodeSection
{
public:
    Function* CreateFunction(const std::string& name);
    void Write(util::CodeFormatter& formatter);
private:
    std::vector<std::unique_ptr<Function>> functions;
};

class File
{
public:
    File(const std::string& filePath_);
    const std::string& FilePath() const { return filePath; }
    DeclarationSection& GetDeclarationSection() { return declarationSection; }
    CodeSection& GetCodeSection() { return codeSection; }
    void Write();
private:
    std::string filePath;
    std::ofstream file;
    util::CodeFormatter formatter;
    DeclarationSection declarationSection;
    CodeSection codeSection;
    std::vector<std::unique_ptr<Function>> functions;
};

} // namespace otava::assembly
