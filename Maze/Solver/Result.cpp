#include "Result.hpp"

#include <sstream>

constexpr auto SEPARATOR = ";";

namespace maze
{
namespace solver
{

std::string Result::header()
{
    auto result = std::stringstream{};
    result << "w x h" << SEPARATOR << "algorithm" << SEPARATOR
           << "time (s)" << SEPARATOR << "discovered blocks" << SEPARATOR
           << "path length";
    return result.str();
}

std::string Result::toString() const
{
    auto result = std::stringstream{};
    if (map)
    {
        result << map->size().width << 'x' << map->size().height << SEPARATOR;
    }
    result << method << SEPARATOR
           << time << SEPARATOR
           << discovered.length() << SEPARATOR
           << trace.length();
    return result.str();
}

}  // namespace maze
}  // namespace solver
