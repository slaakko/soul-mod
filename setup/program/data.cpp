#include "data.hpp"

namespace setup {

std::string PackageResourceName()
{
    return "setup.package";
}

int64_t UncompressedPackageSize()
{
    return 330218122;
}

std::string UnicodeDBResourceName()
{
    return "wng_unicode_db";
}

int64_t UncompressedUnicodeDBSize()
{
    return 53233116;
}

std::string SetupIconResourceName()
{
    return "setup_icon";
}

std::string AppName()
{
    return "Soul";
}

std::string AppVersion()
{
    return "4.0.0";
}

int Compression()
{
    return 1; // deflate
}

std::string DefaultContainingDirPath()
{
    return "C:/";
}

std::string InstallDirName()
{
    return "soul-4.0.0";
}


} // setup

