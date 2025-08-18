// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.intermediate.metadata;

import otava.intermediate.data;
import util;
import soul.ast.span;
import std;

export namespace otava::intermediate {

export namespace metadata {}

class MetadataStruct;
class Context;

enum class MetadataItemKind
{
    metadataRef, metadataBool, metadataLong, metadataString, metadataStruct
};

const std::int64_t fileInfoNodeType = 0;
const std::int64_t funcInfoNodeType = 1;
const std::int64_t lineInfoNodeType = 2;

class MetadataItem
{
public:
    MetadataItem(MetadataItemKind kind_);
    virtual ~MetadataItem();
    inline MetadataItemKind Kind() const { return kind; }
    inline bool IsMetadataRef() const { return kind == MetadataItemKind::metadataRef; }
    inline bool IsMetadataBool() const { return kind == MetadataItemKind::metadataBool; }
    inline bool IsMetadataLong() const { return kind == MetadataItemKind::metadataLong; }
    inline bool IsMetadataString() const { return kind == MetadataItemKind::metadataString; }
    virtual void Write(util::CodeFormatter& formatter) = 0;
private:
    MetadataItemKind kind;
};

class MetadataRef : public MetadataItem
{
public:
    MetadataRef(const soul::ast::Span& span_, std::int32_t nodeId_);
    inline const soul::ast::Span& GetSpan() const { return span; }
    inline std::int32_t NodeId() const { return nodeId; }
    inline MetadataStruct* GetMetadataStruct() const { return metadataStruct; }
    inline void SetMetadataStruct(MetadataStruct* metadataStruct_) { metadataStruct = metadataStruct_; }
    void Write(util::CodeFormatter& formatter) override;
private:
    soul::ast::Span span;
    std::int32_t nodeId;
    MetadataStruct* metadataStruct;
};

class MetadataBool : public MetadataItem
{
public:
    MetadataBool(bool value_);
    inline bool Value() const { return value; }
    void Write(util::CodeFormatter& formatter) override;
private:
    bool value;
};

class MetadataLong : public MetadataItem
{
public:
    MetadataLong(std::int64_t value_);
    inline std::int64_t Value() const { return value; }
    void Write(util::CodeFormatter& formatter) override;
private:
    std::int64_t value;
};

class MetadataString : public MetadataItem
{
public:
    MetadataString(const std::string& value_);
    inline const std::string& Value() const { return value; }
    void Write(util::CodeFormatter& formatter) override;
private:
    std::string value;
};

class MetadataStruct : public MetadataItem
{
public:
    MetadataStruct(const soul::ast::Span& span_, std::int32_t id_);
    MetadataStruct(const MetadataStruct&) = delete;
    MetadataStruct& operator=(const MetadataStruct&) = delete;
    inline const soul::ast::Span& GetSpan() const { return span; }
    inline std::int32_t Id() const { return id; }
    void AddItem(const std::string& fieldName, MetadataItem* item);
    MetadataItem* GetItem(const std::string& fieldName) const;
    void Write(util::CodeFormatter& formatter) override;
    void WriteDefinition(util::CodeFormatter& formatter);
private:
    soul::ast::Span span;
    std::int32_t id;
    std::map<std::string, MetadataItem*> itemMap;
};

class Metadata
{
public:
    Metadata();
    Metadata(const Metadata&) = delete;
    Metadata& operator=(const Metadata&) = delete;
    inline Context* GetContext() const { return context; }
    inline void SetContext(Context* context_) { context = context_; }
    MetadataStruct* CreateMetadataStruct();
    MetadataStruct* GetMetadataStruct(std::int32_t id) const;
    MetadataStruct* AddMetadataStruct(const soul::ast::Span& span, std::int32_t id);
    MetadataBool* CreateMetadataBool(bool value);
    MetadataLong* CreateMetadataLong(std::int64_t value);
    MetadataString* CreateMetadataString(const std::string& value, bool crop);
    MetadataRef* CreateMetadataRef(const soul::ast::Span& span, std::int32_t nodeId);
    void ResolveMetadataReferences();
    void Write(util::CodeFormatter& formatter);
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
};

} // otava::intermediate
