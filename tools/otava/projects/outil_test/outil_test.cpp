import std;
import util;

int main()
{
    util::FileStream fs("foo", util::OpenMode::read);
    if (!fs)
    {
        std::cerr << util::GetErrorMessage(fs.Error()) << "\n";
        return 1;
    }
}
