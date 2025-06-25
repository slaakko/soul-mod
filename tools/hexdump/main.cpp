// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

import std;
// import std.filesystem;
import util;

void PrintHelp()
{
    std::cout << "usage: hexdump [options] { FILE }" << std::endl;
    std::cout << "options:" << std::endl;
    std::cout << "--help | -h:" << std::endl;
    std::cout << "  print help and exit:" << std::endl;
    std::cout << "--verbose | -v:" << std::endl;
    std::cout << "  be verbose:" << std::endl;
}

const int bytesInLine = 16;

std::string HexDumpLine(std::uint64_t addr, std::uint8_t* bytes, std::int64_t numBytes)
{
    std::string line(util::ToHexString(addr));
    line.append(": ");
    for (int i = 0; i < bytesInLine; ++i)
    {
        if (i == bytesInLine / 2)
        {
            line.append("- ");
        }
        if (i < numBytes)
        {
            line.append(util::ToHexString(bytes[i]));
        }
        else
        {
            line.append("  ");
        }
        line.append(1, ' ');
    }
    line.append(1, '|');
    for (int i = 0; i < bytesInLine; ++i)
    {
        char c = ' ';
        if (i < numBytes)
        {
            char b = static_cast<char>(bytes[i]);
            if (b > 32 && b < 127)
            {
                c = b;
            }
        }
        line.append(1, c);
    }
    line.append(1, '|');
    return line;
}

void HexDump(const std::string& file, bool verbose)
{
    std::int64_t fileSize = std::filesystem::file_size(file);
    if (verbose)
    {
        std::cout << file << ": " << fileSize << " bytes" << std::endl;
    }
    util::FileStream fileStream(file, util::OpenMode::read | util::OpenMode::binary);
    util::BufferedStream bufferedStream(fileStream);
    util::BinaryStreamReader reader(bufferedStream);
    std::uint8_t bytes[bytesInLine];
    std::uint64_t addr = 0;
    std::int64_t numRows = fileSize / bytesInLine;
    for (std::int64_t i = 0; i < numRows; ++i)
    {
        for (int j = 0; j < bytesInLine; ++j)
        {
            bytes[j] = reader.ReadByte();
        }
        std::cout << HexDumpLine(addr, &bytes[0], bytesInLine) << std::endl;
        addr = addr + bytesInLine;
    }
    std::int64_t rest = fileSize % bytesInLine;
    for (int j = 0; j < rest; ++j)
    {
        bytes[j] = reader.ReadByte();
    }
    std::cout << HexDumpLine(addr, &bytes[0], rest) << std::endl;
}

int main(int argc, const char** argv)
{
    try
    {
        util::Init();
        bool verbose = false;
        std::vector<std::string> files;
        for (int i = 1; i < argc; ++i)
        {
            std::string arg = argv[i];
            if (arg.starts_with("--"))
            {
                if (arg == "--help")
                {
                    PrintHelp();
                    return 1;
                }
                else if (arg == "--verbose")
                {
                    verbose = true;
                }
                else
                {
                    throw std::runtime_error("unknown option '" + arg + "'");
                }
            }
            else if (arg.starts_with("-"))
            {
                std::string options = arg.substr(1);
                for (char o : options)
                {
                    switch (o)
                    {
                        case 'h':
                        { 
                            PrintHelp();
                            return 1;
                        }
                        case 'v':
                        {
                            verbose = true;
                            break;
                        }
                        default:
                        {
                            throw std::runtime_error("unknown option '-" + std::string(1, o) + "'");
                        }
                    }
                }
            }
            else
            {
                files.push_back(util::GetFullPath(arg));
            }
        }
        if (files.empty())
        {
            throw std::runtime_error("no files given");
        }
        for (const auto& file : files)
        {
            HexDump(file, verbose);
        }
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
        return 1;
    }
    util::Done();
    return 0;
}