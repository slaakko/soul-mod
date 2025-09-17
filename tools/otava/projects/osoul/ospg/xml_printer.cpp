// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.spg.xml.printer;

import util;
import soul.ast.spg;
import soul.xml.dom;

namespace soul::spg {

class XmlPrinter : public soul::ast::spg::DefaultVisitor
{
public:
    XmlPrinter(bool verbose_, bool opt_);
    void Visit(soul::ast::spg::ChoiceParser& parser) override;
    void Visit(soul::ast::spg::SwitchParser& parser) override;
    void Visit(soul::ast::spg::CaseParser& parser) override;
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
private:
    bool verbose;
    bool opt;
    soul::xml::Element* currentElement;
};

XmlPrinter::XmlPrinter(bool verbose_, bool opt_) : verbose(verbose_), opt(opt_)
{
}

void XmlPrinter::Visit(soul::ast::spg::ChoiceParser& parser)
{
    if (!Valid()) return;
    soul::xml::Element* parentElement = currentElement;
    currentElement = soul::xml::MakeElement("choice");
    auto rv = parentElement->AppendChild(currentElement);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    currentElement->SetAttribute("first", parser.First().ToString());
    parser.Left()->Accept(*this);
    if (!Valid()) return;
    parser.Right()->Accept(*this);
    if (!Valid()) return;
    currentElement = parentElement;
}

void XmlPrinter::Visit(soul::ast::spg::SwitchParser& parser)
{
    if (!Valid()) return;
    soul::xml::Element* parentElement = currentElement;
    currentElement = soul::xml::MakeElement("switch");
    auto rv = parentElement->AppendChild(currentElement);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    currentElement->SetAttribute("first", parser.First().ToString());
    for (const auto& caseParser : parser.CaseParsers())
    {
        caseParser->Accept(*this);
        if (!Valid()) return;
    }
    currentElement = parentElement;
}

void XmlPrinter::Visit(soul::ast::spg::CaseParser& parser)
{
    if (!Valid()) return;
    soul::xml::Element* parentElement = currentElement;
    currentElement = soul::xml::MakeElement("case");
    auto rv = parentElement->AppendChild(currentElement);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    currentElement->SetAttribute("first", parser.First().ToString());
    parser.Child()->Accept(*this);
    if (!Valid()) return;
    currentElement = parentElement;
}

void XmlPrinter::Visit(soul::ast::spg::SequenceParser& parser)
{
    if (!Valid()) return;
    soul::xml::Element* parentElement = currentElement;
    currentElement = soul::xml::MakeElement("sequence");
    auto rv = parentElement->AppendChild(currentElement);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    currentElement->SetAttribute("first", parser.First().ToString());
    parser.Left()->Accept(*this);
    if (!Valid()) return;
    parser.Right()->Accept(*this);
    if (!Valid()) return;
    currentElement = parentElement;
}

void XmlPrinter::Visit(soul::ast::spg::DifferenceParser& parser)
{
    if (!Valid()) return;
    soul::xml::Element* parentElement = currentElement;
    currentElement = soul::xml::MakeElement("difference");
    auto rv = parentElement->AppendChild(currentElement);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    currentElement->SetAttribute("first", parser.First().ToString());
    parser.Left()->Accept(*this);
    if (!Valid()) return;
    parser.Right()->Accept(*this);
    if (!Valid()) return;
    currentElement = parentElement;
}

void XmlPrinter::Visit(soul::ast::spg::ListParser& parser)
{
    if (!Valid()) return;
    soul::xml::Element* parentElement = currentElement;
    currentElement = soul::xml::MakeElement("list");
    auto rv = parentElement->AppendChild(currentElement);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    currentElement->SetAttribute("first", parser.First().ToString());
    parser.Child()->Accept(*this);
    if (!Valid()) return;
    currentElement = parentElement;
}

void XmlPrinter::Visit(soul::ast::spg::LookaheadParser& parser)
{
    if (!Valid()) return;
    soul::xml::Element* parentElement = currentElement;
    currentElement = soul::xml::MakeElement("lookahead");
    auto rv = parentElement->AppendChild(currentElement);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    currentElement->SetAttribute("first", parser.First().ToString());
    parser.Child()->Accept(*this);
    if (!Valid()) return;
    currentElement = parentElement;
}

void XmlPrinter::Visit(soul::ast::spg::KleeneParser& parser)
{
    if (!Valid()) return;
    soul::xml::Element* parentElement = currentElement;
    currentElement = soul::xml::MakeElement("kleene");
    auto rv = parentElement->AppendChild(currentElement);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    currentElement->SetAttribute("first", parser.First().ToString());
    parser.Child()->Accept(*this);
    if (!Valid()) return;
    currentElement = parentElement;
}

void XmlPrinter::Visit(soul::ast::spg::PositiveParser& parser)
{
    if (!Valid()) return;
    soul::xml::Element* parentElement = currentElement;
    currentElement = soul::xml::MakeElement("positive");
    auto rv = parentElement->AppendChild(currentElement);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    currentElement->SetAttribute("first", parser.First().ToString());
    parser.Child()->Accept(*this);
    if (!Valid()) return;
    currentElement = parentElement;
}

void XmlPrinter::Visit(soul::ast::spg::OptionalParser& parser)
{
    if (!Valid()) return;
    soul::xml::Element* parentElement = currentElement;
    currentElement = soul::xml::MakeElement("optional");
    auto rv = parentElement->AppendChild(currentElement);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    currentElement->SetAttribute("first", parser.First().ToString());
    parser.Child()->Accept(*this);
    if (!Valid()) return;
    currentElement = parentElement;
}

void XmlPrinter::Visit(soul::ast::spg::ExpectationParser& parser)
{
    if (!Valid()) return;
    soul::xml::Element* parentElement = currentElement;
    currentElement = soul::xml::MakeElement("expectation");
    auto rv = parentElement->AppendChild(currentElement);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    currentElement->SetAttribute("first", parser.First().ToString());
    parser.Child()->Accept(*this);
    if (!Valid()) return;
    currentElement = parentElement;
}

void XmlPrinter::Visit(soul::ast::spg::ActionParser& parser)
{
    if (!Valid()) return;
    soul::xml::Element* parentElement = currentElement;
    currentElement = soul::xml::MakeElement("action");
    auto rv = parentElement->AppendChild(currentElement);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    currentElement->SetAttribute("first", parser.First().ToString());
    parser.Child()->Accept(*this);
    if (!Valid()) return;
    currentElement = parentElement;
}

void XmlPrinter::Visit(soul::ast::spg::NonterminalParser& parser)
{
    if (!Valid()) return;
    soul::xml::Element* parentElement = currentElement;
    currentElement = soul::xml::MakeElement("nonterminal");
    auto rv = parentElement->AppendChild(currentElement);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    currentElement->SetAttribute("ruleName", parser.RuleName());
    currentElement->SetAttribute("first", parser.First().ToString());
    currentElement = parentElement;
}

void XmlPrinter::Visit(soul::ast::spg::EmptyParser& parser)
{
    if (!Valid()) return;
    soul::xml::Element* parentElement = currentElement;
    currentElement = soul::xml::MakeElement("empty");
    auto rv = parentElement->AppendChild(currentElement);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    currentElement->SetAttribute("first", parser.First().ToString());
    currentElement = parentElement;
}

void XmlPrinter::Visit(soul::ast::spg::AnyParser& parser)
{
    if (!Valid()) return;
    soul::xml::Element* parentElement = currentElement;
    currentElement = soul::xml::MakeElement("any");
    auto rv = parentElement->AppendChild(currentElement);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    currentElement->SetAttribute("first", parser.First().ToString());
    currentElement = parentElement;
}

void XmlPrinter::Visit(soul::ast::spg::TokenParser& parser)
{
    if (!Valid()) return;
    soul::xml::Element* parentElement = currentElement;
    currentElement = soul::xml::MakeElement("token");
    auto rv = parentElement->AppendChild(currentElement);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    currentElement->SetAttribute("name", parser.TokenName());
    currentElement->SetAttribute("first", parser.First().ToString());
    currentElement = parentElement;
}

void XmlPrinter::Visit(soul::ast::spg::GroupParser& parser)
{
    if (!Valid()) return;
    soul::xml::Element* parentElement = currentElement;
    currentElement = soul::xml::MakeElement("group");
    auto rv = parentElement->AppendChild(currentElement);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    currentElement->SetAttribute("first", parser.First().ToString());
    parser.Child()->Accept(*this);
    if (!Valid()) return;
    currentElement = parentElement;
}

void XmlPrinter::Visit(soul::ast::spg::RuleParser& parser)
{
    if (!Valid()) return;
    soul::xml::Element* parentElement = currentElement;
    currentElement = soul::xml::MakeElement("rule");
    auto rv = parentElement->AppendChild(currentElement);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    currentElement->SetAttribute("name", parser.Name());
    currentElement->SetAttribute("first", parser.First().ToString());
    parser.Definition()->Accept(*this);
    if (!Valid()) return;
    currentElement = parentElement;
}

void XmlPrinter::Visit(soul::ast::spg::GrammarParser& parser)
{
    if (!Valid()) return;
    soul::xml::Element* parentElement = currentElement;
    currentElement = soul::xml::MakeElement("grammar");
    auto rv = parentElement->AppendChild(currentElement);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    currentElement->SetAttribute("name", parser.Name());
    for (const auto& rule : parser.Rules())
    {
        rule->Accept(*this);
        if (!Valid()) return;
    }
    currentElement = parentElement;
}

void XmlPrinter::Visit(soul::ast::spg::ParserFile& parserFile)
{
    if (!Valid()) return;
    soul::xml::Document doc;
    std::string xmlFilePath;
    if (opt)
    {
        xmlFilePath = parserFile.FilePath() + ".opt.xml";
    }
    else
    {
        xmlFilePath = parserFile.FilePath() + ".xml";
    }
    std::ofstream file(xmlFilePath);
    if (!file)
    {
        SetError(util::AllocateError("could not create file '" + xmlFilePath + "'"));
        return;
    }
    util::CodeFormatter formatter(file);
    formatter.SetIndentSize(1);
    currentElement = soul::xml::MakeElement("parserFile");
    auto rv = doc.AppendChild(currentElement);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    for (const auto& grammar : parserFile.Parsers())
    {
        grammar->Accept(*this);
        if (!Valid()) return;
    }
    rv = doc.Write(formatter);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    if (verbose)
    {
        std::cout << "==> " << xmlFilePath << std::endl;
    }
}

std::expected<bool, int> PrintXml(soul::ast::spg::SpgFile* spgFile, bool verbose, bool opt)
{
    XmlPrinter printer(verbose, opt);
    spgFile->Accept(printer);
    if (!printer) return std::unexpected<int>(printer.Error());
    return std::expected<bool, int>(true);
}

} // namespace soul::spg
