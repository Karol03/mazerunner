#pragma once

#include <random>
#include <chrono>


namespace maze
{
namespace solver
{
namespace tools
{

class Random
{
public:
    Random()
    {
        m_rng = std::mt19937(static_cast<unsigned>(current_time()));
    }

    inline int get(const int max)
    {
        std::uniform_int_distribution<std::mt19937::result_type> dist(0, max);
        return static_cast<int>(dist(m_rng));
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

}  // namespace tools
}  // namespace solver
}  // namespace maze
