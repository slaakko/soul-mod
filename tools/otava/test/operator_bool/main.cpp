import std;

class Visitor
{
public:
    Visitor(bool valid_) : valid(valid_) {}
    bool Valid() const { return valid; }
    explicit inline operator bool() const { return Valid(); }
private:
    bool valid;
};

class Derived : public Visitor
{
public:
    Derived(bool valid_) : Visitor(valid_) {} 
};

int main()
{
    Derived derived(false);
    if (!derived)
    {
        std::cout << "not valid\n";
    }
    else
    {
        std::cout << "valid\n";
    }
}
