// =================================
// Copyright (c) 2023 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.assembly.data;

import std.core;
import util.code.formatter;
import otava.assembly.declaration;

export namespace otava::assembly {

class Value;

enum class DataInst
{
    DB, DW, DD, DQ
};

std::string DataInstStr(DataInst inst);

class Data
{
public:
    Data(const std::string& label_, DataInst commonInst_);
    void AddItem(DataInst inst, Value* item);
    void Write(util::CodeFormatter& formatter);
    void UseCommonInst(bool useCommonInst_) { useCommonInst = useCommonInst_; }
private:
    std::string label;
    bool useCommonInst;
    DataInst commonInst;
    std::vector<DataInst> insts;
    std::vector<Value*> items;
};

class PublicDataDeclaration : public Declaration
{
public:
    PublicDataDeclaration(const std::string& name_);
    void Write(util::CodeFormatter& formatter) override;
};

class ExternalDataDeclaration : public Declaration
{
public:
    ExternalDataDeclaration(const std::string& name_);
    void Write(util::CodeFormatter& formatter) override;
};

} // namespace otava::assembly
