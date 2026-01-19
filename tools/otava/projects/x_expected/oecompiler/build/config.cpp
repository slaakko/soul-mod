
// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.build.config;

import soul.xml.dom;
import soul.xml.dom.parser;
import soul.xml.xpath;
import util;

namespace otava::build {

std::expected<std::string, int> GetVCVars64Path()
{
    std::expected<std::string, int> s = util::SoulRoot();
    if (!s) return s;
    std::string soulRoot = std::move(*s);
    auto cfp = util::GetFullPath(util::Path::Combine(util::Path::Combine(soulRoot, "config"), "otava.config"));
    if (!cfp) return std::unexpected<int>(cfp.error());
    std::string configFilePath = *cfp;
    std::string dirPath = util::Path::GetDirectoryName(configFilePath);
    ort_create_directories(dirPath.c_str());
    if (!ort_path_exists(configFilePath.c_str()))
    {
        soul::xml::Document configDoc;
        soul::xml::Element* configurationElement = soul::xml::MakeElement("configuration");
        auto rv = configDoc.AppendChild(configurationElement);
        if (!rv) return std::unexpected<int>(rv.error());
        soul::xml::Element* vcvars64Element = soul::xml::MakeElement("vcvars64");
        rv = configurationElement->AppendChild(vcvars64Element);
        if (!rv) return std::unexpected<int>(rv.error());
        vcvars64Element->SetAttribute("path", "C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Auxiliary/Build/vcvars64.bat");
        std::ofstream configFile(configFilePath);
        if (!configFile) return std::unexpected<int>(util::AllocateError("could not create file '" + configFilePath + "'"));
        util::CodeFormatter formatter(configFile);
        formatter.SetIndentSize(1);
        rv = configDoc.Write(formatter);
        if (!rv) return std::unexpected<int>(rv.error());
    }
    auto doc = soul::xml::ParseXmlFile(configFilePath);
    if (!doc) return std::unexpected<int>(doc.error());
    std::unique_ptr<soul::xml::Document> configDoc = std::move(*doc);
    auto ns = soul::xml::xpath::EvaluateToNodeSet("/configuration/vcvars64", configDoc.get());
    if (!ns) return std::unexpected<int>(ns.error());
    std::unique_ptr<soul::xml::xpath::NodeSet> nodeSet = std::move(*ns);
    int n = nodeSet->Count();
    for (int i = 0; i < n; ++i)
    {
        auto n = nodeSet->GetNode(i);
        if (!n) return std::unexpected<int>(n.error());
        soul::xml::Node* node = *n;
        if (node->IsElementNode())
        {
            soul::xml::Element* element = static_cast<soul::xml::Element*>(node);
            std::string path = element->GetAttribute("path");
            if (path.empty())
            {
                return std::unexpected<int>(util::AllocateError("/configuration/vcvars64 element has no 'path' attribute"));
            }
            return std::expected<std::string, int>(path);
        }
    }
    return std::expected<std::string, int>(std::string());
}

} // namespace otava::build
