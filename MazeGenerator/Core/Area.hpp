#pragma once

#include <string>
#include <vector>

#include "../../Utils/Operators.hpp"

namespace mazegenerator
{
namespace core
{

class Area
{
public:
    using Point = std::pair<int, int>;
    using PointCollection = std::vector<Point>;

    explicit Area(unsigned width, unsigned height);
    ~Area();

    Area(const Area&) = delete;
    Area operator=(const Area&) = delete;

    Area(Area&&);
    Area& operator=(Area&&);

    inline char operator()(unsigned x, unsigned y) const
    {
        return m_area[x][y];
    }

    inline char operator()(const Point& p) const
    {
        return m_area[p.first][p.second];
    }

    inline char& operator()(unsigned x, unsigned y)
    {
        return m_area[x][y];
    }

    inline char& operator()(const Point& p)
    {
        return m_area[p.first][p.second];
    }

    inline bool isBorder(const unsigned x, const unsigned y) const
    {
        return (x == 0) or (y == 0) or (x + 1 == m_width) or (y + 1 == m_height);
    }

    inline bool isBorder(const Point& p) const
    {
        return isBorder(static_cast<unsigned>(p.first), static_cast<unsigned>(p.second));
    }

    inline bool isIn(const unsigned x, const unsigned y) const
    {
        return x < m_width and y < m_height;
    }

    inline bool isIn(const Point& p) const
    {
        return isIn(static_cast<unsigned>(p.first), static_cast<unsigned>(p.second));
    }

    inline PointCollection adjacent(const unsigned x, const unsigned y) const
    {
        auto result = PointCollection{};
        if (x > 0)
        {
            result.push_back({x - 1, y});
        }
        if (y > 0)
        {
            result.push_back({x, y - 1});
        }
        if (x < m_width - 1)
        {
            result.push_back({x + 1, y});
        }
        if (y < m_height - 1)
        {
            result.push_back({x, y + 1});
        }
        return result;
    }

    inline PointCollection adjacent(const unsigned x, const unsigned y, const char value) const
    {
        auto result = PointCollection{};
        if (x > 0 and m_area[x - 1][y] == value)
        {
            result.push_back({x - 1, y});
        }
        if (y > 0 and m_area[x][y - 1] == value)
        {
            result.push_back({x, y - 1});
        }
        if (x < m_width - 1 and m_area[x + 1][y] == value)
        {
            result.push_back({x + 1, y});
        }
        if (y < m_height - 1 and m_area[x][y + 1] == value)
        {
            result.push_back({x, y + 1});
        }
        return result;
    }

    inline PointCollection adjacent(const Point& p) const
    {
        return adjacent(static_cast<unsigned>(p.first), static_cast<unsigned>(p.second));
    }

    inline PointCollection adjacent(const Point& p, const char value) const
    {
        return adjacent(static_cast<unsigned>(p.first), static_cast<unsigned>(p.second), value);
    }

    std::string toString() const;

private:
    char** m_area;
    unsigned m_width;
    unsigned m_height;
};


}  // namespace core
}  // namespace mazegenerator


