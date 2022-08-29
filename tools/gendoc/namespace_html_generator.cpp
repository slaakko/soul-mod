// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module gendoc.namespace_html_generator;

import gendoc.type_element_generator;
import soul.cpp20.symbols;
import soul.xml.dom;
import util;
import std.filesystem;

namespace gendoc {

void GenerateConceptSection(soul::xml::Element* bodyElement, NamespaceSymbols* symbols)
{
    if (symbols->concepts.empty()) return;
    std::sort(symbols->concepts.begin(), symbols->concepts.end(), soul::cpp20::symbols::ConceptLess());
}

void GenerateClassSection(soul::xml::Element* bodyElement, NamespaceSymbols* symbols)
{
    if (symbols->classes.empty()) return;
    std::sort(symbols->classes.begin(), symbols->classes.end(), soul::cpp20::symbols::ClassLess());
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
    for (const auto& cls : symbols->classes)
    {
        soul::cpp20::symbols::Module* module = cls->GetModule();
        std::string moduleName = module->Name();
        soul::xml::Element* trClassElement = soul::xml::MakeElement("tr");
        tableElement->AppendChild(trClassElement);
        soul::xml::Element* tdElement = soul::xml::MakeElement("td");
        trClassElement->AppendChild(tdElement);
        soul::xml::Element* linkElement = soul::xml::MakeElement("a");
        tdElement->AppendChild(linkElement);
        linkElement->SetAttribute("href", "../../module/" + moduleName + "/" + cls->DocName() + ".html");
        soul::xml::Text* linkText = soul::xml::MakeText(util::ToUtf8(cls->Name()));
        linkElement->AppendChild(linkText);
    }
}

void GenerateEnumerationSection(soul::xml::Element* bodyElement, NamespaceSymbols* symbols)
{
    if (symbols->enumerations.empty()) return;
    std::sort(symbols->enumerations.begin(), symbols->enumerations.end(), soul::cpp20::symbols::EnumTypeLess());
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
    for (const auto& enumType : symbols->enumerations)
    {
        soul::cpp20::symbols::Module* module = enumType->GetModule();
        std::string moduleName = module->Name();
        soul::xml::Element* trEnumElement = soul::xml::MakeElement("tr");
        tableElement->AppendChild(trEnumElement);
        soul::xml::Element* tdElement = soul::xml::MakeElement("td");
        trEnumElement->AppendChild(tdElement);
        soul::xml::Element* linkElement = soul::xml::MakeElement("a");
        tdElement->AppendChild(linkElement);
        linkElement->SetAttribute("href", "../../module/" + moduleName + "/" + enumType->DocName() + ".html");
        soul::xml::Text* linkText = soul::xml::MakeText(util::ToUtf8(enumType->Name()));
        linkElement->AppendChild(linkText);
    }
}

void GenerateTypeAliasSection(soul::xml::Element* bodyElement, NamespaceSymbols* symbols)
{
    if (symbols->typeAliases.empty()) return;
    std::sort(symbols->typeAliases.begin(), symbols->typeAliases.end(), soul::cpp20::symbols::AliasTypeLess());
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
    for (const auto& alias : symbols->typeAliases)
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
        soul::xml::Element* typeElement = GenerateTypeXmlElement(nullptr, nullptr, alias->ReferredType());
        tdTypeElement->AppendChild(typeElement);
    }
}

void GenerateFunctionSection(soul::xml::Element* bodyElement, NamespaceSymbols* symbols)
{
    if (symbols->functions.empty()) return;
    std::sort(symbols->functions.begin(), symbols->functions.end(), soul::cpp20::symbols::FunctionLess());
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
    for (const auto& function : symbols->functions)
    {
        soul::cpp20::symbols::Module* module = function->GetModule();
        std::string moduleName = module->Name();
        soul::xml::Element* trElement = soul::xml::MakeElement("tr");
        tableElement->AppendChild(trElement);
        soul::xml::Element* tdSpecifiersElement = soul::xml::MakeElement("td");
        trElement->AppendChild(tdSpecifiersElement);
        soul::xml::Element* spanSpecifierElement = soul::xml::MakeElement("span");
        tdSpecifiersElement->AppendChild(spanSpecifierElement);
        spanSpecifierElement->SetAttribute("class", "specifier");
        soul::cpp20::symbols::DeclarationFlags flags = function->GetDeclarationFlags();
        std::string specifierStr = soul::cpp20::symbols::DeclarationFlagStr(flags);
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
            soul::xml::Element* returnTypeElement = GenerateTypeXmlElement(nullptr, nullptr, function->ReturnType());
            tdElement->AppendChild(returnTypeElement);
        }
        soul::xml::Element* tdFunctionElement = soul::xml::MakeElement("td");
        tdFunctionElement->SetAttribute("id", function->DocName());
        trElement->AppendChild(tdFunctionElement);
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
            soul::cpp20::symbols::TypeSymbol* parameterType = parameter->Type();
            soul::xml::Element* typeElement = GenerateTypeXmlElement(nullptr, nullptr, parameterType);
            spanElement->AppendChild(typeElement);
            if (!parameter->Name().empty())
            {
                soul::xml::Text* paramNameText = soul::xml::MakeText(" " + util::ToUtf8(parameter->Name()));
                spanElement->AppendChild(paramNameText);
            }
            if (parameter->DefaultValue())
            {
                AddValue(spanElement, parameter->DefaultValue(), nullptr, nullptr);
                soul::xml::Text* defaultValueText = soul::xml::MakeText(" = " + util::ToUtf8(parameter->DefaultValue()->ToString()));
                spanElement->AppendChild(defaultValueText);
            }
        }
        soul::xml::Text* rparenText = soul::xml::MakeText(")");
        spanElement->AppendChild(rparenText);
        std::string qualifierStr = soul::cpp20::symbols::MakeFunctionQualifierStr(function->Qualifiers());
        if (!qualifierStr.empty())
        {
            soul::xml::Element* spanQualifierElement = soul::xml::MakeElement("span");
            spanQualifierElement->SetAttribute("class", "specifier");
            soul::xml::Text* qualifierText = soul::xml::MakeText(" " + qualifierStr);
            spanQualifierElement->AppendChild(qualifierText);
            spanElement->AppendChild(spanQualifierElement);
        }
        tdFunctionElement->AppendChild(spanElement);
    }
}

