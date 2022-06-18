// this file has been automatically generated from 'C:/work/soul-mod/soul/xml/serialization_test_data/ns.xmlser' by xmlsergen version 4.0.0

export module ns;

import std.core;
import util.uuid;
import util.time;
import soul.xml.element;

export namespace my::ns {

class empty
{
public:
    empty();
    virtual ~empty();
    virtual std::string ClassName() const;
    static std::string StaticClassName();
    static void* Create();
    static void Register();
    void WriteToXmlFile(const std::string& xmlFileName);
    std::string ToXmlString();
    void ReadFromXmlFile(const std::string& xmlFileName);
    void ReadFromXmlString(const std::string& xmlString);
    virtual soul::xml::Element* ToXml(const std::string& fieldName) const;
    virtual void FromXml(soul::xml::Element* element);
public:
};


} // namespace my::ns
