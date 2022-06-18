// main.cpp:

import std.core;
import std.filesystem;
import util;
import soul.rex;

int main()
{
    try
    {
        util::Init();
        soul::rex::context::Context context;
        soul::rex::nfa::Nfa nfa = soul::rex::CompileFilePattern(context, "*.xml");
        for (const auto& entry : std::filesystem::directory_iterator{ "C:/soul-4.0.0/soul/xml/xml_test_data" })
        {
            if (entry.is_regular_file())
            {
                std::string fileName = entry.path().filename().generic_string();
                if (soul::rex::PatternMatch(fileName, nfa))
                {
                    std::cout << fileName << std::endl;
                }
            }

        }
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
        return 1;
    }
    util::Done();
    return 0;
}
