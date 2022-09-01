// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module gendoc.class_html_generator;

import gendoc.type_element_generator;
import util;
import soul.cpp20.symbols;
import soul.xml.dom;

namespace gendoc {

class ClassHtmlGenerator : public soul::cpp20::symbols::DefaultVisitor
{
public:
    ClassHtmlGenerator(const std::string& modulePath_, soul::cpp20::symbols::Module* module_);
    void Visit(soul::cpp20::symbols::ClassTypeSymbol& symbol) override;
    void Visit(soul::cpp20::symbols::EnumeratedTypeSymbol& symbol) override;
    void Visit(soul::cpp20::symbols::AliasTypeSymbol& symbol) override;
    void Visit(soul::cpp20::symbols::FunctionSymbol& symbol) override;
    void Visit(soul::cpp20::symbols::VariableSymbol& symbol) override;
    void GenerateClassSection();
    void GenerateEnumerationSection();
    void GenerateTypeAliasSection();
    void GenerateFunctionSection();
    void GenerateVariableSection();
    void WriteDoc();
private:
    soul::cpp20::symbols::ClassTypeSymbol* currentClass;
    std::string modulePath;
    soul::cpp20::symbols::Module* module;
    std::string filePath;
    soul::xml::Document doc;
    soul::xml::Element* bodyElement;
    soul::xml::Element* currentElement;
    bool innerClass;
    std::vector<soul::cpp20::symbols::AliasTypeSymbol*> typeAliases;
    std::vector<soul::cpp20::symbols::ClassTypeSymbol*> classes;
    std::vector<soul::cpp20::symbols::EnumeratedTypeSymbol*> enumerations;
    std::vector<soul::cpp20::symbols::FunctionSymbol*> functions;
    std::vector<soul::cpp20::symbols::VariableSymbol*> variables;
};

ClassHtmlGenerator::ClassHtmlGenerator(const std::string& modulePath_, soul::cpp20::symbols::Module* module_) : 
    currentClass(nullptr),
    modulePath(modulePath_), 
    module(module_),
    bodyElement(nullptr), 
    currentElement(nullptr), 
    innerClass(false)
{
}

void ClassHtmlGenerator::Visit(soul::cpp20::symbols::ClassTypeSymbol& symbol)
{
    if (innerClass)
    {
        classes.push_back(&symbol);
    }
    else
    {
        currentClass = &symbol;
        filePath = util::GetFullPath(util::Path::Combine(modulePath, symbol.DocName() + ".html"));
        soul::xml::Element* htmlElement = soul::xml::MakeElement("html");
        doc.AppendChild(htmlElement);
        soul::xml::Element* headElement = soul::xml::MakeElement("head");
        htmlElement->AppendChild(headElement);
        soul::xml::Element* metaElement = soul::xml::MakeElement("meta");
        metaElement->SetAttribute("charset", "utf-8");
        headElement->AppendChild(metaElement);
        soul::xml::Element* titleElement = soul::xml::MakeElement("title");
        std::string title = util::ToUtf8(symbol.Name());
        switch (symbol.GetClassKind())
        {
        case soul::cpp20::symbols::ClassKind::class_:
        {
            title.append(" Class");
            break;
        }
        case soul::cpp20::symbols::ClassKind::struct_:
        {
            title.append(" Struct");
            break;
        }
        case soul::cpp20::symbols::ClassKind::union_:
        {
            title.append(" Union");
            break;
        }
        }
        if (symbol.ParentTemplateDeclaration())
        {
            title.append(" Template");
        }
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
        htmlElement->AppendChild(bodyElement);
        soul::cpp20::symbols::TemplateDeclarationSymbol* templateDeclaration = symbol.ParentTemplateDeclaration();
        if (templateDeclaration)
        {
            soul::xml::Element* h2Element = soul::xml::MakeElement("h2");
            soul::xml::Text* h2Text = soul::xml::MakeText("Template Parameters");;
            h2Element->AppendChild(h2Text);
            bodyElement->AppendChild(h2Element);
            soul::xml::Element* tableElement = soul::xml::MakeElement("table");
            bodyElement->AppendChild(tableElement);
            tableElement->SetAttribute("class", "doc");
            soul::xml::Element* trElement = soul::xml::MakeElement("tr");
            tableElement->AppendChild(trElement);
            soul::xml::Element* thTemplateParameterElement = soul::xml::MakeElement("th");
            trElement->AppendChild(thTemplateParameterElement);
            soul::xml::Text* thTemplateParameterText = soul::xml::MakeText("template parameter");
            thTemplateParameterElement->AppendChild(thTemplateParameterText);
            soul::xml::Element* thConstraintElement = soul::xml::MakeElement("th");
            trElement->AppendChild(thConstraintElement);
            soul::xml::Text* thConstraintText = soul::xml::MakeText("constraint");
            thConstraintElement->AppendChild(thConstraintText);
            for (const auto& templateParameter : templateDeclaration->TemplateParameters())
            {
                soul::xml::Element* trElement = soul::xml::MakeElement("tr");
                tableElement->AppendChild(trElement);
                soul::xml::Element* tdTemplateParameterElement = soul::xml::MakeElement("td");
                tdTemplateParameterElement->SetAttribute("id", templateParameter->DocName());
                trElement->AppendChild(tdTemplateParameterElement);
                soul::xml::Text* templateParameterText = soul::xml::MakeText(util::ToUtf8(templateParameter->Name()));
                tdTemplateParameterElement->AppendChild(templateParameterText);
                soul::xml::Element* tdConstraintElement = soul::xml::MakeElement("td");
                trElement->AppendChild(tdConstraintElement);
                if (templateParameter->Constraint())
                {
                    soul::xml::Text* constraintText = soul::xml::MakeText(util::ToUtf8(templateParameter->Constraint()->Name()));
                    tdConstraintElement->AppendChild(constraintText);
                }
            }
        }
        currentElement = bodyElement;
        innerClass = true;
        DefaultVisitor::Visit(symbol);
        innerClass = false;
    }
}

void ClassHtmlGenerator::Visit(soul::cpp20::symbols::EnumeratedTypeSymbol& symbol)
{
    enumerations.push_back(&symbol);
}

void ClassHtmlGenerator::Visit(soul::cpp20::symbols::AliasTypeSymbol& symbol)
{
    typeAliases.push_back(&symbol);
}

void ClassHtmlGenerator::Visit(soul::cpp20::symbols::FunctionSymbol& symbol)
{
    functions.push_back(&symbol);
}

void ClassHtmlGenerator::Visit(soul::cpp20::symbols::VariableSymbol& symbol)
{
    variables.push_back(&symbol);
}

void ClassHtmlGenerator::GenerateTypeAliasSection()
{
    if (typeAliases.empty()) return;
    std::sort(typeAliases.begin(), typeAliases.end(), soul::cpp20::symbols::AliasTypeLess());
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
        soul::xml::Element* typeElement = GenerateTypeXmlElement(module, currentClass, alias->ReferredType());
        tdTypeElement->AppendChild(typeElement);
    }
}

