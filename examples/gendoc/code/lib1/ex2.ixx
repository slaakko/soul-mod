export module lib1.ex2;

import lib1.ex1;

export namespace ns {

class Bar : public Foo
{
public:
    void bar();
};

} // namespace ns
