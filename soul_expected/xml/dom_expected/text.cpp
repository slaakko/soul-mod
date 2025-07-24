// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul_expected.xml.text;

import soul_expected.xml.visitor;

namespace soul_expected::xml {

Text::Text(const soul_expected::ast::SourcePos& sourcePos_) : CharacterData(NodeKind::textNode, sourcePos_, "text")
{
}

Text::Text(const soul_expected::ast::SourcePos& sourcePos_, const std::string& text_) : CharacterData(NodeKind::textNode, sourcePos_, "text", text_)
{
}

Text::Text(NodeKind kind_, const soul_expected::ast::SourcePos& sourcePos_, const std::string& name_) : CharacterData(kind_, sourcePos_, name_)
{
}

Text::Text(NodeKind kind_, const soul_expected::ast::SourcePos& sourcePos_, const std::string& name_, const std::string& text_) : CharacterData(kind_, sourcePos_, name_, text_)
{
}

void Text::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

Text* MakeText(const std::string& text)
{
    return new Text(soul_expected::ast::SourcePos(), text);
}

} // namespace soul_expected::xml
