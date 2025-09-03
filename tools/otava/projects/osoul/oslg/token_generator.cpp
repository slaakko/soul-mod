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
    std::string interfaceFilePath;
    interfaceFilePath = tokenFile->FilePath() + ".cppm";
    std::ofstream interfaceFile(interfaceFilePath);
    if (!interfaceFile) return std::unexpected<int>(util::AllocateError("could not create file '" + interfaceFilePath + "'"));
    util::CodeFormatter formatter(interfaceFile);
    soul::ast::common::TokenCollection* tokenCollection = tokenFile->GetTokenCollection();
    formatter.WriteLine();
    std::expected<bool, int> rv = formatter.WriteLine("// this file has been automatically generated from '" +
        tokenFile->FilePath() + "' using soul lexer generator version " + util::SoulVersionStr());
    if (!rv) return rv;
    formatter.WriteLine();
    rv = formatter.WriteLine("export module " + tokenCollection->Name() + ";");
    if (!rv) return rv;
    formatter.WriteLine();
    rv = formatter.WriteLine("import std;");
    if (!rv) return rv;
    formatter.WriteLine();
    std::string tokenNamespaceName = soul::ast::common::ToNamespaceName(tokenCollection->Name());
    rv = formatter.WriteLine("export namespace " + tokenNamespaceName + " {");
    if (!rv) return rv;
    formatter.WriteLine();
    rv = formatter.WriteLine("constexpr std::int32_t tokenSetID = " + std::to_string(tokenCollection->Id()) + ";");
    if (!rv) return rv;
    formatter.WriteLine();
    int n = static_cast<int>(tokenCollection->Tokens().size());
    for (int i = 0; i < n; ++i)
    {
        soul::ast::common::Token* token = tokenCollection->Tokens()[i].get();
        rv = formatter.WriteLine("constexpr std::int64_t " + token->Name() + " = (static_cast<std::int64_t>(tokenSetID) << 32) | " + std::to_string(i + 1) + ";");
        if (!rv) return rv;
    }
    formatter.WriteLine();
    rv = formatter.WriteLine("} // " + tokenNamespaceName);
    if (!rv) return rv;
    if (verbose)
    {
        std::cout << "==> " << interfaceFilePath << "\n";
    }
    return std::expected<bool, int>(true);
}

} // namespace soul::slg
