#pragma once

#include "../SolveStrategy.hpp"

namespace maze
{
namespace solver
{
namespace algorithms
{

class RandomMove : public SolveStrategy
{
public:
    RandomMove(UniqueFlatMap ufm);

    Result* run() override;

private:
    Result* solve();
};

}  // namespace algorithms
}  // namespace maze
}  // namespace solver

