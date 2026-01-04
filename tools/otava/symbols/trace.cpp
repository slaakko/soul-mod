// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.trace;

import otava.symbols.function.symbol;
import otava.symbols.context;
import otava.symbols.modules;
import otava.symbols.declaration;
import otava.symbols.statement.binder;
import otava.symbols.project;

namespace otava::symbols {

SourceFileInfo::SourceFileInfo() : sourceFileId(-1), sourceFilePath()
{
}

SourceFileInfo::SourceFileInfo(std::int32_t moduleId, std::int32_t sourceFileIndex, const std::string& sourceFilePath_) : 
    sourceFileId((std::int64_t(moduleId) << 32) | std::int64_t(sourceFileIndex)), sourceFilePath(sourceFilePath_)
{
}

void SourceFileInfo::Write(util::BinaryStreamWriter& writer)
{
    writer.Write(sourceFileId);
    writer.Write(sourceFilePath);
}

void SourceFileInfo::Read(util::BinaryStreamReader& reader)
{
    sourceFileId = reader.ReadLong();
    sourceFilePath = reader.ReadUtf8String();
}

FunctionTraceInfo::FunctionTraceInfo() : sourceFileId(-1), functionId(-1), functionFullName()
{
}

FunctionTraceInfo::FunctionTraceInfo(std::int64_t sourceFileId_, std::int32_t moduleId, std::int32_t functionIndex, const std::string& functionFullName_) :
    sourceFileId(sourceFileId_), functionId((std::int64_t(moduleId) << 32) | std::int64_t(functionIndex)), functionFullName(functionFullName_)
{
}

void FunctionTraceInfo::Write(util::BinaryStreamWriter& writer)
{
    writer.Write(sourceFileId);
    writer.Write(functionId);
    writer.Write(functionFullName);
}

void FunctionTraceInfo::Read(util::BinaryStreamReader& reader)
{
    sourceFileId = reader.ReadLong();
    functionId = reader.ReadLong();
    functionFullName = reader.ReadUtf8String();
}

TraceInfo::TraceInfo()
{
}

void TraceInfo::AddSourceFileInfo(std::int32_t moduleId, const std::string& sourceFilePath)
{
    auto it = sourceFileInfoMap.find(sourceFilePath);
    if (it == sourceFileInfoMap.end())
    {
        SourceFileInfo* sourceFileInfo = new SourceFileInfo(moduleId, sourceFileInfos.size(), sourceFilePath);
        sourceFileInfos.push_back(std::unique_ptr<SourceFileInfo>(sourceFileInfo));
        sourceFileInfoMap[sourceFilePath] = sourceFileInfo;
    }
}

std::int64_t TraceInfo::GetSourceFileId(const std::string& sourceFilePath) const
{
    auto it = sourceFileInfoMap.find(sourceFilePath);
    if (it != sourceFileInfoMap.end())
    {
        return it->second->sourceFileId;
    }
    else
    {
        return -1;
    }
}

void TraceInfo::AddFunctionTraceInfo(std::int64_t sourceFileId, std::int32_t moduleId, const std::string& functionFullName)
{
    auto it = functionTraceInfoMap.find(functionFullName);
    if (it == functionTraceInfoMap.end())
    {
        FunctionTraceInfo* functionTraceInfo = new FunctionTraceInfo(sourceFileId, moduleId, functionTraceInfos.size(), functionFullName);
        functionTraceInfos.push_back(std::unique_ptr<FunctionTraceInfo>(functionTraceInfo));
        functionTraceInfoMap[functionFullName] = functionTraceInfo;
    }
}

std::int64_t TraceInfo::GetFunctionId(const std::string& functionFullName) const
{
    auto it = functionTraceInfoMap.find(functionFullName);
    if (it != functionTraceInfoMap.end())
    {
        return it->second->functionId;
    }
    else
    {
        return -1;
    }
}

SourceFileInfo* TraceInfo::ReleaseSourceFileInfo(int index)
{
    return sourceFileInfos[index].release();
}

FunctionTraceInfo* TraceInfo::ReleaseFunctionTraceInfo(int index)
{
    return functionTraceInfos[index].release();
}

void TraceInfo::Write(util::BinaryStreamWriter& writer)
{
    writer.Write(static_cast<std::int32_t>(sourceFileInfos.size()));
    for (const auto& sourceFileInfo : sourceFileInfos)
    {
        sourceFileInfo->Write(writer);
    }
    writer.Write(static_cast<std::int32_t>(functionTraceInfos.size()));
    for (const auto& functionTraceInfo : functionTraceInfos)
    {
        functionTraceInfo->Write(writer);
    }
}

void TraceInfo::Read(util::BinaryStreamReader& reader)
{
    std::int32_t ns = reader.ReadInt();
    for (std::int32_t i = 0; i < ns; ++i)
    {
        SourceFileInfo* sourceFileInfo = new SourceFileInfo();
        sourceFileInfo->Read(reader);
        sourceFileInfos.push_back(std::unique_ptr<SourceFileInfo>(sourceFileInfo));
    }
    std::int32_t nf = reader.ReadInt();
    for (std::int32_t i = 0; i < nf; ++i)
    {
        FunctionTraceInfo* functionTraceInfo = new FunctionTraceInfo();
        functionTraceInfo->Read(reader);
        functionTraceInfos.push_back(std::unique_ptr<FunctionTraceInfo>(functionTraceInfo));
    }
}

TraceBin::TraceBin()
{
}

void TraceBin::Import(TraceInfo& traceInfo)
{
    int numSourceFileInfos = traceInfo.NumSourceFileInfos();
    for (int i = 0; i < numSourceFileInfos; ++i)
    {
        SourceFileInfo* sourceFileInfo = traceInfo.ReleaseSourceFileInfo(i);
        sourceFileInfos.push_back(std::unique_ptr<SourceFileInfo>(sourceFileInfo));
    }
    int numTraceInfos = traceInfo.NumFunctionTraceInfos();
    for (int i = 0; i < numTraceInfos; ++i)
    {
        FunctionTraceInfo* functionTraceInfo = traceInfo.ReleaseFunctionTraceInfo(i);
        functionTraceInfos.push_back(std::unique_ptr<FunctionTraceInfo>(functionTraceInfo));
    }
}

void TraceBin::Write(util::BinaryStreamWriter& writer)
{
    writer.Write(static_cast<std::int32_t>(sourceFileInfos.size()));
    for (const auto& sourceFileInfo : sourceFileInfos)
    {
        sourceFileInfo->Write(writer);
    }
    writer.Write(static_cast<std::int32_t>(functionTraceInfos.size()));
    for (const auto& functionTraceInfo : functionTraceInfos)
    {
        functionTraceInfo->Write(writer);
    }
}

void TraceBin::Read(util::BinaryStreamReader& reader)
{
    std::int32_t ns = reader.ReadInt();
    for (std::int32_t i = 0; i < ns; ++i)
    {
        SourceFileInfo* sourceFileInfo = new SourceFileInfo();
        sourceFileInfo->Read(reader);
        sourceFileInfos.push_back(std::unique_ptr<SourceFileInfo>(sourceFileInfo));
        sourceFileInfosMap[sourceFileInfo->sourceFileId] = sourceFileInfo;
    }
    std::int32_t nf = reader.ReadInt();
    for (std::int32_t i = 0; i < nf; ++i)
    {
        FunctionTraceInfo* functionTraceInfo = new FunctionTraceInfo();
        functionTraceInfo->Read(reader);
        functionTraceInfos.push_back(std::unique_ptr<FunctionTraceInfo>(functionTraceInfo));
        functionTraceInfoMap[functionTraceInfo->functionId] = functionTraceInfo;
    }
}

SourceFileInfo* TraceBin::GetSourceFileInfo(std::int64_t sourceFileId) const
{
    auto it = sourceFileInfosMap.find(sourceFileId);
    if (it != sourceFileInfosMap.end())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}

FunctionTraceInfo* TraceBin::GetFunctionTraceInfo(std::int64_t functionId) const
{
    auto it = functionTraceInfoMap.find(functionId);
    if (it != functionTraceInfoMap.end())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}

void WriteTraceBin(TraceBin& traceBin, const std::string& traceBinPath)
{
    util::FileStream file(traceBinPath, util::OpenMode::write | util::OpenMode::binary);
    util::BufferedStream bufStream(file);
    util::BinaryStreamWriter writer(bufStream);
    traceBin.Write(writer);
}

void GenerateEnterFunctionCode(otava::ast::Node* functionDefinitionNode, FunctionDefinitionSymbol* fn, Context* context)
{
    if (context->ReleaseConfig() && !(context->CurrentProject() && context->CurrentProject()->HasDefine("TRACE"))) return;
    if (!context->GetTraceInfo()) return;
    if (fn->ParentFn()) return; // child functions do not have enter function code
    Module* module = context->GetModule();
    if (module->Name() == "std.trace" ||
        module->Name() == "std.trace.cpp" ||
        module->Name() == "std.type.fundamental" ||
        module->Name() == "std.rt" ||
        module->Name() == "std.basic_string")
    {
        return;
    }
    if (context->ReleaseConfig() && fn->IsInline()) return;
    std::int64_t fnId = context->GetTraceInfo()->GetFunctionId(util::ToUtf8(fn->FullName()));
    if (fnId != -1)
    {
        if (functionDefinitionNode->IsFunctionDefinitionNode())
        {
            otava::ast::FunctionDefinitionNode* fndefNode = static_cast<otava::ast::FunctionDefinitionNode*>(functionDefinitionNode);
            if (fndefNode->FunctionBody())
            {
                otava::ast::FunctionBodyNode* body = static_cast<otava::ast::FunctionBodyNode*>(fndefNode->FunctionBody());
                if (body->Child()->IsCompoundStatementNode())
                {
                    otava::ast::CompoundStatementNode* compoundStatement = static_cast<otava::ast::CompoundStatementNode*>(body->Child());
                    otava::ast::DeclSpecifierSequenceNode* entryDeclSpecifiers = new otava::ast::DeclSpecifierSequenceNode(soul::ast::SourcePos());
                    otava::ast::NestedNameSpecifierNode* entryNns = new otava::ast::NestedNameSpecifierNode(soul::ast::SourcePos());
                    entryNns->AddNode(new otava::ast::IdentifierNode(soul::ast::SourcePos(), U"std"));
                    entryNns->AddNode(new otava::ast::ColonColonNode(soul::ast::SourcePos()));
                    otava::ast::IdentifierNode* entryId = new otava::ast::IdentifierNode(soul::ast::SourcePos(), U"trace_entry");
                    otava::ast::QualifiedIdNode* entrQualifiedId = new otava::ast::QualifiedIdNode(soul::ast::SourcePos(), entryNns, entryId);
                    entryDeclSpecifiers->AddNode(entrQualifiedId);
                    otava::ast::IdentifierNode* entryDeclaratorId = new otava::ast::IdentifierNode(soul::ast::SourcePos(), U"@entry");
                    otava::ast::IntegerLiteralNode* fnIdNode = new otava::ast::IntegerLiteralNode(soul::ast::SourcePos(),
                        static_cast<std::uint64_t>(fnId), otava::ast::Suffix::ll, otava::ast::Base::decimal, util::ToUtf32(std::to_string(fnId)));
                    otava::ast::InitDeclaratorNode* entryInitDeclarator = new otava::ast::InitDeclaratorNode(soul::ast::SourcePos(), entryDeclaratorId, fnIdNode);
                    otava::ast::InitDeclaratorListNode* entryInitDeclaratorList = new otava::ast::InitDeclaratorListNode(soul::ast::SourcePos());
                    entryInitDeclaratorList->AddNode(entryInitDeclarator);
                    otava::ast::SimpleDeclarationNode* entrySimpleDeclarationNode = new otava::ast::SimpleDeclarationNode(soul::ast::SourcePos(),
                        entryDeclSpecifiers, entryInitDeclaratorList, nullptr, nullptr);
                    otava::ast::DeclarationStatementNode* entryStatementNode = new otava::ast::DeclarationStatementNode(soul::ast::SourcePos(), entrySimpleDeclarationNode);
                    context->GetSymbolTable()->BeginScope(fn->GetScope());
                    Symbol* block = context->GetSymbolTable()->GetSymbolNothrow(compoundStatement);
                    context->GetSymbolTable()->BeginScope(block->GetScope());
                    context->PushSetFlag(ContextFlags::saveDeclarations);
                    otava::symbols::ProcessSimpleDeclaration(entrySimpleDeclarationNode, nullptr, context);
                    context->PopFlags();
                    compoundStatement->InsertNode(0, entryStatementNode);
                    context->GetSymbolTable()->EndScope();
                    otava::ast::DeclSpecifierSequenceNode* guardDeclSpecifiers = new otava::ast::DeclSpecifierSequenceNode(soul::ast::SourcePos());
                    otava::ast::NestedNameSpecifierNode* guardNns = new otava::ast::NestedNameSpecifierNode(soul::ast::SourcePos());
                    guardNns->AddNode(new otava::ast::IdentifierNode(soul::ast::SourcePos(), U"std"));
                    guardNns->AddNode(new otava::ast::ColonColonNode(soul::ast::SourcePos()));
                    otava::ast::IdentifierNode* guardId = new otava::ast::IdentifierNode(soul::ast::SourcePos(), U"trace_guard");
                    otava::ast::QualifiedIdNode* guardQualifiedId = new otava::ast::QualifiedIdNode(soul::ast::SourcePos(), guardNns, guardId);
                    guardDeclSpecifiers->AddNode(guardQualifiedId);
                    otava::ast::IdentifierNode* guardDeclaratorId = new otava::ast::IdentifierNode(soul::ast::SourcePos(), U"@guard");
                    otava::ast::IdentifierNode* entryIdNode = new otava::ast::IdentifierNode(soul::ast::SourcePos(), U"@entry");
                    otava::ast::UnaryExprNode* entryNode = new otava::ast::UnaryExprNode(soul::ast::SourcePos(),
                        new otava::ast::AddrOfNode(soul::ast::SourcePos()), entryIdNode);
                    otava::ast::InitDeclaratorNode* guardInitDeclarator = new otava::ast::InitDeclaratorNode(soul::ast::SourcePos(), guardDeclaratorId, entryNode);
                    otava::ast::InitDeclaratorListNode* guardInitDeclaratorList = new otava::ast::InitDeclaratorListNode(soul::ast::SourcePos());
                    guardInitDeclaratorList->AddNode(guardInitDeclarator);
                    otava::ast::SimpleDeclarationNode* guardSimpleDeclarationNode = new otava::ast::SimpleDeclarationNode(soul::ast::SourcePos(),
                        guardDeclSpecifiers, guardInitDeclaratorList, nullptr, nullptr);
                    otava::ast::DeclarationStatementNode* guardStatementNode = new otava::ast::DeclarationStatementNode(soul::ast::SourcePos(), guardSimpleDeclarationNode);
                    Symbol* guardBlock = context->GetSymbolTable()->GetSymbolNothrow(compoundStatement);
                    context->GetSymbolTable()->BeginScope(guardBlock->GetScope());
                    context->PushSetFlag(ContextFlags::saveDeclarations);
                    otava::symbols::ProcessSimpleDeclaration(guardSimpleDeclarationNode, nullptr, context);
                    context->PopFlags();
                    compoundStatement->InsertNode(1, guardStatementNode);
                    context->GetSymbolTable()->EndScope();
                    context->GetSymbolTable()->EndScope();

                    otava::ast::MemberExprNode* memberExprNode = new otava::ast::MemberExprNode(soul::ast::SourcePos(),
                        new otava::ast::IdentifierNode(soul::ast::SourcePos(), U"@entry"),
                        new otava::ast::DotNode(soul::ast::SourcePos()),
                        new otava::ast::IdentifierNode(soul::ast::SourcePos(), U"line"));
                    otava::ast::IntegerLiteralNode* lineNumberNode = new otava::ast::IntegerLiteralNode(
                        soul::ast::SourcePos(), 0, otava::ast::Suffix::none, otava::ast::Base::decimal, U"0");
                    otava::ast::BinaryExprNode* setLineNode = new otava::ast::BinaryExprNode(soul::ast::SourcePos(),
                        new otava::ast::AssignNode(soul::ast::SourcePos()), memberExprNode, lineNumberNode);
                    otava::ast::ExpressionStatementNode* setLineStatement = new otava::ast::ExpressionStatementNode(soul::ast::SourcePos(), setLineNode, nullptr, nullptr);
                    context->GetBoundFunction()->SetSetLineStatementNode(setLineStatement);
                }
            }
        }
    }
}

} // namespace otava::symbols
