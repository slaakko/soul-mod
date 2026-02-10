// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.intermediate.compile_unit;

import otava.intermediate.context;
import util;

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

std::expected<bool, int> CompileUnit::Write()
{
    std::ofstream file(filePath);
    if (!file) return std::unexpected<int>(util::AllocateError("could not create file '" + filePath + "'"));
    util::CodeFormatter formatter(file);
    formatter.SetIndentSize(8);
    context->GetTypes().Write(formatter);
    context->GetData().Write(formatter);
    bool first = true;
    Function* fn = context->GetCode().FirstFunction();
    while (fn)
    {
        if (first)
        {
            first = false;
        }
        else
        {
            formatter.WriteLine();
        }
        std::expected<bool, int> rv = fn->Write(formatter);
        if (!rv) return rv;
        fn = fn->Next();
    }
    std::expected<bool, int> rv = context->GetMetadata().Write(formatter);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

} // otava::intermediate
