// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module gendoc.namespace_symbols;

import std.core;
import soul.cpp20.symbols.symbol;

export namespace gendoc {

struct NamespaceSymbols
{
    NamespaceSymbols(const std::string& namespaceName_);
    std::string namespaceName;
    std::vector<soul::cpp20::symbols::ConceptSymbol*> concepts;
    std::vector<soul::cpp20::symbols::AliasTypeSymbol*> typeAliases;
    std::vector<soul::cpp20::symbols::ClassTypeSymbol*> classes;
    std::vector<soul::cpp20::symbols::EnumeratedTypeSymbol*> enumerations;
    std::vector<soul::cpp20::symbols::FunctionSymbol*> functions;
    std::vector<soul::cpp20::symbols::VariableSymbol*> variables;
};

} // namespace gendoc
