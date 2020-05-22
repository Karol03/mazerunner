#include "Method.hpp"

namespace maze
{
namespace solver
{

Method toType(const int t)
{
    switch (t)
    {
        case 1: return Method::ERandom;
        case 2: return Method::Ebfs;
        case 3: return Method::Edfs;
        case 4: return Method::Edijkstra;
        case 5: return Method::Eastar;
        case 6: return Method::Edoubleastar;
        default: return Method::ENot_set;
    }
}

}  // namespace solver
}  // namespace maze

std::ostream& operator<<(std::ostream& ostr, maze::solver::Method stype)
{
    switch (stype)
    {
        case maze::solver::Method::ERandom: ostr << "Random way"; break;
        case maze::solver::Method::Ebfs: ostr << "Breadth First Search"; break;
        case maze::solver::Method::Edfs: ostr << "Depth First Search"; break;
        case maze::solver::Method::Edijkstra: ostr << "Dijkstra"; break;
        case maze::solver::Method::Eastar: ostr << "A*"; break;
        case maze::solver::Method::Edoubleastar: ostr << "Double A*"; break;
        default: ostr << "Solver not set"; break;
    }
    return ostr;
}
