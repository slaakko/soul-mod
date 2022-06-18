// this file has been automatically generated from 'C:/work/soul-mod/soul/xml/serialization_test_data/example.xmlser' by xmlsergen version 4.0.0

module example;

import soul.xml.document;
import soul.xml.dom.parser;
import soul.xml.serialization.class_registry;
import soul.xml.serialization.exp;
import soul.xml.serialization.imp;

namespace example::ns {

Data::Data()
     : name()
{
}

Data::~Data()
{
}

std::string Data::ClassName() const
{
    return "example::ns::Data";
}

std::string Data::StaticClassName()
{
    return "example::ns::Data";
}

void* Data::Create()
{
    return new Data();
}

void Data::Register()
{
    soul::xml::serialization::RegisterClass<Data>();
}

void Data::WriteToXmlFile(const std::string& xmlFileName)
{
    soul::xml::Document xmlDoc;
    xmlDoc.AppendChild(ToXml("Data"));
    std::ofstream xmlFile(xmlFileName);
    util::CodeFormatter formatter(xmlFile);
    formatter.SetIndentSize(2);
    xmlDoc.Write(formatter);
}

std::string Data::ToXmlString()
{
    std::stringstream stringStream;
    soul::xml::Document xmlDoc;
    xmlDoc.AppendChild(ToXml("Data"));
    util::CodeFormatter formatter(stringStream);
    formatter.SetIndentSize(2);
    xmlDoc.Write(formatter);
    return stringStream.str();
}

void Data::ReadFromXmlFile(const std::string& xmlFileName)
{
    std::unique_ptr<soul::xml::Document> xmlDoc = soul::xml::ParseXmlFile(xmlFileName);
    FromXml(xmlDoc->DocumentElement());
}

void Data::ReadFromXmlString(const std::string& xmlString)
{
    std::unique_ptr<soul::xml::Document> xmlDoc = soul::xml::ParseXmlContent(xmlString, "Data");
    FromXml(xmlDoc->DocumentElement());
}

soul::xml::Element* Data::ToXml(const std::string& fieldName) const
{
    soul::xml::Element* element = soul::xml::MakeElement(fieldName);
    element->AppendChild(soul::xml::serialization::ToXml(name, "name"));
    return element;
}

void Data::FromXml(soul::xml::Element* element)
{
    soul::xml::serialization::FromXml(element, "name", name);
}

Derived::Derived()
     : Data(), derivedStr()
{
}

std::string Derived::ClassName() const
{
    return "example::ns::Derived";
}

std::string Derived::StaticClassName()
{
    return "example::ns::Derived";
}

void* Derived::Create()
{
    return new Derived();
}

void Derived::Register()
{
    soul::xml::serialization::RegisterClass<Derived>();
}

soul::xml::Element* Derived::ToXml(const std::string& fieldName) const
{
    soul::xml::Element* element = Data::ToXml(fieldName);
    element->AppendChild(soul::xml::serialization::ToXml(derivedStr, "derivedStr"));
    return element;
}

void Derived::FromXml(soul::xml::Element* element)
{
    Data::FromXml(element);
    soul::xml::serialization::FromXml(element, "derivedStr", derivedStr);
}

Contained::Contained()
     : name()
{
}

Contained::~Contained()
{
}

std::string Contained::ClassName() const
{
    return "example::ns::Contained";
}

std::string Contained::StaticClassName()
{
    return "example::ns::Contained";
}

void* Contained::Create()
{
    return new Contained();
}

void Contained::Register()
{
    soul::xml::serialization::RegisterClass<Contained>();
}

void Contained::WriteToXmlFile(const std::string& xmlFileName)
{
    soul::xml::Document xmlDoc;
    xmlDoc.AppendChild(ToXml("Contained"));
    std::ofstream xmlFile(xmlFileName);
    util::CodeFormatter formatter(xmlFile);
    formatter.SetIndentSize(2);
    xmlDoc.Write(formatter);
}

std::string Contained::ToXmlString()
{
    std::stringstream stringStream;
    soul::xml::Document xmlDoc;
    xmlDoc.AppendChild(ToXml("Contained"));
    util::CodeFormatter formatter(stringStream);
    formatter.SetIndentSize(2);
    xmlDoc.Write(formatter);
    return stringStream.str();
}

void Contained::ReadFromXmlFile(const std::string& xmlFileName)
{
    std::unique_ptr<soul::xml::Document> xmlDoc = soul::xml::ParseXmlFile(xmlFileName);
    FromXml(xmlDoc->DocumentElement());
}

void Contained::ReadFromXmlString(const std::string& xmlString)
{
    std::unique_ptr<soul::xml::Document> xmlDoc = soul::xml::ParseXmlContent(xmlString, "Contained");
    FromXml(xmlDoc->DocumentElement());
}

soul::xml::Element* Contained::ToXml(const std::string& fieldName) const
{
    soul::xml::Element* element = soul::xml::MakeElement(fieldName);
    element->AppendChild(soul::xml::serialization::ToXml(name, "name"));
    return element;
}

void Contained::FromXml(soul::xml::Element* element)
{
    soul::xml::serialization::FromXml(element, "name", name);
}

Foo::Foo()
     : name(), contained(), data(), strings(), datas()
{
}

Foo::~Foo()
{
}

std::string Foo::ClassName() const
{
    return "example::ns::Foo";
}

std::string Foo::StaticClassName()
{
    return "example::ns::Foo";
}

void* Foo::Create()
{
    return new Foo();
}

void Foo::Register()
{
    soul::xml::serialization::RegisterClass<Foo>();
}

void Foo::WriteToXmlFile(const std::string& xmlFileName)
{
    soul::xml::Document xmlDoc;
    xmlDoc.AppendChild(ToXml("Foo"));
    std::ofstream xmlFile(xmlFileName);
    util::CodeFormatter formatter(xmlFile);
    formatter.SetIndentSize(2);
    xmlDoc.Write(formatter);
}

std::string Foo::ToXmlString()
{
    std::stringstream stringStream;
    soul::xml::Document xmlDoc;
    xmlDoc.AppendChild(ToXml("Foo"));
    util::CodeFormatter formatter(stringStream);
    formatter.SetIndentSize(2);
    xmlDoc.Write(formatter);
    return stringStream.str();
}

void Foo::ReadFromXmlFile(const std::string& xmlFileName)
{
    std::unique_ptr<soul::xml::Document> xmlDoc = soul::xml::ParseXmlFile(xmlFileName);
    FromXml(xmlDoc->DocumentElement());
}

void Foo::ReadFromXmlString(const std::string& xmlString)
{
    std::unique_ptr<soul::xml::Document> xmlDoc = soul::xml::ParseXmlContent(xmlString, "Foo");
    FromXml(xmlDoc->DocumentElement());
}

soul::xml::Element* Foo::ToXml(const std::string& fieldName) const
{
    soul::xml::Element* element = soul::xml::MakeElement(fieldName);
    element->AppendChild(soul::xml::serialization::ToXml(name, "name"));
    element->AppendChild(soul::xml::serialization::ToXml(contained, "contained"));
    element->AppendChild(soul::xml::serialization::ToXml(data, "data"));
    element->AppendChild(soul::xml::serialization::ToXml(strings, "strings"));
    element->AppendChild(soul::xml::serialization::ToXml(datas, "datas"));
    return element;
}

void Foo::FromXml(soul::xml::Element* element)
{
    soul::xml::serialization::FromXml(element, "name", name);
    soul::xml::serialization::FromXml(element, "contained", contained);
    soul::xml::serialization::FromXml(element, "data", data);
    soul::xml::serialization::FromXml(element, "strings", strings);
    soul::xml::serialization::FromXml(element, "datas", datas);
}

Bar::Bar()
     : Foo(), anotherData(), anotherContained(), derived(), derivedVec()
{
}

std::string Bar::ClassName() const
{
    return "example::ns::Bar";
}

std::string Bar::StaticClassName()
{
    return "example::ns::Bar";
}

void* Bar::Create()
{
    return new Bar();
}

void Bar::Register()
{
    soul::xml::serialization::RegisterClass<Bar>();
}

soul::xml::Element* Bar::ToXml(const std::string& fieldName) const
{
    soul::xml::Element* element = Foo::ToXml(fieldName);
    element->AppendChild(soul::xml::serialization::ToXml(anotherData, "anotherData"));
    element->AppendChild(soul::xml::serialization::ToXml(anotherContained, "anotherContained"));
    element->AppendChild(soul::xml::serialization::ToXml(derived, "derived"));
    element->AppendChild(soul::xml::serialization::ToXml(derivedVec, "derivedVec"));
    return element;
}

void Bar::FromXml(soul::xml::Element* element)
{
    Foo::FromXml(element);
    soul::xml::serialization::FromXml(element, "anotherData", anotherData);
    soul::xml::serialization::FromXml(element, "anotherContained", anotherContained);
    soul::xml::serialization::FromXml(element, "derived", derived);
    soul::xml::serialization::FromXml(element, "derivedVec", derivedVec);
}


} // namespace example::ns

namespace {

struct Reg
{
    Reg()
    {
        example::ns::Data::Register();
        example::ns::Derived::Register();
        example::ns::Contained::Register();
        example::ns::Foo::Register();
        example::ns::Bar::Register();
    }
};

Reg reg;

} // namespace

