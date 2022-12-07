module std.string;

import std.utilities.utility;
import std.crt;

namespace std {

char32_t nul = 0;

string::string() : chars(nullptr), len(0), res(0)
{
}

string::string(const char* chars_) : chars(nullptr), len(slen(chars_)), res(0)
{
	if (len > 0)
	{
		reserve(len);
		scpy(chars, chars_);
	}
}

string::string(const char* chars_, ssize_t len_) : chars(nullptr), len(0), res(0)
{
	if (len_ > 0)
	{
		reserve(len_);
		len = slencpy(chars, chars_, len_);
	}
}

string::string(const char* begin, const char* end) : string(begin, end - begin)
{
}

string::string(const string& that) : chars(nullptr), len(that.len), res(0)
{
	if (len > 0)
	{
		reserve(len);
		scpy(chars, that.chars);
	}
}

string::string(string&& that) : chars(that.chars), len(that.len), res(that.res)
{
	that.chars = nullptr;
	that.len = 0;
	that.res = 0;
}

string::string(ssize_t count, char c) : chars(nullptr), len(count), res(0)
{
	if (count > 0)
	{
		reserve(count);
		for (ssize_t i = 0; i < count; ++i)
		{
			chars[i] = c;
		}
		chars[count] = '\0';
	}
}

string::~string()
{
	deallocate();
}

const char* string::c_str() const
{
	if (chars)
	{
		return chars;
	}
	else
	{
		return static_cast<const char*>(static_cast<void*>(&nul));
	}
}

void string::reserve(ssize_t min_len)
{
	if (min_len > 0)
	{
		ssize_t min_res = min_len + 1;
		if (min_res > res)
		{
			grow(min_res);
		}
	}
}

void string::grow(ssize_t min_res)
{
	min_res = std::grow_size(min_res);
	char* new_chars = static_cast<char*>(malloc(min_res));
	if (chars)
	{
		scpy(new_chars, chars);
		free(chars);
	}
	chars = new_chars;
	res = min_res;
}

void string::deallocate()
{
	len = 0;
	if (res != 0)
	{
		free(chars);
		res = 0;
	}
	chars = nullptr;
}

} // std
