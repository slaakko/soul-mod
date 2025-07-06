// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.assembly.file;

import std;
import util;

export namespace otava::assembly {

class Data;
class Declaration;
class Function;
class FunctionDeclaration;
class PublicDeclaration;
class LinkOnceDeclaration;
class ExternalDataDeclaration;

class DeclarationSection
{
public:
    void AddFunctionDeclaration(FunctionDeclaration* declaration);
    void AddPublicDeclaration(PublicDeclaration* declaration);
    void AddLinkOnceDeclaration(LinkOnceDeclaration* declaration);
    void AddExternalDataDeclaration(ExternalDataDeclaration* declaration);
    void Write(util::CodeFormatter& formatter);
private:
    std::vector<std::unique_ptr<Declaration>> declarations;
    std::set<std::string> externalFunctionDeclarations;
    std::set<std::string> externalDataDeclarations;
};

class DataSection
{
public:
    void AddData(Data* data);
    void Write(util::CodeFormatter& formatter);
private:
    std::vector<std::unique_ptr<Data>> dataVec;
};

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
    DataSection& GetDataSection() { return dataSection; }
    CodeSection& GetCodeSection() { return codeSection; }
    void Write();
    const std::string& Id() const { return id; }
private:
    std::string filePath;
    std::ofstream file;
    util::CodeFormatter formatter;
    DeclarationSection declarationSection;
    DataSection dataSection;
    CodeSection codeSection;
    std::string id;
};

} // otava::assembly
