// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul_expected.xml.entity.reference;

import std;
import soul_expected.xml.character.data;

export namespace soul_expected::xml {

class EntityReference : public CharacterData
{
public:
    EntityReference(const soul_expected::ast::SourcePos& sourcePos_);
    EntityReference(const soul_expected::ast::SourcePos& sourcePos_, const std::string& entityRef_);
    void Accept(Visitor& visitor) override;
    std::expected<bool, int> Write(util::CodeFormatter& formatter) override;
};

EntityReference* MakeEntityReference(const std::string& entityRef);

} // namespace soul_expected::xml
