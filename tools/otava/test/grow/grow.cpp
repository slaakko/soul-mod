import std.core;

ssize_t grow_size(ssize_t size)
{
    if (size < 8) return 8;
    if (size < 64) return 64;
    if (size < 512) return 512;
    if (size < 4096) return 4096;
    return 2 * align(size, 4096);
}

int main()
{
    return 0;
}
