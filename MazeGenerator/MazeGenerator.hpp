#pragma once

#include <string>
#include <utility>

namespace mazegenerator
{

class MazeGenerator
{
public:
    using Size = unsigned;
    using Point = std::pair<int, int>;

    explicit MazeGenerator(Size width, Size height);
    inline MazeGenerator& startAt(Point begin)
    {
        std::swap(begin, m_begin);
        return *this;
    }

    inline MazeGenerator& endAt(Point end)
    {
        std::swap(end, m_end);
        return *this;
    }

    inline MazeGenerator& outputFile(std::string filename)
    {
        std::swap(filename, m_filename);
        return *this;
    }

    bool generate();

private:
    bool isProperlyConfigured() const;
    bool isInRange(const Point&) const;

private:
    std::string m_filename;
    Point m_begin;
    Point m_end;
    Size m_width;
    Size m_height;
};

}  // namespace mazegenerator

