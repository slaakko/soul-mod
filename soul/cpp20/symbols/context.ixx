// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.symbols.context;

import std.core;
import soul.lexer.base;
import soul.cpp20.ast.node;

export namespace soul::cpp20::symbols {

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
    saveDeclarations = 1 << 11
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
class BoundFunctionNode;
class BoundCompoundStatementNode;
class OperationRepository;

class Context
{
public:
    Context();
    Lexer* GetLexer() { return lexer; }
    void SetLexer(Lexer* lexer_);
    SymbolTable* GetSymbolTable() { return symbolTable; }
    void SetSymbolTable(SymbolTable* symbolTable_);
    BoundCompileUnitNode* GetBoundCompileUnit() const { return boundCompileUnit; }
    void SetBoundCompileUnit(BoundCompileUnitNode* boundCompileUnit_);
    OperationRepository* GetOperationRepository() const;
    BoundFunctionNode* GetBoundFunction() const { return boundFunction; }
    void SetBoundFunction(BoundFunctionNode* boundFunction_);
    BoundCompoundStatementNode* GetCurrentCompoundStatement() const { return currentCompoundStatement; }
    void BeginCompoundStatement();
    void EndCompoundStatement();
    EvaluationContext* GetEvaluationContext();
    std::string FileName() const;
    void PushFlags();
    void PopFlags();
    void PushSetFlag(ContextFlags flag);
    void PushResetFlag(ContextFlags flag);
    void SetFlag(ContextFlags flag) { flags = flags | flag; }
    bool GetFlag(ContextFlags flag) const { return (flags & flag) != ContextFlags::none; }
    void ResetFlag(ContextFlags flag) { flags = flags & ~flag; }
    bool IsConstructorNameNode(soul::cpp20::ast::Node* node) const;
    bool EnableNoDeclSpecFunctionDeclaration() const;
    bool EnableNoDeclSpecFunctionDefinition() const;
    void PushNode(soul::cpp20::ast::Node* node_);
    void PopNode();
    soul::cpp20::ast::Node* GetNode() const { return node; }
    void SetDeclarationList(soul::cpp20::ast::Node* node, DeclarationList* declarations);
    std::unique_ptr<DeclarationList> ReleaseDeclarationList(soul::cpp20::ast::Node* node);
private:
    Lexer* lexer;
    SymbolTable* symbolTable;
    BoundCompileUnitNode* boundCompileUnit;
    BoundFunctionNode* boundFunction;
    BoundCompoundStatementNode* currentCompoundStatement;
    std::stack<BoundCompoundStatementNode*> compoundStatementStack;
    ContextFlags flags;
    std::stack<ContextFlags> flagStack;
    std::stack<soul::cpp20::ast::Node*> nodeStack;
    soul::cpp20::ast::Node* node;
    std::map<soul::cpp20::ast::Node*, std::unique_ptr<DeclarationList>> declarationMap;
};

} // namespace soul::cpp20::symbols

export namespace soul::cpp20::symbols::context {

} // soul::cpp20::symbols::context;
