import std.core;
import util;
import server;
import msg;
import book_msg;
import soul.xml.serialization.imp;

void HandleBookReply(book_msg::BookReply* reply)
{
    std::cout << "book: " << reply->book.name << std::endl;
    if (reply->book.authors.size() == 1)
    {
        std::cout << "author: " << reply->book.authors[0] << std::endl;
    }
    else
    {
        std::cout << "authors:" << std::endl;
        for (const auto& author : reply->book.authors)
        {
            std::cout << author << std::endl;
        }
    }
    std::cout << "published: " << reply->book.published.ToString() << std::endl;
}

void HandleErrorReply(book_msg::ErrorReply* reply)
{
    std::cout << reply->errorMessage << std::endl;
}

void HandleStopReply(book_msg::StopReply* reply)
{
    std::cout << "server stopped" << std::endl;
}

void HandleReply(book_msg::Reply* reply)
{
    switch (reply->kind)
    {
        case book_msg::ReplyKind::bookReply:
        {
            HandleBookReply(static_cast<book_msg::BookReply*>(reply));
            break;
        }
        case book_msg::ReplyKind::errorReply:
        {
            HandleErrorReply(static_cast<book_msg::ErrorReply*>(reply));
            break;
        }
        case book_msg::ReplyKind::stopReply:
        {
            HandleStopReply(static_cast<book_msg::StopReply*>(reply));
            break;
        }
    }
}

int main()
{
    try
    {
        util::Init();
        book_server::Run(56780);
        util::TcpSocket socket = util::TcpSocket("127.0.0.1", "56780");
        std::cout << "enter book id, or 'exit'> ";
        std::string request;
        std::cin >> request;
        while (request != "exit")
        {
            std::unique_ptr<book_msg::Request> bookRequest = msg::MakeBookRequest(request);
            std::string requestStr = bookRequest->ToXmlString();
            util::Write(socket, requestStr);
            std::string replyStr = util::ReadStr(socket);
            std::unique_ptr<book_msg::Reply> reply = soul::xml::serialization::MakeObject<book_msg::Reply>(replyStr, "client");
            HandleReply(reply.get());
            std::cout << std::endl;
            std::cout << "enter book id, or 'exit'> ";
            std::cin >> request;
        }
        std::unique_ptr<book_msg::Request> stopRequest = msg::MakeStopRequest();
        std::string requestStr = stopRequest->ToXmlString();
        util::Write(socket, requestStr);
        std::string replyStr = util::ReadStr(socket);
        std::unique_ptr<book_msg::Reply> reply = soul::xml::serialization::MakeObject<book_msg::Reply>(replyStr, "client");
        HandleReply(reply.get());
        book_server::ThrowError();
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
        return 1; 
    }
    util::Done();
    return 0;
}