import std.core;
import util;

int main()
{
    util::FileStream* fstream = new util::FileStream("C:\\work\\soul-mod\\util\\binary_resource_ptr.cpp", util::OpenMode::read);
    std::cout << fstream->FilePath() << std::endl;
    int64_t s = fstream->Size();
    return 0;
}
