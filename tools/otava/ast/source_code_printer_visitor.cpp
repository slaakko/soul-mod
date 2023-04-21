// =================================
// Copyright (c) 2023 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.ast.source.code.printer.visitor;

import util.unicode;
import otava.ast.node;
import otava.ast.util;

namespace otava::ast {

SourceCodePrinterVisitor::SourceCodePrinterVisitor(std::ostream& stream) : formatter(stream), line(1), col(1)
{
}

void SourceCodePrinterVisitor::Move(const soul::ast::SourcePos& sourcePos)
{
    while (sourcePos.line > line)
    {
        formatter.WriteLine();
        ++line;
        col = 1;
    }
    if (sourcePos.col > col)
    {
        int n = sourcePos.col - col;
        formatter.Write(std::string(n, ' '));
        col += n;
    }
}

void SourceCodePrinterVisitor::Move(const std::u32string& str)
{
    for (char32_t c : str)
    {
        if (c == '\n')
        {
            ++line;
            col = 1;
        }
        else if (c == '\t')
        {
            col += 4;
        }
        else
        {
            ++col;
        }
    }
}

void SourceCodePrinterVisitor::Write(const std::string& str)
{
    formatter.Write(str);
    Move(util::ToUtf32(str));
}

void SourceCodePrinterVisitor::Write(const std::u32string& str)
{
    formatter.Write(util::ToUtf8(str));
    Move(str);
}

void SourceCodePrinterVisitor::BeginVisit(Node& node)
{
    Move(node.GetSourcePos());
}

void SourceCodePrinterVisitor::VisitIdentifier(const std::u32string& id, const soul::ast::SourcePos& sourcePos)
{
    Move(sourcePos);
    Write(ToUniversalId(id));
}

void SourceCodePrinterVisitor::VisitKeyword(const std::string& keyword, const soul::ast::SourcePos& sourcePos)
{
    Move(sourcePos);
    Write(keyword);
}

void SourceCodePrinterVisitor::VisitOperator(const std::string& symbol, const soul::ast::SourcePos& sourcePos)
{
    Move(sourcePos);
    Write(symbol);
}

void SourceCodePrinterVisitor::VisitToken(const std::u32string& tokenStr, const soul::ast::SourcePos& sourcePos)
{
    Move(sourcePos);
    Write(tokenStr);
}

void SourceCodePrinterVisitor::VisitLiteral(const std::u32string& rep, const soul::ast::SourcePos& sourcePos)
{
    Move(sourcePos);
    Write(rep);
}

void SourceCodePrinterVisitor::VisitHeaderName(const std::u32string& rep, const soul::ast::SourcePos& sourcePos)
{
    Move(sourcePos);
    Write(rep);
}

} // namespace otava::ast
