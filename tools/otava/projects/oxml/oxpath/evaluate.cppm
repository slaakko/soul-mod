// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.xml.xpath.evaluate;

import std;
import soul.xml.dom;
import soul.xml.xpath.object;
import soul.xml.xpath.expr;
import soul.xml.node;

export namespace soul::xml::xpath {

std::expected<std::unique_ptr<soul::xml::xpath::expr::Expr>, int> ParseXPathExpr(const std::string& xpathExpr);
std::expected<std::unique_ptr<soul::xml::xpath::Object>, int> Evaluate(soul::xml::xpath::expr::Expr* expr, soul::xml::Node* node);
std::expected<std::unique_ptr<soul::xml::xpath::Object>, int> Evaluate(const std::string& xpathExpr, soul::xml::Node* node);
std::expected<std::unique_ptr<soul::xml::xpath::NodeSet>, int> EvaluateToNodeSet(soul::xml::xpath::expr::Expr* expr, soul::xml::Node* node);
std::expected<std::unique_ptr<soul::xml::xpath::NodeSet>, int> EvaluateToNodeSet(const std::string& xpathExpr, soul::xml::Node* node);
std::expected<std::unique_ptr<soul::xml::Document>, int> EvaluateToXMLInfoDocument(soul::xml::xpath::expr::Expr* expr, soul::xml::Node* node);
std::expected<std::unique_ptr<soul::xml::Document>, int> EvaluateToXMLInfoDocument(const std::string& xpathExpr, soul::xml::Node* node);
std::expected<std::unique_ptr<soul::xml::Document>, int> EvaluateToXMLInfoDocument(const std::string& xpathExpr, const std::string& xmlFileName);

} // namespace soul::xml::xpath
