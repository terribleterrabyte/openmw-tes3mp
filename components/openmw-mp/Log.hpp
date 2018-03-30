//
// Created by koncord on 15.08.16.
//

#ifndef OPENMW_LOG_HPP
#define OPENMW_LOG_HPP

#include <boost/filesystem.hpp>
#include <boost/format.hpp>
#include <iostream>

#ifdef __GNUC__
#pragma GCC system_header
#endif

#if defined(NOLOGS)
#define LOG_INIT(logLevel)
#define LOG_QUIT()
#define LOG_MESSAGE(level, msg, ...)
#define LOG_MESSAGE_SIMPLE(level, msg, ...)
#else
#define LOG_INIT(logLevel) Log::Get().SetLevel(logLevel)
#define LOG_QUIT()
#if defined(_MSC_VER)
#define LOG_MESSAGE(level, msg, ...) Log::Get().print((level), (1), (__FILE__), (__LINE__), (msg), __VA_ARGS__)
#define LOG_MESSAGE_SIMPLE(level, msg, ...) Log::Get().print((level), (1), (0), (0), (msg), __VA_ARGS__)
#define LOG_APPEND(level, msg, ...) Log::Get().print((level), (0), (0), (0), (msg), __VA_ARGS__)
#else
#define LOG_MESSAGE(level, msg, args...) Log::Get().print((level), (1), (__FILE__), (__LINE__), (msg), ##args)
#define LOG_MESSAGE_SIMPLE(level, msg, args...) Log::Get().print((level), (true), (0), (0), (msg), ##args)
#define LOG_APPEND(level, msg, args...) Log::Get().print((level), (false), (0), (0), (msg), ##args)
#endif
#endif

class Log
{
private:
    std::string Message(boost::format &message) const
    {
        return message.str();
    }

    template<typename T, typename... Args>
    std::string Message(boost::format &msg, T arg, Args&&... args) const
    {
        msg % arg;
        return Message(msg, args...);
    }

    template<typename... Args>
    std::string Message(const std::string &fmt, Args&&... args) const
    {
        boost::format msg(fmt);
        return Message(msg, args...);
    }

public:
    enum
    {
        LOG_OFF = 0,
        LOG_FATAL,
        LOG_ERROR,
        LOG_WARN,
        LOG_INFO,
        LOG_VERBOSE,
        LOG_TRACE,
    };

    static Log &Get()
    {
        static Log instance(1000);
        return instance;
    }

    static int GetLevel()
    {
        return Log::Get().logLevel;
    }

    void SetLevel(int level)
    {
        logLevel = level;
    }

    template<typename... Args>
    void print(int level, bool hasPrefix, const char *file, int line, const std::string &message, Args&&... args) const
    {
        if (level > logLevel || logLevel == LOG_OFF) return;

        if (hasPrefix)
        {
            auto getTime = [this] () {
                time_t t = time(nullptr);
                struct tm *tm = localtime(&t);
                return Message("%.4d-%.2d-%.2d %.2d:%.2d:%.2d",
                               1900 + tm->tm_year, tm->tm_mon + 1, tm->tm_mday,
                               tm->tm_hour, tm->tm_min, tm->tm_sec);
            };

            std::cout << "[" << getTime() << "] ";

            if (file != nullptr && line != 0)
            {
                std::cout << "[" << file << ":";
                std::cout << line << "] ";
            }

            std::cout << "[";
            switch (level)
            {
                case LOG_WARN:
                    std::cout << "WARN";
                    break;
                case LOG_ERROR:
                    std::cout << "ERR";
                    break;
                case LOG_FATAL:
                    std::cout << "FATAL";
                    break;
                case LOG_TRACE:
                    std::cout << "TRACE";
                    break;
                case LOG_VERBOSE:
                case LOG_INFO:
                    std::cout << "INFO";
                    break;
                default:
                    std::cout << "INFO";
            }
            std::cout << "]: ";

        }
        std::string str = Message(message, std::forward<Args&&>(args)...);
        if (str.back() != '\n')
            std::cout << str << std::endl;
        else
            std::cout << str << std::flush;
    }

    Log(const Log &) = delete;
    Log &operator=(Log &) = delete;
private:
    explicit Log(int logLevel) : logLevel(logLevel) {}
    int logLevel;
};


#endif //OPENMW_LOG_HPP
