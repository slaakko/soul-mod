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
private:
    Errors();
    int nextErrorId;
    std::mutex mtx;
    std::map<int, std::string> errorMap;
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
    std::lock_guard<std::mutex> lock(mtx);
    int errorId = nextErrorId++;
    errorMap[errorId] = msg;
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

int AllocateError(const std::string& msg)
{
    return Errors::Instance().AllocateError(msg);
}

std::string GetErrorMessage(int error)
{
    return Errors::Instance().GetErrorMessage(error);
}

} // util
