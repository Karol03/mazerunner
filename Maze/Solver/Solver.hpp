#pragma once

#include <memory>
#include "SolveStrategy.hpp"
#include "Method.hpp"
#include "Result.hpp"

namespace maze
{
namespace solver
{

class Solver
{
public:
    using Type = Method;

public:
    Solver(SolveStrategy::UniqueFlatMap ufm, Type type);

    inline auto run()
    {
        auto result = std::unique_ptr<Result>{};
        if (m_strategy)
        {
            result.reset(m_strategy->run());
        }
        return result;
    }

private:
    void create(SolveStrategy::UniqueFlatMap ufm, Type type);

private:
    std::unique_ptr<SolveStrategy> m_strategy;
};

}  // namespace solver
}  // namespace maze

