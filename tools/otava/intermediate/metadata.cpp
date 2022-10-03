// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.intermediate.metadata;

import otava.intermediate.error;
import util.text.util;

namespace otava::intermediate {

MetadataRef::MetadataRef(const SourcePos& sourcePos_, int32_t nodeId_) : MetadataItem(MetadataItemKind::metadataRef), sourcePos(sourcePos_), nodeId(nodeId_), metadataStruct(nullptr)
{
}

void MetadataRef::Write(util::CodeFormatter& formatter)
{
    formatter.Write("!" + std::to_string(nodeId));
}

MetadataItem::MetadataItem(MetadataItemKind kind_) : kind(kind_)
{
}

MetadataItem::~MetadataItem()
{
}

MetadataBool::MetadataBool(bool value_) : MetadataItem(MetadataItemKind::metadataBool), value(value_)
{
}

void MetadataBool::Write(util::CodeFormatter& formatter)
{
    if (value)
    {
        formatter.Write("true");
    }
    else
    {
        formatter.Write("false");
    }
}

MetadataLong::MetadataLong(int64_t value_) : MetadataItem(MetadataItemKind::metadataLong), value(value_)
{
}

void MetadataLong::Write(util::CodeFormatter& formatter)
{
    formatter.Write(std::to_string(value));
}

MetadataString::MetadataString(const std::string& value_) : MetadataItem(MetadataItemKind::metadataString), value(value_)
{
}

void MetadataString::Write(util::CodeFormatter& formatter)
{
    formatter.Write("\"");
    formatter.Write(util::StringStr(value));
    formatter.Write("\"");
}

MetadataStruct::MetadataStruct(const SourcePos& sourcePos_, int32_t id_) : sourcePos(sourcePos_), id(id_)
{
}

void MetadataStruct::Write(util::CodeFormatter& formatter)
{
    formatter.Write("!" + std::to_string(id) + " = {");
    bool first = true;
    for (const auto& item : itemMap)
    {
        if (first)
        {
            first = false;
        }
        else
        {
            formatter.Write(", ");
        }
        formatter.Write(item.first);
        formatter.Write(": ");
        item.second->Write(formatter);
    }
    formatter.WriteLine("}");
}

void MetadataStruct::AddItem(const std::string& fieldName, MetadataItem* item)
{
    itemMap[fieldName] = item;
}

MetadataItem* MetadataStruct::GetItem(const std::string& fieldName) const
{
    auto it = itemMap.find(fieldName);
    if (it != itemMap.cend())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}

Metadata::Metadata() : context(nullptr), trueItem(), falseItem()
{
}

void Metadata::Write(util::CodeFormatter& formatter)
{
    if (metadataNodes.empty()) return;
    formatter.WriteLine();
    formatter.WriteLine("metadata");
    formatter.WriteLine("{");
    formatter.IncIndent();
    for (const auto& s : metadataNodes)
    {
        s->Write(formatter);
    }
    formatter.DecIndent();
    formatter.WriteLine("}");
}

MetadataStruct* Metadata::GetMetadataStruct(int32_t id) const
{
    auto it = metadataMap.find(id);
    if (it != metadataMap.cend())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}

MetadataStruct* Metadata::AddMetadataStruct(const SourcePos& sourcePos, int32_t id, Context* context)
{
    MetadataStruct* prev = GetMetadataStruct(id);
    if (prev)
    {
        Error("error adding metadata node: node id " + std::to_string(id) + " not unique", sourcePos, context, prev->GetSourcePos());
    }
    MetadataStruct* metadataStruct = new MetadataStruct(sourcePos, id);
    metadataNodes.push_back(std::unique_ptr<MetadataStruct>(metadataStruct));
    metadataMap[metadataStruct->Id()] = metadataStruct;
    return metadataStruct;
}

MetadataStruct* Metadata::CreateMetadataStruct(Context* context)
{
    return AddMetadataStruct(SourcePos(), nextNodeId++, context);
}

MetadataBool* Metadata::CreateMetadataBool(bool value)
{
    if (value)
    {
        if (!trueItem)
        {
            trueItem = new MetadataBool(true);
            metadataItems.push_back(std::unique_ptr<MetadataItem>(trueItem));
        }
        return trueItem;
    }
    else
    {
        if (!falseItem)
        {
            falseItem = new MetadataBool(false);
            metadataItems.push_back(std::unique_ptr<MetadataItem>(falseItem));
        }
        return falseItem;
    }
}

MetadataLong* Metadata::CreateMetadataLong(int64_t value)
{
    auto it = longItemMap.find(value);
    if (it != longItemMap.cend())
    {
        return it->second;
    }
    else
    {
        MetadataLong* metadataLong = new MetadataLong(value);
        metadataItems.push_back(std::unique_ptr<MetadataItem>(metadataLong));
        longItemMap[value] = metadataLong;
        return metadataLong;
    }
}

MetadataString* Metadata::CreateMetadataString(const std::string& value)
{
    auto it = stringItemMap.find(value);
    if (it != stringItemMap.cend())
    {
        return it->second;
    }
    else
    {
        MetadataString* metadataString = new MetadataString(value);
        metadataItems.push_back(std::unique_ptr<MetadataItem>(metadataString));
        stringItemMap[value] = metadataString;
        return metadataString;
    }
}

MetadataRef* Metadata::CreateMetadataRef(const SourcePos& sourcePos, int32_t nodeId)
{
    auto it = referenceMap.find(nodeId);
    if (it != referenceMap.cend())
    {
        return it->second;
    }
    else
    {
        MetadataRef* metadataRef = new MetadataRef(sourcePos, nodeId);
        referenceMap[metadataRef->NodeId()] = metadataRef;
        metadataItems.push_back(std::unique_ptr<MetadataItem>(metadataRef));
        metadataReferences.push_back(metadataRef);
        return metadataRef;
    }
}

void Metadata::ResolveMetadataReferences(Context* context)
{
    for (MetadataRef* metadataRef : metadataReferences)
    {
        int32_t nodeId = metadataRef->NodeId();
        MetadataStruct* metadataNode = GetMetadataStruct(nodeId);
        if (metadataNode)
        {
            metadataRef->SetMetadataStruct(metadataNode);
        }
        else
        {
            Error("error resolving metadata reference: node id " + std::to_string(nodeId) + " not found", metadataRef->GetSourcePos(), context);
        }
    }
}

} // otava::intermediate
