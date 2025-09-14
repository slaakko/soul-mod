// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.spg.linking;

import util;
import soul.lexer.error;

namespace soul::spg {

enum class LinkingStage
{
    makeTokenMap, addParsers, resolveRulesAndTokens
};

class LinkingVisitor : public soul::ast::spg::DefaultVisitor
{
public:
    LinkingVisitor(soul::ast::spg::SpgFile* spgFile_, soul::lexer::FileMap& fileMap_);
    void SetStage(LinkingStage stage_) { stage = stage_; }
    void Visit(soul::ast::spg::TokenParser& parser) override;
    void Visit(soul::ast::spg::NonterminalParser& parser) override;
    void Visit(soul::ast::spg::RuleParser& parser) override;
    void Visit(soul::ast::spg::GrammarParser& parser) override;
    void Visit(soul::ast::spg::ParserFile& parserFile) override;
private:
    soul::ast::spg::SpgFile* spgFile;
    soul::ast::spg::ParserFile* currentParserFile;
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

void LinkingVisitor::Visit(soul::ast::spg::TokenParser& parser)
{
    if (stage == LinkingStage::resolveRulesAndTokens)
    {
        soul::ast::common::TokenMap* tokenMap = currentParserFile->GetTokenMap();
        if (tokenMap)
        {
            std::vector<soul::ast::common::Token*> tokens = tokenMap->GetTokens(parser.TokenName());
            if (!tokens.empty())
            {
                int n = static_cast<int>(tokens.size());
                if (n > 1)
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
                    auto rv = soul::lexer::MakeMessage("error", "ambiguous reference to token '" + parser.TokenName() + "' in parser file '" +
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
                    soul::ast::common::Token* token = tokens.front();
                    parser.SetToken(token);
                }
            }
            else
            {
                auto rv = soul::lexer::MakeMessage("error", "token '" + parser.TokenName() + "' not found from parser file '" +
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

void LinkingVisitor::Visit(soul::ast::spg::NonterminalParser& parser)
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
        soul::ast::spg::RuleParser* rule = currentParser->GetRule(parser.RuleName());
        if (!rule)
        {
            std::expected<std::string, int> rv = soul::lexer::MakeMessage("error", "rule '" + parser.RuleName() + "' not found from parser '" +
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
            std::expected<std::string, int> rv = soul::lexer::MakeMessage("error",
                "Rule '" + rule->Name() + "' takes " + std::to_string(rule->Params().size()) + " parameters (" +
                std::to_string(argCount) + " arguments supplied). Detected in parser '" + currentParser->Name() + "' rule '" + currentRule->Name() + "'.",
                parser.GetSourcePos(), fileMap);
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
            std::string errorMessage = std::move(*rv);
            rv = soul::lexer::MakeMessage("info", "see reference", rule->GetSourcePos(), fileMap);
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

void LinkingVisitor::Visit(soul::ast::spg::RuleParser& parser)
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

void LinkingVisitor::Visit(soul::ast::spg::GrammarParser& parser)
{
    if (!Valid()) return;
    if (parser.Lexers().empty())
    {
        std::expected<std::string, int> rv = soul::lexer::MakeMessage(
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
        std::string fullGrammarName = parser.GetParserFile()->GetExportModule()->ModuleName();
        fullGrammarName.append(1, '.').append(parser.Name());
        std::int32_t grammarId = std::hash<std::string>()(fullGrammarName) & 0x7FFFFFFF;
        parser.SetId(grammarId);
    }
    if (stage == LinkingStage::addParsers)
    {
        if (!spgFile->AddParser(&parser))
        {
            std::expected<std::string, int> rv = soul::lexer::MakeMessage("error", "Parser '" + parser.Name() + "' name not unique. Detected in SPG file '" +
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
            std::vector<std::string> components = util::Split(usng.fullName, '.');
            if (components.size() != 2)
            {
                std::expected<std::string, int> rv = soul::lexer::MakeMessage("error", "invalid using '" + usng.fullName + "' in parser '" + parser.Name() +
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
            soul::ast::spg::GrammarParser* targetParser = spgFile->GetParser(parserName);
            if (!targetParser)
            {
                std::expected<std::string, int> rv = soul::lexer::MakeMessage("error", "parser '" + parserName + "' not found", usng.sourcePos, fileMap);
                if (!rv)
                {
                    SetError(rv.error());
                    return;
                }
                std::string errorMessage = std::move(*rv);
                SetError(util::AllocateError(std::move(errorMessage)));
                return;
            }
            soul::ast::spg::RuleParser* rule = targetParser->GetRule(ruleName);
            if (!rule)
            {
                std::expected<std::string, int> rv = soul::lexer::MakeMessage("error", "rule '" + ruleName + "' not found from parser '" +
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
                std::expected<std::string, int> rv = soul::lexer::MakeMessage("error", "rule '" + ruleName + "' already added to parser '" + parser.Name() + "'",
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

void LinkingVisitor::Visit(soul::ast::spg::ParserFile& parserFile)
{
    if (!Valid()) return;
    if (!parserFile.GetExportModule())
    {
        SetError(util::AllocateError("export module declaration missing from parser file '" + parserFile.FilePath() + "'"));
        return;
    }
    currentParserFile = &parserFile;
    if (stage == LinkingStage::makeTokenMap)
    {
        std::cout << ">make token map" << "\n";
        int n = static_cast<int>(parserFile.Imports().size());
        for (int i = 0; i < n; ++i)
        {
            soul::ast::common::Import* import = parserFile.Imports()[i].get();
            soul::ast::common::TokenCollection* tokenCollection = spgFile->GetTokenCollection(import->ModuleName());
            if (tokenCollection)
            {
                for (const auto& token : tokenCollection->Tokens())
                {
                    soul::ast::common::TokenMap* tokenMap = parserFile.GetTokenMap();
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

std::expected<bool, int> Link(soul::ast::spg::SpgFile* spgFile, bool verbose, soul::lexer::FileMap& fileMap)
{
    if (verbose)
    {
        std::cout << "linking..." << "\n";
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

} // namespace soul::spg
