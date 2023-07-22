// this file has been automatically generated from 'C:/work/soul-mod/examples/book_server/book_msg.xmlser' by xmlsergen version 4.1.0

module book_msg;

import soul.xml.document;
import soul.xml.dom.parser;
import soul.xml.serialization.class_registry;
import soul.xml.serialization.exp;
import soul.xml.serialization.imp;

namespace book_msg {

Book::Book()
     : name(), authors(), published()
{
}

Book::~Book()
{
}

std::string Book::ClassName() const
{
    return "book_msg::Book";
}

std::string Book::StaticClassName()
{
    return "book_msg::Book";
}

void* Book::Create()
{
    return new Book();
}

void Book::Register()
{
    soul::xml::serialization::RegisterClass<Book>();
}

void Book::WriteToXmlFile(const std::string& xmlFileName)
{
    soul::xml::Document xmlDoc;
    xmlDoc.AppendChild(ToXml("Book"));
    std::ofstream xmlFile(xmlFileName);
    util::CodeFormatter formatter(xmlFile);
    formatter.SetIndentSize(2);
    xmlDoc.Write(formatter);
}

std::string Book::ToXmlString()
{
    std::stringstream stringStream;
    soul::xml::Document xmlDoc;
    xmlDoc.AppendChild(ToXml("Book"));
    util::CodeFormatter formatter(stringStream);
    formatter.SetIndentSize(2);
    xmlDoc.Write(formatter);
    return stringStream.str();
}

void Book::ReadFromXmlFile(const std::string& xmlFileName)
{
    std::unique_ptr<soul::xml::Document> xmlDoc = soul::xml::ParseXmlFile(xmlFileName);
    FromXml(xmlDoc->DocumentElement());
}

void Book::ReadFromXmlString(const std::string& xmlString)
{
    std::unique_ptr<soul::xml::Document> xmlDoc = soul::xml::ParseXmlContent(xmlString, "Book");
    FromXml(xmlDoc->DocumentElement());
}

soul::xml::Element* Book::ToXml(const std::string& fieldName) const
{
    soul::xml::Element* element = soul::xml::MakeElement(fieldName);
    element->AppendChild(soul::xml::serialization::ToXml(name, "name"));
    element->AppendChild(soul::xml::serialization::ToXml(authors, "authors"));
    element->AppendChild(soul::xml::serialization::ToXml(published, "published"));
    return element;
}

void Book::FromXml(soul::xml::Element* element)
{
    soul::xml::serialization::FromXml(element, "name", name);
    soul::xml::serialization::FromXml(element, "authors", authors);
    soul::xml::serialization::FromXml(element, "published", published);
}

Request::Request()
     : kind()
{
}

Request::~Request()
{
}

std::string Request::ClassName() const
{
    return "book_msg::Request";
}

std::string Request::StaticClassName()
{
    return "book_msg::Request";
}

void* Request::Create()
{
    return new Request();
}

void Request::Register()
{
    soul::xml::serialization::RegisterClass<Request>();
}

void Request::WriteToXmlFile(const std::string& xmlFileName)
{
    soul::xml::Document xmlDoc;
    xmlDoc.AppendChild(ToXml("Request"));
    std::ofstream xmlFile(xmlFileName);
    util::CodeFormatter formatter(xmlFile);
    formatter.SetIndentSize(2);
    xmlDoc.Write(formatter);
}

std::string Request::ToXmlString()
{
    std::stringstream stringStream;
    soul::xml::Document xmlDoc;
    xmlDoc.AppendChild(ToXml("Request"));
    util::CodeFormatter formatter(stringStream);
    formatter.SetIndentSize(2);
    xmlDoc.Write(formatter);
    return stringStream.str();
}

void Request::ReadFromXmlFile(const std::string& xmlFileName)
{
    std::unique_ptr<soul::xml::Document> xmlDoc = soul::xml::ParseXmlFile(xmlFileName);
    FromXml(xmlDoc->DocumentElement());
}

void Request::ReadFromXmlString(const std::string& xmlString)
{
    std::unique_ptr<soul::xml::Document> xmlDoc = soul::xml::ParseXmlContent(xmlString, "Request");
    FromXml(xmlDoc->DocumentElement());
}

soul::xml::Element* Request::ToXml(const std::string& fieldName) const
{
    soul::xml::Element* element = soul::xml::MakeElement(fieldName);
    element->AppendChild(soul::xml::serialization::ToXml(kind, "kind"));
    return element;
}

void Request::FromXml(soul::xml::Element* element)
{
    soul::xml::serialization::FromXml(element, "kind", kind);
}

BookRequest::BookRequest()
     : Request(), bookId()
{
}

std::string BookRequest::ClassName() const
{
    return "book_msg::BookRequest";
}

std::string BookRequest::StaticClassName()
{
    return "book_msg::BookRequest";
}

void* BookRequest::Create()
{
    return new BookRequest();
}

void BookRequest::Register()
{
    soul::xml::serialization::RegisterClass<BookRequest>();
}

soul::xml::Element* BookRequest::ToXml(const std::string& fieldName) const
{
    soul::xml::Element* element = Request::ToXml(fieldName);
    element->SetAttribute("className", "book_msg::BookRequest");
    element->AppendChild(soul::xml::serialization::ToXml(bookId, "bookId"));
    return element;
}

void BookRequest::FromXml(soul::xml::Element* element)
{
    Request::FromXml(element);
    soul::xml::serialization::FromXml(element, "bookId", bookId);
}

StopRequest::StopRequest()
     : Request()
{
}

std::string StopRequest::ClassName() const
{
    return "book_msg::StopRequest";
}

std::string StopRequest::StaticClassName()
{
    return "book_msg::StopRequest";
}

void* StopRequest::Create()
{
    return new StopRequest();
}

void StopRequest::Register()
{
    soul::xml::serialization::RegisterClass<StopRequest>();
}

soul::xml::Element* StopRequest::ToXml(const std::string& fieldName) const
{
    soul::xml::Element* element = Request::ToXml(fieldName);
    element->SetAttribute("className", "book_msg::StopRequest");
    return element;
}

void StopRequest::FromXml(soul::xml::Element* element)
{
    Request::FromXml(element);
}

Reply::Reply()
     : kind()
{
}

Reply::~Reply()
{
}

std::string Reply::ClassName() const
{
    return "book_msg::Reply";
}

std::string Reply::StaticClassName()
{
    return "book_msg::Reply";
}

void* Reply::Create()
{
    return new Reply();
}

void Reply::Register()
{
    soul::xml::serialization::RegisterClass<Reply>();
}

void Reply::WriteToXmlFile(const std::string& xmlFileName)
{
    soul::xml::Document xmlDoc;
    xmlDoc.AppendChild(ToXml("Reply"));
    std::ofstream xmlFile(xmlFileName);
    util::CodeFormatter formatter(xmlFile);
    formatter.SetIndentSize(2);
    xmlDoc.Write(formatter);
}

std::string Reply::ToXmlString()
{
    std::stringstream stringStream;
    soul::xml::Document xmlDoc;
    xmlDoc.AppendChild(ToXml("Reply"));
    util::CodeFormatter formatter(stringStream);
    formatter.SetIndentSize(2);
    xmlDoc.Write(formatter);
    return stringStream.str();
}

void Reply::ReadFromXmlFile(const std::string& xmlFileName)
{
    std::unique_ptr<soul::xml::Document> xmlDoc = soul::xml::ParseXmlFile(xmlFileName);
    FromXml(xmlDoc->DocumentElement());
}

void Reply::ReadFromXmlString(const std::string& xmlString)
{
    std::unique_ptr<soul::xml::Document> xmlDoc = soul::xml::ParseXmlContent(xmlString, "Reply");
    FromXml(xmlDoc->DocumentElement());
}

soul::xml::Element* Reply::ToXml(const std::string& fieldName) const
{
    soul::xml::Element* element = soul::xml::MakeElement(fieldName);
    element->AppendChild(soul::xml::serialization::ToXml(kind, "kind"));
    return element;
}

void Reply::FromXml(soul::xml::Element* element)
{
    soul::xml::serialization::FromXml(element, "kind", kind);
}

BookReply::BookReply()
     : Reply(), book()
{
}

std::string BookReply::ClassName() const
{
    return "book_msg::BookReply";
}

std::string BookReply::StaticClassName()
{
    return "book_msg::BookReply";
}

void* BookReply::Create()
{
    return new BookReply();
}

void BookReply::Register()
{
    soul::xml::serialization::RegisterClass<BookReply>();
}

soul::xml::Element* BookReply::ToXml(const std::string& fieldName) const
{
    soul::xml::Element* element = Reply::ToXml(fieldName);
    element->SetAttribute("className", "book_msg::BookReply");
    element->AppendChild(soul::xml::serialization::ToXml(book, "book"));
    return element;
}

void BookReply::FromXml(soul::xml::Element* element)
{
    Reply::FromXml(element);
    soul::xml::serialization::FromXml(element, "book", book);
}

StopReply::StopReply()
     : Reply()
{
}

std::string StopReply::ClassName() const
{
    return "book_msg::StopReply";
}

std::string StopReply::StaticClassName()
{
    return "book_msg::StopReply";
}

void* StopReply::Create()
{
    return new StopReply();
}

void StopReply::Register()
{
    soul::xml::serialization::RegisterClass<StopReply>();
}

soul::xml::Element* StopReply::ToXml(const std::string& fieldName) const
{
    soul::xml::Element* element = Reply::ToXml(fieldName);
    element->SetAttribute("className", "book_msg::StopReply");
    return element;
}

void StopReply::FromXml(soul::xml::Element* element)
{
    Reply::FromXml(element);
}

ErrorReply::ErrorReply()
     : Reply(), errorMessage()
{
}

std::string ErrorReply::ClassName() const
{
    return "book_msg::ErrorReply";
}

std::string ErrorReply::StaticClassName()
{
    return "book_msg::ErrorReply";
}

void* ErrorReply::Create()
{
    return new ErrorReply();
}

void ErrorReply::Register()
{
    soul::xml::serialization::RegisterClass<ErrorReply>();
}

soul::xml::Element* ErrorReply::ToXml(const std::string& fieldName) const
{
    soul::xml::Element* element = Reply::ToXml(fieldName);
    element->SetAttribute("className", "book_msg::ErrorReply");
    element->AppendChild(soul::xml::serialization::ToXml(errorMessage, "errorMessage"));
    return element;
}

void ErrorReply::FromXml(soul::xml::Element* element)
{
    Reply::FromXml(element);
    soul::xml::serialization::FromXml(element, "errorMessage", errorMessage);
}


} // namespace book_msg

namespace {

struct Reg
{
    Reg()
    {
        book_msg::Book::Register();
        book_msg::Request::Register();
        book_msg::BookRequest::Register();
        book_msg::StopRequest::Register();
        book_msg::Reply::Register();
        book_msg::BookReply::Register();
        book_msg::StopReply::Register();
        book_msg::ErrorReply::Register();
    }
};

Reg reg;

} // namespace

