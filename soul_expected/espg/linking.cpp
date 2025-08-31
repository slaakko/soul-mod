// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul_expected.spg.linking;

import util_expected;
import soul_expected.lexer.error;

namespace soul_expected::spg {

enum class LinkingStage
{
    makeTokenMap, addParsers, resolveRulesAndTokens
};

class LinkingVisitor : public soul_expected::ast::spg::DefaultVisitor
{
public:
    LinkingVisitor(soul_expected::ast::spg::SpgFile* spgFile_, soul_expected::lexer::FileMap& fileMap_);
    void SetStage(LinkingStage stage_) { stage = stage_; }
    void Visit(soul_expected::ast::spg::TokenParser& parser) override;
    void Visit(soul_expected::ast::spg::NonterminalParser& parser) override;
    void Visit(soul_expected::ast::spg::RuleParser& parser) override;
    void Visit(soul_expected::ast::spg::GrammarParser& parser) override;
    void Visit(soul_expected::ast::spg::ParserFile& parserFile) override;
private:
    soul_expected::ast::spg::SpgFile* spgFile;
    soul_expected::ast::spg::ParserFile* currentParserFile;
    soul_expected::ast::spg::GrammarParser* currentParser;
    soul_expected::ast::spg::RuleParser* currentRule;
    LinkingStage stage;
    soul_expected::lexer::FileMap& fileMap;
};

LinkingVisitor::LinkingVisitor(soul_expected::ast::spg::SpgFile* spgFile_, soul_expected::lexer::FileMap& fileMap_) :
    spgFile(spgFile_), currentParser(nullptr), currentRule(nullptr), stage(LinkingStage::addParsers),
    fileMap(fileMap_)
{
}

void LinkingVisitor::Visit(soul_expected::ast::spg::TokenParser& parser)
{
    if (stage == LinkingStage::resolveRulesAndTokens)
    {
        soul_expected::ast::common::TokenMap* tokenMap = currentParserFile->GetTokenMap();
        if (tokenMap)
        {
            std::vector<soul_expected::ast::common::Token*> tokens = tokenMap->GetTokens(parser.TokenName());
            if (!tokens.empty())
            {
                int n = static_cast<int>(tokens.size());
                if (n > 1)
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
                    auto rv = soul_expected::lexer::MakeMessage("error", "ambiguous reference to token '" + parser.TokenName() + "' in parser file '" +
                        currentParserFile->FilePath() + "':\n" + tokenString, parser.GetSourcePos(), fileMap);
                    if (!rv)
                    {
                        SetError(rv.error());
                        return;
                    }
                    std::string errorMessage = *rv;
                    SetError(util::AllocateError(errorMessage));
                    return;
                }
                else
                {
                    soul_expected::ast::common::Token* token = tokens.front();
                    parser.SetToken(token);
                }
            }
            else
            {
                auto rv = soul_expected::lexer::MakeMessage("error", "token '" + parser.TokenName() + "' not found from parser file '" + 
                    currentParserFile->FilePath() + "'", parser.GetSourcePos(), fileMap);
                if (!rv)
                {
                    SetError(rv.error());
                    return;
                }
                std::string errorMessage = *rv;
                SetError(util::AllocateError(errorMessage));
                return;
            }
        }
        else
        {
            SetError(util::AllocateError("token map not found"));
            return;
        }
    }

}

