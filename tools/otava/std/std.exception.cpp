module std.exception;

namespace std {

const char* exception::what() const
{
    return str.c_str();
}

} // namespace std
