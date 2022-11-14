// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.assembly.data;

import std.core;
import util.code.formatter;

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
    Data(const std::string& label_, DataInst inst_);
    void AddItem(Value* item);
    void Write(util::CodeFormatter& formatter);
private:
    std::string label;
    DataInst inst;
    std::vector<Value*> items;
};

} // namespace otava::assembly
