module std.atexit;

namespace std {

at_exit_entry* at_exit_list = nullptr;

using at_exit_fn = void (*)(void arg);

void at_exit(at_exit_entry* entry, void* fn, void* arg)
{
    entry->fn = fn;
    entry->arg = arg;
    entry->next = at_exit_list;
    at_exit_list = entry;
}

void run_at_exits()
{
    at_exit_entry* entry = at_exit_list;
    while (entry)
    {
        at_exit_list = entry->next;
        at_exit_fn invoke_fn = entry->fn;
        invoke_fn(entry->arg);
        entry = at_exit_list;
    }
}

} // namespace std
