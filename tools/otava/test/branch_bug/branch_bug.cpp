import std.core;

int bug(int n)
{
    if (true)
    {
        return 1;
    }
    else
    {
        int left = 0;
        if (left)
        {
            return left;
        }
        else
        {
            int u = n;
            int left = u;
            while (n == left)
            {
                n = u;
                u = 1;
                left = 2;
            }
            return u;
        }
    }
}

int main()
{
    bug(0);
    return 0;
}
