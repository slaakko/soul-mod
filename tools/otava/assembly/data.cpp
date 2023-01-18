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

Data::Data(const std::string& label_, DataInst commonInst_) : useCommonInst(false), label(label_), commonInst(commonInst_), insts()
{
}

void Data::AddItem(DataInst inst, Value* item)
{
    insts.push_back(inst);
    items.push_back(item);
}

void Data::Write(util::CodeFormatter& formatter)
{
    if (!label.empty())
    {
        formatter.Write(label);
        formatter.Write(" ");
    }
    if (useCommonInst)
    {
        formatter.Write(DataInstStr(commonInst));
        formatter.Write(" ");
    }
    int n = items.size();
    for (int i = 0; i < n; ++i)
    {
        if (!useCommonInst)
        {
            if (i > 0)
            {
                formatter.Write(" ");
            }
            formatter.Write(DataInstStr(insts[i]));
            formatter.Write(" ");
        }
        else
        {
            if (i > 0)
            {
                formatter.Write(", ");
            }
        }
        formatter.Write(items[i]->ToString());
    }
    formatter.WriteLine();
}

PublicDataDeclaration::PublicDataDeclaration(const std::string& name_) : Declaration(name_)
{
}

void PublicDataDeclaration::Write(util::CodeFormatter& formatter)
{
    formatter.Write("PUBLIC ");
    formatter.WriteLine(Name());
}

ExternalDataDeclaration::ExternalDataDeclaration(const std::string& name_) : Declaration(name_)
{
}

void ExternalDataDeclaration::Write(util::CodeFormatter& formatter)
{
    formatter.Write("EXTRN ");
    formatter.Write(Name());
    formatter.WriteLine(":BYTE");
}


} // namespace otava::assembly
