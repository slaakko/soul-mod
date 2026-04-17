export module fruits;

import std;

export namespace fruits {

class fruit
{
public:
    virtual ~fruit() {}
    virtual void print() = 0;
};

class apple : public fruit
{
public:
    apple() {}
    void print() override { std::cout << "apple"; }
};

class orange : public fruit
{
public:
    orange() {}
    void print() override { std::cout << "orange"; }
};

class banana : public fruit
{
public:
    banana() {}
    void print() override { std::cout << "banana"; }
};

} // namespace fruits

