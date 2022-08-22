export module std.utilities.pair;

import std.type.fundamental;

export namespace std {

template<class T, class U>
struct pair
{
    using first_type = T;
    using second_type = U;
    T first;
    U second;
    pair(const pair&) = default;
    pair(pair&&) = default;
    template<class U1, class U2>
    pair(U1&& x, U2&& y);
    template<class U1, class U2>
    pair(const pair<U1, U2>& p);
    template<class U1, class U2>
    pair(pair<U1, U2>&& p);
    pair& operator=(const pair& p);
    template<class U1, class U2>
    pair& operator=(const pair<U1, U2>& p);
    pair& operator=(pair&& p);
    template<class U1, class U2>
    pair& operator=(pair<U1, U2>&& p);
    void swap(pair& p);
};

template<class T, class U>
bool operator==(const pair<T, U>& x, const pair<T, U>& y);
template<class T, class U>
void swap(pair<T, U>& x, pair<T, U>& y);
template<class T, class U>
pair<T, U> make_pair(T&& x, U&& y);

} // namespace std
