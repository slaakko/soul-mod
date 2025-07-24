// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul_expected.xml.cdata.section;

import std;
import soul_expected.xml.text;

export namespace soul_expected::xml {

class CDataSection : public Text
{
public:
    CDataSection(const soul_expected::ast::SourcePos& sourcePos_);
    CDataSection(const soul_expected::ast::SourcePos& sourcePos_, const std::string& text_);
    void Accept(Visitor& visitor) override;
    std::expected<bool, int> Write(util::CodeFormatter& formatter) override;
};

CDataSection* MakeCDataSection(const std::string& text);

} // namespace soul_expected::xml
