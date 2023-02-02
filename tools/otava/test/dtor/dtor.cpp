import std.core;

template<typename T>
void destroy(T* p)
{
    p->T::~T();
    free(p);
}

struct X
{
};

struct Y
{
    std::string s;
};

struct Z
{
    ~Z()
    {
        prints("~Z", 1);
    }
};

struct Q
{
    ~Q()
    {
        prints("~Q", 1);
    }
    std::string s;
};

int main()
{
    int* p1 = new int();
    destroy(p1);

    int* p2 = new int();
    delete p2;

    X* x1 = new X();
    destroy(x1);

    X* x2 = new X();
    delete x2;

    Y* y1 = new Y();
    destroy(y1);

    Y* y2 = new Y();
    delete y2;

    Z* z1 = new Z();
    destroy(z1);

    Z* z2 = new Z();
    delete z2;

    Q* q1 = new Q();
    destroy(q1);

    Q* q2 = new Q();
    delete q2;
}
