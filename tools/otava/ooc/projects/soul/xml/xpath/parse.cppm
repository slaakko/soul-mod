// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.xml.xpath.parse;

import std;
import soul.xml.xpath.expr;

export namespace soul::xml::xpath {

std::unique_ptr<soul::xml::xpath::expr::Expr> TryParseXPathExpr(const std::string& xpathExpr, std::string& parsingError);

} // namespace soul::xml::xpath
