// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul_expected.xml.xpath.evaluate;

import util_expected;
import soul_expected.xml.xpath.lexer;
import soul_expected.xml.xpath.expr;
import soul_expected.xml.xpath.parser;
import soul_expected.xml.xpath.context;
import soul_expected.xml.xpath.parser.rules;
import soul_expected.xml.dom_expected;
import soul_expected.xml.dom.parser;

namespace soul_expected::xml::xpath {

std::expected<std::unique_ptr<soul_expected::xml::xpath::expr::Expr>, int> ParseXPathExpr(const std::string& xpathExpr)
{
    auto u = util::ToUtf32(xpathExpr);
    if (!u) return std::unexpected<int>(u.error());
    std::u32string u32expr = *u;
    auto rv = soul_expected::xml::xpath::lexer::MakeLexer(u32expr.c_str(), u32expr.c_str() + u32expr.length(), "xpath expression");
    if (!rv) return std::unexpected<int>(rv.error());
    auto lexer = std::move(*rv);
    lexer.SetRuleNameMapPtr(soul_expected::xml::xpath::parser::rules::GetRuleNameMapPtr());
    using LexerType = decltype(lexer);
    std::expected<std::unique_ptr<soul_expected::xml::xpath::expr::Expr>, int> p = soul_expected::xml::xpath::parser::XPathParser<LexerType>::Parse(lexer);
    if (!p) return std::unexpected<int>(p.error());
    std::unique_ptr<soul_expected::xml::xpath::expr::Expr> expr = std::move(*p);
    expr->SetStr(xpathExpr);
    return expr;
}

std::expected<std::unique_ptr<soul_expected::xml::xpath::Object>, int> Evaluate(soul_expected::xml::xpath::expr::Expr* expr, soul_expected::xml::Node* node)
{
    Context context(node, 1, 1);
    return expr->Evaluate(context);
}

std::expected<std::unique_ptr<soul_expected::xml::xpath::Object>, int>  Evaluate(const std::string& xpathExpr, soul_expected::xml::Node* node)
{
    auto p = ParseXPathExpr(xpathExpr);
    if (!p) return std::unexpected<int>(p.error());
    std::unique_ptr<soul_expected::xml::xpath::expr::Expr> expr = std::move(*p);
    return Evaluate(expr.get(), node);
}

std::expected<std::unique_ptr<soul_expected::xml::xpath::NodeSet>, int> EvaluateToNodeSet(soul_expected::xml::xpath::expr::Expr* expr, soul_expected::xml::Node* node)
{
    auto r = Evaluate(expr, node);
    if (!r) return std::unexpected<int>(r.error());
    std::unique_ptr<soul_expected::xml::xpath::Object> result = std::move(*r);
    if (result->IsNodeSet())
    {
        return std::unique_ptr<soul_expected::xml::xpath::NodeSet>(static_cast<soul_expected::xml::xpath::NodeSet*>(result.release()));
    }
    else
    {
        return std::unexpected<int>(util::AllocateError("node-set result expected"));
    }
}

std::expected<std::unique_ptr<soul_expected::xml::xpath::NodeSet>, int> EvaluateToNodeSet(const std::string& xpathExpr, soul_expected::xml::Node* node)
{
    auto p = ParseXPathExpr(xpathExpr);
    if (!p) return std::unexpected<int>(p.error());
    std::unique_ptr<soul_expected::xml::xpath::expr::Expr> expr = std::move(*p);
    return EvaluateToNodeSet(expr.get(), node);
}

std::expected<std::unique_ptr<soul_expected::xml::Document>, int> EvaluateToXMLInfoDocument(soul_expected::xml::xpath::expr::Expr* expr, const std::string& parsingError,
    soul_expected::xml::Node* node, const std::string& xmlFileName)
{
    std::unique_ptr<soul_expected::xml::Document> infoDoc = soul_expected::xml::MakeDocument();
    soul_expected::xml::Element* xpathElement = soul_expected::xml::MakeElement("xpath");
    auto rv = infoDoc->AppendChild(xpathElement);
    if (!rv) return std::unexpected<int>(rv.error());
    if (expr)
    {
        soul_expected::xml::Element* exprElement = soul_expected::xml::MakeElement("expr-string");
        exprElement->SetAttribute("value", expr->Str());
        rv = xpathElement->AppendChild(exprElement);
        if (!rv) return std::unexpected<int>(rv.error());
    }
    if (!xmlFileName.empty())
    {
        soul_expected::xml::Element* xmlFileNameElement = soul_expected::xml::MakeElement("xmlFileName");
        xmlFileNameElement->SetAttribute("value", xmlFileName);
        rv = xpathElement->AppendChild(xmlFileNameElement);
        if (!rv) return std::unexpected<int>(rv.error());
    }
    soul_expected::xml::Element* resultElement = soul_expected::xml::MakeElement("result");
    if (expr)
    {
        auto e = expr->ToXmlElement();
        if (!e) return std::unexpected<int>(e.error());
        rv = xpathElement->AppendChild(*e);
        if (!rv) return std::unexpected<int>(rv.error());
        auto p = Evaluate(expr, node);
        if (p)
        {
            std::unique_ptr<soul_expected::xml::xpath::Object> result = std::move(*p);
            e = result->ToXmlElement();
            if (!e) return std::unexpected<int>(e.error());
            rv = resultElement->AppendChild(*e);
            if (!rv) return std::unexpected<int>(rv.error());
        }
        else
        {
            soul_expected::xml::Element* errorElement = soul_expected::xml::MakeElement("error");
            errorElement->SetAttribute("value", util::GetErrorMessage(e.error()));
            rv = resultElement->AppendChild(errorElement);
            if (!rv) return std::unexpected<int>(rv.error());
        }
    }
    else if (!parsingError.empty())
    {
        soul_expected::xml::Element* errorElement = soul_expected::xml::MakeElement("error");
        errorElement->SetAttribute("value", parsingError);
        rv = resultElement->AppendChild(errorElement);
        if (!rv) return std::unexpected<int>(rv.error());
    }
    rv = xpathElement->AppendChild(resultElement);
    if (!rv) return std::unexpected<int>(rv.error());
    return infoDoc;
}

std::expected<std::unique_ptr<soul_expected::xml::Document>, int> EvaluateToXMLInfoDocument(soul_expected::xml::xpath::expr::Expr* expr, soul_expected::xml::Node* node, const std::string& xmlFileName)
{
    return EvaluateToXMLInfoDocument(expr, std::string(), node, xmlFileName);
}

std::expected<std::unique_ptr<soul_expected::xml::Document>, int> EvaluateToXMLInfoDocument(soul_expected::xml::xpath::expr::Expr* expr, soul_expected::xml::Node* node)
{
    return EvaluateToXMLInfoDocument(expr, node, std::string());
}

std::expected<std::unique_ptr<soul_expected::xml::Document>, int>  EvaluateToXMLInfoDocument(const std::string& xpathExpr, soul_expected::xml::Node* node, const std::string& xmlFileName)
{
    std::unique_ptr<soul_expected::xml::xpath::expr::Expr> expr;
    std::string parsingError;
    auto e = ParseXPathExpr(xpathExpr);
    if (!e)
    {
        parsingError = util::GetErrorMessage(e.error());
    }
    else
    {
        expr = std::move(*e);
    }
    return EvaluateToXMLInfoDocument(expr.get(), parsingError, node, xmlFileName);
}

std::expected<std::unique_ptr<soul_expected::xml::Document>, int>  EvaluateToXMLInfoDocument(const std::string& xpathExpr, soul_expected::xml::Node* node)
{
    return EvaluateToXMLInfoDocument(xpathExpr, node, std::string());
}

std::expected<std::unique_ptr<soul_expected::xml::Document>, int>  EvaluateToXMLInfoDocument(const std::string& xpathExpr, const std::string& xmlFileName)
{
    auto x = soul_expected::xml::ParseXmlFile(xmlFileName);
    if (!x) return std::unexpected<int>(x.error());
    std::unique_ptr<soul_expected::xml::Document> doc = std::move(*x);
    return EvaluateToXMLInfoDocument(xpathExpr, doc.get(), xmlFileName);
}

} // namespace soul_expected::xml::xpath

