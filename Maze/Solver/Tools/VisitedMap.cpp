#include "VisitedMap.hpp"

#include <string>

namespace maze
{
namespace solver
{
namespace tools
{

VisitedMap::VisitedMap(unsigned width, unsigned height)
    : m_width{width}
    , m_height{height}
    , m_visitedArea{nullptr}
{
    if (m_width > 1 and m_height > 1)
    {
        m_visitedArea = new Point*[width];
        for (auto i{0u}; i < width; ++i)
        {
            m_visitedArea[i] = new Point[height];
            std::memset(m_visitedArea[i], 0xFF, height * sizeof(Point));
        }
    }
}

VisitedMap::~VisitedMap()
{
    if (m_visitedArea)
    {
        for (auto i{0u}; i < m_width; ++i)
        {
            delete [] m_visitedArea[i];
        }
        delete [] m_visitedArea;
    }
    m_visitedArea = nullptr;
}

VisitedMap::VisitedMap(VisitedMap&& vm)
    : m_width{vm.m_width}
    , m_height{vm.m_height}
    , m_visitedArea{vm.m_visitedArea}
{
    vm.m_visitedArea = nullptr;
}

VisitedMap& VisitedMap::operator=(VisitedMap&& vm)
{
    std::swap(m_width, vm.m_width);
    std::swap(m_height, vm.m_height);
    std::swap(m_visitedArea, vm.m_visitedArea);
    return *this;
}

}  // namespace tools
}  // namespace solver
}  // namespace maze
