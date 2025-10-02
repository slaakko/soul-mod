// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.xml.cdata.section;

import soul.xml.visitor;

namespace soul::xml {

CDataSection::CDataSection(const soul::ast::SourcePos& sourcePos_) : Text(NodeKind::cdataSectionNode, sourcePos_, "cdata_section")
{
}

CDataSection::CDataSection(const soul::ast::SourcePos& sourcePos_, const std::string& text_) : Text(NodeKind::cdataSectionNode, sourcePos_, "cdata_section", text_)
{
}

void CDataSection::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> CDataSection::Write(util::CodeFormatter& formatter)
{
    formatter.Write("<![CDATA[");
    formatter.Write(Data());
    formatter.Write("]]>");
    return std::expected<bool, int>(true);
}

CDataSection* MakeCDataSection(const std::string& text)
{
    return new CDataSection(soul::ast::SourcePos(), text);
}

} // namespace soul::xml
