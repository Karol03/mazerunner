#pragma once

#include <iostream>
#include <ctime>
#include <iomanip>
#include <chrono>

#define OSTREAM std::cout

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
    Logger(const char* function, const int line) : m_function{function}, m_line{line} {}

    template <typename ...Args>
    void debug(Args&&... args)
    {
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        std::time_t t_c = std::chrono::system_clock::to_time_t(now);
        OSTREAM << '[' << std::put_time(std::localtime(&t_c), "%F %T") << "|"
                << m_function << ':' << m_line << "] : ";
        print(OSTREAM, std::forward<Args>(args)...);
    }

private:
    const char* m_function;
    const int m_line;
};

#ifdef LOGGER_ON
#define LOG(...) Logger{__func__, __LINE__}.debug(__VA_ARGS__)
#else
#define LOG(...) do {} while(0)
#endif
