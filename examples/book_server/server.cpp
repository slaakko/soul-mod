module server;

import std.core;
import util;
import soul.xml.document;
import soul.xml.dom.parser;
import soul.xml.xpath.evaluate;
import soul.xml.xpath.object;
import soul.xml.serialization.imp;
import book_msg;
import msg;

namespace book_server {

class Server
{
public:
    static Server& Instance();
    void Start(int port);
    void Run();
    void ThrowError();
    ~Server();
private:
    Server();
    std::unique_ptr<book_msg::Reply> HandleRequest(book_msg::Request* request);
    std::unique_ptr<book_msg::Reply> HandleBookRequest(book_msg::BookRequest* request);
    std::unique_ptr<book_msg::Reply> HandleStopRequest(book_msg::StopRequest* request);
    book_msg::Book GetBook(const std::string& bookId) const;
    int port;
    bool exiting;
    std::thread thread;
    util::TcpSocket socket;
    std::exception_ptr exception;
    std::unique_ptr<soul::xml::Document> libraryXmlDoc;
};

Server::Server() : port(0), exiting(false)
{
    libraryXmlDoc = soul::xml::ParseXmlFile("../../soul/xml/xml_test_data/library.xml");
}

Server::~Server()
{
    try
    {
        if (thread.joinable())
        {
            thread.join();
        }
    }
    catch (...)
    {
    }
}

Server& Server::Instance()
{
    static Server instance;
    return instance;
}

void RunServer()
{
    Server::Instance().Run();
}

void Server::Start(int port_)
{
    port = port_;
    thread = std::thread(RunServer);
}

void Server::ThrowError()
{
    if (exception)
    {
        std::rethrow_exception(exception);
    }
}

std::unique_ptr<book_msg::Reply> Server::HandleRequest(book_msg::Request* request)
{
    try
    {
        switch (request->kind)
        {
            case book_msg::RequestKind::bookRequest:
            {
                return HandleBookRequest(static_cast<book_msg::BookRequest*>(request));
            }
            case book_msg::RequestKind::stopRequest:
            {
                return HandleStopRequest(static_cast<book_msg::StopRequest*>(request));
            }
            default:
            {
                return msg::MakeErrorReply("book server error: unknown request kind");
            }
        }
    }
    catch (const std::exception& ex)
    {
        return msg::MakeErrorReply("book server error: " + std::string(ex.what()));
    }
}

std::unique_ptr<book_msg::Reply> Server::HandleBookRequest(book_msg::BookRequest* request)
{
    return msg::MakeBookReply(GetBook(request->bookId));
}

std::unique_ptr<book_msg::Reply> Server::HandleStopRequest(book_msg::StopRequest* request)
{
    exiting = true;
    return msg::MakeStopReply();
}

std::string GetBookName(soul::xml::Element* bookElement) 
{
    std::unique_ptr<soul::xml::xpath::NodeSet> nameNodeSet = soul::xml::xpath::EvaluateToNodeSet("name", bookElement);
    if (nameNodeSet->Count() > 0)
    {
        soul::xml::Node* node = nameNodeSet->GetNode(0);
        if (node->IsElementNode())
        {
            soul::xml::Element* bookNameElement = static_cast<soul::xml::Element*>(node);
            return bookNameElement->GetAttribute("value");
        }
    }
    return std::string();
}

util::Date GetBookPublishingDate(soul::xml::Element* bookElement) 
{
    std::unique_ptr<soul::xml::xpath::NodeSet> publishedNodeSet = soul::xml::xpath::EvaluateToNodeSet("created", bookElement);
    if (publishedNodeSet->Count() > 0)
    {
        soul::xml::Node* node = publishedNodeSet->GetNode(0);
        if (node->IsElementNode())
        {
            soul::xml::Element* bookPublishedElement = static_cast<soul::xml::Element*>(node);
            return util::ParseDate(bookPublishedElement->GetAttribute("value"));
        }
    }
    return util::Date();
}

soul::xml::Element* GetObject(soul::xml::Document* libraryXmlDoc, const std::string& objectId)
{
    std::unique_ptr<soul::xml::xpath::NodeSet> nodeSet = soul::xml::xpath::EvaluateToNodeSet("//object[@id='" + objectId + "']", libraryXmlDoc);
    if (nodeSet->Count() > 0)
    {
        soul::xml::Node* node = nodeSet->GetNode(0);
        if (node->IsElementNode())
        {
            return static_cast<soul::xml::Element*>(node);
        }
    }
    return nullptr;
}

std::string GetPersonName(soul::xml::Element* personElement)
{
    std::unique_ptr<soul::xml::xpath::NodeSet> nameNodeSet = soul::xml::xpath::EvaluateToNodeSet("name", personElement);
    if (nameNodeSet->Count() > 0)
    {
        soul::xml::Node* node = nameNodeSet->GetNode(0);
        if (node->IsElementNode())
        {
            soul::xml::Element* personNameElement = static_cast<soul::xml::Element*>(node);
            return personNameElement->GetAttribute("value");
        }
    }
    return std::string();
}

std::vector<std::string> GetGroupMembers(soul::xml::Element* groupElement, soul::xml::Document* libraryXmlDoc)
{
    std::vector<std::string> members;
    std::unique_ptr<soul::xml::xpath::NodeSet> memberNodeSet = soul::xml::xpath::EvaluateToNodeSet("members/item", groupElement);
    int n = memberNodeSet->Count();
    for (int i = 0; i < n; ++i)
    {
        soul::xml::Node* node = memberNodeSet->GetNode(i);
        if (node->IsElementNode())
        {
            soul::xml::Element* memberElement = static_cast<soul::xml::Element*>(node);
            std::string memberObjectId = memberElement->GetAttribute("objectID");
            if (!memberObjectId.empty())
            {
                soul::xml::Element* memberObject = GetObject(libraryXmlDoc, memberObjectId);
                if (memberObject)
                {
                    members.push_back(GetPersonName(memberObject));
                }
            }
        }
    }
    return members;
}

std::vector<std::string> GetBookAuthors(soul::xml::Element* bookElement, soul::xml::Document* libraryXmlDoc) 
{
    std::vector<std::string> authors;
    std::unique_ptr<soul::xml::xpath::NodeSet> authorNodeSet = soul::xml::xpath::EvaluateToNodeSet("author", bookElement);
    if (authorNodeSet->Count() > 0)
    {
        soul::xml::Node* node = authorNodeSet->GetNode(0);
        if (node->IsElementNode())
        {
            soul::xml::Element* authorElement = static_cast<soul::xml::Element*>(node);
            std::string authorObjectId = authorElement->GetAttribute("objectID");
            soul::xml::Element* authorObject = GetObject(libraryXmlDoc, authorObjectId);
            if (authorObject)
            {
                std::string kind = authorObject->GetAttribute("kind");
                if (kind == "person")
                {
                    authors.push_back(GetPersonName(authorObject));
                }
                else if (kind == "group")
                {
                    authors = GetGroupMembers(authorObject, libraryXmlDoc);
                }
            }
        }
    }
    return authors;
}

book_msg::Book Server::GetBook(const std::string& bookId) const
{
    book_msg::Book book;
    std::unique_ptr<soul::xml::xpath::NodeSet> nodeSet = soul::xml::xpath::EvaluateToNodeSet("/library/objects/object[@kind='book'][@id='" + bookId + "']", libraryXmlDoc.get());
    if (nodeSet->Count() == 1)
    {
        soul::xml::Node* node = nodeSet->GetNode(0);
        if (node->IsElementNode())
        {
            soul::xml::Element* bookElement = static_cast<soul::xml::Element*>(node);
            book.name = GetBookName(bookElement);
            book.published = GetBookPublishingDate(bookElement);
            book.authors = GetBookAuthors(bookElement, libraryXmlDoc.get());
        }
        else
        {
            throw std::runtime_error("book with id '" + bookId + "' not found");
        }
    }
    else if (nodeSet->Count() == 0)
    {
        throw std::runtime_error("book with id '" + bookId + "' not found");
    }
    else
    {
        throw std::runtime_error("more than one book matched with id='" + bookId + "'");
    }
    return book;
}

void Server::Run()
{
    try
    {
        socket.Bind(port);
        socket.Listen(10);
        util::TcpSocket client = socket.Accept();
        while (!exiting)
        {
            std::string requestXmlStr = util::ReadStr(client);
            if (!requestXmlStr.empty())
            {
                std::unique_ptr<book_msg::Request> request = soul::xml::serialization::MakeObject<book_msg::Request>(requestXmlStr, "server");
                std::unique_ptr<book_msg::Reply> reply = HandleRequest(request.get());
                std::string replyXmlStr = reply->ToXmlString();
                util::Write(client, replyXmlStr);
            }
            else
            {
                exiting = true;
            }
        }
    }
    catch (const std::exception& ex)
    {
        std::cerr << "server error: " << ex.what() << std::endl;
        exception = std::current_exception();
    }
}

void Run(int port)
{
    Server::Instance().Start(port);
}

void ThrowError()
{
    Server::Instance().ThrowError();
}

} // namespace book_server