void ClassHtmlGenerator::GenerateClassSection()
{
    if (classes.empty()) return;
    std::sort(classes.begin(), classes.end(), soul::cpp20::symbols::ClassLess());
    soul::xml::Element* h2Element = soul::xml::MakeElement("h2");
    bodyElement->AppendChild(h2Element);
    soul::xml::Text* h2Text = soul::xml::MakeText("Classes");
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
    soul::xml::Element* thClassElement = soul::xml::MakeElement("th");
    trElement->AppendChild(thClassElement);
    soul::xml::Text* thClassText = soul::xml::MakeText("class");
    thClassElement->AppendChild(thClassText);
    for (const auto& cls : classes)
    {
        soul::xml::Element* trClassElement = soul::xml::MakeElement("tr");
        tableElement->AppendChild(trClassElement);
        soul::xml::Element* tdSpecifiersElement = soul::xml::MakeElement("td");
        trClassElement->AppendChild(tdSpecifiersElement);
        soul::xml::Element* spanSpecifiersElement = soul::xml::MakeElement("span");
        spanSpecifiersElement->SetAttribute("class", "specifier");
        tdSpecifiersElement->AppendChild(spanSpecifiersElement);
        std::string accessStr = soul::cpp20::symbols::AccessStr(cls->GetAccess());
        if (!accessStr.empty())
        {
            soul::xml::Text* accessText = soul::xml::MakeText(accessStr);
            spanSpecifiersElement->AppendChild(accessText);
        }
        soul::xml::Element* tdElement = soul::xml::MakeElement("td");
        trClassElement->AppendChild(tdElement);
        soul::xml::Element* linkElement = soul::xml::MakeElement("a");
        tdElement->AppendChild(linkElement);
        linkElement->SetAttribute("href", cls->DocName() + ".html");
        soul::xml::Text* linkText = soul::xml::MakeText(util::ToUtf8(cls->Name()));
        linkElement->AppendChild(linkText);
    }
}

