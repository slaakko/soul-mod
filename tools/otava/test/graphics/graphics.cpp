import std.core;

class Shape
{
public:
    Shape();
    virtual ~Shape();
    virtual void Draw() = 0;
};

Shape::Shape()
{
}

Shape::~Shape()
{
}

class Circle : public Shape
{
public:
    void Draw() override;
};

void Circle::Draw()
{
    prints("circle::draw\n", 1);
}

class Square : public Shape
{
public:
    void Draw() override;
};

void Square::Draw()
{
    prints("square::draw\n", 1);
}

class Triangle : public Shape
{
public:
    void Draw() override;
};

void Triangle::Draw()
{
    prints("triangle::draw\n", 1);
}

int main()
{
    std::vector<Shape*> shapes;
    shapes.push_back(new Circle());
    shapes.push_back(new Square());
    shapes.push_back(new Triangle());
    int n = shapes.size();
    for (int i = 0; i < n; ++i)
    {
        Shape* shape = shapes[i];
        shape->Draw();
    }
    for (int i = 0; i < n; ++i)
    {
        Shape* shape = shapes[i];
        delete shape;
    }
    return 0;
}
