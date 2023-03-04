module counters;

import util.text.util;
import util.unicode;

Counters::Counters() : nprojects(0), ncpp_projects(0), nfiles(0), nlines(0), nslines(0), nclines(0), nbytes(0)
{
}

Counters& Counters::operator+=(const Counters& that)
{
    nprojects += that.nprojects;
    ncpp_projects += that.ncpp_projects;
    nfiles += that.nfiles;
    nlines += that.nlines;
    nslines += that.nslines;
    nclines += that.nclines;
    nbytes += that.nbytes;
    return *this;
}

std::string FormatNumber(int x, int width)
{
    std::string s;
    for (int i = 0; i < width; ++i)
    {
        int digit = x % 10;
        x /= 10;
        s = std::string(1, '0' + digit) + s;
        if (i % 3 == 2)
        {
            s = " " + s;
        }
        if (x == 0) break;
    }
    return s;
}

void PrintResults(const Counters& counters)
{
    std::cout << util::Format("projects", 16);
    std::cout << " : ";
    std::cout << util::Format(FormatNumber(counters.nprojects, 16), 16, util::FormatJustify::right);
    std::cout << "\n";

    std::cout << util::Format("C++ projects", 16);
    std::cout << " : ";
    std::cout << util::Format(FormatNumber(counters.ncpp_projects, 16), 16, util::FormatJustify::right);
    std::cout << "\n";

    std::cout << util::Format("files", 16);
    std::cout << " : ";
    std::cout << util::Format(FormatNumber(counters.nfiles, 16), 16, util::FormatJustify::right);
    std::cout << "\n";

    std::cout << util::Format("lines", 16);
    std::cout << " : ";
    std::cout << util::Format(FormatNumber(counters.nlines, 16), 16, util::FormatJustify::right);
    std::cout << "\n";

    std::cout << util::Format("source lines", 16);
    std::cout << " : ";
    std::cout << util::Format(FormatNumber(counters.nslines, 16), 16, util::FormatJustify::right);
    std::cout << "\n";

    std::cout << util::Format("comment lines", 16);
    std::cout << " : ";
    std::cout << util::Format(FormatNumber(counters.nclines, 16), 16, util::FormatJustify::right);
    std::cout << "\n";

    std::cout << util::Format("bytes", 16);
    std::cout << " : ";
    std::cout << util::Format(FormatNumber(counters.nbytes, 16), 16, util::FormatJustify::right);
    std::cout << "\n";
}