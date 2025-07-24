// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module;
#ifdef _WIN32
#include <Windows.h>
#endif

module util_expected.binary.resource.ptr;

import util_expected.error;
import util_expected.unicode;
import util_expected.win_error;

namespace util {

#ifdef _WIN32

BinaryResourcePtr::BinaryResourcePtr(const std::string& moduleName, const std::string& resourceName_) : BinaryResourcePtr(moduleName, resourceName_, ResourceFlags::none)
{
}

BinaryResourcePtr::BinaryResourcePtr(const std::string& moduleName, const std::string& resourceName_, ResourceFlags flags) : resourceName(resourceName_), size(0), error(0)
{
    std::expected<std::u16string, int> mrv = ToUtf16(moduleName);
    if (!mrv)
    {
        error = mrv.error();
        return;
    }
    std::u16string moduleNameStr = *mrv;
    mrv = ToUtf16(resourceName);
    if (!mrv)
    {
        error = mrv.error();
        return;
    }
    std::u16string resourceNameStr = *mrv;
    HMODULE moduleHandle = nullptr;
    if ((flags & ResourceFlags::loadLibraryAsDataFile) != ResourceFlags::none)
    {
        moduleHandle = LoadLibraryExW((LPCWSTR)moduleNameStr.c_str(), 0, LOAD_LIBRARY_AS_DATAFILE);
    }
    else
    {
        moduleHandle = GetModuleHandleW((LPCWSTR)moduleNameStr.c_str());
    }
    if (!moduleHandle)
    {
        std::expected<std::string, int> wrv = WindowsErrorMessage(GetLastError());
        if (!wrv)
        {
            error = wrv.error();
            return;
        }
        std::string errorMessage = "error: error getting resource '" + resourceName + "' from module '" + moduleName + "': could not get module handle: " + *wrv;
        error = AllocateError(errorMessage);
        return;
    }
    HRSRC res = FindResourceW(moduleHandle, (LPCWSTR)resourceNameStr.c_str(), RT_RCDATA);
    if (!res)
    {
        std::string resourceFileName = resourceName + ".rc";
        std::expected<std::string, int> wrv = WindowsErrorMessage(GetLastError());
        if (!wrv)
        {
            error = wrv.error();
            return;
        }
        std::string errorMessage = "error: error getting resource '" + resourceName + "' from module '" + moduleName + "': could not find resource: " +
            *wrv +  ": note: please add resource file '" + resourceFileName + "' to the C++ project that makes executable '" + moduleName + "'";
        error = AllocateError(errorMessage);
        return;
    }
    HGLOBAL handle = LoadResource(moduleHandle, res);
    if (!handle)
    {
        std::expected<std::string, int> wrv = WindowsErrorMessage(GetLastError());
        if (!wrv)
        {
            error = wrv.error();
            return;
        }
        std::string resourceFileName = resourceName + ".rc";
        std::string errorMessage = "error: error loading resource '" + resourceName + "' from module '" + moduleName + ": " +
            *wrv + ": note: please add resource file '" + resourceFileName + "' to the C++ project that makes executable '" + moduleName + "'";
        error = AllocateError(errorMessage);
        return;
    }
    data = static_cast<std::uint8_t*>(LockResource(handle));
    size = SizeofResource(moduleHandle, res);
}

#endif

} // util