void ClassHtmlGenerator::GenerateEnumerationSection()
{
    if (enumerations.empty()) return;
    std::sort(enumerations.begin(), enumerations.end(), soul::cpp20::symbols::EnumTypeLess());
    soul::xml::Element* h2Element = soul::xml::MakeElement("h2");
    bodyElement->AppendChild(h2Element);
    soul::xml::Text* h2Text = soul::xml::MakeText("Enumerated Types");
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
    soul::xml::Element* thEnumElement = soul::xml::MakeElement("th");
    trElement->AppendChild(thEnumElement);
    soul::xml::Text* thEnumText = soul::xml::MakeText("enum type");
    thEnumElement->AppendChild(thEnumText);
    for (const auto& enumType : enumerations)
    {
        soul::xml::Element* trEnumElement = soul::xml::MakeElement("tr");
        tableElement->AppendChild(trEnumElement);
        soul::xml::Element* tdSpecifiersElement = soul::xml::MakeElement("td");
        soul::xml::Element* spanSpecifiersElement = soul::xml::MakeElement("span");
        spanSpecifiersElement->SetAttribute("class", "specifier");
        tdSpecifiersElement->AppendChild(spanSpecifiersElement);
        trEnumElement->AppendChild(tdSpecifiersElement);
        std::string accessStr = soul::cpp20::symbols::AccessStr(enumType->GetAccess());
        if (!accessStr.empty())
        {
            soul::xml::Text* accessText = soul::xml::MakeText(accessStr);
            spanSpecifiersElement->AppendChild(accessText);
        }
        soul::xml::Element* tdElement = soul::xml::MakeElement("td");
        trEnumElement->AppendChild(tdElement);
        soul::xml::Element* linkElement = soul::xml::MakeElement("a");
        tdElement->AppendChild(linkElement);
        linkElement->SetAttribute("href", enumType->DocName() + ".html");
        soul::xml::Text* linkText = soul::xml::MakeText(util::ToUtf8(enumType->Name()));
        linkElement->AppendChild(linkText);
    }
}

