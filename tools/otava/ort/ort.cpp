// =================================
// Copyright (c) 2023 Seppo Laakko
// Distributed under the MIT license
// =================================

module;
#include <cstdio>
#include <cstring>
#include <direct.h>
#include <io.h>
#include <fcntl.h>

module ort;

import class_info_index;
import context_stack;
import std.filesystem;
import util;

bool initialized = false;
bool stdout_tty = false;
bool stderr_tty = false;
util::Utf8ToUtf32Engine stdoutEngine;
util::Utf8ToUtf32Engine stderrEngine;

void init_console()
{
    stdout_tty = _isatty(1);
    if (stdout_tty)
    {
        _setmode(1, _O_U16TEXT);
    }
    stderr_tty = _isatty(2);
    if (stderr_tty)
    {
        _setmode(2, _O_U16TEXT);
    }
    initialized = true;
}

void print_unicode(const char* s, util::Utf8ToUtf32Engine& engine, FILE* file)
{
    std::u32string utf32Chars;
    while (*s)
    {
        engine.Put(*s);
        ++s;
        if (engine.ResultReady())
        {
            utf32Chars.append(1, engine.Result());
        }
    }
    std::u16string utf16Chars(util::ToUtf16(utf32Chars));
    if (!utf16Chars.empty())
    {
        std::fwrite(utf16Chars.c_str(), sizeof(char16_t), utf16Chars.length(), file);
    }
}

void prints(const char* s, int handle)
{
    if (!initialized)
    {
        init_console();
    }
    switch (handle)
    {
        case 1:
        {
            if (stdout_tty)
            {
                print_unicode(s, stdoutEngine, stdout);
            }
            else
            {
                std::fwrite(s, strlen(s), 1, stdout);
            }
            break;
        }
        case 2:
        {
            if (stderr_tty)
            {
                print_unicode(s, stderrEngine, stderr);
            }
            else
            {
                std::fwrite(s, strlen(s), 1, stderr);
            }
            break;
        }
        default:
        {
            if (stdout_tty)
            {
                print_unicode(s, stdoutEngine, stdout);
            }
            else
            {
                std::fwrite(s, strlen(s), 1, stdout);
            }
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

int puts_file(const char* str, void* stream)
{
    return std::fputs(str, static_cast<FILE*>(stream));
}

int eof_file(void* stream)
{
    return std::feof(static_cast<FILE*>(stream));
}

 int flush_file(void* stream)
{
     return std::fflush(static_cast<FILE*>(stream));
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

void* mem_set(void* dest, int c, size_t count)
{
    return std::memset(dest, c, count);
}

char* get_cwd(char* buffer, int maxlen)
{
    return _getcwd(buffer, maxlen);
}

bool file_exists(const char* path)
{
    return std::filesystem::exists(path) && !std::filesystem::is_directory(path);
}

bool dir_exists(const char* path)
{
    return std::filesystem::exists(path) && std::filesystem::is_directory(path);
}

bool path_exists(const char* path)
{
    return std::filesystem::exists(path);
}

int to_lower(int c)
{
    return std::tolower(c);
}

int to_upper(int c)
{
    return std::toupper(c);
}

bool is_alpha(int c)
{
    return std::isalpha(c);
}

bool is_digit(int c)
{
    return std::isdigit(c);
}

bool is_atty(int handle)
{
    return _isatty(handle);
}

int64_t current_time()
{
    return std::time(nullptr);
}

void current_date(int& yyyy, int& month, int& day)
{
    util::Date date = util::GetCurrentDate();
    yyyy = date.Year();
    month = static_cast<int8_t>(date.GetMonth());
    day = date.Day();
}

void current_date_time(int& yyyy, int& month, int& day, int& seconds)
{
    util::DateTime dateTime = util::GetCurrentDateTime();
    util::Date date = dateTime.GetDate();
    yyyy = date.Year();
    month = static_cast<int8_t>(date.GetMonth());
    day = date.Day();
    seconds = dateTime.Seconds();
}

int64_t make_time(int yyyy, int month, int day, int seconds)
{
    util::Date date(yyyy, static_cast<util::Month>(month), static_cast<int8_t>(day));
    util::DateTime dt(date, seconds);
    return util::MkTime(dt);
}

int64_t current_ms()
{
    return util::CurrentMs();
}
