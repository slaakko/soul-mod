// this file has been automatically generated from 'C:/work/soul-mod/soul/xml/serialization_test_data/class.xmlser' by xmlsergen version 4.0.0

export module test_cls;

import std.core;
import util.uuid;
import util.time;
import soul.xml.element;

export namespace ns {


enum class enm
{
    first
    , second
    , third
};

class cls
{
public:
    cls();
    virtual ~cls();
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
    bool b0;
    int8_t sb1;
    uint8_t b2;
    int16_t s3;
    uint16_t us4;
    int32_t i5;
    uint32_t ui6;
    int64_t l7;
    uint64_t ul8;
    float f9;
    double d10;
    char c11;
    char16_t wc12;
    char32_t uc13;
    util::uuid u14;
    std::string s15;
    std::u16string ws16;
    std::u32string us17;
    util::Date d18;
    util::DateTime d19;
    std::chrono::steady_clock::time_point tp20;
    std::chrono::steady_clock::duration du21;
    enm en22;
};


} // namespace ns
