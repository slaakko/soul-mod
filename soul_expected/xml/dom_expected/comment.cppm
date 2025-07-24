// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul_expected.xml.comment;

import std;
import soul_expected.xml.character.data;

export namespace soul_expected::xml {

class Comment : public CharacterData
{
public:
    Comment(const soul_expected::ast::SourcePos& sourcePos_);
    Comment(const soul_expected::ast::SourcePos& sourcePos_, const std::string& comment_);
    void Accept(Visitor& visitor) override;
    std::expected<bool, int> Write(util::CodeFormatter& formatter) override;
};

Comment* MakeComment(const std::string& comment);

} // namespace soul_expected::xml
