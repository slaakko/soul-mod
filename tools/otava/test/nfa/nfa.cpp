import std;

class NfaState;

class NfaEdge
{
public:
    NfaEdge(NfaState* next_);
    void Print();
private:
    NfaState* next;
};

class NfaState
{
public:
    NfaState(int id_);
    inline int Id() const { return id; }
private:
    int id;
};

NfaEdge::NfaEdge(NfaState* next_) : next(next_)
{
}

void NfaEdge::Print()
{
    std::string s = std::to_string(next->Id());
    std::cout << s << "\n";
}

NfaState::NfaState(int id_) : id(id_)
{
}

int main()
{
    NfaState* state = new NfaState(2);
    NfaEdge* edge = new NfaEdge(state);
    edge->Print();
}
