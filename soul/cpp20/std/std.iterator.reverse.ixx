export module std.iterator.reverse;

import std.type.fundamental;

export namespace std {

template<typename Iterator>
class reverse_iterator
{
public:
	using iterator_type = Iterator;
	using value_type = typename Iterator::value_type;
	using difference_type = typename Iterator::difference_type;
	using pointer = typename Iterator::pointer;
	using reference = typename Iterator::reference;
	
	reverse_iterator();
	explicit reverse_iterator(Iterator x);
	template<class U>
	reverse_iterator(const reverse_iterator<U>& u);
	template<class U>
	reverse_iterator& operator=(const reverse_iterator<U>& u);
	Iterator base() const;
	reference operator*() const;
	pointer operator->() const;
	reverse_iterator& operator++();
	reverse_iterator operator++(int);
	reverse_iterator& operator--();
	reverse_iterator operator--(int);
	reverse_iterator operator+(difference_type n) const;
	reverse_iterator& operator+=(difference_type n) const;
	reverse_iterator operator-(difference_type n) const;
	reverse_iterator& operator-=(difference_type n) const;
protected:
	Iterator current;
};

} // namespace std
