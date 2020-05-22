#pragma once

#include <string>

namespace maze
{
struct LineReader;
}  // namespace maze

maze::LineReader& operator<<(maze::LineReader& lr, std::string values);
maze::LineReader& operator<<(maze::LineReader& lr, unsigned number);

namespace maze
{

struct LineReader
{
    std::string values{};
    unsigned number{};
};

}  // namespace maze
