module std.stream; 

namespace std {

ios_base::ios_base() : fl(fmtflags::dec)
{
}

ios_base::~ios_base()
{
}

fmtflags ios_base::flags() const
{
    return fl;
}

void ios_base::flags(fmtflags f_) 
{
    fl = f_; 
}

void ios_base::setf(fmtflags f_) 
{ 
    fl = fl | f_; 
}

void ios_base::unsetf(fmtflags f_) 
{ 
    fl = fl & ~f_; 
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
