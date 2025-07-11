// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module ort;

import std;

export extern "C" void flush_handle(int handle);
export extern "C" void set_rand_seed(std::uint64_t seed);
export extern "C" std::uint8_t get_random_byte();
export extern "C" bool is_space(int c);
export extern "C" const char* get_env(const char* env);
export extern "C" void* open_file(const char* path, const char* mode);
export extern "C" int close_file(void* stream);
export extern "C" int get_char(void* stream);
export extern "C" int put_char(int character, void* stream);
export extern "C" int read_file(void* ptr, size_t size, size_t count, void* stream);
export extern "C" int write_file(void* ptr, size_t size, size_t count, void* stream);
export extern "C" int puts_file(const char* str, void* stream);
export extern "C" int eof_file(void* stream);
export extern "C" int flush_file(void* stream);
export extern "C" int error_file(void* stream);
export extern "C" int seek_file(void* stream, int offset, int origin);
export extern "C" int tell_file(void* stream);
export extern "C" char* str_error(int errnum);
export extern "C" int error_number();
export extern "C" void destroy_str(const char* str);
export extern "C" void* mem_set(void* dest, int c, size_t count);
export extern "C" char* get_cwd(char* buffer, int maxlen);
export extern "C" bool file_exists(const char* path);
export extern "C" bool dir_exists(const char* path);
export extern "C" bool path_exists(const char* path);
export extern "C" int to_lower(int c);
export extern "C" int to_upper(int c);
export extern "C" bool is_alpha(int c);
export extern "C" bool is_digit(int c);
export extern "C" bool is_atty(int handle);
export extern "C" std::int64_t current_time();
export extern "C" void current_date(int& yyyy, int& month, int& day);
export extern "C" void current_date_time(int& yyyy, int& month, int& day, int& seconds);
export extern "C" std::int64_t make_time(int yyyy, int month, int day, int seconds);
export extern "C" std::int64_t current_ms();
