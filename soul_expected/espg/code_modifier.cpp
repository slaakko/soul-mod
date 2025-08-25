// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul_expected.spg.code.modifier;

import util_expected;
import soul_expected.ast.cpp;
import soul_expected.ast.common;
import soul_expected.lexer.error;
import soul_expected.spg.parsing.util;

namespace soul_expected::spg {

class UnexpectedMatcher : public soul_expected::ast::cpp::DefaultVisitor
{
public:
    UnexpectedMatcher();
    bool Matched() const { return matched; }
    void Visit(soul_expected::ast::cpp::InvokeNode& node) override;
    void Visit(soul_expected::ast::cpp::TypeSpecifierNode& node) override;
    void Visit(soul_expected::ast::cpp::TypeNameNode& node) override;
private:
    int invokeLevel;
    bool unexpectedMatched;
    bool intMatched;
    bool matched;
};

UnexpectedMatcher::UnexpectedMatcher() : invokeLevel(0), unexpectedMatched(false), intMatched(false), matched(false)
{
}

void UnexpectedMatcher::Visit(soul_expected::ast::cpp::InvokeNode& node)
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

void UnexpectedMatcher::Visit(soul_expected::ast::cpp::TypeSpecifierNode& node)
{
    if (unexpectedMatched && node.Name() == "int")
    {
        intMatched = true;
    }
}

void UnexpectedMatcher::Visit(soul_expected::ast::cpp::TypeNameNode& node)
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

class CodeModifierVisitor : public soul_expected::ast::cpp::DefaultVisitor
{
public:
    CodeModifierVisitor(bool ptrType_, const std::vector<NonterminalInfo>& nonterminalInfos_, soul_expected::ast::cpp::TypeIdNode* returnType_, bool noDebugSupport_,
        const std::string& ruleName_, soul_expected::ast::common::TokenMap* tokenMap, soul_expected::lexer::FileMap& fileMap_);
    void Visit(soul_expected::ast::cpp::TypeNameNode& node) override;
    void Visit(soul_expected::ast::cpp::IdExprNode& node) override;
    void Visit(soul_expected::ast::cpp::ReturnStatementNode& node) override;
private:
    bool ptrType;
    const std::vector<NonterminalInfo>& nonterminalInfos;
    soul_expected::ast::cpp::TypeIdNode* returnType;
    bool noDebugSupport;
    std::string ruleName;
    soul_expected::ast::common::TokenMap* tokenMap;
    soul_expected::lexer::FileMap& fileMap;
};

CodeModifierVisitor::CodeModifierVisitor(
    bool ptrType_, const std::vector<NonterminalInfo>& nonterminalInfos_, soul_expected::ast::cpp::TypeIdNode* returnType_, bool noDebugSupport_, 
    const std::string& ruleName_, soul_expected::ast::common::TokenMap* tokenMap_, soul_expected::lexer::FileMap& fileMap_) :
    ptrType(ptrType_), nonterminalInfos(nonterminalInfos_), returnType(returnType_), noDebugSupport(noDebugSupport_), ruleName(ruleName_), tokenMap(tokenMap_), 
    fileMap(fileMap_)
{
}

void CodeModifierVisitor::Visit(soul_expected::ast::cpp::IdExprNode& node)
{
    if (!Valid()) return;
    soul_expected::ast::cpp::Visitor::Visit(node);
    for (const auto& info : nonterminalInfos)
    {
        if (node.Id() == info.nonterminalParser->InstanceName())
        {
            if (info.ptrType)
            {
                if (!soul_expected::spg::parsing::util::IsGetNode(node))
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
    std::vector<soul_expected::ast::common::Token*> tokens = tokenMap->GetTokens(node.Id());
    if (tokens.size() == 1)
    {
        soul_expected::ast::common::Token* token = tokens.front();
        node.SetId(token->FullCppId());
    }
}

void CodeModifierVisitor::Visit(soul_expected::ast::cpp::TypeNameNode& node)
{
    if (!Valid()) return;
    soul_expected::ast::cpp::Visitor::Visit(node);
    for (const auto& info : nonterminalInfos)
    {
        if (node.Name() == info.nonterminalParser->InstanceName())
        {
            if (info.ptrType)
            {
                if (!soul_expected::spg::parsing::util::IsGetNode(node))
                {
                    node.SetName(info.nonterminalParser->InstanceName() + ".release()");
                }
            }
            else
            {
                node.SetName(info.nonterminalParser->InstanceName() + "->value");
            }
        }
    }
    std::vector<soul_expected::ast::common::Token*> tokens = tokenMap->GetTokens(node.Name());
    if (tokens.size() == 1)
    {
        soul_expected::ast::common::Token* token = tokens.front();
        node.SetName(token->FullCppId());
    }
}

void CodeModifierVisitor::Visit(soul_expected::ast::cpp::ReturnStatementNode& node)
{
    if (!Valid()) return;
    UnexpectedMatcher unexpectedMatcher;
    node.Accept(unexpectedMatcher);
    if (unexpectedMatcher.Matched()) return;
    soul_expected::ast::SourcePos sourcePos = node.GetSourcePos();
    soul_expected::ast::cpp::DefaultVisitor::Visit(node);
    if (node.Expr())
    {
        std::vector<soul_expected::ast::cpp::Node*> matchArgs;
        matchArgs.push_back(new soul_expected::ast::cpp::LiteralNode(sourcePos, "true"));
        if (!ptrType)
        {
            if (!returnType)
            {
                std::expected<std::string, int> rv = soul_expected::lexer::MakeMessage("error", "return type is null", node.GetSourcePos(), fileMap);
                if (!rv)
                {
                    SetError(rv.error());
                    return;
                }
                std::string errorMessage = std::move(*rv);
                SetError(util::AllocateError(errorMessage));
                return;
            }
            soul_expected::ast::cpp::TypeIdNode* typeId = new soul_expected::ast::cpp::TypeIdNode(sourcePos);
            typeId->Add(new soul_expected::ast::cpp::TypeSpecifierNode(sourcePos, "soul_expected::parser::Value<" + returnType->ToString() + ">"));
            soul_expected::ast::cpp::NewNode* newNode = new soul_expected::ast::cpp::NewNode(sourcePos, false);
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
        soul_expected::ast::cpp::InvokeNode* invokeMatch = 
            new soul_expected::ast::cpp::InvokeNode(sourcePos, new soul_expected::ast::cpp::IdExprNode(sourcePos, "soul_expected::parser::Match"));
        for (auto arg : matchArgs)
        {
            invokeMatch->Add(arg);
        }
        if (!noDebugSupport)
        {
            soul_expected::ast::cpp::StatementNode* parent = static_cast<soul_expected::ast::cpp::StatementNode*>(node.Parent());
            if (parent->IsCompoundStatementNode())
            {
                soul_expected::ast::cpp::CompoundStatementNode* debugBlock = new soul_expected::ast::cpp::CompoundStatementNode(sourcePos);
                soul_expected::ast::cpp::IfdefStatementNode* ifdefStatementNode = new soul_expected::ast::cpp::IfdefStatementNode(sourcePos,
                    new soul_expected::ast::cpp::LiteralNode(sourcePos, "SOUL_PARSER_DEBUG_SUPPORT"));
                debugBlock->Add(ifdefStatementNode);
                soul_expected::ast::cpp::InvokeNode* invokeNode = 
                    new soul_expected::ast::cpp::InvokeNode(sourcePos, new soul_expected::ast::cpp::IdExprNode(sourcePos, "soul_expected::lexer::WriteSuccessToLog"));
                invokeNode->Add(new soul_expected::ast::cpp::IdExprNode(sourcePos, "lexer"));
                invokeNode->Add(new soul_expected::ast::cpp::IdExprNode(sourcePos, "parser_debug_match_pos"));
                invokeNode->Add(new soul_expected::ast::cpp::LiteralNode(sourcePos, "\"" + ruleName + "\""));
                soul_expected::ast::cpp::ExpressionStatementNode* expressionStatementNode = new soul_expected::ast::cpp::ExpressionStatementNode(sourcePos, invokeNode);
                soul_expected::ast::cpp::IfStatementNode* ifStatementNode = new soul_expected::ast::cpp::IfStatementNode(sourcePos,
                    new soul_expected::ast::cpp::LiteralNode(sourcePos, "parser_debug_write_to_log"),
                    expressionStatementNode, nullptr);
                debugBlock->Add(ifStatementNode);
                soul_expected::ast::cpp::EndIfStatementNode* endifStatementNode = new soul_expected::ast::cpp::EndIfStatementNode(sourcePos);
                debugBlock->Add(endifStatementNode);
                soul_expected::ast::cpp::StatementNode* returnStmtNode = new soul_expected::ast::cpp::ReturnStatementNode(sourcePos, invokeMatch);
                debugBlock->Add(returnStmtNode);
                parent->Replace(&node, debugBlock);
            }
            else
            {
                std::expected<std::string, int> rv = soul_expected::lexer::MakeMessage("error", "return statement must be inside a compound statement",
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
}

std::expected<bool, int> ModifyCode(soul_expected::ast::cpp::CompoundStatementNode* code, bool ptrType, const std::string& nonterminalName, 
    const std::vector<NonterminalInfo>& nonterminalInfos, soul_expected::ast::cpp::TypeIdNode* returnType, bool noDebugSupport, const std::string& currentRuleName, 
    soul_expected::ast::common::TokenMap* tokenMap, soul_expected::lexer::FileMap& fileMap)
{
    CodeModifierVisitor visitor(ptrType, nonterminalInfos, returnType, noDebugSupport, currentRuleName, tokenMap, fileMap);
    code->Accept(visitor);
    if (!visitor) return std::unexpected<int>(visitor.Error());
    return std::expected<bool, int>(true);
}

} // namespace soul_expected::spg
