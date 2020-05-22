#pragma once

#include "../SolveStrategy.hpp"

namespace maze
{
namespace solver
{
namespace algorithms
{

class DoubleAStar : public SolveStrategy
{
public:
    DoubleAStar(UniqueFlatMap ufm);

    Result* run() override;

private:
    Result* solve();
};

}  // namespace algorithms
}  // namespace maze
}  // namespace solver

