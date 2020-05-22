#include "BFS.hpp"

#include <chrono>
#include <queue>

#include "../../../Utils/Logger.hpp"
#include "../Tools/VisitedMap.hpp"
#include "../Result.hpp"

namespace maze
{
namespace solver
{
namespace algorithms
{

BFS::BFS(UniqueFlatMap ufm)
    : SolveStrategy{std::move(ufm)}
{}

Result* BFS::run()
{
    LOG("Solve using Breadth First Search method");
    return solve();
}

Result* BFS::solve()
{
    auto visited = tools::VisitedMap{m_flatmap->size().width, m_flatmap->size().height};
    auto ways = std::queue<tools::Path::Point>{};
    ways.push(m_flatmap->begin());

    auto position = m_flatmap->begin();
    visited.visit(position, {0, 0});
    m_discovered.save(position);
    auto begin = std::chrono::high_resolution_clock::now();
    while (not ways.empty())
    {
        position = ways.front();
        ways.pop();

        for (const auto& adjacent : m_flatmap->adjacent(position))
        {
            if (not visited.isVisited(adjacent))
            {
                visited.visit(adjacent, position);
                ways.push(adjacent);
                m_discovered.save(adjacent);

                if (adjacent == m_flatmap->end())
                {
                    position = adjacent;
                    goto finish;
                }
            }
        }
    }
    finish:
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

    return new Result{std::move(pathToExit),
                      std::move(m_discovered),
                      time.count(),
                      m_flatmap->size().width,
                      m_flatmap->size().height,
                      Method::Ebfs};
}

}  // namespace algorithms
}  // namespace maze
}  // namespace solver

