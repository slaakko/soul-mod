// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module util.error;

namespace util {

class Errors
{
public:
    static Errors& Instance();
    int AllocateError(const std::string& msg);
    std::string GetErrorMessage(int error) const;
    std::string GetStackTrace(int error) const;
    void FreeStackTrace(int error);
private:
    Errors();
    int nextErrorId;
    std::mutex mtx;
    std::map<int, std::string> errorMap;
    std::map<int, int> traceMap;
};

Errors& Errors::Instance()
{
    static Errors instance;
    return instance;
}

Errors::Errors() : nextErrorId(1)
{
}

int Errors::AllocateError(const std::string& msg)
{
    int errorId = nextErrorId++;
    errorMap[errorId] = msg;
    int stackTrace = ort_generate_stack_trace();
    traceMap[errorId] = stackTrace;
    return errorId;
}

std::string Errors::GetErrorMessage(int error) const
{
    auto it = errorMap.find(error);
    if (it != errorMap.end())
    {
        return it->second;
    }
    else
    {
        return std::string();
    }
}

std::string Errors::GetStackTrace(int error) const
{
    auto it = traceMap.find(error);
    if (it != traceMap.end())
    {
        int traceId = it->second;
        if (traceId != -1)
        {
            const char* trace = ort_get_stack_trace(traceId);
            if (trace)
            {
                return std::string(trace);
            }
        }
    }
    return std::string();
}

void Errors::FreeStackTrace(int error)
{
    auto it = traceMap.find(error);
    if (it != traceMap.end())
    {
        int traceId = it->second;
        if (traceId != -1)
        {
            ort_free_stack_trace(traceId);
        }
    }
}

int AllocateError(const std::string& msg)
{
    return Errors::Instance().AllocateError(msg);
}

std::string GetErrorMessage(int error, bool includeStackTrace)
{
    std::string errorMessage = Errors::Instance().GetErrorMessage(error);
    if (includeStackTrace)
    {
        std::string stackTrace = Errors::Instance().GetStackTrace(error);
        if (!stackTrace.empty())
        {
            errorMessage.append("\n").append(stackTrace);
        }
    }
    return errorMessage;
}

std::string GetErrorMessage(int error)
{
    return GetErrorMessage(error, false);
}

std::string GetStackTrace(int error)
{
    return Errors::Instance().GetStackTrace(error);
}

void FreeStackTrace(int error)
{
    Errors::Instance().FreeStackTrace(error);
}

} // util
