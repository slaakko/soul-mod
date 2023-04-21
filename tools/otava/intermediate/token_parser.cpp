// =================================
// Copyright (c) 2023 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.intermediate.token_parser;

import util.text.util;

namespace otava::intermediate::token_parser {

std::string ParseStringValue(const std::string& str)
{
    std::string result;
    std::string content = str.substr(1, str.length() - 2);
    int state = 0;
    bool ret = false;
    std::string hexByteStr;
    for (char c : content)
    {
        if (ret)
        {
            break;
        }
        switch (state)
        {
            case 0:
            {
                if (c == U'\\')
                {
                    state = 1;
                    hexByteStr.clear();
                }
                else
                {
                    result.append(1, c);
                }
                break;
            }
            case 1:
            {
                hexByteStr.append(1, c);
                state = 2;
                break;
            }
            case 2:
            {
                hexByteStr.append(1, c);
                uint8_t hexByte = util::ParseHexByte(hexByteStr);
                if (hexByte == 0)
                {
                    ret = true;
                }
                else
                {
                    result.append(1, static_cast<char>(hexByte));
                    state = 0;
                }
                break;
            }
        }
    }
    return result;
}

} // otava::intermediate::token_parser
