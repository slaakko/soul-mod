// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.xml.comment;

import std;
import soul.xml.character.data;

export namespace soul::xml {

class Comment : public CharacterData
{
public:
    Comment(const soul::ast::SourcePos& sourcePos_);
    Comment(const soul::ast::SourcePos& sourcePos_, const std::string& comment_);
    void Accept(Visitor& visitor) override;
    void Write(util::CodeFormatter& formatter) override;
};

Comment* MakeComment(const std::string& comment);

} // namespace soul::xml
