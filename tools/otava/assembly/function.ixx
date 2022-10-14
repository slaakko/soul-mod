// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.assembly.function;

import std.core;
import util.code.formatter;

export namespace otava::assembly {

class Instruction;

class Function
{
public:
    Function(const std::string& name_);
    const std::string& Name() const { return name; }
    void AddInstruction(Instruction* inst);
    const std::vector<std::unique_ptr<Instruction>>& Instructions() const { return instructions; }
    void Write(util::CodeFormatter& formatter);
private:
    std::string name;
    std::vector<std::unique_ptr<Instruction>> instructions;
};

} // namespace otava::assembly
