export module std.atexit;

import std.type.fundamental;

export namespace std {

using at_exit_fn = void (*)(void* arg);

void at_exit(at_exit_fn fn, void* arg);
void run_at_exits();

} // namespace std
