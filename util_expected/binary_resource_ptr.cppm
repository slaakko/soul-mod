// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module util_expected.binary.resource.ptr;

import std;

export namespace util {

#ifdef _WIN32

enum class ResourceFlags
{
    none = 0, loadLibraryAsDataFile = 1 << 0
};

constexpr ResourceFlags operator|(ResourceFlags left, ResourceFlags right)
{
    return ResourceFlags(int(left) | int(right));
}

constexpr ResourceFlags operator&(ResourceFlags left, ResourceFlags right)
{
    return ResourceFlags(int(left) & int(right));
}

constexpr ResourceFlags operator~(ResourceFlags flags)
{
    return ResourceFlags(~int(flags));
}

class BinaryResourcePtr
{
public:
    BinaryResourcePtr(const std::string& moduleName, const std::string& resourceName_);
    BinaryResourcePtr(const std::string& moduleName, const std::string& resourceName_, ResourceFlags flags);
    inline const std::string& ResourceName() const { return resourceName; }
    inline std::uint8_t* Data() const { return data; }
    inline std::int64_t Size() const { return size; }
    inline bool Valid() const { return error == 0; }
    inline int Error() const { return error; }
    inline explicit operator bool() const { return Valid(); }
private:
    std::string resourceName;
    std::uint8_t* data;
    std::int64_t size;
    int error;
};

#endif

} // util
