#include "ResultsSaver.hpp"

#include <fstream>

#include "../../Utils/Logger.hpp"

namespace maze
{
namespace file
{

ResultsSaver::ResultsSaver(std::string fileName)
    : m_fileName{std::move(fileName)}
{}

void ResultsSaver::save(const std::unique_ptr<solver::Result>& results)
{
    if (m_fileName.empty())
    {
        return;
    }

    if (not results)
    {
        LOG("No results to save");
        return;
    }

    std::ofstream file(m_fileName, std::ios::app | std::ios::ate);
    if (not file.is_open())
    {
        LOG("Cannot open file \"", m_fileName, "\". Results not save");
        return;
    }
    else if (isEmpty(file))
    {
        LOG("The file is empty, add header");
        addHeader(file);
    }
    file << results->toString() << '\n';
    LOG("Results successfully saved");
}

bool ResultsSaver::isEmpty(std::ofstream& file) const
{
    return file.tellp() == 0;
}

void ResultsSaver::addHeader(std::ofstream& file) const
{
    file << solver::Result::header() << '\n';
}

}  // namespace file
}  // namespace maze
