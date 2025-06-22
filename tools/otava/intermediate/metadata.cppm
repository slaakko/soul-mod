// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.intermediate.metadata;

import std.core;
import util.code.formatter;
import soul.ast.source.pos;

export namespace otava::intermediate::metadata {}

export namespace otava::intermediate {

using SourcePos = soul::ast::SourcePos;

class MetadataStruct;
class Context;

enum class MetadataItemKind
{
    metadataRef, metadataBool, metadataLong, metadataString
};

const std::int64_t fileInfoNodeType = 0;
const std::int64_t funcInfoNodeType = 1;
const std::int64_t lineInfoNodeType = 2;
const std::int64_t beginTryNodeType = 3;
const std::int64_t endTryNodeType = 4;
const std::int64_t catchNodeType = 5;
const std::int64_t beginCleanupNodeType = 6;
const std::int64_t endCleanupNodeType = 7;


class MetadataItem
{
public:
    MetadataItem(MetadataItemKind kind_);
    virtual ~MetadataItem();
    virtual void Write(util::CodeFormatter& formatter) = 0;
    MetadataItemKind Kind() const { return kind; }
private:
    MetadataItemKind kind;
};

class MetadataRef : public MetadataItem
{
public:
    MetadataRef(const SourcePos& sourcePos_, std::int32_t nodeId_);
    const SourcePos& GetSourcePos() const { return sourcePos; }
    std::int32_t NodeId() const { return nodeId; }
    MetadataStruct* GetMetadataStruct() const { return metadataStruct; }
    void SetMetadataStruct(MetadataStruct* metadataStruct_) { metadataStruct = metadataStruct_; }
    void Write(util::CodeFormatter& formatter) override;
private:
    SourcePos sourcePos;
    std::int32_t nodeId;
    MetadataStruct* metadataStruct;
};

class MetadataBool : public MetadataItem
{
public:
    MetadataBool(bool value_);
    bool Value() const { return value; }
    void Write(util::CodeFormatter& formatter) override;
private:
    bool value;
};

class MetadataLong : public MetadataItem
{
public:
    MetadataLong(std::int64_t value_);
    std::int64_t Value() const { return value; }
    void Write(util::CodeFormatter& formatter) override;
private:
    std::int64_t value;
};

class MetadataString : public MetadataItem
{
public:
    MetadataString(const std::string& value_);
    const std::string& Value() const { return value; }
    void Write(util::CodeFormatter& formatter) override;
private:
    std::string value;
};

class MetadataStruct
{
public:
    MetadataStruct(const SourcePos& sourcePos_, std::int32_t id_);
    MetadataStruct(const MetadataStruct&) = delete;
    MetadataStruct& operator=(const MetadataStruct&) = delete;
    const SourcePos& GetSourcePos() const { return sourcePos; }
    std::int32_t Id() const { return id; }
    void AddItem(const std::string& fieldName, MetadataItem* item);
    MetadataItem* GetItem(const std::string& fieldName) const;
    void Write(util::CodeFormatter& formatter);
private:
    SourcePos sourcePos;
    std::int32_t id;
    std::map<std::string, MetadataItem*> itemMap;
};

class Metadata
{
public:
    Metadata();
    void Write(util::CodeFormatter& formatter);
    Context* GetContext() const { return context; }
    void SetContext(Context* context_) { context = context_; }
    MetadataStruct* GetMetadataStruct(std::int32_t id) const;
    MetadataStruct* AddMetadataStruct(const SourcePos& sourcePos, std::int32_t id, Context* context);
    MetadataStruct* CreateMetadataStruct(Context* context);
    MetadataBool* CreateMetadataBool(bool value);
    MetadataLong* CreateMetadataLong(std::int64_t value);
    MetadataString* CreateMetadataString(const std::string& value);
    MetadataRef* CreateMetadataRef(const SourcePos& sourcePos, std::int32_t nodeId);
    void ResolveMetadataReferences(Context* context);
private:
    Context* context;
    std::vector<std::unique_ptr<MetadataStruct>> metadataNodes;
    std::vector<std::unique_ptr<MetadataItem>> metadataItems;
    std::map<std::int32_t, MetadataStruct*> metadataMap;
    MetadataBool* trueItem;
    MetadataBool* falseItem;
    std::map<std::int64_t, MetadataLong*> longItemMap;
    std::map<std::string, MetadataString*> stringItemMap;
    std::map<std::int32_t, MetadataRef*> referenceMap;
    std::vector<MetadataRef*> metadataReferences;
    std::int32_t nextNodeId;
};

} // otava::intermediate
