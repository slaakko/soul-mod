// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul_expected.xml.cdata.section;

import soul_expected.xml.visitor;

namespace soul_expected::xml {

CDataSection::CDataSection(const soul_expected::ast::SourcePos& sourcePos_) : Text(NodeKind::cdataSectionNode, sourcePos_, "cdata_section")
{
}

CDataSection::CDataSection(const soul_expected::ast::SourcePos& sourcePos_, const std::string& text_) : Text(NodeKind::cdataSectionNode, sourcePos_, "cdata_section", text_)
{
}

void CDataSection::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> CDataSection::Write(util::CodeFormatter& formatter)
{
    std::expected<bool, int> rv = formatter.Write("<![CDATA[");
    if (!rv) return rv;
    rv = formatter.Write(Data());
    if (!rv) return rv;
    return formatter.Write("]]>");
}

CDataSection* MakeCDataSection(const std::string& text)
{
    return new CDataSection(soul_expected::ast::SourcePos(), text);
}

} // namespace soul_expected::xml
