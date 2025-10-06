// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.assembly.file;

import std;
import util;
import otava.assembly.declaration;

export namespace otava::assembly {

class Data;
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
    ~DataSection();
    void AddData(Data* data);
    void Write(util::CodeFormatter& formatter);
private:
    std::vector<Data*> dataVec;
};

class CodeSection
{
public:
    ~CodeSection();
    Function* CreateFunction(const std::string& name);
    void Write(util::CodeFormatter& formatter);
private:
    std::vector<Function*> functions;
};

class File
{
public:
    File(const std::string& filePath_);
    inline const std::string& FilePath() const { return filePath; }
    inline DeclarationSection& GetDeclarationSection() { return declarationSection; }
    inline DataSection& GetDataSection() { return dataSection; }
    inline CodeSection& GetCodeSection() { return codeSection; }
    void Write();
    inline const std::string& Id() const { return id; }
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
