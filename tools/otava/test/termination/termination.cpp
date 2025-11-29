import std;

class Value
{
public:
    virtual ~Value();
};

Value::~Value()
{
}

class Component
{
public:
    virtual ~Component();
};

Component::~Component()
{
}

class Instruction : public Value, public Component
{
};

class RetInstruction : public Instruction
{
};

int main()
{
    Component* inst = new RetInstruction();
    delete inst;
}
