// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.intermediate.compile_unit;

import std;

export namespace otava::intermediate {

class Context;
class MetadataRef;

class CompileUnit
{
public:
    CompileUnit();
    Context* GetContext() const { return context; }
    void SetContext(Context* context_) { context = context_; }
    const std::string& FilePath() const { return filePath; }
    void SetFilePath(const std::string& filePath_);
    const std::string& Id() const { return id; }
    void SetInfo(const std::string& id_, MetadataRef* metadataRef_);
    MetadataRef* GetMetadataRef() const { return metadataRef; }
    void Write();
private:
    Context* context;
    std::string filePath;
    std::string id;
    MetadataRef* metadataRef;
};

} // otava::intermediate
