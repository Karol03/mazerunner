#pragma once

#include "../SolveStrategy.hpp"

namespace maze
{
namespace solver
{
namespace algorithms
{

class DFS : public SolveStrategy
{
public:
    DFS(UniqueFlatMap ufm);

    Result* run() override;

private:
    Result* solve();
};

}  // namespace algorithms
}  // namespace maze
}  // namespace solver
