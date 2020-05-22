#include "FlatMap.hpp"

#include <sstream>
#include <ostream>

#include "LineReader.hpp"

namespace maze
{

FlatMap::FlatMap(Size width, Size height, MapPoint beginpoint, MapPoint endpoint)
    : m_begin{beginpoint}
    , m_end{endpoint}
    , m_width{width}
    , m_height{height}
    , m_area{nullptr}
{
    if (m_width > 1 and m_height > 1)
    {
        m_area = new Field*[m_width];
        for (Size i = 0; i < m_width; ++i)
        {
            m_area[i] = new Field[m_height];
            std::memset(m_area[i], 0, sizeof(Field)*m_height);
        }
    }
}

FlatMap::~FlatMap()
{
    if (m_area)
    {
        for (Size i = 0; i < m_width; ++i)
        {
            delete [] m_area[i];
        }
        delete [] m_area;
    }
    m_area = nullptr;
}

FlatMap::FlatMap(FlatMap&& fm)
{
    std::swap(m_width, fm.m_width);
    std::swap(m_height, fm.m_height);
    std::swap(m_area, fm.m_area);
}

const FlatMap& FlatMap::operator=(FlatMap&& fm)
{
    std::swap(m_width, fm.m_width);
    std::swap(m_height, fm.m_height);
    std::swap(m_area, fm.m_area);
    return *this;
}

}  // namespace maze

maze::FlatMap& operator<<(maze::FlatMap& fm, const maze::LineReader& line)
{
    std::stringstream stream{line.values};
    auto ln{line.number};
    for (auto i{0u}; not stream.eof() or i < fm.size().width; ++i)
    {
        stream >> fm(i, ln);
    }
    return fm;
}

std::ostream& operator<<(std::ostream& ostr, const maze::FlatMap& fm)
{
    auto size = fm.size();
    for (auto i{0u}; i < size.height; ++i)
    {
        ostr << fm(0, i);
        for (auto j{1u}; j < size.width; ++j)
        {
            ostr << ' ' << fm(j, i);
        }
        ostr << '\n';
    }
    ostr << "begin at (" << fm.begin().x << ", " << fm.begin().y
         << ") and end at (" << fm.end().x << ", " << fm.end().y << ")\n";
    return ostr;
}
