// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module util.binary.resource.ptr;

import util.error;
import util.unicode;

namespace util {

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
    void* moduleHandle = nullptr;
    if ((flags & ResourceFlags::loadLibraryAsDataFile) != ResourceFlags::none)
    {
        moduleHandle = ort_load_library_as_data_file(moduleNameStr.c_str());
    }
    else
    {
        moduleHandle = ort_get_module_handle(moduleNameStr.c_str());
    }
    if (!moduleHandle)
    {
        std::uint32_t winError = ort_get_last_windows_error();
        char buf[4096];
        ort_get_windows_error_message(winError, buf, 4096);
        std::string msg(buf);
        std::string errorMessage = "error: error getting resource '" + resourceName + "' from module '" + moduleName + "': could not get module handle: " + msg;
        error = AllocateError(errorMessage);
        return;
    }
    void* resource = ort_find_resource(moduleHandle, resourceNameStr.c_str());
    if (!resource)
    {
        std::string resourceFileName = resourceName + ".rc";
        std::uint32_t winError = ort_get_last_windows_error();
        char buf[4096];
        ort_get_windows_error_message(winError, buf, 4096);
        std::string msg(buf);
        std::string errorMessage = "error: error getting resource '" + resourceName + "' from module '" + moduleName + "': could not find resource: " +
            msg + ": note: please add resource file '" + resourceFileName + "' to the C++ project that makes executable '" + moduleName + "'";
        error = AllocateError(errorMessage);
        return;
    }
    void* handle = ort_load_resource(moduleHandle, resource);
    if (!handle)
    {
        std::uint32_t winError = ort_get_last_windows_error();
        char buf[4096];
        ort_get_windows_error_message(winError, buf, 4096);
        std::string msg(buf);
        std::string resourceFileName = resourceName + ".rc";
        std::string errorMessage = "error: error loading resource '" + resourceName + "' from module '" + moduleName + ": " +
            msg + ": note: please add resource file '" + resourceFileName + "' to the C++ project that makes executable '" + moduleName + "'";
        error = AllocateError(errorMessage);
        return;
    }
    data = static_cast<std::uint8_t*>(ort_lock_resource(handle));
    size = ort_size_of_resource(moduleHandle, resource);
}

} // util
