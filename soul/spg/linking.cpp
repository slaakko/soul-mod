// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.spg.linking;

import util;
import soul.lexer.error;

namespace soul::spg {

enum class LinkingStage
{
    addParsers, resolveRules
};

class LinkingVisitor : public soul::ast::spg::DefaultVisitor
{
public:
    LinkingVisitor(soul::ast::spg::SpgFile* spgFile_, soul::lexer::FileMap& fileMap_);
    void SetStage(LinkingStage stage_) { stage = stage_; }
    void Visit(soul::ast::spg::NonterminalParser& parser) override;
    void Visit(soul::ast::spg::RuleParser& parser) override;
    void Visit(soul::ast::spg::GrammarParser& parser) override;
    void Visit(soul::ast::spg::ParserFile& parserFile) override;
private:
    soul::ast::spg::SpgFile* spgFile;
    soul::ast::spg::GrammarParser* currentParser;
    soul::ast::spg::RuleParser* currentRule;
    LinkingStage stage;
    soul::lexer::FileMap& fileMap;
};

LinkingVisitor::LinkingVisitor(soul::ast::spg::SpgFile* spgFile_, soul::lexer::FileMap& fileMap_) : 
    spgFile(spgFile_), currentParser(nullptr), currentRule(nullptr), stage(LinkingStage::addParsers), 
    fileMap(fileMap_)
{
}

void LinkingVisitor::Visit(soul::ast::spg::NonterminalParser& parser)
{
    if (stage == LinkingStage::resolveRules)
    {
        if (!currentRule)
        {
            throw std::runtime_error("current rule not set");
        }
        currentRule->AddNonterminal(&parser);
        if (!currentParser)
        {
            throw std::runtime_error("current parser not set");
        }
        soul::ast::spg::RuleParser* rule = currentParser->GetRule(parser.RuleName());
        if (!rule)
        {
            std::string errorMessage = soul::lexer::MakeMessage("error", "rule '" + parser.RuleName() + "' not found from parser '" + currentParser->Name() + "'",
                parser.GetSourcePos(), fileMap);
            throw std::runtime_error(errorMessage);
        }
        parser.SetRule(rule);
        int argCount = 0;
        if (parser.Arguments())
        {
            argCount = parser.Arguments()->Count();
        }
        if (rule->Params().size() != argCount)
        {
            std::string errorMessage = soul::lexer::MakeMessage("error",
                "Rule '" + rule->Name() + "' takes " + std::to_string(rule->Params().size()) + " parameters (" +
                std::to_string(argCount) + " arguments supplied). Detected in parser '" + currentParser->Name() + "' rule '" + currentRule->Name() + "'.",
                parser.GetSourcePos(), fileMap);
            errorMessage.append("\n:").append(soul::lexer::MakeMessage("info", "see reference", rule->GetSourcePos(), fileMap));
            throw std::runtime_error(errorMessage);
        }
    }
    Visitor::Visit(parser);
}

void LinkingVisitor::Visit(soul::ast::spg::RuleParser& parser)
{
    currentRule = &parser;
    if (stage == LinkingStage::resolveRules)
    {
        spgFile->AddRule(&parser);
    }
    DefaultVisitor::Visit(parser);
}

void LinkingVisitor::Visit(soul::ast::spg::GrammarParser& parser)
{
    currentParser = &parser;
    if (stage == LinkingStage::addParsers)
    {
        spgFile->AddParser(&parser);
    }
    else if (stage == LinkingStage::resolveRules)
    {
        for (const auto& usng : parser.Usings())
        {
            std::vector<std::string> components = util::Split(usng.parserRuleId, '.');
            if (components.size() != 2)
            {
                std::string errorMessage = soul::lexer::MakeMessage("error", "invalid using '" + usng.parserRuleId + "' in parser '" + parser.Name() + 
                    "': format 'PARSER.RULE' expected",
                    usng.sourcePos, fileMap);
                throw std::runtime_error(errorMessage);
            }
            const std::string& parserName = components[0];
            const std::string& ruleName = components[1];
            soul::ast::spg::GrammarParser* targetParser = spgFile->GetParser(parserName);
            if (!targetParser)
            {
                std::string errorMessage = soul::lexer::MakeMessage("error", "parser '" + parserName + "' not found", usng.sourcePos, fileMap);
                throw std::runtime_error(errorMessage);
            }
            soul::ast::spg::RuleParser* rule = targetParser->GetRule(ruleName);
            if (!rule)
            {
                std::string errorMessage = soul::lexer::MakeMessage("error", "rule '" + ruleName + "' not found from parser '" + targetParser->Name() + "'",
                    usng.sourcePos, fileMap);
                throw std::runtime_error(errorMessage);
            }
            if (!parser.MapRule(rule))
            {
                std::string errorMessage = soul::lexer::MakeMessage("error", "rule '" + ruleName + "' already added to parser '" + parser.Name() + "'", 
                    usng.sourcePos, fileMap);
                throw std::runtime_error(errorMessage);
            }
        }
    }
    DefaultVisitor::Visit(parser);
}

void LinkingVisitor::Visit(soul::ast::spg::ParserFile& parserFile)
{
    if (!parserFile.ExportModule())
    {
        throw std::runtime_error("export module declaration missing from parser file '" + parserFile.FilePath() + "'");
    }
    DefaultVisitor::Visit(parserFile);
}

void Link(soul::ast::spg::SpgFile* spgFile, bool verbose, soul::lexer::FileMap& fileMap)
{
    if (verbose)
    {
        std::cout << "linking..." << std::endl;
    }
    LinkingVisitor visitor(spgFile, fileMap);
    visitor.SetStage(LinkingStage::addParsers);
    spgFile->Accept(visitor);
    visitor.SetStage(LinkingStage::resolveRules);
    spgFile->Accept(visitor);
}

} // namespace soul::spg
