// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.ast.xml.generator.visitor;

import std.core;
import soul.cpp20.ast.visitor;
import soul.xml.element;

export namespace soul::cpp20::ast {

class XmlGeneratorVisitor : public DefaultVisitor
{
public:
    std::unique_ptr<soul::xml::Element> GetElement() { return std::move(element); }
    void BeginVisit(Node& node) override;
    void EndVisit(Node& node) override;
    void VisitIdentifier(const std::u32string& id, const soul::ast::SourcePos& sourcePos) override;
    void VisitKeyword(const std::string& keyword, const soul::ast::SourcePos& sourcePos) override;
    void VisitOperator(const std::string& symbol, const soul::ast::SourcePos& sourcePos) override;
    void VisitToken(const std::u32string& tokenStr, const soul::ast::SourcePos& sourcePos) override;
    void VisitLiteral(const std::u32string& rep, const soul::ast::SourcePos& sourcePos) override;
    void VisitHeaderName(const std::u32string& rep, const soul::ast::SourcePos& sourcePos) override;
    void AddAttribute(const std::string& name, const std::string& value);
    void AddElement(soul::xml::Element* child);
private:
    std::unique_ptr<soul::xml::Element> element;
    std::stack<std::unique_ptr<soul::xml::Element>> stack;
};

} // namespace soul::cpp20::ast
