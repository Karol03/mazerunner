#include "LineReader.hpp"

#include <utility>

maze::LineReader& operator<<(maze::LineReader& lr, std::string values)
{
    std::swap(lr.values, values);
    return lr;
}

maze::LineReader& operator<<(maze::LineReader& lr, unsigned number)
{
    std::swap(lr.number, number);
    return lr;
}
