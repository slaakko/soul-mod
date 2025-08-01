// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.assembly.function;

import otava.assembly.declaration;
import otava.assembly.macro;
import std;
import util;

export namespace otava::assembly {

class FunctionDeclaration : public Declaration
{
public:
    FunctionDeclaration(const std::string& name_);
    void Write(util::CodeFormatter& formatter) override;
};

class LinkOnceDeclaration : public Declaration
{
public:
    LinkOnceDeclaration(const std::string& name_);
    void Write(util::CodeFormatter& formatter) override;
};

class Instruction;

enum class FunctionPart
{
    prologue, body, epilogue
};

class Function
{
public:
    Function(const std::string& name_);
    inline const std::string& Name() const { return name; }
    inline int Index() const { return body.size(); }
    void SetActiveFunctionPart(FunctionPart activeFunctionPart_);
    void AddInstruction(Instruction* inst);
    void InsertInstruction(int index, Instruction* inst);
    void Write(util::CodeFormatter& formatter);
    void AddMacro(Macro* macro);
    Macro* GetMacro(const std::string& name) const;
    inline const std::string& Comment() const { return comment; }
    void SetComment(const std::string& comment_);
private:
    std::string name;
    FunctionPart activeFunctionPart;
    std::vector<std::unique_ptr<Instruction>> prologue;
    std::vector<std::unique_ptr<Instruction>> body;
    std::vector<std::unique_ptr<Instruction>> epilogue;
    std::vector<Macro*> macros;
    std::map<std::string, Macro*> macroMap;
    std::string comment;
};

} // namespace otava::assembly
