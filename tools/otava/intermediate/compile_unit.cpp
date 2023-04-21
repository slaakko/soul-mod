// =================================
// Copyright (c) 2023 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.intermediate.compile.unit;

import otava.intermediate.context;
import otava.intermediate.type;
import otava.intermediate.code;
import otava.intermediate.data;
import otava.intermediate.function;
import util.code.formatter;

namespace otava::intermediate {

CompileUnit::CompileUnit() : context(nullptr), id(), metadataRef()
{
}

void CompileUnit::SetFilePath(const std::string& filePath_)
{
    filePath = filePath_;
}

void CompileUnit::SetInfo(const std::string& id_, MetadataRef* metadataRef_)
{
    id = id_;
    metadataRef = metadataRef_;
}

void CompileUnit::Write()
{
    std::ofstream file(filePath);
    util::CodeFormatter formatter(file);
    formatter.SetIndentSize(8);
    formatter.Write("cu(");
    formatter.Write(id);
    formatter.Write(",");
    metadataRef->Write(formatter);
    formatter.WriteLine(")");
    formatter.WriteLine();
    context->GetTypes().Write(formatter);
    context->GetData().Write(formatter);
    context->GetCode().Write(formatter);
    context->GetMetadata().Write(formatter);
}

} // namespace otava::intermediate
