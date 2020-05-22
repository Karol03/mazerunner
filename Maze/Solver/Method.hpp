#pragma once

#include <ostream>

namespace maze
{
namespace solver
{

enum class Method
{
    ENot_set,
    ERandom,
    Ebfs,
    Edfs,
    Edijkstra,
    Eastar,
    Edoubleastar
};

Method toType(const int t);

}  // namespace maze
}  // namespace solver

std::ostream& operator<<(std::ostream& ostr, maze::solver::Method stype);
