import std.core;

void copy(char* from, char* to)
{
    if (from)
    {
        while (*from)
        {
            *to++ = *from++;
        }
    }
    *to = '\0';
}

int main()
{
    char* p = static_cast<char*>(malloc(4));
    char* q = p;
    *p = 'a';
    ++p;
    *p = 'b';
    ++p;
    *p = 'c';
    ++p;
    *p = '\0';
    prints(q);
    char* from = q;

    char* to = static_cast<char*>(malloc(4));
    copy(from, to);
    prints(to);
}
