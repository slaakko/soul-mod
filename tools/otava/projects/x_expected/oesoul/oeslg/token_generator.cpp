// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.slg.token.generator;

import soul.ast.common;
import util;

namespace soul::slg {

std::expected<bool, int> GenerateTokenModule(soul::ast::common::TokenFile* tokenFile, bool verbose)
{
    if (tokenFile->IsExternal())
    {
        if (verbose)
        {
            std::cout << "skipping external token file '" + tokenFile->FilePath() + "'" << "\n";
        }
        return std::expected<bool, int>(false);
    }
    std::string interfaceFilePath = tokenFile->FilePath();
    interfaceFilePath.append(".cppm");
    std::ofstream interfaceFile(interfaceFilePath);
    if (!interfaceFile) return std::unexpected<int>(util::AllocateError("could not create file '" + interfaceFilePath + "'"));
    util::CodeFormatter formatter(interfaceFile);
    soul::ast::common::TokenCollection* tokenCollection = tokenFile->GetTokenCollection();
    formatter.WriteLine();
    formatter.WriteLine("// this file has been automatically generated from '" +
        tokenFile->FilePath() + "' using soul lexer generator version " + util::SoulVersionStr());
    formatter.WriteLine();
    formatter.WriteLine("export module " + tokenCollection->Name() + ";");
    formatter.WriteLine();
    formatter.WriteLine("import std;");
    formatter.WriteLine();
    std::string tokenNamespaceName = soul::ast::common::ToNamespaceName(tokenCollection->Name());
    formatter.WriteLine("export namespace " + tokenNamespaceName + " {");
    formatter.WriteLine();
    formatter.WriteLine("constexpr std::int32_t tokenSetID = " + std::to_string(tokenCollection->Id()) + ";");
    formatter.WriteLine();
    int n = static_cast<int>(tokenCollection->Tokens().size());
    for (int i = 0; i < n; ++i)
    {
        soul::ast::common::Token* token = tokenCollection->Tokens()[i].get();
        formatter.WriteLine("constexpr std::int64_t " + token->Name() + " = (static_cast<std::int64_t>(tokenSetID) << 32) | " + std::to_string(i + 1) + ";");
    }
    formatter.WriteLine();
    formatter.WriteLine("} // " + tokenNamespaceName);
    if (verbose)
    {
        std::cout << "==> " << interfaceFilePath << "\n";
    }
    return std::expected<bool, int>(true);
}

} // namespace soul::slg
