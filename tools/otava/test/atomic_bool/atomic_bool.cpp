import std.core;

std::atomic_bool initialized;

void init()
{
    std::cout << "init" << "\n";
}

void check_init()
{
    if (!initialized)
    {
        std::lock_guard<std::recursive_mutex> lock(std::get_init_lock());
        if (!initialized)
        {
            init();
            initialized = true;
        }
    }
}

int main()
{
    check_init();
    return 0;
}
