import std;
import util;

int main()
{
    std::string path = "D:/work/test_soul/tools/otava/projects/soul/token/tokens.slg";
    std::cout << "PATH=" << path << "\n";
    std::string dir = util::Path::GetDirectoryName(path);
    std::cout << "DIR=" << dir << "\n";
}
