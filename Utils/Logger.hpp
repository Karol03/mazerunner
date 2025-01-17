#pragma once

#include <iostream>
#include <ctime>
#include <iomanip>
#include <chrono>

#ifdef LOG_SAVE_TO_FILE
    #include <fstream>
    #define OSTREAM file
#else
    #define OSTREAM std::cout
#endif

class Logger
{
private:
    template <typename Head>
    void print(std::ostream& ostr, Head&& head)
    {
        ostr << head << '\n';
    }

    template <typename Head, typename ...Tail>
    void print(std::ostream& ostr, Head&& head, Tail&&... tail)
    {
        ostr << head << ' ';
        print(ostr, std::forward<Tail>(tail)...);
    }

public:
    Logger(const char* file, const char* function, const int line)
        : m_file{file}, m_function{function}, m_line{line}
    {}

    template <typename ...Args>
    void debug(Args&&... args)
    {
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        std::time_t t_c = std::chrono::system_clock::to_time_t(now);
#ifdef LOG_SAVE_TO_FILE
        std::ofstream file("MAZERUNNER.log", std::ios::app | std::ios::ate);
        OSTREAM << '[' << std::put_time(std::localtime(&t_c), "%F %T") << "|"
                << m_file << ':' << m_function << ':' << m_line << "] : ";
        print(OSTREAM, std::forward<Args>(args)...);
#else
        OSTREAM << '[' << std::put_time(std::localtime(&t_c), "%F %T") << "|"
                << m_file << ':' << m_function << ':' << m_line << "] : ";
        print(OSTREAM, std::forward<Args>(args)...);
#endif

    }

private:
    const char* m_file;
    const char* m_function;
    const int m_line;
};

#ifdef LOGGER_ON
#define LOG(...) Logger{__FILE__, __func__, __LINE__}.debug(__VA_ARGS__)
#else
#define LOG(...) do {} while(0)
#endif
