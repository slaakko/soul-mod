// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.spg.parser.generator;

import std.filesystem;
import util;
import soul.spg.file.parsers;
import soul.spg.linking;
import soul.spg.optimizer;
import soul.spg.code.generator;
import soul.spg.pp.style.code.generator;
import soul.spg.xml.printer;
import soul.ast.common;

namespace soul::spg {

void GenerateRuleNameModule(soul::ast::spg::SpgFile* spgFile, bool verbose, soul::common::ModuleMap& moduleMap, bool ppstyle)
{
    if (verbose)
    {
        std::cout << "generating rule name module..." << std::endl;
    }
    std::filesystem::path spgFilePath = spgFile->FilePath();
    std::filesystem::path root = spgFilePath.parent_path();
    std::filesystem::path interfaceFilePath;
    if (ppstyle)
    {
        interfaceFilePath = root / (spgFilePath.stem().generic_string() + "_rules.hpp");
    }
    else
    {
        interfaceFilePath = root / (spgFilePath.stem().generic_string() + "_rules.cppm");
    }
    std::ofstream interfaceFile(interfaceFilePath.generic_string());
    util::CodeFormatter interfaceFormatter(interfaceFile);
    std::string moduleName = spgFile->ProjectName() + ".rules";
    moduleMap.MapModule(moduleName, interfaceFilePath.generic_string());
    std::string includeGuard;
    if (ppstyle)
    {
        includeGuard = "INCLUDE_GUARD_" + util::GetSha1MessageDigest(moduleName);
        interfaceFormatter.WriteLine("#ifndef " + includeGuard);
        interfaceFormatter.WriteLine("#define " + includeGuard);
        interfaceFormatter.WriteLine();
        interfaceFormatter.WriteLine("// export module " + moduleName + ";");
        interfaceFormatter.WriteLine();
        interfaceFormatter.WriteLine("#include <stdint.h>");
        interfaceFormatter.WriteLine("#include <string>");
        interfaceFormatter.WriteLine("#include <map>");
        interfaceFormatter.WriteLine();
        interfaceFormatter.WriteLine("namespace " + soul::ast::common::ToNamespaceName(moduleName) + " {");
    }
    else
    {
        interfaceFormatter.WriteLine("export module " + moduleName + ";");
        interfaceFormatter.WriteLine();
        interfaceFormatter.WriteLine("import std.core;");
        interfaceFormatter.WriteLine();
        interfaceFormatter.WriteLine("export namespace " + soul::ast::common::ToNamespaceName(moduleName) + " {");
    }
    interfaceFormatter.WriteLine();
    interfaceFormatter.WriteLine("std::map<std::int64_t, std::string>* GetRuleNameMapPtr();");
    interfaceFormatter.WriteLine();
    interfaceFormatter.WriteLine("} // " + soul::ast::common::ToNamespaceName(moduleName));
    if (ppstyle)
    {
        interfaceFormatter.WriteLine();
        interfaceFormatter.WriteLine("#endif // " + includeGuard);
    }
    if (verbose)
    {
        std::cout << "==> " << interfaceFilePath.generic_string() << std::endl;
    }

    std::filesystem::path implementationFilePath = root / (spgFilePath.stem().generic_string() + "_rules.cpp");
    std::ofstream implementationFile(implementationFilePath.generic_string());
    util::CodeFormatter implementationFormatter(implementationFile);
    if (ppstyle)
    {
        std::string headerFilePath = moduleMap.GetHeaderFilePath(moduleName, root.generic_string());
        if (!headerFilePath.empty())
        {
            implementationFormatter.WriteLine("#include <" + headerFilePath + ">");
            implementationFormatter.WriteLine("#include <mutex>");
            implementationFormatter.WriteLine();
        }
        implementationFormatter.WriteLine("// module " + moduleName + ";");
    }
    else
    {
        implementationFormatter.WriteLine("module " + moduleName + ";");
    }
    implementationFormatter.WriteLine();
    implementationFormatter.WriteLine("namespace " + soul::ast::common::ToNamespaceName(moduleName) + " {");
    implementationFormatter.WriteLine();
    implementationFormatter.WriteLine("std::mutex ruleMtx;");
    implementationFormatter.WriteLine();
    implementationFormatter.WriteLine("std::map<std::int64_t, std::string>* GetRuleNameMapPtr()");
    implementationFormatter.WriteLine("{");
    implementationFormatter.IncIndent();
    implementationFormatter.WriteLine("std::lock_guard<std::mutex> lock(ruleMtx);");
    implementationFormatter.WriteLine("static std::map<std::int64_t, std::string> ruleNameMap = {");
    implementationFormatter.IncIndent();
    int n = spgFile->Rules().size();
    for (int i = 0; i < n; ++i)
    {
        soul::ast::spg::RuleParser* rule = spgFile->Rules()[i];
        std::string ruleName = rule->Grammar()->Name() + "." + rule->Name();
        implementationFormatter.Write("{ " + std::to_string(rule->Id()) + ", \"" + ruleName + "\" }");
        if (i != n - 1)
        {
            implementationFormatter.Write(",");
        }
        implementationFormatter.WriteLine();
    }
    implementationFormatter.DecIndent();
    implementationFormatter.WriteLine("};");
    implementationFormatter.WriteLine("return &ruleNameMap;");
    implementationFormatter.DecIndent();
    implementationFormatter.WriteLine("}");
    implementationFormatter.WriteLine();
    implementationFormatter.WriteLine("} // " + soul::ast::common::ToNamespaceName(moduleName));
    if (verbose)
    {
        std::cout << "==> " << implementationFilePath.generic_string() << std::endl;
    }
}

void GenerateParsers(soul::ast::spg::SpgFile* spgFile, soul::lexer::FileMap& fileMap, bool verbose, bool noDebugSupport, bool optimize, bool xml, bool ppstyle, 
    const std::string& version, soul::common::ModuleMap& moduleMap)
{
    std::cout << "generating parsers for project '" << spgFile->ProjectName() << "'..." << std::endl;
    std::string root = util::Path::GetDirectoryName(spgFile->FilePath());
    for (const auto& declaration : spgFile->Declarations())
    {
        switch (declaration->GetFileKind())
        {
            case soul::ast::spg::FileKind::parserFile:
            {
                soul::ast::spg::ParserFileDeclaration* parserFileDeclaration = static_cast<soul::ast::spg::ParserFileDeclaration*>(declaration.get());
                std::string parserFilePath = util::GetFullPath(util::Path::Combine(root, parserFileDeclaration->FilePath()));
                std::unique_ptr<soul::ast::spg::ParserFile> parserFile = soul::spg::ParseParserFile(parserFilePath, parserFileDeclaration->GetSourcePos(), 
                    fileMap, verbose, parserFileDeclaration->External());
                spgFile->AddParserFile(parserFile.release());
                break;
            }
        }
    }
    Link(spgFile, verbose, fileMap);
    std::unique_ptr<soul::ast::spg::SpgFile> optimizedSpg;
    if (optimize)
    {
        optimizedSpg = Optimize(spgFile, verbose, xml, fileMap);
        spgFile = optimizedSpg.get();
    }
    if (xml)
    {
        PrintXml(spgFile, verbose, optimize);
    }
    if (ppstyle)
    {
        GeneratePPCode(spgFile, verbose, noDebugSupport, version, fileMap, moduleMap);
    }
    else
    {
        GenerateCode(spgFile, verbose, noDebugSupport, version, fileMap);
    }
    GenerateRuleNameModule(spgFile, verbose, moduleMap, ppstyle);
    optimizedSpg.reset();
    std::cout << "parsers for project '" << spgFile->ProjectName() << "' generated successfully." << std::endl;
}

} // namespace soul::spg

