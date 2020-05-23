#include "AStar.hpp"

#include <chrono>
#include <queue>

#include "../../../Utils/Logger.hpp"
#include "../../FlatMap.hpp"
#include "../Tools/DistanceMap.hpp"
#include "../Tools/VisitedMap.hpp"
#include "../Tools/PriorityPoint.hpp"
#include "../Result.hpp"

using PriorityPoints = std::vector<maze::solver::tools::PriorityPoint>;
using rprority_queue = std::priority_queue<PriorityPoints::value_type,
                                          PriorityPoints,
                                          std::greater<typename PriorityPoints::value_type>>;

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

AStar::AStar(UniqueFlatMap ufm)
    : SolveStrategy{std::move(ufm)}
{}

Result* AStar::run()
{
    LOG("Solve using A* algorithm");
    return solve();
}

Result* AStar::solve()
{
    auto visited = tools::VisitedMap{m_flatmap->size().width, m_flatmap->size().height};
    auto distances = tools::DistanceMap{m_flatmap->size().width, m_flatmap->size().height};
    auto ways = rprority_queue{};
    ways.push(m_flatmap->begin());

    auto position = m_flatmap->begin();
    const auto& endpoint = m_flatmap->end();
    visited.visit(position, {0, 0});
    distances(position) = 0;
    m_discovered.save(position);
    auto begin = std::chrono::high_resolution_clock::now();
    while (not ways.empty())
    {
        position = ways.top().point;
        ways.pop();

        if (position == endpoint)
        {
            break;
        }

        for (const auto& adjacent : m_flatmap->adjacent(position))
        {
            auto adjDistance = distances(position) + ONE_STEP_COST;
            if (not visited.isVisited(adjacent) or adjDistance < distances(adjacent))
            {
                distances(adjacent) = adjDistance;
                auto priority = adjDistance + endpoint.manhattanDistance(adjacent);

                ways.push({adjacent, priority});
                visited.visit(adjacent, position);
                m_discovered.save(adjacent);
            }
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto time = std::chrono::duration<double>(end - begin);
    auto pathToExit = tools::Path{};

    LOG("Finished\nDiscovered [", m_discovered.length() ,"] blocks in ", time.count(), " seconds\n",
        "Exploring path: ", m_discovered.toString());
    if (position == m_flatmap->end())
    {
        pathToExit = visited.path(position);
        LOG("Exit found\nPath to exit goes through: ", pathToExit.toString());
    }
    else
    {
        LOG("Exit not found");
    }

    return new Result{std::move(m_flatmap),
                      std::move(pathToExit),
                      std::move(m_discovered),
                      time.count(),
                      Method::Eastar};
}

}  // namespace algorithms
}  // namespace maze
}  // namespace solver

