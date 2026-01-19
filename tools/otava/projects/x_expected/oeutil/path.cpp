// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module util.path;

import std;
import util.error;
import util.text.util;

namespace util {

std::unexpected<int> InvalidPath(const std::string& msg)
{
    return std::unexpected<int>(AllocateError(msg));
}

std::expected<std::string, int> GetCurrentWorkingDirectory()
{
    char buf[4096];
    const char* wd = ort_get_cwd(&buf, 4096);
    if (wd != nullptr)
    {
        return Path::MakeCanonical(wd);
    }
    else
    {
        return std::unexpected<int>(AllocateError("could not get current working directory"));
    }
}

bool FileExists(const std::string& filePath)
{
    return ort_path_exists(filePath.c_str());
}

bool DirectoryExists(const std::string& directoryPath)
{
    return ort_path_exists(directoryPath.c_str());
}

bool PathExists(const std::string& path)
{
    return ort_path_exists(path.c_str());
}

std::string Path::MakeCanonical(const std::string& path)
{
    bool startsWithDriveLetter = false;
    if (path.length() >= 2 && std::isalpha(path[0]) && path[1] == ':')
    {
        startsWithDriveLetter = true;
    }
    std::string result;
    char prev = ' ';
    bool first = true;
    for (char c : path)
    {
        if (first)
        {
            first = false;
            if (startsWithDriveLetter)
            {
                c = static_cast<unsigned char>(std::toupper(static_cast<unsigned char>(c)));
            }
        }
        if (c == '\\')
        {
            c = '/';
        }
        if (c == '/')
        {
            if (prev != '/')
            {
                result.append(1, c);
            }
        }
        else
        {
            result.append(1, c);
        }
        prev = c;
    }
    if (result.length() == 3 && std::isalpha(result[0]) && result[1] == ':' && result[2] == '/')
    {
        return result;
    }
    if (result == "/")
    {
        return result;
    }
    if (!result.empty())
    {
        if (result[result.length() - 1] == '/')
        {
            return result.substr(0, result.length() - 1);
        }
    }
    return result;
}

std::string Path::ChangeExtension(const std::string& path, const std::string& extension)
{
    std::string p = MakeCanonical(path);
    std::string::size_type lastSlashPos = p.rfind('/');
    std::string::size_type lastDotPos = path.rfind('.');
    if (extension.empty())
    {
        if (lastDotPos != std::string::npos && lastDotPos > lastSlashPos)
        {
            return p.substr(0, lastDotPos);
        }
        else
        {
            return p;
        }
    }
    else
    {
        if ((lastDotPos == std::string::npos) || (lastSlashPos != std::string::npos) && (lastDotPos < lastSlashPos))
        {
            if (extension[0] == '.')
            {
                p.append(extension);
                return p;
            }
            else
            {
                p.append(".").append(extension);
                return p;
            }
        }
        else
        {
            if (extension[0] == '.')
            {
                p = p.substr(0, lastDotPos);
                p.append(extension);
                return p;
            }
            else
            {
                p = p.substr(0, lastDotPos + 1);
                p.append(extension);
                return p;
            }
        }
    }
}

bool Path::HasExtension(const std::string& path)
{
    std::string::size_type lastDotPos = path.rfind('.');
    if (lastDotPos != std::string::npos)
    {
        std::string::size_type lastColon = path.find(':', lastDotPos + 1);
        std::string::size_type lastDirSep = path.find('/', lastDotPos + 1);
        if (lastColon != std::string::npos && lastColon > lastDotPos || lastDirSep != std::string::npos && lastDirSep > lastDotPos)
        {
            return false;
        }
        else if (lastDotPos < path.length() - 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

std::string Path::GetExtension(const std::string& path)
{
    std::string::size_type lastDotPos = path.rfind('.');
    if (lastDotPos != std::string::npos)
    {
        if (path.find('/', lastDotPos + 1) != std::string::npos)
        {
            return std::string();
        }
        else
        {
            return path.substr(lastDotPos);
        }
    }
    else
    {
        return std::string();
    }
}

std::string Path::GetDrive(const std::string& path)
{
    if (path.length() >= 2 && std::isalpha(path[0]) && path[1] == ':')
    {
        char c = path[0];
        unsigned char uc = static_cast<unsigned char>(c);
        uc = static_cast<unsigned char>(ort_toupper(uc));
        std::string s(1, uc);
        s.append(1, ':');
        return s;
    }
    return std::string();
}

std::string Path::GetFileName(const std::string& path)
{
    if (path.empty())
    {
        return std::string();
    }
    else
    {
        char lastChar = path[path.length() - 1];
        if (lastChar == '/' || lastChar == ':')
        {
            return std::string();
        }
        else
        {
            std::string::size_type lastDirSepPos = path.rfind('/');
            if (lastDirSepPos != std::string::npos)
            {
                return path.substr(lastDirSepPos + 1);
            }
            else
            {
                return path;
            }
        }
    }
}

std::string Path::GetFileNameWithoutExtension(const std::string& path)
{
    std::string fileName = GetFileName(path);
    std::string::size_type lastDotPos = fileName.rfind('.');
    if (lastDotPos != std::string::npos)
    {
        return fileName.substr(0, lastDotPos);
    }
    else
    {
        return fileName;
    }
}

std::string Path::GetDirectoryName(const std::string& path)
{
    if (path.empty())
    {
        return std::string();
    }
    else if (path.length() == 3 && std::isalpha(path[0]) && path[1] == ':' && path[2] == '/')
    {
        return std::string();
    }
    else
    {
        std::string::size_type lastDirSepPos = path.rfind('/');
        if (lastDirSepPos != std::string::npos)
        {
            std::string dir = path.substr(0, lastDirSepPos);
            if (dir.length() == 2 && std::isalpha(dir[0]) && dir[1] == ':')
            {
                dir.append(1, '/');
            }
            return dir;
        }
        else
        {
            return std::string();
        }
    }
}

std::string Path::Combine(const std::string& path1, const std::string& path2)
{
    if (path1.empty())
    {
        return path2;
    }
    else if (path2.empty())
    {
        return path1;
    }
    else
    {
        if (IsAbsolute(path2))
        {
            return path2;
        }
        else
        {
            std::string result = path1;
            if (result[result.length() - 1] != '/')
            {
                result.append(1, '/');
            }
            result.append(path2);
            return result;
        }
    }
}

bool Path::IsAbsolute(const std::string& path)
{
    if (path.empty())
    {
        return false;
    }
    else
    {
        if (path[0] == '/')
        {
            return true;
        }
        else if (std::isalpha(path[0]) && path.length() > 2 && path[1] == ':' && path[2] == '/')
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

bool Path::IsRelative(const std::string& path)
{
    return !IsAbsolute(path);
}

std::expected<std::string, int> GetFullPath(const std::string& path)
{
    std::string p = Path::MakeCanonical(path);
    if (Path::IsRelative(p))
    {
        std::expected<std::string, int> cwdrv = GetCurrentWorkingDirectory();
        if (!cwdrv) return std::unexpected<int>(cwdrv.error());
        p = *cwdrv;
        p.append(1, '/');
        p.append(Path::MakeCanonical(path));
    }
    std::vector<std::string> components = Split(p, '/');
    int w = 0;
    int n = int(components.size());
    for (int i = 0; i < n; ++i)
    {
        const std::string& c = components[i];
        if (i == 0 || (!c.empty() && c != "."))
        {
            if (c == "..")
            {
                --w;
                if (w < 0)
                {
                    std::string msg("path '");
                    msg.append(path);
                    msg.append("' is invalid");
                    return InvalidPath(msg);
                }
            }
            else
            {
                if (w != i)
                {
                    components[w] = components[i];
                }
                ++w;
            }
        }
    }
    if (w == 0)
    {
        return "/";
    }
    else if (w == 1)
    {
        std::string p = components[0];
        if (p.length() == 2 && std::isalpha(p[0]) && p[1] == ':')
        {
            p.append("/");
            return std::expected<std::string, int>(p);
        }
    }
    std::string result;
    for (int i = 0; i < w; ++i)
    {
        if (i != 0)
        {
            result.append(1, '/');
        }
        result.append(components[i]);
    }
    return std::expected<std::string, int>(result);
}

std::expected<std::string, int> MakeRelativeDirPath(const std::string& dirPath, const std::string& referenceDirPath)
{
    std::expected<std::string, int> rv = GetFullPath(dirPath);
    if (!rv) return rv;
    std::string p = *rv;
    rv = GetFullPath(referenceDirPath);
    if (!rv) return rv;
    std::string r = *rv;
    if (p == r)
    {
        return std::expected<std::string, int>(std::string());
    }
    if (Path::GetDrive(p) != Path::GetDrive(r))
    {
        return std::expected<std::string, int>(p);
    }
    std::vector<std::string> pc = Split(p, '/');
    int pcs = pc.size();
    std::vector<std::string> rc = Split(r, '/');
    int rcs = rc.size();
    int n = std::min(pcs, rcs);
    int m = 0;
    for (; m < n; ++m)
    {
        if (pc[m] != rc[m])
        {
            break;
        }
    }
    std::string result;
    for (int i = m; i < rc.size(); ++i)
    {
        result = Path::Combine(result, "..");
    }
    for (int i = m; i < pc.size(); ++i)
    {
        result = Path::Combine(result, pc[i]);
    }
    return std::expected<std::string, int>(result);
}

std::string MakeNativePath(const std::string& path)
{
    std::string nativePath;
    for (char c : path)
    {
        if (c == '/')
        {
            nativePath.append(1, '\\');
        }
        else
        {
            nativePath.append(1, c);
        }
    }
    return nativePath;
}

} // namespace util
