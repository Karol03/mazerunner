#pragma once

#include "../SolveStrategy.hpp"

namespace maze
{
namespace solver
{
namespace algorithms
{

class AStar : public SolveStrategy
{
public:
    AStar(UniqueFlatMap ufm);

    Result* run() override;

private:
    Result* solve();
};

}  // namespace algorithms
}  // namespace maze
}  // namespace solver

