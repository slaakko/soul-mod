// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.ast.xml.generator.visitor;

import soul.cpp20.ast.node;
import util.unicode;

namespace soul::cpp20::ast {

void XmlGeneratorVisitor::BeginVisit(Node& node)
{
    stack.push(std::move(element));
    element.reset(soul::xml::MakeElement(NodeKindStr(node.Kind())));
    AddAttribute("type", NodeTypeStr(node.Type()));
    AddAttribute("pos", ToString(node.GetSourcePos()));
    int n = node.Count();
    if (n != 0)
    {
        AddAttribute("count", std::to_string(n));
    }
}

void XmlGeneratorVisitor::EndVisit(Node& node)
{
    std::unique_ptr<soul::xml::Element> parent = std::move(stack.top());
    stack.pop();
    if (parent)
    {
        parent->AppendChild(element.release());
        element.reset(parent.release());
    }
}

void XmlGeneratorVisitor::VisitIdentifier(const std::u32string& id, const soul::ast::SourcePos& sourcePos)
{
    std::unique_ptr<soul::xml::Element> idElement(soul::xml::MakeElement("identifier"));
    idElement->SetAttribute("value", util::ToUtf8(id));
    idElement->SetAttribute("pos", ToString(sourcePos));
    AddElement(idElement.release());
}

void XmlGeneratorVisitor::VisitKeyword(const std::string& keyword, const soul::ast::SourcePos& sourcePos)
{
    std::unique_ptr<soul::xml::Element> kwElement(soul::xml::MakeElement("keyword"));
    kwElement->SetAttribute("value", keyword);
    kwElement->SetAttribute("pos", ToString(sourcePos));
    AddElement(kwElement.release());
}

void XmlGeneratorVisitor::VisitOperator(const std::string& symbol, const soul::ast::SourcePos& sourcePos)
{
    std::unique_ptr<soul::xml::Element> opElement(soul::xml::MakeElement("operator"));
    opElement->SetAttribute("value", symbol);
    opElement->SetAttribute("pos", ToString(sourcePos));
    AddElement(opElement.release());
}

void XmlGeneratorVisitor::VisitToken(const std::u32string& tokenStr, const soul::ast::SourcePos& sourcePos)
{
    std::unique_ptr<soul::xml::Element> tokenElement(soul::xml::MakeElement("token"));
    tokenElement->SetAttribute("value", util::ToUtf8(tokenStr));
    tokenElement->SetAttribute("pos", ToString(sourcePos));
    AddElement(tokenElement.release());
}

void XmlGeneratorVisitor::VisitLiteral(const std::u32string& rep, const soul::ast::SourcePos& sourcePos)
{
    std::unique_ptr<soul::xml::Element> literalElement(soul::xml::MakeElement("literal"));
    literalElement->SetAttribute("value", util::ToUtf8(rep));
    literalElement->SetAttribute("pos", ToString(sourcePos));
    AddElement(literalElement.release());
}

void XmlGeneratorVisitor::VisitHeaderName(const std::u32string& rep, const soul::ast::SourcePos& sourcePos)
{
    std::unique_ptr<soul::xml::Element> headerElement(soul::xml::MakeElement("header"));
    headerElement->SetAttribute("value", util::ToUtf8(rep));
    headerElement->SetAttribute("pos", ToString(sourcePos));
    AddElement(headerElement.release());
}

void XmlGeneratorVisitor::AddAttribute(const std::string& name, const std::string& value)
{
    element->SetAttribute(name, value);
}

void XmlGeneratorVisitor::AddElement(soul::xml::Element* child)
{
    element->AppendChild(child);
}

} // namespace soul::cpp20::ast
