// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul_expected.slg.lexer.generator;

import util_expected;
import soul_expected.slg.classmap;
import soul_expected.slg.file.parsers;
import soul_expected.slg.token.generator;
import soul_expected.slg.regular.expression.parser;
import soul_expected.slg.code.modifier;
import soul_expected.ast.re;
import soul_expected.ast.cpp;
import soul_expected.ast.common;
import soul_expected.ast.source.pos;
import soul_expected.lexer;

namespace soul_expected::slg {

std::expected<bool, int> MakeNfas(soul_expected::ast::re::LexerContext& lexerContext)
{
    for (auto& rule : lexerContext.GetLexer()->Rules())
    {
        std::expected<soul_expected::ast::re::Nfa, int> rv = lexerContext.GetExprParser()->Parse(rule->Expr(), &lexerContext, lexerContext.FileName(), rule->Line());
        if (!rv) return std::unexpected<int>(rv.error());
        soul_expected::ast::re::Nfa* nfa = new soul_expected::ast::re::Nfa(std::move(*rv));
        nfa->End()->SetRuleIndex(rule->Index());
        int nfaIndex = lexerContext.AddNfa(nfa);
        rule->SetNfaIndex(nfaIndex);
    }
    if (lexerContext.Debug())
    {
        std::string nfaFilePath = util::Path::Combine(lexerContext.Base(), "NFA.debug.txt");
        std::ofstream nfaFile(nfaFilePath);
        if (!nfaFile)
        {
            return std::unexpected<int>(util::AllocateError("could not create file '" + nfaFilePath + "'"));
        }
        util::CodeFormatter formatter(nfaFile);
        for (soul_expected::ast::re::NfaState* state : lexerContext.NfaStates())
        {
            std::expected<bool, int> rv = state->Print(formatter);
            if (!rv) return rv;
        }
        if (lexerContext.Verbose())
        {
            std::cout << "==> " << nfaFilePath << "\n";
        }
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> MakeCanonicalClasses(soul_expected::ast::re::LexerContext& lexerContext)
{
    std::vector<soul_expected::ast::re::Symbol*> s = lexerContext.Symbols();
    for (soul_expected::ast::re::Symbol* symbol : s)
    {
        if (symbol->Contained()) continue;
        if (symbol->Kind() == soul_expected::ast::re::SymbolKind::classSymbol)
        {
            soul_expected::ast::re::Class* cls = static_cast<soul_expected::ast::re::Class*>(symbol);
            std::expected<soul_expected::ast::re::Class*, int> rv = cls->MakeCanonical(lexerContext);
            if (!rv) return std::unexpected<int>(rv.error());
            soul_expected::ast::re::Class* canonicalClass = *rv;
            lexerContext.AddCanonicalClass(canonicalClass);
        }
        else if (symbol->Kind() == soul_expected::ast::re::SymbolKind::charSymbol)
        {
            soul_expected::ast::re::CharSymbol* chr = static_cast<soul_expected::ast::re::CharSymbol*>(symbol);
            soul_expected::ast::re::Class* canonicalClass = new soul_expected::ast::re::Class(-1);
            canonicalClass->Ranges().push_back(soul_expected::ast::re::Range(chr->Chr(), chr->Chr()));
            lexerContext.AddCanonicalClass(canonicalClass);
        }
        else if (symbol->Kind() == soul_expected::ast::re::SymbolKind::anySymbol)
        {
            std::expected<soul_expected::ast::re::Symbol*, int> rv = lexerContext.MakeRange(static_cast<char32_t>(1), static_cast<char32_t>(0x10FFFF));
            if (!rv) return std::unexpected<int>(rv.error());
            soul_expected::ast::re::Symbol* range = *rv;
            soul_expected::ast::re::Class* canonicalClass = new soul_expected::ast::re::Class(-1);
            canonicalClass->Ranges().push_back(soul_expected::ast::re::Range(static_cast<char32_t>(1), static_cast<char32_t>(0x10FFFF)));
            lexerContext.AddCanonicalClass(canonicalClass);
        }
        else if (symbol->Kind() == soul_expected::ast::re::SymbolKind::rangeSymbol)
        {
            soul_expected::ast::re::Range* range = static_cast<soul_expected::ast::re::Range*>(symbol);
            soul_expected::ast::re::Class* canonicalClass = new soul_expected::ast::re::Class(-1);
            canonicalClass->Ranges().push_back(*range);
            lexerContext.AddCanonicalClass(canonicalClass);
        }
    }
    int index = 0;
    for (soul_expected::ast::re::Class* canonicalClass : lexerContext.CanonicalClasses())
    {
        canonicalClass->SetIndex(index++);
        for (const soul_expected::ast::re::Range& range : canonicalClass->Ranges())
        {
            if (canonicalClass->Chars().empty())
            {
                canonicalClass->AddChar(range.Start());
            }
            break;
        }
    }
    if (lexerContext.Debug())
    {
        std::string classFilePath = util::Path::Combine(lexerContext.Base(), "CLASS.debug.txt");
        std::ofstream classFile(classFilePath);
        if (!classFile)
        {
            return std::unexpected<int>(util::AllocateError("could not create file '" + classFilePath + "'"));
        }
        util::CodeFormatter formatter(classFile);
        for (soul_expected::ast::re::Class* canonicalClass : lexerContext.CanonicalClasses())
        {
            std::expected<bool, int> rv = canonicalClass->Print(formatter);
            if (!rv) return rv;
        }
        if (lexerContext.Verbose())
        {
            std::cout << "==> " << classFilePath << "\n";
        }
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> MakeClassPartition(soul_expected::ast::re::LexerContext& lexerContext)
{
    std::list<soul_expected::ast::re::Class*> classes;
    for (soul_expected::ast::re::Class* cls : lexerContext.CanonicalClasses())
    {
        classes.push_back(cls);
    }
    auto classIt = classes.begin();
    while (classIt != classes.end())
    {
        bool classChanged = false;
        soul_expected::ast::re::Class* cls = *classIt;
        auto sourceIt = classes.begin();
        while (!cls->Ranges().empty() && sourceIt != classes.end())
        {
            if (sourceIt == classIt)
            {
                ++sourceIt;
                continue;
            }
            bool sourceChanged = false;
            soul_expected::ast::re::Class* source = *sourceIt;
            std::unique_ptr<soul_expected::ast::re::Class> splitClass(new soul_expected::ast::re::Class(-1));
            auto leftIt = cls->Ranges().begin();
            while (leftIt != cls->Ranges().end())
            {
                bool leftChanged = false;
                auto rightIt = source->Ranges().begin();
                while (leftIt != cls->Ranges().end() && rightIt != source->Ranges().end())
                {
                    bool rightChanged = false;
                    if (soul_expected::ast::re::Intersect(*leftIt, *rightIt))
                    {
                        std::vector<soul_expected::ast::re::Range> leftRanges = *leftIt - *rightIt;
                        std::vector<soul_expected::ast::re::Range> rightRanges = *rightIt - *leftIt;
                        soul_expected::ast::re::Range intersection = *leftIt & *rightIt;
                        for (const soul_expected::ast::re::Range& leftRange : leftRanges)
                        {
                            if (leftRange.IsEmpty()) continue;
                            auto it = leftIt;
                            ++it;
                            cls->Ranges().insert(it, leftRange);
                        }
                        leftIt = cls->Ranges().erase(leftIt);
                        leftChanged = true;
                        if (!intersection.IsEmpty())
                        {
                            splitClass->Ranges().push_back(intersection);
                        }
                        for (const soul_expected::ast::re::Range& rightRange : rightRanges)
                        {
                            if (rightRange.IsEmpty()) continue;
                            auto it = rightIt;
                            ++it;
                            source->Ranges().insert(it, rightRange);
                        }
                        rightIt = source->Ranges().erase(rightIt);
                        rightChanged = true;
                    }
                    if (!rightChanged)
                    {
                        ++rightIt;
                    }
                }
                if (!leftChanged)
                {
                    ++leftIt;
                }
            }
            if (source->Ranges().empty())
            {
                sourceIt = classes.erase(sourceIt);
                sourceChanged = true;
            }
            if (!splitClass->Ranges().empty())
            {
                classes.insert(sourceIt, splitClass.get());
                lexerContext.AddToSymbols(splitClass.release());
                sourceChanged = true;
            }
            if (!sourceChanged)
            {
                ++sourceIt;
            }
        }
        if (cls->Ranges().empty())
        {
            classIt = classes.erase(classIt);
            classChanged = true;
        }
        if (!classChanged)
        {
            ++classIt;
        }
    }
    for (soul_expected::ast::re::Class* cls : classes)
    {
        cls->MakeMinimal(lexerContext);
        lexerContext.AddToPartition(cls);
    }
    for (int i = 0; i < lexerContext.Partition().size(); ++i)
    {
        soul_expected::ast::re::Class* cls = lexerContext.Partition()[i];
        cls->SetIndex(i);
    }
    if (lexerContext.Debug())
    {
        std::string partitionFilePath = util::Path::Combine(lexerContext.Base(), "PARTITION.debug.txt");
        std::ofstream partitionFile(partitionFilePath);
        if (!partitionFile)
        {
            return std::unexpected<int>(util::AllocateError("could not create file '" + partitionFilePath + "'"));
        }
        util::CodeFormatter formatter(partitionFile);
        for (int i = 0; i < lexerContext.Partition().size(); ++i)
        {
            soul_expected::ast::re::Class* cls = lexerContext.Partition()[i];
            std::expected<bool, int> rv = cls->Print(formatter);
            if (!rv) return rv;
        }
        if (lexerContext.Verbose())
        {
            std::cout << "==> " << partitionFilePath << "\n";
        }
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> MakeClassMap(soul_expected::ast::re::LexerContext& lexerContext, const std::string& root, bool verbose)
{
    std::vector<std::int32_t> classMapVec(0x110000, -1);
    for (soul_expected::ast::re::Class* cls : lexerContext.Partition())
    {
        for (const soul_expected::ast::re::Range& range : cls->Ranges())
        {
            for (char32_t i = range.Start(); i <= range.End(); ++i)
            {
                if (classMapVec[i] == -1)
                {
                    classMapVec[static_cast<std::int32_t>(i)] = cls->Index();
                }
            }
        }
    }
    std::string moduleName;
    soul_expected::ast::slg::Lexer* lexer = lexerContext.GetLexer();
    soul_expected::ast::common::File* file = lexer->GetFile();
    if (file->Kind() == soul_expected::ast::common::FileKind::lexerFile)
    {
        soul_expected::ast::slg::LexerFile* lexerFile = static_cast<soul_expected::ast::slg::LexerFile*>(file);
        soul_expected::ast::common::ExportModule* mod = lexerFile->GetExportModule();
        moduleName = mod->ModuleName();
    }
    else
    {
        return std::unexpected<int>(util::AllocateError("lexer file expected"));
    }
    std::string classMapName = moduleName + ".classmap";
    std::string classMapFileName = util::Path::Combine(root, classMapName);
    util::FileStream fileStream(classMapFileName, util::OpenMode::binary | util::OpenMode::write);
    if (!fileStream) return std::unexpected<int>(fileStream.Error());
    util::BufferedStream bufferedStream(fileStream);
    util::BinaryStreamWriter writer(bufferedStream);
    std::int32_t size = static_cast<std::int32_t>(classMapVec.size());
    std::expected<bool, int> rv = writer.Write(size);
    if (!rv) return rv;
    // size = 0x110000
    for (std::int32_t x : classMapVec)
    {
        rv = writer.Write(x);
        if (!rv) return rv;
    }
    if (verbose)
    {
        std::cout << "==> " << classMapFileName << std::endl;
    }
    if (lexerContext.Debug())
    {
        std::string classMapFilePath = util::Path::Combine(lexerContext.Base(), "CLASSMAP.debug.txt");
        std::ofstream classMapFile(classMapFilePath);
        if (!classMapFile)
        {
            return std::unexpected<int>(util::AllocateError("could not create file '" + classMapFilePath + "'"));
        }
        util::CodeFormatter formatter(classMapFile);
        std::expected<bool, int> rv = formatter.WriteLine("CLASSMAP:");
        if (!rv) return rv;
        int32_t i = 0;
        for (std::int32_t x : classMapVec)
        {
            rv = formatter.WriteLine(std::to_string(i) + " : " + std::to_string(x));
            if (!rv) return rv;
            ++i;
        }
        if (lexerContext.Verbose())
        {
            std::cout << "==> " << classMapFilePath << "\n";
        }
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> CompressClassMap(soul_expected::ast::re::LexerContext& lexerContext, const std::string& root, bool verbose)
{
    std::string moduleName;
    soul_expected::ast::slg::Lexer* lexer = lexerContext.GetLexer();
    soul_expected::ast::common::File* file = lexer->GetFile();
    if (file->Kind() == soul_expected::ast::common::FileKind::lexerFile)
    {
        soul_expected::ast::slg::LexerFile* lexerFile = static_cast<soul_expected::ast::slg::LexerFile*>(file);
        soul_expected::ast::common::ExportModule* mod = lexerFile->GetExportModule();
        moduleName = mod->ModuleName();
    }
    else
    {
        return std::unexpected<int>(util::AllocateError("lexer file expected"));
    }
    std::string classMapName = moduleName + ".classmap";
    std::expected<bool, int> rv = MakeCompressedClassMap(root, classMapName, verbose);
    if (!rv) return rv;
    rv = MakeResourceFile(root, classMapName, verbose);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> MakeMasterNfa(soul_expected::ast::re::LexerContext& lexerContext)
{
    soul_expected::ast::re::Nfa* masterNfa = new soul_expected::ast::re::Nfa();
    int masterNfaIndex = lexerContext.AddNfa(masterNfa);
    lexerContext.SetMasterNfaIndex(masterNfaIndex);
    soul_expected::ast::re::NfaState* start = lexerContext.MakeNfaState();
    masterNfa->SetStart(start);
    soul_expected::ast::slg::Lexer* lexer = lexerContext.GetLexer();
    for (const auto& rule : lexer->Rules())
    {
        std::expected< soul_expected::ast::re::Nfa*, int> rv = lexerContext.GetNfa(rule->NfaIndex());
        if (!rv) return std::unexpected<int>(rv.error());
        soul_expected::ast::re::Nfa* ruleNfa = *rv;
        start->AddEdge(soul_expected::ast::re::NfaEdge(lexerContext.MakeEpsilon(), ruleNfa->Start()));
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> MakeDfa(soul_expected::ast::re::LexerContext& lexerContext)
{
    std::expected< soul_expected::ast::re::Nfa*, int> rv = lexerContext.GetNfa(lexerContext.MasterNfaIndex());
    if (!rv) return std::unexpected<int>(rv.error());
    soul_expected::ast::re::Nfa* masterNfa = *rv;
    std::expected<soul_expected::ast::re::Dfa, int> drv = soul_expected::ast::re::Compile(lexerContext, *masterNfa);
    if (!drv) return std::unexpected<int>(drv.error());
    soul_expected::ast::re::Dfa dfa = std::move(*drv);
    lexerContext.SetDfa(std::move(dfa));
    if (lexerContext.Debug())
    {
        std::string dfaFilePath = util::Path::Combine(lexerContext.Base(), "DFA.debug.txt");
        std::ofstream dfaFile(dfaFilePath);
        if (!dfaFile)
        {
            return std::unexpected<int>(util::AllocateError("could not create file '" + dfaFilePath + "'"));
        }
        util::CodeFormatter formatter(dfaFile);
        std::expected<bool, int> rv = lexerContext.GetDfa().Print(lexerContext, formatter);
        if (!rv) return rv;
        if (lexerContext.Verbose())
        {
            std::cout << "==> " << dfaFilePath << "\n";
        }
    }
    return std::expected<bool, int>(true);
}

std::expected<std::string, int> GetTokenCppId(soul_expected::ast::slg::LexerFile* lexerFile, soul_expected::lexer::FileMap& fileMap, 
    const soul_expected::ast::SourcePos& sourcePos,  const std::string& tokenName)
{
    soul_expected::ast::common::TokenMap* tokenMap = lexerFile->GetTokenMap();
    if (tokenMap)
    {
        std::vector<soul_expected::ast::common::Token*> tokens = tokenMap->GetTokens(tokenName);
        int n = static_cast<int>(tokens.size());
        if (n == 1)
        {
            soul_expected::ast::common::Token* token = tokens.front();
            return token->FullCppId();
        }
        else if (n > 1)
        {
            std::string tokenString;
            for (int i = 0; i < n; ++i)
            {
                soul_expected::ast::common::Token* token = tokens[i];
                if (i > 0)
                {
                    tokenString.append(" or\n");
                }
                tokenString.append(token->FullName());
            }
            std::expected<std::string, int> rv = soul_expected::lexer::MakeMessage("error", "ambiguous reference to token '" + tokenName + "' in lexer file '" +
                lexerFile->FilePath() + "':\n" + tokenString, sourcePos, fileMap);
            if (!rv) return rv;
            std::string errorMessage = *rv;
            return std::unexpected<int>(util::AllocateError(errorMessage));
        }
        else
        {
            std::expected<std::string, int> rv = soul_expected::lexer::MakeMessage("error", "token '" + tokenName + "' not found in lexer file '" +
                lexerFile->FilePath(), sourcePos, fileMap);
            if (!rv) return rv;
            std::string errorMessage = *rv;
            return std::unexpected<int>(util::AllocateError(errorMessage));
        }
    }
    else
    {
        return std::unexpected<int>(util::AllocateError("token map not set"));
    }
}

std::expected<bool, int> WriteVariables(soul_expected::ast::re::LexerContext& lexerContext, util::CodeFormatter& interfaceFormatter, util::CodeFormatter sourceFormatter)
{
    soul_expected::ast::slg::Lexer* lexer = lexerContext.GetLexer();
    std::string variableClassName = lexer->Name() + "_Variables";
    lexer->SetVariableClassName(variableClassName);
    std::expected<bool, int> rv = interfaceFormatter.WriteLine("struct " + variableClassName + " : public soul_expected::lexer::Variables");
    if (!rv) return rv;
    rv = interfaceFormatter.WriteLine("{");
    if (!rv) return rv;
    interfaceFormatter.IncIndent();
    rv = interfaceFormatter.WriteLine(variableClassName + "();");
    if (!rv) return rv;
    bool hasVariables = false;
    for (const auto& var : lexer->Variables())
    {
        rv = var->Type()->Write(interfaceFormatter);
        if (!rv) return rv;
        rv = interfaceFormatter.Write(" ");
        if (!rv) return rv;
        rv = interfaceFormatter.WriteLine(var->Name() + ";");
        if (!rv) return rv;
        hasVariables = true;
    }
    interfaceFormatter.DecIndent();
    rv = interfaceFormatter.WriteLine("};");
    if (!rv) return rv;
    sourceFormatter.WriteLine();
    rv = sourceFormatter.Write(variableClassName + "::" + variableClassName + "()");
    if (!rv) return rv;
    if (hasVariables)
    {
        rv = sourceFormatter.Write(" :");
        if (!rv) return rv;
    }
    sourceFormatter.WriteLine();
    sourceFormatter.IncIndent();
    bool first = true;
    for (const auto& var : lexer->Variables())
    {
        if (first)
        {
            first = false;
        }
        else
        {
            rv = sourceFormatter.Write(", ");
            if (!rv) return rv;
        }
        rv = sourceFormatter.Write(var->Name() + "()");
        if (!rv) return rv;
    }
    if (hasVariables)
    {
        sourceFormatter.WriteLine();
    }
    sourceFormatter.DecIndent();
    rv = sourceFormatter.WriteLine("{");
    if (!rv) return rv;
    rv = sourceFormatter.WriteLine("}");
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> WriteLexer(soul_expected::ast::re::LexerContext& lexerContext, soul_expected::ast::slg::SlgFile* slgFile, const std::string& root, 
    soul_expected::lexer::FileMap& fileMap, bool verbose)
{
    std::string interfaceFilePath;
    std::expected<std::string, int> fp = util::GetFullPath(util::Path::Combine(root, lexerContext.FileName() + ".cppm"));
    if (!fp) return std::unexpected<int>(fp.error());
    interfaceFilePath = *fp;
    fp = util::GetFullPath(util::Path::Combine(root, lexerContext.FileName() + ".cpp"));
    if (!fp) return std::unexpected<int>(fp.error());
    std::string sourceFilePath = *fp;
    std::ofstream interfaceStream(interfaceFilePath);
    if (!interfaceStream) return std::unexpected<int>(util::AllocateError("could not create file '" + interfaceFilePath + "'"));
    util::CodeFormatter interfaceFormatter(interfaceStream);
    std::expected<bool, int> rv = interfaceFormatter.WriteLine("// this file has been automatically generated from '" + 
        lexerContext.FileName() + "' using soul lexer generator eslg version " + util::SoulVersionStr());
    if (!rv) return rv;
    interfaceFormatter.WriteLine();
    std::ofstream sourceStream(sourceFilePath);
    if (!sourceStream) return std::unexpected<int>(util::AllocateError("could not create file '" + sourceFilePath + "'"));
    util::CodeFormatter sourceFormatter(sourceStream);
    rv = sourceFormatter.WriteLine("// this file has been automatically generated from '" + lexerContext.FileName() + "' using soul lexer generator eslg version " +
        util::SoulVersionStr());
    if (!rv) return rv;
    sourceFormatter.WriteLine();
    soul_expected::ast::slg::Lexer* lexer = lexerContext.GetLexer();
    soul_expected::ast::common::File* file = lexer->GetFile();
    soul_expected::ast::slg::LexerFile* lexerFile = nullptr;
    std::string moduleName;
    if (file->Kind() == soul_expected::ast::common::FileKind::lexerFile)
    {
        lexerFile = static_cast<soul_expected::ast::slg::LexerFile*>(file);
        soul_expected::ast::common::ExportModule* mod = lexerFile->GetExportModule();
        moduleName = mod->ModuleName();
    }
    else
    {
        return std::unexpected<int>(util::AllocateError("lexer file expected"));
    }
    rv = sourceFormatter.WriteLine("module " + moduleName + ";");
    if (!rv) return rv;
    sourceFormatter.WriteLine();
    rv = interfaceFormatter.WriteLine("export module " + moduleName + ";");
    if (!rv) return rv;
    interfaceFormatter.WriteLine();
    rv = interfaceFormatter.WriteLine("import std;");
    if (!rv) return rv;
    rv = interfaceFormatter.WriteLine("import soul_expected.lexer;");
    if (!rv) return rv;
    rv = interfaceFormatter.WriteLine("import soul_expected.ast.slg;");
    if (!rv) return rv;
    rv = interfaceFormatter.WriteLine("import soul_expected.ast.common;");
    if (!rv) return rv;
    rv = interfaceFormatter.WriteLine("import util_expected;");
    if (!rv) return rv;
    for (const auto& imprt : lexerFile->Imports())
    {
        std::expected<soul_expected::ast::common::Collection*, int> crv = slgFile->GetCollection(imprt->ModuleName());
        if (!crv) return std::unexpected<int>(crv.error());
        soul_expected::ast::common::Collection* collection = *crv;
        if (collection->Kind() == soul_expected::ast::common::CollectionKind::tokenCollection)
        {
            rv = interfaceFormatter.WriteLine("import " + collection->Name() + ";");
            if (!rv) return rv;
        }
    }
    interfaceFormatter.WriteLine();
    sourceFormatter.WriteLine();
    rv = interfaceFormatter.WriteLine("export namespace " + soul_expected::ast::common::ToNamespaceName(moduleName) + " {");
    if (!rv) return rv;
    interfaceFormatter.WriteLine();
    rv = interfaceFormatter.WriteLine("std::mutex& MakeLexerMtx();");
    if (!rv) return rv;
    interfaceFormatter.WriteLine();
    rv = interfaceFormatter.WriteLine("template<typename CharT>");
    if (!rv) return rv;
    rv = interfaceFormatter.WriteLine("struct " + lexer->Name() + ";");
    if (!rv) return rv;
    interfaceFormatter.WriteLine();
    rv = interfaceFormatter.WriteLine("template<typename CharT>");
    if (!rv) return rv;
    rv = interfaceFormatter.WriteLine("std::expected<soul_expected::lexer::Lexer<" + lexer->Name() + "<CharT>, CharT>, int> MakeLexer(" + 
        "const CharT* start, const CharT* end, const std::string& fileName);");
    if (!rv) return rv;
    interfaceFormatter.WriteLine();
    rv = interfaceFormatter.WriteLine("template<typename CharT>");
    if (!rv) return rv;
    rv = interfaceFormatter.WriteLine("std::expected<soul_expected::lexer::Lexer<" + lexer->Name() + "<CharT>, CharT>, int> MakeLexer(" + 
        "const std::string& moduleFileName, util::ResourceFlags resourceFlags, const CharT* start, const CharT* end, const std::string& fileName);");
    if (!rv) return rv;
    interfaceFormatter.WriteLine();
    rv = interfaceFormatter.WriteLine("soul_expected::ast::common::TokenCollection* GetTokens();");
    if (!rv) return rv;
    interfaceFormatter.WriteLine();
    rv = sourceFormatter.WriteLine("namespace " + soul_expected::ast::common::ToNamespaceName(moduleName) + " {");
    if (!rv) return rv;
    sourceFormatter.WriteLine();
    rv = sourceFormatter.WriteLine("soul_expected::ast::common::TokenCollection* GetTokens()");
    if (!rv) return rv;
    rv = sourceFormatter.WriteLine("{");
    if (!rv) return rv;
    sourceFormatter.IncIndent();
    rv = sourceFormatter.WriteLine("static soul_expected::ast::common::TokenCollection tokens(\"" + moduleName + ".tokens\");");
    if (!rv) return rv;
    rv = sourceFormatter.WriteLine("if (!tokens.Initialized())");
    if (!rv) return rv;
    rv = sourceFormatter.WriteLine("{");
    if (!rv) return rv;
    sourceFormatter.IncIndent();
    rv = sourceFormatter.WriteLine("tokens.SetInitialized();");
    if (!rv) return rv;
    soul_expected::ast::slg::Tokens* tokens = lexerContext.GetTokens();
    for (const auto& token : tokens->GetTokens())
    {
        rv = sourceFormatter.WriteLine("tokens.AddToken(new soul_expected::ast::common::Token(" + token->FullCppId() + ", \"" + token->Name() + "\", \"" + token->Info() + "\"));");
        if (!rv) return rv;
    }
    sourceFormatter.DecIndent();
    rv = sourceFormatter.WriteLine("}");
    if (!rv) return rv;
    rv = sourceFormatter.WriteLine("return &tokens;");
    if (!rv) return rv;
    sourceFormatter.DecIndent();
    rv = sourceFormatter.WriteLine("}");
    if (!rv) return rv;
    rv = WriteVariables(lexerContext, interfaceFormatter, sourceFormatter);
    if (!rv) return rv;
    interfaceFormatter.WriteLine();
    rv = interfaceFormatter.WriteLine("template<typename CharT>");
    if (!rv) return rv;
    rv = interfaceFormatter.WriteLine("struct " + lexer->Name());
    if (!rv) return rv;
    rv =interfaceFormatter.WriteLine("{");
    if (!rv) return rv;
    interfaceFormatter.IncIndent();
    rv = interfaceFormatter.WriteLine("using Variables = " + lexer->VariableClassName() + ";");
    if (!rv) return rv;
    interfaceFormatter.WriteLine();
    rv = interfaceFormatter.WriteLine("static std::int32_t NextState(std::int32_t state, CharT chr, soul_expected::lexer::LexerBase<CharT>& lexer)");
    if (!rv) return rv;
    rv = interfaceFormatter.WriteLine("{");
    if (!rv) return rv;
    interfaceFormatter.IncIndent();
    rv = interfaceFormatter.WriteLine("soul_expected::lexer::ClassMap<CharT>* classmap = lexer.GetClassMap();");
    if (!rv) return rv;
    rv = interfaceFormatter.WriteLine("std::int32_t cls = classmap->GetClass(chr);");
    if (!rv) return rv;
    rv = interfaceFormatter.WriteLine("switch (state)");
    if (!rv) return rv;
    rv = interfaceFormatter.WriteLine("{");
    if (!rv) return rv;
    interfaceFormatter.IncIndent();
    for (const auto& state : lexerContext.GetDfa().States())
    {
        rv = interfaceFormatter.WriteLine("case " + std::to_string(state->Id()) + ":");
        if (!rv) return rv;
        rv = interfaceFormatter.WriteLine("{");
        if (!rv) return rv;
        interfaceFormatter.IncIndent();
        if (state->Accept())
        {
            rv = interfaceFormatter.WriteLine("auto& token = lexer.CurrentToken();");
            if (!rv) return rv;
            rv = interfaceFormatter.WriteLine("auto prevMatch = token.match;");
            if (!rv) return rv;
            rv = interfaceFormatter.WriteLine("token.match = lexer.CurrentLexeme();");
            if (!rv) return rv;
            rv = interfaceFormatter.WriteLine("std::int64_t tokenId = GetTokenId(" + std::to_string(state->RuleIndex()) + ", lexer);");
            if (!rv) return rv;
            rv = interfaceFormatter.WriteLine("if (tokenId == soul_expected::lexer::CONTINUE_TOKEN)");
            if (!rv) return rv;
            rv = interfaceFormatter.WriteLine("{");
            if (!rv) return rv;
            interfaceFormatter.IncIndent();
            rv = interfaceFormatter.WriteLine("token.id = soul_expected::lexer::CONTINUE_TOKEN;");
            if (!rv) return rv;
            rv = interfaceFormatter.WriteLine("return -1;");
            if (!rv) return rv;
            interfaceFormatter.DecIndent();
            rv = interfaceFormatter.WriteLine("}");
            if (!rv) return rv;
            rv = interfaceFormatter.WriteLine("else if (tokenId != soul_expected::lexer::INVALID_TOKEN)");
            if (!rv) return rv;
            rv = interfaceFormatter.WriteLine("{");
            if (!rv) return rv;
            interfaceFormatter.IncIndent();
            rv = interfaceFormatter.WriteLine("token.id = tokenId;");
            if (!rv) return rv;
            interfaceFormatter.DecIndent();
            rv = interfaceFormatter.WriteLine("}");
            if (!rv) return rv;
            rv = interfaceFormatter.WriteLine("else");
            if (!rv) return rv;
            rv = interfaceFormatter.WriteLine("{");
            if (!rv) return rv;
            interfaceFormatter.IncIndent();
            rv = interfaceFormatter.WriteLine("token.match = prevMatch;");
            if (!rv) return rv;
            interfaceFormatter.DecIndent();
            rv = interfaceFormatter.WriteLine("}");
            if (!rv) return rv;
        }
        std::map<std::int32_t, std::set<std::int32_t>> m;
        for (soul_expected::ast::re::Class* cls : lexerContext.Partition())
        {
            soul_expected::ast::re::DfaState* next = state->Next(cls->Index());
            if (next != nullptr)
            {
                m[next->Id()].insert(cls->Index());
            }
        }
        if (m.empty())
        {
            rv = interfaceFormatter.WriteLine("return -1;");
            if (!rv) return rv;
        }
        else
        {
            rv = interfaceFormatter.WriteLine("switch (cls)");
            if (!rv) return rv;
            rv = interfaceFormatter.WriteLine("{");
            if (!rv) return rv;
            interfaceFormatter.IncIndent();
            for (const auto& p : m)
            {
                std::int32_t n = p.first;
                const std::set<std::int32_t>& s = p.second;
                for (std::int32_t k : s)
                {
                    rv =interfaceFormatter.WriteLine("case " + std::to_string(k) + ":");
                    if (!rv) return rv;
                }
                rv = interfaceFormatter.WriteLine("{");
                if (!rv) return rv;
                interfaceFormatter.IncIndent();
                rv = interfaceFormatter.WriteLine("return " + std::to_string(n) + ";");
                if (!rv) return rv;
                interfaceFormatter.DecIndent();
                rv = interfaceFormatter.WriteLine("}");
                if (!rv) return rv;
            }
            rv = interfaceFormatter.WriteLine("default:");
            if (!rv) return rv;
            rv = interfaceFormatter.WriteLine("{");
            if (!rv) return rv;
            interfaceFormatter.IncIndent();
            rv = interfaceFormatter.WriteLine("return -1;");
            if (!rv) return rv;
            interfaceFormatter.DecIndent();
            rv = interfaceFormatter.WriteLine("}");
            if (!rv) return rv;
            interfaceFormatter.DecIndent();
            rv = interfaceFormatter.WriteLine("}");
            if (!rv) return rv;
        }
        interfaceFormatter.DecIndent();
        rv = interfaceFormatter.WriteLine("}");
        if (!rv) return rv;
    }
    interfaceFormatter.DecIndent();
    rv = interfaceFormatter.WriteLine("}");
    if (!rv) return rv;
    rv = interfaceFormatter.WriteLine("return -1;");
    if (!rv) return rv;
    interfaceFormatter.DecIndent();
    rv = interfaceFormatter.WriteLine("}");
    if (!rv) return rv;
    interfaceFormatter.WriteLine();
    rv = interfaceFormatter.WriteLine("static std::int64_t GetTokenId(std::int32_t ruleIndex, soul_expected::lexer::LexerBase<CharT>& lexer)");
    if (!rv) return rv;
    rv = interfaceFormatter.WriteLine("{");
    if (!rv) return rv;
    interfaceFormatter.IncIndent();
    rv = interfaceFormatter.WriteLine("switch (ruleIndex)");
    if (!rv) return rv;
    rv = interfaceFormatter.WriteLine("{");
    if (!rv) return rv;
    interfaceFormatter.IncIndent();
    for (const auto& rule : lexer->Rules())
    {
        rv = interfaceFormatter.WriteLine("case " + std::to_string(rule->Index()) + ":");
        if (!rv) return rv;
        soul_expected::ast::common::TokenMap* tokenMap = lexerFile->GetTokenMap();
        if (tokenMap)
        {
            rv = ModifyCode(rule->Code(), *tokenMap, lexerFile, fileMap);
        }
        else
        {
            return std::unexpected<int>(util::AllocateError("token map not set"));
        }
        if (!rv) return rv;
        soul_expected::ast::SourcePos sourcePos;
        rule->Code()->InsertFront(
            new soul_expected::ast::cpp::ExpressionStatementNode(sourcePos,
                new soul_expected::ast::cpp::InvokeNode(sourcePos,
                    new soul_expected::ast::cpp::IdExprNode(sourcePos, "lexer.Retract"))));
        if (rule->Action() != -1)
        {
            soul_expected::ast::slg::Action* action = lexer->GetActions().GetAction(rule->Action());
            if (action != nullptr)
            {
                soul_expected::ast::cpp::CodeEvaluationVisitor visitor;
                action->Code()->Accept(visitor);
                if (!visitor) return std::unexpected<int>(visitor.Error());
                int n = static_cast<int>(action->Code()->Statements().size());
                for (int i = n - 1; i >= 0; --i)
                {
                    soul_expected::ast::cpp::StatementNode* s = action->Code()->Statements()[i].get();
                    rule->Code()->InsertFront(static_cast<soul_expected::ast::cpp::StatementNode*>(s->Clone()));
                }
                if (visitor.HasVars())
                {
                    soul_expected::ast::cpp::DeclarationStatementNode* declarationStmt = new soul_expected::ast::cpp::DeclarationStatementNode(sourcePos,
                        new soul_expected::ast::cpp::InitDeclaratorNode(sourcePos, "auto vars",
                            new soul_expected::ast::cpp::InitializerNode(sourcePos,
                                new soul_expected::ast::cpp::AssignInitNode(sourcePos,
                                    new soul_expected::ast::cpp::IdExprNode(sourcePos, "static_cast<Variables*>(lexer.GetVariables())")))));
                    rule->Code()->InsertFront(declarationStmt);
                }
            }
            else
            {
                return std::unexpected<int>(util::AllocateError("action " + std::to_string(rule->Action()) + " not found"));
            }
        }
        rule->Code()->Add(new soul_expected::ast::cpp::BreakStatementNode(sourcePos));
        rv = rule->Code()->Write(interfaceFormatter);
        if (!rv) return rv;
    }
    interfaceFormatter.DecIndent();
    rv = interfaceFormatter.WriteLine("}");
    if (!rv) return rv;
    rv = interfaceFormatter.WriteLine("return soul_expected::lexer::CONTINUE_TOKEN;");
    if (!rv) return rv;
    interfaceFormatter.DecIndent();
    rv = interfaceFormatter.WriteLine("}");
    if (!rv) return rv;
    interfaceFormatter.DecIndent();
    rv = interfaceFormatter.WriteLine("};");
    if (!rv) return rv;
    interfaceFormatter.WriteLine();
    rv = interfaceFormatter.WriteLine("template<typename CharT>");
    if (!rv) return rv;
    rv = interfaceFormatter.WriteLine("std::expected<soul_expected::lexer::ClassMap<CharT>*, int> GetClassMap()");
    if (!rv) return rv;
    rv = interfaceFormatter.WriteLine("{");
    if (!rv) return rv;
    interfaceFormatter.IncIndent();
    rv = interfaceFormatter.WriteLine("static soul_expected::lexer::ClassMap<CharT>* classmap;");
    if (!rv) return rv;
    rv = interfaceFormatter.WriteLine("if (!classmap)");
    if (!rv) return rv;
    rv = interfaceFormatter.WriteLine("{");
    if (!rv) return rv;
    interfaceFormatter.IncIndent();
    rv = interfaceFormatter.WriteLine("std::expected<soul_expected::lexer::ClassMap<CharT>*, int> rv = soul_expected::lexer::MakeClassMap<CharT>(\"" + moduleName + ".classmap\");");
    if (!rv) return rv;
    rv = interfaceFormatter.WriteLine("if (!rv) return std::unexpected<int>(rv.error());");
    if (!rv) return rv;
    rv = interfaceFormatter.WriteLine("classmap = *rv;");
    if (!rv) return rv;
    interfaceFormatter.DecIndent();
    rv = interfaceFormatter.WriteLine("}");
    if (!rv) return rv;
    rv = interfaceFormatter.WriteLine("return classmap;");
    if (!rv) return rv;
    interfaceFormatter.DecIndent();
    rv = interfaceFormatter.WriteLine("}");
    if (!rv) return rv;
    interfaceFormatter.WriteLine();
    rv = interfaceFormatter.WriteLine("template<typename CharT>");
    if (!rv) return rv;
    rv = interfaceFormatter.WriteLine("std::expected<soul_expected::lexer::ClassMap<CharT>*, int> GetClassMap(const std::string & moduleFileName, util::ResourceFlags resourceFlags)");
    if (!rv) return rv;
    rv = interfaceFormatter.WriteLine("{");
    if (!rv) return rv;
    interfaceFormatter.IncIndent();
    rv = interfaceFormatter.WriteLine("static soul_expected::lexer::ClassMap<CharT>* classmap;");
    if (!rv) return rv;
    rv = interfaceFormatter.WriteLine("if (!classmap)");
    if (!rv) return rv;
    rv = interfaceFormatter.WriteLine("{");
    if (!rv) return rv;
    interfaceFormatter.IncIndent();
    rv = interfaceFormatter.WriteLine("std::expected<soul_expected::lexer::ClassMap<CharT>*, int> rv = soul_expected::lexer::MakeClassMap<CharT>(moduleFileName, \"" +
        moduleName + ".classmap\", resourceFlags);");
    if (!rv) return rv;
    rv = interfaceFormatter.WriteLine("if (!rv) return std::unexpected<int>(rv.error());");
    if (!rv) return rv;
    rv = interfaceFormatter.WriteLine("classmap = *rv;");
    if (!rv) return rv;
    interfaceFormatter.DecIndent();
    rv = interfaceFormatter.WriteLine("}");
    if (!rv) return rv;
    rv = interfaceFormatter.WriteLine("return classmap;");
    if (!rv) return rv;
    interfaceFormatter.DecIndent();
    rv = interfaceFormatter.WriteLine("}");
    if (!rv) return rv;
    interfaceFormatter.WriteLine();
    rv = interfaceFormatter.WriteLine("template<typename CharT>");
    if (!rv) return rv;
    rv = interfaceFormatter.WriteLine("soul_expected::lexer::KeywordMap<CharT>* GetKeywords();");
    if (!rv) return rv;
    interfaceFormatter.WriteLine();
    rv = interfaceFormatter.WriteLine("template<>");
    if (!rv) return rv;
    rv = interfaceFormatter.WriteLine("soul_expected::lexer::KeywordMap<char>* GetKeywords<char>();");
    if (!rv) return rv;
    interfaceFormatter.WriteLine();
    rv = interfaceFormatter.WriteLine("template<>");
    if (!rv) return rv;
    rv = interfaceFormatter.WriteLine("soul_expected::lexer::KeywordMap<char8_t>* GetKeywords<char8_t>();");
    if (!rv) return rv;
    interfaceFormatter.WriteLine();
    rv = interfaceFormatter.WriteLine("template<>");
    if (!rv) return rv;
    rv = interfaceFormatter.WriteLine("soul_expected::lexer::KeywordMap<char16_t>* GetKeywords<char16_t>();");
    if (!rv) return rv;
    interfaceFormatter.WriteLine();
    rv = interfaceFormatter.WriteLine("template<>");
    if (!rv) return rv;
    rv = interfaceFormatter.WriteLine("soul_expected::lexer::KeywordMap<char32_t>* GetKeywords<char32_t>();");
    if (!rv) return rv;
    interfaceFormatter.WriteLine();

    rv = interfaceFormatter.WriteLine("template<typename CharT>");
    if (!rv) return rv;
    rv = interfaceFormatter.WriteLine("std::expected<soul_expected::lexer::Lexer<" + lexer->Name() + "<CharT>, CharT>, int> MakeLexer(const CharT* start, const CharT* end, const std::string& fileName)");
    if (!rv) return rv;
    rv = interfaceFormatter.WriteLine("{");
    if (!rv) return rv;
    interfaceFormatter.IncIndent();
    rv = interfaceFormatter.WriteLine("std::lock_guard<std::mutex> lock(MakeLexerMtx());");
    if (!rv) return rv;
    rv = interfaceFormatter.WriteLine("auto lexer = soul_expected::lexer::Lexer<" + lexer->Name() + "<CharT>, CharT>(start, end, fileName);");
    if (!rv) return rv;
    rv = interfaceFormatter.WriteLine("std::expected<soul_expected::lexer::ClassMap<CharT>*, int> rv = GetClassMap<CharT>();");
    if (!rv) return rv;
    rv = interfaceFormatter.WriteLine("if (!rv) return std::unexpected<int>(rv.error());");
    if (!rv) return rv;
    rv = interfaceFormatter.WriteLine("lexer.SetClassMap(*rv);");
    if (!rv) return rv;
    rv = interfaceFormatter.WriteLine("lexer.SetTokenCollection(GetTokens());");
    if (!rv) return rv;
    rv = interfaceFormatter.WriteLine("lexer.SetKeywordMap(GetKeywords<CharT>());");
    if (!rv) return rv;
    rv = interfaceFormatter.WriteLine("return lexer;");
    if (!rv) return rv;
    interfaceFormatter.DecIndent();
    rv = interfaceFormatter.WriteLine("}");
    if (!rv) return rv;
    interfaceFormatter.WriteLine();

    rv = interfaceFormatter.WriteLine("template<typename CharT>");
    if (!rv) return rv;
    rv = interfaceFormatter.WriteLine("std::expected<soul_expected::lexer::Lexer<" + lexer->Name() +
        "<CharT>, CharT>, int> MakeLexer(const std::string& moduleFileName, util::ResourceFlags resourceFlags, const CharT* start, const CharT* end, const std::string& fileName)");
    if (!rv) return rv;
    rv = interfaceFormatter.WriteLine("{");
    if (!rv) return rv;
    interfaceFormatter.IncIndent();
    rv = interfaceFormatter.WriteLine("std::lock_guard<std::mutex> lock(MakeLexerMtx());");
    if (!rv) return rv;
    rv = interfaceFormatter.WriteLine("auto lexer = soul_expected::lexer::Lexer<" + lexer->Name() + "<CharT>, CharT>(start, end, fileName);");
    if (!rv) return rv;
    rv = interfaceFormatter.WriteLine("std::expected<soul_expected::lexer::ClassMap<CharT>*, int> rv = GetClassMap<CharT>(moduleFileName, resourceFlags);");
    if (!rv) return rv;
    rv = interfaceFormatter.WriteLine("if (!rv) return std::unexpected<int>(rv.error());");
    if (!rv) return rv;
    rv = interfaceFormatter.WriteLine("lexer.SetClassMap(*rv);");
    if (!rv) return rv;
    rv = interfaceFormatter.WriteLine("lexer.SetTokenCollection(GetTokens());");
    if (!rv) return rv;
    rv = interfaceFormatter.WriteLine("lexer.SetKeywordMap(GetKeywords<CharT>());");
    if (!rv) return rv;
    rv = interfaceFormatter.WriteLine("return lexer;");
    if (!rv) return rv;
    interfaceFormatter.DecIndent();
    rv = interfaceFormatter.WriteLine("}");
    if (!rv) return rv;
    interfaceFormatter.WriteLine();

    rv = interfaceFormatter.WriteLine("} // namespace " + soul_expected::ast::common::ToNamespaceName(moduleName));
    if (!rv) return rv;
    if (verbose)
    {
        std::cout << "==> " << interfaceFilePath << std::endl;
    }

    sourceFormatter.WriteLine();
    rv = sourceFormatter.WriteLine("std::mutex mtx;");
    if (!rv) return rv;
    sourceFormatter.WriteLine();
    rv = sourceFormatter.WriteLine("std::mutex& MakeLexerMtx() { return mtx; }");
    if (!rv) return rv;
    sourceFormatter.WriteLine();
    rv = sourceFormatter.WriteLine("template<>");
    if (!rv) return rv;
    rv = sourceFormatter.WriteLine("soul_expected::lexer::KeywordMap<char>* GetKeywords<char>()");
    if (!rv) return rv;
    rv = sourceFormatter.WriteLine("{");
    if (!rv) return rv;
    sourceFormatter.IncIndent();
    rv = sourceFormatter.WriteLine("static const soul_expected::lexer::Keyword<char> keywords[] = {");
    if (!rv) return rv;
    sourceFormatter.IncIndent();
    bool first = true;
    auto keywords = lexerContext.GetKeywords();
    bool hasKw = false;
    for (const auto& keyword : keywords->GetKeywords())
    {
        if (first)
        {
            first = false;
        }
        else
        {
            rv = sourceFormatter.WriteLine(",");
            if (!rv) return rv;
        }
        auto kwrv = GetTokenCppId(lexerFile, fileMap, keyword->GetSourcePos(), keyword->TokenName());
        if (!kwrv) return std::unexpected<int>(kwrv.error());
        rv = sourceFormatter.Write(" { \"" + keyword->Str() + "\", " + *kwrv + " }");
        if (!rv) return rv;
        hasKw = true;
    }
    if (hasKw)
    {
        rv = sourceFormatter.WriteLine(",");
        if (!rv) return rv;
    }
    rv = sourceFormatter.WriteLine(" { nullptr, -1 }");
    if (!rv) return rv;
    sourceFormatter.DecIndent();
    rv = sourceFormatter.WriteLine("};");
    if (!rv) return rv;
    rv = sourceFormatter.WriteLine("static soul_expected::lexer::KeywordMap<char> keywordMap(keywords);");
    if (!rv) return rv;
    rv = sourceFormatter.WriteLine("return &keywordMap;");
    if (!rv) return rv;
    sourceFormatter.DecIndent();
    rv = sourceFormatter.WriteLine("}");
    if (!rv) return rv;

    sourceFormatter.WriteLine();
    rv = sourceFormatter.WriteLine("template<>");
    if (!rv) return rv;
    rv = sourceFormatter.WriteLine("soul_expected::lexer::KeywordMap<char8_t>* GetKeywords<char8_t>()");
    if (!rv) return rv;
    rv = sourceFormatter.WriteLine("{");
    if (!rv) return rv;
    sourceFormatter.IncIndent();
    rv = sourceFormatter.WriteLine("static const soul_expected::lexer::Keyword<char8_t> keywords[] = {");
    if (!rv) return rv;
    sourceFormatter.IncIndent();
    bool first8 = true;
    bool hasKw8 = false;
    auto keywords8 = lexerContext.GetKeywords();
    for (const auto& keyword : keywords8->GetKeywords())
    {
        if (first8)
        {
            first8 = false;
        }
        else
        {
            rv = sourceFormatter.WriteLine(",");
            if (!rv) return rv;
        }
        auto kwrv = GetTokenCppId(lexerFile, fileMap, keyword->GetSourcePos(), keyword->TokenName());
        if (!kwrv) return std::unexpected<int>(kwrv.error());
        rv = sourceFormatter.Write(" { u8\"" + keyword->Str() + "\", " + *kwrv + " }");
        if (!rv) return rv;
        hasKw8 = true;
    }
    if (hasKw8)
    {
        rv = sourceFormatter.WriteLine(",");
        if (!rv) return rv;
    }
    rv = sourceFormatter.WriteLine(" { nullptr, -1 }");
    if (!rv) return rv;
    sourceFormatter.DecIndent();
    rv = sourceFormatter.WriteLine("};");
    if (!rv) return rv;
    rv = sourceFormatter.WriteLine("static soul_expected::lexer::KeywordMap<char8_t> keywordMap(keywords);");
    if (!rv) return rv;
    rv = sourceFormatter.WriteLine("return &keywordMap;");
    if (!rv) return rv;
    sourceFormatter.DecIndent();
    rv = sourceFormatter.WriteLine("}");
    if (!rv) return rv;
    sourceFormatter.WriteLine();
    rv = sourceFormatter.WriteLine("template<>");
    if (!rv) return rv;
    rv = sourceFormatter.WriteLine("soul_expected::lexer::KeywordMap<char16_t>* GetKeywords<char16_t>()");
    if (!rv) return rv;
    rv = sourceFormatter.WriteLine("{");
    if (!rv) return rv;
    sourceFormatter.IncIndent();
    rv = sourceFormatter.WriteLine("static const soul_expected::lexer::Keyword<char16_t> keywords[] = {");
    if (!rv) return rv;
    sourceFormatter.IncIndent();
    bool first16 = true;
    bool hasKw16 = false;
    auto keywords16 = lexerContext.GetKeywords();
    for (const auto& keyword : keywords16->GetKeywords())
    {
        if (first16)
        {
            first16 = false;
        }
        else
        {
            rv = sourceFormatter.WriteLine(",");
            if (!rv) return rv;
        }
        auto kwrv = GetTokenCppId(lexerFile, fileMap, keyword->GetSourcePos(), keyword->TokenName());
        if (!kwrv) return std::unexpected<int>(kwrv.error());
        rv = sourceFormatter.Write(" { u\"" + keyword->Str() + "\", " + *kwrv + " }");
        if (!rv) return rv;
        hasKw16 = true;
    }
    if (hasKw16)
    {
        rv = sourceFormatter.WriteLine(",");
        if (!rv) return rv;
    }
    rv = sourceFormatter.WriteLine(" { nullptr, -1 }");
    if (!rv) return rv;
    sourceFormatter.DecIndent();
    rv = sourceFormatter.WriteLine("};");
    if (!rv) return rv;
    rv = sourceFormatter.WriteLine("static soul_expected::lexer::KeywordMap<char16_t> keywordMap(keywords);");
    if (!rv) return rv;
    rv = sourceFormatter.WriteLine("return &keywordMap;");
    if (!rv) return rv;
    sourceFormatter.DecIndent();
    rv = sourceFormatter.WriteLine("}");
    if (!rv) return rv;

    sourceFormatter.WriteLine();
    rv = sourceFormatter.WriteLine("template<>");
    if (!rv) return rv;
    rv = sourceFormatter.WriteLine("soul_expected::lexer::KeywordMap<char32_t>* GetKeywords<char32_t>()");
    if (!rv) return rv;
    rv = sourceFormatter.WriteLine("{");
    if (!rv) return rv;
    sourceFormatter.IncIndent();
    rv = sourceFormatter.WriteLine("static const soul_expected::lexer::Keyword<char32_t> keywords[] = {");
    if (!rv) return rv;
    sourceFormatter.IncIndent();
    bool first32 = true;
    bool hasKw32 = false;
    auto keywords32 = lexerContext.GetKeywords();
    for (const auto& keyword : keywords32->GetKeywords())
    {
        if (first32)
        {
            first32 = false;
        }
        else
        {
            rv = sourceFormatter.WriteLine(",");
            if (!rv) return rv;
        }
        auto kwrv = GetTokenCppId(lexerFile, fileMap, keyword->GetSourcePos(), keyword->TokenName());
        if (!kwrv) return std::unexpected<int>(kwrv.error());
        rv = sourceFormatter.Write(" { U\"" + keyword->Str() + "\", " + *kwrv + " }");
        if (!rv) return rv;
        hasKw32 = true;
    }
    if (hasKw32)
    {
        rv = sourceFormatter.WriteLine(",");
        if (!rv) return rv;
    }
    rv = sourceFormatter.WriteLine(" { nullptr, -1 }");
    if (!rv) return rv;
    sourceFormatter.DecIndent();
    rv = sourceFormatter.WriteLine("};");
    if (!rv) return rv;
    rv = sourceFormatter.WriteLine("static soul_expected::lexer::KeywordMap<char32_t> keywordMap(keywords);");
    if (!rv) return rv;
    rv = sourceFormatter.WriteLine("return &keywordMap;");
    if (!rv) return rv;
    sourceFormatter.DecIndent();
    rv = sourceFormatter.WriteLine("}");
    if (!rv) return rv;

    sourceFormatter.WriteLine();
    rv = sourceFormatter.WriteLine("} // namespace " + soul_expected::ast::common::ToNamespaceName(moduleName));
    if (!rv) return rv;

    if (verbose)
    {
        std::cout << "==> " << sourceFilePath << std::endl;
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> GenerateLexer(soul_expected::ast::slg::SlgFile* slgFile, soul_expected::ast::slg::LexerFile* lexerFile, soul_expected::lexer::FileMap& fileMap, 
    bool verbose, bool debug)
{
    soul_expected::ast::re::LexerContext lexerContext;
    if (!lexerContext) return std::unexpected<int>(lexerContext.Error());
    if (verbose) lexerContext.SetVerbose();
    if (debug) lexerContext.SetDebug();
    lexerContext.SetFileName(lexerFile->FilePath());
    lexerContext.SetBase(util::Path::GetDirectoryName(lexerFile->FilePath()));
    RegularExpressionParser regularExpressionParser;
    lexerContext.SetExprParser(&regularExpressionParser);
    soul_expected::ast::slg::Tokens tokens;
    soul_expected::ast::slg::Keywords keywords;
    soul_expected::ast::slg::Expressions expressions;
    for (const auto& imprt : lexerFile->Imports())
    {
        std::expected<soul_expected::ast::common::Collection*, int> rv = slgFile->GetCollection(imprt->ModuleName());
        if (!rv) return std::unexpected<int>(rv.error());
        soul_expected::ast::common::Collection* collection = *rv;
        switch (collection->Kind())
        {
            case soul_expected::ast::common::CollectionKind::tokenCollection:
            {
                soul_expected::ast::common::TokenCollection* tokenCollection = static_cast<soul_expected::ast::common::TokenCollection*>(collection);
                for (const auto& token : tokenCollection->Tokens())
                {
                    tokens.AddToken(token.get());
                    lexerFile->GetTokenMap()->AddToken(token.get());
                }
                break;
            }
            case soul_expected::ast::common::CollectionKind::keywordCollection:
            {
                soul_expected::ast::slg::KeywordCollection* keywordCollection = static_cast<soul_expected::ast::slg::KeywordCollection*>(collection);
                for (const auto& keyword : keywordCollection->Keywords())
                {
                    keywords.AddKeyword(keyword.get());
                }
                break;
            }
            case soul_expected::ast::common::CollectionKind::expressionCollection:
            {
                soul_expected::ast::slg::ExpressionCollection* expressionCollection = static_cast<soul_expected::ast::slg::ExpressionCollection*>(collection);
                for (const auto& expression : expressionCollection->Expressions())
                {
                    std::expected<bool, int> rv = expressions.AddExpression(expression.get());
                    if (!rv) return std::unexpected<int>(rv.error());
                }
                break;
            }
        }
    }
    lexerContext.SetTokens(&tokens);
    lexerContext.SetKeywords(&keywords);
    lexerContext.SetExpressions(&expressions);
    lexerContext.SetLexer(lexerFile->GetLexer());
    std::expected<bool, int> rv = MakeNfas(lexerContext);
    if (!rv) return rv;
    rv = MakeCanonicalClasses(lexerContext);
    if (!rv) return rv;
    rv = MakeClassPartition(lexerContext);
    if (!rv) return rv;
    std::string root = util::Path::GetDirectoryName(slgFile->FilePath());
    rv = MakeClassMap(lexerContext, root, verbose);
    if (!rv) return rv;
    rv = CompressClassMap(lexerContext, root, verbose);
    if (!rv) return rv;
    rv = MakeMasterNfa(lexerContext);
    if (!rv) return rv;
    rv = MakeDfa(lexerContext);
    if (!rv) return rv;
    rv = WriteLexer(lexerContext, slgFile, root, fileMap, verbose);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> GenerateLexer(soul_expected::ast::slg::SlgFile* slgFile, soul_expected::lexer::FileMap& fileMap, bool verbose, bool debug)
{
    if (verbose)
    {
        std::cout << "generating lexers for project '" << slgFile->ProjectName() << "'..." << std::endl;
    }
    auto u = util::GetFullPath(slgFile->FilePath());
    if (!u) return std::unexpected<int>(u.error());
    std::string filePath = *u;
    std::string dir = util::Path::GetDirectoryName(filePath);
    for (const auto& declaration : slgFile->Declarations())
    {
        switch (declaration->Kind())
        {
            case soul_expected::ast::slg::SlgFileDeclarationKind::tokenFileDeclaration:
            {
                soul_expected::ast::slg::TokenFileDeclaration* tokenFileDeclaration = static_cast<soul_expected::ast::slg::TokenFileDeclaration*>(declaration.get());
                auto u = util::GetFullPath(util::Path::Combine(dir, tokenFileDeclaration->FilePath()));
                if (!u) return std::unexpected<int>(u.error());
                std::string tokenFilePath = *u;
                if (verbose)
                {
                    std::cout << "> " << tokenFilePath << std::endl;
                }
                std::expected<std::unique_ptr<soul_expected::ast::common::TokenFile>, int> rv = ParseTokenFile(tokenFilePath, tokenFileDeclaration->External(), fileMap);
                if (!rv) return std::unexpected<int>(rv.error());
                std::unique_ptr<soul_expected::ast::common::TokenFile> tokenFile = std::move(*rv);
                std::expected<bool, int> mrv = GenerateTokenModule(tokenFile.get(), verbose);
                if (!mrv) return std::unexpected<int>(mrv.error());
                std::expected<bool, int> trv = slgFile->AddTokenFile(tokenFile.release());
                if (!trv) return std::unexpected<int>(trv.error());
                break;
            }
            case soul_expected::ast::slg::SlgFileDeclarationKind::keywordFileDeclaration:
            {
                auto u = util::GetFullPath(util::Path::Combine(dir, declaration->FilePath()));
                if (!u) return std::unexpected<int>(u.error());
                std::string keywordFilePath = *u;
                if (verbose)
                {
                    std::cout << "> " << keywordFilePath << std::endl;
                }
                std::expected<std::unique_ptr<soul_expected::ast::slg::KeywordFile>, int> rv = ParseKeywordFile(keywordFilePath, fileMap);
                if (!rv) return std::unexpected<int>(rv.error());
                std::unique_ptr<soul_expected::ast::slg::KeywordFile> keywordFile = std::move(*rv);
                std::expected<bool, int> krv = slgFile->AddKeywordFile(keywordFile.release());
                if (!krv) return std::unexpected<int>(krv.error());
                break;
            }
            case soul_expected::ast::slg::SlgFileDeclarationKind::expressionFileDeclaration:
            {
                auto u = util::GetFullPath(util::Path::Combine(dir, declaration->FilePath()));
                if (!u) return std::unexpected<int>(u.error());
                std::string expressionFilePath = *u;
                if (verbose)
                {
                    std::cout << "> " << expressionFilePath << std::endl;
                }
                std::expected<std::unique_ptr<soul_expected::ast::slg::ExpressionFile>, int> rv = ParseExpressionFile(expressionFilePath, fileMap);
                if (!rv) return std::unexpected<int>(rv.error());
                std::unique_ptr<soul_expected::ast::slg::ExpressionFile> expressionFile = std::move(*rv);
                std::expected<bool, int> erv = slgFile->AddExpressionFile(expressionFile.release());
                if (!erv) return std::unexpected<int>(erv.error());
                break;
            }
            case soul_expected::ast::slg::SlgFileDeclarationKind::lexerFileDeclararation:
            {
                auto u = util::GetFullPath(util::Path::Combine(dir, declaration->FilePath()));
                if (!u) return std::unexpected<int>(u.error());
                std::string lexerFilePath = *u;
                if (verbose)
                {
                    std::cout << "> " << lexerFilePath << std::endl;
                }
                std::expected<std::unique_ptr<soul_expected::ast::slg::LexerFile>, int> rv = ParseLexerFile(lexerFilePath, fileMap);
                if (!rv) return std::unexpected<int>(rv.error());
                std::unique_ptr<soul_expected::ast::slg::LexerFile> lexerFile = std::move(*rv);
                std::expected<bool, int> lrv = slgFile->AddLexerFile(lexerFile.release());
                if (!lrv) return std::unexpected<int>(lrv.error());
                break;
            }
        }
    }
    for (const auto& lexerFile : slgFile->LexerFiles())
    {
        std::expected<bool, int> rv = GenerateLexer(slgFile, lexerFile.get(), fileMap, verbose, debug);
        if (!rv) return rv;
    }
    if (verbose)
    {
        std::cout << "lexers for project '" << slgFile->ProjectName() << "' generated successfully." << std::endl;
    }
    return std::expected<bool, int>(true);
}

} // namespace soul_expected::slg
