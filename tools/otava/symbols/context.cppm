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
import otava.symbols.instantiation_queue;
import otava.symbols.function_definition_symbol_set;
import otava.symbols.templates;
import otava.symbols.template_param_compare;

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
    skipNonstaticMemberFunctions = static_cast<std::int64_t>(1) << 38
};

constexpr ContextFlags operator|(ContextFlags left, ContextFlags right)
{
    return ContextFlags(std::int64_t(left) | std::int64_t(right));
}

constexpr ContextFlags operator&(ContextFlags left, ContextFlags right)
{
    return ContextFlags(std::int64_t(left) & std::int64_t(right));
}

constexpr ContextFlags operator~(ContextFlags flags)
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

int GetOptLevel(int level, bool release);

class Context
{
public:
    Context();
    inline Lexer* GetLexer() { return lexer; }
    void SetLexer(Lexer* lexer_);
    inline SymbolTable* GetSymbolTable() { return symbolTable; }
    void SetSymbolTable(SymbolTable* symbolTable_);
    Module* GetModule();
    void SetFunctionDefinitionSymbolSet(FunctionDefinitionSymbolSet* functionDefinitionSymbolSet_);
    FunctionDefinitionSymbolSet* GetFunctionDefinitionSymbolSet() const;
    inline BoundCompileUnitNode* GetBoundCompileUnit() const { return boundCompileUnit.get(); }
    OperationRepository* GetOperationRepository() const;
    inline BoundFunctionNode* GetBoundFunction() const { return boundFunction.get(); }
    inline BoundFunctionNode* ReleaseBoundFunction() { return boundFunction.release(); }
    void PushBoundFunction(BoundFunctionNode* boundFunction_);
    void PopBoundFunction();
    BoundExpressionNode* GetThisPtr(const soul::ast::SourcePos& sourcePos);
    EvaluationContext* GetEvaluationContext();
    std::string FileName() const;
    void SetFileName(const std::string& fileName_);
    void PushFlags();
    void PopFlags();
    void PushSetFlag(ContextFlags flag);
    void PushResetFlag(ContextFlags flag);
    inline void SetFlag(ContextFlags flag) { flags = flags | flag; }
    inline bool GetFlag(ContextFlags flag) const { return (flags & flag) != ContextFlags::none; }
    inline void ResetFlag(ContextFlags flag) { flags = flags & ~flag; }
    inline bool ReleaseConfig() const { return GetFlag(ContextFlags::release); }
    inline void SetReleaseConfig() { SetFlag(ContextFlags::release); }
    int OptLevel() const;
    inline void SetOptLevel(int optLevel_) { optLevel = optLevel_; }
    bool IsConstructorNameNode(otava::ast::Node* node) const;
    bool EnableNoDeclSpecFunctionDeclaration() const;
    bool EnableNoDeclSpecFunctionDefinition() const;
    void PushNode(otava::ast::Node* node_);
    void PopNode();
    inline otava::ast::Node* GetNode() const { return node; }
    void SetDeclarationList(otava::ast::Node* node, DeclarationList* declarations);
    std::unique_ptr<DeclarationList> ReleaseDeclarationList(otava::ast::Node* node);
    inline soul::lexer::FileMap* GetFileMap() const { return fileMap; }
    inline void SetFileMap(soul::lexer::FileMap* fileMap_) { fileMap = fileMap_; }
    inline void SetAliasType(AliasTypeSymbol* aliasType_) { aliasType = aliasType_; }
    inline AliasTypeSymbol* GetAliasType() const { return aliasType; }
    inline void SetPtr(otava::intermediate::Value* ptr_) { ptr = ptr_; }
    inline otava::intermediate::Value* Ptr() const { return ptr; }
    inline int MemFunDefSymbolIndex() const { return memFunDefSymbolIndex; }
    inline void SetMemFunDefSymbolIndex(int index) { memFunDefSymbolIndex = index; }
    inline void ResetRejectTemplateId() { rejectTemplateId = false; }
    inline void SetRejectTemplateId() { rejectTemplateId = true; }
    inline bool RejectTemplateId() const { return rejectTemplateId; }
    void PushSwitchCondType(TypeSymbol* switchCondType_);
    void PopSwitchCondType();
    inline TypeSymbol* GetSwitchCondType() const { return switchCondType; }
    void SetInstantiationQueue(InstantiationQueue* instantiationQueue_);
    inline InstantiationQueue* GetInstantiationQueue() { return instantiationQueue; }
    void AddTemporaryAliasType(AliasTypeSymbol* temporaryAliasType);
    inline const std::vector<AliasTypeSymbol*>& TemporaryAliasTypes() const { return temporaryAliasTypes; }
    void ClearTemporaryAliasTypes();
    inline void SetDeclaredInitializerType(TypeSymbol* type) { declaredInitializerType = type; }
    inline TypeSymbol* DeclaredInitializerType() const { return declaredInitializerType; }
    FunctionSymbol* GetSpecialization(otava::ast::Node* functionNode) const;
    void SetSpecialization(FunctionSymbol* specialization, otava::ast::Node* functionNode);
    void RemoveSpecialization(otava::ast::Node* functionNode);
    ClassTemplateSpecializationSymbol* GetClassTemplateSpecialization(otava::ast::Node* functionNode) const;
    void SetClassTemplateSpecialization(otava::ast::Node* functionNode, ClassTemplateSpecializationSymbol* sp);
    void RemoveClassTemplateSpecialization(otava::ast::Node* functionNode);
    void SetInstantiationIrName(const std::string& instantiationIrName_);
    inline const std::string& InstantiationIrName() const { return instantiationIrName; }
    void AddBoundVTabFunction(BoundFunctionNode* node);
    inline const std::vector<std::unique_ptr<BoundFunctionNode>>& BoundVTabFunctions() const { return boundVTabFunctions; }
    void ClearBoundVTabFunctions();
    void PushTemplateParameterMap(std::map<TemplateParameterSymbol*, TypeSymbol*, TemplateParamLess>* templateParamMap);
    void PopTemplateParameterMap();
    inline std::map<TemplateParameterSymbol*, TypeSymbol*, TemplateParamLess>* TemplateParameterMap() const { return templateParameterMap; }
    inline void SetSourcePos(const soul::ast::SourcePos& sourcePos_) { sourcePos = sourcePos_; }
    inline const soul::ast::SourcePos& GetSourcePos() const { return sourcePos; }
    inline TypeSymbol* ArgType() { return argType; }
    inline void SetArgType(TypeSymbol* argType_) { argType = argType_; }
    inline TypeSymbol* ParamType() { return paramType; }
    inline void SetParamType(TypeSymbol* paramType_) { paramType = paramType_; }
    inline int TotalFunctionsCompiled() const { return totalFunctionsCompiled; }
    inline int FunctionCallsInlined() const { return functionCallsInlined; }
    inline int FunctionsInlined() const { return functionsInlined; }
    inline void SetTotalFunctionsCompiled(int totalFunctionsCompiled_) { totalFunctionsCompiled = totalFunctionsCompiled_; }
    inline void SetFunctionCallsInlined(int functionCallsInlined_) { functionCallsInlined = functionCallsInlined_; }
    inline void SetFunctionsInlined(int functionsInlined_) { functionsInlined = functionsInlined_; }
    inline Emitter* GetEmitter() { return emitter; }
    inline void SetEmitter(Emitter* emitter_) { emitter = emitter_; }
    inline int ArgIndex() const { return argIndex; }
    void SetArgIndex(int argIndex_) { argIndex = argIndex_; }
private:
    Lexer* lexer;
    SymbolTable* symbolTable;
    Emitter* emitter;
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
    int argIndex;
};

} // namespace otava::symbols

export namespace otava::symbols::context {

} // otava::symbols::context;
