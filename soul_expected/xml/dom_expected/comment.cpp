// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul_expected.xml.comment;

import soul_expected.xml.visitor;

namespace soul_expected::xml {

Comment::Comment(const soul_expected::ast::SourcePos& sourcePos_) : CharacterData(NodeKind::commentNode, sourcePos_, "comment")
{
}

Comment::Comment(const soul_expected::ast::SourcePos& sourcePos_, const std::string& comment_) : CharacterData(NodeKind::commentNode, sourcePos_, "comment", comment_)
{
}

void Comment::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> Comment::Write(util::CodeFormatter& formatter)
{
    std::expected<bool, int> rv = formatter.Write("<!-- ");
    if (!rv) return rv;
    rv = formatter.Write(Data());
    if (!rv) return rv;
    return formatter.Write(" -->");
}

Comment* MakeComment(const std::string& comment)
{
    return new Comment(soul_expected::ast::SourcePos(), comment);
}

} // namespace soul_expected::xml
