#include "DoubleAStar.hpp"

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
    auto visitedBegin = tools::VisitedMap{m_flatmap->size().width, m_flatmap->size().height};
    auto visitedEnd = tools::VisitedMap{m_flatmap->size().width, m_flatmap->size().height};
    auto distances = tools::DistanceMap{m_flatmap->size().width, m_flatmap->size().height};

    auto pathToExit = tools::Path{};
    auto startways = rprority_queue{};
    startways.push(m_flatmap->begin());

    auto endways = rprority_queue{};
    endways.push(m_flatmap->end());

    auto startposition = m_flatmap->begin();
    auto endposition = m_flatmap->end();

    const auto& endpoint = m_flatmap->end();
    visitedBegin.visit(startposition, {0, 0});
    distances(startposition) = 0;

    visitedEnd.visit(endposition, {0, 0});
    distances(endposition) = 0;

    m_discovered.save(startposition);
    m_discovered.save(endposition);
    auto end = std::chrono::high_resolution_clock::now();
    auto begin = std::chrono::high_resolution_clock::now();
    while (not startways.empty() and not endways.empty())
    {
        startposition = startways.top().point;
        startways.pop();

        if (visitedEnd.isVisited(startposition))
        {
            pathToExit = visitedBegin.path(startposition);
            pathToExit.merge(visitedEnd.path(startposition));
            end = std::chrono::high_resolution_clock::now();
            goto finish;
        }

        for (const auto& adjacent : m_flatmap->adjacent(startposition))
        {
            auto adjDistance = distances(startposition) + ONE_STEP_COST;
            if (not visitedBegin.isVisited(adjacent) or adjDistance < distances(adjacent))
            {
                distances(adjacent) = adjDistance;
                auto priority = adjDistance + endpoint.manhattanDistance(adjacent);

                startways.push({adjacent, priority});
                visitedBegin.visit(adjacent, startposition);
                m_discovered.save(adjacent);
            }
        }

        endposition = endways.top().point;
        endways.pop();
        if (visitedBegin.isVisited(endposition))
        {
            pathToExit = visitedBegin.path(endposition);
            pathToExit.merge(visitedEnd.path(endposition));
            end = std::chrono::high_resolution_clock::now();
            goto finish;
        }

        for (const auto& adjacent : m_flatmap->adjacent(endposition))
        {
            auto adjDistance = distances(endposition) + ONE_STEP_COST;
            if (not visitedEnd.isVisited(adjacent) or adjDistance < distances(adjacent))
            {
                distances(adjacent) = adjDistance;
                auto priority = adjDistance + endpoint.manhattanDistance(adjacent);

                endways.push({adjacent, priority});
                visitedEnd.visit(adjacent, endposition);
                m_discovered.save(adjacent);
            }
        }
    }
    end = std::chrono::high_resolution_clock::now();
    finish:
    auto time = std::chrono::duration<double>(end - begin);

    LOG("Finished\nDiscovered [", m_discovered.length() ,"] blocks in ", time.count(), " seconds\n",
        "Exploring path: ", m_discovered.toString());
    if (pathToExit.length() > 0)
    {
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
                      Method::Edoubleastar};
}

}  // namespace algorithms
}  // namespace maze
}  // namespace solver

