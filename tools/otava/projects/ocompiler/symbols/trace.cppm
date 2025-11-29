// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.trace;

import std;
import util;
import otava.ast;

export namespace otava::symbols {

class FunctionDefinitionSymbol;
class Context;

struct SourceFileInfo
{
    SourceFileInfo();
    SourceFileInfo(std::int32_t moduleId, std::int32_t sourceFileIndex, const std::string& sourceFilePath_);
    std::expected<bool, int> Write(util::BinaryStreamWriter& writer);
    std::expected<bool, int> Read(util::BinaryStreamReader& reader);
    std::int64_t sourceFileId;
    std::string sourceFilePath;
};

struct FunctionTraceInfo
{
    FunctionTraceInfo();
    FunctionTraceInfo(std::int64_t sourceFileId_, std::int32_t moduleId, std::int32_t functionIndex, const std::string& functionFullName_);
    std::expected<bool, int> Write(util::BinaryStreamWriter& writer);
    std::expected<bool, int> Read(util::BinaryStreamReader& reader);
    std::int64_t sourceFileId;
    std::int64_t functionId;
    std::string functionFullName;
};

class TraceInfo
{
public:
    TraceInfo();
    void AddSourceFileInfo(std::int32_t moduleId, const std::string& sourceFilePath);
    std::int64_t GetSourceFileId(const std::string& sourceFilePath) const;
    void AddFunctionTraceInfo(std::int64_t sourceFileId, std::int32_t moduleId, const std::string& functionFullName);
    int NumSourceFileInfos() const { return sourceFileInfos.size(); }
    std::int64_t GetFunctionId(const std::string& functionFullName) const;
    SourceFileInfo* ReleaseSourceFileInfo(int index);
    int NumFunctionTraceInfos() const { return functionTraceInfos.size(); }
    FunctionTraceInfo* ReleaseFunctionTraceInfo(int index);
    std::expected<bool, int> Write(util::BinaryStreamWriter& writer);
    std::expected<bool, int> Read(util::BinaryStreamReader& reader);
private:
    std::map<std::string, SourceFileInfo*> sourceFileInfoMap;
    std::vector<std::unique_ptr<SourceFileInfo>> sourceFileInfos;
    std::map<std::string, FunctionTraceInfo*> functionTraceInfoMap;
    std::vector<std::unique_ptr<FunctionTraceInfo>> functionTraceInfos;
};

class TraceBin
{
public:
    TraceBin();
    void Import(TraceInfo& traceInfo);
    std::expected<bool, int> Write(util::BinaryStreamWriter& writer);
    std::expected<bool, int> Read(util::BinaryStreamReader& reader);
    SourceFileInfo* GetSourceFileInfo(std::int64_t sourceFileId) const;
    FunctionTraceInfo* GetFunctionTraceInfo(std::int64_t functionId) const;
private:
    std::vector<std::unique_ptr<SourceFileInfo>> sourceFileInfos;
    std::map<std::int64_t, SourceFileInfo*> sourceFileInfosMap;
    std::vector<std::unique_ptr<FunctionTraceInfo>> functionTraceInfos;
    std::map<std::int64_t, FunctionTraceInfo*> functionTraceInfoMap;
};

std::expected<bool, int> WriteTraceBin(TraceBin& traceBin, const std::string& traceBinPath);

std::expected<bool, int> GenerateEnterFunctionCode(otava::ast::Node* functionDefinitionNode, FunctionDefinitionSymbol* fn, Context* context);

} // namespace otava::symbols
