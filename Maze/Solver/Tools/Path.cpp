#include "Path.hpp"

#include <sstream>

namespace maze
{
namespace solver
{
namespace tools
{

Path::Path()
{
    m_trace.reserve(128);
}

std::string Path::toString() const
{
    auto result = std::stringstream{};
    if (m_trace.empty())
    {
        return {};
    }
    result << "(" << m_trace[0].x << ", " << m_trace[0].y << ")";
    for (auto i{1u}; i < m_trace.size(); ++i)
    {
        result << " -> (" << m_trace[i].x << ", " << m_trace[i].y << ")";
    }
    return result.str();
}

}  // namespace tools
}  // namespace solver
}  // namespace maze
