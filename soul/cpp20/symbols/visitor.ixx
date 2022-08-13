// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.symbols.visitor;

import std.core;

export namespace soul::cpp20::symbols {

class Module;
class SymbolTable;
class Symbol;
class ContainerSymbol;
class BoolValue;
class IntegerValue;
class FloatingValue;
class AliasGroupSymbol;
class AliasTypeSymbol;
class BlockSymbol;
class ClassGroupSymbol;
class ClassTypeSymbol;
class CompoundTypeSymbol;
class ConceptGroupSymbol;
class ConceptSymbol;
class FunctionGroupSymbol;
class ParameterSymbol;
class FunctionSymbol;
class FundamentalTypeSymbol;
class NamespaceSymbol;
class SpecializationSymbol;
class TypenameConstraintSymbol;
class TemplateParameterSymbol;
class TemplateDeclarationSymbol;
class ErrorTypeSymbol;
class VariableGroupSymbol;
class VariableSymbol;

class Visitor
{
public:
    Visitor();
    virtual void VisitContainer(ContainerSymbol& symbol);
    virtual void BeginVisitExports() {}
    virtual void EndVisitExports() {}
    virtual void BeginVisitImports() {}
    virtual void EndVisitImports() {}
    virtual void Visit(Module& module) {}
    virtual void Visit(SymbolTable& symbolTable) {}
    virtual void Visit(BoolValue& value) {}
    virtual void Visit(IntegerValue& value) {}
    virtual void Visit(FloatingValue& value) {}
    virtual void Visit(AliasGroupSymbol& symbol) {}
    virtual void Visit(AliasTypeSymbol& symbol) {}
    virtual void Visit(BlockSymbol& symbol) {}
    virtual void Visit(ClassGroupSymbol& symbol) {}
    virtual void Visit(ClassTypeSymbol& symbol) {}
    virtual void Visit(CompoundTypeSymbol& symbol) {}
    virtual void Visit(ConceptGroupSymbol& symbol) {}
    virtual void Visit(ConceptSymbol& symbol) {}
    virtual void Visit(FunctionGroupSymbol& symbol) {}
    virtual void Visit(ParameterSymbol& symbol) {}
    virtual void Visit(FunctionSymbol& symbol) {}
    virtual void Visit(FundamentalTypeSymbol& symbol) {}
    virtual void Visit(NamespaceSymbol& symbol) {}
    virtual void Visit(SpecializationSymbol& symbol) {}
    virtual void Visit(TypenameConstraintSymbol& symbol) {}
    virtual void Visit(TemplateParameterSymbol& symbol) {}
    virtual void Visit(TemplateDeclarationSymbol& symbol) {}
    virtual void Visit(ErrorTypeSymbol& symbol) {}
    virtual void Visit(VariableGroupSymbol& symbol) {}
    virtual void Visit(VariableSymbol& symbol) {}
    void SetVisitContainer(bool visitContainer_) { visitContainer = visitContainer_; }
private:
    bool visitContainer;
};

class DefaultVisitor : public Visitor
{
public:
    void Visit(Module& module) override;
    void Visit(NamespaceSymbol& symbol) override;
    void Visit(SymbolTable& symbolTable) override;
    void Visit(AliasGroupSymbol& symbol) override;
    void Visit(AliasTypeSymbol& symbol) override;
    void Visit(BlockSymbol& symbol) override;
    void Visit(ClassGroupSymbol& symbol) override;
    void Visit(ClassTypeSymbol& symbol) override;
    void Visit(CompoundTypeSymbol& symbol) override;
    void Visit(ConceptGroupSymbol& symbol) override;
    void Visit(FunctionGroupSymbol& symbol) override;
    void Visit(FunctionSymbol& symbol) override;
    void Visit(SpecializationSymbol& symbol) override;
    void Visit(TemplateParameterSymbol& symbol) override;
    void Visit(TemplateDeclarationSymbol& symbol) override;
    void Visit(VariableGroupSymbol& symbol) override;
    void Visit(VariableSymbol& symbol) override;
};

} // namespace soul::cpp20::symbols
