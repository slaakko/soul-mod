// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul_expected.spg.optimizer;

import soul_expected.spg.first.set.computer;
import soul_expected.spg.xml.printer;
import soul_expected.spg.linking;

namespace soul_expected::spg {

class OptimizationFlagsSetter : public soul_expected::ast::spg::DefaultVisitor
{
public:
    OptimizationFlagsSetter();
    int Count() const { return count; }
    void Visit(soul_expected::ast::spg::ChoiceParser& parser) override;
private:
    int count;
};

OptimizationFlagsSetter::OptimizationFlagsSetter() : count(0)
{
}

void OptimizationFlagsSetter::Visit(soul_expected::ast::spg::ChoiceParser& parser)
{
    soul_expected::ast::spg::DefaultVisitor::Visit(parser);
    parser.SetOptimizationFlag(count);
}

class Optimizer : public soul_expected::ast::spg::DefaultVisitor
{
public:
    Optimizer(soul_expected::ast::spg::SwitchParser* switchParser_);
    soul_expected::ast::spg::Parser* GetOptimizedParser() { return optimizedParser; }
    soul_expected::ast::spg::SpgFile* GetOptimizedSpgFile() const { return optimizedSpgFile; }
    void Visit(soul_expected::ast::spg::ChoiceParser& parser) override;
    void Visit(soul_expected::ast::spg::SequenceParser& parser) override;
    void Visit(soul_expected::ast::spg::DifferenceParser& parser) override;
    void Visit(soul_expected::ast::spg::ListParser& parser) override;
    void Visit(soul_expected::ast::spg::LookaheadParser& parser) override;
    void Visit(soul_expected::ast::spg::KleeneParser& parser) override;
    void Visit(soul_expected::ast::spg::PositiveParser& parser) override;
    void Visit(soul_expected::ast::spg::OptionalParser& parser) override;
    void Visit(soul_expected::ast::spg::ExpectationParser& parser) override;
    void Visit(soul_expected::ast::spg::ActionParser& parser) override;
    void Visit(soul_expected::ast::spg::NonterminalParser& parser) override;
    void Visit(soul_expected::ast::spg::EmptyParser& parser) override;
    void Visit(soul_expected::ast::spg::AnyParser& parser) override;
    void Visit(soul_expected::ast::spg::TokenParser& parser) override;
    void Visit(soul_expected::ast::spg::GroupParser& parser) override;
    void Visit(soul_expected::ast::spg::RuleParser& parser) override;
    void Visit(soul_expected::ast::spg::GrammarParser& parser) override;
    void Visit(soul_expected::ast::spg::ParserFile& parserFile) override;
    void Visit(soul_expected::ast::spg::SpgFile& spgFile) override;
private:
    soul_expected::ast::spg::SpgFile* optimizedSpgFile;
    soul_expected::ast::spg::ParserFile* optimizedParserFile;
    soul_expected::ast::spg::GrammarParser* optimizedGrammar;
    soul_expected::ast::spg::RuleParser* optimizedRule;
    soul_expected::ast::spg::Parser* optimizedParser;
    soul_expected::ast::spg::SwitchParser* switchParser;
};

std::expected<soul_expected::ast::spg::Parser*, int> GenerateOptimizedParser(soul_expected::ast::spg::Parser* from, soul_expected::ast::spg::SwitchParser* switchParser)
{
    Optimizer optimizer(switchParser);
    from->Accept(optimizer);
    if (!optimizer) return std::unexpected<int>(optimizer.Error());
    return optimizer.GetOptimizedParser();
}

std::expected<soul_expected::ast::spg::SwitchParser*, int> GenerateSwitch(soul_expected::ast::spg::ChoiceParser& fromChoice)
{
    soul_expected::ast::spg::SwitchParser* switchParser = new soul_expected::ast::spg::SwitchParser(fromChoice.GetSourcePos());
    std::expected<soul_expected::ast::spg::Parser*, int> leftrv = GenerateOptimizedParser(fromChoice.Left(), switchParser);
    if (!leftrv) return std::unexpected<int>(leftrv.error());
    soul_expected::ast::spg::Parser* left = *leftrv;
    if (left)
    {
        switchParser->AddCaseParser(new soul_expected::ast::spg::CaseParser(fromChoice.GetSourcePos(), left));
    }
    std::expected<soul_expected::ast::spg::Parser*, int> rightrv = GenerateOptimizedParser(fromChoice.Right(), switchParser);
    if (!rightrv) return std::unexpected<int>(rightrv.error());
    soul_expected::ast::spg::Parser* right = *rightrv;
    if (right)
    {
        switchParser->AddCaseParser(new soul_expected::ast::spg::CaseParser(fromChoice.GetSourcePos(), right));
    }
    return switchParser;
}

Optimizer::Optimizer(soul_expected::ast::spg::SwitchParser* switchParser_) :
    switchParser(switchParser_),
    optimizedSpgFile(nullptr),
    optimizedParserFile(nullptr),
    optimizedGrammar(nullptr),
    optimizedRule(nullptr),
    optimizedParser(nullptr)
{
}

void Optimizer::Visit(soul_expected::ast::spg::ChoiceParser& parser)
{
    if (!Valid()) return;
    if (parser.Optimize())
    {
        if (switchParser)
        {
            std::expected<soul_expected::ast::spg::Parser*, int> leftrv = GenerateOptimizedParser(parser.Left(), switchParser);
            if (!leftrv)
            {
                SetError(leftrv.error());
                return;
            }
            soul_expected::ast::spg::Parser* left = *leftrv;
            if (left)
            {
                switchParser->AddCaseParser(new soul_expected::ast::spg::CaseParser(parser.GetSourcePos(), left));
            }
            std::expected<soul_expected::ast::spg::Parser*, int> rightrv = GenerateOptimizedParser(parser.Right(), switchParser);
            if (!rightrv)
            {
                SetError(rightrv.error());
                return;
            }
            soul_expected::ast::spg::Parser* right = *rightrv;
            if (right)
            {
                switchParser->AddCaseParser(new soul_expected::ast::spg::CaseParser(parser.GetSourcePos(), right));
            }
            optimizedParser = nullptr;
        }
        else
        {
            std::expected<soul_expected::ast::spg::SwitchParser*, int> srv = GenerateSwitch(parser);
            if (!srv)
            {
                SetError(srv.error());
                return;
            }
            optimizedParser = *srv;
        }
    }
    else
    {
        std::expected<soul_expected::ast::spg::Parser*, int> leftrv = GenerateOptimizedParser(parser.Left(), nullptr);
        if (!leftrv)
        {
            SetError(leftrv.error());
            return;
        }
        soul_expected::ast::spg::Parser* left = *leftrv;
        std::expected<soul_expected::ast::spg::Parser*, int> rightrv = GenerateOptimizedParser(parser.Right(), nullptr);
        if (!rightrv)
        {
            SetError(rightrv.error());
            return;
        }
        soul_expected::ast::spg::Parser* right = *rightrv;
        if (left && right)
        {
            optimizedParser = new soul_expected::ast::spg::ChoiceParser(parser.GetSourcePos(), left, right);
        }
        else if (left)
        {
            optimizedParser = left;
        }
        else if (right)
        {
            optimizedParser = right;
        }
        else
        {
            optimizedParser = nullptr;
        }
    }
}

void Optimizer::Visit(soul_expected::ast::spg::SequenceParser& parser)
{
    if (!Valid()) return;
    std::expected<soul_expected::ast::spg::Parser*, int> leftrv = GenerateOptimizedParser(parser.Left(), nullptr);
    if (!leftrv)
    {
        SetError(leftrv.error());
        return;
    }
    soul_expected::ast::spg::Parser* left = *leftrv;
    std::expected<soul_expected::ast::spg::Parser*, int> rightrv = GenerateOptimizedParser(parser.Right(), nullptr);
    if (!rightrv)
    {
        SetError(rightrv.error());
        return;
    }
    soul_expected::ast::spg::Parser* right = *rightrv;
    if (left && right)
    {
        optimizedParser = new soul_expected::ast::spg::SequenceParser(parser.GetSourcePos(), left, right);
    }
    else if (left)
    {
        optimizedParser = left;
    }
    else if (right)
    {
        optimizedParser = right;
    }
    else
    {
        optimizedParser = nullptr;
    }
}

void Optimizer::Visit(soul_expected::ast::spg::DifferenceParser& parser)
{
    if (!Valid()) return;
    std::expected<soul_expected::ast::spg::Parser*, int> leftrv = GenerateOptimizedParser(parser.Left(), nullptr);
    if (!leftrv)
    {
        SetError(leftrv.error());
        return;
    }
    soul_expected::ast::spg::Parser* left = *leftrv;
    std::expected<soul_expected::ast::spg::Parser*, int> rightrv = GenerateOptimizedParser(parser.Right(), nullptr);
    if (!rightrv)
    {
        SetError(rightrv.error());
        return;
    }
    soul_expected::ast::spg::Parser* right = *rightrv;
    if (left && right)
    {
        optimizedParser = new soul_expected::ast::spg::DifferenceParser(parser.GetSourcePos(), left, right);
    }
    else if (left)
    {
        optimizedParser = left;
    }
    else if (right)
    {
        optimizedParser = right;
    }
    else
    {
        optimizedParser = nullptr;
    }
}

void Optimizer::Visit(soul_expected::ast::spg::ListParser& parser)
{
    if (!Valid()) return;
    std::expected<soul_expected::ast::spg::Parser*, int> leftrv = GenerateOptimizedParser(parser.Left(), nullptr);
    if (!leftrv)
    {
        SetError(leftrv.error());
        return;
    }
    soul_expected::ast::spg::Parser* left = *leftrv;
    std::expected<soul_expected::ast::spg::Parser*, int> rightrv = GenerateOptimizedParser(parser.Right(), nullptr);
    if (!rightrv)
    {
        SetError(rightrv.error());
        return;
    }
    soul_expected::ast::spg::Parser* right = *rightrv;
    if (left && right)
    {
        optimizedParser = new soul_expected::ast::spg::ListParser(parser.GetSourcePos(), left, right);
    }
    else if (left)
    {
        optimizedParser = left;
    }
    else if (right)
    {
        optimizedParser = right;
    }
    else
    {
        optimizedParser = nullptr;
    }
}

void Optimizer::Visit(soul_expected::ast::spg::LookaheadParser& parser)
{
    if (!Valid()) return;
    parser.Child()->Accept(*this);
    if (!Valid()) return;
    if (optimizedParser)
    {
        optimizedParser = new soul_expected::ast::spg::LookaheadParser(parser.GetSourcePos(), optimizedParser);
    }
}

void Optimizer::Visit(soul_expected::ast::spg::KleeneParser& parser)
{
    if (!Valid()) return;
    parser.Child()->Accept(*this);
    if (!Valid()) return;
    if (optimizedParser)
    {
        optimizedParser = new soul_expected::ast::spg::KleeneParser(parser.GetSourcePos(), optimizedParser);
    }
}

void Optimizer::Visit(soul_expected::ast::spg::PositiveParser& parser)
{
    if (!Valid()) return;
    parser.Child()->Accept(*this);
    if (!Valid()) return;
    if (optimizedParser)
    {
        optimizedParser = new soul_expected::ast::spg::PositiveParser(parser.GetSourcePos(), optimizedParser);
    }
}

void Optimizer::Visit(soul_expected::ast::spg::OptionalParser& parser)
{
    if (!Valid()) return;
    parser.Child()->Accept(*this);
    if (!Valid()) return;
    if (optimizedParser)
    {
        optimizedParser = new soul_expected::ast::spg::OptionalParser(parser.GetSourcePos(), optimizedParser);
    }
}

void Optimizer::Visit(soul_expected::ast::spg::ExpectationParser& parser)
{
    if (!Valid()) return;
    parser.Child()->Accept(*this);
    if (!Valid()) return;
    if (optimizedParser)
    {
        optimizedParser = new soul_expected::ast::spg::ExpectationParser(parser.GetSourcePos(), optimizedParser);
    }
}

void Optimizer::Visit(soul_expected::ast::spg::ActionParser& parser)
{
    if (!Valid()) return;
    parser.Child()->Accept(*this);
    if (!Valid()) return;
    if (optimizedParser)
    {
        soul_expected::ast::cpp::CompoundStatementNode* clonedSuccessCode = static_cast<soul_expected::ast::cpp::CompoundStatementNode*>(parser.SuccessCode()->Clone());
        soul_expected::ast::cpp::CompoundStatementNode* clonedFailureCode = nullptr;
        if (parser.FailureCode())
        {
            clonedFailureCode = static_cast<soul_expected::ast::cpp::CompoundStatementNode*>(parser.FailureCode()->Clone());
        }
        optimizedParser = new soul_expected::ast::spg::ActionParser(parser.GetSourcePos(), optimizedParser, clonedSuccessCode, clonedFailureCode);
    }
}

void Optimizer::Visit(soul_expected::ast::spg::NonterminalParser& parser)
{
    if (!Valid()) return;
    optimizedParser = parser.Clone();
}

void Optimizer::Visit(soul_expected::ast::spg::EmptyParser& parser)
{
    if (!Valid()) return;
    optimizedParser = parser.Clone();
}

void Optimizer::Visit(soul_expected::ast::spg::AnyParser& parser)
{
    if (!Valid()) return;
    optimizedParser = parser.Clone();
}

void Optimizer::Visit(soul_expected::ast::spg::TokenParser& parser)
{
    if (!Valid()) return;
    optimizedParser = parser.Clone();
}

void Optimizer::Visit(soul_expected::ast::spg::GroupParser& parser)
{
    if (!Valid()) return;
    parser.Child()->Accept(*this);
    if (!Valid()) return;
    if (optimizedParser)
    {
        optimizedParser = new soul_expected::ast::spg::GroupParser(parser.GetSourcePos(), optimizedParser);
    }
}

void Optimizer::Visit(soul_expected::ast::spg::RuleParser& parser)
{
    if (!Valid()) return;
    optimizedRule = new soul_expected::ast::spg::RuleParser(parser.GetSourcePos(), parser.Name());
    for (const auto& param : parser.Params())
    {
        soul_expected::ast::spg::ParamVar* clonedParamVar = static_cast<soul_expected::ast::spg::ParamVar*>(param->Clone());
        optimizedRule->AddParamOrVariable(clonedParamVar);
    }
    for (const auto& var : parser.Vars())
    {
        soul_expected::ast::spg::ParamVar* clonedParamVar = static_cast<soul_expected::ast::spg::ParamVar*>(var->Clone());
        optimizedRule->AddParamOrVariable(clonedParamVar);
    }
    if (parser.ReturnType())
    {
        optimizedRule->SetReturnType(static_cast<soul_expected::ast::cpp::TypeIdNode*>(parser.ReturnType()->Clone()));
    }
    if (parser.HasReturn())
    {
        optimizedRule->SetHasReturn();
    }
    parser.Definition()->Accept(*this);
    if (!Valid()) return;
    optimizedRule->SetDefinition(optimizedParser);
}

void Optimizer::Visit(soul_expected::ast::spg::GrammarParser& parser)
{
    if (!Valid()) return;
    optimizedGrammar = new soul_expected::ast::spg::GrammarParser(parser.GetSourcePos(), parser.Name());
    if (parser.Main())
    {
        optimizedGrammar->SetMain();
    }
    optimizedGrammar->SetId(parser.Id());
    for (const auto& lexer : parser.Lexers())
    {
        optimizedGrammar->AddLexer(static_cast<soul_expected::ast::cpp::TypeIdNode*>(lexer->Clone()));
    }
    for (const auto& usng : parser.Usings())
    {
        optimizedGrammar->AddUsing(usng.sourcePos, usng.parserRuleId);
    }
    for (const auto& rule : parser.Rules())
    {
        rule->Accept(*this);
        if (!Valid()) return;
        optimizedGrammar->AddRule(optimizedRule);
    }
}

void Optimizer::Visit(soul_expected::ast::spg::ParserFile& parserFile)
{
    if (!Valid()) return;
    optimizedParserFile = new soul_expected::ast::spg::ParserFile(parserFile.FilePath());
    if (parserFile.IsExternal())
    {
        optimizedParserFile->SetExternal();
    }
    soul_expected::ast::common::ExportModule* exportModule = new soul_expected::ast::common::ExportModule(parserFile.ExportModule()->ModuleName());
    std::expected<bool, int> rv = optimizedParserFile->SetExportModule(exportModule);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    for (const auto& import : parserFile.Imports())
    {
        soul_expected::ast::common::Import* imp = new soul_expected::ast::common::Import(import->ModuleName(), import->Prefix());
        optimizedParserFile->AddImport(imp);
    }
    for (const auto& parser : parserFile.Parsers())
    {
        parser->Accept(*this);
        if (!Valid()) return;
        optimizedParserFile->AddParser(optimizedGrammar);
    }
}

void Optimizer::Visit(soul_expected::ast::spg::SpgFile& spgFile)
{
    if (!Valid()) return;
    optimizedSpgFile = new soul_expected::ast::spg::SpgFile(spgFile.FilePath(), spgFile.ProjectName());
    for (const auto& parserFile : spgFile.ParserFiles())
    {
        parserFile->Accept(*this);
        if (!Valid()) return;
        optimizedSpgFile->AddParserFile(optimizedParserFile);
    }
}

std::expected<soul_expected::ast::spg::SpgFile*, int> GenerateOptimizedSpg(soul_expected::ast::spg::SpgFile* spgFile, bool verbose)
{
    if (verbose)
    {
        std::cout << "generating optimized parsers..." << std::endl;
    }
    Optimizer optimizer(nullptr);
    spgFile->Accept(optimizer);
    if (!optimizer) return std::unexpected<int>(optimizer.Error());
    return optimizer.GetOptimizedSpgFile();
}

std::expected<bool, int> SetOptimizationFlags(soul_expected::ast::spg::SpgFile* spgFile, bool verbose)
{
    if (verbose)
    {
        std::cout << "setting optimization flags..." << std::endl;
    }
    OptimizationFlagsSetter flagSetter;
    spgFile->Accept(flagSetter);
    if (!flagSetter) return std::unexpected<int>(flagSetter.Error());
    if (verbose)
    {
        std::cout << flagSetter.Count() << " choice parsers can be optimized" << std::endl;
    }
    return std::expected<bool, int>(true);
}

std::expected<std::unique_ptr<soul_expected::ast::spg::SpgFile>, int> Optimize(soul_expected::ast::spg::SpgFile* spgFile, bool verbose, bool xml, 
    soul_expected::lexer::FileMap& fileMap)
{
    if (verbose)
    {
        std::cout << "optimizing..." << std::endl;
    }
    std::expected<bool, int> rv = ComputeFirstSets(spgFile, verbose);
    if (!rv) return std::unexpected<int>(rv.error());
    if (xml)
    {
        rv = PrintXml(spgFile, verbose, false);
        if (!rv) return std::unexpected<int>(rv.error());
    }
    rv = SetOptimizationFlags(spgFile, verbose);
    if (!rv) return std::unexpected<int>(rv.error());
    std::expected<soul_expected::ast::spg::SpgFile*, int> orv = GenerateOptimizedSpg(spgFile, verbose);
    if (!orv) return std::unexpected<int>(orv.error());
    soul_expected::ast::spg::SpgFile* optimizedSpg = *orv;
    rv = Link(optimizedSpg, verbose, fileMap);
    if (!rv) return std::unexpected<int>(rv.error());
    rv = ComputeFirstSets(optimizedSpg, verbose);
    if (!rv) return std::unexpected<int>(rv.error());
    return std::expected<std::unique_ptr<soul_expected::ast::spg::SpgFile>, int>(optimizedSpg);
}

} // namespace soul_expected::spg
