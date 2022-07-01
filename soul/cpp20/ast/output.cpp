// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.ast.output;

import soul.cpp20.ast.source.code.printer.visitor;
import soul.cpp20.ast.xml.generator.visitor;
import soul.xml.document;
import util.code.formatter;

namespace soul::cpp20::ast {

void PrintSource(Node& node, std::ostream& stream)
{
    SourceCodePrinterVisitor visitor(stream);
    node.Accept(visitor);
    stream << std::endl;
}

void PrintXml(Node& node, std::ostream& stream)
{
    XmlGeneratorVisitor visitor;
    node.Accept(visitor);
    std::unique_ptr<soul::xml::Element> element = visitor.GetElement();
    soul::xml::Document doc;
    doc.AppendChild(element.release());
    util::CodeFormatter formatter(stream);
    formatter.SetIndentSize(2);
    doc.Write(formatter);
}

} // namespace soul::cpp20::ast