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
import soul.ast.re;
import soul.ast.cpp;
import soul.ast.common;

namespace soul::slg {

#ifndef OTAVA

void MakeNfas(soul::ast::re::LexerContext& lexerContext)
{
    for (auto& rule : lexerContext.GetLexer()->Rules())
    {
        soul::ast::re::Nfa* nfa = new soul::ast::re::Nfa(lexerContext.GetExprParser()->Parse(rule->Expr(), &lexerContext, lexerContext.FileName(), rule->Line()));
        nfa->End()->SetRuleIndex(rule->Index());
        int nfaIndex = lexerContext.AddNfa(nfa);
        rule->SetNfaIndex(nfaIndex);
    }
}

void MakeCanonicalClasses(soul::ast::re::LexerContext& lexerContext)
{
    std::vector<soul::ast::re::Symbol*> s = lexerContext.Symbols();
    for (soul::ast::re::Symbol* symbol : s)
    {
        if (symbol->Contained()) continue;
        if (symbol->Kind() == soul::ast::re::SymbolKind::classSymbol)
        {
            soul::ast::re::Class* cls = static_cast<soul::ast::re::Class*>(symbol);
            soul::ast::re::Class* canonicalClass = cls->MakeCanonical(lexerContext);
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
            soul::ast::re::Symbol* range = lexerContext.MakeRange(static_cast<char32_t>(1), static_cast<char32_t>(0x10FFFF));
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
    for (soul::ast::re::Class* canonicalClass : lexerContext.CanonicalClasses())
    {
        for (const soul::ast::re::Range& range : canonicalClass->Ranges())
        {
            if (canonicalClass->Chars().empty())
            {
                canonicalClass->AddChar(range.Start());
            }
            break;
        }
    }
}

void MakeClassPartition(soul::ast::re::LexerContext& lexerContext)
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
}

void MakeClassMap(soul::ast::re::LexerContext& lexerContext, const std::string& root, bool verbose)
{
    std::vector<std::int32_t> classMapVec(0x110000, -1);
    for (soul::ast::re::Class* cls : lexerContext.Partition())
    {
        for (const soul::ast::re::Range& range : cls->Ranges())
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
    soul::ast::slg::Lexer* lexer = lexerContext.GetLexer();
    soul::ast::slg::File* file = lexer->GetFile();
    if (file->Kind() == soul::ast::slg::FileKind::lexerFile)
    {
        soul::ast::slg::LexerFile* lexerFile = static_cast<soul::ast::slg::LexerFile*>(file);
        soul::ast::common::ExportModule* mod = lexerFile->GetExportModule();
        moduleName = mod->ModuleName();
    }
    else
    {
        throw std::runtime_error("lexer file expected");
    }
    std::string classMapName = moduleName + ".classmap";
    std::string classMapFileName = util::Path::Combine(root, classMapName);
    util::FileStream fileStream(classMapFileName, util::OpenMode::binary | util::OpenMode::write);
    util::BufferedStream bufferedStream(fileStream);
    util::BinaryStreamWriter writer(bufferedStream);
    std::int32_t size = static_cast<std::int32_t>(classMapVec.size());
    writer.Write(size);
    // size = 0x110000
    for (std::int32_t x : classMapVec)
    {
        writer.Write(x);
    }
    if (verbose)
    {
        std::cout << "==> " << classMapFileName << std::endl;
    }
}

void CompressClassMap(soul::ast::re::LexerContext& lexerContext, const std::string& root, bool verbose)
{
    std::string moduleName;
    soul::ast::slg::Lexer* lexer = lexerContext.GetLexer();
    soul::ast::slg::File* file = lexer->GetFile();
    if (file->Kind() == soul::ast::slg::FileKind::lexerFile)
    {
        soul::ast::slg::LexerFile* lexerFile = static_cast<soul::ast::slg::LexerFile*>(file);
        soul::ast::common::ExportModule* mod = lexerFile->GetExportModule();
        moduleName = mod->ModuleName();
    }
    else
    {
        throw std::runtime_error("lexer file expected");
    }
    std::string classMapName = moduleName + ".classmap";
    MakeCompressedClassMap(root, classMapName, verbose);
    MakeResourceFile(root, classMapName, verbose);
}

void MakeMasterNfa(soul::ast::re::LexerContext& lexerContext)
{
    soul::ast::re::Nfa* masterNfa = new soul::ast::re::Nfa();
    int masterNfaIndex = lexerContext.AddNfa(masterNfa);
    lexerContext.SetMasterNfaIndex(masterNfaIndex);
    soul::ast::re::NfaState* start = lexerContext.MakeNfaState();
    masterNfa->SetStart(start);
    soul::ast::slg::Lexer* lexer = lexerContext.GetLexer();
    for (const auto& rule : lexer->Rules())
    {
        soul::ast::re::Nfa* ruleNfa = lexerContext.GetNfa(rule->NfaIndex());
        start->AddEdge(soul::ast::re::NfaEdge(lexerContext.MakeEpsilon(), ruleNfa->Start()));
    }
}

void MakeDfa(soul::ast::re::LexerContext& lexerContext)
{
    soul::ast::re::Nfa* masterNfa = lexerContext.GetNfa(lexerContext.MasterNfaIndex());
    soul::ast::re::Dfa dfa = soul::ast::re::Compile(lexerContext, *masterNfa);
    lexerContext.SetDfa(std::move(dfa));
}

void WriteVariables(soul::ast::re::LexerContext& lexerContext, util::CodeFormatter& interfaceFormatter, util::CodeFormatter sourceFormatter)
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
}

void WriteLexer(soul::ast::re::LexerContext& lexerContext, soul::ast::slg::SlgFile* slgFile, const std::string& root, bool verbose, soul::common::ModuleMap& moduleMap, bool ppstyle)
{
    std::string interfaceFilePath;
    if (ppstyle)
    {
        interfaceFilePath = util::GetFullPath(util::Path::Combine(root, lexerContext.FileName() + ".hpp"));
    }
    else
    {
        interfaceFilePath = util::GetFullPath(util::Path::Combine(root, lexerContext.FileName() + ".cppm"));
    }
    std::string sourceFilePath = util::GetFullPath(util::Path::Combine(root, lexerContext.FileName() + ".cpp"));
    std::ofstream interfaceStream(interfaceFilePath);
    util::CodeFormatter interfaceFormatter(interfaceStream);
    interfaceFormatter.WriteLine("// this file has been automatically generated from '" + lexerContext.FileName() + "' using soul lexer generator slg version " + 
        util::SoulVersionStr());
    interfaceFormatter.WriteLine();
    std::ofstream sourceStream(sourceFilePath);
    util::CodeFormatter sourceFormatter(sourceStream);
    sourceFormatter.WriteLine("// this file has been automatically generated from '" + lexerContext.FileName() + "' using soul lexer generator slg version " + 
        util::SoulVersionStr());
    sourceFormatter.WriteLine();
    soul::ast::slg::Lexer* lexer = lexerContext.GetLexer();
    soul::ast::slg::File* file = lexer->GetFile();
    soul::ast::slg::LexerFile* lexerFile = nullptr;
    std::string moduleName;
    if (file->Kind() == soul::ast::slg::FileKind::lexerFile)
    {
        lexerFile = static_cast<soul::ast::slg::LexerFile*>(file);
        soul::ast::common::ExportModule* mod = lexerFile->GetExportModule();
        moduleName = mod->ModuleName();
        moduleMap.MapModule(moduleName, interfaceFilePath);
    }
    else
    {
        throw std::runtime_error("lexer file expected");
    }
    if (ppstyle)
    {
        std::string headerFilePath = moduleMap.GetHeaderFilePath(moduleName, root);
        if (!headerFilePath.empty())
        {
            sourceFormatter.WriteLine("#include <" + headerFilePath + ">");
        }
        sourceFormatter.WriteLine();
        sourceFormatter.WriteLine("// module " + moduleName + ";");
    }
    else
    {
        sourceFormatter.WriteLine("module " + moduleName + ";");
    }
    sourceFormatter.WriteLine();
    std::string includeGuard;
    if (ppstyle)
    {
        includeGuard = "INCLUDE_GUARD_" + util::GetSha1MessageDigest(moduleName);
        interfaceFormatter.WriteLine("#ifndef " + includeGuard);
        interfaceFormatter.WriteLine("#define " + includeGuard);
        interfaceFormatter.WriteLine();
        interfaceFormatter.WriteLine("// export module " + moduleName + ";");
        interfaceFormatter.WriteLine();
        std::string soulLexerHeaderFilePath = moduleMap.GetHeaderFilePath("soul.lexer", root);
        if (!soulLexerHeaderFilePath.empty())
        {
            interfaceFormatter.WriteLine("#include <" + soulLexerHeaderFilePath + ">");
        }
        std::string soulAstSlgHeaderFilePath = moduleMap.GetHeaderFilePath("soul.ast.slg", root);
        if (!soulAstSlgHeaderFilePath.empty())
        {
            interfaceFormatter.WriteLine("#include <" + soulAstSlgHeaderFilePath + ">");
        }
        interfaceFormatter.WriteLine("#include <util/binary_resource_ptr.hpp>");
        interfaceFormatter.WriteLine("#include <mutex>");
    }
    else
    {
        interfaceFormatter.WriteLine("export module " + moduleName + ";");
        interfaceFormatter.WriteLine();
        interfaceFormatter.WriteLine("import std;");
        interfaceFormatter.WriteLine("import soul.lexer;");
        interfaceFormatter.WriteLine("import soul.ast.slg;");
        interfaceFormatter.WriteLine("import util;");
    }
    for (const auto& imprt : lexerFile->Imports())
    {
        soul::ast::slg::Collection* collection = slgFile->GetCollection(imprt->ModuleName());
        if (collection->Kind() == soul::ast::slg::CollectionKind::tokenCollection)
        {
            if (ppstyle)
            {
                std::string tokenCollectionHeader = moduleMap.GetHeaderFilePath(collection->Name(), root);
                if (!tokenCollectionHeader.empty())
                {
                    interfaceFormatter.WriteLine("#include <" + tokenCollectionHeader + ">");
                }
            }
            else
            {
                interfaceFormatter.WriteLine("import " + collection->Name() + ";");
            }
        }
    }
    interfaceFormatter.WriteLine();
    interfaceFormatter.WriteLine("using namespace soul;");
    interfaceFormatter.WriteLine("using namespace soul::lexer;");
    for (const auto& imprt : lexerFile->Imports())
    {
        soul::ast::slg::Collection* collection = slgFile->GetCollection(imprt->ModuleName());
        if (collection->Kind() == soul::ast::slg::CollectionKind::tokenCollection)
        {
            interfaceFormatter.WriteLine("using namespace " + soul::ast::common::ToNamespaceName(collection->Name()) + ";");
            sourceFormatter.WriteLine("using namespace " + soul::ast::common::ToNamespaceName(collection->Name()) + ";");
        }
    }
    interfaceFormatter.WriteLine();
    sourceFormatter.WriteLine();
    if (ppstyle)
    {
        interfaceFormatter.WriteLine("namespace " + soul::ast::common::ToNamespaceName(moduleName) + " {");
    }
    else
    {
        interfaceFormatter.WriteLine("export namespace " + soul::ast::common::ToNamespaceName(moduleName) + " {");
    }
    interfaceFormatter.WriteLine();
    interfaceFormatter.WriteLine("std::mutex& MakeLexerMtx();");
    interfaceFormatter.WriteLine();
    interfaceFormatter.WriteLine("template<typename Char>");
    interfaceFormatter.WriteLine("struct " + lexer->Name() + ";");
    interfaceFormatter.WriteLine();
    interfaceFormatter.WriteLine("template<typename Char>");
    interfaceFormatter.WriteLine("soul::lexer::Lexer<" + lexer->Name() + "<Char>, Char> MakeLexer(const Char* start, const Char* end, const std::string& fileName);");
    interfaceFormatter.WriteLine();
    interfaceFormatter.WriteLine("template<typename Char>");
    interfaceFormatter.WriteLine("soul::lexer::Lexer<" + lexer->Name() + 
        "<Char>, Char> MakeLexer(const std::string& moduleFileName, util::ResourceFlags resourceFlags, const Char* start, const Char* end, const std::string& fileName);");
    interfaceFormatter.WriteLine();
    interfaceFormatter.WriteLine("soul::ast::slg::TokenCollection* GetTokens();");
    interfaceFormatter.WriteLine();
    sourceFormatter.WriteLine("namespace " + soul::ast::common::ToNamespaceName(moduleName) + " {");
    sourceFormatter.WriteLine();
    sourceFormatter.WriteLine("soul::ast::slg::TokenCollection* GetTokens()");
    sourceFormatter.WriteLine("{");
    sourceFormatter.IncIndent();
    sourceFormatter.WriteLine("static soul::ast::slg::TokenCollection tokens(\"" + moduleName + ".tokens\");");
    sourceFormatter.WriteLine("if (!tokens.Initialized())");
    sourceFormatter.WriteLine("{");
    sourceFormatter.IncIndent();
    sourceFormatter.WriteLine("tokens.SetInitialized();");
    soul::ast::slg::Tokens* tokens = lexerContext.GetTokens();
    for (const auto& token : tokens->GetTokens())
    {
        sourceFormatter.WriteLine("tokens.AddToken(new soul::ast::slg::Token(" + token->Name() + ", \"" + token->Name() + "\", \"" + token->Info() + "\"));");
    }
    sourceFormatter.DecIndent();
    sourceFormatter.WriteLine("}");
    sourceFormatter.WriteLine("return &tokens;");
    sourceFormatter.DecIndent();
    sourceFormatter.WriteLine("}");
    WriteVariables(lexerContext, interfaceFormatter, sourceFormatter);
    interfaceFormatter.WriteLine();
    interfaceFormatter.WriteLine("template<typename Char>");
    interfaceFormatter.WriteLine("struct " + lexer->Name());
    interfaceFormatter.WriteLine("{");
    interfaceFormatter.IncIndent();
    interfaceFormatter.WriteLine("using Variables = " + lexer->VariableClassName() + ";");
    interfaceFormatter.WriteLine();
    interfaceFormatter.WriteLine("static std::int32_t NextState(std::int32_t state, Char chr, soul::lexer::LexerBase<Char>& lexer)");
    interfaceFormatter.WriteLine("{");
    interfaceFormatter.IncIndent();
    interfaceFormatter.WriteLine("soul::lexer::ClassMap<Char>* classmap = lexer.GetClassMap();");
    interfaceFormatter.WriteLine("std::int32_t cls = classmap->GetClass(chr);");
    interfaceFormatter.WriteLine("switch (state)");
    interfaceFormatter.WriteLine("{");
    interfaceFormatter.IncIndent();
    for (const auto& state : lexerContext.GetDfa().States())
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
            soul::ast::re::DfaState* next = state->Next(cls->Index());
            if (next != nullptr)
            {
                m[next->Id()].insert(cls->Index());
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
                const std::set<std::int32_t>& s = p.second;
                for (std::int32_t k : s)
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
    interfaceFormatter.WriteLine("static std::int64_t GetTokenId(std::int32_t ruleIndex, soul::lexer::LexerBase<Char>& lexer)");
    interfaceFormatter.WriteLine("{");
    interfaceFormatter.IncIndent();
    interfaceFormatter.WriteLine("switch (ruleIndex)");
    interfaceFormatter.WriteLine("{");
    interfaceFormatter.IncIndent();
    for (const auto& rule : lexer->Rules())
    {
        interfaceFormatter.WriteLine("case " + std::to_string(rule->Index()) + ":");
        soul::ast::SourcePos sourcePos; // todo
        rule->Code()->InsertFront(
            new soul::ast::cpp::ExpressionStatementNode(sourcePos, 
                new soul::ast::cpp::InvokeNode(sourcePos, 
                    new soul::ast::cpp::IdExprNode(sourcePos, "lexer.Retract"))));
        if (rule->Action() != -1)
        {
            soul::ast::slg::Action* action = lexer->GetActions().GetAction(rule->Action());
            if (action != nullptr)
            {
                soul::ast::cpp::CodeEvaluationVisitor visitor;
                action->Code()->Accept(visitor);
                int n = action->Code()->Statements().size();
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
                throw std::runtime_error("action " + std::to_string(rule->Action()) + " not found");
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
    interfaceFormatter.WriteLine("template<typename Char>");
    interfaceFormatter.WriteLine("soul::lexer::ClassMap<Char>* GetClassMap()");
    interfaceFormatter.WriteLine("{");
    interfaceFormatter.IncIndent();
    interfaceFormatter.WriteLine("static soul::lexer::ClassMap<Char>* classmap = soul::lexer::MakeClassMap<Char>(\"" + moduleName + ".classmap\");");
    interfaceFormatter.WriteLine("return classmap;");
    interfaceFormatter.DecIndent();
    interfaceFormatter.WriteLine("}");
    interfaceFormatter.WriteLine();
    interfaceFormatter.WriteLine("template<typename Char>");
    interfaceFormatter.WriteLine("soul::lexer::ClassMap<Char>* GetClassMap(const std::string& moduleFileName, util::ResourceFlags resourceFlags)");
    interfaceFormatter.WriteLine("{");
    interfaceFormatter.IncIndent();
    interfaceFormatter.WriteLine("static soul::lexer::ClassMap<Char>* classmap = soul::lexer::MakeClassMap<Char>(moduleFileName, \"" + moduleName + ".classmap\", resourceFlags);");
    interfaceFormatter.WriteLine("return classmap;");
    interfaceFormatter.DecIndent();
    interfaceFormatter.WriteLine("}");
    interfaceFormatter.WriteLine();
    interfaceFormatter.WriteLine("template<typename Char>");
    interfaceFormatter.WriteLine("soul::lexer::KeywordMap<Char>* GetKeywords();");
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

    interfaceFormatter.WriteLine("template<typename Char>");
    interfaceFormatter.WriteLine("soul::lexer::Lexer<" + lexer->Name() + "<Char>, Char> MakeLexer(const Char* start, const Char* end, const std::string& fileName)");
    interfaceFormatter.WriteLine("{");
    interfaceFormatter.IncIndent();
    interfaceFormatter.WriteLine("std::lock_guard<std::mutex> lock(MakeLexerMtx());");
    interfaceFormatter.WriteLine("auto lexer = soul::lexer::Lexer<" + lexer->Name() + "<Char>, Char>(start, end, fileName);");
    interfaceFormatter.WriteLine("lexer.SetClassMap(GetClassMap<Char>());");
    interfaceFormatter.WriteLine("lexer.SetTokenCollection(GetTokens());");
    interfaceFormatter.WriteLine("lexer.SetKeywordMap(GetKeywords<Char>());");
    interfaceFormatter.WriteLine("return lexer;");
    interfaceFormatter.DecIndent();
    interfaceFormatter.WriteLine("}");
    interfaceFormatter.WriteLine();
    
    interfaceFormatter.WriteLine("template<typename Char>");
    interfaceFormatter.WriteLine("soul::lexer::Lexer<" + lexer->Name() + 
        "<Char>, Char> MakeLexer(const std::string& moduleFileName, util::ResourceFlags resourceFlags, const Char* start, const Char* end, const std::string& fileName)");
    interfaceFormatter.WriteLine("{");
    interfaceFormatter.IncIndent();
    interfaceFormatter.WriteLine("std::lock_guard<std::mutex> lock(MakeLexerMtx());");
    interfaceFormatter.WriteLine("auto lexer = soul::lexer::Lexer<" + lexer->Name() + "<Char>, Char>(start, end, fileName);");
    interfaceFormatter.WriteLine("lexer.SetClassMap(GetClassMap<Char>(moduleFileName, resourceFlags));");
    interfaceFormatter.WriteLine("lexer.SetTokenCollection(GetTokens());");
    interfaceFormatter.WriteLine("lexer.SetKeywordMap(GetKeywords<Char>());");
    interfaceFormatter.WriteLine("return lexer;");
    interfaceFormatter.DecIndent();
    interfaceFormatter.WriteLine("}");
    interfaceFormatter.WriteLine();
    
    interfaceFormatter.WriteLine("} // namespace " + soul::ast::common::ToNamespaceName(moduleName));
    if (ppstyle)
    {
        interfaceFormatter.WriteLine();
        interfaceFormatter.WriteLine("#endif // " + includeGuard);
    }
    if (verbose)
    {
        std::cout << "==> " << interfaceFilePath << std::endl;
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
    for (const auto& keyword : keywords->GetKeywords())
    {
        if (first)
        {
            first = false;
        }
        else
        {
            sourceFormatter.WriteLine(",");
        }
        sourceFormatter.Write(" { \"" + keyword->Str() + "\", " + keyword->TokenName() + " }");
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
    for (const auto& keyword : keywords8->GetKeywords())
    {
        if (first8)
        {
            first8 = false;
        }
        else
        {
            sourceFormatter.WriteLine(",");
        }
        sourceFormatter.Write(" { u8\"" + keyword->Str() + "\", " + keyword->TokenName() + " }");
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
    for (const auto& keyword : keywords16->GetKeywords())
    {
        if (first16)
        {
            first16 = false;
        }
        else
        {
            sourceFormatter.WriteLine(",");
        }
        sourceFormatter.Write(" { u\"" + keyword->Str() + "\", " + keyword->TokenName() + " }");
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
    for (const auto& keyword : keywords32->GetKeywords())
    {
        if (first32)
        {
            first32 = false;
        }
        else
        {
            sourceFormatter.WriteLine(",");
        }
        sourceFormatter.Write(" { U\"" + keyword->Str() + "\", " + keyword->TokenName() + " }");
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
        std::cout << "==> " << sourceFilePath << std::endl;
    }
}

void GenerateLexer(soul::ast::slg::SlgFile* slgFile, soul::ast::slg::LexerFile* lexerFile, bool verbose, soul::common::ModuleMap& moduleMap, bool ppstyle)
{
    soul::ast::re::LexerContext lexerContext;
    lexerContext.SetFileName(lexerFile->FilePath());
    RegularExpressionParser regularExpressionParser;
    lexerContext.SetExprParser(&regularExpressionParser);
    soul::ast::slg::Tokens tokens;
    soul::ast::slg::Keywords keywords;
    soul::ast::slg::Expressions expressions;
    for (const auto& imprt : lexerFile->Imports())
    {
        soul::ast::slg::Collection* collection = slgFile->GetCollection(imprt->ModuleName());
        switch (collection->Kind())
        {
            case soul::ast::slg::CollectionKind::tokenCollection:
            {
                soul::ast::slg::TokenCollection* tokenCollection = static_cast<soul::ast::slg::TokenCollection*>(collection);
                for (const auto& token : tokenCollection->Tokens())
                {
                    tokens.AddToken(token.get());
                }
                break;
            }
            case soul::ast::slg::CollectionKind::keywordCollection:
            {
                soul::ast::slg::KeywordCollection* keywordCollection = static_cast<soul::ast::slg::KeywordCollection*>(collection);
                for (const auto& keyword : keywordCollection->Keywords())
                {
                    keywords.AddKeyword(keyword.get());
                }
                break;
            }
            case soul::ast::slg::CollectionKind::expressionCollection:
            {
                soul::ast::slg::ExpressionCollection* expressionCollection = static_cast<soul::ast::slg::ExpressionCollection*>(collection);
                for (const auto& expression : expressionCollection->Expressions())
                {
                    expressions.AddExpression(expression.get());
                }
                break;
            }
        }
    }
    lexerContext.SetTokens(&tokens);
    lexerContext.SetKeywords(&keywords);
    lexerContext.SetExpressions(&expressions);
    lexerContext.SetLexer(lexerFile->GetLexer());
    MakeNfas(lexerContext);
    MakeCanonicalClasses(lexerContext);
    MakeClassPartition(lexerContext);
    std::string root = util::Path::GetDirectoryName(slgFile->FilePath());
    MakeClassMap(lexerContext, root, verbose);
    CompressClassMap(lexerContext, root, verbose);
    MakeMasterNfa(lexerContext);
    MakeDfa(lexerContext);
    WriteLexer(lexerContext, slgFile, root, verbose, moduleMap, ppstyle);
}

void GenerateLexer(soul::ast::slg::SlgFile* slgFile, bool verbose, soul::common::ModuleMap& moduleMap, bool ppstyle)
{
    moduleMap.MapModule("soul.lexer", "../lexer/lexer.hpp");
    moduleMap.MapModule("soul.ast.slg", "../ast/slg.hpp");
    if (verbose)
    {
        std::cout << "generating lexers for project '" << slgFile->ProjectName() << "'..." << std::endl;
    }
    std::string filePath = util::GetFullPath(slgFile->FilePath());
    std::string dir = util::Path::GetDirectoryName(filePath);
    for (const auto& declaration : slgFile->Declarations())
    {
        switch (declaration->Kind())
        {
            case soul::ast::slg::SlgFileDeclarationKind::tokenFileDeclaration:
            {
                soul::ast::slg::TokenFileDeclaration* tokenFileDeclaration = static_cast<soul::ast::slg::TokenFileDeclaration*>(declaration.get());
                std::string tokenFilePath = util::GetFullPath(util::Path::Combine(dir, tokenFileDeclaration->FilePath()));
                if (verbose)
                {
                    std::cout << "> " << tokenFilePath << std::endl;
                }
                std::unique_ptr<soul::ast::slg::TokenFile> tokenFile = ParseTokenFile(tokenFilePath, tokenFileDeclaration->External());
                GenerateTokenModule(tokenFile.get(), verbose, moduleMap, ppstyle);
                slgFile->AddTokenFile(tokenFile.release());
                break;
            }
            case soul::ast::slg::SlgFileDeclarationKind::keywordFileDeclaration:
            {
                std::string keywordFilePath = util::GetFullPath(util::Path::Combine(dir, declaration->FilePath()));
                if (verbose)
                {
                    std::cout << "> " << keywordFilePath << std::endl;
                }
                std::unique_ptr<soul::ast::slg::KeywordFile> keywordFile = ParseKeywordFile(keywordFilePath);
                slgFile->AddKeywordFile(keywordFile.release());
                break;
            }
            case soul::ast::slg::SlgFileDeclarationKind::expressionFileDeclaration:
            {
                std::string expressionFilePath = util::GetFullPath(util::Path::Combine(dir, declaration->FilePath()));
                if (verbose)
                {
                    std::cout << "> " << expressionFilePath << std::endl;
                }
                std::unique_ptr<soul::ast::slg::ExpressionFile> expressionFile = ParseExpressionFile(expressionFilePath);
                slgFile->AddExpressionFile(expressionFile.release());
                break;
            }
            case soul::ast::slg::SlgFileDeclarationKind::lexerFileDeclararation:
            {
                std::string lexerFilePath = util::GetFullPath(util::Path::Combine(dir, declaration->FilePath()));
                if (verbose)
                {
                    std::cout << "> " << lexerFilePath << std::endl;
                }
                std::unique_ptr<soul::ast::slg::LexerFile> lexerFile = ParseLexerFile(lexerFilePath);
                slgFile->AddLexerFile(lexerFile.release());
                break;
            }
        }
    }
    for (const auto& lexerFile : slgFile->LexerFiles())
    {
        GenerateLexer(slgFile, lexerFile.get(), verbose, moduleMap, ppstyle);
    }
    if (verbose)
    {
        std::cout << "lexers for project '" << slgFile->ProjectName() << "' generated successfully." << std::endl;
    }
}

#else

void GenerateLexer(soul::ast::slg::SlgFile* slgFile, bool verbose, soul::common::ModuleMap& moduleMap, bool ppstyle)
{
}

#endif

} // namespace soul::slg
