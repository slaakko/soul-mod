// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.spg.optimizer;

import soul.spg.first.set.computer;
import soul.spg.xml.printer;
import soul.spg.linking;

namespace soul::spg {

class OptimizationFlagsSetter : public soul::ast::spg::DefaultVisitor
{
public:
    OptimizationFlagsSetter();
    inline int Count() const { return count; }
    void Visit(soul::ast::spg::ChoiceParser& parser) override;
private:
    int count;
};

OptimizationFlagsSetter::OptimizationFlagsSetter() : count(0)
{
}

void OptimizationFlagsSetter::Visit(soul::ast::spg::ChoiceParser& parser)
{
    soul::ast::spg::DefaultVisitor::Visit(parser);
    auto rv = parser.SetOptimizationFlag(count);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

class Optimizer : public soul::ast::spg::DefaultVisitor
{
public:
    Optimizer(soul::ast::spg::SwitchParser* switchParser_);
    inline soul::ast::spg::Parser* GetOptimizedParser() { return optimizedParser; }
    inline soul::ast::spg::SpgFile* GetOptimizedSpgFile() const { return optimizedSpgFile; }
    void Visit(soul::ast::spg::ChoiceParser& parser) override;
    void Visit(soul::ast::spg::SequenceParser& parser) override;
    void Visit(soul::ast::spg::DifferenceParser& parser) override;
    void Visit(soul::ast::spg::ListParser& parser) override;
    void Visit(soul::ast::spg::LookaheadParser& parser) override;
    void Visit(soul::ast::spg::KleeneParser& parser) override;
    void Visit(soul::ast::spg::PositiveParser& parser) override;
    void Visit(soul::ast::spg::OptionalParser& parser) override;
    void Visit(soul::ast::spg::ExpectationParser& parser) override;
    void Visit(soul::ast::spg::ActionParser& parser) override;
    void Visit(soul::ast::spg::NonterminalParser& parser) override;
    void Visit(soul::ast::spg::EmptyParser& parser) override;
    void Visit(soul::ast::spg::AnyParser& parser) override;
    void Visit(soul::ast::spg::TokenParser& parser) override;
    void Visit(soul::ast::spg::GroupParser& parser) override;
    void Visit(soul::ast::spg::RuleParser& parser) override;
    void Visit(soul::ast::spg::GrammarParser& parser) override;
    void Visit(soul::ast::spg::ParserFile& parserFile) override;
    void Visit(soul::ast::spg::SpgFile& spgFile) override;
private:
    soul::ast::spg::SpgFile* optimizedSpgFile;
    soul::ast::spg::ParserFile* optimizedParserFile;
    soul::ast::spg::GrammarParser* optimizedGrammar;
    soul::ast::spg::RuleParser* optimizedRule;
    soul::ast::spg::Parser* optimizedParser;
    soul::ast::spg::SwitchParser* switchParser;
};

std::expected<soul::ast::spg::Parser*, int> GenerateOptimizedParser(soul::ast::spg::Parser* from, soul::ast::spg::SwitchParser* switchParser)
{
    Optimizer optimizer(switchParser);
    from->Accept(optimizer);
    if (!optimizer) return std::unexpected<int>(optimizer.Error());
    return optimizer.GetOptimizedParser();
}

std::expected<soul::ast::spg::SwitchParser*, int> GenerateSwitch(soul::ast::spg::ChoiceParser& fromChoice)
{
    soul::ast::spg::SwitchParser* switchParser = new soul::ast::spg::SwitchParser(fromChoice.GetSourcePos());
    std::expected<soul::ast::spg::Parser*, int> leftrv = GenerateOptimizedParser(fromChoice.Left(), switchParser);
    if (!leftrv) return std::unexpected<int>(leftrv.error());
    soul::ast::spg::Parser* left = *leftrv;
    if (left)
    {
        switchParser->AddCaseParser(new soul::ast::spg::CaseParser(fromChoice.GetSourcePos(), left));
    }
    std::expected<soul::ast::spg::Parser*, int> rightrv = GenerateOptimizedParser(fromChoice.Right(), switchParser);
    if (!rightrv) return std::unexpected<int>(rightrv.error());
    soul::ast::spg::Parser* right = *rightrv;
    if (right)
    {
        switchParser->AddCaseParser(new soul::ast::spg::CaseParser(fromChoice.GetSourcePos(), right));
    }
    return switchParser;
}

Optimizer::Optimizer(soul::ast::spg::SwitchParser* switchParser_) :
    switchParser(switchParser_),
    optimizedSpgFile(nullptr),
    optimizedParserFile(nullptr),
    optimizedGrammar(nullptr),
    optimizedRule(nullptr),
    optimizedParser(nullptr)
{
}

void Optimizer::Visit(soul::ast::spg::ChoiceParser& parser)
{
    if (!Valid()) return;
    if (parser.Optimize())
    {
        if (switchParser)
        {
            std::expected<soul::ast::spg::Parser*, int> leftrv = GenerateOptimizedParser(parser.Left(), switchParser);
            if (!leftrv)
            {
                SetError(leftrv.error());
                return;
            }
            soul::ast::spg::Parser* left = *leftrv;
            if (left)
            {
                switchParser->AddCaseParser(new soul::ast::spg::CaseParser(parser.GetSourcePos(), left));
            }
            std::expected<soul::ast::spg::Parser*, int> rightrv = GenerateOptimizedParser(parser.Right(), switchParser);
            if (!rightrv)
            {
                SetError(rightrv.error());
                return;
            }
            soul::ast::spg::Parser* right = *rightrv;
            if (right)
            {
                switchParser->AddCaseParser(new soul::ast::spg::CaseParser(parser.GetSourcePos(), right));
            }
            optimizedParser = nullptr;
        }
        else
        {
            std::expected<soul::ast::spg::SwitchParser*, int> srv = GenerateSwitch(parser);
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
        std::expected<soul::ast::spg::Parser*, int> leftrv = GenerateOptimizedParser(parser.Left(), nullptr);
        if (!leftrv)
        {
            SetError(leftrv.error());
            return;
        }
        soul::ast::spg::Parser* left = *leftrv;
        std::expected<soul::ast::spg::Parser*, int> rightrv = GenerateOptimizedParser(parser.Right(), nullptr);
        if (!rightrv)
        {
            SetError(rightrv.error());
            return;
        }
        soul::ast::spg::Parser* right = *rightrv;
        if (left && right)
        {
            optimizedParser = new soul::ast::spg::ChoiceParser(parser.GetSourcePos(), left, right);
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

void Optimizer::Visit(soul::ast::spg::SequenceParser& parser)
{
    if (!Valid()) return;
    std::expected<soul::ast::spg::Parser*, int> leftrv = GenerateOptimizedParser(parser.Left(), nullptr);
    if (!leftrv)
    {
        SetError(leftrv.error());
        return;
    }
    soul::ast::spg::Parser* left = *leftrv;
    std::expected<soul::ast::spg::Parser*, int> rightrv = GenerateOptimizedParser(parser.Right(), nullptr);
    if (!rightrv)
    {
        SetError(rightrv.error());
        return;
    }
    soul::ast::spg::Parser* right = *rightrv;
    if (left && right)
    {
        optimizedParser = new soul::ast::spg::SequenceParser(parser.GetSourcePos(), left, right);
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

void Optimizer::Visit(soul::ast::spg::DifferenceParser& parser)
{
    if (!Valid()) return;
    std::expected<soul::ast::spg::Parser*, int> leftrv = GenerateOptimizedParser(parser.Left(), nullptr);
    if (!leftrv)
    {
        SetError(leftrv.error());
        return;
    }
    soul::ast::spg::Parser* left = *leftrv;
    std::expected<soul::ast::spg::Parser*, int> rightrv = GenerateOptimizedParser(parser.Right(), nullptr);
    if (!rightrv)
    {
        SetError(rightrv.error());
        return;
    }
    soul::ast::spg::Parser* right = *rightrv;
    if (left && right)
    {
        optimizedParser = new soul::ast::spg::DifferenceParser(parser.GetSourcePos(), left, right);
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

void Optimizer::Visit(soul::ast::spg::ListParser& parser)
{
    if (!Valid()) return;
    std::expected<soul::ast::spg::Parser*, int> leftrv = GenerateOptimizedParser(parser.Left(), nullptr);
    if (!leftrv)
    {
        SetError(leftrv.error());
        return;
    }
    soul::ast::spg::Parser* left = *leftrv;
    std::expected<soul::ast::spg::Parser*, int> rightrv = GenerateOptimizedParser(parser.Right(), nullptr);
    if (!rightrv)
    {
        SetError(rightrv.error());
        return;
    }
    soul::ast::spg::Parser* right = *rightrv;
    if (left && right)
    {
        optimizedParser = new soul::ast::spg::ListParser(parser.GetSourcePos(), left, right);
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

void Optimizer::Visit(soul::ast::spg::LookaheadParser& parser)
{
    if (!Valid()) return;
    parser.Child()->Accept(*this);
    if (!Valid()) return;
    if (optimizedParser)
    {
        optimizedParser = new soul::ast::spg::LookaheadParser(parser.GetSourcePos(), optimizedParser);
    }
}

void Optimizer::Visit(soul::ast::spg::KleeneParser& parser)
{
    if (!Valid()) return;
    parser.Child()->Accept(*this);
    if (!Valid()) return;
    if (optimizedParser)
    {
        optimizedParser = new soul::ast::spg::KleeneParser(parser.GetSourcePos(), optimizedParser);
    }
}

void Optimizer::Visit(soul::ast::spg::PositiveParser& parser)
{
    if (!Valid()) return;
    parser.Child()->Accept(*this);
    if (!Valid()) return;
    if (optimizedParser)
    {
        optimizedParser = new soul::ast::spg::PositiveParser(parser.GetSourcePos(), optimizedParser);
    }
}

void Optimizer::Visit(soul::ast::spg::OptionalParser& parser)
{
    if (!Valid()) return;
    parser.Child()->Accept(*this);
    if (!Valid()) return;
    if (optimizedParser)
    {
        optimizedParser = new soul::ast::spg::OptionalParser(parser.GetSourcePos(), optimizedParser);
    }
}

void Optimizer::Visit(soul::ast::spg::ExpectationParser& parser)
{
    if (!Valid()) return;
    parser.Child()->Accept(*this);
    if (!Valid()) return;
    if (optimizedParser)
    {
        optimizedParser = new soul::ast::spg::ExpectationParser(parser.GetSourcePos(), optimizedParser);
    }
}

void Optimizer::Visit(soul::ast::spg::ActionParser& parser)
{
    if (!Valid()) return;
    parser.Child()->Accept(*this);
    if (!Valid()) return;
    if (optimizedParser)
    {
        soul::ast::cpp::CompoundStatementNode* clonedSuccessCode = static_cast<soul::ast::cpp::CompoundStatementNode*>(parser.SuccessCode()->Clone());
        soul::ast::cpp::CompoundStatementNode* clonedFailureCode = nullptr;
        if (parser.FailureCode())
        {
            clonedFailureCode = static_cast<soul::ast::cpp::CompoundStatementNode*>(parser.FailureCode()->Clone());
        }
        optimizedParser = new soul::ast::spg::ActionParser(parser.GetSourcePos(), optimizedParser, clonedSuccessCode, clonedFailureCode);
    }
}

void Optimizer::Visit(soul::ast::spg::NonterminalParser& parser)
{
    if (!Valid()) return;
    optimizedParser = parser.Clone();
}

void Optimizer::Visit(soul::ast::spg::EmptyParser& parser)
{
    if (!Valid()) return;
    optimizedParser = parser.Clone();
}

void Optimizer::Visit(soul::ast::spg::AnyParser& parser)
{
    if (!Valid()) return;
    optimizedParser = parser.Clone();
}

void Optimizer::Visit(soul::ast::spg::TokenParser& parser)
{
    if (!Valid()) return;
    optimizedParser = parser.Clone();
}

void Optimizer::Visit(soul::ast::spg::GroupParser& parser)
{
    if (!Valid()) return;
    parser.Child()->Accept(*this);
    if (!Valid()) return;
    if (optimizedParser)
    {
        optimizedParser = new soul::ast::spg::GroupParser(parser.GetSourcePos(), optimizedParser);
    }
}

void Optimizer::Visit(soul::ast::spg::RuleParser& parser)
{
    if (!Valid()) return;
    optimizedRule = new soul::ast::spg::RuleParser(parser.GetSourcePos(), parser.Name());
    for (const auto& param : parser.Params())
    {
        soul::ast::spg::ParamVar* clonedParamVar = static_cast<soul::ast::spg::ParamVar*>(param->Clone());
        optimizedRule->AddParamOrVariable(clonedParamVar);
    }
    for (const auto& var : parser.Vars())
    {
        soul::ast::spg::ParamVar* clonedParamVar = static_cast<soul::ast::spg::ParamVar*>(var->Clone());
        optimizedRule->AddParamOrVariable(clonedParamVar);
    }
    if (parser.ReturnType())
    {
        optimizedRule->SetReturnType(static_cast<soul::ast::cpp::TypeIdNode*>(parser.ReturnType()->Clone()));
    }
    if (parser.HasReturn())
    {
        optimizedRule->SetHasReturn();
    }
    parser.Definition()->Accept(*this);
    if (!Valid()) return;
    optimizedRule->SetDefinition(optimizedParser);
}

void Optimizer::Visit(soul::ast::spg::GrammarParser& parser)
{
    if (!Valid()) return;
    optimizedGrammar = new soul::ast::spg::GrammarParser(parser.GetSourcePos(), parser.Name());
    if (parser.Main())
    {
        optimizedGrammar->SetMain();
    }
    optimizedGrammar->SetId(parser.Id());
    for (const auto& lexer : parser.Lexers())
    {
        optimizedGrammar->AddLexer(static_cast<soul::ast::cpp::TypeIdNode*>(lexer->Clone()));
    }
    for (const auto& usng : parser.Usings())
    {
        optimizedGrammar->AddUsing(usng.sourcePos, usng.fullName);
    }
    for (const auto& rule : parser.Rules())
    {
        rule->Accept(*this);
        if (!Valid()) return;
        optimizedGrammar->AddRule(optimizedRule);
    }
}

void Optimizer::Visit(soul::ast::spg::ParserFile& parserFile)
{
    if (!Valid()) return;
    optimizedParserFile = new soul::ast::spg::ParserFile(parserFile.FilePath());
    if (parserFile.IsExternal())
    {
        optimizedParserFile->SetExternal();
    }
    soul::ast::common::ExportModule* exportModule = new soul::ast::common::ExportModule(parserFile.GetExportModule()->ModuleName());
    std::expected<bool, int> rv = optimizedParserFile->SetExportModule(exportModule);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    for (const auto& import : parserFile.Imports())
    {
        soul::ast::common::Import* imp = new soul::ast::common::Import(import->ModuleName(), import->Prefix());
        optimizedParserFile->AddImport(imp);
    }
    for (const auto& parser : parserFile.Parsers())
    {
        parser->Accept(*this);
        if (!Valid()) return;
        optimizedParserFile->AddParser(optimizedGrammar);
    }
}

void Optimizer::Visit(soul::ast::spg::SpgFile& spgFile)
{
    if (!Valid()) return;
    optimizedSpgFile = new soul::ast::spg::SpgFile(spgFile.FilePath(), spgFile.ProjectName());
    for (const auto& parserFile : spgFile.ParserFiles())
    {
        parserFile->Accept(*this);
        if (!Valid()) return;
        optimizedSpgFile->AddParserFile(optimizedParserFile);
    }
}

std::expected<soul::ast::spg::SpgFile*, int> GenerateOptimizedSpg(soul::ast::spg::SpgFile* spgFile, bool verbose)
{
    if (verbose)
    {
        std::cout << "generating optimized parsers..." << "\n";
    }
    Optimizer optimizer(nullptr);
    spgFile->Accept(optimizer);
    if (!optimizer) return std::unexpected<int>(optimizer.Error());
    soul::ast::spg::SpgFile* optimizedSpgFile = optimizer.GetOptimizedSpgFile();
    int n = static_cast<int>(spgFile->TokenFiles().size());
    for (int i = 0; i < n; ++i)
    {
        optimizedSpgFile->AddTokenFile(spgFile->TokenFiles()[i]->Clone());
    }
    return optimizedSpgFile;
}

std::expected<bool, int> SetOptimizationFlags(soul::ast::spg::SpgFile* spgFile, bool verbose)
{
    if (verbose)
    {
        std::cout << "setting optimization flags..." << "\n";
    }
    OptimizationFlagsSetter flagSetter;
    spgFile->Accept(flagSetter);
    if (!flagSetter) return std::unexpected<int>(flagSetter.Error());
    if (verbose)
    {
        std::cout << flagSetter.Count() << " choice parsers can be optimized" << "\n";
    }
    return std::expected<bool, int>(true);
}

std::expected<std::unique_ptr<soul::ast::spg::SpgFile>, int> Optimize(soul::ast::spg::SpgFile* spgFile, bool verbose, bool xml,
    soul::lexer::FileMap& fileMap)
{
    if (verbose)
    {
        std::cout << "optimizing..." << "\n";
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
    std::expected<soul::ast::spg::SpgFile*, int> orv = GenerateOptimizedSpg(spgFile, verbose);
    if (!orv) return std::unexpected<int>(orv.error());
    soul::ast::spg::SpgFile* optimizedSpg = *orv;
    rv = Link(optimizedSpg, verbose, fileMap);
    if (!rv) return std::unexpected<int>(rv.error());
    rv = ComputeFirstSets(optimizedSpg, verbose);
    if (!rv) return std::unexpected<int>(rv.error());
    return std::expected<std::unique_ptr<soul::ast::spg::SpgFile>, int>(std::unique_ptr<soul::ast::spg::SpgFile>(optimizedSpg));
}

} // namespace soul::spg
