#pragma once

#include <random>
#include <chrono>


namespace utils
{

class Random
{
public:
    Random()
    {
        m_rng = std::mt19937(static_cast<unsigned>(current_time()));
    }

    inline unsigned get(const unsigned max)
    {
        std::uniform_int_distribution<std::mt19937::result_type> dist(0, max);
        return dist(m_rng);
    }

private:
    inline long long current_time()
    {
        auto now = std::chrono::system_clock::now();
        return now.time_since_epoch().count();
    }

private:
    static std::mt19937 m_rng;
};

}  // namespace utils
