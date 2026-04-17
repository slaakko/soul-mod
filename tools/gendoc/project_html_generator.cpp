// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module gendoc.project_html_generator;

import gendoc.project;
import soul.xml.dom;
import util;

namespace gendoc {

void GenerateProjectHtml(Project* project, const std::string& rootDir, std::vector<otava::symbols::Module*>& modules)
{
    std::string projectDir = util::GetFullPath(util::Path::Combine(util::Path::Combine(rootDir, "project"), project->BuildProject()->Name()));
    std::filesystem::create_directories(projectDir);
    std::string filePath = util::Path::Combine(projectDir, "index.html");
    soul::xml::Element* htmlElement = soul::xml::MakeElement("html");
    soul::xml::Document doc;
    doc.AppendChild(htmlElement);
    soul::xml::Element* headElement = soul::xml::MakeElement("head");
    htmlElement->AppendChild(headElement);
    soul::xml::Element* metaElement = soul::xml::MakeElement("meta");
    metaElement->SetAttribute("charset", "utf-8");
    headElement->AppendChild(metaElement);
    soul::xml::Element* titleElement = soul::xml::MakeElement("title");
    std::string title = project->BuildProject()->Name() + " Project";
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
    htmlElement->AppendChild(bodyElement);
    soul::xml::Element* h1Element = soul::xml::MakeElement("h1");
    soul::xml::Text* h1Text = soul::xml::MakeText(title);
    h1Element->AppendChild(h1Text);
    bodyElement->AppendChild(h1Element);

    soul::xml::Element* modulesElement = soul::xml::MakeElement("h2");
    soul::xml::Text* modulesText = soul::xml::MakeText("Modules");
    modulesElement->AppendChild(modulesText);
    bodyElement->AppendChild(modulesElement);
    soul::xml::Element* tableElement = soul::xml::MakeElement("table");
    tableElement->SetAttribute("class", "doc");
    bodyElement->AppendChild(tableElement);
    soul::xml::Element* trElement = soul::xml::MakeElement("tr");
    soul::xml::Element* thElement = soul::xml::MakeElement("th");
    soul::xml::Text* moduleText = soul::xml::MakeText("module");
    thElement->AppendChild(moduleText);
    trElement->AppendChild(thElement);
    tableElement->AppendChild(trElement);

    for (const auto* module : modules)
    {
        soul::xml::Element* trElement = soul::xml::MakeElement("tr");
        tableElement->AppendChild(trElement);
        soul::xml::Element* tdElement = soul::xml::MakeElement("td");
        trElement->AppendChild(tdElement);
        soul::xml::Element* linkElement = soul::xml::MakeElement("a");
        tdElement->AppendChild(linkElement);
        linkElement->SetAttribute("href", "../../module/" + module->Name() + "/index.html");
        soul::xml::Text* linkText = soul::xml::MakeText(module->Name());
        linkElement->AppendChild(linkText);
    }

    std::ofstream file(filePath);
    if (!file)
    {
        otava::symbols::SetExceptionThrown();
        throw std::runtime_error("could not create file '" + filePath + "'");
    }
    util::CodeFormatter formatter(file);
    formatter.SetIndentSize(1);
    doc.Write(formatter);
}

} // namespace gendoc
