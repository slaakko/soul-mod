// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.ast.source.code.printer.visitor;

import soul.cpp20.ast.visitor;
import util.code.formatter;

export namespace soul::cpp20::ast {

class SourceCodePrinterVisitor : public DefaultVisitor
{
public:
    SourceCodePrinterVisitor(std::ostream& stream);
    void BeginVisit(Node& node) override;
    void VisitIdentifier(const std::u32string& id, const soul::ast::SourcePos& sourcePos) override;
    void VisitKeyword(const std::string& keyword, const soul::ast::SourcePos& sourcePos) override;
    void VisitOperator(const std::string& symbol, const soul::ast::SourcePos& sourcePos) override;
    void VisitToken(const std::u32string& tokenStr, const soul::ast::SourcePos& sourcePos) override;
    void VisitLiteral(const std::u32string& rep, const soul::ast::SourcePos& sourcePos) override;
    void VisitHeaderName(const std::u32string& rep, const soul::ast::SourcePos& sourcePos) override;
private:
    void Move(const soul::ast::SourcePos& sourcePos);
    void Move(const std::u32string& str);
    void Write(const std::string& str);
    void Write(const std::u32string& str);
    util::CodeFormatter formatter;
    int line;
    int col;
};

} // namespace soul::cpp20::ast
