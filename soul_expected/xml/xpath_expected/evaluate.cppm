// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul_expected.xml.xpath.evaluate;

import std;
import soul_expected.xml.dom_expected;
import soul_expected.xml.xpath.object;
import soul_expected.xml.xpath.expr;
import soul_expected.xml.node;

export namespace soul_expected::xml::xpath {

std::expected<std::unique_ptr<soul_expected::xml::xpath::expr::Expr>, int> ParseXPathExpr(const std::string& xpathExpr);
std::expected<std::unique_ptr<soul_expected::xml::xpath::Object>, int> Evaluate(soul_expected::xml::xpath::expr::Expr* expr, soul_expected::xml::Node* node);
std::expected<std::unique_ptr<soul_expected::xml::xpath::Object>, int> Evaluate(const std::string& xpathExpr, soul_expected::xml::Node* node);
std::expected<std::unique_ptr<soul_expected::xml::xpath::NodeSet>, int> EvaluateToNodeSet(soul_expected::xml::xpath::expr::Expr* expr, soul_expected::xml::Node* node);
std::expected<std::unique_ptr<soul_expected::xml::xpath::NodeSet>, int> EvaluateToNodeSet(const std::string& xpathExpr, soul_expected::xml::Node* node);
std::expected<std::unique_ptr<soul_expected::xml::Document>, int> EvaluateToXMLInfoDocument(soul_expected::xml::xpath::expr::Expr* expr, soul_expected::xml::Node* node);
std::expected<std::unique_ptr<soul_expected::xml::Document>, int> EvaluateToXMLInfoDocument(const std::string& xpathExpr, soul_expected::xml::Node* node);
std::expected<std::unique_ptr<soul_expected::xml::Document>, int> EvaluateToXMLInfoDocument(const std::string& xpathExpr, const std::string& xmlFileName);

} // namespace soul_expected::xml::xpath
