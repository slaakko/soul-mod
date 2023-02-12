// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module;
#include <cstdio>
#include <cstring>

module ort;

import class_info_index;
import context_stack;

void prints(const char* s, int handle)
{
    switch (handle)
    {
        case 1:
        {
            std::fwrite(s, strlen(s), 1, stdout);
            break;
        }
        case 2:
        {
            std::fwrite(s, strlen(s), 1, stderr);
            break;
        }
        default:
        {
            std::fwrite(s, strlen(s), 1, stdout);
            break;
        }
    }
}

void flush_handle(int handle)
{
    switch (handle)
    {
        case 1:
        {
            std::fflush(stdout);
            break;
        }
        case 2:
        {
            std::fflush(stderr);
            break;
        }
        default:
        {
            std::fflush(nullptr);
            break;
        }
    }
}

class Rng
{
public:
    Rng(uint64_t seed_);
    uint8_t Get() { return dist(mt); }
private:
    std::random_device rd;
    uint64_t seed;
    std::mt19937_64 mt;
    std::uniform_int_distribution<> dist;
};

uint64_t GetSeed(uint64_t seed, std::random_device& rd)
{
    if (seed == -1)
    {
        return static_cast<uint64_t>(rd()) ^ static_cast<uint64_t>(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    }
    else
    {
        return seed;
    }
}

Rng::Rng(uint64_t seed_) : rd(), seed(GetSeed(seed_, rd)), mt(seed), dist(0, 255)
{
}

#ifdef _WIN32

__declspec(thread) uint64_t init_seed = -1;
__declspec(thread) Rng* rng = nullptr;

#else

__thread uint64_t init_seed = -1;
__thread Rng* rng = nullptr;

#endif

void set_rand_seed(uint64_t seed)
{
    init_seed = seed;
}

uint8_t get_random_byte()
{
    if (!rng)
    {
        rng = new Rng(init_seed);
    }
    return rng->Get();
}

void* current_exception = nullptr;
uint64_t currentExceptionTypeIdHigh = 0;
uint64_t currentExceptionTypeIdLow = 0;

void set_exception(void* ex, uint64_t eth, uint64_t etl)
{
    current_exception = ex;
    currentExceptionTypeIdHigh = eth;
    currentExceptionTypeIdLow = etl;
}

void* get_exception()
{
    return current_exception;
}

void throw_exception()
{
    void* ctx = pop_context();
    if (ctx)
    {
        restore_context(ctx, 1);
    }
    else
    {
        std::cerr << "could not throw exception: no context" << std::endl;
        std::abort();
    }
}

bool handle_exception(uint64_t hth, uint64_t htl)
{
    if (hth == 0 && htl == 0)
    {
        return true; 
    }
    else if (info::is_same_or_has_base(currentExceptionTypeIdHigh, currentExceptionTypeIdLow, hth, htl))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool is_space(int c)
{
    return std::isspace(c);
}

const char* get_env(const char* env)
{
#pragma warning(suppress : 4996)
    return std::getenv(env);
}

void* open_file(const char* path, const char* mode)
{
#pragma warning(suppress : 4996)
    return std::fopen(path, mode);
}

int close_file(void* stream)
{
    return std::fclose(static_cast<FILE*>(stream));
}

int get_char(void* stream)
{
    return std::fgetc(static_cast<FILE*>(stream));
}

int put_char(int character, void* stream)
{
    return std::fputc(character, static_cast<FILE*>(stream));
}

int read_file(void* ptr, size_t size, size_t count, void* stream)
{
    return std::fread(ptr, size, count, static_cast<FILE*>(stream));
}

int write_file(void* ptr, size_t size, size_t count, void* stream)
{
    return std::fwrite(ptr, size, count, static_cast<FILE*>(stream));
}

int eof_file(void* stream)
{
    return std::feof(static_cast<FILE*>(stream));
}

int error_file(void* stream)
{
    return std::ferror(static_cast<FILE*>(stream));
}

int seek_file(void* stream, int offset, int origin)
{
    return std::fseek(static_cast<FILE*>(stream), offset, origin);
}

int tell_file(void* stream)
{
    return std::ftell(static_cast<FILE*>(stream));
}

char* str_error(int errnum)
{
#pragma warning(suppress : 4996)
    return std::strerror(errnum);
}

int error_number()
{
    return errno;
}

void destroy_str(const char* str)
{
    delete str;
}
