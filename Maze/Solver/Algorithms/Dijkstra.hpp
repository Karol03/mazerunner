#pragma once

#include "../SolveStrategy.hpp"

namespace maze
{
namespace solver
{
namespace algorithms
{

class Dijkstra : public SolveStrategy
{
public:
    Dijkstra(UniqueFlatMap ufm);

    Result* run() override;

private:
    Result* solve();
};

}  // namespace algorithms
}  // namespace maze
}  // namespace solver
