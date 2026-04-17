// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module gendoc.namespace_symbols;

import std;
import otava.symbols;

export namespace gendoc {

struct NamespaceSymbols
{
    NamespaceSymbols(const std::string& namespaceName_);
    std::string namespaceName;
    std::vector<otava::symbols::ConceptSymbol*> concepts;
    std::vector<otava::symbols::AliasTypeSymbol*> typeAliases;
    std::vector<otava::symbols::ClassTypeSymbol*> classes;
    std::vector<otava::symbols::EnumeratedTypeSymbol*> enumerations;
    std::vector<otava::symbols::FunctionSymbol*> functions;
    std::vector<otava::symbols::VariableSymbol*> variables;
};

} // namespace gendoc
