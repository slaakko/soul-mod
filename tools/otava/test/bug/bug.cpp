import std.core;

extern "C" void fs_path_dtor(void* p);
extern "C" void* fs_path_string_ctor(const char* source);

class path
{
public:
    path& operator=(const char* source);
private:
    void* handle;
};

path& path::operator=(const char* source)
{
    if (handle)
    {
        fs_path_dtor(handle);
    }
    handle = fs_path_string_ctor(source);
    return *this;
}

int main()
{
    path p;
    p = "foo";
    return 0;
}
