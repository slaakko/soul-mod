// =================================
// Copyright (c) 2025 Seppo Laakko
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
import util;

bool initialized = false;

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
    Rng(std::uint64_t seed_);
    std::uint8_t Get() { return dist(mt); }
private:
    std::random_device rd;
    std::uint64_t seed;
    std::mt19937_64 mt;
    std::uniform_int_distribution<> dist;
};

std::uint64_t GetSeed(std::uint64_t seed, std::random_device& rd)
{
    if (seed == -1)
    {
        return static_cast<std::uint64_t>(rd()) ^ static_cast<std::uint64_t>(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    }
    else
    {
        return seed;
    }
}

Rng::Rng(std::uint64_t seed_) : rd(), seed(GetSeed(seed_, rd)), mt(seed), dist(0, 255)
{
}

#ifdef _WIN32

__declspec(thread) std::uint64_t init_seed = -1;
__declspec(thread) Rng* rng = nullptr;

#else

__thread std::uint64_t init_seed = -1;
__thread Rng* rng = nullptr;

#endif

void set_rand_seed(std::uint64_t seed)
{
    init_seed = seed;
}

std::uint8_t get_random_byte()
{
    if (!rng)
    {
        rng = new Rng(init_seed);
    }
    return rng->Get();
}

void* current_exception = nullptr;
std::uint64_t currentExceptionTypeIdHigh = 0;
std::uint64_t currentExceptionTypeIdLow = 0;

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

std::int64_t current_time()
{
    return std::time(nullptr);
}

void current_date(int& yyyy, int& month, int& day)
{
    util::Date date = util::GetCurrentDate();
    yyyy = date.Year();
    month = static_cast<std::int8_t>(date.GetMonth());
    day = date.Day();
}

void current_date_time(int& yyyy, int& month, int& day, int& seconds)
{
    util::DateTime dateTime = util::GetCurrentDateTime();
    util::Date date = dateTime.GetDate();
    yyyy = date.Year();
    month = static_cast<std::int8_t>(date.GetMonth());
    day = date.Day();
    seconds = dateTime.Seconds();
}

std::int64_t make_time(int yyyy, int month, int day, int seconds)
{
    util::Date date(yyyy, static_cast<util::Month>(month), static_cast<std::int8_t>(day));
    util::DateTime dt(date, seconds);
    return util::MkTime(dt);
}

std::int64_t current_ms()
{
    return util::CurrentMs();
}
