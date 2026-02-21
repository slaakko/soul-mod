// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.context;

import std;
import soul.lexer.base;
import soul.lexer.file.map;
import soul.ast.source.pos;
import otava.ast.node;
import otava.ast.function;
import otava.intermediate.data;
import otava.symbols.exception_handling;
import otava.symbols.instantiation_queue;
import otava.symbols.function_definition_symbol_set;
import otava.symbols.templates;
import otava.symbols.template_param_compare;
import otava.symbols.trace;
import otava.symbols.declaration;
import otava.symbols.operation.repository;
import otava.symbols.function.templates;
import otava.symbols.alias.type.symbol;
import util.uuid;

export namespace otava::symbols {

using Lexer = soul::lexer::LexerBase<char32_t>;

struct DeclarationList;

enum class ContextFlags : std::int64_t
{
    none = static_cast<std::int64_t>(0),
    hasDefiningTypeSpecifier = static_cast<std::int64_t>(1) << 0,
    friendSpecifier = static_cast<std::int64_t>(1) << 1,
    parsingParameters = static_cast<std::int64_t>(1) << 2,
    parsingConceptDefinition = static_cast<std::int64_t>(1) << 3,
    parsingTemplateId = static_cast<std::int64_t>(1) << 4,
    assumeType = static_cast<std::int64_t>(1) << 5,
    parseSavedMemberFunctionBody = static_cast<std::int64_t>(1) << 6,
    parsingTemplateDeclaration = static_cast<std::int64_t>(1) << 7,
    parseMemberFunction = static_cast<std::int64_t>(1) << 8,
    retMemberDeclSpecifiers = static_cast<std::int64_t>(1) << 9,
    addClassScope = static_cast<std::int64_t>(1) << 10,
    saveDeclarations = static_cast<std::int64_t>(1) << 11,
    linkageDeclaration = static_cast<std::int64_t>(1) << 12,
    instantiateFunctionTemplate = static_cast<std::int64_t>(1) << 13,
    instantiateAliasTypeTemplate = static_cast<std::int64_t>(1) << 14,
    instantiateMemFnOfClassTemplate = static_cast<std::int64_t>(1) << 15,
    instantiateInlineFunction = static_cast<std::int64_t>(1) << 16,
    dontBind = static_cast<std::int64_t>(1) << 17,
    parseSavedCtorInitializer = static_cast<std::int64_t>(1) << 18,
    skipFunctionDefinitions = static_cast<std::int64_t>(1) << 19,
    returnRef = static_cast<std::int64_t>(1) << 20,
    virtualSeen = static_cast<std::int64_t>(1) << 21,
    ignoreClassTemplateSpecializations = static_cast<std::int64_t>(1) << 22,
    generateMainWrapper = static_cast<std::int64_t>(1) << 23,
    noDynamicInit = static_cast<std::int64_t>(1) << 24,
    requireForwardResolved = static_cast<std::int64_t>(1) << 25,
    noPtrOps = static_cast<std::int64_t>(1) << 26,
    reinterpretCast = static_cast<std::int64_t>(1) << 27,
    derefAfterConv = static_cast<std::int64_t>(1) << 28,
    generatingVTab = static_cast<std::int64_t>(1) << 29,
    resolveNestedTypes = static_cast<std::int64_t>(1) << 30,
    release = static_cast<std::int64_t>(1) << 31,
    suppress_warning = static_cast<std::int64_t>(1) << 32,
    resolveDependentTypes = static_cast<std::int64_t>(1) << 33,
    processingAliasDeclation = static_cast<std::int64_t>(1) << 34,
    leaveBoundFunction = static_cast<std::int64_t>(1) << 35,
    skipFirstPtrToBooleanConversion = static_cast<std::int64_t>(1) << 36,
    matchClassGroup = static_cast<std::int64_t>(1) << 37,
    skipNonstaticMemberFunctions = static_cast<std::int64_t>(1) << 38,
    skipInvokeChecking = static_cast<std::int64_t>(1) << 39,
    dontProcess = static_cast<std::int64_t>(1) << 40,
    makeChildFn = static_cast<std::int64_t>(1) << 41,
    invoke = static_cast<std::int64_t>(1) << 42,
    tryCatch = static_cast<std::int64_t>(1) << 43,
    makeCompileUnitInitFn = static_cast<std::int64_t>(1) << 44,
    cast = static_cast<std::int64_t>(1) << 45,
    expected = static_cast<std::int64_t>(1) << 46,
    lookupOnlyFromMemberScope = static_cast<std::int64_t>(1) << 47,
    setParentBlockIds = static_cast<std::int64_t>(1) << 48
};

constexpr ContextFlags operator|(ContextFlags left, ContextFlags right) noexcept
{
    return ContextFlags(std::int64_t(left) | std::int64_t(right));
}

constexpr ContextFlags operator&(ContextFlags left, ContextFlags right) noexcept
{
    return ContextFlags(std::int64_t(left) & std::int64_t(right));
}

constexpr ContextFlags operator~(ContextFlags flags) noexcept
{
    return ContextFlags(~std::int64_t(flags));
}

class SymbolTable;
class Module;
class EvaluationContext;
class BoundCompileUnitNode;
class BoundExpressionNode;
class BoundFunctionNode;
class BoundCompoundStatementNode;
class OperationRepository;
class FunctionDefinitionSymbol;
class AliasTypeSymbol;
class TypeSymbol;
class ClassTemplateSpecializationSymbol;
class Emitter;
class Project;
class StatementBinder;

int GetOptLevel(int level, bool release) noexcept;

struct RangeForBlockIds
{
    RangeForBlockIds();
    int compoundBlockId;
    int forActionStatementId;
    int forStatementId;
};

class Context
{
public:
    Context();
    Lexer* GetLexer() noexcept { return lexer; }
    void SetLexer(Lexer* lexer_) noexcept;
    SymbolTable* GetSymbolTable() noexcept { return symbolTable; }
    void SetSymbolTable(SymbolTable* symbolTable_) noexcept;
    Module* GetModule() noexcept;
    inline TraceInfo* GetTraceInfo() const noexcept { return traceInfo; }
    inline void SetTraceInfo(TraceInfo* traceInfo_) noexcept { traceInfo = traceInfo_; }
    void SetFunctionDefinitionSymbolSet(FunctionDefinitionSymbolSet* functionDefinitionSymbolSet_) noexcept;
    FunctionDefinitionSymbolSet* GetFunctionDefinitionSymbolSet() const noexcept;
    inline BoundCompileUnitNode* GetBoundCompileUnit() const noexcept { return boundCompileUnit.get(); }
    OperationRepository* GetOperationRepository() const noexcept;
    inline BoundFunctionNode* GetBoundFunction() const noexcept { return boundFunction.get(); }
    inline BoundFunctionNode* ReleaseBoundFunction() noexcept { return boundFunction.release(); }
    void PushBoundFunction(BoundFunctionNode* boundFunction_);
    void PopBoundFunction();
    BoundExpressionNode* GetThisPtr(const soul::ast::SourcePos& sourcePos);
    EvaluationContext* GetEvaluationContext() noexcept;
    std::string FileName() const;
    void SetFileName(const std::string& fileName_);
    void PushFlags();
    void PopFlags();
    void ResetFlags() noexcept;
    void PushSetFlag(ContextFlags flag);
    void PushResetFlag(ContextFlags flag);
    inline void SetFlag(ContextFlags flag) noexcept { flags = flags | flag; }
    inline bool GetFlag(ContextFlags flag) const noexcept { return (flags & flag) != ContextFlags::none; }
    inline void ResetFlag(ContextFlags flag) noexcept { flags = flags & ~flag; }
    inline bool ReleaseConfig() const noexcept { return GetFlag(ContextFlags::release); }
    inline void SetReleaseConfig() noexcept { SetFlag(ContextFlags::release); }
    int OptLevel() const noexcept;
    inline void SetOptLevel(int optLevel_) noexcept { optLevel = optLevel_; }
    bool IsConstructorNameNode(otava::ast::Node* node) const noexcept;
    bool EnableNoDeclSpecFunctionDeclaration() const noexcept;
    bool EnableNoDeclSpecFunctionDefinition() const noexcept;
    void PushNode(otava::ast::Node* node_);
    void PopNode();
    inline otava::ast::Node* GetNode() const noexcept { return node; }
    void SetDeclarationList(otava::ast::Node* node, DeclarationList* declarations);
    std::unique_ptr<DeclarationList> ReleaseDeclarationList(otava::ast::Node* node);
    inline soul::lexer::FileMap* GetFileMap() const noexcept { return fileMap; }
    inline void SetFileMap(soul::lexer::FileMap* fileMap_) noexcept { fileMap = fileMap_; }
    inline void SetAliasType(AliasTypeSymbol* aliasType_) noexcept { aliasType = aliasType_; }
    inline AliasTypeSymbol* GetAliasType() const noexcept { return aliasType; }
    inline void SetPtr(otava::intermediate::Value* ptr_) noexcept { ptr = ptr_; }
    inline otava::intermediate::Value* Ptr() const noexcept { return ptr; }
    inline int MemFunDefSymbolIndex() const noexcept { return memFunDefSymbolIndex; }
    inline void SetMemFunDefSymbolIndex(int index) noexcept { memFunDefSymbolIndex = index; }
    inline void ResetRejectTemplateId() noexcept { rejectTemplateId = false; }
    inline void SetRejectTemplateId() noexcept { rejectTemplateId = true; }
    inline bool RejectTemplateId() const noexcept { return rejectTemplateId; }
    void PushSwitchCondType(TypeSymbol* switchCondType_);
    void PopSwitchCondType();
    inline TypeSymbol* GetSwitchCondType() const noexcept { return switchCondType; }
    void SetInstantiationQueue(InstantiationQueue* instantiationQueue_) noexcept;
    inline InstantiationQueue* GetInstantiationQueue() noexcept { return instantiationQueue; }
    void AddTemporaryAliasType(AliasTypeSymbol* temporaryAliasType);
    inline const std::vector<AliasTypeSymbol*>& TemporaryAliasTypes() const noexcept { return temporaryAliasTypes; }
    void ClearTemporaryAliasTypes();
    inline void SetDeclaredInitializerType(TypeSymbol* type) noexcept { declaredInitializerType = type; }
    inline TypeSymbol* DeclaredInitializerType() const noexcept { return declaredInitializerType; }
    FunctionSymbol* GetSpecialization(otava::ast::Node* functionNode) const noexcept;
    void SetSpecialization(FunctionSymbol* specialization, otava::ast::Node* functionNode);
    void RemoveSpecialization(otava::ast::Node* functionNode);
    ClassTemplateSpecializationSymbol* GetClassTemplateSpecialization(otava::ast::Node* functionNode) const noexcept;
    void SetClassTemplateSpecialization(otava::ast::Node* functionNode, ClassTemplateSpecializationSymbol* sp);
    void RemoveClassTemplateSpecialization(otava::ast::Node* functionNode);
    void SetInstantiationIrName(const std::string& instantiationIrName_);
    inline const std::string& InstantiationIrName() const noexcept { return instantiationIrName; }
    void AddBoundVTabFunction(BoundFunctionNode* node);
    inline const std::vector<std::unique_ptr<BoundFunctionNode>>& BoundVTabFunctions() const noexcept { return boundVTabFunctions; }
    void ClearBoundVTabFunctions();
    void PushTemplateParameterMap(std::map<TemplateParameterSymbol*, TypeSymbol*, TemplateParamLess>* templateParamMap);
    void PopTemplateParameterMap();
    inline std::map<TemplateParameterSymbol*, TypeSymbol*, TemplateParamLess>* TemplateParameterMap() const noexcept { return templateParameterMap; }
    inline void SetSourcePos(const soul::ast::SourcePos& sourcePos_) noexcept { sourcePos = sourcePos_; }
    inline const soul::ast::SourcePos& GetSourcePos() const noexcept { return sourcePos; }
    inline TypeSymbol* ArgType() noexcept { return argType; }
    inline void SetArgType(TypeSymbol* argType_) noexcept { argType = argType_; }
    inline TypeSymbol* ParamType() noexcept { return paramType; }
    inline void SetParamType(TypeSymbol* paramType_) noexcept { paramType = paramType_; }
    inline int TotalFunctionsCompiled() const noexcept { return totalFunctionsCompiled; }
    inline int FunctionCallsInlined() const noexcept { return functionCallsInlined; }
    inline int FunctionsInlined() const noexcept { return functionsInlined; }
    inline void SetTotalFunctionsCompiled(int totalFunctionsCompiled_) noexcept { totalFunctionsCompiled = totalFunctionsCompiled_; }
    inline void SetFunctionCallsInlined(int functionCallsInlined_) noexcept { functionCallsInlined = functionCallsInlined_; }
    inline void SetFunctionsInlined(int functionsInlined_) noexcept { functionsInlined = functionsInlined_; }
    inline int Invokes() const noexcept { return invokes; }
    inline void IncInvokes() noexcept { ++invokes; }
    inline void SetInvokes(int invokes_) noexcept { invokes = invokes_; }
    inline Emitter* GetEmitter() noexcept { return emitter; }
    inline void SetEmitter(Emitter* emitter_) noexcept { emitter = emitter_; }
    inline int ArgIndex() const noexcept { return argIndex; }
    void SetArgIndex(int argIndex_) noexcept { argIndex = argIndex_; }
    inline void SetRequesterModule(Module* requesterModule_) noexcept { requesterModule = requesterModule_; }
    inline Module* GetRequesterModule() const noexcept { return requesterModule; }
    Project* CurrentProject() const noexcept { return currentProject; }
    inline void SetCurrentProject(Project* project) noexcept { currentProject = project; }
    inline int NextTrySerial() noexcept { return trySerial++; }
    inline int NextInvokeSerial() noexcept { return invokeSerial++; }
    inline int NextCleanupSerial() noexcept { return cleanupSerial++; }
    inline int NextResultSerial() noexcept { return resultSerial++; }
    inline int NextLabelSerial() noexcept { return labelSerial++; }
    inline int NextEhReturnFromSerial() noexcept { return ehReturnFromSerial++; }
    inline int NextChildControlResultSerial() noexcept { return childControlResultSerial++; }
    inline int NextConditionVariableSerial() noexcept { return conditionVariableSerial++; }
    void PushStatementBinder(StatementBinder* statementBinder_);
    void PopStatementBinder();
    inline StatementBinder* GetStatementBinder() const noexcept { return statementBinder; }
    StatementBinder* GetParentStatementBinder() const noexcept;
    const std::u32string& ResultVarName() const { return resultVariableName; }
    void PushResultVarName(const std::u32string& resultVarName_);
    void PopResultVarName();
    const std::u32string& ChildControlResultVarName() const { return childControlResultVariableName; }
    void PushChildControlResultVarName(const std::u32string& childControlResultVarName);
    void PopChildControlResultVarName();
    std::u32string NextResultVarName();
    std::u32string NextEhReturnFromVarName();
    std::u32string NextChildControlResultVarName();
    std::u32string NextConditionVariableName();
    inline int NextBlockId() noexcept { return nextBlockId++; }
    inline int CurrentBlockId() const noexcept { return currentBlockId; }
    void PushBlockId(int blockId);
    void PopBlockId();
    FunctionDefinitionSymbol* ParentFn() const noexcept { return parentFn; }
    void PushParentFn(FunctionDefinitionSymbol* parentFn_);
    void PopParentFn();
    inline int ParentBlockId() const noexcept { return parentBlockId; }
    void PushParentBlockId(int blockId);
    void PopParentBlockId();
    RangeForBlockIds& GetRangeForBlockIds(const util::uuid& rangeForId);
private:
    Lexer* lexer;
    SymbolTable* symbolTable;
    TraceInfo* traceInfo;
    Emitter* emitter;
    Project* currentProject;
    std::unique_ptr<BoundCompileUnitNode> boundCompileUnit;
    std::unique_ptr<BoundFunctionNode> boundFunction;
    std::stack<std::unique_ptr<BoundFunctionNode>> boundFunctionStack;
    std::vector<std::unique_ptr<BoundFunctionNode>> boundVTabFunctions;
    ContextFlags flags;
    std::stack<ContextFlags> flagStack;
    int optLevel;
    std::stack<otava::ast::Node*> nodeStack;
    otava::ast::Node* node;
    std::map<otava::ast::Node*, std::unique_ptr<DeclarationList>> declarationMap;
    soul::lexer::FileMap* fileMap;
    otava::ast::Node* functionNode;
    std::map<otava::ast::Node*, FunctionSymbol*> specializationMap;
    std::map<otava::ast::Node*, ClassTemplateSpecializationSymbol*> classTemplateSpecializationMap;
    AliasTypeSymbol* aliasType;
    otava::intermediate::Value* ptr;
    int memFunDefSymbolIndex;
    std::string fileName;
    bool rejectTemplateId;
    TypeSymbol* switchCondType;
    std::stack<TypeSymbol*> switchCondTypeStack;
    InstantiationQueue* instantiationQueue;
    std::vector<AliasTypeSymbol*> temporaryAliasTypes;
    TypeSymbol* declaredInitializerType;
    std::string instantiationIrName;
    FunctionDefinitionSymbolSet* functionDefinitionSymbolSet;
    std::stack< std::map<TemplateParameterSymbol*, TypeSymbol*, TemplateParamLess>*> templateParameterMapStack;
    std::map<TemplateParameterSymbol*, TypeSymbol*, TemplateParamLess>* templateParameterMap;
    soul::ast::SourcePos sourcePos;
    TypeSymbol* argType;
    TypeSymbol* paramType;
    int totalFunctionsCompiled;
    int functionCallsInlined;
    int functionsInlined;
    int invokes;
    int argIndex;
    int boundFunctionSerial;
    int trySerial;
    int invokeSerial;
    int cleanupSerial;
    int resultSerial;
    int labelSerial;
    int ehReturnFromSerial;
    int childControlResultSerial;
    int conditionVariableSerial;
    Module* requesterModule;
    std::vector<StatementBinder*> statementBinders;
    StatementBinder* statementBinder;
    std::u32string resultVariableName;
    std::stack<std::u32string> resultVariableNameStack;
    std::u32string childControlResultVariableName;
    std::stack<std::u32string> childControlResultVariableNameStack;
    int nextBlockId;
    std::stack<int> blockIdStack;
    int currentBlockId;
    FunctionDefinitionSymbol* parentFn;
    std::stack<FunctionDefinitionSymbol*> parentFnStack;
    std::stack<int> parentBlockIdStack;
    int parentBlockId;
    std::map<util::uuid, RangeForBlockIds> rangeForBlockIdMap;
};

} // namespace otava::symbols
