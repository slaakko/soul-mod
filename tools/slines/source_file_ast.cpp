module source_file.ast;

import util.file.stream;

namespace source_file::ast {

SourceFile::SourceFile(const std::string& filePath_) : filePath(filePath_), content(util::ReadFile(filePath))
{
    ++counters.nfiles;
}

void SourceFile::ProcessContent()
{
    int state = 0;
    for (char c : content)
    {
        switch (state)
        {
            case 0:
            {
                switch (c)
                {
                    case '/':
                    {
                        state = 1;
                        break;
                    }
                    case ' ': case '\t': case '\r':
                    {
                        break;
                    }
                    case '\n':
                    {
                        ++counters.nlines;
                        break;
                    }
                    default:
                    {
                        state = 3;
                        break;
                    }
                }
                break;
            }
            case 1:
            {
                switch (c)
                {
                    case '/': 
                    {
                        state = 2;
                        break;
                    }
                    case '*':
                    {
                        state = 4;
                        break;
                    }
                    case '\n':
                    {
                        ++counters.nlines;
                        ++counters.nslines;
                        state = 0;
                        break;
                    }
                }
                break;
            }
            case 2:
            {
                switch (c)
                {
                    case '\n':
                    {
                        ++counters.nlines;
                        ++counters.nclines;
                        state = 0;
                        break;
                    }
                }
                break;
            }
            case 3:
            {
                switch (c)
                {
                    case '\n':
                    {
                        ++counters.nlines;
                        ++counters.nslines;
                        state = 0;
                        break;
                    }
                }
                break;
            }
            case 4:
            {
                switch (c)
                {
                    case '*':
                    {
                        state = 5;
                        break;
                    }
                    case '\n':
                    {
                        ++counters.nlines;
                        ++counters.nclines;
                        break;
                    }
                }
                break;
            }
            case 5:
            {
                switch (c)
                {
                    case '/':
                    {
                        state = 0;
                        break;
                    }
                    case '\n':
                    {
                        ++counters.nlines;
                        ++counters.nclines;
                        state = 4;
                        break;
                    }
                    case '*':
                    {
                        break;
                    }
                    default:
                    {
                        state = 4;
                        break;
                    }
                }
                break;
            }
        }
    }
    counters.nbytes += content.size();
}

void ProcessSourceFile(SourceFile* sourceFile)
{
    sourceFile->ProcessContent();
}

} // namespace sourced_file::ast
