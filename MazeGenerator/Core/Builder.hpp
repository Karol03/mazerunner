#pragma once

#include "Area.hpp"

namespace mazegenerator
{
namespace core
{

class Builder
{
    using Point = Area::Point;
    using PointCollection = Area::PointCollection;

public:
    Builder(const unsigned width,
            const unsigned height,
            const unsigned beginX,
            const unsigned beginY,
            const unsigned endX,
            const unsigned endY);

    Area create();

private:
    enum Field : char { ESpace = 0, EWall = 1, EUnset = 0xFF };

    inline void setField(Area& area, unsigned x, unsigned y, Field type = Field::EWall)
    {
        area(x, y) = static_cast<char>(type);
    }

    void block(Area& area);
    void build(Area& area);
    void overwriteNotSet(Area& area);
    void setEnter(Area& area, Point p);
    bool hunt(Area& area);
    bool kill(Area& area);

private:
    Point m_last;
    unsigned m_width;
    unsigned m_height;
    unsigned m_beginX;
    unsigned m_beginY;
    unsigned m_endX;
    unsigned m_endY;
};

}  // namespace core
}  // namespace mazegenerator
