// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.slg.lexer.generator;

import util;
import soul.slg.classmap;
import soul.slg.file.parsers;
import soul.slg.token.generator;
import soul.slg.regular.expression.parser;
import soul.slg.code.modifier;
import soul.ast.re;
import soul.ast.cpp;
import soul.ast.common;
import soul.ast.source.pos;
import soul.lex;

namespace soul::slg {

std::expected<bool, int> MakeNfas(soul::ast::re::LexerContext& lexerContext)
{
    for (auto& rule : lexerContext.GetLexer()->Rules())
    {
        std::expected<soul::ast::re::Nfa, int> rv = lexerContext.GetExprParser()->Parse(rule->Expr(), &lexerContext, lexerContext.FileName(), rule->Line());
        if (!rv) return std::unexpected<int>(rv.error());
        soul::ast::re::Nfa* nfa = new soul::ast::re::Nfa(std::move(*rv));
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
        for (soul::ast::re::NfaState* state : lexerContext.NfaStates())
        {
            auto rv = state->Print(formatter);
            if (!rv) return rv;
        }
        if (lexerContext.Verbose())
        {
            std::cout << "==> " << nfaFilePath << "\n";
        }
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> MakeCanonicalClasses(soul::ast::re::LexerContext& lexerContext)
{
    std::vector<soul::ast::re::Symbol*> s = lexerContext.Symbols();
    for (soul::ast::re::Symbol* symbol : s)
    {
        if (symbol->Contained()) continue;
        if (symbol->Kind() == soul::ast::re::SymbolKind::classSymbol)
        {
            soul::ast::re::Class* cls = static_cast<soul::ast::re::Class*>(symbol);
            std::expected<soul::ast::re::Class*, int> rv = cls->MakeCanonical(lexerContext);
            if (!rv) return std::unexpected<int>(rv.error());
            soul::ast::re::Class* canonicalClass = *rv;
            lexerContext.AddCanonicalClass(canonicalClass);
        }
        else if (symbol->Kind() == soul::ast::re::SymbolKind::charSymbol)
        {
            soul::ast::re::CharSymbol* chr = static_cast<soul::ast::re::CharSymbol*>(symbol);
            soul::ast::re::Class* canonicalClass = new soul::ast::re::Class(-1);
            canonicalClass->Ranges().push_back(soul::ast::re::Range(chr->Chr(), chr->Chr()));
            lexerContext.AddCanonicalClass(canonicalClass);
        }
        else if (symbol->Kind() == soul::ast::re::SymbolKind::anySymbol)
        {
            std::expected<soul::ast::re::Symbol*, int> rv = lexerContext.MakeRange(static_cast<char32_t>(1), static_cast<char32_t>(0x10FFFF));
            if (!rv) return std::unexpected<int>(rv.error());
            soul::ast::re::Symbol* range = *rv;
            soul::ast::re::Class* canonicalClass = new soul::ast::re::Class(-1);
            canonicalClass->Ranges().push_back(soul::ast::re::Range(static_cast<char32_t>(1), static_cast<char32_t>(0x10FFFF)));
            lexerContext.AddCanonicalClass(canonicalClass);
        }
        else if (symbol->Kind() == soul::ast::re::SymbolKind::rangeSymbol)
        {
            soul::ast::re::Range* range = static_cast<soul::ast::re::Range*>(symbol);
            soul::ast::re::Class* canonicalClass = new soul::ast::re::Class(-1);
            canonicalClass->Ranges().push_back(*range);
            lexerContext.AddCanonicalClass(canonicalClass);
        }
    }
    int index = 0;
    for (soul::ast::re::Class* canonicalClass : lexerContext.CanonicalClasses())
    {
        canonicalClass->SetIndex(index++);
        for (const soul::ast::re::Range& range : canonicalClass->Ranges())
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
        for (soul::ast::re::Class* canonicalClass : lexerContext.CanonicalClasses())
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

std::expected<bool, int> MakeClassPartition(soul::ast::re::LexerContext& lexerContext)
{
    std::list<soul::ast::re::Class*> classes;
    for (soul::ast::re::Class* cls : lexerContext.CanonicalClasses())
    {
        classes.push_back(cls);
    }
    auto classIt = classes.begin();
    while (classIt != classes.end())
    {
        bool classChanged = false;
        soul::ast::re::Class* cls = *classIt;
        auto sourceIt = classes.begin();
        while (!cls->Ranges().empty() && sourceIt != classes.end())
        {
            if (sourceIt == classIt)
            {
                ++sourceIt;
                continue;
            }
            bool sourceChanged = false;
            soul::ast::re::Class* source = *sourceIt;
            std::unique_ptr<soul::ast::re::Class> splitClass(new soul::ast::re::Class(-1));
            auto leftIt = cls->Ranges().begin();
            while (leftIt != cls->Ranges().end())
            {
                bool leftChanged = false;
                auto rightIt = source->Ranges().begin();
                while (leftIt != cls->Ranges().end() && rightIt != source->Ranges().end())
                {
                    bool rightChanged = false;
                    if (soul::ast::re::Intersect(*leftIt, *rightIt))
                    {
                        std::vector<soul::ast::re::Range> leftRanges = *leftIt - *rightIt;
                        std::vector<soul::ast::re::Range> rightRanges = *rightIt - *leftIt;
                        soul::ast::re::Range intersection = *leftIt & *rightIt;
                        for (const soul::ast::re::Range& leftRange : leftRanges)
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
                        for (const soul::ast::re::Range& rightRange : rightRanges)
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
    for (soul::ast::re::Class* cls : classes)
    {
        cls->MakeMinimal(lexerContext);
        lexerContext.AddToPartition(cls);
    }
    for (int i = 0; i < lexerContext.Partition().size(); ++i)
    {
        soul::ast::re::Class* cls = lexerContext.Partition()[i];
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
            soul::ast::re::Class* cls = lexerContext.Partition()[i];
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

std::expected<bool, int> MakeClassMap(soul::ast::re::LexerContext& lexerContext, const std::string& root, bool verbose)
{
    std::vector<std::int32_t> classMapVec(0x110000, -1);
    for (soul::ast::re::Class* cls : lexerContext.Partition())
    {
        for (const soul::ast::re::Range& range : cls->Ranges())
        {
            for (char32_t i = range.Start(); i <= range.End(); i = static_cast<char32_t>(static_cast<int>(i) + 1))
            {
                if (classMapVec[i] == -1)
                {
                    classMapVec[static_cast<std::int32_t>(i)] = cls->Index();
                }
            }
        }
    }
    std::string moduleName;
    soul::ast::slg::Lexer* lexer = lexerContext.GetLexer();
    soul::ast::common::File* file = lexer->GetFile();
    if (file->Kind() == soul::ast::common::FileKind::lexerFile)
    {
        soul::ast::slg::LexerFile* lexerFile = static_cast<soul::ast::slg::LexerFile*>(file);
        soul::ast::common::ExportModule* mod = lexerFile->GetExportModule();
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
        formatter.WriteLine("CLASSMAP:");
        int32_t i = 0;
        for (std::int32_t x : classMapVec)
        {
            formatter.WriteLine(std::to_string(i) + " : " + std::to_string(x));
            ++i;
        }
        if (lexerContext.Verbose())
        {
            std::cout << "==> " << classMapFilePath << "\n";
        }
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> CompressClassMap(soul::ast::re::LexerContext& lexerContext, const std::string& root, bool verbose)
{
    std::string moduleName;
    soul::ast::slg::Lexer* lexer = lexerContext.GetLexer();
    soul::ast::common::File* file = lexer->GetFile();
    if (file->Kind() == soul::ast::common::FileKind::lexerFile)
    {
        soul::ast::slg::LexerFile* lexerFile = static_cast<soul::ast::slg::LexerFile*>(file);
        soul::ast::common::ExportModule* mod = lexerFile->GetExportModule();
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

std::expected<bool, int> MakeMasterNfa(soul::ast::re::LexerContext& lexerContext)
{
    soul::ast::re::Nfa* masterNfa = new soul::ast::re::Nfa();
    int masterNfaIndex = lexerContext.AddNfa(masterNfa);
    lexerContext.SetMasterNfaIndex(masterNfaIndex);
    soul::ast::re::NfaState* start = lexerContext.MakeNfaState();
    masterNfa->SetStart(start);
    soul::ast::slg::Lexer* lexer = lexerContext.GetLexer();
    for (const auto& rule : lexer->Rules())
    {
        std::expected< soul::ast::re::Nfa*, int> rv = lexerContext.GetNfa(rule->NfaIndex());
        if (!rv) return std::unexpected<int>(rv.error());
        soul::ast::re::Nfa* ruleNfa = *rv;
        start->AddEdge(soul::ast::re::NfaEdge(lexerContext.MakeEpsilon(), ruleNfa->Start()));
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> MakeDfa(soul::ast::re::LexerContext& lexerContext)
{
    std::expected< soul::ast::re::Nfa*, int> rv = lexerContext.GetNfa(lexerContext.MasterNfaIndex());
    if (!rv) return std::unexpected<int>(rv.error());
    soul::ast::re::Nfa* masterNfa = *rv;
    std::expected<soul::ast::re::Dfa, int> drv = soul::ast::re::Compile(lexerContext, *masterNfa);
    if (!drv) return std::unexpected<int>(drv.error());
    soul::ast::re::Dfa dfa = std::move(*drv);
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
        auto rv = lexerContext.GetDfa().Print(lexerContext, formatter);
        if (!rv) return rv;
        if (lexerContext.Verbose())
        {
            std::cout << "==> " << dfaFilePath << "\n";
        }
    }
    return std::expected<bool, int>(true);
}

std::expected<std::string, int> GetTokenCppId(soul::ast::slg::LexerFile* lexerFile, soul::lexer::FileMap& fileMap,
    const soul::ast::SourcePos& sourcePos, const std::string& tokenName)
{
    soul::ast::common::TokenMap* tokenMap = lexerFile->GetTokenMap();
    if (tokenMap)
    {
        std::vector<soul::ast::common::Token*> tokens = tokenMap->GetTokens(tokenName);
        int n = static_cast<int>(tokens.size());
        if (n == 1)
        {
            soul::ast::common::Token* token = tokens.front();
            return token->FullCppId();
        }
        else if (n > 1)
        {
            std::string tokenString;
            for (int i = 0; i < n; ++i)
            {
                soul::ast::common::Token* token = tokens[i];
                if (i > 0)
                {
                    tokenString.append(" or\n");
                }
                tokenString.append(token->FullName());
            }
            std::expected<std::string, int> rv = soul::lexer::MakeMessage("error", "ambiguous reference to token '" + tokenName + "' in lexer file '" +
                lexerFile->FilePath() + "':\n" + tokenString, sourcePos, fileMap);
            if (!rv) return rv;
            std::string errorMessage = *rv;
            return std::unexpected<int>(util::AllocateError(errorMessage));
        }
        else
        {
            std::expected<std::string, int> rv = soul::lexer::MakeMessage("error", "token '" + tokenName + "' not found in lexer file '" +
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

std::expected<bool, int> WriteVariables(soul::ast::re::LexerContext& lexerContext, util::CodeFormatter& interfaceFormatter, util::CodeFormatter sourceFormatter)
{
    soul::ast::slg::Lexer* lexer = lexerContext.GetLexer();
    std::string variableClassName = lexer->Name() + "_Variables";
    lexer->SetVariableClassName(variableClassName);
    interfaceFormatter.WriteLine("struct " + variableClassName + " : public soul::lexer::Variables");
    interfaceFormatter.WriteLine("{");
    interfaceFormatter.IncIndent();
    interfaceFormatter.WriteLine(variableClassName + "();");
    bool hasVariables = false;
    for (const auto& var : lexer->Variables())
    {
        var->Type()->Write(interfaceFormatter);
        interfaceFormatter.Write(" ");
        interfaceFormatter.WriteLine(var->Name() + ";");
        hasVariables = true;
    }
    interfaceFormatter.DecIndent();
    interfaceFormatter.WriteLine("};");
    sourceFormatter.WriteLine();
    sourceFormatter.Write(variableClassName + "::" + variableClassName + "()");
    if (hasVariables)
    {
        sourceFormatter.Write(" :");
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
            sourceFormatter.Write(", ");
        }
        sourceFormatter.Write(var->Name() + "()");
    }
    if (hasVariables)
    {
        sourceFormatter.WriteLine();
    }
    sourceFormatter.DecIndent();
    sourceFormatter.WriteLine("{");
    sourceFormatter.WriteLine("}");
    return std::expected<bool, int>(true);
}

std::expected<bool, int> WriteLexer(soul::ast::re::LexerContext& lexerContext, soul::ast::slg::SlgFile* slgFile, const std::string& root,
    soul::lexer::FileMap& fileMap, bool verbose)
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
    interfaceFormatter.WriteLine("// this file has been automatically generated from '" +
        lexerContext.FileName() + "' using soul lexer generator oslg version " + util::SoulVersionStr());
    interfaceFormatter.WriteLine();
    std::ofstream sourceStream(sourceFilePath);
    if (!sourceStream) return std::unexpected<int>(util::AllocateError("could not create file '" + sourceFilePath + "'"));
    util::CodeFormatter sourceFormatter(sourceStream);
    sourceFormatter.WriteLine("// this file has been automatically generated from '" + lexerContext.FileName() + "' using soul lexer generator oslg version " +
        util::SoulVersionStr());
    sourceFormatter.WriteLine();
    soul::ast::slg::Lexer* lexer = lexerContext.GetLexer();
    soul::ast::common::File* file = lexer->GetFile();
    soul::ast::slg::LexerFile* lexerFile = nullptr;
    std::string moduleName;
    if (file->Kind() == soul::ast::common::FileKind::lexerFile)
    {
        lexerFile = static_cast<soul::ast::slg::LexerFile*>(file);
        soul::ast::common::ExportModule* mod = lexerFile->GetExportModule();
        moduleName = mod->ModuleName();
    }
    else
    {
        return std::unexpected<int>(util::AllocateError("lexer file expected"));
    }
    sourceFormatter.WriteLine("module " + moduleName + ";");
    sourceFormatter.WriteLine();
    interfaceFormatter.WriteLine("export module " + moduleName + ";");
    interfaceFormatter.WriteLine();
    interfaceFormatter.WriteLine("import std;");
    interfaceFormatter.WriteLine("import soul.lexer;");
    interfaceFormatter.WriteLine("import soul.ast.slg;");
    interfaceFormatter.WriteLine("import soul.ast.common;");
    interfaceFormatter.WriteLine("import util;");
    for (const auto& imprt : lexerFile->Imports())
    {
        soul::ast::common::Collection* collection = slgFile->GetCollection(imprt->ModuleName());
        if (!collection)
        {
            interfaceFormatter.WriteLine("import " + imprt->ModuleName() + ";");
        }
        else if (collection->Kind() == soul::ast::common::CollectionKind::tokenCollection)
        {
            interfaceFormatter.WriteLine("import " + collection->Name() + ";");
        }
    }
    interfaceFormatter.WriteLine();
    sourceFormatter.WriteLine();
    interfaceFormatter.WriteLine("export namespace " + soul::ast::common::ToNamespaceName(moduleName) + " {");
    interfaceFormatter.WriteLine();
    interfaceFormatter.WriteLine("std::mutex& MakeLexerMtx();");
    interfaceFormatter.WriteLine();
    interfaceFormatter.WriteLine("template<typename CharT>");
    interfaceFormatter.WriteLine("struct " + lexer->Name() + ";");
    interfaceFormatter.WriteLine();
    interfaceFormatter.WriteLine("template<typename CharT>");
    interfaceFormatter.WriteLine("std::expected<soul::lexer::Lexer<" + lexer->Name() + "<CharT>, CharT>, int> MakeLexer(" +
        "const CharT* start, const CharT* end, const std::string& fileName);");
    interfaceFormatter.WriteLine();
    interfaceFormatter.WriteLine("template<typename CharT>");
    interfaceFormatter.WriteLine("std::expected<soul::lexer::Lexer<" + lexer->Name() + "<CharT>, CharT>, int> MakeLexer(" +
        "const std::string& moduleFileName, util::ResourceFlags resourceFlags, const CharT* start, const CharT* end, const std::string& fileName);");
    interfaceFormatter.WriteLine();
    interfaceFormatter.WriteLine("soul::ast::common::TokenCollection* GetTokens();");
    interfaceFormatter.WriteLine();
    sourceFormatter.WriteLine("namespace " + soul::ast::common::ToNamespaceName(moduleName) + " {");
    sourceFormatter.WriteLine();
    sourceFormatter.WriteLine("soul::ast::common::TokenCollection* GetTokens()");
    sourceFormatter.WriteLine("{");
    sourceFormatter.IncIndent();
    sourceFormatter.WriteLine("static soul::ast::common::TokenCollection tokens(\"" + moduleName + ".tokens\");");
    sourceFormatter.WriteLine("if (!tokens.Initialized())");
    sourceFormatter.WriteLine("{");
    sourceFormatter.IncIndent();
    sourceFormatter.WriteLine("tokens.SetInitialized();");
    soul::ast::slg::Tokens* tokens = lexerContext.GetTokens();
    for (const auto* token : tokens->GetTokens())
    {
        sourceFormatter.WriteLine("tokens.AddToken(new soul::ast::common::Token(" + token->FullCppId() + ", \"" + token->Name() + "\", \"" + token->Info() + "\"));");
    }
    sourceFormatter.DecIndent();
    sourceFormatter.WriteLine("}");
    sourceFormatter.WriteLine("return &tokens;");
    sourceFormatter.DecIndent();
    sourceFormatter.WriteLine("}");
    auto rv = WriteVariables(lexerContext, interfaceFormatter, sourceFormatter);
    if (!rv) return rv;
    interfaceFormatter.WriteLine();
    interfaceFormatter.WriteLine("template<typename CharT>");
    interfaceFormatter.WriteLine("struct " + lexer->Name());
    interfaceFormatter.WriteLine("{");
    interfaceFormatter.IncIndent();
    interfaceFormatter.WriteLine("using Variables = " + lexer->VariableClassName() + ";");
    interfaceFormatter.WriteLine();
    interfaceFormatter.WriteLine("static std::int32_t NextState(std::int32_t state, CharT chr, soul::lexer::LexerBase<CharT>& lexer)");
    interfaceFormatter.WriteLine("{");
    interfaceFormatter.IncIndent();
    interfaceFormatter.WriteLine("soul::lexer::ClassMap<CharT>* classmap = lexer.GetClassMap();");
    interfaceFormatter.WriteLine("std::int32_t cls = classmap->GetClass(chr);");
    interfaceFormatter.WriteLine("switch (state)");
    interfaceFormatter.WriteLine("{");
    interfaceFormatter.IncIndent();
    for (const auto* state : lexerContext.GetDfa().States())
    {
        interfaceFormatter.WriteLine("case " + std::to_string(state->Id()) + ":");
        interfaceFormatter.WriteLine("{");
        interfaceFormatter.IncIndent();
        if (state->Accept())
        {
            interfaceFormatter.WriteLine("auto& token = lexer.CurrentToken();");
            interfaceFormatter.WriteLine("auto prevMatch = token.match;");
            interfaceFormatter.WriteLine("token.match = lexer.CurrentLexeme();");
            interfaceFormatter.WriteLine("std::int64_t tokenId = GetTokenId(" + std::to_string(state->RuleIndex()) + ", lexer);");
            interfaceFormatter.WriteLine("if (tokenId == soul::lexer::CONTINUE_TOKEN)");
            interfaceFormatter.WriteLine("{");
            interfaceFormatter.IncIndent();
            interfaceFormatter.WriteLine("token.id = soul::lexer::CONTINUE_TOKEN;");
            interfaceFormatter.WriteLine("return -1;");
            interfaceFormatter.DecIndent();
            interfaceFormatter.WriteLine("}");
            interfaceFormatter.WriteLine("else if (tokenId != soul::lexer::INVALID_TOKEN)");
            interfaceFormatter.WriteLine("{");
            interfaceFormatter.IncIndent();
            interfaceFormatter.WriteLine("token.id = tokenId;");
            interfaceFormatter.DecIndent();
            interfaceFormatter.WriteLine("}");
            interfaceFormatter.WriteLine("else");
            interfaceFormatter.WriteLine("{");
            interfaceFormatter.IncIndent();
            interfaceFormatter.WriteLine("token.match = prevMatch;");
            interfaceFormatter.DecIndent();
            interfaceFormatter.WriteLine("}");
        }
        std::map<std::int32_t, std::set<std::int32_t>> m;
        for (soul::ast::re::Class* cls : lexerContext.Partition())
        {
            soul::ast::re::DfaState* nxt = state->Next(cls->Index());
            if (nxt != nullptr)
            {
                m[nxt->Id()].insert(cls->Index());
            }
        }
        if (m.empty())
        {
            interfaceFormatter.WriteLine("return -1;");
        }
        else
        {
            interfaceFormatter.WriteLine("switch (cls)");
            interfaceFormatter.WriteLine("{");
            interfaceFormatter.IncIndent();
            for (const auto& p : m)
            {
                std::int32_t n = p.first;
                std::set<std::int32_t>* s = &p.second;
                for (std::int32_t k : *s)
                {
                    interfaceFormatter.WriteLine("case " + std::to_string(k) + ":");
                }
                interfaceFormatter.WriteLine("{");
                interfaceFormatter.IncIndent();
                interfaceFormatter.WriteLine("return " + std::to_string(n) + ";");
                interfaceFormatter.DecIndent();
                interfaceFormatter.WriteLine("}");
            }
            interfaceFormatter.WriteLine("default:");
            interfaceFormatter.WriteLine("{");
            interfaceFormatter.IncIndent();
            interfaceFormatter.WriteLine("return -1;");
            interfaceFormatter.DecIndent();
            interfaceFormatter.WriteLine("}");
            interfaceFormatter.DecIndent();
            interfaceFormatter.WriteLine("}");
        }
        interfaceFormatter.DecIndent();
        interfaceFormatter.WriteLine("}");
    }
    interfaceFormatter.DecIndent();
    interfaceFormatter.WriteLine("}");
    interfaceFormatter.WriteLine("return -1;");
    interfaceFormatter.DecIndent();
    interfaceFormatter.WriteLine("}");
    interfaceFormatter.WriteLine();
    interfaceFormatter.WriteLine("static std::int64_t GetTokenId(std::int32_t ruleIndex, soul::lexer::LexerBase<CharT>& lexer)");
    interfaceFormatter.WriteLine("{");
    interfaceFormatter.IncIndent();
    interfaceFormatter.WriteLine("switch (ruleIndex)");
    interfaceFormatter.WriteLine("{");
    interfaceFormatter.IncIndent();
    for (const auto& rule : lexer->Rules())
    {
        interfaceFormatter.WriteLine("case " + std::to_string(rule->Index()) + ":");
        soul::ast::common::TokenMap* tokenMap = lexerFile->GetTokenMap();
        if (tokenMap)
        {
            std::expected<bool, int> rv = ModifyCode(rule->Code(), *tokenMap, lexerFile, fileMap);
            if (!rv) return rv;
        }
        else
        {
            return std::unexpected<int>(util::AllocateError("token map not set"));
        }
        soul::ast::SourcePos sourcePos;
        rule->Code()->InsertFront(
            new soul::ast::cpp::ExpressionStatementNode(sourcePos,
                new soul::ast::cpp::InvokeNode(sourcePos,
                    new soul::ast::cpp::IdExprNode(sourcePos, "lexer.Retract"))));
        if (rule->GetAction() != -1)
        {
            soul::ast::slg::Action* action = lexer->GetActions().GetAction(rule->GetAction());
            if (action != nullptr)
            {
                soul::ast::cpp::CodeEvaluationVisitor visitor;
                action->Code()->Accept(visitor);
                if (!visitor) return std::unexpected<int>(visitor.Error());
                int n = static_cast<int>(action->Code()->Statements().size());
                for (int i = n - 1; i >= 0; --i)
                {
                    soul::ast::cpp::StatementNode* s = action->Code()->Statements()[i].get();
                    rule->Code()->InsertFront(static_cast<soul::ast::cpp::StatementNode*>(s->Clone()));
                }
                if (visitor.HasVars())
                {
                    soul::ast::cpp::DeclarationStatementNode* declarationStmt = new soul::ast::cpp::DeclarationStatementNode(sourcePos,
                        new soul::ast::cpp::InitDeclaratorNode(sourcePos, "auto vars",
                            new soul::ast::cpp::InitializerNode(sourcePos,
                                new soul::ast::cpp::AssignInitNode(sourcePos,
                                    new soul::ast::cpp::IdExprNode(sourcePos, "static_cast<Variables*>(lexer.GetVariables())")))));
                    rule->Code()->InsertFront(declarationStmt);
                }
            }
            else
            {
                return std::unexpected<int>(util::AllocateError("action " + std::to_string(rule->GetAction()) + " not found"));
            }
        }
        rule->Code()->Add(new soul::ast::cpp::BreakStatementNode(sourcePos));
        rule->Code()->Write(interfaceFormatter);
    }
    interfaceFormatter.DecIndent();
    interfaceFormatter.WriteLine("}");
    interfaceFormatter.WriteLine("return soul::lexer::CONTINUE_TOKEN;");
    interfaceFormatter.DecIndent();
    interfaceFormatter.WriteLine("}");
    interfaceFormatter.DecIndent();
    interfaceFormatter.WriteLine("};");
    interfaceFormatter.WriteLine();
    interfaceFormatter.WriteLine("template<typename CharT>");
    interfaceFormatter.WriteLine("std::expected<soul::lexer::ClassMap<CharT>*, int> GetClassMap()");
    interfaceFormatter.WriteLine("{");
    interfaceFormatter.IncIndent();
    interfaceFormatter.WriteLine("static soul::lexer::ClassMap<CharT>* classmap;");
    interfaceFormatter.WriteLine("if (!classmap)");
    interfaceFormatter.WriteLine("{");
    interfaceFormatter.IncIndent();
    interfaceFormatter.WriteLine("std::expected<soul::lexer::ClassMap<CharT>*, int> rv = soul::lexer::MakeClassMap<CharT>(\"" + moduleName + ".classmap\");");
    interfaceFormatter.WriteLine("if (!rv) return std::unexpected<int>(rv.error());");
    interfaceFormatter.WriteLine("classmap = *rv;");
    interfaceFormatter.DecIndent();
    interfaceFormatter.WriteLine("}");
    interfaceFormatter.WriteLine("return classmap;");
    interfaceFormatter.DecIndent();
    interfaceFormatter.WriteLine("}");
    interfaceFormatter.WriteLine();
    interfaceFormatter.WriteLine("template<typename CharT>");
    interfaceFormatter.WriteLine("std::expected<soul::lexer::ClassMap<CharT>*, int> GetClassMap(const std::string & moduleFileName, util::ResourceFlags resourceFlags)");
    interfaceFormatter.WriteLine("{");
    interfaceFormatter.IncIndent();
    interfaceFormatter.WriteLine("static soul::lexer::ClassMap<CharT>* classmap;");
    interfaceFormatter.WriteLine("if (!classmap)");
    interfaceFormatter.WriteLine("{");
    interfaceFormatter.IncIndent();
    interfaceFormatter.WriteLine("std::expected<soul::lexer::ClassMap<CharT>*, int> rv = soul::lexer::MakeClassMap<CharT>(moduleFileName, \"" +
        moduleName + ".classmap\", resourceFlags);");
    interfaceFormatter.WriteLine("if (!rv) return std::unexpected<int>(rv.error());");
    interfaceFormatter.WriteLine("classmap = *rv;");
    interfaceFormatter.DecIndent();
    interfaceFormatter.WriteLine("}");
    interfaceFormatter.WriteLine("return classmap;");
    interfaceFormatter.DecIndent();
    interfaceFormatter.WriteLine("}");
    interfaceFormatter.WriteLine();
    interfaceFormatter.WriteLine("template<typename CharT>");
    interfaceFormatter.WriteLine("soul::lexer::KeywordMap<CharT>* GetKeywords();");
    interfaceFormatter.WriteLine();
    interfaceFormatter.WriteLine("template<>");
    interfaceFormatter.WriteLine("soul::lexer::KeywordMap<char>* GetKeywords<char>();");
    interfaceFormatter.WriteLine();
    interfaceFormatter.WriteLine("template<>");
    interfaceFormatter.WriteLine("soul::lexer::KeywordMap<char8_t>* GetKeywords<char8_t>();");
    interfaceFormatter.WriteLine();
    interfaceFormatter.WriteLine("template<>");
    interfaceFormatter.WriteLine("soul::lexer::KeywordMap<char16_t>* GetKeywords<char16_t>();");
    interfaceFormatter.WriteLine();
    interfaceFormatter.WriteLine("template<>");
    interfaceFormatter.WriteLine("soul::lexer::KeywordMap<char32_t>* GetKeywords<char32_t>();");
    interfaceFormatter.WriteLine();

    interfaceFormatter.WriteLine("template<typename CharT>");
    interfaceFormatter.WriteLine("std::expected<soul::lexer::Lexer<" + lexer->Name() + "<CharT>, CharT>, int> MakeLexer(const CharT* start, const CharT* end, const std::string& fileName)");
    interfaceFormatter.WriteLine("{");
    interfaceFormatter.IncIndent();
    interfaceFormatter.WriteLine("std::lock_guard<std::mutex> lock(MakeLexerMtx());");
    interfaceFormatter.WriteLine("auto lexer = soul::lexer::Lexer<" + lexer->Name() + "<CharT>, CharT>(start, end, fileName);");
    interfaceFormatter.WriteLine("std::expected<soul::lexer::ClassMap<CharT>*, int> rv = GetClassMap<CharT>();");
    interfaceFormatter.WriteLine("if (!rv) return std::unexpected<int>(rv.error());");
    interfaceFormatter.WriteLine("lexer.SetClassMap(*rv);");
    interfaceFormatter.WriteLine("lexer.SetTokenCollection(GetTokens());");
    interfaceFormatter.WriteLine("lexer.SetKeywordMap(GetKeywords<CharT>());");
    interfaceFormatter.WriteLine("return lexer;");
    interfaceFormatter.DecIndent();
    interfaceFormatter.WriteLine("}");
    interfaceFormatter.WriteLine();

    interfaceFormatter.WriteLine("template<typename CharT>");
    interfaceFormatter.WriteLine("std::expected<soul::lexer::Lexer<" + lexer->Name() +
        "<CharT>, CharT>, int> MakeLexer(const std::string& moduleFileName, util::ResourceFlags resourceFlags, const CharT* start, const CharT* end, const std::string& fileName)");
    interfaceFormatter.WriteLine("{");
    interfaceFormatter.IncIndent();
    interfaceFormatter.WriteLine("std::lock_guard<std::mutex> lock(MakeLexerMtx());");
    interfaceFormatter.WriteLine("auto lexer = soul::lexer::Lexer<" + lexer->Name() + "<CharT>, CharT>(start, end, fileName);");
    interfaceFormatter.WriteLine("std::expected<soul::lexer::ClassMap<CharT>*, int> rv = GetClassMap<CharT>(moduleFileName, resourceFlags);");
    interfaceFormatter.WriteLine("if (!rv) return std::unexpected<int>(rv.error());");
    interfaceFormatter.WriteLine("lexer.SetClassMap(*rv);");
    interfaceFormatter.WriteLine("lexer.SetTokenCollection(GetTokens());");
    interfaceFormatter.WriteLine("lexer.SetKeywordMap(GetKeywords<CharT>());");
    interfaceFormatter.WriteLine("return lexer;");
    interfaceFormatter.DecIndent();
    interfaceFormatter.WriteLine("}");
    interfaceFormatter.WriteLine();
    interfaceFormatter.WriteLine("template class " + lexer->Name() + "<char32_t>;");
    interfaceFormatter.WriteLine("template class soul::lexer::Lexer<" + lexer->Name() + "<char32_t>, char32_t>;");
    interfaceFormatter.WriteLine();
    interfaceFormatter.WriteLine("} // namespace " + soul::ast::common::ToNamespaceName(moduleName));
    if (verbose)
    {
        std::cout << "==> " << interfaceFilePath << "\n";
    }
    sourceFormatter.WriteLine();
    sourceFormatter.WriteLine("std::mutex mtx;");
    sourceFormatter.WriteLine();
    sourceFormatter.WriteLine("std::mutex& MakeLexerMtx() { return mtx; }");
    sourceFormatter.WriteLine();
    sourceFormatter.WriteLine("template<>");
    sourceFormatter.WriteLine("soul::lexer::KeywordMap<char>* GetKeywords<char>()");
    sourceFormatter.WriteLine("{");
    sourceFormatter.IncIndent();
    sourceFormatter.WriteLine("static const soul::lexer::Keyword<char> keywords[] = {");
    sourceFormatter.IncIndent();
    bool first = true;
    auto keywords = lexerContext.GetKeywords();
    bool hasKw = false;
    for (const auto* keyword : keywords->GetKeywords())
    {
        if (first)
        {
            first = false;
        }
        else
        {
            sourceFormatter.WriteLine(",");
        }
        auto kwrv = GetTokenCppId(lexerFile, fileMap, keyword->GetSourcePos(), keyword->TokenName());
        if (!kwrv) return std::unexpected<int>(kwrv.error());
        sourceFormatter.Write(" { \"" + keyword->Str() + "\", " + *kwrv + " }");
        hasKw = true;
    }
    if (hasKw)
    {
        sourceFormatter.WriteLine(",");
    }
    sourceFormatter.WriteLine(" { nullptr, -1 }");
    sourceFormatter.DecIndent();
    sourceFormatter.WriteLine("};");
    sourceFormatter.WriteLine("static soul::lexer::KeywordMap<char> keywordMap(keywords);");
    sourceFormatter.WriteLine("return &keywordMap;");
    sourceFormatter.DecIndent();
    sourceFormatter.WriteLine("}");

    sourceFormatter.WriteLine();
    sourceFormatter.WriteLine("template<>");
    sourceFormatter.WriteLine("soul::lexer::KeywordMap<char8_t>* GetKeywords<char8_t>()");
    sourceFormatter.WriteLine("{");
    sourceFormatter.IncIndent();
    sourceFormatter.WriteLine("static const soul::lexer::Keyword<char8_t> keywords[] = {");
    sourceFormatter.IncIndent();
    bool first8 = true;
    bool hasKw8 = false;
    auto keywords8 = lexerContext.GetKeywords();
    for (const auto* keyword : keywords8->GetKeywords())
    {
        if (first8)
        {
            first8 = false;
        }
        else
        {
            sourceFormatter.WriteLine(",");
        }
        auto kwrv = GetTokenCppId(lexerFile, fileMap, keyword->GetSourcePos(), keyword->TokenName());
        if (!kwrv) return std::unexpected<int>(kwrv.error());
        sourceFormatter.Write(" { u8\"" + keyword->Str() + "\", " + *kwrv + " }");
        hasKw8 = true;
    }
    if (hasKw8)
    {
        sourceFormatter.WriteLine(",");
    }
    sourceFormatter.WriteLine(" { nullptr, -1 }");
    sourceFormatter.DecIndent();
    sourceFormatter.WriteLine("};");
    sourceFormatter.WriteLine("static soul::lexer::KeywordMap<char8_t> keywordMap(keywords);");
    sourceFormatter.WriteLine("return &keywordMap;");
    sourceFormatter.DecIndent();
    sourceFormatter.WriteLine("}");
    sourceFormatter.WriteLine();
    sourceFormatter.WriteLine("template<>");
    sourceFormatter.WriteLine("soul::lexer::KeywordMap<char16_t>* GetKeywords<char16_t>()");
    sourceFormatter.WriteLine("{");
    sourceFormatter.IncIndent();
    sourceFormatter.WriteLine("static const soul::lexer::Keyword<char16_t> keywords[] = {");
    sourceFormatter.IncIndent();
    bool first16 = true;
    bool hasKw16 = false;
    auto keywords16 = lexerContext.GetKeywords();
    for (const auto* keyword : keywords16->GetKeywords())
    {
        if (first16)
        {
            first16 = false;
        }
        else
        {
            sourceFormatter.WriteLine(",");
        }
        auto kwrv = GetTokenCppId(lexerFile, fileMap, keyword->GetSourcePos(), keyword->TokenName());
        if (!kwrv) return std::unexpected<int>(kwrv.error());
        sourceFormatter.Write(" { u\"" + keyword->Str() + "\", " + *kwrv + " }");
        hasKw16 = true;
    }
    if (hasKw16)
    {
        sourceFormatter.WriteLine(",");
    }
    sourceFormatter.WriteLine(" { nullptr, -1 }");
    sourceFormatter.DecIndent();
    sourceFormatter.WriteLine("};");
    sourceFormatter.WriteLine("static soul::lexer::KeywordMap<char16_t> keywordMap(keywords);");
    sourceFormatter.WriteLine("return &keywordMap;");
    sourceFormatter.DecIndent();
    sourceFormatter.WriteLine("}");

    sourceFormatter.WriteLine();
    sourceFormatter.WriteLine("template<>");
    sourceFormatter.WriteLine("soul::lexer::KeywordMap<char32_t>* GetKeywords<char32_t>()");
    sourceFormatter.WriteLine("{");
    sourceFormatter.IncIndent();
    sourceFormatter.WriteLine("static const soul::lexer::Keyword<char32_t> keywords[] = {");
    sourceFormatter.IncIndent();
    bool first32 = true;
    bool hasKw32 = false;
    auto keywords32 = lexerContext.GetKeywords();
    for (const auto* keyword : keywords32->GetKeywords())
    {
        if (first32)
        {
            first32 = false;
        }
        else
        {
            sourceFormatter.WriteLine(",");
        }
        auto kwrv = GetTokenCppId(lexerFile, fileMap, keyword->GetSourcePos(), keyword->TokenName());
        if (!kwrv) return std::unexpected<int>(kwrv.error());
        sourceFormatter.Write(" { U\"" + keyword->Str() + "\", " + *kwrv + " }");
        hasKw32 = true;
    }
    if (hasKw32)
    {
        sourceFormatter.WriteLine(",");
    }
    sourceFormatter.WriteLine(" { nullptr, -1 }");
    sourceFormatter.DecIndent();
    sourceFormatter.WriteLine("};");
    sourceFormatter.WriteLine("static soul::lexer::KeywordMap<char32_t> keywordMap(keywords);");
    sourceFormatter.WriteLine("return &keywordMap;");
    sourceFormatter.DecIndent();
    sourceFormatter.WriteLine("}");

    sourceFormatter.WriteLine();
    sourceFormatter.WriteLine("} // namespace " + soul::ast::common::ToNamespaceName(moduleName));

    if (verbose)
    {
        std::cout << "==> " << sourceFilePath << "\n";
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> GenerateLexer(soul::ast::slg::SlgFile* slgFile, soul::ast::slg::LexerFile* lexerFile, soul::lexer::FileMap& fileMap,
    bool verbose, bool debug)
{
    soul::ast::re::LexerContext lexerContext;
    if (!lexerContext) return std::unexpected<int>(lexerContext.Error());
    if (verbose) lexerContext.SetVerbose();
    if (debug) lexerContext.SetDebug();
    lexerContext.SetFileName(lexerFile->FilePath());
    lexerContext.SetBase(util::Path::GetDirectoryName(lexerFile->FilePath()));
    RegularExpressionParser regularExpressionParser;
    lexerContext.SetExprParser(&regularExpressionParser);
    soul::ast::slg::Tokens tokens;
    soul::ast::slg::Keywords keywords;
    soul::ast::slg::Expressions expressions;
    for (const auto& imprt : lexerFile->Imports())
    {
        soul::ast::common::Collection* collection = slgFile->GetCollection(imprt->ModuleName());
        if (collection)
        {
            switch (collection->Kind())
            {
                case soul::ast::common::CollectionKind::tokenCollection:
                {
                    soul::ast::common::TokenCollection* tokenCollection = static_cast<soul::ast::common::TokenCollection*>(collection);
                    for (const auto& token : tokenCollection->Tokens())
                    {
                        tokens.AddToken(token.get());
                        auto rv = lexerFile->GetTokenMap()->AddToken(token.get());
                        if (!rv) return rv;
                    }
                    break;
                }
                case soul::ast::common::CollectionKind::keywordCollection:
                {
                    soul::ast::slg::KeywordCollection* keywordCollection = static_cast<soul::ast::slg::KeywordCollection*>(collection);
                    for (const auto& keyword : keywordCollection->GetKeywords())
                    {
                        keywords.AddKeyword(keyword.get());
                    }
                    break;
                }
                case soul::ast::common::CollectionKind::expressionCollection:
                {
                    soul::ast::slg::ExpressionCollection* expressionCollection = static_cast<soul::ast::slg::ExpressionCollection*>(collection);
                    for (const auto& expression : expressionCollection->GetExpressions())
                    {
                        std::expected<bool, int> rv = expressions.AddExpression(expression.get());
                        if (!rv) return std::unexpected<int>(rv.error());
                    }
                    break;
                }
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

std::expected<bool, int> GenerateLexer(soul::ast::slg::SlgFile* slgFile, soul::lexer::FileMap& fileMap, bool verbose, bool debug)
{
    if (verbose)
    {
        std::cout << "generating lexers for project '" << slgFile->ProjectName() << "'..." << "\n";
    }
    auto u = util::GetFullPath(slgFile->FilePath());
    if (!u) return std::unexpected<int>(u.error());
    std::string filePath = *u;
    std::string dir = util::Path::GetDirectoryName(filePath);
    for (const auto& declaration : slgFile->Declarations())
    {
        switch (declaration->Kind())
        {
            case soul::ast::slg::SlgFileDeclarationKind::tokenFileDeclaration:
            {
                soul::ast::slg::TokenFileDeclaration* tokenFileDeclaration = static_cast<soul::ast::slg::TokenFileDeclaration*>(declaration.get());
                auto u = util::GetFullPath(util::Path::Combine(dir, tokenFileDeclaration->FilePath()));
                if (!u) return std::unexpected<int>(u.error());
                std::string tokenFilePath = *u;
                if (verbose)
                {
                    std::cout << "> " << tokenFilePath << "\n";
                }
                std::expected<std::unique_ptr<soul::ast::common::TokenFile>, int> rv = ParseTokenFile(tokenFilePath, tokenFileDeclaration->External(), fileMap);
                if (!rv) return std::unexpected<int>(rv.error());
                std::unique_ptr<soul::ast::common::TokenFile> tokenFile = std::move(*rv);
                std::expected<bool, int> mrv = GenerateTokenModule(tokenFile.get(), verbose);
                if (!mrv) return std::unexpected<int>(mrv.error());
                std::expected<bool, int> trv = slgFile->AddTokenFile(tokenFile.release());
                if (!trv) return std::unexpected<int>(trv.error());
                break;
            }
            case soul::ast::slg::SlgFileDeclarationKind::keywordFileDeclaration:
            {
                auto u = util::GetFullPath(util::Path::Combine(dir, declaration->FilePath()));
                if (!u) return std::unexpected<int>(u.error());
                std::string keywordFilePath = *u;
                if (verbose)
                {
                    std::cout << "> " << keywordFilePath << "\n";
                }
                std::expected<std::unique_ptr<soul::ast::slg::KeywordFile>, int> rv = ParseKeywordFile(keywordFilePath, fileMap);
                if (!rv) return std::unexpected<int>(rv.error());
                std::unique_ptr<soul::ast::slg::KeywordFile> keywordFile = std::move(*rv);
                std::expected<bool, int> krv = slgFile->AddKeywordFile(keywordFile.release());
                if (!krv) return std::unexpected<int>(krv.error());
                break;
            }
            case soul::ast::slg::SlgFileDeclarationKind::expressionFileDeclaration:
            {
                auto u = util::GetFullPath(util::Path::Combine(dir, declaration->FilePath()));
                if (!u) return std::unexpected<int>(u.error());
                std::string expressionFilePath = *u;
                if (verbose)
                {
                    std::cout << "> " << expressionFilePath << "\n";
                }
                std::expected<std::unique_ptr<soul::ast::slg::ExpressionFile>, int> rv = ParseExpressionFile(expressionFilePath, fileMap);
                if (!rv) return std::unexpected<int>(rv.error());
                std::unique_ptr<soul::ast::slg::ExpressionFile> expressionFile = std::move(*rv);
                std::expected<bool, int> erv = slgFile->AddExpressionFile(expressionFile.release());
                if (!erv) return std::unexpected<int>(erv.error());
                break;
            }
            case soul::ast::slg::SlgFileDeclarationKind::lexerFileDeclararation:
            {
                auto u = util::GetFullPath(util::Path::Combine(dir, declaration->FilePath()));
                if (!u) return std::unexpected<int>(u.error());
                std::string lexerFilePath = *u;
                if (verbose)
                {
                    std::cout << "> " << lexerFilePath << "\n";
                }
                std::expected<std::unique_ptr<soul::ast::slg::LexerFile>, int> rv = ParseLexerFile(lexerFilePath, fileMap);
                if (!rv) return std::unexpected<int>(rv.error());
                std::unique_ptr<soul::ast::slg::LexerFile> lexerFile = std::move(*rv);
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
        std::cout << "lexers for project '" << slgFile->ProjectName() << "' generated successfully." << "\n";
    }
    return std::expected<bool, int>(true);
}

} // namespace soul::slg
