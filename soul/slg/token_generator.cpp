// =================================
// Copyright (c) 2023 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.slg.token.generator;

import soul.ast.common;
import util;

namespace soul::slg {

#ifndef OTAVA

void GenerateTokenModule(soul::ast::slg::TokenFile* tokenFile, bool verbose)
{
    if (tokenFile->IsExternal())
    {
        if (verbose)
        {
            std::cout << "skipping external token file '" + tokenFile->FilePath() + "'" << std::endl;
        }
        return;
    }
    std::string cppmFilePath = tokenFile->FilePath() + ".cppm";
    std::ofstream cppmFile(cppmFilePath);
    util::CodeFormatter formatter(cppmFile);
    soul::ast::slg::TokenCollection* tokenCollection = tokenFile->GetTokenCollection();
    formatter.WriteLine();
    formatter.WriteLine("// this file has been automatically generated from '" + tokenFile->FilePath() + "' using soul lexer generator version 4.0.0");
    formatter.WriteLine();
    formatter.WriteLine("export module " + tokenCollection->Name() + ";");
    formatter.WriteLine();
    formatter.WriteLine("import std.core;");
    formatter.WriteLine();
    std::string tokenNamespaceName = soul::ast::common::ToNamespaceName(tokenCollection->Name());
    formatter.WriteLine("export namespace " + tokenNamespaceName + " {");
    formatter.WriteLine();
    formatter.WriteLine("constexpr int32_t tokenSetID = " + std::to_string(tokenCollection->Id()) + ";");
    formatter.WriteLine();
    int n = tokenCollection->Tokens().size();
    for (int i = 0; i < n; ++i)
    {
        soul::ast::slg::Token* token = tokenCollection->Tokens()[i].get();
        formatter.WriteLine("constexpr int64_t " + token->Name() + " = (static_cast<int64_t>(tokenSetID) << 32) | " + std::to_string(i + 1) + ";");
    }
    formatter.WriteLine();
    formatter.WriteLine("} // " + tokenNamespaceName);
    if (verbose)
    {
        std::cout << "==> " << cppmFilePath << std::endl;
    }
}

#else

void GenerateTokenModule(soul::ast::slg::TokenFile* tokenFile, bool verbose)
{
}

#endif

} // namespace soul::slg
