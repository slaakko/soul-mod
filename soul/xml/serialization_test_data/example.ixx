// this file has been automatically generated from 'C:/work/soul-mod/soul/xml/serialization_test_data/example.xmlser' by xmlsergen version 4.0.0

export module example;

import std.core;
import util.uuid;
import util.time;
import soul.xml.element;

export namespace example::ns {

class Data
{
public:
    Data();
    virtual ~Data();
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
    std::string name;
};

class Derived : public Data
{
public:
    Derived();
    std::string ClassName() const override;
    static std::string StaticClassName();
    static void* Create();
    static void Register();
    soul::xml::Element* ToXml(const std::string& fieldName) const override;
    void FromXml(soul::xml::Element* element) override;
public:
    std::string derivedStr;
};

class Contained
{
public:
    Contained();
    virtual ~Contained();
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
    std::string name;
};

class Foo
{
public:
    Foo();
    virtual ~Foo();
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
    std::string name;
    Contained contained;
    std::unique_ptr<Data> data;
    std::vector<std::string> strings;
    std::vector<std::unique_ptr<Data>> datas;
};

class Bar : public Foo
{
public:
    Bar();
    std::string ClassName() const override;
    static std::string StaticClassName();
    static void* Create();
    static void Register();
    soul::xml::Element* ToXml(const std::string& fieldName) const override;
    void FromXml(soul::xml::Element* element) override;
public:
    std::unique_ptr<Data> anotherData;
    Contained anotherContained;
    std::unique_ptr<Derived> derived;
    std::vector<std::unique_ptr<Derived>> derivedVec;
};


} // namespace example::ns
