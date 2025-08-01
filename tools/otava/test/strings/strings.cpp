import std;

int main()
{ 
    std::string empty;
    std::string s = "foo";
    empty.append(s);
    std::cout << empty << "\n";
}