void ClassHtmlGenerator::GenerateFunctionSection()
{
    if (functions.empty()) return;
    std::sort(functions.begin(), functions.end(), soul::cpp20::symbols::FunctionLess());
    soul::xml::Element* h2Element = soul::xml::MakeElement("h2");
    bodyElement->AppendChild(h2Element);
    soul::xml::Text* h2Text = soul::xml::MakeText("Member Functions");
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
    for (const auto& function : functions)
    {
        soul::xml::Element* trElement = soul::xml::MakeElement("tr");
        tableElement->AppendChild(trElement);
        soul::xml::Element* tdSpecifiersElement = soul::xml::MakeElement("td");
        trElement->AppendChild(tdSpecifiersElement);
        soul::xml::Element* spanSpecifierElement = soul::xml::MakeElement("span");
        tdSpecifiersElement->AppendChild(spanSpecifierElement);
        spanSpecifierElement->SetAttribute("class", "specifier");
        spanSpecifierElement->SetAttribute("xml:space", "preserve");
        std::string accessStr = soul::cpp20::symbols::AccessStr(function->GetAccess());
        if (!accessStr.empty())
        {
            soul::xml::Text* accessText = soul::xml::MakeText(accessStr);
            spanSpecifierElement->AppendChild(accessText);
        }
        soul::cpp20::symbols::DeclarationFlags flags = function->GetDeclarationFlags();
        std::string specifierStr = soul::cpp20::symbols::DeclarationFlagStr(flags);
        if (!specifierStr.empty())
        {
            if (!accessStr.empty())
            {
                spanSpecifierElement->AppendChild(soul::xml::MakeText(" "));
            }
            soul::xml::Text* specifierText = soul::xml::MakeText(specifierStr);
            spanSpecifierElement->AppendChild(specifierText);
        }
        soul::xml::Element* tdElement = soul::xml::MakeElement("td");
        tdElement->SetAttribute("class", "right");
        trElement->AppendChild(tdElement);
        if (function->ReturnType())
        {
            soul::xml::Element* returnTypeElement = GenerateTypeXmlElement(module, currentClass, function->ReturnType());
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
            soul::xml::Element* typeElement = GenerateTypeXmlElement(module, currentClass, parameterType);
            spanElement->AppendChild(typeElement);
            if (!parameter->Name().empty())
            {
                soul::xml::Text* paramNameText = soul::xml::MakeText(" " + util::ToUtf8(parameter->Name()));
                spanElement->AppendChild(paramNameText);
            }
            if (parameter->DefaultValue())
            {
                AddValue(spanElement, parameter->DefaultValue(), module, currentClass);
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

void ClassHtmlGenerator::GenerateVariableSection()
{
    if (variables.empty()) return;
    std::sort(variables.begin(), variables.end(), soul::cpp20::symbols::VariableLess());
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
        std::string accessStr = soul::cpp20::symbols::AccessStr(variable->GetAccess());
        if (!accessStr.empty())
        {
            soul::xml::Text* accessText = soul::xml::MakeText(accessStr);
            spanSpecifierElement->AppendChild(accessText);
        }
        soul::cpp20::symbols::DeclarationFlags flags = variable->GetDeclarationFlags();
        std::string specifierStr = soul::cpp20::symbols::DeclarationFlagStr(flags);
        if (!specifierStr.empty())
        {
            if (!accessStr.empty())
            {
                spanSpecifierElement->AppendChild(soul::xml::MakeText(" "));
            }
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
        soul::xml::Element* typeElement = GenerateTypeXmlElement(module, currentClass, variable->GetType());
        tdTypeElement->AppendChild(typeElement);
        if (variable->GetValue())
        {
            soul::xml::Element* tdInitializerElement = soul::xml::MakeElement("td");
            trElement->AppendChild(tdInitializerElement);
            AddValue(tdInitializerElement, variable->GetValue(), module, currentClass);
        }
    }
}

void ClassHtmlGenerator::WriteDoc()
{
    GenerateClassSection();
    GenerateEnumerationSection();
    GenerateTypeAliasSection();
    GenerateFunctionSection();
    GenerateVariableSection();
    std::ofstream file(filePath);
    util::CodeFormatter formatter(file);
    formatter.SetIndentSize(1);
    doc.Write(formatter);
}

void GenerateClassHtml(const std::string& modulePath, soul::cpp20::symbols::Module* module, soul::cpp20::symbols::ClassTypeSymbol* classTypeSymbol)
{
    ClassHtmlGenerator generator(modulePath, module);
    classTypeSymbol->Accept(generator);
    generator.WriteDoc();
}

} // namespace gendoc
