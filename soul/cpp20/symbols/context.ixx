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
    retMemberDeclSpecifiers = 1 << 9
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

class Context
{
public:
    Context();
    Lexer* GetLexer() { return lexer; }
    void SetLexer(Lexer* lexer_);
    SymbolTable* GetSymbolTable() { return symbolTable; }
    void SetSymbolTable(SymbolTable* symbolTable_);
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
private:
    Lexer* lexer;
    SymbolTable* symbolTable;
    ContextFlags flags;
    std::stack<ContextFlags> flagStack;
    std::stack<soul::cpp20::ast::Node*> nodeStack;
    soul::cpp20::ast::Node* node;

};

} // namespace soul::cpp20::symbols

export namespace soul::cpp20::symbols::context {

} // soul::cpp20::symbols::context;
