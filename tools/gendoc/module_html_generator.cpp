// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module gendoc.module_html_generator;

import gendoc.type_element_generator;
import gendoc.class_html_generator;
import gendoc.enum_html_generator;
import gendoc.file_html_generator;
import gendoc.project;
import std;
import util;
import otava.symbols;
import soul.xml.dom;

namespace gendoc {

class ModuleHtmlGenerator : public otava::symbols::DefaultVisitor
{
public:
    ModuleHtmlGenerator(const std::string& rootDir_, Project* nsProject_);
    void BeginVisitExports() override;
    void EndVisitExports() override;
    void BeginVisitImports() override;
    void EndVisitImports() override;
    const std::string& ModuleDir() const { return moduleDir; }
    void Visit(otava::symbols::Module& module) override;
    void Visit(otava::symbols::NamespaceSymbol& symbol) override;
    void Visit(otava::symbols::ConceptSymbol& symbol) override;
    void Visit(otava::symbols::AliasTypeSymbol& symbol) override;
    void Visit(otava::symbols::ClassTypeSymbol& symbol) override;
    void Visit(otava::symbols::EnumeratedTypeSymbol& symbol) override;
    void Visit(otava::symbols::FunctionSymbol& symbol) override;
    void Visit(otava::symbols::VariableSymbol& symbol) override;
    void GenerateNamespaceSection();
    void GenerateClassSection();
    void GenerateEnumerationSection();
    void GenerateTypeAliasSection();
    void GenerateFunctionSection();
    void GenerateVariableSection();
    void GenerateClassDocs();
    void GenerateEnumDocs();
    void WriteDoc();
private:
    std::string rootDir;
    Project* nsProject;
    std::string moduleDir;
    soul::xml::Document doc;
    std::string filePath;
    bool visitingExports;
    bool visitingImports;
    bool visitNamespaces;
    soul::xml::Element* bodyElement;
    soul::xml::Element* currentElement;
    otava::symbols::Module* currentModule;
    std::vector<otava::symbols::Module*> exportedModules;
    std::vector<otava::symbols::Module*> importedModules;
    std::vector<otava::symbols::NamespaceSymbol*> namespaces;
    std::vector<otava::symbols::ConceptSymbol*> concepts;
    std::vector<otava::symbols::AliasTypeSymbol*> typeAliases;
    std::vector<otava::symbols::ClassTypeSymbol*> classes;
    std::vector<otava::symbols::EnumeratedTypeSymbol*> enumerations;
    std::vector<otava::symbols::FunctionSymbol*> functions;
    std::vector<otava::symbols::VariableSymbol*> variables;
};

ModuleHtmlGenerator::ModuleHtmlGenerator(const std::string& rootDir_, Project* nsProject_) :
    rootDir(rootDir_), 
    nsProject(nsProject_),
    visitingExports(false), 
    visitingImports(false), 
    visitNamespaces(false),
    bodyElement(nullptr), 
    currentElement(nullptr),
    currentModule(nullptr)
{
}

void ModuleHtmlGenerator::BeginVisitExports()
{
    if (visitNamespaces) return;
    visitingExports = true;
    soul::xml::Element* exportsElement = soul::xml::MakeElement("h2");
    soul::xml::Text* exportsText = soul::xml::MakeText("Exports");
    exportsElement->AppendChild(exportsText);
    bodyElement->AppendChild(exportsElement);
    soul::xml::Element* tableElement = soul::xml::MakeElement("table");
    tableElement->SetAttribute("class", "doc");
    bodyElement->AppendChild(tableElement);
    soul::xml::Element* trElement = soul::xml::MakeElement("tr");
    soul::xml::Element* thElement = soul::xml::MakeElement("th");
    soul::xml::Text* moduleText = soul::xml::MakeText("module");
    thElement->AppendChild(moduleText);
    trElement->AppendChild(thElement);
    tableElement->AppendChild(trElement);
    currentElement = tableElement;
}

void ModuleHtmlGenerator::EndVisitExports()
{
    if (visitNamespaces) return;
    visitingExports = false;
    std::sort(exportedModules.begin(), exportedModules.end(), otava::symbols::ModuleNameLess());
    for (const auto& module : exportedModules)
    {
        soul::xml::Element* trElement = soul::xml::MakeElement("tr");
        currentElement->AppendChild(trElement);
        soul::xml::Element* tdElement = soul::xml::MakeElement("td");
        trElement->AppendChild(tdElement);
        soul::xml::Element* linkElement = soul::xml::MakeElement("a");
        tdElement->AppendChild(linkElement);
        linkElement->SetAttribute("href", "../" + module->Name() + "/index.html");
        soul::xml::Text* moduleText = soul::xml::MakeText(module->Name());
        linkElement->AppendChild(moduleText);
    }
    currentElement = bodyElement;
}

void ModuleHtmlGenerator::BeginVisitImports()
{
    if (visitNamespaces) return;
    visitingImports = true;
    soul::xml::Element* importsElement = soul::xml::MakeElement("h2");
    soul::xml::Text* importsText = soul::xml::MakeText("Imports");
    importsElement->AppendChild(importsText);
    bodyElement->AppendChild(importsElement);
    soul::xml::Element* tableElement = soul::xml::MakeElement("table");
    tableElement->SetAttribute("class", "doc");
    bodyElement->AppendChild(tableElement);
    soul::xml::Element* trElement = soul::xml::MakeElement("tr");
    soul::xml::Element* thElement = soul::xml::MakeElement("th");
    soul::xml::Text* moduleText = soul::xml::MakeText("module");
    thElement->AppendChild(moduleText);
    trElement->AppendChild(thElement);
    tableElement->AppendChild(trElement);
    currentElement = tableElement;
}

void ModuleHtmlGenerator::EndVisitImports()
{
    if (visitNamespaces) return;
    visitingImports = false;
    std::sort(importedModules.begin(), importedModules.end(), otava::symbols::ModuleNameLess());
    for (const auto& module : importedModules)
    {
        soul::xml::Element* trElement = soul::xml::MakeElement("tr");
        currentElement->AppendChild(trElement);
        soul::xml::Element* tdElement = soul::xml::MakeElement("td");
        trElement->AppendChild(tdElement);
        soul::xml::Element* linkElement = soul::xml::MakeElement("a");
        tdElement->AppendChild(linkElement);
        linkElement->SetAttribute("href", "../" + module->Name() + "/index.html");
        soul::xml::Text* moduleText = soul::xml::MakeText(module->Name());
        linkElement->AppendChild(moduleText);
    }
    currentElement = bodyElement;
}

void ModuleHtmlGenerator::Visit(otava::symbols::Module& module)
{
    if (visitingExports || visitingImports)
    {
        if (visitingExports)
        {
            exportedModules.push_back(&module);
        }
        else if (visitingImports)
        {
            importedModules.push_back(&module);
        }
    }
    else
    {
        if (visitNamespaces) return;
        currentModule = &module;
        moduleDir = util::GetFullPath(util::Path::Combine(util::Path::Combine(rootDir, "module"), module.Name()));
        std::filesystem::create_directories(moduleDir);
        filePath = util::Path::Combine(moduleDir, "index.html");
        soul::xml::Element* htmlElement = soul::xml::MakeElement("html");
        doc.AppendChild(htmlElement);
        soul::xml::Element* headElement = soul::xml::MakeElement("head");
        htmlElement->AppendChild(headElement);
        soul::xml::Element* metaElement = soul::xml::MakeElement("meta");
        metaElement->SetAttribute("charset", "utf-8");
        headElement->AppendChild(metaElement);
        soul::xml::Element* titleElement = soul::xml::MakeElement("title");
        std::string title = module.Name() + " Module";
        soul::xml::Text* titleText = soul::xml::MakeText(title);
        titleElement->AppendChild(titleText);
        headElement->AppendChild(titleElement);
        soul::xml::Element* linkElement = soul::xml::MakeElement("link");
        std::string styleFilePath = "../../style/style.css";
        linkElement->SetAttribute("href", styleFilePath);
        linkElement->SetAttribute("rel", "stylesheet");
        linkElement->SetAttribute("type", "text/css");
        headElement->AppendChild(linkElement);
        bodyElement = soul::xml::MakeElement("body");
        soul::xml::Element* h1Element = soul::xml::MakeElement("h1");
        soul::xml::Text* h1Text = soul::xml::MakeText(title);
        h1Element->AppendChild(h1Text);
        bodyElement->AppendChild(h1Element);
        soul::xml::Element* h2Element = soul::xml::MakeElement("h2");
        h2Element->AppendChild(soul::xml::MakeText("Interface"));
        soul::xml::Element* interfaceFileLink = soul::xml::MakeElement("a");
        otava::ast::File* file = module.GetFile();
        interfaceFileLink->SetAttribute("href", "file/" + util::Path::GetFileName(file->filePath) + ".html");
        interfaceFileLink->AppendChild(soul::xml::MakeText(util::Path::GetFileName(file->filePath)));
        bodyElement->AppendChild(h2Element);
        bodyElement->AppendChild(interfaceFileLink);
        if (!module.ImplementationUnits().empty())
        {
            soul::xml::Element* h2ImplElement = soul::xml::MakeElement("h2");
            h2ImplElement->AppendChild(soul::xml::MakeText("Implementation"));
            bodyElement->AppendChild(h2ImplElement);
            bool first = true;
            for (const auto& implementationUnit : module.ImplementationUnits())
            {
                if (first)
                {
                    first = false;
                }
                else
                {
                    bodyElement->AppendChild(soul::xml::MakeElement("br"));
                }
                soul::xml::Element* implementationFileLink = soul::xml::MakeElement("a");
                otava::ast::File* file = implementationUnit->GetFile();
                implementationFileLink->SetAttribute("href", "file/" + util::Path::GetFileName(file->filePath) + ".html");
                implementationFileLink->AppendChild(soul::xml::MakeText(util::Path::GetFileName(file->filePath)));
                bodyElement->AppendChild(implementationFileLink);
            }
        }
        htmlElement->AppendChild(bodyElement);
        currentElement = bodyElement;
        DefaultVisitor::Visit(module);
    }
}

void ModuleHtmlGenerator::Visit(otava::symbols::NamespaceSymbol& symbol)
{
    return;
}

void ModuleHtmlGenerator::Visit(otava::symbols::ConceptSymbol& symbol)
{
    if (visitNamespaces) return;
    if (symbol.ParentClassType()) return;
    concepts.push_back(&symbol);
    if (nsProject)
    {
        nsProject->AddToNamespace(symbol.ParentNamespace(), &symbol);
    }
}

void ModuleHtmlGenerator::Visit(otava::symbols::AliasTypeSymbol& symbol)
{
    if (visitNamespaces) return;
    if (symbol.ParentClassType()) return;
    typeAliases.push_back(&symbol);
    if (nsProject)
    {
        nsProject->AddToNamespace(symbol.ParentNamespace(), &symbol);
    }
}

void ModuleHtmlGenerator::Visit(otava::symbols::ClassTypeSymbol& symbol)
{
    if (visitNamespaces) return;
    if (symbol.ParentClassType()) return;
    classes.push_back(&symbol);
    if (nsProject)
    {
        nsProject->AddToNamespace(symbol.ParentNamespace(), &symbol);
    }
}

void ModuleHtmlGenerator::Visit(otava::symbols::EnumeratedTypeSymbol& symbol)
{
    if (visitNamespaces) return;
    if (symbol.ParentClassType()) return;
    enumerations.push_back(&symbol);
    if (nsProject)
    {
        nsProject->AddToNamespace(symbol.ParentNamespace(), &symbol);
    }
}

void ModuleHtmlGenerator::Visit(otava::symbols::FunctionSymbol& symbol)
{
    if (visitNamespaces) return;
    if (symbol.ParentClassType()) return;
    functions.push_back(&symbol);
    if (nsProject)
    {
        nsProject->AddToNamespace(symbol.ParentNamespace(), &symbol);
    }
}

void ModuleHtmlGenerator::Visit(otava::symbols::VariableSymbol& symbol)
{
    if (visitNamespaces) return;
    if (symbol.ParentClassType()) return;
    variables.push_back(&symbol);
    if (nsProject)
    {
        nsProject->AddToNamespace(symbol.ParentNamespace(), &symbol);
    }
}

void ModuleHtmlGenerator::GenerateNamespaceSection()
{
    return;
    if (namespaces.empty()) return;
    std::sort(namespaces.begin(), namespaces.end(), otava::symbols::NamespaceLess());
    soul::xml::Element* h2Element = soul::xml::MakeElement("h2");
    bodyElement->AppendChild(h2Element);
    soul::xml::Text* h2Text = soul::xml::MakeText("Namespaces");
    h2Element->AppendChild(h2Text);
    soul::xml::Element* tableElement = soul::xml::MakeElement("table");
    bodyElement->AppendChild(tableElement);
    tableElement->SetAttribute("class", "doc");
    soul::xml::Element* trElement = soul::xml::MakeElement("tr");
    tableElement->AppendChild(trElement);
    soul::xml::Element* thNsElement = soul::xml::MakeElement("th");
    trElement->AppendChild(thNsElement);
    soul::xml::Text* thNsText = soul::xml::MakeText("namespace");
    thNsElement->AppendChild(thNsText);
    for (const auto& ns : namespaces)
    {
        soul::xml::Element* trElement = soul::xml::MakeElement("tr");
        tableElement->AppendChild(trElement);
        soul::xml::Element* tdElement = soul::xml::MakeElement("td");
        trElement->AppendChild(tdElement);
        soul::xml::Element* linkElement = soul::xml::MakeElement("a");
        tdElement->AppendChild(linkElement);
        linkElement->SetAttribute("href", "../../namespace/" + ns->DocName() + "/index.html");
        soul::xml::Text* linkText = soul::xml::MakeText(MakeNsText(ns));
        linkElement->AppendChild(linkText);
    }
}

void ModuleHtmlGenerator::GenerateTypeAliasSection()
{
    if (typeAliases.empty()) return;
    std::sort(typeAliases.begin(), typeAliases.end(), otava::symbols::AliasTypeLess());
    soul::xml::Element* h2Element = soul::xml::MakeElement("h2");
    bodyElement->AppendChild(h2Element);
    soul::xml::Text* h2Text = soul::xml::MakeText("Type Aliases");
    h2Element->AppendChild(h2Text);
    soul::xml::Element* tableElement = soul::xml::MakeElement("table");
    bodyElement->AppendChild(tableElement);
    tableElement->SetAttribute("class", "doc");
    soul::xml::Element* trElement = soul::xml::MakeElement("tr");
    tableElement->AppendChild(trElement);
    soul::xml::Element* thTypeAliasElement = soul::xml::MakeElement("th");
    trElement->AppendChild(thTypeAliasElement);
    soul::xml::Text* thTypeAliasText = soul::xml::MakeText("alias");
    thTypeAliasElement->AppendChild(thTypeAliasText);
    soul::xml::Element* thTypeElement = soul::xml::MakeElement("th");
    trElement->AppendChild(thTypeElement);
    soul::xml::Text* thTypeText = soul::xml::MakeText("type");
    thTypeElement->AppendChild(thTypeText);
    soul::xml::Element* thNamespaceElement = soul::xml::MakeElement("th");
    trElement->AppendChild(thNamespaceElement);
    soul::xml::Text* thNamespaceText = soul::xml::MakeText("namespace");
    thNamespaceElement->AppendChild(thNamespaceText);
    for (const auto& alias : typeAliases)
    {
        soul::xml::Element* trTypeAliasElement = soul::xml::MakeElement("tr");
        tableElement->AppendChild(trTypeAliasElement);
        soul::xml::Element* tdElement = soul::xml::MakeElement("td");
        tdElement->SetAttribute("id", alias->DocName());
        trTypeAliasElement->AppendChild(tdElement);
        soul::xml::Text* tdTypeAliasText = soul::xml::MakeText(util::ToUtf8(alias->Name()));
        tdElement->AppendChild(tdTypeAliasText);
        soul::xml::Element* tdTypeElement = soul::xml::MakeElement("td");
        trTypeAliasElement->AppendChild(tdTypeElement);
        soul::xml::Element* typeElement = GenerateTypeXmlElement(currentModule, nullptr, alias->ReferredType());
        tdTypeElement->AppendChild(typeElement);
        otava::symbols::NamespaceSymbol* ns = alias->ParentNamespace();
        soul::xml::Element* tdNsElement = soul::xml::MakeElement("td");
        trTypeAliasElement->AppendChild(tdNsElement);
        soul::xml::Element* linkNsElement = soul::xml::MakeElement("a");
        tdNsElement->AppendChild(linkNsElement);
        linkNsElement->SetAttribute("href", "../../namespace/" + ns->DocName() + "/index.html");
        soul::xml::Text* linkNsText = soul::xml::MakeText(MakeNsText(ns));
        linkNsElement->AppendChild(linkNsText);
    }
}

void ModuleHtmlGenerator::GenerateClassSection()
{
    if (classes.empty()) return;
    std::sort(classes.begin(), classes.end(), otava::symbols::ClassLess());
    soul::xml::Element* h2Element = soul::xml::MakeElement("h2");
    bodyElement->AppendChild(h2Element);
    soul::xml::Text* h2Text = soul::xml::MakeText("Classes");
    h2Element->AppendChild(h2Text);
    soul::xml::Element* tableElement = soul::xml::MakeElement("table");
    bodyElement->AppendChild(tableElement);
    tableElement->SetAttribute("class", "doc");
    soul::xml::Element* trElement = soul::xml::MakeElement("tr");
    tableElement->AppendChild(trElement);
    soul::xml::Element* thClassElement = soul::xml::MakeElement("th");
    trElement->AppendChild(thClassElement);
    soul::xml::Text* thClassText = soul::xml::MakeText("class");
    thClassElement->AppendChild(thClassText);
    soul::xml::Element* thNamespaceElement = soul::xml::MakeElement("th");
    trElement->AppendChild(thNamespaceElement);
    soul::xml::Text* thNamespaceText = soul::xml::MakeText("namespace");
    thNamespaceElement->AppendChild(thNamespaceText);
    for (const auto& cls : classes)
    {
        soul::xml::Element* trClassElement = soul::xml::MakeElement("tr");
        tableElement->AppendChild(trClassElement);
        soul::xml::Element* tdElement = soul::xml::MakeElement("td");
        trClassElement->AppendChild(tdElement);
        soul::xml::Element* linkElement = soul::xml::MakeElement("a");
        tdElement->AppendChild(linkElement);
        linkElement->SetAttribute("href", cls->DocName() + ".html");
        soul::xml::Text* linkText = soul::xml::MakeText(util::ToUtf8(cls->Name()));
        linkElement->AppendChild(linkText);
        otava::symbols::NamespaceSymbol* ns = cls->ParentNamespace();
        soul::xml::Element* tdNsElement = soul::xml::MakeElement("td");
        trClassElement->AppendChild(tdNsElement);
        soul::xml::Element* linkNsElement = soul::xml::MakeElement("a");
        tdNsElement->AppendChild(linkNsElement);
        linkNsElement->SetAttribute("href", "../../namespace/" + ns->DocName() + "/index.html");
        soul::xml::Text* linkNsText = soul::xml::MakeText(MakeNsText(ns));
        linkNsElement->AppendChild(linkNsText);
    }
}

void ModuleHtmlGenerator::GenerateEnumerationSection()
{
    if (enumerations.empty()) return;
    std::sort(enumerations.begin(), enumerations.end(), otava::symbols::EnumTypeLessFunctor());
    soul::xml::Element* h2Element = soul::xml::MakeElement("h2");
    bodyElement->AppendChild(h2Element);
    soul::xml::Text* h2Text = soul::xml::MakeText("Enumerated Types");
    h2Element->AppendChild(h2Text);
    soul::xml::Element* tableElement = soul::xml::MakeElement("table");
    bodyElement->AppendChild(tableElement);
    tableElement->SetAttribute("class", "doc");
    soul::xml::Element* trElement = soul::xml::MakeElement("tr");
    tableElement->AppendChild(trElement);
    soul::xml::Element* thEnumElement = soul::xml::MakeElement("th");
    trElement->AppendChild(thEnumElement);
    soul::xml::Text* thEnumText = soul::xml::MakeText("enum type");
    thEnumElement->AppendChild(thEnumText);
    soul::xml::Element* thNamespaceElement = soul::xml::MakeElement("th");
    trElement->AppendChild(thNamespaceElement);
    soul::xml::Text* thNamespaceText = soul::xml::MakeText("namespace");
    thNamespaceElement->AppendChild(thNamespaceText);
    for (const auto& enumType : enumerations)
    {
        soul::xml::Element* trEnumElement = soul::xml::MakeElement("tr");
        tableElement->AppendChild(trEnumElement);
        soul::xml::Element* tdElement = soul::xml::MakeElement("td");
        trEnumElement->AppendChild(tdElement);
        soul::xml::Element* linkElement = soul::xml::MakeElement("a");
        tdElement->AppendChild(linkElement);
        linkElement->SetAttribute("href", enumType->DocName() + ".html");
        soul::xml::Text* linkText = soul::xml::MakeText(util::ToUtf8(enumType->Name()));
        linkElement->AppendChild(linkText);
        otava::symbols::NamespaceSymbol* ns = enumType->ParentNamespace();
        soul::xml::Element* tdNsElement = soul::xml::MakeElement("td");
        trEnumElement->AppendChild(tdNsElement);
        soul::xml::Element* linkNsElement = soul::xml::MakeElement("a");
        tdNsElement->AppendChild(linkNsElement);
        linkNsElement->SetAttribute("href", "../../namespace/" + ns->DocName() + "/index.html");
        soul::xml::Text* linkNsText = soul::xml::MakeText(MakeNsText(ns));
        linkNsElement->AppendChild(linkNsText);
    }
}

void ModuleHtmlGenerator::GenerateFunctionSection()
{
    if (functions.empty()) return;
    std::sort(functions.begin(), functions.end(), otava::symbols::FunctionLess());
    soul::xml::Element* h2Element = soul::xml::MakeElement("h2");
    bodyElement->AppendChild(h2Element);
    soul::xml::Text* h2Text = soul::xml::MakeText("Functions");
    h2Element->AppendChild(h2Text);
    soul::xml::Element* tableElement = soul::xml::MakeElement("table");
    bodyElement->AppendChild(tableElement);
    tableElement->SetAttribute("class", "doc");
    soul::xml::Element* trElement = soul::xml::MakeElement("tr");
    tableElement->AppendChild(trElement);
    soul::xml::Element* thSpecifiersElement = soul::xml::MakeElement("th");
    trElement->AppendChild(thSpecifiersElement);
    soul::xml::Text* thSpecifierText = soul::xml::MakeText("specifiers");
    thSpecifiersElement->AppendChild(thSpecifierText);
    soul::xml::Element* thReturnTypeElement = soul::xml::MakeElement("th");
    trElement->AppendChild(thReturnTypeElement);
    soul::xml::Text* thReturnTypeText = soul::xml::MakeText("return type");
    thReturnTypeElement->AppendChild(thReturnTypeText);
    soul::xml::Element* thFunctionElement = soul::xml::MakeElement("th");
    trElement->AppendChild(thFunctionElement);
    soul::xml::Text* thFunctionText = soul::xml::MakeText("function");
    thFunctionElement->AppendChild(thFunctionText);
    soul::xml::Element* thNamespaceElement = soul::xml::MakeElement("th");
    trElement->AppendChild(thNamespaceElement);
    soul::xml::Text* thNamespaceText = soul::xml::MakeText("namespace");
    thNamespaceElement->AppendChild(thNamespaceText);
    for (const auto& function : functions)
    {
        otava::symbols::NamespaceSymbol* ns = function->ParentNamespace();
        soul::xml::Element* trElement = soul::xml::MakeElement("tr");
        tableElement->AppendChild(trElement);
        soul::xml::Element* tdSpecifiersElement = soul::xml::MakeElement("td");
        trElement->AppendChild(tdSpecifiersElement);
        soul::xml::Element* spanSpecifierElement = soul::xml::MakeElement("span");
        tdSpecifiersElement->AppendChild(spanSpecifierElement);
        spanSpecifierElement->SetAttribute("class", "specifier");
        spanSpecifierElement->SetAttribute("xml:space", "preserve");
        otava::symbols::DeclarationFlags flags = function->GetDeclarationFlags();
        std::string specifierStr = otava::symbols::DeclarationFlagStr(flags);
        if (!specifierStr.empty())
        {
            soul::xml::Text* specifierText = soul::xml::MakeText(specifierStr);
            spanSpecifierElement->AppendChild(specifierText);
        }
        soul::xml::Element* tdElement = soul::xml::MakeElement("td");
        tdElement->SetAttribute("class", "right");
        trElement->AppendChild(tdElement);
        if (function->ReturnType())
        {
            soul::xml::Element* returnTypeElement = GenerateTypeXmlElement(currentModule, nullptr, function->ReturnType());
            tdElement->AppendChild(returnTypeElement);
        }
        soul::xml::Element* tdFunctionElement = soul::xml::MakeElement("td");
        trElement->AppendChild(tdFunctionElement);
        tdFunctionElement->SetAttribute("id", function->DocName());
        soul::xml::Element* spanElement = soul::xml::MakeElement("span");
        spanElement->SetAttribute("xml:space", "preserve");
        soul::xml::Text* functionNameText = soul::xml::MakeText(util::ToUtf8(function->Name()));
        spanElement->AppendChild(functionNameText);
        tdFunctionElement->AppendChild(spanElement);
        soul::xml::Text* lparenText = soul::xml::MakeText("(");
        spanElement->AppendChild(lparenText);
        bool first = true;
        for (const auto& parameter : function->Parameters())
        {
            if (first)
            {
                first = false;
            }
            else
            {
                soul::xml::Text* commaText = soul::xml::MakeText(", ");
                spanElement->AppendChild(commaText);
            }
            otava::symbols::TypeSymbol* parameterType = parameter->GetType();
            soul::xml::Element* typeElement = GenerateTypeXmlElement(currentModule, nullptr, parameterType);
            spanElement->AppendChild(typeElement);
            if (!parameter->Name().empty())
            {
                soul::xml::Text* paramNameText = soul::xml::MakeText(" " + util::ToUtf8(parameter->Name()));
                spanElement->AppendChild(paramNameText);
            }
            if (parameter->DefaultValue())
            {
                otava::symbols::TypeSymbol* charPtrType = otava::symbols::CurrentContext()->GetSymbolTable()->MakeConstCharPtrType(otava::symbols::CurrentContext());
                AddValue(spanElement, 
                    new otava::symbols::StringValue(util::ToUtf8(parameter->DefaultValue()->Str()), charPtrType), currentModule, nullptr);
            }
        }
        soul::xml::Text* rparenText = soul::xml::MakeText(")");
        spanElement->AppendChild(rparenText);
        std::string qualifierStr = otava::symbols::MakeFunctionQualifierStr(function->Qualifiers());
        if (!qualifierStr.empty())
        {
            soul::xml::Element* spanQualifierElement = soul::xml::MakeElement("span");
            spanQualifierElement->SetAttribute("class", "specifier");
            soul::xml::Text* qualifierText = soul::xml::MakeText(" " + qualifierStr);
            spanQualifierElement->AppendChild(qualifierText);
            spanElement->AppendChild(spanQualifierElement);
        }
        if (function->IsNoExcept())
        {
            soul::xml::Element* spanNoexceptElement = soul::xml::MakeElement("span");
            spanNoexceptElement->SetAttribute("class", "specifier");
            soul::xml::Text* noexceptText = soul::xml::MakeText(" noexcept");
            spanNoexceptElement->AppendChild(noexceptText);
            spanElement->AppendChild(spanNoexceptElement);
        }
        tdFunctionElement->AppendChild(spanElement);
        soul::xml::Element* tdNsElement = soul::xml::MakeElement("td");
        trElement->AppendChild(tdNsElement);
        soul::xml::Element* linkNsElement = soul::xml::MakeElement("a");
        tdNsElement->AppendChild(linkNsElement);
        linkNsElement->SetAttribute("href", "../../namespace/" + ns->DocName() + "/index.html");
        soul::xml::Text* linkNsText = soul::xml::MakeText(MakeNsText(ns));
        linkNsElement->AppendChild(linkNsText);
    }
}

void ModuleHtmlGenerator::GenerateVariableSection()
{
    if (variables.empty()) return;
    std::sort(variables.begin(), variables.end(), otava::symbols::VariableLess());
    soul::xml::Element* h2Element = soul::xml::MakeElement("h2");
    bodyElement->AppendChild(h2Element);
    soul::xml::Text* h2Text = soul::xml::MakeText("Member Variables");
    h2Element->AppendChild(h2Text);
    soul::xml::Element* tableElement = soul::xml::MakeElement("table");
    bodyElement->AppendChild(tableElement);
    tableElement->SetAttribute("class", "doc");
    soul::xml::Element* trElement = soul::xml::MakeElement("tr");
    tableElement->AppendChild(trElement);
    soul::xml::Element* thSpecifiersElement = soul::xml::MakeElement("th");
    trElement->AppendChild(thSpecifiersElement);
    soul::xml::Text* thSpecifierText = soul::xml::MakeText("specifiers");
    thSpecifiersElement->AppendChild(thSpecifierText);
    soul::xml::Element* thVariableElement = soul::xml::MakeElement("th");
    trElement->AppendChild(thVariableElement);
    soul::xml::Text* thVariableText = soul::xml::MakeText("variable");
    thVariableElement->AppendChild(thVariableText);
    soul::xml::Element* thTypeElement = soul::xml::MakeElement("th");
    trElement->AppendChild(thTypeElement);
    soul::xml::Text* thTypeText = soul::xml::MakeText("type");
    thTypeElement->AppendChild(thTypeText);
    soul::xml::Element* thInitiazerElement = soul::xml::MakeElement("th");
    trElement->AppendChild(thInitiazerElement);
    soul::xml::Text* tInitializerText = soul::xml::MakeText("initializer");
    thInitiazerElement->AppendChild(tInitializerText);
    for (const auto& variable : variables)
    {
        soul::xml::Element* trElement = soul::xml::MakeElement("tr");
        tableElement->AppendChild(trElement);
        soul::xml::Element* tdSpecifiersElement = soul::xml::MakeElement("td");
        trElement->AppendChild(tdSpecifiersElement);
        soul::xml::Element* spanSpecifierElement = soul::xml::MakeElement("span");
        tdSpecifiersElement->AppendChild(spanSpecifierElement);
        spanSpecifierElement->SetAttribute("class", "specifier");
        spanSpecifierElement->SetAttribute("xml:space", "preserve");
        otava::symbols::DeclarationFlags flags = variable->GetDeclarationFlags();
        std::string specifierStr = otava::symbols::DeclarationFlagStr(flags);
        if (!specifierStr.empty())
        {
            soul::xml::Text* specifierText = soul::xml::MakeText(specifierStr);
            spanSpecifierElement->AppendChild(specifierText);
        }
        soul::xml::Element* tdElement = soul::xml::MakeElement("td");
        tdElement->SetAttribute("id", variable->DocName());
        soul::xml::Text* tdVariableText = soul::xml::MakeText(util::ToUtf8(variable->Name()));
        tdElement->AppendChild(tdVariableText);
        trElement->AppendChild(tdElement);
        soul::xml::Element* tdTypeElement = soul::xml::MakeElement("td");
        trElement->AppendChild(tdTypeElement);
        soul::xml::Element* typeElement = GenerateTypeXmlElement(currentModule, nullptr, variable->GetDeclaredType());
        tdTypeElement->AppendChild(typeElement);
        if (variable->GetValue())
        {
            soul::xml::Element* tdInitializerElement = soul::xml::MakeElement("td");
            trElement->AppendChild(tdInitializerElement);
            AddValue(tdInitializerElement, variable->GetValue(), currentModule, nullptr);
        }
    }
}

void ModuleHtmlGenerator::GenerateClassDocs()
{
    if (classes.empty()) return;
    for (const auto& classTypeSymbol : classes)
    {
        GenerateClassHtml(util::Path::GetDirectoryName(filePath), currentModule, classTypeSymbol);
    }
}

void ModuleHtmlGenerator::GenerateEnumDocs()
{
    if (enumerations.empty()) return;
    for (const auto& enumTypeSymbol : enumerations)
    {
        GenerateEnumHtml(util::Path::GetDirectoryName(filePath), currentModule, enumTypeSymbol);
    }
}

void ModuleHtmlGenerator::WriteDoc()
{
    GenerateNamespaceSection();
    GenerateClassSection();
    GenerateEnumerationSection();
    GenerateTypeAliasSection();
    GenerateFunctionSection();
    GenerateVariableSection();
    std::ofstream file(filePath);
    if (!file)
    {
        otava::symbols::SetExceptionThrown();
        throw std::runtime_error("could not create file '" + filePath + "'");
    }
    util::CodeFormatter formatter(file);
    formatter.SetIndentSize(1);
    doc.Write(formatter);
    GenerateClassDocs();
    GenerateEnumDocs();
}

void GenerateModuleHtml(Project* project, const std::string& rootDir, otava::symbols::Module* module, otava::symbols::ModuleMapper& moduleMapper, Project* nsProject)
{
    module->LoadImplementationUnits(moduleMapper, "gendoc", 0, project->Configurations(), otava::symbols::CurrentContext());
    ModuleHtmlGenerator generator(rootDir, nsProject);
    module->Accept(generator);
    generator.WriteDoc();
    GenerateFileHtml(module, generator.ModuleDir());
}

} // namespace gendoc
