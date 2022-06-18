// this file has been automatically generated from 'C:/work/soul-mod/soul/xml/serialization_test_data/empty_class.xmlser' by xmlsergen version 4.0.0

module empty_class;

import soul.xml.document;
import soul.xml.dom.parser;
import soul.xml.serialization.class_registry;
import soul.xml.serialization.exp;
import soul.xml.serialization.imp;

empty::empty()
{
}

empty::~empty()
{
}

std::string empty::ClassName() const
{
    return "empty";
}

std::string empty::StaticClassName()
{
    return "empty";
}

void* empty::Create()
{
    return new empty();
}

void empty::Register()
{
    soul::xml::serialization::RegisterClass<empty>();
}

void empty::WriteToXmlFile(const std::string& xmlFileName)
{
    soul::xml::Document xmlDoc;
    xmlDoc.AppendChild(ToXml("empty"));
    std::ofstream xmlFile(xmlFileName);
    util::CodeFormatter formatter(xmlFile);
    formatter.SetIndentSize(2);
    xmlDoc.Write(formatter);
}

std::string empty::ToXmlString()
{
    std::stringstream stringStream;
    soul::xml::Document xmlDoc;
    xmlDoc.AppendChild(ToXml("empty"));
    util::CodeFormatter formatter(stringStream);
    formatter.SetIndentSize(2);
    xmlDoc.Write(formatter);
    return stringStream.str();
}

void empty::ReadFromXmlFile(const std::string& xmlFileName)
{
    std::unique_ptr<soul::xml::Document> xmlDoc = soul::xml::ParseXmlFile(xmlFileName);
    FromXml(xmlDoc->DocumentElement());
}

void empty::ReadFromXmlString(const std::string& xmlString)
{
    std::unique_ptr<soul::xml::Document> xmlDoc = soul::xml::ParseXmlContent(xmlString, "empty");
    FromXml(xmlDoc->DocumentElement());
}

soul::xml::Element* empty::ToXml(const std::string& fieldName) const
{
    soul::xml::Element* element = soul::xml::MakeElement(fieldName);
    return element;
}

void empty::FromXml(soul::xml::Element* element)
{
}


namespace {

struct Reg
{
    Reg()
    {
        empty::Register();
    }
};

Reg reg;

} // namespace

