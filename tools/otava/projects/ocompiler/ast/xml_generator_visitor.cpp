// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.ast.xml.generator.visitor;

import otava.ast.node;
import util.unicode;
import soul.ast.source.pos;

namespace otava::ast {

void XmlGeneratorVisitor::BeginVisit(Node& node)
{
    if (!Valid()) return;
    stack.push(std::move(element));
    element.reset(soul::xml::MakeElement(NodeKindStr(node.Kind())));
    AddAttribute("type", NodeTypeStr(node.Type()));
    AddAttribute("pos", soul::ast::ToString(node.GetSourcePos()));
    int n = node.Count();
    if (n != 0)
    {
        AddAttribute("count", std::to_string(n));
    }
}

void XmlGeneratorVisitor::EndVisit(Node& node)
{
    if (!Valid()) return;
    std::unique_ptr<soul::xml::Element> parent = std::move(stack.top());
    stack.pop();
    if (parent)
    {
        std::expected<bool, int> rv = parent->AppendChild(element.release());
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        element.reset(parent.release());
    }
}

void XmlGeneratorVisitor::VisitIdentifier(const std::u32string& id, const soul::ast::SourcePos& sourcePos)
{
    if (!Valid()) return;
    std::unique_ptr<soul::xml::Element> idElement(soul::xml::MakeElement("identifier"));
    std::expected<std::string, int> rv = util::ToUtf8(id);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    idElement->SetAttribute("value", *rv);
    idElement->SetAttribute("pos", soul::ast::ToString(sourcePos));
    AddElement(idElement.release());
}

void XmlGeneratorVisitor::VisitKeyword(const std::string& keyword, const soul::ast::SourcePos& sourcePos)
{
    if (!Valid()) return;
    std::unique_ptr<soul::xml::Element> kwElement(soul::xml::MakeElement("keyword"));
    kwElement->SetAttribute("value", keyword);
    kwElement->SetAttribute("pos", soul::ast::ToString(sourcePos));
    AddElement(kwElement.release());
}

void XmlGeneratorVisitor::VisitOperator(const std::string& symbol, const soul::ast::SourcePos& sourcePos)
{
    if (!Valid()) return;
    std::unique_ptr<soul::xml::Element> opElement(soul::xml::MakeElement("operator"));
    opElement->SetAttribute("value", symbol);
    opElement->SetAttribute("pos", soul::ast::ToString(sourcePos));
    AddElement(opElement.release());
}

void XmlGeneratorVisitor::VisitToken(const std::u32string& tokenStr, const soul::ast::SourcePos& sourcePos)
{
    if (!Valid()) return;
    std::unique_ptr<soul::xml::Element> tokenElement(soul::xml::MakeElement("token"));
    std::expected<std::string, int> rv = util::ToUtf8(tokenStr);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    tokenElement->SetAttribute("value", *rv);
    tokenElement->SetAttribute("pos", soul::ast::ToString(sourcePos));
    AddElement(tokenElement.release());
}

void XmlGeneratorVisitor::VisitLiteral(const std::u32string& rep, const soul::ast::SourcePos& sourcePos)
{
    if (!Valid()) return;
    std::unique_ptr<soul::xml::Element> literalElement(soul::xml::MakeElement("literal"));
    std::expected<std::string, int> rv = util::ToUtf8(rep);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    literalElement->SetAttribute("value", *rv);
    literalElement->SetAttribute("pos", soul::ast::ToString(sourcePos));
    AddElement(literalElement.release());
}

void XmlGeneratorVisitor::VisitHeaderName(const std::u32string& rep, const soul::ast::SourcePos& sourcePos)
{
    if (!Valid()) return;
    std::unique_ptr<soul::xml::Element> headerElement(soul::xml::MakeElement("header"));
    std::expected<std::string, int> rv = util::ToUtf8(rep);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    headerElement->SetAttribute("value", *rv);
    headerElement->SetAttribute("pos", soul::ast::ToString(sourcePos));
    AddElement(headerElement.release());
}

void XmlGeneratorVisitor::AddAttribute(const std::string& name, const std::string& value)
{
    element->SetAttribute(name, value);
}

void XmlGeneratorVisitor::AddElement(soul::xml::Element* child)
{
    std::expected<bool, int> rv = element->AppendChild(child);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

} // namespace otava::ast
