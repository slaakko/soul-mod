import std;

class QualifiedIdNode
{
public:
    QualifiedIdNode(int x_) : x(x_) {}
private:
    int x;
};

int main()
{
    QualifiedIdNode* qid(new QualifiedIdNode(1));
}
