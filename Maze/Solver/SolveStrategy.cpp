#include "SolveStrategy.hpp"

namespace maze
{
namespace solver
{

SolveStrategy::SolveStrategy(UniqueFlatMap ufm)
    : m_flatmap{std::move(ufm)}
{}

}  // namespace maze
}  // namespace solver
