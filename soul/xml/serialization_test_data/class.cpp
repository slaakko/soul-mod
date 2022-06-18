// this file has been automatically generated from 'C:/work/soul-mod/soul/xml/serialization_test_data/class.xmlser' by xmlsergen version 4.0.0

module test_cls;

import soul.xml.document;
import soul.xml.dom.parser;
import soul.xml.serialization.class_registry;
import soul.xml.serialization.exp;
import soul.xml.serialization.imp;

namespace ns {

cls::cls()
     : b0(), sb1(), b2(), s3(), us4(), i5(), ui6(), l7(), ul8(), f9(), d10(), c11(), wc12(), uc13(), u14(), s15(), ws16(), us17(), d18(), d19(), tp20(), du21(), en22()
{
}

cls::~cls()
{
}

std::string cls::ClassName() const
{
    return "ns::cls";
}

std::string cls::StaticClassName()
{
    return "ns::cls";
}

void* cls::Create()
{
    return new cls();
}

void cls::Register()
{
    soul::xml::serialization::RegisterClass<cls>();
}

void cls::WriteToXmlFile(const std::string& xmlFileName)
{
    soul::xml::Document xmlDoc;
    xmlDoc.AppendChild(ToXml("cls"));
    std::ofstream xmlFile(xmlFileName);
    util::CodeFormatter formatter(xmlFile);
    formatter.SetIndentSize(2);
    xmlDoc.Write(formatter);
}

std::string cls::ToXmlString()
{
    std::stringstream stringStream;
    soul::xml::Document xmlDoc;
    xmlDoc.AppendChild(ToXml("cls"));
    util::CodeFormatter formatter(stringStream);
    formatter.SetIndentSize(2);
    xmlDoc.Write(formatter);
    return stringStream.str();
}

void cls::ReadFromXmlFile(const std::string& xmlFileName)
{
    std::unique_ptr<soul::xml::Document> xmlDoc = soul::xml::ParseXmlFile(xmlFileName);
    FromXml(xmlDoc->DocumentElement());
}

void cls::ReadFromXmlString(const std::string& xmlString)
{
    std::unique_ptr<soul::xml::Document> xmlDoc = soul::xml::ParseXmlContent(xmlString, "cls");
    FromXml(xmlDoc->DocumentElement());
}

soul::xml::Element* cls::ToXml(const std::string& fieldName) const
{
    soul::xml::Element* element = soul::xml::MakeElement(fieldName);
    element->AppendChild(soul::xml::serialization::ToXml(b0, "b0"));
    element->AppendChild(soul::xml::serialization::ToXml(sb1, "sb1"));
    element->AppendChild(soul::xml::serialization::ToXml(b2, "b2"));
    element->AppendChild(soul::xml::serialization::ToXml(s3, "s3"));
    element->AppendChild(soul::xml::serialization::ToXml(us4, "us4"));
    element->AppendChild(soul::xml::serialization::ToXml(i5, "i5"));
    element->AppendChild(soul::xml::serialization::ToXml(ui6, "ui6"));
    element->AppendChild(soul::xml::serialization::ToXml(l7, "l7"));
    element->AppendChild(soul::xml::serialization::ToXml(ul8, "ul8"));
    element->AppendChild(soul::xml::serialization::ToXml(f9, "f9"));
    element->AppendChild(soul::xml::serialization::ToXml(d10, "d10"));
    element->AppendChild(soul::xml::serialization::ToXml(c11, "c11"));
    element->AppendChild(soul::xml::serialization::ToXml(wc12, "wc12"));
    element->AppendChild(soul::xml::serialization::ToXml(uc13, "uc13"));
    element->AppendChild(soul::xml::serialization::ToXml(u14, "u14"));
    element->AppendChild(soul::xml::serialization::ToXml(s15, "s15"));
    element->AppendChild(soul::xml::serialization::ToXml(ws16, "ws16"));
    element->AppendChild(soul::xml::serialization::ToXml(us17, "us17"));
    element->AppendChild(soul::xml::serialization::ToXml(d18, "d18"));
    element->AppendChild(soul::xml::serialization::ToXml(d19, "d19"));
    element->AppendChild(soul::xml::serialization::ToXml(tp20, "tp20"));
    element->AppendChild(soul::xml::serialization::ToXml(du21, "du21"));
    element->AppendChild(soul::xml::serialization::ToXml(en22, "en22"));
    return element;
}

void cls::FromXml(soul::xml::Element* element)
{
    soul::xml::serialization::FromXml(element, "b0", b0);
    soul::xml::serialization::FromXml(element, "sb1", sb1);
    soul::xml::serialization::FromXml(element, "b2", b2);
    soul::xml::serialization::FromXml(element, "s3", s3);
    soul::xml::serialization::FromXml(element, "us4", us4);
    soul::xml::serialization::FromXml(element, "i5", i5);
    soul::xml::serialization::FromXml(element, "ui6", ui6);
    soul::xml::serialization::FromXml(element, "l7", l7);
    soul::xml::serialization::FromXml(element, "ul8", ul8);
    soul::xml::serialization::FromXml(element, "f9", f9);
    soul::xml::serialization::FromXml(element, "d10", d10);
    soul::xml::serialization::FromXml(element, "c11", c11);
    soul::xml::serialization::FromXml(element, "wc12", wc12);
    soul::xml::serialization::FromXml(element, "uc13", uc13);
    soul::xml::serialization::FromXml(element, "u14", u14);
    soul::xml::serialization::FromXml(element, "s15", s15);
    soul::xml::serialization::FromXml(element, "ws16", ws16);
    soul::xml::serialization::FromXml(element, "us17", us17);
    soul::xml::serialization::FromXml(element, "d18", d18);
    soul::xml::serialization::FromXml(element, "d19", d19);
    soul::xml::serialization::FromXml(element, "tp20", tp20);
    soul::xml::serialization::FromXml(element, "du21", du21);
    soul::xml::serialization::FromXml(element, "en22", en22);
}


} // namespace ns

namespace {

struct Reg
{
    Reg()
    {
        ns::cls::Register();
    }
};

Reg reg;

} // namespace

