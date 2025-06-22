export module msg;

import std;
import book_msg;

export namespace msg {

std::unique_ptr<book_msg::Request> MakeBookRequest(const std::string& bookId);
std::unique_ptr<book_msg::Reply> MakeBookReply(book_msg::Book&& book);
std::unique_ptr<book_msg::Request> MakeStopRequest();
std::unique_ptr<book_msg::Reply> MakeStopReply();
std::unique_ptr<book_msg::Reply> MakeErrorReply(const std::string& errorMsg);

} // namespace msg;
