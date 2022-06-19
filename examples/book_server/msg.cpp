module msg;

namespace msg {

std::unique_ptr<book_msg::Request> MakeBookRequest(const std::string& bookId)
{
    std::unique_ptr<book_msg::BookRequest> request(new book_msg::BookRequest());
    request->kind = book_msg::RequestKind::bookRequest;
    request->bookId = bookId;
    return std::unique_ptr<book_msg::Request>(request.release());
}

std::unique_ptr<book_msg::Request> MakeStopRequest()
{
    std::unique_ptr<book_msg::StopRequest> request(new book_msg::StopRequest());
    request->kind = book_msg::RequestKind::stopRequest;
    return std::unique_ptr<book_msg::Request>(request.release());
}

std::unique_ptr<book_msg::Reply> MakeBookReply(book_msg::Book&& book)
{
    std::unique_ptr<book_msg::BookReply> reply(new book_msg::BookReply());
    reply->kind = book_msg::ReplyKind::bookReply;
    reply->book = std::move(book);
    return std::unique_ptr<book_msg::Reply>(reply.release());
}

std::unique_ptr<book_msg::Reply> MakeStopReply()
{
    std::unique_ptr<book_msg::StopReply> reply(new book_msg::StopReply());
    reply->kind = book_msg::ReplyKind::stopReply;
    return std::unique_ptr<book_msg::Reply>(reply.release());
}

std::unique_ptr<book_msg::Reply> MakeErrorReply(const std::string& errorMsg)
{
    std::unique_ptr<book_msg::ErrorReply> reply(new book_msg::ErrorReply());
    reply->kind = book_msg::ReplyKind::errorReply;
    reply->errorMessage = errorMsg;
    return std::unique_ptr<book_msg::Reply>(reply.release());
}

} // namespace msg;
