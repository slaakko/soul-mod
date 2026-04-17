import std;

/*
void foo(const std::string& s)
{
    std::cout << s << "\n";
}
*/

std::string GetPathToExecutable()
{
    char buf[4096];
    bool result = ort_get_path_to_executable(buf, 4096);
    if (result)
    {
        return std::string(buf);
    }
    else
    {
        std::uint32_t error = ort_get_last_windows_error();
        ort_get_windows_error_message(error, buf, 4096);
        std::string msg(buf);
        throw std::runtime_error("could not get path to current executable: " + msg);
    }
}

void foo()
{
    std::string s = GetPathToExecutable();
    std::cout << s << "\n";
}

int main()
{
    foo();
    //foo("abc");
    //util::CodeFormatter formatter(std::cout);
    //formatter.WriteLine("foo");
}
