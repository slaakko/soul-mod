// =================================
// Copyright (c) 2023 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.spg.pp.style.code.generator.visitor;

import util;
import soul.spg.array.generator;

namespace soul::spg {

PPStyleCodeGeneratorVisitor::PPStyleCodeGeneratorVisitor(soul::ast::spg::SpgFile* spgFile_, bool verbose_, bool noDebugSupport_, const std::string& version_, 
    soul::lexer::FileMap& fileMap_, soul::common::ModuleMap& moduleMap_) : CodeGeneratorVisitor(spgFile_, verbose_, noDebugSupport_, version_, fileMap_), moduleMap(moduleMap_)
{
}

void PPStyleCodeGeneratorVisitor::Visit(soul::ast::spg::ParserFile& parserFile)
{
    std::string root = util::Path::GetDirectoryName(util::GetFullPath(parserFile.FilePath()));
    if (parserFile.IsExternal())
    {
        if (verbose)
        {
            std::cout << "> " << parserFile.FilePath() << std::endl;
            std::cout << "skipping external parser file '" << parserFile.FilePath() << "'" << std::endl;
        }
        return;
    }
    if (verbose)
    {
        std::cout << "> " << parserFile.FilePath() << std::endl;
        std::cout << "generating code..." << std::endl;
    }
    sn = 0;
    stage = CodeGenerationStage::generateInterface;
    std::string interfaceFileName = parserFile.FilePath() + ".hpp";
    std::ofstream interfaceFile(interfaceFileName);
    util::CodeFormatter interfaceFormatter(interfaceFile);
    formatter = &interfaceFormatter;

    formatter->WriteLine();
    formatter->WriteLine("// this file has been automatically generated from '" + parserFile.FilePath() + "' using soul parser generator spg version " + version);
    formatter->WriteLine();
    soul::ast::common::ExportModule* mod = parserFile.ExportModule();
    moduleMap.MapModule(mod->ModuleName(), interfaceFileName);
    std::string includeGuard = "INCLUDE_GUARD_" + util::GetSha1MessageDigest(mod->ModuleName());
    formatter->WriteLine("#ifndef " + includeGuard);
    formatter->WriteLine("#define " + includeGuard);
    formatter->WriteLine();
    formatter->WriteLine("// export module " + mod->ModuleName() + ";");
    formatter->WriteLine();
    std::string soulLexerHeaderFilePath = moduleMap.GetHeaderFilePath("soul.lexer", root);
    if (!soulLexerHeaderFilePath.empty())
    {
        formatter->WriteLine("#include <" + soulLexerHeaderFilePath + ">");
    }
    std::string soulParserHeaderFilePath = moduleMap.GetHeaderFilePath("soul.parser", root);
    if (!soulParserHeaderFilePath.empty())
    {
        formatter->WriteLine("#include <" + soulParserHeaderFilePath + ">");
    }
    std::string utilHeaderFilePath = moduleMap.GetHeaderFilePath("util", root);
    if (!utilHeaderFilePath.empty())
    {
        formatter->WriteLine("#include <" + utilHeaderFilePath + ">");
    }
    std::string astSpgHeaderFilePath = moduleMap.GetHeaderFilePath("soul.ast.spg", root);
    if (!astSpgHeaderFilePath.empty())
    {
        formatter->WriteLine("#include <" + astSpgHeaderFilePath + ">");
    }
    for (const auto& imp : parserFile.Imports())
    {
        std::string moduleName = imp->ModuleName();
        std::string headerFilePath = moduleMap.GetHeaderFilePath(moduleName, root);
        if (!headerFilePath.empty())
        {
            formatter->WriteLine("#include <" + headerFilePath  + ">");
        }
    }
    formatter->WriteLine();
    formatter->WriteLine("namespace " + soul::ast::common::ToNamespaceName(mod->ModuleName()) + " {");
    formatter->WriteLine();
    bool first = true;
    for (const auto& parser : parserFile.Parsers())
    {
        if (first)
        {
            first = false;
        }
        else
        {
            formatter->WriteLine();
        }
        parser->Accept(*this);
    }
    formatter->WriteLine();
    formatter->WriteLine("} // namespace " + soul::ast::common::ToNamespaceName(mod->ModuleName()));
    formatter->WriteLine();
    formatter->WriteLine("#endif // " + includeGuard);

    if (verbose)
    {
        std::cout << "==> " << interfaceFileName << std::endl;
    }

    stage = CodeGenerationStage::generateImplementation;
    std::string implementationFileName = parserFile.FilePath() + ".cpp";
    std::ofstream implementationFile(implementationFileName);
    util::CodeFormatter implementationFormatter(implementationFile);
    formatter = &implementationFormatter;

    formatter->WriteLine();
    formatter->WriteLine("// this file has been automatically generated from '" + parserFile.FilePath() + "' using soul parser generator spg version " + version);
    formatter->WriteLine();
    std::string headerFileName = moduleMap.GetHeaderFilePath(mod->ModuleName(), util::Path::GetDirectoryName(implementationFileName));
    formatter->WriteLine("#include <" + headerFileName + ">");
    formatter->WriteLine();
    formatter->WriteLine("// module " + mod->ModuleName() + ";");
    formatter->WriteLine();

    formatter->WriteLine("namespace " + soul::ast::common::ToNamespaceName(mod->ModuleName()) + " {");
    formatter->WriteLine();
    GenerateArrays(parserFile, *formatter, sn);
    for (const auto& parser : parserFile.Parsers())
    {
        parser->Accept(*this);
    }
    formatter->WriteLine();
    bool hasLexers = false;
    for (const auto& parser : parserFile.Parsers())
    {
        for (const auto& lexer : parser->Lexers())
        {
            if (lexer->TypeSpecifiers().size() > 0)
            {
                soul::ast::cpp::TypeSpecifierNode* firstTypeSpecifier = lexer->TypeSpecifiers()[0].get();
                std::string charTypeName = "char";
                if (firstTypeSpecifier->Kind() == soul::ast::cpp::NodeKind::typeNameNode)
                {
                    soul::ast::cpp::TypeNameNode* lexerType = static_cast<soul::ast::cpp::TypeNameNode*>(firstTypeSpecifier);
                    if (lexerType->IsTemplate() && lexerType->TemplateArgs().size() > 0)
                    {
                        soul::ast::cpp::Node* firstTemplateArg = lexerType->TemplateArgs()[0].get();
                        charTypeName = firstTemplateArg->ToString();
                    }
                }
                hasLexers = true;
                formatter->WriteLine("template struct " + parser->Name() + "<soul::lexer::Lexer<" + lexer->ToString() + ", " + charTypeName + ">>;");
            }
        }
    }
    if (hasLexers)
    {
        formatter->WriteLine();
    }
    formatter->WriteLine("} // namespace " + soul::ast::common::ToNamespaceName(mod->ModuleName()));
    if (verbose)
    {
        std::cout << "==> " << implementationFileName << std::endl;
    }


}

} // namespace soul::spg
