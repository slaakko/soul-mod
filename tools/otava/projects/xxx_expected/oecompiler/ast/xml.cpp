// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.ast.xml;
import otava.ast.xml.generator.visitor;
import otava.ast.node;
import soul.xml.dom;
import util.code.formatter;
import util.error;

namespace otava::ast {

std::expected<bool, int> WriteXml(Node* node, const std::string& filePath)
{
    XmlGeneratorVisitor generator;
    node->Accept(generator);
    if (!generator) return std::unexpected<int>(generator.Error());
    std::unique_ptr<soul::xml::Element> element = generator.GetElement();
    soul::xml::Document doc;
    std::expected<bool, int> rv = doc.AppendChild(element.release());
    if (!rv) return rv;
    std::ofstream file(filePath);
    if (!file)
    {
        return std::unexpected<int>(util::AllocateError("could not create file '" + filePath + "'"));
    }
    util::CodeFormatter formatter(file);
    formatter.SetIndentSize(1);
    rv = doc.Write(formatter);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

} // namespace otava::ast
