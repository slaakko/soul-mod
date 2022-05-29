// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.spg.code.modifier;

import soul.ast.cpp;

namespace soul::spg {

class CodeModifierVisitor : public soul::ast::cpp::DefaultVisitor
{
public:
    CodeModifierVisitor(bool ptrType_, const std::vector<NonterminalInfo>& nonterminalInfos_, soul::ast::cpp::TypeIdNode* returnType_, bool noDebugSupport_, 
        const std::string& ruleName_);
    void Visit(soul::ast::cpp::IdExprNode& node) override;
    void Visit(soul::ast::cpp::ReturnStatementNode& node) override;
private:
    bool ptrType;
    const std::vector<NonterminalInfo>& nonterminalInfos;
    soul::ast::cpp::TypeIdNode* returnType;
    bool noDebugSupport;
    std::string ruleName;
};

CodeModifierVisitor::CodeModifierVisitor(
    bool ptrType_, const std::vector<NonterminalInfo>& nonterminalInfos_, soul::ast::cpp::TypeIdNode* returnType_, bool noDebugSupport_, const std::string& ruleName_) :
    ptrType(ptrType_), nonterminalInfos(nonterminalInfos_), returnType(returnType_), noDebugSupport(noDebugSupport_), ruleName(ruleName_)
{
}

void CodeModifierVisitor::Visit(soul::ast::cpp::IdExprNode& node)
{
    soul::ast::cpp::Visitor::Visit(node);
    // todo
    for (const auto& info : nonterminalInfos)
    {
        if (node.Id() == info.name)
        {
            if (info.ptrType)
            {
                node.SetId(info.name + ".release()");
            }
            else
            {
                node.SetId(info.name + "->value");
            }
        }
    }
}

void CodeModifierVisitor::Visit(soul::ast::cpp::ReturnStatementNode& node)
{
    soul::ast::cpp::DefaultVisitor::Visit(node);
    if (node.Expr())
    {
        std::vector<soul::ast::cpp::Node*> matchArgs;
        matchArgs.push_back(new soul::ast::cpp::LiteralNode("true"));
        if (!ptrType)
        {
            if (!returnType)
            {
                throw std::runtime_error("return type is null");
            }
            soul::ast::cpp::TypeIdNode* typeId = new soul::ast::cpp::TypeIdNode();
            typeId->Add(new soul::ast::cpp::TypeSpecifierNode("soul::parser::Value<" + returnType->ToString() + ">"));
            soul::ast::cpp::NewNode* newNode = new soul::ast::cpp::NewNode(false);
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
        soul::ast::cpp::InvokeNode* invokeMatch = new soul::ast::cpp::InvokeNode(new soul::ast::cpp::IdExprNode("soul::parser::Match"));
        for (const auto& arg : matchArgs)
        {
            invokeMatch->Add(arg);
        }
        if (!noDebugSupport)
        {
            soul::ast::cpp::StatementNode* parent = static_cast<soul::ast::cpp::StatementNode*>(node.Parent());
            if (parent->IsCompoundStatementNode())
            {
                soul::ast::cpp::CompoundStatementNode* debugBlock = new soul::ast::cpp::CompoundStatementNode();
                soul::ast::cpp::IfdefStatementNode* ifdefStatementNode = new soul::ast::cpp::IfdefStatementNode(new soul::ast::cpp::LiteralNode("SOUL_PARSER_DEBUG_SUPPORT"));
                debugBlock->Add(ifdefStatementNode);
                soul::ast::cpp::InvokeNode* invokeNode = new soul::ast::cpp::InvokeNode(new soul::ast::cpp::IdExprNode("soul::lexer::WriteSuccessToLog"));
                invokeNode->Add(new soul::ast::cpp::IdExprNode("lexer"));
                invokeNode->Add(new soul::ast::cpp::IdExprNode("parser_debug_match_pos"));
                invokeNode->Add(new soul::ast::cpp::LiteralNode("\"" + ruleName + "\""));
                soul::ast::cpp::ExpressionStatementNode* expressionStatementNode = new soul::ast::cpp::ExpressionStatementNode(invokeNode);
                soul::ast::cpp::IfStatementNode* ifStatementNode = new soul::ast::cpp::IfStatementNode(new soul::ast::cpp::LiteralNode("parser_debug_write_to_log"),
                    expressionStatementNode, nullptr);
                debugBlock->Add(ifStatementNode);
                soul::ast::cpp::EndIfStatementNode* endifStatementNode = new soul::ast::cpp::EndIfStatementNode(new soul::ast::cpp::LiteralNode("SOUL_PARSER_DEBUG_SUPPORT"));
                debugBlock->Add(endifStatementNode);
                soul::ast::cpp::StatementNode* returnStmtNode = new soul::ast::cpp::ReturnStatementNode(invokeMatch);
                debugBlock->Add(returnStmtNode);
                parent->Replace(&node, debugBlock);
            }
            else
            {
                throw std::runtime_error("return statement should be inside a compound statement");
            }
        }
        else
        {
            node.SetExpr(invokeMatch);
        }
    }
}

void ModifyCode(soul::ast::cpp::CompoundStatementNode* code, bool ptrType, const std::string& nonterminalName, const std::vector<NonterminalInfo>& nonterminalInfos,
    soul::ast::cpp::TypeIdNode* returnType, bool noDebugSupport, const std::string& currentRuleName)
{
    CodeModifierVisitor visitor(ptrType, nonterminalInfos, returnType, noDebugSupport, currentRuleName);
    code->Accept(visitor);
}

} // namespace soul::spg