void GenerateVariableSection(soul::xml::Element* bodyElement, NamespaceSymbols* symbols)
{
    if (symbols->variables.empty()) return;
    std::sort(symbols->variables.begin(), symbols->variables.end(), soul::cpp20::symbols::VariableLess());
    soul::xml::Element* h2Element = soul::xml::MakeElement("h2");
    bodyElement->AppendChild(h2Element);
    soul::xml::Text* h2Text = soul::xml::MakeText("Variables");
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
    for (const auto& variable : symbols->variables)
    {
        soul::xml::Element* trElement = soul::xml::MakeElement("tr");
        tableElement->AppendChild(trElement);
        soul::xml::Element* tdSpecifiersElement = soul::xml::MakeElement("td");
        trElement->AppendChild(tdSpecifiersElement);
        soul::xml::Element* spanSpecifierElement = soul::xml::MakeElement("span");
        tdSpecifiersElement->AppendChild(spanSpecifierElement);
        spanSpecifierElement->SetAttribute("class", "specifier");
        soul::cpp20::symbols::DeclarationFlags flags = variable->GetDeclarationFlags();
        std::string specifierStr = soul::cpp20::symbols::DeclarationFlagStr(flags);
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
        soul::xml::Element* typeElement = GenerateTypeXmlElement(nullptr, nullptr, variable->GetType());
        tdTypeElement->AppendChild(typeElement);
        if (variable->GetValue())
        {
            soul::xml::Element* tdInitializerElement = soul::xml::MakeElement("td");
            trElement->AppendChild(tdInitializerElement);
            AddValue(tdInitializerElement, variable->GetValue(), nullptr, nullptr);
        }
    }
}

void GenerateNamespaceHtml(const std::string& rootDir, const std::string& nsDocName, NamespaceSymbols* symbols)
{
    std::string nsDirPath = util::Path::Combine(util::Path::Combine(rootDir, "namespace"), nsDocName);
    std::filesystem::create_directories(nsDirPath);
    std::string nsFilePath = util::Path::Combine(nsDirPath, "index.html");
    std::ofstream nsFile(nsFilePath);
    util::CodeFormatter formatter(nsFile);
    formatter.SetIndentSize(1);
    soul::xml::Element* htmlElement = soul::xml::MakeElement("html");
    soul::xml::Document doc;
    doc.AppendChild(htmlElement);
    soul::xml::Element* headElement = soul::xml::MakeElement("head");
    htmlElement->AppendChild(headElement);
    soul::xml::Element* metaElement = soul::xml::MakeElement("meta");
    metaElement->SetAttribute("charset", "utf-8");
    headElement->AppendChild(metaElement);
    soul::xml::Element* titleElement = soul::xml::MakeElement("title");
    std::string title = symbols->namespaceName + " Namespace";
    soul::xml::Text* titleText = soul::xml::MakeText(title);
    titleElement->AppendChild(titleText);
    headElement->AppendChild(titleElement);
    soul::xml::Element* linkElement = soul::xml::MakeElement("link");
    std::string styleFilePath = "../../style/style.css";
    linkElement->SetAttribute("href", styleFilePath);
    linkElement->SetAttribute("rel", "stylesheet");
    linkElement->SetAttribute("type", "text/css");
    headElement->AppendChild(linkElement);
    soul::xml::Element* bodyElement = soul::xml::MakeElement("body");
    soul::xml::Element* h1Element = soul::xml::MakeElement("h1");
    soul::xml::Text* h1Text = soul::xml::MakeText(title);
    h1Element->AppendChild(h1Text);
    bodyElement->AppendChild(h1Element);
    htmlElement->AppendChild(bodyElement);
    GenerateConceptSection(bodyElement, symbols);
    GenerateClassSection(bodyElement, symbols);
    GenerateEnumerationSection(bodyElement, symbols);
    GenerateTypeAliasSection(bodyElement, symbols);
    GenerateFunctionSection(bodyElement, symbols);
    GenerateVariableSection(bodyElement, symbols);
    doc.Write(formatter);
}

} // namespace gendoc
