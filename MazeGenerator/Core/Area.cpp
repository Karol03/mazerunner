#include "Area.hpp"

#include <sstream>

namespace mazegenerator
{
namespace core
{

Area::Area(unsigned width, unsigned height)
    : m_area{nullptr}
    , m_width{width}
    , m_height{height}
{
    if (m_width > 1 and m_height > 1)
    {
        m_area = new char*[m_width];
        for (auto i{0u}; i < m_width; ++i)
        {
            m_area[i] = new char[m_height];

            std::memset(m_area[i], 0xFF, sizeof(char)*m_height);
            m_area[i][0] = 1;
            m_area[i][m_height - 1] = 1;
        }
        std::memset(m_area[0], 1, sizeof(char)*m_height);
        std::memset(m_area[m_width - 1], 1, sizeof(char)*m_height);
    }
}

Area::~Area()
{
    if (m_area)
    {
        for (auto i{0u}; i < m_width; ++i)
        {
            delete [] m_area[i];
        }
        delete [] m_area;
    }
    m_area = nullptr;
}

Area::Area(Area&& a)
    : m_area{a.m_area}
    , m_width{a.m_width}
    , m_height{a.m_height}
{
    a.m_area = nullptr;
}

Area& Area::operator=(Area&& a)
{
    std::swap(m_area, a.m_area);
    std::swap(m_width, a.m_width);
    std::swap(m_height, a.m_height);
    return *this;
}

std::string Area::toString() const
{
    auto result = std::stringstream{};
    for (auto i{0u}; i < m_height; ++i)
    {
        result << static_cast<char>('0' + m_area[0][i]);
        for (auto j{1u}; j < m_width; ++j)
        {
            result << ' ' << static_cast<char>('0' + m_area[j][i]);
        }
        result << '\n';
    }
    return result.str();
}

}  // namespace mazegenerator
}  // namespace core
