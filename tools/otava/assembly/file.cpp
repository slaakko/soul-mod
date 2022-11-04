// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.assembly.file;

import otava.assembly.function;
import otava.assembly.instruction;

namespace otava::assembly {

void DeclarationSection::AddFunctionDeclaration(FunctionDeclaration* declaration)
{
    declarations.push_back(std::unique_ptr<FunctionDeclaration>(declaration));
}

void DeclarationSection::Write(util::CodeFormatter& formatter)
{
    for (const auto& functionDeclaration : declarations)
    {
        functionDeclaration->Write(formatter);
    }
    formatter.WriteLine();
}

Function* CodeSection::CreateFunction(const std::string& name)
{
    Function* function = new Function(name);
    functions.push_back(std::unique_ptr<Function>(function));
    return function;
}

void CodeSection::Write(util::CodeFormatter& formatter)
{
    formatter.WriteLine(".CODE");
    formatter.WriteLine();
    for (const auto& function : functions)
    {
        function->Write(formatter);
        formatter.WriteLine();
    }
}

File::File(const std::string& filePath_) : filePath(filePath_), file(filePath), formatter(file)
{
    formatter.SetIndentSize(8);
}

void File::Write()
{
    declarationSection.Write(formatter);
    codeSection.Write(formatter);
    formatter.WriteLine("END");
}

} // namespace otava::assembly
