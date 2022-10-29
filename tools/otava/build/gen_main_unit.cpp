// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.build.gen_main_unit;

import util.code.formatter;

namespace otava::build {

void GenerateMainUnit(const std::string& mainFilePath, const std::string& mainFunctionIrName, int numParams)
{
    std::ofstream mainFile(mainFilePath);
    util::CodeFormatter formatter(mainFile);
    if (numParams == 2)
    {
        formatter.WriteLine("extern \"C\" int " + mainFunctionIrName + "(int argc, const char** argv);");
    }
    else if (numParams == 0)
    {
        formatter.WriteLine("extern \"C\" int " + mainFunctionIrName + "();");
    }
    formatter.WriteLine();
    formatter.WriteLine("int main(int argc, const char** argv)");
    formatter.WriteLine("{");
    formatter.IncIndent();
    if (numParams == 2)
    {
        formatter.WriteLine("int retVal = " + mainFunctionIrName + "(argc, argv);");
    }
    else if (numParams == 0)
    {
        formatter.WriteLine("int retVal = " + mainFunctionIrName + "();");
    }
    else
    {
        throw std::runtime_error("invalid number of main function parameters");
    }
    formatter.WriteLine("return retVal;");
    formatter.DecIndent();
    formatter.WriteLine("}");
}

} // namespace otava::build

