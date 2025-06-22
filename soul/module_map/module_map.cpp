// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.common.module_map;

import soul.xml.dom;
import soul.xml.dom.parser;
import soul.xml.xpath;
import util;
import std.filesystem;

namespace soul::common {

void ModuleMap::SetRoot(const std::string& root_)
{
    root = root_;
}

void ModuleMap::Read(const std::string& xmlFilePath)
{
    std::unique_ptr<soul::xml::Document> doc = soul::xml::ParseXmlFile(xmlFilePath);
    std::unique_ptr<soul::xml::xpath::NodeSet> nodeSet = soul::xml::xpath::EvaluateToNodeSet("/map/element", doc.get());
    int n = nodeSet->Count();
    for (int i = 0; i < n; ++i)
    {
        soul::xml::Node* node = nodeSet->GetNode(i);
        if (node->IsElementNode())
        {
            soul::xml::Element* element = static_cast<soul::xml::Element*>(node);
            std::string moduleName = element->GetAttribute("module");
            std::string filePath = element->GetAttribute("file");
            MapModule(moduleName, filePath);
        }
    }
}

void ModuleMap::Write(const std::string& xmlFilePath)
{
    soul::xml::Document doc;
    soul::xml::Element* root = soul::xml::MakeElement("map");
    doc.AppendChild(root);
    for (const auto& p : map)
    {
        soul::xml::Element* element = soul::xml::MakeElement("element");
        element->SetAttribute("module", p.first);
        element->SetAttribute("file", p.second);
        root->AppendChild(element);
    }
    std::ofstream file(xmlFilePath);
    util::CodeFormatter formatter(file);
    formatter.SetIndentSize(1);
    doc.Write(formatter);
}
    
void ModuleMap::MapModule(const std::string& moduleName, const std::string& headerFilePath)
{
    std::string filePath = headerFilePath;
    filePath = util::GetFullPath(util::Path::Combine(root, filePath));
    map[moduleName] = filePath;
}

std::string ModuleMap::GetHeaderFilePath(const std::string& moduleName, const std::string& absoluteDirPath) const
{
    auto it = map.find(moduleName);
    if (it != map.end())
    {
        std::string headerFilePath = it->second;
        return std::filesystem::relative(headerFilePath, absoluteDirPath).generic_string();
    }
    return std::string();
}

} // namespace soul::common
