// =================================
// Copyright (c) 2022 Seppo Laakko
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

export namespace otava::symbols {

using Lexer = soul::lexer::LexerBase<char32_t>;

struct DeclarationList;

enum class ContextFlags : int32_t
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
    skipFunctionDefinitions = 1 << 18
};

constexpr ContextFlags operator|(ContextFlags left, ContextFlags right)
{
    return ContextFlags(int32_t(left) | int32_t(right));
}

constexpr  ContextFlags operator&(ContextFlags left, ContextFlags right)
{
    return ContextFlags(int32_t(left) & int32_t(right));
}

constexpr  ContextFlags operator~(ContextFlags flags)
{
    return ContextFlags(~int32_t(flags));
}

class SymbolTable;
class EvaluationContext;
class BoundCompileUnitNode;
class BoundExpressionNode;
class BoundFunctionNode;
class BoundCompoundStatementNode;
class OperationRepository;
class FunctionDefinitionSymbol;
class AliasTypeSymbol;

class Context
{
public:
    Context();
    Lexer* GetLexer() { return lexer; }
    void SetLexer(Lexer* lexer_);
    SymbolTable* GetSymbolTable() { return symbolTable; }
    void SetSymbolTable(SymbolTable* symbolTable_);
    BoundCompileUnitNode* GetBoundCompileUnit() const { return boundCompileUnit.get(); }
    OperationRepository* GetOperationRepository() const;
    BoundFunctionNode* GetBoundFunction() const { return boundFunction.get(); }
    BoundFunctionNode* ReleaseBoundFunction() { return boundFunction.release(); }
    void PushBoundFunction(BoundFunctionNode* boundFunction_);
    void PopBoundFunction();
    BoundExpressionNode* GetThisPtr(const soul::ast::SourcePos& sourcePos);
    EvaluationContext* GetEvaluationContext();
    std::string FileName() const;
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
    void SetSpecialization(FunctionDefinitionSymbol* specialization_) { specialization = specialization_; }
    FunctionDefinitionSymbol* GetSpecialization() const { return specialization; }
    void SetFunctionDefinitionNode(otava::ast::FunctionDefinitionNode* functionDefinitionNode_) { functionDefinitionNode = functionDefinitionNode_; }
    otava::ast::Node* GetFunctionDefinitionNode() const { return functionDefinitionNode; }
    void SetAliasType(AliasTypeSymbol* aliasType_) { aliasType = aliasType_; }
    AliasTypeSymbol* GetAliasType() const { return aliasType; }
    void SetPtr(otava::intermediate::Value* ptr_) { ptr = ptr_; }
    otava::intermediate::Value* Ptr() const { return ptr; }
private:
    Lexer* lexer;
    SymbolTable* symbolTable;
    std::unique_ptr<BoundCompileUnitNode> boundCompileUnit;
    std::unique_ptr<BoundFunctionNode> boundFunction;
    std::stack<std::unique_ptr<BoundFunctionNode>> boundFunctionStack;
    ContextFlags flags;
    std::stack<ContextFlags> flagStack;
    std::stack<otava::ast::Node*> nodeStack;
    otava::ast::Node* node;
    std::map<otava::ast::Node*, std::unique_ptr<DeclarationList>> declarationMap;
    soul::lexer::FileMap* fileMap;
    FunctionDefinitionSymbol* specialization;
    otava::ast::FunctionDefinitionNode* functionDefinitionNode;
    AliasTypeSymbol* aliasType;
    otava::intermediate::Value* ptr;
};

} // namespace otava::symbols

export namespace otava::symbols::context {

} // otava::symbols::context;
