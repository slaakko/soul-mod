export module std.string;

import std.type.fundamental;

export namespace std {

class string
{
public:
	string();
	~string();
	const char* c_str() const;
	string(const char* chars_);
	string(const char* chars_, ssize_t len_);
	string(const char* begin, const char* end);
	string(const string& that);
	string(string&& that);
	string(ssize_t count, char c);
	void reserve(ssize_t min_len);
private:
	void grow(ssize_t min_res);
	void deallocate();
	char* chars;
	ssize_t len;
	ssize_t res;
};

} // std
