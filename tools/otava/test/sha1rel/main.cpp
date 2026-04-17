import std;
import util;

int main()
{
    std::string source = "abc";
    std::string s = util::GetSha1MessageDigest(source);
    std::cout << s << std::endl;
}
