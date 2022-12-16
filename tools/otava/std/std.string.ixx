export module std.string;

import std.type.fundamental;
import std.iterator.reverse;

export namespace std {

class string
{
public:
	using iterator = char*;
	using const_iterator = const char*;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;
	using value_type = char;
	using size_type = ssize_t;
	string();
	~string();
	const char* c_str() const;
	string(const char* chars_);
	string(const char* chars_, size_type len_);
	string(const char* b, const char* e);
	string(const string& that);
	string(string&& that);
	string(size_type count, char c);
	string& append(size_type count, char c);
	void reserve(size_type min_len);
	size_type length() const { return len; }
	size_type size() const { return len; }
	size_type capacity() const { return res; }
	char* data() { return chars; }
	const char* data() const { return chars; }
	bool empty() const { return len == 0; }
	void clear();
	iterator begin() { return chars; }
	const_iterator begin() const { return chars; }
	const_iterator cbegin() const { return chars; }
	iterator end() 
	{ 
		if (chars)
		{
			return chars + len;
		}
		else
		{
			return nullptr;
		}
	}
	const_iterator end() const 
	{ 
		if (chars)
		{
			return chars + len;
		}
		else
		{
			return nullptr;
		}
	}
	const_iterator cend() const
	{
		if (chars)
		{
			return chars + len;
		}
		else
		{
			return nullptr;
		}
	}
private:
	void grow(size_type min_res);
	void deallocate();
	char* chars;
	size_type len;
	size_type res;
};

} // std
