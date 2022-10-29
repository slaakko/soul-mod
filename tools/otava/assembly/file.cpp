// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.assembly.file;

import otava.assembly.function;
import otava.assembly.instruction;

namespace otava::assembly {

File::File(const std::string& filePath_) : filePath(filePath_), file(filePath), formatter(file)
{
    formatter.SetIndentSize(8);
}

Function* File::CreateFunction(const std::string& name)
{
    Function* function = new Function(name);
    functions.push_back(std::unique_ptr<Function>(function));
    return function;
}

void File::Write()
{
    formatter.WriteLine(".CODE");
    formatter.WriteLine();
    for (const auto& function : functions)
    {
        function->Write(formatter);
        formatter.WriteLine();
    }
    formatter.WriteLine("END");
}

} // namespace otava::assembly
