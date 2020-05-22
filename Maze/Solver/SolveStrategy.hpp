#pragma once

#include "../FlatMap.hpp"
#include "Tools/Path.hpp"

namespace maze
{
namespace solver
{
struct Result;

class SolveStrategy
{
public:
    using UniqueFlatMap = std::unique_ptr<FlatMap>;

    SolveStrategy(UniqueFlatMap flatmap);
    virtual ~SolveStrategy() = default;

    virtual Result* run() = 0;

protected:
    tools::Path m_discovered;
    UniqueFlatMap m_flatmap;
};

}  // namespace solver
}  // namespace maze
