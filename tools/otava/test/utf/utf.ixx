export module utf;

import std.core;

inline const std::string& to_utf8(const std::string& s) { return s; }
std::string to_utf8(const std::u16string& s);
std::string to_utf8(const std::u32string& s);
inline const std::u16string& to_utf16(const std::u16string& s) { return s; }
std::u16string to_utf16(const std::string& s);
std::u16string to_utf16(const std::u32string& s);
inline const std::u32string& to_utf32(const std::u32string& s) { return s; }
std::u32string to_utf32(const std::string& s);
std::u32string to_utf32(const std::u16string& s);