void LinkingVisitor::Visit(soul_expected::ast::spg::NonterminalParser& parser)
{
    if (!Valid()) return;
    if (stage == LinkingStage::resolveRulesAndTokens)
    {
        if (!currentRule)
        {
            SetError(util::AllocateError("current rule not set"));
            return;
        }
        currentRule->AddNonterminal(&parser);
        if (!currentParser)
        {
            SetError(util::AllocateError("current parser not set"));
            return;
        }
        soul_expected::ast::spg::RuleParser* rule = currentParser->GetRule(parser.RuleName());
        if (!rule)
        {
            std::expected<std::string, int> rv = soul_expected::lexer::MakeMessage("error", "rule '" + parser.RuleName() + "' not found from parser '" + 
                currentParser->Name() + "'", parser.GetSourcePos(), fileMap);
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
            std::string errorMessage = std::move(*rv);
            SetError(util::AllocateError(errorMessage));
            return;
        }
        parser.SetRule(rule);
        int argCount = 0;
        if (parser.Arguments())
        {
            argCount = parser.Arguments()->Count();
        }
        if (rule->Params().size() != argCount)
        {
            std::expected<std::string, int> rv = soul_expected::lexer::MakeMessage("error",
                "Rule '" + rule->Name() + "' takes " + std::to_string(rule->Params().size()) + " parameters (" +
                std::to_string(argCount) + " arguments supplied). Detected in parser '" + currentParser->Name() + "' rule '" + currentRule->Name() + "'.",
                parser.GetSourcePos(), fileMap);
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
            std::string errorMessage = std::move(*rv);
            rv = soul_expected::lexer::MakeMessage("info", "see reference", rule->GetSourcePos(), fileMap);
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
            errorMessage.append("\n:").append(std::move(*rv));
            SetError(util::AllocateError(errorMessage));
            return;
        }
    }
    Visitor::Visit(parser);
}

void LinkingVisitor::Visit(soul_expected::ast::spg::RuleParser& parser)
{
    if (!Valid()) return;
    currentRule = &parser;
    if (stage == LinkingStage::resolveRulesAndTokens)
    {
        std::int64_t ruleId = (std::int64_t(parser.Grammar()->Id()) << 32) | std::int64_t(parser.Index() + 1);
        parser.SetId(ruleId);
        spgFile->AddRule(&parser);
    }
    DefaultVisitor::Visit(parser);
}

void LinkingVisitor::Visit(soul_expected::ast::spg::GrammarParser& parser)
{
    if (!Valid()) return;
    if (parser.Lexers().empty())
    {
        std::expected<std::string, int> rv = soul_expected::lexer::MakeMessage(
            "error", "Parser '" + parser.Name() + "' has no lexer statements.", parser.GetSourcePos(), fileMap);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        std::string errorMessage = std::move(*rv);
        SetError(util::AllocateError(std::move(errorMessage)));
        return;
    }
    currentParser = &parser;
    if (parser.Id() == -1)
    {
        std::string fullGrammarName = parser.GetParserFile()->ExportModule()->ModuleName();
        fullGrammarName.append(1, '.').append(parser.Name());
        std::int32_t grammarId = std::hash<std::string>()(fullGrammarName) & 0x7FFFFFFF;
        parser.SetId(grammarId);
    }
    if (stage == LinkingStage::addParsers)
    {
        if (!spgFile->AddParser(&parser))
        {
            std::expected<std::string, int> rv = soul_expected::lexer::MakeMessage("error", "Parser '" + parser.Name() + "' name not unique. Detected in SPG file '" + 
                spgFile->FilePath() + "'", parser.GetSourcePos(), fileMap);
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
            std::string errorMessage = std::move(*rv);
            SetError(util::AllocateError(std::move(errorMessage)));
            return;
        }
    }
    else if (stage == LinkingStage::resolveRulesAndTokens)
    {
        for (const auto& usng : parser.Usings())
        {
            std::vector<std::string> components = util::Split(usng.parserRuleId, '.');
            if (components.size() != 2)
            {
                std::expected<std::string, int> rv = soul_expected::lexer::MakeMessage("error", "invalid using '" + usng.parserRuleId + "' in parser '" + parser.Name() +
                    "': format 'PARSER.RULE' expected", usng.sourcePos, fileMap);
                if (!rv)
                {
                    SetError(rv.error());
                    return;
                }
                std::string errorMessage = std::move(*rv);
                SetError(util::AllocateError(std::move(errorMessage)));
                return;
            }
            const std::string& parserName = components[0];
            const std::string& ruleName = components[1];
            soul_expected::ast::spg::GrammarParser* targetParser = spgFile->GetParser(parserName);
            if (!targetParser)
            {
                std::expected<std::string, int> rv = soul_expected::lexer::MakeMessage("error", "parser '" + parserName + "' not found", usng.sourcePos, fileMap);
                if (!rv)
                {
                    SetError(rv.error());
                    return;
                }
                std::string errorMessage = std::move(*rv);
                SetError(util::AllocateError(std::move(errorMessage)));
                return;
            }
            soul_expected::ast::spg::RuleParser* rule = targetParser->GetRule(ruleName);
            if (!rule)
            {
                std::expected<std::string, int> rv = soul_expected::lexer::MakeMessage("error", "rule '" + ruleName + "' not found from parser '" + 
                    targetParser->Name() + "'", usng.sourcePos, fileMap);
                if (!rv)
                {
                    SetError(rv.error());
                    return;
                }
                std::string errorMessage = std::move(*rv);
                SetError(util::AllocateError(std::move(errorMessage)));
                return;
            }
            if (!parser.MapRule(rule))
            {
                std::expected<std::string, int> rv = soul_expected::lexer::MakeMessage("error", "rule '" + ruleName + "' already added to parser '" + parser.Name() + "'",
                    usng.sourcePos, fileMap);
                if (!rv)
                {
                    SetError(rv.error());
                    return;
                }
                std::string errorMessage = std::move(*rv);
                SetError(util::AllocateError(std::move(errorMessage)));
                return;
            }
        }
    }
    DefaultVisitor::Visit(parser);
}

