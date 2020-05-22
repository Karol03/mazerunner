#pragma once

#include "Path.hpp"

namespace maze
{
namespace solver
{
namespace tools
{

struct PriorityPoint
{
public:
    PriorityPoint() = default;
    PriorityPoint(Path::Point p) : point{std::move(p)} {}
    PriorityPoint(Path::Point p, unsigned c) : point{std::move(p)}, prio{c} {}
    inline bool operator<(const PriorityPoint& p) const { return prio < p.prio; }

public:
    tools::Path::Point point;
    unsigned prio;
};

}  // namespace tools
}  // namespace solver
}  // namespace maze
