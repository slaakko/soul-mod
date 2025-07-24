// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul_expected.xml.text;

import std;
import soul_expected.xml.character.data;
import soul_expected.xml.node;

export namespace soul_expected::xml {

class Text : public CharacterData
{
public:
    Text(const soul_expected::ast::SourcePos& sourcePos_);
    Text(const soul_expected::ast::SourcePos& sourcePos_, const std::string& text_);
    Text(NodeKind kind_, const soul_expected::ast::SourcePos& sourcePos_, const std::string& name_);
    Text(NodeKind kind_, const soul_expected::ast::SourcePos& sourcePos_, const std::string& name_, const std::string& text_);
    void Accept(Visitor& visitor) override;
};

Text* MakeText(const std::string& text);

} // namespace soul_expected::xml
