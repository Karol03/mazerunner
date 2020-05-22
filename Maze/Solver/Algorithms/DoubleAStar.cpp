#include "DoubleAStar.hpp"

#include <chrono>
#include <queue>

#include "../../../Utils/Logger.hpp"
#include "../../FlatMap.hpp"
#include "../Tools/DistanceMap.hpp"
#include "../Tools/VisitedMap.hpp"
#include "../Tools/PriorityPoint.hpp"
#include "../Result.hpp"

namespace maze
{
namespace solver
{
namespace algorithms
{
namespace
{
const auto ONE_STEP_COST = 1u;
}  // namespace

DoubleAStar::DoubleAStar(UniqueFlatMap ufm)
    : SolveStrategy{std::move(ufm)}
{}

Result* DoubleAStar::run()
{
    LOG("Solve using Double A* algorithm");
    return solve();
}

Result* DoubleAStar::solve()
{
    return {};
}

}  // namespace algorithms
}  // namespace maze
}  // namespace solver

