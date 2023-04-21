// =================================
// Copyright (c) 2023 Seppo Laakko
// Distributed under the MIT license
// =================================

export module ort;

import std.core;

export extern "C" void prints(const char* s, int handle);
export extern "C" void flush_handle(int handle);
export extern "C" void set_rand_seed(uint64_t seed);
export extern "C" uint8_t get_random_byte();
export extern "C" int save_context(void* ctx);
export extern "C" void restore_context(void* ctx, int retval);
export extern "C" void set_exception(void* ex, uint64_t eth, uint64_t etl);
export extern "C" void* get_exception();
export extern "C" void throw_exception();
export extern "C" bool handle_exception(uint64_t hth, uint64_t htl);
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
export extern "C" int64_t current_time();
export extern "C" void current_date(int& yyyy, int& month, int& day);
export extern "C" void current_date_time(int& yyyy, int& month, int& day, int& seconds);
export extern "C" int64_t make_time(int yyyy, int month, int day, int seconds);
export extern "C" int64_t current_ms();
