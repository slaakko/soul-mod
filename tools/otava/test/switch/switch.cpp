import std.core;

int main()
{
    int x = 1;
    int y = 0;
    switch (x)
    {
        case 1:
        {
            y = 1;
            break;
        }
        case 2:
        {
            y = 2;
            break;
        }
        case 3:
        {
            y = 3;
            break;
        }
        default:
        {
            y = 4;
            break;
        }
    }
    return 0;
}
