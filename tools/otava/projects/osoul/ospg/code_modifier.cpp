// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.spg.code.modifier;

import util;
import soul.ast.cpp;
import soul.ast.common;
import soul.lexer.error;
import soul.spg.parsing.util;

namespace soul::spg {

class UnexpectedMatcher : public soul::ast::cpp::DefaultVisitor
{
public:
    UnexpectedMatcher();
    bool Matched() const { return matched; }
    void Visit(soul::ast::cpp::InvokeNode& node) override;
    void Visit(soul::ast::cpp::TypeSpecifierNode& node) override;
    void Visit(soul::ast::cpp::TypeNameNode& node) override;
private:
    int invokeLevel;
    bool unexpectedMatched;
    bool intMatched;
    bool matched;
};

UnexpectedMatcher::UnexpectedMatcher() : invokeLevel(0), unexpectedMatched(false), intMatched(false), matched(false)
{
}

void UnexpectedMatcher::Visit(soul::ast::cpp::InvokeNode& node)
{
    ++invokeLevel;
    if (invokeLevel == 1)
    {
        node.Child()->Accept(*this);
        if (unexpectedMatched && intMatched)
        {
            matched = true;
        }
    }
    --invokeLevel;
}

void UnexpectedMatcher::Visit(soul::ast::cpp::TypeSpecifierNode& node)
{
    if (unexpectedMatched && node.Name() == "int")
    {
        intMatched = true;
    }
}

void UnexpectedMatcher::Visit(soul::ast::cpp::TypeNameNode& node)
{
    if (invokeLevel == 1 && node.IsTemplate() && node.Name() == "std::unexpected")
    {
        unexpectedMatched = true;
        if (node.TemplateArgs().size() == 1)
        {
            node.TemplateArgs().front()->Accept(*this);
        }
    }
}

class CodeModifierVisitor : public soul::ast::cpp::DefaultVisitor
{
public:
    CodeModifierVisitor(bool ptrType_, const std::vector<NonterminalInfo>& nonterminalInfos_, soul::ast::cpp::TypeIdNode* returnType_, bool noDebugSupport_,
        const std::string& ruleName_, soul::ast::common::TokenMap* tokenMap_, soul::lexer::FileMap& fileMap_);
    void Visit(soul::ast::cpp::TypeNameNode& node) override;
    void Visit(soul::ast::cpp::IdExprNode& node) override;
    void Visit(soul::ast::cpp::ReturnStatementNode& node) override;
private:
    bool ptrType;
    const std::vector<NonterminalInfo>& nonterminalInfos;
    soul::ast::cpp::TypeIdNode* returnType;
    bool noDebugSupport;
    std::string ruleName;
    soul::ast::common::TokenMap* tokenMap;
    soul::lexer::FileMap& fileMap;
};

CodeModifierVisitor::CodeModifierVisitor(
    bool ptrType_, const std::vector<NonterminalInfo>& nonterminalInfos_, soul::ast::cpp::TypeIdNode* returnType_, bool noDebugSupport_,
    const std::string& ruleName_, soul::ast::common::TokenMap* tokenMap_, soul::lexer::FileMap& fileMap_) :
    ptrType(ptrType_), nonterminalInfos(nonterminalInfos_), returnType(returnType_), noDebugSupport(noDebugSupport_), ruleName(ruleName_), tokenMap(tokenMap_),
    fileMap(fileMap_)
{
}

void CodeModifierVisitor::Visit(soul::ast::cpp::IdExprNode& node)
{
    if (!Valid()) return;
    soul::ast::cpp::DefaultVisitor::Visit(node);
    for (const auto& info : nonterminalInfos)
    {
        if (node.Id() == info.nonterminalParser->InstanceName())
        {
            if (info.ptrType)
            {
                if (!soul::spg::parsing::util::IsGetNode(node))
                {
                    node.SetId(info.nonterminalParser->InstanceName() + ".release()");
                }
            }
            else
            {
                node.SetId(info.nonterminalParser->InstanceName() + "->value");
            }
        }
    }
    if (tokenMap)
    {
        std::vector<soul::ast::common::Token*> tokens = tokenMap->GetTokens(node.Id());
        if (tokens.size() == 1)
        {
            soul::ast::common::Token* token = tokens.front();
            node.SetId(token->FullCppId());
        }
    }
    else
    {
        SetError(util::AllocateError("code modifier has no token map"));
        return;
    }
}

void CodeModifierVisitor::Visit(soul::ast::cpp::TypeNameNode& node)
{
    std::cout << ">modify type name" << "\n";
    if (!Valid()) return;
    soul::ast::cpp::DefaultVisitor::Visit(node);
    for (const auto& info : nonterminalInfos)
    {
        std::cout << ">modify type name, into: " << info.nonterminalParser->Name() << "\n";
        if (node.Name() == info.nonterminalParser->InstanceName())
        {
            if (info.ptrType)
            {
                if (!soul::spg::parsing::util::IsGetNode(node))
                {
                    node.SetName(info.nonterminalParser->InstanceName() + ".release()");
                }
            }
            else
            {
                node.SetName(info.nonterminalParser->InstanceName() + "->value");
            }
        }
        std::cout << "<modify type name, into: " << info.nonterminalParser->Name() << "\n";
    }
    std::cout << ">modify type name, token map" << "\n";
    if (tokenMap)
    {
        std::vector<soul::ast::common::Token*> tokens = tokenMap->GetTokens(node.Name());
        if (tokens.size() == 1)
        {
            soul::ast::common::Token* token = tokens.front();
            node.SetName(token->FullCppId());
        }
        std::cout << "<modify type name, token map" << "\n";
    }
    else
    {
        SetError(util::AllocateError("code modifier has no token map"));
        return;
    }
    std::cout << "<modify type name" << "\n";
}

void CodeModifierVisitor::Visit(soul::ast::cpp::ReturnStatementNode& node)
{
    std::cout << ">modify return" << "\n";
    if (!Valid()) return;
    UnexpectedMatcher unexpectedMatcher;
    node.Accept(unexpectedMatcher);
    if (unexpectedMatcher.Matched()) return;
    soul::ast::SourcePos sourcePos = node.GetSourcePos();
    soul::ast::cpp::DefaultVisitor::Visit(node);
    if (node.Expr())
    {
        std::cout << ">modify return expr" << "\n";
        std::vector<soul::ast::cpp::Node*> matchArgs;
        matchArgs.push_back(new soul::ast::cpp::LiteralNode(sourcePos, "true"));
        if (!ptrType)
        {
            if (!returnType)
            {
                std::expected<std::string, int> rv = soul::lexer::MakeMessage("error", "return type is null", node.GetSourcePos(), fileMap);
                if (!rv)
                {
                    SetError(rv.error());
                    return;
                }
                std::string errorMessage = std::move(*rv);
                SetError(util::AllocateError(errorMessage));
                return;
            }
            soul::ast::cpp::TypeIdNode* typeId = new soul::ast::cpp::TypeIdNode(sourcePos);
            typeId->Add(new soul::ast::cpp::TypeSpecifierNode(sourcePos, "soul::parser::Value<" + returnType->ToString() + ">"));
            soul::ast::cpp::NewNode* newNode = new soul::ast::cpp::NewNode(sourcePos, false);
            newNode->SetTypeId(typeId);
            newNode->BeginAddToInitializer();
            newNode->Add(node.Expr()->Clone());
            newNode->EndAddToInitializer();
            matchArgs.push_back(newNode);
        }
        else
        {
            matchArgs.push_back(node.Expr()->Clone());
        }
        std::cout << ">modify return expr 1" << "\n";
        soul::ast::cpp::InvokeNode* invokeMatch =
            new soul::ast::cpp::InvokeNode(sourcePos, new soul::ast::cpp::IdExprNode(sourcePos, "soul::parser::Match"));
        for (auto* arg : matchArgs)
        {
            invokeMatch->Add(arg);
        }
        std::cout << ">modify return expr 2" << "\n";
        if (!noDebugSupport)
        {
            soul::ast::cpp::StatementNode* parent = static_cast<soul::ast::cpp::StatementNode*>(node.Parent());
            if (parent->IsCompoundStatementNode())
            {
                soul::ast::cpp::CompoundStatementNode* debugBlock = new soul::ast::cpp::CompoundStatementNode(sourcePos);
                soul::ast::cpp::IfdefStatementNode* ifdefStatementNode = new soul::ast::cpp::IfdefStatementNode(sourcePos,
                    new soul::ast::cpp::LiteralNode(sourcePos, "SOUL_PARSER_DEBUG_SUPPORT"));
                debugBlock->Add(ifdefStatementNode);
                soul::ast::cpp::InvokeNode* invokeNode =
                    new soul::ast::cpp::InvokeNode(sourcePos, new soul::ast::cpp::IdExprNode(sourcePos, "soul::lexer::WriteSuccessToLog"));
                invokeNode->Add(new soul::ast::cpp::IdExprNode(sourcePos, "lexer"));
                invokeNode->Add(new soul::ast::cpp::IdExprNode(sourcePos, "parser_debug_match_pos"));
                invokeNode->Add(new soul::ast::cpp::LiteralNode(sourcePos, "\"" + ruleName + "\""));
                soul::ast::cpp::ExpressionStatementNode* expressionStatementNode = new soul::ast::cpp::ExpressionStatementNode(sourcePos, invokeNode);
                soul::ast::cpp::IfStatementNode* ifStatementNode = new soul::ast::cpp::IfStatementNode(sourcePos,
                    new soul::ast::cpp::LiteralNode(sourcePos, "parser_debug_write_to_log"),
                    expressionStatementNode, nullptr);
                debugBlock->Add(ifStatementNode);
                soul::ast::cpp::EndIfStatementNode* endifStatementNode = new soul::ast::cpp::EndIfStatementNode(sourcePos);
                debugBlock->Add(endifStatementNode);
                soul::ast::cpp::StatementNode* returnStmtNode = new soul::ast::cpp::ReturnStatementNode(sourcePos, invokeMatch);
                debugBlock->Add(returnStmtNode);
                parent->Replace(&node, debugBlock);
            }
            else
            {
                std::expected<std::string, int> rv = soul::lexer::MakeMessage("error", "return statement must be inside a compound statement",
                    node.GetSourcePos(), fileMap);
                if (!rv)
                {
                    SetError(rv.error());
                    return;
                }
                std::string errorMessage = std::move(*rv);
                SetError(util::AllocateError(errorMessage));
                return;
            }
        }
        else
        {
            node.SetExpr(invokeMatch);
            return;
        }
    }
    std::cout << "<modify return" << "\n";
}

std::expected<bool, int> ModifyCode(soul::ast::cpp::CompoundStatementNode* code, bool ptrType, const std::string& nonterminalName,
    const std::vector<NonterminalInfo>& nonterminalInfos, soul::ast::cpp::TypeIdNode* returnType, bool noDebugSupport, const std::string& currentRuleName,
    soul::ast::common::TokenMap* tokenMap, soul::lexer::FileMap& fileMap)
{
    std::cout << ">modify" << "\n";
    CodeModifierVisitor visitor(ptrType, nonterminalInfos, returnType, noDebugSupport, currentRuleName, tokenMap, fileMap);
    std::cout << ">modify visitor" << "\n";
    code->Accept(visitor);
    std::cout << "<modify" << "\n";
    if (!visitor) return std::unexpected<int>(visitor.Error());
    return std::expected<bool, int>(true);
}

} // namespace soul::spg
