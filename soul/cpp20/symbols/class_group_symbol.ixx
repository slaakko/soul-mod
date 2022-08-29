// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.symbols.class_group.symbol;

import std.core;
import soul.cpp20.symbols.symbol;
import soul.cpp20.symbols.match;

export namespace soul::cpp20::symbols {

class ClassTypeSymbol;
class ForwardClassDeclarationSymbol;
class TypeSymbol;

class ClassGroupSymbol : public Symbol
{
public:
    ClassGroupSymbol(const std::u32string& name_);
    std::string SymbolKindStr() const override { return "class group symbol"; }
    std::string SymbolDocKindStr() const override { return "class_group"; }
    bool IsValidDeclarationScope(ScopeKind scopeKind) const override;
    Symbol* GetSingleSymbol() override;
    void AddClass(ClassTypeSymbol* classTypeSymbol);
    ClassTypeSymbol* GetClass(int arity) const;
    const std::vector<ClassTypeSymbol*>& Classes() const { return classes; }
    void AddForwardDeclaration(ForwardClassDeclarationSymbol* forwardDeclaration);
    ForwardClassDeclarationSymbol* GetForwardDeclaration(int arity) const;
    const std::vector<ForwardClassDeclarationSymbol*>& ForwardDeclarations() const { return forwardDeclarations; }
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
    void Accept(Visitor& visitor) override;
    void Merge(ClassGroupSymbol* that);
private:
    std::vector<ClassTypeSymbol*> classes;
    std::vector<ForwardClassDeclarationSymbol*> forwardDeclarations;
    std::vector<util::uuid> classIds;
};

} // namespace soul::cpp20::symbols
