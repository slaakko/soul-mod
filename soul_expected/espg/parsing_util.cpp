// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul_expected.spg.parsing.util;

namespace soul_expected::spg::parsing::util {

bool IsGetNode(const soul_expected::ast::cpp::IdExprNode& node)
{
    soul_expected::ast::cpp::Node* parent = node.Parent();
    if (parent && parent->Kind() == soul_expected::ast::cpp::NodeKind::memberAccessNode)
    {
        soul_expected::ast::cpp::MemberAccessNode* memberAccessNode = static_cast<soul_expected::ast::cpp::MemberAccessNode*>(parent);
        if (memberAccessNode->Member()->Kind() == soul_expected::ast::cpp::NodeKind::idExprNode)
        {
            soul_expected::ast::cpp::IdExprNode* memberId = static_cast<soul_expected::ast::cpp::IdExprNode*>(memberAccessNode->Member());
            if (memberId->Id() == "get")
            {
                return true;
            }
        }
    }
    return false;
}

bool IsGetNode(const soul_expected::ast::cpp::TypeNameNode& node)
{
    soul_expected::ast::cpp::Node* parent = node.Parent();
    if (parent && parent->Kind() == soul_expected::ast::cpp::NodeKind::memberAccessNode)
    {
        soul_expected::ast::cpp::MemberAccessNode* memberAccessNode = static_cast<soul_expected::ast::cpp::MemberAccessNode*>(parent);
        if (memberAccessNode->Member()->Kind() == soul_expected::ast::cpp::NodeKind::idExprNode)
        {
            soul_expected::ast::cpp::IdExprNode* memberId = static_cast<soul_expected::ast::cpp::IdExprNode*>(memberAccessNode->Member());
            if (memberId->Id() == "get")
            {
                return true;
            }
        }
    }
    return false;
}

bool IsContainedBySwitchStatment(const soul_expected::ast::cpp::IdExprNode& node)
{
    soul_expected::ast::cpp::Node* parent = node.Parent();
    while (parent)
    {
        if (parent->Kind() == soul_expected::ast::cpp::NodeKind::switchStatementNode)
        {
            return true;
        }
        parent = parent->Parent();
    }
    return false;
}

bool IsContainedBySwitchStatment(const soul_expected::ast::cpp::TypeNameNode& node)
{
    soul_expected::ast::cpp::Node* parent = node.Parent();
    while (parent)
    {
        if (parent->Kind() == soul_expected::ast::cpp::NodeKind::switchStatementNode)
        {
            return true;
        }
        parent = parent->Parent();
    }
    return false;
}

class NonterminalCountingVisitor : public soul_expected::ast::cpp::DefaultVisitor
{
public:
    NonterminalCountingVisitor(std::vector<NonterminalInfo>& nonterminalInfos_) : nonterminalInfos(nonterminalInfos_) {}
    void Visit(soul_expected::ast::cpp::TypeNameNode& node);
    void Visit(soul_expected::ast::cpp::IdExprNode& node);
private:
    std::vector<NonterminalInfo>& nonterminalInfos;
};

void NonterminalCountingVisitor::Visit(soul_expected::ast::cpp::TypeNameNode& node)
{
    for (auto& info : nonterminalInfos)
    {
        if (node.Name() == info.nonterminalParser->InstanceName() && !IsGetNode(node) && !IsContainedBySwitchStatment(node))
        {
            ++info.count;
            info.sourcePositions.push_back(node.GetSourcePos());
        }
    }
}

void NonterminalCountingVisitor::Visit(soul_expected::ast::cpp::IdExprNode& node)
{
    for (auto& info : nonterminalInfos)
    {
        if (node.Id() == info.nonterminalParser->InstanceName() && !IsGetNode(node) && !IsContainedBySwitchStatment(node))
        {
            ++info.count;
            info.sourcePositions.push_back(node.GetSourcePos());
        }
    }
}

void CountNonterminals(soul_expected::ast::cpp::CompoundStatementNode* code, std::vector<NonterminalInfo>& nonterminalInfos)
{
    NonterminalCountingVisitor visitor(nonterminalInfos);
    code->Accept(visitor);
}

bool IsListParserNonterminal(const NonterminalInfo& info)
{
    if (info.count != 2)
    {
        return false;
    }
    soul_expected::ast::spg::NonterminalParser* nonterminalParser = info.nonterminalParser;
    soul_expected::ast::spg::Parser* parent = nonterminalParser->Parent();
    while (parent)
    {
        if (parent->IsListParser())
        {
            return true;
        }
        parent = parent->Parent();
    }
    return false;
}

soul_expected::ast::spg::Parser* MakeParserFromStrLiteral(const soul_expected::ast::SourcePos& sourcePos, const std::u32string& str)
{
    return nullptr; // todo
}

} // namespace soul_expected::spg
