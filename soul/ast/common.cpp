// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.ast.common;

import util;

namespace soul::ast::common {

std::string ToNamespaceName(const std::string& qualifiedId)
{
    std::string namespaceName;
    std::vector<std::string> components = util::Split(qualifiedId, '.');
    bool first = true;
    for (const auto& component : components)
    {
        if (first)
        {
            first = false;
        }
        else
        {
            namespaceName.append("::");
        }
        namespaceName.append(component);
    }
    return namespaceName;
}

ExportModule::ExportModule(const std::string& moduleName_) : moduleName(moduleName_)
{
}

Import::Import(const std::string& moduleName_, ImportPrefix prefix_) : moduleName(moduleName_), prefix(prefix_)
{
}

File::File(FileKind kind_, const std::string& filePath_) : kind(kind_), filePath(filePath_), external(false)
{
}

File::~File()
{
}

void File::Accept(Visitor& visitor)
{
}

Collection::Collection(CollectionKind kind_, const std::string& name_) : kind(kind_), name(name_), file(nullptr)
{
}

Collection::~Collection()
{
}

Token::Token(std::int64_t id_, const std::string& name_, const std::string& info_) : id(id_), name(name_), info(info_), collection(nullptr)
{
}

Token::Token(const std::string& name_, const std::string& info_) : id(-1), name(name_), info(info_), collection(nullptr)
{
}

TokenCollection::TokenCollection(const std::string& name_) : Collection(CollectionKind::tokenCollection, name_), initialized(false), id(std::hash<std::string>()(Name()) & 0x7FFFFFFF)
{
}

void TokenCollection::AddToken(Token* token)
{
    if (token->Id() == -1)
    {
        std::int64_t tokenId = (std::int64_t(Id()) << 32) | (std::int64_t(tokens.size()) + 1);
        token->SetId(tokenId);
    }
    tokens.push_back(std::unique_ptr<Token>(token));
    tokenMap[token->Id()] = token;
    token->SetCollection(this);
}

Token* TokenCollection::GetToken(std::int64_t id) const
{
    auto it = tokenMap.find(id);
    if (it != tokenMap.cend())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}

TokenFile::TokenFile(const std::string& filePath_) : File(FileKind::tokenFile, filePath_)
{
}

void TokenFile::SetTokenCollection(TokenCollection* tokenCollection_)
{
    tokenCollection.reset(tokenCollection_);
    tokenCollection->SetFile(this);
}

void TokenFile::Accept(soul::ast::common::Visitor& visitor)
{
    visitor.Visit(*this);
}

Visitor::Visitor()
{
}

Visitor::~Visitor()
{
}

} // namespace soul::ast::common
