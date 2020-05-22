#include "DistanceMap.hpp"

namespace maze
{
namespace solver
{
namespace tools
{

DistanceMap::DistanceMap(unsigned width, unsigned height)
    : m_width{width}
    , m_height{height}
    , m_distances{nullptr}
{
    if (m_width > 1 and m_height > 1)
    {
        m_distances = new unsigned*[width];
        for (auto i{0u}; i < width; ++i)
        {
            m_distances[i] = new unsigned[height];
            std::memset(m_distances[i], 0xFF, height * sizeof(unsigned));
        }
    }
}

DistanceMap::~DistanceMap()
{
    if (m_distances)
    {
        for (auto i{0u}; i < m_width; ++i)
        {
            delete [] m_distances[i];
        }
        delete [] m_distances;
    }
    m_distances = nullptr;
}

DistanceMap::DistanceMap(DistanceMap&& dm)
    : m_width{dm.m_width}
    , m_height{dm.m_height}
    , m_distances{dm.m_distances}
{
    dm.m_distances = nullptr;
}

DistanceMap& DistanceMap::operator=(DistanceMap&& dm)
{
    std::swap(m_width, dm.m_width);
    std::swap(m_height, dm.m_height);
    std::swap(m_distances, dm.m_distances);
    return *this;
}
}  // namespace tools
}  // namespace solver
}  // namespace maze
