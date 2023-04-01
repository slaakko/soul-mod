// this file has been automatically generated from 'C:/work/soul-mod/examples/book_server/book_msg.xmlser' by xmlsergen version 4.0.0

export module book_msg;

import std.core;
import util.uuid;
import util.time;
import soul.xml.element;

export namespace book_msg {

class Book
{
public:
    Book();
    virtual ~Book();
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
    std::vector<std::string> authors;
    util::Date published;
};


enum class RequestKind
{
    none
    , bookRequest
    , stopRequest
};

class Request
{
public:
    Request();
    virtual ~Request();
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
    RequestKind kind;
};

class BookRequest : public Request
{
public:
    BookRequest();
    std::string ClassName() const override;
    static std::string StaticClassName();
    static void* Create();
    static void Register();
    soul::xml::Element* ToXml(const std::string& fieldName) const override;
    void FromXml(soul::xml::Element* element) override;
public:
    std::string bookId;
};

class StopRequest : public Request
{
public:
    StopRequest();
    std::string ClassName() const override;
    static std::string StaticClassName();
    static void* Create();
    static void Register();
    soul::xml::Element* ToXml(const std::string& fieldName) const override;
    void FromXml(soul::xml::Element* element) override;
public:
};


enum class ReplyKind
{
    none
    , bookReply
    , stopReply
    , errorReply
};

class Reply
{
public:
    Reply();
    virtual ~Reply();
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
    ReplyKind kind;
};

class BookReply : public Reply
{
public:
    BookReply();
    std::string ClassName() const override;
    static std::string StaticClassName();
    static void* Create();
    static void Register();
    soul::xml::Element* ToXml(const std::string& fieldName) const override;
    void FromXml(soul::xml::Element* element) override;
public:
    Book book;
};

class StopReply : public Reply
{
public:
    StopReply();
    std::string ClassName() const override;
    static std::string StaticClassName();
    static void* Create();
    static void Register();
    soul::xml::Element* ToXml(const std::string& fieldName) const override;
    void FromXml(soul::xml::Element* element) override;
public:
};

class ErrorReply : public Reply
{
public:
    ErrorReply();
    std::string ClassName() const override;
    static std::string StaticClassName();
    static void* Create();
    static void Register();
    soul::xml::Element* ToXml(const std::string& fieldName) const override;
    void FromXml(soul::xml::Element* element) override;
public:
    std::string errorMessage;
};


} // namespace book_msg
