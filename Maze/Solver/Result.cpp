#include "Result.hpp"

#include <sstream>

namespace maze
{
namespace solver
{

std::string Result::header()
{
    auto result = std::stringstream{};
    result << "w x h | method | time (s) | discovered blocks | path length";
    return result.str();
}

std::string Result::toString() const
{
    auto result = std::stringstream{};
    result << width << 'x' << height << " | "
           << method << " | "
           << time << " | "
           << discovered.length() << " | "
           << trace.length();
    return result.str();
}

}  // namespace maze
}  // namespace solver
