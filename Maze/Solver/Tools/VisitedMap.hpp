#pragma once

#include <limits>

#include "../../../Utils/Operators.hpp"
#include "../../FlatMap.hpp"
#include "Path.hpp"

namespace maze
{
namespace solver
{
namespace tools
{

class VisitedMap
{
public:
    using Point = FlatMap::MapPoint;

    VisitedMap(unsigned width, unsigned height);
    ~VisitedMap();

    VisitedMap(const VisitedMap&) = delete;
    VisitedMap operator=(const VisitedMap&) = delete;

    VisitedMap(VisitedMap&& vm);
    VisitedMap& operator=(VisitedMap&&);

    inline void visit(const Point& p, const Point& from)
    {
        m_visitedArea[p.x][p.y] = from;
    }

    inline bool isVisited(const Point& p) const
    {
        return m_visitedArea[p.x][p.y] != Point{UINT_MAX, UINT_MAX};
    }

    inline Path path(Point end) const
    {
        auto result = Path{};
        while (end != Point{0, 0})
        {
            result.save(end);
            end = m_visitedArea[end.x][end.y];
        }
        result.reverse();
        return result;
    }

private:
    unsigned m_width;
    unsigned m_height;
    Point** m_visitedArea;
};

}  // namespace tools
}  // namespace solver
}  // namespace maze
