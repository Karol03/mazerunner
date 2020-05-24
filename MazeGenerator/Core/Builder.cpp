#include "Builder.hpp"

#include "../../Utils/Logger.hpp"
#include "../../Utils/Random.hpp"

namespace mazegenerator
{
namespace core
{

Builder::Builder(const unsigned width,
                 const unsigned height,
                 const unsigned beginX,
                 const unsigned beginY,
                 const unsigned endX,
                 const unsigned endY)
    : m_width{width}
    , m_height{height}
    , m_beginX{beginX}
    , m_beginY{beginY}
    , m_endX{endX}
    , m_endY{endY}
{}

void Builder::block(Area& area)
{
    for(auto i{m_last.first - 1}; i <= m_last.first + 1; ++i)
    {
        for(auto j{m_last.second - 1}; j <= m_last.second + 1; ++j)
        {
            auto point = Point{i, j};
            if(m_last.first == i and m_last.second == j)
            {
                continue;
            }
            if (area.isIn(point) and not area.isBorder(point) and
                area.adjacent(point, Field::ESpace).size() >= 2 and
                area(point) == Field::EUnset)
            {
                area(point) = Field::EWall;
            }
        }
    }
}

bool Builder::hunt(Area& area)
{
    for (auto i{0u}; i < m_width; ++i)
    {
        for (auto j{0u}; j < m_height; ++j)
        {
            if (area(i,j) == Field::EUnset and
                not area.adjacent(i, j, Field::ESpace).empty())
            {
                m_last = {i, j};
                area(m_last) = Field::ESpace;
                block(area);
                return true;
            }
        }
    }
    return false;
}

bool Builder::kill(Area& area)
{
    auto randomizer = utils::Random{};
    auto available = area.adjacent(m_last, Field::EUnset);

    if (available.empty())
    {
        return false;
    }

    m_last = available[randomizer.get(static_cast<unsigned>(available.size()) - 1)];
    area(m_last) = Field::ESpace;
    block(area);
    return true;
}

void Builder::build(Area& area)
{
    m_last = {m_beginX, m_beginY};
    do
    {
        while (kill(area));
    }
    while (hunt(area));
}

void Builder::setEnter(Area& area, Point p)
{
    auto versor = Point{0, 0};
    if (p.first == 0)
    {
        versor = {1, 0};
    }
    else if (p.second == 0)
    {
        versor = {0, 1};
    }
    else if (p.first == m_width - 1)
    {
        versor = {-1, 0};
    }
    else
    {
        versor = {0, -1};
    }

    do
    {
        p.first += versor.first;
        p.second += versor.second;
        area(p) = Field::ESpace;
    }
    while (area.adjacent(p, Field::ESpace).size() < 2);
}

void Builder::overwriteNotSet(Area& area)
{
    for (auto i{0u}; i < m_width; ++i)
    {
        for (auto j{0u}; j < m_height; ++j)
        {
            if (area(i, j) == Field::EUnset)
            {
                area(i, j) = Field::EWall;
            }
        }
    }
}

Area Builder::create()
{
    auto area = Area{m_width, m_height};

    setField(area, m_beginX, m_beginY, ESpace);
    setField(area, m_endX, m_endY, ESpace);

    build(area);
    setEnter(area, {m_endX, m_endY});
    overwriteNotSet(area);

    return area;
}

}  // namespace core
}  // namespace mazegenerator
