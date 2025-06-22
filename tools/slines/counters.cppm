export module counters;

import std;

export struct Counters
{
    Counters();
    Counters& operator+=(const Counters& that);
    int nprojects;
    int ncpp_projects;
    int nfiles;
    int nlines;
    int nslines;
    int nclines;
    int nbytes;
};

export void PrintResults(const Counters& counters);