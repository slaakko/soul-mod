// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.context;

import std.core;
import soul.lexer.base;
import soul.ast.source.pos;
import otava.ast.node;

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
    BoundCompileUnitNode* GetBoundCompileUnit() const { return boundCompileUnit.get(); }
    OperationRepository* GetOperationRepository() const;
    BoundFunctionNode* GetBoundFunction() const { return boundFunction; }
    void SetBoundFunction(BoundFunctionNode* boundFunction_);
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
private:
    Lexer* lexer;
    SymbolTable* symbolTable;
    std::unique_ptr<BoundCompileUnitNode> boundCompileUnit;
    BoundFunctionNode* boundFunction;
    ContextFlags flags;
    std::stack<ContextFlags> flagStack;
    std::stack<otava::ast::Node*> nodeStack;
    otava::ast::Node* node;
    std::map<otava::ast::Node*, std::unique_ptr<DeclarationList>> declarationMap;
};

} // namespace otava::symbols

export namespace otava::symbols::context {

} // otava::symbols::context;
