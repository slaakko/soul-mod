// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.ast.output;

import otava.ast.source.code.printer.visitor;
import otava.ast.xml.generator.visitor;
import soul.xml.document;
import util.code.formatter;

namespace otava::ast {

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

} // namespace otava::ast