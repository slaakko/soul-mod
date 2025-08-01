// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module util_expected.log;

import util_expected.text.util;
import util_expected.unicode;

namespace util {

std::mutex logMutex;
LogMode logMode = LogMode::console;
bool endLog = false;
std::list<std::string> log;
std::condition_variable messageEnqueuedOrEndLog;

void SetLogMode(LogMode mode)
{
    logMode = mode;
}

void StartLog()
{
    endLog = false;
}

void EndLog()
{
    for (int i = 0; i < 10; ++i)
    {
        if (!log.empty())
        {
            messageEnqueuedOrEndLog.notify_one();
            std::this_thread::sleep_for(std::chrono::milliseconds{ 500 });
        }
        else
        {
            break;
        }
    }
    endLog = true;
    messageEnqueuedOrEndLog.notify_one();
}

void LogMessage(int logStreamId, const std::string& message)
{
    std::lock_guard<std::mutex> lock(logMutex);
    if (logMode == LogMode::console)
    {
        if (logStreamId == -1)
        {
            std::cout << message << std::endl;
        }
        else
        {
            std::cout << Format(std::to_string(logStreamId), 2, FormatWidth::min, FormatJustify::right, '0') << ">" << message << std::endl;
        }
    }
    else if (logMode == LogMode::queue)
    {
        if (logStreamId == -1)
        {
            log.push_back(message);
        }
        else
        {
            log.push_back(Format(std::to_string(logStreamId), 2, FormatWidth::min, FormatJustify::right, '0') + ">" + message);
        }
        messageEnqueuedOrEndLog.notify_one();
    }
}

void LogMessage(int logStreamId, const std::string& message, int indent)
{
    LogMessage(logStreamId, std::string(indent, ' ') + message);
}

std::string logMessage;

int WaitForLogMessage()
{
    std::unique_lock<std::mutex> lock(logMutex);
    messageEnqueuedOrEndLog.wait(lock, [] { return !log.empty() || endLog; });
    if (!log.empty())
    {
        logMessage = log.front();
        log.pop_front();
        return static_cast<int>(logMessage.length());
    }
    else
    {
        return -1;
    }
}

std::expected<int, int> FetchLogMessage(char16_t* buf, int size)
{
    std::expected<std::u16string, int> rv = ToUtf16(logMessage);
    if (!rv) return std::unexpected<int>(rv.error());
    std::u16string utf16LogMessage = *rv;
    if (size <= utf16LogMessage.length())
    {
        return std::expected<int, int>(-1);
    }
    else
    {
        int n = static_cast<int>(utf16LogMessage.length());
        for (int i = 0; i < n; ++i)
        {
            char16_t c = utf16LogMessage[i];
            buf[i] = c;
        }
        buf[n] = u'\0';
        return std::expected<int, int>(n);
    }
}

std::string FetchLogMessage(bool& endOfLog, int timeoutMs, bool& timeout)
{
    endOfLog = false;
    std::unique_lock<std::mutex> lock(logMutex);
    if (timeoutMs)
    {
        if (!messageEnqueuedOrEndLog.wait_for(lock, std::chrono::milliseconds{ timeoutMs }, [] { return !log.empty() || endLog; }))
        {
            timeout = true;
            return std::string();
        }
    }
    else
    {
        messageEnqueuedOrEndLog.wait(lock, [] { return !log.empty() || endLog; });
    }
    if (!log.empty())
    {
        logMessage = log.front();
        log.pop_front();
        return logMessage;
    }
    endOfLog = true;
    return std::string();
}

} // namespace util
