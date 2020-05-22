#pragma once

#include "../../../Utils/Operators.hpp"
#include "../../FlatMap.hpp"

namespace maze
{
namespace solver
{
namespace tools
{

class DistanceMap
{
public:
    using Point = FlatMap::MapPoint;

    DistanceMap(unsigned width, unsigned height);
    ~DistanceMap();

    DistanceMap(const DistanceMap&) = delete;
    DistanceMap operator=(const DistanceMap&) = delete;

    DistanceMap(DistanceMap&& vm);
    DistanceMap& operator=(DistanceMap&&);

    inline unsigned operator()(const Point& p) const
    {
        return m_distances[p.x][p.y];
    }

    inline unsigned& operator()(const Point& p)
    {
        return m_distances[p.x][p.y];
    }

private:
    unsigned m_width;
    unsigned m_height;
    unsigned** m_distances;
};

}  // namespace tools
}  // namespace solver
}  // namespace maze
