#include "RandomMove.hpp"

#include <vector>

#include "../../../Utils/Logger.hpp"
#include "../../../Utils/Random.hpp"
#include "../Tools/VisitedMap.hpp"
#include "../Result.hpp"

namespace maze
{
namespace solver
{
namespace algorithms
{

RandomMove::RandomMove(UniqueFlatMap ufm)
    : SolveStrategy{std::move(ufm)}
{}

Result* RandomMove::run()
{
    LOG("Solve using random moves");
    return solve();
}

Result* RandomMove::solve()
{
    auto randomizer = utils::Random{};
    auto visited = tools::VisitedMap{m_flatmap->size().width, m_flatmap->size().height};
    auto ways = std::vector<tools::Path::Point>{};
    auto pos{0u};
    ways.push_back(m_flatmap->begin());

    auto position = m_flatmap->begin();
    visited.visit(position, {0, 0});
    m_discovered.save(position);
    auto begin = std::chrono::high_resolution_clock::now();
    while (not ways.empty())
    {
        pos = static_cast<unsigned>(randomizer.get(static_cast<int>(ways.size() - 1)));
        position = ways[pos];
        if (pos + 1 != ways.size())
        {
            std::swap(ways[pos], ways[ways.size() - 1]);
        }
        ways.pop_back();

        for (const auto& adjacent : m_flatmap->adjacent(position))
        {
            if (not visited.isVisited(adjacent))
            {
                visited.visit(adjacent, position);
                ways.push_back(adjacent);
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

    return new Result{std::move(m_flatmap),
                      std::move(pathToExit),
                      std::move(m_discovered),
                      time.count(),
                      Method::ERandom};
}

}  // namespace algorithms
}  // namespace maze
}  // namespace solver

