// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.slg.code.modifier;

import util;

namespace soul::slg {

class CodeModifierVisitor : public soul::ast::cpp::DefaultVisitor
{
public:
    CodeModifierVisitor(soul::ast::common::TokenMap& tokenMap_, soul::ast::slg::LexerFile* lexerFile_, soul::lexer::FileMap& fileMap_);
    void Visit(soul::ast::cpp::IdExprNode& node) override;
    void Visit(soul::ast::cpp::TypeNameNode& node) override;
    void Visit(soul::ast::cpp::ReturnStatementNode& node) override;
    bool Valid() const { return error == 0; }
    explicit operator bool() const { return Valid(); }
    int Error() const { return error; }
private:
    soul::ast::common::TokenMap& tokenMap;
    soul::ast::slg::LexerFile* lexerFile;
    soul::lexer::FileMap& fileMap;
    bool processReturnValue;
    int error;
};

CodeModifierVisitor::CodeModifierVisitor(soul::ast::common::TokenMap& tokenMap_, soul::ast::slg::LexerFile* lexerFile_,
    soul::lexer::FileMap& fileMap_) :
    tokenMap(tokenMap_), lexerFile(lexerFile_), fileMap(fileMap_), processReturnValue(false), error(0)
{
}

void CodeModifierVisitor::Visit(soul::ast::cpp::IdExprNode& node)
{
    if (processReturnValue)
    {
        std::vector<soul::ast::common::Token*> tokens = tokenMap.GetTokens(node.Id());
        int n = static_cast<int>(tokens.size());
        if (n == 1)
        {
            soul::ast::common::Token* tkn = tokens.front();
            node.SetId(tkn->FullCppId());
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
            std::expected<std::string, int> rv = soul::lexer::MakeMessage("error", "ambiguous reference to token '" + node.Id() + "' in lexer file '" +
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

void CodeModifierVisitor::Visit(soul::ast::cpp::TypeNameNode& node)
{
    if (processReturnValue)
    {
        std::vector<soul::ast::common::Token*> tokens = tokenMap.GetTokens(node.Name());
        int n = static_cast<int>(tokens.size());
        if (n == 1)
        {
            soul::ast::common::Token* tkn = tokens.front();
            node.SetName(tkn->FullCppId());
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
            std::expected<std::string, int> rv = soul::lexer::MakeMessage("error", "ambiguous reference to token '" + node.Name() + "' in lexer file '" +
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

void CodeModifierVisitor::Visit(soul::ast::cpp::ReturnStatementNode& node)
{
    if (node.Expr())
    {
        processReturnValue = true;
        node.Expr()->Accept(*this);
        processReturnValue = false;
    }
}

std::expected<bool, int> ModifyCode(soul::ast::cpp::CompoundStatementNode* code, soul::ast::common::TokenMap& tokenMap,
    soul::ast::slg::LexerFile* lexerFile, soul::lexer::FileMap& fileMap)
{
    CodeModifierVisitor visitor(tokenMap, lexerFile, fileMap);
    code->Accept(visitor);
    if (!visitor)
    {
        return std::unexpected<int>(visitor.Error());
    }
    return std::expected<bool, int>(true);
}

} // namespace soul::slg
