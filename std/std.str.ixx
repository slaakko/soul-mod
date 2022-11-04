export module std.str;

import std.type.fundamental;

export namespace std {

class str
{
public:
	str();
	~str();
private:
    void* mem;
};

} // namespace std
