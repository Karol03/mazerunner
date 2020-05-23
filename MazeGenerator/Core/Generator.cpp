#include "Generator.hpp"

#include <sstream>

#include "../../Utils/Logger.hpp"

namespace mazegenerator
{
namespace core
{

Generator::Generator(const unsigned width,
                     const unsigned height,
                     const unsigned beginX,
                     const unsigned beginY,
                     const unsigned endX,
                     const unsigned endY)
    : m_builder{width, height, beginX, beginY, endX, endY}
{
    std::stringstream stream;
    stream << width << ' ' << height << ' '
           << beginX << ' ' << beginY << ' '
           << endX << ' ' << endY;
    m_header = stream.str();
}

void Generator::saveHeader(std::ofstream& file) const
{
    file << m_header << '\n';
}

void Generator::saveArea(std::ofstream& file) const
{
    file << m_area << '\n';
}

bool Generator::save(const char* filename)
{
    std::ofstream file(filename, std::ios::app | std::ios::ate);
    if (not isEmpty(file))
    {
        LOG("File with given name \"", filename, "\" already exist");
        return false;
    }

    if (create())
    {
        saveHeader(file);
        saveArea(file);
        return true;
    }

    LOG("Fail during creating a maze");
    return false;
}

bool Generator::create()
{
    m_area = m_builder.create()
                      .toString();
    return not m_area.empty();
}

bool Generator::isEmpty(std::ofstream& file) const
{
    return file.tellp() == 0;
}

}  // namespace core
}  // namespace mazegenerator
