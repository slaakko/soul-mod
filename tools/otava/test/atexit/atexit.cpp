import std.core;

using at_exit_fn = void (*)(void* arg);

struct at_exit_entry
{
    at_exit_entry(void* fn_, void* arg_, at_exit_entry* next_);
    void* fn;
    void* arg;
    at_exit_entry* next;
};

at_exit_entry* at_exit_list = nullptr;

at_exit_entry::at_exit_entry(void* fn_, void* arg_, at_exit_entry* next_) : fn(fn_), arg(arg_), next(next_)
{
}

void at_exit(void* fn, void* arg)
{
    at_exit_entry* entry = new at_exit_entry(fn, arg, at_exit_list);
    at_exit_list = entry;
}

void run_at_exits()
{
    at_exit_entry* entry = at_exit_list;
    while (entry)
    {
        at_exit_list = entry->next;
        void* fn = entry->fn;
        at_exit_fn invoke_fn = static_cast<at_exit_fn>(fn);
        void* arg = entry->arg;
        invoke_fn(arg);
        entry = at_exit_list;
    }
}

int main()
{
    return 0;
}