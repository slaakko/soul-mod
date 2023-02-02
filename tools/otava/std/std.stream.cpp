module std.stream; 

namespace std {

ios_base::ios_base() : fl(fmtflags::dec)
{
}

ios_base::~ios_base()
{
}

ios_base& dec(std::ios_base& strm)
{
    strm.unsetf(std::fmtflags::basefield);
    strm.setf(std::fmtflags::dec);
    return strm;
}

ios_base& hex(std::ios_base& strm)
{
    strm.unsetf(std::fmtflags::basefield);
    strm.setf(std::fmtflags::hex);
    return strm;
}

ios_base& oct(std::ios_base& strm)
{
    strm.unsetf(std::fmtflags::basefield);
    strm.setf(std::fmtflags::oct);
    return strm;
}

} // namespace std
