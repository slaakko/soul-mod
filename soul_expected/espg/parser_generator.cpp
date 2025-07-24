// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul_expected.spg.parser.generator;

import util_expected;
import soul_expected.spg.file.parsers;
import soul_expected.spg.linking;
import soul_expected.spg.optimizer;
import soul_expected.spg.code.generator;
import soul_expected.spg.xml.printer;
import soul_expected.ast.common;

namespace soul_expected::spg {

std::expected<bool, int> GenerateRuleNameModule(soul_expected::ast::spg::SpgFile* spgFile, bool verbose)
{
    if (verbose)
    {
        std::cout << "generating rule name module..." << std::endl;
    }
    std::filesystem::path spgFilePath = spgFile->FilePath();
    std::filesystem::path root = spgFilePath.parent_path();
    std::filesystem::path interfaceFilePath;
    interfaceFilePath = root / (spgFilePath.stem().generic_string() + "_rules.cppm");
    std::ofstream interfaceFile(interfaceFilePath.generic_string());
    if (!interfaceFile) return std::unexpected<int>(util::AllocateError("could not create file '" + interfaceFilePath.generic_string() + "'"));
    util::CodeFormatter interfaceFormatter(interfaceFile);
    std::string moduleName = spgFile->ProjectName() + ".rules";
    std::string includeGuard;
    std::expected<bool, int> rv = interfaceFormatter.WriteLine("export module " + moduleName + ";");
    if (!rv) return rv;
    interfaceFormatter.WriteLine();
    rv = interfaceFormatter.WriteLine("import std;");
    if (!rv) return rv;
    interfaceFormatter.WriteLine();
    rv = interfaceFormatter.WriteLine("export namespace " + soul_expected::ast::common::ToNamespaceName(moduleName) + " {");
    if (!rv) return rv;
    interfaceFormatter.WriteLine();
    rv = interfaceFormatter.WriteLine("std::map<std::int64_t, std::string>* GetRuleNameMapPtr();");
    if (!rv) return rv;
    interfaceFormatter.WriteLine();
    rv = interfaceFormatter.WriteLine("} // " + soul_expected::ast::common::ToNamespaceName(moduleName));
    if (!rv) return rv;
    if (verbose)
    {
        std::cout << "==> " << interfaceFilePath.generic_string() << std::endl;
    }

    std::filesystem::path implementationFilePath = root / (spgFilePath.stem().generic_string() + "_rules.cpp");
    std::ofstream implementationFile(implementationFilePath.generic_string());
    if (!implementationFile) return std::unexpected<int>(util::AllocateError("could not create file '" + implementationFilePath.generic_string() + "'"));
    util::CodeFormatter implementationFormatter(implementationFile);
    rv = implementationFormatter.WriteLine("module " + moduleName + ";");
    if (!rv) return rv;
    implementationFormatter.WriteLine();
    rv = implementationFormatter.WriteLine("namespace " + soul_expected::ast::common::ToNamespaceName(moduleName) + " {");
    if (!rv) return rv;
    implementationFormatter.WriteLine();
    rv = implementationFormatter.WriteLine("std::mutex ruleMtx;");
    if (!rv) return rv;
    implementationFormatter.WriteLine();
    rv = implementationFormatter.WriteLine("std::map<std::int64_t, std::string>* GetRuleNameMapPtr()");
    if (!rv) return rv;
    rv = implementationFormatter.WriteLine("{");
    if (!rv) return rv;
    implementationFormatter.IncIndent();
    rv = implementationFormatter.WriteLine("std::lock_guard<std::mutex> lock(ruleMtx);");
    if (!rv) return rv;
    rv = implementationFormatter.WriteLine("static std::map<std::int64_t, std::string> ruleNameMap = {");
    if (!rv) return rv;
    implementationFormatter.IncIndent();
    int n = static_cast<int>(spgFile->Rules().size());
    for (int i = 0; i < n; ++i)
    {
        soul_expected::ast::spg::RuleParser* rule = spgFile->Rules()[i];
        std::string ruleName = rule->Grammar()->Name() + "." + rule->Name();
        rv = implementationFormatter.Write("{ " + std::to_string(rule->Id()) + ", \"" + ruleName + "\" }");
        if (!rv) return rv;
        if (i != n - 1)
        {
            rv = implementationFormatter.Write(",");
            if (!rv) return rv;
        }
        implementationFormatter.WriteLine();
    }
    implementationFormatter.DecIndent();
    rv = implementationFormatter.WriteLine("};");
    if (!rv) return rv;
    rv = implementationFormatter.WriteLine("return &ruleNameMap;");
    if (!rv) return rv;
    implementationFormatter.DecIndent();
    rv = implementationFormatter.WriteLine("}");
    if (!rv) return rv;
    implementationFormatter.WriteLine();
    rv = implementationFormatter.WriteLine("} // " + soul_expected::ast::common::ToNamespaceName(moduleName));
    if (!rv) return rv;
    if (verbose)
    {
        std::cout << "==> " << implementationFilePath.generic_string() << std::endl;
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> GenerateParsers(soul_expected::ast::spg::SpgFile* spgFile, soul_expected::lexer::FileMap& fileMap, bool verbose, bool noDebugSupport, 
    bool optimize, bool xml, const std::string& version)
{
    std::cout << "generating parsers for project '" << spgFile->ProjectName() << "'..." << std::endl;
    std::string root = util::Path::GetDirectoryName(spgFile->FilePath());
    for (const auto& declaration : spgFile->Declarations())
    {
        switch (declaration->GetFileKind())
        {
            case soul_expected::ast::spg::FileKind::parserFile:
            {
                soul_expected::ast::spg::ParserFileDeclaration* parserFileDeclaration = static_cast<soul_expected::ast::spg::ParserFileDeclaration*>(declaration.get());
                std::expected<std::string, int> fp = util::GetFullPath(util::Path::Combine(root, parserFileDeclaration->FilePath()));
                if (!fp) return std::unexpected<int>(fp.error());
                std::string parserFilePath = *fp;
                std::expected<std::unique_ptr<soul_expected::ast::spg::ParserFile>, int> rv = soul_expected::spg::ParseParserFile(
                    parserFilePath, parserFileDeclaration->GetSourcePos(), fileMap, verbose, parserFileDeclaration->External());
                if (!rv) return std::unexpected<int>(rv.error());
                std::unique_ptr<soul_expected::ast::spg::ParserFile> parserFile = std::move(*rv);
                spgFile->AddParserFile(parserFile.release());
                break;
            }
        }
    }
    std::expected<bool, int> rv = Link(spgFile, verbose, fileMap);
    if (!rv) return rv;
    std::unique_ptr<soul_expected::ast::spg::SpgFile> optimizedSpg;
    if (optimize)
    {
        std::expected<std::unique_ptr<soul_expected::ast::spg::SpgFile>, int> rv = Optimize(spgFile, verbose, xml, fileMap);
        if (!rv) return std::unexpected<int>(rv.error());
        optimizedSpg = std::move(*rv);
        spgFile = optimizedSpg.get();
    }
    if (xml)
    {
        rv = PrintXml(spgFile, verbose, optimize);
        if (!rv) return rv;
    }
    rv = GenerateCode(spgFile, verbose, noDebugSupport, version, fileMap);
    if (!rv) return rv;
    rv = GenerateRuleNameModule(spgFile, verbose);
    if (!rv) return rv;
    std::cout << "parsers for project '" << spgFile->ProjectName() << "' generated successfully." << std::endl;
    optimizedSpg.reset();
    return std::expected<bool, int>(true);
}

} // namespace soul_expected::spg

