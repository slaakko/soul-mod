module std.atexit;

import std.new_delete_op;

namespace std {

struct at_exit_entry
{
    at_exit_entry(at_exit_fn fn_, void* arg_, at_exit_entry* next_);
    at_exit_fn fn;
    void* arg;
    at_exit_entry* next;
};

at_exit_entry* at_exit_list = nullptr;

at_exit_entry::at_exit_entry(at_exit_fn fn_, void* arg_, at_exit_entry* next_) : fn(fn_), arg(arg_), next(next_)
{
}

void at_exit(at_exit_fn fn, void* arg)
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
        at_exit_fn fn = entry->fn;
        void* arg = entry->arg;
        fn(arg);
        entry = at_exit_list;
    }
}

} // namespace std
