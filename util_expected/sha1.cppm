// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module util_expected.sha1;

import std;

export namespace util {

class Sha1
{
public:
    Sha1();
    void Reset();
    void Process(std::uint8_t x)
    {
        ProcessByte(x);
        bitCount = bitCount + 8u;
    }
    void Process(void* begin, void* end);
    void Process(void* buf, int count)
    {
        std::uint8_t* b = static_cast<std::uint8_t*>(buf);
        Process(b, b + count);
    }
    std::string GetDigest();
private:
    void ProcessByte(std::uint8_t x)
    {
        block[byteIndex++] = x;
        if (byteIndex == 64u)
        {
            byteIndex = 0u;
            ProcessBlock();
        }
    }
    void ProcessBlock();
    std::uint32_t digest[5];
    std::uint8_t block[64];
    std::uint8_t byteIndex;
    std::uint64_t bitCount;
};

std::string GetSha1MessageDigest(const std::string& message);

} // namespace util
