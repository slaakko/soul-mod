import std.core;

int main()
{
    int x = 0;
    switch (x)
    {
        case 0:
        case 1:
        case 2:
        {
            return 0;
        }
        case 10:
        {
            return 1;
        }
    }
    return 0;
}
