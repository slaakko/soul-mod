// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module std.crt;

import std.type.fundamental;

export {

extern "C" void* malloc(ssize_t size);
extern "C" void free(void* ptr);
extern "C" void prints(const char* s, int handle);
extern "C" void flush_handle(int handle);
extern "C" int save_context(void* ctx);
extern "C" void restore_context(void* ctx, int retval);
extern "C" void* push_context();
extern "C" void* pop_context();
extern "C" void set_exception(void* ex, uint64_t eth, uint64_t etl);
extern "C" void* get_exception();
extern "C" void throw_exception();
extern "C" bool handle_exception(uint64_t hth, uint64_t htl);
extern "C" bool is_space(int c);
extern "C" const char* get_env(const char* env);
extern "C" void* create_mutex();
extern "C" void destroy_mutex(void* mtx);
extern "C" void lock_mutex(void* mtx);
extern "C" void unlock_mutex(void* mtx);
extern "C" bool trylock_mutex(void* mtx);
extern "C" void* create_recursive_mutex();
extern "C" void destroy_recursive_mutex(void* mtx);
extern "C" void lock_recursive_mutex(void* mtx);
extern "C" void unlock_recursive_mutex(void* mtx);
extern "C" bool trylock_recursive_mutex(void* mtx);
extern "C" void* create_atomic_bool();
extern "C" void destroy_atomic_bool(void* a);
extern "C" bool load_atomic_bool(void* a);
extern "C" void store_atomic_bool(void* a, bool value);
extern "C" void* open_file(const char* path, const char* mode);
extern "C" int close_file(void* stream);
extern "C" int get_char(void* stream);
extern "C" int put_char(int character, void* stream);
extern "C" size_t read_file(void* ptr, size_t size, size_t count, void* stream);
extern "C" size_t write_file(const void* ptr, size_t size, size_t count, void* stream);
extern "C" int eof_file(void* stream);
extern "C" int error_file(void* stream);
extern "C" int flush_file(void* stream);
extern "C" int seek_file(void* stream, int offset, int origin);
extern "C" int tell_file(void* stream);
extern "C" char* str_error(int errnum);

}

export namespace std {

using FILE = void;
int SEEK_SET = 0;
int SEEK_CUR = 1;
int SEEK_END = 2;

bool isspace(int c);
const char* getenv(const char* env);
FILE* fopen(const char* path, const char* mode);
int fclose(FILE* stream);
int fgetc(FILE* stream);
int fputc(int character, FILE* stream);
size_t fread(void* ptr, size_t size, size_t count, FILE* stream);
size_t fwrite(const void* ptr, size_t size, size_t count, FILE* stream);
int feof(FILE* stream);
int ferror(FILE* stream);
int fflush(FILE* stream);
int fseek(FILE* stream, long int offset, int origin);
long int ftell(FILE* stream);
char* strerror(int errnum);


} // namespace std
