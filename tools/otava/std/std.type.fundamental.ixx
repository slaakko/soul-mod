// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module std.type.fundamental;

export {

using int8_t = char;
using uint8_t = unsigned char;
using int16_t = short;
using uint16_t = unsigned short;
using int32_t = int;
using uint32_t = unsigned int;
using int64_t = long long int;
using uint64_t = unsigned long long int;
using size_t = uint64_t;
using ssize_t = int64_t;
using time_t = int64_t;

} 

export namespace std {

using ::int8_t;
using ::uint8_t;
using ::int16_t;
using ::uint16_t;
using ::int32_t;
using ::uint32_t;
using ::int64_t;
using ::uint64_t;

} // namespace std
