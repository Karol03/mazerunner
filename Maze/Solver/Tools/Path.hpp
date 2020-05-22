#pragma once

#include <string>
#include <vector>

#include "../../FlatMap.hpp"

namespace maze
{
namespace solver
{
namespace tools
{

class Path
{
public:
    using Point = FlatMap::MapPoint;
    using Trace = std::vector<Point>;

    explicit Path();

    inline void save(Point point)
    {
        m_trace.push_back(std::move(point));
    }

    inline void clear()
    {
        m_trace.clear();
    }

    inline const Trace& trace() const
    {
        return m_trace;
    }

    inline auto length() const
    {
        return m_trace.size();
    }

    inline void reverse()
    {
        std::reverse(m_trace.begin(), m_trace.end());
    }

    std::string toString() const;

private:
    Trace m_trace;
};

}  // namespace tools
}  // namespace solver
}  // namespace maze

