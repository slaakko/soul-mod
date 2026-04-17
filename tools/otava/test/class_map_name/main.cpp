import std;
import util;

void foo()
{
    std::string currentExecutableName = util::Path::GetFileName(util::GetFullPath(util::GetPathToExecutable()));
    std::cout << currentExecutableName << "\n";
}

int main()
{
    foo();
}
