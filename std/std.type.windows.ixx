export module std.type.windows;

export {

using HANDLE = void*;
using WORD = int16_t;
using DWORD = int32_t;
using CONSOLE_SCREEN_BUFFER_INFO = void*;
using LPWSTR = wchar_t*;
using LPCWSTR = const wchar_t*;
using HMODULE = void*;
using HRSRC = void*;
using HGLOBAL = void*;
using LPFIBER_START_ROUTINE = void*;
using WSADATA = void;
using SOCKET = int;

struct UUID
{
};

struct sockaddr
{
};

struct sockaddr_in
{
};

} 
