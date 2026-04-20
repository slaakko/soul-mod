export module a;

import std;

export namespace a
{
    bool GetTokens()
    {
        return true;
    }

    bool GetLexer()
    {
        return GetTokens();
    }
}

