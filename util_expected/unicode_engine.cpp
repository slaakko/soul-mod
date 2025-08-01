// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module util_expected.unicode;

namespace util {

Utf8ToUtf32Engine::Utf8ToUtf32Engine() : state(0), resultReady(false), result(U'\0')
{
    std::memset(static_cast<void*>(&bytes[0]), 0, sizeof(bytes));
}

std::expected<bool, int> Utf8ToUtf32Engine::Put(std::uint8_t x)
{
    switch (state)
    {
        case 0:
        {
            resultReady = false;
            if ((x & 0x80u) == 0u)
            {
                result = static_cast<char32_t>(x);
                resultReady = true;
            }
            else if ((x & 0xE0u) == 0xC0u)
            {
                bytes[0] = x;
                state = 1;
            }
            else if ((x & 0xF0u) == 0xE0u)
            {
                bytes[0] = x;
                state = 2;
            }
            else if ((x & 0xF8u) == 0xF0u)
            {
                bytes[0] = x;
                state = 4;
            }
            else
            {
                return InvalidUtf8Sequence();
            }
            break;
        }
        case 1:
        {
            result = static_cast<char32_t>(0);
            bytes[1] = x;
            std::uint8_t b1 = bytes[1];
            if ((b1 & 0xC0u) != 0x80u)
            {
                return InvalidUtf8Sequence();
            }
            std::uint8_t shift = 0u;
            for (std::uint8_t i = 0u; i < 6u; ++i)
            {
                std::uint8_t bit = b1 & 1u;
                b1 = b1 >> 1u;
                result = static_cast<char32_t>(static_cast<std::uint32_t>(result) | (static_cast<std::uint32_t>(bit) << shift));
                ++shift;
            }
            std::uint8_t b0 = bytes[0];
            for (std::uint8_t i = 0u; i < 5u; ++i)
            {
                std::uint8_t bit = b0 & 1u;
                b0 = b0 >> 1u;
                result = static_cast<char32_t>(static_cast<std::uint32_t>(result) | (static_cast<std::uint32_t>(bit) << shift));
                ++shift;
            }
            resultReady = true;
            state = 0;
            break;
        }
        case 2:
        {
            bytes[1] = x;
            state = 3;
            break;
        }
        case 3:
        {
            bytes[2] = x;
            result = static_cast<char32_t>(0);
            std::uint8_t b2 = bytes[2];
            if ((b2 & 0xC0u) != 0x80u)
            {
                return InvalidUtf8Sequence();
            }
            std::uint8_t shift = 0u;
            for (std::uint8_t i = 0u; i < 6u; ++i)
            {
                std::uint8_t bit = b2 & 1u;
                b2 = b2 >> 1u;
                result = static_cast<char32_t>(static_cast<std::uint32_t>(result) | (static_cast<std::uint32_t>(bit) << shift));
                ++shift;
            }
            std::uint8_t b1 = bytes[1];
            if ((b1 & 0xC0u) != 0x80u)
            {
                return InvalidUtf8Sequence();
            }
            for (std::uint8_t i = 0u; i < 6u; ++i)
            {
                std::uint8_t bit = b1 & 1u;
                b1 = b1 >> 1u;
                result = static_cast<char32_t>(static_cast<std::uint32_t>(result) | (static_cast<std::uint32_t>(bit) << shift));
                ++shift;
            }
            std::uint8_t b0 = bytes[0];
            for (std::uint8_t i = 0u; i < 4u; ++i)
            {
                std::uint8_t bit = b0 & 1u;
                b0 = b0 >> 1u;
                result = static_cast<char32_t>(static_cast<std::uint32_t>(result) | (static_cast<std::uint32_t>(bit) << shift));
                ++shift;
            }
            resultReady = true;
            state = 0;
            break;
        }
        case 4:
        {
            bytes[1] = x;
            state = 5;
            break;
        }
        case 5:
        {
            bytes[2] = x;
            state = 6;
            break;
        }
        case 6:
        {
            bytes[3] = x;
            result = static_cast<char32_t>(0);
            std::uint8_t b3 = bytes[3];
            if ((b3 & 0xC0u) != 0x80u)
            {
                return InvalidUtf8Sequence();
            }
            std::uint8_t shift = 0u;
            for (std::uint8_t i = 0u; i < 6u; ++i)
            {
                std::uint8_t bit = b3 & 1u;
                b3 = b3 >> 1u;
                result = static_cast<char32_t>(static_cast<std::uint32_t>(result) | (static_cast<std::uint32_t>(bit) << shift));
                ++shift;
            }
            std::uint8_t b2 = bytes[2];
            if ((b2 & 0xC0u) != 0x80u)
            {
                return InvalidUtf8Sequence();
            }
            for (std::uint8_t i = 0u; i < 6u; ++i)
            {
                std::uint8_t bit = b2 & 1u;
                b2 = b2 >> 1u;
                result = static_cast<char32_t>(static_cast<std::uint32_t>(result) | (static_cast<std::uint32_t>(bit) << shift));
                ++shift;
            }
            std::uint8_t b1 = bytes[1];
            if ((b1 & 0xC0u) != 0x80u)
            {
                return InvalidUtf8Sequence();
            }
            for (std::uint8_t i = 0u; i < 6u; ++i)
            {
                std::uint8_t bit = b1 & 1u;
                b1 = b1 >> 1u;
                result = static_cast<char32_t>(static_cast<std::uint32_t>(result) | (static_cast<std::uint32_t>(bit) << shift));
                ++shift;
            }
            std::uint8_t b0 = bytes[0];
            for (std::uint8_t i = 0u; i < 3u; ++i)
            {
                std::uint8_t bit = b0 & 1u;
                b0 = b0 >> 1u;
                result = static_cast<char32_t>(static_cast<std::uint32_t>(result) | (static_cast<std::uint32_t>(bit) << shift));
                ++shift;
            }
            resultReady = true;
            state = 0;
            break;
        }
    }
    return std::expected<bool, int>(true);
}

} // namespace util
