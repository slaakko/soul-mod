import std;

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};
struct contiguous_iterator_tag : public random_access_iterator_tag {};

template<typename IterT>
struct iterator_traits
{
    using difference_type = typename IterT::difference_type;
    using value_type = typename IterT::value_type;
    using pointer = typename IterT::pointer;
    using reference = typename IterT::reference;
    using iterator_category = typename IterT::iterator_category;
};

template<typename T>
struct iterator_traits<T*>
{
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using iterator_category = random_access_iterator_tag;
};

template<typename T>
struct iterator_traits<const T*>
{
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = const T*;
    using reference = const T&;
    using iterator_category = random_access_iterator_tag;
};

class my_it
{
public:
    using difference_type = std::int64_t;
    using value_type = int;
    using pointer = int*;
    using reference = int&;
    using iterator_category = forward_iterator_tag;
};

int main()
{
    //using myit_tag = iterator_traits<my_it>::iterator_category;
    using ptr_tag = iterator_traits<int*>::iterator_category;
}
