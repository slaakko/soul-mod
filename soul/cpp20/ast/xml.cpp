// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.ast.xml;
import soul.cpp20.ast.xml.generator.visitor;
import soul.cpp20.ast.node;
import soul.xml.dom;
import util.code.formatter;

namespace soul::cpp20::ast {

void WriteXml(Node* node, const std::string& filePath)
{
    XmlGeneratorVisitor generator;
    node->Accept(generator);
    std::unique_ptr<soul::xml::Element> element = generator.GetElement();
    soul::xml::Document doc;
    doc.AppendChild(element.release());
    std::ofstream file(filePath);
    util::CodeFormatter formatter(file);
    formatter.SetIndentSize(1);
    doc.Write(formatter);
}

} // namespace soul::cpp20::ast
