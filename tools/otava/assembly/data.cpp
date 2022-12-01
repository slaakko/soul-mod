// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.assembly.data;

import otava.assembly.value;

namespace otava::assembly {

std::string DataInstStr(DataInst inst)
{
    switch (inst)
    {
        case DataInst::DB: return "DB";
        case DataInst::DW: return "DW";
        case DataInst::DD: return "DD";
        case DataInst::DQ: return "DQ";
    }
    return std::string();
}

Data::Data(const std::string& label_, DataInst inst_) : label(label_), inst(inst_)
{
}

void Data::AddItem(Value* item)
{
    items.push_back(item);
}

void Data::Write(util::CodeFormatter& formatter)
{
    if (!label.empty())
    {
        formatter.Write(label);
        formatter.Write(" ");
    }
    formatter.Write(DataInstStr(inst));
    formatter.Write(" ");
    bool first = true;
    for (Value* item : items)
    {
        if (first)
        {
            first = false;
        }
        else
        {
            formatter.Write(", ");
        }
        formatter.Write(item->ToString());
    }
    formatter.WriteLine();
}

} // namespace otava::assembly
