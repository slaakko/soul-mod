// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.slg.token.generator;

import soul.ast.common;
import util;

namespace soul::slg {

void GenerateTokenModule(soul::ast::common::TokenFile* tokenFile, bool verbose, soul::common::ModuleMap& moduleMap, bool ppstyle)
{
    if (tokenFile->IsExternal())
    {
        if (verbose)
        {
            std::cout << "skipping external token file '" + tokenFile->FilePath() + "'" << std::endl;
        }
        return;
    }
    std::string interfaceFilePath;
    if (ppstyle)
    {
        interfaceFilePath = tokenFile->FilePath() + ".hpp";
    }
    else
    {
        interfaceFilePath = tokenFile->FilePath() + ".cppm";
    }
    std::ofstream interfaceFile(interfaceFilePath);
    util::CodeFormatter formatter(interfaceFile);
    soul::ast::common::TokenCollection* tokenCollection = tokenFile->GetTokenCollection();
    if (ppstyle)
    {
        moduleMap.MapModule(tokenCollection->Name(), interfaceFilePath);
    }
    formatter.WriteLine();
    formatter.WriteLine("// this file has been automatically generated from '" + tokenFile->FilePath() + "' using soul lexer generator version " + util::SoulVersionStr());
    formatter.WriteLine();
    std::string includeGuard;
    if (ppstyle)
    {
        includeGuard = "INCLUDE_GUARD_" + util::GetSha1MessageDigest(tokenCollection->Name());
        formatter.WriteLine("#ifndef " + includeGuard);
        formatter.WriteLine("#define " + includeGuard);
        formatter.WriteLine("#include <cstdint");
        formatter.WriteLine();
        formatter.WriteLine("// export module " + tokenCollection->Name() + ";");
        formatter.WriteLine();
    }
    else
    {
        formatter.WriteLine("export module " + tokenCollection->Name() + ";");
        formatter.WriteLine();
        formatter.WriteLine("import std;");
        formatter.WriteLine();
    }
    std::string tokenNamespaceName = soul::ast::common::ToNamespaceName(tokenCollection->Name());
    if (ppstyle)
    {
        formatter.WriteLine("namespace " + tokenNamespaceName + " {");
        formatter.WriteLine();
    }
    else
    {
        formatter.WriteLine("export namespace " + tokenNamespaceName + " {");
        formatter.WriteLine();
    }
    formatter.WriteLine("constexpr std::int32_t tokenSetID = " + std::to_string(tokenCollection->Id()) + ";");
    formatter.WriteLine();
    int n = tokenCollection->Tokens().size();
    for (int i = 0; i < n; ++i)
    {
        soul::ast::common::Token* token = tokenCollection->Tokens()[i].get();
        formatter.WriteLine("constexpr std::int64_t " + token->Name() + " = (static_cast<std::int64_t>(tokenSetID) << 32) | " + std::to_string(i + 1) + ";");
    }
    formatter.WriteLine();
    if (ppstyle)
    {
        formatter.WriteLine("} // " + tokenNamespaceName); 
        formatter.WriteLine();
        formatter.WriteLine("#endif // " + includeGuard);
    }
    else
    {
        formatter.WriteLine("} // " + tokenNamespaceName);
    }
    if (verbose)
    {
        std::cout << "==> " << interfaceFilePath << std::endl;
    }
}

} // namespace soul::slg
