#pragma once

#include <algorithm>
#include <ostream>
#include <string>
#include <vector>

#include "../Utils/Operators.hpp"

namespace maze
{
struct LineReader;

class FlatMap
{
public:
    using Size = unsigned;
    using Field = int;
    struct MapPoint
    {
        inline bool operator==(const MapPoint& mp) const { return x == mp.x and y == mp.y; }
        inline bool operator!=(const MapPoint& mp) const { return not operator==(mp); }
        inline unsigned manhattanDistance(const MapPoint& mp) const
        {
            return (std::max(x, mp.x) - std::min(x, mp.x)) +
                   (std::max(y, mp.y) - std::min(y, mp.y));
        }
        inline unsigned squareEuclidesDistance(const MapPoint& mp) const
        {
            return (std::max(x, mp.x) - std::min(x, mp.x))^2 +
                   (std::max(y, mp.y) - std::min(y, mp.y))^2;
        }
        Size x, y;
    };

    FlatMap(Size width, Size height, MapPoint beginpoint, MapPoint endpoint);
    ~FlatMap();

    FlatMap(const FlatMap&) = delete;
    FlatMap operator=(const FlatMap&) = delete;

    FlatMap(FlatMap&& fm);
    const FlatMap& operator=(FlatMap&& fm);

    inline bool isInBorder(const Size x, const Size y) const
    {
        return (x == 0) or (y == 0) or (x + 1 == m_width) or (y + 1 == m_height);
    }

    inline bool isInMap(const Size x, const Size y) const
    {
        return (x < m_width and y < m_height);
    }

    inline bool isAvailable(const Size x, const Size y) const
    {
        return isInMap(x, y) and m_area[x][y] != 1;
    }

    inline std::vector<MapPoint> adjacent(const Size x, const Size y) const
    {
        auto result = std::vector<MapPoint>{};
        if (x > 0 and m_area[x - 1][y] == 0)
        {
            result.push_back({x - 1, y});
        }
        if (y > 0 and m_area[x][y - 1] == 0)
        {
            result.push_back({x, y - 1});
        }
        if (x < m_width - 1 and m_area[x + 1][y] == 0)
        {
            result.push_back({x + 1, y});
        }
        if (y < m_height - 1 and m_area[x][y + 1] == 0)
        {
            result.push_back({x, y + 1});
        }
        return result;
    }

    inline std::vector<MapPoint> adjacent(const MapPoint& mp) const
    {
        return adjacent(mp.x, mp.y);
    }

    inline Field operator()(const Size x, const Size y) const
    {
        return m_area[x][y];
    }

    inline Field& operator()(const Size x, const Size y)
    {
        return m_area[x][y];
    }

    inline auto size() const
    {
        struct { Size width, height; } _size;
        _size.width = m_width;
        _size.height = m_height;
        return _size;
    }

    inline auto begin() const
    {
        return m_begin;
    }

    inline auto end() const
    {
        return m_end;
    }

private:
    MapPoint m_begin;
    MapPoint m_end;
    Size m_width;
    Size m_height;
    Field** m_area;
};

}  // namespace maze

maze::FlatMap& operator<<(maze::FlatMap& fm, const maze::LineReader& line);
std::ostream& operator<<(std::ostream& ostr, const maze::FlatMap& fm);
