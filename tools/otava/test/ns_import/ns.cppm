export module ns;

import std.core;

namespace using_foo
{
    const int x = 0;
}

export namespace foo
{
    using namespace using_foo;
}
