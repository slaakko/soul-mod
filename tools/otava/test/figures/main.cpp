import std;

class node
{
public:
    virtual ~node()
    {
        std::cout << "~node" << "\n";
    }
};

class figure : public node
{
public:
    ~figure()
    {
        std::cout << "~figure" << "\n";
    }
};

class circle : public figure
{
public:
    ~circle()
    {
        std::cout << "~circle" << "\n";
    }
};

class square : public figure
{
public:
    ~square()
    {
        std::cout << "~square" << "\n";
    }
};

int main()
{
    std::vector<std::unique_ptr<figure>> figures;
    figures.push_back(std::unique_ptr<figure>(new circle()));
    figures.push_back(std::unique_ptr<figure>(new square()));
}
