export module std.hash;

import std.type.fundamental;
import std.basic_string;

export namespace std {

template<class T>
struct hash
{
    size_t operator()(const T& x) const;
};

size_t hash_bytes(uint8_t* x, size_t size);

template<typename charT>
struct hash<std::basic_string<charT>>
{
    size_t operator()(const basic_string<charT>& key) const
    {
        return hash_bytes(static_cast<uint8_t*>(static_cast<void*>(key.c_str())), key.length() * sizeof(charT));
    }
};

} // namespace std
