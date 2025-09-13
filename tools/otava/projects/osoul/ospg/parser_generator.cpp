// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.spg.parser.generator;

import util;
import soul.spg.file.parsers;
import soul.spg.linking;
import soul.spg.optimizer;
import soul.spg.code.generator;
import soul.spg.xml.printer;
import soul.ast.common;

namespace soul::spg {

std::expected<bool, int> GenerateRuleNameModule(soul::ast::spg::SpgFile* spgFile, bool verbose)
{
    if (verbose)
    {
        std::cout << "generating rule name module..." << "\n";
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
    rv = interfaceFormatter.WriteLine("export namespace " + soul::ast::common::ToNamespaceName(moduleName) + " {");
    if (!rv) return rv;
    interfaceFormatter.WriteLine();
    rv = interfaceFormatter.WriteLine("std::map<std::int64_t, std::string>* GetRuleNameMapPtr();");
    if (!rv) return rv;
    interfaceFormatter.WriteLine();
    rv = interfaceFormatter.WriteLine("} // " + soul::ast::common::ToNamespaceName(moduleName));
    if (!rv) return rv;
    if (verbose)
    {
        std::cout << "==> " << interfaceFilePath.generic_string() << "\n";
    }

    std::filesystem::path implementationFilePath = root / (spgFilePath.stem().generic_string() + "_rules.cpp");
    std::ofstream implementationFile(implementationFilePath.generic_string());
    if (!implementationFile) return std::unexpected<int>(util::AllocateError("could not create file '" + implementationFilePath.generic_string() + "'"));
    util::CodeFormatter implementationFormatter(implementationFile);
    rv = implementationFormatter.WriteLine("module " + moduleName + ";");
    if (!rv) return rv;
    implementationFormatter.WriteLine();
    rv = implementationFormatter.WriteLine("namespace " + soul::ast::common::ToNamespaceName(moduleName) + " {");
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
        soul::ast::spg::RuleParser* rule = spgFile->Rules()[i];
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
    rv = implementationFormatter.WriteLine("} // " + soul::ast::common::ToNamespaceName(moduleName));
    if (!rv) return rv;
    if (verbose)
    {
        std::cout << "==> " << implementationFilePath.generic_string() << "\n";
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> GenerateParsers(soul::ast::spg::SpgFile* spgFile, soul::lexer::FileMap& fileMap, bool verbose, bool noDebugSupport,
    bool optimize, bool xml, const std::string& version)
{
    std::cout << "generating parsers for project '" << spgFile->ProjectName() << "'..." << "\n";
    std::string root = util::Path::GetDirectoryName(spgFile->FilePath());
    for (const auto& declaration : spgFile->Declarations())
    {
        switch (declaration->GetFileKind())
        {
        case soul::ast::common::FileKind::parserFile:
        {
            soul::ast::spg::ParserFileDeclaration* parserFileDeclaration = static_cast<soul::ast::spg::ParserFileDeclaration*>(declaration.get());
            std::expected<std::string, int> fp = util::GetFullPath(util::Path::Combine(root, parserFileDeclaration->FilePath()));
            if (!fp) return std::unexpected<int>(fp.error());
            std::string parserFilePath = *fp;
            std::expected<std::unique_ptr<soul::ast::spg::ParserFile>, int> rv = soul::spg::ParseParserFile(
                parserFilePath, parserFileDeclaration->GetSourcePos(), fileMap, verbose, parserFileDeclaration->External());
            if (!rv) return std::unexpected<int>(rv.error());
            std::unique_ptr<soul::ast::spg::ParserFile> parserFile = std::move(*rv);
            spgFile->AddParserFile(parserFile.release());
            break;
        }
        case soul::ast::common::FileKind::tokenFile:
        {
            soul::ast::spg::TokenFileDeclaration* tokenFileDeclaration = static_cast<soul::ast::spg::TokenFileDeclaration*>(declaration.get());
            auto rv = util::GetFullPath(util::Path::Combine(root, tokenFileDeclaration->FilePath()));
            if (!rv) return std::unexpected<int>(rv.error());
            std::string tokenFilePath = *rv;
            auto prv = soul::spg::ParseTokenFile(tokenFilePath, tokenFileDeclaration->GetSourcePos(), verbose,
                tokenFileDeclaration->External(), fileMap);
            if (!prv) return std::unexpected<int>(prv.error());
            std::unique_ptr<soul::ast::common::TokenFile> tokenFile = std::move(*prv);
            spgFile->AddTokenFile(tokenFile.release());
            break;
        }
        }
    }
    std::expected<bool, int> rv = Link(spgFile, verbose, fileMap);
    if (!rv) return rv;
    std::unique_ptr<soul::ast::spg::SpgFile> optimizedSpg;
    if (optimize)
    {
        std::expected<std::unique_ptr<soul::ast::spg::SpgFile>, int> rv = Optimize(spgFile, verbose, xml, fileMap);
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
    std::cout << "parsers for project '" << spgFile->ProjectName() << "' generated successfully." << "\n";
    optimizedSpg.reset();
    return std::expected<bool, int>(true);
}

} // namespace soul::spg
