#include "Solver.hpp"

#include "../../Utils/Logger.hpp"

#include "Algorithms/AStar.hpp"
#include "Algorithms/BFS.hpp"
#include "Algorithms/DFS.hpp"
#include "Algorithms/DoubleAStar.hpp"
#include "Algorithms/Dijkstra.hpp"
#include "Algorithms/RandomMove.hpp"

namespace maze
{
namespace solver
{

Solver::Solver(SolveStrategy::UniqueFlatMap ufm, Type type)
    : m_strategy{nullptr}
{
    create(std::move(ufm), type);
    if (m_strategy)
    {
        LOG("Choosen solve way \"", type, "\"");
    }
    else
    {
        LOG("Solver \"", type, "\" not available. Invalid given type or missing implementation");
    }
}

void Solver::create(SolveStrategy::UniqueFlatMap ufm, Type type)
{
    m_strategy.reset();
    switch (type)
    {
        case maze::solver::Solver::Type::ERandom:
            m_strategy = std::make_unique<algorithms::RandomMove>(std::move(ufm));
            break;
        case maze::solver::Solver::Type::Ebfs:
            m_strategy = std::make_unique<algorithms::BFS>(std::move(ufm));
            break;
        case maze::solver::Solver::Type::Edfs:
            m_strategy = std::make_unique<algorithms::DFS>(std::move(ufm));
            break;
        case maze::solver::Solver::Type::Edijkstra:
            m_strategy = std::make_unique<algorithms::Dijkstra>(std::move(ufm));
            break;
        case maze::solver::Solver::Type::Eastar:
            m_strategy = std::make_unique<algorithms::AStar>(std::move(ufm));
            break;
        case maze::solver::Solver::Type::Edoubleastar:
            m_strategy = std::make_unique<algorithms::DoubleAStar>(std::move(ufm));
            break;
        default:
            break;
    }
}

}  // namespace solver
}  // namespace maze

