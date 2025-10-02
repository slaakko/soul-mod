// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.xml.comment;

import soul.xml.visitor;

namespace soul::xml {

Comment::Comment(const soul::ast::SourcePos& sourcePos_) : CharacterData(NodeKind::commentNode, sourcePos_, "comment")
{
}

Comment::Comment(const soul::ast::SourcePos& sourcePos_, const std::string& comment_) : CharacterData(NodeKind::commentNode, sourcePos_, "comment", comment_)
{
}

void Comment::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> Comment::Write(util::CodeFormatter& formatter)
{
    formatter.Write("<!-- ");
    formatter.Write(Data());
    formatter.Write(" -->");
    return std::expected<bool, int>(true);
}

Comment* MakeComment(const std::string& comment)
{
    return new Comment(soul::ast::SourcePos(), comment);
}

} // namespace soul::xml
