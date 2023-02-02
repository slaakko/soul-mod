// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module std.crt;

export {

extern "C" void* malloc(ssize_t size);
extern "C" void free(void* ptr);
extern "C" void prints(const char* s, int handle);
extern "C" void flush_file(int handle);
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

}

export namespace std {

inline bool isspace(int c)
{
    return is_space(c);
}
inline const char* getenv(const char* env)
{
    return get_env(env);
}

} // namespace std
