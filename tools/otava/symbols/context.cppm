// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.context;

import std.core;
import soul.lexer.base;
import soul.lexer.file.map;
import soul.ast.source.pos;
import otava.ast.node;
import otava.ast.function;
import otava.intermediate.value;
import otava.symbols.instantiation_queue;
import otava.symbols.function_definition_symbol_set;
import otava.symbols.templates;
import otava.symbols.template_param_compare;

export namespace otava::symbols {

using Lexer = soul::lexer::LexerBase<char32_t>;

struct DeclarationList;

enum class ContextFlags : std::int32_t
{
    none = 0,
    hasDefiningTypeSpecifier = 1 << 0,
    friendSpecifier = 1 << 1,
    parsingParameters = 1 << 2,
    parsingConceptDefinition = 1 << 3,
    parsingTemplateId = 1 << 4,
    assumeType = 1 << 5,
    parseSavedMemberFunctionBody = 1 << 6,
    parsingTemplateDeclaration = 1 << 7,
    parseMemberFunction = 1 << 8,
    retMemberDeclSpecifiers = 1 << 9,
    addClassScope = 1 << 10,
    saveDeclarations = 1 << 11,
    linkageDeclaration = 1 << 12,
    instantiateFunctionTemplate = 1 << 13,
    instantiateAliasTypeTemplate = 1 << 14,
    instantiateMemFnOfClassTemplate = 1 << 15,
    dontBind = 1 << 16,
    parseSavedCtorInitializer = 1 << 17,
    skipFunctionDefinitions = 1 << 18,
    returnRef = 1 << 19,
    virtualSeen = 1 << 20,
    ignoreClassTemplateSpecializations = 1 << 21,
    generateMainWrapper = 1 << 22,
    noDynamicInit = 1 << 23,
    requireForwardResolved = 1 << 24,
    noPtrOps = 1 << 25,
    reinterpretCast = 1 << 26,
    derefAfterConv = 1 << 27,
    generatingVTab = 1 << 28,
    resolveNestedTypes = 1 << 29
};

constexpr ContextFlags operator|(ContextFlags left, ContextFlags right)
{
    return ContextFlags(std::int32_t(left) | std::int32_t(right));
}

constexpr  ContextFlags operator&(ContextFlags left, ContextFlags right)
{
    return ContextFlags(std::int32_t(left) & std::int32_t(right));
}

constexpr  ContextFlags operator~(ContextFlags flags)
{
    return ContextFlags(~std::int32_t(flags));
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

class Context
{
public:
    Context();
    Lexer* GetLexer() { return lexer; }
    void SetLexer(Lexer* lexer_);
    SymbolTable* GetSymbolTable() { return symbolTable; }
    void SetSymbolTable(SymbolTable* symbolTable_);
    Module* GetModule();
    void SetFunctionDefinitionSymbolSet(FunctionDefinitionSymbolSet* functionDefinitionSymbolSet_);
    FunctionDefinitionSymbolSet* GetFunctionDefinitionSymbolSet() const;
    BoundCompileUnitNode* GetBoundCompileUnit() const { return boundCompileUnit.get(); }
    OperationRepository* GetOperationRepository() const;
    BoundFunctionNode* GetBoundFunction() const { return boundFunction.get(); }
    BoundFunctionNode* ReleaseBoundFunction() { return boundFunction.release(); }
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
    void SetFlag(ContextFlags flag) { flags = flags | flag; }
    bool GetFlag(ContextFlags flag) const { return (flags & flag) != ContextFlags::none; }
    void ResetFlag(ContextFlags flag) { flags = flags & ~flag; }
    bool IsConstructorNameNode(otava::ast::Node* node) const;
    bool EnableNoDeclSpecFunctionDeclaration() const;
    bool EnableNoDeclSpecFunctionDefinition() const;
    void PushNode(otava::ast::Node* node_);
    void PopNode();
    otava::ast::Node* GetNode() const { return node; }
    void SetDeclarationList(otava::ast::Node* node, DeclarationList* declarations);
    std::unique_ptr<DeclarationList> ReleaseDeclarationList(otava::ast::Node* node);
    soul::lexer::FileMap* GetFileMap() const { return fileMap; }
    void SetFileMap(soul::lexer::FileMap* fileMap_) { fileMap = fileMap_; }
    void SetAliasType(AliasTypeSymbol* aliasType_) { aliasType = aliasType_; }
    AliasTypeSymbol* GetAliasType() const { return aliasType; }
    void SetPtr(otava::intermediate::Value* ptr_) { ptr = ptr_; }
    otava::intermediate::Value* Ptr() const { return ptr; }
    int MemFunDefSymbolIndex() const { return memFunDefSymbolIndex; }
    void SetMemFunDefSymbolIndex(int index) { memFunDefSymbolIndex = index; }
    void ResetRejectTemplateId() { rejectTemplateId = false; }
    void SetRejectTemplateId() { rejectTemplateId = true; }
    bool RejectTemplateId() const { return rejectTemplateId; }
    void PushSwitchCondType(TypeSymbol* switchCondType_);
    void PopSwitchCondType();
    TypeSymbol* GetSwitchCondType() const { return switchCondType; }
    void SetInstantiationQueue(InstantiationQueue* instantiationQueue_);
    InstantiationQueue* GetInstantiationQueue() { return instantiationQueue; }
    void AddTemporaryAliasType(AliasTypeSymbol* temporaryAliasType);
    const std::vector<AliasTypeSymbol*>& TemporaryAliasTypes() const { return temporaryAliasTypes; }
    void ClearTemporaryAliasTypes();
    void SetDeclaredInitializerType(TypeSymbol* type) { declaredInitializerType = type; }
    TypeSymbol* DeclaredInitializerType() const { return declaredInitializerType; }
    FunctionSymbol* GetSpecialization(otava::ast::Node* functionNode) const;
    void SetSpecialization(FunctionSymbol* specialization, otava::ast::Node* functionNode);
    void RemoveSpecialization(otava::ast::Node* functionNode);
    ClassTemplateSpecializationSymbol* GetClassTemplateSpecialization(otava::ast::Node* functionNode) const;
    void SetClassTemplateSpecialization(otava::ast::Node* functionNode, ClassTemplateSpecializationSymbol* sp);
    void RemoveClassTemplateSpecialization(otava::ast::Node* functionNode);
    void SetInstantiationIrName(const std::string& instantiationIrName_);
    const std::string& InstantiationIrName() const { return instantiationIrName; }
    void AddBoundVTabFunction(BoundFunctionNode* node);
    const std::vector<std::unique_ptr<BoundFunctionNode>>& BoundVTabFunctions() const { return boundVTabFunctions; }
    void ClearBoundVTabFunctions();
    void PushTemplateParameterMap(std::map<TemplateParameterSymbol*, TypeSymbol*, TemplateParamLess>* templateParamMap);
    void PopTemplateParameterMap();
    std::map<TemplateParameterSymbol*, TypeSymbol*, TemplateParamLess>* TemplateParameterMap() const { return templateParameterMap; }
    void SetSourcePos(const soul::ast::SourcePos& sourcePos_) { sourcePos = sourcePos_; }
    const soul::ast::SourcePos& GetSourcePos() const { return sourcePos; }
private:
    Lexer* lexer;
    SymbolTable* symbolTable;
    std::unique_ptr<BoundCompileUnitNode> boundCompileUnit;
    std::unique_ptr<BoundFunctionNode> boundFunction;
    std::stack<std::unique_ptr<BoundFunctionNode>> boundFunctionStack;
    std::vector<std::unique_ptr<BoundFunctionNode>> boundVTabFunctions;
    ContextFlags flags;
    std::stack<ContextFlags> flagStack;
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
};

} // namespace otava::symbols

export namespace otava::symbols::context {

} // otava::symbols::context;
