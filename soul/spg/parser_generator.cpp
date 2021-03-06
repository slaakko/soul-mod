// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.spg.parser.generator;

import std.filesystem;
import util;
import soul.spg.file.parsers;
import soul.spg.linking;
import soul.spg.code.generator;
import soul.ast.common;

namespace soul::spg {

void GenerateRuleNameModule(soul::ast::spg::SpgFile* spgFile, bool verbose)
{
    if (verbose)
    {
        std::cout << "generating rule name module..." << std::endl;
    }
    std::filesystem::path spgFilePath = spgFile->FilePath();
    std::filesystem::path root = spgFilePath.parent_path();
    std::filesystem::path interfaceFilePath = root / (spgFilePath.stem().generic_string() + "_rules.ixx");
    std::ofstream interfaceFile(interfaceFilePath);
    util::CodeFormatter interfaceFormatter(interfaceFile);
    std::string moduleName = spgFile->ProjectName() + ".rules";
    interfaceFormatter.WriteLine("export module " + moduleName + ";");
    interfaceFormatter.WriteLine();
    interfaceFormatter.WriteLine("import std.core;");
    interfaceFormatter.WriteLine();
    interfaceFormatter.WriteLine("export namespace " + soul::ast::common::ToNamespaceName(moduleName) + " {");
    interfaceFormatter.WriteLine();
    interfaceFormatter.WriteLine("std::map<int64_t, std::string>* GetRuleNameMapPtr();");
    interfaceFormatter.WriteLine();
    interfaceFormatter.WriteLine("} // " + soul::ast::common::ToNamespaceName(moduleName));
    if (verbose)
    {
        std::cout << "==> " << interfaceFilePath.generic_string() << std::endl;
    }

    std::filesystem::path implementationFilePath = root / (spgFilePath.stem().generic_string() + "_rules.cpp");
    std::ofstream implementationFile(implementationFilePath);
    util::CodeFormatter implementationFormatter(implementationFile);
    implementationFormatter.WriteLine("module " + moduleName + ";");
    implementationFormatter.WriteLine();
    implementationFormatter.WriteLine("namespace " + soul::ast::common::ToNamespaceName(moduleName) + " {");
    implementationFormatter.WriteLine();
    implementationFormatter.WriteLine("std::mutex ruleMtx;");
    implementationFormatter.WriteLine();
    implementationFormatter.WriteLine("std::map<int64_t, std::string>* GetRuleNameMapPtr()");
    implementationFormatter.WriteLine("{");
    implementationFormatter.IncIndent();
    implementationFormatter.WriteLine("std::lock_guard<std::mutex> lock(ruleMtx);");
    implementationFormatter.WriteLine("static std::map<int64_t, std::string> ruleNameMap = {");
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

void GenerateParsers(soul::ast::spg::SpgFile* spgFile, soul::lexer::FileMap& fileMap, bool verbose, bool noDebugSupport, const std::string& version)
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
    GenerateCode(spgFile, verbose, noDebugSupport, version, fileMap);
    GenerateRuleNameModule(spgFile, verbose);
    std::cout << "parsers for project '" << spgFile->ProjectName() << "' generated successfully." << std::endl;
}

} // namespace soul::spg
