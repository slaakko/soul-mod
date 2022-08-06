export module std.container.vector;

import std.type.fundamental;

export namespace std {

template<typename T>
class vector
{
public:
/*
	using value_type = T;
	using reference = value_type&;
	using const_reference = const value_type&;
	using size_type = int64_t;
	using difference_type = int64_t;
	using iterator = value_type*;
	using const_iterator = const value_type*;
	
	vector();
	vector(size_type n);
	vector(size_type n, const T& value);
	template<class InputIterator>
	vector(InputIterator first, InputIterator last);
*/	
	vector(const vector&);
};

} // namespace std