void LinkingVisitor::Visit(soul_expected::ast::spg::ParserFile& parserFile)
{
    if (!Valid()) return;
    if (!parserFile.ExportModule())
    {
        SetError(util::AllocateError("export module declaration missing from parser file '" + parserFile.FilePath() + "'"));
        return;
    }
    currentParserFile = &parserFile;
    if (stage == LinkingStage::makeTokenMap)
    {
        int n = static_cast<int>(parserFile.Imports().size());
        for (int i = 0; i < n; ++i)
        {
            soul_expected::ast::common::Import* import = parserFile.Imports()[i].get();
            soul_expected::ast::common::TokenCollection* tokenCollection = spgFile->GetTokenCollection(import->ModuleName());
            if (tokenCollection)
            {
                for (const auto& token : tokenCollection->Tokens())
                {
                    soul_expected::ast::common::TokenMap* tokenMap = parserFile.GetTokenMap();
                    if (tokenMap)
                    {
                        auto rv = tokenMap->AddToken(token.get());
                        if (!rv)
                        {
                            int error = rv.error();
                            SetError(util::AllocateError(util::GetErrorMessage(error) + ": detected in parser file '" + parserFile.FilePath() + "'"));
                            return;
                        }
                    }
                    else
                    {
                        SetError(util::AllocateError("token map not found, detected in parser file '" + parserFile.FilePath() + "'"));
                        return;
                    }
                }
            }
        }
    }
    else
    {
        DefaultVisitor::Visit(parserFile);
    }
}

std::expected<bool, int> Link(soul_expected::ast::spg::SpgFile* spgFile, bool verbose, soul_expected::lexer::FileMap& fileMap)
{
    if (verbose)
    {
        std::cout << "linking..." << std::endl;
    }
    LinkingVisitor visitor(spgFile, fileMap);
    visitor.SetStage(LinkingStage::makeTokenMap);
    spgFile->Accept(visitor);
    if (!visitor) return std::unexpected<int>(visitor.Error());
    visitor.SetStage(LinkingStage::addParsers);
    spgFile->Accept(visitor);
    if (!visitor) return std::unexpected<int>(visitor.Error());
    visitor.SetStage(LinkingStage::resolveRulesAndTokens);
    spgFile->Accept(visitor);
    if (!visitor) return std::unexpected<int>(visitor.Error());
    return std::expected<bool, int>(true);
}

} // namespace soul_expected::spg
