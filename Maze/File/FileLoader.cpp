#include "FileLoader.hpp"

#include <fstream>
#include "../../Utils/Logger.hpp"
#include "../LineReader.hpp"

namespace maze
{
namespace file
{

FileLoader::FileLoader(std::string name)
    : m_name{std::move(name)}
{}

FlatMap* FileLoader::read()
{
    std::ifstream file(m_name);
    if (not file.is_open())
    {
        LOG("Cannot open file named ", m_name);
        return {};
    }

    auto width{0u}, height{0u}, begin_x{0u}, begin_y{0u}, end_x{0u}, end_y{0u};
    file >> width >> height >> begin_x >> begin_y >> end_x >> end_y;
    auto begin = maze::FlatMap::MapPoint{begin_x, begin_y};
    auto end = maze::FlatMap::MapPoint{end_x, end_y};
    if (width < 2 or height < 2)
    {
        LOG("Invalid width(", width, ")/height(", height, "). Both values should be >= 2");
        return {};
    }
    else if (begin == end)
    {
        LOG("Input and output cannot be in the same place");
        return {};
    }

    auto flatMap = new FlatMap{width, height, begin, end};
    LineReader lr;
    std::getline(file, lr.values);
    for (auto i{0u}; i < height; ++i)
    {
        if (std::getline(file, lr.values))
        {
            lr << i;
            *flatMap << lr;
        }
        else
        {
            LOG("Missing rows (", i, ") in the maze file \"", m_name, "\"");
            delete flatMap;
            return {};
        }
    }

    return flatMap;
}

}  // namespace file
}  // namespace maze
