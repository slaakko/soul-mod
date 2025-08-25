// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul_expected.slg.code.modifier;

import util_expected;

namespace soul_expected::slg {

class CodeModifierVisitor : public soul_expected::ast::cpp::DefaultVisitor
{
public:
    CodeModifierVisitor(soul_expected::ast::common::TokenMap& tokenMap_, soul_expected::ast::slg::LexerFile* lexerFile_, soul_expected::lexer::FileMap& fileMap_);
    void Visit(soul_expected::ast::cpp::IdExprNode& node) override;
    void Visit(soul_expected::ast::cpp::TypeNameNode& node) override;
    void Visit(soul_expected::ast::cpp::ReturnStatementNode& node) override;
    bool Valid() const { return error == 0; }
    explicit operator bool() const { return Valid(); }
    int Error() const { return error; }
private:
    soul_expected::ast::common::TokenMap& tokenMap;
    soul_expected::ast::slg::LexerFile* lexerFile;
    soul_expected::lexer::FileMap& fileMap;
    bool processReturnValue;
    int error;
};

CodeModifierVisitor::CodeModifierVisitor(soul_expected::ast::common::TokenMap& tokenMap_, soul_expected::ast::slg::LexerFile* lexerFile_, 
    soul_expected::lexer::FileMap& fileMap_) :
    tokenMap(tokenMap_), lexerFile(lexerFile_), fileMap(fileMap_), processReturnValue(false), error(0)
{
}

void CodeModifierVisitor::Visit(soul_expected::ast::cpp::IdExprNode& node)
{
    if (processReturnValue)
    {
        std::vector<soul_expected::ast::common::Token*> tokens = tokenMap.GetTokens(node.Id());
        int n = static_cast<int>(tokens.size());
        if (n == 1)
        {
            soul_expected::ast::common::Token* tkn = tokens.front();
            node.SetId(tkn->FullCppId());
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
            std::expected<std::string, int> rv = soul_expected::lexer::MakeMessage("error", "ambiguous reference to token '" + node.Id() + "' in lexer file '" +
                lexerFile->FilePath() + "':\n" + tokenString, node.GetSourcePos(), fileMap);
            if (!rv)
            {
                error = rv.error();
                return;
            }
            error = util::AllocateError(*rv);
            return;
        }
    }
}

void CodeModifierVisitor::Visit(soul_expected::ast::cpp::TypeNameNode& node)
{
    if (processReturnValue)
    {
        std::vector<soul_expected::ast::common::Token*> tokens = tokenMap.GetTokens(node.Name());
        int n = static_cast<int>(tokens.size());
        if (n == 1)
        {
            soul_expected::ast::common::Token* tkn = tokens.front();
            node.SetName(tkn->FullCppId());
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
            std::expected<std::string, int> rv = soul_expected::lexer::MakeMessage("error", "ambiguous reference to token '" + node.Name() + "' in lexer file '" +
                lexerFile->FilePath() + "':\n" + tokenString, node.GetSourcePos(), fileMap);
            if (!rv)
            {
                error = rv.error();
                return;
            }
            error = util::AllocateError(*rv);
            return;
        }
    }
}

void CodeModifierVisitor::Visit(soul_expected::ast::cpp::ReturnStatementNode& node)
{
    if (node.Expr())
    {
        processReturnValue = true;
        node.Expr()->Accept(*this);
        processReturnValue = false;
    }
}

std::expected<bool, int> ModifyCode(soul_expected::ast::cpp::CompoundStatementNode* code, soul_expected::ast::common::TokenMap& tokenMap, 
    soul_expected::ast::slg::LexerFile* lexerFile, soul_expected::lexer::FileMap& fileMap)
{
    CodeModifierVisitor visitor(tokenMap, lexerFile, fileMap);
    code->Accept(visitor);
    if (!visitor)
    {
        return std::unexpected<int>(visitor.Error());
    }
    return std::expected<bool, int>(true);
}

} // namespace soul_expected::slg
