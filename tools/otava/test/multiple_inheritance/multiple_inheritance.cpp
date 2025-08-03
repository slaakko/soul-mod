import std;

class Component
{
public:
    Component(const std::string& name_, int x_, int y_) : name(name_), x(x_), y(y_) {}
    const std::string& Name() const { return name; }
    virtual ~Component() {}
    virtual int X() const { return x; }
    virtual int Y() const { return y; }
private:
    std::string name;
    int x;
    int y;
};

class Value
{
public:
    Value(const std::string& name_) : name(name_) {}
    virtual ~Value() {}
    const std::string& Name() const { return name; }
private:
    std::string name;
};

class Instruction : public Value, public Component
{
public:
    Instruction(const std::string& name_, const std::string& valueName_, const std::string&  componentName_, int componentX, int componentY, int instY) : 
        Value(valueName_), Component(componentName_, componentX, componentY), name(name_), y(instY) {}
    const std::string& Name() const { return name; }
    int Y() const override { return y; }
private:
    std::string name;
    int y;
};

int main()
{
    std::unique_ptr<Instruction> inst(new Instruction("foo", "foo.value", "foo.component", 1, 2, 3));
    std::cout << inst->Name() << "\n";
    Component* component = inst.get();
    std::cout << component->Name() << ", " << component->X() << ", " << component->Y() << "\n";
    Instruction* ci = static_cast<Instruction*>(component);
    std::cout << ci->Name() << "\n";
    Value* value = inst.get();
    std::cout << value->Name() << "\n";
    Instruction* cv = static_cast<Instruction*>(value);
    std::cout << cv->Name() << "\n";
}
