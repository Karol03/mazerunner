#include "MazeGenerator.hpp"

#include "Core/Generator.hpp"
#include "Utils/Logger.hpp"

#define POINT_NOT_SET mazegenerator::MazeGenerator::Point{-1, -1}
#define MINIMAL_MAZE_WALL_SIZE 4u

namespace mazegenerator
{

MazeGenerator::MazeGenerator(Size width, Size height)
    : m_begin{POINT_NOT_SET}
    , m_end{POINT_NOT_SET}
    , m_width{width}
    , m_height{height}
{}

bool MazeGenerator::isInRange(const Point& point) const
{
    if (point == POINT_NOT_SET)
    {
        LOG("Set begin and end previously");
        return false;
    }
    else if (point.first >= m_width)
    {
        LOG("Endpoint is not in available area. A width must be bigger");
        return false;
    }
    else if (point.second >= m_height)
    {
        LOG("Endpoint is not in available area. A height must be bigger");
        return false;
    }
    return true;
}

bool MazeGenerator::isProperlyConfigured() const
{
    if (m_width <= MINIMAL_MAZE_WALL_SIZE)
    {
        LOG("Width must be bigger than", MINIMAL_MAZE_WALL_SIZE);
        return false;
    }
    else if (m_height <= MINIMAL_MAZE_WALL_SIZE)
    {
        LOG("Height must be bigger than", MINIMAL_MAZE_WALL_SIZE);
        return false;
    }
    else if (not isInRange(m_begin))
    {
        LOG("Invalid begin point values. Maze not generated");
        return false;
    }
    else if (not isInRange(m_end))
    {
        LOG("Invalid end point values. Maze not generated");
        return false;
    }
    return true;
}

bool MazeGenerator::generate()
{
    if (isProperlyConfigured())
    {
        return core::Generator{m_width, m_height,
                               static_cast<unsigned>(m_begin.first),
                               static_cast<unsigned>(m_begin.second),
                               static_cast<unsigned>(m_end.first),
                               static_cast<unsigned>(m_end.second)}.save(m_filename.c_str());
    }
    return false;
}

}  // namespace mazegenerator
