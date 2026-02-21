// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.control.xml.generator;

import otava.symbols.bound.tree.visitor;
import otava.symbols.function.symbol;
import soul.xml.dom;
import util;

namespace otava::symbols {

class ControlXmlGenerator : public BoundTreeVisitor
{
public:
    std::unique_ptr<soul::xml::Element> GetElement() { return std::unique_ptr<soul::xml::Element>(element); }
    void Visit(BoundFunctionNode& node) override;
    void Visit(BoundCompoundStatementNode& node) override;
    void Visit(BoundIfStatementNode& node) override;
    void Visit(BoundSwitchStatementNode& node) override;
    void Visit(BoundCaseStatementNode& node) override;
    void Visit(BoundDefaultStatementNode& node) override;
    void Visit(BoundWhileStatementNode& node) override;
    void Visit(BoundDoStatementNode& node) override;
    void Visit(BoundForStatementNode& node) override;
    void Visit(BoundSequenceStatementNode& node) override;
    void Visit(BoundBreakStatementNode& node) override;
    void Visit(BoundContinueStatementNode& node) override;
    void Visit(BoundReturnStatementNode& node) override;
    void Visit(BoundGotoStatementNode& node) override;
    void Visit(BoundLabeledStatementNode& node) override;
    void Visit(BoundConstructionStatementNode& node) override;
    void Visit(BoundExpressionStatementNode& node) override;
    void Visit(BoundSetVPtrStatementNode& node) override;
    void Visit(BoundAliasDeclarationStatementNode& node) override;
private:
    soul::xml::Element* element;
};

void ControlXmlGenerator::Visit(BoundFunctionNode& node)
{
    element = soul::xml::MakeElement("function");
    element->SetAttribute("name", util::ToUtf8(node.GetFunctionDefinitionSymbol()->Name()));
    node.Body()->Accept(*this);
}

void ControlXmlGenerator::Visit(BoundCompoundStatementNode& node)
{
    soul::xml::Element* prevElement = element;
    element = soul::xml::MakeElement("compound");
    for (const auto& statement : node.Statements())
    {
        statement->Accept(*this);
    }
    prevElement->AppendChild(element);
    element = prevElement;
}

void ControlXmlGenerator::Visit(BoundIfStatementNode& node)
{
    soul::xml::Element* prevElement = element;
    soul::xml::Element* ifElement = soul::xml::MakeElement("if");
    soul::xml::Element* thenElement = soul::xml::MakeElement("then");
    ifElement->AppendChild(thenElement);
    element = thenElement;
    node.ThenStatement()->Accept(*this);
    if (node.ElseStatement())
    {
        soul::xml::Element* elseElement = soul::xml::MakeElement("else");
        ifElement->AppendChild(elseElement);
        element = elseElement;
        node.ElseStatement()->Accept(*this);
    }
    element = ifElement;
    prevElement->AppendChild(element);
    element = prevElement;
}

void ControlXmlGenerator::Visit(BoundSwitchStatementNode& node)
{
    soul::xml::Element* prevElement = element;
    element = soul::xml::MakeElement("switch");
    node.Statement()->Accept(*this);
    prevElement->AppendChild(element);
    element = prevElement;
}

void ControlXmlGenerator::Visit(BoundCaseStatementNode& node)
{
    soul::xml::Element* prevElement = element;
    element = soul::xml::MakeElement("case");
    node.Statement()->Accept(*this);
    prevElement->AppendChild(element);
    element = prevElement;
}

void ControlXmlGenerator::Visit(BoundDefaultStatementNode& node)
{
    soul::xml::Element* prevElement = element;
    element = soul::xml::MakeElement("default");
    node.Statement()->Accept(*this);
    prevElement->AppendChild(element);
    element = prevElement;
}

void ControlXmlGenerator::Visit(BoundWhileStatementNode& node)
{
    soul::xml::Element* prevElement = element;
    element = soul::xml::MakeElement("while");
    node.Statement()->Accept(*this);
    prevElement->AppendChild(element);
    element = prevElement;
}

void ControlXmlGenerator::Visit(BoundDoStatementNode& node)
{
    soul::xml::Element* prevElement = element;
    element = soul::xml::MakeElement("do");
    node.Statement()->Accept(*this);
    prevElement->AppendChild(element);
    element = prevElement;
}

void ControlXmlGenerator::Visit(BoundForStatementNode& node)
{
    soul::xml::Element* prevElement = element;
    element = soul::xml::MakeElement("for");
    node.Statement()->Accept(*this);
    prevElement->AppendChild(element);
    element = prevElement;
}

void ControlXmlGenerator::Visit(BoundSequenceStatementNode& node)
{
    soul::xml::Element* prevElement = element;
    element = soul::xml::MakeElement("sequence");
    soul::xml::Element* sequenceElement = element;
    soul::xml::Element* firstElement = soul::xml::MakeElement("first");
    element->AppendChild(firstElement);
    element = firstElement;
    node.First()->Accept(*this);
    soul::xml::Element* secondElement = soul::xml::MakeElement("second");
    sequenceElement->AppendChild(secondElement);
    element = secondElement;
    node.Second()->Accept(*this);
    element = sequenceElement;
    prevElement->AppendChild(element);
    element = prevElement;
}

void ControlXmlGenerator::Visit(BoundBreakStatementNode& node)
{
    soul::xml::Element* prevElement = element;
    element = soul::xml::MakeElement("break");
    prevElement->AppendChild(element);
    element = prevElement;
}

void ControlXmlGenerator::Visit(BoundContinueStatementNode& node)
{
    soul::xml::Element* prevElement = element;
    element = soul::xml::MakeElement("continue");
    prevElement->AppendChild(element);
    element = prevElement;
}

void ControlXmlGenerator::Visit(BoundReturnStatementNode& node)
{
    soul::xml::Element* prevElement = element;
    element = soul::xml::MakeElement("return");
    prevElement->AppendChild(element);
    element = prevElement;
}

void ControlXmlGenerator::Visit(BoundGotoStatementNode& node)
{
    soul::xml::Element* prevElement = element;
    element = soul::xml::MakeElement("goto");
    prevElement->AppendChild(element);
    element = prevElement;
}

void ControlXmlGenerator::Visit(BoundLabeledStatementNode& node)
{
    soul::xml::Element* prevElement = element;
    element = soul::xml::MakeElement("labeled");
    node.Statement()->Accept(*this);
    prevElement->AppendChild(element);
    element = prevElement;
}

void ControlXmlGenerator::Visit(BoundConstructionStatementNode& node)
{
    soul::xml::Element* prevElement = element;
    element = soul::xml::MakeElement("construction");
    prevElement->AppendChild(element);
    element = prevElement;
}

void ControlXmlGenerator::Visit(BoundExpressionStatementNode& node)
{
    soul::xml::Element* prevElement = element;
    element = soul::xml::MakeElement("expression");
    prevElement->AppendChild(element);
    element = prevElement;
}

void ControlXmlGenerator::Visit(BoundSetVPtrStatementNode& node)
{
    soul::xml::Element* prevElement = element;
    element = soul::xml::MakeElement("vptr");
    prevElement->AppendChild(element);
    element = prevElement;
}

void ControlXmlGenerator::Visit(BoundAliasDeclarationStatementNode& node)
{
    soul::xml::Element* prevElement = element;
    element = soul::xml::MakeElement("alias");
    prevElement->AppendChild(element);
    element = prevElement;
}

void GenerateControlXml(BoundFunctionNode* fn)
{
    ControlXmlGenerator generator;
    fn->Accept(generator);
    std::unique_ptr<soul::xml::Element> element = generator.GetElement();
    util::CodeFormatter formatter(std::cout);
    formatter.SetIndentSize(1);
    element->Write(formatter);
}

} // namespace otava::symbols
