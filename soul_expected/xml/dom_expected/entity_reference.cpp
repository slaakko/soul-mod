// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul_expected.xml.entity.reference;

import soul_expected.xml.visitor;

namespace soul_expected::xml {

EntityReference::EntityReference(const soul_expected::ast::SourcePos& sourcePos_) :
    CharacterData(NodeKind::entityReferenceNode, sourcePos_, "entity_reference")
{
}

EntityReference::EntityReference(const soul_expected::ast::SourcePos& sourcePos_, const std::string& entityRef_) :
    CharacterData(NodeKind::entityReferenceNode, sourcePos_, "entity_reference", entityRef_)
{
}

void EntityReference::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int>  EntityReference::Write(util::CodeFormatter& formatter)
{
    auto rv = formatter.Write("&");
    if (!rv) return rv;
    rv = formatter.Write(Data());
    if (!rv) return rv;
    return formatter.Write(";");
}

EntityReference* MakeEntityReference(const std::string& entityRef)
{
    return new EntityReference(soul_expected::ast::SourcePos(), entityRef);
}

} // namespace soul_expected::xml
