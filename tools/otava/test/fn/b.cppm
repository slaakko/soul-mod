export module b;

import std;
import a;

export namespace b
{
    bool GetTokens()
    {
        return false;
    }

    bool GetLexer()
    {
        return GetTokens();
    }
}
