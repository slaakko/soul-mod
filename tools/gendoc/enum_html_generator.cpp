// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module gendoc.enum_html_generator;

import util;
import soul.cpp20.symbols;
import soul.xml.dom;

namespace gendoc {

class EnumHtmlGenerator : public soul::cpp20::symbols::DefaultVisitor
{
public:
    EnumHtmlGenerator(const std::string& modulePath_, soul::cpp20::symbols::Module* module_);
    void Visit(soul::cpp20::symbols::EnumeratedTypeSymbol& symbol) override;
    void Visit(soul::cpp20::symbols::EnumConstantSymbol& symbol) override;
    void WriteDoc();
private:
    void GenerateEnumConstantTable();
    std::string modulePath;
    soul::cpp20::symbols::Module* module;
    std::string filePath;
    soul::xml::Document doc;
    soul::xml::Element* bodyElement;
    soul::xml::Element* currentElement;
    std::vector<soul::cpp20::symbols::EnumConstantSymbol*> enumConstants;
};

EnumHtmlGenerator::EnumHtmlGenerator(const std::string& modulePath_, soul::cpp20::symbols::Module* module_) : 
    modulePath(modulePath_),
    module(module_),
    bodyElement(nullptr),
    currentElement(nullptr)
{
}

void EnumHtmlGenerator::Visit(soul::cpp20::symbols::EnumeratedTypeSymbol& symbol)
{
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
    title.append(" Enumerated Type");
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
    currentElement = bodyElement;
    DefaultVisitor::Visit(symbol);
}

void EnumHtmlGenerator::Visit(soul::cpp20::symbols::EnumConstantSymbol& symbol)
{
    enumConstants.push_back(&symbol);
}

void EnumHtmlGenerator::GenerateEnumConstantTable()
{
    soul::xml::Element* tableElement = soul::xml::MakeElement("table");
    currentElement->AppendChild(tableElement);
    tableElement->SetAttribute("class", "doc");
    soul::xml::Element* trElement = soul::xml::MakeElement("tr");
    tableElement->AppendChild(trElement);
    soul::xml::Element* thEnumConstantElement = soul::xml::MakeElement("th");
    trElement->AppendChild(thEnumConstantElement);
    soul::xml::Text* thEnumConstantText = soul::xml::MakeText("enum constant");
    thEnumConstantElement->AppendChild(thEnumConstantText);
    soul::xml::Element* thValueElement = soul::xml::MakeElement("th");
    trElement->AppendChild(thValueElement);
    soul::xml::Text* thValueText = soul::xml::MakeText("value");
    thValueElement->AppendChild(thValueText);
    for (const auto& enumConstant : enumConstants)
    {
        soul::xml::Element* trEnumConstantElement = soul::xml::MakeElement("tr");
        tableElement->AppendChild(trEnumConstantElement);
        soul::xml::Element* tdElement = soul::xml::MakeElement("td");
        trEnumConstantElement->AppendChild(tdElement);
        tdElement->SetAttribute("id", enumConstant->DocName());
        std::string enumNameStr = util::ToUtf8(enumConstant->Name());
        soul::xml::Text* enumNameText = soul::xml::MakeText(enumNameStr);
        tdElement->AppendChild(enumNameText);
        soul::xml::Element* tdValueElement = soul::xml::MakeElement("td");
        trEnumConstantElement->AppendChild(tdValueElement);
        std::string valueStr = util::ToUtf8(enumConstant->GetValue()->ToString());
        soul::xml::Text* valueText = soul::xml::MakeText(valueStr);
        tdValueElement->AppendChild(valueText);
    }
}

void EnumHtmlGenerator::WriteDoc()
{
    GenerateEnumConstantTable();
    std::ofstream file(filePath);
    util::CodeFormatter formatter(file);
    formatter.SetIndentSize(1);
    doc.Write(formatter);
}

void GenerateEnumHtml(const std::string& modulePath, soul::cpp20::symbols::Module* module, soul::cpp20::symbols::EnumeratedTypeSymbol* enumTypeSymbol)
{
    EnumHtmlGenerator generator(modulePath, module);
    enumTypeSymbol->Accept(generator);
    generator.WriteDoc();
}

} // namespace gendoc
